using Revise
using Geant4
using G4Visualization
using Geant4.SystemOfUnits
using GLMakie

include(joinpath(@__DIR__, "../../examples/TestEm3/DetectorTestEm3.jl"))

det = TestEm3Detector()
TestEm3Construct(det)

world = det.fPhysiWorld[]
draw(world)

