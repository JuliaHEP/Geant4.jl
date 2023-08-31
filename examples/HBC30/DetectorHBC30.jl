
mutable struct HBC30 <: G4JLDetector
    # main input parameters
    const chamberDiameter::Float64  # chamber diameter
    const targetLength::Float64     # length of target
    const checkOverlaps::Bool       # do check overlaps when creating the geometry
    # mutable data
    worldZHalfLength::Float64
    # constructor with defaults values for parameters
    function HBC30(; chamberDiameter=30cm,
                     targetLength=5cm,
                     checkOverlaps=false)
        self = new(chamberDiameter, targetLength, checkOverlaps)
        # derived parameters
        self.worldZHalfLength = 1.1 * (targetLength + chamberDiameter)/2
        return self
    end
end

import Geant4.SystemOfUnits:mole,cm3

function HBC30Construct(det::HBC30)::CxxPtr{G4VPhysicalVolume}
    (; chamberDiameter, targetLength, checkOverlaps) = det

    #---Materials----------------------------------------------------------------------------------
    G4Material("LH₂",  z=1., a=1.008*g/mole, density= 70.8*mg/cm3)
    nist = G4NistManager!Instance()
    m_air    = FindOrBuildMaterial(nist, "G4_AIR")
    m_lh2    = FindOrBuildMaterial(nist, "LH₂")
    m_glass  = FindOrBuildMaterial(nist, "G4_GLASS_PLATE")
    m_target = FindOrBuildMaterial(nist, "G4_W")

    #---Volumes------------------------------------------------------------------------------------
    worldS  = G4Box("world", det.worldZHalfLength, det.worldZHalfLength, det.worldZHalfLength)
    worldLV = G4LogicalVolume(move!(worldS), m_air, "World")
    worldPV = G4PVPlacement(nothing, G4ThreeVector(), worldLV, "World", nothing, false, 0, checkOverlaps)

    chamberS  = G4Tubs("chamber", 0, chamberDiameter/2, 7.5cm, 0, 2π)
    chamberLV = G4LogicalVolume(move!(chamberS), m_lh2, "chamber")
    G4PVPlacement(nothing, G4ThreeVector(), chamberLV, "chamber", worldLV, false, 0, checkOverlaps)

    windowS  = G4Tubs("window", 0, chamberDiameter/2, 1.5cm, 0, 2π)
    windowLV = G4LogicalVolume(move!(windowS), m_glass, "window")
    G4PVPlacement(nothing, G4ThreeVector(0, 0, 7.5cm+1.5cm), windowLV, "window1", worldLV, false, 0, checkOverlaps)
    G4PVPlacement(nothing, G4ThreeVector(0, 0, -7.5cm-1.5cm), windowLV, "window2", worldLV, false, 0, checkOverlaps)

    targetS = G4Tubs("target", 0, 1cm, targetLength/2, 0, 2π)
    targetLV = G4LogicalVolume(move!(targetS), m_air, "target")
    rot = G4RotationMatrix()
    rotateX(rot, π/2)
    G4PVPlacement(rot, G4ThreeVector(0, chamberDiameter/2+targetLength/2, 0), targetLV, "target", worldLV, false, 0, checkOverlaps)

    # Visualization attributes
    boxVisAtt = G4VisAttributes(G4Colour(1.0, 1.0, 1.0, 0.0))
    targetVisAtt = G4VisAttributes(G4Colour(1.0, 1.0, 1.0, 0.9))
    chamberVisAtt = G4VisAttributes(G4Colour(1.0, 1.0, 0.0, 0.1))
    windowVisAtt = G4VisAttributes(G4Colour(0.0, 0.0, 1.0, 0.05))
    SetVisAttributes(worldLV, boxVisAtt)
    SetVisAttributes(targetLV, targetVisAtt)
    SetVisAttributes(chamberLV, chamberVisAtt)
    SetVisAttributes(windowLV, windowVisAtt)

    # Always return the physical world-------------------------------------------------------------
    return worldPV
end

Geant4.getConstructor(::HBC30)::Function = HBC30Construct
