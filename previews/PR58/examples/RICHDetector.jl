using Geant4
using Geant4.SystemOfUnits
using Geant4.PhysicalConstants
using Parameters

#---Optical properties-----------------------------------------------------------------------------
# Photon energies between 1.5 eV (827 nm) and 4.5 eV (276 nm)
const photonEnergies = collect(range(1.5eV, 4.5eV, length=31))
wavelength(E) = h_Planck * c_light / E

# Refractive index of C4F10 as a function of the photon energy (Sellmeier formula with one pole)
c4f10RIndex(E) = 1 + 0.25324e-6 / (1/73.7^2 - 1/(wavelength(E)/nm)^2)

# Aerogel scatters the light (Rayleigh) with a scattering length of λ⁴/C, where C is the clarity
const aerogelClarity = 0.0055μm^4/cm
aerogelRayleigh(E) = wavelength(E)^4 / aerogelClarity

# Quantum efficiency of the photodetectors (bialkali photocathode)
const qeEnergies = [1.5eV, 1.8eV, 2.1eV, 2.4eV, 2.7eV, 3.0eV, 3.3eV, 3.6eV, 3.9eV, 4.2eV, 4.5eV]
const qeValues   = [0.0,   0.01,  0.05,  0.12,  0.20,  0.25,  0.25,  0.23,  0.20,  0.15,  0.10]
function quantumEfficiency(E)
    (E <= qeEnergies[1] || E >= qeEnergies[end]) && return 0.
    i = searchsortedlast(qeEnergies, E)
    f = (E - qeEnergies[i]) / (qeEnergies[i+1] - qeEnergies[i])
    return qeValues[i] + f * (qeValues[i+1] - qeValues[i])
end

#---Detector parameters----------------------------------------------------------------------------
# A box filled with C4F10 gas, from z = 1 m to 2.1 m, contains the aerogel tile at the entrance,
# two spherical mirrors (top and bottom) at z ≈ 2 m and two planes of photodetectors at
# z = 1 m, outside the acceptance. The centre of curvature of each mirror is displaced vertically
# so that the light is focused on the photodetector plane of the same half (y > 0 or y < 0).
@with_kw mutable struct RICHDetector <: G4JLDetector
    worldHalfSize::Float64 = 2.5m
    vesselHalfX::Float64 = 1.0m
    vesselHalfY::Float64 = 1.5m
    vesselZ::Tuple{Float64,Float64} = (1m, 2.1m)         ## z range of the gas vessel
    beamPipeRadius::Float64 = 3cm
    beamPipeThickness::Float64 = 1mm
    aerogelZ::Float64 = 1m                              ## front face of the aerogel
    aerogelThickness::Float64 = 5cm
    aerogelHalfSize::Float64 = 35cm
    aerogelRIndex::Float64 = 1.03
    mirrorRadius::Float64 = 2m
    mirrorThickness::Float64 = 5mm
    mirrorReflectivity::Float64 = 0.9
    detectorZ::Float64 = 1.01m                          ## photodetector surface
    detectorY::Tuple{Float64,Float64} = (45cm, 135cm)   ## |y| range of the photodetector planes
    detectorHalfX::Float64 = 70cm
    detectorThickness::Float64 = 1cm
    mirrorCentreY::Float64 = 75cm                       ## |y| of the centre of curvature of the mirrors
    checkOverlaps::Bool = false
end

# Centre of curvature of the top (+1) or bottom (-1) mirror. The focal surface (a sphere of radius
# R/2 around the centre of curvature) touches the photodetector plane.
mirrorCentre(det::RICHDetector, side) = (0., side * det.mirrorCentreY, det.detectorZ - det.mirrorRadius/2)

# Visualization attributes (colour and transparency) of a logical volume
setVis(lv, r, g, b, a=1.; visible=true) = SetVisAttributes(lv, G4VisAttributes(visible, G4Colour(r, g, b, a)))

function buildMPT(props::Pair...)
    mpt = G4MaterialPropertiesTable()
    for (name, f) in props
        AddProperty(mpt, name, StdVector(photonEnergies), StdVector(f.(photonEnergies)))
    end
    return mpt
end

#---Detector construction--------------------------------------------------------------------------
function richConstruct(det::RICHDetector)::CxxPtr{G4VPhysicalVolume}
    (; worldHalfSize, vesselHalfX, vesselHalfY, vesselZ, beamPipeRadius, beamPipeThickness,
       aerogelZ, aerogelThickness, aerogelHalfSize, mirrorRadius, mirrorThickness,
       detectorZ, detectorY, detectorHalfX, detectorThickness, checkOverlaps) = det
    nist = G4NistManager!Instance()

    #---Materials with their optical properties----------------------------------------------------
    air = FindOrBuildMaterial(nist, "G4_AIR")
    vacuum = FindOrBuildMaterial(nist, "G4_Galactic")
    beryllium = FindOrBuildMaterial(nist, "G4_Be")
    glass = FindOrBuildMaterial(nist, "G4_GLASS_PLATE")
    if G4Material!GetMaterial("C4F10", false) == C_NULL
        c4f10 = G4Material("C4F10", density=10.39mg/cm3, ncomponents=2, state=kStateGas)
        AddElement(c4f10, FindOrBuildElement(nist, "C"), Int32(4))
        AddElement(c4f10, FindOrBuildElement(nist, "F"), Int32(10))
        aerogel = G4Material("Aerogel", density=0.15g/cm3, ncomponents=2, state=kStateSolid)
        AddElement(aerogel, FindOrBuildElement(nist, "Si"), Int32(1))
        AddElement(aerogel, FindOrBuildElement(nist, "O"), Int32(2))
    end
    c4f10 = G4Material!GetMaterial("C4F10")
    aerogel = G4Material!GetMaterial("Aerogel")
    SetMaterialPropertiesTable(c4f10, move!(buildMPT("RINDEX" => c4f10RIndex, "ABSLENGTH" => E -> 100m)))
    SetMaterialPropertiesTable(aerogel, move!(buildMPT("RINDEX" => E -> det.aerogelRIndex,
                                                       "ABSLENGTH" => E -> 1m,
                                                       "RAYLEIGH" => aerogelRayleigh)))

    #---World and gas vessel-----------------------------------------------------------------------
    worldLV = G4LogicalVolume(G4Box("World", worldHalfSize, worldHalfSize, worldHalfSize), air, "World")
    worldPV = G4PVPlacement(nothing, G4ThreeVector(), worldLV, "World", nothing, false, 0, checkOverlaps)
    setVis(worldLV, 1, 1, 1, visible=false)

    vesselHalfZ = (vesselZ[2] - vesselZ[1])/2
    vesselZc = (vesselZ[2] + vesselZ[1])/2
    vesselLV = G4LogicalVolume(G4Box("Vessel", vesselHalfX, vesselHalfY, vesselHalfZ), c4f10, "Vessel")
    G4PVPlacement(nothing, G4ThreeVector(0, 0, vesselZc), vesselLV, "Vessel", worldLV, false, 0, checkOverlaps)
    setVis(vesselLV, 0.6, 0.9, 1.0, 0.1, visible=false)
    toVessel(x, y, z) = G4ThreeVector(x, y, z - vesselZc)      ## global → vessel coordinates

    #---Beam pipe----------------------------------------------------------------------------------
    pipeLV = G4LogicalVolume(G4Tubs("BeamPipe", 0, beamPipeRadius + beamPipeThickness, vesselHalfZ, 0, 2π), beryllium, "BeamPipe")
    G4PVPlacement(nothing, G4ThreeVector(), pipeLV, "BeamPipe", vesselLV, false, 0, checkOverlaps)
    beamLV = G4LogicalVolume(G4Tubs("BeamVacuum", 0, beamPipeRadius, vesselHalfZ, 0, 2π), vacuum, "BeamVacuum")
    G4PVPlacement(nothing, G4ThreeVector(), beamLV, "BeamVacuum", pipeLV, false, 0, checkOverlaps)
    setVis(pipeLV, 0.5, 0.5, 0.5, 0.5)
    setVis(beamLV, 1, 1, 1, visible=true)

    #---Aerogel: a square tile with a hole for the beam pipe-------------------------------------
    hole = G4Tubs("AerogelHole", 0, beamPipeRadius + beamPipeThickness + 1mm, aerogelThickness, 0, 2π)
    tile = G4Box("AerogelTile", aerogelHalfSize, aerogelHalfSize, aerogelThickness/2)
    aerogelS = G4SubtractionSolid("Aerogel", move!(tile), move!(hole))
    aerogelLV = G4LogicalVolume(aerogelS, aerogel, "Aerogel")
    setVis(aerogelLV, 1.0, 0.9, 0.2, 0.8)
    G4PVPlacement(nothing, toVessel(0, 0, aerogelZ + aerogelThickness/2), aerogelLV, "Aerogel", vesselLV, false, 0, checkOverlaps)

    #---Mirrors: spherical shells cut by a box to the top (or bottom) half of the vessel----------
    mirrorReflector = G4OpticalSurface("MirrorSurface")
    SetType(mirrorReflector, dielectric_metal)
    SetModel(mirrorReflector, unified)
    SetFinish(mirrorReflector, polished)
    SetMaterialPropertiesTable(mirrorReflector, move!(buildMPT("REFLECTIVITY" => E -> det.mirrorReflectivity)))
    yGap = beamPipeRadius + beamPipeThickness + 5mm
    zmin = vesselZ[1] + vesselHalfZ                        ## the mirrors are in the back half of the vessel
    for (side, name) in ((1, "MirrorTop"), (-1, "MirrorBottom"))
        cx, cy, cz = mirrorCentre(det, side)
        ## cut box in global coordinates and its position relative to the centre of curvature
        bhx, bhy, bhz = vesselHalfX - 1mm, (vesselHalfY - 1mm - yGap)/2, (vesselZ[2] - 1mm - zmin)/2
        bx, by, bz = 0., side * (yGap + bhy), zmin + bhz
        shell = G4Sphere(name * "Shell", mirrorRadius, mirrorRadius + mirrorThickness, 0, 2π, 0, π/2)
        cut = G4Box(name * "Cut", bhx, bhy, bhz)
        mirrorS = G4IntersectionSolid(name, move!(shell), move!(cut),
                                      G4Transform3D(G4RotationMatrix(), G4ThreeVector(bx - cx, by - cy, bz - cz)))
        mirrorLV = G4LogicalVolume(mirrorS, glass, name)
        setVis(mirrorLV, 0.8, 0.8, 0.8, 0.5)
        G4PVPlacement(nothing, toVessel(cx, cy, cz), mirrorLV, name, vesselLV, false, 0, checkOverlaps)
        G4LogicalSkinSurface(name * "Surface", CxxPtr(mirrorLV), CxxPtr(mirrorReflector))
    end

    #---Photodetector planes, facing the mirrors---------------------------------------------------
    dhy = (detectorY[2] - detectorY[1])/2
    detS = G4Box("Photodetector", detectorHalfX, dhy, detectorThickness/2)
    detLV = G4LogicalVolume(detS, glass, "Photodetector")
    setVis(detLV, 0.5, 0.4, 0.4)
    for (side, name) in ((1, "PhotodetectorTop"), (-1, "PhotodetectorBottom"))
        G4PVPlacement(nothing, toVessel(0, side * (detectorY[1] + dhy), detectorZ - detectorThickness/2),
                      detLV, name, vesselLV, false, side > 0 ? 0 : 1, checkOverlaps)
    end

    return worldPV
end

Geant4.getConstructor(::RICHDetector)::Function = richConstruct
