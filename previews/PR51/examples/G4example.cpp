#include "G4VUserDetectorConstruction.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4UserEventAction.hh"
#include "G4UserRunAction.hh"
#include "G4ParticleGun.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4RunManagerFactory.hh"
#include "QBBC.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
//#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include "G4VUserActionInitialization.hh"
#include "G4UserWorkerInitialization.hh"
#include <julia.h>
#include <iostream>

//---Detector construction class-------------------------------------------------------------------
class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction() = default;
    ~DetectorConstruction() override = default;
    G4VPhysicalVolume* Construct() override {
        auto nist = G4NistManager::Instance();
        auto world_mat = nist->FindOrBuildMaterial("G4_AIR");
        auto core_mat  = nist->FindOrBuildMaterial("G4_WATER");
        auto world_size = 1.0*CLHEP::m;
        auto solidWorld = new G4Box("World", world_size, world_size, world_size);
        auto logicWorld = new G4LogicalVolume(solidWorld, world_mat, "World");
        auto physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0);
        auto core_size = 0.5*CLHEP::m;
        auto solidCore = new G4Box("Core", core_size, core_size, core_size);
        auto logicCore = new G4LogicalVolume(solidCore, core_mat, "Core");
        new G4PVPlacement(0, G4ThreeVector(), logicCore, "Core", logicWorld, false, 0);
        return physWorld;
    }
    void ConstructSDandField() override {}
};

//---Primary generator action class----------------------------------------------------------------
class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    PrimaryGeneratorAction() { fParticleGun  = new G4ParticleGun(); }    
    ~PrimaryGeneratorAction() { delete fParticleGun; }
    void GeneratePrimaries(G4Event* anEvent) override {
        fPrimaryParticleName = fParticleGun->GetParticleDefinition()->GetParticleName();
        fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
        fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,-1.*CLHEP::m));
        fParticleGun->GeneratePrimaryVertex(anEvent);
    }
    G4ParticleGun* GetParticleGun() {return fParticleGun;};
    const G4String& GetParticleName() { return fPrimaryParticleName;}
private:
    G4String fPrimaryParticleName;
    G4ParticleGun* fParticleGun;
};

typedef  void (*stepaction_f)(const G4Step*);
class SteppingAction : public G4UserSteppingAction
{
public:
    SteppingAction() {
      action_jl = (stepaction_f)(jl_unbox_voidpointer(jl_eval_string("@cfunction(stepping_action, Nothing, (CxxPtr{G4Step},))")));
      std::cout << "=====> " << action_jl << std::endl;
    } 
    ~SteppingAction() {}
    void UserSteppingAction(const G4Step* step) override { action_jl(step); }
private:
    stepaction_f action_jl;
};

typedef  void (*eventaction_f)(const G4Event*);
class EventAction : public G4UserEventAction
{
  public:
    EventAction() {
      beginevent_jl = (eventaction_f)(jl_unbox_voidpointer(jl_eval_string("@cfunction(begin_of_event_action, Nothing, (CxxPtr{G4Event},))")));
      endevent_jl = (eventaction_f)(jl_unbox_voidpointer(jl_eval_string("@cfunction(end_of_event_action, Nothing, (CxxPtr{G4Event},))")));
    }
    ~EventAction() override = default;

    void BeginOfEventAction(const G4Event* event) override { beginevent_jl(event); }
    void EndOfEventAction(const G4Event* event) override { endevent_jl(event); }
  private:
    eventaction_f beginevent_jl;
    eventaction_f endevent_jl;
};

typedef  void (*runaction_f)(const G4Run*);
class RunAction : public G4UserRunAction
{
  public:
    RunAction() {
      beginrun_jl = (runaction_f)(jl_unbox_voidpointer(jl_eval_string("@cfunction(begin_of_run_action, Nothing, (CxxPtr{G4Run},))")));
      endrun_jl = (runaction_f)(jl_unbox_voidpointer(jl_eval_string("@cfunction(end_of_run_action, Nothing, (CxxPtr{G4Run},))")));
    }
    ~RunAction() override = default;

    void BeginOfRunAction(const G4Run* run) override { beginrun_jl(run); }
    void EndOfRunAction(const G4Run* run) override { endrun_jl(run); }

  private:
    runaction_f beginrun_jl;
    runaction_f endrun_jl;
};


class WorkerInitialization : public G4UserWorkerInitialization {
  public:
    WorkerInitialization() = default;
    virtual ~WorkerInitialization() = default;
    virtual void WorkerInitialize() const override {
      if (jl_get_pgcstack() == NULL) jl_adopt_thread();
    }
    virtual void WorkerStart() const override {}
    virtual void WorkerRunStart() const override {}
    virtual void WorkerRunEnd() const override {
      jl_ptls_t ptls = jl_current_task->ptls;
      jl_gc_safe_enter(ptls);
    }
    virtual void WorkerStop() const override {}
};

//---Action initialization class-------------------------------------------------------------------
class ActionInitialization : public G4VUserActionInitialization
{
  public:
    ActionInitialization() = default;
    ~ActionInitialization() override = default;
    void BuildForMaster() const override {
        SetUserAction(new RunAction);
    }
    void Build() const override {
        SetUserAction(new PrimaryGeneratorAction);
        SetUserAction(new RunAction);
        SetUserAction(new EventAction);
        SetUserAction(new SteppingAction);
    }
};



JULIA_DEFINE_FAST_TLS // only define this once, in an executable (not in a shared library) if you want fast code.

//----Main program---------------------------------------------------------------------------------
int main(int, char**)
{
    int nthreads = 0; // Default number of threads
    if (getenv("G4NUMTHREADS")) nthreads = atoi(getenv("G4NUMTHREADS"));

    //--- Required to setup the Julia context------------------------------------------------------
    jl_init();
        /* run Julia commands */
    jl_eval_string("include(\"MyCode.jl\")");
    if (jl_exception_occurred()) {
        std::cout << "=====> " << jl_typeof_str(jl_exception_occurred()) << std::endl;
    }

    //---Construct the default run manager (taking into account the number of threads)-------------
    G4RunManager* runManager;
    if (nthreads > 0) { 
        runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::MT);
        runManager->SetNumberOfThreads(nthreads);
        runManager->SetUserInitialization(new WorkerInitialization());
    } else {
        runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Serial);
    }

    //---Set mandatory initialization classes------------------------------------------------------
    // Detector construction
    runManager->SetUserInitialization(new DetectorConstruction());

    // Physics list
    runManager->SetUserInitialization(new QBBC(0));

    // User action initialization
    runManager->SetUserInitialization(new ActionInitialization());

    // Initialize G4 kernel
    runManager->Initialize();
    
    // Get the pointer to the User Interface manager
    auto UImanager = G4UImanager::GetUIpointer();
    UImanager->ApplyCommand("/control/verbose 1");
    UImanager->ApplyCommand("/run/verbose 1");
    //UImanager->ApplyCommand("/event/verbose 0");
    //UImanager->ApplyCommand("/tracking/verbose 1");
    UImanager->ApplyCommand("/gun/particle e+");
    UImanager->ApplyCommand("/gun/energy 100 MeV");

    // Start a run (we need to enter GC safe region here because the worker threads 
    // will enter a wait state while waiting for workers to finish and this can block GC
    auto state = jl_gc_safe_enter(jl_current_task->ptls);
    runManager->BeamOn(100000);
    jl_gc_safe_leave(jl_current_task->ptls, state);

    // Job termination---------------------------------------------------------------------------
    delete runManager;

    // strongly recommended: notify Julia that the program is about to terminate. 
    // this allows Julia time to cleanup pending write requests and run all finalizers
    jl_atexit_hook(0);
}
