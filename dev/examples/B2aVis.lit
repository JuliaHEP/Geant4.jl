# # Basic/B2a Event Display Example
#
# In this example is based on the Geant4 basic/B2 example of the
# Geant4 distribution. It is a simple example that shows how to 
# interact with the Geant4 classes.

#md # !!! note "Note that"
#md #     You can also download this example as a
#md #     [Jupyter notebook](B2aVis.ipynb) and a plain
#md #     [Julia source file](B2aVis.jl).
#
#md # #### Table of contents
#md # ```@contents
#md # Pages = ["B2aVis.md"]
#md # Depth = 2:3
#md # ```

# ## Loading the necessary Julia modules
# Load the `Geant4` and `Geant4.SystemOfUnits` modules.
# In order to trigger the load of the G4Vis extension we need to load the 
# following modules: `GLMakie`, `Rotations`, `LinearAlgebra`, `IGLWrap_jll`
using Geant4
using Geant4.SystemOfUnits
using CairoMakie, Rotations, LinearAlgebra, IGLWrap_jll  # to force loading G4Vis extension
#md import DisplayAs: PNG
#nb import DisplayAs: PNG

# ## Define Detector Parameters structure
# The `B2aDetector` structure is defined with the default detector parameters. We include the [B2aDetector.jl](@ref) file not to clutter the example.
include(joinpath(@__DIR__, "B2aDetector.jl"))

# ## Particle Gun initialization
particlegun = G4JLGunGenerator(particle = "proton", 
                               energy = 3GeV, 
                               direction = G4ThreeVector(0,0,1), 
                               position = G4ThreeVector(0,0,-2940.0));

# ## Event Display
# To setup the event display we need to create an instance of the `G4JLEventDisplay` type. The file [`B2aVisSettings.jl`](@ref) contains 
# the settings for the visualization.     
evtdisplay = G4JLEventDisplay(joinpath(@__DIR__, "B2aVisSettings.jl"));

#  ## Create the application
app = G4JLApplication(;detector = B2aDetector(nChambers=5),          ## detector with parameters
                       generator = particlegun,                      ## primary particle generator
                       physics_type = FTFP_BERT,                     ## what physics list to instantiate
                       evtdisplay =  evtdisplay,                     ## detector and event visualization
                      );
## wait_for_key(prompt) = (print(stdout, prompt); read(stdin, 1); nothing)
                    
# ## Configure, Initialize and Run
configure(app)
initialize(app)

# Display the detector geometry at this point
beamOn(app,0)  ## Needed to really initialize  
#nb PNG(evtdisplay.figure)
#md PNG(evtdisplay.figure)
#jl display(evtdisplay.figure)

# Display the detector geometry with the first event
beamOn(app,1)
#nb PNG(evtdisplay.figure)
#md PNG(evtdisplay.figure)
#jl display(evtdisplay.figure)

# Display the detector geometry with the second event
beamOn(app,1)
#nb PNG(evtdisplay.figure)
#md PNG(evtdisplay.figure)
#jl display(evtdisplay.figure)
