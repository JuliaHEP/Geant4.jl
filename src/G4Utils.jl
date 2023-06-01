#---Exports from this section----------------------------------------------------------------------
export G4ThreeVector, G4RotationMatrix, G4Transform3D
export CxxPtr, ConstCxxPtr, CxxRef, ConstCxxRef, move!, preserve, @ui_cmd

#---Useful Geant4 Typedefs-------------------------------------------------------------------------
const G4RotationMatrix = CLHEP!HepRotation
const G4ThreeVector = CLHEP!Hep3Vector
const G4Transform3D = HepGeom!Transform3D

"""
    move!(o)

Move ownerhip of C++ object to receiver. The object cannot not be used anymore after this call.
"""
function move!(a)
    r = CxxPtr(a)
    a.cpp_object = C_NULL
    return r
end

#---Keep a reference to SafeCFuntion(s) to avoid GC to remove them---------------------------------
_cfuncs = Vector{CxxWrap.SafeCFunction}()
function preserve(f::CxxWrap.SafeCFunction)
    global _cfuncs
    push!(_cfuncs, f)
    return f
end

#---Cast operations-------------------------------------------------------------------------------
Base.convert(::Type{CxxPtr{G4VPhysicalVolume}}, o::G4PVPlacement) =  CxxPtr{G4VPhysicalVolume}(CxxPtr(o))
Base.convert(::Type{CxxPtr{G4VPhysicalVolume}}, o::G4PVReplica) =  CxxPtr{G4VPhysicalVolume}(CxxPtr(o))
Base.convert(::Type{G4String}, s::String) = make_G4String(s)


#---UI commands processing------------------------------------------------------------------------
macro ui_cmd(str)
    ex = Expr(:block)
    ex.args = [:(ApplyCommand(G4UImanager!GetUIpointer(), String($s))) for s = eachsplit(str,'\n')]
    ex
end