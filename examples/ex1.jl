using Geant4
using HEPSystemOfUnits
using Test

runmgr = Geant4.G4RunManager()
v = String(GetVersionString(runmgr))

const cm = 10.

pos1 = Geant4.G4ThreeVector(0, 2cm, -7cm)