#---Exports from this section----------------------------------------------------------------------
export G4ThreeVector, G4RotationMatrix, G4Transform3D
export G4Random, G4Random!getTheSeed, G4Random!setTheSeed, G4Random!getTheEngine, G4Random!setTheEngine
export G4RandFlat, G4RandBit, G4RandGamma, G4RandGauss, G4RandExponential, G4RandGeneral
export CxxPtr, ConstCxxPtr, CxxRef, ConstCxxRef, move!, preserve, @ui_cmd, StdVector

#---Useful Geant4 Typedefs-------------------------------------------------------------------------
typedef(t, n) = isdefined(Geant4, t) && eval(:(const $n = $t))

typedef(:CLHEP!HepRotation, :G4RotationMatrix)
typedef(:CLHEP!Hep3Vector, :G4ThreeVector)
typedef(:CLHEP!HepRandom, :G4Random)
typedef(:HepGeom!Transform3D, :G4Transform3D)
typedef(:CLHEP!RandFlat, :G4RandFlat)
typedef(:CLHEP!RandBit, :G4RandBit)
typedef(:CLHEP!RandGamma, :G4RandGamma)
typedef(:CLHEP!RandGaussQ, :G4RandGaussQ)
typedef(:CLHEP!RandExponential, :G4RandExponential)
typedef(:CLHEP!RandGeneral, :G4RandGeneral)
typedef(:CLHEP!HepRandom!getTheSeed, :G4Random!getTheSeed)
typedef(:CLHEP!HepRandom!setTheSeed, :G4Random!setTheSeed)
typedef(:CLHEP!HepRandom!getTheEngine, :G4Random!getTheEngine)
typedef(:CLHEP!HepRandom!setTheEngine, :G4Random!setTheEngine)
 
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
#---Iteration G4LogicalVolumeStore
function Base.iterate(iter::CxxPtr{G4LogicalVolumeStore})
    Geant4.size(iter) == 0 && return nothing
    return (GetVolume(iter, 0), 0)
end
function Base.iterate(iter::CxxPtr{G4LogicalVolumeStore}, i::Int)
    i = i + 1
    i >= Geant4.size(iter) && return nothing
    return (GetVolume(iter, i), i)
end
#---Iteration G4TrajectoryContainer
function Base.iterate(iter::G4TrajectoryContainer)
    Geant4.size(iter) == 0 && return nothing
    return (iter[0], 0)
end
function Base.iterate(iter::G4TrajectoryContainer, i::Int)
    i = i + 1
    i >= Geant4.size(iter) && return nothing
    return (iter[i], i)
end

#---G4Point3D-------------------------------------------------------------------------------------
const G4Point3D = HepGeom!Point3D{Float64}
const G4Normal3D = HepGeom!Normal3D{Float64}
Base.getindex(p::G4Point3D, i::Int) = 0 < i < 4 ? _getindex(p, i) : throw(BoundsError(p, i))
Base.getindex(p::G4Normal3D, i::Int) = 0 < i < 4 ? _getindex(p, i) : throw(BoundsError(p, i))

AddFacet(s::G4TessellatedSolid, f::G4TriangularFacet) = AddFacet(s, move!(f))