using Geant4
using Geant4.SystemOfUnits
using GLMakie, Rotations

include(joinpath(@__DIR__, "../../../examples/basic/B2/B2a.jl"))

world = GetWorldVolume()
draw(world)

tracks = app.simdata.tracks
empty!(tracks)

beamOn(app, 1)
for t in tracks
    lines!(t)
end


