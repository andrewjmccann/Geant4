/***************************************************************************
*   Copyright (C) Minister of Natural Resources Canada 2008.              *
*   hseywerd@nrcan.gc.ca                                                  *
*                                                                         *
***************************************************************************/
/**
 * @file SimpleScintillator.cpp
 * @brief Main program for SimpleScintillator application
 *
 * @date 2008/12/08
 *
 *
 * @author HCJ Seywerd hseywerd@nrcan.gc.ca
 **/

#define G4VIS_USE 1
#define G4VIS_USE_OPENGLX 1


#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#ifdef G4MPI_USE
#include "G4MPImanager.hh"
#include "G4MPIsession.hh"
#endif

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#include "G4UIExecutive.hh"
#include "SimpleScintillatorDetectorConstruction.h"
#include "CISensitiveScintiDetector.h"
#include "CISensitiveOpticalDetector.h"
#include "CISensitiveMaterials.h"
#include "CIPhysicsList.h"
#include "CIPrimaryGeneratorAction.h"
#include "CIRunAction.h"
#include "CIEventAction.h"
#include "CISteppingAction.h"
#include "CIModuleTable.h"
#include "FullDetectorConstruction.h"

#include "CISteppingVerbose.h"

/* Still to do
   --- OK  --- Hits collection handling
   --- OK Output Event format
   --- OK Check audrey and Laurel stuff
   ----OK Correct physics constants - mostly done
   --- OK Material boundary interfaces
   --- OK For interfaces between specular surfaces we don't specify anything except the indices of refraction.
   --- OK Do we move boundary properties to the materials class - YES Create boundary members in CIMaterials, also create functions for wrapping
   PhotoDetector Base class
   ---- Sorted this out Repeating logical volumes without a new one each time...
   --- OK Comments headers etc for Doygen
   --- OK chose a standard for variable names theItem vs other choices
   Provide a set of instructions on generating Root interface classes.
   Digitization in particular assigning a module ID address
   --- OK Look at GLGSim HITPMT
   Setting of cuts in G4Physics
   --- OK (now we are) Are we getting the right stuff from our user interface...
   --- OK email to sensl on properties
   --- OK turn on and off the output data formats EventActionMessenger
   --- OK RunActionMessenger doesn't do anything
   --- OK Check PhysicsListMessenger

   Note on geometry - Detector centred in world, generator at +5m in Z and shooting in -z direction
*/

  #include "QGSP_BERT.hh"

int main (int argc, char** argv)
{
  
  G4int myseed = 1234;
	//gROOT->GetPluginManager()->AddHandler("TVirtualStreamerInfo", "*", "TStreamerInfo", "RIO", "TStreamerInfo()");
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  if(argc == 3)
    {
      myseed = atoi(argv[2]);
    }

  G4cout<< "The random seeds are " << myseed << " and " <<  myseed+1 <<G4endl;
  G4Random::setTheSeed(myseed);
#ifdef G4MPI_USE
  // --------------------------------------------------------------------
  // MPI session
  // --------------------------------------------------------------------
  // At first, G4MPImanager/G4MPIsession should be created.
  G4MPImanager* g4MPI= new G4MPImanager(argc,argv);

  // MPI session (G4MPIsession) instead of G4UIterminal
  // Terminal availability depends on your MPI implementation.
  G4MPIsession* session= g4MPI-> GetMPIsession();
#endif

  // Printing info during stepping
  G4VSteppingVerbose::SetInstance(new CISteppingVerbose);



  // Run manager
  //
  G4RunManager * runManager = new G4RunManager;

  // User Initialization classes (mandatory)

  const G4String sensitiveScintiDetectorName = "/SimpleScintillator/Scintillation";
  const G4String sensitiveOpticalDetectorName = "/SimpleScintillator/Optical";
  const G4String sensitiveMaterialsName = "/SimpleScintillator/Materials";

  // Detector construction
  CIModuleTable* pModuleTable = new CIModuleTable();

  CISensitiveScintiDetector* pSensitiveScintiDetector = new CISensitiveScintiDetector (sensitiveScintiDetectorName);
  pSensitiveScintiDetector->SetCIModuleTable(pModuleTable);
  CISensitiveOpticalDetector* pSensitiveOpticalDetector = new CISensitiveOpticalDetector (sensitiveOpticalDetectorName);
  pSensitiveOpticalDetector->SetCIModuleTable(pModuleTable);
  CISensitiveMaterials* pCISensitiveMaterials = new CISensitiveMaterials(sensitiveMaterialsName);

  //SimpleScintillatorDetectorConstruction* pDetector = new SimpleScintillatorDetectorConstruction(pSensitiveScintiDetector, pSensitiveOpticalDetector);

  //TwoPixelDetector* pDetector = new TwoPixelDetector(pSensitiveScintiDetector, pSensitiveOpticalDetector, pCISensitiveMaterials);
  //runManager->SetUserInitialization (pDetector);

    FullDetectorConstruction* pDetector = new FullDetectorConstruction(pSensitiveScintiDetector, pSensitiveOpticalDetector, pCISensitiveMaterials);
   runManager->SetUserInitialization (pDetector);

  // Particle creation
  //G4VUserPhysicsList* physics = new QGSP_BERT(1);
  //runManager->SetUserInitialization(physics);

   G4VUserPhysicsList* pPhysics = new CIPhysicsList;
   runManager->SetUserInitialization (pPhysics);

  // Event generator configuration
  G4VUserPrimaryGeneratorAction* gen_action = new CIPrimaryGeneratorAction ();
  runManager->SetUserAction (gen_action);

  // Pre/post run actions
  G4UserRunAction* pRun_action = new CIRunAction;
  runManager->SetUserAction (pRun_action);

  // Per event actions CIEventAction
  CIEventAction* pEvent_action = new CIEventAction;
  pEvent_action->SetScintiSDetector(pSensitiveScintiDetector);
  pEvent_action->SetOpticalSDetector(pSensitiveOpticalDetector);
  pEvent_action->SetSensitiveMaterials(pCISensitiveMaterials);
  runManager->SetUserAction (dynamic_cast<G4UserEventAction*>(pEvent_action));

  // Actions during particle stepping
  G4UserSteppingAction* pStepping_action = new CISteppingAction(pSensitiveOpticalDetector);
  runManager->SetUserAction (pStepping_action);

#ifdef G4VIS_USE
    G4VisManager* visManager = new G4VisExecutive;
    //visManager->RegisterGraphicsSystem(new G4OpenGLImmediateX);
    //visManager->RegisterGraphicsSystem(new G4OpenGLStoredX);
    visManager->Initialize();
#endif


#ifndef G4MPI_USE
  // Get the pointer to the User Interface manager
  G4UImanager * UI = G4UImanager::GetUIpointer();

  

  if (argc >= 2) // batch mode
  {
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UI->ApplyCommand (command + fileName);
  }
  else           // interactive mode : define visualization and UI terminal
  {
    G4UIsession * session = 0;
#ifdef G4UI_USE_TCSH
    session = new G4UIterminal (new G4UItcsh);
#else
    session = new G4UIterminal();
#endif
    UI->ApplyCommand ("/control/execute vis.mac");
    session->SessionStart();
    delete session;
  }
#endif

#ifdef G4MPI_USE
    // --------------------------------------------------------------------
    // ready for go
    // MPIsession treats both interactive and batch modes.
    // Just start your session as below.
    // --------------------------------------------------------------------
    session-> SessionStart();
#endif


#ifdef G4VIS_USE
    delete visManager;
#endif

//  Free the store: user actions, physics_list and detector_description are
//                  owned and deleted by the run manager, so they should not
//                  be deleted in the main() program !

#ifdef G4MPI_USE
  delete g4MPI;
#endif

  delete runManager;
  delete pModuleTable;

  return 0;
}

