@testset "G4Geometry" begin
    # Vectors
    m1 = G4ThreeVector(1, 2, 3)
    m2 = G4ThreeVector(10, 20, 30)

    @test x(m1) == 1.
    @test y(m1) == 2.
    @test z(m1) == 3.

    @test m1 + m2 == G4ThreeVector(11,22,33)
    @test mag(m1) == √14
    @test dot(m2, m2) == mag2(m2)

    # Transformations
    r1 = G4RotationMatrix(0,0,0)  # unit rotation
    @test r1 * m1 == m1

    rotateX(r1, π/3)
    rotateY(r1, π/4)
    rotateZ(r1, π/6)

    p0 = G4ThreeVector(1,1,1)
    v0 = G4ThreeVector(1,1,1)
  
    t1 = G4Transform3D(r1, m1)
    @test getRotation(t1) * p0 + getTranslation(t1) == r1 * p0 + m1

    # Shapes

end