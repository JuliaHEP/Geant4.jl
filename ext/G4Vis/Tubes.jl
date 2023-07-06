#---G4Tubs--------------------------------------------------------------------------------------
function GeometryBasics.coordinates(tub::G4Tubs, facets=36)
    rmin = GetInnerRadius(tub)
    rmax = GetOuterRadius(tub)
    z     = GetZHalfLength(tub)
    ϕ₀    = GetStartPhiAngle(tub)
    Δϕ    = GetDeltaPhiAngle(tub)

    issector = Δϕ < 2π
    ishollow = rmin > 0
    issector ?  facets =  round(Int64, (facets/2π) * Δϕ) : nothing
    isodd(facets) ? facets = 2 * div(facets, 2) : nothing
    facets < 8 ? facets = 8 : nothing
    nbf = Int(facets / 2)            # Number of faces
    nbv = issector ? nbf + 1 : nbf   # Number of vertices
    nbc = ishollow ? nbv : 1         # Number of centers
    z = z
    range = 1:(2*nbv + 2*nbc)
    function inner(i)
        return if i <= 2*nbv
            ϕ = ϕ₀ + (Δϕ * (((i + 1) ÷ 2) - 1)) / nbf
            up = ifelse(isodd(i), z, -z)
            Point(rmax * cos(ϕ), rmax * sin(ϕ), up)
        elseif ishollow
            ϕ = ϕ₀ + (Δϕ * (((i - 2 * nbv + 1) ÷ 2) - 1)) / nbf
            up = ifelse(isodd(i), z, -z)
            Point(rmin * cos(ϕ), rmin * sin(ϕ), up)
        elseif i == length(range)
            Point(0., 0., -z)
        elseif i == length(range) - 1
            Point(0., 0., z)
        end
    end
    return (inner(i) for i in range)
end
    
function GeometryBasics.faces(tub::G4Tubs, facets=36)
    rmin = GetInnerRadius(tub)
    Δϕ    = GetDeltaPhiAngle(tub)
    issector = Δϕ < 2π
    ishollow = rmin > 0
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

function GeometryBasics.normals(tub::G4Tubs, facets=36)
    rmin = GetInnerRadius(tub)
    Δϕ    = GetDeltaPhiAngle(tub)
    issector = Δϕ < 2π
    ishollow = rmin > 0
    issector ?  facets =  round(Int64, (facets/2π) * Δϕ) : nothing
    isodd(facets) ? facets = 2 * div(facets, 2) : nothing
    facets < 8 ? facets = 8 : nothing
    nbf = Int(facets / 2)            # Number of faces
    nbv = issector ? nbf + 1 : nbf   # Number of vertices
    nbc = ishollow ? nbv : 1         # Number of centers
    range = 1:(2*nbv + 2*nbc)
    function inner(i)
        return if i <= 2*nbv
            ϕ = ϕ₀ + (Δϕ * (((i + 1) ÷ 2) - 1)) / nbf
            up = ifelse(isodd(i), 1/√2, -1/√2)
            Vector3(cos(ϕ)/√2, sin(ϕ)/√2, up)
        elseif ishollow
            ϕ = ϕ₀ + (Δϕ * (((i + 1) ÷ 2) - 1)) / nbf
            up = ifelse(isodd(i), 1/√2, -1/√2)
            Vector3(-cos(ϕ)/√2, -sin(ϕ)/√2, up)
        elseif i == length(range)
            Vector3(0., 0., -1.)
        elseif i == length(range) - 1
            Vector3(0., 0., 1.)
        end
    end
    return (inner(i) for i in range)
end

#---CutTubs----------------------------------------------------------------------------------------
function zLimit(tub::G4CutTubs, dz, r, ϕ)
    lownorm = GetLowNorm(tub)
    highnorm = GetHighNorm(tub)
    if dz < 0
        newz =  dz - r*(cos(ϕ) * x(lownorm) + sin(ϕ) * y(lownorm))/z(lownorm)
    else
        newz =  dz - r*(cos(ϕ) * x(highnorm) + sin(ϕ) * y(highnorm))/z(highnorm)
    end
end

function GeometryBasics.coordinates(tub::G4CutTubs, facets=36)
    rmin = GetInnerRadius(tub)
    rmax = GetOuterRadius(tub)
    z     = GetZHalfLength(tub)
    ϕ₀    = GetStartPhiAngle(tub)
    Δϕ    = GetDeltaPhiAngle(tub)
    issector = Δϕ < 2π
    ishollow = rmin > 0
    issector ?  facets =  round(Int64, (facets/2π) * Δϕ) : nothing
    isodd(facets) ? facets = 2 * div(facets, 2) : nothing
    facets < 8 ? facets = 8 : nothing
    nbf = Int(facets / 2)            # Number of faces
    nbv = issector ? nbf + 1 : nbf   # Number of vertices
    nbc = ishollow ? nbv : 1         # Number of centers
    range = 1:(2*nbv + 2*nbc)
    function inner(i)
        return if i <= 2*nbv
            ϕ = ϕ₀ + (Δϕ * (((i + 1) ÷ 2) - 1)) / nbf
            Point(rmax * cos(ϕ), rmax * sin(ϕ), zLimit(tub, z*(-1)^(i%2+1), rmax, ϕ))
        elseif ishollow
            ϕ = ϕ₀ + (Δϕ * (((i - 2 * nbv + 1) ÷ 2) - 1)) / nbf
            Point(rmin * cos(ϕ), rmin * sin(ϕ), zLimit(tub, z*(-1)^(i%2+1), rmin, ϕ))
        elseif i == length(range)
            Point(0., 0., -z)
        elseif i == length(range) - 1
            Point(0., 0., z)
        end
    end
    return [inner(i) for i in range]
end

function GeometryBasics.faces(tub::G4CutTubs, facets=36)
    rmin = GetInnerRadius(tub)
    rmax = GetOuterRadius(tub)
    z     = GetZHalfLength(tub)
    ϕ₀    = GetStartPhiAngle(tub)
    Δϕ    = GetDeltaPhiAngle(tub)
    GeometryBasics.faces(G4Tubs("",rmin, rmax, z, ϕ₀, Δϕ ), facets)
end
