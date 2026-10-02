using Parameters
#--------------------------------------------------------------------------------------------------
# Implementation of the B3::DetectorConstruction class
#--------------------------------------------------------------------------------------------------
@with_kw mutable struct B3Detector <: G4JLDetector
    cryst_dX::Float64 = 6cm
    cryst_dY::Float64 = 6cm
    cryst_dZ::Float64 = 3cm
    nb_cryst::Int32 = 32
    nb_rings::Int32 = 9
    patient_radius::Float64 = 8cm
    patient_dZ::Float64 = 10cm
    checkOverlaps::Bool = true
end

function construct(det::B3Detector)::CxxPtr{G4VPhysicalVolume}
    (; cryst_dX, cryst_dY, cryst_dZ, nb_cryst, nb_rings, patient_radius, checkOverlaps, patient_dZ) = det

    #---Derived parameters-------------------------------------------------------------------------
    dPhi = 2π/nb_cryst 
    half_dPhi = 0.5*dPhi
    cosdPhi = cos(half_dPhi)
    tandPhi = tan(half_dPhi)
    ring_R1 = 0.5*cryst_dY/tandPhi
    ring_R2 = (ring_R1+cryst_dZ)/cosdPhi
    detector_dZ = nb_rings*cryst_dX
    world_sizeXY = 2.4*ring_R2
    world_sizeZ  = 1.2*detector_dZ
  
    #---Materials----------------------------------------------------------------------------------
    nist = G4NistManager!Instance()
    default_mat = FindOrBuildMaterial(nist, "G4_AIR")

    O = FindOrBuildElement(nist, "O" , false)
    Si = FindOrBuildElement(nist, "Si", false)
    Lu = FindOrBuildElement(nist, "Lu", false)
    Lu2SiO5 = G4Material("Lu2SiO5", density=7.4*g/cm3, ncomponents=3)
    AddElement(Lu2SiO5, Lu, natoms=2)
    AddElement(Lu2SiO5, Si, natoms=1)
    AddElement(Lu2SiO5, O, natoms=5)
  
    cryst_mat   = FindOrBuildMaterial(nist, "Lu2SiO5")
    @show cryst_mat

    #---Volumes------------------------------------------------------------------------------------
    solidWorldS = G4Box("world", world_sizeXY/2, world_sizeXY/2, world_sizeZ/2)
    logicWorld  = G4LogicalVolume(solidWorldS, default_mat, "World")
    physWorld   = G4PVPlacement(nothing, 
                                G4ThreeVector(),                # at (0,0,0)
                                logicWorld,                     # its logical volume
                                "World",                        # its name
                                nothing,                        # its mother  volume
                                false,                          # no boolean operations
                                0,                              # copy number
                                checkOverlaps)                  # checking overlaps

    solidRing = G4Tubs("Ring", ring_R1, ring_R2, cryst_dX/2, 0., 2π)
    logicRing = G4LogicalVolume(solidRing, default_mat, "Ring")

    gap = 0.5mm 
    dX = cryst_dX - gap
    dY = cryst_dY - gap
    solidCryst = G4Box("crystal", dX/2, dY/2, cryst_dZ/2)
    logicCryst = G4LogicalVolume(solidCryst, cryst_mat, "CrystalLV")

    # place crystals within a ring
    for icrys in 0:nb_cryst-1
      ϕ = icrys*dPhi
      rotm  = G4RotationMatrix()
      rotateY(rotm, π/2)
      rotateZ(rotm, ϕ)
      position = (ring_R1 + cryst_dZ/2) * G4ThreeVector(cos(ϕ), sin(ϕ), 0)
      transform = G4Transform3D(rotm, position)
  
      G4PVPlacement(transform,             # rotation,position
                    logicCryst,            # its logical volume
                    "crystal",             # its name
                    logicRing,             # its mother  volume
                    false,                 # no boolean operation
                    icrys,                 # copy number
                    checkOverlaps)         # checking overlaps
    end
  
    # full detector
    solidDetector = G4Tubs("Detector", ring_R1, ring_R2, detector_dZ/2, 0., 2π)
    logicDetector = G4LogicalVolume(solidDetector, default_mat, "Detector")

    # place rings within detector
    OG = -0.5*(detector_dZ + cryst_dX)
    for iring in 0:nb_rings-1
      OG += cryst_dX
      G4PVPlacement(nothing,                  # no rotation
                    G4ThreeVector(0, 0, OG),  # position
                    logicRing,                # its logical volume
                    "ring",                   # its name
                    logicDetector,            # its mother  volume
                    false,                    # no boolean operation
                    iring,                    # copy number
                    checkOverlaps)            # checking overlaps
    end
    
    # place detector in world
    G4PVPlacement(nothing,                  # no rotation
                  G4ThreeVector(),          # at (0,0,0)
                  logicDetector,            # its logical volume
                  "Detector",               # its name
                  logicWorld,               # its mother  volume
                  false,                    # no boolean operation
                  0,                        # copy number
                  checkOverlaps)            # checking overlaps

    # patient
    patient_mat = FindOrBuildMaterial(nist, "G4_BRAIN_ICRP")
    solidPatient = G4Tubs("Patient", 0., patient_radius, patient_dZ/2, 0., 2π)
    logicPatient = G4LogicalVolume(solidPatient, patient_mat,"PatientLV")
    G4PVPlacement(nothing  ,                # no rotation
                  G4ThreeVector(),          # at (0,0,0)
                  logicPatient,             # its logical volume
                  "Patient",                # its name
                  logicWorld,               # its mother  volume
                  false,                    # no boolean operation
                  0,                        # copy number
                  checkOverlaps)            # checking overlaps
                

    #---Visualization attributes-------------------------------------------------------------------
    SetVisAttributes(logicWorld, G4VisAttributes!GetInvisible())
    SetVisAttributes(logicRing, G4VisAttributes!GetInvisible())
    SetVisAttributes(logicDetector, G4VisAttributes!GetInvisible())

    #---Always return the physical world-----------------------------------------------------------
    return physWorld
end

Geant4.getConstructor(::B3Detector)::Function = construct
