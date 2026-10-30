using Geant4
using Geant4.SystemOfUnits
using Geant4.PhysicalConstants
using FHist, GeometryBasics, Printf
using LinearAlgebra: dot, normalize          ## Geant4 also exports `dot`
using GLMakie

include(joinpath(@__DIR__, "RICHDetector.jl"))
rich = RICHDetector()

fig = Figure(size=(1000, 400))
ax1 = Axis(fig[1,1], title="C₄F₁₀ refractive index", xlabel="Photon energy [eV]", ylabel="n - 1")
lines!(ax1, photonEnergies/eV, c4f10RIndex.(photonEnergies) .- 1)
ax2 = Axis(fig[1,2], title="Aerogel scattering length", xlabel="Photon energy [eV]", ylabel="Length [cm]", yscale=log10)
lines!(ax2, photonEnergies/eV, aerogelRayleigh.(photonEnergies)/cm)
ax3 = Axis(fig[1,3], title="Quantum efficiency", xlabel="Photon energy [eV]", ylabel="QE")
lines!(ax3, photonEnergies/eV, quantumEfficiency.(photonEnergies))
display(fig)

struct RICHPhysics <: G4VUserPhysicsList
    function RICHPhysics(verbose)
        pl = FTFP_BERT(verbose)
        RegisterPhysics(pl, move!(G4OpticalPhysics(verbose)))
        return pl
    end
end

mutable struct RICHGunData <: G4JLGeneratorData
    gun::Union{Nothing, CxxPtr{G4ParticleGun}}
    particles::Vector{String}
    pmin::Float64
    pmax::Float64
    θmin::Float64
    θmax::Float64
    ##---the current track
    particle::String
    mass::Float64
    momentum::Float64
    direction::Vec3{Float64}
end

function RICHGunGenerator(; particles=["pi+", "kaon+", "proton"], pmin=1GeV, pmax=80GeV, θmin=50mrad, θmax=250mrad)
    data = RICHGunData(nothing, particles, pmin, pmax, θmin, θmax, "", 0., 0., Vec3(0.,0.,1.))
    function init(data::RICHGunData, ::Any)
        data.gun = move!(G4ParticleGun())
        SetParticlePosition(data.gun, G4ThreeVector(0, 0, 0))
    end
    function generate(evt::G4Event, data::RICHGunData)::Nothing
        gun = data.gun
        data.particle = rand(data.particles)
        SetParticleByName(gun, data.particle)
        data.mass = gun |> GetParticleDefinition |> GetPDGMass
        data.momentum = data.pmin * (data.pmax/data.pmin)^rand()
        cosθ = cos(data.θmin) - rand() * (cos(data.θmin) - cos(data.θmax))    ## uniform in solid angle
        sinθ, ϕ = sqrt(1 - cosθ^2), 2π * rand()
        data.direction = Vec3(sinθ * cos(ϕ), sinθ * sin(ϕ), cosθ)
        SetParticleEnergy(gun, sqrt(data.momentum^2 + data.mass^2) - data.mass)    ## kinetic energy
        SetParticleMomentumDirection(gun, G4ThreeVector(data.direction...))
        GeneratePrimaryVertex(gun, CxxPtr(evt))
    end
    G4JLPrimaryGenerator("RICHGun", data; init_method=init, generate_method=generate)
end
generator = RICHGunGenerator()

struct Hit
    position::Point3{Float64}
    energy::Float64
    radiator::Symbol            ## :aerogel or :gas
    primary::Bool               ## produced by the primary track
end
struct Photon
    event::Int
    θc::Float64                 ## reconstructed Cherenkov angle
    radiator::Symbol
    primary::Bool
end
struct Track
    particle::String
    mass::Float64
    momentum::Float64
    direction::Vec3{Float64}
end

mutable struct RICHSimData <: G4JLSimulationData
    ##---Cached pointers----------------------------------------------------------------------------
    opticalphoton::CxxPtr{G4ParticleDefinition}
    ##---Event data---------------------------------------------------------------------------------
    hits::Vector{Hit}
    paths::Dict{Int, Vector{Point3{Float64}}}     ## points of each track, when recordPaths is true
    detected::Set{Int}                             ## IDs of the tracks of detected photons
    recordPaths::Bool
    ##---Run data-----------------------------------------------------------------------------------
    tracks::Vector{Track}
    photons::Vector{Photon}
    eventHits::Vector{Vector{Hit}}                 ## hits of the first events, for the displays
    RICHSimData() = new(CxxPtr{G4ParticleDefinition}(C_NULL), Hit[], Dict(), Set{Int}(), false, Track[], Photon[], [])
end

function reflectionPoint(E, D, C, R)
    a, b = E - C, D - C
    â = normalize(a)
    ĉ = normalize(b - dot(b, â) * â)
    mirrorpoint(φ) = C + R * (cos(φ) * â + sin(φ) * ĉ)
    function g(φ)                                  ## difference of the cosines of the two angles
        M = mirrorpoint(φ)
        m = normalize(M - C)
        dot(normalize(E - M), m) - dot(normalize(D - M), m)
    end
    lo, hi = 0., atan(dot(b, ĉ), dot(b, â))
    for _ in 1:40
        mid = (lo + hi) / 2
        g(mid) < 0 ? (lo = mid) : (hi = mid)
    end
    return mirrorpoint((lo + hi) / 2)
end

function sphereIntersection(t, C, R)
    b = dot(t, C)
    return b + sqrt(b^2 - dot(C, C) + R^2)
end

const nGas = c4f10RIndex(3.2eV)

function cherenkovAngle(det::RICHDetector, track::Track, hit::Hit)
    t = track.direction
    side = hit.position[2] > 0 ? 1 : -1
    C = Point3{Float64}(mirrorCentre(det, side)...)
    zAerogel = det.aerogelZ + det.aerogelThickness
    if hit.radiator == :aerogel
        s = (det.aerogelZ + det.aerogelThickness/2) / t[3]
    else
        s = (zAerogel / t[3] + sphereIntersection(t, C, det.mirrorRadius)) / 2
    end
    E = Point3{Float64}(s * t)
    M = reflectionPoint(E, hit.position, C, det.mirrorRadius)
    d = normalize(M - E)
    if hit.radiator == :aerogel
        dt = Vec3(d[1], d[2], 0.) * nGas / det.aerogelRIndex
        d = Vec3(dt[1], dt[2], sqrt(1 - dot(dt, dt)))
    end
    return acos(clamp(dot(d, t), -1., 1.))
end

function expectedAngle(n, m, p)
    β = p / sqrt(p^2 + m^2)
    nβ = n * β
    return nβ > 1 ? acos(1/nβ) : NaN
end

function beginrun(run::G4Run, app::G4JLApplication)::Nothing
    data = getSIMdata(app)
    data.opticalphoton = FindParticle("opticalphoton")
    empty!(data.tracks)
    empty!(data.photons)
    empty!(data.eventHits)
    return
end

function beginevent(evt::G4Event, app::G4JLApplication)::Nothing
    data = getSIMdata(app)
    empty!(data.hits)
    empty!(data.paths)
    empty!(data.detected)
    return
end

function pretrackaction(track::G4Track, app::G4JLApplication)::Nothing
    data = getSIMdata(app)
    data.recordPaths || return
    p = GetPosition(track)[]
    push!(get!(data.paths, GetTrackID(track), Point3{Float64}[]), Point3{Float64}(x(p), y(p), z(p)))
    return
end

function stepaction(step::G4Step, app::G4JLApplication)::Nothing
    data = getSIMdata(app)
    track = GetTrack(step)
    post = GetPostStepPoint(step)
    if data.recordPaths
        p = GetPosition(post)[]
        push!(data.paths[GetTrackID(track)], Point3{Float64}(x(p), y(p), z(p)))
    end
    GetParticleDefinition(track) == data.opticalphoton || return
    GetStepStatus(post) == fGeomBoundary || return
    pv = GetPhysicalVolume(post)
    (pv == C_NULL || !startswith(String(GetName(pv)), "Photodetector")) && return
    SetTrackStatus(track, fStopAndKill)
    energy = GetTotalEnergy(track)
    rand() < quantumEfficiency(energy) || return
    p = GetPosition(post)[]
    vertex = GetVertexPosition(track)[]
    radiator = z(vertex) < app.detector.aerogelZ + app.detector.aerogelThickness + 1mm ? :aerogel : :gas
    push!(data.hits, Hit(Point3{Float64}(x(p), y(p), z(p)), energy, radiator, GetParentID(track) == 1))
    push!(data.detected, GetTrackID(track))
    return
end

function endevent(evt::G4Event, app::G4JLApplication)::Nothing
    data = getSIMdata(app)
    gen = app.generator.data
    track = Track(gen.particle, gen.mass, gen.momentum, gen.direction)
    push!(data.tracks, track)
    ievt = length(data.tracks)
    for hit in data.hits
        push!(data.photons, Photon(ievt, cherenkovAngle(app.detector, track, hit), hit.radiator, hit.primary))
    end
    length(data.eventHits) < 100 && push!(data.eventHits, copy(data.hits))
    return
end

app = G4JLApplication(; detector = rich,                              ## detector with parameters
                        simdata = RICHSimData(),                      ## simulation data structure
                        generator = generator,                        ## primary particle generator
                        nthreads = 0,                                 ## # of threads (0 = no MT)
                        physics_type = RICHPhysics,                   ## what physics list to instantiate
                        stepaction_method = stepaction,               ## step action method
                        pretrackaction_method = pretrackaction,       ## pre-tracking action
                        begineventaction_method = beginevent,         ## begin-event action
                        endeventaction_method = endevent,             ## end-event action
                        beginrunaction_method = beginrun              ## begin run action
                      );

configure(app)
initialize(app)

data = getSIMdata(app)
data.recordPaths = true
generator.data.particles, generator.data.pmin, generator.data.pmax = ["pi+"], 10GeV, 10GeV
beamOn(app, 1)
data.recordPaths = false

fig = Figure(size=(1200, 900))
s = LScene(fig[1,1])
Geant4.draw!(s, GetWorldVolume())
for (id, path) in data.paths
    if id == 1
        lines!(s, path, color=:red, linewidth=2)
    elseif id in data.detected
        vertex = path[1][3] < rich.aerogelZ + rich.aerogelThickness + 1mm
        lines!(s, path, color = vertex ? (:yellow, 0.5) : (:blue, 0.3), linewidth=1)
    end
end
for hits in data.eventHits
    scatter!(s, [p.position[1] for p in hits], [p.position[2] for p in hits], [p.position[3] + 0.1cm for p in hits],
             markersize=6, color=[p.radiator == :aerogel ? :yellow : :blue for p in hits])
end
display(fig)

generator.data.particles, generator.data.pmin, generator.data.pmax = ["pi+", "kaon+", "proton"], 1GeV, 80GeV
@time beamOn(app, 1000)

tracks, photons = data.tracks, data.photons
@printf "Number of tracks: %d, detected photons: %d\n" length(tracks) length(photons)
for rad in (:aerogel, :gas)
    sel = [p for p in photons if p.radiator == rad && p.primary]
    nfired = count(t -> expectedAngle(rad == :aerogel ? rich.aerogelRIndex : nGas, t.mass, t.momentum) > 0, tracks)
    @printf "%-8s: %6.1f detected photons per track above threshold\n" rad length(sel)/max(nfired, 1)
end

fig = Figure(size=(1000, 900))
for (i, side) in enumerate((1, -1))
    ax = Axis(fig[i,1], title = side > 0 ? "Top photodetector" : "Bottom photodetector",
              xlabel="x [cm]", ylabel="y [cm]", aspect=DataAspect())
    xlims!(ax, -rich.detectorHalfX/cm, rich.detectorHalfX/cm)
    ylims!(ax, side .* rich.detectorY ./ cm |> extrema)
    for hits in data.eventHits[1:20]
        h = [hit for hit in hits if sign(hit.position[2]) == side]
        isempty(h) && continue
        scatter!(ax, [p.position[1]/cm for p in h], [p.position[2]/cm for p in h], markersize=5,
                 color=[p.radiator == :aerogel ? :orange : :blue for p in h])
    end
end
display(fig)

masses = Dict("pi+" => (139.57MeV, :red, "π"), "kaon+" => (493.68MeV, :green, "K"), "proton" => (938.27MeV, :blue, "p"))
pgrid = exp.(range(log(1GeV), log(80GeV), length=200))
fig = Figure(size=(1200, 500))
for (i, (rad, n, ymax)) in enumerate(((:aerogel, rich.aerogelRIndex, 300), (:gas, nGas, 70)))
    ax = Axis(fig[1,i], title = rad == :aerogel ? "Aerogel" : "C₄F₁₀",
              xlabel="Momentum [GeV/c]", ylabel="θc [mrad]", xscale=log10)
    sel = [p for p in photons if p.radiator == rad && p.primary]
    scatter!(ax, [tracks[p.event].momentum/GeV for p in sel], [p.θc/mrad for p in sel],
             markersize=2, color=(:black, 0.2))
    for (name, (m, c, label)) in masses
        lines!(ax, pgrid/GeV, expectedAngle.(n, m, pgrid)/mrad, color=c, label=label)
    end
    ylims!(ax, 0, ymax)
    axislegend(ax, position=:rb)
end
display(fig)

fig = Figure(size=(1200, 450))
for (i, (rad, n)) in enumerate(((:aerogel, rich.aerogelRIndex), (:gas, nGas)))
    Δθ = Float64[]
    for p in photons
        (p.radiator == rad && p.primary) || continue
        t = tracks[p.event]
        θ = expectedAngle(n, t.mass, t.momentum)
        isnan(θ) || push!(Δθ, (p.θc - θ)/mrad)
    end
    h = Hist1D(Δθ; binedges=range(-10, 10, length=101))
    core = filter(x -> abs(x) < 5, Δθ)
    μ, σ = sum(core)/length(core), sqrt(sum(abs2, core .- sum(core)/length(core))/length(core))
    ax = Axis(fig[1,i], title = (rad == :aerogel ? "Aerogel" : "C₄F₁₀") * @sprintf(" (core σ = %.2f mrad)", σ),
              xlabel="θc(reconstructed) - θc(expected) [mrad]", ylabel="Photons")
    stephist!(ax, h)
end
display(fig)

function trackAngle(θs, σ)
    isempty(θs) && return NaN
    μ = sum(θs) / length(θs)
    for _ in 1:3
        sel = filter(θ -> abs(θ - μ) < 3σ, θs)
        isempty(sel) && return NaN
        μ = sum(sel) / length(sel)
    end
    return μ
end

fig = Figure(size=(1200, 500))
for (i, (rad, n, σ, pmax)) in enumerate(((:aerogel, rich.aerogelRIndex, 5mrad, 15GeV), (:gas, nGas, 2mrad, 80GeV)))
    ax = Axis(fig[1,i], title = rad == :aerogel ? "Aerogel" : "C₄F₁₀",
              xlabel="Momentum [GeV/c]", ylabel="Reconstructed mass [MeV/c²]", xscale=log10)
    θs = [Float64[] for _ in tracks]
    for p in photons
        p.radiator == rad && p.primary && push!(θs[p.event], p.θc)
    end
    for (name, (m, c, label)) in masses
        idx = [j for (j, t) in enumerate(tracks) if t.particle == name && t.momentum < pmax && length(θs[j]) >= 3]
        θ = [trackAngle(θs[j], σ) for j in idx]
        mass = [tracks[j].momentum * sqrt(max(n^2 * cos(θ[k])^2 - 1, 0.)) for (k, j) in enumerate(idx)]
        scatter!(ax, [tracks[j].momentum/GeV for j in idx], mass/MeV, color=c, markersize=5, label=label)
    end
    ylims!(ax, 0, 1500)
    axislegend(ax, position=:lt)
end
display(fig)
