using Geant4
using Geant4.SystemOfUnits
using Printf, GeometryBasics

#---Define Detector Parameters struct--------------------------------------------------------------
include(joinpath(@__DIR__, "DetectorB2a.jl"))

#---Define Tracker Hit-----------------------------------------------------------------------------
struct TrackerHit
  trackID::Int32
  chamberNb::Int32
  edep::Float64
  pos::Point3{Float64}
end
function Base.show(io::IO, hit::TrackerHit)
  (;trackID, chamberNb, edep, pos) = hit
  @printf(io, "\ntrackID: %3d chamberNb: %2d Edep: %.3f MeV Position: (%3f, %3f, %3f)", trackID, chamberNb, edep/MeV, pos...) 
end

#--------------------------------------------------------------------------------------------------
#---Define Sensitive Detector----------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------
#---SD collected data------------------------------------------------------------------------------
struct B2aSDData <: G4JLSDData
  trackerHits::Vector{TrackerHit}
  B2aSDData() = new([])
end
#---Initialize method------------------------------------------------------------------------------
function _initialize(data::B2aSDData, ::G4HCofThisEvent)::Nothing
  empty!(data.trackerHits)
  return
end
#---End of Event method----------------------------------------------------------------------------
function _endOfEvent(data::B2aSDData, ::G4HCofThisEvent)::Nothing
  #println(data.trackerHits)
  return
end
#---Process Hit method-----------------------------------------------------------------------------
function _processHits(data::B2aSDData, step::G4Step, ::G4TouchableHistory)::Bool
  edep = step |> GetTotalEnergyDeposit
  edep <  0. && return false
  pos = step |> GetPostStepPoint |> GetPosition
  push!(data.trackerHits, TrackerHit(step |> GetTrack |> GetTrackID,
                                    step |> GetPreStepPoint |> GetTouchable |> GetCopyNumber,
                                    edep,
                                    Point3{Float64}(x(pos),y(pos),z(pos))))
  return true
end
#---Create SD instance-----------------------------------------------------------------------------
chamber_SD = G4JLSensitiveDetector("Chamber_SD", B2aSDData();           # SD name an associated data are mandatory
                                    processhits_method=_processHits,    # process hist method (also mandatory)
                                    initialize_method=_initialize,      # intialize method
                                    endofevent_method=_endOfEvent)      # end of event method

#---End Event Action-------------------------------------------------------------------------------
function endeventaction(evt::G4Event, app::G4JLApplication)
  #hits = chamber_SD.data.trackerHits
  hits = app.sdetectors["Chamber_LV+"].data.trackerHits
  eventID = evt |> GetEventID
  if eventID < 10 || eventID % 100 == 0
    println("Event: $eventID with $(length(hits)) hits stored in this event")
  end
  return
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

#---Create the Application-------------------------------------------------------------------------
app = G4JLApplication(;detector = B2aDetector(nChambers=5),          # detector with parameters
                       runmanager_type = G4RunManager,               # what RunManager to instantiate
                       physics_type = FTFP_BERT,                     # what physics list to instantiate
                       generator_type = G4JLParticleGun,             # what primary generator to instantiate
                       endeventaction_method = endeventaction,       # end event action
                       sdetectors = ["Chamber_LV+" => chamber_SD]    # mapping of LVs to SDs (+ means multiple LVs with same name)
                      )             
              
#---Configure, Initialize and Run------------------------------------------------------------------                      
configure(app)
initialize(app)

beamOn(app, 1)

