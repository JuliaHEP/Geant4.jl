@enum HitType Si ScintCryst
struct Hit
    arrivalTime::Float64
    depositedEnergy::Float64
    hittype::HitType
    position::G4ThreeVector
    function Hit(time, pos, edep, typ)
        hit = new(time, edep, typ, G4ThreeVector())
        assign(hit.position, pos)
        return hit
    end
end
#--------------------------------------------------------------------------------------------------
#---Define Crystal Sensitive Detector--------------------------------------------------------------
#--------------------------------------------------------------------------------------------------
#---SD collected data------------------------------------------------------------------------------
struct CrystalSDData <: G4JLSDData
    hitcollection::Vector{Hit}
    CrystalSDData() = new(Hit[])
end

#---Initialize method------------------------------------------------------------------------------
function crystal_initialize(::G4HCofThisEvent, data::CrystalSDData)::Nothing
    empty!(data.hitcollection)
    return
end
#---Process Hit method-----------------------------------------------------------------------------
let G4OpticalPhoton, first=true
    global function crystal_processHits(step::G4Step, ::G4TouchableHistory, data::CrystalSDData)::Bool
        if first
            G4OpticalPhoton = FindParticle("opticalphoton")
            first = false
        end
        part = step |> GetTrack |> GetParticleDefinition
        part == G4OpticalPhoton && return false 
        edep = step |> GetTotalEnergyDeposit
        edep <  0. && return false
        pos = step |> GetPostStepPoint |> GetPosition
        push!(data.hitcollection, Hit(0., pos, edep, ScintCryst))
        return true
    end
end
#---Create SD instance-----------------------------------------------------------------------------
crystal_SD = G4JLSensitiveDetector("Crystal_SD", CrystalSDData();               # SD name an associated data are mandatory
                                    processhits_method=crystal_processHits,     # process hist method (also mandatory)
                                    initialize_method=crystal_initialize)       # intialize method

#--------------------------------------------------------------------------------------------------
#---Define Silicon Sensitive Detector----------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------
#---SD collected data------------------------------------------------------------------------------
struct SiSDData <: G4JLSDData
    hitcollection::Vector{Hit}
    SiSDData() = new(Hit[])
end

#---Initialize method------------------------------------------------------------------------------
function si_initialize(::G4HCofThisEvent, data::SiSDData)::Nothing
    empty!(data.hitcollection)
    return
end
#---Process Hit method-----------------------------------------------------------------------------
function si_processHits(step::G4Step, ::G4TouchableHistory, data::SiSDData)::Bool
    return false
end
#---Process Optical method-------------------------------------------------------------------------
function processOptical(step::G4Step, data::SiSDData)
    edep = step |> GetTotalEnergyDeposit
    edep == 0 && return
    pos =  step |> GetPostStepPoint |> GetPosition
    t = step |> GetPostStepPoint |> GetGlobalTime
    push!(data.hitcollection, Hit(t, pos, edep, Si))
    return
end
#---Create SD instance-----------------------------------------------------------------------------
silicon_SD = G4JLSensitiveDetector("Silicon_SD", SiSDData();               # SD name an associated data are mandatory
                                    processhits_method=si_processHits,     # process hist method (also mandatory)
                                    initialize_method=si_initialize)       # intialize method

#------------------------------------------------------------------------------------------------------
#---Define User actions
#------------------------------------------------------------------------------------------------------
#---Begin Run Action-------------------------------------------------------------------------------
function beginrun(run::G4Run, app::G4JLApplication)::Nothing
    data = getSIMdata(app)
    # init histos
    data.scintPhotonsHisto = Hist1D(;bins=2.:0.5:50.)
    data.siHitsHisto = Hist1D(;bins=20.:20.:2000.)
    data.crysEdepHisto = Hist1D(;bins=28.:0.05:32.)
    nothing
end
#---End Run Action---------------------------------------------------------------------------------
function endrun(run::G4Run, app::G4JLApplication)::Nothing
    #---end run action is called for each workwer thread and the master one
    if G4Threading!G4GetThreadId() == -1   
        data = app.simdata[1]
        #---This is the master thread, so we need to add all the simuation results-----------------
        for d in app.simdata[2:end]
            add!(data, d)
        end
        nEvt = GetNumberOfEvent(run)
        G4JL_println("Run ended with a total of $nEvt events") 
    end
end
#---Begin Event Action-----------------------------------------------------------------------------
function beginevent(evt::G4Event, app::G4JLApplication)::Nothing
    data = getSIMdata(app)
    data.scintPhotonsPerEvent = 0
    nothing
end
#---End Event Action-------------------------------------------------------------------------------
function endevent(evt::G4Event, app::G4JLApplication)
    data = getSIMdata(app)
    push!(data.scintPhotonsHisto, data.scintPhotonsPerEvent)
    # get the data from the SDs
    cryshits = getSDdata(app, "Crystal_SD").hitcollection
    sihits = getSDdata(app, "Silicon_SD").hitcollection
    push!(data.siHitsHisto, length(sihits))
    push!(data.scintPhotonsHisto, length(cryshits))
    push!(data.crysEdepHisto, isempty(cryshits) ? 0. : sum((h.depositedEnergy for h in cryshits))/keV)
    nothing
end
#---User Stepping action-------------------------------------------------------------------------------
let G4OpticalPhoton, first=true
    global function stepping(step::G4Step, app::G4JLApplication)::Nothing
        if first
            G4OpticalPhoton = FindParticle("opticalphoton")
            first = false
        end

        boundary = findOpticalBoundary(step)
        boundary == C_NULL && return

        data = getSIMdata(app)
        #---trackScintillation
        # secs = step |> GetSecondaryInCurrentStep # not wrapped (missing definition of type const std::vector<const G4Track *> *)
        nsec = step |> GetNumberOfSecondariesInCurrentStep
        if nsec > 0
            allsecs =  step |> GetSecondary
            lsec = length(allsecs)
            secs = allsecs[][lsec-nsec+1:lsec]
            # store the number of optical photons generated to be saved at end of event
            numOps = count(t -> t |> GetParticleDefinition == G4OpticalPhoton, secs)
            data.scintPhotonsPerEvent += numOps
        end
        #---process optical
        track = step |> GetTrack
        if track |> GetParticleDefinition == G4OpticalPhoton
            prePV = step |> GetPreStepPoint |> GetPhysicalVolume
            postPV = step |> GetPostStepPoint |> GetPhysicalVolume
            preName = prePV == C_NULL ? "" : prePV |> GetName |> String
            postName = postPV == C_NULL ? "" : postPV |> GetName |> String

            yesSilicon = occursin("si", preName) || occursin("si", postName)

            if step |> GetPostStepPoint |> GetStepStatus == fGeomBoundary
                stat = boundary |> GetStatus
                if stat == Detection
                    sddata = getSDdata(app, "Silicon_SD")
                    processOptical(step, sddata)
                    return
                elseif stat in (Absorption, TotalInternalReflection, StepTooSmall, Transmission, FresnelRefraction, FresnelReflection)
                    return
                elseif stat == NoRINDEX
                    G4JL_println("NoRINDEX: \n pre vol = $preName \n post vol = $postName")
                else
                    if yesSilicon
                        G4JL_println("omething weird: $stat \n pre volume $preName \n post volume $postName")
                        return
                    end
                end
            end
        end
    end
end
function findOpticalBoundary(step::G4Step)::CxxPtr{G4OpBoundaryProcess}
    pv  = step |> GetTrack |> GetDefinition |> GetProcessManager |> GetProcessList
    for p in pv
        if p |> GetProcessName |> String == "OpBoundary"
            return CxxPtr{G4OpBoundaryProcess}(p)
        end
    end
    # G4JL_println("ImpSteppingAction/findOpticalBoundary: issue finding optical boundary\n")
    return CxxPtr{G4OpBoundaryProcess}(C_NULL)
end
