#---G4Orb----------------------------------------------------------------------------------------
function GeometryBasics.coordinates(orb::G4Orb, nvertices=24)
    r = GetRadius(orb)
    θ = LinRange(0, π, nvertices)
    ϕ = LinRange(0, 2π, nvertices)
    inner(θ, ϕ) = Point(cos(ϕ) * sin(θ), sin(ϕ) * sin(θ), cos(θ)) .* r 
    return vec([inner(θ, ϕ) for θ in θ, ϕ in ϕ])
end
function GeometryBasics.faces(::G4Orb, nvertices=24)
    idx = LinearIndices((nvertices, nvertices))
    quad(i, j) = QuadFace{Int}(idx[i, j], idx[i + 1, j], idx[i + 1, j + 1], idx[i, j + 1])
    return vec([quad(i, j) for i in 1:(nvertices - 1), j in 1:(nvertices - 1)])
end
function GeometryBasics.normals(::G4Orb, nvertices=24)
    return GeometryBasics.coordinates(G4Orb("",1), nvertices)
end

#---G4Sphere--------------------------------------------------------------------------------------
function GeometryBasics.coordinates(sph::G4Sphere, nvertices=24)
    rmin = GetInnerRadius(sph)
    rmax = GetOuterRadius(sph)
    ϕ₀   = GetStartPhiAngle(sph)
    Δϕ   = GetDeltaPhiAngle(sph)
    θ₀   = GetStartThetaAngle(sph)
    Δθ   = GetDeltaThetaAngle(sph)
    ϕfacets = round(Int64, (nvertices/2π) * Δϕ)
    θfacets = round(Int64, (nvertices/π) * Δθ)
    θ = LinRange(θ₀, θ₀+Δθ, θfacets)
    ϕ = LinRange(ϕ₀, ϕ₀+Δϕ, ϕfacets)
    inner(θ, ϕ) = Point(cos(ϕ) * sin(θ), sin(ϕ) * sin(θ), cos(θ))
    oshell = [inner(θ, ϕ) * rmax for θ in θ, ϕ in ϕ]
    ishell = rmin > 0 ? [inner(θ, ϕ) * rmin for θ in θ, ϕ in ϕ] : (Δϕ < 2π || Δθ < π) ? [Point(0,0,0)] : []
    return [vec(oshell); vec(ishell)] 
end

function GeometryBasics.faces(sph::G4Sphere, nvertices=24)
    rmin = GetInnerRadius(sph)
    Δϕ   = GetDeltaPhiAngle(sph)
    Δθ   = GetDeltaThetaAngle(sph)
    ϕfacets = round(Int64, (nvertices/2π) * Δϕ)
    θfacets = round(Int64, (nvertices/π) * Δθ)
    idx = LinearIndices((θfacets, ϕfacets))
    nf = ϕfacets * θfacets
    quad(i, j) = QuadFace{Int}(idx[i, j], idx[i + 1, j], idx[i + 1, j + 1], idx[i, j + 1])
    faces = vec([quad(i, j) for i in 1:(θfacets - 1), j in 1:(ϕfacets - 1)])
    if rmin > 0
        for q in vec([quad(i,j) .+ nf for i in 1:(θfacets - 1), j in 1:(ϕfacets - 1)])
            push!(faces, q)
        end
        if π - Δϕ > 0 || π - Δθ > 0
            bidx =  [idx[1,1:end-1];idx[1:end-1,end];idx[end,end:-1:2];idx[end:-1:1,1]]
            for i in 1:2(ϕfacets + θfacets)-4
                push!(faces, QuadFace{Int}(bidx[i], bidx[i+1], bidx[i+1]+nf, bidx[i]+nf)) 
            end
        end
    else
        if 2π - Δϕ > 0 || π - Δθ > 0
            bidx =  [idx[1,1:end-1];idx[1:end-1,end];idx[end,end:-1:2];idx[end:-1:1,1]]
            for i in 1:2(ϕfacets + θfacets)-4
                push!(faces, QuadFace{Int}(bidx[i], bidx[i+1], nf+1, nf+1)) 
            end
        end

    end
    return faces
end

#---G4Ellipsoid------------------------------------------------------------------------------------
function GeometryBasics.coordinates(ellip::G4Ellipsoid, nvertices=24)
    dx = GetDx(ellip)
    dy = GetDy(ellip)
    dz = GetDz(ellip)
    topz = GetZTopCut(ellip)
    botz = GetZBottomCut(ellip)
    ϕfacets = nvertices
    θfacets = nvertices ÷ 2
    θ = LinRange(acos(topz/dz), acos(botz/dz), θfacets)
    ϕ = LinRange(0, 2π, ϕfacets)
    inner(θ, ϕ) = Point(dx * cos(ϕ) * sin(θ), dy * sin(ϕ) * sin(θ), dz * cos(θ))
    points = vec([inner(θ, ϕ) for θ in θ, ϕ in ϕ])
    push!(points, Point(0,0,topz), Point(0,0,botz))
    return points
end

function GeometryBasics.faces(::G4Ellipsoid, nvertices=24)
    ϕfacets = nvertices
    θfacets = nvertices ÷ 2
    idx = LinearIndices((θfacets, ϕfacets))
    quad(i, j) = QuadFace{Int}(idx[i, j], idx[i + 1, j], idx[i + 1, j + 1], idx[i, j + 1])
    faces = vec([quad(i, j) for i in 1:(θfacets - 1), j in 1:(ϕfacets - 1)])
    for j in 1:(ϕfacets - 1)
        push!(faces, QuadFace{Int}(idx[1,j], length(idx)+1, length(idx)+1, idx[1,j+1]),
                     QuadFace{Int}(idx[end,j], length(idx)+2, length(idx)+2, idx[end,j+1]))
    end
    return faces
end
