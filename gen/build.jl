using CxxWrap
using Geant4_jll
using Expat_jll
using Xerces_jll

#---Build the wrapper library----------------------------------------------------------------------
builddir = joinpath(@__DIR__, "build")
sourcedir = @__DIR__
cd(@__DIR__)
mkpath(builddir)
cd(builddir)

if Sys.isapple()
    ENV["SDKROOT"]=readchomp(`xcrun --sdk macosx --show-sdk-path`)
end

cxxwrap_prefix = CxxWrap.prefix_path()
geant4_prefix = Geant4_jll.artifact_dir
xerces_prefix = Xerces_jll.artifact_dir

           #-DXercesC_LIBRARY_RELEASE=$(Xerces_jll.libxerces)

run(`cmake -DCMAKE_BUILD_TYPE=Release
           -DCMAKE_CXX_STANDARD=std++17
           -DEXPAT_INCLUDE_DIR=$(Expat_jll.artifact_dir)/include
           -DEXPAT_LIBRARY=$(Expat_jll.libexpat)
           -DXercesC_INCLUDE_DIR=$(Xerces_jll.artifact_dir)/include
           -DCMAKE_PREFIX_PATH=$cxxwrap_prefix\;$geant4_prefix\;$xerces_prefix  $sourcedir`)
run(`cmake --build . --config Release --parallel 8`)
