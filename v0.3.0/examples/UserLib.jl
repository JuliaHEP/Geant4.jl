using Geant4
using Geant4.SystemOfUnits
using Libdl
using CairoMakie  # to force loading G4Vis extension

prefix = Geant4.Geant4_jll.artifact_dir
dlext = Libdl.dlext;
if Sys.KERNEL == :Linux
    ldflags = "-Wl,-rpath,$prefix/lib -Wl,--no-as-needed"
else
    ldflags = "-Wl,-rpath,$prefix/lib -Wl"
end
# Compilation of the custom library

Base.run(`c++ -O2 -shared -fPIC -std=c++17 -I$prefix/include/Geant4 $ldflags
         -L$prefix/lib -lG4geometry -lG4materials -lG4global -lG4clhep
         -o UserLibrary.$dlext $(@__DIR__)/UserLibrary.cpp`).exitcode == 0 || error("Compilation failed")

const lib = "./UserLibrary.$(Libdl.dlext)"
createRoundCube(a,r) = @ccall lib.createRoundCube(a::Float64, r::Float64)::CxxPtr{G4VSolid}
deleteRoundCube(s::CxxPtr{G4VSolid}) = @ccall lib.deleteRoundCube(s::CxxPtr{G4VSolid})::Cvoid
infoRoundCube(s::CxxPtr{G4VSolid}) = (@ccall lib.infoRoundCube(s::CxxPtr{G4VSolid})::Cstring) |> unsafe_string

rcube = createRoundCube(10cm, 1cm)        # returns a CxxPtr{G4VSolid}
img = drawDistanceToOut(rcube[], 100000)  # implemented in G4Vis ext. It expects a G4VSolid.
display(img)

info = infoRoundCube(rcube)
println(info)

deleteRoundCube(rcube)
