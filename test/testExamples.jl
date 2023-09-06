
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

    # Basic examples
    run(`julia -E "LOAD_PATH"`)
    run(`julia -E "Base.load_path()"`)

    instantiate("examples")
    @test run(`julia --project=examples examples/basic/B2/B2a.jl`, devnull, devnull).exitcode  == 0
    @test run(`julia --project=examples examples/basic/B1/B1.jl`, devnull, devnull).exitcode  == 0
    @test run(`julia --project=examples examples/extended/RE03/RE03.jl`, devnull, devnull).exitcode  == 0
    @test run(`julia --project=examples examples/TestEm3/TestEm3.jl`, devnull, devnull).exitcode  == 0

    # Visualization
    instantiate("ext/G4Vis/examples")
    @test run(`julia --project=ext/G4Vis/examples ext/G4Vis/examples/HBC30/HBC30.jl`, devnull, devnull).exitcode == 0
    @test run(`julia --project=ext/G4Vis/examples ext/G4Vis/examples/B1vis.jl`, devnull, devnull).exitcode == 0
    @test run(`julia --project=ext/G4Vis/examples ext/G4Vis/examples/B2aVis.jl`, devnull, devnull).exitcode == 0
    @test run(`julia --project=ext/G4Vis/examples ext/G4Vis/examples/TestEm3Vis.jl`, devnull, devnull).exitcode == 0
end
