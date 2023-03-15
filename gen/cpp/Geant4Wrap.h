#ifndef G4Wrap_H
#define G4Wrap_H

#include "G4VExceptionHandler.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VUserActionInitialization.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4UserSteppingAction.hh"
#include "G4UserTrackingAction.hh"
#include "G4ParticleGun.hh"
#include "G4VPhysicalVolume.hh"
#include "jlcxx/functions.hpp"

#include <string>

#ifndef VECCORE_ENABLE_VC
  #define VECCORE_ENABLE_VC
#endif

//---G4JLExceptionHandler--------------------------------------------------------------------------
class G4JLExceptionHandler : public G4VExceptionHandler {
public:
  G4JLExceptionHandler(): G4VExceptionHandler() {}
  ~G4JLExceptionHandler() = default;
  G4bool Notify(const char* originOfException,
                const char* exceptionCode,
                G4ExceptionSeverity severity,
                const char* description);
};

//---G4JLDetectorConstruction----------------------------------------------------------------------
typedef  G4VPhysicalVolume* (*construct_f) ();
class G4JLDetectorConstruction : public G4VUserDetectorConstruction { 
  public:
    G4JLDetectorConstruction(construct_f f) : construct(f) {} 
    ~G4JLDetectorConstruction() = default;
    G4VPhysicalVolume* Construct() {return construct();}
  protected:
    construct_f construct;
};

//---G4JLActionInitialization----------------------------------------------------------------------
class G4JLActionInitialization;
typedef  void (*build_f)(const G4JLActionInitialization*);
class G4JLActionInitialization : public G4VUserActionInitialization
{
  public:
    G4JLActionInitialization(build_f f) : build(f) {}
    G4JLActionInitialization() : build(nullptr) {}
    ~G4JLActionInitialization() override = default;
    void BuildForMaster() const override {}
    void Build() const override {if (build != nullptr) return build(this);}
    // Make these public to be used from Julia
    void SetUserAction(G4VUserPrimaryGeneratorAction* a) const {G4VUserActionInitialization::SetUserAction(a); }
    void SetUserAction(G4UserRunAction* a) const {G4VUserActionInitialization::SetUserAction(a); }
    void SetUserAction(G4UserEventAction* a) const {G4VUserActionInitialization::SetUserAction(a); }
    void SetUserAction(G4UserStackingAction* a) const {G4VUserActionInitialization::SetUserAction(a); }
    void SetUserAction(G4UserTrackingAction* a) const {G4VUserActionInitialization::SetUserAction(a); }
    void SetUserAction(G4UserSteppingAction* a) const {G4VUserActionInitialization::SetUserAction(a); }

  protected:
    build_f build;
};

//---G4JLParticleGun-------------------------------------------------------------------------------
class G4JLParticleGun : public G4VUserPrimaryGeneratorAction {
public:
  G4JLParticleGun() {gun = new G4ParticleGun();}
  ~G4JLParticleGun() override {delete gun;}
  G4ParticleGun* GetGun() const { return gun;}
  void GeneratePrimaries(G4Event* event) override {gun->GeneratePrimaryVertex(event);}
private:
  G4ParticleGun* gun;
};

typedef  void (*stepaction_f) (const G4Step*);
//---G4JLSteppingAction-------------------------------------------------------------------------------
class G4JLSteppingAction : public G4UserSteppingAction {
public:
  G4JLSteppingAction(stepaction_f f) : action(f) {}
  ~G4JLSteppingAction() = default;
  virtual void UserSteppingAction(const G4Step* step) {action(step);}
private:
  stepaction_f action;
};

//---G4JLTrackingAction-------------------------------------------------------------------------------
typedef  void (*trackaction_f) (const G4Track*);
class G4JLTrackingAction : public G4UserTrackingAction {
  public:  
    G4JLTrackingAction(trackaction_f pre = nullptr, trackaction_f post = nullptr) : preaction(pre), postaction(post) {} 
   ~G4JLTrackingAction() = default;
    void PreUserTrackingAction(const G4Track* track) {if (preaction) preaction(track);}   
    void PostUserTrackingAction(const G4Track* track) {if (postaction) postaction(track);}
  private:
    trackaction_f preaction;
    trackaction_f postaction;
};

void SetParticleByName(G4ParticleGun* gun, const char* pname);
inline G4String make_G4String(const char* s) {return G4String(s);}
//G4Material * G4NistManager::FindOrBuildMaterial(const G4String &, G4bool, G4bool)



char* G4JL_getenv(const char* x);
int   G4JL_setenv(const char* x, const char* v);
void  G4JL_init(void);

#endif