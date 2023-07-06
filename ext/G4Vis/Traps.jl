#---G4Box--------------------------------------------------------------------------------------
function GeometryBasics.coordinates(box::G4Box, facets=6)
    x, y, z = GetXHalfLength(box), GetYHalfLength(box), GetZHalfLength(box)
    return Point3{Float64}[(-x,-y,-z), (-x,-y, z), (-x, y, z), (-x, y,-z),
                            (-x,-y,-z), ( x,-y,-z), ( x,-y, z), (-x,-y, z),
                            (-x,-y,-z), (-x, y,-z), ( x, y,-z), ( x,-y,-z), 
                            ( x, y, z), (-x, y, z), (-x,-y, z), ( x,-y, z),
                            ( x, y, z), ( x,-y, z), ( x,-y,-z), ( x, y,-z),
                            ( x, y, z), ( x, y,-z), (-x, y,-z), (-x, y, z)]
end

function GeometryBasics.faces(::G4Box, facets=6)
    return QuadFace{Int}[(1,2,3,4), (5,6,7,8), (9,10,11,12), (13,14,15,16), (17,18,19,20), (21,22,23,24)]
end

#---G4Trd--------------------------------------------------------------------------------------
function GeometryBasics.coordinates(trd::G4Trd, facets=6)
    x1 = GetXHalfLength1(trd)
    x2 = GetXHalfLength2(trd)
    y1 = GetYHalfLength1(trd)
    y2 = GetYHalfLength2(trd)
    z  = GetZHalfLength(trd)
    Point3{Float64}[(-x1,-y1,-z), ( x1,-y1,-z), (-x1, y1,-z), ( x1, y1,-z),
                    (-x2,-y2, z), ( x2,-y2, z), (-x2, y2, z), ( x2, y2, z)]
end

function GeometryBasics.faces(::G4Trd, facets=6)
    iface = (( 1,5,6,2),(3,4,8,7),( 1,3,7,5),(2,6,8,4),( 1,2,4,3),(5,6,8,7))
    [QuadFace{Int64}(f...) for f in iface]
end

#---G4Para--------------------------------------------------------------------------------------
function GeometryBasics.coordinates(par::G4Para, facets=6)
    x = GetXHalfLength(par)
    y = GetYHalfLength(par)
    z = GetZHalfLength(par)
    α = GetAlpha(par)
    θ = GetTheta(par)
    ϕ = GetPhi(par)

    ztθcϕ = z * tan(θ) * cos(ϕ)
    ztθsϕ = z * tan(θ) * sin(ϕ)
    ytα = y * tan(α)

    Point3{Float64}[(-ztθcϕ - ytα - x, -ztθsϕ - y, -z),
                    (-ztθcϕ - ytα + x, -ztθsϕ - y, -z),
                    (-ztθcϕ + ytα - x, -ztθsϕ + y, -z),
                    (-ztθcϕ + ytα + x, -ztθsϕ + y, -z),
                    ( ztθcϕ - ytα - x,  ztθsϕ - y,  z),
                    ( ztθcϕ - ytα + x,  ztθsϕ - y,  z),
                    ( ztθcϕ + ytα - x,  ztθsϕ + y,  z),
                    ( ztθcϕ + ytα + x,  ztθsϕ + y,  z)]
end

function GeometryBasics.faces(::G4Para, facets=6)
    iface = (( 1,5,6,2),(3,4,8,7),( 1,3,7,5),(2,6,8,4),( 1,2,4,3),(5,6,8,7))
    [QuadFace{Int64}(f...) for f in iface]
end

#---G4Trap--------------------------------------------------------------------------------------
function GeometryBasics.coordinates(par::G4Trap, facets=6)
    x₁ = GetXHalfLength1(par)
    x₂ = GetXHalfLength2(par)
    x₃ = GetXHalfLength3(par)
    x₄ = GetXHalfLength4(par)
    y₁ = GetYHalfLength1(par)
    y₂ = GetYHalfLength2(par)
    z = GetZHalfLength(par)
    α₁ = GetAlpha1(par)
    α₂ = GetAlpha2(par)
    θ = GetTheta(par)
    ϕ = GetPhi(par)

    ztθcϕ = z * tan(θ) * cos(ϕ)
    ztθsϕ = z * tan(θ) * sin(ϕ)

    Point3{Float64}[(-ztθcϕ - y₁*tan(α₁) - x₁, -ztθsϕ - y₁, -z),
                    (-ztθcϕ - y₁*tan(α₁) + x₁, -ztθsϕ - y₁, -z),
                    (-ztθcϕ + y₁*tan(α₁) - x₂, -ztθsϕ + y₁, -z),
                    (-ztθcϕ + y₁*tan(α₁) + x₂, -ztθsϕ + y₁, -z),
                    ( ztθcϕ - y₂*tan(α₂) - x₃,  ztθsϕ - y₂,  z),
                    ( ztθcϕ - y₂*tan(α₂) + x₃,  ztθsϕ - y₂,  z),
                    ( ztθcϕ + y₂*tan(α₂) - x₄,  ztθsϕ + y₂,  z),
                    ( ztθcϕ + y₂*tan(α₂) + x₄,  ztθsϕ + y₂,  z)]
end

function GeometryBasics.faces(::G4Trap, facets=6)
    iface = (( 1,5,6,2),(3,4,8,7),( 1,3,7,5),(2,6,8,4),( 1,2,4,3),(5,6,8,7))
    [QuadFace{Int64}(f...) for f in iface]
end