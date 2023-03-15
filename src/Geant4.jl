module Geant4
    include(joinpath(@__DIR__, "../gen/jl/Geant4-export.jl"))
    using CxxWrap
    using Geant4_jll

    @wrapmodule(joinpath(@__DIR__, "../deps/build/lib", "libGeant4Wrap"))
    function __init__()
        @initcxx
        #---Call Wrapper init--------------------------------------------------
        G4JL_init()
        #---Setup [data] environment-------------------------------------------
        GEANT4_DATA_DIR = get(ENV, "GEANT4_DATA_DIR", Geant4_jll.data_dir)
        for line in readlines(joinpath(Geant4_jll.artifact_dir, "bin/geant4.sh"))
            m = match(r"export[ ]+(G4.*)=.*/(.*)$", line)
            if !isnothing(m)
                G4JL_setenv(String(m[1]), joinpath(GEANT4_DATA_DIR, m[2]))
            end
        end
    end

    # Typedef hack! 
    const G4RotationMatrix = CLHEP!HepRotation
    const G4ThreeVector = CLHEP!Hep3Vector
    const G4Transform3D = HepGeom!Transform3D
    export G4ThreeVector, G4RotationMatrix, G4Transform3D

    # Transfer ownership
    function move(a)
        r = CxxPtr(a)
        a.cpp_object = C_NULL
        return r
    end
    # Keep a reference 
    _cfuncs = Vector{CxxWrap.SafeCFunction}()
    function preserve(f::CxxWrap.SafeCFunction)
        global _cfuncs
        push!(_cfuncs, f)
        return f
    end

    # Useful pointers
    export CxxPtr, ConstCxxPtr, CxxRef, ConstCxxRef, move, preserve

    # Cast operations
    Base.convert(::Type{CxxPtr{G4VPhysicalVolume}}, o::G4PVPlacement) =  CxxPtr{G4VPhysicalVolume}(CxxPtr(o))
    Base.convert(::Type{G4String}, s::String) = make_G4String(s)

    # Addional usability functions
    G4PVPlacement(r::Union{Nothing, G4RotationMatrix}, d::G4ThreeVector, l::Union{Nothing,G4LogicalVolume}, s::String, 
                  p::Union{Nothing, G4LogicalVolume}, b1::Bool, n::Int, b2::Bool) = 
                  G4PVPlacement(isnothing(r) ? CxxPtr{G4RotationMatrix}(C_NULL) : move(r), d, 
                                isnothing(l) ? CxxPtr{G4LogicalVolume}(C_NULL) : CxxPtr(l), s, 
                                isnothing(p) ? CxxPtr{G4LogicalVolume}(C_NULL) : CxxPtr(p), b1, n, b2)
                   
    function G4JLDetectorConstruction(f::Function)
        sf = @safe_cfunction($f, CxxPtr{G4VPhysicalVolume}, ())  # crate a safe c function
        G4JLDetectorConstruction(preserve(sf))
    end

    function G4JLActionInitialization(f::Function)
        ff(self::ConstCxxPtr{G4JLActionInitialization}) = f(self[])
        sf = @safe_cfunction($ff, Nothing, (ConstCxxPtr{G4JLActionInitialization},))                      # crate a safe c function
        c = G4JLActionInitialization(sf)                          # call the construction                        
    end

    # Better HL interface (more Julia friendly)----------------------------------------------------
    export G4JLDetector, G4JLSimulationData, G4JLApplication, configure, initialize, beamOn, getConstructor, getInitializer

    abstract type  G4JLAbstrcatApp end
    abstract type  G4JLDetector end
    abstract type  G4JLSimulationData end

    getConstructor(::G4JLDetector) = nothing
    getInitializer(::G4VUserPrimaryGeneratorAction) = nothing

    struct G4JLNoData <: G4JLSimulationData
    end
    
    struct G4JLApplication <: G4JLAbstrcatApp
        runmanager::G4RunManager
        detector::G4JLDetector
        simdata::G4JLSimulationData
        # Types 
        runmanager_type::Type{<:G4RunManager}
        builder_type::Type{<:G4VUserDetectorConstruction}
        physics_type::Type{<:G4VUserPhysicsList}
        generator_type::Type{<:G4VUserPrimaryGeneratorAction}
        #runaction_type::Type{<:G4UserRunAction}
        #eventaction_type::Type{<:G4UserEventAction}
        #stackaction_type::Type{<:G4UserStakingAction}
        trackaction_type::Type{<:G4UserTrackingAction}
        stepaction_type::Type{<:G4UserSteppingAction}
        stepaction_method::Union{Nothing,Function}
        pretrackaction_method::Union{Nothing,Function}
        posttrackaction_method::Union{Nothing,Function}
        function G4JLApplication(detector::G4JLDetector;
                                 simdata=G4JLNoData(),
                                 runmanager_type=G4RunManager,
                                 builder_type=G4JLDetectorConstruction,
                                 physics_type=FTFP_BERT,
                                 generator_type=G4JLParticleGun,
                                 stepaction_type=G4JLSteppingAction,
                                 trackaction_type=G4JLTrackingAction,
                                 stepaction_method=nothing,
                                 pretrackaction_method=nothing,
                                 posttrackaction_method=nothing)
            new(runmanager_type(), detector, simdata, runmanager_type, builder_type, physics_type, generator_type, trackaction_type, stepaction_type,
                stepaction_method, pretrackaction_method, posttrackaction_method)
        end
    end
    
    function configure(app::G4JLApplication)
        #---Detector construction----------------------------------------------------------------------
        runmgr = app.runmanager
        det    = app.detector
        sf1 = @safe_cfunction($(()->getConstructor(det)(det)), CxxPtr{G4VPhysicalVolume}, ())  # crate a safe c function
        SetUserInitialization(runmgr, move(app.builder_type(preserve(sf1))))
        SetUserInitialization(runmgr, move(app.physics_type()))
        #---User Actions-------------------------------------------------------------------------------
        ua = G4JLActionInitialization()
        if !isnothing(app.stepaction_method)
            sf2 = @safe_cfunction($((step::ConstCxxPtr{G4Step}) ->  app.stepaction_method(step[], app)), Nothing, (ConstCxxPtr{G4Step},)) 
            SetUserAction(ua, move(app.stepaction_type(preserve(sf2))))
        end
        if !isnothing(app.pretrackaction_method)
            t1 = @safe_cfunction($((track::ConstCxxPtr{G4Track}) ->  app.pretrackaction_method(track[], app)), Nothing, (ConstCxxPtr{G4Track},))
        else
            t1 = @safe_cfunction($((::ConstCxxPtr{G4Track}) -> nothing), Nothing, (ConstCxxPtr{G4Track},))
        end
        if !isnothing(app.posttrackaction_method)
            t2 = @safe_cfunction($((track::ConstCxxPtr{G4Track}) ->  app.posttrackaction_method(track[], app)), Nothing, (ConstCxxPtr{G4Track},))
        else
            t2 = @safe_cfunction($((::ConstCxxPtr{G4Track}) -> nothing), Nothing, (ConstCxxPtr{G4Track},))
        end
        if !isnothing(app.pretrackaction_method) || !isnothing(app.posttrackaction_method)
            SetUserAction(ua, move(app.trackaction_type(preserve(t1), preserve(t2))))
        end
        #---Primary particles generator------------------------------------------------------------
        gen = app.generator_type()
        init_method = getInitializer(gen)
        !isnothing(init_method) && init_method(gen, det)
        SetUserAction(ua, move(gen))
        #---User initilizatioon--------------------------------------------------------------------
        SetUserInitialization(runmgr, move(ua))
    end

    function initialize(app::G4JLApplication)
        Initialize(app.runmanager)
    end

    function beamOn(app::G4JLApplication, nevents::Int)
        BeamOn(app.runmanager, nevents)
    end

    GetWorldVolume() = GetWorldVolume(GetNavigatorForTracking(G4TransportationManager!GetTransportationManager()))[]

    include("SystemOfUnits.jl")

end # module Geant4

