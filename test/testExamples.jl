
@testset "G4Examples" begin
    @test run(`julia --project=. examples/basic/B2/B2a.jl`, devnull, devnull).exitcode  == 0
    @test run(`julia --project=. examples/basic/B1/B1.jl`, devnull, devnull).exitcode  == 0
    @test run(`julia --project=. examples/extended/RE03/RE03.jl`, devnull, devnull).exitcode  == 0
    @test run(`julia --project=examples/TestEm3 examples/TestEm3/TestEm3.jl`, devnull, devnull).exitcode  == 0
    # Visualization
    @test run(`julia --project=examples/HBC30 examples/HBC30/HBC30.jl`, devnull, devnull).exitcode == 0
    @test run(`julia --project=ext/G4Vis/examples ext/G4Vis/examples/B1vis.jl`, devnull, devnull).exitcode == 0
    @test run(`julia --project=ext/G4Vis/examples ext/G4Vis/examples/B2aVis.jl`, devnull, devnull).exitcode == 0
    @test run(`julia --project=ext/G4Vis/examples ext/G4Vis/examples/TestEm3Vis.jl`, devnull, devnull).exitcode == 0
end
