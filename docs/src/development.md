# Development

## How the package is built

Geant4.jl is made of three layers:

- [Geant4\_jll](https://github.com/JuliaBinaryWrappers/Geant4_jll.jl) provides the Geant4 libraries and data files. It is built with the [BinaryBuilder recipe](https://github.com/JuliaPackaging/Yggdrasil/tree/master/G/Geant4) in Yggdrasil, and there is a new version for each Geant4 release.
- [Geant4\_julia\_jll](https://github.com/JuliaBinaryWrappers/Geant4_julia_jll.jl) provides `libGeant4Wrap`, the C++ wrapper library. It is built from the generated code in the [Geant4\_cxxwrap](https://github.com/peremato/Geant4_cxxwrap) repository.
- This package loads the wrapper library with CxxWrap and adds the Julia interface (the `G4JL` types) on top of it.

## Running the tests

```bash
julia --project=. -e 'import Pkg; Pkg.test()'
```

The examples are not run by the tests. They are run in CI when the documentation is built.

## Regenerating the wrapper code

To wrap additional Geant4 classes, or to try changes to the wrappers, you can regenerate and build the wrapper library locally. This needs the [`wrapit`](https://github.com/grasph/wrapit) executable on your `PATH`, which in turn needs `libclang`.

- `gen/Geant4.wit.in` is the WrapIt configuration. It lists the Geant4 header files to wrap. Add header files there to wrap more classes.
- `gen/Geant4-veto.h` lists the classes and methods to exclude.
- `gen/cpp/` contains hand-written C++ code (the `G4JL*` helper classes) that is compiled into the wrapper library.
- `gen/build.jl` generates the code with WrapIt and builds the library in `gen/build`.

```bash
julia --project=gen -e 'import Pkg; Pkg.instantiate()'
julia --project=gen gen/build.jl
```

When `gen/build/lib` exists, `using Geant4` loads the local wrapper library instead of the one from `Geant4_julia_jll`, and prints a message to say so. Delete `gen/build` to go back to the binary package.

Once the wrappers are stable, the generated code is moved to [Geant4\_cxxwrap](https://github.com/peremato/Geant4_cxxwrap), and a new version of `Geant4_julia_jll` is built with BinaryBuilder.

## Building the documentation

The example pages are generated with [Literate.jl](https://github.com/fredrikekre/Literate.jl) from the `.lit` files in `docs/src/examples`, which are copies of the sources in [G4Examples.jl](https://github.com/JuliaHEP/G4Examples.jl). Every example is run during the build, which takes some time.

```bash
julia --project=docs -e 'import Pkg; Pkg.develop(path="."); Pkg.instantiate()'
julia --project=docs docs/make.jl
```

To generate a single example page, run `julia --project=docs docs/literate.jl <name>`.

To add an example:

1. Copy its `.lit` file and any files it includes into `docs/src/examples`.
2. Add its name to the right `process_literate` call in `docs/make.jl`.
3. Add any included files to `create_extras`, so that the links to them work.
