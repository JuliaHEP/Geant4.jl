import Base: convert

#---Conversion and utility functions----------------------------------------------------------------

"""
    convert(::Type{Vector3{Float64}}, v::G4ThreeVector)

Convert a G4ThreeVector to a Vector3{Float64}.
"""
function Base.convert(::Type{Vector3{Float64}}, v::G4ThreeVector)
    Vector3{Float64}(x(v), y(v), z(v))
end

"""
    Base.convert(::Type{Point3{Float64}}, v::G4ThreeVector)

Convert a G4ThreeVector to a Point3{Float64}.
"""
function Base.convert(::Type{Point3{Float64}}, v::G4ThreeVector)
    Point3{Float64}(x(v), y(v), z(v))
end

"""
    Base.convert(::Type{RotMatrix3{Float64}}, r::CxxPtr{G4RotationMatrix})

Convert a G4RotationMatrix to a RotMatrix3{Float64}. If the pointer is null, return the identity matrix.
"""
function Base.convert(::Type{RotMatrix3{Float64}}, r::CxxPtr{G4RotationMatrix})
    if r == C_NULL
        one(RotMatrix3{Float64})
    else  
        RotMatrix3{Float64}(xx(r[]), yx(r[]), zx(r[]), xy(r[]), yy(r[]), zy(r[]), xz(r[]), yz(r[]), zz(r[]))
    end
end

#---Color conversion-----------------------------------------------------------------------------
const LVColor = Union{ColorTypes.Color, Tuple{ColorTypes.RGB, Float64}}

"""
    Base.convert(::Type{Tuple{RGB, Float64}}, c::ConstCxxRef{G4Colour})

Convert a G4Colour to a tuple of RGB and alpha. The RGB values are in the range [0,1].
"""
function Base.convert(::Type{Tuple{RGB, Float64}}, c::ConstCxxRef{G4Colour})
    return (RGB(GetRed(c),GetGreen(c), GetBlue(c)),GetAlpha(c))
end

#---Color lookup table by atomic number------------------------------------------------------------
const colZ = let c = fill(colorant"gray", 110)
    c[3]  = colorant"silver"       # Li
    c[4]  = colorant"slategray"    # Be
    c[5]  = colorant"gray30"       # B
    c[6]  = colorant"gray30"       # C
    c[7]  = colorant"skyblue"      # N
    c[8]  = colorant"white"        # O
    c[9]  = colorant"lightyellow"  # F
    c[10] = colorant"orange"       # Ne
    c[11] = colorant"silver"       # Na
    c[12] = colorant"silver"       # Mg
    c[13] = colorant"silver"       # Al
    c[14] = colorant"yellow"       # Si
    c[16] = colorant"yellowgreen"  # S
    c[20] = colorant"gold"         # Ca
    c[22] = colorant"lightgray"    # Ti
    c[24] = colorant"darkgray"     # Cr
    c[26] = colorant"orangered"    # Fe
    c[29] = colorant"blue"         # Cu
    c[47] = colorant"lightgray"    # Ag
    c[79] = colorant"gold"         # Au
    c[82] = colorant"lightyellow"  # Pb
    c
end

function default_color(mat)
    z = GetTotNbOfElectPerVolume(mat) / GetTotNbOfAtomsPerVolume(mat) |> round |> Int
    d = GetDensity(mat)
    return (colZ[z], d > 0.25g/cm3 ? 1.0 : -1.0)
end

#---Mesh conversion from G4Polyhedron----------------------------------------------------------------
# Debug counter for mesh processing
const _mesh_counter = Ref{Int}(0)

"""
    polyhedron_to_mesh(ph, t::Transformation3D{Float64}) -> Union{GeometryBasics.Mesh, Nothing}

Convert a Geant4 polyhedron to a GeometryBasics mesh with smooth per-vertex normals
and correct hard-edge handling.

Uses index-based GetVertex/GetFacet instead of the slow stateful GetNextVertex iterator.
Vertices at hard edges (crease angle > threshold) are duplicated so that each smooth
group gets its own normal. This prevents the renderer from flipping shading normals
due to winding/normal disagreement at sharp features.

Returns nothing if the polyhedron is invalid or empty.
"""
function polyhedron_to_mesh(ph; transform::Transformation3D{Float64}=one(Transformation3D{Float64}), crease_cos::Float64=0.5)
    ph == C_NULL && return nothing

    nv = GetNoVertices(ph)
    nf = GetNoFacets(ph)
    (nv <= 0 || nf <= 0) && return nothing

    # Debug: track mesh count
    _mesh_counter[] += 1
    if _mesh_counter[] % 100 == 0
        #println("Processing mesh #$(_mesh_counter[]), nv=$nv, nf=$nf")
    end

    # Collect all vertices at once (nv FFI calls)
    local_points = Vector{Vec3{Float64}}(undef, nv)
    world_points = Vector{Point3{Float64}}(undef, nv)
    for i in 1:nv
        v = GetVertex(ph, i)
        p_local = Vec3{Float64}(v[1], v[2], v[3])
        local_points[i] = p_local
        world_points[i] = Point3{Float64}(apply_transform(transform, p_local)...)
    end

    # Pass 1: Collect face data (nf FFI calls for GetFacet + nf for GetNormal)
    # Store: face vertex indices, face normal (world space), vertex count per face
    face_verts = Vector{NTuple{4,Int32}}(undef, nf)
    face_nverts = Vector{Int}(undef, nf)
    face_normals_world = Vector{Vec3{Float64}}(undef, nf)
    # vertex → list of face indices
    vert_faces = [Int[] for _ in 1:nv]

    nodes_buf = Vector{Int32}(undef, 4)
    n_ref = Ref{Int32}(0)
    valid_faces = 0

    for i in 1:nf
        GetFacet(ph, i, n_ref, nodes_buf)
        nn = n_ref[]
        nn < 3 && continue
        valid_faces += 1

        g4n = GetNormal(ph, i)
        g4_normal = Vec3{Float64}(g4n[1], g4n[2], g4n[3])
        g4_world = transform.rotation' * g4_normal
        g4_len = LinearAlgebra.norm(g4_world)
        if g4_len > 0
            g4_world = g4_world / g4_len
        end

        face_verts[valid_faces] = (nodes_buf[1], nodes_buf[2], nodes_buf[3], nodes_buf[4])
        face_nverts[valid_faces] = nn
        face_normals_world[valid_faces] = g4_world

        for j in 1:nn
            push!(vert_faces[nodes_buf[j]], valid_faces)
        end
    end

    valid_faces == 0 && return nothing

    # Pass 2: For each (vertex, face) pair, compute the smooth normal by averaging
    # normals from adjacent faces at that vertex within the crease angle.
    # If a vertex has multiple smooth groups, it gets duplicated.
    out_points = Point3{Float64}[]
    out_normals = Vec3{Float32}[]
    # Map (original_vertex, face_index) → new vertex index
    # We use a per-vertex group assignment to reuse indices within smooth groups.
    vert_new_idx = Vector{Vector{Tuple{Vec3{Float64}, Int}}}(undef, nv)
    for i in 1:nv
        vert_new_idx[i] = Tuple{Vec3{Float64}, Int}[]
    end

    function get_or_create_vertex(vi::Int32, face_idx::Int)
        fn = face_normals_world[face_idx]
        # Compute smooth normal for this vertex from compatible adjacent faces
        smooth_n = Vec3{Float64}(0, 0, 0)
        for adj_fi in vert_faces[vi]
            if LinearAlgebra.dot(face_normals_world[adj_fi], fn) >= crease_cos
                smooth_n += face_normals_world[adj_fi]
            end
        end
        sn_len = LinearAlgebra.norm(smooth_n)
        smooth_n = sn_len > 0 ? smooth_n / sn_len : fn

        # Check if we already have a vertex with this smooth normal
        for (existing_n, idx) in vert_new_idx[vi]
            if LinearAlgebra.dot(existing_n, smooth_n) > 0.999
                return idx
            end
        end

        # Create new vertex
        push!(out_points, world_points[vi])
        push!(out_normals, Vec3{Float32}(smooth_n...))
        new_idx = length(out_points)
        push!(vert_new_idx[vi], (smooth_n, new_idx))
        return new_idx
    end

    # Pass 3: Build faces with new vertex indices + winding check
    out_faces = Vector{Union{TriangleFace, QuadFace}}()
    sizehint!(out_faces, valid_faces)

    for fi in 1:valid_faces
        fv = face_verts[fi]
        nn = face_nverts[fi]

        # Get new vertex indices
        new_vi = ntuple(j -> get_or_create_vertex(fv[j], fi), nn)

        # Winding check: geometric normal from world-space points vs face normal
        p1 = out_points[new_vi[1]]
        p2 = out_points[new_vi[2]]
        p3 = out_points[new_vi[3]]
        e1 = Vec3{Float64}((p2 - p1)...)
        e2 = Vec3{Float64}((p3 - p1)...)
        geo_n = Vec3{Float64}(
            e1[2]*e2[3] - e1[3]*e2[2],
            e1[3]*e2[1] - e1[1]*e2[3],
            e1[1]*e2[2] - e1[2]*e2[1]
        )
        needs_flip = LinearAlgebra.dot(geo_n, face_normals_world[fi]) < 0

        if nn == 3
            if needs_flip
                push!(out_faces, TriangleFace(new_vi[1], new_vi[3], new_vi[2]))
            else
                push!(out_faces, TriangleFace(new_vi[1], new_vi[2], new_vi[3]))
            end
        elseif nn == 4
            if needs_flip
                push!(out_faces, QuadFace(new_vi[1], new_vi[4], new_vi[3], new_vi[2]))
            else
                push!(out_faces, QuadFace(new_vi[1], new_vi[2], new_vi[3], new_vi[4]))
            end
        end
    end

    isempty(out_faces) && return nothing
    return GeometryBasics.Mesh(out_points, out_faces; normal=out_normals)
end

const UnitOnAxis = [( 1,0,0), (0,1,0), (0,0,1)]

"""
    collect_meshes_with_cut!(lv, lv_meshes, cutter, cutter_offset, t, level, maxlevel)

Recursively collect meshes from a logical volume hierarchy, applying a quadrant cut
to remove the x>0, y>0 region in world coordinates. Also collects the cut-out pieces
for glass visualization.

# Arguments
- `lv::G4LogicalVolume`: The logical volume to process
- `lv_meshes::Dict`: Output dictionary mapping LogicalVolume -> (meshes, color, visible)
- `cutter::G4VSolid`: The cutting solid (typically a large box)
- `cutter_offset::Vec3{Float64}`: Center of the cutter in world coordinates
- `t::Transformation3D{Float64}`: Accumulated transform from world to this volume
- `level::Int64`: Current recursion depth
- `maxlevel::Int64`: Maximum recursion depth
"""
function collect_meshes_with_cut!(
    lv::G4LogicalVolume,
    lv_meshes::Dict{G4LogicalVolume, Tuple{Vector{GeometryBasics.Mesh}, LVColor, Bool}},
    cutter::Union{G4VSolid, Nothing},
    cutter_offset::Vec3{Float64},
    t::Transformation3D{Float64},
    level::Int64,
    maxlevel::Int64
)
    solid = GetSolid(lv)
    g4vis = GetVisAttributes(lv)

    # Transform the cutter into the local coordinate system
    local_cutter_pos = apply_inv_transform(t, Vec3{Float64}(cutter_offset...))

    # Build G4RotationMatrix from accumulated rotation
    R = t.rotation
    rotColX = G4ThreeVector(R[1,1], R[2,1], R[3,1])
    rotColY = G4ThreeVector(R[1,2], R[2,2], R[3,2])
    rotColZ = G4ThreeVector(R[1,3], R[2,3], R[3,3])
    g4rot = G4RotationMatrix(rotColX, rotColY, rotColZ)
    local_cutter_transform = G4Transform3D(
        g4rot,
        G4ThreeVector(local_cutter_pos[1], local_cutter_pos[2], local_cutter_pos[3])
    )

    # Get the original solid's polyhedron
    ph_orig = GetPolyhedron(solid[])
    if ph_orig == C_NULL
        @goto after_mesh
    end

    nv_orig = GetNoVertices(ph_orig)
    if nv_orig <= 0
        @goto after_mesh
    end

    local ph
    local cut_solid_ref = nothing  # Keep reference alive to prevent GC
    local intersect_solid_ref = nothing  # Keep reference alive for intersection solid

    # Get color info for this logical volume
    color = g4vis != C_NULL ? convert(Tuple{RGB, Float64}, GetColour(g4vis)) : default_color(GetMaterial(lv))
    visible = g4vis != C_NULL ? IsVisible(g4vis) : color[2] > 0

    if !visible
        @goto after_mesh
    end

    # Check if we need to cut at all
    if cutter === nothing
        ph = ph_orig
        @goto before_mesh
    end

    # Check if cutting is needed by examining vertices in world space
    # Use GC.@preserve to ensure solid stays alive while we access ph_orig
    needs_cut = false
    all_inside_cutter = true
    GC.@preserve solid for i in 1:nv_orig
        v = GetVertex(ph_orig, i)
        p_cutter = apply_transform(t, Vec3{Float64}(v[1], v[2], v[3])) - cutter_offset # Transform to cutter-centered coordinates
        in_cutter = Geant4.Inside(cutter, G4ThreeVector(p_cutter...)) == kInside
        if in_cutter
            needs_cut = true
        else
            all_inside_cutter = false
        end
    end

    # If all vertices are inside the cutter, solid is completely removed
    if all_inside_cutter
        @goto after_mesh
    end

    # Choose which polyhedron to use for the main (subtracted) mesh
    if needs_cut
        cut_solid_ref = G4SubtractionSolid(
            "cut_$(GetName(solid[]))",
            solid,
            CxxPtr(cutter),
            local_cutter_transform
        )
        ph = GetPolyhedron(cut_solid_ref)
    else
        ph = ph_orig
    end

    @label before_mesh

    # Create the main mesh from the (possibly subtracted) solid
    # Use GC.@preserve to ensure the solid owning ph stays alive:
    # - solid owns ph_orig (when needs_cut=false)
    # - cut_solid_ref owns ph (when needs_cut=true)
    m = GC.@preserve solid cut_solid_ref polyhedron_to_mesh(ph; transform = t)
    if m !== nothing
        #for p in m.position
        #    if p[1] > 0.1 && p[2] > 0.1 # World-space check for the cut region
        #        println("Warning: Mesh vertex at $(p) is in the cut region $(String(GetName(lv)))")
        #        break
        #    end
        #end
        if haskey(lv_meshes, lv)
            push!(lv_meshes[lv][1], m)
        else
            lv_meshes[lv] = ([m], color, visible)
        end
    end

    @label after_mesh

    # Recurse to daughters
    level >= maxlevel && return
    g4vis != C_NULL && IsDaughtersInvisible(g4vis) && return

    for idx in 1:GetNoDaughters(lv)
        daughter = GetDaughter(lv, idx - 1)

        if IsReplicated(daughter)
            volume = GetLogicalVolume(daughter)
            axis = Ref{EAxis}(kYAxis)
            nReplicas = Ref{Int32}(0)
            width = Ref{Float64}(0.0)
            offset_val = Ref{Float64}(0.0)
            consuming = Ref{UInt8}(0)
            GetReplicationData(daughter, axis, nReplicas, width, offset_val, consuming)

            unitV = Vector3{Float64}(UnitOnAxis[axis[] + 1]...)
            for i in 1:nReplicas[]
                local_t = unitV * (-width[] * (nReplicas[] - 1) * 0.5 + (i - 1) * width[])
                child_transform = Transformation3D{Float64}(one(RotMatrix3{Float64}), local_t)
                new_t = child_transform * t
                collect_meshes_with_cut!(volume[], lv_meshes, cutter, cutter_offset, new_t, level + 1, maxlevel)
            end
        else
            g4t = GetTranslation(daughter)
            g4r = GetRotation(daughter)

            local_rot = if g4r == C_NULL
                one(RotMatrix3{Float64})
            else
                RotMatrix3{Float64}(
                    xx(g4r[]), yx(g4r[]), zx(g4r[]),
                    xy(g4r[]), yy(g4r[]), zy(g4r[]),
                    xz(g4r[]), yz(g4r[]), zz(g4r[])
                )
            end
            local_trans = Vector3{Float64}(x(g4t), y(g4t), z(g4t))

            child_transform = Transformation3D{Float64}(local_rot, local_trans)
            new_t = child_transform * t
            volume = GetLogicalVolume(daughter)
            collect_meshes_with_cut!(volume[], lv_meshes, cutter, cutter_offset, new_t, level + 1, maxlevel)
        end
    end
end

"""
    collect_lv_meshes(lv; maxlevel=5, cut_quadrant=true)

Collect all meshes from a Geant4 logical volume.

Returns lv_meshes, which is a Dict mapping
LogicalVolume -> (meshes, color, visible).
"""
function collect_lv_meshes(lv; maxlevel::Int=5, clip=:none, epsilon=1e-2)
    lv_meshes = Dict{G4LogicalVolume, Tuple{Vector{GeometryBasics.Mesh}, LVColor, Bool}}()

    lo = G4ThreeVector()
    hi = G4ThreeVector()
    BoundingLimits(GetSolid(lv), lo, hi)
    dim = hi - lo
    sx, sy, sz = dim[0]/2 + 100, dim[1]/2 + 100 , dim[2]/2 + 100 # Add margin to ensure we fully encompass the cut region
    if clip == :none
        cutter_offset = Vec3{Float64}(0, 0, 0)
        cutter = nothing
    else
        cutter = G4Box("cutter", sx, sy, sz) # Large box to ensure it fully encompasses the cut region
        if clip == :x
            cutter_offset = Vec3{Float64}(sx - epsilon, 0, 0)
        elseif clip == :y
            cutter_offset = Vec3{Float64}(0, sy - epsilon, 0)
        elseif clip == :z
            cutter_offset = Vec3{Float64}(0, 0, sz - epsilon)
        elseif clip == :xy
            cutter_offset = Vec3{Float64}(sx - epsilon, sy - epsilon, 0)
        elseif clip == :xz
            cutter_offset = Vec3{Float64}(sx - epsilon, 0, sz - epsilon)
        elseif clip == :yz
            cutter_offset = Vec3{Float64}(0, sy - epsilon, sz - epsilon)
        elseif clip == :xyz
            cutter_offset = Vec3{Float64}(sx - epsilon, sy - epsilon, sz - epsilon)
        end
    end
     _mesh_counter[] = 0 # Reset mesh counter for this collection  
    collect_meshes_with_cut!(lv, lv_meshes, cutter, cutter_offset,
                                 one(Transformation3D{Float64}), 1, maxlevel)

    # compact meshes with same color into single mesh collection to reduce draw calls
    col_meshes = Dict{Tuple{LVColor, Bool}, Vector{GeometryBasics.Mesh}}()
    for (_ , (meshes, color, visible)) in lv_meshes
        key = (color, visible)
        if haskey(col_meshes, key)
            push!(col_meshes[key], meshes...)
        else
            col_meshes[key] = meshes
        end
    end
    return col_meshes
end

