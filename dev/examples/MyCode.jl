#---Load the needed Julia modules------------------------------------------------------------------

using Geant4
using GeometryBasics
using FHist
using Plots

println("=====> Loading MyCode.jl")

edepHist = H1D("Event total Edep distribution", 100, 0., 110.)
edep = 0.0

function end_of_event_action(event)
    push!(edepHist, edep)
    return                      # This is mandatory to force to return nothing
end

function begin_of_event_action(event)
    global edep = 0.0
    return                      # This is mandatory to force to return nothing
end

function stepping_action(step)
    global edep += GetTotalEnergyDeposit(step)
    return                      # This is mandatory to force to return nothing
end

function begin_of_run_action(run)
    return                      # This is mandatory to force to return nothing
end

function end_of_run_action(run)    
    println("=====> End of run")
    h = edepHist
    img = plot(h.hist, title=h.title)
    savefig(img, "edepHist.png")
    println("=====> edepHist.png saved")
    return                      # This is mandatory to force to return nothing
end  
