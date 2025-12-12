using Geant4
using Geant4.SystemOfUnits
using CairoMakie  # to force loading G4Vis extension

include(joinpath(@__DIR__, "B2aDetector.jl"))

particlegun = G4JLGunGenerator(particle = "proton",
                               energy = 3GeV,
                               direction = G4ThreeVector(0,0,1),
                               position = G4ThreeVector(0,0,-2940.0));

evtdisplay = G4JLEventDisplay(joinpath(@__DIR__, "B2aVisSettings.jl"));

app = G4JLApplication(;detector = B2aDetector(nChambers=5),          ## detector with parameters
                       generator = particlegun,                      ## primary particle generator
                       physics_type = FTFP_BERT,                     ## what physics list to instantiate
                       evtdisplay =  evtdisplay,                     ## detector and event visualization
                      );
# wait_for_key(prompt) = (print(stdout, prompt); read(stdin, 1); nothing)

configure(app)
initialize(app)

beamOn(app,0)  ## Needed to really initialize
display(evtdisplay.figure)

beamOn(app,1)
display(evtdisplay.figure)

beamOn(app,1)
display(evtdisplay.figure)
