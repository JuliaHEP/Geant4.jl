using Geant4
using Geant4.SystemOfUnits
using GLMakie                 # to force loading G4Vis extension

#detname = "LHCb_Upgrade_fullLHCb"
detname = "cms2018"

#---Create the detector geometry from a GDML file---------------------------------------------- 
detector = G4JLDetectorGDML("$(@__DIR__)/$(detname).gdml"; validate_schema=false);
#---Create the Application---------------------------------------------------------------------
app = G4JLApplication(;detector = detector,                          ## detector defined with a GDML file
                       physics_type = FTFP_BERT,                     ## what physics list to instantiate
                      );                   
configure(app)
initialize(app)                   ## Initialize Geant4 kernel (including the geometry)

world = GetWorldVolume()

#---Create the display scene-------------------------------------------------------------------
set_theme!(backgroundcolor = :black)
fig = Figure(size=(1280, 720))
sc = LScene(fig[1,1], show_axis=false)
Camera3D(sc.scene, upvector=Vec3f(0, 1, 0))
rotate_cam!(sc.scene, Vec3f(π, 0, 0))

# Cut out a wedge from θ1 to θ2
θ1, θ2 = 0, π / 2  # 0° to 90° wedge removed

# Part 1: everything with angle > θ2
n1 = Vec3f(sin(θ2), -cos(θ2), 0)
draw!(sc, world, maxlevel=5, clip_planes=[Makie.Plane3f(n1, 0f0)]);
# Part 2: everything with angle < θ1  
n2 = Vec3f(-sin(θ1), cos(θ1), 0)
draw!(sc, world, maxlevel=5, clip_planes=[Makie.Plane3f(n2, 0f0)]);
display(fig)

save("$(@__DIR__)/$(detname).png", fig)