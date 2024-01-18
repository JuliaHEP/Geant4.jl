using Geant4
using Geant4.PhysicalConstants
using Geant4.SystemOfUnits
using Geant4.SystemOfUnits: deg
using FHist
using Parameters
get = Base.get
using Plots

#---Choose the Makie backend
#using GLMakie
#using WGLMakie
#using CairoMakie
#using GeometryBasics, Rotations, IGLWrap_jll  # to force loding G4Vis extension

#---Detector construction--------------------------------------------------------------------------
include(joinpath(@__DIR__, "DetectorGPS.jl"))

# Cnstruct and draw the detector
#det = GPSDetector()
#world = construct(det)
#draw(world[])

#---Simulation Data--------------------------------------------------------------------------------
const nbins = 50
@with_kw mutable struct GPSSimData <: G4JLSimulationData
    hKEne     = H1D("Energy Spectrum", nbins, 0., 15., :MeV)
    hRad      = H1D("Radial ditribution", nbins, 0., 10., :cm)
    hAngcosθ  = H1D("Angular ditribution cosθ", nbins, -1., 1.)
    hAngϕ     = H1D("Angular distribution ϕ", nbins, 0.,360., :deg)
    hXYpos    = H2D("Source X-Y distribution", nbins, -10., 10., nbins, -10., 10., (:cm, :cm))
    hZXpos    = H2D("Source Z-X distribution", nbins, -10., 10., nbins, -10., 10., (:cm, :cm))
    hYZpos    = H2D("Source Y-Z distribution", nbins, -10., 10., nbins, -10., 10., (:cm, :cm))
    hcosθϕ    = H2D("Angular cos(θ)-ϕ distribution", nbins, -1., 1., nbins, 0., 360., (:nounit, :deg))
    hθϕ       = H2D("Angular θ-ϕ distribution", nbins, 0., 180., nbins, 0., 360., (:deg, :deg))
end
#---merge and empty functions----------------------------------------------------------------------
function Base.merge!(x::D, y::D) where D <: G4JLSimulationData
    for f in fieldnames(D)
        merge!(getfield(x,f), getfield(y,f))
    end
end
function Base.empty!(x::D) where D <: G4JLSimulationData
    for f in fieldnames(D)
        empty!(getfield(x,f))
    end
end
function do_plot(data::GPSSimData)
    img = Plots.plot(layout=(3,3), show=true, size=(1400,1000))
    for (i,fn) in enumerate(fieldnames(GPSSimData))
        h = getfield(data, fn)
        Plots.plot!(subplot=i, h.hist, title=h.title, show=true, cgrad=:plasma)
    end
    return img
end

#---Run Actions------------------------------------------------------------------------------------
function beginrun(::G4Run, app::G4JLApplication)::Nothing
    data = getSIMdata(app)
    empty!(data) 
    nothing
end
function endrun(::G4Run, app::G4JLApplication)::Nothing
    #---end run action is called for each workwer thread and the master one
    if G4Threading!G4GetThreadId() == -1   
        data = app.simdata[1]
        #---This is the master thread, so we need to add all the simuation results-----------------
        for d in app.simdata[2:end]
            merge!(data, d)
        end
    end
end
#---Tracking Actions-----------------------------------------------------------------------------
function pretrackaction(track::G4Track, app::G4JLApplication)::Nothing
    data = getSIMdata(app)
    ekin = track |> GetKineticEnergy
    vertex = track |> GetPosition
    direction = track |> GetMomentumDirection
    weight = track |> GetWeight

    x = vertex |> getX
    y = vertex |> getY
    z = vertex |> getZ
    θ = direction |> getTheta
    ϕ = direction |> getPhi
    ϕ < 0 &&  (ϕ += 2π)
    r = vertex |> mag
    dr = binedges(data.hRad.hist).step |> Float64
    dv = 4π * r^2 * dr

    # fill histograms
    push!(data.hKEne, ekin)
    push!(data.hRad, r, 1.0/dv)
    push!(data.hAngcosθ, cos(θ))
    push!(data.hAngϕ, ϕ)
    push!(data.hXYpos, x, y)
    push!(data.hZXpos, z, x)
    push!(data.hYZpos, y, z)
    push!(data.hcosθϕ, cos(θ), ϕ)
    push!(data.hθϕ, θ, ϕ)
    nothing
end

#---Particle Gun initialization--------------------------------------------------------------------
gps = G4JLGeneralParticleSource(particle = "geantino", 
                                energy = 10MeV, 
                                direction = G4ThreeVector(1,0,0), 
                                position = G4ThreeVector(1,2,1))

#---Create the Application-------------------------------------------------------------------------
app = G4JLApplication(detector = GPSDetector(),                   # detector with parameters
                      simdata = GPSSimData(),                     # simulation data structure
                      generator = gps,                            # primary particle generator 
                      nthreads = VERSION > v"1.9" ? 4 : 0,        # number of threads (MT)
                      physics_type = FTFP_BERT,                   # what physics list to instantiate
                      #----Actions--------------------------------
                      pretrackaction_method = pretrackaction,     # pre-tracking action
                      beginrunaction_method = beginrun,           # begin-run action (initialize counters and histograms)
                      endrunaction_method = endrun,               # end-run action (print summary)               
                      );

configure(app)
initialize(app)

beamOn(app,100000)
do_plot(app.simdata[1])

ui`/gps/particle geantino`
ui`/gps/pos/type Plane`
ui`/gps/pos/shape Square`
ui`/gps/pos/centre 1 2 1 cm`
ui`/gps/pos/halfx 2 cm`
ui`/gps/pos/halfy 2 cm`
ui`/gps/ang/type cos`
ui`/gps/ene/type Lin`
ui`/gps/ene/min 2 MeV`
ui`/gps/ene/max 10 MeV`
ui`/gps/ene/gradient 1`
ui`/gps/ene/intercept 1`

beamOn(app,100000)
do_plot(app.simdata[1])

