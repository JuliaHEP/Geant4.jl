using Geant4
using Geant4.SystemOfUnits
using Printf, GeometryBasics


#---Define Detector Parameters struct--------------------------------------------------------------
include(joinpath(@__DIR__, "DetectorRE03.jl"))

#---Particle Gun initialization--------------------------------------------------------------------
function gun_initialize(gen::G4JLParticleGun, det::G4JLDetector)
  pg = GetGun(gen)
  SetParticleByName(pg, "e-")
  SetParticleEnergy(pg, 1GeV)
  SetParticleMomentumDirection(pg, G4ThreeVector(0,0,1))
  SetParticlePosition(pg, G4ThreeVector(0,0,-1.01m))
end
Geant4.getInitializer(::G4JLParticleGun) = gun_initialize

#---Particle Gun initialization--------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------
particlegun = G4JLGunGenerator(particle = "e-", 
                               energy = 1GeV, 
                               direction = G4ThreeVector(0,0,1), 
                               position = G4ThreeVector(0,0,-1.01m))

#---Scoring Setup----------------------------------------------------------------------------------
sc1 = G4JLScoringMesh("boxMesh_1",
                      BoxMesh(1m,1m,1m),
                      bins = (30, 30, 30),
                      quantities = [ energyDeposit("eDep")
                                     nOfStep("nOfStepGamma", filters=[ParticleFilter("gammafilter", "gamma")])
                                     nOfStep("nOfStepEMinus", filters=[ParticleFilter("eMinusFilter", "e-")])
                                     nOfStep("nOfStepEPlus", filters=[ParticleFilter("ePlusFilter", "e+")])
                                   ]
                      )

#---Create the Application-------------------------------------------------------------------------
app = G4JLApplication(;detector = RE03Detector(),                    # detector with parameters
                       generator = particlegun,                      # primary particle generator
                       nthreads = VERSION > v"1.9" ? 4 : 0,          # number of threads (MT)
                       physics_type = FTFP_BERT,                     # what physics list to instantiate
                       scorers = [sc1]                               # list of scorers 
                      )
SetNumberOfThreads(app.runmanager,4)

#---Configure, Initialize and Run------------------------------------------------------------------                      
configure(app)
initialize(app)
beamOn(app, 0)

#---Do a run and get the scoring-------------------------------------------------------------------
beamOn(app,1000)
G4JL_println("done with run!!!")

#---Get the results--------------------------------------------------------------------------------
t, t2, n = sc1.eDep
G4JL_println("Total EDep = $(sum(t))")


