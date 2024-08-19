#---Event Display----------------------------------------------------------------------------------
mutable struct G4JLEventDisplay <: G4JLDisplay
    const settings::NamedTuple
    const stateChange::Function
    const initDisplay::Function
    # mutable attributes
    lscene::LScene
    figure::Figure
    G4JLEventDisplay(settings, statech, initdisp) = new(settings, statech, initdisp)
end
"""
G4JLEventDisplay(settings_file)

Create a G4JLEventDisplay with all settings from .jl file
# Arguments
"""
function Geant4.G4JLEventDisplay(settings_file=nothing)
    settings = eval(Meta.parse(read(joinpath(@__DIR__, "settings.jl"), String)))
    if ! isnothing(settings_file)
        user_settings = eval(Meta.parse(read(settings_file, String)))
        settings = settings_merge(settings, user_settings)
    end
    G4JLEventDisplay(settings, stateChange, initDisplay)
end

#---State change notify---------------------------------------------------------------------------- 
function stateChange(from::G4ApplicationState, to::G4ApplicationState, app::G4JLApplication)::Bool
    eventdisplay = app.evtdisplay
    if from == G4State_Init && to == G4State_Idle
    elseif from == G4State_Idle && to == G4State_GeomClosed        
    elseif from == G4State_GeomClosed && to == G4State_EventProc
        clearEvent(eventdisplay)
    elseif from == G4State_EventProc && to == G4State_GeomClosed
        drawEvent(eventdisplay)
    elseif from == G4State_GeomClosed && to == G4State_Idle
    end
    return true
end

#--------------------------------------------------------------------------------------------------

function initDisplay(evtdisp::G4JLEventDisplay)
    settings = evtdisp.settings
    if ! isdefined(evtdisp, :scene)
        ui`/tracking/storeTrajectory 1`
        # create the scene
        set_theme!(backgroundcolor = settings.display.backgroundcolor)
        fig = Figure(size=settings.display.resolution)
        sc = LScene(fig[1,1], show_axis=settings.display.show_axis)
        #display(fig)
        evtdisp.lscene = sc
        evtdisp.figure = fig
    end
    # draw the detector
    if settings.detector.show_detector
        sc = evtdisp.lscene
        world = GetWorldVolume()
        draw!(sc, world)
    end
end

function clearEvent(evtdisp::G4JLEventDisplay)
    s = evtdisp.lscene.scene
    tobe = [p for p in plots(s) if p isa Lines || p isa Makie.Text]  # The event is made of lines and text 
    for p in tobe
        delete!(s,p)
    end
end

function drawEvent(evtdisp::G4JLEventDisplay)
    s = evtdisp.lscene.scene
    settings = evtdisp.settings
    trajectories = G4EventManager!GetEventManager() |> GetConstCurrentEvent |> GetTrajectoryContainer
    if trajectories != C_NULL
        points = Point3{Float64}[]
        for t in trajectories
            for i in 1:GetPointEntries(t)
                push!(points, convert(Point3{Float64}, GetPoint(t, i-1) |> GetPosition))
            end
            push!(points, Point3{Float64}(NaN, NaN, NaN))
        end
        lines!(s, points, color=settings.trajectories.color, transparency=false, overdraw=false)
    end
    #wait_for_key("Press any key to continue with next event")
end

#---Settings (nested NamedTuple) merge fnction-----------------------------------------------------
function settings_merge(s1::NamedTuple, s2::NamedTuple)
    for k in intersect(keys(s1), keys(s2))
        v1, v2 = getfield(s1,k), getfield(s2,k)
        if v1 isa NamedTuple
            if  v2 isa NamedTuple
                v = settings_merge(v1, v2)
                s2 = merge(s2, (; k => v))
            else
                error("$k in not of type NamedTuple in both NamedTuples")
            end
        end
    end
    merge(s1, s2)
end