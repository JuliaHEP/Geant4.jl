#---G4Sphere--------------------------------------------------------------------------------------
function GeometryBasics.coordinates(tor::G4Torus, nvertices=48)
    rmin = GetRmin(tor)
    rmax = GetRmax(tor)
    rtor = GetRtor(tor)
    ϕ₀   = GetSPhi(tor)
    Δϕ   = GetDPhi(tor)
    ϕfacets = round(Int64, (nvertices/2π) * Δϕ)
    θfacets = round(Int64, nvertices/2)
    θ = LinRange(0, 2π, θfacets)
    ϕ = LinRange(ϕ₀, ϕ₀+Δϕ, ϕfacets)
    inner(θ, ϕ, r, R) = Point((R + r * cos(θ))* cos(ϕ), (R + r * cos(θ)) * sin(ϕ), r * sin(θ))
    oshell = [inner(θ, ϕ, rmax, rtor) for θ in θ, ϕ in ϕ]
    ishell = rmin > 0 ? [inner(θ, ϕ, rmin, rtor) for θ in θ, ϕ in ϕ] : Δϕ < 2π  ? [Point(rtor*cos(ϕ₀),rtor*sin(ϕ₀), 0), Point(rtor*cos(ϕ₀+Δϕ),rtor*sin(ϕ₀+Δϕ), 0)] : []
    return [vec(oshell); vec(ishell)] 
end

function GeometryBasics.faces(tor::G4Torus, nvertices=48)
    rmin = GetRmin(tor)
    Δϕ   = GetDPhi(tor)
    ϕfacets = round(Int64, (nvertices/2π) * Δϕ)
    θfacets = round(Int64, nvertices/2)
    idx = LinearIndices((θfacets, ϕfacets))
    nf = ϕfacets * θfacets
    quad(i, j) = QuadFace{Int}(idx[i, j], idx[i + 1, j], idx[i + 1, j + 1], idx[i, j + 1])
    faces = vec([quad(i, j) for i in 1:(θfacets - 1), j in 1:(ϕfacets - 1)])
    if rmin > 0
        for q in vec([quad(i,j) .+ nf for i in 1:(θfacets - 1), j in 1:(ϕfacets - 1)])
            push!(faces, q)
        end
        if Δϕ < 2π
            for i in 1:(θfacets - 1)
                push!(faces, QuadFace{Int}(idx[i, 1], idx[i+1, 1], idx[i+1, 1]+nf, idx[i, 1]+nf))
                push!(faces, QuadFace{Int}(idx[i, end], idx[i+1, end], idx[i+1, end]+nf, idx[i+1, end]+nf))
            end
        end
    else
        if Δϕ < 2π
            for i in 1:(θfacets - 1)
                push!(faces, QuadFace{Int}(idx[i, 1], idx[i + 1, 1], nf + 1, nf + 1))
                push!(faces, QuadFace{Int}(idx[i, end], idx[i + 1, end], nf + 2, nf + 2))
            end
        end

    end
    return faces
end