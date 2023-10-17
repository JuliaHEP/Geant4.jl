using Geant4
using Geant4.SystemOfUnits
using GLMakie, Rotations, IGLWrap_jll  # to force loding G4Vis extension

include(joinpath(@__DIR__, "../../../examples/basic/B2/DetectorB2a.jl"))

#--------------------------------------------------------------------------------------------------
#---Particle Gun initialization--------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------
particlegun = G4JLGunGenerator(particle = "proton", 
                               energy = 3GeV, 
                               direction = G4ThreeVector(0,0,1), 
                               position = G4ThreeVector(0,0,-2940.0))
#--------------------------------------------------------------------------------------------------
#---Event Display----------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------
display = G4JLEventDisplay(joinpath(@__DIR__, "VisSettings.jl"))
#--------------------------------------------------------------------------------------------------
#---Create the Application-------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------
app = G4JLApplication(;detector = B2aDetector(nChambers=5),          # detector with parameters
                       generator = particlegun,                      # primary particle generator
                       physics_type = FTFP_BERT,                     # what physics list to instantiate
                       evtdisplay =  display,                        # detector and event visualization
                      )
wait_for_key(prompt) = (print(stdout, prompt); read(stdin, 1); nothing)

#---Configure, Initialize and Run------------------------------------------------------------------                      
configure(app)
initialize(app)

beamOn(app,1)
wait_for_key("press any key to continue")

beamOn(app,1)
wait_for_key("press any key to continue")

reinitialize(app,  B2aDetector(nChambers=8))
wait_for_key("press any key to continue")

beamOn(app,1)
wait_for_key("press any key to continue")

beamOn(app,1)
wait_for_key("press any key to continue")