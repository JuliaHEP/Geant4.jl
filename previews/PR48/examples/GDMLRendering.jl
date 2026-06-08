using Geant4
using Geant4.SystemOfUnits
using GLMakie

HepPolyhedron!SetNumberOfRotationSteps(64)
set_theme!(backgroundcolor = :black)

detname = "cms2018"
detector = G4JLDetectorGDML("$(@__DIR__)/$(detname).gdml"; validate_schema=false);

CMS     = GetVolume("CMSE")[]
tracker = GetVolume("Tracker")[]
muon    = GetVolume("MUON")[]
ebar    = GetVolume("EBAR")[]

for lv in (CMS, tracker, muon, ebar)
  lvname = GetName(lv) |> String
  println("Drawing logical volume: $lvname")
  fig = Figure(size=(1080, 800))
  ax = LScene(fig[1, 1]; show_axis=false, scenekw=(;
      lights=[ PointLight(RGBf(1, 1, 1), Vec3f(1, 1, 0)),
               DirectionalLight(RGBf(1, 1, 1), Vec3f(1, 1, 1) ),
               AmbientLight(RGBf(.5, .5, .5)),
             ]))
  Camera3D(ax.scene, upvector=Vec3f(0, 1, 0), eyeposition=Vec3f(8m, 8m, 2m), lookat=Vec3f(0, 0, 0))
  draw!(ax, lv; maxlevel=5, clip=:xy);
  #display(fig)
  save("$(detname)_$(lvname).png", fig)
end
