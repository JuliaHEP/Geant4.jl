#--------------------------------------------------------------------------------------------------
# Implementation of the B2a::DetectorConstruction class
#--------------------------------------------------------------------------------------------------
mutable struct B2aDetector <: G4JLDetector
    # main input parameters
    const nChambers::Int            # number of chambers
    const checkOverlaps::Bool       # do check overlaps when creating the geometry
    const chamberSpacing::Float64   # from chamber center to center!
    const chamberWidth::Float64     # width of the chambers
    const targetLength::Float64     # full length of Target
    # mutable data
    worldZHalfLength::Float64
    # constructor with defaults values for parameters
    function B2aDetector(;  nChambers::Int=5, 
                            checkOverlaps::Bool=true,
                            chamberSpacing::Float64=80cm,
                            chamberWidth::Float64=20cm,
                            targetLength::Float64=5cm)
        self = new(nChambers, checkOverlaps, chamberSpacing, chamberWidth, targetLength)
        # Setup some geometry
        self.worldZHalfLength = 1.2 * (2*targetLength +  (nChambers+1) * chamberSpacing) /2 
        return self
    end
end

function B2aConstruct(det::B2aDetector)::CxxPtr{G4VPhysicalVolume}
    (; nChambers, checkOverlaps, chamberSpacing, chamberWidth, targetLength) = det

    #---Materials----------------------------------------------------------------------------------
    nist = G4NistManager!Instance()
    m_air = FindOrBuildMaterial(nist, "G4_AIR")
    m_target = FindOrBuildMaterial(nist, "G4_Pb")
    m_chamber = FindOrBuildMaterial(nist, "G4_Xe")

    #---Derived parameters-------------------------------------------------------------------------
    trackerLength = (nChambers+1) * chamberSpacing
    worldLength = 1.2 * (2*targetLength + trackerLength)
    targetRadius = targetLength/2   # Radius of Target
    targetLength = targetLength/2   # Half length of the Target
    trackerSize  = trackerLength/2  # Half length of the Tracker

    #---Volumes------------------------------------------------------------------------------------
    det.worldZHalfLength = worldLength/2
    worldS = G4Box("world", det.worldZHalfLength, det.worldZHalfLength, det.worldZHalfLength)
    worldLV = G4LogicalVolume(move!(worldS), m_air, "World")
    worldPV = G4PVPlacement(nothing, 
        G4ThreeVector(),                # at (0,0,0)
        worldLV,                        # its logical volume
        "World",                        # its name
        nothing,                        # its mother  volume
        false,                          # no boolean operations
        0,                              # copy number
        checkOverlaps)                  # checking overlaps

    positionTarget = G4ThreeVector(0,0,-(targetLength+trackerSize))
    targetS = G4Tubs("target", 0, targetRadius, targetLength/2, 0, 360deg)
    targetLV = G4LogicalVolume(move!(targetS), m_target, "Target")
    G4PVPlacement(nothing,              # no rotation
        positionTarget,                 # at (x,y,z)
        targetLV,                       # its logical volume
        "Target",                       # its name
        worldLV,                        # its mother volume
        false,                          # no boolean operations
        0,                              # copy number
        checkOverlaps)                  # checking overlaps
  
    positionTracker = G4ThreeVector(0,0,0)
    trackerS = G4Tubs("tracker", 0, trackerSize, trackerSize, 0, 360deg)
    trackerLV = G4LogicalVolume(move!(trackerS), m_air, "Tracker")
    G4PVPlacement(nothing,              # no rotation
        positionTracker,                # at (x,y,z)
        trackerLV,                      # its logical volume
        "Tracker",                      # its name
        worldLV,                        # its mother  volume
        false,                          # no boolean operations
        0,                              # copy number
        checkOverlaps)                  # checking overlaps

    # Visualization attributes
    boxVisAtt = G4VisAttributes(G4Colour(1.0, 1.0, 1.0, 0.1))
    targetVisAtt = G4VisAttributes(G4Colour(0.0, 0.0, 1.0))
    chamberVisAtt = G4VisAttributes(G4Colour(1.0, 1.0, 0.0))
    SetVisAttributes(worldLV, boxVisAtt)
    SetVisAttributes(targetLV, targetVisAtt)
    SetVisAttributes(trackerLV, boxVisAtt)

    # Tracker segments
    firstPosition = -trackerSize + chamberSpacing
    firstLength   = trackerLength/10
    lastLength    = trackerLength
  
    halfWidth = chamberWidth/2
    rmaxFirst = firstLength/2
  
    rmaxIncr = 0.
    if nChambers > 0
        rmaxIncr =  0.5 * (lastLength-firstLength)/(nChambers-1)
        if chamberSpacing  < chamberWidth
            G4Exception("DetectorConstruction::DefineVolumes()",
                       "InvalidSetup", FatalException,
                       "Width>Spacing")
        end 
    end

    fLogicChamber = Vector{G4LogicalVolume}()

    for copyNo in 1:nChambers
        Zposition = firstPosition + (copyNo-1) * chamberSpacing
        rmax =  rmaxFirst + (copyNo -1) * rmaxIncr
        chamberS = G4Tubs("Chamber_solid", 0, rmax, halfWidth, 0, 360deg)
        push!(fLogicChamber, G4LogicalVolume(move!(chamberS), m_chamber, "Chamber_LV"))
  
        SetVisAttributes(fLogicChamber[copyNo], chamberVisAtt)

        G4PVPlacement(nothing,              # no rotation
            G4ThreeVector(0, 0, Zposition), # at (x,y,z)
            fLogicChamber[copyNo],          # its logical volume
            "Chamber_PV",                   # its name
            trackerLV,                      # its mother  volume
            false,                          # no boolean operations
            copyNo,                         # copy number
            checkOverlaps)                  # checking overlaps
    end

    # Example of User Limits
    #
    # Below is an example of how to set tracking constraints in a given
    # logical volume
    #
    # Sets a max step length in the tracker region, with G4StepLimiter
    maxStep = chamberWidth/2
    fStepLimit = G4UserLimits(maxStep)
    SetUserLimits(trackerLV, move!(fStepLimit))
   
    # Always return the physical world-------------------------------------------------------------
    return worldPV
end

Geant4.getConstructor(::B2aDetector)::Function = B2aConstruct
