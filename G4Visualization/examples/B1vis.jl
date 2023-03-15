using Geant4
using G4Visualization
using Geant4.SystemOfUnits
using GLMakie

include("../../examples/basic/B1/DetectorB1.jl")

pv = constructB1Detector()
draw(pv[])
