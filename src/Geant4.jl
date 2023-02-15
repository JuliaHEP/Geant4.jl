module Geant4
    include(joinpath(@__DIR__, "../gen/jl/Geant4-export.jl"))
    using CxxWrap

    @wrapmodule(joinpath(@__DIR__, "../gen/build/lib", "libGeant4Wrap"))
    function __init__()
        @initcxx
        #---Call Wrapper init--------------------------------------------------
        G4JL_init()
        #---Setup [data] environment-------------------------------------------
        GEANT4_DATA_DIR = get(ENV, "GEANT4_DATA_DIR", "/Users/mato/Development/releases/dev4/Geant4/11.1.0/x86_64-mac11-clang120-opt/share/Geant4/data")
        G4JL_setenv("G4ENSDFSTATEDATA", joinpath(GEANT4_DATA_DIR, "G4ENSDFSTATE2.3"))
        G4JL_setenv("G4LEDATA", joinpath(GEANT4_DATA_DIR, "G4EMLOW8.2"))
        G4JL_setenv("G4NEUTRONHPDATA", joinpath(GEANT4_DATA_DIR, "G4NDL4.7"))
        G4JL_setenv("G4ENSDFSTATEDATA", joinpath(GEANT4_DATA_DIR, "G4ENSDFSTATE2.3"))
        G4JL_setenv("G4ABLADATA", joinpath(GEANT4_DATA_DIR, "G4ABLA3.1"))
        G4JL_setenv("G4PIIDATA", joinpath(GEANT4_DATA_DIR, "G4PII1.3"))
        G4JL_setenv("G4PARTICLEXSDATA", joinpath(GEANT4_DATA_DIR, "G4PARTICLEXS4.0"))
        G4JL_setenv("G4SAIDXSDATA", joinpath(GEANT4_DATA_DIR, "G4SAIDDATA2.0"))
        G4JL_setenv("G4REALSURFACEDATA", joinpath(GEANT4_DATA_DIR, "RealSurface2.2"))
        G4JL_setenv("G4INCLDATA", joinpath(GEANT4_DATA_DIR, "G4INCL1.0"))
    end

    # Typedef hack! 
    const G4RotationMatrix = CLHEP!HepRotation
    const G4ThreeVector = CLHEP!Hep3Vector
    const G4Transform3D = HepGeom!Transform3D

    export G4ThreeVector, G4RotationMatrix, G4Transform3D

    nullptr(T::Type) = CxxPtr{T}(C_NULL)
    ptr(o::Any) = CxxPtr(o)

    # Addional usability functions
    G4LogicalVolume(s::G4VSolid, m::CxxPtr{G4Material}, l::String) = G4LogicalVolume(CxxPtr(s), m, l)
    G4PVPlacement(r::Union{Ptr{Nothing}, G4RotationMatrix}, 
                  d::G4ThreeVector, 
                  l::Union{Ptr{Nothing},G4LogicalVolume}, 
                  s::String, 
                  p::Union{Ptr{Nothing}, G4LogicalVolume}, 
                  b1::Bool, n::Int, b2::Bool) = 
        G4PVPlacement(typeof(r) == Ptr{Nothing} ? CxxPtr{G4RotationMatrix}(r) : r, d, 
                      typeof(l) == Ptr{Nothing} ? CxxPtr{G4LogicalVolume}(l) : CxxPtr(l), s,
                      typeof(p) == Ptr{Nothing} ? CxxPtr{G4LogicalVolume}(p) : CxxPtr(p), b1, n, b2)
    
    #                   
    function G4JLDetectorConstruction(f::Function)
        ff() = CxxPtr{G4VPhysicalVolume}(f().cpp_object)          # wrap the Julia function to return a pointer to G4PhysicalVolume
        sf = @safe_cfunction($ff, CxxPtr{G4VPhysicalVolume}, ())  # crate a safe c function
        c = G4JLDetectorConstruction(sf)                          # call the construction                        
        return CxxPtr(c)                                          # convert to pointer 
    end
    function G4JLActionInitialization(f::Function)
        ff(self::ConstCxxPtr{G4JLActionInitialization}) = f(self[])
        sf = @safe_cfunction($ff, Nothing, (ConstCxxPtr{G4JLActionInitialization},))                      # crate a safe c function
        c = G4JLActionInitialization(sf)                          # call the construction                        
        return CxxPtr(c)                                          # convert to pointer 
    end
    
    export nullptr, ptr

    include("HEPSystemOfUnits.jl")

end # module Geant4




