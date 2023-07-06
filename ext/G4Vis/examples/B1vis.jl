using Geant4
using Geant4.SystemOfUnits
using GLMakie, Rotations

include("../../../examples/basic/B1/DetectorB1.jl")

pv = constructB1Detector()
draw(pv[])
