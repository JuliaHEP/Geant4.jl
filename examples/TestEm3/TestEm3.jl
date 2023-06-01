using Geant4
using Geant4.SystemOfUnits
using FHist, Printf, Plots

#---Define Detector Parameters struct--------------------------------------------------------------
include(joinpath(@__DIR__, "DetectorTestEm3.jl"))

#---Define Simulation Data struct------------------------------------------------------------------
const Hist1D64 = Hist1D{Float64, Tuple{StepRangeLen{Float64, Base.TwicePrecision{Float64}, Base.TwicePrecision{Float64}, Int64}}}
mutable struct TestEm3SimData <: G4JLSimulationData
    #---Run data-----------------------------------------------------------------------------------
    fParticle::CxxPtr{G4ParticleDefinition}
    fEkin::Float64
                           
    #fSumEAbs::Vector{Float64}
    #fSum2EAbs::Vector{Float64} 
    #fSumLAbs::Vector{Float64}
    #fSum2LAbs::Vector{Float64}
    
    #fEdepTot::Float64
    #fEdepTot2::Float64    
    #fEleakTot::Float64
    #fEleakTot2::Float64

    #fEtotal::Float64
    #fEtotal2::Float64
    
    #fEnergyFlow::Vector{Float64}
    #fLateralEleak::Vector{Float64}
    #fEnergyDeposit::Matrix{Float64}
    
    fChargedStep::Int32
    fNeutralStep::Int32

    fN_gamma::Int32
    fN_elec::Int32
    fN_pos::Int32

    fEnergyDeposit::Vector{Float64}     # Energy deposit per event
    fTrackLengthCh::Vector{Float64}     # Track length per event

    fEdepEventHistos::Vector{Hist1D64}
    fTrackLengthChHistos::Vector{Hist1D64}
    fEdepHistos::Vector{Hist1D64}
    fAbsorLabel::Vector{String}
    
    #G4double fEdeptrue [kMaxAbsor];
    #G4double fRmstrue  [kMaxAbsor];
    #G4double fLimittrue[kMaxAbsor];        
    #G4bool fApplyLimit;

    #fTimer::Float64

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

#---Plot the Sumulation data-----------------------------------------------------------------------
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
                               position = G4ThreeVector(0,0,0))  # temporary potition, will update once the detector is constructed

#--------------------------------------------------------------------------------------------------
#----Actions---------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------
#---Step action------------------------------------------------------------------------------------
function stepaction(step::G4Step, app::G4JLApplication)::Nothing
    detector = app.detector
    data = getSIMdata(app)
    prepoint = GetPreStepPoint(step)
    track = GetTrack(step)
 
    # Return if step in not in the world volume
    prepoint |> GetPhysicalVolume |> GetLogicalVolume |> GetMaterial == detector.fWorldMaterial && return nothing
 
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
    (; fNbOfAbsor, fNbOfLayers, fAbsorMaterial, fAbsorThickness) = app.detector
    gun = app.generator.data.gun
    data.fParticle = GetParticleDefinition(gun)
    data.fEkin = GetParticleEnergy(gun)
    data.fN_gamma = data.fN_elec = data.fN_pos = 0
    data.fChargedStep = data.fNeutralStep = 0
    # init arrays
    data.fEnergyDeposit = zeros(fNbOfAbsor)
    data.fTrackLengthCh = zeros(fNbOfAbsor)
    data.fEdepHistos = [Hist1D(Float64; bins=0.:1.0:fNbOfLayers) for i in 1:fNbOfAbsor]
    data.fEdepEventHistos = [Hist1D(;bins=0.:10.:1000.) for i in 1:fNbOfAbsor]
    data.fTrackLengthChHistos = [Hist1D(;bins=0.:20.:2000.) for i in 1:fNbOfAbsor]
    data.fAbsorLabel = ["$(fAbsorThickness[i])mm of $(fAbsorMaterial[i] |> GetName |> String)" for i in 1:fNbOfAbsor]
    nothing
end
#---End Run Action---------------------------------------------------------------------------------
function endrun(run::G4Run, app::G4JLApplication)::Nothing
    #---end run action is called for each workwer thread and the master onc
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
    (; fNbOfAbsor, fNbOfLayers) = app.detector
    for i in 1:fNbOfAbsor
        push!(data.fEdepEventHistos[i], data.fEnergyDeposit[i])
        push!(data.fTrackLengthChHistos[i], data.fTrackLengthCh[i])
    end
    nothing
end

#---Create the Application-------------------------------------------------------------------------
app = G4JLApplication(detector = TestEm3Detector(),               # detector with parameters
                      simdata = TestEm3SimData(),                 # simulation data structure
                      generator = particlegun,                    # primary particle generator 
                      #nthreads = 4,
                      physics_type = FTFP_BERT,                   # what physics list to instantiate
                      #----Actions--------------------------------
                      stepaction_method = stepaction,             # step action method
                      pretrackaction_method = pretrackaction,     # pre-tracking action
                      posttrackaction_method = posttrackaction,   # post-tracking action
                      beginrunaction_method = beginrun,           # begin-run action (initialize counters and histograms)
                      endrunaction_method = endrun,               # end-run action (print summary)               
                      begineventaction_method = beginevent,       # begin-event action (initialize per-event data)
                      endeventaction_method = endevent            # end-event action (fill histogram per event data)
                      )
              
#---Configure, Initialize and Run------------------------------------------------------------------                      
configure(app)
initialize(app)
SetParticlePosition(particlegun, G4ThreeVector(-app.detector.fWorldSizeX/2,0,0))  # Only now is known the size of the 'world'

beamOn(app, 1000)

#---Generate the plots with the results------------------------------------------------------------
do_plot(app.simdata[1])


