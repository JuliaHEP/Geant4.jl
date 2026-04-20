using Geant4
using Geant4.SystemOfUnits
using Plots

mutable struct RE03Detector <: G4JLDetector
    const worldXY::Float64
    const worldZ::Float64
    const phantomXY::Float64
    const phantomZ::Float64
    RE03Detector(;worldXY=100cm, worldZ=300cm, phantomXY=30.5cm, phantomZ=30cm) = new(worldXY, worldZ, phantomXY, phantomZ)
end

function construct(det::RE03Detector)::CxxPtr{G4VPhysicalVolume}
    ##---Materials----------------------------------------------------------------------------------
    nist = G4NistManager!Instance()
    fAir = FindOrBuildMaterial(nist, "G4_AIR")
    fWater = FindOrBuildMaterial(nist, "G4_WATER")

    ##---World--------------------------------------------------------------------------------------
    worldSolid = G4Box("World",det.worldXY/2, det.worldXY/2, det.worldZ/2)
    worldLogical = G4LogicalVolume(worldSolid,fAir,"World")
    worldPhys = G4PVPlacement(nothing, G4ThreeVector(), worldLogical, "World", nothing,false,0)

    ##---Phantom------------------------------------------------------------------------------------
    phantomSolid = G4Box("Phantom", det.phantomXY/2, det.phantomXY/2, det.phantomZ/2)
    phantomLogical = G4LogicalVolume(phantomSolid, fWater, "Phantom");
    phantomPhys = G4PVPlacement(nothing, G4ThreeVector(), phantomLogical, "Phantom", worldLogical, false, 0)

    ##---Visualization attributes-------------------------------------------------------------------
    SetVisAttributes(worldLogical, G4VisAttributes!GetInvisible())
    simpleBoxVisAtt = G4VisAttributes(G4Colour(1.0, 1.0, 1.0))
    SetVisibility(simpleBoxVisAtt, true)
    SetVisAttributes(phantomLogical, simpleBoxVisAtt)

    return worldPhys
end
Geant4.getConstructor(::RE03Detector)::Function = construct

mutable struct MedicalBeamData <: G4JLGeneratorData
    particleName::String
    particlePtr::CxxPtr{G4ParticleDefinition}
    energy::Float64
    ssd::Float64
    fieldXY::Float64
    surfaceZ::Float64
  end

  function generateBeamDir(ssd::Float64, fxy::Float64)
    dr = √2/2*fxy
    R = √(ssd^2 + dr^2)
    cos0 = ssd/R
    xymax = fxy/ssd/2
    dx = dy = dz = 0.
    while true
      dz = rand()*(1-cos0)+ cos0
      dsin = √(1-dz^2)
      dphi = rand()*2π
      dx = dsin * cos(dphi)
      dy = dsin * sin(dphi)
      if abs(dx) < xymax*dz && abs(dy) < xymax*dz
        break
      end
    end
    G4ThreeVector(dx, dy, dz)
  end

  function MedicalBeam(;particle="e-", energy=10MeV, ssd=100cm, fieldXY=10cm)
    data = MedicalBeamData(particle, CxxPtr{G4ParticleDefinition}(C_NULL), energy, ssd, fieldXY, 0.)
    function init(data::MedicalBeamData, app::G4JLApplication)
      data.particlePtr = FindParticle(data.particleName)
      data.surfaceZ = -app.detector.phantomZ/2
    end
    function generate( evt::G4Event, data::MedicalBeamData)::Nothing
      mass = data.particlePtr |> GetPDGMass
      momemtum = √((mass + data.energy)^2 - mass^2)
      pvec = momemtum * generateBeamDir(data.ssd, data.fieldXY);
      primary = G4PrimaryParticle(data.particlePtr, pvec |> x, pvec |> y, pvec |> z )
      vertex = G4PrimaryVertex(G4ThreeVector(0, 0, data.surfaceZ - data.ssd), 0ns)
      SetPrimary(vertex, move!(primary))    # note that we give up ownership of the objects just created
      AddPrimaryVertex(evt, move!(vertex))  # note that we give up ownership of the objects just created
    end
    G4JLPrimaryGenerator("MedicalBeam", data; init_method=init, generate_method=generate)
  end
  function SetParticleByName(gen::G4JLPrimaryGenerator{MedicalBeamData}, particle::String)
    gen.data.particleName = particle
    gen.data.particlePtr = FindParticle(particle)
    return
  end
  function SetParticleEnergy(gen::G4JLPrimaryGenerator{MedicalBeamData}, energy::Float64)
    gen.data.energy = energy
    return
  end;

sc1 = G4JLScoringMesh("boxMesh_1",
                      BoxMesh(15.25cm, 15.25cm, 15cm),
                      bins = (61, 61, 150),
                      quantities = [ doseDeposit("dose") ]
                      );

app = G4JLApplication(;detector = RE03Detector(),                    # detector with parameters
                       generator = MedicalBeam(),                    # promary partcile generator
                       nthreads = 8,                                 # define the number of threads
                       physics_type = FTFP_BERT,                     # what physics list to instantiate
                       scorers = [sc1]                               # list of scorers
                      );

configure(app)
initialize(app)
beamOn(app, 0)

function do_plots(sc)
    dose, dose2, nentry = sc.dose
    xaxisvalues = range(0., sc.mesh.dx*2/cm, sc.bins[1])
    zaxisvalues = range(0., sc.mesh.dz*2/cm, sc.bins[3])
    cbin = round(Int, (sc.bins[1]+1)/2)
    fig = plot( layout=(2,1), size=(800,800),
                heatmap(zaxisvalues, xaxisvalues, dose[cbin,:,:], title="Dose (XZ)", color=:thermal, xlabel="Z (cm)", ylabel="X (cm)"),
                plot(zaxisvalues, dose[cbin,cbin,:], title="Depth Dose (center)", xlabel="Z (cm)", label="dose")
    )
    display("image/png, fig)
end

SetParticleByName(app.generator, "e-")
SetParticleEnergy(app.generator, 20MeV)
beamOn(app, 100000)
do_plots(sc1)

SetParticleByName(app.generator, "proton")
SetParticleEnergy(app.generator, 200MeV)
beamOn(app, 100000)
do_plots(sc1)

SetParticleByName(app.generator, "C12")
SetParticleEnergy(app.generator, 3GeV)

beamOn(app, 100000)
do_plots(sc1)
