using Documenter, Literate, Geant4  

const examplesdir =  joinpath(@__DIR__, "src/examples")
const project = @__DIR__

function process_literate(names...)
    examples_mds = []
    for name in names
        run(`julia --project=$project docs/literate.jl $name`)
        push!(examples_mds, "Example $name" => "examples/$name.md")
    end
    return examples_mds
end
function create_extras(extrafiles...)
    extra_mds = []
    for name in extrafiles
        open(joinpath(examplesdir,"$name.jl"), "r") do src
            open(joinpath(examplesdir,"$name.md"), "w") do dest
                write(dest, "# $(name).jl\n")
                write(dest, "```julia\n")
                for line in eachline(src)
                    write(dest, line * "\n")
                end
                write(dest, "```\n")
            end
        end
        push!(extra_mds, "examples/$name.md")
    end
    return extra_mds
end

basic_mds    = process_literate("B1", "B2a", "B2aVis", "B3a")
extend_mds   = process_literate("GPS", "RE03", "TestEm3", "Solids")
advanced_mds = process_literate("TPCSim", "HBC30", "WaterPhantom")
extra_mds    = create_extras("B2aDetector", "B2aVisSettings", "B3Detector", "GPSDetector", 
                             "RE03Detector", "TestEm3Detector", "HBC30Detector")  

#---Build the documentation-----------------------------------------------------------------------
makedocs(;
    modules=[Geant4],
    format = Documenter.HTML(
        prettyurls = Base.get(ENV, "CI", nothing) == "true",
        size_threshold = 8000000,
        size_threshold_warn = 4000000
    ),
    pages=[
        "Introduction" => "index.md",
        "Public API" => "api.md",
        "Examples" => [ "Basic" => basic_mds, 
                        "Extended" => extend_mds ,       
                        "Advanced" => advanced_mds ],
        hide.(extra_mds)...,
        "Release Notes" => "releases.md",
    ],
    repo="https://github.com/JuliaHEP/Geant4.jl/blob/{commit}{path}#L{line}",
    sitename="Geant4.jl",
    authors="Pere Mato",
)
#---Deploy the documentation-----------------------------------------------------------------------
deploydocs(;
    repo="github.com/JuliaHEP/Geant4.jl",
    push_preview = true
)
