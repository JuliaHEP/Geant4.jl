using Geant4_jll   # Needed to locate the Geant4 installation directory

cd(@__DIR__)
g4prefix = Geant4_jll.artifact_dir
jlprefix = dirname(Sys.BINDIR);

g4libs = read(`$g4prefix/bin/geant4-config --libs`, String) |> split
filter!(x -> x != "-lG4gdml", g4libs)
jllibs = replace(read(`$jlprefix/share/julia/julia-config.jl --ldlibs`, String), "'" => "") |> split  # remove shell quotes
append!(jllibs, ["-L$jlprefix/lib"])
cflags = read(`$g4prefix/bin/geant4-config --cflags`, String) |> split
append!(cflags, ["-Wno-nullability-completeness", "-Wno-nullability-extension"])
ldflags = ["-Wl,-rpath,$g4prefix/lib"];
Sys.KERNEL == :Linux  && append!(ldflags, ["-Wl,--no-as-needed"]);

Base.run(`c++ -O2 -fPIC $cflags -I$jlprefix/include/julia $ldflags $g4libs $jllibs
          -o G4example.exe $(@__DIR__)/G4example.cpp`).exitcode == 0 || error("Compilation failed");

withenv("JULIA_PROJECT" => "@.", "G4NUMTHREADS" => "8") do
   Base.run(`./G4example.exe`).exitcode == 0 || error("Execution failed")
end

println("=====> The file edepHist.png should have been saved")
