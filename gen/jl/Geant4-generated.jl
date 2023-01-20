module Geant4


using CxxWrap
@wrapmodule("jlGeant4")

function __init__()
    @initcxx
end

end #module
