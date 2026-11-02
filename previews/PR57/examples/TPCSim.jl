using Geant4
using Geant4.SystemOfUnits
using Parameters
using PYTHIA8

# to force loading G4Vis extension we need to load the following modules
using GLMakie
using PYTHIA8: px, py, pz

using Geant4.SystemOfUnits: m, cm, mole,cm3

@with_kw mutable struct AlephTPC <: G4JLDetector
    totalL::Float64 = 4.4m      # total length of the TPC
    innerR::Float64 = 0.31m     # inner radius of the TPC
    outerR::Float64 = 1.8m      # outer radius of the TPC
    checkOverlaps::Bool = false # do check overlaps when creating the geometry
end

function construct(det::AlephTPC)::CxxPtr{G4VPhysicalVolume}
    (; totalL, innerR, outerR, checkOverlaps) = det

    ##---Materials----------------------------------------------------------------------------------
    nist = G4NistManager!Instance()
    m_Ar     = FindOrBuildMaterial(nist, "G4_Ar")
    m_CH₄    = FindOrBuildMaterial(nist, "G4_METHANE")
    ArCH₄  = G4Material("ArCH₄", 3.491*mg/cm3, 2)
    AddMaterial( ArCH₄, m_Ar, 0.91 )
    AddMaterial( ArCH₄, m_CH₄,0.09 )
    m_ArCH₄  = FindOrBuildMaterial(nist, "ArCH₄")
    m_air    = FindOrBuildMaterial(nist, "G4_AIR")
    m_Al     = FindOrBuildMaterial(nist, "G4_Al")

    ##---Volumes------------------------------------------------------------------------------------
    worldZHalfLength = 1.1 * totalL/2
    worldS  = G4Box("world", worldZHalfLength, worldZHalfLength, worldZHalfLength)
    worldLV = G4LogicalVolume(worldS, m_air, "World")
    worldPV = G4PVPlacement(nothing, G4ThreeVector(), worldLV, "World", nothing, false, 0, checkOverlaps)

    fcOuterS  = G4Tubs("fcOuter", outerR, outerR + 1.8cm, totalL/2, 0, 2π)
    fcOuterLV = G4LogicalVolume(fcOuterS, m_Al, "fcOuter")
    fcInnerS  = G4Tubs("fcInner", innerR - 0.8cm, innerR, totalL/2, 0, 2π)
    fcInnerLV = G4LogicalVolume(fcInnerS, m_Al, "fcInner")

    chamberS  = G4Tubs("chamber", innerR, outerR, totalL/2, 0, 2π)
    chamberLV = G4LogicalVolume(chamberS, m_ArCH₄, "chamber")
    G4PVPlacement(nothing, G4ThreeVector(), fcOuterLV, "fcOuter", worldLV, false, 0, checkOverlaps)
    G4PVPlacement(nothing, G4ThreeVector(), fcInnerLV, "fcInner", worldLV, false, 0, checkOverlaps)
    G4PVPlacement(nothing, G4ThreeVector(), chamberLV, "chamber", worldLV, false, 0, checkOverlaps)
    ##SetUserLimits(chamberLV, G4UserLimits(5mm))

    ##---Visualization attributes------------------------------------------------------------------
    boxVisAtt = G4VisAttributes(G4Colour(1.0, 1.0, 1.0, 0.0))
    chamberVisAtt = G4VisAttributes(G4Colour(0.0, 1.0, 1.0, 0.2))
    fcVisAtt = G4VisAttributes(G4Colour(0.0, 1.0, 0.0, 0.1))
    SetVisAttributes(worldLV, boxVisAtt)
    SetVisAttributes(chamberLV, chamberVisAtt)
    SetVisAttributes(fcInnerLV, fcVisAtt)
    SetVisAttributes(fcOuterLV, fcVisAtt)

    ##---Always return the physical world-------------------------------------------------------------
    return worldPV
end
Geant4.getConstructor(::AlephTPC)::Function = construct

tpc = AlephTPC()          # create the detector

bfield = G4JLUniformMagField(G4ThreeVector(0,0, 1.5tesla))

@with_kw mutable struct PythiaGenerator <: G4JLGeneratorData
    eCM::Float64 = 91.2*GeV
    pythia = nothing
end

function LEPCollision()
    data = PythiaGenerator()
    function LEPinit(data::PythiaGenerator, app::G4JLApplication)
        data.pythia = PYTHIA8.Pythia("", false)
        data.pythia << "Beams:idA = -11" # positron
        data.pythia << "Beams:idB = 11"  # electron
        data.pythia << "Beams:eCM = $(data.eCM/GeV)" # CM energy
        data.pythia << "PDF:lepton = off" # no lepton PDFs
        # Process: hadronic decays of Z0. Initialize. Histogram.
        data.pythia << "WeakSingleBoson:ffbar2gmZ = on"
        data.pythia << "23:onMode = off"
        data.pythia << "23:onIfAny = 1 2 3 4 5"
        # If Pythia fails to initialize, exit with error.
        data.pythia |> init || error("Pythia initialization failed")
    end
    function LEPgenerate(g4evt::G4Event, data::PythiaGenerator)::Nothing
        # Generate event. Skip if error. List first one.
        data.pythia |> next || return
        evt = data.pythia |> event
        # Define primary vertex
        vertex = G4PrimaryVertex(G4ThreeVector(0,0,0), 0)
        # Loop over the particles in the Pythia event
        for p in evt
            if isFinal(p)
                primary = G4PrimaryParticle(p |> PYTHIA8.id, px(p)*GeV, py(p)*GeV, pz(p)*GeV)
                SetPrimary(vertex, move!(primary))    ## note that we give up ownership of the objects just created
            end
        end
        AddPrimaryVertex(g4evt, move!(vertex))  ## note that we give up ownership of the objects just created
    end
    G4JLPrimaryGenerator("LEPCollision", data; init_method=LEPinit, generate_method=LEPgenerate)
end

const G4Vis = Base.get_extension(Geant4, :G4Vis)
function G4Vis.drawEvent(evtdisp::G4Vis.G4JLEventDisplay)
    s = evtdisp.lscene.scene
    settings = evtdisp.settings
    trajectories = G4EventManager!GetEventManager() |> GetConstCurrentEvent |> GetTrajectoryContainer
    if trajectories != C_NULL
        points = Point3{Float64}[]
        for t in trajectories
            t |> GetCharge == 0 && continue # skip neutral particles
            npoints = GetPointEntries(t)
            npoints < 3 && continue         # skip particles with less than 3 points
            for i in 1:npoints
                pos = GetPoint(t, i-1) |> GetPosition
                r = sqrt(pos[0]^2 + pos[1]^2)
                z = pos[2]
                (r > 1.8m || abs(z) > 2.4m) && break  # kill particle outside the TPC
                if r > 0.38m                # skip points inside the beam pipe
                    push!(points, convert(Point3{Float64}, pos))
                else
                    push!(points, Point3{Float64}(NaN, NaN, NaN))
                end
            end
            push!(points, Point3{Float64}(NaN, NaN, NaN))
        end
        lines!(s, points, color=settings.trajectories.color, transparency=false, overdraw=false)
    end
    ##wait_for_key("Press any key to continue with next event")
end
evtdisplay = G4JLEventDisplay(joinpath(@__DIR__, "TPCSimVisSettings.jl"))

app = G4JLApplication(detector     = tpc,                       # detector defined above
                      generator    = LEPCollision(),            # primary generator to instantiate
                      field        = bfield,                    # magnetic field
                      physics_type = FTFP_BERT,                 # what physics list to instantiate
                      evtdisplay   = evtdisplay                 # event display
                     );
configure(app)
initialize(app)

beamOn(app, 1)
display(evtdisplay.figure)

beamOn(app, 1)
display(evtdisplay.figure)
