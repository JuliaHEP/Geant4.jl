#---Exports from this section----------------------------------------------------------------------
export G4JLGunGenerator, G4JLGeneralParticleSource, G4JLPrimaryGenerator, G4JLGeneratorData

#---Abstract Generator Data (Parameters)------------------------------------------------------------
abstract type  G4JLGeneratorData end

#---Primary Particle Generator----------------------------------------------------------------------
mutable struct G4JLPrimaryGenerator{UD<:G4JLGeneratorData}
    const name::String
    const data::UD
    const init_method::Function    #  (::UD, ::G4JLApplication)::Nothing
    const gen_method::Function     #  (::CxxPtr{G4Event}, ::UD)::Nothing
    base::Vector{G4JLGeneratorAction}
end
"""
    G4JLPrimaryGenerator(name::String, data::DATA; <keyword arguments>) where DATA<:G4JLGeneratorData

Creatre a G4JLPrimaryGenerator with its name and associated DATA structure
# Arguments
"""
function G4JLPrimaryGenerator(name::String, data::T;
                              init_method=nothing,
                              generate_method=nothing) where T<:G4JLGeneratorData
    isnothing(generate_method) && error("primary particle generator method not defined")
    G4JLPrimaryGenerator{T}(name, data, init_method, generate_method, G4JLGeneratorAction[])   
end

#--------------------------------------------------------------------------------------------------
#---Implementation (user friendly) Particle Gun----------------------------------------------------
#--------------------------------------------------------------------------------------------------
mutable struct G4JLParticleGunData <: G4JLGeneratorData
    gun::Union{Nothing, CxxPtr{G4ParticleGun}}
    particle::String
    direction::G4ThreeVector
    position::G4ThreeVector
    energy::Float64
end
function G4JLPrimaryGenerator{G4JLParticleGunData}(;particle="e-", energy=10., direction=G4ThreeVector(), position=G4ThreeVector())
    data = G4JLParticleGunData(nothing, particle, direction, position, energy)
    function init(data::G4JLParticleGunData, ::Any)
        pg = data.gun = move!(G4ParticleGun())
        SetParticleByName(pg, data.particle)
        SetParticleEnergy(pg, data.energy)
        SetParticleMomentumDirection(pg, data.direction)
        SetParticlePosition(pg, data.position)
    end
    function gen(evt::G4Event, data::G4JLParticleGunData)::Nothing
        GeneratePrimaryVertex(data.gun, CxxPtr(evt))
    end
    G4JLPrimaryGenerator("ParticleGun", data; init_method=init, generate_method=gen)
end
"""
G4JLGunGenerator(; particle="e-", energy=10., direction=G4ThreeVector(), position=G4ThreeVector())
Create a Particle Gun generator with specified particle type, energy, direction, and position.
# Arguments
- `particle::String="e-"`: The name of the particle to be generated (default is electron).
- `energy::Float64=10.`: The energy of the particle in Me   V (default is 10 MeV).
- `direction::G4ThreeVector=G4ThreeVector()`: The momentum direction of the particle (default is zero vector).
- `position::G4ThreeVector=G4ThreeVector()`: The position of the particle (default is zero vector).
"""
const G4JLGunGenerator = G4JLPrimaryGenerator{G4JLParticleGunData}

function SetParticleByName(gen::G4JLGunGenerator, particle::String)
    gen.data.particle=particle
    SetParticleByName(gen.data.gun, particle)
end
function SetParticleEnergy(gen::G4JLGunGenerator, energy::Float64)
    gen.data.energy=energy
    SetParticleEnergy(gen.data.gun, energy)
end
function SetParticleMomentumDirection(gen::G4JLGunGenerator, direction::G4ThreeVector)
    gen.data.direction=direction
    SetParticleMomentumDirection(gen.data.gun, direction)
end
function SetParticlePosition(gen::G4JLGunGenerator, position::G4ThreeVector)
    gen.data.direction=position
    SetParticlePosition(gen.data.gun, position)
end

#--------------------------------------------------------------------------------------------------
#---Implementation (user friendly) General Particle Source-----------------------------------------
#--------------------------------------------------------------------------------------------------
mutable struct G4JLGPSData <: G4JLGeneratorData
    gps::Union{Nothing, CxxPtr{G4GeneralParticleSource}}
    sources::Vector{<:NamedTuple}
    multiplevertex::Bool
    flatsampling::Bool
end

function G4JLPrimaryGenerator{G4JLGPSData}(;kwargs...)
    if haskey(kwargs, :sources)
        data = G4JLGPSData(nothing, kwargs.sources, 
                                    haskey(kwargs,:multiplevertex) ? kwargs.multiplevertex : false,
                                    haskey(kwargs,:flatsampling) ? kwargs.flatsampling : false)
    else
        data = G4JLGPSData(nothing, [NamedTuple(kwargs)], false, false)
    end
    function gen(evt::G4Event, data::G4JLGPSData)::Nothing
        GeneratePrimaryVertex(data.gps, CxxPtr(evt))
    end
    G4JLPrimaryGenerator("GPS", data; init_method=initGPS, generate_method=gen)
end
const G4JLGeneralParticleSource = G4JLPrimaryGenerator{G4JLGPSData}

function initGPS(data::G4JLGPSData, ::Any)
    gps = data.gps = move!(G4GeneralParticleSource())
    for (idx, source) in enumerate(data.sources)
        if idx != 1
            AddaSource(gps, 1.)
        end
        current = gps |> GetCurrentSource
        #---First level (:intensity, :position, :particle, :direction, :energy)
        for attr in fieldnames(typeof(source))
            if attr == :intensity
                SetCurrentSourceIntensity(gps, source.intensity)
            elseif attr == :position
                pos = current |> GetPosDist
                SetPosDisType(pos, "Point")    
                SetCentreCoords(pos, source.position)
            elseif attr == :direction
                ang = current |> GetAngDist
                SetAngDistType(ang, "planar")    
                SetParticleMomentumDirection(ang, source.direction)
            elseif attr == :energy
                ene = current |> GetEneDist
                SetMonoEnergy(ene, source.energy)
            elseif attr == :particle
                SetParticleDefinition(current, source.particle |> FindParticle)
            elseif attr == :pos
                pos = current |> GetPosDist
                for sattr in fieldnames(typeof(source.pos))
                    if sattr == :type
                        SetPosDisType(pos, source.pos.type)
                    elseif sattr == :shape
                        SetPosDisShape(pos, source.pos.shape)
                    elseif sattr == :centre
                        SetCentreCoords(pos, source.pos.centre)
                    elseif sattr == :rot1
                        SetPosRot1(pos, source.pos.rot1)
                    elseif sattr == :rot2
                        SetPosRot2(pos, source.pos.rot2)
                    elseif sattr == :halfx
                        SetHalfX(pos, source.pos.halfx)
                    elseif sattr == :halfy
                        SetHalfY(pos, source.pos.halfy)
                    elseif sattr == :halfz
                        SetHalfZ(pos, source.pos.halfz)
                    elseif sattr == :radius
                        SetRadius(pos, source.pos.radius)
                    elseif sattr == :inner_radius
                        SetRadius0(pos, source.pos.inner_radius)
                    elseif sattr == :sigma_r
                        SetBeamSigmaInR(pos, source.pos.sigma_r)
                    elseif sattr == :sigma_x
                        SetBeamSigmaInX(pos, source.pos.sigma_x)
                    elseif sattr == :sigma_y
                        SetBeamSigmaInY(pos, source.pos.sigma_y)
                    elseif sattr == :paralp
                        SetParAlpha(pos, source.pos.paralp)
                    elseif sattr == :parthe
                        SetParTheta(pos, source.pos.parthe)
                    elseif sattr == :parphi
                        SetParPhi(pos, source.pos.parphi)
                    elseif sattr == :confine
                        ConfineSourceToVolume(pos, source.pos.confine)
                    else
                        error("$sattr is not an attribute of particle position distribution")
                    end
                end
            elseif attr == :ang
                ang = current |> GetAngDist
                for sattr in fieldnames(typeof(source.ang))
                    if sattr == :type
                        SetAngDistType(ang, source.ang.type)
                    elseif sattr == :rot1
                        DefineAngRefAxes(ang, "angref1", source.ang.rot1)
                    elseif sattr == :rot2
                        DefineAngRefAxes(ang, "angref2", source.ang.rot2)
                    elseif sattr == :mintheta
                        SetMinTheta(ang, source.ang.mintheta)
                    elseif sattr == :maxtheta
                        SetMaxTheta(ang, source.ang.maxtheta)
                    elseif sattr == :minphi
                        SetMinPhi(ang, source.ang.minphi)
                    elseif sattr == :maxphi
                        SetMaxPhi(ang, source.ang.maxphi)
                    elseif sattr == :sigma_r
                        SetBeamSigmaInAngR(ang, source.ang.sigma_r)
                    elseif sattr == :sigma_x
                        SetBeamSigmaInAngX(ang, source.ang.sigma_x)
                    elseif sattr == :sigma_y
                        SetBeamSigmaInAngY(ang, source.ang.sigma_y)
                    elseif sattr == :focuspoint
                        SetFocusPoint(ang, source.ang.focuspoint)
                    elseif sattr == :user_coor
                        SetUseUserAngAxis(ang, source.ang.user_coor)
                    elseif sattr == :surfnorm
                        SetUserWRTSurface(ang, source.ang.surfnorm)
                    else
                        error("$sattr is not an attribute of particle angular distribution")
                    end
                end
            elseif attr == :ene
                ene = current |> GetEneDist
                for sattr in fieldnames(typeof(source.ene))
                    if sattr == :type
                        SetEnergyDisType(ene, source.ene.type)
                    elseif sattr == :min
                        SetEmin(ene, source.ene.min)
                    elseif sattr == :max
                        SetEmax(ene, source.ene.max)
                    elseif sattr == :mono
                        SetMonoEnergy(ene, source.ene.mono)
                    elseif sattr == :sigma
                        SetBeamSigmaInE(ene, source.ene.sigma)
                    elseif sattr == :alpha
                        SetAlpha(ene, source.ene.alpha)
                    elseif sattr == :temp
                        SetTemp(ene, source.ene.temp)
                    elseif sattr == :ezero
                        SetEzero(ene, source.ene.ezero)
                    elseif sattr == :gradient
                        SetGradient(ene, source.ene.gradient)
                    elseif sattr == :intercept
                        SetInterCept(ene, source.ene.intercept)
                    elseif sattr == :biasAlpha
                        SetBiasAlpha(ene, source.ene.biasAlpha)
                    elseif sattr == :calculate
                        Calculate(ene)
                    elseif sattr == :emspec
                        InputEnergySpectra(ene, source.ene.emspec)
                    elseif sattr == :diffspec
                        InputDifferentialSpectra(ene, source.ene.diffspec)
                    elseif sattr == :applyEneWeight
                        ApplyEnergyWeight(ene, source.ene.applyEneWeight)
                    else
                        error("$sattr is not an attribute of particle energy distribution")
                    end
                end
            else
                error("$attr is not an attribute of single particle source")
            end
        end
    end
end

function reinitialize(gen::G4JLGeneralParticleSource; kwargs...)
    isnothing(gen.data.gps) && error("GeneralParticleSource has not been instantiated")
    data = gen.data
    if haskey(kwargs, :sources)
        data.sources = kwargs[:sources]
        haskey(kwargs,:multiplevertex) &&  (data.multiplevertex = kwargs[:multiplevertex])
        haskey(kwargs,:flatsampling) && (data.flatsampling = kwargs[:flatsampling])
    else
        data.sources = [ NamedTuple(kwargs) ]
    end
    initGPS(data, nothing)
end

#=
/gps/pos

type * Sets source distribution type.
shape * Sets source shape for Plan, Surface or Volume type source.
centre * Set centre coordinates of source.
rot1 * Set the 1st vector defining the rotation matrix'.
rot2 * Set the 2nd vector defining the rotation matrix'.
halfx * Set x half length of source.
halfy * Set y half length of source.
halfz * Set z half length of source.
radius * Set radius of source.
inner_radius * Set inner radius of source when required.
sigma_r * Set standard deviation in radial of the beam positional profile
sigma_x * Set standard deviation of beam positional profile in x-dir
sigma_y * Set standard deviation of beam positional profile in y-dir
paralp * Angle from y-axis of y' in Para
parthe * Polar angle through centres of z faces
parphi * Azimuth angle through centres of z faces
confine * Confine source to volume (NULL to unset).

/gps/ang

type * Sets angular source distribution type
rot1 * Sets the 1st vector for angular distribution rotation matrix
rot2 * Sets the 2nd vector for angular distribution rotation matrix
mintheta * Set minimum theta
maxtheta * Set maximum theta
minphi * Set minimum phi
maxphi * Set maximum phi
sigma_r * Set standard deviation in direction for 1D beam.
sigma_x * Set standard deviation in direction in x-direc. for 2D beam
sigma_y * Set standard deviation in direction in y-direc. for 2D beam
focuspoint * Set the focusing point for the beam
user_coor * True for using user defined angular co-ordinates
surfnorm * Makes a user-defined distribution with respect to surface normals rather than x,y,z axes.

/gps/ene

type * Sets energy distribution type
min * Sets minimum energy
max * Sets maximum energy
mono * Sets a monocromatic energy (same as  gps/energy)
sigma * Sets the standard deviation for Gaussian energy dist.
alpha * Sets Alpha (index) for power-law energy dist.
temp * Sets the temperature for Brem and BBody distributions (in Kelvin)
ezero * Sets E_0 for exponential distribution (in MeV)
gradient * Sets the gradient for Lin distribution (in 1/MeV)
intercept * Sets the intercept for Lin distributions (in MeV)
biasAlpha * Sets the power-law index for the energy sampling distri. )
calculate * Calculates the distributions for Cdg and BBody
emspec * True for energy and false for momentum spectra
diffspec * True for differential and flase for integral spectra
applyEneWeight * Apply energy weight.

=#
