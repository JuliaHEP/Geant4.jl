// Example of a custom solid class that will be called by Julia 
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Orb.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"

// The custom solid class needs to inherit from G4VSolid and implement the required methods
class RoundCube : public G4VSolid
{
public:
  RoundCube(double a, double r);
  virtual ~RoundCube() { delete solid; }

  // Required methods for a custom solid
  virtual EInside Inside(const G4ThreeVector& p) const override {return solid->Inside(p);}
  virtual G4ThreeVector SurfaceNormal(const G4ThreeVector& p) const override {return solid->SurfaceNormal(p);}
  virtual G4double DistanceToIn(const G4ThreeVector& p, const G4ThreeVector& v) const override {return solid->DistanceToIn(p, v);}
  virtual G4double DistanceToIn(const G4ThreeVector& p) const override {return solid->DistanceToIn(p);}
  virtual G4double DistanceToOut(const G4ThreeVector& p, const G4ThreeVector& v, 
                                 const G4bool calcNorm=false, G4bool *validNorm=0, 
                                 G4ThreeVector *n=0) const override {return solid->DistanceToOut(p, v, calcNorm, validNorm, n);}
  virtual G4double DistanceToOut(const G4ThreeVector& p) const override {return solid->DistanceToOut(p);}
  virtual G4GeometryType GetEntityType() const override {return "RoundCube";}
  virtual std::ostream& StreamInfo(std::ostream& os) const override {os << "RoundCube with a = " << a << " r = " << r; return os;}

  virtual G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits& pVoxelLimits, const G4AffineTransform& pTransform, G4double& pMin, G4double& pMax) const override {return solid->CalculateExtent(pAxis, pVoxelLimits, pTransform, pMin, pMax);}
  virtual void DescribeYourselfTo (G4VGraphicsScene& scene) const override {return solid->DescribeYourselfTo(scene);}
  virtual void BoundingLimits(G4ThreeVector& pMin, G4ThreeVector& pMax) const override {return solid->BoundingLimits(pMin, pMax);}
private:
  G4VSolid* solid;
  double a, r;
};

// Constructor of the custom solid (RoundCube) implemented as a union and subtractions of several solids
RoundCube::RoundCube(double a, double r) : a(a), r(r), G4VSolid("RoundCube") {
  G4double ca = a / 4;
  G4VSolid* cube = new G4Box("cube", ca, ca, ca);
  G4VSolid* cyl = new G4Tubs("cyl", 0, r, ca, 0, 2 * M_PI);
  G4VSolid* orb = new G4Orb("orb", r);

  G4VSolid* edge = new G4Box("edge", r, r, ca);
  G4VSolid* vert = new G4Box("vert", r, r, r);
  G4VSolid* frame = new G4Box("frame", ca, ca, ca);

  G4VSolid* acyl1 = new G4SubtractionSolid("ucyl", edge, cyl, G4Transform3D(G4RotationMatrix(), G4ThreeVector(-r, -r, 0)));
  G4VSolid* acyl2 = new G4SubtractionSolid("ucyl", edge, cyl, G4Transform3D(G4RotationMatrix(), G4ThreeVector(-r, r, 0)));
  G4VSolid* acyl3 = new G4SubtractionSolid("ucyl", edge, cyl, G4Transform3D(G4RotationMatrix(), G4ThreeVector(r, r, 0)));
  G4VSolid* aorb  = new G4SubtractionSolid("uorb", vert, orb, G4Transform3D(G4RotationMatrix(), G4ThreeVector(-r, -r, -r)));

  G4Transform3D t1(G4RotationMatrix(), G4ThreeVector(ca, ca, 0));
  G4Transform3D t2(G4RotationMatrix(0, M_PI / 2, 0), G4ThreeVector(ca, 0, ca));
  G4Transform3D t3(G4RotationMatrix(0, M_PI / 2, M_PI / 2), G4ThreeVector(0, ca, ca));
  G4Transform3D t4(G4RotationMatrix(), G4ThreeVector(ca, ca, ca));

  G4VSolid* s1 = new G4SubtractionSolid("s1", cube, acyl1, t1);
  G4VSolid* s2 = new G4SubtractionSolid("s2", s1, acyl2, t2);
  G4VSolid* s3 = new G4SubtractionSolid("s3", s2, acyl3, t3);
  G4VSolid* s4 = new G4SubtractionSolid("s4", s3, aorb, t4);

  G4Transform3D t5(G4RotationMatrix(0, 0, 0), G4ThreeVector(ca, ca, ca));
  G4Transform3D t6(G4RotationMatrix(0, M_PI / 2, 0), G4ThreeVector(ca, ca, -ca));
  G4Transform3D t7(G4RotationMatrix(0, -M_PI / 2, 0), G4ThreeVector(ca, -ca, ca));
  G4Transform3D t8(G4RotationMatrix(0, M_PI / 2, M_PI / 2), G4ThreeVector(ca, -ca, -ca));

  G4VSolid* u1 = new G4UnionSolid("u1", frame, s4, t5);
  G4VSolid* u2 = new G4UnionSolid("u2", u1, s4, t6);
  G4VSolid* u3 = new G4UnionSolid("u3", u2, s4, t7);
  G4VSolid* u4 = new G4UnionSolid("u4", u3, s4, t8);

  solid = new G4UnionSolid("u5", u4, u4, G4Transform3D(G4RotationMatrix(0, 0, M_PI), G4ThreeVector()));
}

// Define the callable functions for the custom solid
extern "C" {
  G4VSolid* createRoundCube(double a, double r) {
    return new RoundCube(a, r);
  }
  void deleteRoundCube(G4VSolid* solid) {
    delete solid;
  }
  const char* infoRoundCube(G4VSolid* solid) {
    static std::string str;
    std::ostringstream os;
    solid->StreamInfo(os);
    str = os.str();
    return str.c_str();
  }
}

