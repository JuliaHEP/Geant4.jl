#---HEP coherent system of Units, taken from CLHEP
# The basic units are :
# millimeter              (millimeter)
# nanosecond              (nanosecond)
# Mega electron Volt      (MeV)
# positron charge         (eplus)
# degree Kelvin           (kelvin)
# the amount of substance (mole)
# luminous intensity      (candela)
# radian                  (radian)
# steradian               (steradian)

module SystemOfUnits

  const nounit = 1.
  
  # Length [L]
  const millimeter  = 1.                        
  const millimeter2 = millimeter*millimeter
  const millimeter3 = millimeter*millimeter*millimeter

  const centimeter  = 10*millimeter   
  const centimeter2 = centimeter*centimeter
  const centimeter3 = centimeter*centimeter*centimeter
    
  const meter  = 1000*millimeter                  
  const meter2 = meter*meter
  const meter3 = meter*meter*meter

  const kilometer = 1000*meter                   
  const kilometer2 = kilometer*kilometer
  const kilometer3 = kilometer*kilometer*kilometer

  const parsec = 3.0856775807e+16*meter

  const micrometer = 1.e-6 *meter             
  const  nanometer = 1.e-9 *meter
  const  angstrom  = 1.e-10*meter
  const  fermi     = 1.e-15*meter

  const      barn = 1.e-28*meter2
  const millibarn = 1.e-3 *barn
  const microbarn = 1.e-6 *barn
  const  nanobarn = 1.e-9 *barn
  const  picobarn = 1.e-12*barn

  # symbols
  const nm  = nanometer                        
  const μm  = micrometer                        

  const mm  = millimeter                        
  const mm2 = millimeter2
  const mm3 = millimeter3

  const cm  = centimeter   
  const cm2 = centimeter2
  const cm3 = centimeter3

  const liter = 1.e+3*cm3
  const  L = liter
  const dL = 1.e-1*liter
  const cL = 1.e-2*liter
  const mL = 1.e-3*liter       
  
  const m  = meter                  
  const m2 = meter2
  const m3 = meter3

  const km  = kilometer                   
  const km2 = kilometer2
  const km3 = kilometer3

  const pc = parsec

  # Angle

  const radian      = 1.                  
  const milliradian = 1.e-3*radian
  const degree = (pi/180.0)*radian

  const   steradian = 1.
  
  # symbols
  const rad  = radian
  const mrad = milliradian
  const sr   = steradian
  const deg  = degree

  # Time [T]
  const nanosecond  = 1.
  const second      = 1.e+9 *nanosecond
  const millisecond = 1.e-3 *second
  const microsecond = 1.e-6 *second
  const picosecond  = 1.e-12*second

  const minute = 60*second
  const hour   = 60*minute
  const day    = 24*hour
  const year   = 365*day  

  const hertz = 1. / second
  const kilohertz = 1.e+3*hertz
  const megahertz = 1.e+6*hertz

  # symbols
  const ns = nanosecond
  const  s = second
  const ms = millisecond
  const μs = microsecond
  const ps = picosecond

  # Electric charge [Q]
  const eplus = 1.               # positron charge
  const e_SI  = 1.602176634e-19  # positron charge in coulomb
  const coulomb = eplus/e_SI     # coulomb = 6.24150 e+18 * eplus

  # Energy [E]
  const megaelectronvolt = 1. 
  const     electronvolt = 1.e-6*megaelectronvolt
  const kiloelectronvolt = 1.e-3*megaelectronvolt
  const gigaelectronvolt = 1.e+3*megaelectronvolt
  const teraelectronvolt = 1.e+6*megaelectronvolt
  const petaelectronvolt = 1.e+9*megaelectronvolt
  const millielectronvolt = 1.e-9*megaelectronvolt  

  const joule = electronvolt/e_SI  # joule = 6.24150 e+12 * MeV

  # symbols
  const MeV = megaelectronvolt
  const  eV = electronvolt
  const keV = kiloelectronvolt
  const GeV = gigaelectronvolt
  const TeV = teraelectronvolt
  const PeV = petaelectronvolt

  # Mass [E][T^2][L^-2]
  const  kilogram = joule*second*second/(meter*meter)   
  const      gram = 1.e-3*kilogram
  const milligram = 1.e-3*gram

  # symbols
  const  kg = kilogram
  const   g = gram
  const  mg = milligram

  # Power [E][T^-1]
  const watt = joule/second  # watt = 6.24150 e+3 * MeV/ns

  # Force [E][L^-1]
  const newton = joule/meter# newton = 6.24150 e+9 * MeV/mm

  # Pressure [E][L^-3]
  const pascal     = newton/m2   # pascal = 6.24150 e+3 * MeV/mm3
  const bar        = 100000*pascal # bar    = 6.24150 e+8 * MeV/mm3
  const atmosphere = 101325*pascal # atm    = 6.32420 e+8 * MeV/mm3

  # Electric current [Q][T^-1]
  const      ampere = coulomb/second # ampere = 6.24150 e+9 * eplus/ns
  const milliampere = 1.e-3*ampere
  const microampere = 1.e-6*ampere
  const  nanoampere = 1.e-9*ampere

  # Electric potential [E][Q^-1]
  const megavolt = megaelectronvolt/eplus
  const kilovolt = 1.e-3*megavolt
  const     volt = 1.e-6*megavolt

  # Electric resistance [E][T][Q^-2]
  const ohm = volt/ampere# ohm = 1.60217e-16*(MeV/eplus)/(eplus/ns)

  # Electric capacitance [Q^2][E^-1]
  const farad = coulomb/volt# farad = 6.24150e+24 * eplus/Megavolt
  const millifarad = 1.e-3*farad
  const microfarad = 1.e-6*farad
  const  nanofarad = 1.e-9*farad
  const  picofarad = 1.e-12*farad

  # Magnetic Flux [T][E][Q^-1]
  const weber = volt*second# weber = 1000*megavolt*ns

  # Magnetic Field [T][E][Q^-1][L^-2]
  const tesla     = volt*second/meter2# tesla =0.001*megavolt*ns/mm2

  const gauss     = 1.e-4*tesla
  const kilogauss = 1.e-1*tesla

  # Inductance [T^2][E][Q^-2]
  const henry = weber/ampere# henry = 1.60217e-7*MeV*(ns/eplus)**2

  # Temperature
  const kelvin = 1.

  # Amount of substance
  const mole = 1.

  # Activity [T^-1]
  const becquerel = 1. / second 
  const curie = 3.7e+10 * becquerel
  const kilobecquerel = 1.e+3*becquerel
  const megabecquerel = 1.e+6*becquerel
  const gigabecquerel = 1.e+9*becquerel
  const millicurie = 1.e-3*curie
  const microcurie = 1.e-6*curie
  const Bq = becquerel
  const kBq = kilobecquerel
  const MBq = megabecquerel
  const GBq = gigabecquerel
  const Ci = curie
  const mCi = millicurie
  const μCi = microcurie

  # Absorbed dose [L^2][T^-2]
  const      gray = joule/kilogram 
  const  kilogray = 1.e+3*gray
  const milligray = 1.e-3*gray
  const microgray = 1.e-6*gray

  # Luminous intensity [I]
  const candela = 1.

  # Luminous flux [I]
  const lumen = candela*steradian

  # Illuminance [I][L^-2]
  const lux = lumen/meter2

  # Miscellaneous
  const perCent     = 0.01 
  const perThousand = 0.001
  const perMillion  = 0.000001

#---Export only the 'symbols'
export nm, μm, mm, cm, cm2, cm3, L, dL, cL, mL, m, km, rad, mrad, er, deg, ns, s, ms, μs, ps, kg, g, mg
export MeV, GeV, keV, eV
export mole, joule, eplus, henry, atmosphere, kelvin, pascal, tesla

end


