using Geant4
using Geant4.SystemOfUnits
using Parameters

#---Detector parameters----------------------------------------------------------------------------
# The head of a GE Saturn 43 linear accelerator in the 12 MV photon mode and a water phantom. The
# head (target, primary collimator, flattening filter, ionization chamber, vacuum window and jaws)
# is inside a vacuum box whose origin is the source. The phantom surface is at z = 0 and the beam
# goes along +z. Only the field size and the source to skin distance are parameters. The
# dimensions of the head are fixed in the construction function.
@with_kw mutable struct MedicalLinacDetector <: G4JLDetector
    fieldSide::Float64 = 100mm                  ## side of the square field at SSD + 10 cm
    sourceToSkinDistance::Float64 = 900mm       ## SSD: from the source to the phantom surface
    phantomSide::Float64 = 255mm                ## side of the cubic water phantom
    checkOverlaps::Bool = false
    ##---filled by the construction
    jawPVs::Vector{CxxPtr{G4VPhysicalVolume}} = CxxPtr{G4VPhysicalVolume}[]     ## the 4 jaw envelopes
    filterPVs::Vector{CxxPtr{G4VPhysicalVolume}} = CxxPtr{G4VPhysicalVolume}[]  ## target, collimator and flattening filter
    ffRadius::Float64 = 54mm                    ## radius and position of the top face of the
    ffZ::Float64 = 149.5mm                      ## flattening filter (they define the useful cone)
end

# Visualization attributes (colour and transparency) of a logical volume
setVis(lv, r, g, b, a=1.; visible=true) = SetVisAttributes(lv, G4VisAttributes(visible, G4Colour(r, g, b, a)))

# Region with its production cut for all particles
function cutRegion(name, cut, lvs...)
    region = G4Region(name)
    foreach(lv -> AddRootLogicalVolume(region, lv), lvs)
    cuts = G4ProductionCuts()
    SetProductionCut(cuts, cut)
    SetProductionCuts(region, cuts)
    return region
end

function rotation(; x=0, y=0)
    rot = G4RotationMatrix()
    x != 0 && rotateX(rot, x)
    y != 0 && rotateY(rot, y)
    return rot
end

#---Detector construction--------------------------------------------------------------------------
function medicalLinacConstruct(det::MedicalLinacDetector)::CxxPtr{G4VPhysicalVolume}
    (; fieldSide, sourceToSkinDistance, phantomSide, checkOverlaps) = det
    nist = G4NistManager!Instance()
    empty!(det.jawPVs)
    empty!(det.filterPVs)

    #---Materials----------------------------------------------------------------------------------
    air = FindOrBuildMaterial(nist, "G4_AIR")
    vacuum = FindOrBuildMaterial(nist, "G4_Galactic")
    water = FindOrBuildMaterial(nist, "G4_WATER")
    W = FindOrBuildMaterial(nist, "G4_W")
    Ti = FindOrBuildMaterial(nist, "G4_Ti")
    Pb = FindOrBuildMaterial(nist, "G4_Pb")
    Al = FindOrBuildMaterial(nist, "G4_Al")
    if G4Material!GetMaterial("Denal(WNICU)", false) == C_NULL
        for (name, density, fractions) in
            (("StainlessSteel", 7.8g/cm3, ("G4_Fe" => 0.6898, "G4_Cr" => 0.18, "G4_Ni" => 0.10,
                                           "G4_Mn" => 0.02, "G4_Si" => 0.01, "G4_C" => 0.0002)),
             ("CARBON_STEEL", 7.8g/cm3, ("G4_Fe" => 0.993, "G4_Mn" => 0.006, "G4_C" => 0.001)),
             ("Denal(WNICU)", 16.8g/cm3, ("G4_W" => 0.905, "G4_Ni" => 0.07, "G4_Cu" => 0.025)),
             ("Kapton", 1.42g/cm3, ("G4_C" => 0.691133, "G4_O" => 0.209235, "G4_N" => 0.07327, "G4_H" => 0.026362)))
            mat = G4Material(name, density=density, ncomponents=length(fractions))
            for (el, f) in fractions
                AddMaterial(mat, FindOrBuildMaterial(nist, el), f)
            end
        end
    end
    steel = G4Material!GetMaterial("StainlessSteel")
    xc10 = G4Material!GetMaterial("CARBON_STEEL")
    wnicu = G4Material!GetMaterial("Denal(WNICU)")
    kapton = G4Material!GetMaterial("Kapton")

    # Logical volume with a colour, and placement inside a mother volume
    function volume(solid, material, name, color...; visible=true)
        lv = G4LogicalVolume(solid, material, name)
        setVis(lv, color..., visible=visible)
        return lv
    end
    place(lv, name, mother, z; x=0., y=0.) = G4PVPlacement(nothing, G4ThreeVector(x, y, z), lv, name, mother, false, 0, checkOverlaps)
    tube(name, r, hz) = G4Tubs(name, 0, r, hz, 0, 2π)
    cone(name, r1, r2, hz) = G4Cons(name, 0, r1, 0, r2, hz, 0, 2π)       ## radius r1 at -hz and r2 at +hz
    noRot = CxxPtr{G4RotationMatrix}(C_NULL)

    #---World and accelerator box------------------------------------------------------------------
    worldLV = volume(G4Box("World", 1.75m, 1.75m, 1.75m), air, "World", 1, 1, 1, visible=false)
    worldPV = G4PVPlacement(nothing, G4ThreeVector(), worldLV, "World", nothing, false, 0, checkOverlaps)
    accLV = volume(G4Box("accWorld", 600mm, 600mm, 600mm), vacuum, "accWorld", 1, 1, 1, visible=false)
    place(accLV, "acceleratorBox", worldLV, -sourceToSkinDistance)

    #---Target: W block with a hole on the beam side, and a Ti disk----------------------------------
    targetLV = volume(G4SubtractionSolid("TargetSolid", move!(G4Box("targetBox", 5mm, 5mm, 7.5mm)),
                                         move!(tube("targetTube", 3mm, 5.5mm)), noRot, G4ThreeVector(0, 0, -2mm)),
                      W, "TargetLV", 0.5, 0.5, 0.5)
    targetPV = place(targetLV, "TargetPV", accLV, -3.5mm)
    diskLV = volume(tube("targetDisk", 4mm, 0.025mm), Ti, "targetDiskLV", 0.5, 0.5, 0.5)
    place(diskLV, "diskPV", accLV, -15mm)
    cutRegion("TargetR", 1mm, targetLV, diskLV)

    #---Primary collimator: three tubes with a conical hole------------------------------------------
    # Each hole is a short cylinder (of length 2hzTube) followed by a cone that opens downwards. The
    # C++ example subtracts the hole from the tube. The same solid is a G4Polycone, which is simpler
    # and can also be drawn cut in half. The arrays are passed to C++ as pointers, so they must be
    # kept alive during the call.
    function collimator(name, R, hz, r, hzTube, r2, material, color...)
        z, rin, rout = [-hz, -hz + 2hzTube, hz], [r, r, r2], [R, R, R]
        solid = GC.@preserve z rin rout G4Polycone(name, 0, 2π, 3, z, rin, rout)
        volume(solid, material, name * "LV", color..., 0.3)
    end
    z1 = 5mm + 39.5mm
    upperLV = collimator("PriCollUpper", 70.5mm, 39.5mm, 17mm, 7.93mm, 27mm, xc10, 0, 1, 0)
    z2 = z1 + 39.5mm + 28.75mm
    middleLV = collimator("PriCollMiddle", 70.5mm, 28.75mm, 26.5mm, 0.675mm, 40.5mm, wnicu, 1, 0, 0)
    z3 = z2 + 28.75mm + 19.5mm + 20.25mm
    lowerLV = collimator("PriCollLower", 120.5mm, 20.25mm, 44.03mm, 0, 54.88mm, Pb, 0, 0, 1)
    upperPV = place(upperLV, "PriCollUpperPV", accLV, z1)
    middlePV = place(middleLV, "PriCollMiddlePV", accLV, z2)
    place(lowerLV, "PriCollLowerPV", accLV, z3)
    cutRegion("primaryCollimatorR", 1cm, upperLV, middleLV, lowerLV)

    #---Vacuum window------------------------------------------------------------------------------
    windowLV = volume(tube("VacWindowTube", 116.53mm/2, 1mm), Al, "VacWindowTubeLV", 0, 1, 0)
    place(windowLV, "VacWindowTubePV", accLV, 215.75mm + 1mm)
    cutRegion("VacWindowR", 1mm, windowLV)

    #---Flattening filter: a tube and three cones of steel-------------------------------------------
    hzTube, hz1, hz2, hz3 = 7.5mm/2, 13.7mm/2, (44.3mm - 13.7mm)/2, (46.8mm - 44.3mm)/2
    pos1 = hz1 - hzTube - 1mm
    pos2 = pos1 + hz1 + hz2
    pos3 = pos2 + hz2 + hz3
    ff = G4UnionSolid("ffTube1AndCone1", move!(tube("ffTube1", det.ffRadius, hzTube)), move!(cone("ffCone1", 38mm, 27mm, hz1)),
                      noRot, G4ThreeVector(0, 0, pos1))
    ff = G4UnionSolid("ffTubeCone1AndCone2", move!(ff), move!(cone("ffCone2", 27mm, 4mm, hz2)), noRot, G4ThreeVector(0, 0, pos2))
    ff = G4UnionSolid("ffTubeCone12AndCone3", move!(ff), move!(cone("ffCone3", 4mm, 1e-6mm, hz3)), noRot, G4ThreeVector(0, 0, pos3))
    ffLV = volume(ff, steel, "ffLV", 1, 0, 1)
    ffPV = place(ffLV, "ffPV", accLV, det.ffZ + hzTube)
    cutRegion("ffR", 1mm, ffLV)

    #---Ionization chamber: six Al layers, each followed by a kapton layer----------------------------
    hzKapton, hzAl1, hzAl8 = 0.025mm/2, 1.6e-5cm/2, 8e-6cm/2
    al1LV = volume(tube("ICTube2A", 55mm, hzAl1), Al, "IC_Al1_LV", 1, 0, 0)
    al8LV = volume(tube("ICTube1A", 55mm, hzAl8), Al, "IC_Al8_LV", 1, 0, 1)
    kaptonLV = volume(tube("ICTube1B", 55mm, hzKapton), kapton, "IC_K_LV", 0, 0, 1)
    for (i, (z, alLV, hzAl)) in enumerate(((202.5mm, al8LV, hzAl8), (204.5mm, al1LV, hzAl1), (206.5mm, al8LV, hzAl8),
                                           (207.5mm, al8LV, hzAl8), (209.5mm, al1LV, hzAl1), (211.5mm, al8LV, hzAl8)))
        place(alLV, "IC_Al_PV$i", accLV, z + hzAl)
        place(kaptonLV, "IC_K_PV$i", accLV, z + 2hzAl + hzKapton)
    end
    cutRegion("IonChamberR", 0.1mm, al1LV, al8LV, kaptonLV)

    #---Jaws---------------------------------------------------------------------------------------
    # Each jaw is a stack of blocks inside an air envelope of 101 × 101 mm. The envelopes are rotated
    # around the source, so that their inner faces define a field of side `fieldSide` at SSD + 10 cm.
    # As in the C++ example, the envelopes of the X and Y jaws overlap (only their air parts), so
    # the overlaps are not checked.
    θ = atan(fieldSide/2 / (sourceToSkinDistance + 10cm))
    jawLVs = G4LogicalVolume[]
    function jaw(name, height, z0, blocks, axis, sign)
        envLV = volume(G4Box(name * "box", 50.5mm, 50.5mm, height/2), air, name * "boxLV", 1, 1, 0, visible=false)
        z = -height/2
        for (i, (thickness, gap, material, color)) in enumerate(blocks)
            z += gap
            lv = volume(G4Box(name * "Block$i", 50.5mm, 50.5mm, thickness/2), material, name * "LV$i", color...)
            G4PVPlacement(nothing, G4ThreeVector(0, 0, z + thickness/2), lv, name * "PV$i", envLV, false, 0, false)
            push!(jawLVs, lv)
            z += thickness
        end
        rot = axis == :x ? rotation(y=sign*θ) : rotation(x=-sign*θ)
        pos = rot * (axis == :x ? G4ThreeVector(sign*50.5mm, 0, z0 + height/2) : G4ThreeVector(0, sign*50.5mm, z0 + height/2))
        push!(det.jawPVs, G4PVPlacement(G4Transform3D(rot, pos), envLV, name * "PV", accLV, false, 0, false))
    end
    green, blue, red = (0, 1, 0), (0, 0, 1), (1, 0, 0)
    xBlocks = ((3mm, 0, xc10, green), (35mm, 0, Pb, blue), (35mm, 0, wnicu, red), (27mm, 0, Pb, blue),
               (10mm, 97mm, Pb, blue), (5mm, 0, wnicu, red))
    yBlocks = ((15mm, 0, xc10, red), (31mm, 117.5mm, Pb, blue), (35mm, 0, wnicu, red), (21mm, 0, Pb, blue))
    jaw("Jaw1X", 212mm, 275.5mm, xBlocks, :x, 1)
    jaw("Jaw2X", 212mm, 275.5mm, xBlocks, :x, -1)
    jaw("Jaw1Y", 219.5mm, 248.5mm, yBlocks, :y, 1)
    jaw("Jaw2Y", 219.5mm, 248.5mm, yBlocks, :y, -1)
    cutRegion("JawsR", 2cm, jawLVs...)

    #---Water phantom------------------------------------------------------------------------------
    # A 2.5 mm water layer in front of the phantom, which starts at z = 2.5 mm.
    h = phantomSide/2
    layerLV = volume(G4Box("Spessore", h, h, 1.25mm), water, "spessore_log", 0, 1, 1, 0.1)
    place(layerLV, "spessore_phys", worldLV, 1.25mm)
    phantomLV = volume(G4Box("Phantom", h, h, h), water, "Phantom_log", 0, 1, 1, 0.1)
    place(phantomLV, "phantom_phys", worldLV, h + 2.5mm)
    cutRegion("fullWaterPhantomR", 0.1mm, phantomLV)

    append!(det.filterPVs, (targetPV, upperPV, middlePV, ffPV))
    return worldPV
end

Geant4.getConstructor(::MedicalLinacDetector)::Function = medicalLinacConstruct
