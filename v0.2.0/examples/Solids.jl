using Geant4
using Geant4.SystemOfUnits
using CairoMakie
using GeometryBasics, Rotations, LinearAlgebra, IGLWrap_jll  ## to force loading G4Vis extension

box = G4Box("Box", 2,3,4)
img = draw(box;color=:green)

tub1 = G4Tubs("tub1",0,10,10,0,2π)
img = draw(tub1, wireframe=true, color=:blue)

tub2 = G4Tubs("tub2",5,10,10,0, 2π/3)
img = draw(tub2, wireframe=true, color=:blue)

ctub = G4CutTubs("ctub", 12, 20, 20, 0, 3π/2, G4ThreeVector(0,-0.7,-0.71), G4ThreeVector(0.7,0,0.71))
img = draw(ctub, wireframe=true, color=:blue)

cone1 = G4Cons("cone1", 0, 10, 0, 5, 10, 0, 2π)
img = draw(cone1, color=:blue, wireframe=true)

cone1 = G4Cons("cone1", 5, 10, 20, 25, 40, 0, 3π/4)
img = draw(cone1, color=:blue, wireframe=true)

cone1 = G4Cons("cone1", 5, 10, 2, 5, 5, 0, π/2)
img = draw(cone1, color=:orange, shading=true)

para = G4Para("para", 20,30,30, 0, π/4, π/6)
img = draw(para, wireframe=true)

trd1 = G4Trd("trd1", 10, 5, 10, 5, 5)
img = draw(trd1, wireframe=true, color=:blue)

trap = G4Trap("trap", 60, 20deg, 5deg, 40, 30, 40, 10deg, 16, 10, 14, 10deg)
img = draw(trap, wireframe=true, color=:green)

sph = G4Sphere("sphere", 7,10, 0, pi/2, pi/4, pi/2 )
img = draw(sph, wireframe=true, color=:gray)

orb = G4Orb("orb", 10)
img = draw(orb, wireframe=false, color=:green)

torus = G4Torus("torus", 40, 60, 200, 0, π/2)
img = draw(torus, wireframe=true, color=:blue)

img = drawDistanceToOut(torus, 100000)

pcon = G4Polycone("pcone", π/4, 3π/2, 9,
                  [ 5., 7., 9., 11., 25., 27., 29., 31., 37. ],
                  [ 0., 0., 0., 0., 0., 0., 0., 0., 0. ],
                  [ 0., 10., 10., 5. , 5., 10. , 10. , 2., 2.]
                 )
img = draw(pcon, wireframe=true, color=:blue)

pgon = G4Polyhedra("pgon", -π/4, 5π/4, 3, 7,
                  [ 0., 5., 8., 13. , 30., 32., 35. ],
                  [ 0., 0., 0., 0., 0., 0., 0. ],
                  [ 0., 15., 15., 4., 4., 10., 10.])
img = draw(pgon, wireframe=true, color=:blue)

etub = G4EllipticalTube("etube", 5., 10., 20.)
img = draw(etub, wireframe=true, color=:green)

ellip = G4Ellipsoid("ellip", 10., 20., 50., -10., 40.)
img = draw(ellip, wireframe=true, color=:green)

box1 = G4Box("box1", 10,10,10)
tub1 = G4Tubs("tub1",0,7,11,0,2π)
sub1 = G4SubtractionSolid("sub1", CxxPtr(box1), CxxPtr(tub1))
img = draw(sub1, wireframe=true, color=:green)

img = drawDistanceToOut(sub1, 100000)

box1 = G4Box("box1", 10,10,10)
t1 = G4Transform3D(G4RotationMatrix(π/4,0,0), G4ThreeVector())
inter1 = G4IntersectionSolid("inter1", CxxPtr(box1), CxxPtr(box1), t1)
img = draw(inter1, wireframe=true, color=:green)

img = drawDistanceToOut(inter1, 100000)

tub1 = G4Tubs("tub1",0,5,10,0,2π)
t1 = G4Transform3D(G4RotationMatrix(0,π/2,0), G4ThreeVector())
union1 = G4UnionSolid("union1", CxxPtr(tub1), CxxPtr(tub1), t1)
img = draw(union1, wireframe=false, color=:green)

img = drawDistanceToOut(union1, 100000)
