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

    include("SystemOfUnits.jl")

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
    Base.convert(::Type{CxxPtr{G4VPhysicalVolume}}, o::G4PVReplica) =  CxxPtr{G4VPhysicalVolume}(CxxPtr(o))
    Base.convert(::Type{G4String}, s::String) = make_G4String(s)

    # Addional usability functions
    G4PVPlacement(r::Union{Nothing, G4RotationMatrix}, d::G4ThreeVector, l::Union{Nothing,G4LogicalVolume}, s::String, 
                  p::Union{Nothing, G4LogicalVolume}, b1::Bool, n::Int, b2::Bool=false) = 
                  G4PVPlacement(isnothing(r) ? CxxPtr{G4RotationMatrix}(C_NULL) : move(r), d, 
                                isnothing(l) ? CxxPtr{G4LogicalVolume}(C_NULL) : CxxPtr(l), s, 
                                isnothing(p) ? CxxPtr{G4LogicalVolume}(C_NULL) : CxxPtr(p), b1, n, b2)
    G4PVReplica(s::String, l::G4LogicalVolume, m::G4LogicalVolume, a::EAxis, n::Int64, t::Float64) = G4PVReplica(s, CxxPtr(l), CxxPtr(m), a, n, t)

    function G4JLDetectorConstruction(f::Function)
        sf = @safe_cfunction($f, CxxPtr{G4VPhysicalVolume}, ())  # crate a safe c function
        G4JLDetectorConstruction(preserve(sf))
    end

    function G4JLActionInitialization(f::Function)
        ff(self::ConstCxxPtr{G4JLActionInitialization}) = f(self[])
        sf = @safe_cfunction($ff, Nothing, (ConstCxxPtr{G4JLActionInitialization},))                      # crate a safe c function
        c = G4JLActionInitialization(sf)                          # call the construction                        
    end

    # materials friendly functions (keyword arguments)
    using .SystemOfUnits:kelvin, atmosphere
    G4Material(name::String; z::Float64=0., a::Float64=0., density::Float64, ncomponents::Integer=0, 
               state::G4State=kStateUndefined, temperature::Float64=293.15*kelvin, pressure::Float64=1*atmosphere) = ncomponents == 0 ? G4Material(name, z, a, density, state, temperature, pressure) : G4Material(name, density, ncomponents)
    AddElement(mat::G4Material, elem::CxxPtr{G4Element}; fractionmass::Float64=0., natoms::Integer=0) = fractionmass != 0. ?  AddElementByMassFraction(mat, elem, fractionmass) : AddElementByNumberOfAtoms(mat, elem, natoms)
    AddMaterial(mat::G4Material, mat2::CxxPtr{G4Material}; fractionmass=1.0) = AddMaterial(mat, mat2, fractionmass)
    AddMaterial(mat::G4Material, mat2::G4Material; fractionmass=1.0) = AddMaterial(mat, CxxPtr(mat2), fractionmass)
    G4Isotope(name::String; z::Integer, n::Integer, a::Float64=0., mlevel::Integer=0) =  G4Isotope(name, z, n, a, mlevel)

    # Better HL interface (more Julia friendly)----------------------------------------------------
    export G4JLDetector, G4JLSimulationData, G4JLApplication, G4JLDetectorGDML, G4JLSDData, G4JLSensitiveDetector, 
           configure, initialize, reinitialize, beamOn, getConstructor, getInitializer

    abstract type  G4JLAbstrcatApp end
    abstract type  G4JLDetector end
    abstract type  G4JLSimulationData end
    abstract type  G4JLSDData end

    getConstructor(d::G4JLDetector) = error("You need to define the function Geant4.getConstructor($(typeof(d))) returning the actual contruct method")
    getInitializer(::G4VUserPrimaryGeneratorAction) = nothing

    #---G4JLDetectorGDML----(GDML reader)---------------------------------------------------------
    struct G4JLDetectorGDML <: G4JLDetector
        fPhysicalWorld::CxxPtr{G4VPhysicalVolume}
        function G4JLDetectorGDML(gdmlfile::String; check_overlap::Bool=false)
            parser = G4GDMLParser()
            !isfile(gdmlfile) && error("GDML File $gdmlfile does not exists")
            SetOverlapCheck(parser, check_overlap)
            Read(parser, gdmlfile)
            new(GetWorldVolume(parser))
        end
    end
    getConstructor(::G4JLDetectorGDML) = (det::G4JLDetectorGDML) -> det.fPhysicalWorld

    #---SentitiveDetectors------------------------------------------------------------------------
    struct G4JLSensitiveDetector{UD<:G4JLSDData}
        base::G4JLSensDet
        data::UD
    end
    
    function G4JLSensitiveDetector(name::String, data::T; 
                                   processhits_method=nothing,
                                   initialize_method=nothing,
                                   endofevent_method=nothing) where T<:G4JLSDData
        isnothing(processhits_method) && error("processHits method for ($T,G4Step,G4TouchableHistory) not defined")
        ph =  @safe_cfunction($((s::CxxPtr{G4Step}, th::CxxPtr{G4TouchableHistory}) ->  CxxBool(processhits_method(data, s[], th[]))), CxxBool, (CxxPtr{G4Step},CxxPtr{G4TouchableHistory}))
        base = G4JLSensDet(name, preserve(ph))
        if !isnothing(initialize_method)
            sf = @safe_cfunction($((hc::CxxPtr{G4HCofThisEvent}) ->  initialize_method(data, hc[])), Nothing, (CxxPtr{G4HCofThisEvent},))
            SetInitialize(base, preserve(sf))
        end
        if !isnothing(endofevent_method)
            sf = @safe_cfunction($((hc::CxxPtr{G4HCofThisEvent}) ->  endofevent_method(data, hc[])), Nothing, (CxxPtr{G4HCofThisEvent},))
            SetEndOfEvent(base, preserve(sf))
        end
        G4JLSensitiveDetector{T}(base, data)
    end

    struct G4JLNoData <: G4JLSimulationData
    end
    
    mutable struct G4JLApplication{DET<:G4JLDetector,DAT<:G4JLSimulationData} <: G4JLAbstrcatApp
        const runmanager::G4RunManager
        const detector::DET
        const simdata::DAT
        # Types 
        const runmanager_type::Type{<:G4RunManager}
        const builder_type::Type{<:G4VUserDetectorConstruction}
        const physics_type::Type{<:G4VUserPhysicsList}
        const generator_type::Type{<:G4VUserPrimaryGeneratorAction}
        const runaction_type::Type{<:G4UserRunAction}
        const eventaction_type::Type{<:G4UserEventAction}
        #stackaction_type::Type{<:G4UserStakingAction}
        const trackaction_type::Type{<:G4UserTrackingAction}
        const stepaction_type::Type{<:G4UserSteppingAction}
        # Methods
        const stepaction_method::Union{Nothing,Function}
        const pretrackaction_method::Union{Nothing,Function}
        const posttrackaction_method::Union{Nothing,Function}
        const beginrunaction_method::Union{Nothing,Function}
        const endrunaction_method::Union{Nothing,Function}
        const begineventaction_method::Union{Nothing,Function}
        const endeventaction_method::Union{Nothing,Function}
        # Sensitive Detectors
        sdetectors::Dict{String,G4JLSensitiveDetector}
        # Instances
        detbuilder::Any
        generator::Any
        physics::Any
    end
    #---Convenient constructor---------------------------------------------------------------------
    G4JLApplication(;detector::G4JLDetector,
                    simdata=G4JLNoData(),
                    runmanager_type=G4RunManager,
                    builder_type=G4JLDetectorConstruction,
                    physics_type=FTFP_BERT,
                    generator_type=G4JLParticleGun,
                    stepaction_type=G4JLSteppingAction,
                    trackaction_type=G4JLTrackingAction,
                    runaction_type=G4JLRunAction,
                    eventaction_type=G4JLEventAction,
                    stepaction_method=nothing,
                    pretrackaction_method=nothing,
                    posttrackaction_method=nothing,
                    beginrunaction_method=nothing,
                    endrunaction_method=nothing,
                    begineventaction_method=nothing,
                    endeventaction_method=nothing,
                    sdetectors=[],
                    ) = 
        G4JLApplication{typeof(detector), typeof(simdata)}(runmanager_type(), detector, simdata, runmanager_type, builder_type, physics_type, generator_type, 
                                                           runaction_type, eventaction_type, trackaction_type, stepaction_type,
                                                           stepaction_method, pretrackaction_method, posttrackaction_method, 
                                                           beginrunaction_method, endrunaction_method, begineventaction_method, endeventaction_method,
                                                           Dict(sdetectors), nothing, nothing, nothing)

    
    function configure(app::G4JLApplication)
        #---Detector construction------------------------------------------------------------------
        runmgr = app.runmanager
        det    = app.detector
        sf1 = @safe_cfunction($(()->getConstructor(det)(det)), CxxPtr{G4VPhysicalVolume}, ())  # crate a safe c function
        app.detbuilder = app.builder_type(preserve(sf1))
        SetUserInitialization(runmgr, CxxPtr(app.detbuilder))
        #---Physics List---------------------------------------------------------------------------
        physics = app.physics_type()
        app.physics = physics
        SetUserInitialization(runmgr, move(physics))
        #---Stepping Action---------------------------------------------------------------------------
        ua = G4JLActionInitialization()
        if !isnothing(app.stepaction_method)
            sf2 = @safe_cfunction($((step::ConstCxxPtr{G4Step}) ->  app.stepaction_method(step[], app)), Nothing, (ConstCxxPtr{G4Step},)) 
            SetUserAction(ua, move(app.stepaction_type(preserve(sf2))))
        end
        #---Tracking Action---------------------------------------------------------------------------
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
         #---Run Action---------------------------------------------------------------------------
        if !isnothing(app.beginrunaction_method)
            r1 = @safe_cfunction($((track::ConstCxxPtr{G4Run}) ->  app.beginrunaction_method(track[], app)), Nothing, (ConstCxxPtr{G4Run},))
        else
            r1 = @safe_cfunction($((::ConstCxxPtr{G4Run}) -> nothing), Nothing, (ConstCxxPtr{G4Run},))
        end
        if !isnothing(app.endrunaction_method)
            r2 = @safe_cfunction($((track::ConstCxxPtr{G4Run}) ->  app.endrunaction_method(track[], app)), Nothing, (ConstCxxPtr{G4Run},))
        else
            r2 = @safe_cfunction($((::ConstCxxPtr{G4Run}) -> nothing), Nothing, (ConstCxxPtr{G4Run},))
        end
        if !isnothing(app.beginrunaction_method) || !isnothing(app.endrunaction_method)
            SetUserAction(ua, move(app.runaction_type(preserve(r1), preserve(r2))))
        end
         #---Event Action---------------------------------------------------------------------------
         if !isnothing(app.begineventaction_method)
            e1 = @safe_cfunction($((evt::ConstCxxPtr{G4Event}) ->  app.begineventaction_method(evt[], app)), Nothing, (ConstCxxPtr{G4Event},))
        else
            e1 = @safe_cfunction($((::ConstCxxPtr{G4Event}) -> nothing), Nothing, (ConstCxxPtr{G4Event},))
        end
        if !isnothing(app.endeventaction_method)
            e2 = @safe_cfunction($((evt::ConstCxxPtr{G4Event}) ->  app.endeventaction_method(evt[], app)), Nothing, (ConstCxxPtr{G4Event},))
        else
            e2 = @safe_cfunction($((::ConstCxxPtr{G4Event}) -> nothing), Nothing, (ConstCxxPtr{G4Event},))
        end
        if !isnothing(app.begineventaction_method) || !isnothing(app.endeventaction_method)
            SetUserAction(ua, move(app.eventaction_type(preserve(e1), preserve(e2))))
        end

        #---Primary particles generator------------------------------------------------------------
        generator = app.generator_type()
        init_method = getInitializer(generator)
        !isnothing(init_method) && init_method(generator, det)
        app.generator = generator
        SetUserAction(ua, CxxPtr(generator))
        #---User initilization---------------------------------------------------------------------
        SetUserInitialization(runmgr, move(ua))
    end

    function initialize(app::G4JLApplication)
        Initialize(app.runmanager)
        #---Add the Sensitive Detectors now that the geometry is constructed-----------------------
        for (lv,sd) in app.sdetectors
            if lv[end] == '+'
                lv = lv[1:end-1]
                multi = true
            else
                multi = false
            end
            SetSensitiveDetector(app.detbuilder, lv, CxxPtr(sd.base), multi)
        end
    end

    function reinitialize(app::G4JLApplication, det::G4JLDetector)
        app.detector = det
        runmgr = app.runmanager
        sf1 = @safe_cfunction($(()->getConstructor(det)(det)), CxxPtr{G4VPhysicalVolume}, ())  # crate a safe c function
        SetUserInitialization(runmgr, move(app.builder_type(preserve(sf1))))
        ReinitializeGeometry(runmgr)
        Initialize(runmgr)
    end

    function beamOn(app::G4JLApplication, nevents::Int)
        BeamOn(app.runmanager, nevents)
    end

    GetWorldVolume() = GetWorldVolume(GetNavigatorForTracking(G4TransportationManager!GetTransportationManager()))[]

end # module Geant4

