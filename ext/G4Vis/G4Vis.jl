module G4Vis
    using Geant4
    using Geant4.SystemOfUnits: g, cm3, cm
    using Makie
    using Colors

    include("Transformation3D.jl")
    include("VisUtils.jl")



    #---Get vertices and facets from G4VSolid---------------------------------------------------------   
    function mesh_constituents(s::G4VSolid; withnormals::Bool=false)
        ph = GetPolyhedron(s)
        if ph == C_NULL
            println("Solid of type $(GetEntityType(s)) and name $(GetName(s)) cannot be converted to a mesh for visualization")
            return (nothing, nothing, nothing)
        end
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

#---Visualization functions---------------------------------------------------------------------
    #---Solid-level drawing---------------------------------------------------------------------
    function Geant4.draw(solid::G4VSolid; wireframe::Bool=false, kwargs...)
        fig = Figure()
        s = LScene(fig[1, 1])
        draw!(s, solid; wireframe=wireframe, kwargs...)
        return fig
    end
    function Geant4.draw!(s, solid::G4VSolid; wireframe::Bool=false, kwargs...)
        ph = GetPolyhedron(solid)
        m = polyhedron_to_mesh(ph)
        if wireframe
            Makie.wireframe!(s, m; linewidth=1, kwargs...)
        else
            Makie.mesh!(s, m; kwargs...)
        end
    end

    #---PhysicalVolume-level drawing--------------------------------------------------------------
    function Geant4.draw(pv::G4VPhysicalVolume; wireframe::Bool=false, maxlevel::Int64=999, kwargs...)
        fig = Figure()
        s = LScene(fig[1, 1])
        draw!(s, GetLogicalVolume(pv)[]; wireframe=wireframe, maxlevel=maxlevel, kwargs...)
        return fig
    end
    function Geant4.draw!(s, pv::G4VPhysicalVolume; wireframe::Bool=false, maxlevel::Int64=999, kwargs...)
        draw!(s, GetLogicalVolume(pv)[]; wireframe=wireframe, maxlevel=maxlevel, kwargs...)
    end

    #---CxxPtr overloads---------------------------------------------------------------------------
    function Geant4.draw(pv::CxxPtr{G4VPhysicalVolume}; wireframe::Bool=false, maxlevel::Int64=999, kwargs...)
        fig = Figure()
        s = LScene(fig[1, 1])
        draw!(s, GetLogicalVolume(pv[])[]; wireframe=wireframe, maxlevel=maxlevel, kwargs...)
        return fig
    end
    function Geant4.draw!(s, pv::CxxPtr{G4VPhysicalVolume}; wireframe::Bool=false, maxlevel::Int64=999, kwargs...)
        draw!(s, GetLogicalVolume(pv[])[]; wireframe=wireframe, maxlevel=maxlevel, kwargs...)
    end

    #---LogicalVolume-level drawing----------------------------------------------------------------
    function Geant4.draw(lv::G4LogicalVolume; wireframe::Bool=false, maxlevel::Int64=999, kwargs...)
        fig = Figure()
        s = LScene(fig[1, 1])
        Geant4.draw!(s, lv; wireframe=wireframe, maxlevel=maxlevel, kwargs...)
        return fig
    end

    function Geant4.draw!(s, lv::G4LogicalVolume; wireframe::Bool=false, maxlevel::Int64=999, clip=:none, kwargs...)
        m_count = 0
        p_count = 0

        #---Collect the meshes recursively and Vis attributes recursively--------------------------
        println("Collecting LV meshes with clip=$clip...")
        @time col_meshes = collect_lv_meshes(lv; maxlevel, clip=clip)


        #---Count the total number of meshes and points to be drawn--------------------------------
        for ((color, visible), meshes) in col_meshes
            m_count += length(meshes)
            p_count += sum(length(m.position) for m in meshes)
        end

        #---Draw all collected meshes----------------------------------------------------------------
        println("Drawning $m_count meshes with total of $p_count points in $(length(col_meshes)) steps.")
        @time for ((color, visible), meshes) in col_meshes
            # chunk meshes by color and visibility to avoid overloading Makie with enormous mesh data
            for chunk in Iterators.partition(meshes, 256) 
                m = merge(chunk)
                if wireframe
                    Makie.wireframe!(s, m; linewidth=1, visible=visible, kwargs...)
                else
                    Makie.mesh!(s, m; color=color, visible=visible, kwargs...)
                end
            end
        end
        return s
    end

    function Geant4.get_lv_meshes(lv::G4LogicalVolume; maxlevel::Int=5, clip=:none)
        println("Collecting LV meshes with clip=$clip...")
        @time lv_meshes = collect_lv_meshes(lv; maxlevel, clip=clip)
        return lv_meshes
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

