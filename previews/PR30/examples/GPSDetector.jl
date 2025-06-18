# Implementation of the exgps::DetectorConstruction class
#--------------------------------------------------------------------------------------------------
@with_kw mutable struct GPSDetector <: G4JLDetector
    world_r::Float64 = 18*cm
    box_x::Float64 = 10*cm
    box_y::Float64 = 10*cm
    box_z::Float64 = 10*cm
    sphere_r::Float64 = 5*cm
end

function construct(det::GPSDetector)::CxxPtr{G4VPhysicalVolume}
    #---Materials----------------------------------------------------------------------------------
    VacMat = G4Material("Vacuum", z=1., a=1.01g/mole, density=universe_mean_density, state=kStateGas, 
                        temperature=2.73*kelvin, pressure=3.e-18*pascal)
    AlMat = G4Material("Aluminium", z=13., a=26.98154*g/mole, density=2.70*g/cm3)
    Si = G4Element("Silicon", "Si", 14., 28.0855*g/mole)
    O = G4Element("Oxygen", "O", 8., 16.00*g/mole)
    SiO₂Mat = G4Material("Silicon oxide", density=16.00*g/mole, ncomponents=2)
    AddElement(SiO₂Mat, move!(Si), natoms=1)
    AddElement(SiO₂Mat, move!(O), natoms=2)

    #---World--------------------------------------------------------------------------------------
    universe_s = G4Sphere("universe_s", 0, det.world_r, 0, 2π, 0, π)
    universe_log = G4LogicalVolume(universe_s, CxxPtr(VacMat), "universe_L")
    universe_phys = G4PVPlacement(nothing, G4ThreeVector(), universe_log, "universe_P", nothing, false, 0)

    #---define an aluminium box--------------------------------------------------------------------
    Al_box = G4Box("Al_b", det.box_x, det.box_y, det.box_z)
    Al_log = G4LogicalVolume(Al_box, CxxPtr(AlMat), "Box_log")
    G4PVPlacement(nothing, G4ThreeVector(), Al_log, "Box_phys", universe_log, false, 0)

    #---Define an inner sphere---------------------------------------------------------------------
    aSphere_sph = G4Sphere("aSphere", 0, det.sphere_r, 0, 2π, 0, π)
    aSphere_log = G4LogicalVolume(aSphere_sph, CxxPtr(SiO₂Mat), "Sphere_log")
    G4PVPlacement(nothing, G4ThreeVector(), aSphere_log, "Sphere_phys", Al_log, false, 0)
    
    #---Visualization attributes-------------------------------------------------------------------
    SetVisAttributes(universe_log, G4VisAttributes!GetInvisible())
    aVisAtt = G4VisAttributes(G4Colour(0, 1.0, 1.0))
    SetVisAttributes(Al_log, aVisAtt)
    bVisAtt = G4VisAttributes(G4Colour(1.0,2.0,.0))
    SetVisAttributes(aSphere_log, bVisAtt)

    return universe_phys
end

Geant4.getConstructor(::GPSDetector)::Function = construct
