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
  template<> struct IsMirroredType<G4VPhysicalVolume> : std::false_type { };
  template<> struct IsMirroredType<G4VSolid> : std::false_type { };
  template<> struct IsMirroredType<G4AffineTransform> : std::false_type { };
  template<> struct IsMirroredType<G4NavigationLevelRep> : std::false_type { };
  template<> struct IsMirroredType<G4RunManager> : std::false_type { };
  template<> struct IsMirroredType<G4Event> : std::false_type { };
  template<> struct IsMirroredType<G4Region> : std::false_type { };
  template<> struct IsMirroredType<G4LogicalVolume> : std::false_type { };
  template<> struct IsMirroredType<G4UserStackingAction> : std::false_type { };
  template<> struct IsMirroredType<G4UserTrackingAction> : std::false_type { };
  template<> struct IsMirroredType<G4UserSteppingAction> : std::false_type { };
  template<> struct IsMirroredType<G4PrimaryTransformer> : std::false_type { };
  template<> struct IsMirroredType<G4ThreeVector> : std::false_type { };
  template<> struct IsMirroredType<G4RotationMatrix> : std::false_type { };
  template<> struct SuperType<G4String> { typedef std::string type; };
}

JLCXX_MODULE define_julia_module(jlcxx::Module& types){

  types.method("_getenv", [](const std::string& x) { return std::getenv(x.c_str()); });
  types.method("_setenv", [](const std::string& x, const std::string& v) { return setenv(x.c_str(), v.c_str(), 1); });

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

  DEBUG_MSG("Adding wrapper for type G4String (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4String.hh:61:7
  //auto t0 = types.add_type<G4String>("G4String");
  auto t0 = types.add_type<G4String>("G4String", jlcxx::julia_base_type<std::string>())

  DEBUG_MSG("Adding wrapper for type G4VPhysicalVolume (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4VPhysicalVolume.hh:78:7
  auto t1 = types.add_type<G4VPhysicalVolume>("G4VPhysicalVolume");

  DEBUG_MSG("Adding wrapper for type G4VSolid (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4VSolid.hh:82:7
  auto t2 = types.add_type<G4VSolid>("G4VSolid");

  DEBUG_MSG("Adding wrapper for type G4AffineTransform (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4AffineTransform.hh:69:7
  auto t3 = types.add_type<G4AffineTransform>("G4AffineTransform");

  DEBUG_MSG("Adding wrapper for type G4NavigationLevelRep (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NavigationLevelRep.hh:50:7
  auto t5 = types.add_type<G4NavigationLevelRep>("G4NavigationLevelRep");

  DEBUG_MSG("Adding wrapper for type G4RunManager (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:137:7
  auto t6 = types.add_type<G4RunManager>("G4RunManager");

  DEBUG_MSG("Adding wrapper for type G4Event (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4Event.hh:54:7
  auto t7 = types.add_type<G4Event>("G4Event");

  DEBUG_MSG("Adding wrapper for type G4Region (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4Region.hh:95:7
  auto t8 = types.add_type<G4Region>("G4Region");

  DEBUG_MSG("Adding wrapper for type G4LogicalVolume (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4LogicalVolume.hh:181:7
  auto t9 = types.add_type<G4LogicalVolume>("G4LogicalVolume");

  DEBUG_MSG("Adding wrapper for type G4UserStackingAction (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UserStackingAction.hh:44:7
  auto t10 = types.add_type<G4UserStackingAction>("G4UserStackingAction");

  DEBUG_MSG("Adding wrapper for type G4UserTrackingAction (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UserTrackingAction.hh:44:7
  auto t11 = types.add_type<G4UserTrackingAction>("G4UserTrackingAction");

  DEBUG_MSG("Adding wrapper for type G4UserSteppingAction (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4UserSteppingAction.hh:44:7
  auto t12 = types.add_type<G4UserSteppingAction>("G4UserSteppingAction");

  DEBUG_MSG("Adding wrapper for type G4PrimaryTransformer (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4PrimaryTransformer.hh:47:7
  auto t13 = types.add_type<G4PrimaryTransformer>("G4PrimaryTransformer");

  /**********************************************************************
   * Wrappers for typedefs
   */
  DEBUG_MSG("Adding wrapper for type G4ThreeVector (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4ThreeVector.hh:36:7
  types.add_type<G4ThreeVector>("G4ThreeVector");

  DEBUG_MSG("Adding wrapper for type G4RotationMatrix (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RotationMatrix.hh:37:7
  types.add_type<G4RotationMatrix>("G4RotationMatrix");


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
  /* Wrappers for the methods of class G4NavigationLevelRep
   */


  DEBUG_MSG("Adding wrapper for void G4NavigationLevelRep::G4NavigationLevelRep(G4NavigationLevelRep &) (" __HERE__ ")");
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4NavigationLevelRep.icc:69:23
  t5.constructor<G4NavigationLevelRep &>();

  /* End of G4NavigationLevelRep class method wrappers
   **********************************************************************/


  /**********************************************************************/
  /* Wrappers for the methods of class G4RunManager
   */

  DEBUG_MSG("Adding wrapper for void G4RunManager::BeamOn(G4int, const char *, G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::BeamOn(G4int, const char *, G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:163:18
  t6.method("BeamOn", static_cast<void (G4RunManager::*)(G4int, const char *, G4int) >(&G4RunManager::BeamOn));
  t6.method("BeamOn", [](G4RunManager& a, G4int arg0)->void{ a.BeamOn(arg0); });
  t6.method("BeamOn", [](G4RunManager& a, G4int arg0, const char * arg1)->void{ a.BeamOn(arg0, arg1); });
  t6.method("BeamOn", [](G4RunManager* a, G4int arg0)->void{ a->BeamOn(arg0); });
  t6.method("BeamOn", [](G4RunManager* a, G4int arg0, const char * arg1)->void{ a->BeamOn(arg0, arg1); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::Initialize() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::Initialize()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:175:18
  t6.method("Initialize", static_cast<void (G4RunManager::*)() >(&G4RunManager::Initialize));

  DEBUG_MSG("Adding wrapper for void G4RunManager::DefineWorldVolume(G4VPhysicalVolume *, G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::DefineWorldVolume(G4VPhysicalVolume *, G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:188:18
  t6.method("DefineWorldVolume", static_cast<void (G4RunManager::*)(G4VPhysicalVolume *, G4bool) >(&G4RunManager::DefineWorldVolume));
  t6.method("DefineWorldVolume", [](G4RunManager& a, G4VPhysicalVolume * arg0)->void{ a.DefineWorldVolume(arg0); });
  t6.method("DefineWorldVolume", [](G4RunManager* a, G4VPhysicalVolume * arg0)->void{ a->DefineWorldVolume(arg0); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::AbortRun(G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::AbortRun(G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:197:18
  t6.method("AbortRun", static_cast<void (G4RunManager::*)(G4bool) >(&G4RunManager::AbortRun));
  t6.method("AbortRun", [](G4RunManager& a)->void{ a.AbortRun(); });
  t6.method("AbortRun", [](G4RunManager* a)->void{ a->AbortRun(); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::AbortEvent() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::AbortEvent()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:206:18
  t6.method("AbortEvent", static_cast<void (G4RunManager::*)() >(&G4RunManager::AbortEvent));

  DEBUG_MSG("Adding wrapper for void G4RunManager::InitializeGeometry() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::InitializeGeometry()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:211:18
  t6.method("InitializeGeometry", static_cast<void (G4RunManager::*)() >(&G4RunManager::InitializeGeometry));

  DEBUG_MSG("Adding wrapper for void G4RunManager::InitializePhysics() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::InitializePhysics()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:212:18
  t6.method("InitializePhysics", static_cast<void (G4RunManager::*)() >(&G4RunManager::InitializePhysics));

  DEBUG_MSG("Adding wrapper for G4bool G4RunManager::ConfirmBeamOnCondition() (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4RunManager::ConfirmBeamOnCondition()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:219:20
  t6.method("ConfirmBeamOnCondition", static_cast<G4bool (G4RunManager::*)() >(&G4RunManager::ConfirmBeamOnCondition));

  DEBUG_MSG("Adding wrapper for void G4RunManager::RunInitialization() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::RunInitialization()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:220:18
  t6.method("RunInitialization", static_cast<void (G4RunManager::*)() >(&G4RunManager::RunInitialization));

  DEBUG_MSG("Adding wrapper for void G4RunManager::DoEventLoop(G4int, const char *, G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::DoEventLoop(G4int, const char *, G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:221:18
  t6.method("DoEventLoop", static_cast<void (G4RunManager::*)(G4int, const char *, G4int) >(&G4RunManager::DoEventLoop));
  t6.method("DoEventLoop", [](G4RunManager& a, G4int arg0)->void{ a.DoEventLoop(arg0); });
  t6.method("DoEventLoop", [](G4RunManager& a, G4int arg0, const char * arg1)->void{ a.DoEventLoop(arg0, arg1); });
  t6.method("DoEventLoop", [](G4RunManager* a, G4int arg0)->void{ a->DoEventLoop(arg0); });
  t6.method("DoEventLoop", [](G4RunManager* a, G4int arg0, const char * arg1)->void{ a->DoEventLoop(arg0, arg1); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::RunTermination() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::RunTermination()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:223:18
  t6.method("RunTermination", static_cast<void (G4RunManager::*)() >(&G4RunManager::RunTermination));

  DEBUG_MSG("Adding wrapper for void G4RunManager::InitializeEventLoop(G4int, const char *, G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::InitializeEventLoop(G4int, const char *, G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:240:18
  t6.method("InitializeEventLoop", static_cast<void (G4RunManager::*)(G4int, const char *, G4int) >(&G4RunManager::InitializeEventLoop));
  t6.method("InitializeEventLoop", [](G4RunManager& a, G4int arg0)->void{ a.InitializeEventLoop(arg0); });
  t6.method("InitializeEventLoop", [](G4RunManager& a, G4int arg0, const char * arg1)->void{ a.InitializeEventLoop(arg0, arg1); });
  t6.method("InitializeEventLoop", [](G4RunManager* a, G4int arg0)->void{ a->InitializeEventLoop(arg0); });
  t6.method("InitializeEventLoop", [](G4RunManager* a, G4int arg0, const char * arg1)->void{ a->InitializeEventLoop(arg0, arg1); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::ProcessOneEvent(G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::ProcessOneEvent(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:243:18
  t6.method("ProcessOneEvent", static_cast<void (G4RunManager::*)(G4int) >(&G4RunManager::ProcessOneEvent));

  DEBUG_MSG("Adding wrapper for void G4RunManager::TerminateOneEvent() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::TerminateOneEvent()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:244:18
  t6.method("TerminateOneEvent", static_cast<void (G4RunManager::*)() >(&G4RunManager::TerminateOneEvent));

  DEBUG_MSG("Adding wrapper for void G4RunManager::TerminateEventLoop() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::TerminateEventLoop()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:245:18
  t6.method("TerminateEventLoop", static_cast<void (G4RunManager::*)() >(&G4RunManager::TerminateEventLoop));

  DEBUG_MSG("Adding wrapper for G4Event * G4RunManager::GenerateEvent(G4int) (" __HERE__ ")");
  // signature to use in the veto list: G4Event * G4RunManager::GenerateEvent(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:248:22
  t6.method("GenerateEvent", static_cast<G4Event * (G4RunManager::*)(G4int) >(&G4RunManager::GenerateEvent));

  DEBUG_MSG("Adding wrapper for void G4RunManager::AnalyzeEvent(G4Event *) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::AnalyzeEvent(G4Event *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:249:18
  t6.method("AnalyzeEvent", static_cast<void (G4RunManager::*)(G4Event *) >(&G4RunManager::AnalyzeEvent));

  DEBUG_MSG("Adding wrapper for void G4RunManager::ConfigureProfilers(const int &) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::ConfigureProfilers(const int &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:259:18
  t6.method("ConfigureProfilers", static_cast<void (G4RunManager::*)(const int &) >(&G4RunManager::ConfigureProfilers));
  t6.method("ConfigureProfilers", [](G4RunManager& a)->void{ a.ConfigureProfilers(); });
  t6.method("ConfigureProfilers", [](G4RunManager* a)->void{ a->ConfigureProfilers(); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::ConfigureProfilers(G4int, char **) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::ConfigureProfilers(G4int, char **)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:261:10
  t6.method("ConfigureProfilers", static_cast<void (G4RunManager::*)(G4int, char **) >(&G4RunManager::ConfigureProfilers));

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetNumberOfThreads(G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetNumberOfThreads(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:264:18
  t6.method("SetNumberOfThreads", static_cast<void (G4RunManager::*)(G4int) >(&G4RunManager::SetNumberOfThreads));

  DEBUG_MSG("Adding wrapper for G4int G4RunManager::GetNumberOfThreads() (" __HERE__ ")");
  // signature to use in the veto list: G4int G4RunManager::GetNumberOfThreads()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:265:19
  t6.method("GetNumberOfThreads", static_cast<G4int (G4RunManager::*)()  const>(&G4RunManager::GetNumberOfThreads));

  DEBUG_MSG("Adding wrapper for void G4RunManager::DumpRegion(const G4String &) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::DumpRegion(const G4String &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:269:10
  t6.method("DumpRegion", static_cast<void (G4RunManager::*)(const G4String &)  const>(&G4RunManager::DumpRegion));

  DEBUG_MSG("Adding wrapper for void G4RunManager::DumpRegion(G4Region *) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::DumpRegion(G4Region *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:271:10
  t6.method("DumpRegion", static_cast<void (G4RunManager::*)(G4Region *)  const>(&G4RunManager::DumpRegion));
  t6.method("DumpRegion", [](G4RunManager const& a)->void{ a.DumpRegion(); });
  t6.method("DumpRegion", [](G4RunManager const* a)->void{ a->DumpRegion(); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::GeometryHasBeenModified(G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::GeometryHasBeenModified(G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:275:10
  t6.method("GeometryHasBeenModified", static_cast<void (G4RunManager::*)(G4bool) >(&G4RunManager::GeometryHasBeenModified));
  t6.method("GeometryHasBeenModified", [](G4RunManager& a)->void{ a.GeometryHasBeenModified(); });
  t6.method("GeometryHasBeenModified", [](G4RunManager* a)->void{ a->GeometryHasBeenModified(); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::ReinitializeGeometry(G4bool, G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::ReinitializeGeometry(G4bool, G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:283:10
  t6.method("ReinitializeGeometry", static_cast<void (G4RunManager::*)(G4bool, G4bool) >(&G4RunManager::ReinitializeGeometry));
  t6.method("ReinitializeGeometry", [](G4RunManager& a)->void{ a.ReinitializeGeometry(); });
  t6.method("ReinitializeGeometry", [](G4RunManager& a, G4bool arg0)->void{ a.ReinitializeGeometry(arg0); });
  t6.method("ReinitializeGeometry", [](G4RunManager* a)->void{ a->ReinitializeGeometry(); });
  t6.method("ReinitializeGeometry", [](G4RunManager* a, G4bool arg0)->void{ a->ReinitializeGeometry(arg0); });

  DEBUG_MSG("Adding wrapper for void G4RunManager::PhysicsHasBeenModified() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::PhysicsHasBeenModified()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:294:17
  t6.method("PhysicsHasBeenModified", static_cast<void (G4RunManager::*)() >(&G4RunManager::PhysicsHasBeenModified));

  DEBUG_MSG("Adding wrapper for void G4RunManager::CutOffHasBeenModified() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::CutOffHasBeenModified()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:301:17
  t6.method("CutOffHasBeenModified", static_cast<void (G4RunManager::*)() >(&G4RunManager::CutOffHasBeenModified));

  DEBUG_MSG("Adding wrapper for void G4RunManager::ReOptimizeMotherOf(G4VPhysicalVolume *) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::ReOptimizeMotherOf(G4VPhysicalVolume *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:307:10
  t6.method("ReOptimizeMotherOf", static_cast<void (G4RunManager::*)(G4VPhysicalVolume *) >(&G4RunManager::ReOptimizeMotherOf));

  DEBUG_MSG("Adding wrapper for void G4RunManager::ReOptimize(G4LogicalVolume *) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::ReOptimize(G4LogicalVolume *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:314:10
  t6.method("ReOptimize", static_cast<void (G4RunManager::*)(G4LogicalVolume *) >(&G4RunManager::ReOptimize));

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetGeometryToBeOptimized(G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetGeometryToBeOptimized(G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:317:17
  t6.method("SetGeometryToBeOptimized", static_cast<void (G4RunManager::*)(G4bool) >(&G4RunManager::SetGeometryToBeOptimized));

  DEBUG_MSG("Adding wrapper for G4bool G4RunManager::GetGeometryToBeOptimized() (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4RunManager::GetGeometryToBeOptimized()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:326:19
  t6.method("GetGeometryToBeOptimized", static_cast<G4bool (G4RunManager::*)() >(&G4RunManager::GetGeometryToBeOptimized));

  DEBUG_MSG("Adding wrapper for void G4RunManager::GeometryDirectlyUpdated(G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::GeometryDirectlyUpdated(G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:331:10
  t6.method("GeometryDirectlyUpdated", static_cast<void (G4RunManager::*)(G4bool) >(&G4RunManager::GeometryDirectlyUpdated));
  t6.method("GeometryDirectlyUpdated", [](G4RunManager& a)->void{ a.GeometryDirectlyUpdated(); });
  t6.method("GeometryDirectlyUpdated", [](G4RunManager* a)->void{ a->GeometryDirectlyUpdated(); });

  DEBUG_MSG("Adding wrapper for G4bool G4RunManager::IfGeometryHasBeenDestroyed() (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4RunManager::IfGeometryHasBeenDestroyed()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:336:19
  t6.method("G4RunManager!IfGeometryHasBeenDestroyed", static_cast<G4bool (*)() >(&G4RunManager::IfGeometryHasBeenDestroyed));

  DEBUG_MSG("Adding wrapper for void G4RunManager::ConstructScoringWorlds() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::ConstructScoringWorlds()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:341:18
  t6.method("ConstructScoringWorlds", static_cast<void (G4RunManager::*)() >(&G4RunManager::ConstructScoringWorlds));

  DEBUG_MSG("Adding wrapper for void G4RunManager::rndmSaveThisRun() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::rndmSaveThisRun()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:343:18
  t6.method("rndmSaveThisRun", static_cast<void (G4RunManager::*)() >(&G4RunManager::rndmSaveThisRun));

  DEBUG_MSG("Adding wrapper for void G4RunManager::rndmSaveThisEvent() (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::rndmSaveThisEvent()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:344:18
  t6.method("rndmSaveThisEvent", static_cast<void (G4RunManager::*)() >(&G4RunManager::rndmSaveThisEvent));

  DEBUG_MSG("Adding wrapper for void G4RunManager::RestoreRandomNumberStatus(const G4String &) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::RestoreRandomNumberStatus(const G4String &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:345:18
  t6.method("RestoreRandomNumberStatus", static_cast<void (G4RunManager::*)(const G4String &) >(&G4RunManager::RestoreRandomNumberStatus));

  DEBUG_MSG("Adding wrapper for void G4RunManager::RestoreRndmEachEvent(G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::RestoreRndmEachEvent(G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:346:18
  t6.method("RestoreRndmEachEvent", static_cast<void (G4RunManager::*)(G4bool) >(&G4RunManager::RestoreRndmEachEvent));

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetUserAction(G4UserStackingAction *) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetUserAction(G4UserStackingAction *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:356:18
  t6.method("SetUserAction", static_cast<void (G4RunManager::*)(G4UserStackingAction *) >(&G4RunManager::SetUserAction));

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetUserAction(G4UserTrackingAction *) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetUserAction(G4UserTrackingAction *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:357:18
  t6.method("SetUserAction", static_cast<void (G4RunManager::*)(G4UserTrackingAction *) >(&G4RunManager::SetUserAction));

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetUserAction(G4UserSteppingAction *) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetUserAction(G4UserSteppingAction *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:358:18
  t6.method("SetUserAction", static_cast<void (G4RunManager::*)(G4UserSteppingAction *) >(&G4RunManager::SetUserAction));

  DEBUG_MSG("Adding wrapper for const G4UserStackingAction * G4RunManager::GetUserStackingAction() (" __HERE__ ")");
  // signature to use in the veto list: const G4UserStackingAction * G4RunManager::GetUserStackingAction()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:408:40
  t6.method("GetUserStackingAction", static_cast<const G4UserStackingAction * (G4RunManager::*)()  const>(&G4RunManager::GetUserStackingAction));

  DEBUG_MSG("Adding wrapper for const G4UserTrackingAction * G4RunManager::GetUserTrackingAction() (" __HERE__ ")");
  // signature to use in the veto list: const G4UserTrackingAction * G4RunManager::GetUserTrackingAction()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:412:40
  t6.method("GetUserTrackingAction", static_cast<const G4UserTrackingAction * (G4RunManager::*)()  const>(&G4RunManager::GetUserTrackingAction));

  DEBUG_MSG("Adding wrapper for const G4UserSteppingAction * G4RunManager::GetUserSteppingAction() (" __HERE__ ")");
  // signature to use in the veto list: const G4UserSteppingAction * G4RunManager::GetUserSteppingAction()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:416:40
  t6.method("GetUserSteppingAction", static_cast<const G4UserSteppingAction * (G4RunManager::*)()  const>(&G4RunManager::GetUserSteppingAction));

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetNumberOfAdditionalWaitingStacks(G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetNumberOfAdditionalWaitingStacks(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:422:17
  t6.method("SetNumberOfAdditionalWaitingStacks", static_cast<void (G4RunManager::*)(G4int) >(&G4RunManager::SetNumberOfAdditionalWaitingStacks));

  DEBUG_MSG("Adding wrapper for const G4String & G4RunManager::GetVersionString() (" __HERE__ ")");
  // signature to use in the veto list: const G4String & G4RunManager::GetVersionString()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:431:28
  t6.method("GetVersionString", static_cast<const G4String & (G4RunManager::*)()  const>(&G4RunManager::GetVersionString));

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetPrimaryTransformer(G4PrimaryTransformer *) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetPrimaryTransformer(G4PrimaryTransformer *)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:436:17
  t6.method("SetPrimaryTransformer", static_cast<void (G4RunManager::*)(G4PrimaryTransformer *) >(&G4RunManager::SetPrimaryTransformer));

  DEBUG_MSG("Adding wrapper for void G4RunManager::StoreRandomNumberStatusToG4Event(G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::StoreRandomNumberStatusToG4Event(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:441:17
  t6.method("StoreRandomNumberStatusToG4Event", static_cast<void (G4RunManager::*)(G4int) >(&G4RunManager::StoreRandomNumberStatusToG4Event));

  DEBUG_MSG("Adding wrapper for G4int G4RunManager::GetFlagRandomNumberStatusToG4Event() (" __HERE__ ")");
  // signature to use in the veto list: G4int G4RunManager::GetFlagRandomNumberStatusToG4Event()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:451:18
  t6.method("GetFlagRandomNumberStatusToG4Event", static_cast<G4int (G4RunManager::*)()  const>(&G4RunManager::GetFlagRandomNumberStatusToG4Event));

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetRandomNumberStore(G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetRandomNumberStore(G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:456:17
  t6.method("SetRandomNumberStore", static_cast<void (G4RunManager::*)(G4bool) >(&G4RunManager::SetRandomNumberStore));

  DEBUG_MSG("Adding wrapper for G4bool G4RunManager::GetRandomNumberStore() (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4RunManager::GetRandomNumberStore()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:460:19
  t6.method("GetRandomNumberStore", static_cast<G4bool (G4RunManager::*)()  const>(&G4RunManager::GetRandomNumberStore));

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetRandomNumberStoreDir(const G4String &) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetRandomNumberStoreDir(const G4String &)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:464:17
  t6.method("SetRandomNumberStoreDir", static_cast<void (G4RunManager::*)(const G4String &) >(&G4RunManager::SetRandomNumberStoreDir));

  DEBUG_MSG("Adding wrapper for const G4String & G4RunManager::GetRandomNumberStoreDir() (" __HERE__ ")");
  // signature to use in the veto list: const G4String & G4RunManager::GetRandomNumberStoreDir()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:487:28
  t6.method("GetRandomNumberStoreDir", static_cast<const G4String & (G4RunManager::*)()  const>(&G4RunManager::GetRandomNumberStoreDir));

  DEBUG_MSG("Adding wrapper for const G4String & G4RunManager::GetRandomNumberStatusForThisRun() (" __HERE__ ")");
  // signature to use in the veto list: const G4String & G4RunManager::GetRandomNumberStatusForThisRun()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:491:28
  t6.method("GetRandomNumberStatusForThisRun", static_cast<const G4String & (G4RunManager::*)()  const>(&G4RunManager::GetRandomNumberStatusForThisRun));

  DEBUG_MSG("Adding wrapper for const G4String & G4RunManager::GetRandomNumberStatusForThisEvent() (" __HERE__ ")");
  // signature to use in the veto list: const G4String & G4RunManager::GetRandomNumberStatusForThisEvent()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:495:28
  t6.method("GetRandomNumberStatusForThisEvent", static_cast<const G4String & (G4RunManager::*)()  const>(&G4RunManager::GetRandomNumberStatusForThisEvent));

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetRandomNumberStorePerEvent(G4bool) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetRandomNumberStorePerEvent(G4bool)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:506:17
  t6.method("SetRandomNumberStorePerEvent", static_cast<void (G4RunManager::*)(G4bool) >(&G4RunManager::SetRandomNumberStorePerEvent));

  DEBUG_MSG("Adding wrapper for G4bool G4RunManager::GetRandomNumberStorePerEvent() (" __HERE__ ")");
  // signature to use in the veto list: G4bool G4RunManager::GetRandomNumberStorePerEvent()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:510:19
  t6.method("GetRandomNumberStorePerEvent", static_cast<G4bool (G4RunManager::*)()  const>(&G4RunManager::GetRandomNumberStorePerEvent));

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetVerboseLevel(G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetVerboseLevel(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:515:17
  t6.method("SetVerboseLevel", static_cast<void (G4RunManager::*)(G4int) >(&G4RunManager::SetVerboseLevel));

  DEBUG_MSG("Adding wrapper for G4int G4RunManager::GetVerboseLevel() (" __HERE__ ")");
  // signature to use in the veto list: G4int G4RunManager::GetVerboseLevel()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:520:18
  t6.method("GetVerboseLevel", static_cast<G4int (G4RunManager::*)()  const>(&G4RunManager::GetVerboseLevel));

  DEBUG_MSG("Adding wrapper for G4int G4RunManager::GetPrintProgress() (" __HERE__ ")");
  // signature to use in the veto list: G4int G4RunManager::GetPrintProgress()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:521:18
  t6.method("GetPrintProgress", static_cast<G4int (G4RunManager::*)() >(&G4RunManager::GetPrintProgress));

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetPrintProgress(G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetPrintProgress(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:522:17
  t6.method("SetPrintProgress", static_cast<void (G4RunManager::*)(G4int) >(&G4RunManager::SetPrintProgress));

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetNumberOfEventsToBeStored(G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetNumberOfEventsToBeStored(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:524:17
  t6.method("SetNumberOfEventsToBeStored", static_cast<void (G4RunManager::*)(G4int) >(&G4RunManager::SetNumberOfEventsToBeStored));

  DEBUG_MSG("Adding wrapper for const G4Event * G4RunManager::GetCurrentEvent() (" __HERE__ ")");
  // signature to use in the veto list: const G4Event * G4RunManager::GetCurrentEvent()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:537:27
  t6.method("GetCurrentEvent", static_cast<const G4Event * (G4RunManager::*)()  const>(&G4RunManager::GetCurrentEvent));

  DEBUG_MSG("Adding wrapper for const G4Event * G4RunManager::GetPreviousEvent(G4int) (" __HERE__ ")");
  // signature to use in the veto list: const G4Event * G4RunManager::GetPreviousEvent(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:540:27
  t6.method("GetPreviousEvent", static_cast<const G4Event * (G4RunManager::*)(G4int)  const>(&G4RunManager::GetPreviousEvent));

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetRunIDCounter(G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetRunIDCounter(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:558:17
  t6.method("SetRunIDCounter", static_cast<void (G4RunManager::*)(G4int) >(&G4RunManager::SetRunIDCounter));

  DEBUG_MSG("Adding wrapper for G4int G4RunManager::GetNumberOfParallelWorld() (" __HERE__ ")");
  // signature to use in the veto list: G4int G4RunManager::GetNumberOfParallelWorld()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:562:18
  t6.method("GetNumberOfParallelWorld", static_cast<G4int (G4RunManager::*)()  const>(&G4RunManager::GetNumberOfParallelWorld));

  DEBUG_MSG("Adding wrapper for void G4RunManager::SetNumberOfEventsToBeProcessed(G4int) (" __HERE__ ")");
  // signature to use in the veto list: void G4RunManager::SetNumberOfEventsToBeProcessed(G4int)
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:563:17
  t6.method("SetNumberOfEventsToBeProcessed", static_cast<void (G4RunManager::*)(G4int) >(&G4RunManager::SetNumberOfEventsToBeProcessed));

  DEBUG_MSG("Adding wrapper for G4int G4RunManager::GetNumberOfEventsToBeProcessed() (" __HERE__ ")");
  // signature to use in the veto list: G4int G4RunManager::GetNumberOfEventsToBeProcessed()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:567:18
  t6.method("GetNumberOfEventsToBeProcessed", static_cast<G4int (G4RunManager::*)()  const>(&G4RunManager::GetNumberOfEventsToBeProcessed));

  DEBUG_MSG("Adding wrapper for G4int G4RunManager::GetNumberOfSelectEvents() (" __HERE__ ")");
  // signature to use in the veto list: G4int G4RunManager::GetNumberOfSelectEvents()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:571:18
  t6.method("GetNumberOfSelectEvents", static_cast<G4int (G4RunManager::*)()  const>(&G4RunManager::GetNumberOfSelectEvents));

  DEBUG_MSG("Adding wrapper for const G4String & G4RunManager::GetSelectMacro() (" __HERE__ ")");
  // signature to use in the veto list: const G4String & G4RunManager::GetSelectMacro()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:572:28
  t6.method("GetSelectMacro", static_cast<const G4String & (G4RunManager::*)()  const>(&G4RunManager::GetSelectMacro));

  DEBUG_MSG("Adding wrapper for G4RunManager::RMType G4RunManager::GetRunManagerType() (" __HERE__ ")");
  // signature to use in the veto list: G4RunManager::RMType G4RunManager::GetRunManagerType()
  // defined in /cvmfs/sft.cern.ch/lcg/releases/Geant4/11.0.3-e531e/x86_64-centos7-gcc11-opt/include/Geant4/G4RunManager.hh:582:19
  t6.method("GetRunManagerType", static_cast<G4RunManager::RMType (G4RunManager::*)()  const>(&G4RunManager::GetRunManagerType));

  /* End of G4RunManager class method wrappers
   **********************************************************************/

  DEBUG_MSG("End of wrapper definitions");

}
