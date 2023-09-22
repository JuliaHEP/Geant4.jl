using IGLWrap_jll

#---A mesh type to capture what is returned by IGL functions---------------------------------------
mutable struct Cmesh
	nv::Cint
	nf::Cint
	vertices::Ptr{Cdouble}
	faces::Ptr{Cint}
	@inline Cmesh() = new()
end

#---Functions to convert from Julia/C elements of the structure------------------------------------
@inline unsafe_array(T, p, n) = unsafe_wrap(Array, convert(Ptr{T}, p), n; own=true)
@inline fieldpointer(m::T, name) where{T} = pointer_from_objref(m) + fieldoffset(T, findfirst(==(name), fieldnames(T)))
@inline ncoors(m::Cmesh) = fieldpointer(m, :nv)
@inline nfaces(m::Cmesh) = fieldpointer(m, :nf)
@inline vpointer(m::Cmesh) = fieldpointer(m, :vertices)
@inline fpointer(m::Cmesh) = fieldpointer(m, :faces)

@inline vpointer(c::Vector{Point3{Float64}}) = convert(Ptr{Cdouble}, pointer(c))
@inline fpointer(f::Vector{TriangleFace{Int32}}) = convert(Ptr{Cint}, pointer(f))
@inline ncoors(c::Vector{Point3{Float64}}) = size(c, 1) |> Int32
@inline nfaces(f::Vector{TriangleFace{Int32}}) = size(f, 1) |> Int32


function boolean(op, m1::GeometryBasics.Mesh, m2::GeometryBasics.Mesh, t::Transformation3D{Float64}=one(Transformation3D{Float64}))
    c1 = GeometryBasics.coordinates(m1)
    f1 = GeometryBasics.decompose(TriangleFace{Int32}, GeometryBasics.faces(m1))
    c2 = map(c -> c * t, GeometryBasics.coordinates(m2))
    f2 = GeometryBasics.decompose(TriangleFace{Int32}, GeometryBasics.faces(m2))

    cm = Cmesh()
    j = Ref(Ptr{Cint}(0));

    ret = @ccall libiglwrap.mesh_boolean(op::Cint,
        ncoors(c1)::Cint, nfaces(f1)::Cint,
        vpointer(c1)::Ref{Cdouble}, fpointer(f1)::Ref{Cint},
        ncoors(c2)::Cint, nfaces(f2)::Cint,
        vpointer(c2)::Ref{Cdouble}, fpointer(f2)::Ref{Cint},
        ncoors(cm)::Ptr{Cint}, nfaces(cm)::Ptr{Cint},
        vpointer(cm)::Ptr{Ptr{Cdouble}}, fpointer(cm)::Ptr{Ptr{Cint}},
        j::Ref{Ptr{Cint}})::Cint

    if ret == 0
        c = unsafe_array(Point3{Float64}, cm.vertices, cm.nv)
        f = unsafe_array(TriangleFace{Int32}, cm.faces, cm.nf)
        return GeometryBasics.Mesh(c,f)
    else
        return
    end
end


function GeometryBasics.mesh(psolid::CxxPtr{G4VSolid})
    tsolid = GetEntityType(psolid)
    shape =  getproperty(Geant4, Symbol(tsolid))
    solid = CxxRef{shape}(psolid)
    GeometryBasics.mesh(solid[])
end

const operation = Dict("G4UnionSolid" => 0, "G4IntersectionSolid" => 1, "G4SubtractionSolid" => 2)

function GeometryBasics.mesh(s::G4BooleanSolid)
    if  isdefined(IGLWrap_jll, :libiglwrap)
        op = operation[GetEntityType(s)]
        left = GetConstituentSolid(s, 0)
        right = GetConstituentSolid(s, 1)
        boolean(op, GeometryBasics.mesh(left), GeometryBasics.mesh(right))
    else
        println("IGLWrap_jll is not available for currrent platform $(Sys.MACHINE) and is needed for drawing boolean solids")
        GeometryBasics.Mesh(Point3{Float64}[], QuadFace{Int32}[])
    end
end

function GeometryBasics.mesh(s::G4DisplacedSolid)
    g4t = GetObjectTranslation(s)
    g4r = GetObjectRotation(s)
    t = Transformation3D{Float64}(convert(RotMatrix3{Float64}, CxxPtr(g4r)), convert(Vector3{Float64}, g4t))
    m = GeometryBasics.mesh(GetConstituentMovedSolid(s))
    points = GeometryBasics.coordinates(m)
    faces  = GeometryBasics.faces(m)
    map!(c -> c * t, points, points)
    GeometryBasics.Mesh(points, faces)
end

function Geant4.draw(solid::G4BooleanSolid; wireframe::Bool=false, kwargs...)
    #---Needs library libigl for drawing booleans and this is not available in all platforms
    if  isdefined(IGLWrap_jll, :libiglwrap)
        m = GeometryBasics.mesh(solid)
        if wireframe
            Makie.wireframe(m; linewidth=1, kwargs...)
        else
            Makie.mesh(m; kwargs...)
        end
    else
        println("IGLWrap_jll is not available for currrent platform $(Sys.MACHINE) and is needed for drawing boolean solids")
        return
    end
end
