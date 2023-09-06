
@testset "G4Examples" begin
    #---change the working directory
    cd(dirname(dirname(pathof(Geant4))))
    run(`julia --project=. -e 'import Pkg;Pkg.instantiate()'`)
    @test run(`julia --project=. examples/basic/B2/B2a.jl`, devnull, devnull).exitcode  == 0
    @test run(`julia --project=. examples/basic/B1/B1.jl`, devnull, devnull).exitcode  == 0
    @test run(`julia --project=. examples/extended/RE03/RE03.jl`, devnull, devnull).exitcode  == 0

    run(`julia --project=examples/TestEm3 -e 'import Pkg;Pkg.instantiate()'`)
    @test run(`julia --project=examples/TestEm3 examples/TestEm3/TestEm3.jl`, devnull, devnull).exitcode  == 0

    # Visualization
    run(`julia --project=examples/HBC30 -e 'import Pkg;Pkg.instantiate()'`)
    @test run(`julia --project=examples/HBC30 examples/HBC30/HBC30.jl`, devnull, devnull).exitcode == 0

    run(`julia --project=ext/G4Vis/examples -e 'import Pkg;Pkg.instantiate()'`)
    @test run(`julia --project=ext/G4Vis/examples ext/G4Vis/examples/B1vis.jl`, devnull, devnull).exitcode == 0
    @test run(`julia --project=ext/G4Vis/examples ext/G4Vis/examples/B2aVis.jl`, devnull, devnull).exitcode == 0
    @test run(`julia --project=ext/G4Vis/examples ext/G4Vis/examples/TestEm3Vis.jl`, devnull, devnull).exitcode == 0
end
