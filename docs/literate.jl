using Literate
name = ARGS[1]

examplesdir =  joinpath(@__DIR__, "src/examples")
println("====> Processing $name")
file = "$(name)_lit.jl"

Literate.markdown(joinpath(examplesdir, file), examplesdir, name = name, execute = true, documenter = true, credit = true)
Literate.notebook(joinpath(examplesdir, file), examplesdir, name = name, execute = false, documenter = true, credit = true)
Literate.script(joinpath(examplesdir, file), examplesdir, name = name, keep_comments = false, documenter = true, credit = false)

