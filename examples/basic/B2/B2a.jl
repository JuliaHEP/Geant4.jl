using Geant4
using Geant4.SystemOfUnits

#---Define Detector Parameters struct--------------------------------------------------------------
include(joinpath(@__DIR__, "DetectorB2a.jl"))

#---Define Simulation Data struct------------------------------------------------------------------
using GeometryBasics
mutable struct B2aSimData <: G4JLSimulationData
  tracks::Vector{Vector{Point3{Float64}}}   # vector of vector of step positions
  B2aSimData() = new([])
end

#---Particle Gun initialization--------------------------------------------------------------------
function gun_initialize(gen::G4JLParticleGun, det::G4JLDetector)
  pg = GetGun(gen)
  SetParticleByName(pg, "proton")
  SetParticleEnergy(pg, 3GeV)
  SetParticleMomentumDirection(pg, G4ThreeVector(0,0,1))
  SetParticlePosition(pg, G4ThreeVector(0,0,-16cm))
  SetParticlePosition(pg, G4ThreeVector(0, 0, -det.worldZHalfLength))
end
Geant4.getInitializer(::G4JLParticleGun) = gun_initialize

#--------------------------------------------------------------------------------------------------
#----Actions---------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------
#---Step action------------------------------------------------------------------------------------
function stepaction(step::G4Step, app::G4JLApplication)::Nothing
  tracks = app.simdata.tracks
  p = GetPosition(GetPostStepPoint(step))
  push!(tracks[end], Point3{Float64}(x(p),y(p),z(p)))
  nothing
end
#---Tracking pre-action---------------------------------------------------------------------------- 
function pretrackaction(track::G4Track, app::G4JLApplication)::Nothing
  tracks = app.simdata.tracks
  p = GetPosition(track)[]
  push!(tracks, [Point3{Float64}(x(p),y(p),z(p))])
  nothing
end
#---Tracking post-action---------------------------------------------------------------------------
function posttrackaction(track::G4Track, ::G4JLApplication)::Nothing
  println("Finished track ID $(GetTrackID(track))")
  nothing
end

#---Create the Application-------------------------------------------------------------------------
app = G4JLApplication(B2aDetector(nChambers=5);                   # detector with parameters
                      simdata = B2aSimData(),                     # simulation data structure
                      runmanager_type = G4RunManager,             # what RunManager to instantiate
                      physics_type = FTFP_BERT,                   # what physics list to instantiate
                      generator_type = G4JLParticleGun,           # what primary generator to instantiate
                      stepaction_method = stepaction,             # step action method
                      pretrackaction_method = pretrackaction,     # pre-tracking action
                      posttrackaction_method = posttrackaction)   # post-tracking action
              
#---Configure, Initialize and Run------------------------------------------------------------------                      
configure(app)
initialize(app)

#ui = G4UImanager!GetUIpointer()
#ApplyCommand(ui, "/tracking/verbose 1")

beamOn(app, 1)

