# Running the examples

The examples are ports of the Geant4 basic, extended and advanced examples, plus some that show features specific to Julia. Their source is in the [G4Examples.jl](https://github.com/JuliaHEP/G4Examples.jl) repository, kept separate from this package because the examples use extra packages for plotting and visualization (Makie, Plots, FHist, ...).

The pages in this section are generated from those sources and run with the current version of Geant4.jl when the documentation is built. They show the code together with its output and plots. Each page has links to download the example as a Jupyter notebook or a plain Julia script.

## Setting up an environment

The simplest way to run the examples is to clone G4Examples.jl, which includes a Julia environment with all the dependencies:

```bash
git clone https://github.com/JuliaHEP/G4Examples.jl.git
cd G4Examples.jl
julia --project=. -e 'import Pkg; Pkg.instantiate()'
julia --project=. basic/B1/B1.jl
```

To run an example downloaded from these pages instead, use the [`Project.toml`](https://github.com/JuliaHEP/Geant4.jl/blob/master/docs/Project.toml) of this documentation, which lists every package that the examples need:

1. Put `Project.toml` in an empty directory, together with the downloaded example and any files it includes (for example, `B2aDetector.jl`).
2. Run `julia --project=. -e 'import Pkg; Pkg.instantiate()'`. The first time, this takes a while: it downloads the Geant4 data files and compiles Makie.
3. Run the example with `julia --project=. <example>.jl`, or open the notebook in Jupyter.

The interactive visualization uses `GLMakie`, which needs a display. On a headless Linux machine, run the examples under `xvfb-run`.

## Available examples

```@contents
Pages = Main.examples_mds
Depth = 1:1
```
