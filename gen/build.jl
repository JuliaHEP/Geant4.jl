using CxxWrap
using WrapIt
using Geant4_jll
using Expat_jll
using Xerces_jll

#---Build the wrapper library----------------------------------------------------------------------
builddir = joinpath(@__DIR__, "build")
sourcedir = @__DIR__
cd(@__DIR__)
mkpath(builddir)

if Sys.isapple()
    ENV["SDKROOT"]=readchomp(`xcrun --sdk macosx --show-sdk-path`)
end

cxxwrap_prefix = CxxWrap.prefix_path()
geant4_prefix = Geant4_jll.artifact_dir
xercesc_prefix = Xerces_jll.artifact_dir
julia_prefix = dirname(Sys.BINDIR)

#---Generate the wrapper code----------------------------------------------------------------------
updatemode = ("--update" ∈ ARGS)
updatemode && println("Update mode")
wit = joinpath(@__DIR__, "Geant4.wit")
witin = joinpath(@__DIR__, "Geant4.wit.in")
open(wit, "w") do f
    for l in eachline(witin)
	println(f, replace(l, "@Geant4_INCLUDE_DIR@" => "$geant4_prefix/include/Geant4",
                          "@XercesC_INCLUDE_DIR@" => "$xercesc_prefix/include/xercesc",
                          "@Julia_INCLUDE_DIR@" => "$julia_prefix/include/julia",
                          "@JlCxx_INCLUDE_DIR@" => "$cxxwrap_prefix/include",
                          "@CxxWrap_VERSION@" => "$(pkgversion(CxxWrap))"))
    end
end

rc = wrapit(wit, force=true, cmake=false, update=updatemode, verbosity=0)
if !isnothing(rc) && rc != 0
    println(stderr, "Failed to produce wrapper code with the wrapit function. Exited with code ", rc, ".")
    exit(rc)
end

cd(builddir)
run(`cmake -DCMAKE_BUILD_TYPE=Release
           -DCMAKE_CXX_STANDARD=17
           -DEXPAT_INCLUDE_DIR=$(Expat_jll.artifact_dir)/include
           -DEXPAT_LIBRARY=$(Expat_jll.libexpat)
           -DXercesC_INCLUDE_DIR=$(Xerces_jll.artifact_dir)/include
           -DCMAKE_PREFIX_PATH=$cxxwrap_prefix\;$geant4_prefix\;$xercesc_prefix  $sourcedir`)
run(`cmake --build . --config Release --parallel 8`)
