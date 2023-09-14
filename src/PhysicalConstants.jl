# From the file provided by Geant4 (simulation toolkit for HEP).
#
# The basic units are :
#  		millimeter  
# 		nanosecond  
# 		Mega electron Volt  
# 		positon charge 
# 		degree Kelvin
#       amount of substance (mole)
#       luminous intensity (candela)
# 		radian  
#       steradian 

module PhysicalConstants

    using Geant4.SystemOfUnits

    const Avogadro = 6.02214076e+23/mole

    # c   = 299.792458 mm/ns
    # c^2 = 898.7404 (mm/ns)^2 
    const c_light   = 2.99792458e+8 * m/s
    const c_squared = c_light * c_light

    # h     = 4.13566e-12 MeV*ns
    # hbar  = 6.58212e-13 MeV*ns
    # hbarc = 197.32705e-12 MeV*mm
    const h_Planck      = 6.62607015e-34 * joule*s
    const hbar_Planck   = h_Planck/2pi
    const hbarc         = hbar_Planck * c_light
    const hbarc_squared = hbarc * hbarc


    const electron_charge = - eplus # see SystemOfUnits.h
    const e_squared = eplus * eplus

    # amu_c2 - atomic equivalent mass unit
    #        - AKA, unified atomic mass unit (u)
    # amu    - atomic mass unit
    const electron_mass_c2 = 0.510998910 * MeV
    const   proton_mass_c2 = 938.272013 * MeV
    const  neutron_mass_c2 = 939.56536 * MeV
    const           amu_c2 = 931.494028 * MeV
    const              amu = amu_c2/c_squared

    # permeability of free space mu0    = 2.01334e-16 Mev*(ns*eplus)^2/mm
    # permittivity of free space epsil0 = 5.52636e+10 eplus^2/(MeV*mm)
    const mu0      = 4*pi*1.e-7 * henry/m
    const epsilon0 = 1.0/(c_squared*mu0)

    # electromagnetic coupling = 1.43996e-12 MeV*mm/(eplus^2)
    const elm_coupling           = e_squared/(4*pi*epsilon0)
    const fine_structure_const   = elm_coupling/hbarc
    const classic_electr_radius  = elm_coupling/electron_mass_c2
    const electron_Compton_length = hbarc/electron_mass_c2
    const Bohr_radius = electron_Compton_length/fine_structure_const

    const alpha_rcl2 = fine_structure_const*classic_electr_radius*classic_electr_radius
    const twopi_mc2_rcl2 = 2pi*electron_mass_c2*classic_electr_radius*classic_electr_radius

    const Bohr_magneton = (eplus*hbarc*c_light)/(2*electron_mass_c2)
    const nuclear_magneton = (eplus*hbarc*c_light)/(2*proton_mass_c2)

    const k_Boltzmann = 8.617333e-11 * MeV/kelvin
    const STP_Temperature = 273.15*kelvin
    const STP_Pressure    = 1.0*atmosphere
    const kGasThreshold   = 10.0*mg/cm3

    const universe_mean_density = 1.e-25*g/cm3

    #---Export the ones exported by Geant4
    export alpha_rcl2, amu, amu_c2, Avogadro, Bohr_radius, c_light, c_squared, classic_electr_radius, e_squared
    export electron_charge, electron_Compton_length, electron_mass_c2, elm_coupling, epsilon0, fine_structure_const 
    export h_Planck, hbar_Planck, hbarc, hbarc_squared, k_Boltzmann, kGasThreshold, mu0
    export neutron_mass_c2, proton_mass_c2, STP_Pressure, STP_Temperature, twopi_mc2_rcl2
    export Bohr_magneton, nuclear_magneton, universe_mean_density
end