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
  template<> struct IsMirroredType<G4JLExceptionHandler> : std::false_type { };
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

  DEBUG_MSG("Adding wrapper for enum G4ExceptionSeverity (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4ExceptionSeverity.hh:59:6
  types.add_bits<G4ExceptionSeverity>("G4ExceptionSeverity", jlcxx::julia_type("CppEnum"));
  types.set_const("FatalException", FatalException);
  types.set_const("FatalErrorInArgument", FatalErrorInArgument);
  types.set_const("RunMustBeAborted", RunMustBeAborted);
  types.set_const("EventMustBeAborted", EventMustBeAborted);
  types.set_const("JustWarning", JustWarning);

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

  DEBUG_MSG("Adding wrapper for type G4JLExceptionHandler (" __HERE__ ")");
  // defined in ./cpp/Geant4Wrap.h:6:7
  auto t0 = types.add_type<G4JLExceptionHandler>("G4JLExceptionHandler");

  DEBUG_MSG("Adding wrapper for type G4String (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4String.hh:61:7
  auto t2 = types.add_type<G4String>("G4String");

  DEBUG_MSG("Adding wrapper for type G4Box (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UBox.hh:45:7
  auto t3 = types.add_type<G4Box>("G4Box");

  DEBUG_MSG("Adding wrapper for type G4VPVParameterisation (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4VPVParameterisation.hh:68:7
  auto t4 = types.add_type<G4VPVParameterisation>("G4VPVParameterisation");

  DEBUG_MSG("Adding wrapper for type G4VPhysicalVolume (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4VPhysicalVolume.hh:78:7
  auto t5 = types.add_type<G4VPhysicalVolume>("G4VPhysicalVolume");

  DEBUG_MSG("Adding wrapper for type G4VSolid (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4VSolid.hh:82:7
  auto t6 = types.add_type<G4VSolid>("G4VSolid");

  DEBUG_MSG("Adding wrapper for type G4VoxelLimits (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4VoxelLimits.hh:52:7
  auto t8 = types.add_type<G4VoxelLimits>("G4VoxelLimits");

  DEBUG_MSG("Adding wrapper for type G4AffineTransform (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4AffineTransform.hh:69:7
  auto t9 = types.add_type<G4AffineTransform>("G4AffineTransform");

  DEBUG_MSG("Adding wrapper for type G4Polyhedron (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4Polyhedron.hh:123:7
  auto t10 = types.add_type<G4Polyhedron>("G4Polyhedron");

  DEBUG_MSG("Adding wrapper for type G4Cons (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:45:7
  auto t11 = types.add_type<G4Cons>("G4Cons");

  DEBUG_MSG("Adding wrapper for type G4Orb (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UOrb.hh:45:7
  auto t12 = types.add_type<G4Orb>("G4Orb");

  DEBUG_MSG("Adding wrapper for type G4Sphere (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:45:7
  auto t13 = types.add_type<G4Sphere>("G4Sphere");

  DEBUG_MSG("Adding wrapper for type G4Trd (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:45:7
  auto t14 = types.add_type<G4Trd>("G4Trd");

  DEBUG_MSG("Adding wrapper for type G4LVData (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:127:7
  auto t15 = types.add_type<G4LVData>("G4LVData");

  DEBUG_MSG("Adding wrapper for type G4Material (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4Material.hh:117:7
  auto t16 = types.add_type<G4Material>("G4Material");

  DEBUG_MSG("Adding wrapper for type G4LogicalVolume (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:181:7
  auto t17 = types.add_type<G4LogicalVolume>("G4LogicalVolume");

  DEBUG_MSG("Adding wrapper for type G4SmartVoxelHeader (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4SmartVoxelHeader.hh:74:7
  auto t19 = types.add_type<G4SmartVoxelHeader>("G4SmartVoxelHeader");

  DEBUG_MSG("Adding wrapper for type G4Region (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4Region.hh:95:7
  auto t20 = types.add_type<G4Region>("G4Region");

  DEBUG_MSG("Adding wrapper for type G4NavigationLevelRep (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NavigationLevelRep.hh:50:7
  auto t21 = types.add_type<G4NavigationLevelRep>("G4NavigationLevelRep");

  DEBUG_MSG("Adding wrapper for type G4RunManager (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:137:7
  auto t22 = types.add_type<G4RunManager>("G4RunManager");

  DEBUG_MSG("Adding wrapper for type G4Event (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4Event.hh:54:7
  auto t23 = types.add_type<G4Event>("G4Event");

  DEBUG_MSG("Adding wrapper for type G4UserStackingAction (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UserStackingAction.hh:44:7
  auto t24 = types.add_type<G4UserStackingAction>("G4UserStackingAction");

  DEBUG_MSG("Adding wrapper for type G4UserTrackingAction (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UserTrackingAction.hh:44:7
  auto t25 = types.add_type<G4UserTrackingAction>("G4UserTrackingAction");

  DEBUG_MSG("Adding wrapper for type G4UserSteppingAction (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UserSteppingAction.hh:44:7
  auto t26 = types.add_type<G4UserSteppingAction>("G4UserSteppingAction");

  DEBUG_MSG("Adding wrapper for type G4PrimaryTransformer (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4PrimaryTransformer.hh:47:7
  auto t27 = types.add_type<G4PrimaryTransformer>("G4PrimaryTransformer");

  DEBUG_MSG("Adding wrapper for type G4NistManager (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:83:7
  auto t29 = types.add_type<G4NistManager>("G4NistManager");

  DEBUG_MSG("Adding wrapper for type G4Element (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4Element.hh:97:7
  auto t30 = types.add_type<G4Element>("G4Element");

  DEBUG_MSG("Adding wrapper for type G4ICRU90StoppingData (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4ICRU90StoppingData.hh:56:7
  auto t32 = types.add_type<G4ICRU90StoppingData>("G4ICRU90StoppingData");

  DEBUG_MSG("Adding wrapper for type G4PVPlacement (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4PVPlacement.hh:43:7
  auto t33 = types.add_type<G4PVPlacement>("G4PVPlacement", jlcxx::julia_base_type<G4VPhysicalVolume>());

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
  /* Wrappers for the methods of class G4JLExceptionHandler
   */


  DEBUG_MSG("Adding wrapper for void G4JLExceptionHandler::G4JLExceptionHandler() (" __HERE__ ")");
  // defined in ./cpp/Geant4Wrap.h:8:3
  t0.constructor<>();

  DEBUG_MSG("Adding wrapper for G4bool G4JLExceptionHandler::Notify(const char *, const char *, G4ExceptionSeverity, const char *) (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4JLExceptionHandler::Notify(const char *, const char *, G4ExceptionSeverity, const char *)
  // defined in ./cpp/Geant4Wrap.h:10:10
  t0.method("Notify", [](G4JLExceptionHandler& a, const char * arg0, const char * arg1, G4ExceptionSeverity arg2, const char * arg3)->G4bool{ return a.Notify(arg0, arg1, arg2, arg3); });
  t0.method("Notify", [](G4JLExceptionHandler* a, const char * arg0, const char * arg1, G4ExceptionSeverity arg2, const char * arg3)->G4bool{ return a->Notify(arg0, arg1, arg2, arg3); });

  /* End of G4JLExceptionHandler class method wrappers
   **********************************************************************/


  /**********************************************************************/
  /* Wrappers for the methods of class G4String
   */


  DEBUG_MSG("Adding wrapper for void G4String::G4String(const G4String &) (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4String.icc:35:18
  t2.constructor<const G4String &>();



  /* End of G4String class method wrappers
   **********************************************************************/


  /**********************************************************************/
  /* Wrappers for the methods of class G4Box
   */


  DEBUG_MSG("Adding wrapper for void G4Box::G4Box(const G4String &, G4double, G4double, G4double) (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UBox.hh:52:5
  t3.constructor<const G4String &, G4double, G4double, G4double>();

  DEBUG_MSG("Adding wrapper for void G4Box::ComputeDimensions(G4VPVParameterisation *, const G4int, const G4VPhysicalVolume *) (" __HERE__ ")");
  // signature to use in the veto list: void G4Box::ComputeDimensions(G4VPVParameterisation *, const G4int, const G4VPhysicalVolume *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UBox.hh:57:10
  t3.method("ComputeDimensions", [](G4Box& a, G4VPVParameterisation * arg0, const G4int arg1, const G4VPhysicalVolume * arg2)->void{ a.ComputeDimensions(arg0, arg1, arg2); });
  t3.method("ComputeDimensions", [](G4Box* a, G4VPVParameterisation * arg0, const G4int arg1, const G4VPhysicalVolume * arg2)->void{ a->ComputeDimensions(arg0, arg1, arg2); });

  DEBUG_MSG("Adding wrapper for G4VSolid * G4Box::Clone() (" __HERE__ ")");
  // signature to use in the veto list: G4VSolid * G4Box::Clone()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UBox.hh:61:15
  t3.method("Clone", [](G4Box const& a)->G4VSolid *{ return a.Clone(); });
  t3.method("Clone", [](G4Box const* a)->G4VSolid *{ return a->Clone(); });

  DEBUG_MSG("Adding wrapper for G4double G4Box::GetXHalfLength() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Box::GetXHalfLength()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UBox.hh:63:14
  t3.method("GetXHalfLength", [](G4Box const& a)->G4double{ return a.GetXHalfLength(); });
  t3.method("GetXHalfLength", [](G4Box const* a)->G4double{ return a->GetXHalfLength(); });

  DEBUG_MSG("Adding wrapper for G4double G4Box::GetYHalfLength() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Box::GetYHalfLength()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UBox.hh:64:14
  t3.method("GetYHalfLength", [](G4Box const& a)->G4double{ return a.GetYHalfLength(); });
  t3.method("GetYHalfLength", [](G4Box const* a)->G4double{ return a->GetYHalfLength(); });

  DEBUG_MSG("Adding wrapper for G4double G4Box::GetZHalfLength() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Box::GetZHalfLength()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UBox.hh:65:14
  t3.method("GetZHalfLength", [](G4Box const& a)->G4double{ return a.GetZHalfLength(); });
  t3.method("GetZHalfLength", [](G4Box const* a)->G4double{ return a->GetZHalfLength(); });

  DEBUG_MSG("Adding wrapper for void G4Box::SetXHalfLength(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Box::SetXHalfLength(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UBox.hh:67:10
  t3.method("SetXHalfLength", [](G4Box& a, G4double arg0)->void{ a.SetXHalfLength(arg0); });
  t3.method("SetXHalfLength", [](G4Box* a, G4double arg0)->void{ a->SetXHalfLength(arg0); });

  DEBUG_MSG("Adding wrapper for void G4Box::SetYHalfLength(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Box::SetYHalfLength(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UBox.hh:68:10
  t3.method("SetYHalfLength", [](G4Box& a, G4double arg0)->void{ a.SetYHalfLength(arg0); });
  t3.method("SetYHalfLength", [](G4Box* a, G4double arg0)->void{ a->SetYHalfLength(arg0); });

  DEBUG_MSG("Adding wrapper for void G4Box::SetZHalfLength(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Box::SetZHalfLength(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UBox.hh:69:10
  t3.method("SetZHalfLength", [](G4Box& a, G4double arg0)->void{ a.SetZHalfLength(arg0); });
  t3.method("SetZHalfLength", [](G4Box* a, G4double arg0)->void{ a->SetZHalfLength(arg0); });

  DEBUG_MSG("Adding wrapper for G4GeometryType G4Box::GetEntityType() (" __HERE__ ")");
  // signature to use in the veto list: G4GeometryType G4Box::GetEntityType()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UBox.hh:71:27
  t3.method("GetEntityType", [](G4Box const& a)->G4GeometryType{ return a.GetEntityType(); });
  t3.method("GetEntityType", [](G4Box const* a)->G4GeometryType{ return a->GetEntityType(); });

  DEBUG_MSG("Adding wrapper for void G4Box::BoundingLimits(G4ThreeVector &, G4ThreeVector &) (" __HERE__ ")");
  // signature to use in the veto list: void G4Box::BoundingLimits(G4ThreeVector &, G4ThreeVector &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UBox.hh:73:10
  t3.method("BoundingLimits", [](G4Box const& a, G4ThreeVector & arg0, G4ThreeVector & arg1)->void{ a.BoundingLimits(arg0, arg1); });
  t3.method("BoundingLimits", [](G4Box const* a, G4ThreeVector & arg0, G4ThreeVector & arg1)->void{ a->BoundingLimits(arg0, arg1); });

  DEBUG_MSG("Adding wrapper for G4bool G4Box::CalculateExtent(const EAxis, const G4VoxelLimits &, const G4AffineTransform &, G4double &, G4double &) (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4Box::CalculateExtent(const EAxis, const G4VoxelLimits &, const G4AffineTransform &, G4double &, G4double &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UBox.hh:75:12
  t3.method("CalculateExtent", [](G4Box const& a, const EAxis arg0, const G4VoxelLimits & arg1, const G4AffineTransform & arg2, G4double & arg3, G4double & arg4)->G4bool{ return a.CalculateExtent(arg0, arg1, arg2, arg3, arg4); });
  t3.method("CalculateExtent", [](G4Box const* a, const EAxis arg0, const G4VoxelLimits & arg1, const G4AffineTransform & arg2, G4double & arg3, G4double & arg4)->G4bool{ return a->CalculateExtent(arg0, arg1, arg2, arg3, arg4); });

  DEBUG_MSG("Adding wrapper for G4Polyhedron * G4Box::CreatePolyhedron() (" __HERE__ ")");
  // signature to use in the veto list: G4Polyhedron * G4Box::CreatePolyhedron()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UBox.hh:80:19
  t3.method("CreatePolyhedron", [](G4Box const& a)->G4Polyhedron *{ return a.CreatePolyhedron(); });
  t3.method("CreatePolyhedron", [](G4Box const* a)->G4Polyhedron *{ return a->CreatePolyhedron(); });


  DEBUG_MSG("Adding wrapper for void G4Box::G4Box(const G4Box &) (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UBox.hh:89:5
  t3.constructor<const G4Box &>();

  DEBUG_MSG("Adding wrapper for G4Box & G4Box::operator=(const G4Box &) (" __HERE__ ")");
  // signature to use in the veto list: G4Box & G4Box::operator=(const G4Box &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UBox.hh:90:13
  t3.method("assign", [](G4Box& a, const G4Box & arg0)->G4Box &{ return a.operator=(arg0); });
  t3.method("assign", [](G4Box* a, const G4Box & arg0)->G4Box &{ return a->operator=(arg0); });

  /* End of G4Box class method wrappers
   **********************************************************************/


  /**********************************************************************/
  /* Wrappers for the methods of class G4Cons
   */


  DEBUG_MSG("Adding wrapper for void G4Cons::G4Cons(const G4String &, G4double, G4double, G4double, G4double, G4double, G4double, G4double) (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:52:5
  t11.constructor<const G4String &, G4double, G4double, G4double, G4double, G4double, G4double, G4double>();

  DEBUG_MSG("Adding wrapper for void G4Cons::ComputeDimensions(G4VPVParameterisation *, const G4int, const G4VPhysicalVolume *) (" __HERE__ ")");
  // signature to use in the veto list: void G4Cons::ComputeDimensions(G4VPVParameterisation *, const G4int, const G4VPhysicalVolume *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:61:10
  t11.method("ComputeDimensions", [](G4Cons& a, G4VPVParameterisation * arg0, const G4int arg1, const G4VPhysicalVolume * arg2)->void{ a.ComputeDimensions(arg0, arg1, arg2); });
  t11.method("ComputeDimensions", [](G4Cons* a, G4VPVParameterisation * arg0, const G4int arg1, const G4VPhysicalVolume * arg2)->void{ a->ComputeDimensions(arg0, arg1, arg2); });

  DEBUG_MSG("Adding wrapper for G4VSolid * G4Cons::Clone() (" __HERE__ ")");
  // signature to use in the veto list: G4VSolid * G4Cons::Clone()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:65:15
  t11.method("Clone", [](G4Cons const& a)->G4VSolid *{ return a.Clone(); });
  t11.method("Clone", [](G4Cons const* a)->G4VSolid *{ return a->Clone(); });

  DEBUG_MSG("Adding wrapper for G4double G4Cons::GetInnerRadiusMinusZ() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Cons::GetInnerRadiusMinusZ()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:67:14
  t11.method("GetInnerRadiusMinusZ", [](G4Cons const& a)->G4double{ return a.GetInnerRadiusMinusZ(); });
  t11.method("GetInnerRadiusMinusZ", [](G4Cons const* a)->G4double{ return a->GetInnerRadiusMinusZ(); });

  DEBUG_MSG("Adding wrapper for G4double G4Cons::GetOuterRadiusMinusZ() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Cons::GetOuterRadiusMinusZ()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:68:14
  t11.method("GetOuterRadiusMinusZ", [](G4Cons const& a)->G4double{ return a.GetOuterRadiusMinusZ(); });
  t11.method("GetOuterRadiusMinusZ", [](G4Cons const* a)->G4double{ return a->GetOuterRadiusMinusZ(); });

  DEBUG_MSG("Adding wrapper for G4double G4Cons::GetInnerRadiusPlusZ() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Cons::GetInnerRadiusPlusZ()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:69:14
  t11.method("GetInnerRadiusPlusZ", [](G4Cons const& a)->G4double{ return a.GetInnerRadiusPlusZ(); });
  t11.method("GetInnerRadiusPlusZ", [](G4Cons const* a)->G4double{ return a->GetInnerRadiusPlusZ(); });

  DEBUG_MSG("Adding wrapper for G4double G4Cons::GetOuterRadiusPlusZ() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Cons::GetOuterRadiusPlusZ()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:70:14
  t11.method("GetOuterRadiusPlusZ", [](G4Cons const& a)->G4double{ return a.GetOuterRadiusPlusZ(); });
  t11.method("GetOuterRadiusPlusZ", [](G4Cons const* a)->G4double{ return a->GetOuterRadiusPlusZ(); });

  DEBUG_MSG("Adding wrapper for G4double G4Cons::GetZHalfLength() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Cons::GetZHalfLength()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:71:14
  t11.method("GetZHalfLength", [](G4Cons const& a)->G4double{ return a.GetZHalfLength(); });
  t11.method("GetZHalfLength", [](G4Cons const* a)->G4double{ return a->GetZHalfLength(); });

  DEBUG_MSG("Adding wrapper for G4double G4Cons::GetStartPhiAngle() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Cons::GetStartPhiAngle()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:72:14
  t11.method("GetStartPhiAngle", [](G4Cons const& a)->G4double{ return a.GetStartPhiAngle(); });
  t11.method("GetStartPhiAngle", [](G4Cons const* a)->G4double{ return a->GetStartPhiAngle(); });

  DEBUG_MSG("Adding wrapper for G4double G4Cons::GetDeltaPhiAngle() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Cons::GetDeltaPhiAngle()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:73:14
  t11.method("GetDeltaPhiAngle", [](G4Cons const& a)->G4double{ return a.GetDeltaPhiAngle(); });
  t11.method("GetDeltaPhiAngle", [](G4Cons const* a)->G4double{ return a->GetDeltaPhiAngle(); });

  DEBUG_MSG("Adding wrapper for G4double G4Cons::GetSinStartPhi() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Cons::GetSinStartPhi()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:74:14
  t11.method("GetSinStartPhi", [](G4Cons const& a)->G4double{ return a.GetSinStartPhi(); });
  t11.method("GetSinStartPhi", [](G4Cons const* a)->G4double{ return a->GetSinStartPhi(); });

  DEBUG_MSG("Adding wrapper for G4double G4Cons::GetCosStartPhi() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Cons::GetCosStartPhi()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:75:14
  t11.method("GetCosStartPhi", [](G4Cons const& a)->G4double{ return a.GetCosStartPhi(); });
  t11.method("GetCosStartPhi", [](G4Cons const* a)->G4double{ return a->GetCosStartPhi(); });

  DEBUG_MSG("Adding wrapper for G4double G4Cons::GetSinEndPhi() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Cons::GetSinEndPhi()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:76:14
  t11.method("GetSinEndPhi", [](G4Cons const& a)->G4double{ return a.GetSinEndPhi(); });
  t11.method("GetSinEndPhi", [](G4Cons const* a)->G4double{ return a->GetSinEndPhi(); });

  DEBUG_MSG("Adding wrapper for G4double G4Cons::GetCosEndPhi() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Cons::GetCosEndPhi()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:77:14
  t11.method("GetCosEndPhi", [](G4Cons const& a)->G4double{ return a.GetCosEndPhi(); });
  t11.method("GetCosEndPhi", [](G4Cons const* a)->G4double{ return a->GetCosEndPhi(); });

  DEBUG_MSG("Adding wrapper for void G4Cons::SetInnerRadiusMinusZ(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Cons::SetInnerRadiusMinusZ(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:79:10
  t11.method("SetInnerRadiusMinusZ", [](G4Cons& a, G4double arg0)->void{ a.SetInnerRadiusMinusZ(arg0); });
  t11.method("SetInnerRadiusMinusZ", [](G4Cons* a, G4double arg0)->void{ a->SetInnerRadiusMinusZ(arg0); });

  DEBUG_MSG("Adding wrapper for void G4Cons::SetOuterRadiusMinusZ(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Cons::SetOuterRadiusMinusZ(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:80:10
  t11.method("SetOuterRadiusMinusZ", [](G4Cons& a, G4double arg0)->void{ a.SetOuterRadiusMinusZ(arg0); });
  t11.method("SetOuterRadiusMinusZ", [](G4Cons* a, G4double arg0)->void{ a->SetOuterRadiusMinusZ(arg0); });

  DEBUG_MSG("Adding wrapper for void G4Cons::SetInnerRadiusPlusZ(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Cons::SetInnerRadiusPlusZ(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:81:10
  t11.method("SetInnerRadiusPlusZ", [](G4Cons& a, G4double arg0)->void{ a.SetInnerRadiusPlusZ(arg0); });
  t11.method("SetInnerRadiusPlusZ", [](G4Cons* a, G4double arg0)->void{ a->SetInnerRadiusPlusZ(arg0); });

  DEBUG_MSG("Adding wrapper for void G4Cons::SetOuterRadiusPlusZ(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Cons::SetOuterRadiusPlusZ(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:82:10
  t11.method("SetOuterRadiusPlusZ", [](G4Cons& a, G4double arg0)->void{ a.SetOuterRadiusPlusZ(arg0); });
  t11.method("SetOuterRadiusPlusZ", [](G4Cons* a, G4double arg0)->void{ a->SetOuterRadiusPlusZ(arg0); });

  DEBUG_MSG("Adding wrapper for void G4Cons::SetZHalfLength(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Cons::SetZHalfLength(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:83:10
  t11.method("SetZHalfLength", [](G4Cons& a, G4double arg0)->void{ a.SetZHalfLength(arg0); });
  t11.method("SetZHalfLength", [](G4Cons* a, G4double arg0)->void{ a->SetZHalfLength(arg0); });

  DEBUG_MSG("Adding wrapper for void G4Cons::SetStartPhiAngle(G4double, G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4Cons::SetStartPhiAngle(G4double, G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:84:10
  t11.method("SetStartPhiAngle", [](G4Cons& a, G4double arg0)->void{ a.SetStartPhiAngle(arg0); });
  t11.method("SetStartPhiAngle", [](G4Cons& a, G4double arg0, G4bool arg1)->void{ a.SetStartPhiAngle(arg0, arg1); });
  t11.method("SetStartPhiAngle", [](G4Cons* a, G4double arg0)->void{ a->SetStartPhiAngle(arg0); });
  t11.method("SetStartPhiAngle", [](G4Cons* a, G4double arg0, G4bool arg1)->void{ a->SetStartPhiAngle(arg0, arg1); });

  DEBUG_MSG("Adding wrapper for void G4Cons::SetDeltaPhiAngle(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Cons::SetDeltaPhiAngle(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:85:10
  t11.method("SetDeltaPhiAngle", [](G4Cons& a, G4double arg0)->void{ a.SetDeltaPhiAngle(arg0); });
  t11.method("SetDeltaPhiAngle", [](G4Cons* a, G4double arg0)->void{ a->SetDeltaPhiAngle(arg0); });

  DEBUG_MSG("Adding wrapper for G4GeometryType G4Cons::GetEntityType() (" __HERE__ ")");
  // signature to use in the veto list: G4GeometryType G4Cons::GetEntityType()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:87:27
  t11.method("GetEntityType", [](G4Cons const& a)->G4GeometryType{ return a.GetEntityType(); });
  t11.method("GetEntityType", [](G4Cons const* a)->G4GeometryType{ return a->GetEntityType(); });

  DEBUG_MSG("Adding wrapper for void G4Cons::BoundingLimits(G4ThreeVector &, G4ThreeVector &) (" __HERE__ ")");
  // signature to use in the veto list: void G4Cons::BoundingLimits(G4ThreeVector &, G4ThreeVector &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:89:10
  t11.method("BoundingLimits", [](G4Cons const& a, G4ThreeVector & arg0, G4ThreeVector & arg1)->void{ a.BoundingLimits(arg0, arg1); });
  t11.method("BoundingLimits", [](G4Cons const* a, G4ThreeVector & arg0, G4ThreeVector & arg1)->void{ a->BoundingLimits(arg0, arg1); });

  DEBUG_MSG("Adding wrapper for G4bool G4Cons::CalculateExtent(const EAxis, const G4VoxelLimits &, const G4AffineTransform &, G4double &, G4double &) (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4Cons::CalculateExtent(const EAxis, const G4VoxelLimits &, const G4AffineTransform &, G4double &, G4double &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:91:12
  t11.method("CalculateExtent", [](G4Cons const& a, const EAxis arg0, const G4VoxelLimits & arg1, const G4AffineTransform & arg2, G4double & arg3, G4double & arg4)->G4bool{ return a.CalculateExtent(arg0, arg1, arg2, arg3, arg4); });
  t11.method("CalculateExtent", [](G4Cons const* a, const EAxis arg0, const G4VoxelLimits & arg1, const G4AffineTransform & arg2, G4double & arg3, G4double & arg4)->G4bool{ return a->CalculateExtent(arg0, arg1, arg2, arg3, arg4); });

  DEBUG_MSG("Adding wrapper for G4Polyhedron * G4Cons::CreatePolyhedron() (" __HERE__ ")");
  // signature to use in the veto list: G4Polyhedron * G4Cons::CreatePolyhedron()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:96:19
  t11.method("CreatePolyhedron", [](G4Cons const& a)->G4Polyhedron *{ return a.CreatePolyhedron(); });
  t11.method("CreatePolyhedron", [](G4Cons const* a)->G4Polyhedron *{ return a->CreatePolyhedron(); });


  DEBUG_MSG("Adding wrapper for void G4Cons::G4Cons(const G4Cons &) (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:105:5
  t11.constructor<const G4Cons &>();

  DEBUG_MSG("Adding wrapper for G4Cons & G4Cons::operator=(const G4Cons &) (" __HERE__ ")");
  // signature to use in the veto list: G4Cons & G4Cons::operator=(const G4Cons &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UCons.hh:106:14
  t11.method("assign", [](G4Cons& a, const G4Cons & arg0)->G4Cons &{ return a.operator=(arg0); });
  t11.method("assign", [](G4Cons* a, const G4Cons & arg0)->G4Cons &{ return a->operator=(arg0); });

  /* End of G4Cons class method wrappers
   **********************************************************************/


  /**********************************************************************/
  /* Wrappers for the methods of class G4Orb
   */


  DEBUG_MSG("Adding wrapper for void G4Orb::G4Orb(const G4String &, G4double) (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UOrb.hh:52:5
  t12.constructor<const G4String &, G4double>();

  DEBUG_MSG("Adding wrapper for void G4Orb::ComputeDimensions(G4VPVParameterisation *, const G4int, const G4VPhysicalVolume *) (" __HERE__ ")");
  // signature to use in the veto list: void G4Orb::ComputeDimensions(G4VPVParameterisation *, const G4int, const G4VPhysicalVolume *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UOrb.hh:56:10
  t12.method("ComputeDimensions", [](G4Orb& a, G4VPVParameterisation * arg0, const G4int arg1, const G4VPhysicalVolume * arg2)->void{ a.ComputeDimensions(arg0, arg1, arg2); });
  t12.method("ComputeDimensions", [](G4Orb* a, G4VPVParameterisation * arg0, const G4int arg1, const G4VPhysicalVolume * arg2)->void{ a->ComputeDimensions(arg0, arg1, arg2); });

  DEBUG_MSG("Adding wrapper for G4VSolid * G4Orb::Clone() (" __HERE__ ")");
  // signature to use in the veto list: G4VSolid * G4Orb::Clone()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UOrb.hh:60:15
  t12.method("Clone", [](G4Orb const& a)->G4VSolid *{ return a.Clone(); });
  t12.method("Clone", [](G4Orb const* a)->G4VSolid *{ return a->Clone(); });

  DEBUG_MSG("Adding wrapper for G4double G4Orb::GetRadius() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Orb::GetRadius()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UOrb.hh:62:14
  t12.method("GetRadius", [](G4Orb const& a)->G4double{ return a.GetRadius(); });
  t12.method("GetRadius", [](G4Orb const* a)->G4double{ return a->GetRadius(); });

  DEBUG_MSG("Adding wrapper for void G4Orb::SetRadius(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Orb::SetRadius(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UOrb.hh:63:10
  t12.method("SetRadius", [](G4Orb& a, G4double arg0)->void{ a.SetRadius(arg0); });
  t12.method("SetRadius", [](G4Orb* a, G4double arg0)->void{ a->SetRadius(arg0); });

  DEBUG_MSG("Adding wrapper for G4double G4Orb::GetRadialTolerance() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Orb::GetRadialTolerance()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UOrb.hh:64:14
  t12.method("GetRadialTolerance", [](G4Orb const& a)->G4double{ return a.GetRadialTolerance(); });
  t12.method("GetRadialTolerance", [](G4Orb const* a)->G4double{ return a->GetRadialTolerance(); });

  DEBUG_MSG("Adding wrapper for G4GeometryType G4Orb::GetEntityType() (" __HERE__ ")");
  // signature to use in the veto list: G4GeometryType G4Orb::GetEntityType()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UOrb.hh:66:27
  t12.method("GetEntityType", [](G4Orb const& a)->G4GeometryType{ return a.GetEntityType(); });
  t12.method("GetEntityType", [](G4Orb const* a)->G4GeometryType{ return a->GetEntityType(); });

  DEBUG_MSG("Adding wrapper for void G4Orb::BoundingLimits(G4ThreeVector &, G4ThreeVector &) (" __HERE__ ")");
  // signature to use in the veto list: void G4Orb::BoundingLimits(G4ThreeVector &, G4ThreeVector &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UOrb.hh:68:10
  t12.method("BoundingLimits", [](G4Orb const& a, G4ThreeVector & arg0, G4ThreeVector & arg1)->void{ a.BoundingLimits(arg0, arg1); });
  t12.method("BoundingLimits", [](G4Orb const* a, G4ThreeVector & arg0, G4ThreeVector & arg1)->void{ a->BoundingLimits(arg0, arg1); });

  DEBUG_MSG("Adding wrapper for G4bool G4Orb::CalculateExtent(const EAxis, const G4VoxelLimits &, const G4AffineTransform &, G4double &, G4double &) (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4Orb::CalculateExtent(const EAxis, const G4VoxelLimits &, const G4AffineTransform &, G4double &, G4double &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UOrb.hh:70:12
  t12.method("CalculateExtent", [](G4Orb const& a, const EAxis arg0, const G4VoxelLimits & arg1, const G4AffineTransform & arg2, G4double & arg3, G4double & arg4)->G4bool{ return a.CalculateExtent(arg0, arg1, arg2, arg3, arg4); });
  t12.method("CalculateExtent", [](G4Orb const* a, const EAxis arg0, const G4VoxelLimits & arg1, const G4AffineTransform & arg2, G4double & arg3, G4double & arg4)->G4bool{ return a->CalculateExtent(arg0, arg1, arg2, arg3, arg4); });

  DEBUG_MSG("Adding wrapper for G4Polyhedron * G4Orb::CreatePolyhedron() (" __HERE__ ")");
  // signature to use in the veto list: G4Polyhedron * G4Orb::CreatePolyhedron()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UOrb.hh:75:19
  t12.method("CreatePolyhedron", [](G4Orb const& a)->G4Polyhedron *{ return a.CreatePolyhedron(); });
  t12.method("CreatePolyhedron", [](G4Orb const* a)->G4Polyhedron *{ return a->CreatePolyhedron(); });


  DEBUG_MSG("Adding wrapper for void G4Orb::G4Orb(const G4Orb &) (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UOrb.hh:84:5
  t12.constructor<const G4Orb &>();

  DEBUG_MSG("Adding wrapper for G4Orb & G4Orb::operator=(const G4Orb &) (" __HERE__ ")");
  // signature to use in the veto list: G4Orb & G4Orb::operator=(const G4Orb &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UOrb.hh:85:13
  t12.method("assign", [](G4Orb& a, const G4Orb & arg0)->G4Orb &{ return a.operator=(arg0); });
  t12.method("assign", [](G4Orb* a, const G4Orb & arg0)->G4Orb &{ return a->operator=(arg0); });

  /* End of G4Orb class method wrappers
   **********************************************************************/


  /**********************************************************************/
  /* Wrappers for the methods of class G4Sphere
   */


  DEBUG_MSG("Adding wrapper for void G4Sphere::G4Sphere(const G4String &, G4double, G4double, G4double, G4double, G4double, G4double) (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:52:5
  t13.constructor<const G4String &, G4double, G4double, G4double, G4double, G4double, G4double>();

  DEBUG_MSG("Adding wrapper for void G4Sphere::ComputeDimensions(G4VPVParameterisation *, const G4int, const G4VPhysicalVolume *) (" __HERE__ ")");
  // signature to use in the veto list: void G4Sphere::ComputeDimensions(G4VPVParameterisation *, const G4int, const G4VPhysicalVolume *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:61:10
  t13.method("ComputeDimensions", [](G4Sphere& a, G4VPVParameterisation * arg0, const G4int arg1, const G4VPhysicalVolume * arg2)->void{ a.ComputeDimensions(arg0, arg1, arg2); });
  t13.method("ComputeDimensions", [](G4Sphere* a, G4VPVParameterisation * arg0, const G4int arg1, const G4VPhysicalVolume * arg2)->void{ a->ComputeDimensions(arg0, arg1, arg2); });

  DEBUG_MSG("Adding wrapper for G4VSolid * G4Sphere::Clone() (" __HERE__ ")");
  // signature to use in the veto list: G4VSolid * G4Sphere::Clone()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:65:15
  t13.method("Clone", [](G4Sphere const& a)->G4VSolid *{ return a.Clone(); });
  t13.method("Clone", [](G4Sphere const* a)->G4VSolid *{ return a->Clone(); });

  DEBUG_MSG("Adding wrapper for G4double G4Sphere::GetInnerRadius() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Sphere::GetInnerRadius()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:67:14
  t13.method("GetInnerRadius", [](G4Sphere const& a)->G4double{ return a.GetInnerRadius(); });
  t13.method("GetInnerRadius", [](G4Sphere const* a)->G4double{ return a->GetInnerRadius(); });

  DEBUG_MSG("Adding wrapper for G4double G4Sphere::GetOuterRadius() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Sphere::GetOuterRadius()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:68:14
  t13.method("GetOuterRadius", [](G4Sphere const& a)->G4double{ return a.GetOuterRadius(); });
  t13.method("GetOuterRadius", [](G4Sphere const* a)->G4double{ return a->GetOuterRadius(); });

  DEBUG_MSG("Adding wrapper for G4double G4Sphere::GetStartPhiAngle() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Sphere::GetStartPhiAngle()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:69:14
  t13.method("GetStartPhiAngle", [](G4Sphere const& a)->G4double{ return a.GetStartPhiAngle(); });
  t13.method("GetStartPhiAngle", [](G4Sphere const* a)->G4double{ return a->GetStartPhiAngle(); });

  DEBUG_MSG("Adding wrapper for G4double G4Sphere::GetDeltaPhiAngle() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Sphere::GetDeltaPhiAngle()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:70:14
  t13.method("GetDeltaPhiAngle", [](G4Sphere const& a)->G4double{ return a.GetDeltaPhiAngle(); });
  t13.method("GetDeltaPhiAngle", [](G4Sphere const* a)->G4double{ return a->GetDeltaPhiAngle(); });

  DEBUG_MSG("Adding wrapper for G4double G4Sphere::GetStartThetaAngle() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Sphere::GetStartThetaAngle()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:71:14
  t13.method("GetStartThetaAngle", [](G4Sphere const& a)->G4double{ return a.GetStartThetaAngle(); });
  t13.method("GetStartThetaAngle", [](G4Sphere const* a)->G4double{ return a->GetStartThetaAngle(); });

  DEBUG_MSG("Adding wrapper for G4double G4Sphere::GetDeltaThetaAngle() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Sphere::GetDeltaThetaAngle()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:72:14
  t13.method("GetDeltaThetaAngle", [](G4Sphere const& a)->G4double{ return a.GetDeltaThetaAngle(); });
  t13.method("GetDeltaThetaAngle", [](G4Sphere const* a)->G4double{ return a->GetDeltaThetaAngle(); });

  DEBUG_MSG("Adding wrapper for G4double G4Sphere::GetSinStartPhi() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Sphere::GetSinStartPhi()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:73:14
  t13.method("GetSinStartPhi", [](G4Sphere const& a)->G4double{ return a.GetSinStartPhi(); });
  t13.method("GetSinStartPhi", [](G4Sphere const* a)->G4double{ return a->GetSinStartPhi(); });

  DEBUG_MSG("Adding wrapper for G4double G4Sphere::GetCosStartPhi() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Sphere::GetCosStartPhi()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:74:14
  t13.method("GetCosStartPhi", [](G4Sphere const& a)->G4double{ return a.GetCosStartPhi(); });
  t13.method("GetCosStartPhi", [](G4Sphere const* a)->G4double{ return a->GetCosStartPhi(); });

  DEBUG_MSG("Adding wrapper for G4double G4Sphere::GetSinEndPhi() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Sphere::GetSinEndPhi()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:75:14
  t13.method("GetSinEndPhi", [](G4Sphere const& a)->G4double{ return a.GetSinEndPhi(); });
  t13.method("GetSinEndPhi", [](G4Sphere const* a)->G4double{ return a->GetSinEndPhi(); });

  DEBUG_MSG("Adding wrapper for G4double G4Sphere::GetCosEndPhi() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Sphere::GetCosEndPhi()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:76:14
  t13.method("GetCosEndPhi", [](G4Sphere const& a)->G4double{ return a.GetCosEndPhi(); });
  t13.method("GetCosEndPhi", [](G4Sphere const* a)->G4double{ return a->GetCosEndPhi(); });

  DEBUG_MSG("Adding wrapper for G4double G4Sphere::GetSinStartTheta() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Sphere::GetSinStartTheta()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:77:14
  t13.method("GetSinStartTheta", [](G4Sphere const& a)->G4double{ return a.GetSinStartTheta(); });
  t13.method("GetSinStartTheta", [](G4Sphere const* a)->G4double{ return a->GetSinStartTheta(); });

  DEBUG_MSG("Adding wrapper for G4double G4Sphere::GetCosStartTheta() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Sphere::GetCosStartTheta()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:78:14
  t13.method("GetCosStartTheta", [](G4Sphere const& a)->G4double{ return a.GetCosStartTheta(); });
  t13.method("GetCosStartTheta", [](G4Sphere const* a)->G4double{ return a->GetCosStartTheta(); });

  DEBUG_MSG("Adding wrapper for G4double G4Sphere::GetSinEndTheta() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Sphere::GetSinEndTheta()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:79:14
  t13.method("GetSinEndTheta", [](G4Sphere const& a)->G4double{ return a.GetSinEndTheta(); });
  t13.method("GetSinEndTheta", [](G4Sphere const* a)->G4double{ return a->GetSinEndTheta(); });

  DEBUG_MSG("Adding wrapper for G4double G4Sphere::GetCosEndTheta() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Sphere::GetCosEndTheta()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:80:14
  t13.method("GetCosEndTheta", [](G4Sphere const& a)->G4double{ return a.GetCosEndTheta(); });
  t13.method("GetCosEndTheta", [](G4Sphere const* a)->G4double{ return a->GetCosEndTheta(); });

  DEBUG_MSG("Adding wrapper for void G4Sphere::SetInnerRadius(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Sphere::SetInnerRadius(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:82:10
  t13.method("SetInnerRadius", [](G4Sphere& a, G4double arg0)->void{ a.SetInnerRadius(arg0); });
  t13.method("SetInnerRadius", [](G4Sphere* a, G4double arg0)->void{ a->SetInnerRadius(arg0); });

  DEBUG_MSG("Adding wrapper for void G4Sphere::SetOuterRadius(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Sphere::SetOuterRadius(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:83:10
  t13.method("SetOuterRadius", [](G4Sphere& a, G4double arg0)->void{ a.SetOuterRadius(arg0); });
  t13.method("SetOuterRadius", [](G4Sphere* a, G4double arg0)->void{ a->SetOuterRadius(arg0); });

  DEBUG_MSG("Adding wrapper for void G4Sphere::SetStartPhiAngle(G4double, G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4Sphere::SetStartPhiAngle(G4double, G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:84:10
  t13.method("SetStartPhiAngle", [](G4Sphere& a, G4double arg0)->void{ a.SetStartPhiAngle(arg0); });
  t13.method("SetStartPhiAngle", [](G4Sphere& a, G4double arg0, G4bool arg1)->void{ a.SetStartPhiAngle(arg0, arg1); });
  t13.method("SetStartPhiAngle", [](G4Sphere* a, G4double arg0)->void{ a->SetStartPhiAngle(arg0); });
  t13.method("SetStartPhiAngle", [](G4Sphere* a, G4double arg0, G4bool arg1)->void{ a->SetStartPhiAngle(arg0, arg1); });

  DEBUG_MSG("Adding wrapper for void G4Sphere::SetDeltaPhiAngle(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Sphere::SetDeltaPhiAngle(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:85:10
  t13.method("SetDeltaPhiAngle", [](G4Sphere& a, G4double arg0)->void{ a.SetDeltaPhiAngle(arg0); });
  t13.method("SetDeltaPhiAngle", [](G4Sphere* a, G4double arg0)->void{ a->SetDeltaPhiAngle(arg0); });

  DEBUG_MSG("Adding wrapper for void G4Sphere::SetStartThetaAngle(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Sphere::SetStartThetaAngle(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:86:10
  t13.method("SetStartThetaAngle", [](G4Sphere& a, G4double arg0)->void{ a.SetStartThetaAngle(arg0); });
  t13.method("SetStartThetaAngle", [](G4Sphere* a, G4double arg0)->void{ a->SetStartThetaAngle(arg0); });

  DEBUG_MSG("Adding wrapper for void G4Sphere::SetDeltaThetaAngle(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Sphere::SetDeltaThetaAngle(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:87:10
  t13.method("SetDeltaThetaAngle", [](G4Sphere& a, G4double arg0)->void{ a.SetDeltaThetaAngle(arg0); });
  t13.method("SetDeltaThetaAngle", [](G4Sphere* a, G4double arg0)->void{ a->SetDeltaThetaAngle(arg0); });

  DEBUG_MSG("Adding wrapper for G4GeometryType G4Sphere::GetEntityType() (" __HERE__ ")");
  // signature to use in the veto list: G4GeometryType G4Sphere::GetEntityType()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:89:27
  t13.method("GetEntityType", [](G4Sphere const& a)->G4GeometryType{ return a.GetEntityType(); });
  t13.method("GetEntityType", [](G4Sphere const* a)->G4GeometryType{ return a->GetEntityType(); });

  DEBUG_MSG("Adding wrapper for void G4Sphere::BoundingLimits(G4ThreeVector &, G4ThreeVector &) (" __HERE__ ")");
  // signature to use in the veto list: void G4Sphere::BoundingLimits(G4ThreeVector &, G4ThreeVector &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:91:10
  t13.method("BoundingLimits", [](G4Sphere const& a, G4ThreeVector & arg0, G4ThreeVector & arg1)->void{ a.BoundingLimits(arg0, arg1); });
  t13.method("BoundingLimits", [](G4Sphere const* a, G4ThreeVector & arg0, G4ThreeVector & arg1)->void{ a->BoundingLimits(arg0, arg1); });

  DEBUG_MSG("Adding wrapper for G4bool G4Sphere::CalculateExtent(const EAxis, const G4VoxelLimits &, const G4AffineTransform &, G4double &, G4double &) (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4Sphere::CalculateExtent(const EAxis, const G4VoxelLimits &, const G4AffineTransform &, G4double &, G4double &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:93:12
  t13.method("CalculateExtent", [](G4Sphere const& a, const EAxis arg0, const G4VoxelLimits & arg1, const G4AffineTransform & arg2, G4double & arg3, G4double & arg4)->G4bool{ return a.CalculateExtent(arg0, arg1, arg2, arg3, arg4); });
  t13.method("CalculateExtent", [](G4Sphere const* a, const EAxis arg0, const G4VoxelLimits & arg1, const G4AffineTransform & arg2, G4double & arg3, G4double & arg4)->G4bool{ return a->CalculateExtent(arg0, arg1, arg2, arg3, arg4); });

  DEBUG_MSG("Adding wrapper for G4Polyhedron * G4Sphere::CreatePolyhedron() (" __HERE__ ")");
  // signature to use in the veto list: G4Polyhedron * G4Sphere::CreatePolyhedron()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:98:19
  t13.method("CreatePolyhedron", [](G4Sphere const& a)->G4Polyhedron *{ return a.CreatePolyhedron(); });
  t13.method("CreatePolyhedron", [](G4Sphere const* a)->G4Polyhedron *{ return a->CreatePolyhedron(); });


  DEBUG_MSG("Adding wrapper for void G4Sphere::G4Sphere(const G4Sphere &) (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:108:5
  t13.constructor<const G4Sphere &>();

  DEBUG_MSG("Adding wrapper for G4Sphere & G4Sphere::operator=(const G4Sphere &) (" __HERE__ ")");
  // signature to use in the veto list: G4Sphere & G4Sphere::operator=(const G4Sphere &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4USphere.hh:109:16
  t13.method("assign", [](G4Sphere& a, const G4Sphere & arg0)->G4Sphere &{ return a.operator=(arg0); });
  t13.method("assign", [](G4Sphere* a, const G4Sphere & arg0)->G4Sphere &{ return a->operator=(arg0); });

  /* End of G4Sphere class method wrappers
   **********************************************************************/


  /**********************************************************************/
  /* Wrappers for the methods of class G4Trd
   */


  DEBUG_MSG("Adding wrapper for void G4Trd::G4Trd(const G4String &, G4double, G4double, G4double, G4double, G4double) (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:52:5
  t14.constructor<const G4String &, G4double, G4double, G4double, G4double, G4double>();

  DEBUG_MSG("Adding wrapper for void G4Trd::ComputeDimensions(G4VPVParameterisation *, const G4int, const G4VPhysicalVolume *) (" __HERE__ ")");
  // signature to use in the veto list: void G4Trd::ComputeDimensions(G4VPVParameterisation *, const G4int, const G4VPhysicalVolume *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:60:10
  t14.method("ComputeDimensions", [](G4Trd& a, G4VPVParameterisation * arg0, const G4int arg1, const G4VPhysicalVolume * arg2)->void{ a.ComputeDimensions(arg0, arg1, arg2); });
  t14.method("ComputeDimensions", [](G4Trd* a, G4VPVParameterisation * arg0, const G4int arg1, const G4VPhysicalVolume * arg2)->void{ a->ComputeDimensions(arg0, arg1, arg2); });

  DEBUG_MSG("Adding wrapper for G4VSolid * G4Trd::Clone() (" __HERE__ ")");
  // signature to use in the veto list: G4VSolid * G4Trd::Clone()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:64:15
  t14.method("Clone", [](G4Trd const& a)->G4VSolid *{ return a.Clone(); });
  t14.method("Clone", [](G4Trd const* a)->G4VSolid *{ return a->Clone(); });

  DEBUG_MSG("Adding wrapper for G4double G4Trd::GetXHalfLength1() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Trd::GetXHalfLength1()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:66:14
  t14.method("GetXHalfLength1", [](G4Trd const& a)->G4double{ return a.GetXHalfLength1(); });
  t14.method("GetXHalfLength1", [](G4Trd const* a)->G4double{ return a->GetXHalfLength1(); });

  DEBUG_MSG("Adding wrapper for G4double G4Trd::GetXHalfLength2() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Trd::GetXHalfLength2()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:67:14
  t14.method("GetXHalfLength2", [](G4Trd const& a)->G4double{ return a.GetXHalfLength2(); });
  t14.method("GetXHalfLength2", [](G4Trd const* a)->G4double{ return a->GetXHalfLength2(); });

  DEBUG_MSG("Adding wrapper for G4double G4Trd::GetYHalfLength1() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Trd::GetYHalfLength1()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:68:14
  t14.method("GetYHalfLength1", [](G4Trd const& a)->G4double{ return a.GetYHalfLength1(); });
  t14.method("GetYHalfLength1", [](G4Trd const* a)->G4double{ return a->GetYHalfLength1(); });

  DEBUG_MSG("Adding wrapper for G4double G4Trd::GetYHalfLength2() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Trd::GetYHalfLength2()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:69:14
  t14.method("GetYHalfLength2", [](G4Trd const& a)->G4double{ return a.GetYHalfLength2(); });
  t14.method("GetYHalfLength2", [](G4Trd const* a)->G4double{ return a->GetYHalfLength2(); });

  DEBUG_MSG("Adding wrapper for G4double G4Trd::GetZHalfLength() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4Trd::GetZHalfLength()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:70:14
  t14.method("GetZHalfLength", [](G4Trd const& a)->G4double{ return a.GetZHalfLength(); });
  t14.method("GetZHalfLength", [](G4Trd const* a)->G4double{ return a->GetZHalfLength(); });

  DEBUG_MSG("Adding wrapper for void G4Trd::SetXHalfLength1(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Trd::SetXHalfLength1(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:72:10
  t14.method("SetXHalfLength1", [](G4Trd& a, G4double arg0)->void{ a.SetXHalfLength1(arg0); });
  t14.method("SetXHalfLength1", [](G4Trd* a, G4double arg0)->void{ a->SetXHalfLength1(arg0); });

  DEBUG_MSG("Adding wrapper for void G4Trd::SetXHalfLength2(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Trd::SetXHalfLength2(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:73:10
  t14.method("SetXHalfLength2", [](G4Trd& a, G4double arg0)->void{ a.SetXHalfLength2(arg0); });
  t14.method("SetXHalfLength2", [](G4Trd* a, G4double arg0)->void{ a->SetXHalfLength2(arg0); });

  DEBUG_MSG("Adding wrapper for void G4Trd::SetYHalfLength1(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Trd::SetYHalfLength1(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:74:10
  t14.method("SetYHalfLength1", [](G4Trd& a, G4double arg0)->void{ a.SetYHalfLength1(arg0); });
  t14.method("SetYHalfLength1", [](G4Trd* a, G4double arg0)->void{ a->SetYHalfLength1(arg0); });

  DEBUG_MSG("Adding wrapper for void G4Trd::SetYHalfLength2(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Trd::SetYHalfLength2(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:75:10
  t14.method("SetYHalfLength2", [](G4Trd& a, G4double arg0)->void{ a.SetYHalfLength2(arg0); });
  t14.method("SetYHalfLength2", [](G4Trd* a, G4double arg0)->void{ a->SetYHalfLength2(arg0); });

  DEBUG_MSG("Adding wrapper for void G4Trd::SetZHalfLength(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Trd::SetZHalfLength(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:76:10
  t14.method("SetZHalfLength", [](G4Trd& a, G4double arg0)->void{ a.SetZHalfLength(arg0); });
  t14.method("SetZHalfLength", [](G4Trd* a, G4double arg0)->void{ a->SetZHalfLength(arg0); });

  DEBUG_MSG("Adding wrapper for void G4Trd::SetAllParameters(G4double, G4double, G4double, G4double, G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4Trd::SetAllParameters(G4double, G4double, G4double, G4double, G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:78:10
  t14.method("SetAllParameters", [](G4Trd& a, G4double arg0, G4double arg1, G4double arg2, G4double arg3, G4double arg4)->void{ a.SetAllParameters(arg0, arg1, arg2, arg3, arg4); });
  t14.method("SetAllParameters", [](G4Trd* a, G4double arg0, G4double arg1, G4double arg2, G4double arg3, G4double arg4)->void{ a->SetAllParameters(arg0, arg1, arg2, arg3, arg4); });

  DEBUG_MSG("Adding wrapper for G4GeometryType G4Trd::GetEntityType() (" __HERE__ ")");
  // signature to use in the veto list: G4GeometryType G4Trd::GetEntityType()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:81:27
  t14.method("GetEntityType", [](G4Trd const& a)->G4GeometryType{ return a.GetEntityType(); });
  t14.method("GetEntityType", [](G4Trd const* a)->G4GeometryType{ return a->GetEntityType(); });

  DEBUG_MSG("Adding wrapper for void G4Trd::BoundingLimits(G4ThreeVector &, G4ThreeVector &) (" __HERE__ ")");
  // signature to use in the veto list: void G4Trd::BoundingLimits(G4ThreeVector &, G4ThreeVector &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:83:10
  t14.method("BoundingLimits", [](G4Trd const& a, G4ThreeVector & arg0, G4ThreeVector & arg1)->void{ a.BoundingLimits(arg0, arg1); });
  t14.method("BoundingLimits", [](G4Trd const* a, G4ThreeVector & arg0, G4ThreeVector & arg1)->void{ a->BoundingLimits(arg0, arg1); });

  DEBUG_MSG("Adding wrapper for G4bool G4Trd::CalculateExtent(const EAxis, const G4VoxelLimits &, const G4AffineTransform &, G4double &, G4double &) (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4Trd::CalculateExtent(const EAxis, const G4VoxelLimits &, const G4AffineTransform &, G4double &, G4double &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:85:12
  t14.method("CalculateExtent", [](G4Trd const& a, const EAxis arg0, const G4VoxelLimits & arg1, const G4AffineTransform & arg2, G4double & arg3, G4double & arg4)->G4bool{ return a.CalculateExtent(arg0, arg1, arg2, arg3, arg4); });
  t14.method("CalculateExtent", [](G4Trd const* a, const EAxis arg0, const G4VoxelLimits & arg1, const G4AffineTransform & arg2, G4double & arg3, G4double & arg4)->G4bool{ return a->CalculateExtent(arg0, arg1, arg2, arg3, arg4); });

  DEBUG_MSG("Adding wrapper for G4Polyhedron * G4Trd::CreatePolyhedron() (" __HERE__ ")");
  // signature to use in the veto list: G4Polyhedron * G4Trd::CreatePolyhedron()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:90:19
  t14.method("CreatePolyhedron", [](G4Trd const& a)->G4Polyhedron *{ return a.CreatePolyhedron(); });
  t14.method("CreatePolyhedron", [](G4Trd const* a)->G4Polyhedron *{ return a->CreatePolyhedron(); });


  DEBUG_MSG("Adding wrapper for void G4Trd::G4Trd(const G4Trd &) (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:99:5
  t14.constructor<const G4Trd &>();

  DEBUG_MSG("Adding wrapper for G4Trd & G4Trd::operator=(const G4Trd &) (" __HERE__ ")");
  // signature to use in the veto list: G4Trd & G4Trd::operator=(const G4Trd &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UTrd.hh:100:13
  t14.method("assign", [](G4Trd& a, const G4Trd & arg0)->G4Trd &{ return a.operator=(arg0); });
  t14.method("assign", [](G4Trd* a, const G4Trd & arg0)->G4Trd &{ return a->operator=(arg0); });

  /* End of G4Trd class method wrappers
   **********************************************************************/


  /**********************************************************************/
  /* Wrappers for the methods of class G4LVData
   */


  DEBUG_MSG("Adding wrapper for void G4LVData::G4LVData() (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:134:5
  t15.constructor<>();

  DEBUG_MSG("Adding wrapper for void G4LVData::initialize() (" __HERE__ ")");
  // signature to use in the veto list: void G4LVData::initialize()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:135:10
  t15.method("initialize", [](G4LVData& a)->void{ a.initialize(); });
  t15.method("initialize", [](G4LVData* a)->void{ a->initialize(); });

  DEBUG_MSG("Adding fSolid methods  to provide read access to the field fSolid (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:147:15
  // signature to use in the veto list: G4LVData::fSolid
  t15.method("fSolid", [](const G4LVData& a) -> G4VSolid * { return a.fSolid; });
  t15.method("fSolid", [](G4LVData& a) -> G4VSolid * { return a.fSolid; });
  t15.method("fSolid", [](const G4LVData* a) -> G4VSolid * { return a->fSolid; });
  t15.method("fSolid", [](G4LVData* a) -> G4VSolid * { return a->fSolid; });
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:147:15
  // signature to use in the veto list: G4LVData::fSolid
  // with ! suffix to veto the setter only

  DEBUG_MSG("Adding fSolid! methods to provide write access to the field fSolid (" __HERE__ ")");
  t15.method("fSolid!", [](G4LVData& a, G4VSolid * val) -> G4VSolid * { return a.fSolid = val; });

  DEBUG_MSG("Adding fSolid! methods to provide write access to the field fSolid (" __HERE__ ")");
  t15.method("fSolid!", [](G4LVData* a, G4VSolid * val) -> G4VSolid * { return a->fSolid = val; });

  DEBUG_MSG("Adding fSensitiveDetector methods  to provide read access to the field fSensitiveDetector (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:149:27
  // signature to use in the veto list: G4LVData::fSensitiveDetector
  t15.method("fSensitiveDetector", [](const G4LVData& a) -> G4VSensitiveDetector * { return a.fSensitiveDetector; });
  t15.method("fSensitiveDetector", [](G4LVData& a) -> G4VSensitiveDetector * { return a.fSensitiveDetector; });
  t15.method("fSensitiveDetector", [](const G4LVData* a) -> G4VSensitiveDetector * { return a->fSensitiveDetector; });
  t15.method("fSensitiveDetector", [](G4LVData* a) -> G4VSensitiveDetector * { return a->fSensitiveDetector; });
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:149:27
  // signature to use in the veto list: G4LVData::fSensitiveDetector
  // with ! suffix to veto the setter only

  DEBUG_MSG("Adding fSensitiveDetector! methods to provide write access to the field fSensitiveDetector (" __HERE__ ")");
  t15.method("fSensitiveDetector!", [](G4LVData& a, G4VSensitiveDetector * val) -> G4VSensitiveDetector * { return a.fSensitiveDetector = val; });

  DEBUG_MSG("Adding fSensitiveDetector! methods to provide write access to the field fSensitiveDetector (" __HERE__ ")");
  t15.method("fSensitiveDetector!", [](G4LVData* a, G4VSensitiveDetector * val) -> G4VSensitiveDetector * { return a->fSensitiveDetector = val; });

  DEBUG_MSG("Adding fFieldManager methods  to provide read access to the field fFieldManager (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:151:21
  // signature to use in the veto list: G4LVData::fFieldManager
  t15.method("fFieldManager", [](const G4LVData& a) -> G4FieldManager * { return a.fFieldManager; });
  t15.method("fFieldManager", [](G4LVData& a) -> G4FieldManager * { return a.fFieldManager; });
  t15.method("fFieldManager", [](const G4LVData* a) -> G4FieldManager * { return a->fFieldManager; });
  t15.method("fFieldManager", [](G4LVData* a) -> G4FieldManager * { return a->fFieldManager; });
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:151:21
  // signature to use in the veto list: G4LVData::fFieldManager
  // with ! suffix to veto the setter only

  DEBUG_MSG("Adding fFieldManager! methods to provide write access to the field fFieldManager (" __HERE__ ")");
  t15.method("fFieldManager!", [](G4LVData& a, G4FieldManager * val) -> G4FieldManager * { return a.fFieldManager = val; });

  DEBUG_MSG("Adding fFieldManager! methods to provide write access to the field fFieldManager (" __HERE__ ")");
  t15.method("fFieldManager!", [](G4LVData* a, G4FieldManager * val) -> G4FieldManager * { return a->fFieldManager = val; });

  DEBUG_MSG("Adding fMaterial methods  to provide read access to the field fMaterial (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:153:17
  // signature to use in the veto list: G4LVData::fMaterial
  t15.method("fMaterial", [](const G4LVData& a) -> G4Material * { return a.fMaterial; });
  t15.method("fMaterial", [](G4LVData& a) -> G4Material * { return a.fMaterial; });
  t15.method("fMaterial", [](const G4LVData* a) -> G4Material * { return a->fMaterial; });
  t15.method("fMaterial", [](G4LVData* a) -> G4Material * { return a->fMaterial; });
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:153:17
  // signature to use in the veto list: G4LVData::fMaterial
  // with ! suffix to veto the setter only

  DEBUG_MSG("Adding fMaterial! methods to provide write access to the field fMaterial (" __HERE__ ")");
  t15.method("fMaterial!", [](G4LVData& a, G4Material * val) -> G4Material * { return a.fMaterial = val; });

  DEBUG_MSG("Adding fMaterial! methods to provide write access to the field fMaterial (" __HERE__ ")");
  t15.method("fMaterial!", [](G4LVData* a, G4Material * val) -> G4Material * { return a->fMaterial = val; });

  DEBUG_MSG("Adding fMass methods  to provide read access to the field fMass (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:155:14
  // signature to use in the veto list: G4LVData::fMass
  t15.method("fMass", [](const G4LVData& a) -> G4double { return a.fMass; });
  t15.method("fMass", [](G4LVData& a) -> G4double { return a.fMass; });
  t15.method("fMass", [](const G4LVData* a) -> G4double { return a->fMass; });
  t15.method("fMass", [](G4LVData* a) -> G4double { return a->fMass; });
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:155:14
  // signature to use in the veto list: G4LVData::fMass
  // with ! suffix to veto the setter only

  DEBUG_MSG("Adding fMass! methods to provide write access to the field fMass (" __HERE__ ")");
  t15.method("fMass!", [](G4LVData& a, G4double val) -> G4double { return a.fMass = val; });

  DEBUG_MSG("Adding fMass! methods to provide write access to the field fMass (" __HERE__ ")");
  t15.method("fMass!", [](G4LVData* a, G4double val) -> G4double { return a->fMass = val; });

  DEBUG_MSG("Adding fCutsCouple methods  to provide read access to the field fCutsCouple (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:157:27
  // signature to use in the veto list: G4LVData::fCutsCouple
  t15.method("fCutsCouple", [](const G4LVData& a) -> G4MaterialCutsCouple * { return a.fCutsCouple; });
  t15.method("fCutsCouple", [](G4LVData& a) -> G4MaterialCutsCouple * { return a.fCutsCouple; });
  t15.method("fCutsCouple", [](const G4LVData* a) -> G4MaterialCutsCouple * { return a->fCutsCouple; });
  t15.method("fCutsCouple", [](G4LVData* a) -> G4MaterialCutsCouple * { return a->fCutsCouple; });
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:157:27
  // signature to use in the veto list: G4LVData::fCutsCouple
  // with ! suffix to veto the setter only

  DEBUG_MSG("Adding fCutsCouple! methods to provide write access to the field fCutsCouple (" __HERE__ ")");
  t15.method("fCutsCouple!", [](G4LVData& a, G4MaterialCutsCouple * val) -> G4MaterialCutsCouple * { return a.fCutsCouple = val; });

  DEBUG_MSG("Adding fCutsCouple! methods to provide write access to the field fCutsCouple (" __HERE__ ")");
  t15.method("fCutsCouple!", [](G4LVData* a, G4MaterialCutsCouple * val) -> G4MaterialCutsCouple * { return a->fCutsCouple = val; });

  /* End of G4LVData class method wrappers
   **********************************************************************/


  /**********************************************************************/
  /* Wrappers for the methods of class G4LogicalVolume
   */

  DEBUG_MSG("Adding wrapper for const G4String & G4LogicalVolume::GetName() (" __HERE__ ")");
  // signature to use in the veto list: const G4String & G4LogicalVolume::GetName()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:208:28
  t17.method("GetName", [](G4LogicalVolume const& a)->const G4String &{ return a.GetName(); });
  t17.method("GetName", [](G4LogicalVolume const* a)->const G4String &{ return a->GetName(); });

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::SetName(const G4String &) (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::SetName(const G4String &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:209:10
  t17.method("SetName", [](G4LogicalVolume& a, const G4String & arg0)->void{ a.SetName(arg0); });
  t17.method("SetName", [](G4LogicalVolume* a, const G4String & arg0)->void{ a->SetName(arg0); });

  DEBUG_MSG("Adding wrapper for int G4LogicalVolume::GetNoDaughters() (" __HERE__ ")");
  // signature to use in the veto list: int G4LogicalVolume::GetNoDaughters()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:212:19
  t17.method("GetNoDaughters", [](G4LogicalVolume const& a)->int{ return a.GetNoDaughters(); });
  t17.method("GetNoDaughters", [](G4LogicalVolume const* a)->int{ return a->GetNoDaughters(); });

  DEBUG_MSG("Adding wrapper for G4VPhysicalVolume * G4LogicalVolume::GetDaughter(const G4int) (" __HERE__ ")");
  // signature to use in the veto list: G4VPhysicalVolume * G4LogicalVolume::GetDaughter(const G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:214:31
  t17.method("GetDaughter", [](G4LogicalVolume const& a, const G4int arg0)->G4VPhysicalVolume *{ return a.GetDaughter(arg0); });
  t17.method("GetDaughter", [](G4LogicalVolume const* a, const G4int arg0)->G4VPhysicalVolume *{ return a->GetDaughter(arg0); });

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::AddDaughter(G4VPhysicalVolume *) (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::AddDaughter(G4VPhysicalVolume *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:217:10
  t17.method("AddDaughter", [](G4LogicalVolume& a, G4VPhysicalVolume * arg0)->void{ a.AddDaughter(arg0); });
  t17.method("AddDaughter", [](G4LogicalVolume* a, G4VPhysicalVolume * arg0)->void{ a->AddDaughter(arg0); });

  DEBUG_MSG("Adding wrapper for G4bool G4LogicalVolume::IsDaughter(const G4VPhysicalVolume *) (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4LogicalVolume::IsDaughter(const G4VPhysicalVolume *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:219:19
  t17.method("IsDaughter", [](G4LogicalVolume const& a, const G4VPhysicalVolume * arg0)->G4bool{ return a.IsDaughter(arg0); });
  t17.method("IsDaughter", [](G4LogicalVolume const* a, const G4VPhysicalVolume * arg0)->G4bool{ return a->IsDaughter(arg0); });

  DEBUG_MSG("Adding wrapper for G4bool G4LogicalVolume::IsAncestor(const G4VPhysicalVolume *) (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4LogicalVolume::IsAncestor(const G4VPhysicalVolume *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:222:12
  t17.method("IsAncestor", [](G4LogicalVolume const& a, const G4VPhysicalVolume * arg0)->G4bool{ return a.IsAncestor(arg0); });
  t17.method("IsAncestor", [](G4LogicalVolume const* a, const G4VPhysicalVolume * arg0)->G4bool{ return a->IsAncestor(arg0); });

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::RemoveDaughter(const G4VPhysicalVolume *) (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::RemoveDaughter(const G4VPhysicalVolume *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:226:10
  t17.method("RemoveDaughter", [](G4LogicalVolume& a, const G4VPhysicalVolume * arg0)->void{ a.RemoveDaughter(arg0); });
  t17.method("RemoveDaughter", [](G4LogicalVolume* a, const G4VPhysicalVolume * arg0)->void{ a->RemoveDaughter(arg0); });

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::ClearDaughters() (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::ClearDaughters()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:229:10
  t17.method("ClearDaughters", [](G4LogicalVolume& a)->void{ a.ClearDaughters(); });
  t17.method("ClearDaughters", [](G4LogicalVolume* a)->void{ a->ClearDaughters(); });

  DEBUG_MSG("Adding wrapper for G4int G4LogicalVolume::TotalVolumeEntities() (" __HERE__ ")");
  // signature to use in the veto list: G4int G4LogicalVolume::TotalVolumeEntities()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:232:11
  t17.method("TotalVolumeEntities", [](G4LogicalVolume const& a)->G4int{ return a.TotalVolumeEntities(); });
  t17.method("TotalVolumeEntities", [](G4LogicalVolume const* a)->G4int{ return a->TotalVolumeEntities(); });

  DEBUG_MSG("Adding wrapper for EVolume G4LogicalVolume::CharacteriseDaughters() (" __HERE__ ")");
  // signature to use in the veto list: EVolume G4LogicalVolume::CharacteriseDaughters()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:235:20
  t17.method("CharacteriseDaughters", [](G4LogicalVolume const& a)->EVolume{ return a.CharacteriseDaughters(); });
  t17.method("CharacteriseDaughters", [](G4LogicalVolume const* a)->EVolume{ return a->CharacteriseDaughters(); });

  DEBUG_MSG("Adding wrapper for EVolume G4LogicalVolume::DeduceDaughtersType() (" __HERE__ ")");
  // signature to use in the veto list: EVolume G4LogicalVolume::DeduceDaughtersType()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:237:20
  t17.method("DeduceDaughtersType", [](G4LogicalVolume const& a)->EVolume{ return a.DeduceDaughtersType(); });
  t17.method("DeduceDaughtersType", [](G4LogicalVolume const* a)->EVolume{ return a->DeduceDaughtersType(); });

  DEBUG_MSG("Adding wrapper for G4VSolid * G4LogicalVolume::GetSolid() (" __HERE__ ")");
  // signature to use in the veto list: G4VSolid * G4LogicalVolume::GetSolid()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:240:15
  t17.method("GetSolid", [](G4LogicalVolume const& a)->G4VSolid *{ return a.GetSolid(); });
  t17.method("GetSolid", [](G4LogicalVolume const* a)->G4VSolid *{ return a->GetSolid(); });

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::SetSolid(G4VSolid *) (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::SetSolid(G4VSolid *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:241:10
  t17.method("SetSolid", [](G4LogicalVolume& a, G4VSolid * arg0)->void{ a.SetSolid(arg0); });
  t17.method("SetSolid", [](G4LogicalVolume* a, G4VSolid * arg0)->void{ a->SetSolid(arg0); });

  DEBUG_MSG("Adding wrapper for G4Material * G4LogicalVolume::GetMaterial() (" __HERE__ ")");
  // signature to use in the veto list: G4Material * G4LogicalVolume::GetMaterial()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:244:17
  t17.method("GetMaterial", [](G4LogicalVolume const& a)->G4Material *{ return a.GetMaterial(); });
  t17.method("GetMaterial", [](G4LogicalVolume const* a)->G4Material *{ return a->GetMaterial(); });

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::SetMaterial(G4Material *) (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::SetMaterial(G4Material *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:245:10
  t17.method("SetMaterial", [](G4LogicalVolume& a, G4Material * arg0)->void{ a.SetMaterial(arg0); });
  t17.method("SetMaterial", [](G4LogicalVolume* a, G4Material * arg0)->void{ a->SetMaterial(arg0); });

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::UpdateMaterial(G4Material *) (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::UpdateMaterial(G4Material *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:247:10
  t17.method("UpdateMaterial", [](G4LogicalVolume& a, G4Material * arg0)->void{ a.UpdateMaterial(arg0); });
  t17.method("UpdateMaterial", [](G4LogicalVolume* a, G4Material * arg0)->void{ a->UpdateMaterial(arg0); });

  DEBUG_MSG("Adding wrapper for G4double G4LogicalVolume::GetMass(G4bool, G4bool, G4Material *) (" __HERE__ ")");
  // signature to use in the veto list: G4double G4LogicalVolume::GetMass(G4bool, G4bool, G4Material *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:251:14
  t17.method("GetMass", [](G4LogicalVolume& a)->G4double{ return a.GetMass(); });
  t17.method("GetMass", [](G4LogicalVolume& a, G4bool arg0)->G4double{ return a.GetMass(arg0); });
  t17.method("GetMass", [](G4LogicalVolume& a, G4bool arg0, G4bool arg1)->G4double{ return a.GetMass(arg0, arg1); });
  t17.method("GetMass", [](G4LogicalVolume& a, G4bool arg0, G4bool arg1, G4Material * arg2)->G4double{ return a.GetMass(arg0, arg1, arg2); });
  t17.method("GetMass", [](G4LogicalVolume* a)->G4double{ return a->GetMass(); });
  t17.method("GetMass", [](G4LogicalVolume* a, G4bool arg0)->G4double{ return a->GetMass(arg0); });
  t17.method("GetMass", [](G4LogicalVolume* a, G4bool arg0, G4bool arg1)->G4double{ return a->GetMass(arg0, arg1); });
  t17.method("GetMass", [](G4LogicalVolume* a, G4bool arg0, G4bool arg1, G4Material * arg2)->G4double{ return a->GetMass(arg0, arg1, arg2); });

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::ResetMass() (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::ResetMass()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:266:10
  t17.method("ResetMass", [](G4LogicalVolume& a)->void{ a.ResetMass(); });
  t17.method("ResetMass", [](G4LogicalVolume* a)->void{ a->ResetMass(); });

  DEBUG_MSG("Adding wrapper for G4SmartVoxelHeader * G4LogicalVolume::GetVoxelHeader() (" __HERE__ ")");
  // signature to use in the veto list: G4SmartVoxelHeader * G4LogicalVolume::GetVoxelHeader()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:289:32
  t17.method("GetVoxelHeader", [](G4LogicalVolume const& a)->G4SmartVoxelHeader *{ return a.GetVoxelHeader(); });
  t17.method("GetVoxelHeader", [](G4LogicalVolume const* a)->G4SmartVoxelHeader *{ return a->GetVoxelHeader(); });

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::SetVoxelHeader(G4SmartVoxelHeader *) (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::SetVoxelHeader(G4SmartVoxelHeader *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:290:17
  t17.method("SetVoxelHeader", [](G4LogicalVolume& a, G4SmartVoxelHeader * arg0)->void{ a.SetVoxelHeader(arg0); });
  t17.method("SetVoxelHeader", [](G4LogicalVolume* a, G4SmartVoxelHeader * arg0)->void{ a->SetVoxelHeader(arg0); });

  DEBUG_MSG("Adding wrapper for G4double G4LogicalVolume::GetSmartless() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4LogicalVolume::GetSmartless()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:293:21
  t17.method("GetSmartless", [](G4LogicalVolume const& a)->G4double{ return a.GetSmartless(); });
  t17.method("GetSmartless", [](G4LogicalVolume const* a)->G4double{ return a->GetSmartless(); });

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::SetSmartless(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::SetSmartless(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:294:17
  t17.method("SetSmartless", [](G4LogicalVolume& a, G4double arg0)->void{ a.SetSmartless(arg0); });
  t17.method("SetSmartless", [](G4LogicalVolume* a, G4double arg0)->void{ a->SetSmartless(arg0); });

  DEBUG_MSG("Adding wrapper for G4bool G4LogicalVolume::IsToOptimise() (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4LogicalVolume::IsToOptimise()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:297:19
  t17.method("IsToOptimise", [](G4LogicalVolume const& a)->G4bool{ return a.IsToOptimise(); });
  t17.method("IsToOptimise", [](G4LogicalVolume const* a)->G4bool{ return a->IsToOptimise(); });

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::SetOptimisation(G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::SetOptimisation(G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:300:17
  t17.method("SetOptimisation", [](G4LogicalVolume& a, G4bool arg0)->void{ a.SetOptimisation(arg0); });
  t17.method("SetOptimisation", [](G4LogicalVolume* a, G4bool arg0)->void{ a->SetOptimisation(arg0); });

  DEBUG_MSG("Adding wrapper for G4bool G4LogicalVolume::IsRootRegion() (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4LogicalVolume::IsRootRegion()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:305:19
  t17.method("IsRootRegion", [](G4LogicalVolume const& a)->G4bool{ return a.IsRootRegion(); });
  t17.method("IsRootRegion", [](G4LogicalVolume const* a)->G4bool{ return a->IsRootRegion(); });

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::SetRegionRootFlag(G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::SetRegionRootFlag(G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:307:17
  t17.method("SetRegionRootFlag", [](G4LogicalVolume& a, G4bool arg0)->void{ a.SetRegionRootFlag(arg0); });
  t17.method("SetRegionRootFlag", [](G4LogicalVolume* a, G4bool arg0)->void{ a->SetRegionRootFlag(arg0); });

  DEBUG_MSG("Adding wrapper for G4bool G4LogicalVolume::IsRegion() (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4LogicalVolume::IsRegion()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:309:19
  t17.method("IsRegion", [](G4LogicalVolume const& a)->G4bool{ return a.IsRegion(); });
  t17.method("IsRegion", [](G4LogicalVolume const* a)->G4bool{ return a->IsRegion(); });

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::SetRegion(G4Region *) (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::SetRegion(G4Region *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:311:17
  t17.method("SetRegion", [](G4LogicalVolume& a, G4Region * arg0)->void{ a.SetRegion(arg0); });
  t17.method("SetRegion", [](G4LogicalVolume* a, G4Region * arg0)->void{ a->SetRegion(arg0); });

  DEBUG_MSG("Adding wrapper for G4Region * G4LogicalVolume::GetRegion() (" __HERE__ ")");
  // signature to use in the veto list: G4Region * G4LogicalVolume::GetRegion()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:313:22
  t17.method("GetRegion", [](G4LogicalVolume const& a)->G4Region *{ return a.GetRegion(); });
  t17.method("GetRegion", [](G4LogicalVolume const* a)->G4Region *{ return a->GetRegion(); });

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::PropagateRegion() (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::PropagateRegion()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:315:17
  t17.method("PropagateRegion", [](G4LogicalVolume& a)->void{ a.PropagateRegion(); });
  t17.method("PropagateRegion", [](G4LogicalVolume* a)->void{ a->PropagateRegion(); });
  types.set_override_module(jl_base_module);

  DEBUG_MSG("Adding wrapper for G4bool G4LogicalVolume::operator==(const G4LogicalVolume &) (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4LogicalVolume::operator==(const G4LogicalVolume &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:322:12
  t17.method("==", [](G4LogicalVolume const& a, const G4LogicalVolume & arg0)->G4bool{ return a.operator==(arg0); });
  t17.method("==", [](G4LogicalVolume const* a, const G4LogicalVolume & arg0)->G4bool{ return a->operator==(arg0); });

  types.unset_override_module();

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::SetBiasWeight(G4double) (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::SetBiasWeight(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:335:17
  t17.method("SetBiasWeight", [](G4LogicalVolume& a, G4double arg0)->void{ a.SetBiasWeight(arg0); });
  t17.method("SetBiasWeight", [](G4LogicalVolume* a, G4double arg0)->void{ a->SetBiasWeight(arg0); });

  DEBUG_MSG("Adding wrapper for G4double G4LogicalVolume::GetBiasWeight() (" __HERE__ ")");
  // signature to use in the veto list: G4double G4LogicalVolume::GetBiasWeight()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:336:21
  t17.method("GetBiasWeight", [](G4LogicalVolume const& a)->G4double{ return a.GetBiasWeight(); });
  t17.method("GetBiasWeight", [](G4LogicalVolume const* a)->G4double{ return a->GetBiasWeight(); });

  DEBUG_MSG("Adding wrapper for G4bool G4LogicalVolume::IsExtended() (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4LogicalVolume::IsExtended()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:346:20
  t17.method("IsExtended", [](G4LogicalVolume const& a)->G4bool{ return a.IsExtended(); });
  t17.method("IsExtended", [](G4LogicalVolume const* a)->G4bool{ return a->IsExtended(); });

  DEBUG_MSG("Adding wrapper for G4VSolid * G4LogicalVolume::GetMasterSolid() (" __HERE__ ")");
  // signature to use in the veto list: G4VSolid * G4LogicalVolume::GetMasterSolid()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:353:22
  t17.method("GetMasterSolid", [](G4LogicalVolume const& a)->G4VSolid *{ return a.GetMasterSolid(); });
  t17.method("GetMasterSolid", [](G4LogicalVolume const* a)->G4VSolid *{ return a->GetMasterSolid(); });

  DEBUG_MSG("Adding wrapper for G4int G4LogicalVolume::GetInstanceID() (" __HERE__ ")");
  // signature to use in the veto list: G4int G4LogicalVolume::GetInstanceID()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:356:18
  t17.method("GetInstanceID", [](G4LogicalVolume const& a)->G4int{ return a.GetInstanceID(); });
  t17.method("GetInstanceID", [](G4LogicalVolume const* a)->G4int{ return a->GetInstanceID(); });

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::Clean() (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::Clean()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:362:17
  t17.method("G4LogicalVolume!Clean", []()->void{ G4LogicalVolume::Clean(); });

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::Lock() (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::Lock()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:365:17
  t17.method("Lock", [](G4LogicalVolume& a)->void{ a.Lock(); });
  t17.method("Lock", [](G4LogicalVolume* a)->void{ a->Lock(); });

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::TerminateWorker(G4LogicalVolume *) (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::TerminateWorker(G4LogicalVolume *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:373:10
  t17.method("TerminateWorker", [](G4LogicalVolume& a, G4LogicalVolume * arg0)->void{ a.TerminateWorker(arg0); });
  t17.method("TerminateWorker", [](G4LogicalVolume* a, G4LogicalVolume * arg0)->void{ a->TerminateWorker(arg0); });

  DEBUG_MSG("Adding wrapper for G4VSolid * G4LogicalVolume::GetSolid(G4LVData &) (" __HERE__ ")");
  // signature to use in the veto list: G4VSolid * G4LogicalVolume::GetSolid(G4LVData &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:380:22
  t17.method("G4LogicalVolume!GetSolid", [](G4LVData & arg0)->G4VSolid *{ return G4LogicalVolume::GetSolid(arg0); });

  DEBUG_MSG("Adding wrapper for void G4LogicalVolume::SetSolid(G4LVData &, G4VSolid *) (" __HERE__ ")");
  // signature to use in the veto list: void G4LogicalVolume::SetSolid(G4LVData &, G4VSolid *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:381:17
  t17.method("G4LogicalVolume!SetSolid", [](G4LVData & arg0, G4VSolid * arg1)->void{ G4LogicalVolume::SetSolid(arg0, arg1); });

  DEBUG_MSG("Adding wrapper for G4bool G4LogicalVolume::ChangeDaughtersType(EVolume) (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4LogicalVolume::ChangeDaughtersType(EVolume)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:384:12
  t17.method("ChangeDaughtersType", [](G4LogicalVolume& a, EVolume arg0)->G4bool{ return a.ChangeDaughtersType(arg0); });
  t17.method("ChangeDaughtersType", [](G4LogicalVolume* a, EVolume arg0)->G4bool{ return a->ChangeDaughtersType(arg0); });

  /* End of G4LogicalVolume class method wrappers
   **********************************************************************/


  /**********************************************************************/
  /* Wrappers for the methods of class G4NavigationLevelRep
   */


  DEBUG_MSG("Adding wrapper for void G4NavigationLevelRep::G4NavigationLevelRep(G4NavigationLevelRep &) (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NavigationLevelRep.icc:69:23
  t21.constructor<G4NavigationLevelRep &>();

  /* End of G4NavigationLevelRep class method wrappers
   **********************************************************************/


  /**********************************************************************/
  /* Wrappers for the methods of class G4RunManager
   */

  DEBUG_MSG("Adding wrapper for void G4RunManager::BeamOn(G4int, const char *, G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::BeamOn(G4int, const char *, G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:163:18
  t22.method("BeamOn", [](G4RunManager& a, G4int arg0)->void{ a.BeamOn(arg0); });
  t22.method("BeamOn", [](G4RunManager& a, G4int arg0, const char * arg1)->void{ a.BeamOn(arg0, arg1); });
  t22.method("BeamOn", [](G4RunManager& a, G4int arg0, const char * arg1, G4int arg2)->void{ a.BeamOn(arg0, arg1, arg2); });
  t22.method("BeamOn", [](G4RunManager* a, G4int arg0)->void{ a->BeamOn(arg0); });
  t22.method("BeamOn", [](G4RunManager* a, G4int arg0, const char * arg1)->void{ a->BeamOn(arg0, arg1); });
  t22.method("BeamOn", [](G4RunManager* a, G4int arg0, const char * arg1, G4int arg2)->void{ a->BeamOn(arg0, arg1, arg2); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::Initialize() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::Initialize()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:175:18
  t22.method("Initialize", [](G4RunManager& a)->void{ a.Initialize(); });
  t22.method("Initialize", [](G4RunManager* a)->void{ a->Initialize(); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::DefineWorldVolume(G4VPhysicalVolume *, G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::DefineWorldVolume(G4VPhysicalVolume *, G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:188:18
  t22.method("DefineWorldVolume", [](G4RunManager& a, G4VPhysicalVolume * arg0)->void{ a.DefineWorldVolume(arg0); });
  t22.method("DefineWorldVolume", [](G4RunManager& a, G4VPhysicalVolume * arg0, G4bool arg1)->void{ a.DefineWorldVolume(arg0, arg1); });
  t22.method("DefineWorldVolume", [](G4RunManager* a, G4VPhysicalVolume * arg0)->void{ a->DefineWorldVolume(arg0); });
  t22.method("DefineWorldVolume", [](G4RunManager* a, G4VPhysicalVolume * arg0, G4bool arg1)->void{ a->DefineWorldVolume(arg0, arg1); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::AbortRun(G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::AbortRun(G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:197:18
  t22.method("AbortRun", [](G4RunManager& a)->void{ a.AbortRun(); });
  t22.method("AbortRun", [](G4RunManager& a, G4bool arg0)->void{ a.AbortRun(arg0); });
  t22.method("AbortRun", [](G4RunManager* a)->void{ a->AbortRun(); });
  t22.method("AbortRun", [](G4RunManager* a, G4bool arg0)->void{ a->AbortRun(arg0); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::AbortEvent() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::AbortEvent()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:206:18
  t22.method("AbortEvent", [](G4RunManager& a)->void{ a.AbortEvent(); });
  t22.method("AbortEvent", [](G4RunManager* a)->void{ a->AbortEvent(); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::InitializeGeometry() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::InitializeGeometry()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:211:18
  t22.method("InitializeGeometry", [](G4RunManager& a)->void{ a.InitializeGeometry(); });
  t22.method("InitializeGeometry", [](G4RunManager* a)->void{ a->InitializeGeometry(); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::InitializePhysics() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::InitializePhysics()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:212:18
  t22.method("InitializePhysics", [](G4RunManager& a)->void{ a.InitializePhysics(); });
  t22.method("InitializePhysics", [](G4RunManager* a)->void{ a->InitializePhysics(); });

  DEBUG_MSG("Adding wrapper for G4bool G4RunManager::ConfirmBeamOnCondition() (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4RunManager::ConfirmBeamOnCondition()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:219:20
  t22.method("ConfirmBeamOnCondition", [](G4RunManager& a)->G4bool{ return a.ConfirmBeamOnCondition(); });
  t22.method("ConfirmBeamOnCondition", [](G4RunManager* a)->G4bool{ return a->ConfirmBeamOnCondition(); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::RunInitialization() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::RunInitialization()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:220:18
  t22.method("RunInitialization", [](G4RunManager& a)->void{ a.RunInitialization(); });
  t22.method("RunInitialization", [](G4RunManager* a)->void{ a->RunInitialization(); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::DoEventLoop(G4int, const char *, G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::DoEventLoop(G4int, const char *, G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:221:18
  t22.method("DoEventLoop", [](G4RunManager& a, G4int arg0)->void{ a.DoEventLoop(arg0); });
  t22.method("DoEventLoop", [](G4RunManager& a, G4int arg0, const char * arg1)->void{ a.DoEventLoop(arg0, arg1); });
  t22.method("DoEventLoop", [](G4RunManager& a, G4int arg0, const char * arg1, G4int arg2)->void{ a.DoEventLoop(arg0, arg1, arg2); });
  t22.method("DoEventLoop", [](G4RunManager* a, G4int arg0)->void{ a->DoEventLoop(arg0); });
  t22.method("DoEventLoop", [](G4RunManager* a, G4int arg0, const char * arg1)->void{ a->DoEventLoop(arg0, arg1); });
  t22.method("DoEventLoop", [](G4RunManager* a, G4int arg0, const char * arg1, G4int arg2)->void{ a->DoEventLoop(arg0, arg1, arg2); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::RunTermination() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::RunTermination()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:223:18
  t22.method("RunTermination", [](G4RunManager& a)->void{ a.RunTermination(); });
  t22.method("RunTermination", [](G4RunManager* a)->void{ a->RunTermination(); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::InitializeEventLoop(G4int, const char *, G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::InitializeEventLoop(G4int, const char *, G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:240:18
  t22.method("InitializeEventLoop", [](G4RunManager& a, G4int arg0)->void{ a.InitializeEventLoop(arg0); });
  t22.method("InitializeEventLoop", [](G4RunManager& a, G4int arg0, const char * arg1)->void{ a.InitializeEventLoop(arg0, arg1); });
  t22.method("InitializeEventLoop", [](G4RunManager& a, G4int arg0, const char * arg1, G4int arg2)->void{ a.InitializeEventLoop(arg0, arg1, arg2); });
  t22.method("InitializeEventLoop", [](G4RunManager* a, G4int arg0)->void{ a->InitializeEventLoop(arg0); });
  t22.method("InitializeEventLoop", [](G4RunManager* a, G4int arg0, const char * arg1)->void{ a->InitializeEventLoop(arg0, arg1); });
  t22.method("InitializeEventLoop", [](G4RunManager* a, G4int arg0, const char * arg1, G4int arg2)->void{ a->InitializeEventLoop(arg0, arg1, arg2); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::ProcessOneEvent(G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::ProcessOneEvent(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:243:18
  t22.method("ProcessOneEvent", [](G4RunManager& a, G4int arg0)->void{ a.ProcessOneEvent(arg0); });
  t22.method("ProcessOneEvent", [](G4RunManager* a, G4int arg0)->void{ a->ProcessOneEvent(arg0); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::TerminateOneEvent() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::TerminateOneEvent()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:244:18
  t22.method("TerminateOneEvent", [](G4RunManager& a)->void{ a.TerminateOneEvent(); });
  t22.method("TerminateOneEvent", [](G4RunManager* a)->void{ a->TerminateOneEvent(); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::TerminateEventLoop() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::TerminateEventLoop()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:245:18
  t22.method("TerminateEventLoop", [](G4RunManager& a)->void{ a.TerminateEventLoop(); });
  t22.method("TerminateEventLoop", [](G4RunManager* a)->void{ a->TerminateEventLoop(); });

  DEBUG_MSG("Adding wrapper for G4Event * G4RunManager::GenerateEvent(G4int) (" __HERE__ ")");
  // signature to use in the veto list: G4Event * G4RunManager::GenerateEvent(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:248:22
  t22.method("GenerateEvent", [](G4RunManager& a, G4int arg0)->G4Event *{ return a.GenerateEvent(arg0); });
  t22.method("GenerateEvent", [](G4RunManager* a, G4int arg0)->G4Event *{ return a->GenerateEvent(arg0); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::AnalyzeEvent(G4Event *) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::AnalyzeEvent(G4Event *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:249:18
  t22.method("AnalyzeEvent", [](G4RunManager& a, G4Event * arg0)->void{ a.AnalyzeEvent(arg0); });
  t22.method("AnalyzeEvent", [](G4RunManager* a, G4Event * arg0)->void{ a->AnalyzeEvent(arg0); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::ConfigureProfilers(const int &) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::ConfigureProfilers(const int &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:259:18
  t22.method("ConfigureProfilers", [](G4RunManager& a)->void{ a.ConfigureProfilers(); });
  t22.method("ConfigureProfilers", [](G4RunManager& a, const int & arg0)->void{ a.ConfigureProfilers(arg0); });
  t22.method("ConfigureProfilers", [](G4RunManager* a)->void{ a->ConfigureProfilers(); });
  t22.method("ConfigureProfilers", [](G4RunManager* a, const int & arg0)->void{ a->ConfigureProfilers(arg0); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::ConfigureProfilers(G4int, char **) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::ConfigureProfilers(G4int, char **)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:261:10
  t22.method("ConfigureProfilers", [](G4RunManager& a, G4int arg0, char ** arg1)->void{ a.ConfigureProfilers(arg0, arg1); });
  t22.method("ConfigureProfilers", [](G4RunManager* a, G4int arg0, char ** arg1)->void{ a->ConfigureProfilers(arg0, arg1); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetNumberOfThreads(G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetNumberOfThreads(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:264:18
  t22.method("SetNumberOfThreads", [](G4RunManager& a, G4int arg0)->void{ a.SetNumberOfThreads(arg0); });
  t22.method("SetNumberOfThreads", [](G4RunManager* a, G4int arg0)->void{ a->SetNumberOfThreads(arg0); });

  DEBUG_MSG("Adding wrapper for G4int G4RunManager::GetNumberOfThreads() (" __HERE__ ")");
  // signature to use in the veto list: G4int G4RunManager::GetNumberOfThreads()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:265:19
  t22.method("GetNumberOfThreads", [](G4RunManager const& a)->G4int{ return a.GetNumberOfThreads(); });
  t22.method("GetNumberOfThreads", [](G4RunManager const* a)->G4int{ return a->GetNumberOfThreads(); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::DumpRegion(const G4String &) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::DumpRegion(const G4String &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:269:10
  t22.method("DumpRegion", [](G4RunManager const& a, const G4String & arg0)->void{ a.DumpRegion(arg0); });
  t22.method("DumpRegion", [](G4RunManager const* a, const G4String & arg0)->void{ a->DumpRegion(arg0); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::DumpRegion(G4Region *) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::DumpRegion(G4Region *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:271:10
  t22.method("DumpRegion", [](G4RunManager const& a)->void{ a.DumpRegion(); });
  t22.method("DumpRegion", [](G4RunManager const& a, G4Region * arg0)->void{ a.DumpRegion(arg0); });
  t22.method("DumpRegion", [](G4RunManager const* a)->void{ a->DumpRegion(); });
  t22.method("DumpRegion", [](G4RunManager const* a, G4Region * arg0)->void{ a->DumpRegion(arg0); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::GeometryHasBeenModified(G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::GeometryHasBeenModified(G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:275:10
  t22.method("GeometryHasBeenModified", [](G4RunManager& a)->void{ a.GeometryHasBeenModified(); });
  t22.method("GeometryHasBeenModified", [](G4RunManager& a, G4bool arg0)->void{ a.GeometryHasBeenModified(arg0); });
  t22.method("GeometryHasBeenModified", [](G4RunManager* a)->void{ a->GeometryHasBeenModified(); });
  t22.method("GeometryHasBeenModified", [](G4RunManager* a, G4bool arg0)->void{ a->GeometryHasBeenModified(arg0); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::ReinitializeGeometry(G4bool, G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::ReinitializeGeometry(G4bool, G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:283:10
  t22.method("ReinitializeGeometry", [](G4RunManager& a)->void{ a.ReinitializeGeometry(); });
  t22.method("ReinitializeGeometry", [](G4RunManager& a, G4bool arg0)->void{ a.ReinitializeGeometry(arg0); });
  t22.method("ReinitializeGeometry", [](G4RunManager& a, G4bool arg0, G4bool arg1)->void{ a.ReinitializeGeometry(arg0, arg1); });
  t22.method("ReinitializeGeometry", [](G4RunManager* a)->void{ a->ReinitializeGeometry(); });
  t22.method("ReinitializeGeometry", [](G4RunManager* a, G4bool arg0)->void{ a->ReinitializeGeometry(arg0); });
  t22.method("ReinitializeGeometry", [](G4RunManager* a, G4bool arg0, G4bool arg1)->void{ a->ReinitializeGeometry(arg0, arg1); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::PhysicsHasBeenModified() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::PhysicsHasBeenModified()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:294:17
  t22.method("PhysicsHasBeenModified", [](G4RunManager& a)->void{ a.PhysicsHasBeenModified(); });
  t22.method("PhysicsHasBeenModified", [](G4RunManager* a)->void{ a->PhysicsHasBeenModified(); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::CutOffHasBeenModified() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::CutOffHasBeenModified()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:301:17
  t22.method("CutOffHasBeenModified", [](G4RunManager& a)->void{ a.CutOffHasBeenModified(); });
  t22.method("CutOffHasBeenModified", [](G4RunManager* a)->void{ a->CutOffHasBeenModified(); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::ReOptimizeMotherOf(G4VPhysicalVolume *) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::ReOptimizeMotherOf(G4VPhysicalVolume *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:307:10
  t22.method("ReOptimizeMotherOf", [](G4RunManager& a, G4VPhysicalVolume * arg0)->void{ a.ReOptimizeMotherOf(arg0); });
  t22.method("ReOptimizeMotherOf", [](G4RunManager* a, G4VPhysicalVolume * arg0)->void{ a->ReOptimizeMotherOf(arg0); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::ReOptimize(G4LogicalVolume *) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::ReOptimize(G4LogicalVolume *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:314:10
  t22.method("ReOptimize", [](G4RunManager& a, G4LogicalVolume * arg0)->void{ a.ReOptimize(arg0); });
  t22.method("ReOptimize", [](G4RunManager* a, G4LogicalVolume * arg0)->void{ a->ReOptimize(arg0); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetGeometryToBeOptimized(G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetGeometryToBeOptimized(G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:317:17
  t22.method("SetGeometryToBeOptimized", [](G4RunManager& a, G4bool arg0)->void{ a.SetGeometryToBeOptimized(arg0); });
  t22.method("SetGeometryToBeOptimized", [](G4RunManager* a, G4bool arg0)->void{ a->SetGeometryToBeOptimized(arg0); });

  DEBUG_MSG("Adding wrapper for G4bool G4RunManager::GetGeometryToBeOptimized() (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4RunManager::GetGeometryToBeOptimized()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:326:19
  t22.method("GetGeometryToBeOptimized", [](G4RunManager& a)->G4bool{ return a.GetGeometryToBeOptimized(); });
  t22.method("GetGeometryToBeOptimized", [](G4RunManager* a)->G4bool{ return a->GetGeometryToBeOptimized(); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::GeometryDirectlyUpdated(G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::GeometryDirectlyUpdated(G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:331:10
  t22.method("GeometryDirectlyUpdated", [](G4RunManager& a)->void{ a.GeometryDirectlyUpdated(); });
  t22.method("GeometryDirectlyUpdated", [](G4RunManager& a, G4bool arg0)->void{ a.GeometryDirectlyUpdated(arg0); });
  t22.method("GeometryDirectlyUpdated", [](G4RunManager* a)->void{ a->GeometryDirectlyUpdated(); });
  t22.method("GeometryDirectlyUpdated", [](G4RunManager* a, G4bool arg0)->void{ a->GeometryDirectlyUpdated(arg0); });

  DEBUG_MSG("Adding wrapper for G4bool G4RunManager::IfGeometryHasBeenDestroyed() (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4RunManager::IfGeometryHasBeenDestroyed()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:336:19
  t22.method("G4RunManager!IfGeometryHasBeenDestroyed", []()->G4bool{ return G4RunManager::IfGeometryHasBeenDestroyed(); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::ConstructScoringWorlds() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::ConstructScoringWorlds()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:341:18
  t22.method("ConstructScoringWorlds", [](G4RunManager& a)->void{ a.ConstructScoringWorlds(); });
  t22.method("ConstructScoringWorlds", [](G4RunManager* a)->void{ a->ConstructScoringWorlds(); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::rndmSaveThisRun() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::rndmSaveThisRun()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:343:18
  t22.method("rndmSaveThisRun", [](G4RunManager& a)->void{ a.rndmSaveThisRun(); });
  t22.method("rndmSaveThisRun", [](G4RunManager* a)->void{ a->rndmSaveThisRun(); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::rndmSaveThisEvent() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::rndmSaveThisEvent()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:344:18
  t22.method("rndmSaveThisEvent", [](G4RunManager& a)->void{ a.rndmSaveThisEvent(); });
  t22.method("rndmSaveThisEvent", [](G4RunManager* a)->void{ a->rndmSaveThisEvent(); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::RestoreRandomNumberStatus(const G4String &) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::RestoreRandomNumberStatus(const G4String &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:345:18
  t22.method("RestoreRandomNumberStatus", [](G4RunManager& a, const G4String & arg0)->void{ a.RestoreRandomNumberStatus(arg0); });
  t22.method("RestoreRandomNumberStatus", [](G4RunManager* a, const G4String & arg0)->void{ a->RestoreRandomNumberStatus(arg0); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::RestoreRndmEachEvent(G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::RestoreRndmEachEvent(G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:346:18
  t22.method("RestoreRndmEachEvent", [](G4RunManager& a, G4bool arg0)->void{ a.RestoreRndmEachEvent(arg0); });
  t22.method("RestoreRndmEachEvent", [](G4RunManager* a, G4bool arg0)->void{ a->RestoreRndmEachEvent(arg0); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetUserAction(G4UserStackingAction *) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetUserAction(G4UserStackingAction *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:356:18
  t22.method("SetUserAction", [](G4RunManager& a, G4UserStackingAction * arg0)->void{ a.SetUserAction(arg0); });
  t22.method("SetUserAction", [](G4RunManager* a, G4UserStackingAction * arg0)->void{ a->SetUserAction(arg0); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetUserAction(G4UserTrackingAction *) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetUserAction(G4UserTrackingAction *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:357:18
  t22.method("SetUserAction", [](G4RunManager& a, G4UserTrackingAction * arg0)->void{ a.SetUserAction(arg0); });
  t22.method("SetUserAction", [](G4RunManager* a, G4UserTrackingAction * arg0)->void{ a->SetUserAction(arg0); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetUserAction(G4UserSteppingAction *) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetUserAction(G4UserSteppingAction *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:358:18
  t22.method("SetUserAction", [](G4RunManager& a, G4UserSteppingAction * arg0)->void{ a.SetUserAction(arg0); });
  t22.method("SetUserAction", [](G4RunManager* a, G4UserSteppingAction * arg0)->void{ a->SetUserAction(arg0); });

  DEBUG_MSG("Adding wrapper for const G4UserStackingAction * G4RunManager::GetUserStackingAction() (" __HERE__ ")");
  // signature to use in the veto list: const G4UserStackingAction * G4RunManager::GetUserStackingAction()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:408:40
  t22.method("GetUserStackingAction", [](G4RunManager const& a)->const G4UserStackingAction *{ return a.GetUserStackingAction(); });
  t22.method("GetUserStackingAction", [](G4RunManager const* a)->const G4UserStackingAction *{ return a->GetUserStackingAction(); });

  DEBUG_MSG("Adding wrapper for const G4UserTrackingAction * G4RunManager::GetUserTrackingAction() (" __HERE__ ")");
  // signature to use in the veto list: const G4UserTrackingAction * G4RunManager::GetUserTrackingAction()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:412:40
  t22.method("GetUserTrackingAction", [](G4RunManager const& a)->const G4UserTrackingAction *{ return a.GetUserTrackingAction(); });
  t22.method("GetUserTrackingAction", [](G4RunManager const* a)->const G4UserTrackingAction *{ return a->GetUserTrackingAction(); });

  DEBUG_MSG("Adding wrapper for const G4UserSteppingAction * G4RunManager::GetUserSteppingAction() (" __HERE__ ")");
  // signature to use in the veto list: const G4UserSteppingAction * G4RunManager::GetUserSteppingAction()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:416:40
  t22.method("GetUserSteppingAction", [](G4RunManager const& a)->const G4UserSteppingAction *{ return a.GetUserSteppingAction(); });
  t22.method("GetUserSteppingAction", [](G4RunManager const* a)->const G4UserSteppingAction *{ return a->GetUserSteppingAction(); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetNumberOfAdditionalWaitingStacks(G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetNumberOfAdditionalWaitingStacks(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:422:17
  t22.method("SetNumberOfAdditionalWaitingStacks", [](G4RunManager& a, G4int arg0)->void{ a.SetNumberOfAdditionalWaitingStacks(arg0); });
  t22.method("SetNumberOfAdditionalWaitingStacks", [](G4RunManager* a, G4int arg0)->void{ a->SetNumberOfAdditionalWaitingStacks(arg0); });

  DEBUG_MSG("Adding wrapper for const G4String & G4RunManager::GetVersionString() (" __HERE__ ")");
  // signature to use in the veto list: const G4String & G4RunManager::GetVersionString()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:431:28
  t22.method("GetVersionString", [](G4RunManager const& a)->const G4String &{ return a.GetVersionString(); });
  t22.method("GetVersionString", [](G4RunManager const* a)->const G4String &{ return a->GetVersionString(); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetPrimaryTransformer(G4PrimaryTransformer *) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetPrimaryTransformer(G4PrimaryTransformer *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:436:17
  t22.method("SetPrimaryTransformer", [](G4RunManager& a, G4PrimaryTransformer * arg0)->void{ a.SetPrimaryTransformer(arg0); });
  t22.method("SetPrimaryTransformer", [](G4RunManager* a, G4PrimaryTransformer * arg0)->void{ a->SetPrimaryTransformer(arg0); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::StoreRandomNumberStatusToG4Event(G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::StoreRandomNumberStatusToG4Event(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:441:17
  t22.method("StoreRandomNumberStatusToG4Event", [](G4RunManager& a, G4int arg0)->void{ a.StoreRandomNumberStatusToG4Event(arg0); });
  t22.method("StoreRandomNumberStatusToG4Event", [](G4RunManager* a, G4int arg0)->void{ a->StoreRandomNumberStatusToG4Event(arg0); });

  DEBUG_MSG("Adding wrapper for G4int G4RunManager::GetFlagRandomNumberStatusToG4Event() (" __HERE__ ")");
  // signature to use in the veto list: G4int G4RunManager::GetFlagRandomNumberStatusToG4Event()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:451:18
  t22.method("GetFlagRandomNumberStatusToG4Event", [](G4RunManager const& a)->G4int{ return a.GetFlagRandomNumberStatusToG4Event(); });
  t22.method("GetFlagRandomNumberStatusToG4Event", [](G4RunManager const* a)->G4int{ return a->GetFlagRandomNumberStatusToG4Event(); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetRandomNumberStore(G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetRandomNumberStore(G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:456:17
  t22.method("SetRandomNumberStore", [](G4RunManager& a, G4bool arg0)->void{ a.SetRandomNumberStore(arg0); });
  t22.method("SetRandomNumberStore", [](G4RunManager* a, G4bool arg0)->void{ a->SetRandomNumberStore(arg0); });

  DEBUG_MSG("Adding wrapper for G4bool G4RunManager::GetRandomNumberStore() (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4RunManager::GetRandomNumberStore()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:460:19
  t22.method("GetRandomNumberStore", [](G4RunManager const& a)->G4bool{ return a.GetRandomNumberStore(); });
  t22.method("GetRandomNumberStore", [](G4RunManager const* a)->G4bool{ return a->GetRandomNumberStore(); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetRandomNumberStoreDir(const G4String &) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetRandomNumberStoreDir(const G4String &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:464:17
  t22.method("SetRandomNumberStoreDir", [](G4RunManager& a, const G4String & arg0)->void{ a.SetRandomNumberStoreDir(arg0); });
  t22.method("SetRandomNumberStoreDir", [](G4RunManager* a, const G4String & arg0)->void{ a->SetRandomNumberStoreDir(arg0); });

  DEBUG_MSG("Adding wrapper for const G4String & G4RunManager::GetRandomNumberStoreDir() (" __HERE__ ")");
  // signature to use in the veto list: const G4String & G4RunManager::GetRandomNumberStoreDir()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:487:28
  t22.method("GetRandomNumberStoreDir", [](G4RunManager const& a)->const G4String &{ return a.GetRandomNumberStoreDir(); });
  t22.method("GetRandomNumberStoreDir", [](G4RunManager const* a)->const G4String &{ return a->GetRandomNumberStoreDir(); });

  DEBUG_MSG("Adding wrapper for const G4String & G4RunManager::GetRandomNumberStatusForThisRun() (" __HERE__ ")");
  // signature to use in the veto list: const G4String & G4RunManager::GetRandomNumberStatusForThisRun()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:491:28
  t22.method("GetRandomNumberStatusForThisRun", [](G4RunManager const& a)->const G4String &{ return a.GetRandomNumberStatusForThisRun(); });
  t22.method("GetRandomNumberStatusForThisRun", [](G4RunManager const* a)->const G4String &{ return a->GetRandomNumberStatusForThisRun(); });

  DEBUG_MSG("Adding wrapper for const G4String & G4RunManager::GetRandomNumberStatusForThisEvent() (" __HERE__ ")");
  // signature to use in the veto list: const G4String & G4RunManager::GetRandomNumberStatusForThisEvent()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:495:28
  t22.method("GetRandomNumberStatusForThisEvent", [](G4RunManager const& a)->const G4String &{ return a.GetRandomNumberStatusForThisEvent(); });
  t22.method("GetRandomNumberStatusForThisEvent", [](G4RunManager const* a)->const G4String &{ return a->GetRandomNumberStatusForThisEvent(); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetRandomNumberStorePerEvent(G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetRandomNumberStorePerEvent(G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:506:17
  t22.method("SetRandomNumberStorePerEvent", [](G4RunManager& a, G4bool arg0)->void{ a.SetRandomNumberStorePerEvent(arg0); });
  t22.method("SetRandomNumberStorePerEvent", [](G4RunManager* a, G4bool arg0)->void{ a->SetRandomNumberStorePerEvent(arg0); });

  DEBUG_MSG("Adding wrapper for G4bool G4RunManager::GetRandomNumberStorePerEvent() (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4RunManager::GetRandomNumberStorePerEvent()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:510:19
  t22.method("GetRandomNumberStorePerEvent", [](G4RunManager const& a)->G4bool{ return a.GetRandomNumberStorePerEvent(); });
  t22.method("GetRandomNumberStorePerEvent", [](G4RunManager const* a)->G4bool{ return a->GetRandomNumberStorePerEvent(); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetVerboseLevel(G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetVerboseLevel(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:515:17
  t22.method("SetVerboseLevel", [](G4RunManager& a, G4int arg0)->void{ a.SetVerboseLevel(arg0); });
  t22.method("SetVerboseLevel", [](G4RunManager* a, G4int arg0)->void{ a->SetVerboseLevel(arg0); });

  DEBUG_MSG("Adding wrapper for G4int G4RunManager::GetVerboseLevel() (" __HERE__ ")");
  // signature to use in the veto list: G4int G4RunManager::GetVerboseLevel()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:520:18
  t22.method("GetVerboseLevel", [](G4RunManager const& a)->G4int{ return a.GetVerboseLevel(); });
  t22.method("GetVerboseLevel", [](G4RunManager const* a)->G4int{ return a->GetVerboseLevel(); });

  DEBUG_MSG("Adding wrapper for G4int G4RunManager::GetPrintProgress() (" __HERE__ ")");
  // signature to use in the veto list: G4int G4RunManager::GetPrintProgress()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:521:18
  t22.method("GetPrintProgress", [](G4RunManager& a)->G4int{ return a.GetPrintProgress(); });
  t22.method("GetPrintProgress", [](G4RunManager* a)->G4int{ return a->GetPrintProgress(); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetPrintProgress(G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetPrintProgress(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:522:17
  t22.method("SetPrintProgress", [](G4RunManager& a, G4int arg0)->void{ a.SetPrintProgress(arg0); });
  t22.method("SetPrintProgress", [](G4RunManager* a, G4int arg0)->void{ a->SetPrintProgress(arg0); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetNumberOfEventsToBeStored(G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetNumberOfEventsToBeStored(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:524:17
  t22.method("SetNumberOfEventsToBeStored", [](G4RunManager& a, G4int arg0)->void{ a.SetNumberOfEventsToBeStored(arg0); });
  t22.method("SetNumberOfEventsToBeStored", [](G4RunManager* a, G4int arg0)->void{ a->SetNumberOfEventsToBeStored(arg0); });

  DEBUG_MSG("Adding wrapper for const G4Event * G4RunManager::GetCurrentEvent() (" __HERE__ ")");
  // signature to use in the veto list: const G4Event * G4RunManager::GetCurrentEvent()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:537:27
  t22.method("GetCurrentEvent", [](G4RunManager const& a)->const G4Event *{ return a.GetCurrentEvent(); });
  t22.method("GetCurrentEvent", [](G4RunManager const* a)->const G4Event *{ return a->GetCurrentEvent(); });

  DEBUG_MSG("Adding wrapper for const G4Event * G4RunManager::GetPreviousEvent(G4int) (" __HERE__ ")");
  // signature to use in the veto list: const G4Event * G4RunManager::GetPreviousEvent(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:540:27
  t22.method("GetPreviousEvent", [](G4RunManager const& a, G4int arg0)->const G4Event *{ return a.GetPreviousEvent(arg0); });
  t22.method("GetPreviousEvent", [](G4RunManager const* a, G4int arg0)->const G4Event *{ return a->GetPreviousEvent(arg0); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetRunIDCounter(G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetRunIDCounter(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:558:17
  t22.method("SetRunIDCounter", [](G4RunManager& a, G4int arg0)->void{ a.SetRunIDCounter(arg0); });
  t22.method("SetRunIDCounter", [](G4RunManager* a, G4int arg0)->void{ a->SetRunIDCounter(arg0); });

  DEBUG_MSG("Adding wrapper for G4int G4RunManager::GetNumberOfParallelWorld() (" __HERE__ ")");
  // signature to use in the veto list: G4int G4RunManager::GetNumberOfParallelWorld()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:562:18
  t22.method("GetNumberOfParallelWorld", [](G4RunManager const& a)->G4int{ return a.GetNumberOfParallelWorld(); });
  t22.method("GetNumberOfParallelWorld", [](G4RunManager const* a)->G4int{ return a->GetNumberOfParallelWorld(); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetNumberOfEventsToBeProcessed(G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetNumberOfEventsToBeProcessed(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:563:17
  t22.method("SetNumberOfEventsToBeProcessed", [](G4RunManager& a, G4int arg0)->void{ a.SetNumberOfEventsToBeProcessed(arg0); });
  t22.method("SetNumberOfEventsToBeProcessed", [](G4RunManager* a, G4int arg0)->void{ a->SetNumberOfEventsToBeProcessed(arg0); });

  DEBUG_MSG("Adding wrapper for G4int G4RunManager::GetNumberOfEventsToBeProcessed() (" __HERE__ ")");
  // signature to use in the veto list: G4int G4RunManager::GetNumberOfEventsToBeProcessed()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:567:18
  t22.method("GetNumberOfEventsToBeProcessed", [](G4RunManager const& a)->G4int{ return a.GetNumberOfEventsToBeProcessed(); });
  t22.method("GetNumberOfEventsToBeProcessed", [](G4RunManager const* a)->G4int{ return a->GetNumberOfEventsToBeProcessed(); });

  DEBUG_MSG("Adding wrapper for G4int G4RunManager::GetNumberOfSelectEvents() (" __HERE__ ")");
  // signature to use in the veto list: G4int G4RunManager::GetNumberOfSelectEvents()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:571:18
  t22.method("GetNumberOfSelectEvents", [](G4RunManager const& a)->G4int{ return a.GetNumberOfSelectEvents(); });
  t22.method("GetNumberOfSelectEvents", [](G4RunManager const* a)->G4int{ return a->GetNumberOfSelectEvents(); });

  DEBUG_MSG("Adding wrapper for const G4String & G4RunManager::GetSelectMacro() (" __HERE__ ")");
  // signature to use in the veto list: const G4String & G4RunManager::GetSelectMacro()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:572:28
  t22.method("GetSelectMacro", [](G4RunManager const& a)->const G4String &{ return a.GetSelectMacro(); });
  t22.method("GetSelectMacro", [](G4RunManager const* a)->const G4String &{ return a->GetSelectMacro(); });

  DEBUG_MSG("Adding wrapper for G4RunManager::RMType G4RunManager::GetRunManagerType() (" __HERE__ ")");
  // signature to use in the veto list: G4RunManager::RMType G4RunManager::GetRunManagerType()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:582:19
  t22.method("GetRunManagerType", [](G4RunManager const& a)->G4RunManager::RMType{ return a.GetRunManagerType(); });
  t22.method("GetRunManagerType", [](G4RunManager const* a)->G4RunManager::RMType{ return a->GetRunManagerType(); });

  /* End of G4RunManager class method wrappers
   **********************************************************************/


  /**********************************************************************/
  /* Wrappers for the methods of class G4NistManager
   */

  DEBUG_MSG("Adding wrapper for G4NistManager * G4NistManager::Instance() (" __HERE__ ")");
  // signature to use in the veto list: G4NistManager * G4NistManager::Instance()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:88:25
  t29.method("G4NistManager!Instance", []()->G4NistManager *{ return G4NistManager::Instance(); });

  DEBUG_MSG("Adding wrapper for G4Element * G4NistManager::GetElement(int) (" __HERE__ ")");
  // signature to use in the veto list: G4Element * G4NistManager::GetElement(int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:93:21
  t29.method("GetElement", [](G4NistManager const& a, int arg0)->G4Element *{ return a.GetElement(arg0); });
  t29.method("GetElement", [](G4NistManager const* a, int arg0)->G4Element *{ return a->GetElement(arg0); });

  DEBUG_MSG("Adding wrapper for G4Element * G4NistManager::FindElement(G4int) (" __HERE__ ")");
  // signature to use in the veto list: G4Element * G4NistManager::FindElement(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:97:21
  t29.method("FindElement", [](G4NistManager const& a, G4int arg0)->G4Element *{ return a.FindElement(arg0); });
  t29.method("FindElement", [](G4NistManager const* a, G4int arg0)->G4Element *{ return a->FindElement(arg0); });

  DEBUG_MSG("Adding wrapper for G4Element * G4NistManager::FindOrBuildElement(G4int, G4bool) (" __HERE__ ")");
  // signature to use in the veto list: G4Element * G4NistManager::FindOrBuildElement(G4int, G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:98:21
  t29.method("FindOrBuildElement", [](G4NistManager& a, G4int arg0)->G4Element *{ return a.FindOrBuildElement(arg0); });
  t29.method("FindOrBuildElement", [](G4NistManager& a, G4int arg0, G4bool arg1)->G4Element *{ return a.FindOrBuildElement(arg0, arg1); });
  t29.method("FindOrBuildElement", [](G4NistManager* a, G4int arg0)->G4Element *{ return a->FindOrBuildElement(arg0); });
  t29.method("FindOrBuildElement", [](G4NistManager* a, G4int arg0, G4bool arg1)->G4Element *{ return a->FindOrBuildElement(arg0, arg1); });

  DEBUG_MSG("Adding wrapper for G4Element * G4NistManager::FindOrBuildElement(const G4String &, G4bool) (" __HERE__ ")");
  // signature to use in the veto list: G4Element * G4NistManager::FindOrBuildElement(const G4String &, G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:102:21
  t29.method("FindOrBuildElement", [](G4NistManager& a, const G4String & arg0)->G4Element *{ return a.FindOrBuildElement(arg0); });
  t29.method("FindOrBuildElement", [](G4NistManager& a, const G4String & arg0, G4bool arg1)->G4Element *{ return a.FindOrBuildElement(arg0, arg1); });
  t29.method("FindOrBuildElement", [](G4NistManager* a, const G4String & arg0)->G4Element *{ return a->FindOrBuildElement(arg0); });
  t29.method("FindOrBuildElement", [](G4NistManager* a, const G4String & arg0, G4bool arg1)->G4Element *{ return a->FindOrBuildElement(arg0, arg1); });

  DEBUG_MSG("Adding wrapper for int G4NistManager::GetNumberOfElements() (" __HERE__ ")");
  // signature to use in the veto list: int G4NistManager::GetNumberOfElements()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:107:17
  t29.method("GetNumberOfElements", [](G4NistManager const& a)->int{ return a.GetNumberOfElements(); });
  t29.method("GetNumberOfElements", [](G4NistManager const* a)->int{ return a->GetNumberOfElements(); });

  DEBUG_MSG("Adding wrapper for G4int G4NistManager::GetZ(const G4String &) (" __HERE__ ")");
  // signature to use in the veto list: G4int G4NistManager::GetZ(const G4String &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:111:16
  t29.method("GetZ", [](G4NistManager const& a, const G4String & arg0)->G4int{ return a.GetZ(arg0); });
  t29.method("GetZ", [](G4NistManager const* a, const G4String & arg0)->G4int{ return a->GetZ(arg0); });

  DEBUG_MSG("Adding wrapper for G4double G4NistManager::GetAtomicMassAmu(const G4String &) (" __HERE__ ")");
  // signature to use in the veto list: G4double G4NistManager::GetAtomicMassAmu(const G4String &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:116:19
  t29.method("GetAtomicMassAmu", [](G4NistManager const& a, const G4String & arg0)->G4double{ return a.GetAtomicMassAmu(arg0); });
  t29.method("GetAtomicMassAmu", [](G4NistManager const* a, const G4String & arg0)->G4double{ return a->GetAtomicMassAmu(arg0); });

  DEBUG_MSG("Adding wrapper for G4double G4NistManager::GetAtomicMassAmu(G4int) (" __HERE__ ")");
  // signature to use in the veto list: G4double G4NistManager::GetAtomicMassAmu(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:121:19
  t29.method("GetAtomicMassAmu", [](G4NistManager const& a, G4int arg0)->G4double{ return a.GetAtomicMassAmu(arg0); });
  t29.method("GetAtomicMassAmu", [](G4NistManager const* a, G4int arg0)->G4double{ return a->GetAtomicMassAmu(arg0); });

  DEBUG_MSG("Adding wrapper for G4double G4NistManager::GetIsotopeMass(G4int, G4int) (" __HERE__ ")");
  // signature to use in the veto list: G4double G4NistManager::GetIsotopeMass(G4int, G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:125:19
  t29.method("GetIsotopeMass", [](G4NistManager const& a, G4int arg0, G4int arg1)->G4double{ return a.GetIsotopeMass(arg0, arg1); });
  t29.method("GetIsotopeMass", [](G4NistManager const* a, G4int arg0, G4int arg1)->G4double{ return a->GetIsotopeMass(arg0, arg1); });

  DEBUG_MSG("Adding wrapper for G4double G4NistManager::GetAtomicMass(G4int, G4int) (" __HERE__ ")");
  // signature to use in the veto list: G4double G4NistManager::GetAtomicMass(G4int, G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:130:19
  t29.method("GetAtomicMass", [](G4NistManager const& a, G4int arg0, G4int arg1)->G4double{ return a.GetAtomicMass(arg0, arg1); });
  t29.method("GetAtomicMass", [](G4NistManager const* a, G4int arg0, G4int arg1)->G4double{ return a->GetAtomicMass(arg0, arg1); });

  DEBUG_MSG("Adding wrapper for G4double G4NistManager::GetTotalElectronBindingEnergy(G4int) (" __HERE__ ")");
  // signature to use in the veto list: G4double G4NistManager::GetTotalElectronBindingEnergy(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:134:19
  t29.method("GetTotalElectronBindingEnergy", [](G4NistManager const& a, G4int arg0)->G4double{ return a.GetTotalElectronBindingEnergy(arg0); });
  t29.method("GetTotalElectronBindingEnergy", [](G4NistManager const* a, G4int arg0)->G4double{ return a->GetTotalElectronBindingEnergy(arg0); });

  DEBUG_MSG("Adding wrapper for G4int G4NistManager::GetNistFirstIsotopeN(G4int) (" __HERE__ ")");
  // signature to use in the veto list: G4int G4NistManager::GetNistFirstIsotopeN(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:138:16
  t29.method("GetNistFirstIsotopeN", [](G4NistManager const& a, G4int arg0)->G4int{ return a.GetNistFirstIsotopeN(arg0); });
  t29.method("GetNistFirstIsotopeN", [](G4NistManager const* a, G4int arg0)->G4int{ return a->GetNistFirstIsotopeN(arg0); });

  DEBUG_MSG("Adding wrapper for G4int G4NistManager::GetNumberOfNistIsotopes(G4int) (" __HERE__ ")");
  // signature to use in the veto list: G4int G4NistManager::GetNumberOfNistIsotopes(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:142:16
  t29.method("GetNumberOfNistIsotopes", [](G4NistManager const& a, G4int arg0)->G4int{ return a.GetNumberOfNistIsotopes(arg0); });
  t29.method("GetNumberOfNistIsotopes", [](G4NistManager const* a, G4int arg0)->G4int{ return a->GetNumberOfNistIsotopes(arg0); });

  DEBUG_MSG("Adding wrapper for G4double G4NistManager::GetIsotopeAbundance(G4int, G4int) (" __HERE__ ")");
  // signature to use in the veto list: G4double G4NistManager::GetIsotopeAbundance(G4int, G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:146:19
  t29.method("GetIsotopeAbundance", [](G4NistManager const& a, G4int arg0, G4int arg1)->G4double{ return a.GetIsotopeAbundance(arg0, arg1); });
  t29.method("GetIsotopeAbundance", [](G4NistManager const* a, G4int arg0, G4int arg1)->G4double{ return a->GetIsotopeAbundance(arg0, arg1); });

  DEBUG_MSG("Adding wrapper for void G4NistManager::PrintElement(G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4NistManager::PrintElement(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:150:15
  t29.method("PrintElement", [](G4NistManager const& a, G4int arg0)->void{ a.PrintElement(arg0); });
  t29.method("PrintElement", [](G4NistManager const* a, G4int arg0)->void{ a->PrintElement(arg0); });

  DEBUG_MSG("Adding wrapper for void G4NistManager::PrintElement(const G4String &) (" __HERE__ ")");
  // signature to use in the veto list: void G4NistManager::PrintElement(const G4String &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:154:8
  t29.method("PrintElement", [](G4NistManager const& a, const G4String & arg0)->void{ a.PrintElement(arg0); });
  t29.method("PrintElement", [](G4NistManager const* a, const G4String & arg0)->void{ a->PrintElement(arg0); });

  DEBUG_MSG("Adding wrapper for void G4NistManager::PrintG4Element(const G4String &) (" __HERE__ ")");
  // signature to use in the veto list: void G4NistManager::PrintG4Element(const G4String &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:158:8
  t29.method("PrintG4Element", [](G4NistManager const& a, const G4String & arg0)->void{ a.PrintG4Element(arg0); });
  t29.method("PrintG4Element", [](G4NistManager const* a, const G4String & arg0)->void{ a->PrintG4Element(arg0); });

  DEBUG_MSG("Adding wrapper for const int & G4NistManager::GetNistElementNames() (" __HERE__ ")");
  // signature to use in the veto list: const int & G4NistManager::GetNistElementNames()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:162:39
  t29.method("GetNistElementNames", [](G4NistManager const& a)->const int &{ return a.GetNistElementNames(); });
  t29.method("GetNistElementNames", [](G4NistManager const* a)->const int &{ return a->GetNistElementNames(); });

  DEBUG_MSG("Adding wrapper for G4double G4NistManager::GetMeanIonisationEnergy(G4int) (" __HERE__ ")");
  // signature to use in the veto list: G4double G4NistManager::GetMeanIonisationEnergy(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:166:19
  t29.method("GetMeanIonisationEnergy", [](G4NistManager const& a, G4int arg0)->G4double{ return a.GetMeanIonisationEnergy(arg0); });
  t29.method("GetMeanIonisationEnergy", [](G4NistManager const* a, G4int arg0)->G4double{ return a->GetMeanIonisationEnergy(arg0); });

  DEBUG_MSG("Adding wrapper for G4double G4NistManager::GetNominalDensity(G4int) (" __HERE__ ")");
  // signature to use in the veto list: G4double G4NistManager::GetNominalDensity(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:171:19
  t29.method("GetNominalDensity", [](G4NistManager const& a, G4int arg0)->G4double{ return a.GetNominalDensity(arg0); });
  t29.method("GetNominalDensity", [](G4NistManager const* a, G4int arg0)->G4double{ return a->GetNominalDensity(arg0); });

  DEBUG_MSG("Adding wrapper for G4Material * G4NistManager::GetMaterial(int) (" __HERE__ ")");
  // signature to use in the veto list: G4Material * G4NistManager::GetMaterial(int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:175:22
  t29.method("GetMaterial", [](G4NistManager const& a, int arg0)->G4Material *{ return a.GetMaterial(arg0); });
  t29.method("GetMaterial", [](G4NistManager const* a, int arg0)->G4Material *{ return a->GetMaterial(arg0); });

  DEBUG_MSG("Adding wrapper for G4Material * G4NistManager::FindMaterial(const G4String &) (" __HERE__ ")");
  // signature to use in the veto list: G4Material * G4NistManager::FindMaterial(const G4String &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:179:22
  t29.method("FindMaterial", [](G4NistManager const& a, const G4String & arg0)->G4Material *{ return a.FindMaterial(arg0); });
  t29.method("FindMaterial", [](G4NistManager const* a, const G4String & arg0)->G4Material *{ return a->FindMaterial(arg0); });

  DEBUG_MSG("Adding wrapper for G4Material * G4NistManager::FindOrBuildMaterial(const G4String &, G4bool, G4bool) (" __HERE__ ")");
  // signature to use in the veto list: G4Material * G4NistManager::FindOrBuildMaterial(const G4String &, G4bool, G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:180:22
  t29.method("FindOrBuildMaterial", [](G4NistManager& a, const G4String & arg0)->G4Material *{ return a.FindOrBuildMaterial(arg0); });
  t29.method("FindOrBuildMaterial", [](G4NistManager& a, const G4String & arg0, G4bool arg1)->G4Material *{ return a.FindOrBuildMaterial(arg0, arg1); });
  t29.method("FindOrBuildMaterial", [](G4NistManager& a, const G4String & arg0, G4bool arg1, G4bool arg2)->G4Material *{ return a.FindOrBuildMaterial(arg0, arg1, arg2); });
  t29.method("FindOrBuildMaterial", [](G4NistManager* a, const G4String & arg0)->G4Material *{ return a->FindOrBuildMaterial(arg0); });
  t29.method("FindOrBuildMaterial", [](G4NistManager* a, const G4String & arg0, G4bool arg1)->G4Material *{ return a->FindOrBuildMaterial(arg0, arg1); });
  t29.method("FindOrBuildMaterial", [](G4NistManager* a, const G4String & arg0, G4bool arg1, G4bool arg2)->G4Material *{ return a->FindOrBuildMaterial(arg0, arg1, arg2); });

  DEBUG_MSG("Adding wrapper for G4Material * G4NistManager::FindSimpleMaterial(G4int) (" __HERE__ ")");
  // signature to use in the veto list: G4Material * G4NistManager::FindSimpleMaterial(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:186:22
  t29.method("FindSimpleMaterial", [](G4NistManager const& a, G4int arg0)->G4Material *{ return a.FindSimpleMaterial(arg0); });
  t29.method("FindSimpleMaterial", [](G4NistManager const* a, G4int arg0)->G4Material *{ return a->FindSimpleMaterial(arg0); });

  DEBUG_MSG("Adding wrapper for G4Material * G4NistManager::FindOrBuildSimpleMaterial(G4int, G4bool) (" __HERE__ ")");
  // signature to use in the veto list: G4Material * G4NistManager::FindOrBuildSimpleMaterial(G4int, G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:187:22
  t29.method("FindOrBuildSimpleMaterial", [](G4NistManager& a, G4int arg0)->G4Material *{ return a.FindOrBuildSimpleMaterial(arg0); });
  t29.method("FindOrBuildSimpleMaterial", [](G4NistManager& a, G4int arg0, G4bool arg1)->G4Material *{ return a.FindOrBuildSimpleMaterial(arg0, arg1); });
  t29.method("FindOrBuildSimpleMaterial", [](G4NistManager* a, G4int arg0)->G4Material *{ return a->FindOrBuildSimpleMaterial(arg0); });
  t29.method("FindOrBuildSimpleMaterial", [](G4NistManager* a, G4int arg0, G4bool arg1)->G4Material *{ return a->FindOrBuildSimpleMaterial(arg0, arg1); });

  DEBUG_MSG("Adding wrapper for G4Material * G4NistManager::BuildMaterialWithNewDensity(const G4String &, const G4String &, G4double, G4double, G4double) (" __HERE__ ")");
  // signature to use in the veto list: G4Material * G4NistManager::BuildMaterialWithNewDensity(const G4String &, const G4String &, G4double, G4double, G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:193:15
  t29.method("BuildMaterialWithNewDensity", [](G4NistManager& a, const G4String & arg0, const G4String & arg1)->G4Material *{ return a.BuildMaterialWithNewDensity(arg0, arg1); });
  t29.method("BuildMaterialWithNewDensity", [](G4NistManager& a, const G4String & arg0, const G4String & arg1, G4double arg2)->G4Material *{ return a.BuildMaterialWithNewDensity(arg0, arg1, arg2); });
  t29.method("BuildMaterialWithNewDensity", [](G4NistManager& a, const G4String & arg0, const G4String & arg1, G4double arg2, G4double arg3)->G4Material *{ return a.BuildMaterialWithNewDensity(arg0, arg1, arg2, arg3); });
  t29.method("BuildMaterialWithNewDensity", [](G4NistManager& a, const G4String & arg0, const G4String & arg1, G4double arg2, G4double arg3, G4double arg4)->G4Material *{ return a.BuildMaterialWithNewDensity(arg0, arg1, arg2, arg3, arg4); });
  t29.method("BuildMaterialWithNewDensity", [](G4NistManager* a, const G4String & arg0, const G4String & arg1)->G4Material *{ return a->BuildMaterialWithNewDensity(arg0, arg1); });
  t29.method("BuildMaterialWithNewDensity", [](G4NistManager* a, const G4String & arg0, const G4String & arg1, G4double arg2)->G4Material *{ return a->BuildMaterialWithNewDensity(arg0, arg1, arg2); });
  t29.method("BuildMaterialWithNewDensity", [](G4NistManager* a, const G4String & arg0, const G4String & arg1, G4double arg2, G4double arg3)->G4Material *{ return a->BuildMaterialWithNewDensity(arg0, arg1, arg2, arg3); });
  t29.method("BuildMaterialWithNewDensity", [](G4NistManager* a, const G4String & arg0, const G4String & arg1, G4double arg2, G4double arg3, G4double arg4)->G4Material *{ return a->BuildMaterialWithNewDensity(arg0, arg1, arg2, arg3, arg4); });

  DEBUG_MSG("Adding wrapper for G4Material * G4NistManager::ConstructNewMaterial(const G4String &, const int &, const int &, G4double, G4bool, G4State, G4double, G4double) (" __HERE__ ")");
  // signature to use in the veto list: G4Material * G4NistManager::ConstructNewMaterial(const G4String &, const int &, const int &, G4double, G4bool, G4State, G4double, G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:202:22
  t29.method("ConstructNewMaterial", [](G4NistManager& a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3)->G4Material *{ return a.ConstructNewMaterial(arg0, arg1, arg2, arg3); });
  t29.method("ConstructNewMaterial", [](G4NistManager& a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3, G4bool arg4)->G4Material *{ return a.ConstructNewMaterial(arg0, arg1, arg2, arg3, arg4); });
  t29.method("ConstructNewMaterial", [](G4NistManager& a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3, G4bool arg4, G4State arg5)->G4Material *{ return a.ConstructNewMaterial(arg0, arg1, arg2, arg3, arg4, arg5); });
  t29.method("ConstructNewMaterial", [](G4NistManager& a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3, G4bool arg4, G4State arg5, G4double arg6)->G4Material *{ return a.ConstructNewMaterial(arg0, arg1, arg2, arg3, arg4, arg5, arg6); });
  t29.method("ConstructNewMaterial", [](G4NistManager& a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3, G4bool arg4, G4State arg5, G4double arg6, G4double arg7)->G4Material *{ return a.ConstructNewMaterial(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7); });
  t29.method("ConstructNewMaterial", [](G4NistManager* a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3)->G4Material *{ return a->ConstructNewMaterial(arg0, arg1, arg2, arg3); });
  t29.method("ConstructNewMaterial", [](G4NistManager* a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3, G4bool arg4)->G4Material *{ return a->ConstructNewMaterial(arg0, arg1, arg2, arg3, arg4); });
  t29.method("ConstructNewMaterial", [](G4NistManager* a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3, G4bool arg4, G4State arg5)->G4Material *{ return a->ConstructNewMaterial(arg0, arg1, arg2, arg3, arg4, arg5); });
  t29.method("ConstructNewMaterial", [](G4NistManager* a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3, G4bool arg4, G4State arg5, G4double arg6)->G4Material *{ return a->ConstructNewMaterial(arg0, arg1, arg2, arg3, arg4, arg5, arg6); });
  t29.method("ConstructNewMaterial", [](G4NistManager* a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3, G4bool arg4, G4State arg5, G4double arg6, G4double arg7)->G4Material *{ return a->ConstructNewMaterial(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7); });

  DEBUG_MSG("Adding wrapper for G4Material * G4NistManager::ConstructNewMaterial(const G4String &, const int &, const int &, G4double, G4bool, G4State, G4double, G4double) (" __HERE__ ")");
  // signature to use in the veto list: G4Material * G4NistManager::ConstructNewMaterial(const G4String &, const int &, const int &, G4double, G4bool, G4State, G4double, G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:215:22
  t29.method("ConstructNewMaterial", [](G4NistManager& a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3)->G4Material *{ return a.ConstructNewMaterial(arg0, arg1, arg2, arg3); });
  t29.method("ConstructNewMaterial", [](G4NistManager& a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3, G4bool arg4)->G4Material *{ return a.ConstructNewMaterial(arg0, arg1, arg2, arg3, arg4); });
  t29.method("ConstructNewMaterial", [](G4NistManager& a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3, G4bool arg4, G4State arg5)->G4Material *{ return a.ConstructNewMaterial(arg0, arg1, arg2, arg3, arg4, arg5); });
  t29.method("ConstructNewMaterial", [](G4NistManager& a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3, G4bool arg4, G4State arg5, G4double arg6)->G4Material *{ return a.ConstructNewMaterial(arg0, arg1, arg2, arg3, arg4, arg5, arg6); });
  t29.method("ConstructNewMaterial", [](G4NistManager& a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3, G4bool arg4, G4State arg5, G4double arg6, G4double arg7)->G4Material *{ return a.ConstructNewMaterial(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7); });
  t29.method("ConstructNewMaterial", [](G4NistManager* a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3)->G4Material *{ return a->ConstructNewMaterial(arg0, arg1, arg2, arg3); });
  t29.method("ConstructNewMaterial", [](G4NistManager* a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3, G4bool arg4)->G4Material *{ return a->ConstructNewMaterial(arg0, arg1, arg2, arg3, arg4); });
  t29.method("ConstructNewMaterial", [](G4NistManager* a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3, G4bool arg4, G4State arg5)->G4Material *{ return a->ConstructNewMaterial(arg0, arg1, arg2, arg3, arg4, arg5); });
  t29.method("ConstructNewMaterial", [](G4NistManager* a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3, G4bool arg4, G4State arg5, G4double arg6)->G4Material *{ return a->ConstructNewMaterial(arg0, arg1, arg2, arg3, arg4, arg5, arg6); });
  t29.method("ConstructNewMaterial", [](G4NistManager* a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3, G4bool arg4, G4State arg5, G4double arg6, G4double arg7)->G4Material *{ return a->ConstructNewMaterial(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7); });

  DEBUG_MSG("Adding wrapper for G4Material * G4NistManager::ConstructNewGasMaterial(const G4String &, const G4String &, G4double, G4double, G4bool) (" __HERE__ ")");
  // signature to use in the veto list: G4Material * G4NistManager::ConstructNewGasMaterial(const G4String &, const G4String &, G4double, G4double, G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:227:22
  t29.method("ConstructNewGasMaterial", [](G4NistManager& a, const G4String & arg0, const G4String & arg1, G4double arg2, G4double arg3)->G4Material *{ return a.ConstructNewGasMaterial(arg0, arg1, arg2, arg3); });
  t29.method("ConstructNewGasMaterial", [](G4NistManager& a, const G4String & arg0, const G4String & arg1, G4double arg2, G4double arg3, G4bool arg4)->G4Material *{ return a.ConstructNewGasMaterial(arg0, arg1, arg2, arg3, arg4); });
  t29.method("ConstructNewGasMaterial", [](G4NistManager* a, const G4String & arg0, const G4String & arg1, G4double arg2, G4double arg3)->G4Material *{ return a->ConstructNewGasMaterial(arg0, arg1, arg2, arg3); });
  t29.method("ConstructNewGasMaterial", [](G4NistManager* a, const G4String & arg0, const G4String & arg1, G4double arg2, G4double arg3, G4bool arg4)->G4Material *{ return a->ConstructNewGasMaterial(arg0, arg1, arg2, arg3, arg4); });

  DEBUG_MSG("Adding wrapper for G4Material * G4NistManager::ConstructNewIdealGasMaterial(const G4String &, const int &, const int &, G4bool, G4double, G4double) (" __HERE__ ")");
  // signature to use in the veto list: G4Material * G4NistManager::ConstructNewIdealGasMaterial(const G4String &, const int &, const int &, G4bool, G4double, G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:235:22
  t29.method("ConstructNewIdealGasMaterial", [](G4NistManager& a, const G4String & arg0, const int & arg1, const int & arg2)->G4Material *{ return a.ConstructNewIdealGasMaterial(arg0, arg1, arg2); });
  t29.method("ConstructNewIdealGasMaterial", [](G4NistManager& a, const G4String & arg0, const int & arg1, const int & arg2, G4bool arg3)->G4Material *{ return a.ConstructNewIdealGasMaterial(arg0, arg1, arg2, arg3); });
  t29.method("ConstructNewIdealGasMaterial", [](G4NistManager& a, const G4String & arg0, const int & arg1, const int & arg2, G4bool arg3, G4double arg4)->G4Material *{ return a.ConstructNewIdealGasMaterial(arg0, arg1, arg2, arg3, arg4); });
  t29.method("ConstructNewIdealGasMaterial", [](G4NistManager& a, const G4String & arg0, const int & arg1, const int & arg2, G4bool arg3, G4double arg4, G4double arg5)->G4Material *{ return a.ConstructNewIdealGasMaterial(arg0, arg1, arg2, arg3, arg4, arg5); });
  t29.method("ConstructNewIdealGasMaterial", [](G4NistManager* a, const G4String & arg0, const int & arg1, const int & arg2)->G4Material *{ return a->ConstructNewIdealGasMaterial(arg0, arg1, arg2); });
  t29.method("ConstructNewIdealGasMaterial", [](G4NistManager* a, const G4String & arg0, const int & arg1, const int & arg2, G4bool arg3)->G4Material *{ return a->ConstructNewIdealGasMaterial(arg0, arg1, arg2, arg3); });
  t29.method("ConstructNewIdealGasMaterial", [](G4NistManager* a, const G4String & arg0, const int & arg1, const int & arg2, G4bool arg3, G4double arg4)->G4Material *{ return a->ConstructNewIdealGasMaterial(arg0, arg1, arg2, arg3, arg4); });
  t29.method("ConstructNewIdealGasMaterial", [](G4NistManager* a, const G4String & arg0, const int & arg1, const int & arg2, G4bool arg3, G4double arg4, G4double arg5)->G4Material *{ return a->ConstructNewIdealGasMaterial(arg0, arg1, arg2, arg3, arg4, arg5); });

  DEBUG_MSG("Adding wrapper for void G4NistManager::SetDensityEffectCalculatorFlag(const G4String &, G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4NistManager::SetDensityEffectCalculatorFlag(const G4String &, G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:245:8
  t29.method("SetDensityEffectCalculatorFlag", [](G4NistManager& a, const G4String & arg0, G4bool arg1)->void{ a.SetDensityEffectCalculatorFlag(arg0, arg1); });
  t29.method("SetDensityEffectCalculatorFlag", [](G4NistManager* a, const G4String & arg0, G4bool arg1)->void{ a->SetDensityEffectCalculatorFlag(arg0, arg1); });

  DEBUG_MSG("Adding wrapper for void G4NistManager::SetDensityEffectCalculatorFlag(G4Material *, G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4NistManager::SetDensityEffectCalculatorFlag(G4Material *, G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:249:8
  t29.method("SetDensityEffectCalculatorFlag", [](G4NistManager& a, G4Material * arg0, G4bool arg1)->void{ a.SetDensityEffectCalculatorFlag(arg0, arg1); });
  t29.method("SetDensityEffectCalculatorFlag", [](G4NistManager* a, G4Material * arg0, G4bool arg1)->void{ a->SetDensityEffectCalculatorFlag(arg0, arg1); });

  DEBUG_MSG("Adding wrapper for int G4NistManager::GetNumberOfMaterials() (" __HERE__ ")");
  // signature to use in the veto list: int G4NistManager::GetNumberOfMaterials()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:253:17
  t29.method("GetNumberOfMaterials", [](G4NistManager const& a)->int{ return a.GetNumberOfMaterials(); });
  t29.method("GetNumberOfMaterials", [](G4NistManager const* a)->int{ return a->GetNumberOfMaterials(); });

  DEBUG_MSG("Adding wrapper for G4int G4NistManager::GetVerbose() (" __HERE__ ")");
  // signature to use in the veto list: G4int G4NistManager::GetVerbose()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:255:16
  t29.method("GetVerbose", [](G4NistManager const& a)->G4int{ return a.GetVerbose(); });
  t29.method("GetVerbose", [](G4NistManager const* a)->G4int{ return a->GetVerbose(); });

  DEBUG_MSG("Adding wrapper for void G4NistManager::SetVerbose(G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4NistManager::SetVerbose(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:257:8
  t29.method("SetVerbose", [](G4NistManager& a, G4int arg0)->void{ a.SetVerbose(arg0); });
  t29.method("SetVerbose", [](G4NistManager* a, G4int arg0)->void{ a->SetVerbose(arg0); });

  DEBUG_MSG("Adding wrapper for void G4NistManager::PrintG4Material(const G4String &) (" __HERE__ ")");
  // signature to use in the veto list: void G4NistManager::PrintG4Material(const G4String &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:261:8
  t29.method("PrintG4Material", [](G4NistManager const& a, const G4String & arg0)->void{ a.PrintG4Material(arg0); });
  t29.method("PrintG4Material", [](G4NistManager const* a, const G4String & arg0)->void{ a->PrintG4Material(arg0); });

  DEBUG_MSG("Adding wrapper for void G4NistManager::ListMaterials(const G4String &) (" __HERE__ ")");
  // signature to use in the veto list: void G4NistManager::ListMaterials(const G4String &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:270:15
  t29.method("ListMaterials", [](G4NistManager const& a, const G4String & arg0)->void{ a.ListMaterials(arg0); });
  t29.method("ListMaterials", [](G4NistManager const* a, const G4String & arg0)->void{ a->ListMaterials(arg0); });

  DEBUG_MSG("Adding wrapper for const int & G4NistManager::GetNistMaterialNames() (" __HERE__ ")");
  // signature to use in the veto list: const int & G4NistManager::GetNistMaterialNames()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:274:39
  t29.method("GetNistMaterialNames", [](G4NistManager const& a)->const int &{ return a.GetNistMaterialNames(); });
  t29.method("GetNistMaterialNames", [](G4NistManager const* a)->const int &{ return a->GetNistMaterialNames(); });

  DEBUG_MSG("Adding wrapper for G4double G4NistManager::GetZ13(G4double) (" __HERE__ ")");
  // signature to use in the veto list: G4double G4NistManager::GetZ13(G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:278:19
  t29.method("GetZ13", [](G4NistManager const& a, G4double arg0)->G4double{ return a.GetZ13(arg0); });
  t29.method("GetZ13", [](G4NistManager const* a, G4double arg0)->G4double{ return a->GetZ13(arg0); });

  DEBUG_MSG("Adding wrapper for G4double G4NistManager::GetZ13(G4int) (" __HERE__ ")");
  // signature to use in the veto list: G4double G4NistManager::GetZ13(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:279:19
  t29.method("GetZ13", [](G4NistManager const& a, G4int arg0)->G4double{ return a.GetZ13(arg0); });
  t29.method("GetZ13", [](G4NistManager const* a, G4int arg0)->G4double{ return a->GetZ13(arg0); });

  DEBUG_MSG("Adding wrapper for G4double G4NistManager::GetA27(G4int) (" __HERE__ ")");
  // signature to use in the veto list: G4double G4NistManager::GetA27(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:283:19
  t29.method("GetA27", [](G4NistManager const& a, G4int arg0)->G4double{ return a.GetA27(arg0); });
  t29.method("GetA27", [](G4NistManager const* a, G4int arg0)->G4double{ return a->GetA27(arg0); });

  DEBUG_MSG("Adding wrapper for G4double G4NistManager::GetLOGZ(G4int) (" __HERE__ ")");
  // signature to use in the veto list: G4double G4NistManager::GetLOGZ(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:287:19
  t29.method("GetLOGZ", [](G4NistManager const& a, G4int arg0)->G4double{ return a.GetLOGZ(arg0); });
  t29.method("GetLOGZ", [](G4NistManager const* a, G4int arg0)->G4double{ return a->GetLOGZ(arg0); });

  DEBUG_MSG("Adding wrapper for G4double G4NistManager::GetLOGAMU(G4int) (" __HERE__ ")");
  // signature to use in the veto list: G4double G4NistManager::GetLOGAMU(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:288:19
  t29.method("GetLOGAMU", [](G4NistManager const& a, G4int arg0)->G4double{ return a.GetLOGAMU(arg0); });
  t29.method("GetLOGAMU", [](G4NistManager const* a, G4int arg0)->G4double{ return a->GetLOGAMU(arg0); });

  DEBUG_MSG("Adding wrapper for G4ICRU90StoppingData * G4NistManager::GetICRU90StoppingData() (" __HERE__ ")");
  // signature to use in the veto list: G4ICRU90StoppingData * G4NistManager::GetICRU90StoppingData()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:290:25
  t29.method("GetICRU90StoppingData", [](G4NistManager& a)->G4ICRU90StoppingData *{ return a.GetICRU90StoppingData(); });
  t29.method("GetICRU90StoppingData", [](G4NistManager* a)->G4ICRU90StoppingData *{ return a->GetICRU90StoppingData(); });

  DEBUG_MSG("Adding wrapper for int G4NistManager::GetNumberOfMaterials() (" __HERE__ ")");
  // signature to use in the veto list: int G4NistManager::GetNumberOfMaterials()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:322:30
  t29.method("GetNumberOfMaterials", [](G4NistManager const& a)->int{ return a.GetNumberOfMaterials(); });
  t29.method("GetNumberOfMaterials", [](G4NistManager const* a)->int{ return a->GetNumberOfMaterials(); });

  DEBUG_MSG("Adding wrapper for G4Element * G4NistManager::GetElement(int) (" __HERE__ ")");
  // signature to use in the veto list: G4Element * G4NistManager::GetElement(int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:329:34
  t29.method("GetElement", [](G4NistManager const& a, int arg0)->G4Element *{ return a.GetElement(arg0); });
  t29.method("GetElement", [](G4NistManager const* a, int arg0)->G4Element *{ return a->GetElement(arg0); });

  DEBUG_MSG("Adding wrapper for int G4NistManager::GetNumberOfElements() (" __HERE__ ")");
  // signature to use in the veto list: int G4NistManager::GetNumberOfElements()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:362:30
  t29.method("GetNumberOfElements", [](G4NistManager const& a)->int{ return a.GetNumberOfElements(); });
  t29.method("GetNumberOfElements", [](G4NistManager const* a)->int{ return a->GetNumberOfElements(); });

  DEBUG_MSG("Adding wrapper for const int & G4NistManager::GetNistElementNames() (" __HERE__ ")");
  // signature to use in the veto list: const int & G4NistManager::GetNistElementNames()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:439:45
  t29.method("GetNistElementNames", [](G4NistManager const& a)->const int &{ return a.GetNistElementNames(); });
  t29.method("GetNistElementNames", [](G4NistManager const* a)->const int &{ return a->GetNistElementNames(); });

  DEBUG_MSG("Adding wrapper for G4Material * G4NistManager::GetMaterial(int) (" __HERE__ ")");
  // signature to use in the veto list: G4Material * G4NistManager::GetMaterial(int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:467:35
  t29.method("GetMaterial", [](G4NistManager const& a, int arg0)->G4Material *{ return a.GetMaterial(arg0); });
  t29.method("GetMaterial", [](G4NistManager const* a, int arg0)->G4Material *{ return a->GetMaterial(arg0); });

  DEBUG_MSG("Adding wrapper for G4Material * G4NistManager::ConstructNewMaterial(const G4String &, const int &, const int &, G4double, G4bool, G4State, G4double, G4double) (" __HERE__ ")");
  // signature to use in the veto list: G4Material * G4NistManager::ConstructNewMaterial(const G4String &, const int &, const int &, G4double, G4bool, G4State, G4double, G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:515:35
  t29.method("ConstructNewMaterial", [](G4NistManager& a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3, G4bool arg4, G4State arg5, G4double arg6, G4double arg7)->G4Material *{ return a.ConstructNewMaterial(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7); });
  t29.method("ConstructNewMaterial", [](G4NistManager* a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3, G4bool arg4, G4State arg5, G4double arg6, G4double arg7)->G4Material *{ return a->ConstructNewMaterial(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7); });

  DEBUG_MSG("Adding wrapper for G4Material * G4NistManager::ConstructNewMaterial(const G4String &, const int &, const int &, G4double, G4bool, G4State, G4double, G4double) (" __HERE__ ")");
  // signature to use in the veto list: G4Material * G4NistManager::ConstructNewMaterial(const G4String &, const int &, const int &, G4double, G4bool, G4State, G4double, G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:532:35
  t29.method("ConstructNewMaterial", [](G4NistManager& a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3, G4bool arg4, G4State arg5, G4double arg6, G4double arg7)->G4Material *{ return a.ConstructNewMaterial(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7); });
  t29.method("ConstructNewMaterial", [](G4NistManager* a, const G4String & arg0, const int & arg1, const int & arg2, G4double arg3, G4bool arg4, G4State arg5, G4double arg6, G4double arg7)->G4Material *{ return a->ConstructNewMaterial(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7); });

  DEBUG_MSG("Adding wrapper for G4Material * G4NistManager::ConstructNewIdealGasMaterial(const G4String &, const int &, const int &, G4bool, G4double, G4double) (" __HERE__ ")");
  // signature to use in the veto list: G4Material * G4NistManager::ConstructNewIdealGasMaterial(const G4String &, const int &, const int &, G4bool, G4double, G4double)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:558:35
  t29.method("ConstructNewIdealGasMaterial", [](G4NistManager& a, const G4String & arg0, const int & arg1, const int & arg2, G4bool arg3, G4double arg4, G4double arg5)->G4Material *{ return a.ConstructNewIdealGasMaterial(arg0, arg1, arg2, arg3, arg4, arg5); });
  t29.method("ConstructNewIdealGasMaterial", [](G4NistManager* a, const G4String & arg0, const int & arg1, const int & arg2, G4bool arg3, G4double arg4, G4double arg5)->G4Material *{ return a->ConstructNewIdealGasMaterial(arg0, arg1, arg2, arg3, arg4, arg5); });

  DEBUG_MSG("Adding wrapper for const int & G4NistManager::GetNistMaterialNames() (" __HERE__ ")");
  // signature to use in the veto list: const int & G4NistManager::GetNistMaterialNames()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NistManager.hh:580:45
  t29.method("GetNistMaterialNames", [](G4NistManager const& a)->const int &{ return a.GetNistMaterialNames(); });
  t29.method("GetNistMaterialNames", [](G4NistManager const* a)->const int &{ return a->GetNistMaterialNames(); });

  /* End of G4NistManager class method wrappers
   **********************************************************************/


  /**********************************************************************/
  /* Wrappers for the methods of class G4PVPlacement
   */


  DEBUG_MSG("Adding wrapper for void G4PVPlacement::G4PVPlacement(G4RotationMatrix *, const G4ThreeVector &, G4LogicalVolume *, const G4String &, G4LogicalVolume *, G4bool, G4int, G4bool) (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4PVPlacement.hh:47:5
  t33.constructor<G4RotationMatrix *, const G4ThreeVector &, G4LogicalVolume *, const G4String &, G4LogicalVolume *, G4bool, G4int>();
  t33.constructor<G4RotationMatrix *, const G4ThreeVector &, G4LogicalVolume *, const G4String &, G4LogicalVolume *, G4bool, G4int, G4bool>();


  DEBUG_MSG("Adding wrapper for void G4PVPlacement::G4PVPlacement(const G4Transform3D &, G4LogicalVolume *, const G4String &, G4LogicalVolume *, G4bool, G4int, G4bool) (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4PVPlacement.hh:69:5
  t33.constructor<const G4Transform3D &, G4LogicalVolume *, const G4String &, G4LogicalVolume *, G4bool, G4int>();
  t33.constructor<const G4Transform3D &, G4LogicalVolume *, const G4String &, G4LogicalVolume *, G4bool, G4int, G4bool>();


  DEBUG_MSG("Adding wrapper for void G4PVPlacement::G4PVPlacement(G4RotationMatrix *, const G4ThreeVector &, const G4String &, G4LogicalVolume *, G4VPhysicalVolume *, G4bool, G4int, G4bool) (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4PVPlacement.hh:90:5
  t33.constructor<G4RotationMatrix *, const G4ThreeVector &, const G4String &, G4LogicalVolume *, G4VPhysicalVolume *, G4bool, G4int>();
  t33.constructor<G4RotationMatrix *, const G4ThreeVector &, const G4String &, G4LogicalVolume *, G4VPhysicalVolume *, G4bool, G4int, G4bool>();


  DEBUG_MSG("Adding wrapper for void G4PVPlacement::G4PVPlacement(const G4Transform3D &, const G4String &, G4LogicalVolume *, G4VPhysicalVolume *, G4bool, G4int, G4bool) (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4PVPlacement.hh:102:5
  t33.constructor<const G4Transform3D &, const G4String &, G4LogicalVolume *, G4VPhysicalVolume *, G4bool, G4int>();
  t33.constructor<const G4Transform3D &, const G4String &, G4LogicalVolume *, G4VPhysicalVolume *, G4bool, G4int, G4bool>();

  DEBUG_MSG("Adding wrapper for G4int G4PVPlacement::GetCopyNo() (" __HERE__ ")");
  // signature to use in the veto list: G4int G4PVPlacement::GetCopyNo()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4PVPlacement.hh:117:18
  t33.method("GetCopyNo", [](G4PVPlacement const& a)->G4int{ return a.GetCopyNo(); });
  t33.method("GetCopyNo", [](G4PVPlacement const* a)->G4int{ return a->GetCopyNo(); });

  DEBUG_MSG("Adding wrapper for void G4PVPlacement::SetCopyNo(G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4PVPlacement::SetCopyNo(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4PVPlacement.hh:119:10
  t33.method("SetCopyNo", [](G4PVPlacement& a, G4int arg0)->void{ a.SetCopyNo(arg0); });
  t33.method("SetCopyNo", [](G4PVPlacement* a, G4int arg0)->void{ a->SetCopyNo(arg0); });

  DEBUG_MSG("Adding wrapper for G4bool G4PVPlacement::CheckOverlaps(G4int, G4double, G4bool, G4int) (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4PVPlacement::CheckOverlaps(G4int, G4double, G4bool, G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4PVPlacement.hh:122:12
  t33.method("CheckOverlaps", [](G4PVPlacement& a)->G4bool{ return a.CheckOverlaps(); });
  t33.method("CheckOverlaps", [](G4PVPlacement& a, G4int arg0)->G4bool{ return a.CheckOverlaps(arg0); });
  t33.method("CheckOverlaps", [](G4PVPlacement& a, G4int arg0, G4double arg1)->G4bool{ return a.CheckOverlaps(arg0, arg1); });
  t33.method("CheckOverlaps", [](G4PVPlacement& a, G4int arg0, G4double arg1, G4bool arg2)->G4bool{ return a.CheckOverlaps(arg0, arg1, arg2); });
  t33.method("CheckOverlaps", [](G4PVPlacement& a, G4int arg0, G4double arg1, G4bool arg2, G4int arg3)->G4bool{ return a.CheckOverlaps(arg0, arg1, arg2, arg3); });
  t33.method("CheckOverlaps", [](G4PVPlacement* a)->G4bool{ return a->CheckOverlaps(); });
  t33.method("CheckOverlaps", [](G4PVPlacement* a, G4int arg0)->G4bool{ return a->CheckOverlaps(arg0); });
  t33.method("CheckOverlaps", [](G4PVPlacement* a, G4int arg0, G4double arg1)->G4bool{ return a->CheckOverlaps(arg0, arg1); });
  t33.method("CheckOverlaps", [](G4PVPlacement* a, G4int arg0, G4double arg1, G4bool arg2)->G4bool{ return a->CheckOverlaps(arg0, arg1, arg2); });
  t33.method("CheckOverlaps", [](G4PVPlacement* a, G4int arg0, G4double arg1, G4bool arg2, G4int arg3)->G4bool{ return a->CheckOverlaps(arg0, arg1, arg2, arg3); });

  DEBUG_MSG("Adding wrapper for G4bool G4PVPlacement::IsMany() (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4PVPlacement::IsMany()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4PVPlacement.hh:143:12
  t33.method("IsMany", [](G4PVPlacement const& a)->G4bool{ return a.IsMany(); });
  t33.method("IsMany", [](G4PVPlacement const* a)->G4bool{ return a->IsMany(); });

  DEBUG_MSG("Adding wrapper for G4bool G4PVPlacement::IsReplicated() (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4PVPlacement::IsReplicated()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4PVPlacement.hh:144:12
  t33.method("IsReplicated", [](G4PVPlacement const& a)->G4bool{ return a.IsReplicated(); });
  t33.method("IsReplicated", [](G4PVPlacement const* a)->G4bool{ return a->IsReplicated(); });

  DEBUG_MSG("Adding wrapper for G4bool G4PVPlacement::IsParameterised() (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4PVPlacement::IsParameterised()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4PVPlacement.hh:145:12
  t33.method("IsParameterised", [](G4PVPlacement const& a)->G4bool{ return a.IsParameterised(); });
  t33.method("IsParameterised", [](G4PVPlacement const* a)->G4bool{ return a->IsParameterised(); });

  DEBUG_MSG("Adding wrapper for G4VPVParameterisation * G4PVPlacement::GetParameterisation() (" __HERE__ ")");
  // signature to use in the veto list: G4VPVParameterisation * G4PVPlacement::GetParameterisation()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4PVPlacement.hh:146:28
  t33.method("GetParameterisation", [](G4PVPlacement const& a)->G4VPVParameterisation *{ return a.GetParameterisation(); });
  t33.method("GetParameterisation", [](G4PVPlacement const* a)->G4VPVParameterisation *{ return a->GetParameterisation(); });

  DEBUG_MSG("Adding wrapper for void G4PVPlacement::GetReplicationData(EAxis &, G4int &, G4double &, G4double &, G4bool &) (" __HERE__ ")");
  // signature to use in the veto list: void G4PVPlacement::GetReplicationData(EAxis &, G4int &, G4double &, G4double &, G4bool &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4PVPlacement.hh:147:10
  t33.method("GetReplicationData", [](G4PVPlacement const& a, EAxis & arg0, G4int & arg1, G4double & arg2, G4double & arg3, G4bool & arg4)->void{ a.GetReplicationData(arg0, arg1, arg2, arg3, arg4); });
  t33.method("GetReplicationData", [](G4PVPlacement const* a, EAxis & arg0, G4int & arg1, G4double & arg2, G4double & arg3, G4bool & arg4)->void{ a->GetReplicationData(arg0, arg1, arg2, arg3, arg4); });

  DEBUG_MSG("Adding wrapper for G4bool G4PVPlacement::IsRegularStructure() (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4PVPlacement::IsRegularStructure()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4PVPlacement.hh:152:12
  t33.method("IsRegularStructure", [](G4PVPlacement const& a)->G4bool{ return a.IsRegularStructure(); });
  t33.method("IsRegularStructure", [](G4PVPlacement const* a)->G4bool{ return a->IsRegularStructure(); });

  DEBUG_MSG("Adding wrapper for G4int G4PVPlacement::GetRegularStructureId() (" __HERE__ ")");
  // signature to use in the veto list: G4int G4PVPlacement::GetRegularStructureId()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4PVPlacement.hh:153:11
  t33.method("GetRegularStructureId", [](G4PVPlacement const& a)->G4int{ return a.GetRegularStructureId(); });
  t33.method("GetRegularStructureId", [](G4PVPlacement const* a)->G4int{ return a->GetRegularStructureId(); });

  DEBUG_MSG("Adding wrapper for EVolume G4PVPlacement::VolumeType() (" __HERE__ ")");
  // signature to use in the veto list: EVolume G4PVPlacement::VolumeType()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4PVPlacement.hh:155:13
  t33.method("VolumeType", [](G4PVPlacement const& a)->EVolume{ return a.VolumeType(); });
  t33.method("VolumeType", [](G4PVPlacement const* a)->EVolume{ return a->VolumeType(); });

  /* End of G4PVPlacement class method wrappers
   **********************************************************************/

  /**********************************************************************
   * Wrappers for global functions and variables including
   * class static members
   */

  DEBUG_MSG("Adding wrapper for char * G4JL_getenv(const std::string &) (" __HERE__ ")");
  // signature to use in the veto list: char * G4JL_getenv(const std::string &)
  // defined in ./cpp/Geant4Wrap.h:16:7
  types.method("G4JL_getenv", [](const std::string & arg0)->char *{ return G4JL_getenv(arg0); });

  DEBUG_MSG("Adding wrapper for char * G4JL_setenv(const std::string &, const std::string &) (" __HERE__ ")");
  // signature to use in the veto list: char * G4JL_setenv(const std::string &, const std::string &)
  // defined in ./cpp/Geant4Wrap.h:17:7
  types.method("G4JL_setenv", [](const std::string & arg0, const std::string & arg1)->char *{ return G4JL_setenv(arg0, arg1); });

  DEBUG_MSG("Adding wrapper for void G4JL_init() (" __HERE__ ")");
  // signature to use in the veto list: void G4JL_init()
  // defined in ./cpp/Geant4Wrap.h:19:6
  types.method("G4JL_init", []()->void{ G4JL_init(); });
  /* End of global function wrappers
   **********************************************************************/

  DEBUG_MSG("End of wrapper definitions");

}
