@testset "Cone{$T}" for T in (Float64, Float32)
    # Vectors
    m1 = G4ThreeVector(1, 2, 3)
    m2 = G4ThreeVector(10, 20, 30)

    @test x(m1) == 1.

end