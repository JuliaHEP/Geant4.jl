![Geant4](docs/src/assets/logo.png)


[![Dev](https://img.shields.io/badge/docs-dev-blue.svg)](https:///juliahep.github.io/Geant4.jl/dev/)
[![Build Status](https://github.com/JuliaHEP/Geant4.jl/workflows/CI/badge.svg)](https://github.com/JuliaHEP/Geant4.jl/actions)
[![Codecov](https://codecov.io/gh/JuliaHEP/Geant4.jl/branch/master/graph/badge.svg)](https://codecov.io/gh/JuliaHEP/Geant4.jl)

Julia bindings for the [Geant4](https://geant4.web.cern.ch) particle transportation toolkit. It is using [CxxWrap.jl](https://github.com/JuliaInterop/CxxWrap.jl) package to wrap C++ types and functions to Julia. Since the Geant4 toolkit is rather large and complex, writing the wrapper code by hand is not really an option. For this we use the package [WrapIt](https://github.com/grasph/wrapit) that automates the generation of the wrapper code making use of the clang library.

## Building the wrapper code
We use the Geant4 libraries and data from the binary package [Geant4_jll](https://github.com/JuliaBinaryWrappers/Geant4_jll.jl), which has been produced with the `BinaryBuilder` [recipe](https://github.com/JuliaPackaging/Yggdrasil/tree/master/G/Geant4). The wrapper library is downloaded from the binary package [Geant4_julia_jll](https://github.com/JuliaBinaryWrappers/Geant4_julia_jll.jl).    

In order to re-generate locally new C++ wrapper code we need to have `wrapit` installed, which itself requires `libclang` to be installed. If the executable is not found (not in the PATH), we can use the wrapper code that is already pre-generated and distributed with this package.
- what C++ classes get wrapped is controlled by the file `gen/Geant4.wit`. See the documentation of WrapIt for the details. 
- run the `gen/build.jl` script generate the wrapper code (if wrapit found) and build the wrapper library.

Once the wrapper code is stabilized we can move the generated code to the repository [Geant4_cxxwrap](https://github.com/peremato/Geant4_cxxwrap) to regenerate the binary package `Geant using the `BinaryBuilder`.

## Getting started
Import the `Geant4` module. All the wrapped Geant4 classes are exported since they are prefixed by `G4` minimizing the chances of a name clash with other Julia symbols. 
```julia

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
```julia
julia> v = G4ThreeVector(1,2,3)
Geant4.CLHEP!Hep3VectorAllocated(Ptr{Nothing} @0x00007f9fcaf2a710)

julia> mag(v)
3.7416573867739413
```

## Running the tests
To run the tests execute `julia --project . test/runtests.jl`

## Running the examples
For the time being there are only three examples: 
### basic/B1
This is most basic example using a more Geant4 native interface.  
To run it execute `julia --project=. examples/basic/B1/B1.j` or execute the notebook `B1.ipynb`
### basic/B2a
Basic example using a sensitive detector to collect 'hits'.  
To run it execute `julia --project=. examples/basic/B2/B2a.jl`
### extended/RE03
Example using the Geant4 built-in scoring mechanism.   
To run it execute `julia --project=. examples/basic/B2/B2a.jl`
### TestEm3
This example comes from *extended/electromagnetic/TestEm3* example. Since it requires additional packages such as FHist and Plots it has its own Julia environment in the folder `examples/TestEm3`. It is based on user actions.  
To run it execute `julia --project=examples/TestEm3 -i examples/TestEm3/TestEm3.jl` 
### WaterPhantom
Example in a notebook format similar to RE03 but with different primary particle generator (MedicalBeam) and using the scoring mechanism. Plots are produced after each run.
 
## Running the visualization examples
The project includes additional functionality for visualization under the directory G4Visualization. This is done in a different directory to separate the dependencies. To run the examples do:
- `julia --project=G4Visualization -i  G4Visualization/examples/B1vis.jl`
  
  Note the option `-i` to keep the interactive session open.






