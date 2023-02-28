using Geant4
using Geant4.SystemOfUnits

include("DetectorB2a.jl")

# Detector construction
detdesc = G4JLDetectorConstruction(constructB2aDetector)
physics = FTFP_BERT()
#SetVerboseLevel(physics, 1)

# Construct the default run manager
runManager = G4RunManager()
SetUserInitialization(runManager, detdesc)
SetUserInitialization(runManager, move(physics))

# User Actions
function buildApp(self::G4JLActionInitialization)
  # Create and register particle gun
  particle_gun = G4JLParticleGun()
  SetUserAction(self, particle_gun)

  # Setup particle gun
  pg = GetGun(particle_gun)
  SetParticleByName(pg, "proton")
  SetParticleEnergy(pg, 3GeV)
  SetParticleMomentumDirection(pg, G4ThreeVector(0,0,1))
  SetParticlePosition(pg, G4ThreeVector(0,0,-16cm))
  SetParticlePosition(pg, G4ThreeVector(0, 0, -worldZHalfLength))
end

app = G4JLActionInitialization(buildApp)
SetUserInitialization(runManager, app)

# Get the pointer to the User Interface manager
UImanager = G4UImanager!GetUIpointer()

# Initialize kernel
@show ApplyCommand(UImanager, "/run/initialize")

# Change verbosity and go
ApplyCommand(UImanager, "/tracking/verbose 1")
ApplyCommand(UImanager, "/run/beamOn 1")

# 1 event with printing hits
ApplyCommand(UImanager, "/tracking/verbose 0")
ApplyCommand(UImanager, "/hits/verbose 2")
ApplyCommand(UImanager, "/run/beamOn 1")

#