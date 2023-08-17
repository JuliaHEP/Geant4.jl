#include "jlcxx/functions.hpp"

#include "Geant4Wrap.h"
#include "G4StateManager.hh"
#include "G4ios.hh"
#include "G4PVPlacement.hh"
#include "G4ParticleTable.hh"
#include "G4Polycone.hh"

#include <stdexcept>

// --------------------------------------------------------------------------
G4bool G4JLExceptionHandler::Notify(const char* originOfException,
                                    const char* exceptionCode,
                                    G4ExceptionSeverity severity,
                                    const char* description) {
  std::ostringstream message;
  message << "*** G4Exception : " << exceptionCode << G4endl
          << "      issued by : " << originOfException << G4endl
          << description << G4endl;

  switch(severity) {
  case FatalException:
    throw std::runtime_error( message.str() );
    break;
  case FatalErrorInArgument:
    throw std::invalid_argument( message.str() );
    break;
  case RunMustBeAborted:
    throw std::runtime_error( message.str() );
    break;
  case EventMustBeAborted:
    throw std::runtime_error( message.str() );
    break;
  default:
    throw std::runtime_error( message.str() );
    break;
  }
  return false;
}
void SetParticleByName(G4ParticleGun* gun, const char* pname)
{
  G4ParticleTable* particleTable= G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* pd= particleTable-> FindParticle(pname);
  if (pd != 0) {
    gun-> SetParticleDefinition(pd);
  } else {
    G4cout << "*** \"" << pname << "\" is not registered "
	   << "in available particle list" << G4endl;
  }
}
G4ParticleDefinition* FindParticle(const char* pname)
{
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  return particleTable-> FindParticle(pname);
}

char* G4JL_getenv(const char* x) { return std::getenv(x); };

int G4JL_setenv(const char* x, const char* v) { return setenv(x, v, 1); }

void G4JL_init(void) {
  auto sm = G4StateManager::GetStateManager();
  sm-> SetExceptionHandler(new G4JLExceptionHandler());
}

void  G4JL_println(const char * msg) {
  G4cout << msg << std::endl;
}

void G4JLActionInitialization::BuildForMaster() const { 
  if (master_build != nullptr) master_build(this, master_build_d);
}
void G4JLActionInitialization::Build() const {
  if (build != nullptr) build(this, build_d);
}

void G4JLWorkerInitialization::WorkerInitialize() const {
  #if JULIA_VERSION_MAJOR >= 1 && JULIA_VERSION_MINOR >= 9
    if (jl_get_pgcstack() == NULL) jl_adopt_thread();
  #endif
}
void G4JLWorkerInitialization::WorkerStart() const {
  jl_task_t *ct = jl_current_task;
  jl_gc_safe_enter(ct->ptls);
}
void G4JLWorkerInitialization::WorkerRunStart() const {
}
void G4JLWorkerInitialization::WorkerRunEnd() const {
  jl_task_t *ct = jl_current_task;
  jl_gc_safe_enter(ct->ptls);
}
void G4JLWorkerInitialization::WorkerStop() const {
}

G4bool G4JLSensDet::ProcessHits(G4Step* s, G4TouchableHistory* h) {
  return processhits(s, h, processhits_d);
}
void G4JLSensDet::Initialize(G4HCofThisEvent* hc) {
  if (initialize) initialize(hc, initialize_d); 
}
void G4JLSensDet::EndOfEvent(G4HCofThisEvent* hc) {
  if (endofevent) endofevent(hc, endofevent_d); 
}

void G4JLDetectorConstruction::SetSensitiveDetector(const G4String& lv, G4JLSensDet* sd, G4bool m) {
  G4VUserDetectorConstruction::SetSensitiveDetector(lv, sd, m);
}

G4PolyconeSideRZ& GetPolyCorner(const G4Polycone& pc, G4int index) {
  static G4PolyconeSideRZ side;
  side = pc.GetCorner(index);
  return side;
}