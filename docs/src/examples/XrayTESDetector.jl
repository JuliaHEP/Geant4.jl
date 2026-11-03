using Geant4
using Geant4.SystemOfUnits
using Parameters

#---Detector parameters----------------------------------------------------------------------------
# The TES array of the X-IFU: 317 square Bi absorbers on a Si3N4 membrane and a Si grid, inside a
# hexagonal envelope. Only the parameters of the array are exposed. The dimensions of the supports,
# shields and cryostat come from a CAD model and are fixed in the construction function.
@with_kw mutable struct XrayTESDetector <: G4JLDetector
    absorberThickness::Float64 = 3μm          ## Bi absorber
    membraneThickness::Float64 = 0.75μm       ## Si3N4 membrane under the absorbers
    gridThickness::Float64 = 200μm            ## Si grid supporting the membrane
    gridBeam::Float64 = 165μm                 ## width of the grid walls
    waferThickness::Float64 = 0.25mm          ## Si support wafer around the array
    pixelPitch::Float64 = 0.814mm
    pixelGap::Float64 = 11μm
    arrayApothem::Float64 = 8.5mm             ## apothem of the hexagonal envelope of the array
    pixelApothem::Float64 = 8.4mm             ## pixels must fit inside this hexagon
    checkOverlaps::Bool = false
    ##---filled by the construction
    arrayPV::CxxPtr{G4VPhysicalVolume} = CxxPtr{G4VPhysicalVolume}(C_NULL)
    absorberPV::CxxPtr{G4VPhysicalVolume} = CxxPtr{G4VPhysicalVolume}(C_NULL)
    acdLVs::Vector{CxxPtr{G4LogicalVolume}} = CxxPtr{G4LogicalVolume}[]
end

# Positions of the pixels: the cells of a square lattice that fit inside a hexagon with flat sides
# at the top and bottom (as the G4Polyhedra envelope), numbered row by row from the bottom.
function pixelPositions(det::XrayTESDetector)
    (; pixelPitch, pixelApothem) = det
    inside(x, y) = abs(y) <= pixelApothem && abs(x) * √3/2 + abs(y)/2 <= pixelApothem
    n = ceil(Int, pixelApothem / pixelPitch) + 1
    positions = Tuple{Float64,Float64}[]
    for j in -n:n, i in -n:n
        x, y = i * pixelPitch, j * pixelPitch
        all(inside(x + dx * pixelPitch/2, y + dy * pixelPitch/2) for dx in (-1, 1), dy in (-1, 1)) && push!(positions, (x, y))
    end
    return positions
end

# Name of the region of the volumes near the detector
const innerRegion = "InnerRegion"

# Visualization attributes (colour and transparency) of a logical volume
setVis(lv, r, g, b, a=1.; visible=true) = SetVisAttributes(lv, G4VisAttributes(visible, G4Colour(r, g, b, a)))

# Hexagonal prism (6 sides) between z = -hz and z = hz, with inner and outer apothems at both ends.
# The arrays are passed to C++ as pointers, so they must be kept alive during the call.
function hexagon(name, hz, rin, rout)
    z, ri, ro = [-hz, hz], collect(Float64, rin), collect(Float64, rout)
    GC.@preserve z ri ro G4Polyhedra(name, 0, 2π, 6, 2, z, ri, ro)
end

function rotation(; x=0, y=0, z=0)
    rot = G4RotationMatrix()
    x != 0 && rotateX(rot, x)
    y != 0 && rotateY(rot, y)
    z != 0 && rotateZ(rot, z)
    return rot
end

#---Detector construction--------------------------------------------------------------------------
function xrayTESConstruct(det::XrayTESDetector)::CxxPtr{G4VPhysicalVolume}
    (; absorberThickness, membraneThickness, gridThickness, gridBeam, waferThickness,
       pixelPitch, pixelGap, arrayApothem, checkOverlaps) = det
    nist = G4NistManager!Instance()

    #---Materials----------------------------------------------------------------------------------
    vacuum = FindOrBuildMaterial(nist, "G4_Galactic")
    Si = FindOrBuildMaterial(nist, "G4_Si")
    Cu = FindOrBuildMaterial(nist, "G4_Cu")
    Bi = FindOrBuildMaterial(nist, "G4_Bi")
    Al = FindOrBuildMaterial(nist, "G4_Al")
    Au = FindOrBuildMaterial(nist, "G4_Au")
    Ti = FindOrBuildMaterial(nist, "G4_Ti")
    if G4Material!GetMaterial("Cryoperm", false) == C_NULL
        ringAl = G4Material("RingAl", density=0.736g/cm3, ncomponents=1)     ## Al with the average density of the ring
        AddMaterial(ringAl, Al, 1.)
        cryoperm = G4Material("Cryoperm", density=8.7g/cm3, ncomponents=4)
        for (el, f) in (("G4_Ni", 0.775), ("G4_Cu", 0.045), ("G4_Mo", 0.025), ("G4_Fe", 0.155))
            AddMaterial(cryoperm, FindOrBuildMaterial(nist, el), f)
        end
        steel = G4Material("StainlessSteel", density=8.03g/cm3, ncomponents=8)
        for (el, f) in (("G4_N", 0.01), ("G4_Ni", 0.1), ("G4_Cr", 0.185), ("G4_S", 0.03),
                        ("G4_P", 0.045), ("G4_Mn", 0.02), ("G4_C", 0.08), ("G4_Fe", 0.53))
            AddMaterial(steel, FindOrBuildMaterial(nist, el), f)
        end
        si3n4 = G4Material("Si3N4", density=3.44g/cm3, ncomponents=2)
        AddElement(si3n4, FindOrBuildElement(nist, "Si"), Int32(3))
        AddElement(si3n4, FindOrBuildElement(nist, "N"), Int32(4))
    end
    ringAl = G4Material!GetMaterial("RingAl")
    cryoperm = G4Material!GetMaterial("Cryoperm")
    steel = G4Material!GetMaterial("StainlessSteel")
    si3n4 = G4Material!GetMaterial("Si3N4")

    #---World--------------------------------------------------------------------------------------
    worldLV = G4LogicalVolume(G4Box("World", 3m, 3m, 3m), vacuum, "World")
    worldPV = G4PVPlacement(nothing, G4ThreeVector(), worldLV, "World", nothing, false, 0, checkOverlaps)
    setVis(worldLV, 1, 1, 1, visible=false)

    # Logical volume with a colour, and placements in the world
    function volume(solid, material, name, color...; visible=true)
        lv = G4LogicalVolume(solid, material, name)
        setVis(lv, color..., visible=visible)
        return lv
    end
    place(lv, name, x, y, z; copy=0) = G4PVPlacement(nothing, G4ThreeVector(x, y, z), lv, name, worldLV, false, copy, checkOverlaps)
    place(lv, name, rot::G4RotationMatrix, x, y, z) = G4PVPlacement(G4Transform3D(rot, G4ThreeVector(x, y, z)), lv, name, worldLV, false, 0, checkOverlaps)

    #---TES array----------------------------------------------------------------------------------
    # Each pixel element (a box of one pitch) contains the Bi absorber, the Si3N4 membrane and a piece
    # of the Si grid.
    elementZ = absorberThickness + gridThickness + membraneThickness
    pixelSize = pixelPitch - pixelGap
    detectorLV = volume(hexagon("Detector", elementZ/2, (0, 0), (arrayApothem, arrayApothem)), vacuum, "Detector", 1, 1, 1, visible=false)
    det.arrayPV = G4PVPlacement(nothing, G4ThreeVector(0, 0, -elementZ + 0.0001μm), detectorLV, "Detector", worldLV, false, 0, checkOverlaps)

    elementLV = volume(G4Box("Element", pixelPitch/2, pixelPitch/2, elementZ/2), vacuum, "Element", 1, 1, 1, visible=false)
    absorberLV = volume(G4Box("Bipxl", pixelSize/2, pixelSize/2, absorberThickness/2), Bi, "Bipxl", 1.0, 0.8, 0.0)
    det.absorberPV = G4PVPlacement(nothing, G4ThreeVector(0, 0, elementZ/2 - absorberThickness/2), absorberLV, "Bipxl", elementLV, false, 0, checkOverlaps)
    membraneLV = volume(G4Box("Membrane", pixelSize/2, pixelSize/2, membraneThickness/2), si3n4, "Membrane", 0.5, 0.5, 0.9)
    G4PVPlacement(nothing, G4ThreeVector(0, 0, elementZ/2 - absorberThickness - membraneThickness/2), membraneLV, "Membrane", elementLV, false, 0, checkOverlaps)
    gridBox = G4Box("GridBox", pixelPitch/2, pixelPitch/2, gridThickness/2)
    gridHole = G4Box("GridHole", (pixelPitch - gridBeam)/2, (pixelPitch - gridBeam)/2, gridThickness/2 + 0.5mm)
    gridLV = volume(G4SubtractionSolid("GridPiece", move!(gridBox), move!(gridHole)), Si, "GridPiece", 0.6, 0.6, 0.6)
    G4PVPlacement(nothing, G4ThreeVector(0, 0, elementZ/2 - absorberThickness - membraneThickness - gridThickness/2), gridLV, "GridPiece", elementLV, false, 0, checkOverlaps)

    # The 317 pixels are a parameterised volume. The Julia function `pixelTransform` gives the
    # position of each copy, and the copy number is the pixel number.
    positions = pixelPositions(det)
    pixelTransform(copyNo, pv, positions) = (SetTranslation(pv, G4ThreeVector(positions[copyNo+1]..., 0)); nothing)
    G4PVParameterised("Element", elementLV, detectorLV, kXAxis, length(positions), pixelTransform;
                      data=positions, checkOverlaps=checkOverlaps)

    #---Support wafer around the array-------------------------------------------------------------
    waferZ = -elementZ/2 - absorberThickness - gridThickness/2
    waferLV = volume(hexagon("Wafer", waferThickness/2, (arrayApothem, arrayApothem), (39.4mm, 19.7mm)), Si, "Wafer", 0.4, 0.4, 0.5)
    place(waferLV, "Wafer", 0, 0, waferZ)

    #---Backscattering (BSC) surface: an empty volume just above the absorbers---------------------
    bscHZ = 0.05mm
    bscLV = volume(hexagon("BSC", bscHZ, (0, 0), (arrayApothem + 2mm, arrayApothem + 2mm)), vacuum, "BSC", 1, 1, 1, visible=false)
    place(bscLV, "BSC", 0, 0, waferZ + waferThickness + bscHZ/2)

    #---Anti-coincidence detector (ACD): 4 Si trapezoids under the array, each with an inner part----
    acdThickness, acdGap = 200μm, 50μm
    acdZ = -(0.75mm + absorberThickness/2 + acdThickness/2)
    height = 8.5mm
    wide = height * 1.191                     ## sides of the trapezoids (the CAD values)
    narrow = wide/2
    # The inner part could have higher production cuts to reduce the number of secondaries
    innerACD = G4Trap("InnerACD", acdThickness - 50μm, height - 50μm, wide - 50μm, (wide - 50μm)/2)
    outerACD = G4SubtractionSolid("ACD", move!(G4Trap("ACDBox", acdThickness, height, wide, narrow)), CxxPtr(innerACD))
    innerLV = volume(innerACD, Si, "InnerACD", 0.2, 0.7, 0.2)
    acdLV = volume(outerACD, Si, "ACD", 0.2, 0.8, 0.2)
    det.acdLVs = [CxxPtr(innerLV), CxxPtr(acdLV)]
    ax, ay = (narrow * 1.5 + acdGap)/2, (height + acdGap)/2
    for (k, (sx, sy, rot)) in enumerate(((1, 1, (;)), (-1, -1, (z=π,)), (1, -1, (x=π,)), (-1, 1, (y=π,))))
        place(innerLV, "ACDInner$k", rotation(; rot...), sx * ax, sy * ay, acdZ)
        place(acdLV, "ACD$k", rotation(; rot...), sx * ax, sy * ay, acdZ)
    end

    #---ACD support plate--------------------------------------------------------------------------
    plateLV = volume(hexagon("ACDPlate", 1.75mm, (wide, wide), (43mm, 43mm)), Cu, "ACDPlate", 0.9, 0.5, 0.2)
    place(plateLV, "ACDPlate", 0, 0, -2.25mm)

    #---Cage: columns and walls of Cu supporting the detector (simplified from a CAD model)--------
    cageZ = -36.5027mm
    columnLV = volume(G4Tubs("CageColumn", 0, 3.99mm, 30mm, 0, 2π), Cu, "CageColumn", 0.9, 0.5, 0.2)
    for (k, (x, y)) in enumerate(((45.75, 0), (-45.75, 0), (22.875, 39.621), (22.875, -39.621), (-22.875, -39.621), (-22.875, 39.621)))
        place(columnLV, "CageColumn$k", x*mm, y*mm, cageZ)
    end
    hollowLV = volume(G4Tubs("HollowCageColumn", 1.25mm, 3mm, 30mm, 0, 2π), Cu, "HollowCageColumn", 0.9, 0.5, 0.2)
    for (k, (x, y)) in enumerate(((22.875, 0), (-11.4375, -19.8103311), (-11.4375, 19.810331)))
        place(hollowLV, "HollowCageColumn$k", x*mm, y*mm, cageZ)
    end
    wallLV = volume(G4Box("CageWall", 0.5mm, 16.31mm, 32.5mm), Cu, "CageWall", 0.9, 0.5, 0.2)
    place(wallLV, "CageWall1", 22.875mm, 19.3103311mm, cageZ)
    place(wallLV, "CageWall2", 22.875mm, -19.3103311mm, cageZ)
    place(wallLV, "CageWall3", rotation(z=-60deg), 5.2857373mm, 29.4654967mm, cageZ)
    place(wallLV, "CageWall4", rotation(z=-60deg), -28.1607373mm, 10.1551656mm, cageZ)
    place(wallLV, "CageWall5", rotation(z=60deg), -28.1607373mm, -10.1551656mm, cageZ)
    place(wallLV, "CageWall6", rotation(z=60deg), 5.2857373mm, -29.4654967mm, cageZ)
    miniLV = volume(G4Box("MiniCageWall", 7.9375mm, 0.5mm, 32.5mm), Cu, "MiniCageWall", 0.9, 0.5, 0.2)
    place(miniLV, "MiniCageWall1", 33.8125mm, 0, cageZ)
    place(miniLV, "MiniCageWall2", rotation(z=-60deg), -16.90625mm, 29.282484mm, cageZ)
    place(miniLV, "MiniCageWall3", rotation(z=-120deg), -16.90625mm, -29.282484mm, cageZ)
    extLV = volume(G4Box("ExtCageWall", 0.925mm, 18.875mm, 32.5mm), Cu, "ExtCageWall", 0.9, 0.5, 0.2)
    place(extLV, "ExtCageWall1", rotation(z=-30deg), -35.0724512mm, 20.2490891mm, cageZ)
    place(extLV, "ExtCageWall2", rotation(z=-30deg), 35.0724512mm, -20.2490891mm, cageZ)
    boardLV = volume(G4Box("ExtBoard", 0.25mm, 18.25mm, 32.25mm), Si, "ExtBoard", 0.2, 0.5, 0.2)
    place(boardLV, "ExtBoard1", rotation(z=-30deg), 37.932mm, -21.9mm, -36.253mm)
    place(boardLV, "ExtBoard2", rotation(z=-30deg), -37.932mm, 21.9mm, -36.253mm)

    #---First thermal shield (Cryoperm)------------------------------------------------------------
    for (name, rmin, rmax, hz, z) in (("FirstShieldBottom", 0, 80mm, 0.5mm, -101mm),
                                      ("FirstShieldSide", 79mm, 80mm, 72.5mm, -28mm),
                                      ("FirstShieldTop", 31.85mm, 80mm, 0.5mm, 45mm),
                                      ("FirstShieldTopCyl", 31.85mm, 32.85mm, 37mm, 82.5mm))
        place(volume(G4Tubs(name, rmin, rmax, hz, 0, 2π), cryoperm, name, 0.5, 0.5, 0.7, 0.3), name, 0, 0, z)
    end

    #---Ring: simplified as a tube with 3 flat cuts, made of Al with the average density----------
    ring = G4Tubs("RingTube", 80mm, 97.1mm, 42.5mm, 0, 2π)
    cut = G4Box("RingCut", 38.781347139mm/2, 116.620103593mm/2, 85.1mm/2)
    ring1 = G4SubtractionSolid("Ring1", move!(ring), CxxPtr(cut), CxxPtr{G4RotationMatrix}(C_NULL), G4ThreeVector(-105.055643631mm, 0, 0))
    ring2 = G4SubtractionSolid("Ring2", move!(ring1), CxxPtr(cut), move!(rotation(z=60deg)), G4ThreeVector(52.527821885mm, -90.980856208mm, 0))
    ring3 = G4SubtractionSolid("Ring", move!(ring2), move!(cut), move!(rotation(z=120deg)), G4ThreeVector(52.527821885mm, 90.980856208mm, 0))
    place(volume(ring3, ringAl, "Ring", 0.7, 0.7, 0.7, 0.3), "Ring", 0, 0, -22mm)

    #---Second thermal shield (Al): extruded hexagonal shape with bottom and top plates------------
    toPolygon(points) = (v = StdVector{CLHEP!Hep2Vector}(); for (x, y) in points push!(v, CLHEP!Hep2Vector(x*mm, y*mm)) end; v)
    outline = toPolygon(((58.936, 154.115), (104, 128.098), (104, -128.098), (58.936, -154.115), (-162.936, -26.018), (-162.936, 26.018)))
    inline = toPolygon(((58.936, 149.762), (100.23, 125.921), (100.23, -125.921), (58.936, -149.762), (-159.166, -23.841), (-159.166, 23.841)))
    bottom = G4SubtractionSolid("SecondShieldBottom", move!(G4ExtrudedSolid("SSBottom", outline, 1.325mm)), move!(G4Tubs("SSHole", 0, 19mm, 1.5mm, 0, 2π)))
    place(volume(bottom, Al, "SecondShieldBottom", 0.6, 0.6, 0.8, 0.3), "SecondShieldBottom", 0, 0, -110.178mm)
    side = G4SubtractionSolid("SecondShieldSide", move!(G4ExtrudedSolid("SSOuter", outline, 107.675mm)), move!(G4ExtrudedSolid("SSInner", inline, 108mm)))
    place(volume(side, Al, "SecondShieldSide", 0.6, 0.6, 0.8, 0.3), "SecondShieldSide", 0, 0, -1.178mm)
    top = G4SubtractionSolid("SecondShieldTop", move!(G4ExtrudedSolid("SSTop", outline, 5.435mm)), move!(G4Tubs("SSHole2", 0, 36.85mm, 5.5mm, 0, 2π)))
    place(volume(top, Al, "SecondShieldTop", 0.6, 0.6, 0.8, 0.3), "SecondShieldTop", 0, 0, 111.932mm)
    place(volume(G4Tubs("SecondShieldTopCyl", 36.85mm, 39mm, 6mm, 0, 2π), Al, "SecondShieldTopCyl", 0.6, 0.6, 0.8, 0.3), "SecondShieldTopCyl", 0, 0, 123.367mm)

    #---Third thermal shield (Al): a cylinder closed by two cones and a bottom plate---------------
    sideH, coneH, t = 280mm, 40mm, 0.4mm
    place(volume(G4Tubs("ThirdShieldSide", 174.6mm, 174.6mm + t, sideH/2, 0, 2π), Al, "ThirdShieldSide", 0.5, 0.7, 0.9, 0.2), "ThirdShieldSide", 0, 0, 0)
    place(volume(G4Cons("ThirdShieldTopCone", 174.6mm, 174.6mm + t, 93mm, 93mm + t, coneH/2, 0, 2π), Al, "ThirdShieldTopCone", 0.5, 0.7, 0.9, 0.2),
          "ThirdShieldTopCone", 0, 0, (sideH + coneH)/2)
    place(volume(G4Cons("ThirdShieldBottomCone", 80mm, 80mm + t, 174.6mm, 174.6mm + t, coneH/2, 0, 2π), Al, "ThirdShieldBottomCone", 0.5, 0.7, 0.9, 0.2),
          "ThirdShieldBottomCone", 0, 0, -(sideH + coneH)/2)
    place(volume(G4Tubs("ThirdShieldBottom", 0, 80mm + t, t/2, 0, 2π), Al, "ThirdShieldBottom", 0.5, 0.7, 0.9, 0.2),
          "ThirdShieldBottom", 0, 0, -(sideH + t)/2 - coneH)

    #---External layer of the cryostat (Al)--------------------------------------------------------
    r, midT, midH, sideT, sideH2, coneH2 = 200mm, 8.8mm, 120mm, 6.5mm, 85mm, 75mm
    topConeR, botConeR = 97mm, 120mm
    cryoColor = (0.6, 0.6, 0.6, 0.15)
    place(volume(G4Tubs("CryostatMid", r, r + midT, midH/2, 0, 2π), Al, "CryostatMid", cryoColor...), "CryostatMid", 0, 0, 0)
    place(volume(G4Tubs("CryostatTop", r, r + sideT, sideH2/2, 0, 2π), Al, "CryostatTop", cryoColor...), "CryostatTop", 0, 0, (midH + sideH2)/2)
    place(volume(G4Cons("CryostatTopCone", r, r + sideT, topConeR, topConeR + sideT, coneH2/2, 0, 2π), Al, "CryostatTopCone", cryoColor...),
          "CryostatTopCone", 0, 0, midH/2 + sideH2 + coneH2/2)
    place(volume(G4Tubs("CryostatBottom", r, r + sideT, sideH2/2, 0, 2π), Al, "CryostatBottom", cryoColor...), "CryostatBottom", 0, 0, -(midH + sideH2)/2)
    place(volume(G4Cons("CryostatBottomCone", botConeR, botConeR + sideT, r, r + sideT, coneH2/2, 0, 2π), Al, "CryostatBottomCone", cryoColor...),
          "CryostatBottomCone", 0, 0, -midH/2 - sideH2 - coneH2/2)
    place(volume(G4Tubs("CryostatBottomPlate", 0, botConeR, midT/2, 0, 2π), Al, "CryostatBottomPlate", cryoColor...),
          "CryostatBottomPlate", 0, 0, -midH/2 - sideH2 - coneH2 + midT/2)

    #---Radiation filter: 20 nm of Al on a stainless steel mesh, in an Al carrier------------------
    filterHZ, meshT, carrierT, filterR, filterZ = 10nm, 80μm, 5mm, 64mm, 180mm
    filterLV = volume(G4Tubs("AlFilter", 0, filterR, filterHZ, 0, 2π), Al, "AlFilter", 0.8, 0.8, 0.9, 0.5)
    place(filterLV, "AlFilter", 0, 0, filterZ)
    meshZ = filterZ - filterHZ - meshT/2
    meshLV = volume(G4Tubs("Mesh", 0, filterR + 3.3mm, meshT/2, 0, 2π), vacuum, "Mesh", 1, 1, 1, visible=false)
    place(meshLV, "Mesh", 0, 0, meshZ)
    # Each cell of the mesh is a square frame made of 4 trapezoids
    hx1, hx3, hy, dz = 4827/2*μm, 4880/2*μm, 80/2*μm, 26.5/2*μm
    trapLV = volume(G4Trap("MeshBar", dz, 0, 0, hy, hx1, hx1, 0, hy, hx3, hx3, 0), steel, "MeshBar", 0.3, 0.3, 0.3)
    trapRots = ((x=90deg,), (x=90deg, y=-90deg), (x=270deg,), (x=90deg, y=90deg))
    trapPos = ((0, 1), (1, 0), (0, -1), (-1, 0))
    for i in -13:13, j in -13:13
        cx, cy = 2i * hx3, 2j * hx3
        hypot(cx, cy) < filterR || continue
        for (rot, (sx, sy)) in zip(trapRots, trapPos)
            G4PVPlacement(rotation(; rot...), G4ThreeVector(cx + sx * (hx1 + dz), cy + sy * (hx1 + dz), 0), trapLV, "MeshBar", meshLV, false, 0, checkOverlaps)
        end
    end
    place(volume(G4Tubs("FilterCarrier", filterR, filterR + 3.85mm, carrierT/2, 0, 2π), Al, "FilterCarrier", 0.6, 0.6, 0.6),
          "FilterCarrier", 0, 0, meshZ + meshT/2 + carrierT/2)

    #---Aperture cylinder (Ti, 300 K) with an inner Au coating--------------------------------------
    acTop = midH/2 + sideH2 + coneH2
    acH = acTop - filterZ - carrierT
    acR1, acT = 67.8644mm, 1mm
    place(volume(G4Cons("AC", acR1 - acT, acR1, topConeR - acT, topConeR, acH/2, 0, 2π), Ti, "AC", 0.7, 0.7, 0.8, 0.3), "AC", 0, 0, acTop - acH/2)
    coatingLV = volume(G4Cons("ACCoating", acR1 - acT - 5μm, acR1 - acT, topConeR - acT - 5μm, topConeR - acT, acH/2, 0, 2π), Au, "ACCoating", 1.0, 0.85, 0.0, 0.3)
    place(coatingLV, "ACCoating", 0, 0, acTop - acH/2)

    #---The spacecraft: a 1 cm thick Al sphere------------------------------------------------------
    place(volume(G4Sphere("Spacecraft", 26cm, 27cm, 0, 2π, 0, π), Al, "Spacecraft", 0.8, 0.8, 0.8, 0.1), "Spacecraft", 0, 0, 0)

    #---Inner region: the volumes seen by the detector-----------------------------------------------
    # The physics list can use more precise models in this region (single scattering, atomic
    # deexcitation). The production cuts are the same as in the rest of the geometry.
    region = G4Region(innerRegion)
    for lv in (elementLV, detectorLV, absorberLV, membraneLV, gridLV, waferLV, acdLV, filterLV, coatingLV)
        AddRootLogicalVolume(region, lv)
    end
    cuts = G4ProductionCuts()
    SetProductionCut(cuts, 1mm)
    SetProductionCuts(region, cuts)
    SetEnergyRange(G4ProductionCutsTable!GetProductionCutsTable(), 200eV, 1000GeV)

    return worldPV
end

Geant4.getConstructor(::XrayTESDetector)::Function = xrayTESConstruct
