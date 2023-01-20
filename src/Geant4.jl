module Geant4
    include(joinpath(@__DIR__, "../gen/jl/Geant4-export.jl"))
    using CxxWrap

    @wrapmodule(joinpath(@__DIR__, "../gen/build/lib", "libGeant4Wrap"))
    function __init__()
        @initcxx
        #---Call Wrapper init--------------------------------------------------
        G4JL_init()
        #---Setup [data] environment-------------------------------------------
        G4DATADIR = "/Users/Shared/cvmfs/sft-nightlies.cern.ch/lcg/nightlies/dev4/Sun/Geant4/11.0.3/x86_64-mac11-clang120-opt/share/Geant4-11.0.3/data"
        G4JL_setenv("G4ENSDFSTATEDATA", joinpath(G4DATADIR, "G4ENSDFSTATE2.3"))
        G4JL_setenv("G4LEDATA", joinpath(G4DATADIR, "G4EMLOW8.0"))
        G4JL_setenv("G4NEUTRONHPDATA", joinpath(G4DATADIR, "G4NDL4.6"))
        G4JL_setenv("G4ENSDFSTATEDATA", joinpath(G4DATADIR, "G4ENSDFSTATE2.3"))
        G4JL_setenv("G4ABLADATA", joinpath(G4DATADIR, "G4ABLA3.1"))
        G4JL_setenv("G4PIIDATA", joinpath(G4DATADIR, "G4PII1.3"))
        G4JL_setenv("G4PARTICLEXSDATA", joinpath(G4DATADIR, "G4PARTICLEXS4.0"))
        G4JL_setenv("G4SAIDXSDATA", joinpath(G4DATADIR, "G4SAIDDATA2.0"))
        G4JL_setenv("G4REALSURFACEDATA", joinpath(G4DATADIR, "RealSurface2.2"))
        G4JL_setenv("G4INCLDATA", joinpath(G4DATADIR, "G4INCL1.0"))
    end
end # module Geant4


