using Geant4
using Geant4.SystemOfUnits
using Geant4.SystemOfUnits: volt
using Parameters

@with_kw mutable struct Calorimeter <: G4JLDetector
    # main input parameters
    material::String = "Kr20CO2"
    AbsorberThickness::Float64= 4cm
    AbsorberRadius::Float64 = 10cm
    AbsorberZ::Float64 = 36cm
    WorldSizeR::Float64 = 20cm
    WorldSizeZ::Float64 = 80cm
end

function Field02Construct(det::Calorimeter)::CxxPtr{G4VPhysicalVolume}
    (; material, AbsorberThickness, AbsorberRadius, AbsorberZ, WorldSizeR, WorldSizeZ) = det

    ##---Materials----------------------------------------------------------------------------------
    nist = G4NistManager!Instance()
    m_air = FindOrBuildMaterial(nist, "G4_AIR")

    C  = FindOrBuildElement(nist,6)
    O  = FindOrBuildElement(nist,8)
    Xe = FindOrBuildMaterial(nist, "G4_Xe")
    Kr = FindOrBuildMaterial(nist, "G4_Kr")

    _C0₂ = G4Material("CO2", 1.842 * mg / cm3, 2)
    AddElement(_C0₂, C, natoms=1)
    AddElement(_C0₂, O, natoms=2)
    CO₂ = FindOrBuildMaterial(nist, "CO2")

    Kr20CO2 = G4Material("Kr20CO2", 3.601 * mg / cm3, 2)
    AddMaterial(Kr20CO2, Kr, 0.89)
    AddMaterial(Kr20CO2, CO₂, 0.11)

    ##---Absorber----------------------------------------------------------------------------------
    m_absorber = FindOrBuildMaterial(nist, material)

    ##---Volumes------------------------------------------------------------------------------------
    worldS  = G4Tubs("world", 0, WorldSizeR, WorldSizeZ/2, 0, 360deg)
    worldLV = G4LogicalVolume(worldS, m_air, "World")
    worldPV = G4PVPlacement(nothing, G4ThreeVector(), worldLV, "World", nothing, false, 0, false)

    absorberS  = G4Tubs("absorber", 0, AbsorberRadius, AbsorberThickness/2, 0, 360deg)
    absorberLV = G4LogicalVolume(absorberS, m_absorber, "absorber")
    G4PVPlacement(nothing, G4ThreeVector(0, 0, AbsorberZ), absorberLV, "absorber", worldLV, false, 0, false)
    ##---Visualization attributes-------------------------------------------------------------------
    boxVisAtt = G4VisAttributes(G4Colour(1.0, 1.0, 1.0, 0.0))
    absorberVisAtt = G4VisAttributes(G4Colour(1.0, 1.0, 0.0, 0.1))
    SetVisAttributes(worldLV, boxVisAtt)
    SetVisAttributes(absorberLV, absorberVisAtt)

    return worldPV
end
Geant4.getConstructor(::Calorimeter)::Function = Field02Construct

det = Calorimeter(material="Kr20CO2",
                  AbsorberThickness=4cm,
                  AbsorberRadius=10cm,
                  AbsorberZ=0cm,
                  WorldSizeR=20cm,
                  WorldSizeZ=80cm)

particlegun = G4JLGunGenerator(particle = "e-",
                               energy = 50MeV,
                               direction = G4ThreeVector(0,0,1),
                               position  = G4ThreeVector(0,0,0))

efield = G4UniformElectricField(G4ThreeVector(0, 1e8volt/cm, 0))

app = G4JLApplication(; detector = det,                               # detector with parameters
                        generator = particlegun,                      # primary particle generator
                        field = efield,                               # uniform magnetic field
                        nthreads = 0,                                 # # of threads (0 = no MT)
                        physics_type = FTFP_BERT,                     # what physics list to instantiate
                      );


configure(app)
initialize(app)

ui`/tracking/verbose 1`
beamOn(app,1)
