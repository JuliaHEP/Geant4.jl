using Geant4
using Geant4.SystemOfUnits
using Parameters

#---Optical properties-----------------------------------------------------------------------------
# Energy-dependent properties are given as `NAME => (energies, values)` and constant properties
# as `NAME => value`. This replaces the `/opnovice2/boxProperty`, `/opnovice2/boxConstProperty`,
# `/opnovice2/worldProperty`, ... macro commands of the C++ example.
const PropertyMap = Dict{String, Tuple{Vector{Float64}, Vector{Float64}}}
const ConstPropertyMap = Dict{String, Float64}

function buildMPT(props::PropertyMap, cprops::ConstPropertyMap)
    mpt = G4MaterialPropertiesTable()
    for (name, (energies, values)) in props
        AddProperty(mpt, name, StdVector(energies), StdVector(values))
    end
    for (name, value) in cprops
        AddConstProperty(mpt, name, value)
    end
    return mpt
end

# Linear interpolation of an energy-dependent property (e.g. RINDEX at the primary energy)
function propertyValue(props::PropertyMap, name::String, energy::Float64)
    energies, values = props[name]
    energy <= energies[1] && return values[1]
    energy >= energies[end] && return values[end]
    i = searchsortedlast(energies, energy)
    f = (energy - energies[i]) / (energies[i+1] - energies[i])
    return values[i] + f * (values[i+1] - values[i])
end

#---Detector parameters----------------------------------------------------------------------------
# A cube "tank" of side 2 m inside a "world" cube of side 20 m. The optical properties of both
# materials, and of the surface between them, are parameters of the detector.
@with_kw mutable struct OpDetector <: G4JLDetector
    worldHalfSize::Float64 = 10m
    tankHalfSize::Float64 = 1m
    worldMaterial::String = "G4_AIR"
    tankMaterial::String = "G4_WATER"
    tankProperties::PropertyMap = PropertyMap()
    tankConstProperties::ConstPropertyMap = ConstPropertyMap()
    worldProperties::PropertyMap = PropertyMap()
    worldConstProperties::ConstPropertyMap = ConstPropertyMap()
    surfaceProperties::PropertyMap = PropertyMap()
    surfaceConstProperties::ConstPropertyMap = ConstPropertyMap()
    surfaceType::G4SurfaceType = dielectric_dielectric
    surfaceModel::G4OpticalSurfaceModel = unified
    surfaceFinish::G4OpticalSurfaceFinish = ground
    surfaceSigmaAlpha::Float64 = 0.
    surfacePolish::Float64 = 1.
end

#---Detector construction--------------------------------------------------------------------------
function opConstruct(det::OpDetector)::CxxPtr{G4VPhysicalVolume}
    (; worldHalfSize, tankHalfSize) = det
    nist = G4NistManager!Instance()

    #---Materials with their optical properties----------------------------------------------------
    worldMat = FindOrBuildMaterial(nist, det.worldMaterial)
    tankMat = FindOrBuildMaterial(nist, det.tankMaterial)
    SetMaterialPropertiesTable(worldMat, move!(buildMPT(det.worldProperties, det.worldConstProperties)))
    SetMaterialPropertiesTable(tankMat, move!(buildMPT(det.tankProperties, det.tankConstProperties)))

    #---Volumes------------------------------------------------------------------------------------
    worldBox = G4Box("World", worldHalfSize, worldHalfSize, worldHalfSize)
    worldLV = G4LogicalVolume(worldBox, worldMat, "World")
    worldPV = G4PVPlacement(nothing, G4ThreeVector(), worldLV, "World", nothing, false, 0)

    tankBox = G4Box("Tank", tankHalfSize, tankHalfSize, tankHalfSize)
    tankLV = G4LogicalVolume(tankBox, tankMat, "Tank")
    tankPV = G4PVPlacement(nothing, G4ThreeVector(), tankLV, "Tank", worldLV, false, 0)

    #---Surface between the tank and the world-----------------------------------------------------
    surface = G4OpticalSurface("Surface")
    SetType(surface, det.surfaceType)
    SetModel(surface, det.surfaceModel)
    SetFinish(surface, det.surfaceFinish)
    SetSigmaAlpha(surface, det.surfaceSigmaAlpha)
    SetPolish(surface, det.surfacePolish)
    SetMaterialPropertiesTable(surface, move!(buildMPT(det.surfaceProperties, det.surfaceConstProperties)))
    G4LogicalBorderSurface("Surface", CxxPtr(tankPV), CxxPtr(worldPV), CxxPtr(surface))
    DumpInfo(surface)

    return worldPV
end

Geant4.getConstructor(::OpDetector)::Function = opConstruct
