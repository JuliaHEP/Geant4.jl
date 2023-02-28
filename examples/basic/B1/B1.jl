using Geant4
using Geant4.SystemOfUnits

include("DetectorB1.jl")

# Detector construction
detdesc = G4JLDetectorConstruction(constructB1Detector)
physics = QBBC()
#SetVerboseLevel(physics, 1)

# Construct the default run manager
runManager = G4RunManager()
SetUserInitialization(runManager, detdesc)
SetUserInitialization(runManager, CxxPtr(physics))

# User Actions
function buildApp(self::G4JLActionInitialization)
  # Create and register particle gun
  particle_gun = G4JLParticleGun()
  SetUserAction(self, particle_gun)

  # Setup particle gun
  pg = GetGun(particle_gun)
  SetParticleByName(pg, "e-")
  SetParticleEnergy(pg, 100MeV)
  SetParticleMomentumDirection(pg, G4ThreeVector(0,0,1))
  SetParticlePosition(pg, G4ThreeVector(0,0,-16cm))
end
app = G4JLActionInitialization(buildApp)
SetUserInitialization(runManager, app)

# Get the pointer to the User Interface manager
UImanager = G4UImanager!GetUIpointer()

#Initialize(runManager)
#BeamOn(runManager, 1)

# Initialize kernel
@show ApplyCommand(UImanager, "/run/initialize")

# Change verbosity
#ApplyCommand(UImanager, "/control/verbose 2")
#ApplyCommand(UImanager, "/run/verbose 2")
#ApplyCommand(UImanager, "/event/verbose 0")
ApplyCommand(UImanager, "/tracking/verbose 1")

# gamma 6 MeV to the direction (0.,0.,1.)
#ApplyCommand(UImanager, "/gun/particle gamma")
#ApplyCommand(UImanager, "/gun/energy 6 MeV")

# go
ApplyCommand(UImanager, "/run/beamOn 1")

