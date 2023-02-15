using CxxWrap

#---Generate the files here------------------------------------------------------------------------
cd(@__DIR__)

if Sys.isapple()
    ENV["SDKROOT"]=readchomp(`xcrun --sdk macosx --show-sdk-path`)
end

LCG_prefix = "/Users/mato/Development/views/dev4/x86_64-mac11-clang120-opt"

write("Geant4.out", replace(read("Geant4.wit", String), "%LCG_prefix%" => "$LCG_prefix", 
                                                        "%CxxWrap_prefix%" => "$(CxxWrap.prefix_path())"))
run(`../../wrapit/build/wrapit --force -v 1 Geant4.out`)

#---Build the wrapper library----------------------------------------------------------------------
builddir = joinpath(@__DIR__, "build")
sourcedir = @__DIR__

mkpath(builddir)
cd(builddir)

run(`cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=$(CxxWrap.prefix_path())\;$LCG_prefix  $sourcedir`)
run(`cmake --build . --config Release`)
