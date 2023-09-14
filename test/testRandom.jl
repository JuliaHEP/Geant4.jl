@testset "G4Random" begin
    rdm = G4Random()
    eng = G4Random!getTheEngine()
    
    @test eng |> getSeed == 1
    @test eng |> flat  ≈ 0.4083998396197835
    
    G4Random!setTheSeed(123)
    @test G4Random!getTheSeed() == 123
    @test eng |> getSeed == 123
    @test  eng |> flat ≈ 0.3489624013615084

end
