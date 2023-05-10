# Geant4.jl

Julia bindings for the [Geant4](https://geant4.web.cern.ch) particle transportation toolkit. It is using [CxxWrap.jl](https://github.com/JuliaInterop/CxxWrap.jl) package to wrap C++ types and functions to Julia. Since the Geant4 toolkit is rather large and complex, writing the wrapper code by hand is not really an option. For this we use the package [WrapIt](https://github.com/grasph/wrapit) that automates the generation of the wrapper code making use of the clang library.

Documentation of the concepts and how to write applications with the Geant4 toolkit can be found with the [Application Developer Guide](https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/index.html) or the [Classes and Members reference guide](https://geant4.kek.jp/Reference/v11.1.1/index.html) for a detailed description of each C++ class. In this document we will only highlight the differences between the Julia and the C++ API. We will document the additional types that have been added on top of the C++ classes to make the user interface more Julia friendly. To distinguish these new types from the types coming directly from C++ via the CxxWrap wrappers, these types are prefixed with `G4JL`.

## Getting started
Import the `Geant4` module. All the wrapped Geant4 classes are exported since they are prefixed by `G4` minimizing the chances of a name clash with other Julia symbols. 
```julia-repl

julia> using Geant4
julia> runManager = G4RunManager()
**************************************************************
 Geant4 version Name: geant4-11-01-patch-01 [MT]   (10-February-2023)
                       Copyright : Geant4 Collaboration
                      References : NIM A 506 (2003), 250-303
                                 : IEEE-TNS 53 (2006), 270-278
                                 : NIM A 835 (2016), 186-225
                             WWW : http://geant4.org/
**************************************************************

Geant4.G4RunManagerAllocated(Ptr{Nothing} @0x00007f9fcb6f9c50)

julia> methodswith(G4RunManager, supertypes=true)
[1] convert(t::Type{G4RunManager}, x::T) where T<:G4RunManager in Geant4 at /Users/mato/.julia/packages/CxxWrap/IdOJa/src/CxxWrap.jl:676
[2] AbortEvent(arg1::Union{CxxWrap.CxxWrapCore.CxxRef{<:G4RunManager}, Union{CxxWrap.CxxWrapCore.SmartPointer{T2}, T2} where T2<:G4RunManager}) in Geant4 at /Users/mato/.julia/packages/CxxWrap/IdOJa/src/CxxWrap.jl:618
...
[94] rndmSaveThisRun(arg1::Union{CxxWrap.CxxWrapCore.CxxRef{<:G4RunManager}, Union{CxxWrap.CxxWrapCore.SmartPointer{T2}, T2} where T2<:G4RunManager}) in Geant4 at /Users/mato/.julia/packages/CxxWrap/IdOJa/src/CxxWrap.jl:618

julia> v = GetVersionString(runManager)
ConstCxxRef{G4String}(Ptr{G4String} @0x00007ffed34df2d8)

julia> String(v)
" Geant4 version Name: geant4-11-01-patch-01 [MT]   (10-February-2023)"
```
Note that class methods are called with the object instance as first argument. In C++ the `GetVersionString` method would be called as `runManager->GetVersionString()` while in Julia it is called as `GetVersionString(runManager)`. Thanks to the Julia multi-dispatch we do not need to prefix the methods with the module name `Geant4.GetVersionString(runManager)`, even for very common function names such as `mag`.
```julia-repl
julia> v = G4ThreeVector(1,2,3)
Geant4.CLHEP!Hep3VectorAllocated(Ptr{Nothing} @0x00007f9fcaf2a710)

julia> mag(v)
3.7416573867739413
```

## G4 Julia interface
The main goal for defining a Geant4 application in the Julia interface is to create an instance of the [`G4JLApplication`](@ref) type, where all the needed elements for running a Geant4 application are declared, such as the detector geometry, the physics list, the primary particle generator, the type of run manager, the user actions, etc. These are the needed elements:
- **detector**. An instance of a detector structure inheriting from the abstract type `G4JLDetector`, in which all the detector parameters are defined. The user should also provide a method specialization of `Geant4.getConstructor(::G4JLDetector)::Function` to return the Julia function that toolkit needs to call in order to construct the geometry and return the pointer of the 'world' physical volume. There is no default.
- **simdata**. An instance of the simulation data structure that the program will need to collect during the simulation execution. This mutable structure needs to inherit from the abstract type `G4JLSimulationData` and is completely user defined with counters, data structures to collect the hits or doses, histograms, etc. The default is and instance of `G4JLNoData`.
- **runmanager_type**. C++ type of the required G4 run manager[`G4RunManager`, `G4MTRunManager`, `G4TaskRunManager`]. The default is the serial `G4RunManager`.
- **physics_type**. The physics list predefined type. Default is `FTFP_BERT`.
- **generator_type**. The primary generator generator type. The default is `G4JLParticleGun`, which encapsulates a `G4ParticleGun`. The underlying `G4ParticleGun` can be obtained by calling `GetGun()`.
- **user actions**. Julia methods defining the different possible user actions (e.g. stepping action, tracking action, run action, event action). The default is no action.
- **sdetectors**. List of sensitive detectors. This is given as a `Vector` of pairs `lv::String => sd::G4JLSensitiveDetector` to associate logical volumes by name to sensitive detector instances (see next section).

Once the `G4JLApplication` is instantiated (and implicitely an instance of the `G4RunManager` created), the user can control the application with the following commands:
- `configure(::G4JLApplication)`. It associates the physics list, generator and user actions to the selected `G4RunManager` instance. 
- `initialize(::G4JLApplication)`. It basically calls the `Initialize()` method of the run manager and associate the declared sensitive detectors.
- `reinitialize(::G4JLApplication, ::G4JLDetector)`. It re-defines the declared detector geometry with a new instance of `G4JLDetector`. 
- ` beamOn(::G4JLApplication, ::Int)`. Starts a run with a given number of events.

### Constructing the detector
Parameters of the detector are collected in a user defined mutable data structure inheriting from `G4JLDetector`. The user also needs to provide a Julia method for constructing the geometry. This method needs to have the signature `(::G4JLDetector)::CxxPtr{G4VPhysicalVolume}`. The only argument give access to the structure with all the detector parameters.
!!! note
    The type `CxxPtr{G4VPhysicalVolume}` denotes a C++ pointer to the `G4VPhysicalVolume` type.
The user can use the native G4 classes for constructing the geometry such as the different type of solids (e.g. G4Box, G4Tubs, etc.), `G4LogicalVolume`, `G4PVPlacement`, `G4PVReplica`, etc. Alternatively can the type [`G4JLDetectorGDML`](@ref) to construct a detector from a GDML file.

!!! note
    Note that by default constructed C++ objects from Julia would get automatically deleted by the Julia garbage collector (GC) since a `finalizer` gets installed to the wrapper classes. This is particularly a problem when constructing the geometry.
  
Currently for the following classes have the `finalizer` disabled in the wrapper: `G4PVPlacement`, `G4LogicalVolume`, `G4PVReplica`, `G4Material`, `G4Isotope`, `G4Element`. This means that instances of them will not be deleted by Julia to avoid double deletion (crash) when the geometry gets deleted at the finalization of the application from the C++ side. 

A pointer to any of the `G4Solid` needs to be passed to the `G4LogicalVolume` using [`move!(objref)`](@ref) function to transfer the ownership of the referenced object to the C++ side. See the following example:
```julia
trackerS = G4Tubs("tracker", 0, trackerSize, trackerSize, 0, 360deg)
trackerLV = G4LogicalVolume(move!(trackerS), m_air, "Tracker")
G4PVPlacement(nothing,              # no rotation
    G4ThreeVector(0,0,0),           # at (0,0,0)
    trackerLV,                      # its logical volume
    "Tracker",                      # its name
    worldLV,                        # its mother  volume
    false,                          # no boolean operations
    0,                              # copy number
    checkOverlaps)                  # checking overlaps
```
### User Actions
User actions are native Julia functions that are callbacks of the Geant4 toolkit. They are declared in the constructor of `G4JLApplication`, so they do not need to be associated to a specific function name. All user actions receive a reference to the `G4JLApplication` from which the user can obtain details of the actual application, such as the current detector, the physics, the generator, or the running simulation data. The following are the currently defined possible user actions:
- **stepping action**. Called on each simulation step. The signature is `(::G4Step, ::G4JLApplication)::Nothing`. Consult the [G4Step](https://geant4.kek.jp/Reference/v11.1.1/classG4Step.html) reference manual to see what you can get from it. 
- **pre-tracking action**. Called at the creation of a new participle being tracked. The signature is `(::G4Track, ::G4JLApplication)::Nothing`. Consult the [G4Step](https://geant4.kek.jp/Reference/v11.1.1/classG4Track.html) reference manual to see what you can get from it.
- **post-tracking action**. Called at the end of the particle being tracked. The signature is `(::G4Track, ::G4JLApplication)::Nothing`. Consult the [G4Track](https://geant4.kek.jp/Reference/v11.1.1/classG4Track.html) reference manual to see what you can get from it.
- **begin-event action**. Called at the begining of each event. The signature is `(::G4Event, ::G4JLApplication)::Nothing`. Consult the [G4Event](https://geant4.kek.jp/Reference/v11.1.1/classG4Event.html) reference manual to see what you can get from it.
- **end-event action**. Called at the end of each event. The signature is `(::G4Event, ::G4JLApplication)::Nothing`. Consult the [G4Event](https://geant4.kek.jp/Reference/v11.1.1/classG4Event.html) reference manual to see what you can get from it.
- **begin-run action**. Called at the begining of a run. The signature is `(::G4Run, ::G4JLApplication)::Nothing`. Consult the [G4Run](https://geant4.kek.jp/Reference/v11.1.1/classG4Run.html) reference manual to see what you can get from it.
- **end-run action**. Called at the end of a run. The signature is `(::G4Run, ::G4JLApplication)::Nothing`. Consult the [G4Run](https://geant4.kek.jp/Reference/v11.1.1/classG4Run.html) reference manual to see what you can get from it.

### Sensitive Detectors
The user can define sensitive detectors by defining a data structure and 3 callback functions, which will initialise, fill and dispose the defined data structure. Later, the instantiated sensitive detector would be associated to one or more logical volumes of the detector setup. Instantiating a `G4JLSensitiveDetector` will require the following arguments:
- **name**. A string to identify the sensitive detector. No default.
- **sd data**. A instance of a user defined `G4JLSDData` mutable data structure that will passed to each callback invocation.
- **initialize method**. User method that is called at the beginning of each event. The signature is `(::B2aSDData, ::G4HCofThisEvent)::Nothing`.
- **endOfEvent method**. User method that is called at the end of each event. The signature is `(::B2aSDData, ::G4HCofThisEvent)::Nothing`.
- **processHits method**. User method that is called at simulation step that ends at the associated logical volume. The signature is `(::B2aSDData, ::G4Step, ::G4TouchableHistory)::Bool`. Consult the [G4Step](https://geant4.kek.jp/Reference/v11.1.1/classG4Step.html) reference manual to see what you can get from the G4Step. It returns true if a true hit is generated. 

## Examples

### basic/B1 
This is most basic example. For this example we have kept the interface closer to the native C++ interface. The only difference with respect the C++, is that that we need to instantiate a `G4JLDetectorConstruction` with the Julia function that will be callback to construct the detector geometry as argument. This is becauase we cannot inherit from Julia the C++ class `G4VUserDetectorConstruction`, which is the way foreseen in the native Geant4 toolkit to provide the specific user detector geometry. Similarly, for the user actions and primary particle generator we need to instantiate a `G4JLActionInitialization`. The interaction with the application is done with the `G4UImanager`. 

To run it execute
```
julia --project=. examples/basic/B1/B1.j
```
or execute the notebook `examples/basic/B1/B1.ipynb`
### basic/B2a
This example fills a vector of `TrackerHit` that is stored in the `B2aSDData` simulation data structure for each event. This is achieved with a sensitive detector associated to the `Chamber` logical volume. The example is using the high-level Julia interface with the instantiation of a `G4JLApplication` declaring all the elements of the application (geometry, physics, simulation data, user actions, etc.)

To run it execute
```
julia --project=. examples/basic/B2/B2a.jl
```
### extended/RE03
This example makes use of the built-in scoring capability of Geant4 with a new Julia API interface creating an instance of `G4JLScoringMesh`, instead of using the native Geant4 UI. The user defines a scoring mesh, and quantities to be collect and gets the results after the run. 

To run it execute
```
julia --project=. examples/extended/RE03/RE03.jl
```
### WaterPhantom
This example is similar to RE03 but it defines a custom primary particle generator (`MedicalBeam`) instead of using the predefined particle gun generator (`G4JLGunGenerator`). It is a notebook and produces plots after each run.   
To run it execute
```
jupyter notebook examples/WaterPhantom/WaterPhantom.ipynb
```

### TestEm3
This example comes from *extended/electromagnetic/TestEm3* example. Since it requires additional packages such as `FHist` for histograms and `Plots` for their visualisation, it has its own Julia environment in the folder `examples/TestEm3`. It uses the Julia high-level interface with the instantiation of a `G4JLApplication` declaring all the elements of the application.

To run it execute
```
julia --project=examples/TestEm3 -i examples/TestEm3/TestEm3.jl
``` 

## Visualization examples
The Geant4.jl project includes additional functionality for visualization under the directory G4Visualization. This is done in a different directory to separate the dependencies. 

### B1vis.jl
This example uses the `GLMakie` backend (GL) of Makie. The use may change to other backends depending on his/her setup. To visualize the B1 detector do:
```
julia --project=G4Visualization -i  G4Visualization/examples/B1vis.jl
```
!!! note  
    Note the option `-i` to keep the interactive session open

### B2aVis.jl
This example to visualize the detector and (a very simplistic) visualization of one event.
```
julia --project=G4Visualization -i  G4Visualization/examples/B2avis.jl
```

## Building the wrapper code
We use the Geant4 native binary libraries and data from the binary package [Geant4\_jll](https://github.com/JuliaBinaryWrappers/Geant4_jll.jl), which has been produced with the `BinaryBuilder` [recipe](https://github.com/JuliaPackaging/Yggdrasil/tree/master/G/Geant4). The wrapper library is downloaded from the binary package [Geant4\_julia\_jll](https://github.com/JuliaBinaryWrappers/Geant4_julia_jll.jl).

We have the possibility during the development of this package to re-generate locally new C++ wrapper code. For this we need to have `wrapit` installed, which itself requires `libclang` to be installed. If the executable is not found (not in the PATH), we can use the wrapper code that is already pre-generated and distributed with this package.
- what C++ classes get wrapped is controlled by the file `gen/Geant4.wit`. See the documentation of WrapIt for the details. 
- run the `gen/build.jl` script generate the wrapper code (if wrapit found) and build the wrapper library.

!!! note
    Please note that compiling the single generated wrapper file takes very long. This is due to the current implementation of WrapIt that places all wrapped types in a single file. This may change in the future.

Once the wrapper code is stabilized we move the generated code to the repository [Geant4\_cxxwrap](https://github.com/peremato/Geant4_cxxwrap) to regenerate the binary package `Geant4_julia_jll` using the `BinaryBuilder`.
