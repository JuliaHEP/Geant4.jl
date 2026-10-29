#--------------------------------------------------------------------------------------------------
# 
#--------------------------------------------------------------------------------------------------
mutable struct ScintDetector <: G4JLDetector
    # main input parameters
    const worldSize::Float64
    const doTeflon::Bool
    const doAluminum::Bool
    const crys_size::Float64
    const si_side::Float64
    const si_thick::Float64
    const tef_thick::Float64
    const al_thick::Float64
    const air_gap::Float64
    const checkOverlaps::Bool
    # calculated variables
    vacMat::CxxPtr{G4Material}
    cebr3Mat::CxxPtr{G4Material}
    qzMat::CxxPtr{G4Material}
    alMat::CxxPtr{G4Material}
    tefMat::CxxPtr{G4Material}
    siMat::CxxPtr{G4Material}
    beMat::CxxPtr{G4Material}
    # constructor with defaults values for parameters
    function ScintDetector(; worldSize = 5cm,
                             doTeflon = true,
                             doAluminum = true,
                             crys_size = 2cm,
                             si_side = 1cm,
                             si_thick = 2mm,
                             tef_thick = 1mm,
                             al_thick = 1mm,
                             air_gap = 10mm,
                             checkOverlaps = true )
        self = new(worldSize, doTeflon, doAluminum, crys_size, si_side, si_thick, tef_thick, al_thick, air_gap, checkOverlaps)
        return self
    end
end

function defineMaterials!(det::ScintDetector)
    # to avoid warnings of redefinitions
    G4Material!GetMaterial("vacumm", false) != C_NULL && return

    nist = G4NistManager!Instance()

    #---vacuum------------------------------------------------------------------------------------- 
    vacMat = G4Material("vacumm", z=1., a=1.01g/mole, density=universe_mean_density, state=kStateGas, 
                        temperature=VACUUM_TEMPERATURE, pressure=VACUUM_PRESSURE)
    vacPt = G4MaterialPropertiesTable()
    AddProperty(vacPt, "RINDEX", CEBR3_REFR_IDX_ENERGIES, StdVector(fill(1., length(CEBR3_REFR_IDX_ENERGIES))), useSpline)
    SetMaterialPropertiesTable(vacMat, move!(vacPt))
    det.vacMat = CxxPtr(vacMat)

    #---cebr3--------------------------------------------------------------------------------------
    ce = FindOrBuildElement(nist, "Ce")
    br = FindOrBuildElement(nist, "Br")
    cebr3 = G4Material("cebr3", density=CEBR3_DENSITY, ncomponents=2, state=kStateSolid, temperature=SATELLITE_TEMP)
    AddElement(cebr3, br, BR_MASS_FRAC)
    AddElement(cebr3, ce, CE_MASS_FRAC)

    #  optical parameters
    opp = G4OpticalParameters!Instance()
    SetScintFiniteRiseTime(opp, false)

    scintPt = G4MaterialPropertiesTable()

    AddConstProperty(scintPt, "SCINTILLATIONYIELD", CEBR3_SCINT_YIELD)
    AddProperty(scintPt, "RINDEX", CEBR3_REFR_IDX_ENERGIES, CEBR3_REFR_IDXS, useSpline)
    AddProperty(scintPt, "SCINTILLATIONCOMPONENT1", CEBR3_SCINT_OPTICAL_ENERGIES, CEBR3_SCINT_OPTICAL_INTENSITIES, useSpline)
    AddConstProperty(scintPt, "SCINTILLATIONTIMECONSTANT1", CEBR3_DECAY_TIME_CONSTANT)

    # # of photons emitted = RESOLUTION_SCALE * sqrt(mean # of photons)
    AddConstProperty(scintPt, "RESOLUTIONSCALE", CEBR3_SCINT_RESLN_SCALE)
    AddProperty(scintPt, "ABSLENGTH", CEBR3_ABS_LEN_ENERGIES, CEBR3_ABS_LEN, useSpline)
    # skip optical Rayleigh scattering (not important)
    # skip Mie scattering (doesn't apply)
    SetMaterialPropertiesTable(cebr3, move!(scintPt))
    det.cebr3Mat = CxxPtr(cebr3)

    #---quartz-------------------------------------------------------------------------------------
    qz = FindOrBuildMaterial(nist, "G4_SILICON_DIOXIDE")
    qzPt = G4MaterialPropertiesTable()
    AddProperty(qzPt, "RINDEX", QZ_REFR_IDX_ENERGIES, QZ_REFR_IDXS )
    # do not add real/imag refractive indices to materials. they areo nly for surface indices.
    # qzPt->AddProperty(kREFR_IDX_REAL, QZ_REFR_IDX_ENERGIES, QZ_REFR_IDXS);
    # qzPt->AddProperty(kREFR_IDX_IMAG, QZ_REFR_IDX_ENERGIES, std::vector<G4double>(QZ_REFR_IDXS.size(), 0.0));
    SetMaterialPropertiesTable(qz, move!(qzPt))
    det.qzMat = qz

    #---teflon--------------------------------------------------------------------------------------
    teflon = FindOrBuildMaterial(nist, "G4_TEFLON")
    tefPt = G4MaterialPropertiesTable()
    AddProperty(tefPt, "RINDEX", TEFLON_REFR_IDX_ENERGIES, TEFLON_REFR_IDXS, useSpline)
    AddProperty(tefPt, "REFLECTIVITY", TEFLON_REFR_IDX_ENERGIES, TEFLON_REFLECTIVITY, useSpline)
    SetMaterialPropertiesTable(teflon, move!(tefPt))
    det.tefMat = CxxPtr(teflon)

    #---Silicon------------------------------------------------------------------------------------
    si = FindOrBuildMaterial(nist, "G4_Si")
    simPt = G4MaterialPropertiesTable()
    # set to one and apply detection in post-processing (?)
    AddProperty(simPt, "EFFICIENCY", SI_DET_EFF_ENERGIES, SI_DET_EFF, useSpline)
    refl = StdVector(fill(0., length(SI_BROADCOM_NUMBERS)))
    AddProperty(simPt, "REFLECTIVITY", SI_DET_EFF_ENERGIES, refl, useSpline)
    AddProperty(simPt, "TRANSMITTANCE", SI_DET_EFF_ENERGIES, SI_TRANSMITTANCE, useSpline)
    AddProperty(simPt, "RINDEX", SI_REFR_IDX_ENERGY, SI_REFR_IDX_REAL, useSpline)
    AddProperty(simPt, "REALRINDEX", SI_REFR_IDX_ENERGY, SI_REFR_IDX_REAL, useSpline)
    AddProperty(simPt, "IMAGINARYRINDEX", SI_REFR_IDX_ENERGY, SI_REFR_IDX_IMAG, useSpline)
    SetMaterialPropertiesTable(si, move!(simPt))
    det.siMat = si

    #---aluminum-----------------------------------------------------------------------------------
    alElt = FindOrBuildElement(nist, "Al")
    alElt == C_NULL &&  error("Nist manager gave nullptr for aluminum")

    al = G4Material("aluminum", density=2.712g/cm3, ncomponents=1, state=kStateSolid, temperature=SATELLITE_TEMP)
    AddElement(al, alElt, 1.0)
    alPt = G4MaterialPropertiesTable()
    # DO NOT ADD JUST RINDEX!!!!!!!!!!!!!!!!!!!1
    # IT WILL CAUSE PROGRAM TO CRASH IF YOU PUT A SKIN AROUND THE MATERIAL
    # AddProperty(alPt, "RINDEX", AL_REFR_IDX_ENERGIES, AL_REFR_IDX_REAL)
    AddProperty(alPt, "REALRINDEX", AL_REFR_IDX_ENERGIES, AL_REFR_IDX_REAL)
    AddProperty(alPt, "IMAGINARYRINDEX", AL_REFR_IDX_ENERGIES, AL_REFR_IDX_IMAG)
    SetMaterialPropertiesTable(al, move!(alPt))
    det.alMat = CxxPtr(al)

    #---beryllium-----------------------------------------------------------------------------------
    beElt = FindOrBuildElement(nist, "Be")
    be = G4Material("beryllium", density=BE_DENSITY, ncomponents=1, state=kStateSolid, temperature=SATELLITE_TEMP)
    AddElement(be, beElt, 1)
    bePt = G4MaterialPropertiesTable()
    AddProperty(bePt, "RINDEX", BE_REFR_IDX_ENERGIES, BE_REFR_IDX_REAL)
    AddProperty(bePt, "REALRINDEX", BE_REFR_IDX_ENERGIES, BE_REFR_IDX_REAL)
    AddProperty(bePt, "IMAGINARYRINDEX", BE_REFR_IDX_ENERGIES, BE_REFR_IDX_IMAG)
    SetMaterialPropertiesTable(be, move!(bePt))
    det.beMat = CxxPtr(be)
    
    return
end

function scintConstruct(det::ScintDetector)::CxxPtr{G4VPhysicalVolume}
    (; worldSize, doTeflon, doAluminum, crys_size, si_side, si_thick, tef_thick, al_thick, air_gap, checkOverlaps) = det
 
    #---Materials----------------------------------------------------------------------------------
    defineMaterials!(det)

    #---World--------------------------------------------------------------------------------------
    worldBox = G4Box("World", 0.5*worldSize, 0.5*worldSize, 0.5*worldSize)        
    worldLogVol = G4LogicalVolume(worldBox, det.vacMat, "World")
    worldVis = G4VisAttributes(true, G4Colour(1, 1, 1, 0.05))
    SetVisAttributes(worldLogVol, worldVis)
    worldPlacement = G4PVPlacement(nothing, G4ThreeVector(), worldLogVol, "World", nothing, false, 0, checkOverlaps)

    #---cryst--------------------------------------------------------------------------------------
    crystBox = G4Box("cebr3_box", crys_size/2, crys_size/2, crys_size/2)
    crystLogVol = G4LogicalVolume(crystBox, det.cebr3Mat, "cebr3_log")
    crystVis = G4VisAttributes(true, G4Colour(0.35, 0.5, 0.92, 0.8))
    SetVisAttributes(crystLogVol, crystVis)
    crystPlacement = G4PVPlacement(nothing, G4ThreeVector(), crystLogVol, "cebr3_phys", worldLogVol, false, 0, checkOverlaps)

    surf = G4OpticalSurface("cebr3_optical_edge")
    # See G4 documentation on UNIFIED model
    SetType(surf, dielectric_LUTDAVIS)
    SetModel(surf, DAVIS)
    SetFinish(surf, Rough_LUT);
    G4LogicalBorderSurface("cebr3_logical_border_surf", CxxPtr(crystPlacement), CxxPtr(worldPlacement), CxxPtr(surf))

    #---teflon-------------------------------------------------------------------------------------
    if doTeflon
        precutHalfThick = (air_gap + tef_thick + crys_size)/2
        preCutPtfeBox = G4Box("precut_ptfe", precutHalfThick, precutHalfThick, precutHalfThick)
        addAirGapHalfXyz = 0.5 * (crys_size + air_gap)

        crystPlusAirGap = G4Box("", addAirGapHalfXyz, addAirGapHalfXyz, addAirGapHalfXyz)
        translateSubtract = G4ThreeVector(0, 0, 0)
        slicedPtfe = G4SubtractionSolid("sliced_ptfe", move!(preCutPtfeBox), move!(crystPlusAirGap), CxxPtr{G4RotationMatrix}(C_NULL), translateSubtract)
        translateSubtract = G4ThreeVector(0, 0, 1.8*cm)
        cutCap = G4Box("", precutHalfThick + 5*mm, precutHalfThick + 5*mm, precutHalfThick)
        slicedPtfeOpen = G4SubtractionSolid("sliced_ptfe_open", move!(slicedPtfe), move!(cutCap), CxxPtr{G4RotationMatrix}(C_NULL), translateSubtract)
        ptfeLogVol = G4LogicalVolume(slicedPtfeOpen, det.tefMat, "ptfe_log")
        tefVis = G4VisAttributes(true, G4Colour(0, 1, 0, 0.1))
        SetVisAttributes(ptfeLogVol, tefVis)

        # attachTeflonOpticalSurf
        tefSuf = G4OpticalSurface("teflon_optical_surf")
        SetType(tefSuf, dielectric_dielectric)
        SetModel(tefSuf, unified)
        SetFinish(tefSuf, groundfrontpainted)
        SetSigmaAlpha(tefSuf, 0.)
        SetMaterialPropertiesTable(tefSuf, GetMaterialPropertiesTable(det.tefMat))
        G4LogicalSkinSurface("teflon_skin_surf", CxxPtr(ptfeLogVol), CxxPtr(tefSuf))
        
        G4PVPlacement(nothing, G4ThreeVector(), ptfeLogVol, "ptfe_phys", worldLogVol, false, 0, checkOverlaps)
    end

    #---aluminum-------------------------------------------------------------------------------------
    if doAluminum
        sliceCapThick = 0.5 * (tef_thick + crys_size + al_thick + 2*air_gap) + 5*mm
        precutHalfThick = sliceCapThick - 5*mm
        sliceOutHalfThick = precutHalfThick - 0.5 * al_thick
      
        precut = G4Box("", precutHalfThick, precutHalfThick, precutHalfThick)
        cutThisOut = G4Box("", sliceOutHalfThick, sliceOutHalfThick, sliceOutHalfThick)
        cutOffEnd = G4Box("", sliceCapThick, sliceCapThick, 6*mm)
        hollow = G4SubtractionSolid("hollow_al", move!(precut), move!(cutThisOut), CxxPtr{G4RotationMatrix}(C_NULL), G4ThreeVector())
        translateSubtract = G4ThreeVector(0, 0, sliceCapThick)
        open = G4SubtractionSolid("hollow_open_al", move!(hollow), move!(cutOffEnd), CxxPtr{G4RotationMatrix}(C_NULL), translateSubtract)
        
        alLogVol = G4LogicalVolume(open, det.alMat, "al_log")
        alVis = G4VisAttributes(true, G4Colour(1, 0., 0., 0.1))
        SetVisAttributes(alLogVol, alVis)

        # attachAlOpticalSurface(alLogVol)
        alSurf = G4OpticalSurface("al_optical_surf")
        SetModel(alSurf, unified)
        SetType(alSurf, dielectric_metal)
        SetFinish(alSurf, polished)
        SetMaterialPropertiesTable(alSurf, GetMaterialPropertiesTable(det.alMat))
        G4LogicalSkinSurface("al_skin_surf", CxxPtr(alLogVol), CxxPtr(alSurf))
        G4PVPlacement(nothing, G4ThreeVector(), alLogVol, "al_phys", worldLogVol, false, 0, checkOverlaps)
    end

    #---sillicon-----------------------------------------------------------------------------------
    siBox = G4Box("si_box", si_side/2, si_side/2, si_thick/2)
    siLogVol = G4LogicalVolume(siBox, det.siMat, "si_log")
    siVis = G4VisAttributes(true, G4Colour(0, 0, 1, 0.5))
    SetVisAttributes(siLogVol, siVis)
  
    translate = G4ThreeVector(0, 0, crys_size/2 + si_thick/2)
    G4PVPlacement(nothing, translate, siLogVol, "si_phys", worldLogVol, false, 0, checkOverlaps)

    siSurf = G4OpticalSurface("si_surf")
    SetModel(siSurf, unified)
    SetFinish(siSurf, polished)
    SetType(siSurf, dielectric_dielectric)
    SetMaterialPropertiesTable(siSurf, GetMaterialPropertiesTable(det.siMat))
    G4LogicalSkinSurface("si_skin", CxxPtr(siLogVol), CxxPtr(siSurf))
  
    #  return the world
    return worldPlacement
end

Geant4.getConstructor(::ScintDetector)::Function = scintConstruct