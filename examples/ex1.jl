using Revise
using Geant4

using Test

runmgr = Geant4.G4RunManager()
v = String(Geant4.GetVersionString(runmgr))

const cm = 10.

pos1 = Geant4.G4ThreeVector(0, 2cm, -7cm)