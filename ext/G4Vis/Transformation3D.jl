#---Basic Geometry------------------------------------------------------------------------
using StaticArrays, GeometryBasics, Rotations, LinearAlgebra

const Vector3 = SVector{3}
const Vector2 = SVector{2}
Base.:*(x::Vector3, y::Vector3) = Vector3(x[1]*y[1], x[2]*y[2], x[3]*y[3])
Base.:*(x::Point3, y::Vector3) = Point3(x[1]*y[1], x[2]*y[2], x[3]*y[3])
Base.:*(x::Vector3, n::Number) = Vector3(x[1]*n, x[2]*n, x[3]*n)
Base.:*(n::Number, x::Vector3) = x * n
Base.:/(p::Point3, n::Number) = Point3(p[1]/n, p[2]/n, p[3]/n)
LinearAlgebra.:⋅(x::Vector3, y::Vector3) = x[1]*y[1] + x[2]*y[2] + x[3]*y[3]
#Base.:-(p1::Point3, p2::Point3) = Vector3(p1[1]-p2[1], p1[2]-p2[2], p1[3]-p2[3])
#Base.:+(p1::Point3, p2::Point3) = Vector3(p1[1]+p2[1], p1[2]+p2[2], p1[3]+p2[3])
LinearAlgebra.:×(x::Vector3, y::Vector3) = Vector3(x[2]*y[3]-x[3]*y[2], -x[1]*y[3]+x[3]*y[1], x[1]*y[2]-x[2]*y[1])
unitize(v::Vector3) = v/sqrt(v⋅v)

#---Transformation3D----------------------------------------------------------------------
struct Transformation3D{T<:AbstractFloat}
    rotation::RotMatrix3{T}
    translation::Vector3{T}
    # optimization
    has_rot::Bool
    has_trans::Bool
    Transformation3D{T}(rot::RotMatrix3{T}, trans::Vector3{T}) where T = new(rot, trans, !isone(rot), !iszero(trans))
end

Transformation3D() = Transformation3D{Float64}()

# Usefull constructors 
Transformation3D{T}(dx, dy, dz) where T<:AbstractFloat = Transformation3D{T}(one(RotMatrix3{T}), Vector3{T}(dx, dy, dz))
Transformation3D{T}(dx, dy, dz, rotx, roty, rotz) where T<:AbstractFloat = Transformation3D{T}(RotMatrix3{T}(RotXYZ{T}(rotx, roty, rotz)), Vector3{T}(dx, dy, dz))
Transformation3D{T}(dx, dy, dz, rot::Rotation{3,T}) where T<:AbstractFloat = Transformation3D{T}(RotMatrix3{T}(rot), Vector3{T}(dx, dy, dz))

# Transforms
@inline transform(t::Transformation3D{T}, p::Point3{T}) where T<:AbstractFloat = t.has_rot ? t.rotation * (t.has_trans ? (p - t.translation) : p) : (t.has_trans ? (p - t.translation) : p)
@inline transform(t::Transformation3D{T}, d::Vector3{T}) where T<:AbstractFloat = t.has_rot ? t.rotation * d : d
@inline invtransform(t::Transformation3D{T}, p::Point3{T}) where T<:AbstractFloat = t.has_trans ? ((t.has_rot ? (p' * t.rotation)' : p) + t.translation) : ( t.has_rot ? (p' * t.rotation)' : p)
@inline invtransform(t::Transformation3D{T}, d::Vector3{T}) where T<:AbstractFloat = t.has_rot ? (d' * t.rotation)' : d
@inline Base.:*(t::Transformation3D{T}, p::Point3{T}) where T<:AbstractFloat =  transform(t,p)
@inline Base.:*(t::Transformation3D{T}, d::Vector3{T}) where T<:AbstractFloat =  transform(t,d)
@inline Base.:*(p::Point3{T}, t::Transformation3D{T}) where T<:AbstractFloat =  invtransform(t,p)
@inline Base.:*(d::Vector3{T}, t::Transformation3D{T}) where T<:AbstractFloat =  invtransform(t,d)

# Compose
Base.:*(t1::Transformation3D{T}, t2::Transformation3D{T}) where T<:AbstractFloat = 
    Transformation3D{T}(t1.rotation * t2.rotation, (t1.translation' * t2.rotation)' + t2.translation)
Base.inv(t::Transformation3D{T}) where T<:AbstractFloat = Transformation3D{T}(t.rotation', - t.rotation * t.translation)
Base.isapprox(t1::Transformation3D{T}, t2::Transformation3D{T}; atol::Real=0, rtol::Real=atol>0 ? 0 : √eps, nans::Bool=false) where T<:AbstractFloat =
    isapprox(t1.rotation, t2.rotation; atol=atol, rtol=rtol, nans=nans) && isapprox(t1.translation, t2.translation; atol=atol, rtol=rtol, nans=nans)

# Utilities
Base.one(::Type{Transformation3D{T}}) where T<:AbstractFloat = Transformation3D{T}(one(RotMatrix3{T}), Vector3{T}(0,0,0))
Base.isone(t::Transformation3D{T}) where T<:AbstractFloat = isone(t.rotation) && iszero(t.translation)
hasrotation(t::Transformation3D{T}) where T<:AbstractFloat = !isone(t.rotation)
hastranslation(t::Transformation3D{T}) where T<:AbstractFloat = !iszero(t.translation)

