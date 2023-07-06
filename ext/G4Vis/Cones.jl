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

function GeometryBasics.coordinates(pcon::G4Polycone, facets=36)
    ϕ₀ = GetStartPhi(pcon)
    ϕₑ = GetEndPhi(pcon)
    n = GetNumRZCorner(pcon)
    rz = [unsafe_load(Ptr{SideRZ}(GetPolyCorner(pcon, i-1).cpp_object)) for i in 1:n]
    ϕfacets = round(Int64, (facets/2π) * (ϕₑ-ϕ₀))
    ϕ = LinRange(ϕ₀, ϕₑ, ϕfacets)
    inner(ϕ, r, z) = Point(r * cos(ϕ), r * sin(ϕ), z)
    return vec([inner(ϕ, rz[j].r, rz[j].z) for ϕ in ϕ, j in 1:n])
end

function GeometryBasics.faces(pcon::G4Polycone, facets=36)
    ϕ₀ = GetStartPhi(pcon)
    ϕₑ = GetEndPhi(pcon)
    n = GetNumRZCorner(pcon)
    issector = !(ϕₑ-ϕ₀ ≈ 2π)
    ϕfacets = round(Int64, (facets/2π) * (ϕₑ-ϕ₀))
    idx = LinearIndices((ϕfacets, n))
    quad(i, j) = QuadFace{Int}(idx[i, j], idx[i + 1, j], idx[i + 1, j + 1], idx[i, j + 1])
    faces = vec([quad(i, j) for i in 1:(ϕfacets - 1), j in 1:(n - 1)])
    if issector
        # TODO the phi planes
    end
    return faces
end
