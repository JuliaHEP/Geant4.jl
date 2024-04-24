#---Exports from this section----------------------------------------------------------------------
export G4JLDetector, G4JLSimulationData, G4JLApplication, G4JLDetectorGDML, G4JLSDData, G4JLSensitiveDetector, 
        configure, initialize, reinitialize, beamOn, getSDdata, getSIMdata, getConstructor, getInitializer, 
        G4JLUniformMagField, G4JLMagneticField, G4JLFieldData, G4JLDisplay

#---Geometry usability functions-------------------------------------------------------------------
G4PVPlacement(r::Union{Nothing, G4RotationMatrix}, d::G4ThreeVector, l::Union{Nothing,G4LogicalVolume}, s::String, 
              p::Union{Nothing, G4LogicalVolume}, b1::Bool, n::Int, b2::Bool=false) = 
    G4PVPlacement(isnothing(r) ? CxxPtr{G4RotationMatrix}(C_NULL) : move!(r), d, 
                  isnothing(l) ? CxxPtr{G4LogicalVolume}(C_NULL) : CxxPtr(l), s, 
                  isnothing(p) ? CxxPtr{G4LogicalVolume}(C_NULL) : CxxPtr(p), b1, n, b2)

G4PVPlacement(t::G4Transform3D, l::Union{Nothing,G4LogicalVolume}, s::String, 
              p::Union{Nothing, G4LogicalVolume}, b1::Bool, n::Int, b2::Bool=false) = 
    G4PVPlacement(t, isnothing(l) ? CxxPtr{G4LogicalVolume}(C_NULL) : CxxPtr(l), s, 
                  isnothing(p) ? CxxPtr{G4LogicalVolume}(C_NULL) : CxxPtr(p), b1, n, b2)

G4PVReplica(s::String, l::G4LogicalVolume, m::G4LogicalVolume, a::EAxis, n::Int64, t::Float64) = 
    G4PVReplica(s, CxxPtr(l), CxxPtr(m), a, n, t)

function G4JLDetectorConstruction(f::Function)
    sf = make_callback(nothing, f, CxxPtr{G4VPhysicalVolume}, ()) |> closure
    G4JLDetectorConstruction(sf...)
end

function G4JLActionInitialization(f::Function)
    sf = make_callback(nothing, f, Nothing, (ConstCxxPtr{G4JLActionInitialization},)) |> closure
    G4JLActionInitialization(sf..., sf...)                          # call the construction                        
end

function G4LogicalVolume(solid::G4VSolid, mat::CxxPtr{G4Material}, name::String,
                         fldmgr=CxxPtr{G4FieldManager}(C_NULL), 
                         sd=CxxPtr{G4VSensitiveDetector}(C_NULL), 
                         ulimits=CxxPtr{G4UserLimits}(C_NULL), 
                         opt=true)
    G4LogicalVolume(move!(solid), mat, name, 
                    fldmgr isa G4FieldManagerAllocated ? move!(fldmgr) : fldmgr,
                    sd isa CxxPtr ? sd  : move!(sd),
                    ulimits isa  G4UserLimitsAllocated ? move!(ulimits) : ulimits,  opt)
end
SetUserLimits(lv::G4LogicalVolume, l::G4UserLimitsAllocated) = SetUserLimits(lv, move!(l))     

#---Material friendly functions (keyword arguments)------------------------------------------------
using .SystemOfUnits:kelvin, atmosphere
G4Material(name::String; z::Float64=0., a::Float64=0., density::Float64, ncomponents::Integer=0, 
           state::G4State=kStateUndefined, temperature::Float64=293.15*kelvin, pressure::Float64=1*atmosphere) = 
    ncomponents == 0 ? G4Material(name, z, a, density, state, temperature, pressure) : G4Material(name, density, ncomponents)
AddElement(mat::G4Material, elem::CxxPtr{G4Element}; fractionmass::Float64=0., natoms::Integer=0) = 
    fractionmass != 0. ?  AddElementByMassFraction(mat, elem, fractionmass) : AddElementByNumberOfAtoms(mat, elem, natoms)
AddMaterial(mat::G4Material, mat2::CxxPtr{G4Material}; fractionmass=1.0) = AddMaterial(mat, mat2, fractionmass)
AddMaterial(mat::G4Material, mat2::G4Material; fractionmass=1.0) = AddMaterial(mat, CxxPtr(mat2), fractionmass)
G4Isotope(name::String; z::Integer, n::Integer, a::Float64=0., mlevel::Integer=0) = G4Isotope(name, z, n, a, mlevel)

#---Better HL interface (more Julia friendly)------------------------------------------------------
abstract type  G4JLAbstrcatApp end
abstract type  G4JLDetector end
abstract type  G4JLSimulationData end
abstract type  G4JLSDData end
abstract type  G4JLFieldData end
abstract type  G4JLDisplay end

getConstructor(d::G4JLDetector) = error("You need to define the function Geant4.getConstructor($(typeof(d))) returning the actual contruct method")
getInitializer(::G4VUserPrimaryGeneratorAction) = nothing

#---G4JLDetectorGDML----(GDML reader)--------------------------------------------------------------
struct G4JLDetectorGDML <: G4JLDetector
    fPhysicalWorld::CxxPtr{G4VPhysicalVolume}
end
getConstructor(::G4JLDetectorGDML) = (det::G4JLDetectorGDML) -> det.fPhysicalWorld
"""
    G4JLDetectorGDML(gdmlfile::String; check_overlap::Bool, validate_schema::Bool, init_method::Union{Function,Nothing})

Initialize a G4JLDetector from a GDML file. The GDML file is parsed at this moment.
"""
function G4JLDetectorGDML(gdmlfile::String; 
                          check_overlap::Bool=false, 
                          validate_schema::Bool=true, 
                          init_method::Union{Function,Nothing}=nothing)
    parser = G4GDMLParser()
    !isfile(gdmlfile) && error("GDML File $gdmlfile does not exists")
    SetOverlapCheck(parser, check_overlap)
    Read(parser, gdmlfile, validate_schema)
    world = GetWorldVolume(parser)
    if !isnothing(init_method)
        init_method(world)
    end
    G4JLDetectorGDML(world)
end

#---Custom Magnetic Field--------------------------------------------------------------------------
"""
    Custom Magnetic Field
"""
mutable struct G4JLMagneticField{UD<:G4JLFieldData}
    const name::String
    const data::UD
    const getfield::Function    #  signature  (result::G4ThreeVector, position::G4ThreeVector, ::SD)
    base::Vector{G4JLMagField}
end
"""
    getfield(pos::G4ThreeVector, bfield::G4JLMagneticField)

Function to exercise a custom magnetic field
"""
function getfield(pos::G4ThreeVector, bfield::G4JLMagneticField)
    B = G4ThreeVector()
    bfield.getfield(B, pos, bfield.data)
    return B
end 

"""
    G4JLMagneticField(name::String, data::DATA; <keyword arguments>) where DATA<:G4JLGeneratorData

Create a G4JLMagneticField with its name and associated DATA structure
# Arguments
"""
function G4JLMagneticField(name::String, data::T;
                           getfield_method=nothing) where T<:G4JLFieldData
    isnothing(getfield_method) && error("get field method not defined")
    G4JLMagneticField{T}(name, data, getfield_method, G4JLMagField[])   
end

#---Implementation (user friendly) Uniform Magnetic Field------------------------------------------
mutable struct G4JLUniformMagFieldData <: G4JLFieldData
    field::G4ThreeVector
end

function G4JLMagneticField{G4JLUniformMagFieldData}(field::G4ThreeVector)
    data = G4JLUniformMagFieldData(field)
    function getfield!(field::G4ThreeVector, pos::G4ThreeVector, data::G4JLUniformMagFieldData)::Nothing
        assign(field, data.field)
        return
    end
    G4JLMagneticField("UnifiormB", data; getfield_method=getfield!)
end

const G4JLUniformMagField = G4JLMagneticField{G4JLUniformMagFieldData}

#---SentitiveDetectors-----------------------------------------------------------------------------
struct G4JLSensitiveDetector{UD<:G4JLSDData}
    base::G4JLSensDet
    data::UD
end
struct G4JLProtoSD{UD<:G4JLSDData}
    name::String
    data::UD
    processhits::Union{Function, Nothing}
    initialize::Union{Function, Nothing}
    endofevent::Union{Function, Nothing}
end

"""
    G4JLSensitiveDetector(name::String, data::DATA; <keyword arguments>) where DATA<:G4JLSDData

Initialize a G4JLSensitiveDetector with its name and associated DATA structure.
# Arguments
- `name::String`: Sensitive detector name
- `data::DATA`: Data structure associted to the sensitive detector
- `processhits_method=nothing`: processHit function with signature: `(data::DATA, step::G4Step, ::G4TouchableHistory)::Bool`
- `initialize_method=nothing`: intialize function with signature: `(data::DATA, ::G4HCofThisEvent)::Nothing`
- `endofevent_method=nothing`: endOfEvent function with signature: `(data::DATA, ::G4HCofThisEvent)::Nothing` 
"""
function G4JLSensitiveDetector(name::String, data::T; 
                                processhits_method=nothing,
                                initialize_method=nothing,
                                endofevent_method=nothing) where T<:G4JLSDData
    isnothing(processhits_method) && error("processHits method for ($T,G4Step,G4TouchableHistory) not defined")
    G4JLProtoSD{T}(name, data, processhits_method, initialize_method, endofevent_method)
end

function G4JLSensitiveDetector(sd::G4JLProtoSD)
    (;name, data, processhits, initialize, endofevent) = sd
    tls_data = deepcopy(data)
    cb = make_callback(tls_data, processhits, CxxBool, (CxxPtr{G4Step}, CxxPtr{G4TouchableHistory})) |> closure
    base = G4JLSensDet(name, cb...)
    if !isnothing(initialize)
        cb =  make_callback(tls_data, initialize, Nothing, (CxxPtr{G4HCofThisEvent},)) |> closure
        SetInitialize(base, cb...)
    end
    if !isnothing(endofevent)
        cb =  make_callback(tls_data, endofevent, Nothing, (CxxPtr{G4HCofThisEvent},)) |> closure
        SetEndOfEvent(base, cb...)
    end
    G4JLSensitiveDetector{typeof(data)}(base, tls_data)
end

struct G4JLNoData <: G4JLSimulationData
end

#--Empty Detector----------------------------------------------------------------------------------
struct G4JLEmptyDetector <: G4JLDetector end
using Geant4.PhysicalConstants: universe_mean_density
using Geant4.SystemOfUnits: g, mole, kelvin, pascal, parsec, m
function _construct(::G4JLEmptyDetector)
    vacuum = G4Material("Vacuum", z=1., a=1.01g/mole, density=universe_mean_density, state=kStateGas, 
                        temperature=2.73*kelvin, pressure=3.e-18*pascal)
    G4PVPlacement(nothing, G4ThreeVector(),
                  G4LogicalVolume(G4Orb("World", 1m), move!(vacuum), "World"),
                  "World", nothing, false, 0, false)
end  
Geant4.getConstructor(::G4JLEmptyDetector) = _construct

#---Geant4 Application-----------------------------------------------------------------------------
mutable struct G4JLApplication{DET<:G4JLDetector,DAT<:G4JLSimulationData} <: G4JLAbstrcatApp
    const runmanager::Any
    detector::DET
    simdata::Vector{DAT}  # Each worker thread has its own data                            
    generator::G4JLPrimaryGenerator
    field::Union{Nothing, G4Field, G4JLMagneticField}
    evtdisplay::Union{Nothing, G4JLDisplay}
    const nthreads::Int32
    const verbose::Int32
    # Types 
    const runmanager_type::Type{<:G4RunManager}
    const builder_type::Type{<:G4VUserDetectorConstruction}
    const physics_type::Type{<:G4VUserPhysicsList}
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
    const stackaction_method::Union{Nothing,Function}
    const statechange_method::Union{Nothing, Function}
    # Sensitive Detectors
    protoSDs::Dict{String,G4JLProtoSD}
    sdetectors::Dict{String,Vector{G4JLSensitiveDetector}} # single and MT
    # Scoring Meshes
    scorers::Vector{G4JLScoringMesh}
    # Instances
    detbuilder::Any
    physics::Any
end
"""
    G4JLApplication(<keyword arguments>)

Initialize a G4JLApplication with its associated tyopes and methods.
# Arguments
- `detector::G4JLDetector`: detector description object
- `simdata=G4JLNoData()`: simulation data object
- `generator=G4JLParticleGun()`: primary particle generator
- `field=nothing`: magnetic field
- `evtdisplay=nothing`: event display (visualization)
- `nthreads=0`: number of Geant4 worker threads ( >0 implies MT)
- `verbose=0` : default verbority level (physics, ...)
- `runmanager_type=G4RunManager`: run manager type
- `builder_type=G4JLDetectorConstruction`: detector builder type (the default should be fine most cases)
- `physics_type=FTFP_BERT`: physics list type
- `stepaction_type=G4JLSteppingAction`: stepping action type (the default should be fine most cases)
- `trackaction_type=G4JLTrackingAction`: rtacking action type (the default should be fine most cases)
- `runaction_type=G4JLRunAction`: run action type (the default should be fine most cases)
- `eventaction_type=G4JLEventAction`: event action type (the default should be fine most cases)
- `stepaction_method=nothing`: stepping action method with signature `(::G4Step, ::G4JLApplication)::Nothing`
- `pretrackaction_method=nothing`: pre-tracking action method with signature `(::G4Track, ::G4JLApplication)::Nothing`
- `posttrackaction_method=nothing`: post-tracking action method with signature `(::G4Track, ::G4JLApplication)::Nothing`
- `beginrunaction_method=nothing`: begin run action method with signature `(::G4Run, ::G4JLApplication)::Nothing`
- `endrunaction_method=nothing`: end run action method with signature `(::G4Run, ::G4JLApplication)::Nothing`
- `begineventaction_method=nothing`: begin event action method with signature `(::G4Event, ::G4JLApplication)::Nothing`
- `endeventaction_method=nothing`: end event action method with signature `(::G4Event, ::G4JLApplication)::Nothing`
- `stackaction_method=nothing`: stacking classification of new track with signature `(::G4Track, ::G4JLApplication)::G4ClassificationOfNewTrack`
- `statechange_method=nothing`: state change notifycation method with  signature `(from::G4ApplicationState, to::G4ApplicationState, ::G4JLApplication)::Bool`
- `sdetectors::Vector{}=[]`: vector of pairs `lv::String => sd::G4JLSensitiveDetector` to associate logical volumes to sensitive detector
- `scorers::Vector{}=[]`: vector of [`G4JLScoringMesh`](@ref)s
"""
function G4JLApplication(;
                detector::G4JLDetector = G4JLEmptyDetector(),
                simdata = G4JLNoData(),
                generator = G4JLGunGenerator(),
                field=nothing,
                evtdisplay=nothing,
                nthreads=0,
                verbose=0,
                runmanager_type=G4RunManager,
                builder_type=G4JLDetectorConstruction,
                physics_type=FTFP_BERT,
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
                stackaction_method=nothing,
                statechange_method=nothing,
                sdetectors=[],
                scorers=[],
                )
    # if nthreads > 0 force G4MTRunManager
    runmanager_type = nthreads > 0 ? G4MTRunManager : runmanager_type
    # check whether the RunMamager is already constructed
    runmgr = G4RunManager!GetRunManager()
    if runmgr == C_NULL
        runmgr = runmanager_type()
        physics = nothing
    else
        statemgr = G4StateManager!GetStateManager()
        SetNewState(statemgr, G4State_PreInit)
        physics = isempty(physicslists) ? nothing : last(physicslists)
    end
    # instantiate G4JLApplication
    this = G4JLApplication{typeof(detector), typeof(simdata)}(
                           runmgr, detector, [deepcopy(simdata) for i in 1:nthreads+1], generator, 
                           field, evtdisplay, nthreads, 
                           verbose, nthreads > 0 ? G4MTRunManager : G4RunManager, builder_type, physics_type, 
                           runaction_type, eventaction_type, trackaction_type, stepaction_type,
                           stepaction_method, pretrackaction_method, posttrackaction_method, 
                           beginrunaction_method, endrunaction_method, begineventaction_method, 
                           endeventaction_method, stackaction_method, statechange_method,
                           Dict(sdetectors), Dict{String,Vector{G4JLSensitiveDetector}}(), 
                           scorers, nothing, physics)
    # register state change dependent
    if !isnothing(statechange_method)
        sf = make_callback(this, statechange_method, CxxBool, (G4ApplicationState, G4ApplicationState)) |> closure
        G4JLStateDependent(sf...)
    end
    if !isnothing(evtdisplay)
        sf = make_callback(this, evtdisplay.stateChange, CxxBool, (G4ApplicationState, G4ApplicationState)) |> closure
        G4JLStateDependent(sf...)
    end
    return this
end

physicslists = Vector{Any}()

"""
    configure(app::G4JLApplication)
Configure the Geant4 application. It sets the declared user actions, event generator, and physcis list. 
"""
function configure(app::G4JLApplication)
    runmgr = app.runmanager
    #---Set the number of threads and declare G4UserWorkerInitialization---------------------------
    if app.nthreads > 0 
        SetNumberOfThreads(runmgr, app.nthreads)
        SetUserInitialization(runmgr, move!(G4JLWorkerInitialization()))
    end
    #---Prepare SentitiveDetectors-----------------------------------------------------------------
    for (lv,sd) in app.protoSDs
        app.sdetectors[sd.name] = Vector{G4JLSensitiveDetector}(undef, app.nthreads + 1)
    end
    #---Prepare Primary Generators-----------------------------------------------------------------
    app.generator.base = Vector{G4JLGeneratorAction}(undef, app.nthreads + 1)
    #---Prepare Primary Generators-----------------------------------------------------------------
    if app.field isa G4JLMagneticField
        app.field.base = Vector{G4JLMagField}(undef, app.nthreads + 1)
    end
    #---Detector construction----------------------------------------------------------------------
    function sdandf(app::G4JLApplication)::Nothing  # called by the worker thread during init------
        #---Add the Sensitive Detectors now that the geometry is constructed-----------------------
        tid = G4Threading!G4GetThreadId()
        tid < 0 && (tid = -1)   # master thread (-2 for without multi-threading support)
        for (lv,protosd) in app.protoSDs
            sd = G4JLSensitiveDetector(protosd)
            app.sdetectors[protosd.name][tid+2] = sd
            if lv[end] == '+'
                lv = lv[1:end-1]
                multi = true
            else
                multi = false
            end
            SetSensitiveDetector(app.detbuilder, lv, CxxPtr(sd.base), multi)
        end
        #---Add Magnetic field if needed-----------------------------------------------------------
        fieldMgr = G4TransportationManager!GetTransportationManager() |> GetFieldManager
        if app.field isa G4Field
            B = Clone(app.field)
            SetDetectorField(fieldMgr, B)
            CreateChordFinder(fieldMgr, CxxPtr{G4MagneticField}(B))
        elseif app.field isa G4JLMagneticField
            sf = make_callback(app.field.data, app.field.getfield, Nothing, (CxxRef{G4ThreeVector}, ConstCxxRef{G4ThreeVector})) |> closure
            B = G4JLMagField(sf...)
            app.field.base[tid+2] = B
            SetDetectorField(fieldMgr, CxxPtr(B))
            CreateChordFinder(fieldMgr, CxxPtr(B))
        end
        nothing
    end
    det = app.detector
    cb1 = make_callback(det, getConstructor(det), CxxPtr{G4VPhysicalVolume}, ()) |> closure
    cb2 = make_callback(app, sdandf, Nothing, ()) |> closure
    app.detbuilder = app.builder_type(cb1..., cb2...)
    SetUserInitialization(runmgr, CxxPtr(app.detbuilder))
    #---Physics List---------------------------------------------------------------------------
    if isnothing(app.physics)   # we need to construct the physics list only once
        physics = app.physics_type(app.verbose)
        app.physics = CxxPtr(physics)
        push!(physicslists, app.physics)
        SetUserInitialization(runmgr, move!(physics))
    end
    #---Actions--------------------------------------------------------------------------------
    function build(uai::G4JLActionInitialization, app::G4JLApplication)::Nothing
        if !isnothing(app.stepaction_method)
            cb = make_callback(app, app.stepaction_method, Nothing, (ConstCxxPtr{G4Step},))
            SetUserAction(uai, move!(app.stepaction_type(closure(cb)...)))
        end
        #---Tracking Action---------------------------------------------------------------------------
        if !isnothing(app.pretrackaction_method)
            t1 = make_callback(app, app.pretrackaction_method, Nothing, (ConstCxxPtr{G4Track},)) |> closure
        else
            t1 = null_closure(Nothing, (ConstCxxPtr{G4Track},))
        end
        if !isnothing(app.posttrackaction_method)
            t2 = make_callback(app, app.posttrackaction_method, Nothing, (ConstCxxPtr{G4Track},)) |> closure
        else
            t2 = null_closure(Nothing, (ConstCxxPtr{G4Track},))
        end
        if !isnothing(app.pretrackaction_method) || !isnothing(app.posttrackaction_method)
            SetUserAction(uai, move!(app.trackaction_type(t1..., t2...)))
        end
        #---Run Action---------------------------------------------------------------------------
        if !isnothing(app.beginrunaction_method)
            r1 = make_callback(app, app.beginrunaction_method, Nothing, (ConstCxxPtr{G4Run},)) |> closure
        else
            r1 = null_closure(Nothing, (ConstCxxPtr{G4Run},))
        end
        if !isnothing(app.endrunaction_method)
            r2 = make_callback(app, app.endrunaction_method, Nothing, (ConstCxxPtr{G4Run},)) |> closure
        else
            r2 = null_closure(Nothing, (ConstCxxPtr{G4Run},))
        end
        if !isnothing(app.beginrunaction_method) || !isnothing(app.endrunaction_method)
            SetUserAction(uai, move!(app.runaction_type(r1..., r2...)))
        end
        #---Event Action---------------------------------------------------------------------------
        if !isnothing(app.begineventaction_method)
            e1 = make_callback(app, app.begineventaction_method, Nothing, (ConstCxxPtr{G4Event},)) |> closure
        else
            e1 = null_closure(Nothing, (ConstCxxPtr{G4Event},))
        end
        if !isnothing(app.endeventaction_method)
            e2 = make_callback(app, app.endeventaction_method, Nothing, (ConstCxxPtr{G4Event},)) |> closure
        else
            e2 = null_closure(Nothing, (ConstCxxPtr{G4Event},))
        end
        if !isnothing(app.begineventaction_method) || !isnothing(app.endeventaction_method)
            SetUserAction(uai, move!(app.eventaction_type(e1..., e2...)))
        end
        #---Staking acrion------------------------------------------------------------------------
        if !isnothing(app.stackaction_method)
            cd = make_callback(app, app.stackaction_method, G4ClassificationOfNewTrack, (ConstCxxPtr{G4Track},)) |> closure
            SetUserAction(uai, move!(G4JLStackingAction(cd...)))
        end
        #---Primary particles generator---------(per thread)--------------------------------------
        gen = app.generator
        tid = G4Threading!G4GetThreadId()
        tid < 0 && (tid = -1)   # master thread (-2 for without multi-threading support)
        g1 =  make_callback(gen.data, gen.gen_method, Nothing, (CxxPtr{G4Event},)) |> closure
        gen.base[tid+2] = G4JLGeneratorAction(g1...)
        init_method = gen.init_method
        !isnothing(init_method) && init_method(gen.data, app)
        SetUserAction(uai, CxxPtr(gen.base[tid+2]))
    end
    function master_build(uai::G4JLActionInitialization, app::G4JLApplication)::Nothing
        #---Run Action---------------------------------------------------------------------------
        if !isnothing(app.beginrunaction_method)
            r1 = make_callback(app, app.beginrunaction_method, Nothing, (ConstCxxPtr{G4Run},)) |> closure
        else
            r1 = null_closure(Nothing, (ConstCxxPtr{G4Run},))
        end
        if !isnothing(app.endrunaction_method)
            r2 = make_callback(app, app.endrunaction_method, Nothing, (ConstCxxPtr{G4Run},)) |> closure
        else
            r2 = null_closure(Nothing, (ConstCxxPtr{G4Run},))
        end
        if !isnothing(app.beginrunaction_method) || !isnothing(app.endrunaction_method)
            SetUserAction(uai, move!(app.runaction_type(r1..., r2...)))
        end
    end
    #---User Actions Initialization------------------------------------------------------------
    cb1 = make_callback(app, build, Nothing, (ConstCxxPtr{G4JLActionInitialization},)) |> closure
    cb2 = make_callback(app, master_build, Nothing, (ConstCxxPtr{G4JLActionInitialization},)) |> closure
    ai = G4JLActionInitialization(cb1..., cb2...)
    SetUserInitialization(runmgr, move!(ai))
    #---Setup Scoring--------------------------------------------------------------------------
    if !isempty(app.scorers)
        G4ScoringManager!GetScoringManager()
    end
end
"""
    initialize(app::G4JLApplication)
Initialize the Geant4 application. It initializes the RunManager, which constructs the detector geometry, and sets 
the declared sensitive detectors.
"""
function initialize(app::G4JLApplication)
    Initialize(app.runmanager)
    #---Process scorers------------------------------------------------------------------------
    for sc in app.scorers
        uicmd = toUIstring(sc)
        uimgr = G4UImanager!GetUIpointer()
        for s = eachsplit(uicmd,'\n')
            ApplyCommand(uimgr, String(s)) == 0 || error("Got an error processing UI command '$s'")
        end
        ApplyCommand(uimgr, "/score/close")
        ApplyCommand(uimgr, "/score/list")
    end
    #---Initialize Event Display---------------------------------------------------------------
    if ! isnothing(app.evtdisplay)
        app.evtdisplay.initDisplay(app.evtdisplay)
    end
end
"""
    reinitialize(app::G4JLApplication, det::G4JLDetector)
Re-initialize the Geant4 application with a new detector defintion.
"""
function reinitialize(app::G4JLApplication, det::G4JLDetector)
    app.detector = det
    runmgr = app.runmanager
    cb1 = make_callback(det, getConstructor(det), CxxPtr{G4VPhysicalVolume}, ()) |> closure
    SetUserInitialization(runmgr, move!(app.builder_type(cb1...)))
    ReinitializeGeometry(runmgr)
    Initialize(runmgr)
    #---Initialize Event Display---------------------------------------------------------------
    if ! isnothing(app.evtdisplay)
        app.evtdisplay.initDisplay(app.evtdisplay)
    end
end
"""
    beamOn(app::G4JLApplication, nevents::Int)
Start a new run with `nevents` events.
"""
function beamOn(app::G4JLApplication, nevents::Int)
    statemgr = G4StateManager!GetStateManager()
    in_state = GetCurrentState(statemgr)[]
    try 
        if app.nthreads > 0
            # before starting the run (creation of worker threads) we need to enter GC safe state not 
            # to block any garbage collection.  
            state = ccall(:jl_gc_safe_enter,Cint,())
            BeamOn(app.runmanager, nevents)
            ccall(:jl_gc_safe_leave,Cint,(Cint,), state)
        else
            BeamOn(app.runmanager, nevents)
        end
    catch 
        SetNewState(statemgr, in_state)
        rethrow()
    end
    return
end

"""
    getSDdata(app::G4JLApplication, name::String)
Get the data associated to the Sentitive Detector with a given name taking into account the current worker thread ID 
"""
function getSDdata(app, name)
    tid = G4Threading!G4GetThreadId()
    tid < 0 && (tid = -1)   # master thread (-2 for without multi-threading support)
    app.sdetectors[name][tid+2].data
end

"""
    getSIMdata(app::G4JLApplication)
Get the Simulation Data taking into account the current worker thread ID 
"""
function getSIMdata(app)
    tid = G4Threading!G4GetThreadId()
    tid < 0 && (tid = -1)   # master thread (-2 for without multi-threading support)
    app.simdata[tid+2]
end

"""
    GetWorldVolume()
Get the world volume of the currently instantiated detector geometry.
"""
GetWorldVolume() = GetWorldVolume(GetNavigatorForTracking(G4TransportationManager!GetTransportationManager()))[]
"""
    GetVolume(name::String)
Get the  the G4LogicalVolume with this name.
"""
GetVolume(name::String) = GetVolume(G4LogicalVolumeStore!GetInstance(), name)
