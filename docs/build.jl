examples_dir = examples_dir = joinpath.(pkgdir(Geant4), ("examples","ext/G4Vis/examples"))
notebooks = [joinpath(item[1],notebook) for exdir in examples_dir for item in walkdir(exdir) for notebook in item[3] 
             if splitext(notebook)[2] == ".ipynb" && !contains(notebook, "checkpoint") ]
vis_examples_dir = joinpath(pkgdir(Geant4), "ext/G4Vis/examples")
output_dir = joinpath(pkgdir(Geant4), "docs", "src", "notebooks")

#---Run all Jupyter notebooks (`.ipynb` files) in `examples` and write outputs to MD files---------
function build()
    println("Building notebooks")
    for notebook in notebooks
        run(`jupyter nbconvert --execute --to=markdown --output-dir=$output_dir $notebook`)
        #---Fix for the embedded figures-----------------------------------------------------------
        mdfile = joinpath(output_dir, "$(splitext(basename(notebook))[1]).md")
        original = read(mdfile, String)
        modified = replace(original, 
          "<?xml version=\"1.0\" encoding=\"utf-8\"?>" => "",
          "<svg" => "```@raw html\n<svg",
          "/svg>" => "/svg>\n```"
        )
        write(mdfile, modified)
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

