module G4Vis
    using Geant4
    using Makie
    using Colors

    import Base: convert

    include("Transformation3D.jl")

    function convert(::Type{Vector3{Float64}}, v::G4ThreeVector)
        Vector3{Float64}(x(v), y(v), z(v))
    end

    function convert(::Type{Point3{Float64}}, v::G4ThreeVector)
        Point3{Float64}(x(v), y(v), z(v))
    end
    function convert(::Type{RotMatrix3{Float64}}, r::CxxPtr{G4RotationMatrix})
        if r == C_NULL
            one(RotMatrix3{Float64})
        else  
            RotMatrix3{Float64}(xx(r[]), yx(r[]), zx(r[]), xy(r[]), yy(r[]), zy(r[]), xz(r[]), yz(r[]), zz(r[]))
        end
    end

    function convert(::Type{Tuple{RGB, Float64}}, c::ConstCxxRef{G4Colour})
        return (RGB(GetRed(c),GetGreen(c), GetBlue(c)),GetAlpha(c))
    end

    function GeometryBasics.Tesselation(s::G4VSolid, nvertices::NTuple{N,<:Integer}) where N
        return Tesselation{3,Float64,typeof(s),N}(s, Int.(nvertices))
    end
    GeometryBasics.mesh(s::G4VSolid) = GeometryBasics.mesh(Tesselation(s, 36), facetype=QuadFace{Int})

 
    colors = colormap("Grays", 8)

    function Geant4.draw(pv::G4VPhysicalVolume; wireframe::Bool=false, maxlevel::Int64=999)
        lv = GetLogicalVolume(pv)
        fig = Figure(size=(1280, 720))
        s = LScene(fig[1,1])
        draw!(s, lv[], one(Transformation3D{Float64}), 1, wireframe, maxlevel)
        return fig
    end

    function Geant4.draw(lv::G4LogicalVolume; wireframe::Bool=false, maxlevel::Int64=999)
        fig = Figure(size=(1280, 720))
        s = LScene(fig[1,1])
        draw!(s, lv, one(Transformation3D{Float64}), 1, wireframe, maxlevel)
        return fig
    end

    function Geant4.draw(solid::G4VSolid; wireframe::Bool=false, kwargs...)
        if wireframe
            m = GeometryBasics.mesh(solid)
            img = Makie.wireframe(m; linewidth=1, kwargs...)
        else
            points = GeometryBasics.coordinates(solid)
            faces  = GeometryBasics.faces(solid)
            #normals = GeometryBasics.normals(solid)
            m = GeometryBasics.normal_mesh(points, faces)
            img = Makie.mesh(m; kwargs...)
        end
        #display("image/png", img)
    end

    function Geant4.draw!(s, pv::G4VPhysicalVolume; wireframe::Bool=false, maxlevel::Int64=999)
        lv = GetLogicalVolume(pv)
        draw!(s, lv[], one(Transformation3D{Float64}), 1, wireframe, maxlevel)
    end

    using Geant4.SystemOfUnits:cm3,g

    function GetReplicaParameters(pv::CxxPtr{G4VPhysicalVolume})
        axis = Ref{EAxis}(kYAxis)
        nReplicas = Ref{Int32}(0)
        width = Ref{Float64}(0.)
        offset = Ref{Float64}(0.)
        consuming = Ref{UInt8}(0)
        GetReplicationData(pv, axis, nReplicas, width, offset, consuming)
        return (axis[], nReplicas[], width[])
    end

    const UnitOnAxis = [( 1,0,0), (0,1,0), (0,0,1)]

    function Geant4.draw!(s, lv::G4LogicalVolume, t::Transformation3D{Float64}, level::Int64, wireframe::Bool, maxlevel::Int64)
        vsolid = GetSolid(lv)
        tsolid = GetEntityType(vsolid)
        shape =  getproperty(Geant4,Symbol(tsolid))
        solid = CxxRef{shape}(vsolid)
        m = GeometryBasics.mesh(solid[])
        g4vis = GetVisAttributes(lv)
        if ! isempty(m)
            if ! isone(t)
                points = GeometryBasics.coordinates(m)
                faces  = GeometryBasics.faces(m)
                map!(c -> c * t, points, points)
                m = GeometryBasics.Mesh(meta(points; normals=normals(points, faces)), faces)
            end
            color = g4vis != C_NULL ? convert(Tuple{RGB, Float64}, GetColour(g4vis)) : (colors[level], GetDensity(GetMaterial(lv))/(12g/cm3))
            visible = g4vis != C_NULL ? IsVisible(g4vis) : true
            if wireframe
                wireframe!(s, m, linewidth=1, visible=visible)
            else
                mesh!(s, m, color=color, transparency=true, visible=visible )
            end
        end
        # Go down to the daughters (eventually)
        level >= maxlevel && return
        g4vis != C_NULL &&  IsDaughtersInvisible(g4vis) && return
        for idx in 1:GetNoDaughters(lv)
            daughter = GetDaughter(lv, idx-1)
            if IsReplicated(daughter)
                volume = GetLogicalVolume(daughter)
                axis, nReplicas, width = GetReplicaParameters(daughter)
                unitV = G4ThreeVector(UnitOnAxis[axis+1]...)
                for i in 1:nReplicas
                    g4t = unitV * (-width*(nReplicas-1)*0.5 + (i-1)*width)
                    transformation = Transformation3D{Float64}(one(RotMatrix3{Float64}), convert(Vector3{Float64}, g4t))
                    draw!(s, volume[], transformation * t, level+1, wireframe, maxlevel)
                end
            else    
                g4t = GetTranslation(daughter)
                g4r = GetRotation(daughter)
                transformation = Transformation3D{Float64}(convert(RotMatrix3{Float64}, g4r), convert(Vector3{Float64}, g4t))
                volume = GetLogicalVolume(daughter)
                draw!(s, volume[], transformation * t, level+1, wireframe, maxlevel)
            end
        end
    end

#---Testing functions------------------------------------------------------------
    @inline Base.:*(a::G4ThreeVector, b::Vector3{Float64}) = G4ThreeVector(x(a)*b[1], y(a)*b[2], z(a)*b[3])
    function Geant4.drawDistanceToOut(solid::G4VSolid, N::Int)
        lo = G4ThreeVector()
        hi = G4ThreeVector()
        BoundingLimits(solid, lo, hi)
        dim = hi - lo
        points = (lo + dim * rp for rp in rand(Vector3{Float64}, N))
        result = Vector{Point3{Float64}}()
        for point in points
            if Geant4.Inside(solid, point) == kInside
                dir = normalize(rand(Point3) + Point3(-.5,-.5,-.5))
                #push!(result, convert(Point3{Float64}, point))
                push!(result, convert(Point3{Float64}, point) + dir * DistanceToOut(solid, point, G4ThreeVector(dir...)))
            end
        end
        fig = Figure()
        s = LScene(fig[1, 1])
        scatter!(s, result, color=:black, markersize=1)
        #scatter!(s, [lo, hi], color=:blue, markersize=10)
        return fig
    end
   #---Utility  functions--------------------------------------------------------------------------
   cyc(x,n) = mod(x-1, n) + 1

   #---Basic solids--------------------------------------------------------------------------------
   include("Tubes.jl")
   include("Traps.jl")
   include("Torus.jl")
   include("Cones.jl")
   include("Sphere.jl")
   include("PGon.jl")

   #---Boolean solids------------------------------------------------------------------------------
   include("Boolean.jl")

   #---Event Display-------------------------------------------------------------------------------
   include("G4Display.jl")

end # module G4Visualization

