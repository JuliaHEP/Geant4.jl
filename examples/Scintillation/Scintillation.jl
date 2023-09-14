using Geant4
using Geant4.PhysicalConstants
using Geant4.SystemOfUnits
using FHist, Printf, Plots

#using GLMakie, Rotations, IGLWrap_jll  # to force loading G4Vis extension

#---Detector Geometry------------------------------------------------------------------------------
include(joinpath(@__DIR__, "Parameters.jl"))
include(joinpath(@__DIR__, "Detector.jl"))

crysdet = ScintDetector()
#world = scintConstruct(crystal)
#draw(world[])

#----Physics---------------------------------------------------------------------------------------
struct ScintPhysicsList <: G4VUserPhysicsList
    function ScintPhysicsList(verbose)
        pl = FTFP_BERT(verbose)
        ReplacePhysics(pl, move!(G4EmStandardPhysics_option4(verbose)))
        RegisterPhysics(pl, move!(G4OpticalPhysics(verbose)))
        # need to enable scintillation
        optpar = G4OpticalParameters!Instance()
        SetProcessActivation(optpar, "Scintillation", true);
        # I have found Cherenkov radiation to be error-prone
        SetProcessActivation(optpar, "Cerenkov", true);
        return pl
    end 
end

#---Particle Gun initialization--------------------------------------------------------------------
particlegun = G4JLGunGenerator(particle = "gamma", 
                               energy = 30keV, 
                               direction = G4ThreeVector(0, 0, -1), 
                               position = G4ThreeVector(0, 0, 2cm))

#---Simulation Data-------------(normally filled by actions)---------------------------------------
const Hist1D64 = Hist1D{Float64, Tuple{StepRangeLen{Float64, Base.TwicePrecision{Float64}, Base.TwicePrecision{Float64}, Int64}}}
mutable struct ScintSimData <: G4JLSimulationData
    scintPhotonsPerEvent::Int64
    scintPhotonsHisto::Hist1D64
    siHitsHisto::Hist1D64
    crysEdepHisto::Hist1D64
    ScintSimData() = new()
end
#---Addd function-----------------------------------------------------------------------------------
function add!(x::ScintSimData, y::ScintSimData)
    x.scintPhotonsHisto += y.scintPhotonsHisto
    x.siHitsHisto += y.siHitsHisto
    x.crysEdepHisto += y.crysEdepHisto
end
#---Plot Simulation data----------------------------------------------------------------------------
function do_plot(data::ScintSimData)
    (;scintPhotonsHisto, siHitsHisto, crysEdepHisto) = data
    lay = @layout [° °; °]
    plot(layout=lay, show=true, size=(1400,1000))
    plot!(subplot=1, scintPhotonsHisto, title="# scintillating photons/event", xlabel="# photons", show=true)
    plot!(subplot=2, siHitsHisto, title="# hits in Silicon/event", xlabel="# hits")
    plot!(subplot=3, crysEdepHisto, title="energy deposited in crystal", xlabel="keV")
end

#---User actions and sentivive detectors-----------------------------------------------------------
include(joinpath(@__DIR__, "UserActions.jl"))

#--------------------------------------------------------------------------------------------------
#---Create the Application-------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------
app = G4JLApplication(; detector = crysdet,                           # detector with parameters
                        simdata = ScintSimData(),                     # simulation data structure
                        generator = particlegun,                      # primary particle generator
                        nthreads = 0,                                 # # of threads (0 = no MT)
                        physics_type = ScintPhysicsList,              # what physics list to instantiate
                        stepaction_method = stepping,                 # step action method
                        begineventaction_method = beginevent,         # begin-event action (initialize per-event data)
                        endeventaction_method = endevent,             # end-event action (fill histograms per event)
                        beginrunaction_method = beginrun,             # begin run action
                        endrunaction_method = endrun,                 # end run action
                        sdetectors = ["si_log" => silicon_SD,
                                      "cebr3_log" => crystal_SD]      # mapping of LVs to SDs (+ means multiple LVs with same name)
                      );

#---Configure, Initialize and Run------------------------------------------------------------------
configure(app)
initialize(app)

#ui`/tracking/verbose 1`
beamOn(app,1000)

do_plot(app.simdata[1])

