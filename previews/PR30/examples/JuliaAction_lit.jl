# # Calling G4 actions in Julia
# 
# This is a very simple example of calling user actions in Julia from a C++ 
# Geant4 application. 
# We define the user actions in Julia language in the file [`MyCode.jl`](@ref)
# and call them from the C++ application. The name and signatures of the functions
# are important since the C++ will associate them in the corresponding inherited 
# classes.
# 
# The C++ code is a single file [`G4example.cpp`](@ref) that defines the Geant4 the minimal
# set of classes to run a simulation.
# - The main program is responsible of initializing Julia by calling `julia_init` and 
#   loading the Julia code executing.
#   ```cpp
#   jl_init()
#   jl_eval_string("include(\"MyCode.jl\")");
#   ```
# - Each constructor of a user action class needs to initialize a C++ function pointer to the 
#   corresponding Julia function. This is done in the constructor to avoid any dynamic dispatch
#   at runtime. For example, for the `EventAction` class:
#   ```cpp
#   typedef  void (*eventaction_f)(const G4Event*);
#   class EventAction : public G4UserEventAction {
#     public:
#       EventAction() {
#           beginevent_jl = (eventaction_f)(jl_unbox_voidpointer(jl_eval_string("@cfunction(begin_of_event_action, Nothing, (CxxPtr{G4Event},))")));
#           endevent_jl = (eventaction_f)(jl_unbox_voidpointer(jl_eval_string("@cfunction(end_of_event_action, Nothing, (CxxPtr{G4Event},))")));
#       }
#       ...
#     private:
#       eventaction_f beginevent_jl;
#       eventaction_f endevent_jl;
#   };      
#   ```
# - Finally the actions are called in the corresponding Geant4 classes. For example in the `EventAction` class:
#   ```cpp
#   void EventAction::BeginOfEventAction(const G4Event* event) {
#       beginevent_jl(event);
#   }
#   ...
#   ```

#md # !!! note "Note that"
#md #     You can also download this example as a
#md #     [Jupyter notebook](JuliaAction.ipynb) and a plain
#md #     [Julia source file](JuliaAction.jl).
#md #
#md #     The C++ code is available as a [source file](G4example.cpp) and the
#md #     Julia code is available as a [source file](MyCode.jl).
#md #
#md # #### Table of contents
#md # ```@contents
#md # Pages = ["JuliaAction.md"]
#md # Depth = 2:3
#md # ```

# ## Loading the necessary Julia modules
using Geant4_jll   # Needed to locate the Geant4 installation directory
#md import DisplayAs: PNG #hide

# ## Building G4Example Application
# The custom library is defined in the C++ file `G4example.cpp`. It is a single file to 
# facilitate the building of the executable.
#
# The attribute `Geant4_jll.artifact_dir` provides the path to the Geant4 installation directory.
# Sources are in the same location as this script.
cd(@__DIR__)
g4prefix = Geant4_jll.artifact_dir
jlprefix = dirname(Sys.BINDIR);

# We use the executables `geant4-config` and `julia-config.jl` to get the needed 
# libraries and compiler/linker flags.

g4libs = read(`$g4prefix/bin/geant4-config --libs`, String) |> split
filter!(x -> x != "-lG4gdml", g4libs)
jllibs = read(`$jlprefix/share/julia/julia-config.jl --ldlibs`, String) |> split
append!(jllibs, ["-L$jlprefix/lib"])
cflags = read(`$g4prefix/bin/geant4-config --cflags`, String) |> split
ldflags = ["-Wl,-rpath,$g4prefix/lib", "-Wl,-rpath,$jlprefix/lib"];
Sys.KERNEL == :Linux  && append!(ldflags, ["-Wl,--no-as-needed"]);

# Run the compilation and link command
Base.run(`c++ -O2 -fPIC $cflags -I$jlprefix/include/julia $ldflags $g4libs $jllibs 
          -o G4example.exe $(@__DIR__)/G4example.cpp`).exitcode == 0 || error("Compilation failed");

# ## Run the application
# We need to set the variable `JULIA_PROJECT` pointing to correctly setup Julia environment. 
withenv("JULIA_PROJECT" => "@.", "G4NUMTHREADS" => "4") do
   Base.run(`./G4example.exe`).exitcode == 0 || error("Execution failed")
end

# ## Display the results
println("=====> The file edepHist.png should have been saved")
#md # ![](edepHist.png)
#nb # ![](edepHist.png)
