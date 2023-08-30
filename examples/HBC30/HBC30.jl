using Revise
using Geant4
using Geant4.SystemOfUnits
using Printf, GeometryBasics
using GLMakie, Rotations, IGLWrap_jll  # to force loding G4Vis extension

import Geant4.SystemOfUnits:tesla

include(joinpath(@__DIR__, "DetectorHBC30.jl"))

hbc30 = HBC30()


#---Define Simulation Data struct------------------------------------------------------------------
struct Track
    particle::String
    charge::Int
    energy::Float64
    points::Vector{Point3{Float64}}
end
mutable struct HBC30SimData <: G4JLSimulationData
    #---Run data-----------------------------------------------------------------------------------
    fParticle::String
    fEkin::Float64
    #---tracks-------------------------------------------------------------------------------------
    tracks::Vector{Track}
    HBC30SimData() = new("", 0.0, [])
end

#---Actions----------------------------------------------------------------------------------------
#---Step action------------------------------------------------------------------------------------
function stepaction(step::G4Step, app::G4JLApplication)::Nothing
    tracks = getSIMdata(app).tracks
    p = GetPosition(GetPostStepPoint(step))
    push!(tracks[end].points, Point3{Float64}(x(p),y(p),z(p)))
    return
end
#---Tracking pre-action---------------------------------------------------------------------------- 
function pretrackaction(track::G4Track, app::G4JLApplication)::Nothing
    tracks = getSIMdata(app).tracks
    p = GetPosition(track)[]
    particle = track |> GetParticleDefinition
    name = particle |> GetParticleName |> String
    charge = particle |> GetPDGCharge |> Int
    energy = track |> GetKineticEnergy
    push!(tracks, Track(name, charge, energy, [Point3{Float64}(x(p),y(p),z(p))]))
    return
end
#---Begin-event-action---------------------------------------------------------------------------- 
function beginevent(::G4Event, app::G4JLApplication)::Nothing
    empty!(getSIMdata(app).tracks)
    return
end
#---Begin Run Action-------------------------------------------------------------------------------
function beginrun(run::G4Run, app::G4JLApplication)::Nothing
    data = getSIMdata(app)
    gun = app.generator.data.gun
    data.fParticle = gun |> GetParticleDefinition |> GetParticleName |> String
    data.fEkin = gun |> GetParticleEnergy
    return
end

#--------------------------------------------------------------------------------------------------
#---Particle Gun initialization--------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------
particlegun = G4JLGunGenerator(particle = "proton", 
                               energy = 10GeV, 
                               direction = G4ThreeVector(0,-1,0), 
                               position = G4ThreeVector(0, hbc30.worldZHalfLength,0))

#--------------------------------------------------------------------------------------------------
#---Magnetic Field initialization------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------
bfield = G4JLUniformMagField(G4ThreeVector(0,0, 1.5tesla))

#--------------------------------------------------------------------------------------------------
#---Create the Application-------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------
app = G4JLApplication(; detector = hbc30,                             # detector with parameters
                        simdata = HBC30SimData(),                     # simulation data structure
                        generator = particlegun,                      # primary particle generator
                        field = bfield,                               # uniform magnetic field
                        nthreads = 0,                                 # # of threads (0 = no MT)
                        physics_type = FTFP_BERT,                     # what physics list to instantiate
                        stepaction_method = stepaction,               # step action method
                        begineventaction_method = beginevent,         # begin-event action (initialize per-event data)
                        pretrackaction_method = pretrackaction,       # pre-tracking action
                        beginrunaction_method = beginrun              # begin run action
                      )
              
#---Configure, Initialize and Run------------------------------------------------------------------                      
configure(app)
initialize(app)

#---Draw function----------------------------------------------------------------------------------
function drawevent(app)
    world = GetWorldVolume()
    data = app.simdata[1]
    fig = Figure(resolution=(2048,2028))
    s = LScene(fig[1,1])
    Geant4.draw!(s, world)
    for t in data.tracks
        style = t.charge > 0. ? :solid : :dot
        lines!(t.points, linestyle=style)
        if t.energy > data.fEkin/20
            text!(t.points[end], text=t.particle)
        end
    end
    display(fig)
end

#---Run One event and display-----------------------------------------------------------------------
#ui`/tracking/verbose 1`
beamOn(app,1)
drawevent(app)

