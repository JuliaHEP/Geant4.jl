examples_dir = joinpath(pkgdir(Geant4), "examples")
notebooks = [joinpath(item[1],notebook) for item in walkdir(examples_dir) for notebook in item[3] 
      if splitext(notebook)[2] == ".ipynb" && !contains(notebook, "checkpoint") ]
output_dir = joinpath(pkgdir(Geant4), "docs", "src", "notebooks")

#---Run all Jupyter notebooks (`.ipynb` files) in `examples` and write outputs to MD files---------
function build()
    println("Building notebooks")
    for notebook in notebooks
        run(`jupyter nbconvert --execute --to=markdown --output-dir=$output_dir $notebook`)
    end
    return
end

#---Return Markdown file links which can be passed to Documenter.jl--------------------------------
function markdown_files()
    md_files = map(notebooks) do notebook
        file = splitext(basename(notebook))[1]
        return joinpath("notebooks", "$file.md")
    end
    return md_files
end

