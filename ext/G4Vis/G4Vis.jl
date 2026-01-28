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
    const LVColor = Union{ColorTypes.Color, Tuple{ColorTypes.RGB, Float64}}
    function convert(::Type{Tuple{RGB, Float64}}, c::ConstCxxRef{G4Colour})
        return (RGB(GetRed(c),GetGreen(c), GetBlue(c)),GetAlpha(c))
    end

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
        fig = Figure()
        s = LScene(fig[1, 1])
        if wireframe
            m = GeometryBasics.mesh(solid)
            Makie.wireframe!(s, m; linewidth=1, kwargs...)
        else
            m = GeometryBasics.mesh(solid; withnormals=true)
            Makie.mesh!(s, m; kwargs...)
        end
        return fig
    end
    function Geant4.draw!(s, solid::G4VSolid; wireframe::Bool=false, kwargs...)
        if wireframe
            m = GeometryBasics.mesh(solid)
            Makie.wireframe!(s, m; linewidth=1, kwargs...)
        else
            m = GeometryBasics.mesh(solid; withnormals=true)
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

    function Geant4.draw!(s, lv::G4LogicalVolume; wireframe::Bool=false, maxlevel::Int64=999, kwargs...)
        m_count = 0
        p_count = 0
        #---Collect the meshes recursively and Vis attributes recursively--------------------------
        # This assumes that all Placements of a given LogicalVolume are drawn with the same visibility and color
        lv_meshes = Dict{G4LogicalVolume, Tuple{Vector{GeometryBasics.Mesh}, LVColor, Bool}}()
        collect_meshes(lv, lv_meshes, one(Transformation3D{Float64}), 1, maxlevel)
        #---Draw all collected meshes----------------------------------------------------------------
        for (clv, (meshes, color, visible)) in lv_meshes
            m_count += length(meshes)
            p_count += sum(length(m.position) for m in meshes)   
            m = merge(meshes)
            if wireframe
                Makie.wireframe!(s, m; linewidth=1, visible=visible, kwargs...)
            else
                Makie.mesh!(s, m; color=color, visible=visible, kwargs...)
            end
        end
        println("Drawn $m_count meshes with total $p_count points in $(length(lv_meshes)) logical volumes steps.")
        return s
    end


#---Default color assignment--------------------------------------------------------------------

    colZ = fill(colorant"gray", 110)
    colZ[3] =  colorant"silver"       # Li
    colZ[4] =  colorant"slategray"    # Be
    colZ[5] =  colorant"gray30"       # B
    colZ[6] =  colorant"gray30"       # C
    colZ[7] =  colorant"skyblue"      # N
    colZ[8] =  colorant"white"        # O
    colZ[9] =  colorant"lightyellow"  # F
    colZ[10] = colorant"orange"       # Ne
    colZ[11] = colorant"silver"       # Na
    colZ[12] = colorant"silver"       # Mg
    colZ[13] = colorant"silver"       # Al
    colZ[14] = colorant"yellow"       # Si
    colZ[16] = colorant"yellowgreen"  # S
    colZ[20] = colorant"gold"         # Ca
    colZ[22] = colorant"lightgray"    # Ti
    colZ[24] = colorant"darkgray"     # Cr
    colZ[26] = colorant"orangered"    # Fe
    colZ[29] = colorant"blue"         # Cu
    colZ[47] = colorant"lightgray"    # Ag
    colZ[79] = colorant"gold"         # Au
    colZ[82] = colorant"lightyellow"  # Pb

    function default_color(mat::Union{G4Material, CxxPtr{G4Material}})
        #z = GetZ(mat)
        z = GetTotNbOfElectPerVolume(mat)/GetTotNbOfAtomsPerVolume(mat) |> round |> Int
        d = GetDensity(mat)
        return (colZ[z], d > 1g/cm3 ? 1. : d/(2g/cm3))
    end    
#---Helper functions for recursive drawing------------------------------------------------------
    const UnitOnAxis = [( 1,0,0), (0,1,0), (0,0,1)]

    function collect_meshes(lv::G4LogicalVolume, lv_meshes::Dict{G4LogicalVolume, Tuple{Vector{GeometryBasics.Mesh}, LVColor, Bool}}, t::Transformation3D{Float64}, level::Int64, maxlevel::Int64)
        solid = GetSolid(lv)
        g4vis = GetVisAttributes(lv)
        points, faces, normals = mesh_constituents(solid[], withnormals=true)
        if points !== nothing
            if ! isone(t)
                map!(c -> c * t, points, points)
                map!(n -> t.rotation * n, normals, normals)
            end
            m = GeometryBasics.Mesh(points, faces, normal=per_face(normals, faces))
            if haskey(lv_meshes, lv)
                push!(lv_meshes[lv][1], m)
            else
                color = g4vis != C_NULL ? convert(Tuple{RGB, Float64}, GetColour(g4vis)) : default_color(GetMaterial(lv))
                visible = g4vis != C_NULL ? IsVisible(g4vis) : color[2] >= 0.1 
                lv_meshes[lv] = ([m], color, visible)
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

