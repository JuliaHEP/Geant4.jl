using Test
using Geant4
using Geant4.SystemOfUnits

@testset "Geant4 tests" verbose = true begin 
    include("testGeometry.jl")
    include("testRandom.jl")
    # we do not need to run the examples since they are already tested in the CI while building the docs 
    # include("testExamples.jl")
end

