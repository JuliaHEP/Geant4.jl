module Geant4


import Base.getindex
import Base.setindex!

using CxxWrap
@wrapmodule("jlGeant4")

function __init__()
    @initcxx
end

end #module
