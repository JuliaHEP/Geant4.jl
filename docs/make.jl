using Documenter, Geant4

include("build.jl")

build()
md_files = markdown_files()
T = ["Example $(splitext(basename(f))[1])" => f for f in md_files]

makedocs(;
    modules=[Geant4],
    format = Documenter.HTML(
        prettyurls = Base.get(ENV, "CI", nothing) == "true",
    ),
    pages=[
        "Introduction" => "index.md",
        "APIs" => "api.md",
        "Examples" => T,
    ],
    repo="https://github.com/JuliaHEP/Geant4.jl/blob/{commit}{path}#L{line}",
    sitename="Geant4.jl",
    authors="Pere Mato",
)

deploydocs(;
    repo="github.com/JuliaHEP/Geant4.jl",
    push_preview = true
)
