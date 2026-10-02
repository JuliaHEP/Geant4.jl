using Geant4
using Geant4.SystemOfUnits

include(joinpath(@__DIR__, "RE03Detector.jl"))

particlegun = G4JLGunGenerator(particle = "e-",
                               energy = 1GeV,
                               direction = G4ThreeVector(0,0,1),
                               position = G4ThreeVector(0,0,-1.01m))

sc1 = G4JLScoringMesh("boxMesh_1",
                      BoxMesh(1m,1m,1m),
                      bins = (30, 30, 30),
                      quantities = [ energyDeposit("eDep")
                                     nOfStep("nOfStepGamma", filters=[ParticleFilter("gammafilter", "gamma")])
                                     nOfStep("nOfStepEMinus", filters=[ParticleFilter("eMinusFilter", "e-")])
                                     nOfStep("nOfStepEPlus", filters=[ParticleFilter("ePlusFilter", "e+")])
                                   ]
                      );

app = G4JLApplication(;detector = RE03Detector(),                    ## detector with parameters
                       generator = particlegun,                      ## primary particle generator
                       nthreads = 4,                                 ## number of threads (MT)
                       physics_type = FTFP_BERT,                     ## what physics list to instantiate
                       scorers = [sc1]                               ## list of scorers
                      );

configure(app)
initialize(app)
beamOn(app, 0)

beamOn(app,1000)
println("done with run!!!")

t, t2, n = sc1.eDep

println("Dimensions of the scoring results: $(Base.size(t))")

println("Total EDep = $(sum(t))")
println("Central EDep = $(sum(t[10:20,10:20,:]))")

using CairoMakie
img = heatmap(t[1:30,15,1:30])
