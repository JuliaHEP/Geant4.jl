## Release Notes
### 0.2.x
- New Examples:
    - UserLib: how to build and call a user custom library providing additional Geant4 functionally that is not provided by the set of wrapped classes

### 0.2.0
- New Features
    - Adapted to CxxWrap 0.16
    - Changed `gen/build.jl` to generate the code first and then call `cmake` (not yet using WrapIt.jl package)
    - Added new example `advanced/AlephTPC` to integrate Geant4 with PYTHIA8
    - Changed the documentation to generate examples as markdown, as notebook and as julia script using the package Literate.jl 

### 0.1.17
- New Features
    - Added wrapper for G4StepLimiterPhysics
    
### 0.1.15
- Fixes:
    - Returned threadid is -2 for non-multithreaded builds of Geant4

### 0.1.14
- New Features:
    - Added function getfield(pos::G4ThreeVector, bfield::G4JLMagneticField)
    - Added G4JLEmptyDetector as default detector (for testing and tutorials)
    - build some protection to re-use physics lists in case re-creating an `G4JLApplication` 

### 0.1.13
- New Features:
    - Added wrappers for PhysicsLists classes: `G4DecayPhysics`, `G4EmStandardPhysics`, `G4RadioactiveDecayPhysics`
    - Implemented user stacking action
    - Added examples basic/B3a
### 0.1.12
- Moved the examples to new repository https://github.com/JuliaHEP/G4Examples.jl
- Fixes:
    - Veto CLHEP::HepRandomEngine::get to avoid clash with Base.get
    - Disable finalizer for class G4JLStateDependent. Fixes event display.

### 0.1.11
- Migrated to Julia 1.10
- Using the latest version of WrapIt to generate the CxxWrap wrappers
- New features
    - Added `G4JLGeneralParticleSource`, which makes use of the Geant4 `G4GeneralParticleSource` class for generation of primary particles for simulations. See documentation.
    - Added a new extension module `G4Hist` that defines convenient histogram types (H1D and H2D) on top of FHist.jl. See documentation. 
### 0.1.10
- New features
    - Provide an EventDisplay as a building block of the application. New `evtdisplay` argument in the constructor. 
    - Added new wrapped classes to support event displays: G4EventManager, G4TrajectoryContainer, G4VTrajectory, G4VTrajectoryPoint, G4StateManager, G4VStateDependent G4ApplicationState
### 0.1.9
- Changes needed for running ATLTileCalTB example 
### 0.1.8
- New features:
    - Added all example scripts as tests, so that the CI will systematically execute them.
    - Added new wrapped classes: G4LogicalVolumeStore, G4MaterialPropertiesTable, G4OpticalParameters, G4OpticalSurface, G4LogicalBorderSurface, G4LogicalSkinSurface, G4VProcess, G4ProcessType, G4Random, G4EmStandardPhysics_option4, G4OpticalPhysics, G4OpBoundaryProcess, G4ProcessManager, G4ProcessVector
    - Added `Geant4.PhysicalConstants` sub-module
    - Added testRandom to the test suite
    - Added `Scintillation` example with scintillating crystals and optical photons
- Fixes:
    - Fixed broken [visualization] examples
    - Improve HBC30 example to visualize trajectories in a more smooth manner. Moved it under `ext/G4Vis/examples`
### 0.1.7
- New features:
    - Support for ARM64 (MacOS M1). Implemented workaround for `closures` in `@safe_cfunction`, which were for supported in this  platform. 
    - Added support for magnetic field. Additional keyword argument in the `G4JLApplication`. Added example HBC30 for a simulation of a liquid hydrogen bubble chamber.
    - Added drawing capabilities for `G4Polyhedra`, `G4EllipticalTube`, `G4Ellipsoid`
- Fixes:
    - Fix example WaterPhantom to added to new callback closures
### 0.1.6
- New features:
    - Restructured G4Vis as an extension of Geant4.jl. It is automatically loaded when all the required weak dependencies are satisfied (e.g. "Makie", "Colors", "StaticArrays", "Rotations", "LinearAlgebra")
    - Added missing basic solids including the `BooleanSolid`
    - Using the `IGLWrap_jll` binary wrapper to `libigl` C++ library to draw boolean solids.
    - Added notebook `ext/G4Vis/Solids.ipynb` to exercise and draw all possible solids (some are still missing)
### 0.1.5
- New features:
    - Support for Multi-threading. New parameter in `G4JLApplication` to set the number of threads. Default is serial, `nthreads = 0`
    - Added verbosity level with the argument `verbose` in [`G4JLApplication`](@ref)
- Fixes:
    - Fix continuous pre-compilation after moving to Julia 1.9
    - Fix for embedded figures in notebooks
### 0.1.4
- Added support for scoring with `G4JLScoringMesh` function
- Added generation of documentation including running the jupyter notebooks
