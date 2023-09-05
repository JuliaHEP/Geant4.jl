using Geant4
using Geant4.SystemOfUnits
using GLMakie, Rotations, IGLWrap_jll  # to force loding G4Vis extension

include(joinpath(@__DIR__, "../../../examples/basic/B2/B2a.jl"))

function drawHits(app)
    sddata = getSDdata(app, "Chamber_SD")                   # Get the hits from sensitive detector data
    # Separate the hists into 'tracks' made of points
    tracks = Vector{Point3}[]
    trackid = 0
    for h in sddata.trackerHits
        if h.trackID != trackid  # new track!
            push!(tracks, Point3[])
            trackid = h.trackID
        end
        push!(tracks[end], h.pos)
    end
    # Plot each 'track' as aline 
    for track in tracks
        lines!(track)
    end
end

#---Draw the detector------------------------------------------------------------------------------
world = GetWorldVolume()
draw(world)

#---Draw the TrackerHits---------------------------------------------------------------------------
for i in 1:10
    beamOn(app, 1)
    drawHits(app)
end



