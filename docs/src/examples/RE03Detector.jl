# Implementation of the RE03::DetectorConstruction class
#--------------------------------------------------------------------------------------------------
mutable struct RE03Detector <: G4JLDetector
end

function construct(::RE03Detector)::CxxPtr{G4VPhysicalVolume}
    #---Materials----------------------------------------------------------------------------------
    nist = G4NistManager!Instance()
    fAir = FindOrBuildMaterial(nist, "G4_AIR")
    fWater = FindOrBuildMaterial(nist, "G4_WATER")

    #---World--------------------------------------------------------------------------------------
    worldSolid = G4Box("World",2m, 2m, 2m)
    worldLogical = G4LogicalVolume(worldSolid,fAir,"World")
    worldPhys = G4PVPlacement(nothing, G4ThreeVector(), worldLogical, "World", nothing,false,0)
    
    #---Phantom------------------------------------------------------------------------------------
    phantomSolid = G4Box("Phantom", 1m, 1m, 1m)
    phantomLogical = G4LogicalVolume(phantomSolid, fWater, "Phantom");
    phantomPhys = G4PVPlacement(nothing, G4ThreeVector(), phantomLogical, "Phantom", worldLogical, false, 0)
    
    #---Visualization attributes-------------------------------------------------------------------
    SetVisAttributes(worldLogical, G4VisAttributes!GetInvisible())
    simpleBoxVisAtt = G4VisAttributes(G4Colour(1.0, 1.0, 1.0))
    SetVisibility(simpleBoxVisAtt, true)
    SetVisAttributes(phantomLogical, simpleBoxVisAtt)

    return worldPhys
end

Geant4.getConstructor(::RE03Detector)::Function = construct