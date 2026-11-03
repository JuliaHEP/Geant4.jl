using Geant4
using Geant4.SystemOfUnits
using FHist, GeometryBasics, Printf
using LinearAlgebra: dot, cross, normalize          ## Geant4 also exports `dot` and `cross`
using GLMakie

include(joinpath(@__DIR__, "XrayTESDetector.jl"))
tes = XrayTESDetector()

struct XrayTESPhysics <: G4VUserPhysicsList
    function XrayTESPhysics(verbose)
        pl = QBBC(verbose)
        ReplacePhysics(pl, move!(G4EmStandardPhysics_option4(verbose)))
        RegisterPhysics(pl, move!(G4RadioactiveDecayPhysics(verbose)))
        return pl
    end
end

gcrFlux(T; ϕ=0.379, m=0.938) = 1.9 * ((T + ϕ) * (T + ϕ + 2m))^-1.39 * T * (T + 2m) /
                               ((1 + 0.4866 * ((T + ϕ) * (T + ϕ + 2m))^-1.255) * (T + ϕ) * (T + ϕ + 2m))

mutable struct GCRGunData <: G4JLGeneratorData
    guns::Dict{Int, CxxPtr{G4ParticleGun}}
    lock::ReentrantLock
    radius::Float64
    center::Float64          ## z of the centre of the sphere
    target::Float64          ## radius of the target sphere around the detector (0 for none)
    emin::Float64
    emax::Float64
end

function GCRGenerator(; radius=27cm, center=8cm, target=0., emin=10MeV, emax=100GeV)
    data = GCRGunData(Dict(), ReentrantLock(), radius, center, target, emin, emax)
    function init(data::GCRGunData, ::Any)
        gun = move!(G4ParticleGun())
        SetParticleByName(gun, "proton")
        lock(data.lock) do
            data.guns[G4Threading!G4GetThreadId()] = gun
        end
    end
    function isotropic()
        cθ = 1 - 2rand()
        sθ, ϕ = sqrt(1 - cθ^2), 2π * rand()
        return Vec3(sθ * cos(ϕ), sθ * sin(ϕ), cθ)
    end
    function generate(evt::G4Event, data::GCRGunData)::Nothing
        gun = data.guns[G4Threading!G4GetThreadId()]
        fmax = 0.268                                   ## maximum of the flux
        T = 0.
        while true
            T = data.emin + rand() * (data.emax - data.emin)
            rand() * fmax <= gcrFlux(T/GeV) && break
        end
        C = Vec3(0., 0., data.center)
        if data.target > 0
            u = isotropic()
            e1 = normalize(cross(u, abs(u[3]) < 0.9 ? Vec3(0., 0., 1.) : Vec3(1., 0., 0.)))
            e2 = cross(u, e1)
            ρ, ϕ = data.target * sqrt(rand()), 2π * rand()
            q = ρ * cos(ϕ) * e1 + ρ * sin(ϕ) * e2      ## point of the disk around the detector
            w = q - C
            s = dot(u, w) + sqrt(dot(u, w)^2 - dot(w, w) + data.radius^2)
            a, dir = q - s * u, u
        else
            a, b = C + data.radius * isotropic(), C + data.radius * isotropic()
            dir = b - a
        end
        SetParticleEnergy(gun, T)
        SetParticlePosition(gun, G4ThreeVector(a...))
        SetParticleMomentumDirection(gun, G4ThreeVector(dir...))
        GeneratePrimaryVertex(gun, CxxPtr(evt))
    end
    G4JLPrimaryGenerator("GCRGun", data; init_method=init, generate_method=generate)
end

function intensity(data::GCRGunData)
    T = exp.(range(log(data.emin/GeV), log(data.emax/GeV), length=10000))
    return sum(diff(T) .* (gcrFlux.(T[1:end-1]) .+ gcrFlux.(T[2:end])) ./ 2) / cm2 / s
end
function exposure(data::GCRGunData, n)
    r = data.target > 0 ? data.target : data.radius
    return n / (4π^2 * r^2 * intensity(data))
end

generator = GCRGenerator(target=5cm)

struct PixelHit
    event::Int
    pixel::Int
    edep::Float64
    acd::Float64             ## energy in the ACD in the same event
end

mutable struct Deposit
    event::Int
    track::Int
    parent::Int
    particle::String
    process::String          ## creator process ("primary" for the primary protons)
    pixel::Int               ## first pixel hit
    lastpixel::Int
    vertexEnergy::Float64    ## kinetic energy at creation
    entryEnergy::Float64     ## kinetic energy when entering the absorber
    edep::Float64
end

mutable struct XrayTESSimData <: G4JLSimulationData
    ##---Event data---------------------------------------------------------------------------------
    event::Int
    tracks::Dict{Int, Deposit}                 ## deposits of the current event by track ID
    pixels::Dict{Int, Float64}                 ## energy in each pixel in the current event
    acd::Float64                               ## energy in the ACD in the current event
    ##---Run data-----------------------------------------------------------------------------------
    deposits::Vector{Deposit}
    hits::Vector{PixelHit}
    primaries::Vector{Float64}                 ## kinetic energy of the primaries
    pixelEdep::Vector{Float64}
    pixelTracks::Vector{Int}
    XrayTESSimData(npixels=317) = new(0, Dict(), Dict(), 0., Deposit[], PixelHit[], Float64[], zeros(npixels), zeros(Int, npixels))
end

function Base.merge!(x::XrayTESSimData, y::XrayTESSimData)
    append!(x.deposits, y.deposits)
    append!(x.hits, y.hits)
    append!(x.primaries, y.primaries)
    x.pixelEdep .+= y.pixelEdep
    x.pixelTracks .+= y.pixelTracks
    return x
end
function Base.empty!(x::XrayTESSimData)
    empty!(x.deposits)
    empty!(x.hits)
    empty!(x.primaries)
    fill!(x.pixelEdep, 0)
    fill!(x.pixelTracks, 0)
    return x
end

function beginrun(::G4Run, app::G4JLApplication)::Nothing
    empty!(getSIMdata(app))
    return
end

function endrun(::G4Run, app::G4JLApplication)::Nothing
    if G4Threading!G4GetThreadId() < 0 && app.nthreads > 0
        foldl(merge!, app.simdata[2:end]; init=app.simdata[1])
    end
    return
end

function beginevent(evt::G4Event, app::G4JLApplication)::Nothing
    data = getSIMdata(app)
    data.event = GetEventID(evt)
    empty!(data.tracks)
    empty!(data.pixels)
    data.acd = 0.
    return
end

function pretrackaction(track::G4Track, app::G4JLApplication)::Nothing
    GetParentID(track) == 0 && push!(getSIMdata(app).primaries, GetKineticEnergy(track))
    return
end

function stepaction(step::G4Step, app::G4JLApplication)::Nothing
    pre = GetPreStepPoint(step)
    pv = GetPhysicalVolume(pre)
    if pv != app.detector.absorberPV
        GetLogicalVolume(pv) in app.detector.acdLVs && (getSIMdata(app).acd += GetTotalEnergyDeposit(step))
        return
    end
    data = getSIMdata(app)
    track = GetTrack(step)
    id = GetTrackID(track)
    pixel = GetCopyNumber(GetTouchable(pre), 1) + 1
    dep = get(data.tracks, id, nothing)
    if isnothing(dep)
        creator = GetCreatorProcess(track)
        process = creator == C_NULL ? "primary" : String(GetProcessName(creator))
        particle = String(GetParticleName(GetParticleDefinition(track)))
        dep = Deposit(data.event, id, GetParentID(track), particle, process, pixel, 0,
                      GetVertexKineticEnergy(track), GetKineticEnergy(pre), 0.)
        data.tracks[id] = dep
    end
    if pixel != dep.lastpixel
        data.pixelTracks[pixel] += 1
        dep.lastpixel = pixel
    end
    edep = GetTotalEnergyDeposit(step)
    dep.edep += edep
    data.pixelEdep[pixel] += edep
    data.pixels[pixel] = get(data.pixels, pixel, 0.) + edep
    return
end

function endevent(::G4Event, app::G4JLApplication)::Nothing
    data = getSIMdata(app)
    append!(data.deposits, values(data.tracks))
    for (pixel, edep) in data.pixels
        edep > 0 && push!(data.hits, PixelHit(data.event, pixel, edep, data.acd))
    end
    return
end

app = G4JLApplication(; detector = tes,                               ## detector with parameters
                        simdata = XrayTESSimData(),                   ## simulation data structure
                        generator = generator,                        ## primary particle generator
                        nthreads = 8,                                 ## number of threads (MT)
                        physics_type = XrayTESPhysics,                ## what physics list to instantiate
                        stepaction_method = stepaction,               ## step action method
                        pretrackaction_method = pretrackaction,       ## pre-tracking action
                        begineventaction_method = beginevent,         ## begin-event action
                        endeventaction_method = endevent,             ## end-event action
                        beginrunaction_method = beginrun,             ## begin run action
                        endrunaction_method = endrun                  ## end run action
                      );

configure(app)
em = G4EmParameters!Instance()
SetFluo(em, true)
SetAuger(em, true)
SetPixe(em, true)
SetDeexcitationIgnoreCut(em, false)
SetDeexActiveRegion(em, innerRegion, true, true, true)
AddPhysics(em, innerRegion, "G4EmStandardSS")
SetMuHadLateralDisplacement(em, false)
SetBremsstrahlungTh(em, 10e3GeV)                ## 10 TeV
ui`/run/setCut 1 mm`
initialize(app)

world = GetWorldVolume()
fig = Figure(size=(1200, 600))
s1 = LScene(fig[1,1])
Geant4.draw!(s1, world, clip=:y)
s2 = LScene(fig[1,2])
Geant4.draw!(s2, tes.arrayPV)
display(fig)

data = app.simdata[1]
nevents = 50000
@time beamOn(app, nevents)
deposits = filter(d -> d.edep > 0, data.deposits)
T = exposure(generator.data, nevents)
@printf "GCR intensity: %.3f protons/(cm² s sr), exposure time: %.2f s\n" intensity(generator.data)*cm2*s T/s
@printf "Tracks with deposits in the absorbers: %d, in %d events\n" length(deposits) length(unique(d.event for d in deposits))

fig = Figure(size=(800, 500))
ax = Axis(fig[1,1], title="GCR protons", xlabel="Kinetic energy [GeV]", ylabel="Protons / GeV", xscale=log10, yscale=log10)
edges = 10 .^ range(-2, 2, length=41)
h = Hist1D(data.primaries/GeV; binedges=edges)
widths = diff(edges)
scatter!(ax, bincenters(h), bincounts(h) ./ widths, label="generated")
norm = length(data.primaries) / (sum(gcrFlux.(bincenters(h)) .* widths))
lines!(ax, bincenters(h), norm * gcrFlux.(bincenters(h)), color=:red, label="PAMELA 2009")
axislegend(ax)
display(fig)

pixels = pixelPositions(tes)
fig = Figure(size=(1200, 500))
for (i, (values, title, label)) in enumerate(((data.pixelEdep/keV, "Energy deposit", "keV"),
                                               (data.pixelTracks, "Tracks", "tracks")))
    ax = Axis(fig[1, 2i-1], title=title, xlabel="x [mm]", ylabel="y [mm]", aspect=DataAspect())
    sc = scatter!(ax, first.(pixels), last.(pixels), color=values, marker=:rect, markersize=18, colormap=:viridis)
    Colorbar(fig[1, 2i], sc, label=label)
end
display(fig)

category(p) = p in ("proton", "gamma", "e-", "e+") ? p : "other"
cats = ["proton", "gamma", "e-", "e+", "other"]
counts = [count(d -> category(d.particle) == c, deposits) for c in cats]
procs = sort(unique(d.process for d in deposits), by = p -> -count(d -> d.process == p, deposits))
pcounts = [count(d -> d.process == p, deposits) for p in procs]
fig = Figure(size=(1200, 450))
ax1 = Axis(fig[1,1], title="Particles", xticks=(1:length(cats), cats), ylabel="Tracks")
barplot!(ax1, 1:length(cats), counts)
ax2 = Axis(fig[1,2], title="Creator process", xticks=(1:length(procs), procs), xticklabelrotation=π/4, ylabel="Tracks")
barplot!(ax2, 1:length(procs), pcounts)
display(fig)

primary = filter(d -> d.parent == 0, deposits)
fig = Figure(size=(1200, 450))
for (i, (field, title)) in enumerate(((:vertexEnergy, "Energy at creation"), (:entryEnergy, "Energy at the absorber"), (:edep, "Energy deposit")))
    ax = Axis(fig[1,i], title=title, xlabel="Energy [keV]", ylabel="Tracks", xscale=log10)
    edges = 10 .^ range(-1, 8, length=91)
    energies = [getfield(d, field)/keV for d in deposits]
    stephist!(ax, Hist1D(clamp.(energies, 0.1, 1e8); binedges=edges), label="all")
    isempty(primary) || stephist!(ax, Hist1D(clamp.([getfield(d, field)/keV for d in primary], 0.1, 1e8); binedges=edges), label="primary protons")
    i == 1 && axislegend(ax, position=:lt)
end
display(fig)

area = length(pixels) * (tes.pixelPitch - tes.pixelGap)^2
edges = 10 .^ range(-1, 3, length=41)
fig = Figure(size=(800, 500))
ax = Axis(fig[1,1], title="Background in the TES array", xlabel="Energy [keV]", ylabel="counts / (cm² s keV)",
          xscale=log10, yscale=log10)
for (sel, label) in ((h -> true, "all"), (h -> h.acd < 20keV, "ACD veto (20 keV)"))
    h = Hist1D([hit.edep/keV for hit in data.hits if sel(hit)]; binedges=edges)
    rate = bincounts(h) ./ diff(edges) ./ (area/cm2) ./ (T/s)
    band = filter(x -> 2keV <= x.edep <= 10keV && sel(x), data.hits)
    @printf "%-18s: %.3g counts/(cm² s keV) in 2-10 keV\n" label length(band) / 8 / (area/cm2) / (T/s)
    stairs!(ax, edges, [rate; rate[end]], step=:post, label=label)
end
hlines!(ax, [5e-3], color=:gray, linestyle=:dash, label="requirement")
ylims!(ax, 1e-4, 10)
axislegend(ax, position=:rt)
display(fig)
