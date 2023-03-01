using Revise
using Geant4
using G4Visualization
using Geant4.SystemOfUnits
using GLMakie

include(joinpath(@__DIR__, "../../examples/basic/B2/DetectorB2a.jl"))

pv = constructB2aDetector()
draw(pv)
