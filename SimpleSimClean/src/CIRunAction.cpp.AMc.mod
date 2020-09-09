/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.              *
 *   hseywerd@nrcan.gc.ca                                                  *
 *                                                                         *
 ***************************************************************************/
/**
 * @file CIRunAction.cpp
 * @brief
 **/

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4RandomTools.hh"
#ifdef G4MPI_USE
#include "G4MPImanager.hh"
#endif
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TBranch.h"
#include "CIRunAction.h"
#include "CIRunActionMessenger.h"
#include "CIRootRunHeader.h"
#include "CIEventAction.h"
#include "CIDetectorConstruction.h"
#include "CIPrimaryGeneratorAction.h"

#include <sys/time.h>
#include <iostream>
#ifdef G4MPI_USE
#include "G4MPImanager.hh"
#endif

CIRunAction::CIRunAction()
  : m_pCIRunActionMessenger (NULL), m_iRunNumber(-1), m_iMPIProcessNumber(-1), m_RandomSeed(123477879), m_bEnableRootOutput(true), m_strRootFileName ("CIOutput.root"), m_pROOTOutputFile (NULL), m_pROOTRunInfoTree (NULL), m_pCIRootRunHeader (NULL), m_pROOTEventInfoTree (NULL),
    m_bNewFileForThisRun(true), m_bCloseFilesWhenFinished(true), m_bEnableASCIIOutput(false), m_strASCIIFileName("CIOutput.txt"), m_HEventPrimX(NULL), m_HEventPrimY(NULL), m_HEventPrimZ(NULL),
    m_HEventBeamXY(NULL), m_HEventBeamZY(NULL)
{
#ifdef G4MPI_USE
  m_iMPIProcessNumber= G4MPImanager::GetManager()-> GetRank();
#endif

  m_pCIRunActionMessenger = new CIRunActionMessenger (this);


}
//-----------------------------------------------------------------------------
CIRunAction::~CIRunAction()
{
  if (m_bEnableRootOutput) CleanUpHistograms();
  if (m_pCIRunActionMessenger) delete m_pCIRunActionMessenger;
  if (m_pROOTOutputFile) m_pROOTOutputFile->Close();

  //

  if (m_pCIRootRunHeader) delete m_pCIRootRunHeader;
  if (m_pROOTOutputFile) delete m_pROOTOutputFile;

}

//-----------------------------------------------------------------------------
void CIRunAction::BeginOfRunAction (const G4Run* theRun)
{

  m_iRunNumber = theRun->GetRunID();
  G4RunManager* theRunManager = G4RunManager::GetRunManager();
  CIEventAction* theEventAction =
    dynamic_cast<CIEventAction*> (const_cast<G4UserEventAction*> (theRunManager->GetUserEventAction()));
  assert(theEventAction!=NULL);

  const CIDetectorConstruction* theDetectorConstruction =
    dynamic_cast<const CIDetectorConstruction*> (theRunManager->GetUserDetectorConstruction());
  assert(theDetectorConstruction!=NULL);

  theEventAction->SetSmearValueScat(theDetectorConstruction->GetSmearFactorS());
  theEventAction->SetSmearValueAbs(theDetectorConstruction->GetSmearFactorA());

  theRunManager->GeometryHasBeenModified();

  //AMc did this:
  //long seeds[2];
  //  time_t systime = time(NULL);
  //struct timeval  tv1;
  // gettimeofday(&tv1, NULL);
  
  //seeds[0] = (long) (double(tv1.tv_sec*1000) + double(tv1.tv_usec)/1000.0);
  //seeds[1] = (long) (seeds[0]*G4UniformRand());
  //G4Random::setTheSeeds(seeds);   
  //G4cout<< "The random seeds are " << seeds[0] << " and " << seeds[1]   <<G4endl;

  //G4cout<<":::::::::::::::: new run  "<< m_iRunNumber <<G4endl;
  // Create the root output file
  if (m_bEnableRootOutput && !m_pROOTOutputFile) {

    if (m_bNewFileForThisRun) {

      SetOutputFileName();

      // Overwrite any existing file
      if (m_pROOTOutputFile) delete m_pROOTOutputFile;
      m_pROOTOutputFile = new TFile(m_strRootFileName, "RECREATE");
      //m_pROOTOutputFile->cd();

      if (m_pCIRootRunHeader) delete m_pCIRootRunHeader;
      m_pCIRootRunHeader = new CIRootRunHeader(m_iRunNumber, m_iMPIProcessNumber);
      //G4cout<<"::::::::::::::::  new file "<< m_iRunNumber << " and rank " << m_iMPIProcessNumber<<G4endl;

      // Create the trees
      //G4cout << "::::::::::::::::  Created runinfo tree and eventinfo " << G4endl;
      if (m_pROOTRunInfoTree) delete m_pROOTRunInfoTree;
      m_pROOTRunInfoTree = new TTree("RunInfo", "Run Info Tree");
      if (m_pROOTEventInfoTree) delete m_pROOTEventInfoTree;
      m_pROOTEventInfoTree = new TTree("EventInfo", "Event Information Tree");
      //G4cout << "::::::::::::::::  Create new branch on run run header " << G4endl;
      m_pROOTRunInfoTree->Branch(m_pCIRootRunHeader->ClassName(), m_pCIRootRunHeader->ClassName(), &m_pCIRootRunHeader, 32000, 99);
    }
    m_pROOTEventInfoTree->SetAutoSave(1000000);

    BookHistograms();

  }
  // Histogram preparation etc in Event Action
  if (m_bEnableRootOutput) theEventAction->PrepareOutput();



  G4cout << "##################################################################" << G4endl
	 << "#############   CIRunAction::BeginOfRunAction()  #################" << G4endl
	 << "#############   Run " << m_iRunNumber << " start." << G4endl;
  if (m_iMPIProcessNumber >= 0)
    G4cout << "#############   Running Process " << m_iMPIProcessNumber << G4endl;
  G4cout << "##################################################################" << G4endl;

  if (m_bEnableRootOutput) {
    FillRunHeader(theRun);
    m_pROOTRunInfoTree->Fill();

    if (m_bNewFileForThisRun && !m_bCloseFilesWhenFinished) m_bNewFileForThisRun = false;
  }

  //Ask the runManager to save random number seed
  //G4RunManager::GetRunManager()->SetRandomNumberStore(true);

}

//-----------------------------------------------------------------------------
void CIRunAction::EndOfRunAction (const G4Run* theRun)
{
  if (m_bEnableRootOutput && m_bCloseFilesWhenFinished) {
    // Ensure that the run information is written at end of run
    m_pROOTRunInfoTree->Write();
    //m_pROOTRunInfoTree->Reset();
    CIEventAction* theEventAction =
      dynamic_cast<CIEventAction*> (const_cast<G4UserEventAction*> (G4RunManager::GetRunManager()->GetUserEventAction()));
    assert(theEventAction!=NULL);
    theEventAction->SummarizeRun();
    theEventAction->CloseOutput();
    m_bNewFileForThisRun = true;
  }
  if (!m_bCloseFilesWhenFinished) m_bNewFileForThisRun = false;

}


//-----------------------------------------------------------------------------
void CIRunAction::FillRunHeader(const G4Run* theRun) {
  G4RunManager* theRunManager = G4RunManager::GetRunManager();
  const CIDetectorConstruction* theDetectorConstruction =
    dynamic_cast<const CIDetectorConstruction*> (theRunManager->GetUserDetectorConstruction());
  assert(theDetectorConstruction!=NULL);

  const CIPrimaryGeneratorAction* thePrimaryGeneratorAction =
    dynamic_cast<const CIPrimaryGeneratorAction*> (theRunManager->GetUserPrimaryGeneratorAction());
  assert(thePrimaryGeneratorAction!=NULL);

  m_pCIRootRunHeader->SetRunNumber(m_iRunNumber);
  m_pCIRootRunHeader->SetRank(m_iMPIProcessNumber);

  m_pCIRootRunHeader->SetESource1(thePrimaryGeneratorAction->GetESource1());
  m_pCIRootRunHeader->SetESource2(thePrimaryGeneratorAction->GetESource2());
  m_pCIRootRunHeader->SetISource1(thePrimaryGeneratorAction->GetISource1());
  m_pCIRootRunHeader->SetISource2(thePrimaryGeneratorAction->GetISource2());
  m_pCIRootRunHeader->SetSourceType(thePrimaryGeneratorAction->GetSourceType());
  m_pCIRootRunHeader->SetSmearFactorS(theDetectorConstruction->GetSmearFactorS());
  m_pCIRootRunHeader->SetSmearFactorA(theDetectorConstruction->GetSmearFactorA());
  m_pCIRootRunHeader->SetMaterialScatter(theDetectorConstruction->GetMaterialScatter());
  m_pCIRootRunHeader->SetMaterialAbsorber(theDetectorConstruction->GetMaterialAbsorber());
  m_pCIRootRunHeader->SetRunDataType(CIRootRunHeader::RTYPE_MC);
  m_pCIRootRunHeader->SetSmearType(theDetectorConstruction->GetSmearType());

}
//-----------------------------------------------------------------------------
void CIRunAction::SetOutputFileName() {
#ifdef G4MPI_USE
  //If the file is a .root file, remove this suffix, append a file indicator, and reapply the suffix.
  //Otherwise, simply append the suffix
  std::ostringstream fileNum;
  fileNum << "_MPI";
  fileNum.width(3);
  fileNum.fill('0');
  fileNum << m_iMPIProcessNumber;

  G4String s = m_strRootFileName;
  std::transform(s.begin(), s.end(), s.begin(), toupper);
  size_t found = s.find(".ROOT");
  if (found != std::string::npos) {
    m_strRootFileName = m_strRootFileName.substr(0, found);
    m_strRootFileName = m_strRootFileName + fileNum.str();
    m_strRootFileName += ".root";
  } else {
    m_strRootFileName = m_strRootFileName + fileNum.str();
  }
#endif
}

//-----------------------------------------------------------------------------
void CIRunAction::BookHistograms() {
  // Beam and primary vertex info
  m_HEventPrimX = new TH1F("EventPrimX", "Primary vertex x", 100, -10.0, 10.0);
  m_HEventPrimY = new TH1F("EventPrimY", "Primary vertex y", 100, -10.0, 10.0);
  m_HEventPrimZ = new TH1F("EventPrimZ", "Primary vertex z ", 100, -40010, -39990);
  m_HEventBeamE = new TH1F("EventBeamE", "Beam Energy ", 100, 0.0, 2.0);
  m_HEventBeamXY = new TH2F("EventBeamXY", "Beam distribution at origin in XY (mm)", 20, -300, 300, 20, -300, 300);
  m_HEventBeamZY = new TH2F("EventBeamZY", "Beam distribution at origin in ZY (mm)", 20, -300, 300, 20, -300, 300);

  // For optical hits
  // Same but related to optical hits
  /// Histogram for optical hit energy (scatter det)
  m_HOpHitScatE = new TH1F("OpHitScatE", "Optical hit energy scatter (nm)", 100, 350., 500.);
  /// Histogram for optical hit energy (absorber det)
  m_HOpHitAbsE = new TH1F("OpHitAbsE", "Optical hit energy absorber (nm)", 100, 350., 500.);
  /// Histogram for optical hit time (scatter det)
  m_HOpHitScatT = new TH1F("OpHitScatT", "Optical hit time scatter (ns)", 100, 0., 1000.);
  /// Histogram for optical hit time (absorber det)
  m_HOpHitAbsT = new TH1F("OpHitAbsT", "Optical hit time absorber (ns)", 100, 0., 1000.);
  /// Histogram for optical photon path length for those photons created in the scatter det
  m_HOpHitScatL = new TH1F("OpHitScatL", "Optical Photon path scatter det (mm)", 100, 0., 100.);
  /// Histogram for optical photon path length for those photons created in the absorber det
  m_HOpHitAbsL = new TH1F("OpHitAbsL", "Optical Photon path absorber det (mm)", 100, 0., 100.);
  /// Histogram for optical photon HIT multiplicity for those photons created in the scatter det
  m_HOpHitScatMult = new TH1F("OpHitScatMult", "Optical Photon hit multiplicity scatter det", 100, 0, 50000);
  /// Histogram for optical photon multiplicity for those photons created in the absorber det
  m_HOpHitAbsMult = new TH1F("OpHitAbsMult", "Optical Photon hit multiplicity absorber det", 100, 0, 50000);

  /// Histogram for optical photon multiplicity for those photons created in the scatter det
  m_HOpScatMult = new TH1F("OpScatMult", "Optical Photon created multiplicity scatter det", 100, 0, 50000);
  /// Histogram for optical photon multiplicity for those photons created in the absorber det
  m_HOpAbsMult = new TH1F("OpAbsMult", "Optical Photon created multiplicity absorber det", 100, 0, 50000);

}

//-----------------------------------------------------------------------------
void CIRunAction::SaveHistograms() {

}


//-----------------------------------------------------------------------------
void CIRunAction::CleanUpHistograms() {

  // Clean up any created histos.
  if (m_HEventPrimX) delete m_HEventPrimX;
  if (m_HEventPrimY) delete m_HEventPrimY;
  if (m_HEventPrimZ) delete m_HEventPrimZ;
  if (m_HEventBeamE) delete m_HEventBeamE;
  if (m_HEventBeamXY) delete m_HEventBeamXY;
  if (m_HEventBeamZY) delete m_HEventBeamZY;
  G4cout<<"delete output histos "<<G4endl;



  if (m_HOpHitScatE) delete m_HOpHitScatE;
  if (m_HOpHitAbsE) delete m_HOpHitAbsE;
  if (m_HOpHitScatT) delete m_HOpHitScatT;
  if (m_HOpHitAbsT) delete m_HOpHitAbsT;
  if (m_HOpHitScatL) delete m_HOpHitScatL;
  if (m_HOpHitAbsL) delete  m_HOpHitAbsL;
  if (m_HOpHitScatMult) delete m_HOpHitScatMult;
  if (m_HOpHitAbsMult) delete m_HOpHitAbsMult;
  if (m_HOpScatMult) delete m_HOpScatMult;
  if (m_HOpAbsMult) delete m_HOpAbsMult;

}
