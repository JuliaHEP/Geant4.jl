# Geant4.jl

Julia bindings for the [Geant4](https://geant4.web.cern.ch) toolkit, which simulates the passage of particles through matter.

Geant4.jl gives you two ways to work with Geant4 from Julia:

- **The Geant4 C++ classes.** They are wrapped with [CxxWrap.jl](https://github.com/JuliaInterop/CxxWrap.jl). Geant4 is too large to wrap by hand, so the wrapper code is generated automatically with [WrapIt](https://github.com/grasph/wrapit), which uses the clang library.
- **A Julia interface**, made of types prefixed with `G4JL`. With it, you describe a whole application as a [`G4JLApplication`](@ref), and you write detector construction, user actions, sensitive detectors and field maps as plain Julia functions. The `G4JL` prefix tells these types apart from the wrapped C++ classes.

This documentation covers what is specific to Julia. For the Geant4 concepts themselves, see the [Application Developer Guide](https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/index.html), and see the [class reference](https://geant4.kek.jp/Reference/11.4.1/index.html) for the details of each C++ class.

## Installation

Geant4.jl is registered in the Julia General registry:

```julia
julia> using Pkg
julia> Pkg.add("Geant4")
```

The Geant4 libraries and data files come from the binary package [Geant4\_jll](https://github.com/JuliaBinaryWrappers/Geant4_jll.jl), so you don't need a local Geant4 installation. The first installation downloads the data files, which can take a while. To use data files you already have, set the environment variable `GEANT4_DATA_DIR` to their location before loading the package.

The visualization and histogram functions are package extensions. They are activated when you load [Makie](https://docs.makie.org) (`CairoMakie` or `GLMakie`) or [FHist](https://github.com/Moelf/FHist.jl), respectively.

## Quick start

This example shoots 1 GeV electrons into a box of water and reports how much energy is deposited. The [User Guide](@ref) explains each part.

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

## Using the C++ classes from Julia

All wrapped Geant4 classes are exported. Their names start with `G4`, so they are unlikely to clash with other Julia names.

```julia-repl
julia> using Geant4

julia> runManager = G4RunManager()
**************************************************************
 Geant4 version Name: geant4-11-04-patch-01 [MT]   (13-March-2026)
                       Copyright : Geant4 Collaboration
                      References : NIM A 506 (2003), 250-303
                                 : IEEE-TNS 53 (2006), 270-278
                                 : NIM A 835 (2016), 186-225
                             WWW : http://geant4.org/
**************************************************************

julia> String(GetVersionString(runManager))
"  Geant4 version Name: geant4-11-04-patch-01 [MT]   (13-March-2026)"
```

These conventions map C++ to Julia:

| C++ | Julia |
|:----|:------|
| `runManager->GetVersionString()` | `GetVersionString(runManager)`. The object is the first argument. |
| `G4NistManager::Instance()` | `G4NistManager!Instance()`. A `!` replaces `::` in static methods and namespaces. |
| `CLHEP::Hep3Vector` | `G4ThreeVector` (or `CLHEP!Hep3Vector`) |
| `G4VSolid*` | `CxxPtr{G4VSolid}` |
| `const G4Track&` | `ConstCxxRef{G4Track}`. Use `x[]` to get the object behind a pointer or reference. |
| `G4String` | Convert with `String(s)` |
| `UImanager->ApplyCommand("/run/verbose 1")` | The `ui` string macro (see [The application](@ref)) |

Because of multiple dispatch, you don't need to qualify methods with the module name, even for common names such as `mag`:

```julia-repl
julia> v = G4ThreeVector(1,2,3)
G4ThreeVector(1.0,2.0,3.0)

julia> mag(v)
3.7416573867739413
```

To list all the methods available for a class, use `methodswith(G4RunManager, supertypes=true)`.

### Units and physical constants

The Geant4 system of units and the physical constants are in two submodules:

```julia
using Geant4.SystemOfUnits
using Geant4.PhysicalConstants
```

`Geant4.SystemOfUnits` exports only the most common units (`mm`, `cm`, `m`, `MeV`, `GeV`, `ns`, `deg`, `tesla`, ...). Import any others explicitly:

```julia
import Geant4.SystemOfUnits: candela, volt, kilovolt
```

Numeric literals give a compact notation: `20cm`, `3GeV` or `360deg`.

### Object ownership

Julia's garbage collector deletes C++ objects created from Julia once nothing references them. Geant4, however, often takes ownership of the objects passed to it, and then deletes them itself. To avoid deleting an object twice, use [`move!`](@ref) to hand ownership over to Geant4:

```julia
trackerLV = G4LogicalVolume(move!(G4Tubs("tracker", 0, 10cm, 50cm, 0, 360deg)), air, "Tracker")
```

Some classes are owned by Geant4 by default: `G4PVPlacement`, `G4LogicalVolume`, `G4PVReplica`, `G4Material`, `G4Isotope` and `G4Element`. You don't need `move!` for those.

## Where to go next

- The [User Guide](@ref) describes each part of a `G4JLApplication`.
- The [Examples](@ref "Running the examples") are ported from the Geant4 basic, extended and advanced examples. Each page shows the code together with its output.
- The [Public API](@ref) lists all `G4JL` types and functions.
- [Development](@ref) explains how to regenerate the C++ wrappers and build this documentation.
