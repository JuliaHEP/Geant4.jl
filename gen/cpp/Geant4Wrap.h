#ifndef G4Wrap_H
#define G4Wrap_H

#include "G4VExceptionHandler.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VUserActionInitialization.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4UserSteppingAction.hh"
#include "G4UserTrackingAction.hh"
#include "G4UserRunAction.hh"
#include "G4UserEventAction.hh"
#include "G4ParticleGun.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VSensitiveDetector.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4UserWorkerInitialization.hh"
#include "G4MagneticField.hh"
#include "G4LogicalVolumeStore.hh"
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

//--G4JLSensDet------------------------------------------------------------------------------------
typedef bool (*processhits_f) (G4Step*, G4TouchableHistory*, void*);
typedef void (*initend_f) (G4HCofThisEvent*, void*);
class G4JLSensDet : public G4VSensitiveDetector {
  public:
    G4JLSensDet(const G4String& name, processhits_f f, void* d) : G4VSensitiveDetector(name), 
    processhits_d(d), processhits(f), 
    initialize_d(nullptr), initialize(nullptr), 
    endofevent_d(nullptr), endofevent(nullptr) {
      G4SDManager::GetSDMpointer()->AddNewDetector(this);   // Automatically register the SD to the manager
    }
    ~G4JLSensDet() = default;
    virtual void Initialize(G4HCofThisEvent* hc) override; 
    virtual void EndOfEvent(G4HCofThisEvent* hc) override;
    virtual G4bool ProcessHits(G4Step* s, G4TouchableHistory* h) override;
    void SetInitialize(initend_f f, void* d) {initialize = f; initialize_d = d;}
    void SetEndOfEvent(initend_f f, void* d) {endofevent = f; endofevent_d = d;}
  private:
    void* processhits_d;
    processhits_f processhits;
    void* initialize_d;
    initend_f initialize;
    void* endofevent_d;
    initend_f endofevent;
};

//---G4JLDetectorConstruction----------------------------------------------------------------------
typedef  G4VPhysicalVolume* (*construct_f) (void*);
typedef void (*sdandf_f)(void*);
class G4JLDetectorConstruction : public G4VUserDetectorConstruction { 
  public:
    G4JLDetectorConstruction(construct_f c, void* d, sdandf_f s = nullptr, void* a = nullptr) : 
      construct_d(d), construct(c), 
      sdandf_d(a), sdandf(s) {} 
    ~G4JLDetectorConstruction() = default;
    virtual G4VPhysicalVolume* Construct() override {return construct(construct_d);}
    virtual void ConstructSDandField() override { if (sdandf) sdandf(sdandf_d); }
    void SetSensitiveDetector(const G4String& lv, G4JLSensDet* sd, G4bool m = false);
  protected:
    void* construct_d;
    construct_f construct;
    void* sdandf_d;
    sdandf_f sdandf;
};

//---G4JLActionInitialization----------------------------------------------------------------------
class G4JLActionInitialization;
typedef  void (*build_f)(const G4JLActionInitialization*, void*);
class G4JLActionInitialization : public G4VUserActionInitialization
{
  public:
    G4JLActionInitialization(build_f f, void* d, build_f mf = nullptr, void* md = nullptr) : 
      build_d(d), build(f), 
      master_build_d(md), master_build(mf) {}
    G4JLActionInitialization() : build_d(nullptr), build(nullptr), master_build_d(nullptr), master_build(nullptr) {}
    ~G4JLActionInitialization() override = default;
    void BuildForMaster() const override;
    void Build() const override;
    // Make these public to be used from Julia
    void SetUserAction(G4VUserPrimaryGeneratorAction* a) const { G4VUserActionInitialization::SetUserAction(a); }
    void SetUserAction(G4UserRunAction* a) const {G4VUserActionInitialization::SetUserAction(a); }
    void SetUserAction(G4UserEventAction* a) const {G4VUserActionInitialization::SetUserAction(a); }
    void SetUserAction(G4UserStackingAction* a) const {G4VUserActionInitialization::SetUserAction(a); }
    void SetUserAction(G4UserTrackingAction* a) const {G4VUserActionInitialization::SetUserAction(a); }
    void SetUserAction(G4UserSteppingAction* a) const {G4VUserActionInitialization::SetUserAction(a); }

  protected:
    void* build_d;
    build_f build;
    void* master_build_d;
    build_f master_build;
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

//---G4JLWorkerInitialization-----------------------------------------------------------------------
class G4JLWorkerInitialization : public G4UserWorkerInitialization {
  public:
    G4JLWorkerInitialization() = default;
    virtual ~G4JLWorkerInitialization() = default;
    virtual void WorkerInitialize() const override;
    virtual void WorkerStart() const override;
    virtual void WorkerRunStart() const override;
    virtual void WorkerRunEnd() const override;
    virtual void WorkerStop() const override;
};

//---G4JLGeneratorAction-----------------------------------------------------------------------------
typedef  void (*generate_f) (G4Event*, void*);
class G4JLGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
  G4JLGeneratorAction(generate_f f, void* d) : generate_d(d), generate(f) { }
  ~G4JLGeneratorAction() = default;
  void GeneratePrimaries(G4Event* event) override { generate(event, generate_d); }
private:
  void* generate_d;
  generate_f generate;
};

//---G4JLMagField-----------------------------------------------------------------------------
typedef  void (*getfield_f) (G4ThreeVector&, const G4ThreeVector&, void*);
class G4JLMagField : public G4MagneticField {
public:
  G4JLMagField(getfield_f f, void* d) : field_d(d), getfield(f) { }
  ~G4JLMagField() = default;
  void GetFieldValue( const G4double point[3], G4double* field) const override;
private:
  void* field_d;
  getfield_f getfield;
};

typedef  void (*stepaction_f) (const G4Step*, void*);
//---G4JLSteppingAction-------------------------------------------------------------------------------
class G4JLSteppingAction : public G4UserSteppingAction {
public:
  G4JLSteppingAction(stepaction_f f, void* d) : stepaction_d(d), action(f) {}
  ~G4JLSteppingAction() = default;
  virtual void UserSteppingAction(const G4Step* step) {action(step, stepaction_d);}
private:
  void* stepaction_d;
  stepaction_f action;
};

//---G4JLTrackingAction-------------------------------------------------------------------------------
typedef  void (*trackaction_f) (const G4Track*, void*);
class G4JLTrackingAction : public G4UserTrackingAction {
  public:  
    G4JLTrackingAction(trackaction_f pre = nullptr, void* pre_d = nullptr,  trackaction_f post = nullptr, void* post_d = nullptr) : 
      preaction_d(pre_d), preaction(pre), 
      postaction_d(post_d), postaction(post) {} 
   ~G4JLTrackingAction() = default;
    void PreUserTrackingAction(const G4Track* track) {if (preaction) preaction(track, preaction_d);}   
    void PostUserTrackingAction(const G4Track* track) {if (postaction) postaction(track, postaction_d);}
  private:
    void* preaction_d;
    trackaction_f preaction;
    void* postaction_d;
    trackaction_f postaction;
};

//---G4JLRunAction------------------------------------------------------------------------------------
class G4Run;
typedef  void (*runaction_f) (const G4Run*, void*);
class G4JLRunAction : public G4UserRunAction {
  public:
    G4JLRunAction(runaction_f begin = nullptr, void* begin_d = nullptr, runaction_f end = nullptr, void* end_d = nullptr) :
    beginaction_d(begin_d), beginaction(begin), 
    endaction_d(end_d), endaction(end) {} 
    ~G4JLRunAction() = default;
    virtual void BeginOfRunAction(const G4Run* run) {if (beginaction) beginaction(run, beginaction_d);}
    virtual void   EndOfRunAction(const G4Run* run) {if (endaction) endaction(run, endaction_d);}
  private:
    void* beginaction_d;
    runaction_f beginaction;
    void* endaction_d;
    runaction_f endaction;
};

//---G4JLEventAction------------------------------------------------------------------------------------
typedef  void (*eventaction_f) (const G4Event*, void*);
class G4JLEventAction : public G4UserEventAction {
  public:  
    G4JLEventAction(eventaction_f begin = nullptr, void* begin_d = nullptr, eventaction_f end = nullptr, void* end_d = nullptr) : 
    beginaction_d(begin_d), beginaction(begin), 
    endaction_d(end_d), endaction(end) {}  
   ~G4JLEventAction() = default;
    virtual void BeginOfEventAction(const G4Event* evt) {if (beginaction) beginaction(evt, beginaction_d);}
    virtual void   EndOfEventAction(const G4Event* evt) {if (endaction) endaction(evt, endaction_d);}
  private:
    void* beginaction_d;
    eventaction_f beginaction;
    void* endaction_d;
    eventaction_f endaction;
};

inline size_t size(const G4LogicalVolumeStore* st) { return st->size();}
inline G4LogicalVolume* GetVolume(const G4LogicalVolumeStore* st, size_t indx) { return st->at(indx);}

class G4PolyconeSideRZ;
class G4PolyhedraSideRZ;
class G4Polycone;
class G4Polyhedra;
G4PolyconeSideRZ& GetPolyCorner(const G4Polycone&, G4int);
G4PolyhedraSideRZ& GetPolyCorner(const G4Polyhedra&, G4int);

void SetParticleByName(G4ParticleGun* gun, const char* pname);
G4ParticleDefinition* FindParticle(const char* pname);
inline G4String make_G4String(const char* s) {return G4String(s);}
char* G4JL_getenv(const char* x);
int   G4JL_setenv(const char* x, const char* v);
void  G4JL_init(void);
void  G4JL_println(const char *);


#endif