#include <type_traits>
#include "jlcxx/jlcxx.hpp"
#include "jlcxx/functions.hpp"
#include "jlcxx/stl.hpp"

#include "jlGeant4.h"

#ifdef VERBOSE_IMPORT
#  define DEBUG_MSG(a) std::cerr << a << "\n"
#else
#  define DEBUG_MSG(a)
#endif
#define __HERE__  __FILE__ ":" QUOTE2(__LINE__)
#define QUOTE(arg) #arg
#define QUOTE2(arg) QUOTE(arg)

namespace jlcxx {
  template<> struct IsMirroredType<G4String> : std::false_type { };
  template<> struct IsMirroredType<G4Box> : std::false_type { };
  template<> struct IsMirroredType<G4VPVParameterisation> : std::false_type { };
  template<> struct IsMirroredType<G4VPhysicalVolume> : std::false_type { };
  template<> struct IsMirroredType<G4VSolid> : std::false_type { };
  template<> struct IsMirroredType<G4VoxelLimits> : std::false_type { };
  template<> struct IsMirroredType<G4AffineTransform> : std::false_type { };
  template<> struct IsMirroredType<G4Polyhedron> : std::false_type { };
  template<> struct IsMirroredType<G4Cons> : std::false_type { };
  template<> struct IsMirroredType<G4Orb> : std::false_type { };
  template<> struct IsMirroredType<G4Sphere> : std::false_type { };
  template<> struct IsMirroredType<G4Trd> : std::false_type { };
  template<> struct IsMirroredType<G4LVData> : std::false_type { };
  template<> struct IsMirroredType<G4Material> : std::false_type { };
  template<> struct IsMirroredType<G4LogicalVolume> : std::false_type { };
  template<> struct IsMirroredType<G4SmartVoxelHeader> : std::false_type { };
  template<> struct IsMirroredType<G4Region> : std::false_type { };
  template<> struct IsMirroredType<G4NavigationLevelRep> : std::false_type { };
  template<> struct IsMirroredType<G4RunManager> : std::false_type { };
  template<> struct IsMirroredType<G4Event> : std::false_type { };
  template<> struct IsMirroredType<G4UserStackingAction> : std::false_type { };
  template<> struct IsMirroredType<G4UserTrackingAction> : std::false_type { };
  template<> struct IsMirroredType<G4UserSteppingAction> : std::false_type { };
  template<> struct IsMirroredType<G4PrimaryTransformer> : std::false_type { };
  template<> struct IsMirroredType<G4NistManager> : std::false_type { };
  template<> struct IsMirroredType<G4Element> : std::false_type { };
  template<> struct IsMirroredType<G4ICRU90StoppingData> : std::false_type { };
  template<> struct IsMirroredType<G4PVPlacement> : std::false_type { };
  template<> struct IsMirroredType<G4ThreeVector> : std::false_type { };
  template<> struct IsMirroredType<G4RotationMatrix> : std::false_type { };
  template<> struct IsMirroredType<G4Transform3D> : std::false_type { };
  template<> struct SuperType<G4PVPlacement> { typedef G4VPhysicalVolume type; };
}

JLCXX_MODULE define_julia_module(jlcxx::Module& types){

  DEBUG_MSG("Adding wrapper for enum EAxis (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/geomdefs.hh:53:6
  types.add_bits<EAxis>("EAxis", jlcxx::julia_type("CppEnum"));
  types.set_const("kXAxis", kXAxis);
  types.set_const("kYAxis", kYAxis);
  types.set_const("kZAxis", kZAxis);
  types.set_const("kRho", kRho);
  types.set_const("kRadial3D", kRadial3D);
  types.set_const("kPhi", kPhi);
  types.set_const("kUndefined", kUndefined);

  DEBUG_MSG("Adding wrapper for enum EVolume (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/geomdefs.hh:82:6
  types.add_bits<EVolume>("EVolume", jlcxx::julia_type("CppEnum"));
  types.set_const("kNormal", kNormal);
  types.set_const("kReplica", kReplica);
  types.set_const("kParameterised", kParameterised);
  types.set_const("kExternal", kExternal);

  DEBUG_MSG("Adding wrapper for enum G4RunManager::RMType (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:575:10
  types.add_bits<G4RunManager::RMType>("G4RunManager!RMType", jlcxx::julia_type("CppEnum"));
  types.set_const("G4RunManager!sequentialRM", G4RunManager::sequentialRM);
  types.set_const("G4RunManager!masterRM", G4RunManager::masterRM);
  types.set_const("G4RunManager!workerRM", G4RunManager::workerRM);

  DEBUG_MSG("Adding wrapper for enum G4State (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4Material.hh:111:6
  types.add_bits<G4State>("G4State", jlcxx::julia_type("CppEnum"));
  types.set_const("kStateUndefined", kStateUndefined);
  types.set_const("kStateSolid", kStateSolid);
  types.set_const("kStateLiquid", kStateLiquid);
  types.set_const("kStateGas", kStateGas);

  DEBUG_MSG("Adding wrapper for type G4String (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4String.hh:61:7
  auto t0 = types.add_type<G4String>("G4String");

  DEBUG_MSG("Adding wrapper for type G4Box (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UBox.hh:45:7
  auto t1 = types.add_type<G4Box>("G4Box");

  DEBUG_MSG("Adding wrapper for type G4VPVParameterisation (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4VPVParameterisation.hh:68:7
  auto t2 = types.add_type<G4VPVParameterisation>("G4VPVParameterisation");

  DEBUG_MSG("Adding wrapper for type G4VPhysicalVolume (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4VPhysicalVolume.hh:78:7
  auto t3 = types.add_type<G4VPhysicalVolume>("G4VPhysicalVolume");

  DEBUG_MSG("Adding wrapper for type G4VSolid (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4VSolid.hh:82:7
  auto t4 = types.add_type<G4VSolid>("G4VSolid");

  DEBUG_MSG("Adding wrapper for type G4VoxelLimits (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4VoxelLimits.hh:52:7
  auto t6 = types.add_type<G4VoxelLimits>("G4VoxelLimits");

  DEBUG_MSG("Adding wrapper for type G4AffineTransform (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4AffineTransform.hh:69:7
  auto t7 = types.add_type<G4AffineTransform>("G4AffineTransform");

  DEBUG_MSG("Adding wrapper for type G4Polyhedron (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4Polyhedron.hh:123:7
  auto t8 = types.add_type<G4Polyhedron>("G4Polyhedron");

  DEBUG_MSG("Adding wrapper for type G4Cons (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:45:7
  auto t9 = types.add_type<G4Cons>("G4Cons");

  DEBUG_MSG("Adding wrapper for type G4Orb (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UOrb.hh:45:7
  auto t10 = types.add_type<G4Orb>("G4Orb");

  DEBUG_MSG("Adding wrapper for type G4Sphere (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:45:7
  auto t11 = types.add_type<G4Sphere>("G4Sphere");

  DEBUG_MSG("Adding wrapper for type G4Trd (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:45:7
  auto t12 = types.add_type<G4Trd>("G4Trd");

  DEBUG_MSG("Adding wrapper for type G4LVData (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:127:7
  auto t13 = types.add_type<G4LVData>("G4LVData");

  DEBUG_MSG("Adding wrapper for type G4Material (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4Material.hh:117:7
  auto t14 = types.add_type<G4Material>("G4Material");

  DEBUG_MSG("Adding wrapper for type G4LogicalVolume (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:181:7
  auto t15 = types.add_type<G4LogicalVolume>("G4LogicalVolume");

  DEBUG_MSG("Adding wrapper for type G4SmartVoxelHeader (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4SmartVoxelHeader.hh:74:7
  auto t17 = types.add_type<G4SmartVoxelHeader>("G4SmartVoxelHeader");

  DEBUG_MSG("Adding wrapper for type G4Region (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4Region.hh:95:7
  auto t18 = types.add_type<G4Region>("G4Region");

  DEBUG_MSG("Adding wrapper for type G4NavigationLevelRep (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NavigationLevelRep.hh:50:7
  auto t19 = types.add_type<G4NavigationLevelRep>("G4NavigationLevelRep");

  DEBUG_MSG("Adding wrapper for type G4RunManager (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:137:7
  auto t20 = types.add_type<G4RunManager>("G4RunManager");

  DEBUG_MSG("Adding wrapper for type G4Event (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4Event.hh:54:7
  auto t21 = types.add_type<G4Event>("G4Event");

  DEBUG_MSG("Adding wrapper for type G4UserStackingAction (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UserStackingAction.hh:44:7
  auto t22 = types.add_type<G4UserStackingAction>("G4UserStackingAction");

  DEBUG_MSG("Adding wrapper for type G4UserTrackingAction (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UserTrackingAction.hh:44:7
  auto t23 = types.add_type<G4UserTrackingAction>("G4UserTrackingAction");

  DEBUG_MSG("Adding wrapper for type G4UserSteppingAction (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UserSteppingAction.hh:44:7
  auto t24 = types.add_type<G4UserSteppingAction>("G4UserSteppingAction");

  DEBUG_MSG("Adding wrapper for type G4PrimaryTransformer (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4PrimaryTransformer.hh:47:7
  auto t25 = types.add_type<G4PrimaryTransformer>("G4PrimaryTransformer");

  DEBUG_MSG("Adding wrapper for type G4NistManager (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:83:7
  auto t27 = types.add_type<G4NistManager>("G4NistManager");

  DEBUG_MSG("Adding wrapper for type G4Element (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4Element.hh:97:7
  auto t28 = types.add_type<G4Element>("G4Element");

  DEBUG_MSG("Adding wrapper for type G4ICRU90StoppingData (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4ICRU90StoppingData.hh:56:7
  auto t30 = types.add_type<G4ICRU90StoppingData>("G4ICRU90StoppingData");

  DEBUG_MSG("Adding wrapper for type G4PVPlacement (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4PVPlacement.hh:43:7
  auto t31 = types.add_type<G4PVPlacement>("G4PVPlacement", jlcxx::julia_base_type<G4VPhysicalVolume>());

  /**********************************************************************
   * Wrappers for typedefs
   */
  DEBUG_MSG("Adding wrapper for type G4ThreeVector (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4ThreeVector.hh:36:7
  types.add_type<G4ThreeVector>("G4ThreeVector");

  DEBUG_MSG("Adding wrapper for type G4RotationMatrix (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RotationMatrix.hh:37:7
  types.add_type<G4RotationMatrix>("G4RotationMatrix");

  DEBUG_MSG("Adding wrapper for type G4GeometryType (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4VSolid.hh:80:7
  types.add_type<G4GeometryType>("G4GeometryType");

  DEBUG_MSG("Adding wrapper for type G4Transform3D (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4Transform3D.hh:34:30
  types.add_type<G4Transform3D>("G4Transform3D");


  /* End of typedefs wrappers
   **********************************************************************/


  /**********************************************************************/
  /* Wrappers for the methods of class G4String
   */


  DEBUG_MSG("Adding wrapper for void G4String::G4String(const G4String &) (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4String.icc:35:18
  t0.constructor<const G4String &>();



  /* End of G4String class method wrappers
   **********************************************************************/


  /**********************************************************************/
  /* Wrappers for the methods of class G4Box
   */


  DEBUG_MSG("Adding wrapper for void G4Box::G4Box(const G4String &, G4double, G4double, G4double) (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UBox.hh:52:5
  t1.constructor<const G4String &, G4double, G4double, G4double>();

  DEBUG_MSG("Adding wrapper for void G4Box::ComputeDimensions(G4VPVParameterisation *, const G4int, const G4VPhysicalVolume *) (" __HERE__ ")");
  // signature to use in the veto list: void G4Box::ComputeDimensions(G4VPVParameterisation *, const G4int, const G4VPhysicalVolume *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UBox.hh:57:10
  t1.method("ComputeDimensions", static_cast<void (G4Box::*)(G4VPVParameterisation *, const G4int, const G4VPhysicalVolume *) >(&G4Box::ComputeDimensions));

  DEBUG_MSG("Adding wrapper for G4VSolid * G4Box::Clone() (" __HERE__ ")");
  // signature to use in the veto list: G4VSolid * G4Box::Clone()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UBox.hh:61:15
  t1.method("Clone", static_cast<G4VSolid * (G4Box::*)()  const>(&G4Box::Clone));

  DEBUG_MSG("Adding wrapper for G4double G4Box::GetXHalfLength() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Box::GetXHalfLength()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UBox.hh:63:14
  t1.method("GetXHalfLength", static_cast<G4double (G4Box::*)()  const>(&G4Box::GetXHalfLength));

  DEBUG_MSG("Adding wrapper for G4double G4Box::GetYHalfLength() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Box::GetYHalfLength()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UBox.hh:64:14
  t1.method("GetYHalfLength", static_cast<G4double (G4Box::*)()  const>(&G4Box::GetYHalfLength));

  DEBUG_MSG("Adding wrapper for G4double G4Box::GetZHalfLength() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Box::GetZHalfLength()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UBox.hh:65:14
  t1.method("GetZHalfLength", static_cast<G4double (G4Box::*)()  const>(&G4Box::GetZHalfLength));

  DEBUG_MSG("Adding wrapper for void G4Box::SetXHalfLength(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Box::SetXHalfLength(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UBox.hh:67:10
  t1.method("SetXHalfLength", static_cast<void (G4Box::*)(G4double) >(&G4Box::SetXHalfLength));

  DEBUG_MSG("Adding wrapper for void G4Box::SetYHalfLength(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Box::SetYHalfLength(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UBox.hh:68:10
  t1.method("SetYHalfLength", static_cast<void (G4Box::*)(G4double) >(&G4Box::SetYHalfLength));

  DEBUG_MSG("Adding wrapper for void G4Box::SetZHalfLength(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Box::SetZHalfLength(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UBox.hh:69:10
  t1.method("SetZHalfLength", static_cast<void (G4Box::*)(G4double) >(&G4Box::SetZHalfLength));

  DEBUG_MSG("Adding wrapper for G4GeometryType G4Box::GetEntityType() (" __HERE__ ")");
  // signature to use in the veto list: G4GeometryType G4Box::GetEntityType()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UBox.hh:71:27
  t1.method("GetEntityType", static_cast<G4GeometryType (G4Box::*)()  const>(&G4Box::GetEntityType));

  DEBUG_MSG("Adding wrapper for void G4Box::BoundingLimits(G4ThreeVector &, G4ThreeVector &) (" __HERE__ ")");
  // signature to use in the veto list: void G4Box::BoundingLimits(G4ThreeVector &, G4ThreeVector &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UBox.hh:73:10
  t1.method("BoundingLimits", static_cast<void (G4Box::*)(G4ThreeVector &, G4ThreeVector &)  const>(&G4Box::BoundingLimits));

  DEBUG_MSG("Adding wrapper for G4bool G4Box::CalculateExtent(const EAxis, const G4VoxelLimits &, const G4AffineTransform &, G4double &, G4double &) (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4Box::CalculateExtent(const EAxis, const G4VoxelLimits &, const G4AffineTransform &, G4double &, G4double &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UBox.hh:75:12
  t1.method("CalculateExtent", static_cast<G4bool (G4Box::*)(const EAxis, const G4VoxelLimits &, const G4AffineTransform &, G4double &, G4double &)  const>(&G4Box::CalculateExtent));

  DEBUG_MSG("Adding wrapper for G4Polyhedron * G4Box::CreatePolyhedron() (" __HERE__ ")");
  // signature to use in the veto list: G4Polyhedron * G4Box::CreatePolyhedron()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UBox.hh:80:19
  t1.method("CreatePolyhedron", static_cast<G4Polyhedron * (G4Box::*)()  const>(&G4Box::CreatePolyhedron));


  DEBUG_MSG("Adding wrapper for void G4Box::G4Box(const G4Box &) (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UBox.hh:89:5
  t1.constructor<const G4Box &>();

  DEBUG_MSG("Adding wrapper for G4Box & G4Box::operator=(const G4Box &) (" __HERE__ ")");
  // signature to use in the veto list: G4Box & G4Box::operator=(const G4Box &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UBox.hh:90:13
  t1.method("assign", static_cast<G4Box & (G4Box::*)(const G4Box &) >(&G4Box::operator=));

  /* End of G4Box class method wrappers
   **********************************************************************/


  /**********************************************************************/
  /* Wrappers for the methods of class G4Cons
   */


  DEBUG_MSG("Adding wrapper for void G4Cons::G4Cons(const G4String &, G4double, G4double, G4double, G4double, G4double, G4double, G4double) (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:52:5
  t9.constructor<const G4String &, G4double, G4double, G4double, G4double, G4double, G4double, G4double>();

  DEBUG_MSG("Adding wrapper for void G4Cons::ComputeDimensions(G4VPVParameterisation *, const G4int, const G4VPhysicalVolume *) (" __HERE__ ")");
  // signature to use in the veto list: void G4Cons::ComputeDimensions(G4VPVParameterisation *, const G4int, const G4VPhysicalVolume *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:61:10
  t9.method("ComputeDimensions", static_cast<void (G4Cons::*)(G4VPVParameterisation *, const G4int, const G4VPhysicalVolume *) >(&G4Cons::ComputeDimensions));

  DEBUG_MSG("Adding wrapper for G4VSolid * G4Cons::Clone() (" __HERE__ ")");
  // signature to use in the veto list: G4VSolid * G4Cons::Clone()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:65:15
  t9.method("Clone", static_cast<G4VSolid * (G4Cons::*)()  const>(&G4Cons::Clone));

  DEBUG_MSG("Adding wrapper for G4double G4Cons::GetInnerRadiusMinusZ() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Cons::GetInnerRadiusMinusZ()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:67:14
  t9.method("GetInnerRadiusMinusZ", static_cast<G4double (G4Cons::*)()  const>(&G4Cons::GetInnerRadiusMinusZ));

  DEBUG_MSG("Adding wrapper for G4double G4Cons::GetOuterRadiusMinusZ() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Cons::GetOuterRadiusMinusZ()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:68:14
  t9.method("GetOuterRadiusMinusZ", static_cast<G4double (G4Cons::*)()  const>(&G4Cons::GetOuterRadiusMinusZ));

  DEBUG_MSG("Adding wrapper for G4double G4Cons::GetInnerRadiusPlusZ() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Cons::GetInnerRadiusPlusZ()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:69:14
  t9.method("GetInnerRadiusPlusZ", static_cast<G4double (G4Cons::*)()  const>(&G4Cons::GetInnerRadiusPlusZ));

  DEBUG_MSG("Adding wrapper for G4double G4Cons::GetOuterRadiusPlusZ() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Cons::GetOuterRadiusPlusZ()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:70:14
  t9.method("GetOuterRadiusPlusZ", static_cast<G4double (G4Cons::*)()  const>(&G4Cons::GetOuterRadiusPlusZ));

  DEBUG_MSG("Adding wrapper for G4double G4Cons::GetZHalfLength() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Cons::GetZHalfLength()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:71:14
  t9.method("GetZHalfLength", static_cast<G4double (G4Cons::*)()  const>(&G4Cons::GetZHalfLength));

  DEBUG_MSG("Adding wrapper for G4double G4Cons::GetStartPhiAngle() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Cons::GetStartPhiAngle()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:72:14
  t9.method("GetStartPhiAngle", static_cast<G4double (G4Cons::*)()  const>(&G4Cons::GetStartPhiAngle));

  DEBUG_MSG("Adding wrapper for G4double G4Cons::GetDeltaPhiAngle() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Cons::GetDeltaPhiAngle()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:73:14
  t9.method("GetDeltaPhiAngle", static_cast<G4double (G4Cons::*)()  const>(&G4Cons::GetDeltaPhiAngle));

  DEBUG_MSG("Adding wrapper for G4double G4Cons::GetSinStartPhi() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Cons::GetSinStartPhi()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:74:14
  t9.method("GetSinStartPhi", static_cast<G4double (G4Cons::*)()  const>(&G4Cons::GetSinStartPhi));

  DEBUG_MSG("Adding wrapper for G4double G4Cons::GetCosStartPhi() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Cons::GetCosStartPhi()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:75:14
  t9.method("GetCosStartPhi", static_cast<G4double (G4Cons::*)()  const>(&G4Cons::GetCosStartPhi));

  DEBUG_MSG("Adding wrapper for G4double G4Cons::GetSinEndPhi() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Cons::GetSinEndPhi()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:76:14
  t9.method("GetSinEndPhi", static_cast<G4double (G4Cons::*)()  const>(&G4Cons::GetSinEndPhi));

  DEBUG_MSG("Adding wrapper for G4double G4Cons::GetCosEndPhi() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Cons::GetCosEndPhi()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:77:14
  t9.method("GetCosEndPhi", static_cast<G4double (G4Cons::*)()  const>(&G4Cons::GetCosEndPhi));

  DEBUG_MSG("Adding wrapper for void G4Cons::SetInnerRadiusMinusZ(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Cons::SetInnerRadiusMinusZ(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:79:10
  t9.method("SetInnerRadiusMinusZ", static_cast<void (G4Cons::*)(G4double) >(&G4Cons::SetInnerRadiusMinusZ));

  DEBUG_MSG("Adding wrapper for void G4Cons::SetOuterRadiusMinusZ(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Cons::SetOuterRadiusMinusZ(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:80:10
  t9.method("SetOuterRadiusMinusZ", static_cast<void (G4Cons::*)(G4double) >(&G4Cons::SetOuterRadiusMinusZ));

  DEBUG_MSG("Adding wrapper for void G4Cons::SetInnerRadiusPlusZ(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Cons::SetInnerRadiusPlusZ(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:81:10
  t9.method("SetInnerRadiusPlusZ", static_cast<void (G4Cons::*)(G4double) >(&G4Cons::SetInnerRadiusPlusZ));

  DEBUG_MSG("Adding wrapper for void G4Cons::SetOuterRadiusPlusZ(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Cons::SetOuterRadiusPlusZ(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:82:10
  t9.method("SetOuterRadiusPlusZ", static_cast<void (G4Cons::*)(G4double) >(&G4Cons::SetOuterRadiusPlusZ));

  DEBUG_MSG("Adding wrapper for void G4Cons::SetZHalfLength(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Cons::SetZHalfLength(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:83:10
  t9.method("SetZHalfLength", static_cast<void (G4Cons::*)(G4double) >(&G4Cons::SetZHalfLength));

  DEBUG_MSG("Adding wrapper for void G4Cons::SetStartPhiAngle(G4double, G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4Cons::SetStartPhiAngle(G4double, G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:84:10
  t9.method("SetStartPhiAngle", static_cast<void (G4Cons::*)(G4double, G4bool) >(&G4Cons::SetStartPhiAngle));
  t9.method("SetStartPhiAngle", [](G4Cons& a, G4double arg0)->void{ a.SetStartPhiAngle(arg0); });
  t9.method("SetStartPhiAngle", [](G4Cons* a, G4double arg0)->void{ a->SetStartPhiAngle(arg0); });

  DEBUG_MSG("Adding wrapper for void G4Cons::SetDeltaPhiAngle(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Cons::SetDeltaPhiAngle(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:85:10
  t9.method("SetDeltaPhiAngle", static_cast<void (G4Cons::*)(G4double) >(&G4Cons::SetDeltaPhiAngle));

  DEBUG_MSG("Adding wrapper for G4GeometryType G4Cons::GetEntityType() (" __HERE__ ")");
  // signature to use in the veto list: G4GeometryType G4Cons::GetEntityType()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:87:27
  t9.method("GetEntityType", static_cast<G4GeometryType (G4Cons::*)()  const>(&G4Cons::GetEntityType));

  DEBUG_MSG("Adding wrapper for void G4Cons::BoundingLimits(G4ThreeVector &, G4ThreeVector &) (" __HERE__ ")");
  // signature to use in the veto list: void G4Cons::BoundingLimits(G4ThreeVector &, G4ThreeVector &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:89:10
  t9.method("BoundingLimits", static_cast<void (G4Cons::*)(G4ThreeVector &, G4ThreeVector &)  const>(&G4Cons::BoundingLimits));

  DEBUG_MSG("Adding wrapper for G4bool G4Cons::CalculateExtent(const EAxis, const G4VoxelLimits &, const G4AffineTransform &, G4double &, G4double &) (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4Cons::CalculateExtent(const EAxis, const G4VoxelLimits &, const G4AffineTransform &, G4double &, G4double &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:91:12
  t9.method("CalculateExtent", static_cast<G4bool (G4Cons::*)(const EAxis, const G4VoxelLimits &, const G4AffineTransform &, G4double &, G4double &)  const>(&G4Cons::CalculateExtent));

  DEBUG_MSG("Adding wrapper for G4Polyhedron * G4Cons::CreatePolyhedron() (" __HERE__ ")");
  // signature to use in the veto list: G4Polyhedron * G4Cons::CreatePolyhedron()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:96:19
  t9.method("CreatePolyhedron", static_cast<G4Polyhedron * (G4Cons::*)()  const>(&G4Cons::CreatePolyhedron));


  DEBUG_MSG("Adding wrapper for void G4Cons::G4Cons(const G4Cons &) (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:105:5
  t9.constructor<const G4Cons &>();

  DEBUG_MSG("Adding wrapper for G4Cons & G4Cons::operator=(const G4Cons &) (" __HERE__ ")");
  // signature to use in the veto list: G4Cons & G4Cons::operator=(const G4Cons &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:106:14
  t9.method("assign", static_cast<G4Cons & (G4Cons::*)(const G4Cons &) >(&G4Cons::operator=));

  /* End of G4Cons class method wrappers
   **********************************************************************/


  /**********************************************************************/
  /* Wrappers for the methods of class G4Orb
   */


  DEBUG_MSG("Adding wrapper for void G4Orb::G4Orb(const G4String &, G4double) (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UOrb.hh:52:5
  t10.constructor<const G4String &, G4double>();

  DEBUG_MSG("Adding wrapper for void G4Orb::ComputeDimensions(G4VPVParameterisation *, const G4int, const G4VPhysicalVolume *) (" __HERE__ ")");
  // signature to use in the veto list: void G4Orb::ComputeDimensions(G4VPVParameterisation *, const G4int, const G4VPhysicalVolume *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UOrb.hh:56:10
  t10.method("ComputeDimensions", static_cast<void (G4Orb::*)(G4VPVParameterisation *, const G4int, const G4VPhysicalVolume *) >(&G4Orb::ComputeDimensions));

  DEBUG_MSG("Adding wrapper for G4VSolid * G4Orb::Clone() (" __HERE__ ")");
  // signature to use in the veto list: G4VSolid * G4Orb::Clone()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UOrb.hh:60:15
  t10.method("Clone", static_cast<G4VSolid * (G4Orb::*)()  const>(&G4Orb::Clone));

  DEBUG_MSG("Adding wrapper for G4double G4Orb::GetRadius() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Orb::GetRadius()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UOrb.hh:62:14
  t10.method("GetRadius", static_cast<G4double (G4Orb::*)()  const>(&G4Orb::GetRadius));

  DEBUG_MSG("Adding wrapper for void G4Orb::SetRadius(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Orb::SetRadius(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UOrb.hh:63:10
  t10.method("SetRadius", static_cast<void (G4Orb::*)(G4double) >(&G4Orb::SetRadius));

  DEBUG_MSG("Adding wrapper for G4double G4Orb::GetRadialTolerance() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Orb::GetRadialTolerance()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UOrb.hh:64:14
  t10.method("GetRadialTolerance", static_cast<G4double (G4Orb::*)()  const>(&G4Orb::GetRadialTolerance));

  DEBUG_MSG("Adding wrapper for G4GeometryType G4Orb::GetEntityType() (" __HERE__ ")");
  // signature to use in the veto list: G4GeometryType G4Orb::GetEntityType()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UOrb.hh:66:27
  t10.method("GetEntityType", static_cast<G4GeometryType (G4Orb::*)()  const>(&G4Orb::GetEntityType));

  DEBUG_MSG("Adding wrapper for void G4Orb::BoundingLimits(G4ThreeVector &, G4ThreeVector &) (" __HERE__ ")");
  // signature to use in the veto list: void G4Orb::BoundingLimits(G4ThreeVector &, G4ThreeVector &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UOrb.hh:68:10
  t10.method("BoundingLimits", static_cast<void (G4Orb::*)(G4ThreeVector &, G4ThreeVector &)  const>(&G4Orb::BoundingLimits));

  DEBUG_MSG("Adding wrapper for G4bool G4Orb::CalculateExtent(const EAxis, const G4VoxelLimits &, const G4AffineTransform &, G4double &, G4double &) (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4Orb::CalculateExtent(const EAxis, const G4VoxelLimits &, const G4AffineTransform &, G4double &, G4double &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UOrb.hh:70:12
  t10.method("CalculateExtent", static_cast<G4bool (G4Orb::*)(const EAxis, const G4VoxelLimits &, const G4AffineTransform &, G4double &, G4double &)  const>(&G4Orb::CalculateExtent));

  DEBUG_MSG("Adding wrapper for G4Polyhedron * G4Orb::CreatePolyhedron() (" __HERE__ ")");
  // signature to use in the veto list: G4Polyhedron * G4Orb::CreatePolyhedron()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UOrb.hh:75:19
  t10.method("CreatePolyhedron", static_cast<G4Polyhedron * (G4Orb::*)()  const>(&G4Orb::CreatePolyhedron));


  DEBUG_MSG("Adding wrapper for void G4Orb::G4Orb(const G4Orb &) (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UOrb.hh:84:5
  t10.constructor<const G4Orb &>();

  DEBUG_MSG("Adding wrapper for G4Orb & G4Orb::operator=(const G4Orb &) (" __HERE__ ")");
  // signature to use in the veto list: G4Orb & G4Orb::operator=(const G4Orb &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UOrb.hh:85:13
  t10.method("assign", static_cast<G4Orb & (G4Orb::*)(const G4Orb &) >(&G4Orb::operator=));

  /* End of G4Orb class method wrappers
   **********************************************************************/


  /**********************************************************************/
  /* Wrappers for the methods of class G4Sphere
   */


  DEBUG_MSG("Adding wrapper for void G4Sphere::G4Sphere(const G4String &, G4double, G4double, G4double, G4double, G4double, G4double) (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:52:5
  t11.constructor<const G4String &, G4double, G4double, G4double, G4double, G4double, G4double>();

  DEBUG_MSG("Adding wrapper for void G4Sphere::ComputeDimensions(G4VPVParameterisation *, const G4int, const G4VPhysicalVolume *) (" __HERE__ ")");
  // signature to use in the veto list: void G4Sphere::ComputeDimensions(G4VPVParameterisation *, const G4int, const G4VPhysicalVolume *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:61:10
  t11.method("ComputeDimensions", static_cast<void (G4Sphere::*)(G4VPVParameterisation *, const G4int, const G4VPhysicalVolume *) >(&G4Sphere::ComputeDimensions));

  DEBUG_MSG("Adding wrapper for G4VSolid * G4Sphere::Clone() (" __HERE__ ")");
  // signature to use in the veto list: G4VSolid * G4Sphere::Clone()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:65:15
  t11.method("Clone", static_cast<G4VSolid * (G4Sphere::*)()  const>(&G4Sphere::Clone));

  DEBUG_MSG("Adding wrapper for G4double G4Sphere::GetInnerRadius() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Sphere::GetInnerRadius()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:67:14
  t11.method("GetInnerRadius", static_cast<G4double (G4Sphere::*)()  const>(&G4Sphere::GetInnerRadius));

  DEBUG_MSG("Adding wrapper for G4double G4Sphere::GetOuterRadius() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Sphere::GetOuterRadius()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:68:14
  t11.method("GetOuterRadius", static_cast<G4double (G4Sphere::*)()  const>(&G4Sphere::GetOuterRadius));

  DEBUG_MSG("Adding wrapper for G4double G4Sphere::GetStartPhiAngle() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Sphere::GetStartPhiAngle()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:69:14
  t11.method("GetStartPhiAngle", static_cast<G4double (G4Sphere::*)()  const>(&G4Sphere::GetStartPhiAngle));

  DEBUG_MSG("Adding wrapper for G4double G4Sphere::GetDeltaPhiAngle() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Sphere::GetDeltaPhiAngle()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:70:14
  t11.method("GetDeltaPhiAngle", static_cast<G4double (G4Sphere::*)()  const>(&G4Sphere::GetDeltaPhiAngle));

  DEBUG_MSG("Adding wrapper for G4double G4Sphere::GetStartThetaAngle() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Sphere::GetStartThetaAngle()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:71:14
  t11.method("GetStartThetaAngle", static_cast<G4double (G4Sphere::*)()  const>(&G4Sphere::GetStartThetaAngle));

  DEBUG_MSG("Adding wrapper for G4double G4Sphere::GetDeltaThetaAngle() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Sphere::GetDeltaThetaAngle()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:72:14
  t11.method("GetDeltaThetaAngle", static_cast<G4double (G4Sphere::*)()  const>(&G4Sphere::GetDeltaThetaAngle));

  DEBUG_MSG("Adding wrapper for G4double G4Sphere::GetSinStartPhi() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Sphere::GetSinStartPhi()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:73:14
  t11.method("GetSinStartPhi", static_cast<G4double (G4Sphere::*)()  const>(&G4Sphere::GetSinStartPhi));

  DEBUG_MSG("Adding wrapper for G4double G4Sphere::GetCosStartPhi() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Sphere::GetCosStartPhi()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:74:14
  t11.method("GetCosStartPhi", static_cast<G4double (G4Sphere::*)()  const>(&G4Sphere::GetCosStartPhi));

  DEBUG_MSG("Adding wrapper for G4double G4Sphere::GetSinEndPhi() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Sphere::GetSinEndPhi()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:75:14
  t11.method("GetSinEndPhi", static_cast<G4double (G4Sphere::*)()  const>(&G4Sphere::GetSinEndPhi));

  DEBUG_MSG("Adding wrapper for G4double G4Sphere::GetCosEndPhi() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Sphere::GetCosEndPhi()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:76:14
  t11.method("GetCosEndPhi", static_cast<G4double (G4Sphere::*)()  const>(&G4Sphere::GetCosEndPhi));

  DEBUG_MSG("Adding wrapper for G4double G4Sphere::GetSinStartTheta() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Sphere::GetSinStartTheta()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:77:14
  t11.method("GetSinStartTheta", static_cast<G4double (G4Sphere::*)()  const>(&G4Sphere::GetSinStartTheta));

  DEBUG_MSG("Adding wrapper for G4double G4Sphere::GetCosStartTheta() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Sphere::GetCosStartTheta()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:78:14
  t11.method("GetCosStartTheta", static_cast<G4double (G4Sphere::*)()  const>(&G4Sphere::GetCosStartTheta));

  DEBUG_MSG("Adding wrapper for G4double G4Sphere::GetSinEndTheta() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Sphere::GetSinEndTheta()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:79:14
  t11.method("GetSinEndTheta", static_cast<G4double (G4Sphere::*)()  const>(&G4Sphere::GetSinEndTheta));

  DEBUG_MSG("Adding wrapper for G4double G4Sphere::GetCosEndTheta() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Sphere::GetCosEndTheta()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:80:14
  t11.method("GetCosEndTheta", static_cast<G4double (G4Sphere::*)()  const>(&G4Sphere::GetCosEndTheta));

  DEBUG_MSG("Adding wrapper for void G4Sphere::SetInnerRadius(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Sphere::SetInnerRadius(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:82:10
  t11.method("SetInnerRadius", static_cast<void (G4Sphere::*)(G4double) >(&G4Sphere::SetInnerRadius));

  DEBUG_MSG("Adding wrapper for void G4Sphere::SetOuterRadius(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Sphere::SetOuterRadius(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:83:10
  t11.method("SetOuterRadius", static_cast<void (G4Sphere::*)(G4double) >(&G4Sphere::SetOuterRadius));

  DEBUG_MSG("Adding wrapper for void G4Sphere::SetStartPhiAngle(G4double, G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4Sphere::SetStartPhiAngle(G4double, G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:84:10
  t11.method("SetStartPhiAngle", static_cast<void (G4Sphere::*)(G4double, G4bool) >(&G4Sphere::SetStartPhiAngle));
  t11.method("SetStartPhiAngle", [](G4Sphere& a, G4double arg0)->void{ a.SetStartPhiAngle(arg0); });
  t11.method("SetStartPhiAngle", [](G4Sphere* a, G4double arg0)->void{ a->SetStartPhiAngle(arg0); });

  DEBUG_MSG("Adding wrapper for void G4Sphere::SetDeltaPhiAngle(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Sphere::SetDeltaPhiAngle(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:85:10
  t11.method("SetDeltaPhiAngle", static_cast<void (G4Sphere::*)(G4double) >(&G4Sphere::SetDeltaPhiAngle));

  DEBUG_MSG("Adding wrapper for void G4Sphere::SetStartThetaAngle(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Sphere::SetStartThetaAngle(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:86:10
  t11.method("SetStartThetaAngle", static_cast<void (G4Sphere::*)(G4double) >(&G4Sphere::SetStartThetaAngle));

  DEBUG_MSG("Adding wrapper for void G4Sphere::SetDeltaThetaAngle(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Sphere::SetDeltaThetaAngle(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:87:10
  t11.method("SetDeltaThetaAngle", static_cast<void (G4Sphere::*)(G4double) >(&G4Sphere::SetDeltaThetaAngle));

  DEBUG_MSG("Adding wrapper for G4GeometryType G4Sphere::GetEntityType() (" __HERE__ ")");
  // signature to use in the veto list: G4GeometryType G4Sphere::GetEntityType()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:89:27
  t11.method("GetEntityType", static_cast<G4GeometryType (G4Sphere::*)()  const>(&G4Sphere::GetEntityType));

  DEBUG_MSG("Adding wrapper for void G4Sphere::BoundingLimits(G4ThreeVector &, G4ThreeVector &) (" __HERE__ ")");
  // signature to use in the veto list: void G4Sphere::BoundingLimits(G4ThreeVector &, G4ThreeVector &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:91:10
  t11.method("BoundingLimits", static_cast<void (G4Sphere::*)(G4ThreeVector &, G4ThreeVector &)  const>(&G4Sphere::BoundingLimits));

  DEBUG_MSG("Adding wrapper for G4bool G4Sphere::CalculateExtent(const EAxis, const G4VoxelLimits &, const G4AffineTransform &, G4double &, G4double &) (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4Sphere::CalculateExtent(const EAxis, const G4VoxelLimits &, const G4AffineTransform &, G4double &, G4double &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:93:12
  t11.method("CalculateExtent", static_cast<G4bool (G4Sphere::*)(const EAxis, const G4VoxelLimits &, const G4AffineTransform &, G4double &, G4double &)  const>(&G4Sphere::CalculateExtent));

  DEBUG_MSG("Adding wrapper for G4Polyhedron * G4Sphere::CreatePolyhedron() (" __HERE__ ")");
  // signature to use in the veto list: G4Polyhedron * G4Sphere::CreatePolyhedron()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:98:19
  t11.method("CreatePolyhedron", static_cast<G4Polyhedron * (G4Sphere::*)()  const>(&G4Sphere::CreatePolyhedron));


  DEBUG_MSG("Adding wrapper for void G4Sphere::G4Sphere(const G4Sphere &) (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:108:5
  t11.constructor<const G4Sphere &>();

  DEBUG_MSG("Adding wrapper for G4Sphere & G4Sphere::operator=(const G4Sphere &) (" __HERE__ ")");
  // signature to use in the veto list: G4Sphere & G4Sphere::operator=(const G4Sphere &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:109:16
  t11.method("assign", static_cast<G4Sphere & (G4Sphere::*)(const G4Sphere &) >(&G4Sphere::operator=));

  /* End of G4Sphere class method wrappers
   **********************************************************************/


  /**********************************************************************/
  /* Wrappers for the methods of class G4Trd
   */


  DEBUG_MSG("Adding wrapper for void G4Trd::G4Trd(const G4String &, G4double, G4double, G4double, G4double, G4double) (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:52:5
  t12.constructor<const G4String &, G4double, G4double, G4double, G4double, G4double>();

  DEBUG_MSG("Adding wrapper for void G4Trd::ComputeDimensions(G4VPVParameterisation *, const G4int, const G4VPhysicalVolume *) (" __HERE__ ")");
  // signature to use in the veto list: void G4Trd::ComputeDimensions(G4VPVParameterisation *, const G4int, const G4VPhysicalVolume *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:60:10
  t12.method("ComputeDimensions", static_cast<void (G4Trd::*)(G4VPVParameterisation *, const G4int, const G4VPhysicalVolume *) >(&G4Trd::ComputeDimensions));

  DEBUG_MSG("Adding wrapper for G4VSolid * G4Trd::Clone() (" __HERE__ ")");
  // signature to use in the veto list: G4VSolid * G4Trd::Clone()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:64:15
  t12.method("Clone", static_cast<G4VSolid * (G4Trd::*)()  const>(&G4Trd::Clone));

  DEBUG_MSG("Adding wrapper for G4double G4Trd::GetXHalfLength1() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Trd::GetXHalfLength1()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:66:14
  t12.method("GetXHalfLength1", static_cast<G4double (G4Trd::*)()  const>(&G4Trd::GetXHalfLength1));

  DEBUG_MSG("Adding wrapper for G4double G4Trd::GetXHalfLength2() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Trd::GetXHalfLength2()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:67:14
  t12.method("GetXHalfLength2", static_cast<G4double (G4Trd::*)()  const>(&G4Trd::GetXHalfLength2));

  DEBUG_MSG("Adding wrapper for G4double G4Trd::GetYHalfLength1() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Trd::GetYHalfLength1()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:68:14
  t12.method("GetYHalfLength1", static_cast<G4double (G4Trd::*)()  const>(&G4Trd::GetYHalfLength1));

  DEBUG_MSG("Adding wrapper for G4double G4Trd::GetYHalfLength2() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Trd::GetYHalfLength2()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:69:14
  t12.method("GetYHalfLength2", static_cast<G4double (G4Trd::*)()  const>(&G4Trd::GetYHalfLength2));

  DEBUG_MSG("Adding wrapper for G4double G4Trd::GetZHalfLength() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Trd::GetZHalfLength()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:70:14
  t12.method("GetZHalfLength", static_cast<G4double (G4Trd::*)()  const>(&G4Trd::GetZHalfLength));

  DEBUG_MSG("Adding wrapper for void G4Trd::SetXHalfLength1(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Trd::SetXHalfLength1(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:72:10
  t12.method("SetXHalfLength1", static_cast<void (G4Trd::*)(G4double) >(&G4Trd::SetXHalfLength1));

  DEBUG_MSG("Adding wrapper for void G4Trd::SetXHalfLength2(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Trd::SetXHalfLength2(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:73:10
  t12.method("SetXHalfLength2", static_cast<void (G4Trd::*)(G4double) >(&G4Trd::SetXHalfLength2));

  DEBUG_MSG("Adding wrapper for void G4Trd::SetYHalfLength1(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Trd::SetYHalfLength1(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:74:10
  t12.method("SetYHalfLength1", static_cast<void (G4Trd::*)(G4double) >(&G4Trd::SetYHalfLength1));

  DEBUG_MSG("Adding wrapper for void G4Trd::SetYHalfLength2(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Trd::SetYHalfLength2(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:75:10
  t12.method("SetYHalfLength2", static_cast<void (G4Trd::*)(G4double) >(&G4Trd::SetYHalfLength2));

  DEBUG_MSG("Adding wrapper for void G4Trd::SetZHalfLength(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Trd::SetZHalfLength(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:76:10
  t12.method("SetZHalfLength", static_cast<void (G4Trd::*)(G4double) >(&G4Trd::SetZHalfLength));

  DEBUG_MSG("Adding wrapper for void G4Trd::SetAllParameters(G4double, G4double, G4double, G4double, G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Trd::SetAllParameters(G4double, G4double, G4double, G4double, G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:78:10
  t12.method("SetAllParameters", static_cast<void (G4Trd::*)(G4double, G4double, G4double, G4double, G4double) >(&G4Trd::SetAllParameters));

  DEBUG_MSG("Adding wrapper for G4GeometryType G4Trd::GetEntityType() (" __HERE__ ")");
  // signature to use in the veto list: G4GeometryType G4Trd::GetEntityType()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:81:27
  t12.method("GetEntityType", static_cast<G4GeometryType (G4Trd::*)()  const>(&G4Trd::GetEntityType));

  DEBUG_MSG("Adding wrapper for void G4Trd::BoundingLimits(G4ThreeVector &, G4ThreeVector &) (" __HERE__ ")");
  // signature to use in the veto list: void G4Trd::BoundingLimits(G4ThreeVector &, G4ThreeVector &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:83:10
  t12.method("BoundingLimits", static_cast<void (G4Trd::*)(G4ThreeVector &, G4ThreeVector &)  const>(&G4Trd::BoundingLimits));

  DEBUG_MSG("Adding wrapper for G4bool G4Trd::CalculateExtent(const EAxis, const G4VoxelLimits &, const G4AffineTransform &, G4double &, G4double &) (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4Trd::CalculateExtent(const EAxis, const G4VoxelLimits &, const G4AffineTransform &, G4double &, G4double &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:85:12
  t12.method("CalculateExtent", static_cast<G4bool (G4Trd::*)(const EAxis, const G4VoxelLimits &, const G4AffineTransform &, G4double &, G4double &)  const>(&G4Trd::CalculateExtent));

  DEBUG_MSG("Adding wrapper for G4Polyhedron * G4Trd::CreatePolyhedron() (" __HERE__ ")");
  // signature to use in the veto list: G4Polyhedron * G4Trd::CreatePolyhedron()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:90:19
  t12.method("CreatePolyhedron", static_cast<G4Polyhedron * (G4Trd::*)()  const>(&G4Trd::CreatePolyhedron));


  DEBUG_MSG("Adding wrapper for void G4Trd::G4Trd(const G4Trd &) (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:99:5
  t12.constructor<const G4Trd &>();

  DEBUG_MSG("Adding wrapper for G4Trd & G4Trd::operator=(const G4Trd &) (" __HERE__ ")");
  // signature to use in the veto list: G4Trd & G4Trd::operator=(const G4Trd &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:100:13
  t12.method("assign", static_cast<G4Trd & (G4Trd::*)(const G4Trd &) >(&G4Trd::operator=));

  /* End of G4Trd class method wrappers
   **********************************************************************/


  /**********************************************************************/
  /* Wrappers for the methods of class G4LVData
   */


  DEBUG_MSG("Adding wrapper for void G4LVData::G4LVData() (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:134:5
  t13.constructor<>();

  DEBUG_MSG("Adding wrapper for void G4LVData::initialize() (" __HERE__ ")");
  // signature to use in the veto list: void G4LVData::initialize()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:135:10
  t13.method("initialize", static_cast<void (G4LVData::*)() >(&G4LVData::initialize));

  DEBUG_MSG("Adding fSolid methods  to provide read access to the field fSolid (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:147:15
  // signature to use in the veto list: G4LVData::fSolid
  t13.method("fSolid", [](const G4LVData& a) -> G4VSolid * { return a.fSolid; });
  t13.method("fSolid", [](G4LVData& a) -> G4VSolid * { return a.fSolid; });
  t13.method("fSolid", [](const G4LVData* a) -> G4VSolid * { return a->fSolid; });
  t13.method("fSolid", [](G4LVData* a) -> G4VSolid * { return a->fSolid; });
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:147:15
  // signature to use in the veto list: G4LVData::fSolid
  // with ! suffix to veto the setter only

  DEBUG_MSG("Adding fSolid! methods to provide write access to the field fSolid (" __HERE__ ")");
  t13.method("fSolid!", [](G4LVData& a, G4VSolid * val) -> G4VSolid * { return a.fSolid = val; });

  DEBUG_MSG("Adding fSolid! methods to provide write access to the field fSolid (" __HERE__ ")");
  t13.method("fSolid!", [](G4LVData* a, G4VSolid * val) -> G4VSolid * { return a->fSolid = val; });

  DEBUG_MSG("Adding fSensitiveDetector methods  to provide read access to the field fSensitiveDetector (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:149:27
  // signature to use in the veto list: G4LVData::fSensitiveDetector
  t13.method("fSensitiveDetector", [](const G4LVData& a) -> G4VSensitiveDetector * { return a.fSensitiveDetector; });
  t13.method("fSensitiveDetector", [](G4LVData& a) -> G4VSensitiveDetector * { return a.fSensitiveDetector; });
  t13.method("fSensitiveDetector", [](const G4LVData* a) -> G4VSensitiveDetector * { return a->fSensitiveDetector; });
  t13.method("fSensitiveDetector", [](G4LVData* a) -> G4VSensitiveDetector * { return a->fSensitiveDetector; });
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:149:27
  // signature to use in the veto list: G4LVData::fSensitiveDetector
  // with ! suffix to veto the setter only

  DEBUG_MSG("Adding fSensitiveDetector! methods to provide write access to the field fSensitiveDetector (" __HERE__ ")");
  t13.method("fSensitiveDetector!", [](G4LVData& a, G4VSensitiveDetector * val) -> G4VSensitiveDetector * { return a.fSensitiveDetector = val; });

  DEBUG_MSG("Adding fSensitiveDetector! methods to provide write access to the field fSensitiveDetector (" __HERE__ ")");
  t13.method("fSensitiveDetector!", [](G4LVData* a, G4VSensitiveDetector * val) -> G4VSensitiveDetector * { return a->fSensitiveDetector = val; });

  DEBUG_MSG("Adding fFieldManager methods  to provide read access to the field fFieldManager (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:151:21
  // signature to use in the veto list: G4LVData::fFieldManager
  t13.method("fFieldManager", [](const G4LVData& a) -> G4FieldManager * { return a.fFieldManager; });
  t13.method("fFieldManager", [](G4LVData& a) -> G4FieldManager * { return a.fFieldManager; });
  t13.method("fFieldManager", [](const G4LVData* a) -> G4FieldManager * { return a->fFieldManager; });
  t13.method("fFieldManager", [](G4LVData* a) -> G4FieldManager * { return a->fFieldManager; });
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:151:21
  // signature to use in the veto list: G4LVData::fFieldManager
  // with ! suffix to veto the setter only

  DEBUG_MSG("Adding fFieldManager! methods to provide write access to the field fFieldManager (" __HERE__ ")");
  t13.method("fFieldManager!", [](G4LVData& a, G4FieldManager * val) -> G4FieldManager * { return a.fFieldManager = val; });

  DEBUG_MSG("Adding fFieldManager! methods to provide write access to the field fFieldManager (" __HERE__ ")");
  t13.method("fFieldManager!", [](G4LVData* a, G4FieldManager * val) -> G4FieldManager * { return a->fFieldManager = val; });

  DEBUG_MSG("Adding fMaterial methods  to provide read access to the field fMaterial (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:153:17
  // signature to use in the veto list: G4LVData::fMaterial
  t13.method("fMaterial", [](const G4LVData& a) -> G4Material * { return a.fMaterial; });
  t13.method("fMaterial", [](G4LVData& a) -> G4Material * { return a.fMaterial; });
  t13.method("fMaterial", [](const G4LVData* a) -> G4Material * { return a->fMaterial; });
  t13.method("fMaterial", [](G4LVData* a) -> G4Material * { return a->fMaterial; });
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:153:17
  // signature to use in the veto list: G4LVData::fMaterial
  // with ! suffix to veto the setter only

  DEBUG_MSG("Adding fMaterial! methods to provide write access to the field fMaterial (" __HERE__ ")");
  t13.method("fMaterial!", [](G4LVData& a, G4Material * val) -> G4Material * { return a.fMaterial = val; });

  DEBUG_MSG("Adding fMaterial! methods to provide write access to the field fMaterial (" __HERE__ ")");
  t13.method("fMaterial!", [](G4LVData* a, G4Material * val) -> G4Material * { return a->fMaterial = val; });

  DEBUG_MSG("Adding fMass methods  to provide read access to the field fMass (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:155:14
  // signature to use in the veto list: G4LVData::fMass
  t13.method("fMass", [](const G4LVData& a) -> G4double { return a.fMass; });
  t13.method("fMass", [](G4LVData& a) -> G4double { return a.fMass; });
  t13.method("fMass", [](const G4LVData* a) -> G4double { return a->fMass; });
  t13.method("fMass", [](G4LVData* a) -> G4double { return a->fMass; });
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:155:14
  // signature to use in the veto list: G4LVData::fMass
  // with ! suffix to veto the setter only

  DEBUG_MSG("Adding fMass! methods to provide write access to the field fMass (" __HERE__ ")");
  t13.method("fMass!", [](G4LVData& a, G4double val) -> G4double { return a.fMass = val; });

  DEBUG_MSG("Adding fMass! methods to provide write access to the field fMass (" __HERE__ ")");
  t13.method("fMass!", [](G4LVData* a, G4double val) -> G4double { return a->fMass = val; });

  DEBUG_MSG("Adding fCutsCouple methods  to provide read access to the field fCutsCouple (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:157:27
  // signature to use in the veto list: G4LVData::fCutsCouple
  t13.method("fCutsCouple", [](const G4LVData& a) -> G4MaterialCutsCouple * { return a.fCutsCouple; });
  t13.method("fCutsCouple", [](G4LVData& a) -> G4MaterialCutsCouple * { return a.fCutsCouple; });
  t13.method("fCutsCouple", [](const G4LVData* a) -> G4MaterialCutsCouple * { return a->fCutsCouple; });
  t13.method("fCutsCouple", [](G4LVData* a) -> G4MaterialCutsCouple * { return a->fCutsCouple; });
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:157:27
  // signature to use in the veto list: G4LVData::fCutsCouple
  // with ! suffix to veto the setter only

  DEBUG_MSG("Adding fCutsCouple! methods to provide write access to the field fCutsCouple (" __HERE__ ")");
  t13.method("fCutsCouple!", [](G4LVData& a, G4MaterialCutsCouple * val) -> G4MaterialCutsCouple * { return a.fCutsCouple = val; });

  DEBUG_MSG("Adding fCutsCouple! methods to provide write access to the field fCutsCouple (" __HERE__ ")");
  t13.method("fCutsCouple!", [](G4LVData* a, G4MaterialCutsCouple * val) -> G4MaterialCutsCouple * { return a->fCutsCouple = val; });

  /* End of G4LVData class method wrappers
   **********************************************************************/


  /**********************************************************************/
  /* Wrappers for the methods of class G4LogicalVolume
   */

  DEBUG_MSG("Adding wrapper for const G4String & G4LogicalVolume::GetName() (" __HERE__ ")");
  // signature to use in the veto list: const G4String & G4LogicalVolume::GetName()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:208:28
  t15.method("GetName", static_cast<const G4String & (G4LogicalVolume::*)()  const>(&G4LogicalVolume::GetName));

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::SetName(const G4String &) (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::SetName(const G4String &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:209:10
  t15.method("SetName", static_cast<void (G4LogicalVolume::*)(const G4String &) >(&G4LogicalVolume::SetName));

  DEBUG_MSG("Adding wrapper for int G4LogicalVolume::GetNoDaughters() (" __HERE__ ")");
  // signature to use in the veto list: int G4LogicalVolume::GetNoDaughters()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:212:19
  t15.method("GetNoDaughters", static_cast<int (G4LogicalVolume::*)()  const>(&G4LogicalVolume::GetNoDaughters));

  DEBUG_MSG("Adding wrapper for G4VPhysicalVolume * G4LogicalVolume::GetDaughter(const G4int) (" __HERE__ ")");
  // signature to use in the veto list: G4VPhysicalVolume * G4LogicalVolume::GetDaughter(const G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:214:31
  t15.method("GetDaughter", static_cast<G4VPhysicalVolume * (G4LogicalVolume::*)(const G4int)  const>(&G4LogicalVolume::GetDaughter));

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::AddDaughter(G4VPhysicalVolume *) (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::AddDaughter(G4VPhysicalVolume *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:217:10
  t15.method("AddDaughter", static_cast<void (G4LogicalVolume::*)(G4VPhysicalVolume *) >(&G4LogicalVolume::AddDaughter));

  DEBUG_MSG("Adding wrapper for G4bool G4LogicalVolume::IsDaughter(const G4VPhysicalVolume *) (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4LogicalVolume::IsDaughter(const G4VPhysicalVolume *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:219:19
  t15.method("IsDaughter", static_cast<G4bool (G4LogicalVolume::*)(const G4VPhysicalVolume *)  const>(&G4LogicalVolume::IsDaughter));

  DEBUG_MSG("Adding wrapper for G4bool G4LogicalVolume::IsAncestor(const G4VPhysicalVolume *) (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4LogicalVolume::IsAncestor(const G4VPhysicalVolume *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:222:12
  t15.method("IsAncestor", static_cast<G4bool (G4LogicalVolume::*)(const G4VPhysicalVolume *)  const>(&G4LogicalVolume::IsAncestor));

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::RemoveDaughter(const G4VPhysicalVolume *) (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::RemoveDaughter(const G4VPhysicalVolume *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:226:10
  t15.method("RemoveDaughter", static_cast<void (G4LogicalVolume::*)(const G4VPhysicalVolume *) >(&G4LogicalVolume::RemoveDaughter));

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::ClearDaughters() (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::ClearDaughters()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:229:10
  t15.method("ClearDaughters", static_cast<void (G4LogicalVolume::*)() >(&G4LogicalVolume::ClearDaughters));

  DEBUG_MSG("Adding wrapper for G4int G4LogicalVolume::TotalVolumeEntities() (" __HERE__ ")");
  // signature to use in the veto list: G4int G4LogicalVolume::TotalVolumeEntities()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:232:11
  t15.method("TotalVolumeEntities", static_cast<G4int (G4LogicalVolume::*)()  const>(&G4LogicalVolume::TotalVolumeEntities));

  DEBUG_MSG("Adding wrapper for EVolume G4LogicalVolume::CharacteriseDaughters() (" __HERE__ ")");
  // signature to use in the veto list: EVolume G4LogicalVolume::CharacteriseDaughters()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:235:20
  t15.method("CharacteriseDaughters", static_cast<EVolume (G4LogicalVolume::*)()  const>(&G4LogicalVolume::CharacteriseDaughters));

  DEBUG_MSG("Adding wrapper for EVolume G4LogicalVolume::DeduceDaughtersType() (" __HERE__ ")");
  // signature to use in the veto list: EVolume G4LogicalVolume::DeduceDaughtersType()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:237:20
  t15.method("DeduceDaughtersType", static_cast<EVolume (G4LogicalVolume::*)()  const>(&G4LogicalVolume::DeduceDaughtersType));

  DEBUG_MSG("Adding wrapper for G4VSolid * G4LogicalVolume::GetSolid() (" __HERE__ ")");
  // signature to use in the veto list: G4VSolid * G4LogicalVolume::GetSolid()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:240:15
  t15.method("GetSolid", static_cast<G4VSolid * (G4LogicalVolume::*)()  const>(&G4LogicalVolume::GetSolid));

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::SetSolid(G4VSolid *) (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::SetSolid(G4VSolid *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:241:10
  t15.method("SetSolid", static_cast<void (G4LogicalVolume::*)(G4VSolid *) >(&G4LogicalVolume::SetSolid));

  DEBUG_MSG("Adding wrapper for G4Material * G4LogicalVolume::GetMaterial() (" __HERE__ ")");
  // signature to use in the veto list: G4Material * G4LogicalVolume::GetMaterial()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:244:17
  t15.method("GetMaterial", static_cast<G4Material * (G4LogicalVolume::*)()  const>(&G4LogicalVolume::GetMaterial));

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::SetMaterial(G4Material *) (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::SetMaterial(G4Material *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:245:10
  t15.method("SetMaterial", static_cast<void (G4LogicalVolume::*)(G4Material *) >(&G4LogicalVolume::SetMaterial));

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::UpdateMaterial(G4Material *) (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::UpdateMaterial(G4Material *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:247:10
  t15.method("UpdateMaterial", static_cast<void (G4LogicalVolume::*)(G4Material *) >(&G4LogicalVolume::UpdateMaterial));

  DEBUG_MSG("Adding wrapper for G4double G4LogicalVolume::GetMass(G4bool, G4bool, G4Material *) (" __HERE__ ")");
  // signature to use in the veto list: G4double G4LogicalVolume::GetMass(G4bool, G4bool, G4Material *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:251:14
  t15.method("GetMass", static_cast<G4double (G4LogicalVolume::*)(G4bool, G4bool, G4Material *) >(&G4LogicalVolume::GetMass));
  t15.method("GetMass", [](G4LogicalVolume& a)->G4double{ return a.GetMass(); });
  t15.method("GetMass", [](G4LogicalVolume& a, G4bool arg0)->G4double{ return a.GetMass(arg0); });
  t15.method("GetMass", [](G4LogicalVolume& a, G4bool arg0, G4bool arg1)->G4double{ return a.GetMass(arg0, arg1); });
  t15.method("GetMass", [](G4LogicalVolume* a)->G4double{ return a->GetMass(); });
  t15.method("GetMass", [](G4LogicalVolume* a, G4bool arg0)->G4double{ return a->GetMass(arg0); });
  t15.method("GetMass", [](G4LogicalVolume* a, G4bool arg0, G4bool arg1)->G4double{ return a->GetMass(arg0, arg1); });

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::ResetMass() (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::ResetMass()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:266:10
  t15.method("ResetMass", static_cast<void (G4LogicalVolume::*)() >(&G4LogicalVolume::ResetMass));

  DEBUG_MSG("Adding wrapper for G4SmartVoxelHeader * G4LogicalVolume::GetVoxelHeader() (" __HERE__ ")");
  // signature to use in the veto list: G4SmartVoxelHeader * G4LogicalVolume::GetVoxelHeader()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:289:32
  t15.method("GetVoxelHeader", static_cast<G4SmartVoxelHeader * (G4LogicalVolume::*)()  const>(&G4LogicalVolume::GetVoxelHeader));

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::SetVoxelHeader(G4SmartVoxelHeader *) (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::SetVoxelHeader(G4SmartVoxelHeader *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:290:17
  t15.method("SetVoxelHeader", static_cast<void (G4LogicalVolume::*)(G4SmartVoxelHeader *) >(&G4LogicalVolume::SetVoxelHeader));

  DEBUG_MSG("Adding wrapper for G4double G4LogicalVolume::GetSmartless() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4LogicalVolume::GetSmartless()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:293:21
  t15.method("GetSmartless", static_cast<G4double (G4LogicalVolume::*)()  const>(&G4LogicalVolume::GetSmartless));

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::SetSmartless(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::SetSmartless(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:294:17
  t15.method("SetSmartless", static_cast<void (G4LogicalVolume::*)(G4double) >(&G4LogicalVolume::SetSmartless));

  DEBUG_MSG("Adding wrapper for G4bool G4LogicalVolume::IsToOptimise() (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4LogicalVolume::IsToOptimise()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:297:19
  t15.method("IsToOptimise", static_cast<G4bool (G4LogicalVolume::*)()  const>(&G4LogicalVolume::IsToOptimise));

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::SetOptimisation(G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::SetOptimisation(G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:300:17
  t15.method("SetOptimisation", static_cast<void (G4LogicalVolume::*)(G4bool) >(&G4LogicalVolume::SetOptimisation));

  DEBUG_MSG("Adding wrapper for G4bool G4LogicalVolume::IsRootRegion() (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4LogicalVolume::IsRootRegion()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:305:19
  t15.method("IsRootRegion", static_cast<G4bool (G4LogicalVolume::*)()  const>(&G4LogicalVolume::IsRootRegion));

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::SetRegionRootFlag(G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::SetRegionRootFlag(G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:307:17
  t15.method("SetRegionRootFlag", static_cast<void (G4LogicalVolume::*)(G4bool) >(&G4LogicalVolume::SetRegionRootFlag));

  DEBUG_MSG("Adding wrapper for G4bool G4LogicalVolume::IsRegion() (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4LogicalVolume::IsRegion()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:309:19
  t15.method("IsRegion", static_cast<G4bool (G4LogicalVolume::*)()  const>(&G4LogicalVolume::IsRegion));

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::SetRegion(G4Region *) (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::SetRegion(G4Region *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:311:17
  t15.method("SetRegion", static_cast<void (G4LogicalVolume::*)(G4Region *) >(&G4LogicalVolume::SetRegion));

  DEBUG_MSG("Adding wrapper for G4Region * G4LogicalVolume::GetRegion() (" __HERE__ ")");
  // signature to use in the veto list: G4Region * G4LogicalVolume::GetRegion()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:313:22
  t15.method("GetRegion", static_cast<G4Region * (G4LogicalVolume::*)()  const>(&G4LogicalVolume::GetRegion));

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::PropagateRegion() (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::PropagateRegion()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:315:17
  t15.method("PropagateRegion", static_cast<void (G4LogicalVolume::*)() >(&G4LogicalVolume::PropagateRegion));
  types.set_override_module(jl_base_module);

  DEBUG_MSG("Adding wrapper for G4bool G4LogicalVolume::operator==(const G4LogicalVolume &) (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4LogicalVolume::operator==(const G4LogicalVolume &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:322:12
  t15.method("==", static_cast<G4bool (G4LogicalVolume::*)(const G4LogicalVolume &)  const>(&G4LogicalVolume::operator==));

  types.unset_override_module();

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::SetBiasWeight(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::SetBiasWeight(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:335:17
  t15.method("SetBiasWeight", static_cast<void (G4LogicalVolume::*)(G4double) >(&G4LogicalVolume::SetBiasWeight));

  DEBUG_MSG("Adding wrapper for G4double G4LogicalVolume::GetBiasWeight() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4LogicalVolume::GetBiasWeight()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:336:21
  t15.method("GetBiasWeight", static_cast<G4double (G4LogicalVolume::*)()  const>(&G4LogicalVolume::GetBiasWeight));

  DEBUG_MSG("Adding wrapper for G4bool G4LogicalVolume::IsExtended() (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4LogicalVolume::IsExtended()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:346:20
  t15.method("IsExtended", static_cast<G4bool (G4LogicalVolume::*)()  const>(&G4LogicalVolume::IsExtended));

  DEBUG_MSG("Adding wrapper for G4VSolid * G4LogicalVolume::GetMasterSolid() (" __HERE__ ")");
  // signature to use in the veto list: G4VSolid * G4LogicalVolume::GetMasterSolid()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:353:22
  t15.method("GetMasterSolid", static_cast<G4VSolid * (G4LogicalVolume::*)()  const>(&G4LogicalVolume::GetMasterSolid));

  DEBUG_MSG("Adding wrapper for G4int G4LogicalVolume::GetInstanceID() (" __HERE__ ")");
  // signature to use in the veto list: G4int G4LogicalVolume::GetInstanceID()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:356:18
  t15.method("GetInstanceID", static_cast<G4int (G4LogicalVolume::*)()  const>(&G4LogicalVolume::GetInstanceID));

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::Clean() (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::Clean()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:362:17
  t15.method("G4LogicalVolume!Clean", static_cast<void (*)() >(&G4LogicalVolume::Clean));

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::Lock() (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::Lock()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:365:17
  t15.method("Lock", static_cast<void (G4LogicalVolume::*)() >(&G4LogicalVolume::Lock));

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::TerminateWorker(G4LogicalVolume *) (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::TerminateWorker(G4LogicalVolume *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:373:10
  t15.method("TerminateWorker", static_cast<void (G4LogicalVolume::*)(G4LogicalVolume *) >(&G4LogicalVolume::TerminateWorker));

  DEBUG_MSG("Adding wrapper for G4VSolid * G4LogicalVolume::GetSolid(G4LVData &) (" __HERE__ ")");
  // signature to use in the veto list: G4VSolid * G4LogicalVolume::GetSolid(G4LVData &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:380:22
  t15.method("G4LogicalVolume!GetSolid", static_cast<G4VSolid * (*)(G4LVData &) >(&G4LogicalVolume::GetSolid));

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::SetSolid(G4LVData &, G4VSolid *) (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::SetSolid(G4LVData &, G4VSolid *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:381:17
  t15.method("G4LogicalVolume!SetSolid", static_cast<void (*)(G4LVData &, G4VSolid *) >(&G4LogicalVolume::SetSolid));

  DEBUG_MSG("Adding wrapper for G4bool G4LogicalVolume::ChangeDaughtersType(EVolume) (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4LogicalVolume::ChangeDaughtersType(EVolume)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:384:12
  t15.method("ChangeDaughtersType", static_cast<G4bool (G4LogicalVolume::*)(EVolume) >(&G4LogicalVolume::ChangeDaughtersType));

  /* End of G4LogicalVolume class method wrappers
   **********************************************************************/


  /**********************************************************************/
  /* Wrappers for the methods of class G4NavigationLevelRep
   */


  DEBUG_MSG("Adding wrapper for void G4NavigationLevelRep::G4NavigationLevelRep(G4NavigationLevelRep &) (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NavigationLevelRep.icc:69:23
  t19.constructor<G4NavigationLevelRep &>();

  /* End of G4NavigationLevelRep class method wrappers
   **********************************************************************/


  /**********************************************************************/
  /* Wrappers for the methods of class G4RunManager
   */

  DEBUG_MSG("Adding wrapper for void G4RunManager::BeamOn(G4int, const char *, G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::BeamOn(G4int, const char *, G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:163:18
  t20.method("BeamOn", static_cast<void (G4RunManager::*)(G4int, const char *, G4int) >(&G4RunManager::BeamOn));
  t20.method("BeamOn", [](G4RunManager& a, G4int arg0)->void{ a.BeamOn(arg0); });
  t20.method("BeamOn", [](G4RunManager& a, G4int arg0, const char * arg1)->void{ a.BeamOn(arg0, arg1); });
  t20.method("BeamOn", [](G4RunManager* a, G4int arg0)->void{ a->BeamOn(arg0); });
  t20.method("BeamOn", [](G4RunManager* a, G4int arg0, const char * arg1)->void{ a->BeamOn(arg0, arg1); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::Initialize() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::Initialize()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:175:18
  t20.method("Initialize", static_cast<void (G4RunManager::*)() >(&G4RunManager::Initialize));

  DEBUG_MSG("Adding wrapper for void G4RunManager::DefineWorldVolume(G4VPhysicalVolume *, G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::DefineWorldVolume(G4VPhysicalVolume *, G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:188:18
  t20.method("DefineWorldVolume", static_cast<void (G4RunManager::*)(G4VPhysicalVolume *, G4bool) >(&G4RunManager::DefineWorldVolume));
  t20.method("DefineWorldVolume", [](G4RunManager& a, G4VPhysicalVolume * arg0)->void{ a.DefineWorldVolume(arg0); });
  t20.method("DefineWorldVolume", [](G4RunManager* a, G4VPhysicalVolume * arg0)->void{ a->DefineWorldVolume(arg0); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::AbortRun(G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::AbortRun(G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:197:18
  t20.method("AbortRun", static_cast<void (G4RunManager::*)(G4bool) >(&G4RunManager::AbortRun));
  t20.method("AbortRun", [](G4RunManager& a)->void{ a.AbortRun(); });
  t20.method("AbortRun", [](G4RunManager* a)->void{ a->AbortRun(); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::AbortEvent() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::AbortEvent()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:206:18
  t20.method("AbortEvent", static_cast<void (G4RunManager::*)() >(&G4RunManager::AbortEvent));

  DEBUG_MSG("Adding wrapper for void G4RunManager::InitializeGeometry() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::InitializeGeometry()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:211:18
  t20.method("InitializeGeometry", static_cast<void (G4RunManager::*)() >(&G4RunManager::InitializeGeometry));

  DEBUG_MSG("Adding wrapper for void G4RunManager::InitializePhysics() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::InitializePhysics()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:212:18
  t20.method("InitializePhysics", static_cast<void (G4RunManager::*)() >(&G4RunManager::InitializePhysics));

  DEBUG_MSG("Adding wrapper for G4bool G4RunManager::ConfirmBeamOnCondition() (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4RunManager::ConfirmBeamOnCondition()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:219:20
  t20.method("ConfirmBeamOnCondition", static_cast<G4bool (G4RunManager::*)() >(&G4RunManager::ConfirmBeamOnCondition));

  DEBUG_MSG("Adding wrapper for void G4RunManager::RunInitialization() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::RunInitialization()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:220:18
  t20.method("RunInitialization", static_cast<void (G4RunManager::*)() >(&G4RunManager::RunInitialization));

  DEBUG_MSG("Adding wrapper for void G4RunManager::DoEventLoop(G4int, const char *, G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::DoEventLoop(G4int, const char *, G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:221:18
  t20.method("DoEventLoop", static_cast<void (G4RunManager::*)(G4int, const char *, G4int) >(&G4RunManager::DoEventLoop));
  t20.method("DoEventLoop", [](G4RunManager& a, G4int arg0)->void{ a.DoEventLoop(arg0); });
  t20.method("DoEventLoop", [](G4RunManager& a, G4int arg0, const char * arg1)->void{ a.DoEventLoop(arg0, arg1); });
  t20.method("DoEventLoop", [](G4RunManager* a, G4int arg0)->void{ a->DoEventLoop(arg0); });
  t20.method("DoEventLoop", [](G4RunManager* a, G4int arg0, const char * arg1)->void{ a->DoEventLoop(arg0, arg1); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::RunTermination() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::RunTermination()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:223:18
  t20.method("RunTermination", static_cast<void (G4RunManager::*)() >(&G4RunManager::RunTermination));

  DEBUG_MSG("Adding wrapper for void G4RunManager::InitializeEventLoop(G4int, const char *, G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::InitializeEventLoop(G4int, const char *, G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:240:18
  t20.method("InitializeEventLoop", static_cast<void (G4RunManager::*)(G4int, const char *, G4int) >(&G4RunManager::InitializeEventLoop));
  t20.method("InitializeEventLoop", [](G4RunManager& a, G4int arg0)->void{ a.InitializeEventLoop(arg0); });
  t20.method("InitializeEventLoop", [](G4RunManager& a, G4int arg0, const char * arg1)->void{ a.InitializeEventLoop(arg0, arg1); });
  t20.method("InitializeEventLoop", [](G4RunManager* a, G4int arg0)->void{ a->InitializeEventLoop(arg0); });
  t20.method("InitializeEventLoop", [](G4RunManager* a, G4int arg0, const char * arg1)->void{ a->InitializeEventLoop(arg0, arg1); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::ProcessOneEvent(G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::ProcessOneEvent(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:243:18
  t20.method("ProcessOneEvent", static_cast<void (G4RunManager::*)(G4int) >(&G4RunManager::ProcessOneEvent));

  DEBUG_MSG("Adding wrapper for void G4RunManager::TerminateOneEvent() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::TerminateOneEvent()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:244:18
  t20.method("TerminateOneEvent", static_cast<void (G4RunManager::*)() >(&G4RunManager::TerminateOneEvent));

  DEBUG_MSG("Adding wrapper for void G4RunManager::TerminateEventLoop() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::TerminateEventLoop()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:245:18
  t20.method("TerminateEventLoop", static_cast<void (G4RunManager::*)() >(&G4RunManager::TerminateEventLoop));

  DEBUG_MSG("Adding wrapper for G4Event * G4RunManager::GenerateEvent(G4int) (" __HERE__ ")");
  // signature to use in the veto list: G4Event * G4RunManager::GenerateEvent(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:248:22
  t20.method("GenerateEvent", static_cast<G4Event * (G4RunManager::*)(G4int) >(&G4RunManager::GenerateEvent));

  DEBUG_MSG("Adding wrapper for void G4RunManager::AnalyzeEvent(G4Event *) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::AnalyzeEvent(G4Event *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:249:18
  t20.method("AnalyzeEvent", static_cast<void (G4RunManager::*)(G4Event *) >(&G4RunManager::AnalyzeEvent));

  DEBUG_MSG("Adding wrapper for void G4RunManager::ConfigureProfilers(const int &) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::ConfigureProfilers(const int &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:259:18
  t20.method("ConfigureProfilers", static_cast<void (G4RunManager::*)(const int &) >(&G4RunManager::ConfigureProfilers));
  t20.method("ConfigureProfilers", [](G4RunManager& a)->void{ a.ConfigureProfilers(); });
  t20.method("ConfigureProfilers", [](G4RunManager* a)->void{ a->ConfigureProfilers(); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::ConfigureProfilers(G4int, char **) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::ConfigureProfilers(G4int, char **)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:261:10
  t20.method("ConfigureProfilers", static_cast<void (G4RunManager::*)(G4int, char **) >(&G4RunManager::ConfigureProfilers));

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetNumberOfThreads(G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetNumberOfThreads(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:264:18
  t20.method("SetNumberOfThreads", static_cast<void (G4RunManager::*)(G4int) >(&G4RunManager::SetNumberOfThreads));

  DEBUG_MSG("Adding wrapper for G4int G4RunManager::GetNumberOfThreads() (" __HERE__ ")");
  // signature to use in the veto list: G4int G4RunManager::GetNumberOfThreads()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:265:19
  t20.method("GetNumberOfThreads", static_cast<G4int (G4RunManager::*)()  const>(&G4RunManager::GetNumberOfThreads));

  DEBUG_MSG("Adding wrapper for void G4RunManager::DumpRegion(const G4String &) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::DumpRegion(const G4String &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:269:10
  t20.method("DumpRegion", static_cast<void (G4RunManager::*)(const G4String &)  const>(&G4RunManager::DumpRegion));

  DEBUG_MSG("Adding wrapper for void G4RunManager::DumpRegion(G4Region *) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::DumpRegion(G4Region *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:271:10
  t20.method("DumpRegion", static_cast<void (G4RunManager::*)(G4Region *)  const>(&G4RunManager::DumpRegion));
  t20.method("DumpRegion", [](G4RunManager const& a)->void{ a.DumpRegion(); });
  t20.method("DumpRegion", [](G4RunManager const* a)->void{ a->DumpRegion(); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::GeometryHasBeenModified(G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::GeometryHasBeenModified(G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:275:10
  t20.method("GeometryHasBeenModified", static_cast<void (G4RunManager::*)(G4bool) >(&G4RunManager::GeometryHasBeenModified));
  t20.method("GeometryHasBeenModified", [](G4RunManager& a)->void{ a.GeometryHasBeenModified(); });
  t20.method("GeometryHasBeenModified", [](G4RunManager* a)->void{ a->GeometryHasBeenModified(); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::ReinitializeGeometry(G4bool, G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::ReinitializeGeometry(G4bool, G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:283:10
  t20.method("ReinitializeGeometry", static_cast<void (G4RunManager::*)(G4bool, G4bool) >(&G4RunManager::ReinitializeGeometry));
  t20.method("ReinitializeGeometry", [](G4RunManager& a)->void{ a.ReinitializeGeometry(); });
  t20.method("ReinitializeGeometry", [](G4RunManager& a, G4bool arg0)->void{ a.ReinitializeGeometry(arg0); });
  t20.method("ReinitializeGeometry", [](G4RunManager* a)->void{ a->ReinitializeGeometry(); });
  t20.method("ReinitializeGeometry", [](G4RunManager* a, G4bool arg0)->void{ a->ReinitializeGeometry(arg0); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::PhysicsHasBeenModified() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::PhysicsHasBeenModified()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:294:17
  t20.method("PhysicsHasBeenModified", static_cast<void (G4RunManager::*)() >(&G4RunManager::PhysicsHasBeenModified));

  DEBUG_MSG("Adding wrapper for void G4RunManager::CutOffHasBeenModified() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::CutOffHasBeenModified()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:301:17
  t20.method("CutOffHasBeenModified", static_cast<void (G4RunManager::*)() >(&G4RunManager::CutOffHasBeenModified));

  DEBUG_MSG("Adding wrapper for void G4RunManager::ReOptimizeMotherOf(G4VPhysicalVolume *) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::ReOptimizeMotherOf(G4VPhysicalVolume *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:307:10
  t20.method("ReOptimizeMotherOf", static_cast<void (G4RunManager::*)(G4VPhysicalVolume *) >(&G4RunManager::ReOptimizeMotherOf));

  DEBUG_MSG("Adding wrapper for void G4RunManager::ReOptimize(G4LogicalVolume *) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::ReOptimize(G4LogicalVolume *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:314:10
  t20.method("ReOptimize", static_cast<void (G4RunManager::*)(G4LogicalVolume *) >(&G4RunManager::ReOptimize));

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetGeometryToBeOptimized(G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetGeometryToBeOptimized(G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:317:17
  t20.method("SetGeometryToBeOptimized", static_cast<void (G4RunManager::*)(G4bool) >(&G4RunManager::SetGeometryToBeOptimized));

  DEBUG_MSG("Adding wrapper for G4bool G4RunManager::GetGeometryToBeOptimized() (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4RunManager::GetGeometryToBeOptimized()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:326:19
  t20.method("GetGeometryToBeOptimized", static_cast<G4bool (G4RunManager::*)() >(&G4RunManager::GetGeometryToBeOptimized));

  DEBUG_MSG("Adding wrapper for void G4RunManager::GeometryDirectlyUpdated(G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::GeometryDirectlyUpdated(G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:331:10
  t20.method("GeometryDirectlyUpdated", static_cast<void (G4RunManager::*)(G4bool) >(&G4RunManager::GeometryDirectlyUpdated));
  t20.method("GeometryDirectlyUpdated", [](G4RunManager& a)->void{ a.GeometryDirectlyUpdated(); });
  t20.method("GeometryDirectlyUpdated", [](G4RunManager* a)->void{ a->GeometryDirectlyUpdated(); });

  DEBUG_MSG("Adding wrapper for G4bool G4RunManager::IfGeometryHasBeenDestroyed() (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4RunManager::IfGeometryHasBeenDestroyed()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:336:19
  t20.method("G4RunManager!IfGeometryHasBeenDestroyed", static_cast<G4bool (*)() >(&G4RunManager::IfGeometryHasBeenDestroyed));

  DEBUG_MSG("Adding wrapper for void G4RunManager::ConstructScoringWorlds() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::ConstructScoringWorlds()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:341:18
  t20.method("ConstructScoringWorlds", static_cast<void (G4RunManager::*)() >(&G4RunManager::ConstructScoringWorlds));

  DEBUG_MSG("Adding wrapper for void G4RunManager::rndmSaveThisRun() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::rndmSaveThisRun()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:343:18
  t20.method("rndmSaveThisRun", static_cast<void (G4RunManager::*)() >(&G4RunManager::rndmSaveThisRun));

  DEBUG_MSG("Adding wrapper for void G4RunManager::rndmSaveThisEvent() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::rndmSaveThisEvent()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:344:18
  t20.method("rndmSaveThisEvent", static_cast<void (G4RunManager::*)() >(&G4RunManager::rndmSaveThisEvent));

  DEBUG_MSG("Adding wrapper for void G4RunManager::RestoreRandomNumberStatus(const G4String &) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::RestoreRandomNumberStatus(const G4String &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:345:18
  t20.method("RestoreRandomNumberStatus", static_cast<void (G4RunManager::*)(const G4String &) >(&G4RunManager::RestoreRandomNumberStatus));

  DEBUG_MSG("Adding wrapper for void G4RunManager::RestoreRndmEachEvent(G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::RestoreRndmEachEvent(G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:346:18
  t20.method("RestoreRndmEachEvent", static_cast<void (G4RunManager::*)(G4bool) >(&G4RunManager::RestoreRndmEachEvent));

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetUserAction(G4UserStackingAction *) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetUserAction(G4UserStackingAction *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:356:18
  t20.method("SetUserAction", static_cast<void (G4RunManager::*)(G4UserStackingAction *) >(&G4RunManager::SetUserAction));

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetUserAction(G4UserTrackingAction *) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetUserAction(G4UserTrackingAction *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:357:18
  t20.method("SetUserAction", static_cast<void (G4RunManager::*)(G4UserTrackingAction *) >(&G4RunManager::SetUserAction));

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetUserAction(G4UserSteppingAction *) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetUserAction(G4UserSteppingAction *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:358:18
  t20.method("SetUserAction", static_cast<void (G4RunManager::*)(G4UserSteppingAction *) >(&G4RunManager::SetUserAction));

  DEBUG_MSG("Adding wrapper for const G4UserStackingAction * G4RunManager::GetUserStackingAction() (" __HERE__ ")");
  // signature to use in the veto list: const G4UserStackingAction * G4RunManager::GetUserStackingAction()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:408:40
  t20.method("GetUserStackingAction", static_cast<const G4UserStackingAction * (G4RunManager::*)()  const>(&G4RunManager::GetUserStackingAction));

  DEBUG_MSG("Adding wrapper for const G4UserTrackingAction * G4RunManager::GetUserTrackingAction() (" __HERE__ ")");
  // signature to use in the veto list: const G4UserTrackingAction * G4RunManager::GetUserTrackingAction()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:412:40
  t20.method("GetUserTrackingAction", static_cast<const G4UserTrackingAction * (G4RunManager::*)()  const>(&G4RunManager::GetUserTrackingAction));

  DEBUG_MSG("Adding wrapper for const G4UserSteppingAction * G4RunManager::GetUserSteppingAction() (" __HERE__ ")");
  // signature to use in the veto list: const G4UserSteppingAction * G4RunManager::GetUserSteppingAction()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:416:40
  t20.method("GetUserSteppingAction", static_cast<const G4UserSteppingAction * (G4RunManager::*)()  const>(&G4RunManager::GetUserSteppingAction));

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetNumberOfAdditionalWaitingStacks(G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetNumberOfAdditionalWaitingStacks(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:422:17
  t20.method("SetNumberOfAdditionalWaitingStacks", static_cast<void (G4RunManager::*)(G4int) >(&G4RunManager::SetNumberOfAdditionalWaitingStacks));

  DEBUG_MSG("Adding wrapper for const G4String & G4RunManager::GetVersionString() (" __HERE__ ")");
  // signature to use in the veto list: const G4String & G4RunManager::GetVersionString()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:431:28
  t20.method("GetVersionString", static_cast<const G4String & (G4RunManager::*)()  const>(&G4RunManager::GetVersionString));

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetPrimaryTransformer(G4PrimaryTransformer *) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetPrimaryTransformer(G4PrimaryTransformer *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:436:17
  t20.method("SetPrimaryTransformer", static_cast<void (G4RunManager::*)(G4PrimaryTransformer *) >(&G4RunManager::SetPrimaryTransformer));

  DEBUG_MSG("Adding wrapper for void G4RunManager::StoreRandomNumberStatusToG4Event(G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::StoreRandomNumberStatusToG4Event(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:441:17
  t20.method("StoreRandomNumberStatusToG4Event", static_cast<void (G4RunManager::*)(G4int) >(&G4RunManager::StoreRandomNumberStatusToG4Event));

  DEBUG_MSG("Adding wrapper for G4int G4RunManager::GetFlagRandomNumberStatusToG4Event() (" __HERE__ ")");
  // signature to use in the veto list: G4int G4RunManager::GetFlagRandomNumberStatusToG4Event()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:451:18
  t20.method("GetFlagRandomNumberStatusToG4Event", static_cast<G4int (G4RunManager::*)()  const>(&G4RunManager::GetFlagRandomNumberStatusToG4Event));

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetRandomNumberStore(G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetRandomNumberStore(G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:456:17
  t20.method("SetRandomNumberStore", static_cast<void (G4RunManager::*)(G4bool) >(&G4RunManager::SetRandomNumberStore));

  DEBUG_MSG("Adding wrapper for G4bool G4RunManager::GetRandomNumberStore() (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4RunManager::GetRandomNumberStore()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:460:19
  t20.method("GetRandomNumberStore", static_cast<G4bool (G4RunManager::*)()  const>(&G4RunManager::GetRandomNumberStore));

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetRandomNumberStoreDir(const G4String &) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetRandomNumberStoreDir(const G4String &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:464:17
  t20.method("SetRandomNumberStoreDir", static_cast<void (G4RunManager::*)(const G4String &) >(&G4RunManager::SetRandomNumberStoreDir));

  DEBUG_MSG("Adding wrapper for const G4String & G4RunManager::GetRandomNumberStoreDir() (" __HERE__ ")");
  // signature to use in the veto list: const G4String & G4RunManager::GetRandomNumberStoreDir()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:487:28
  t20.method("GetRandomNumberStoreDir", static_cast<const G4String & (G4RunManager::*)()  const>(&G4RunManager::GetRandomNumberStoreDir));

  DEBUG_MSG("Adding wrapper for const G4String & G4RunManager::GetRandomNumberStatusForThisRun() (" __HERE__ ")");
  // signature to use in the veto list: const G4String & G4RunManager::GetRandomNumberStatusForThisRun()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:491:28
  t20.method("GetRandomNumberStatusForThisRun", static_cast<const G4String & (G4RunManager::*)()  const>(&G4RunManager::GetRandomNumberStatusForThisRun));

  DEBUG_MSG("Adding wrapper for const G4String & G4RunManager::GetRandomNumberStatusForThisEvent() (" __HERE__ ")");
  // signature to use in the veto list: const G4String & G4RunManager::GetRandomNumberStatusForThisEvent()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:495:28
  t20.method("GetRandomNumberStatusForThisEvent", static_cast<const G4String & (G4RunManager::*)()  const>(&G4RunManager::GetRandomNumberStatusForThisEvent));

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetRandomNumberStorePerEvent(G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetRandomNumberStorePerEvent(G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:506:17
  t20.method("SetRandomNumberStorePerEvent", static_cast<void (G4RunManager::*)(G4bool) >(&G4RunManager::SetRandomNumberStorePerEvent));

  DEBUG_MSG("Adding wrapper for G4bool G4RunManager::GetRandomNumberStorePerEvent() (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4RunManager::GetRandomNumberStorePerEvent()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:510:19
  t20.method("GetRandomNumberStorePerEvent", static_cast<G4bool (G4RunManager::*)()  const>(&G4RunManager::GetRandomNumberStorePerEvent));

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetVerboseLevel(G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetVerboseLevel(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:515:17
  t20.method("SetVerboseLevel", static_cast<void (G4RunManager::*)(G4int) >(&G4RunManager::SetVerboseLevel));

  DEBUG_MSG("Adding wrapper for G4int G4RunManager::GetVerboseLevel() (" __HERE__ ")");
  // signature to use in the veto list: G4int G4RunManager::GetVerboseLevel()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:520:18
  t20.method("GetVerboseLevel", static_cast<G4int (G4RunManager::*)()  const>(&G4RunManager::GetVerboseLevel));

  DEBUG_MSG("Adding wrapper for G4int G4RunManager::GetPrintProgress() (" __HERE__ ")");
  // signature to use in the veto list: G4int G4RunManager::GetPrintProgress()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:521:18
  t20.method("GetPrintProgress", static_cast<G4int (G4RunManager::*)() >(&G4RunManager::GetPrintProgress));

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetPrintProgress(G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetPrintProgress(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:522:17
  t20.method("SetPrintProgress", static_cast<void (G4RunManager::*)(G4int) >(&G4RunManager::SetPrintProgress));

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetNumberOfEventsToBeStored(G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetNumberOfEventsToBeStored(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:524:17
  t20.method("SetNumberOfEventsToBeStored", static_cast<void (G4RunManager::*)(G4int) >(&G4RunManager::SetNumberOfEventsToBeStored));

  DEBUG_MSG("Adding wrapper for const G4Event * G4RunManager::GetCurrentEvent() (" __HERE__ ")");
  // signature to use in the veto list: const G4Event * G4RunManager::GetCurrentEvent()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:537:27
  t20.method("GetCurrentEvent", static_cast<const G4Event * (G4RunManager::*)()  const>(&G4RunManager::GetCurrentEvent));

  DEBUG_MSG("Adding wrapper for const G4Event * G4RunManager::GetPreviousEvent(G4int) (" __HERE__ ")");
  // signature to use in the veto list: const G4Event * G4RunManager::GetPreviousEvent(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:540:27
  t20.method("GetPreviousEvent", static_cast<const G4Event * (G4RunManager::*)(G4int)  const>(&G4RunManager::GetPreviousEvent));

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetRunIDCounter(G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetRunIDCounter(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:558:17
  t20.method("SetRunIDCounter", static_cast<void (G4RunManager::*)(G4int) >(&G4RunManager::SetRunIDCounter));

  DEBUG_MSG("Adding wrapper for G4int G4RunManager::GetNumberOfParallelWorld() (" __HERE__ ")");
  // signature to use in the veto list: G4int G4RunManager::GetNumberOfParallelWorld()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:562:18
  t20.method("GetNumberOfParallelWorld", static_cast<G4int (G4RunManager::*)()  const>(&G4RunManager::GetNumberOfParallelWorld));

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetNumberOfEventsToBeProcessed(G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetNumberOfEventsToBeProcessed(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:563:17
  t20.method("SetNumberOfEventsToBeProcessed", static_cast<void (G4RunManager::*)(G4int) >(&G4RunManager::SetNumberOfEventsToBeProcessed));

  DEBUG_MSG("Adding wrapper for G4int G4RunManager::GetNumberOfEventsToBeProcessed() (" __HERE__ ")");
  // signature to use in the veto list: G4int G4RunManager::GetNumberOfEventsToBeProcessed()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:567:18
  t20.method("GetNumberOfEventsToBeProcessed", static_cast<G4int (G4RunManager::*)()  const>(&G4RunManager::GetNumberOfEventsToBeProcessed));

  DEBUG_MSG("Adding wrapper for G4int G4RunManager::GetNumberOfSelectEvents() (" __HERE__ ")");
  // signature to use in the veto list: G4int G4RunManager::GetNumberOfSelectEvents()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:571:18
  t20.method("GetNumberOfSelectEvents", static_cast<G4int (G4RunManager::*)()  const>(&G4RunManager::GetNumberOfSelectEvents));

  DEBUG_MSG("Adding wrapper for const G4String & G4RunManager::GetSelectMacro() (" __HERE__ ")");
  // signature to use in the veto list: const G4String & G4RunManager::GetSelectMacro()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:572:28
  t20.method("GetSelectMacro", static_cast<const G4String & (G4RunManager::*)()  const>(&G4RunManager::GetSelectMacro));

  DEBUG_MSG("Adding wrapper for G4RunManager::RMType G4RunManager::GetRunManagerType() (" __HERE__ ")");
  // signature to use in the veto list: G4RunManager::RMType G4RunManager::GetRunManagerType()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:582:19
  t20.method("GetRunManagerType", static_cast<G4RunManager::RMType (G4RunManager::*)()  const>(&G4RunManager::GetRunManagerType));

  /* End of G4RunManager class method wrappers
   **********************************************************************/


  /**********************************************************************/
  /* Wrappers for the methods of class G4NistManager
   */

  DEBUG_MSG("Adding wrapper for G4NistManager * G4NistManager::Instance() (" __HERE__ ")");
  // signature to use in the veto list: G4NistManager * G4NistManager::Instance()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:88:25
  t27.method("G4NistManager!Instance", static_cast<G4NistManager * (*)() >(&G4NistManager::Instance));

  DEBUG_MSG("Adding wrapper for G4Element * G4NistManager::GetElement(int) (" __HERE__ ")");
  // signature to use in the veto list: G4Element * G4NistManager::GetElement(int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:93:21
  t27.method("GetElement", static_cast<G4Element * (G4NistManager::*)(int)  const>(&G4NistManager::GetElement));

  DEBUG_MSG("Adding wrapper for G4Element * G4NistManager::FindElement(G4int) (" __HERE__ ")");
  // signature to use in the veto list: G4Element * G4NistManager::FindElement(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:97:21
  t27.method("FindElement", static_cast<G4Element * (G4NistManager::*)(G4int)  const>(&G4NistManager::FindElement));

  DEBUG_MSG("Adding wrapper for G4Element * G4NistManager::FindOrBuildElement(G4int, G4bool) (" __HERE__ ")");
  // signature to use in the veto list: G4Element * G4NistManager::FindOrBuildElement(G4int, G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:98:21
  t27.method("FindOrBuildElement", static_cast<G4Element * (G4NistManager::*)(G4int, G4bool) >(&G4NistManager::FindOrBuildElement));
  t27.method("FindOrBuildElement", [](G4NistManager& a, G4int arg0)->G4Element *{ return a.FindOrBuildElement(arg0); });
  t27.method("FindOrBuildElement", [](G4NistManager* a, G4int arg0)->G4Element *{ return a->FindOrBuildElement(arg0); });

  DEBUG_MSG("Adding wrapper for G4Element * G4NistManager::FindOrBuildElement(const G4String &, G4bool) (" __HERE__ ")");
  // signature to use in the veto list: G4Element * G4NistManager::FindOrBuildElement(const G4String &, G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:102:21
  t27.method("FindOrBuildElement", static_cast<G4Element * (G4NistManager::*)(const G4String &, G4bool) >(&G4NistManager::FindOrBuildElement));
  t27.method("FindOrBuildElement", [](G4NistManager& a, const G4String & arg0)->G4Element *{ return a.FindOrBuildElement(arg0); });
  t27.method("FindOrBuildElement", [](G4NistManager* a, const G4String & arg0)->G4Element *{ return a->FindOrBuildElement(arg0); });

  DEBUG_MSG("Adding wrapper for int G4NistManager::GetNumberOfElements() (" __HERE__ ")");
  // signature to use in the veto list: int G4NistManager::GetNumberOfElements()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:107:17
  t27.method("GetNumberOfElements", static_cast<int (G4NistManager::*)()  const>(&G4NistManager::GetNumberOfElements));

  DEBUG_MSG("Adding wrapper for G4int G4NistManager::GetZ(const G4String &) (" __HERE__ ")");
  // signature to use in the veto list: G4int G4NistManager::GetZ(const G4String &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:111:16
  t27.method("GetZ", static_cast<G4int (G4NistManager::*)(const G4String &)  const>(&G4NistManager::GetZ));

  DEBUG_MSG("Adding wrapper for G4double G4NistManager::GetAtomicMassAmu(const G4String &) (" __HERE__ ")");
  // signature to use in the veto list: G4double G4NistManager::GetAtomicMassAmu(const G4String &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:116:19
  t27.method("GetAtomicMassAmu", static_cast<G4double (G4NistManager::*)(const G4String &)  const>(&G4NistManager::GetAtomicMassAmu));

  DEBUG_MSG("Adding wrapper for G4double G4NistManager::GetAtomicMassAmu(G4int) (" __HERE__ ")");
  // signature to use in the veto list: G4double G4NistManager::GetAtomicMassAmu(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:121:19
  t27.method("GetAtomicMassAmu", static_cast<G4double (G4NistManager::*)(G4int)  const>(&G4NistManager::GetAtomicMassAmu));

  DEBUG_MSG("Adding wrapper for G4double G4NistManager::GetIsotopeMass(G4int, G4int) (" __HERE__ ")");
  // signature to use in the veto list: G4double G4NistManager::GetIsotopeMass(G4int, G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:125:19
  t27.method("GetIsotopeMass", static_cast<G4double (G4NistManager::*)(G4int, G4int)  const>(&G4NistManager::GetIsotopeMass));

  DEBUG_MSG("Adding wrapper for G4double G4NistManager::GetAtomicMass(G4int, G4int) (" __HERE__ ")");
  // signature to use in the veto list: G4double G4NistManager::GetAtomicMass(G4int, G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:130:19
  t27.method("GetAtomicMass", static_cast<G4double (G4NistManager::*)(G4int, G4int)  const>(&G4NistManager::GetAtomicMass));

  DEBUG_MSG("Adding wrapper for G4double G4NistManager::GetTotalElectronBindingEnergy(G4int) (" __HERE__ ")");
  // signature to use in the veto list: G4double G4NistManager::GetTotalElectronBindingEnergy(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:134:19
  t27.method("GetTotalElectronBindingEnergy", static_cast<G4double (G4NistManager::*)(G4int)  const>(&G4NistManager::GetTotalElectronBindingEnergy));

  DEBUG_MSG("Adding wrapper for G4int G4NistManager::GetNistFirstIsotopeN(G4int) (" __HERE__ ")");
  // signature to use in the veto list: G4int G4NistManager::GetNistFirstIsotopeN(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:138:16
  t27.method("GetNistFirstIsotopeN", static_cast<G4int (G4NistManager::*)(G4int)  const>(&G4NistManager::GetNistFirstIsotopeN));

  DEBUG_MSG("Adding wrapper for G4int G4NistManager::GetNumberOfNistIsotopes(G4int) (" __HERE__ ")");
  // signature to use in the veto list: G4int G4NistManager::GetNumberOfNistIsotopes(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:142:16
  t27.method("GetNumberOfNistIsotopes", static_cast<G4int (G4NistManager::*)(G4int)  const>(&G4NistManager::GetNumberOfNistIsotopes));

  DEBUG_MSG("Adding wrapper for G4double G4NistManager::GetIsotopeAbundance(G4int, G4int) (" __HERE__ ")");
  // signature to use in the veto list: G4double G4NistManager::GetIsotopeAbundance(G4int, G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:146:19
  t27.method("GetIsotopeAbundance", static_cast<G4double (G4NistManager::*)(G4int, G4int)  const>(&G4NistManager::GetIsotopeAbundance));

  DEBUG_MSG("Adding wrapper for void G4NistManager::PrintElement(G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4NistManager::PrintElement(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:150:15
  t27.method("PrintElement", static_cast<void (G4NistManager::*)(G4int)  const>(&G4NistManager::PrintElement));

  DEBUG_MSG("Adding wrapper for void G4NistManager::PrintElement(const G4String &) (" __HERE__ ")");
  // signature to use in the veto list: void G4NistManager::PrintElement(const G4String &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:154:8
  t27.method("PrintElement", static_cast<void (G4NistManager::*)(const G4String &)  const>(&G4NistManager::PrintElement));

  DEBUG_MSG("Adding wrapper for void G4NistManager::PrintG4Element(const G4String &) (" __HERE__ ")");
  // signature to use in the veto list: void G4NistManager::PrintG4Element(const G4String &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:158:8
  t27.method("PrintG4Element", static_cast<void (G4NistManager::*)(const G4String &)  const>(&G4NistManager::PrintG4Element));

  DEBUG_MSG("Adding wrapper for const int & G4NistManager::GetNistElementNames() (" __HERE__ ")");
  // signature to use in the veto list: const int & G4NistManager::GetNistElementNames()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:162:39
  t27.method("GetNistElementNames", static_cast<const int & (G4NistManager::*)()  const>(&G4NistManager::GetNistElementNames));

  DEBUG_MSG("Adding wrapper for G4double G4NistManager::GetMeanIonisationEnergy(G4int) (" __HERE__ ")");
  // signature to use in the veto list: G4double G4NistManager::GetMeanIonisationEnergy(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:166:19
  t27.method("GetMeanIonisationEnergy", static_cast<G4double (G4NistManager::*)(G4int)  const>(&G4NistManager::GetMeanIonisationEnergy));

  DEBUG_MSG("Adding wrapper for G4double G4NistManager::GetNominalDensity(G4int) (" __HERE__ ")");
  // signature to use in the veto list: G4double G4NistManager::GetNominalDensity(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:171:19
  t27.method("GetNominalDensity", static_cast<G4double (G4NistManager::*)(G4int)  const>(&G4NistManager::GetNominalDensity));

  DEBUG_MSG("Adding wrapper for G4Material * G4NistManager::GetMaterial(int) (" __HERE__ ")");
  // signature to use in the veto list: G4Material * G4NistManager::GetMaterial(int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:175:22
  t27.method("GetMaterial", static_cast<G4Material * (G4NistManager::*)(int)  const>(&G4NistManager::GetMaterial));

  DEBUG_MSG("Adding wrapper for G4Material * G4NistManager::FindMaterial(const G4String &) (" __HERE__ ")");
  // signature to use in the veto list: G4Material * G4NistManager::FindMaterial(const G4String &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:179:22
  t27.method("FindMaterial", static_cast<G4Material * (G4NistManager::*)(const G4String &)  const>(&G4NistManager::FindMaterial));

  DEBUG_MSG("Adding wrapper for G4Material * G4NistManager::FindOrBuildMaterial(const G4String &, G4bool, G4bool) (" __HERE__ ")");
  // signature to use in the veto list: G4Material * G4NistManager::FindOrBuildMaterial(const G4String &, G4bool, G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:180:22
  t27.method("FindOrBuildMaterial", static_cast<G4Material * (G4NistManager::*)(const G4String &, G4bool, G4bool) >(&G4NistManager::FindOrBuildMaterial));
  t27.method("FindOrBuildMaterial", [](G4NistManager& a, const G4String & arg0)->G4Material *{ return a.FindOrBuildMaterial(arg0); });
  t27.method("FindOrBuildMaterial", [](G4NistManager& a, const G4String & arg0, G4bool arg1)->G4Material *{ return a.FindOrBuildMaterial(arg0, arg1); });
  t27.method("FindOrBuildMaterial", [](G4NistManager* a, const G4String & arg0)->G4Material *{ return a->FindOrBuildMaterial(arg0); });
  t27.method("FindOrBuildMaterial", [](G4NistManager* a, const G4String & arg0, G4bool arg1)->G4Material *{ return a->FindOrBuildMaterial(arg0, arg1); });

  DEBUG_MSG("Adding wrapper for G4Material * G4NistManager::FindSimpleMaterial(G4int) (" __HERE__ ")");
  // signature to use in the veto list: G4Material * G4NistManager::FindSimpleMaterial(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:186:22
  t27.method("FindSimpleMaterial", static_cast<G4Material * (G4NistManager::*)(G4int)  const>(&G4NistManager::FindSimpleMaterial));

  DEBUG_MSG("Adding wrapper for G4Material * G4NistManager::FindOrBuildSimpleMaterial(G4int, G4bool) (" __HERE__ ")");
  // signature to use in the veto list: G4Material * G4NistManager::FindOrBuildSimpleMaterial(G4int, G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:187:22
  t27.method("FindOrBuildSimpleMaterial", static_cast<G4Material * (G4NistManager::*)(G4int, G4bool) >(&G4NistManager::FindOrBuildSimpleMaterial));
  t27.method("FindOrBuildSimpleMaterial", [](G4NistManager& a, G4int arg0)->G4Material *{ return a.FindOrBuildSimpleMaterial(arg0); });
  t27.method("FindOrBuildSimpleMaterial", [](G4NistManager* a, G4int arg0)->G4Material *{ return a->FindOrBuildSimpleMaterial(arg0); });

  DEBUG_MSG("Adding wrapper for G4Material * G4NistManager::BuildMaterialWithNewDensity(const G4String &, const G4String &, G4double, G4double, G4double) (" __HERE__ ")");
  // signature to use in the veto list: G4Material * G4NistManager::BuildMaterialWithNewDensity(const G4String &, const G4String &, G4double, G4double, G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:193:15
  t27.method("BuildMaterialWithNewDensity", static_cast<G4Material * (G4NistManager::*)(const G4String &, const G4String &, G4double, G4double, G4double) >(&G4NistManager::BuildMaterialWithNewDensity));
  t27.method("BuildMaterialWithNewDensity", [](G4NistManager& a, const G4String & arg0, const G4String & arg1)->G4Material *{ return a.BuildMaterialWithNewDensity(arg0, arg1); });
  t27.method("BuildMaterialWithNewDensity", [](G4NistManager& a, const G4String & arg0, const G4String & arg1, G4double arg2)->G4Material *{ return a.BuildMaterialWithNewDensity(arg0, arg1, arg2); });
  t27.method("BuildMaterialWithNewDensity", [](G4NistManager& a, const G4String & arg0, const G4String & arg1, G4double arg2, G4double arg3)->G4Material *{ return a.BuildMaterialWithNewDensity(arg0, arg1, arg2, arg3); });
  t27.method("BuildMaterialWithNewDensity", [](G4NistManager* a, const G4String & arg0, const G4String & arg1)->G4Material *{ return a->BuildMaterialWithNewDensity(arg0, arg1); });
  t27.method("BuildMaterialWithNewDensity", [](G4NistManager* a, const G4String & arg0, const G4String & arg1, G4double arg2)->G4Material *{ return a->BuildMaterialWithNewDensity(arg0, arg1, arg2); });
  t27.method("BuildMaterialWithNewDensity", [](G4NistManager* a, const G4String & arg0, const G4String & arg1, G4double arg2, G4double arg3)->G4Material *{ return a->BuildMaterialWithNewDensity(arg0, arg1, arg2, arg3); });

  DEBUG_MSG("Adding wrapper for G4Material * G4NistManager::ConstructNewMaterial(const G4String &, const int &, const int &, G4double, G4bool, G4State, G4double, G4double) (" __HERE__ ")");
  // signature to use in the veto list: G4Material * G4NistManager::ConstructNewMaterial(const G4String &, const int &, const int &, G4double, G4bool, G4State, G4double, G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:202:22
  t27.method("ConstructNewMaterial", static_cast<G4Material * (G4NistManager::*)(const G4String &, const int &, const int &, G4double, G4bool, G4State, G4double, G4double) >(&G4NistManager::ConstructNewMaterial));
  t27.method("ConstructNewMaterial", [](G4NistManager& a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3)->G4Material *{ return a.ConstructNewMaterial(arg0, arg1, arg2, arg3); });
  t27.method("ConstructNewMaterial", [](G4NistManager& a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3, G4bool arg4)->G4Material *{ return a.ConstructNewMaterial(arg0, arg1, arg2, arg3, arg4); });
  t27.method("ConstructNewMaterial", [](G4NistManager& a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3, G4bool arg4, G4State arg5)->G4Material *{ return a.ConstructNewMaterial(arg0, arg1, arg2, arg3, arg4, arg5); });
  t27.method("ConstructNewMaterial", [](G4NistManager& a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3, G4bool arg4, G4State arg5, G4double arg6)->G4Material *{ return a.ConstructNewMaterial(arg0, arg1, arg2, arg3, arg4, arg5, arg6); });
  t27.method("ConstructNewMaterial", [](G4NistManager* a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3)->G4Material *{ return a->ConstructNewMaterial(arg0, arg1, arg2, arg3); });
  t27.method("ConstructNewMaterial", [](G4NistManager* a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3, G4bool arg4)->G4Material *{ return a->ConstructNewMaterial(arg0, arg1, arg2, arg3, arg4); });
  t27.method("ConstructNewMaterial", [](G4NistManager* a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3, G4bool arg4, G4State arg5)->G4Material *{ return a->ConstructNewMaterial(arg0, arg1, arg2, arg3, arg4, arg5); });
  t27.method("ConstructNewMaterial", [](G4NistManager* a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3, G4bool arg4, G4State arg5, G4double arg6)->G4Material *{ return a->ConstructNewMaterial(arg0, arg1, arg2, arg3, arg4, arg5, arg6); });

  DEBUG_MSG("Adding wrapper for G4Material * G4NistManager::ConstructNewMaterial(const G4String &, const int &, const int &, G4double, G4bool, G4State, G4double, G4double) (" __HERE__ ")");
  // signature to use in the veto list: G4Material * G4NistManager::ConstructNewMaterial(const G4String &, const int &, const int &, G4double, G4bool, G4State, G4double, G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:215:22
  t27.method("ConstructNewMaterial", static_cast<G4Material * (G4NistManager::*)(const G4String &, const int &, const int &, G4double, G4bool, G4State, G4double, G4double) >(&G4NistManager::ConstructNewMaterial));
  t27.method("ConstructNewMaterial", [](G4NistManager& a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3)->G4Material *{ return a.ConstructNewMaterial(arg0, arg1, arg2, arg3); });
  t27.method("ConstructNewMaterial", [](G4NistManager& a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3, G4bool arg4)->G4Material *{ return a.ConstructNewMaterial(arg0, arg1, arg2, arg3, arg4); });
  t27.method("ConstructNewMaterial", [](G4NistManager& a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3, G4bool arg4, G4State arg5)->G4Material *{ return a.ConstructNewMaterial(arg0, arg1, arg2, arg3, arg4, arg5); });
  t27.method("ConstructNewMaterial", [](G4NistManager& a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3, G4bool arg4, G4State arg5, G4double arg6)->G4Material *{ return a.ConstructNewMaterial(arg0, arg1, arg2, arg3, arg4, arg5, arg6); });
  t27.method("ConstructNewMaterial", [](G4NistManager* a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3)->G4Material *{ return a->ConstructNewMaterial(arg0, arg1, arg2, arg3); });
  t27.method("ConstructNewMaterial", [](G4NistManager* a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3, G4bool arg4)->G4Material *{ return a->ConstructNewMaterial(arg0, arg1, arg2, arg3, arg4); });
  t27.method("ConstructNewMaterial", [](G4NistManager* a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3, G4bool arg4, G4State arg5)->G4Material *{ return a->ConstructNewMaterial(arg0, arg1, arg2, arg3, arg4, arg5); });
  t27.method("ConstructNewMaterial", [](G4NistManager* a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3, G4bool arg4, G4State arg5, G4double arg6)->G4Material *{ return a->ConstructNewMaterial(arg0, arg1, arg2, arg3, arg4, arg5, arg6); });

  DEBUG_MSG("Adding wrapper for G4Material * G4NistManager::ConstructNewGasMaterial(const G4String &, const G4String &, G4double, G4double, G4bool) (" __HERE__ ")");
  // signature to use in the veto list: G4Material * G4NistManager::ConstructNewGasMaterial(const G4String &, const G4String &, G4double, G4double, G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:227:22
  t27.method("ConstructNewGasMaterial", static_cast<G4Material * (G4NistManager::*)(const G4String &, const G4String &, G4double, G4double, G4bool) >(&G4NistManager::ConstructNewGasMaterial));
  t27.method("ConstructNewGasMaterial", [](G4NistManager& a, const G4String & arg0, const G4String & arg1, G4double arg2, G4double arg3)->G4Material *{ return a.ConstructNewGasMaterial(arg0, arg1, arg2, arg3); });
  t27.method("ConstructNewGasMaterial", [](G4NistManager* a, const G4String & arg0, const G4String & arg1, G4double arg2, G4double arg3)->G4Material *{ return a->ConstructNewGasMaterial(arg0, arg1, arg2, arg3); });

  DEBUG_MSG("Adding wrapper for G4Material * G4NistManager::ConstructNewIdealGasMaterial(const G4String &, const int &, const int &, G4bool, G4double, G4double) (" __HERE__ ")");
  // signature to use in the veto list: G4Material * G4NistManager::ConstructNewIdealGasMaterial(const G4String &, const int &, const int &, G4bool, G4double, G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:235:22
  t27.method("ConstructNewIdealGasMaterial", static_cast<G4Material * (G4NistManager::*)(const G4String &, const int &, const int &, G4bool, G4double, G4double) >(&G4NistManager::ConstructNewIdealGasMaterial));
  t27.method("ConstructNewIdealGasMaterial", [](G4NistManager& a, const G4String & arg0, const int & arg1, const int & arg2)->G4Material *{ return a.ConstructNewIdealGasMaterial(arg0, arg1, arg2); });
  t27.method("ConstructNewIdealGasMaterial", [](G4NistManager& a, const G4String & arg0, const int & arg1, const int & arg2, G4bool arg3)->G4Material *{ return a.ConstructNewIdealGasMaterial(arg0, arg1, arg2, arg3); });
  t27.method("ConstructNewIdealGasMaterial", [](G4NistManager& a, const G4String & arg0, const int & arg1, const int & arg2, G4bool arg3, G4double arg4)->G4Material *{ return a.ConstructNewIdealGasMaterial(arg0, arg1, arg2, arg3, arg4); });
  t27.method("ConstructNewIdealGasMaterial", [](G4NistManager* a, const G4String & arg0, const int & arg1, const int & arg2)->G4Material *{ return a->ConstructNewIdealGasMaterial(arg0, arg1, arg2); });
  t27.method("ConstructNewIdealGasMaterial", [](G4NistManager* a, const G4String & arg0, const int & arg1, const int & arg2, G4bool arg3)->G4Material *{ return a->ConstructNewIdealGasMaterial(arg0, arg1, arg2, arg3); });
  t27.method("ConstructNewIdealGasMaterial", [](G4NistManager* a, const G4String & arg0, const int & arg1, const int & arg2, G4bool arg3, G4double arg4)->G4Material *{ return a->ConstructNewIdealGasMaterial(arg0, arg1, arg2, arg3, arg4); });

  DEBUG_MSG("Adding wrapper for void G4NistManager::SetDensityEffectCalculatorFlag(const G4String &, G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4NistManager::SetDensityEffectCalculatorFlag(const G4String &, G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:245:8
  t27.method("SetDensityEffectCalculatorFlag", static_cast<void (G4NistManager::*)(const G4String &, G4bool) >(&G4NistManager::SetDensityEffectCalculatorFlag));

  DEBUG_MSG("Adding wrapper for void G4NistManager::SetDensityEffectCalculatorFlag(G4Material *, G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4NistManager::SetDensityEffectCalculatorFlag(G4Material *, G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:249:8
  t27.method("SetDensityEffectCalculatorFlag", static_cast<void (G4NistManager::*)(G4Material *, G4bool) >(&G4NistManager::SetDensityEffectCalculatorFlag));

  DEBUG_MSG("Adding wrapper for int G4NistManager::GetNumberOfMaterials() (" __HERE__ ")");
  // signature to use in the veto list: int G4NistManager::GetNumberOfMaterials()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:253:17
  t27.method("GetNumberOfMaterials", static_cast<int (G4NistManager::*)()  const>(&G4NistManager::GetNumberOfMaterials));

  DEBUG_MSG("Adding wrapper for G4int G4NistManager::GetVerbose() (" __HERE__ ")");
  // signature to use in the veto list: G4int G4NistManager::GetVerbose()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:255:16
  t27.method("GetVerbose", static_cast<G4int (G4NistManager::*)()  const>(&G4NistManager::GetVerbose));

  DEBUG_MSG("Adding wrapper for void G4NistManager::SetVerbose(G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4NistManager::SetVerbose(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:257:8
  t27.method("SetVerbose", static_cast<void (G4NistManager::*)(G4int) >(&G4NistManager::SetVerbose));

  DEBUG_MSG("Adding wrapper for void G4NistManager::PrintG4Material(const G4String &) (" __HERE__ ")");
  // signature to use in the veto list: void G4NistManager::PrintG4Material(const G4String &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:261:8
  t27.method("PrintG4Material", static_cast<void (G4NistManager::*)(const G4String &)  const>(&G4NistManager::PrintG4Material));

  DEBUG_MSG("Adding wrapper for void G4NistManager::ListMaterials(const G4String &) (" __HERE__ ")");
  // signature to use in the veto list: void G4NistManager::ListMaterials(const G4String &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:270:15
  t27.method("ListMaterials", static_cast<void (G4NistManager::*)(const G4String &)  const>(&G4NistManager::ListMaterials));

  DEBUG_MSG("Adding wrapper for const int & G4NistManager::GetNistMaterialNames() (" __HERE__ ")");
  // signature to use in the veto list: const int & G4NistManager::GetNistMaterialNames()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:274:39
  t27.method("GetNistMaterialNames", static_cast<const int & (G4NistManager::*)()  const>(&G4NistManager::GetNistMaterialNames));

  DEBUG_MSG("Adding wrapper for G4double G4NistManager::GetZ13(G4double) (" __HERE__ ")");
  // signature to use in the veto list: G4double G4NistManager::GetZ13(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:278:19
  t27.method("GetZ13", static_cast<G4double (G4NistManager::*)(G4double)  const>(&G4NistManager::GetZ13));

  DEBUG_MSG("Adding wrapper for G4double G4NistManager::GetZ13(G4int) (" __HERE__ ")");
  // signature to use in the veto list: G4double G4NistManager::GetZ13(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:279:19
  t27.method("GetZ13", static_cast<G4double (G4NistManager::*)(G4int)  const>(&G4NistManager::GetZ13));

  DEBUG_MSG("Adding wrapper for G4double G4NistManager::GetA27(G4int) (" __HERE__ ")");
  // signature to use in the veto list: G4double G4NistManager::GetA27(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:283:19
  t27.method("GetA27", static_cast<G4double (G4NistManager::*)(G4int)  const>(&G4NistManager::GetA27));

  DEBUG_MSG("Adding wrapper for G4double G4NistManager::GetLOGZ(G4int) (" __HERE__ ")");
  // signature to use in the veto list: G4double G4NistManager::GetLOGZ(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:287:19
  t27.method("GetLOGZ", static_cast<G4double (G4NistManager::*)(G4int)  const>(&G4NistManager::GetLOGZ));

  DEBUG_MSG("Adding wrapper for G4double G4NistManager::GetLOGAMU(G4int) (" __HERE__ ")");
  // signature to use in the veto list: G4double G4NistManager::GetLOGAMU(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:288:19
  t27.method("GetLOGAMU", static_cast<G4double (G4NistManager::*)(G4int)  const>(&G4NistManager::GetLOGAMU));

  DEBUG_MSG("Adding wrapper for G4ICRU90StoppingData * G4NistManager::GetICRU90StoppingData() (" __HERE__ ")");
  // signature to use in the veto list: G4ICRU90StoppingData * G4NistManager::GetICRU90StoppingData()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:290:25
  t27.method("GetICRU90StoppingData", static_cast<G4ICRU90StoppingData * (G4NistManager::*)() >(&G4NistManager::GetICRU90StoppingData));

  DEBUG_MSG("Adding wrapper for int G4NistManager::GetNumberOfMaterials() (" __HERE__ ")");
  // signature to use in the veto list: int G4NistManager::GetNumberOfMaterials()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:322:30
  t27.method("GetNumberOfMaterials", static_cast<int (G4NistManager::*)()  const>(&G4NistManager::GetNumberOfMaterials));

  DEBUG_MSG("Adding wrapper for G4Element * G4NistManager::GetElement(int) (" __HERE__ ")");
  // signature to use in the veto list: G4Element * G4NistManager::GetElement(int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:329:34
  t27.method("GetElement", static_cast<G4Element * (G4NistManager::*)(int)  const>(&G4NistManager::GetElement));

  DEBUG_MSG("Adding wrapper for int G4NistManager::GetNumberOfElements() (" __HERE__ ")");
  // signature to use in the veto list: int G4NistManager::GetNumberOfElements()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:362:30
  t27.method("GetNumberOfElements", static_cast<int (G4NistManager::*)()  const>(&G4NistManager::GetNumberOfElements));

  DEBUG_MSG("Adding wrapper for const int & G4NistManager::GetNistElementNames() (" __HERE__ ")");
  // signature to use in the veto list: const int & G4NistManager::GetNistElementNames()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:439:45
  t27.method("GetNistElementNames", static_cast<const int & (G4NistManager::*)()  const>(&G4NistManager::GetNistElementNames));

  DEBUG_MSG("Adding wrapper for G4Material * G4NistManager::GetMaterial(int) (" __HERE__ ")");
  // signature to use in the veto list: G4Material * G4NistManager::GetMaterial(int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:467:35
  t27.method("GetMaterial", static_cast<G4Material * (G4NistManager::*)(int)  const>(&G4NistManager::GetMaterial));

  DEBUG_MSG("Adding wrapper for G4Material * G4NistManager::ConstructNewMaterial(const G4String &, const int &, const int &, G4double, G4bool, G4State, G4double, G4double) (" __HERE__ ")");
  // signature to use in the veto list: G4Material * G4NistManager::ConstructNewMaterial(const G4String &, const int &, const int &, G4double, G4bool, G4State, G4double, G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:515:35
  t27.method("ConstructNewMaterial", static_cast<G4Material * (G4NistManager::*)(const G4String &, const int &, const int &, G4double, G4bool, G4State, G4double, G4double) >(&G4NistManager::ConstructNewMaterial));

  DEBUG_MSG("Adding wrapper for G4Material * G4NistManager::ConstructNewMaterial(const G4String &, const int &, const int &, G4double, G4bool, G4State, G4double, G4double) (" __HERE__ ")");
  // signature to use in the veto list: G4Material * G4NistManager::ConstructNewMaterial(const G4String &, const int &, const int &, G4double, G4bool, G4State, G4double, G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:532:35
  t27.method("ConstructNewMaterial", static_cast<G4Material * (G4NistManager::*)(const G4String &, const int &, const int &, G4double, G4bool, G4State, G4double, G4double) >(&G4NistManager::ConstructNewMaterial));

  DEBUG_MSG("Adding wrapper for G4Material * G4NistManager::ConstructNewIdealGasMaterial(const G4String &, const int &, const int &, G4bool, G4double, G4double) (" __HERE__ ")");
  // signature to use in the veto list: G4Material * G4NistManager::ConstructNewIdealGasMaterial(const G4String &, const int &, const int &, G4bool, G4double, G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:558:35
  t27.method("ConstructNewIdealGasMaterial", static_cast<G4Material * (G4NistManager::*)(const G4String &, const int &, const int &, G4bool, G4double, G4double) >(&G4NistManager::ConstructNewIdealGasMaterial));

  DEBUG_MSG("Adding wrapper for const int & G4NistManager::GetNistMaterialNames() (" __HERE__ ")");
  // signature to use in the veto list: const int & G4NistManager::GetNistMaterialNames()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:580:45
  t27.method("GetNistMaterialNames", static_cast<const int & (G4NistManager::*)()  const>(&G4NistManager::GetNistMaterialNames));

  /* End of G4NistManager class method wrappers
   **********************************************************************/


  /**********************************************************************/
  /* Wrappers for the methods of class G4PVPlacement
   */


  DEBUG_MSG("Adding wrapper for void G4PVPlacement::G4PVPlacement(G4RotationMatrix *, const G4ThreeVector &, G4LogicalVolume *, const G4String &, G4LogicalVolume *, G4bool, G4int, G4bool) (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4PVPlacement.hh:47:5
  t31.constructor<G4RotationMatrix *, const G4ThreeVector &, G4LogicalVolume *, const G4String &, G4LogicalVolume *, G4bool, G4int>();
  t31.constructor<G4RotationMatrix *, const G4ThreeVector &, G4LogicalVolume *, const G4String &, G4LogicalVolume *, G4bool, G4int, G4bool>();


  DEBUG_MSG("Adding wrapper for void G4PVPlacement::G4PVPlacement(const G4Transform3D &, G4LogicalVolume *, const G4String &, G4LogicalVolume *, G4bool, G4int, G4bool) (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4PVPlacement.hh:69:5
  t31.constructor<const G4Transform3D &, G4LogicalVolume *, const G4String &, G4LogicalVolume *, G4bool, G4int>();
  t31.constructor<const G4Transform3D &, G4LogicalVolume *, const G4String &, G4LogicalVolume *, G4bool, G4int, G4bool>();


  DEBUG_MSG("Adding wrapper for void G4PVPlacement::G4PVPlacement(G4RotationMatrix *, const G4ThreeVector &, const G4String &, G4LogicalVolume *, G4VPhysicalVolume *, G4bool, G4int, G4bool) (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4PVPlacement.hh:90:5
  t31.constructor<G4RotationMatrix *, const G4ThreeVector &, const G4String &, G4LogicalVolume *, G4VPhysicalVolume *, G4bool, G4int>();
  t31.constructor<G4RotationMatrix *, const G4ThreeVector &, const G4String &, G4LogicalVolume *, G4VPhysicalVolume *, G4bool, G4int, G4bool>();


  DEBUG_MSG("Adding wrapper for void G4PVPlacement::G4PVPlacement(const G4Transform3D &, const G4String &, G4LogicalVolume *, G4VPhysicalVolume *, G4bool, G4int, G4bool) (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4PVPlacement.hh:102:5
  t31.constructor<const G4Transform3D &, const G4String &, G4LogicalVolume *, G4VPhysicalVolume *, G4bool, G4int>();
  t31.constructor<const G4Transform3D &, const G4String &, G4LogicalVolume *, G4VPhysicalVolume *, G4bool, G4int, G4bool>();

  DEBUG_MSG("Adding wrapper for G4int G4PVPlacement::GetCopyNo() (" __HERE__ ")");
  // signature to use in the veto list: G4int G4PVPlacement::GetCopyNo()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4PVPlacement.hh:117:18
  t31.method("GetCopyNo", static_cast<G4int (G4PVPlacement::*)()  const>(&G4PVPlacement::GetCopyNo));

  DEBUG_MSG("Adding wrapper for void G4PVPlacement::SetCopyNo(G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4PVPlacement::SetCopyNo(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4PVPlacement.hh:119:10
  t31.method("SetCopyNo", static_cast<void (G4PVPlacement::*)(G4int) >(&G4PVPlacement::SetCopyNo));

  DEBUG_MSG("Adding wrapper for G4bool G4PVPlacement::CheckOverlaps(G4int, G4double, G4bool, G4int) (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4PVPlacement::CheckOverlaps(G4int, G4double, G4bool, G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4PVPlacement.hh:122:12
  t31.method("CheckOverlaps", static_cast<G4bool (G4PVPlacement::*)(G4int, G4double, G4bool, G4int) >(&G4PVPlacement::CheckOverlaps));
  t31.method("CheckOverlaps", [](G4PVPlacement& a)->G4bool{ return a.CheckOverlaps(); });
  t31.method("CheckOverlaps", [](G4PVPlacement& a, G4int arg0)->G4bool{ return a.CheckOverlaps(arg0); });
  t31.method("CheckOverlaps", [](G4PVPlacement& a, G4int arg0, G4double arg1)->G4bool{ return a.CheckOverlaps(arg0, arg1); });
  t31.method("CheckOverlaps", [](G4PVPlacement& a, G4int arg0, G4double arg1, G4bool arg2)->G4bool{ return a.CheckOverlaps(arg0, arg1, arg2); });
  t31.method("CheckOverlaps", [](G4PVPlacement* a)->G4bool{ return a->CheckOverlaps(); });
  t31.method("CheckOverlaps", [](G4PVPlacement* a, G4int arg0)->G4bool{ return a->CheckOverlaps(arg0); });
  t31.method("CheckOverlaps", [](G4PVPlacement* a, G4int arg0, G4double arg1)->G4bool{ return a->CheckOverlaps(arg0, arg1); });
  t31.method("CheckOverlaps", [](G4PVPlacement* a, G4int arg0, G4double arg1, G4bool arg2)->G4bool{ return a->CheckOverlaps(arg0, arg1, arg2); });

  DEBUG_MSG("Adding wrapper for G4bool G4PVPlacement::IsMany() (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4PVPlacement::IsMany()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4PVPlacement.hh:143:12
  t31.method("IsMany", static_cast<G4bool (G4PVPlacement::*)()  const>(&G4PVPlacement::IsMany));

  DEBUG_MSG("Adding wrapper for G4bool G4PVPlacement::IsReplicated() (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4PVPlacement::IsReplicated()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4PVPlacement.hh:144:12
  t31.method("IsReplicated", static_cast<G4bool (G4PVPlacement::*)()  const>(&G4PVPlacement::IsReplicated));

  DEBUG_MSG("Adding wrapper for G4bool G4PVPlacement::IsParameterised() (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4PVPlacement::IsParameterised()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4PVPlacement.hh:145:12
  t31.method("IsParameterised", static_cast<G4bool (G4PVPlacement::*)()  const>(&G4PVPlacement::IsParameterised));

  DEBUG_MSG("Adding wrapper for G4VPVParameterisation * G4PVPlacement::GetParameterisation() (" __HERE__ ")");
  // signature to use in the veto list: G4VPVParameterisation * G4PVPlacement::GetParameterisation()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4PVPlacement.hh:146:28
  t31.method("GetParameterisation", static_cast<G4VPVParameterisation * (G4PVPlacement::*)()  const>(&G4PVPlacement::GetParameterisation));

  DEBUG_MSG("Adding wrapper for void G4PVPlacement::GetReplicationData(EAxis &, G4int &, G4double &, G4double &, G4bool &) (" __HERE__ ")");
  // signature to use in the veto list: void G4PVPlacement::GetReplicationData(EAxis &, G4int &, G4double &, G4double &, G4bool &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4PVPlacement.hh:147:10
  t31.method("GetReplicationData", static_cast<void (G4PVPlacement::*)(EAxis &, G4int &, G4double &, G4double &, G4bool &)  const>(&G4PVPlacement::GetReplicationData));

  DEBUG_MSG("Adding wrapper for G4bool G4PVPlacement::IsRegularStructure() (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4PVPlacement::IsRegularStructure()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4PVPlacement.hh:152:12
  t31.method("IsRegularStructure", static_cast<G4bool (G4PVPlacement::*)()  const>(&G4PVPlacement::IsRegularStructure));

  DEBUG_MSG("Adding wrapper for G4int G4PVPlacement::GetRegularStructureId() (" __HERE__ ")");
  // signature to use in the veto list: G4int G4PVPlacement::GetRegularStructureId()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4PVPlacement.hh:153:11
  t31.method("GetRegularStructureId", static_cast<G4int (G4PVPlacement::*)()  const>(&G4PVPlacement::GetRegularStructureId));

  DEBUG_MSG("Adding wrapper for EVolume G4PVPlacement::VolumeType() (" __HERE__ ")");
  // signature to use in the veto list: EVolume G4PVPlacement::VolumeType()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4PVPlacement.hh:155:13
  t31.method("VolumeType", static_cast<EVolume (G4PVPlacement::*)()  const>(&G4PVPlacement::VolumeType));

  /* End of G4PVPlacement class method wrappers
   **********************************************************************/

  DEBUG_MSG("End of wrapper definitions");

}
