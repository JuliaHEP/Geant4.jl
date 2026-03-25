using Geant4
using Geant4.SystemOfUnits
using GLMakie

HepPolyhedron!SetNumberOfRotationSteps(64)
set_theme!(backgroundcolor = :black)

detname = "OpenDataDetector"
detector = G4JLDetectorGDML("$(@__DIR__)/$(detname).gdml"; validate_schema=false);

odd     = GetVolume("world_volume")[]
lstrips = GetVolume("LongStrips")[]
pixels  = GetVolume("Pixels")[]

for lv in (odd, lstrips, pixels)
  lvname = GetName(lv) |> String
  println("Drawing logical volume: $lvname")
  fig = Figure(size=(1080, 800))
  ax = LScene(fig[1, 1]; show_axis=false, scenekw=(;
      lights=[ PointLight(RGBf(1, 1, 1), Vec3f(1, 1, 0)),
               DirectionalLight(RGBf(1, 1, 1), Vec3f(1, 1, 1) ),
               AmbientLight(RGBf(.5, .5, .5)),
             ]))
  Camera3D(ax.scene, upvector=Vec3f(0, 1, 0), eyeposition=Vec3f(8m, 8m, 2m), lookat=Vec3f(0, 0, 0))
  draw!(ax, lv; maxlevel=7, clip=:xy);
  #display(fig)
  save("$(detname)_$(lvname).png", fig)
end
