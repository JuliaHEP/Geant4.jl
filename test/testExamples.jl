
function instantiate(env)
    cmd = `julia --project=$env -e '
           using Pkg
           Pkg.develop(PackageSpec(path=pwd()))
           Pkg.instantiate()'`
    run(cmd)
end

@testset "G4Examples" begin
    #---change the working directory
    cd(dirname(dirname(pathof(Geant4))))

    # All examples should be used for testing to ensure that the release is working correctly
    instantiate("examples")
    @test run(`julia --project=examples examples/basic/B2/B2a.jl`, devnull, devnull).exitcode  == 0
    @test run(`julia --project=examples examples/basic/B1/B1.jl`, devnull, devnull).exitcode  == 0
    @test run(`julia --project=examples examples/basic/B1/B1vis.jl`, devnull, devnull).exitcode == 0
    @test run(`julia --project=examples examples/basic/B2/B2aVis.jl`, devnull, devnull).exitcode == 0

    @test run(`julia --project=examples examples/extended/RE03/RE03.jl`, devnull, devnull).exitcode  == 0
    @test run(`julia --project=examples examples/extended/GPS/GPS.jl`, devnull, devnull).exitcode == 0
    @test run(`julia --project=examples examples/extended/TestEm3/TestEm3.jl`, devnull, devnull).exitcode  == 0
    @test run(`julia --project=examples examples/extended/TestEm3/TestEm3Vis.jl`, devnull, devnull).exitcode == 0

    @test run(`julia --project=examples examples/advanced/Scintillation/Scintillation.jl`, devnull, devnull).exitcode  == 0
    @test run(`julia --project=examples examples/advanced/HBC30/HBC30.jl`, devnull, devnull).exitcode == 0

end
