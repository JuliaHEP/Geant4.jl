#---Generate the files here------------------------------------------------------------------------

#---Build the wrapper library----------------------------------------------------------------------
using CxxWrap

builddir = joinpath(@__DIR__, "build")
sourcedir = @__DIR__

mkpath(builddir)
cd(builddir)

LCG_prefix = "/Users/Shared/cvmfs/sft.cern.ch/lcg/views/dev4/latest/x86_64-mac11-clang120-opt"
run(`cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=$(CxxWrap.prefix_path())\;$LCG_prefix $sourcedir`)
run(`cmake --build . --config Release`)
