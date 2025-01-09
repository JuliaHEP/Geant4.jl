#---G4Cons--------------------------------------------------------------------------------------
function GeometryBasics.coordinates(cone::G4Cons, facets=36)
    rmin1 = GetInnerRadiusMinusZ(cone)
    rmax1 = GetOuterRadiusMinusZ(cone)
    rmin2 = GetInnerRadiusPlusZ(cone)
    rmax2 = GetOuterRadiusPlusZ(cone)
    z     = GetZHalfLength(cone)
    ϕ₀    = GetStartPhiAngle(cone)
    Δϕ    = GetDeltaPhiAngle(cone)

    issector = Δϕ < 2π
    ishollow = rmin1 > 0 || rmin2 > 0
    issector ?  facets =  round(Int64, (facets/2π) * Δϕ) : nothing
    isodd(facets) ? facets = 2 * div(facets, 2) : nothing
    facets < 8 ? facets = 8 : nothing
    nbf = Int(facets / 2)            # Number of faces
    nbv = issector ? nbf + 1 : nbf   # Number of vertices
    nbc = ishollow ? nbv : 1         # Number of centers
    range = 1:(2*nbv + 2*nbc)
    function inner(i)
        return if i <= 2*nbv
            ϕ = ϕ₀ + (Δϕ * (((i + z) ÷ 2) - z)) / nbf
            isodd(i) ? Point(rmax2 * cos(ϕ), rmax2 * sin(ϕ), z) : Point(rmax1 * cos(ϕ), rmax1 * sin(ϕ), -z)
        elseif ishollow
            ϕ = ϕ₀ + (Δϕ * (((i - 2 * nbv + z) ÷ 2) - z)) / nbf
            isodd(i) ? Point(rmin2 * cos(ϕ), rmin2 * sin(ϕ), z) : Point(rmin1 * cos(ϕ), rmin1 * sin(ϕ), -z)
        elseif i == length(range)
            Point(0., 0., -z)
        elseif i == length(range) - 1
            Point(0., 0., z)
        end
    end
    return [inner(i) for i in range]
end

function GeometryBasics.faces(cone::G4Cons, facets=36)
    rmin1 = GetInnerRadiusMinusZ(cone)
    rmin2 = GetInnerRadiusPlusZ(cone)
    Δϕ    = GetDeltaPhiAngle(cone)
    
    issector = Δϕ < 2π
    ishollow = rmin1 > 0 || rmin2 > 0
    issector ?  facets =  round(Int64, (facets/2π) * Δϕ) : nothing
    isodd(facets) ? facets = 2 * div(facets, 2) : nothing
    facets < 8 ? facets = 8 : nothing
    nbf = Int(facets / 2)            # Number of faces
    nbv = issector ? nbf + 1 : nbf   # Number of vertices
    nbc = ishollow ? nbv : 1         # Number of centers
    indexes = Vector{QuadFace{Int64}}()
    for j in 1:nbf
        a,b = 2j-1, 2j
        c,d = !issector && j == nbf ? (1, 2) : (2j+1, 2j+2) 
        push!(indexes, (a,b,d,c))
        if ishollow
            a′,b′ = 2j-1+2nbv, 2j+2nbv
            c′,d′ = !issector && j == nbf ? (2nbv+1, 2nbv+2) : (2j+1+2nbv, 2j+2+2nbv)
            # inner wall
            push!(indexes, (a′,b′,d′,c′))
            # top
            push!(indexes, (c, c′, a′, a))
            # bottom
            push!(indexes, (b, b′, d′, d))
        else
            a′,b′ = 2nbv+1, 2nbv+2
            # top
            push!(indexes, (a′,a, c, c))
            # bottom
            push!(indexes, (b′,d, b, b))
        end
    end
    if issector
        # wedge walls
        a, b, c, d  = ( 1, 2, 2nbv-1, 2nbv)
        a′,b′,c′,d′ = ishollow ? (2nbv+1, 2nbv+2, 4nbv-1, 4nbv ) : (2nbv+1, 2nbv+2, 2nbv+1, 2nbv+2)
        push!(indexes, (a,  b, b′, a′))
        push!(indexes, (c′, d′, d, c ))
    end
    return indexes
end

#---G4Polycone-------------------------------------------------------------------------------------
mutable struct SideRZ
    r::Float64
    z::Float64
end

mutable struct PolyconeParams
    ϕ₀::Float64
    Δϕ::Float64
    n::Int32
    z::Ptr{Float64}
    rmin::Ptr{Float64}
    rmax::Ptr{Float64}
end

function GeometryBasics.coordinates(pcon::G4Polycone, facets=24)
    ϕ₀ = GetStartPhi(pcon)
    ϕₑ = GetEndPhi(pcon)
    n = GetNumRZCorner(pcon)
    issector = !(ϕₑ-ϕ₀ ≈ 2π)
    rz = [unsafe_load(Ptr{SideRZ}(GetPolyCorner(pcon, i-1).cpp_object)) for i in 1:n]
    ϕfacets = round(Int64, (facets/2π) * (ϕₑ-ϕ₀))
    ϕ = LinRange(ϕ₀, ϕₑ, ϕfacets)
    inner(ϕ, r, z) = Point(r * cos(ϕ), r * sin(ϕ), z)
    points =  vec([inner(ϕ, rz[j].r, rz[j].z) for ϕ in ϕ, j in 1:n])
    if issector
        params = unsafe_load(Ptr{PolyconeParams}(GetOriginalParameters(pcon).cpp_object))
        nz = params.n
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

function GeometryBasics.faces(pcon::G4Polycone, facets=24)
    ϕ₀ = GetStartPhi(pcon)
    ϕₑ = GetEndPhi(pcon)
    n = GetNumRZCorner(pcon)
    issector = !(ϕₑ-ϕ₀ ≈ 2π)
    ϕfacets = round(Int64, (facets/2π) * (ϕₑ-ϕ₀))
    idx = LinearIndices((ϕfacets, n))
    quad(i, j) = QuadFace{Int}(idx[i, j], idx[i + 1, j], idx[i + 1, cyc(j + 1,n)], idx[i, cyc(j + 1,n)])
    faces = vec([quad(i, j) for i in 1:(ϕfacets - 1), j in 1:n])
    if issector
        nz  = unsafe_load(Ptr{PolyconeParams}(GetOriginalParameters(pcon).cpp_object)).n
        offset = ϕfacets  * n
        for c in 0:1
            for i in 0:nz-2
                odx = offset + 2*i + 2*nz*c
                push!(faces, QuadFace{Int}(odx+1, odx+2, odx+4, odx+3))
            end
        end
    end
    return faces
end

#---G4GenericPolycone-------------------------------------------------------------------------------------

mutable struct GenericPolyconeParams
    startPhi::Float64
    endPhi::Float64
    phiIsOpen::Bool
    numCorner::Int32
    corners::Ptr{SideRZ}
end

function GeometryBasics.coordinates(pcon::G4GenericPolycone, facets=24)
    ϕ₀ = GetStartPhi(pcon)
    ϕₑ = GetEndPhi(pcon)
    n = GetNumRZCorner(pcon)
    issector = !(ϕₑ-ϕ₀ ≈ 2π)
    rz = [unsafe_load(Ptr{SideRZ}(GetPolyCorner(pcon, i-1).cpp_object)) for i in 1:n]
    ϕfacets = round(Int64, (facets/2π) * (ϕₑ-ϕ₀))
    ϕ = LinRange(ϕ₀, ϕₑ, ϕfacets)
    inner(ϕ, r, z) = Point(r * cos(ϕ), r * sin(ϕ), z)
    points =  vec([inner(ϕ, rz[j].r, rz[j].z) for ϕ in ϕ, j in 1:n])
    #if issector
    #    for ϕ in (ϕ₀, ϕₑ)
    #        for i in 1:n
    #            push!(points, Point(rz[i].r * cos(ϕ), rz[i].r * sin(ϕ), rz[i].z))
    #        end
    #    end
    #end
    return points
end

function GeometryBasics.faces(pcon::G4GenericPolycone, facets=24)
    ϕ₀ = GetStartPhi(pcon)
    ϕₑ = GetEndPhi(pcon)
    n = GetNumRZCorner(pcon)
    issector = !(ϕₑ-ϕ₀ ≈ 2π)
    ϕfacets = round(Int64, (facets/2π) * (ϕₑ-ϕ₀))
    idx = LinearIndices((ϕfacets, n))
    quad(i, j) = QuadFace{Int}(idx[i, j], idx[i + 1, j], idx[i + 1, cyc(j + 1,n)], idx[i, cyc(j + 1,n)])
    faces = vec([quad(i, j) for i in 1:(ϕfacets - 1), j in 1:n])
    #if issector
    #    offset = ϕfacets  * n
    #    for c in 0:1
    #        for i in 0:n-2
    #            odx = offset + 2*i + 2*n*c
    #            push!(faces, QuadFace{Int}(odx+1, odx+2, odx+4, odx+3))
    #        end
    #    end
    #end
    return faces
end