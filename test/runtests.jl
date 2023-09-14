using Test
using Geant4
using Geant4.SystemOfUnits

@testset "Geant4 tests" verbose = true begin 
    include("testGeometry.jl")
    include("testRandom.jl")
    include("testExamples.jl")
end

