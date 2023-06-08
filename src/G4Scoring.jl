#---Exports from this section----------------------------------------------------------------------
export G4JLScoringMesh, BoxMesh, CylinderMesh, energyDeposit, doseDeposit, nOfStep, ParticleFilter
using CSV

#---Scoring structures-----------------------------------------------------------------------------
abstract type AbstractMesh end
abstract type AbstractFilter end

struct ParticleFilter <: AbstractFilter
    name::String
    pname::String
end
toUIstring(f::ParticleFilter) = "/score/filter/particle $(f.name) $(f.pname)"

struct ScoringQuantity
    name::String
    qtype::Symbol  # :energyDeposit, :cellCharge, :passageCellFlux, :doseDeposit, :nOfStep, :nOfSecondary, ....
    qunit::Symbol  # unit
    filters::Vector{AbstractFilter}
end
energyDeposit(name, qunit="MeV"; filters = AbstractFilter[]) =  ScoringQuantity(name, :energyDeposit, Symbol(qunit), filters)
doseDeposit(name, qunit="Gy"; filters = AbstractFilter[]) =  ScoringQuantity(name, :doseDeposit, Symbol(qunit), filters)
nOfStep(name; filters = AbstractFilter[]) =  ScoringQuantity(name, :nOfStep, Symbol(""), filters)
toUIstring(q::ScoringQuantity) = *("/score/quantity/$(q.qtype) $(q.name) $(q.qunit)", ["\n"*toUIstring(f) for f in q.filters]...)

struct BoxMesh <: AbstractMesh 
    dx::Float64
    dy::Float64
    dz::Float64
    unit::Symbol
    BoxMesh(dx, dy, dz, un=:mm) = new(dx, dy, dz, un)
end
toMstring(::BoxMesh) = "boxMesh"
toUIstring(m::BoxMesh) = "/score/mesh/boxSize $(m.dx) $(m.dy) $(m.dz) $(m.unit)"

struct CylinderMesh <: AbstractMesh 
    r::Float64
    dz::Float64
    unit::Symbol
end
toMstring(::CylinderMesh) = "cylinderMesh"
toUIstring(m::CylinderMesh) = "/score/mesh/cylinderSize $(m.r) $(m.dz) $(m.init)"

struct G4JLScoringMesh{M<:AbstractMesh}
    name::String
    mesh::M                                       # :box, :cylinder, :probe
    bins::Tuple{Int, Int, Int}                    # nX, nY, nZ
    translation::Union{Nothing, Tuple{Float64, Float64, Float64}}
    rotation::Union{Nothing, Tuple{Float64, Float64, Float64}}
    quantities::Vector{ScoringQuantity}
end
"""
    G4JLScoringMesh(name, mesh; <keyword arguments>)

Create a scoring mesh to be added to the Geant4 application.
# Arguments
- `name::String`: scoring mech name
- `mesh::AbstractMesh`: mesh instance. Either a `BoxMesh` or `CylinderMesh`
- `bins::Tuple`: tuple with number on bins in x, y, z (default 30, 30, 30)
- `translation::Tuple`: position (x,y,z) with respect the mesh respect to the world volume. Default is  (0,0,0).
- `rotation::Tuple`: rotation of the mesh with respect the world volume. Default (0,0,0)
- `quantities::Vector`: vector of quanties to be scored (e.g. `energyDeposit`, `doseDeposit`, `nOfStep`)
"""
function G4JLScoringMesh(name::String, mesh::M; 
                     bins = (30,30,30),
                     translation = nothing,
                     rotation = nothing,
                     quantities = ScoringQuantity[]) where M <: AbstractMesh
G4JLScoringMesh{M}(name, mesh, bins, translation, rotation, quantities)
end

function toUIstring(sm::G4JLScoringMesh)
    r = "/score/create/$(toMstring(sm.mesh)) $(sm.name)\n" * toUIstring(sm.mesh) * 
        "\n/score/mesh/nBin $(sm.bins[1]) $(sm.bins[2]) $(sm.bins[3])"
    if !isnothing(sm.translation)
        dx, dy, dz = sm.translation
        r *= "\n/score/mesh/translate/xyz $dx $dy $dz mm"
    end
    if !isnothing(sm.rotation)
        rx, ry, rz = sm.rotation
        r *= "\n/score/mesh/rotate/rotateX $rx"
        r *= "\n/score/mesh/rotate/rotateY $ry"
        r *= "\n/score/mesh/rotate/rotateZ $ry"
    end
    for q in sm.quantities
        r *= "\n" * toUIstring(q)
    end
    return r
end

function getScoringValues(name::String, quantity::String, bins::Tuple{Int, Int, Int})
    fname = tempname()
    sc = ApplyCommand(G4UImanager!GetUIpointer(), "/score/dumpQuantityToFile $name $quantity $fname")
    sc != 0 && return
    csv = CSV.File(fname; comment="#", header=["iX", "iY", "iZ", "total", "total2", "entry"])
    (permutedims(reshape(csv[c], bins[3], bins[2], bins[1]),(3,2,1)) for c in (:total, :total2, :entry))
end

function Base.getproperty(sm::G4JLScoringMesh{T}, f::Symbol) where T
    qname = String(f)
    if any(q.name == qname for q in getfield(sm, :quantities))
        getScoringValues(getfield(sm, :name), qname, getfield(sm, :bins))
    else
        getfield(sm, f)
    end
end
