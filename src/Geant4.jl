module Geant4
    using CxxWrap
    using Geant4_jll

    # Check whether the wrappers have been build locally otherwise use the binary package Geant4_julia_jll
    gendir = normpath(joinpath(@__DIR__, "../gen"))
    if isdir(joinpath(gendir, "build/lib"))
        include(joinpath(gendir, "jl/Geant4-export.jl"))
        @wrapmodule(joinpath(gendir, "build/lib", "libGeant4Wrap"))
    else
        using Geant4_julia_jll
        include(Geant4_julia_jll.Geant4_exports)
        @wrapmodule(Geant4_julia_jll.libGeant4Wrap)
    end

    function __init__()
        @initcxx
        #---Call Wrapper init--------------------------------------------------
        G4JL_init()
        #---Setup [data] environment-------------------------------------------
        GEANT4_DATA_DIR = get(ENV, "GEANT4_DATA_DIR", Geant4_jll.data_dir)
        for line in readlines(joinpath(Geant4_jll.artifact_dir, "bin/geant4.sh"))
            m = match(r"export[ ]+(G4.*)=.*/(.*)$", line)
            if !isnothing(m)
                G4JL_setenv(String(m[1]), joinpath(GEANT4_DATA_DIR, m[2]))
            end
        end
    end

    include("SystemOfUnits.jl")
    include("G4Utils.jl")
    include("G4Scoring.jl")
    include("G4JLInterface.jl")

end
