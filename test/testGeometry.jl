include(joinpath(@__DIR__, "B1Detector.jl"))

@testset "G4Geometry" begin
    # Vectors
    m1 = G4ThreeVector(1, 2, 3)
    m2 = G4ThreeVector(10, 20, 30)

    @test x(m1) == 1.
    @test y(m1) == 2.
    @test z(m1) == 3.

    @test m1 + m2 == G4ThreeVector(11,22,33)
    @test mag(m1) == √14
    @test dot(m2, m2) == mag2(m2)

    # Transformations
    r1 = G4RotationMatrix(0,0,0)  # unit rotation
    @test r1 * m1 == m1

    rotateX(r1, π/3)
    rotateY(r1, π/4)
    rotateZ(r1, π/6)

    p0 = G4ThreeVector(1,1,1)
    v0 = G4ThreeVector(1,1,1)
  
    t1 = G4Transform3D(r1, m1)
    @test getRotation(t1) * p0 + getTranslation(t1) == r1 * p0 + m1

    #---Solids-------------------------------------------------------------------------------------

    #---Geometries---------------------------------------------------------------------------------

    world = constructB1Detector(nothing)
    @test world isa CxxPtr{G4VPhysicalVolume}
    lworld = world |> GetLogicalVolume
    @test lworld |> GetName |> String == "World"
    # Basic hirarchy navigation
    @test lworld |> GetNoDaughters == 1
    daughter = GetDaughter(lworld, 0)
    @test daughter |> GetName |> String == "Envelope"
    @test daughter isa CxxPtr{G4VPhysicalVolume}

    # GetVolume by its name
    envelope = GetVolume("Envelope")
    @test  envelope == daughter |> GetLogicalVolume
    @test envelope |> GetName |> String == "Envelope"
    @test envelope |> GetNoDaughters == 2
    
    # Get Solid and up-cast
    solid = envelope |> GetSolid
    @test solid isa CxxPtr{G4VSolid}
    @test solid |> GetEntityType |> String  == "G4Box"
    box = CxxRef{getproperty(Main,Symbol(GetEntityType(solid)))}(solid)  # upcasting to the concrete G4VSolid
    @test box isa CxxRef{G4Box}
    @test GetXHalfLength(box) == 100.

    #---Parameterised volumes----------------------------------------------------------------------
    nist = G4NistManager!Instance()
    air = FindOrBuildMaterial(nist, "G4_AIR")
    motherLV = G4LogicalVolume(G4Box("ParamMother", 50cm, 10cm, 10cm), air, "ParamMother")
    cellLV = G4LogicalVolume(G4Box("ParamCell", 4cm, 4cm, 4cm), air, "ParamCell")
    xpos = [-40cm, -20cm, 0., 20cm, 40cm]
    transform(copyNo, pv, xpos) = (SetTranslation(pv, G4ThreeVector(xpos[copyNo+1], 0, 0)); nothing)
    ppv = G4PVParameterised("ParamCell", cellLV, motherLV, kXAxis, length(xpos), transform; data=xpos)
    @test ppv isa G4PVParameterised
    @test IsParameterised(ppv)
    @test GetMultiplicity(ppv) == 5
    param = GetParameterisation(ppv)
    for i in (0, 3)
        ComputeTransformation(param, i, CxxPtr(ppv))
        @test x(GetTranslation(ppv)) == xpos[i+1]
    end

    #---Regions and production cuts----------------------------------------------------------------
    region = G4Region("TestRegion")
    AddRootLogicalVolume(region, cellLV)
    @test GetNumberOfRootVolumes(region) == 1
    cuts = G4ProductionCuts()
    SetProductionCut(cuts, 2mm)
    SetProductionCuts(region, cuts)
    @test GetProductionCut(GetProductionCuts(region), "gamma") == 2mm
    @test GetRegion(G4RegionStore!GetInstance(), "TestRegion") == CxxPtr(region)

    #---EM parameters------------------------------------------------------------------------------
    em = G4EmParameters!Instance()
    SetFluo(em, true)
    @test Fluo(em)
    SetFluo(em, false)
    @test !Fluo(em)

    #---Birks constant of a scintillator-----------------------------------------------------------
    polystyrene = FindOrBuildMaterial(nist, "G4_POLYSTYRENE")
    ionisation = GetIonisation(polystyrene)
    SetBirksConstant(ionisation, 0.126mm/MeV)
    @test GetBirksConstant(ionisation) ≈ 0.126mm/MeV
end