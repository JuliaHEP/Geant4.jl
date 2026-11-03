using Geant4
using Geant4.SystemOfUnits
using Printf
using GLMakie

include(joinpath(@__DIR__, "MedicalLinacDetector.jl"))
linac = MedicalLinacDetector(fieldSide = 10cm)

struct MedicalLinacPhysics <: G4VUserPhysicsList
    function MedicalLinacPhysics(verbose)
        pl = QBBC(verbose)
        ReplacePhysics(pl, move!(G4EmStandardPhysics_option4(verbose)))
        for type in (3, 5, 6, 7, 8)       ## EmExtra, HadronElastic, HadronInelastic, Stopping, Ions
            RemovePhysics(pl, type)
        end
        return pl
    end
end

mutable struct LinacGunData <: G4JLGeneratorData
    guns::Dict{Int, CxxPtr{G4ParticleGun}}
    lock::ReentrantLock
    z::Float64               ## start position along the beam
    radius::Float64
    meanEnergy::Float64
    sigmaEnergy::Float64
    sigmaAngle::Float64      ## standard deviation of sin θ
end

function LinacGenerator(; radius=1mm, meanEnergy=12MeV, sigmaEnergy=0.127MeV, sigmaAngle=0.003)
    data = LinacGunData(Dict(), ReentrantLock(), 0., radius, meanEnergy, sigmaEnergy, sigmaAngle)
    function init(data::LinacGunData, app)
        data.z = -app.detector.sourceToSkinDistance - 5mm
        gun = move!(G4ParticleGun())
        SetParticleByName(gun, "e-")
        lock(data.lock) do
            data.guns[G4Threading!G4GetThreadId()] = gun
        end
    end
    function generate(evt::G4Event, data::LinacGunData)::Nothing
        gun = data.guns[G4Threading!G4GetThreadId()]
        sθ = data.sigmaAngle * randn()
        cθ, ϕ = sqrt(1 - sθ^2), 2π * rand()
        ρ, α = data.radius * rand(), 2π * rand()
        SetParticleEnergy(gun, data.meanEnergy + data.sigmaEnergy * randn())
        SetParticlePosition(gun, G4ThreeVector(ρ * sin(α), ρ * cos(α), data.z))
        SetParticleMomentumDirection(gun, G4ThreeVector(sθ * cos(ϕ), sθ * sin(ϕ), cθ))
        GeneratePrimaryVertex(gun, CxxPtr(evt))
    end
    G4JLPrimaryGenerator("LinacGun", data; init_method=init, generate_method=generate)
end

function stepaction(step::G4Step, app::G4JLApplication)::Nothing
    track = GetTrack(step)
    dir = GetMomentumDirection(track)
    dz = z(dir)
    det = app.detector
    if dz < 0 || GetPhysicalVolume(GetPostStepPoint(step)) in det.jawPVs
        SetTrackStatus(track, fStopAndKill)
    elseif GetPhysicalVolume(GetPreStepPoint(step)) in det.filterPVs
        tanmax = det.ffRadius / det.ffZ
        (abs(x(dir) / dz) > tanmax || abs(y(dir) / dz) > tanmax) && SetTrackStatus(track, fStopAndKill)
    end
    return
end

stackaction(track::G4Track, ::G4JLApplication) = z(GetMomentumDirection(track)) < 0 ? fKill : fUrgent

mesh = G4JLScoringMesh("boxMesh_1",
                       BoxMesh(127.5mm, 127.5mm, 127.5mm),
                       translation = (0, 0, 130mm),
                       bins = (51, 51, 51),
                       quantities = [doseDeposit("dDep")])

app = G4JLApplication(; detector = linac,                             ## detector with parameters
                        generator = LinacGenerator(),                 ## primary particle generator
                        nthreads = 8,                                 ## number of threads (MT)
                        physics_type = MedicalLinacPhysics,           ## what physics list to instantiate
                        stepaction_method = stepaction,               ## step action method
                        stackaction_method = stackaction,             ## stacking action method
                        scorers = [mesh])                             ## list of scorers

configure(app)
ui`/run/setCut 1 mm`
em = G4EmParameters!Instance()
for region in ("TargetR", "primaryCollimatorR", "VacWindowR", "ffR", "IonChamberR", "JawsR",
               "DefaultRegionForTheWorld"), process in ("eBrem", "compt", "phot", "conv", "annihil")
    ActivateSecondaryBiasing(em, process, region, 1000., 100MeV)
end
SetDirectionalSplitting(em, true)
SetDirectionalSplittingTarget(em, G4ThreeVector(0, 0, 0))
SetDirectionalSplittingRadius(em, 15cm)
initialize(app)

function sideview!(s, zmin, zmax; distance=0.5, tilt=0.3, fov=15)
    zc, d = (zmin + zmax)/2, distance * (zmax - zmin) * tand(22.5) / tand(fov/2)
    cam = cameracontrols(s.scene)
    cam.fov[] = fov                       ## narrow field of view: little perspective distortion
    update_cam!(s.scene, cam, Vec3f(tilt * d, d, zc), Vec3f(0, 0, zc), Vec3f(1, 0, 0))
    cam.settings.center[] = false         ## keep this view when the figure is displayed
end
fig = Figure(size=(1200, 900))
s1 = LScene(fig[1,1], show_axis=false)
Geant4.draw!(s1, GetVolume("accWorld")[], clip=:y)
sideview!(s1, -20mm, 490mm, distance=0.7)
s2 = LScene(fig[2,1], show_axis=false)
Geant4.draw!(s2, GetWorldVolume(), clip=:y)
sideview!(s2, -920mm, 260mm, distance=0.38)
rowsize!(fig.layout, 1, Relative(0.62))
display(fig)

nevents = 100_000
ui`/run/printProgress 20000`
@time beamOn(app, nevents)

dose, _, _ = mesh.dDep
nb = mesh.bins[1]
centers = range(-127.5mm + 2.5mm, 127.5mm - 2.5mm, length=nb)
depths = centers .+ 130mm
c = (nb + 1) ÷ 2                      ## central voxel
avg(a; dims) = vec(sum(a; dims) / prod(size(a, d) for d in dims))

axis = avg(dose[c-2:c+2, c-2:c+2, :], dims=(1, 2))
imax = argmax(axis)
pdd = 100 * axis / axis[imax]
d10 = pdd[argmin(abs.(depths .- 100mm))]
@printf "Depth of the maximum dose: %.1f cm\n" depths[imax]/cm
@printf "PDD at 10 cm depth       : %.1f %%\n" d10
@printf "Dose at the maximum      : %.3g Gy per electron\n" axis[imax] / nevents

fig = Figure(size=(800, 500))
ax = Axis(fig[1,1], xlabel="Depth [cm]", ylabel="Dose [% of maximum]", title="Percentage depth dose (10 × 10 cm², SSD 90 cm)")
scatterlines!(ax, depths/cm, pdd, markersize=6)
ylims!(ax, 0, 110)
display(fig)

fig = Figure(size=(800, 500))
ax = Axis(fig[1,1], xlabel="x [cm]", ylabel="Dose [% of maximum on axis]", title="Lateral profiles")
norm = axis[imax]
for d in (depths[imax], 100mm, 200mm)
    k = argmin(abs.(depths .- d))
    profile = avg(dose[:, c-2:c+2, k-1:k+1], dims=(2, 3))
    scatterlines!(ax, centers/cm, 100 * profile / norm, markersize=6, label=@sprintf("%.1f cm", depths[k]/cm))
end
vlines!(ax, [-5, 5], color=:gray, linestyle=:dash)
axislegend(ax, position=:rt)
display(fig)

fig = Figure(size=(800, 650))
ax = Axis(fig[1,1], xlabel="x [cm]", ylabel="Depth [cm]", title="Dose in the plane y = 0", yreversed=true, aspect=DataAspect())
hm = heatmap!(ax, centers/cm, depths/cm, 100 * dose[:, c, :] / norm, colormap=:jet, colorrange=(0, 110))
Colorbar(fig[1,2], hm, label="Dose [%]")
display(fig)
