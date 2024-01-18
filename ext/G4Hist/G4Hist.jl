module G4Hist
    using Geant4
    using FHist
    using Geant4.SystemOfUnits

    const Hist1DType = typeof(Hist1D(bins=range(0,1,10)))
    const Hist2DType = typeof(Hist2D(bins=(range(0,1,10),range(0,1,10))))
    
    _getvalue(unit::Symbol) = getfield(Geant4.SystemOfUnits, unit)
    _getvalue(units::Tuple{Symbol,Symbol}) = (getfield(Geant4.SystemOfUnits, units[1]), getfield(Geant4.SystemOfUnits, units[2]))

    """
    H1D(title::String, nbins::Int, min::Float, max::Float, unit::Symbol)
        Create a 1-dimentional histgram carrying the title and units
    """
    struct H1D
        title::String
        hist::Hist1DType
        unit::Symbol
        unitval::Float64
    end
    Geant4.H1D(title, nbins, min, max, unit=:nounit) = H1D(title, Hist1D(Float64;bins=range(min,max,nbins+1),overflow=true), unit, _getvalue(unit))

    Base.push!(h::H1D, v, w=1) = push!(h.hist, v/h.unitval, w)
    Base.merge!(h1::H1D, h2::H1D) = merge!(h1.hist, h2.hist)
    Base.empty!(h1::H1D) = empty!(h1.hist)

    """
    H2D(title::String, xbins::Int, xmin::Float, xmax::Float, ybins::Int, ymin::Float, ymax::Float, unit::Tuple{Symbol,Symbol})
        Create a 2-dimentional histgram carrying the title and units
    """
    struct H2D
        title::String
        hist::Hist2DType
        unit::Tuple{Symbol,Symbol}
        unitval::Tuple{Float64,Float64}
    end
    Geant4.H2D(title, xbins, xmin, xmax, ybins, ymin, ymax, units=(:nounit, :nounit)) = H2D(title, Hist2D(Float64;bins=(range(xmin,xmax,xbins+1), range(ymin,ymax, ybins+1)), overflow=true), units, _getvalue(units))

    Base.push!(h::H2D, u, v, w=1) = push!(h.hist, u/h.unitval[1], v/h.unitval[2], w)
    Base.merge!(h1::H2D, h2::H2D) = merge!(h1.hist, h2.hist) 
    Base.empty!(h1::H2D) = empty!(h1.hist)

end
