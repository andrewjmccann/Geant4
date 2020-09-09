// ***************************************************************************
// *   Copyright (C) Minister of Natural Resources Canada 2008.              *
// *   hseywerd@nrcan.gc.ca                                                  *
// *                                                                         *
// ***************************************************************************/
// **
// * @file CIPhysicsList.cpp
// * @brief Set up physics processes.
// *
// * @date 2008/12/08
// *
// * @author HCJ Seywerd hseywerd@nrcan.gc.ca
// **/

#include "CIPhysicsList.h"
#include "CIPhysicsListMessenger.h"

#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "G4ProcessManager.hh"

#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option1.hh"
#include "G4EmStandardPhysics_option2.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmPenelopePhysics.hh"

#include "G4DecayPhysics.hh"

#include "G4HadronElasticPhysics.hh"
#include "G4HadronDElasticPhysics.hh"
#include "G4HadronHElasticPhysics.hh"
#include "G4HadronInelasticQBBC.hh"
#include "G4IonPhysics.hh"

#include "G4LossTableManager.hh"
#include "G4EmConfigurator.hh"
#include "G4UnitsTable.hh"

#include "G4ProcessManager.hh"
#include "G4Decay.hh"


#include "G4IonFluctuations.hh"
#include "G4IonParametrisedLossModel.hh"
#include "G4UniversalFluctuation.hh"

#include "G4BraggIonGasModel.hh"
#include "G4BetheBlochIonGasModel.hh"
#include "G4UAtomicDeexcitation.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

const G4String CIPhysicsList::m_strParallelWorldName = "ParallelScoringWorld";

CIPhysicsList::CIPhysicsList() : m_bUseG4LECS (true), m_bUseOptical (true), m_bUsePointSource(false), fEmPhysicsList(0),fEmName("emstandard_opt4"), m_pMessenger (NULL)
{
 m_pMessenger = new CIPhysicsListMessenger (this);
 defaultCutValue = 1.0 * mm;
 SetVerboseLevel (1);

  // EM physics
 fEmName = "emstandard_opt4";
 fEmPhysicsList = new G4EmStandardPhysics_option4();

     //   fEmName = "EmLivermore";
     // fEmPhysicsList = new G4EmLivermorePhysics();
    /*  G4VAtomDeexcitation* de = new G4UAtomicDeexcitation();
    G4LossTableManager::Instance()->SetAtomDeexcitation(de);
    de->SetFluo(true);
    de->SetAuger(true);
    de->SetPIXE(true);*/

}

#include "G4Decay.hh"
#include "G4ParallelWorldScoringProcess.hh"

/*void CIPhysicsList::ConstructGeneral()
{
 // Add Decay Process and Parallel world Scoring Process
 G4Decay* pDecayProcess = new G4Decay();
 G4ParallelWorldScoringProcess* pParallelWorldScoringProcess
 = new G4ParallelWorldScoringProcess ();
 pParallelWorldScoringProcess->SetParallelWorld (m_strParallelWorldName);

 theParticleIterator->reset();
 while ( (*theParticleIterator) ())
 {
   G4ParticleDefinition* theParticle = theParticleIterator->value();
   G4ProcessManager* theProcessManager = theParticle->GetProcessManager();
   if (pDecayProcess->IsApplicable (*theParticle))
   {
     theProcessManager ->AddProcess (pDecayProcess);
     theProcessManager ->SetProcessOrdering (pDecayProcess, idxPostStep);
     theProcessManager ->SetProcessOrdering (pDecayProcess, idxAtRest);
   }
   theProcessManager->AddProcess (pParallelWorldScoringProcess);
   theProcessManager->SetProcessOrderingToLast (pParallelWorldScoringProcess, idxAtRest);
   theProcessManager->SetProcessOrdering (pParallelWorldScoringProcess, idxAlongStep, 1);
   theProcessManager->SetProcessOrderingToLast (pParallelWorldScoringProcess, idxPostStep);
 }
 }*/

CIPhysicsList::~CIPhysicsList()
{
 if (m_pMessenger) delete m_pMessenger;
  delete fEmPhysicsList;

}



void CIPhysicsList::ConstructParticle()
{
// gamma
  G4Gamma::Gamma();

// leptons
  G4Electron::Electron();
  G4Positron::Positron();
  G4MuonPlus::MuonPlus();
  G4MuonMinus::MuonMinus();

// mesons
  G4PionPlus::PionPlusDefinition();
  G4PionMinus::PionMinusDefinition();
  G4KaonPlus::KaonPlusDefinition();
  G4KaonMinus::KaonMinusDefinition();

// barions
  G4Proton::Proton();
  G4AntiProton::AntiProton();
  G4Neutron::Neutron();

// ions
  G4Deuteron::Deuteron();
  G4Triton::Triton();
  G4He3::He3();
  G4Alpha::Alpha();
  G4GenericIon::GenericIonDefinition();

 G4OpticalPhoton::OpticalPhotonDefinition();

}
/*
void CIPhysicsList::ConstructParticle()
{

 // Required for em processes at our level
 G4Gamma::GammaDefinition();
 G4Electron::ElectronDefinition();
 G4Positron::PositronDefinition();
 G4Geantino::GeantinoDefinition();
 G4ChargedGeantino::ChargedGeantinoDefinition();

 // Optical photons for scintillation processing
 G4OpticalPhoton::OpticalPhotonDefinition();
 }*/


void CIPhysicsList::ConstructProcess()
{
 AddTransportation();
 //ConstructParticle();
 fEmPhysicsList->ConstructProcess();
  //ConstructGeneral();
 //ConstructPointSource();
 //ConstructEM();
 //AddPhysicsList("G4EmStandardPhysics_option4"); //new EM
 //ConstructOptical();
}


// gamma (normal implementation)
// #include "G4PhotoElectricEffect.hh"
// #include "G4ComptonScattering.hh"
// #include "G4PolarizedComptonScattering.hh"
// #include "G4GammaConversion.hh"
// gamma (low energy implementation)
// #include "G4LowEnergyPhotoElectric.hh"
// #include "G4LowEnergyRayleigh.hh"
// #include "G4LowEnergyCompton.hh"
// #include "G4LowEnergyPolarizedCompton.hh"
// #include "G4LowEnergyGammaConversion.hh"
// gamma (G4LECS implementation)
// #include "G4LECSRayleigh.hh"
// #include "G4LECSCompton.hh"

// e-
// #include "G4MultipleScattering.hh"
// #include "G4LowEnergyIonisation.hh"
// #include "G4LowEnergyBremsstrahlung.hh"
// e+
// #include "G4eIonisation.hh"
// #include "G4eBremsstrahlung.hh"
// #include "G4eplusAnnihilation.hh"

// p+
// #include "G4hIonisation.hh"

/*
void CIPhysicsList::ConstructEM()
{

 // At some point consider switch to Geant's own low energy processes to replace G4LECS
 theParticleIterator->reset();
 const G4String gammaName = G4Gamma::Definition()->GetParticleName();
 const G4String electronName = G4Electron::Definition()->GetParticleName();
 const G4String positronName = G4Positron::Definition()->GetParticleName();
 const G4String chargedGeantinoName = G4ChargedGeantino::Definition()->GetParticleName();
 while ( (*theParticleIterator) ())
 {
   G4ParticleDefinition* theParticle = theParticleIterator->value();
   G4ProcessManager* theProcessManager = theParticle->GetProcessManager();
   const G4String particleName = theParticle->GetParticleName();

   if (particleName == gammaName)
   {
     // gamma
     if (m_bUseG4LECS)
     {
       theProcessManager->AddDiscreteProcess (new G4LowEnergyPhotoElectric);
       theProcessManager->AddDiscreteProcess (new G4LECSRayleigh);
       theProcessManager->AddDiscreteProcess (new G4LECSCompton);
       theProcessManager->AddDiscreteProcess (new G4LowEnergyGammaConversion);
     }
     else
     {
       theProcessManager->AddDiscreteProcess (new G4GammaConversion());
       theProcessManager->AddDiscreteProcess (new G4ComptonScattering());
       theProcessManager->AddDiscreteProcess (new G4PhotoElectricEffect());
       theProcessManager->AddDiscreteProcess (new G4PolarizedComptonScattering());
     }


   }
   else if (particleName == electronName)
   {
     //electron
     if (m_bUseG4LECS)
     {
       theProcessManager->AddProcess (new G4MultipleScattering,        -1, 1, 1);
       theProcessManager->AddProcess (new G4LowEnergyIonisation,         -1, 2, 2);
       theProcessManager->AddProcess (new G4LowEnergyBremsstrahlung,   -1, -1, 3);
     }
     else
     {
       theProcessManager->AddProcess (new G4MultipleScattering, -1, 1, 1);
       theProcessManager->AddProcess (new G4eIonisation(),       -1, 2, 2);
       theProcessManager->AddProcess (new G4eBremsstrahlung(),   -1, -1, 3);
     }

   }
   else if (particleName == positronName)
   {
     // Standard classes:
     theProcessManager->AddProcess (new G4MultipleScattering(), -1, 1, 1);
     theProcessManager->AddProcess (new G4eIonisation(),       -1, 2, 2);
     theProcessManager->AddProcess (new G4eBremsstrahlung(),   -1, -1, 3);
     theProcessManager->AddProcess (new G4eplusAnnihilation(),  0, -1, 4);

   }
   else if ( (!theParticle->IsShortLived()) &&
             (theParticle->GetPDGCharge() != 0.0) &&
             (theParticle->GetParticleName() != chargedGeantinoName))
   {
     //all others charged particles except geantino
     theProcessManager->AddProcess (new G4MultipleScattering(), -1, 1, 1);
     theProcessManager->AddProcess (new G4hIonisation(),       -1, 2, 2);
   }
 }
}
*/
#include "G4Decay.hh"
#include "G4ParallelWorldScoringProcess.hh"
 
void CIPhysicsList::ConstructGeneral()
{
 // Add Decay Process and Parallel world Scoring Process
 G4Decay* pDecayProcess = new G4Decay();
 G4ParallelWorldScoringProcess* pParallelWorldScoringProcess
 = new G4ParallelWorldScoringProcess ();
 pParallelWorldScoringProcess->SetParallelWorld (m_strParallelWorldName);

 theParticleIterator->reset();
 while ( (*theParticleIterator) ())
 {
   G4ParticleDefinition* theParticle = theParticleIterator->value();
   G4ProcessManager* theProcessManager = theParticle->GetProcessManager();
   if (pDecayProcess->IsApplicable (*theParticle))
   {
     theProcessManager ->AddProcess (pDecayProcess);
     theProcessManager ->SetProcessOrdering (pDecayProcess, idxPostStep);
     theProcessManager ->SetProcessOrdering (pDecayProcess, idxAtRest);
   }
   theProcessManager->AddProcess (pParallelWorldScoringProcess);
   theProcessManager->SetProcessOrderingToLast (pParallelWorldScoringProcess, idxAtRest);
   theProcessManager->SetProcessOrdering (pParallelWorldScoringProcess, idxAlongStep, 1);
   theProcessManager->SetProcessOrderingToLast (pParallelWorldScoringProcess, idxPostStep);
 }
}

 
#include "G4Region.hh"
#include "G4RegionStore.hh"
#include "G4ProductionCuts.hh"

void CIPhysicsList::SetCuts()
{
 // set cut values for gamma at first and for e- second and next for e+,
 // because some processes for e+/e- need cut values for gamma

 //SetCutValue (defaultCutValue, G4Gamma::Definition()->GetParticleName());
 //SetCutValue (defaultCutValue, G4Electron::Definition()->GetParticleName());
 //SetCutValue (defaultCutValue, G4Positron::Definition()->GetParticleName());

 SetCutValue (0.001*mm, G4Gamma::Definition()->GetParticleName());
 SetCutValue (0.001*mm, G4Electron::Definition()->GetParticleName());
 SetCutValue (0.001*mm, G4Positron::Definition()->GetParticleName());
  //SetCutValue (1*mm, G4Gamma::Definition()->GetParticleName());//10keV
  //SetCutValue (1*mm, G4Electron::Definition()->GetParticleName());
 //SetCutValue (1*mm, G4Positron::Definition()->GetParticleName());

 //  SetCutsWithDefault();
 if (verboseLevel > 0) DumpCutValuesTable();

}


//Includes for the optical processes
#include "G4Scintillation.hh"
#include "G4OpAbsorption.hh"
#include "G4OpRayleigh.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4OpWLS.hh"
/*

void CIPhysicsList::ConstructOptical()
{

 if (!m_bUseOptical) return;
 // Pointer to scintillation physics process
 G4Scintillation* pScintillationProcess   = new G4Scintillation();
 pScintillationProcess->DumpPhysicsTable();
 // Pointer to optical absorption physics process
 G4OpAbsorption* pAbsorptionProcess       = new G4OpAbsorption();
 // Pointer to optical Rayleigh scattering physics process
 G4OpRayleigh* pRayleighScatteringProcess = new G4OpRayleigh();
 // Pointer to optical boundary physics processes (refraction, reflection)
 G4OpBoundaryProcess* pBoundaryProcess    = new G4OpBoundaryProcess();
 // Pointer to WLS physics processes
 G4OpWLS* pWLSProcess                     = new G4OpWLS();

 pBoundaryProcess->SetModel (G4OpticalSurfaceModel (unified));

 pScintillationProcess->SetScintillationYieldFactor (1.);
 pScintillationProcess->SetTrackSecondariesFirst (true);

 const G4String opticalPhotonName = G4OpticalPhoton::Definition()->GetParticleName();

 theParticleIterator->reset();
 while ( (*theParticleIterator) ())
 {
   G4ParticleDefinition* particle = theParticleIterator->value();
   G4ProcessManager* theProcessManager = particle->GetProcessManager();
   if (!theProcessManager) continue;
   const G4String particleName = particle->GetParticleName();
   if (pScintillationProcess->IsApplicable (*particle))
   {
     theProcessManager->AddProcess (pScintillationProcess);
     theProcessManager->SetProcessOrderingToLast (pScintillationProcess, idxAtRest);
     theProcessManager->SetProcessOrderingToLast (pScintillationProcess, idxPostStep);
   }
   if (particleName == opticalPhotonName)
   {
     G4cout << " Add optical processes to:" << opticalPhotonName << G4endl;
     theProcessManager->AddDiscreteProcess (pAbsorptionProcess);
     theProcessManager->AddDiscreteProcess (pRayleighScatteringProcess);
     theProcessManager->AddDiscreteProcess (pBoundaryProcess);
     theProcessManager->AddDiscreteProcess (pWLSProcess);
   }
 }
}


*/
/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2009.              *
 *   hseywerd@nrcan.gc.ca                                                  *
 *                                                                         *
 ***************************************************************************/
/**
 * @file CIPhysicsList
 * @brief
 *
 * @date 2009-11-14
 *
 * @author hseywerd@nrcan.gc.ca
 **/


#include "G4EmLivermorePhysics.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4DecayPhysics.hh"
#include "G4Decay.hh"
#include "G4LossTableManager.hh"
#include "G4UnitsTable.hh"
#include "G4ProcessManager.hh"

#include "G4IonFluctuations.hh"
#include "G4IonParametrisedLossModel.hh"
#include "G4EmProcessOptions.hh"

#include "G4RadioactiveDecayPhysics.hh"
#include "G4RadioactiveDecay.hh"

#include "CIPhysicsListMessenger.h"
#include "CIPhysicsList.h"


