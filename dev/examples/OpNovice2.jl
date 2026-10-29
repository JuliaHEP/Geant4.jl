using Geant4
using Geant4.SystemOfUnits
using Geant4.PhysicalConstants
using FHist, Plots, Printf

include(joinpath(@__DIR__, "OpDetector.jl"))

electron_detector = OpDetector(
    tankMaterial = "G4_BGO",
    worldMaterial = "G4_AIR",
    tankProperties = PropertyMap(
        "ABSLENGTH" => ([2eV, 5eV, 8eV], [1mm, 2mm, 3mm]),
        "RAYLEIGH"  => ([2eV, 8eV], [1mm, 1mm]),
        "RINDEX"    => ([2eV, 8eV], [1.3, 1.4]),
        "SCINTILLATIONCOMPONENT1" => ([2eV, 5eV, 8eV], [1.0, 1.1, 1.3]),
        "SCINTILLATIONCOMPONENT2" => ([2eV, 3eV, 4eV, 5eV, 6eV, 7eV, 8eV], [0.1, 0.2, 0.4, 0.6, 0.8, 0.9, 1.0]),
        "SCINTILLATIONCOMPONENT3" => ([2eV, 5eV, 8eV], [0.2, 0.1, 0.05])),
    tankConstProperties = ConstPropertyMap(
        "SCINTILLATIONTIMECONSTANT1" => 20ns,
        "SCINTILLATIONTIMECONSTANT2" => 100ns,
        "SCINTILLATIONTIMECONSTANT3" => 200ns,
        "SCINTILLATIONYIELD"  => 5000/MeV,
        "SCINTILLATIONYIELD1" => 1.0,
        "SCINTILLATIONYIELD2" => 1.0,
        "SCINTILLATIONYIELD3" => 0.1,
        "RESOLUTIONSCALE" => 1.0,
        "SCINTILLATIONRISETIME1" => 3ns,
        "SCINTILLATIONRISETIME2" => 10ns,
        "SCINTILLATIONRISETIME3" => 20ns),
    worldProperties = PropertyMap(
        "RINDEX"    => ([2eV, 8eV], [1.01, 1.01]),
        "ABSLENGTH" => ([2eV, 5eV, 8eV], [100mm, 100mm, 100mm])),
    surfaceFinish = ground,
    surfaceSigmaAlpha = 0.2,
    surfaceProperties = PropertyMap(
        "SPECULARLOBECONSTANT"  => ([2eV, 8eV], [0.1, 0.1]),
        "SPECULARSPIKECONSTANT" => ([2eV, 8eV], [0.1, 0.1]),
        "BACKSCATTERCONSTANT"   => ([2eV, 8eV], [0.1, 0.1]),
        "TRANSMITTANCE"         => ([2eV, 8eV], [0.1, 0.1]),
        "REFLECTIVITY"          => ([2eV, 8eV], [0.8, 0.8]),
        "EFFICIENCY"            => ([2eV, 8eV], [0.1, 0.1])))

fresnel_detector = OpDetector(
    tankProperties = PropertyMap("RINDEX"    => ([2eV, 8eV], [1.4, 1.41]),
                                 "ABSLENGTH" => ([2eV, 5eV, 8eV], [100mm, 200mm, 300mm])),
    worldProperties = PropertyMap("RINDEX"    => ([2eV, 8eV], [1.01, 1.01]),
                                  "ABSLENGTH" => ([2eV, 5eV, 8eV], [1000m, 2000m, 3000m])),
    surfaceProperties = PropertyMap("REFLECTIVITY" => ([2eV, 8eV], [1.0, 1.0])),
    surfaceType = dielectric_dielectric,
    surfaceModel = unified,
    surfaceFinish = polished)

struct OpNovice2Physics <: G4VUserPhysicsList
    function OpNovice2Physics(verbose)
        pl = FTFP_BERT(verbose)
        ReplacePhysics(pl, move!(G4EmStandardPhysics_option4(verbose)))
        RegisterPhysics(pl, move!(G4OpticalPhysics(verbose)))
        return pl
    end
end

@with_kw mutable struct OpGunData <: G4JLGeneratorData
    gun::Union{Nothing, CxxPtr{G4ParticleGun}} = nothing
    particle::String = "e+"
    energy::Float64 = 500keV
    position::NTuple{3,Float64} = (0., 0., 0.)
    direction::NTuple{3,Float64} = (1., 0., 0.)
    randomDirection::Bool = false
    polarization::Union{Nothing, Float64} = nothing
end

function photonPolarization(k::NTuple{3,Float64}, angle::Float64)
    (kx, ky, kz) = k
    modul2 = ky^2 + kz^2                                   ## |normal × k|² with normal = (1,0,0)
    e_perp = modul2 > 0 ? (0., -kz, ky) ./ sqrt(modul2) : (0., 0., 1.)
    e_para = (e_perp[2]*kz - e_perp[3]*ky,                 ## e_perp × k
              e_perp[3]*kx - e_perp[1]*kz,
              e_perp[1]*ky - e_perp[2]*kx)
    return cos(angle) .* e_para .+ sin(angle) .* e_perp
end

function OpGunGenerator(; kwargs...)
    data = OpGunData(; kwargs...)
    function init(data::OpGunData, ::Any)
        data.gun = move!(G4ParticleGun())
        setgun!(data)
    end
    function generate(evt::G4Event, data::OpGunData)::Nothing
        gun = data.gun
        if data.randomDirection
            theta = π/2 * rand()
            phi = 2π * rand()
            data.direction = (cos(theta), sin(theta)*sin(phi), sin(theta)*cos(phi))
            SetParticleMomentumDirection(gun, G4ThreeVector(data.direction...))
        end
        if data.particle == "opticalphoton"
            angle = isnothing(data.polarization) ? 2π * rand() : data.polarization
            SetParticlePolarization(gun, G4ThreeVector(photonPolarization(data.direction, angle)...))
        end
        GeneratePrimaryVertex(gun, CxxPtr(evt))
    end
    G4JLPrimaryGenerator("OpGun", data; init_method=init, generate_method=generate)
end

function setgun!(data::OpGunData; kwargs...)
    for (k, v) in kwargs
        setproperty!(data, k, v)
    end
    data.direction = data.direction ./ sqrt(sum(data.direction .^ 2))     ## normalize the direction
    gun = data.gun
    isnothing(gun) && return             ## the gun is created later, at initialization
    SetParticleByName(gun, data.particle)
    SetParticleEnergy(gun, data.energy)
    SetParticlePosition(gun, G4ThreeVector(data.position...))
    SetParticleMomentumDirection(gun, G4ThreeVector(data.direction...))
    SetParticleTime(gun, 0.)
    return
end
setgun!(gen::G4JLPrimaryGenerator{OpGunData}; kwargs...) = setgun!(gen.data; kwargs...)

generator = OpGunGenerator(particle = "e-", energy = 1MeV, position = (-1m, 0., 0.), direction = (1., 0., 0.))

const Hist = typeof(Hist1D(; counttype=Float64, binedges=0.:1.:1.))
newhist(edges) = Hist1D(; counttype=Float64, binedges=edges)
const HISTOS = [ ## name                  binning         title                                       x-axis
                 (:cerenkov,            0.:0.1:10.,     "Cerenkov spectrum",                        "Energy [eV]"),
                 (:scint,               0.:0.1:10.,     "Scintillation spectrum",                   "Energy [eV]"),
                 (:scint_time,          0.:0.5:200.,    "Scintillation creation time",              "Time [ns]"),
                 (:wls_abs,             0.:0.1:10.,     "WLS absorption spectrum",                  "Energy [eV]"),
                 (:wls_em,              0.:0.1:10.,     "WLS emission spectrum",                    "Energy [eV]"),
                 (:wls_time,            0.:0.1:10.,     "WLS emission time",                        "Time [ns]"),
                 (:wls2_abs,            0.:0.1:10.,     "WLS2 absorption spectrum",                 "Energy [eV]"),
                 (:wls2_em,             0.:0.1:10.,     "WLS2 emission spectrum",                   "Energy [eV]"),
                 (:wls2_time,           0.:0.5:50.,     "WLS2 emission time",                       "Time [ns]"),
                 (:bdry_status,         -0.5:1.:43.5,   "Boundary process status",                  "Status code"),
                 (:x_backward,          -1.1:0.022:1.1, "X momentum dir of backward-going photons", "Direction cosine"),
                 (:y_backward,          -1.1:0.022:1.1, "Y momentum dir of backward-going photons", "Direction cosine"),
                 (:z_backward,          -1.1:0.022:1.1, "Z momentum dir of backward-going photons", "Direction cosine"),
                 (:x_forward,           -1.1:0.022:1.1, "X momentum dir of forward-going photons",  "Direction cosine"),
                 (:y_forward,           -1.1:0.022:1.1, "Y momentum dir of forward-going photons",  "Direction cosine"),
                 (:z_forward,           -1.1:0.022:1.1, "Z momentum dir of forward-going photons",  "Direction cosine"),
                 (:x_fresnel,           -1.1:0.022:1.1, "X momentum dir of Fresnel-refracted photons", "Direction cosine"),
                 (:y_fresnel,           -1.1:0.022:1.1, "Y momentum dir of Fresnel-refracted photons", "Direction cosine"),
                 (:z_fresnel,           -1.1:0.022:1.1, "Z momentum dir of Fresnel-refracted photons", "Direction cosine"),
                 (:fresnel_refraction,  0.:1.:90.,      "Fresnel-refracted photons",                "Angle [deg]"),
                 (:fresnel_reflection,  0.:1.:90.,      "Fresnel-reflected photons",                "Angle [deg]"),
                 (:tir,                 0.:1.:90.,      "Total internal reflected photons",         "Angle [deg]"),
                 (:reflection,          0.:1.:90.,      "Fresnel-reflected plus TIR photons",       "Angle [deg]"),
                 (:absorption,          0.:1.:90.,      "Absorbed photons",                         "Angle [deg]"),
                 (:transmission,        0.:1.:90.,      "Transmitted photons",                      "Angle [deg]"),
                 (:spike_reflection,    0.:1.:90.,      "Spike reflected photons",                  "Angle [deg]") ]

const STATUS_NAMES = Dict(Int(getfield(Geant4, n)) => String(n) for n in names(Geant4)
                          if isdefined(Geant4, n) && getfield(Geant4, n) isa G4OpBoundaryProcessStatus)

mutable struct OpNovice2SimData <: G4JLSimulationData
    ##---Settings and cached pointers--------------------------------------------------------------
    killOnSecondSurface::Bool       ## kill photons when they reach a second surface
    summary::Bool                   ## print the summary at the end of the run
    opticalphoton::CxxPtr{G4ParticleDefinition}
    boundary::CxxPtr{G4OpBoundaryProcess}
    ##---Per-track state (TrackInformation in C++)-------------------------------------------------
    firstTankX::Bool
    reflectionNumber::Int
    ##---Run data-----------------------------------------------------------------------------------
    particle::String
    energy::Float64
    polarization::Union{Nothing, Float64}
    cerenkovEnergy::Float64
    scintEnergy::Float64
    wlsAbsorptionEnergy::Float64
    wlsEmissionEnergy::Float64
    wls2AbsorptionEnergy::Float64
    wls2EmissionEnergy::Float64
    cerenkovCount::Int
    scintCount::Int
    rayleighCount::Int
    wlsAbsorptionCount::Int
    wlsEmissionCount::Int
    wls2AbsorptionCount::Int
    wls2EmissionCount::Int
    opAbsorption::Int
    opAbsorptionPrior::Int
    totalSurface::Int
    boundaryProcs::Dict{Int, Int}
    histos::Dict{Symbol, Hist}
    OpNovice2SimData(; killOnSecondSurface=false, summary=true) = new(killOnSecondSurface, summary)
end

function beginrun(run::G4Run, app::G4JLApplication)::Nothing
    data = getSIMdata(app)
    gen = app.generator.data
    data.particle, data.energy, data.polarization = gen.particle, gen.energy, gen.polarization
    data.opticalphoton = FindParticle("opticalphoton")
    data.boundary = CxxPtr{G4OpBoundaryProcess}(C_NULL)
    for p in data.opticalphoton |> GetProcessManager |> GetProcessList
        if p |> GetProcessName |> String == "OpBoundary"
            data.boundary = CxxPtr{G4OpBoundaryProcess}(p)
        end
    end
    data.cerenkovEnergy = data.scintEnergy = 0.
    data.wlsAbsorptionEnergy = data.wlsEmissionEnergy = 0.
    data.wls2AbsorptionEnergy = data.wls2EmissionEnergy = 0.
    data.cerenkovCount = data.scintCount = data.rayleighCount = 0
    data.wlsAbsorptionCount = data.wlsEmissionCount = 0
    data.wls2AbsorptionCount = data.wls2EmissionCount = 0
    data.opAbsorption = data.opAbsorptionPrior = data.totalSurface = 0
    data.boundaryProcs = Dict{Int, Int}()
    data.histos = Dict(name => newhist(edges) for (name, edges, _, _) in HISTOS)
    nothing
end

function mean_rms(h)
    c, x = bincounts(h), bincenters(h)
    n = sum(c)
    n > 0 || return (0., 0.)
    m = sum(c .* x) / n
    return m, sqrt(max(sum(c .* x.^2) / n - m^2, 0.))
end

function endrun(run::G4Run, app::G4JLApplication)::Nothing
    data = getSIMdata(app)
    det = app.detector
    nEvt = GetNumberOfEvent(run)
    nEvt == 0 && return
    (; histos, boundaryProcs) = data
    ##---Normalize the refraction/reflection histograms to the photons at each angle-------------
    h_refract, h_reflect = histos[:fresnel_refraction], histos[:reflection]
    tot = bincounts(h_refract) .+ bincounts(h_reflect)
    for h in (h_refract, h_reflect)
        counts, w2 = bincounts(h), sumw2(h)
        for i in eachindex(tot)
            tot[i] > 0 || continue
            counts[i] /= tot[i]
            w2[i] /= tot[i]^2
        end
    end
    data.summary || return

    @printf "\n    Run Summary\n"
    @printf "---------------------------------\n"
    @printf "Primary particle was: %s with energy %s.\n" data.particle (data.energy < keV ? "$(data.energy/eV) eV" : "$(data.energy/MeV) MeV")
    @printf "Number of events: %d\n" nEvt
    @printf "Material of world: %s\n" det.worldMaterial
    @printf "Material of tank:  %s\n\n" det.tankMaterial
    if data.particle != "opticalphoton"
        @printf "Average energy of Cerenkov photons created per event: %.2f eV.\n" data.cerenkovEnergy/eV/nEvt
        @printf "Average number of Cerenkov photons created per event: %.2f\n" data.cerenkovCount/nEvt
        data.cerenkovCount > 0 && @printf " Average energy per photon: %.2f eV.\n" data.cerenkovEnergy/eV/data.cerenkovCount
        @printf "Average energy of scintillation photons created per event: %.2f eV.\n" data.scintEnergy/eV/nEvt
        @printf "Average number of scintillation photons created per event: %.2f\n" data.scintCount/nEvt
        data.scintCount > 0 && @printf " Average energy per photon: %.2f eV.\n" data.scintEnergy/eV/data.scintCount
    end
    @printf "Average number of photons absorbed by WLS per event: %.2f\n" data.wlsAbsorptionCount/nEvt
    data.wlsAbsorptionCount > 0 && @printf " Average energy per photon: %.2f eV.\n" data.wlsAbsorptionEnergy/eV/data.wlsAbsorptionCount
    @printf "Average number of photons created by WLS per event: %.2f\n" data.wlsEmissionCount/nEvt
    data.wlsEmissionCount > 0 && @printf " Average energy per photon: %.2f eV.\n" data.wlsEmissionEnergy/eV/data.wlsEmissionCount
    @printf "Average number of photons absorbed by WLS2 per event: %.2f\n" data.wls2AbsorptionCount/nEvt
    data.wls2AbsorptionCount > 0 && @printf " Average energy per photon: %.2f eV.\n" data.wls2AbsorptionEnergy/eV/data.wls2AbsorptionCount
    @printf "Average number of photons created by WLS2 per event: %.2f\n" data.wls2EmissionCount/nEvt
    data.wls2EmissionCount > 0 && @printf " Average energy per photon: %.2f eV.\n" data.wls2EmissionEnergy/eV/data.wls2EmissionCount
    @printf "Average number of OpRayleigh per event:   %.2f\n" data.rayleighCount/nEvt
    @printf "Average number of OpAbsorption per event: %.2f\n" data.opAbsorption/nEvt
    @printf "\nSurface events (on +X surface, maximum one per photon) this run:\n"
    @printf "# of primary particles:      %8d\n" nEvt
    @printf "OpAbsorption before surface: %8d\n" data.opAbsorptionPrior
    @printf "Total # of surface events:   %8d\n" data.totalSurface
    if data.particle == "opticalphoton"
        @printf "Unaccounted for:             %8d\n" data.totalSurface + data.opAbsorptionPrior - nEvt
    end
    @printf "\nSurface events by process:\n"
    for status in sort(collect(keys(boundaryProcs)))
        @printf "  %-38s %8d\n" STATUS_NAMES[status] boundaryProcs[status]
    end
    total = sum(values(boundaryProcs); init=0)
    @printf " Sum:                        %8d\n" total
    @printf " Unaccounted for:            %8d\n" data.totalSurface - total
    @printf "---------------------------------\n"

    ##---Brewster angle and critical angle------------------------------------------------------
    if sum(tot) > 0 && !isnothing(data.polarization) && det.surfaceType != coated
        refract, reflect = bincounts(h_refract), bincounts(h_reflect)
        centers = bincenters(h_refract)
        halfwidth = binedges(h_refract)[2] - centers[1]
        n1 = propertyValue(det.tankProperties, "RINDEX", data.energy)
        n2 = propertyValue(det.worldProperties, "RINDEX", data.energy)
        @printf "Polarization of primary optical photons: %.1f deg.\n" data.polarization/deg
        if data.polarization == 0.
            filled = findall(>(0), tot)
            imins = filled[reflect[filled] .== minimum(reflect[filled])]     ## can be several bins with 0
            amin = sum(centers[imins]) / length(imins)
            @printf "Reflectance shows a minimum at: %.1f +/- %.1f deg. Expected Brewster angle: %.2f deg.\n" amin halfwidth*length(imins) atand(n2/n1)
        end
        i = findfirst(i -> refract[i] > 0 && refract[i+1] == 0, 1:length(refract)-1)
        if !isnothing(i)
            @printf "Fresnel transmission goes to 0 at: %.1f +/- %.1f deg. Expected: %.2f deg.\n" centers[i] halfwidth asind(n2/n1)
        end
    end

    ##---Histogram statistics------------------------------------------------------------------
    @printf "\n Histogram statistics for the entire run:\n\n"
    for (name, _, title, xaxis) in HISTOS
        h = histos[name]
        nentries(h) == 0 && continue
        name in (:fresnel_refraction, :reflection) && continue   ## normalized
        m, s = mean_rms(h)
        @printf " %s: mean = %g; rms = %g (%s)\n" title m s xaxis
    end
    nothing
end

function pretrackaction(track::G4Track, app::G4JLApplication)::Nothing
    data = getSIMdata(app)
    data.firstTankX = true
    data.reflectionNumber = 0
    nothing
end

function secondariesInCurrentStep(step::G4Step)
    nsec = GetNumberOfSecondariesInCurrentStep(step)
    nsec == 0 && return CxxPtr{G4Track}[]
    allsecs = GetSecondary(step)[]
    nall = length(allsecs)
    return [allsecs[i] for i in nall-nsec+1:nall]
end

function boundaryStatus!(data::OpNovice2SimData, status::Int, angle::Float64, p1)
    (; histos) = data
    data.boundaryProcs[status] = get(data.boundaryProcs, status, 0) + 1
    push!(histos[:bdry_status], status)
    if status == Int(Transmission)
        push!(histos[:transmission], angle)
    elseif status == Int(FresnelRefraction)
        push!(histos[:x_fresnel], p1[1])
        push!(histos[:y_fresnel], p1[2])
        push!(histos[:z_fresnel], p1[3])
        push!(histos[:fresnel_refraction], angle)
    elseif status == Int(FresnelReflection)
        push!(histos[:fresnel_reflection], angle)
        push!(histos[:reflection], angle)
    elseif status == Int(TotalInternalReflection)
        push!(histos[:tir], angle)
        push!(histos[:reflection], angle)
    elseif status == Int(CoatedDielectricRefraction) || status == Int(CoatedDielectricFrustratedTransmission)
        push!(histos[:fresnel_refraction], angle)
    elseif status == Int(CoatedDielectricReflection)
        push!(histos[:reflection], angle)
    elseif status == Int(SpikeReflection)
        push!(histos[:spike_reflection], angle)
    elseif status == Int(Absorption)
        push!(histos[:absorption], angle)
    end
    return
end

function stepaction(step::G4Step, app::G4JLApplication)::Nothing
    data = getSIMdata(app)
    (; histos) = data
    track = GetTrack(step)
    startPoint = GetPreStepPoint(step)
    endPoint = GetPostStepPoint(step)

    if GetDefinition(track) == data.opticalphoton
        procname = endPoint |> GetProcessDefinedStep |> GetProcessName |> String
        if procname == "OpAbsorption"
            data.opAbsorption += 1
            data.firstTankX && (data.opAbsorptionPrior += 1)
        elseif procname == "OpRayleigh"
            data.rayleighCount += 1
        elseif procname == "OpWLS" || procname == "OpWLS2"
            wls1 = procname == "OpWLS"
            en = GetKineticEnergy(track)
            if wls1
                data.wlsAbsorptionCount += 1; data.wlsAbsorptionEnergy += en
            else
                data.wls2AbsorptionCount += 1; data.wls2AbsorptionEnergy += en
            end
            push!(histos[wls1 ? :wls_abs : :wls2_abs], en/eV)
            for sec in secondariesInCurrentStep(step)
                en = GetKineticEnergy(sec)
                if wls1
                    data.wlsEmissionCount += 1; data.wlsEmissionEnergy += en
                else
                    data.wls2EmissionCount += 1; data.wls2EmissionEnergy += en
                end
                push!(histos[wls1 ? :wls_em : :wls2_em], en/eV)
                push!(histos[wls1 ? :wls_time : :wls2_time], GetGlobalTime(sec)/ns)
            end
        end

        ##---optical process has the end point on a boundary
        if GetStepStatus(endPoint) == fGeomBoundary
            p0 = GetMomentumDirection(startPoint)
            p1 = GetMomentumDirection(endPoint)
            if data.firstTankX
                dir1 = (x(p1), y(p1), z(p1))
                ##---do not count Absorbed or Detected photons here
                if GetTrackStatus(track) != fStopAndKill
                    if dir1[1] < 0.
                        push!(histos[:x_backward], dir1[1])
                        push!(histos[:y_backward], dir1[2])
                        push!(histos[:z_backward], dir1[3])
                    else
                        push!(histos[:x_forward], dir1[1])
                        push!(histos[:y_forward], dir1[2])
                        push!(histos[:z_forward], dir1[3])
                    end
                end
                data.firstTankX = false
                data.totalSurface += 1
                angle = acos(x(p0))/deg
                boundaryStatus!(data, Int(GetStatus(data.boundary)), angle, dir1)
            end
            ##---Kill the photon when it reaches a second surface (there are 2 steps at the boundary).
            #   This can be useful to visualize surface scattering.
            if data.killOnSecondSurface && data.reflectionNumber >= 2
                SetTrackStatus(track, fStopAndKill)
            end
            data.reflectionNumber += 1
        end
    else
        ##---Count the optical photons created in this step
        for sec in secondariesInCurrentStep(step)
            GetDefinition(sec) == data.opticalphoton || continue
            creator = sec |> GetCreatorProcess |> GetProcessName |> String
            en = GetKineticEnergy(sec)
            if creator == "Cerenkov"
                data.cerenkovEnergy += en
                data.cerenkovCount += 1
                push!(histos[:cerenkov], en/eV)
            elseif creator == "Scintillation"
                data.scintEnergy += en
                data.scintCount += 1
                push!(histos[:scint], en/eV)
                push!(histos[:scint_time], GetGlobalTime(sec)/ns)
            end
        end
    end
    nothing
end

app = G4JLApplication(detector = electron_detector,             ## detector with parameters
                      simdata = OpNovice2SimData(),              ## simulation data structure
                      generator = generator,                     ## primary particle generator
                      physics_type = OpNovice2Physics,           ## what physics list to instantiate
                      nthreads = 0,                              ## sequential mode
                      ##----Actions--------------------------------
                      stepaction_method = stepaction,            ## step action method
                      pretrackaction_method = pretrackaction,    ## pre-tracking action (reset track state)
                      beginrunaction_method = beginrun,          ## begin-run action (reset counters and histograms)
                      endrunaction_method = endrun               ## end-run action (print summary)
                      )

configure(app)
ui`/process/optical/cerenkov/setMaxPhotons 3`
ui`/process/optical/cerenkov/setMaxBetaChange 10`
ui`/process/optical/scintillation/setByParticleType false`
ui`/process/optical/scintillation/setTrackInfo false`
ui`/process/optical/scintillation/setFiniteRiseTime true`
ui`/process/optical/scintillation/setStackPhotons true`
initialize(app)

beamOn(app, 100)

function plot_photons(data::OpNovice2SimData)
    (; histos) = data
    lay = @layout [° °; °]
    img = plot(layout=lay, size=(1000,800), legend=false)
    plot!(subplot=1, histos[:cerenkov], title="Cerenkov spectrum", xlabel="Energy [eV]")
    plot!(subplot=2, histos[:scint], title="Scintillation spectrum", xlabel="Energy [eV]")
    plot!(subplot=3, histos[:scint_time], title="Scintillation creation time", xlabel="Time [ns]")
    return img
end
img = plot_photons(app.simdata[1])
display(img)

reinitialize(app, fresnel_detector)

setgun!(generator, particle = "opticalphoton", energy = 5eV, position = (99.99cm, 0., 0.),
        randomDirection = true, polarization = 0.)
beamOn(app, 100000)

function plot_fresnel(data::OpNovice2SimData; title="", expected=nothing)
    (; histos, polarization) = data
    img = plot(title="$title polarization angle $(round(polarization/deg)) deg", xlabel="Incident angle [deg]",
               ylabel="Fraction of photons", legend=:right, size=(800,500))
    plot!(img, histos[:fresnel_refraction], label="Refraction")
    plot!(img, histos[:reflection], label="Reflection (including TIR)")
    if !isnothing(expected)
        angles = 0:0.25:90
        plot!(img, angles, expected.(angles .* deg), label="Expected reflectance", color=:black, linewidth=2)
    end
    return img
end
img = plot_fresnel(app.simdata[1])
display(img)

setgun!(generator, polarization = 90deg)
beamOn(app, 100000)
img = plot_fresnel(app.simdata[1])
display(img)

coated_detector = OpDetector(
    tankProperties = PropertyMap("RINDEX"    => ([2eV, 8eV], [1.4, 1.4]),
                                 "ABSLENGTH" => ([2eV, 5eV, 8eV], [100mm, 200mm, 300mm])),
    worldProperties = PropertyMap("RINDEX"    => ([2eV, 8eV], [1.0, 1.0]),
                                  "ABSLENGTH" => ([2eV, 5eV, 8eV], [1000m, 2000m, 3000m])),
    surfaceType = coated,
    surfaceModel = unified,
    surfaceFinish = polished,
    surfaceProperties = PropertyMap("REFLECTIVITY" => ([2eV, 8eV], [1.0, 1.0]),
                                    "COATEDRINDEX" => ([2eV, 8eV], [1.7, 1.7])),
    surfaceConstProperties = ConstPropertyMap("COATEDTHICKNESS" => 100nm))
reinitialize(app, coated_detector)

function thinFilmReflectance(θ, pol; n1=1.4, nc=1.7, n3=1.0, d=100nm, λ=h_Planck*c_light/5eV)
    c1 = cos(θ)
    cc = sqrt(complex(1 - (n1*sin(θ)/nc)^2))          ## cosine of the angle in the coating
    c3 = sqrt(complex(1 - (n1*sin(θ)/n3)^2))          ## cosine of the angle in the second medium
    if pol == :s
        r12 = (n1*c1 - nc*cc) / (n1*c1 + nc*cc)
        r23 = (nc*cc - n3*c3) / (nc*cc + n3*c3)
    else  ## :p
        r12 = (nc*c1 - n1*cc) / (nc*c1 + n1*cc)
        r23 = (n3*cc - nc*c3) / (n3*cc + nc*c3)
    end
    phase = exp(2im * (2π/λ) * nc * d * cc)
    return abs2((r12 + r23*phase) / (1 + r12*r23*phase))
end

setgun!(generator, particle = "opticalphoton", energy = 5eV, position = (99.99cm, 0., 0.),
        direction = (1., 0., 0.), randomDirection = false, polarization = 0.)
beamOn(app, 100000)
let procs = app.simdata[1].boundaryProcs
    reflected = get(procs, Int(CoatedDielectricReflection), 0) / sum(values(procs))
    @printf "Reflectance at normal incidence: %.4f, expected %.4f\n" reflected thinFilmReflectance(0., :p)
end

setgun!(generator, randomDirection = true, polarization = 0.)
beamOn(app, 100000)
img = plot_fresnel(app.simdata[1], title="Coated surface,", expected = θ -> thinFilmReflectance(θ, :p))
display(img)

setgun!(generator, polarization = 90deg)
beamOn(app, 100000)
img = plot_fresnel(app.simdata[1], title="Coated surface,", expected = θ -> thinFilmReflectance(θ, :s))
display(img)

boundary_detector = OpDetector(
    tankProperties = PropertyMap("RINDEX"    => ([2eV, 8eV], [1.3, 1.4]),
                                 "ABSLENGTH" => ([2eV, 5eV, 8eV], [1000m, 2000m, 3000m])),
    worldProperties = PropertyMap("RINDEX"    => ([2eV, 8eV], [1.01, 1.01]),
                                  "ABSLENGTH" => ([2eV, 5eV, 8eV], [1000m, 2000m, 3000m])),
    surfaceProperties = PropertyMap(
        "SPECULARLOBECONSTANT"  => ([2eV, 8eV], [0.1, 0.1]),
        "SPECULARSPIKECONSTANT" => ([2eV, 8eV], [0.1, 0.1]),
        "BACKSCATTERCONSTANT"   => ([2eV, 8eV], [0.1, 0.1]),
        "TRANSMITTANCE"         => ([2eV, 8eV], [0.1, 0.1]),
        "REFLECTIVITY"          => ([2eV, 8eV], [0.8, 0.8]),
        "EFFICIENCY"            => ([2eV, 8eV], [0.1, 0.1]),
        "RINDEX"                => ([2eV, 8eV], [1.4, 1.5])),
    surfaceSigmaAlpha = 0.2)

const rough = ConstPropertyMap("SURFACEROUGHNESS" => 0.01)
boundary_cases = [
    # label                            model     type                  finish                 other parameters
    ("unified ground",                  unified, dielectric_dielectric, ground,                (;)),
    ("unified polished",                unified, dielectric_dielectric, polished,              (;)),
    ("unified polished rough",          unified, dielectric_dielectric, polished,              (surfaceConstProperties=rough,)),
    ("unified polishedfrontpainted",    unified, dielectric_dielectric, polishedfrontpainted,  (;)),
    ("unified groundfrontpainted",      unified, dielectric_dielectric, groundfrontpainted,    (;)),
    ("unified polishedbackpainted",     unified, dielectric_dielectric, polishedbackpainted,   (;)),
    ("unified groundbackpainted",       unified, dielectric_dielectric, groundbackpainted,     (;)),
    ("unified metal polished",          unified, dielectric_metal,      polished,              (;)),
    ("unified metal ground",            unified, dielectric_metal,      ground,                (;)),
    ("glisur polished",                 glisur,  dielectric_dielectric, polished,              (;)),
    ("glisur polished rough",           glisur,  dielectric_dielectric, polished,              (surfaceConstProperties=rough,)),
    ("glisur ground",                   glisur,  dielectric_dielectric, ground,                (surfacePolish=0.2,)),
    ("glisur polishedfrontpainted",     glisur,  dielectric_dielectric, polishedfrontpainted,  (;)),
    ("glisur polishedbackpainted",      glisur,  dielectric_dielectric, polishedbackpainted,   (;)),
    ("glisur groundfrontpainted",       glisur,  dielectric_dielectric, groundfrontpainted,    (;)),
    ("glisur groundbackpainted",        glisur,  dielectric_dielectric, groundbackpainted,     (surfacePolish=0.2,)),
    ("glisur metal polished",           glisur,  dielectric_metal,      polished,              (;)),
    ("glisur metal ground",             glisur,  dielectric_metal,      ground,                (surfacePolish=0.2,)),
    ("DAVIS RoughTeflon_LUT",           DAVIS,   dielectric_LUTDAVIS,   RoughTeflon_LUT,       (;)),
    ("DAVIS Detector_LUT",              DAVIS,   dielectric_LUTDAVIS,   Detector_LUT,          (;)),
    ("LUT polishedlumirrorair",         LUT,     dielectric_LUT,        polishedlumirrorair,   (;)) ]

data = app.simdata[1]
data.killOnSecondSurface = true
data.summary = false
setgun!(generator, energy = 3eV, position = (0., 0., 0.), direction = (0.9, 0.44, 0.),
        randomDirection = false, polarization = nothing)
results = Pair{String, Dict{Int,Int}}[]
for (label, model, type, finish, other) in boundary_cases
    reinitialize(app, OpDetector(boundary_detector; surfaceModel=model, surfaceType=type, surfaceFinish=finish, other...))
    beamOn(app, 10000)
    push!(results, label => copy(data.boundaryProcs))
end

for (label, procs) in results
    total = sum(values(procs))
    line = join(["$(STATUS_NAMES[s]) $(round(100*n/total, digits=1))" for (s, n) in sort(collect(procs), by=last, rev=true)], ", ")
    @printf "%-30s %s\n" label line
end

function plot_boundary(results)
    statuses = sort(unique(s for (_, procs) in results for s in keys(procs)))
    fractions = [get(procs, s, 0) / sum(values(procs)) for (_, procs) in results, s in statuses]
    nrows, ncols = size(fractions)
    img = heatmap(1:ncols, 1:nrows, fractions, yflip=true, clims=(0, 1), color=:viridis,
                  xticks=(1:ncols, [STATUS_NAMES[s] for s in statuses]), xrotation=45,
                  yticks=(1:nrows, first.(results)), size=(1100, 850),
                  bottom_margin=20Plots.mm, left_margin=5Plots.mm, title="Percentage of photons by boundary status")
    for i in 1:nrows, j in 1:ncols
        f = fractions[i, j]
        f >= 0.005 && annotate!(img, j, i, Plots.text(round(Int, 100f), 7, f > 0.5 ? :black : :white))
    end
    return img
end
img = plot_boundary(results)
display(img)
