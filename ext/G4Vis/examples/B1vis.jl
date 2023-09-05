using Geant4
using Geant4.SystemOfUnits
using GLMakie, Rotations,  IGLWrap_jll  # to force loa ding G4Vis extension

include("../../../examples/basic/B1/DetectorB1.jl")

pv = constructB1Detector(nothing)
draw(pv[])
