![Geant4](docs/src/assets/logo.png)

[![Dev](https://img.shields.io/badge/docs-dev-blue.svg)](https://juliahep.github.io/Geant4.jl/dev/)
[![Build Status](https://github.com/JuliaHEP/Geant4.jl/workflows/CI/badge.svg)](https://github.com/JuliaHEP/Geant4.jl/actions)
[![Codecov](https://codecov.io/gh/JuliaHEP/Geant4.jl/branch/master/graph/badge.svg)](https://codecov.io/gh/JuliaHEP/Geant4.jl)

Julia bindings for the [Geant4](https://geant4.web.cern.ch) toolkit, which simulates the passage of particles through matter.

Geant4.jl gives you two ways to work with Geant4 from Julia:

- **The Geant4 C++ classes.** They are wrapped with [CxxWrap.jl](https://github.com/JuliaInterop/CxxWrap.jl), and the wrapper code is generated automatically with [WrapIt](https://github.com/grasph/wrapit). You can call them in much the same way as you would in C++.
- **A Julia interface**, made of types prefixed with `G4JL`. With it, you describe a whole application (detector, physics, primary generator, user actions, sensitive detectors, scoring) as a `G4JLApplication`, and you write the callbacks as plain Julia functions.

The Geant4 libraries and data files come from the binary package [Geant4_jll](https://github.com/JuliaBinaryWrappers/Geant4_jll.jl), so you don't need a local Geant4 installation. The current release uses Geant4 11.4.

## Installation

Geant4.jl is registered in the Julia General registry:

```julia
julia> using Pkg
julia> Pkg.add("Geant4")
```

The first installation downloads the Geant4 libraries and data files, which can take a while.

## Quick start

This example shoots 1 GeV electrons into a box of water and reports how much energy is deposited:

```julia
using Geant4, Geant4.SystemOfUnits

# Detector: a box of water inside a world volume of air
struct WaterBox <: G4JLDetector
    halfsize::Float64
end

function construct(det::WaterBox)::CxxPtr{G4VPhysicalVolume}
    nist  = G4NistManager!Instance()
    air   = FindOrBuildMaterial(nist, "G4_AIR")
    water = FindOrBuildMaterial(nist, "G4_WATER")
    s = det.halfsize
    worldLV = G4LogicalVolume(move!(G4Box("World", 1.2s, 1.2s, 1.2s)), air, "World")
    worldPV = G4PVPlacement(nothing, G4ThreeVector(), worldLV, "World", nothing, false, 0)
    boxLV   = G4LogicalVolume(move!(G4Box("Box", s, s, s)), water, "Box")
    G4PVPlacement(nothing, G4ThreeVector(), boxLV, "Box", worldLV, false, 0)
    return worldPV
end
Geant4.getConstructor(::WaterBox) = construct

# Simulation data: the total deposited energy
mutable struct EdepData <: G4JLSimulationData
    edep::Float64
end

# Stepping action: accumulate the energy deposited in each step
function stepping(step::G4Step, app::G4JLApplication)::Nothing
    getSIMdata(app).edep += GetTotalEnergyDeposit(step)
    return
end

app = G4JLApplication(detector = WaterBox(20cm),
                      simdata = EdepData(0.),
                      generator = G4JLGunGenerator(particle = "e-", energy = 1GeV,
                                                   position = G4ThreeVector(0, 0, -23cm),
                                                   direction = G4ThreeVector(0, 0, 1)),
                      physics_type = FTFP_BERT,
                      stepaction_method = stepping)
configure(app)
initialize(app)
beamOn(app, 100)
println("Mean deposited energy per event: ", app.simdata[1].edep / 100 / MeV, " MeV")
```

## Documentation

The [documentation](https://juliahep.github.io/Geant4.jl/dev/) includes:

- a user guide to the `G4JLApplication` interface: detectors, physics lists, fields, primary generators, user actions, sensitive detectors, scoring, multi-threading and visualization
- the API reference
- a set of examples, rendered together with their output

For Geant4 itself, see the [Application Developer Guide](https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/index.html) and the [class reference](https://geant4.kek.jp/Reference/11.4.1/index.html).

## Examples

The examples are in a separate repository, [G4Examples.jl](https://github.com/JuliaHEP/G4Examples.jl), because they need additional packages for plotting and visualization (Makie, Plots, FHist, ...). They are ports of the Geant4 basic, extended and advanced examples. To set them up:

```bash
git clone https://github.com/JuliaHEP/G4Examples.jl.git
cd G4Examples.jl
julia --project=. -e 'import Pkg; Pkg.instantiate()'
julia --project=. basic/B1/B1.jl
```

Each example is also available as a Jupyter notebook.

## Development

Run the tests with:

```bash
julia --project=. -e 'import Pkg; Pkg.test()'
```

The C++ wrapper library normally comes from the binary package [Geant4_julia_jll](https://github.com/JuliaBinaryWrappers/Geant4_julia_jll.jl). To wrap additional Geant4 classes, you can regenerate and build the wrappers locally. This needs [WrapIt](https://github.com/grasph/wrapit), which in turn needs `libclang`. When a local build exists in `gen/build`, Geant4.jl loads it in preference to the binary package. For details, see [Building the wrapper code](https://juliahep.github.io/Geant4.jl/dev/development/) in the documentation.
