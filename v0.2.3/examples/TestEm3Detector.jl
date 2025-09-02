using Geant4
using Geant4.SystemOfUnits

#--------------------------------------------------------------------------------------------------
# TestEm3 Detector definition
#--------------------------------------------------------------------------------------------------

mutable struct TestEm3Detector <: G4JLDetector
    # main input parameters
    const fNbOfAbsor::Int64
    const fNbOfLayers::Int64
    const fCalorSizeYZ::Float64
    const fAbsorThickness::Vector{Float64}

    # mutable (computed) detector data
    fLayerThickness::Float64
    fCalorThickness::Float64
    fWorldSizeYZ::Float64
    fWorldSizeX::Float64

    fAbsorMaterial::Vector{CxxPtr{G4Material}}
    fWorldMaterial::CxxPtr{G4Material}

    fSolidWorld::G4Box
    fLogicWorld::G4LogicalVolume
    fPhysiWorld::CxxPtr{G4VPhysicalVolume}
  
    fSolidCalor::G4Box
    fLogicCalor::G4LogicalVolume
    fPhysiCalor::CxxPtr{G4VPhysicalVolume}
  
    fSolidLayer::G4Box
    fLogicLayer::G4LogicalVolume
    fPhysiLayer::CxxPtr{G4VPhysicalVolume}
  
    fSolidAbsor::Vector{G4Box}
    fLogicAbsor::Vector{G4LogicalVolume}
    fPhysiAbsor::Vector{CxxPtr{G4VPhysicalVolume}}

    function TestEm3Detector(;nbOfLayers = 50, 
                              calorSizeYZ = 40cm,
                              absorThickness = [2.3mm, 5.7mm],
                              absorMaterial = ["G4_Pb", "G4_lAr"])
        self = new(length(absorThickness), nbOfLayers, calorSizeYZ, absorThickness)

        # Compute derived parameters of the calorimeter
        self.fLayerThickness = 0.
        for i in 1:self.fNbOfAbsor
          self.fLayerThickness += self.fAbsorThickness[i]
        end
        self.fCalorThickness = self.fNbOfLayers * self.fLayerThickness     
        self.fWorldSizeX = 1.2 * self.fCalorThickness 
        self.fWorldSizeYZ = 1.2 * self.fCalorSizeYZ

        DefineMaterials!(self)

        nist = G4NistManager!Instance()
        self.fWorldMaterial = FindOrBuildMaterial(nist,"Galactic")
        self.fAbsorMaterial = [FindOrBuildMaterial(nist, mat) for mat in absorMaterial]
        self
    end

end      

using Geant4.SystemOfUnits:cm3, mole, kelvin, atmosphere, eV, pascal, bar
const perCent=0.01

function DefineMaterials!(det::TestEm3Detector)
    # to avoid warnings of redefinitions
    G4Material!GetMaterial("liquidH2", false) != C_NULL && return

    nist = G4NistManager!Instance()
    H  = FindOrBuildElement(nist,1)
    C  = FindOrBuildElement(nist,6)
    N  = FindOrBuildElement(nist,7)
    O  = FindOrBuildElement(nist,8)
    Si = FindOrBuildElement(nist,14)
    Ge = FindOrBuildElement(nist,32)
    Sb = FindOrBuildElement(nist,51)
    I  = FindOrBuildElement(nist,53)
    Cs = FindOrBuildElement(nist,55)
    Pb = FindOrBuildElement(nist,82)
    Bi = FindOrBuildElement(nist,83)

    U5 = G4Isotope("U235", z=92, n=235, a=235.01*g/mole)
    U8 = G4Isotope("U238", z=92, n=238, a=238.03*g/mole)
  
    U  = G4Element("enriched Uranium", "U", 2)
    AddIsotope(U, move!(U5), 0.90)
    AddIsotope(U, move!(U8), 0.10)

    G4Material("liquidH2",    z=1.,  a= 1.008*g/mole,  density= 70.8*mg/cm3)
    G4Material("Aluminium",   z=13., a= 26.98*g/mole,  density= 2.700*g/cm3)
    G4Material("Titanium",    z=22., a= 47.867*g/mole, density= 4.54*g/cm3)
    G4Material("Iron",        z=26., a= 55.85*g/mole,  density= 7.870*g/cm3)
    G4Material("Copper",      z=29., a= 63.55*g/mole,  density= 8.960*g/cm3)
    G4Material("Tungsten",    z=74., a= 183.85*g/mole, density= 19.30*g/cm3)
    G4Material("Gold",        z=79., a= 196.97*g/mole, density= 19.32*g/cm3)
    G4Material("Uranium",     z=92., a= 238.03*g/mole, density= 18.95*g/cm3)

    # define a material from elements.   case 1: chemical molecule
  
    H₂O = G4Material("Water", density=1.000*g/cm3, ncomponents=2)

    AddElement(H₂O, H, natoms=2)
    AddElement(H₂O, O, natoms=1)
    #SetMeanExcitationEnergy(GetIonisation(H₂O), 78.0*eV)
    SetChemicalFormula(H₂O, "H_2O")
    
    CH = G4Material("Polystyrene", density= 1.032*g/cm3, ncomponents=2)
    AddElement(CH, C, natoms=1)
    AddElement(CH, H, natoms=1)
 
    Sci = G4Material("Scintillator", density= 1.032*g/cm3, ncomponents=2)
    AddElement(Sci, C, natoms=9)
    AddElement(Sci, H, natoms=10)
    #SetBirksConstant(GetIonisation(Sci), 0.126*mm/MeV)
  
    Lct = G4Material("Lucite", density= 1.185*g/cm3, ncomponents=3)
    AddElement(Lct, C, fractionmass=.5997)
    AddElement(Lct, H, fractionmass=.0807)
    AddElement(Lct, O, fractionmass=.3196)
  
    Sili = G4Material("Silicon", density= 2.330*g/cm3, ncomponents=1)
    AddElement(Sili, Si, natoms=1)
  
    SiO₂ = G4Material("quartz", density= 2.200*g/cm3, ncomponents=2)
    AddElement(SiO₂, Si, natoms=1)
    AddElement(SiO₂, O , natoms=2)
  
    G10 = G4Material("NemaG10", density= 1.700*g/cm3, ncomponents=4)
    AddElement(G10, Si, natoms=1)
    AddElement(G10, O , natoms=2)
    AddElement(G10, C , natoms=3)
    AddElement(G10, H , natoms=3)
  
    CsI = G4Material("CsI", density= 4.534*g/cm3, ncomponents=2)
    AddElement(CsI, Cs, natoms=1)
    AddElement(CsI, I , natoms=1)
    #SetMeanExcitationEnergy(GetIonisation(CsI), 553.1*eV)
  
    BGO = G4Material("BGO", density= 7.10*g/cm3, ncomponents=3)
    AddElement(BGO, O , natoms=12)
    AddElement(BGO, Ge, natoms= 3)
    AddElement(BGO, Bi, natoms= 4)
  
    SiNx= G4Material("SiNx", density= 3.1 *g/cm3, ncomponents=3)
    AddElement(SiNx, Si, natoms=300)
    AddElement(SiNx, N, natoms=310)
    AddElement(SiNx, H, natoms=6)

    # define gaseous materials using G4 NIST database 
    Air = FindOrBuildMaterial(nist, "G4_AIR")
    ConstructNewGasMaterial(nist, "Air20","G4_AIR", 293kelvin, 1atmosphere)

    lAr = FindOrBuildMaterial(nist, "G4_lAr")
    lArEm3 = G4Material("liquidArgon", density= 1.390g/cm3, ncomponents=1)
    AddMaterial(lArEm3, lAr, fractionmass=1.0)

    # define a material from elements and others materials (mixture of mixtures)
    Lead = G4Material("Lead", density=11.35*g/cm3, ncomponents=1)
    AddElement(Lead, Pb, fractionmass=1.0)
  
    LeadSb = G4Material("LeadSb", density=11.35*g/cm3, ncomponents=2)
    AddElement(LeadSb, Sb, fractionmass=4perCent)
    AddElement(LeadSb, Pb, fractionmass=96perCent)
  
    Aerog = G4Material("Aerogel", density= 0.200*g/cm3, ncomponents=3)
    AddMaterial(Aerog, SiO₂, fractionmass=62.5*perCent)
    AddMaterial(Aerog, H₂O , fractionmass=37.4*perCent)
    AddElement(Aerog, C , fractionmass= 0.1*perCent)
  
    # examples of gas in non STP conditions
    CO₂ = G4Material("CarbonicGas", density= 27*mg/cm3, ncomponents=2, state=kStateGas, temperature= 325*kelvin, pressure= 50*atmosphere)
    AddElement(CO₂, C, natoms=1)
    AddElement(CO₂, O, natoms=2)
  
    steam = G4Material("WaterSteam", density= 1.0*mg/cm3, ncomponents=1, state=kStateGas, temperature= 273*kelvin, pressure= 1*atmosphere)
    AddMaterial(steam, H₂O, fractionmass=1.)
    
    G4Material("ArgonGas", z=18., a=39.948*g/mole, density= 1.782*mg/cm3, state=kStateGas, temperature=273.15*kelvin, pressure=1*atmosphere)

    # examples of vacuum
    universe_mean_density = 1.e-25*g/cm3
    move!(G4Material("Galactic", z=1., a=1.008*g/mole, density=universe_mean_density, state=kStateGas, temperature=2.73*kelvin, pressure=3.e-18*pascal))
  
    beam = G4Material("Beam", density=1.e-5*g/cm3, ncomponents=1, state=kStateGas, temperature=273.15*kelvin, pressure=2e-2*bar)
    AddMaterial(beam, Air, fractionmass=1.)

end

function TestEm3Construct(det::TestEm3Detector)::CxxPtr{G4VPhysicalVolume}
    (; fNbOfAbsor, fNbOfLayers, fCalorSizeYZ, fAbsorThickness, fLayerThickness, fCalorThickness, fWorldSizeYZ, fWorldSizeX, fWorldMaterial, fAbsorMaterial) = det

    #isdefined(det,:fSolidWorld) && return det.fPhysiWorld
    println("Building Geometry now!!!")
    
    #---World--------------------------------------------------------------------------------------
    det.fSolidWorld = G4Box("World", fWorldSizeX/2,fWorldSizeYZ/2,fWorldSizeYZ/2)
    det.fLogicWorld = G4LogicalVolume(CxxPtr(det.fSolidWorld), fWorldMaterial, "World")
    det.fPhysiWorld = G4PVPlacement(nothing,              # no rotation
                                    G4ThreeVector(),      # at (0,0,0)
                                    det.fLogicWorld,      # its fLogical volume
                                    "World",              # its name
                                    nothing,              # its mother  volume
                                    false,                # no boolean operation
                                    0)                    #copy number

    #---Calorimeter--------------------------------------------------------------------------------
    det.fSolidCalor = G4Box("Calorimeter", fCalorThickness/2,fCalorSizeYZ/2,fCalorSizeYZ/2)
    det.fLogicCalor = G4LogicalVolume(CxxPtr(det.fSolidCalor), fWorldMaterial, "Calorimeter")      
    det.fPhysiCalor = G4PVPlacement(nothing,               # no rotation
                                    G4ThreeVector(),       # at (0,0,0)
                                    det.fLogicCalor,       # its fLogical volume
                                    "Calorimeter",         # its name
                                    det.fLogicWorld,       # its mother  volume
                                    false,                 # no boolean operation
                                    0)                     # copy number

    #---Layers-------------------------------------------------------------------------------------
    det.fSolidLayer = G4Box("Layer", fLayerThickness/2,fCalorSizeYZ/2,fCalorSizeYZ/2)
    det.fLogicLayer = G4LogicalVolume(CxxPtr(det.fSolidLayer), fWorldMaterial, "Layer")              
    if fNbOfLayers > 1
        det.fPhysiLayer = G4PVReplica("Layer",              
                                      det.fLogicLayer,     
                                      det.fLogicCalor,      
                                      kXAxis,              
                                      fNbOfLayers,            
                                      fLayerThickness)     
    else
        det.fPhysiLayer = G4PVPlacement(nothing,                   
                                        G4ThreeVector(),     
                                        det.fLogicLayer,           
                                        "Layer",             
                                        det.fLogicCalor,         
                                        false,             
                                        0)                    
    end

    #---Absorbers----------------------------------------------------------------------------------
    det.fSolidAbsor = [G4Box("Absorber", fAbsorThickness[k]/2,fCalorSizeYZ/2,fCalorSizeYZ/2) for k in 1:fNbOfAbsor]
    det.fLogicAbsor = [G4LogicalVolume(CxxPtr(det.fSolidAbsor[k]), fAbsorMaterial[k], GetName(fAbsorMaterial[k])) for  k in 1:fNbOfAbsor]

    xcenter = zeros(fNbOfAbsor)
    xfront = -0.5*fLayerThickness
    for k in 1:fNbOfAbsor
        xcenter[k] = xfront + 0.5*fAbsorThickness[k]
        xfront += fAbsorThickness[k]
    end
    det.fPhysiAbsor = [G4PVPlacement(nothing,              
                                     G4ThreeVector(xcenter[k],0.,0.),
                                     det.fLogicAbsor[k],               
                                     String(GetName(fAbsorMaterial[k])),
                                     det.fLogicLayer,                  
                                     false,                      
                                     k) for  k in 1:fNbOfAbsor]
    return det.fPhysiWorld
end

Geant4.getConstructor(::TestEm3Detector)::Function = TestEm3Construct
