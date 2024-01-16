using Geant4
using Geant4.SystemOfUnits
using GLMakie, Rotations, IGLWrap_jll  # to force loading G4Vis extension

include(joinpath(@__DIR__, "../../../examples/TestEm3/DetectorTestEm3.jl"))

det = TestEm3Detector()
TestEm3Construct(det)

world = det.fPhysiWorld
img = draw(world[])
display(img)
