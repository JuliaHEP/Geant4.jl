#---Exports from this section----------------------------------------------------------------------
export G4ThreeVector, G4RotationMatrix, G4Transform3D
export G4Random, G4Random!getTheSeed, G4Random!setTheSeed, G4Random!getTheEngine, G4Random!setTheEngine
export G4RandFlat, G4RandBit, G4RandGamma, G4RandGauss, G4RandExponential, G4RandGeneral
export CxxPtr, ConstCxxPtr, CxxRef, ConstCxxRef, move!, preserve, @ui_cmd, StdVector

#---Useful Geant4 Typedefs-------------------------------------------------------------------------
const G4RotationMatrix = CLHEP!HepRotation
const G4ThreeVector = CLHEP!Hep3Vector
const G4Transform3D = HepGeom!Transform3D
const G4Random = CLHEP!HepRandom
const G4RandFlat = CLHEP!RandFlat
const G4RandBit = CLHEP!RandBit
const G4RandGamma = CLHEP!RandGamma
const G4RandGauss = CLHEP!RandGaussQ
const G4RandExponential = CLHEP!RandExponential
const G4RandGeneral = CLHEP!RandGeneral
const G4Random!getTheSeed = CLHEP!HepRandom!getTheSeed
const G4Random!setTheSeed = CLHEP!HepRandom!setTheSeed
const G4Random!getTheEngine = CLHEP!HepRandom!getTheEngine
const G4Random!setTheEngine = CLHEP!HepRandom!setTheEngine
 
Base.show(io::IO, p::G4ThreeVector) = print(io, "G4ThreeVector($(x(p)),$(y(p)),$(z(p)))")
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

#---Iteration G4ProcessVector
function Base.iterate(iter::G4ProcessVector)
    Geant4.entries(iter) == 0 && return nothing
    return (iter[0], 0)
end
function Base.iterate(iter::G4ProcessVector, i::Int)
    i = i + 1
    i >= Geant4.entries(iter) && return nothing
    return (iter[i], i)
end
