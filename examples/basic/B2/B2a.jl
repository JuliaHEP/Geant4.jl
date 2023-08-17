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
function _initialize(::G4HCofThisEvent, data::B2aSDData)::Nothing
  empty!(data.trackerHits)
  return
end
#---End of Event method----------------------------------------------------------------------------
function _endOfEvent(::G4HCofThisEvent, data::B2aSDData)::Nothing
  return
end
#---Process Hit method-----------------------------------------------------------------------------
function _processHits(step::G4Step, ::G4TouchableHistory, data::B2aSDData)::Bool
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
  hits = getSDdata(app, "Chamber_SD").trackerHits
  eventID = evt |> GetEventID
  if eventID < 10 || eventID % 1000 == 0
    G4JL_println("Event: $eventID with $(length(hits)) hits stored in this event")
  end
  return
end

#--------------------------------------------------------------------------------------------------
#---Particle Gun initialization--------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------
particlegun = G4JLGunGenerator(particle = "proton", 
                               energy = 3GeV, 
                               direction = G4ThreeVector(0,0,1), 
                               position = G4ThreeVector(0,0,-2940.0))

#--------------------------------------------------------------------------------------------------
#---Create the Application-------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------
app = G4JLApplication(;detector = B2aDetector(nChambers=5),          # detector with parameters
                       generator = particlegun,                      # primary particle generator
                       nthreads = 0,                                 # # of threads (0 = no MT)
                       physics_type = FTFP_BERT,                     # what physics list to instantiate
                       endeventaction_method = endeventaction,       # end event action
                       sdetectors = ["Chamber_LV+" => chamber_SD]    # mapping of LVs to SDs (+ means multiple LVs with same name)
                      )
              
#---Configure, Initialize and Run------------------------------------------------------------------                      
configure(app)
initialize(app)

#ui`/tracking/verbose 1`
beamOn(app,100)

