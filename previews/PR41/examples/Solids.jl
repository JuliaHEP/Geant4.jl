using Geant4
using Geant4.SystemOfUnits
using CairoMakie  ## to force loading G4Vis extension

HepPolyhedron!SetNumberOfRotationSteps(64)

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

hyper = G4Hype("Hype", 5, 10, 0.2, 0.2, 20)
img = draw(hyper, wireframe=true, color=:blue)

pcon = G4Polycone("pcone", π/4, 3π/2, 9,
                  [ 5., 7., 9., 11., 25., 27., 29., 31., 37. ],
                  [ 0., 0., 0., 0., 0., 0., 0., 0., 0. ],
                  [ 0., 10., 10., 5. , 5., 10. , 10. , 2., 2.]
                 )
img = draw(pcon, wireframe=true, color=:blue)

gpcon = G4GenericPolycone("pcone", 0, π, 4,
                         [ 5., 10., 10., 5.,],
                         [ 0., 10., 20., 30.]
                        )
img = draw(gpcon, wireframe=true, color=:blue)

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
img = draw(sub1, color=:green)

img = drawDistanceToOut(sub1, 100000)

box1 = G4Box("box1", 10,10,10)
t1 = G4Transform3D(G4RotationMatrix(π/4,0,0), G4ThreeVector())
inter1 = G4IntersectionSolid("inter1", CxxPtr(box1), CxxPtr(box1), t1)
img = draw(inter1, color=:green)

img = drawDistanceToOut(inter1, 100000)

tub1 = G4Tubs("tub1",0,5,10,0,2π)
t1 = G4Transform3D(G4RotationMatrix(0,π/2,0), G4ThreeVector())
union1 = G4UnionSolid("union1", CxxPtr(tub1), CxxPtr(tub1), t1)
img = draw(union1, color=:green)

img = drawDistanceToOut(union1, 100000)

twb1 =  G4TwistedBox( "twbox", 30deg, 1m,  1m,  1m)
img = draw(twb1, wireframe=true, color=:orange)

twt1 = G4TwistedTrap("twt1", 30deg, 6cm, 20deg, 5deg, 4cm, 3cm, 4cm, 1.6cm, 1cm, 1.4cm, 10deg)
img = draw(twt1, wireframe=true, color=:orange)

twtub1 = G4TwistedTubs("twtub1", 15deg, 1cm, 1.5cm, 2cm, π/2rad)
img = draw(twtub1, wireframe=true, color=:orange)

twtrd1 = G4TwistedTrd("twtrd1", 30cm, 10cm, 40cm, 15cm, 60cm, 15deg)
img = draw(twtrd1, wireframe=true, color=:orange)

tsol = G4TessellatedSolid("tsol")
p0 = G4ThreeVector(0, 0, 0)
p1 = G4ThreeVector(-10, -10, 0)
p2 = G4ThreeVector( 10, -10, 0)
p3 = G4ThreeVector( 10,  10, 0)
p4 = G4ThreeVector(-10,  10, 0)
face1 = G4TriangularFacet(p1, p0, p2, ABSOLUTE)
face2 = G4TriangularFacet(p2, p0, p3, ABSOLUTE)
face3 = G4TriangularFacet(p3, p0, p4, ABSOLUTE)
face4 = G4TriangularFacet(p4, p0, p1, ABSOLUTE)
apex = G4ThreeVector(0,0,30)
face5 = G4TriangularFacet(p1, p2, apex, ABSOLUTE)
face6 = G4TriangularFacet(p2, p3, apex, ABSOLUTE)
face7 = G4TriangularFacet(p3, p4, apex, ABSOLUTE)
face8 = G4TriangularFacet(p4, p1, apex, ABSOLUTE)
AddFacet(tsol, face1)
AddFacet(tsol, face2)
AddFacet(tsol, face3)
AddFacet(tsol, face4)
AddFacet(tsol, face5)
AddFacet(tsol, face6)
AddFacet(tsol, face7)
AddFacet(tsol, face8)
SetSolidClosed(tsol, true)
img = draw(tsol, wireframe=false, color=:orange)
