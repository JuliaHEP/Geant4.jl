module G4Vis
    using Geant4
    using Geant4.SystemOfUnits: g, cm3, cm
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

    #---Color conversion-----------------------------------------------------------------------------
    const LVColor = Union{ColorTypes.Color, Tuple{ColorTypes.RGB{Float64}, Float64}}
    function convert(::Type{Tuple{RGB, Float64}}, c::ConstCxxRef{G4Colour})
        return (RGB(GetRed(c),GetGreen(c), GetBlue(c)),GetAlpha(c))
    end

    #---Get vertices and facets from G4VSolid---------------------------------------------------------   
    function mesh_constituents(s::G4VSolid; withnormals::Bool=false)
        ph = GetPolyhedron(s)
        nv = GetNoVertices(ph)
        nf = GetNoFacets(ph)
        points = map(1:nv) do i
            v = GetVertex(ph, i)
            Point3{Float64}(v[1], v[2], v[3])
        end
        faces = map(1:nf) do i
            nodes = Vector{Int32}(undef,4)
            n = Ref{Int32}(0)
            GetFacet(ph, i, n, nodes)
            if n[] == 3
                TriangleFace(nodes[1], nodes[2], nodes[3])
            elseif n[] == 4
                QuadFace(nodes[1], nodes[2], nodes[3], nodes[4])
            else
                error("Facet with $n nodes not supported")
            end
        end
        if withnormals
            normals = map(1:nf) do i
                n = GetNormal(ph, i)
                Vec3{Float64}(n[1], n[2], n[3])
            end
            return (points, faces, normals)
        else
            return (points, faces, nothing)
        end
    end

    #---Create GeometryBasics Mesh from G4VSolid-------------------------------------------------------
    function GeometryBasics.mesh(s::G4VSolid; withnormals::Bool=false)
        p, f, n = mesh_constituents(s; withnormals=withnormals)
        if withnormals
            return GeometryBasics.Mesh(p, f; normal=per_face(n,f))
        else
            return GeometryBasics.Mesh(p, f)
        end
    end

#---Visualization functions---------------------------------------------------------------------
    #---Solid-level drawing---------------------------------------------------------------------
    function Geant4.draw(solid::G4VSolid; wireframe::Bool=false, kwargs...)
        if wireframe
            m = GeometryBasics.mesh(solid)
            img = Makie.wireframe(m; linewidth=1, kwargs...)
        else
            m = GeometryBasics.mesh(solid; withnormals=true)
            img = Makie.mesh(m; kwargs...)
        end
    end

    #---PhysicalVolume-level drawing--------------------------------------------------------------
    function Geant4.draw(pv::G4VPhysicalVolume; wireframe::Bool=false, maxlevel::Int64=999)
        fig = Figure()
        s = LScene(fig[1, 1])
        draw!(s, GetLogicalVolume(pv)[]; wireframe=wireframe, maxlevel=maxlevel)
    end
    function Geant4.draw!(s, pv::G4VPhysicalVolume; wireframe::Bool=false, maxlevel::Int64=999)
        draw!(s, GetLogicalVolume(pv)[]; wireframe=wireframe, maxlevel=maxlevel)
    end

    #---CxxPtr overloads---------------------------------------------------------------------------
    function Geant4.draw(pv::CxxPtr{G4VPhysicalVolume}; wireframe::Bool=false, maxlevel::Int64=999)
        fig = Figure()
        s = LScene(fig[1, 1])
        draw!(s, GetLogicalVolume(pv[])[]; wireframe=wireframe, maxlevel=maxlevel)
    end
    function Geant4.draw!(s, pv::CxxPtr{G4VPhysicalVolume}; wireframe::Bool=false, maxlevel::Int64=999)
        draw!(s, GetLogicalVolume(pv[])[]; wireframe=wireframe, maxlevel=maxlevel)
    end

    #---LogicalVolume-level drawing----------------------------------------------------------------
    function Geant4.draw(lv::G4LogicalVolume; wireframe::Bool=false, maxlevel::Int64=999)
        fig = Figure()
        s = LScene(fig[1, 1])
        Geant4.draw!(s, lv; wireframe=wireframe, maxlevel=maxlevel)
        return fig
    end

    function Geant4.draw!(s, lv::G4LogicalVolume; wireframe::Bool=false, maxlevel::Int64=999)
        #---Collect the meshes recursively and Vis attributes recursively--------------------------
        # This assumes that all Placements of a given LogicalVolume are drawn with the same visibility and color
        lv_meshes = Dict{G4LogicalVolume, Tuple{Vector{GeometryBasics.Mesh}, LVColor, Bool}}()
        collect_meshes(lv, lv_meshes, one(Transformation3D{Float64}), 1, maxlevel)
        #---Draw all collected meshes----------------------------------------------------------------
        for (clv, (meshes, color, visible)) in lv_meshes
            m = merge(meshes)
            if wireframe
                Makie.wireframe!(s, m; linewidth=1, visible=visible)
            else
                Makie.mesh!(s, m; color=color, transparency=true, visible=visible)
            end
        end
    end

#---Helper functions for recursive drawing------------------------------------------------------
    const colors = colormap("Grays", 8)
    const UnitOnAxis = [( 1,0,0), (0,1,0), (0,0,1)]

    function collect_meshes(lv::G4LogicalVolume, lv_meshes::Dict{G4LogicalVolume, Tuple{Vector{GeometryBasics.Mesh}, LVColor, Bool}}, t::Transformation3D{Float64}, level::Int64, maxlevel::Int64)
        solid = GetSolid(lv)
        g4vis = GetVisAttributes(lv)
        points, faces, normals = mesh_constituents(solid[], withnormals=true)
        if ! isone(t)
            map!(c -> c * t, points, points)
            map!(n -> t.rotation * n, normals, normals)
        end
        m = GeometryBasics.Mesh(points, faces, normal=per_face(normals, faces))
        if haskey(lv_meshes, lv)
            push!(lv_meshes[lv][1], m)
        else
            color = g4vis != C_NULL ? convert(Tuple{RGB, Float64}, GetColour(g4vis)) : (colors[level], GetDensity(GetMaterial(lv))/(12g/cm3))
            visible = g4vis != C_NULL ? IsVisible(g4vis) : true
            lv_meshes[lv] = ([m], color, visible)
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
                    collect_meshes(volume[], lv_meshes, transformation * t, level+1, maxlevel)
                end
            else    
                g4t = GetTranslation(daughter)
                g4r = GetRotation(daughter)
                transformation = Transformation3D{Float64}(convert(RotMatrix3{Float64}, g4r), convert(Vector3{Float64}, g4t))
                volume = GetLogicalVolume(daughter)
                collect_meshes(volume[], lv_meshes, transformation * t, level+1, maxlevel)
            end
        end
    end

    function GetReplicaParameters(pv::CxxPtr{G4VPhysicalVolume})
        axis = Ref{EAxis}(kYAxis)
        nReplicas = Ref{Int32}(0)
        width = Ref{Float64}(0.)
        offset = Ref{Float64}(0.)
        consuming = Ref{UInt8}(0)
        GetReplicationData(pv, axis, nReplicas, width, offset, consuming)
        return (axis[], nReplicas[], width[])
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


   #---Event Display-------------------------------------------------------------------------------
   include("G4Display.jl")

end # module G4Visualization

