# # Basic/B2a Example
#
# In this example is based on the Geant4 basic/B2 example of the
# Geant4 distribution. It is a simple example that shows how to 
# interact with the Geant4 classes.

#md # !!! note "Note that"
#md #     You can also download this example as a
#md #     [Jupyter notebook](B2a.ipynb) and a plain
#md #     [Julia source file](B2a.jl).
#
#md # #### Table of contents
#md # ```@contents
#md # Pages = ["B2a.md"]
#md # Depth = 2:3
#md # ```

# ## Loading the necessary Julia modules
# Load the `Geant4` and `Geant4.SystemOfUnits` modules.
# We will also use the `Printf` and `GeometryBasics` modules to format the output and handle the geometry.ß
using Geant4
using Geant4.SystemOfUnits
using Printf, GeometryBasics

# ## Define Detector Parameters structure
# The `B2aDetector` structure is defined with the default detector parameters. We include the [B2aDetector.jl](@ref) file not to clutter the example.
include(joinpath(@__DIR__, "B2aDetector.jl"))

# ## Define Tracker Hit
# We will extract the hits from the tracker and store them in a `TrackerHit` structure that ius custom defined
struct TrackerHit
  trackID::Int32
  chamberNb::Int32
  edep::Float64
  pos::Point3{Float64}
end
# Providing a custom `Base.show` method to print the hits in a nice way
function Base.show(io::IO, hit::TrackerHit)
  (;trackID, chamberNb, edep, pos) = hit
  @printf(io, "\ntrackID: %3d chamberNb: %2d Edep: %.3f MeV Position: (%3f, %3f, %3f)", trackID, chamberNb, edep/MeV, pos...) 
end

# ## Define Sensitive Detector
# First we define the data structure that will hold the hits. In this case we will store the hits in a vector of `TrackerHit` structures.
struct B2aSDData <: G4JLSDData
  trackerHits::Vector{TrackerHit}
  B2aSDData() = new([])
end
# Then we define the methods that will be called by the Geant4 simulation `_initialize` (to initialize), 
# `_endOfEvent` (at the end of the event) and `_processHits` (called when a hit is detected in that sensitive detector)
## Initialize method
function _initialize(::G4HCofThisEvent, data::B2aSDData)::Nothing
  empty!(data.trackerHits)
  return
end
## End of event method
function _endOfEvent(::G4HCofThisEvent, data::B2aSDData)::Nothing
  return
end
## Process Hit method
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
# Finally, create the sensitive detector instance of the type `G4JLSensitiveDetector` with the name `Chamber_SD` and 
# the associated data structure `B2aSDData`. The three previously defined methods are passed as arguments to the constructor.
chamber_SD = G4JLSensitiveDetector("Chamber_SD", B2aSDData();           ## SD name an associated data are mandatory
                                    processhits_method=_processHits,    ## process hist method (also mandatory)
                                    initialize_method=_initialize,      ## intialize method
                                    endofevent_method=_endOfEvent)      ## end of event method

# ## Define End Event Action
# This user function will be called at the end of each event. It will print the number of hits in the tracker for each event. 
function endeventaction(evt::G4Event, app::G4JLApplication)
  hits = getSDdata(app, "Chamber_SD").trackerHits
  eventID = evt |> GetEventID
  if eventID < 10 || eventID % 1000 == 0
    G4JL_println("Event: $eventID with $(length(hits)) hits stored in this event")
  end
  return
end

# ## Particle Gun initialization
particlegun = G4JLGunGenerator(particle = "proton", 
                               energy = 3GeV, 
                               direction = G4ThreeVector(0,0,1), 
                               position = G4ThreeVector(0,0,-2940.0))


# ## Define Physics List
# We define a new physics list that is based on the `FTFP_BERT` physics list and adds 
# a `G4StepLimiterPhysics` to limit the step length of the particles.
struct B2PhysicsList <: G4VUserPhysicsList
  function B2PhysicsList(verbose)
      pl = FTFP_BERT(verbose)
      lp = G4StepLimiterPhysics()
      SetApplyToAll(lp, true)            ## Apply to all particles
      RegisterPhysics(pl, move!(lp))     ## Register to the physics list
      return pl                          ## We need to return the physics list instance
  end 
end
# ## Create the Application
# We put all together in the `G4JLApplication` structure. We define the detector, the primary generator, the number of threads,
# the physics list, the end event action and the sensitive detectors.
app = G4JLApplication(;detector = B2aDetector(nChambers=5),          ## detector with parameters
                       generator = particlegun,                      ## primary particle generator
                       nthreads = 0,                                 ## # of threads (0 = no MT)
                       physics_type = B2PhysicsList,                 ## what physics list to instantiate
                       endeventaction_method = endeventaction,       ## end event action
                       sdetectors = ["Chamber_LV+" => chamber_SD]    ## mapping of LVs to SDs (+ means multiple LVs with same name)
                      )

# ## Configure, Initialize and Run                     
configure(app)
initialize(app)

# ## Run the simulation

## ui`/tracking/verbose 1`
beamOn(app,100)

