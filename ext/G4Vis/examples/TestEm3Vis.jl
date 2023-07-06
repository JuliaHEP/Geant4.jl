using Geant4
using Geant4.SystemOfUnits
using GLMakie, Rotations

include(joinpath(@__DIR__, "../../../examples/TestEm3/DetectorTestEm3.jl"))

det = TestEm3Detector()
TestEm3Construct(det)

world = det.fPhysiWorld[]
draw(world)

