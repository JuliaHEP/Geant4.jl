# # Extended/RE03 Example
# This example demonstrates how to use UI-command base scoring. 
# Its create parallel world(s) for defining scoring mesh(es).

# Due to some performance overhead, this functionality is not provided by default. 
# To enable it, you need to set the parameter `scores` in `G4JLApplication` with a list of scorers

# The geometry consists of one water box in the world volume filled by air. Particle gun shoots a gamma
# into the water box. The physics list is taken from referenced physics-list `FTFP_BERT`` in Geant4.

#md # !!! note "Note that"
#md #     You can also download this example as a
#md #     [Jupyter notebook](RE03.ipynb) and a plain
#md #     [Julia source file](RE03.jl).
#
#md # #### Table of contents
#md # ```@contents
#md # Pages = ["RE03.md"]
#md # Depth = 2:3
#md # ```

# ## Loading the necessary Julia modules
# Load the `Geant4`, `Geant4.PhysicalConstants` and `Geant4.SystemOfUnits` modules. In addition we will use the `Parameters` module to handle the parameters of the detector.
# We will also use the `FHist` and `Plots` modules to handle the histograms and plots.
using Geant4
using Geant4.SystemOfUnits
#md import DisplayAs: PNG
#nb import DisplayAs: PNG

# ## Define Detector structure
# The RE03 detector is a simple box filled with air. The detector is defined by the `RE03Detector` structure.
# We include the [RE03Detector.jl](@ref) file not to clutter the example.
include(joinpath(@__DIR__, "RE03Detector.jl"))

# ## Particle Gun initialization
particlegun = G4JLGunGenerator(particle = "e-", 
                               energy = 1GeV, 
                               direction = G4ThreeVector(0,0,1), 
                               position = G4ThreeVector(0,0,-1.01m))

# ## Scoring Setup
# In this example, we define a scoring mesh that will score the energy deposit and the number of 
# steps of gamma, e- and e+ particles. We do not use the UI interface to define the scoring mesh, instead
# we define it in the Julia code by instantiating a `G4JLScoringMesh` object.
sc1 = G4JLScoringMesh("boxMesh_1",
                      BoxMesh(1m,1m,1m),
                      bins = (30, 30, 30),
                      quantities = [ energyDeposit("eDep")
                                     nOfStep("nOfStepGamma", filters=[ParticleFilter("gammafilter", "gamma")])
                                     nOfStep("nOfStepEMinus", filters=[ParticleFilter("eMinusFilter", "e-")])
                                     nOfStep("nOfStepEPlus", filters=[ParticleFilter("ePlusFilter", "e+")])
                                   ]
                      );
# ## Create the Application
app = G4JLApplication(;detector = RE03Detector(),                    ## detector with parameters
                       generator = particlegun,                      ## primary particle generator
                       nthreads = 4,                                 ## number of threads (MT)
                       physics_type = FTFP_BERT,                     ## what physics list to instantiate
                       scorers = [sc1]                               ## list of scorers 
                      );
# ## Configure, Initialize and Run                    
configure(app)
initialize(app)
beamOn(app, 0)

# ## Do a run and get the scoring results
beamOn(app,1000)
println("done with run!!!")

# ## Access the scoring results
# This is done by accessing the `eDep` field of the `G4JLScoringMesh` object `sc1`, or by accessing
# the fields `nOfStepGamma`, `nOfStepEMinus` or `nOfStepEPlus`. Each of each of these fields
# returns a tuple with the scoring results (mean, mean², N) organized in a 3-dimensional matrix with the
# defined number of bins.
t, t2, n = sc1.eDep
# Lets see the dimensions of the scoring results
println("Dimensions of the scoring results: $(Base.size(t))")
# Print the total energy deposit
println("Total EDep = $(sum(t))")
println("Central EDep = $(sum(t[10:20,10:20,:]))")

# ## Plot the scoring results
# We will use the `CairoMakie` package to plot the scoring results. We will plot the energy deposit in the
# center of the scoring mesh.
using CairoMakie
img = heatmap(t[1:30,15,1:30])
#nb PNG(img)
#md PNG(img)
#jl display(img)
