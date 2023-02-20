using Geant4
using Geant4.SystemOfUnits

function constructB1Detector()

  nist = G4NistManager!Instance()

  # Envelope parameters
  env_sizeXY = 20cm
  env_sizeZ  = 30cm
  env_mat    = FindOrBuildMaterial(nist, "G4_WATER")

  # Option to switch on/off checking of volumes overlaps
  checkOverlaps = true

  # World
  world_sizeXY = 1.2*env_sizeXY
  world_sizeZ  = 1.2*env_sizeZ
  world_mat = FindOrBuildMaterial(nist, "G4_AIR")

  solidworld = G4Box("World", 0.5 * world_sizeXY, 0.5 * world_sizeXY, 0.5 * world_sizeZ)
  logicworld = G4LogicalVolume(solidworld, world_mat, "World")

  physWorld = G4PVPlacement(nothing,          # no rotation
                            G4ThreeVector(),  # at (0,0,0)
                            logicworld,       # its logical volume
                            "World",          # its name
                            nothing,          # its mother volume
                            false,            # no boolean operation
                            0,                # copy number
                            checkOverlaps)    # overlaps checking

  # Envelope
  solidEnv = G4Box("Envelope", 0.5 * env_sizeXY, 0.5 * env_sizeXY, 0.5 * env_sizeZ)
  logicEnv = G4LogicalVolume(solidEnv, env_mat, "Envelope")

  G4PVPlacement(nothing,           # no rotation
                G4ThreeVector(),   # at (0,0,0)
                logicEnv,          # its logical volume
                "Envelope",        # its name
                logicworld,        # its mother  volume
                false,             # no boolean operation
                0,                 # copy number
                checkOverlaps)     # overlaps checking
  # shape 1
  shape1_mat = FindOrBuildMaterial(nist, "G4_A-150_TISSUE")
  pos1 = G4ThreeVector(0, 2cm, -7cm)
  
  # Conical section shape
  shape1_rmina =  0cm; shape1_rmaxa = 2cm
  shape1_rminb =  0cm; shape1_rmaxb = 4cm
  shape1_hz = 3cm
  shape1_phimin = 0deg; shape1_phimax = 360deg

  solidShape1 = G4Cons("Shape1", shape1_rmina, shape1_rmaxa, shape1_rminb, shape1_rmaxb,
                shape1_hz, shape1_phimin, shape1_phimax)
  
  logicShape1 = G4LogicalVolume(solidShape1, shape1_mat, "Shape1")
  G4PVPlacement(nothing,      # no rotation
                pos1,         # at position
                logicShape1,  # its logical volume
                "Shape1",     # its name
                logicEnv,     # its mother  volume
                false,        # no boolean operation
                0,            # copy number
                checkOverlaps)# overlaps checking
  # Shape 2
  shape2_mat = FindOrBuildMaterial(nist, "G4_BONE_COMPACT_ICRU")
  pos2 = G4ThreeVector(0, -1cm, 7cm)
                
  # Trapezoid shape
  shape2_dxa = 12cm; shape2_dxb = 12cm
  shape2_dya = 10cm; shape2_dyb = 16cm
  shape2_dz  = 6cm
  solidShape2 = G4Trd("Shape2", 0.5 * shape2_dxa, 0.5 * shape2_dxb, 0.5 * shape2_dya, 0.5 * shape2_dyb, 0.5 * shape2_dz)
  logicShape2 = G4LogicalVolume(solidShape2, shape2_mat, "Shape2")
  G4PVPlacement(nothing,        # no rotation
                pos2,           # at position
                logicShape2,    # its logical volume
                "Shape2",       # its name
                logicEnv,       # its mother  volume
                false,          # no boolean operation
                0,              # copy number
                checkOverlaps)  # overlaps checking

  return physWorld              # return a pointer to the G4PhysicalVolume
end


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

