using Geant4
using Geant4.SystemOfUnits
using FHist, Printf, Plots

#---Define Simulation Data struct------------------------------------------------------------------
mutable struct TestEm3SimData <: G4JLSimulationData
    #---Run data-----------------------------------------------------------------------------------
    fParticle::CxxPtr{G4ParticleDefinition}
    fEkin::Float64
                    
    fEtotal::Float64
    fEtotal2::Float64
    
    fEnergyFlow::Vector{Float64}
    fLateralEleak::Vector{Float64}
    
    fChargedStep::Int32
    fNeutralStep::Int32

    fN_gamma::Int32
    fN_elec::Int32
    fN_pos::Int32

    fEnergyDeposit::Vector{Float64}     # Energy deposit per event
    fTrackLengthCh::Vector{Float64}     # Track length per event

    fEdepEventHistos::Vector{Hist1D}
    fTrackLengthChHistos::Vector{Hist1D}
    fEdepHistos::Vector{Hist1D{Float64, Tuple{StepRange{Int64, Int64}}}}
    fAbsorLabel::Vector{String}

    fTimer::Float64

    TestEm3SimData() = new()
end
#---add function-----------------------------------------------------------------------------------
function add!(x::TestEm3SimData, y::TestEm3SimData)
    x.fChargedStep += y.fChargedStep
    x.fNeutralStep += y.fNeutralStep
    x.fN_gamma += y.fN_gamma
    x.fN_elec += y.fN_elec
    x.fN_pos += y.fN_pos
    x.fEdepEventHistos += y.fEdepEventHistos
    x.fTrackLengthChHistos += y.fTrackLengthChHistos
    x.fEdepHistos += y.fEdepHistos
end

#---Plot the Simulation data-----------------------------------------------------------------------
function do_plot(data::TestEm3SimData)
    (;fEdepHistos, fEdepEventHistos, fTrackLengthChHistos, fAbsorLabel) = data
    lay = @layout [°; ° °]
    plot(layout=lay, show=true, size=(1400,1000))
    for (h, l) in zip(fEdepHistos, fAbsorLabel)
        plot!(subplot=1, h, title="Energy Deposition", xlabel="layer #", label=l, show=true)
    end
    for (h, l) in zip(fEdepEventHistos, fAbsorLabel)
        plot!(subplot=2, h, title="Energy/event Distribution", label=l, xlabel="MeV")
    end
    for (h, l) in zip(fTrackLengthChHistos, fAbsorLabel)
        plot!(subplot=3, h, title="Track Lengh Distribution", label=l, xlabel="mm")
    end
end

#---Particle Gun initialization--------------------------------------------------------------------
particlegun = G4JLGunGenerator(particle = "e-", 
                               energy = 1GeV, 
                               direction = G4ThreeVector(1,0,0), 
                               position = G4ThreeVector(0,0,0))  # temporary position, will update once the detector is constructed


#--------------------------------------------------------------------------------------------------
#----Actions---------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------
#---Step action------------------------------------------------------------------------------------
function stepaction(step::G4Step, app::G4JLApplication)::Nothing
    data = getSIMdata(app)
    detector = app.detector
    prepoint = GetPreStepPoint(step)
    endPoint = GetPostStepPoint(step)
    track = GetTrack(step)
 
    # Return if step in not in the world volume
    prepoint |> GetPhysicalVolume |> GetLogicalVolume |> GetMaterial == detector.fPhysicalWorld |> GetLogicalVolume |> GetMaterial && return nothing
 
    particle = GetDefinition(track)
    charge  = GetPDGCharge(particle)
    stepl = 0.
    if charge != 0.
        stepl = GetStepLength(step)
        data.fChargedStep += 1
    else
        data.fNeutralStep += 1
    end
    edep = GetTotalEnergyDeposit(step) * GetWeight(track)
    absorNum  = GetCopyNumber(GetTouchable(prepoint), 0)
    layerNum  = GetCopyNumber(GetTouchable(prepoint), 1) + 1  # replicas copynumber starts at 0

    data.fEnergyDeposit[absorNum] += edep
    data.fTrackLengthCh[absorNum] += stepl 	

    push!(data.fEdepHistos[absorNum], layerNum, edep)
    nothing
end
#---Tracking pre-action----------------------------------------------------------------------------
let G4Gamma, G4Electron, G4Positron, first=true
global function pretrackaction(track::G4Track, app::G4JLApplication)::Nothing
    if first
        G4Gamma    = FindParticle("gamma")
        G4Electron = FindParticle("e-")
        G4Positron = FindParticle("e+")
        first = false
    end
    data = getSIMdata(app)
    d = GetDefinition(track)
    if d === G4Gamma 
        data.fN_gamma += 1
    elseif d === G4Electron
        data.fN_elec +=1
    elseif d === G4Positron
        data.fN_pos += 1
    end
    nothing
end
end
#---Tracking post-action---------------------------------------------------------------------------
function posttrackaction(track::G4Track, ::G4JLApplication)::Nothing
  nothing
end
#---Begin Run Action-------------------------------------------------------------------------------
function beginrun(run::G4Run, app::G4JLApplication)::Nothing
    data = getSIMdata(app)
    fNbOfAbsor = 2
    fNbOfLayers = 50
    fAbsorThickness = [2.3mm, 5.7mm]
    fAbsorMaterial = ["G4_Pb", "G4_lAr"]
    gun = app.generator.data.gun
    data.fParticle = GetParticleDefinition(gun)
    data.fEkin = GetParticleEnergy(gun)

    # Good moment to set position
    worldSizeX = app.detector.fPhysicalWorld |> GetLogicalVolume |> GetSolid |> CxxRef{G4Box} |> GetXHalfLength
    SetParticlePosition(gun, G4ThreeVector(-worldSizeX, 0 , 0))

    data.fN_gamma = data.fN_elec = data.fN_pos = 0
    data.fChargedStep = data.fNeutralStep = 0
    # init arrays
    data.fEnergyDeposit = zeros(fNbOfAbsor)
    data.fTrackLengthCh = zeros(fNbOfAbsor)
    data.fEdepHistos = [Hist1D(; bins=0:1:fNbOfLayers) for i in 1:fNbOfAbsor]
    data.fEdepEventHistos = [Hist1D(;bins=0:10:1000) for i in 1:fNbOfAbsor]
    data.fTrackLengthChHistos = [Hist1D(;bins=0:20:2000) for i in 1:fNbOfAbsor]
    data.fAbsorLabel = ["$(fAbsorThickness[i])mm of $(fAbsorMaterial[i])" for i in 1:fNbOfAbsor]
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
        norm = nEvt > 0 ? 1/nEvt : 1.

        @printf "------------------------------------------------------------\n"
        @printf " Beam particle %s E = %.2f GeV\n" String(GetParticleName(data.fParticle)) data.fEkin/GeV 
        @printf " Mean number of gamma          %.2f\n" data.fN_gamma*norm 
        @printf " Mean number of e-             %.2f\n" data.fN_elec*norm 
        @printf " Mean number of e+             %.2f\n" data.fN_pos*norm 
        @printf " Mean number of charged steps  %f\n"   data.fChargedStep*norm 
        @printf " Mean number of neutral steps  %f\n"   data.fNeutralStep*norm 
        @printf "------------------------------------------------------------"
    else
        G4JL_println("end-run  for worker $(G4Threading!G4GetThreadId())") 
    end
end
#---Begin Event Action-----------------------------------------------------------------------------
function beginevent(evt::G4Event, app::G4JLApplication)
    data = getSIMdata(app)
    fill!(data.fEnergyDeposit, 0.0)
    fill!(data.fTrackLengthCh, 0.0)
    nothing
end
#---End Event Action-------------------------------------------------------------------------------
function endevent(evt::G4Event, app::G4JLApplication)
    data = getSIMdata(app)
    fNbOfAbsor = 2
    for i in 1:fNbOfAbsor
        push!(data.fEdepEventHistos[i], data.fEnergyDeposit[i])
        push!(data.fTrackLengthChHistos[i], data.fTrackLengthCh[i])
    end
    nothing
end

#---Create the Application-------------------------------------------------------------------------
app = G4JLApplication(detector = G4JLDetectorGDML("$(@__DIR__)/TestEm3.gdml"),  # detector defined with a GDML file
                      simdata = TestEm3SimData(),                 # simulation data structure
                      generator    = particlegun,                 # primary generator to instantiate
                      physics_type = FTFP_BERT,                   # what physics list to instantiate
                      #----Actions--------------------------------
                      stepaction_method = stepaction,             # step action method
                      pretrackaction_method = pretrackaction,     # pre-tracking action
                      posttrackaction_method = posttrackaction,   # post-tracking action
                      beginrunaction_method=beginrun,             # begin-run action (initialize counters and histograms)
                      endrunaction_method=endrun,                 # end-run action (print summary)               
                      begineventaction_method=beginevent,         # begin-event action (initialize per-event data)
                      endeventaction_method=endevent              # end-event action (fill histogram per event data)
                      )
              
#---Configure, Initialize and Run------------------------------------------------------------------                      
configure(app)
initialize(app)

beamOn(app, 1000)

#---Generate the plots with the results------------------------------------------------------------
do_plot(app.simdata[1])


