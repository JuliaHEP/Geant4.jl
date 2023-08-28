#---G4Polyhedra-------------------------------------------------------------------------------------

mutable struct PolyhedraParams
    ϕ₀::Float64
    Δϕ::Float64
    ns::Int32
    nz::Int32
    z::Ptr{Float64}
    rmin::Ptr{Float64}
    rmax::Ptr{Float64}
end

function GeometryBasics.coordinates(pgon::G4Polyhedra, facets=24)
    ϕ₀ = GetStartPhi(pgon)
    ϕₑ = GetEndPhi(pgon)
    n = GetNumRZCorner(pgon)
    sides = GetNumSide(pgon)
    issector = !(ϕₑ-ϕ₀ ≈ 2π)
    rz = [unsafe_load(Ptr{SideRZ}(GetPolyCorner(pgon, i-1).cpp_object)) for i in 1:n]
    ϕ = LinRange(ϕ₀, ϕₑ, sides + 1)
    inner(ϕ, r, z) = Point(r * cos(ϕ), r * sin(ϕ), z)
    points =  vec([inner(ϕ, rz[j].r, rz[j].z) for ϕ in ϕ, j in 1:n])
    if issector
        params = unsafe_load(Ptr{PolyhedraParams}(GetOriginalParameters(pgon).cpp_object))
        nz = params.nz
        z = unsafe_wrap(Array, params.z, nz; own = false)
        rmin = unsafe_wrap(Array, params.rmin, nz; own = false)
        rmax = unsafe_wrap(Array, params.rmax, nz; own = false)
        for ϕ in (ϕ₀, ϕₑ)
            for i in 1:nz
                push!(points, Point(rmin[i] * cos(ϕ), rmin[i] * sin(ϕ), z[i]))
                push!(points, Point(rmax[i] * cos(ϕ), rmax[i] * sin(ϕ), z[i]))
            end
        end
    end
    return points
end

cyc(x,n) = mod(x-1, n) + 1

function GeometryBasics.faces(pgon::G4Polyhedra, facets=24)
    ϕ₀ = GetStartPhi(pgon)
    ϕₑ = GetEndPhi(pgon)
    n = GetNumRZCorner(pgon)
    sides = GetNumSide(pgon)
    issector = !(ϕₑ-ϕ₀ ≈ 2π)
    idx = LinearIndices((sides + 1, n))
    quad(i, j) = QuadFace{Int}(idx[i, j], idx[i + 1, j], idx[i + 1, cyc(j + 1,n)], idx[i, cyc(j + 1,n)])
    faces = vec([quad(i, j) for i in 1:sides, j in 1:n])
    if issector
        nz  = unsafe_load(Ptr{PolyhedraParams}(GetOriginalParameters(pgon).cpp_object)).nz
        offset = (sides + 1) * n
        for c in 0:1
            for i in 0:nz-2
                odx = offset + 2*i + 2*nz*c
                push!(faces, QuadFace{Int}(odx+1, odx+2, odx+4, odx+3))
            end
        end
    end
    return faces
end