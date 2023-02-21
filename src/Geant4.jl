module Geant4
    include(joinpath(@__DIR__, "../gen/jl/Geant4-export.jl"))
    using CxxWrap
    using Geant4_jll

    @wrapmodule(joinpath(@__DIR__, "../deps/build/lib", "libGeant4Wrap"))
    function __init__()
        @initcxx
        #---Call Wrapper init--------------------------------------------------
        G4JL_init()
        #---Setup [data] environment-------------------------------------------
        GEANT4_DATA_DIR = get(ENV, "GEANT4_DATA_DIR", "/cvmfs/geant4.cern.ch/share/data")
        for line in readlines(joinpath(Geant4_jll.artifact_dir, "bin/geant4.sh"))
            m = match(r"export[ ]+(.*)=.*/(.*)\"", line)
            if !isnothing(m)
                G4JL_setenv(String(m[1]), joinpath(GEANT4_DATA_DIR, m[2]))
            end
        end
    end

    # Typedef hack! 
    const G4RotationMatrix = CLHEP!HepRotation
    const G4ThreeVector = CLHEP!Hep3Vector
    const G4Transform3D = HepGeom!Transform3D
    export G4ThreeVector, G4RotationMatrix, G4Transform3D

    # Useful pointers
    export CxxPtr, ConstCxxPtr, CxxRef, ConstCxxRef

    # Addional usability functions
    G4LogicalVolume(s::G4VSolid, m::CxxPtr{G4Material}, l::String) = G4LogicalVolume(CxxPtr(s), m, l)
    G4PVPlacement(r::Union{Nothing, G4RotationMatrix}, d::G4ThreeVector, l::Union{Nothing,G4LogicalVolume}, s::String, 
                  p::Union{Nothing, G4LogicalVolume}, b1::Bool, n::Int, b2::Bool) = 
                  G4PVPlacement(isnothing(r) ? CxxPtr{G4RotationMatrix}(C_NULL) : CxxPtr(r), d, 
                                isnothing(l) ? CxxPtr{G4LogicalVolume}(C_NULL) : CxxPtr(l), s, 
                                isnothing(p) ? CxxPtr{G4LogicalVolume}(C_NULL) : CxxPtr(p), b1, n, b2)
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
    Base.convert(::Type{G4String}, s::String) = make_G4String(s)

    include("SystemOfUnits.jl")

end # module Geant4
