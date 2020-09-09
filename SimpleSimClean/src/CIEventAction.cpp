/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2009.              *
 *   hseywerd@nrcan.gc.ca                                                  *
 *                                                                         *
 ***************************************************************************/
/**
 * @file CIEventAction.cpp
 * @brief Implementation of per event actions
 **/

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4SDManager.hh"
#include "G4Trajectory.hh"
#include "G4TrajectoryPoint.hh"
#include "G4OpticalPhoton.hh"
#include "TROOT.h"
#include "TClonesArray.h"
#include "TTree.h"
#include "TBranch.h"
#include "TH1F.h"
#include "TH2F.h"
#include "CLHEP/Random/RandGauss.h"
#include "CLHEP/Units/SystemOfUnits.h"
#include <sstream>

#include "CIEventAction.h"
#include "CIEventActionMessenger.h"
#include "CIOutputEvent.h"
#include "CIOutputHit.h"
#include "CIOutputScintiHit.h"
#include "CIOutputPhotoHit.h"
#include "CIOutputSummedHit.h"
#include "CIOutputPhotoDetectorHit.h"
#include "CIOutputMaterialHit.h"
#include "CIRunAction.h"
#include "CISensitiveScintiDetector.h"
#include "CISensitiveOpticalDetector.h"
#include "CISensitiveMaterials.h"
#include "CIModuleTable.h"

#include "G4TransportationManager.hh"
using namespace CLHEP;
using namespace std;

CIEventAction::CIEventAction() :
	m_pCIRunAction(NULL), m_pCIEventActionMessenger(NULL), m_pROOTEventInfoTree(NULL), m_pCIOutputEvent(NULL), m_pCISensitiveScintiDetector(
			NULL), m_pCISensitiveOpticalDetector(NULL), m_pCISensitiveMaterials(NULL), m_bSaveOpticalPhotonHits(true), m_bSaveScintiHits(true),
			m_bSaveProcessedHits(true), m_iSaveOnlyCoincidence(0), m_bApplySmear(false), m_dSmearFactorScat(0),
			 m_dSmearFactorAbs(0), m_pModuleTable(NULL), m_bEnableRootOutput(false),  m_bEnableASCIIOutput(false), m_strASCIIFileName("") {
	// Register the user interface handler
	m_pCIEventActionMessenger = new CIEventActionMessenger(this);


	m_pCIRunAction =
					dynamic_cast<CIRunAction*> (const_cast<G4UserRunAction*> (G4RunManager::GetRunManager()->GetUserRunAction()));
	assert(m_pCIRunAction != NULL);

	m_iNTraj = 0;


}

//-----------------------------------------------------------------------------
CIEventAction::~CIEventAction() {
	if (m_pCIEventActionMessenger)
		delete m_pCIEventActionMessenger;
	if (m_pCIOutputEvent)
		delete m_pCIOutputEvent;
}

//-----------------------------------------------------------------------------
void CIEventAction::PrepareOutput(){
	// Get the tree into which the event information is to be stored

	m_bEnableRootOutput = m_pCIRunAction->m_bEnableRootOutput;
	m_bEnableASCIIOutput = m_pCIRunAction->m_bEnableASCIIOutput;

	if (m_bEnableRootOutput) {
		if (!m_pCIOutputEvent) {
			G4cout << "New CIEventAction created " << G4endl;
			m_pCIOutputEvent = new CIOutputEvent();
			assert(m_pCIOutputEvent != NULL);

			m_pROOTEventInfoTree = m_pCIRunAction->m_pROOTEventInfoTree;
  		// And insert the classes into a new branch for the run
			std::string  branchName = m_pCIOutputEvent->ClassName();
			m_pROOTEventInfoTree->Branch(branchName.c_str(), m_pCIOutputEvent->ClassName(), &m_pCIOutputEvent, 32000, 99);
		}
	}

	if (m_bEnableASCIIOutput) {
		m_strASCIIFileName = m_pCIRunAction->m_strASCIIFileName;
		G4String name = "NPHOTON.";
		name+=m_strASCIIFileName;
		m_PhotonFile.open(name);
		name = "SCINTI.";
		name+=m_strASCIIFileName;
		m_ScintiFile.open(name);
	}
}

//-----------------------------------------------------------------------------
void CIEventAction::BeginOfEventAction(const G4Event* pEvt) {
	// General information
	G4RunManager* theRunManager = G4RunManager::GetRunManager();
	G4int id = fpEventManager->GetConstCurrentEvent()->GetEventID();
	//	G4cout << " Start event number " << id << G4endl;

}

//-----------------------------------------------------------------------------
void CIEventAction::EndOfEventAction(const G4Event* pEvt) {

	// General information
	G4RunManager* theRunManager = G4RunManager::GetRunManager();
	G4int id = fpEventManager->GetConstCurrentEvent()->GetEventID();
	if (m_bEnableRootOutput) {
		m_pCIOutputEvent->m_dEventNum = id;
		m_pCIOutputEvent->m_dRunNum = theRunManager->GetCurrentRun()->GetRunID();
		

		//AMC did this
		m_pCIOutputEvent->m_dPrimaryVertexX = pEvt->GetPrimaryVertex()->GetPosition().getX();
		m_pCIOutputEvent->m_dPrimaryVertexY = pEvt->GetPrimaryVertex()->GetPosition().getY();
		m_pCIOutputEvent->m_dPrimaryVertexZ = pEvt->GetPrimaryVertex()->GetPosition().getZ();


		m_pCIOutputEvent->m_dPrimaryVertexPX = pEvt->GetPrimaryVertex()->GetPrimary()->GetPx();
		m_pCIOutputEvent->m_dPrimaryVertexPY = pEvt->GetPrimaryVertex()->GetPrimary()->GetPy();
		m_pCIOutputEvent->m_dPrimaryVertexPZ = pEvt->GetPrimaryVertex()->GetPrimary()->GetPz();
		







		// Fill standard histograms
		CheckEvent(pEvt);
	}
	if (id%50000 ==0 && id>0) G4cout << "Completed event: "<< id << " of Run " << theRunManager->GetCurrentRun()->GetRunID() << G4endl;

  ////////////////////////////////
	// ASCII OUTPUT OF MAIN NUMBERS
	////////////////////////////////
	if (m_bEnableASCIIOutput) {
		SaveASCIISummedData(id);
		//m_PhotonFile << id << " " << nScintiHit << " " << thOptiCollection->entries() << "\n";
		SaveASCIIScinData(id);
	}

	//	cout << " misaveonlycoincidence is " << m_iSaveOnlyCoincidence << endl;
	//bool isCoincidence = false;
	// OLD Logic checked if event had comptons
	//if (GetNumComptons() >0) isCoincidence = true;
	//if (m_bSaveOnlyCoincidence & !isCoincidence) return;

	// Scrap the event if we wanted coincidences, but this event doesn't have any.
	switch (m_iSaveOnlyCoincidence) {
	case 0:
		break;
	case 1:
		if(CheckNCellsHit()<1) 
		  {
		    return;
		  }
		//G4cout<<"Check coin " << m_iSaveOnlyCoincidence<< " and "<<CheckNCellsHit()<<G4endl;
		break;
	case 2:
		if(CheckNCellsHit()<2) return;
		//G4cout<<"Check coin " << m_iSaveOnlyCoincidence<< " and "<<CheckNCellsHit()<<G4endl;
		break;
	default:
		// Should not get here
		assert(true);
		return;
	}


	if (m_bEnableRootOutput) {
		// Get the scintillator and the optical photon hits collections for this event
		// and save them.
	  if (m_bSaveScintiHits) {
	    // G4cout << "saving scinti hits " << G4endl;
SaveScintiHits();
	  }
		// A hit collection for optical photon data in a detector
		if (m_bSaveOpticalPhotonHits) SaveOptiHits();
		PlotOptiHits(pEvt);

		if (m_bSaveProcessedHits)
		   SaveCellSummedData();
		//G4cout <<" now saving cellsumemd opti data" << G4endl;
		SaveCellSummedOptiData();

		SaveMaterialHits();

		m_pROOTEventInfoTree->Fill();

		// Empty the stuff
		(*m_pCIOutputEvent->m_ScintiHitList).Delete();
		(*m_pCIOutputEvent->m_OpticalHitList).Delete();
		(*m_pCIOutputEvent->m_OutputSummedHitList).Delete();
		(*m_pCIOutputEvent->m_SummedOptiHitList).Delete();
		(*m_pCIOutputEvent->m_MaterialHitList).Delete();

	}

}

//-----------------------------------------------------------------------------
void CIEventAction::CloseOutput() {
	if (m_bEnableRootOutput) {
		m_pROOTEventInfoTree->Write();

		//G4cout<<":::::::::::::::: Writing event tree for run " << m_pCIRunAction->m_iRunNumber <<G4endl;
	  m_pCIRunAction->m_HEventPrimX->Write();
	  m_pCIRunAction->m_HEventPrimY->Write();
	  m_pCIRunAction->m_HEventPrimZ->Write();
	  m_pCIRunAction->m_HEventBeamE->Write();
	  m_pCIRunAction->m_HEventBeamXY->Write();
	  m_pCIRunAction->m_HEventBeamZY->Write();
	  m_pCIRunAction->m_HOpHitScatE->Write();
	  m_pCIRunAction->m_HOpHitAbsE->Write();
	  m_pCIRunAction->m_HOpHitScatT->Write();
	  m_pCIRunAction->m_HOpHitAbsT->Write();
	  m_pCIRunAction->m_HOpHitScatL->Write();
	  m_pCIRunAction->m_HOpHitAbsL->Write();
	  m_pCIRunAction->m_HOpHitScatMult->Write();
	  m_pCIRunAction->m_HOpHitAbsMult->Write();
	  m_pCIRunAction->m_HOpScatMult->Write();
	  m_pCIRunAction->m_HOpAbsMult->Write();

	}

	if (m_bEnableASCIIOutput)  {
		m_PhotonFile.close();
		m_ScintiFile.close();
	}
}


//-----------------------------------------------------------------------------
void CIEventAction::CheckEvent(const G4Event* pEvt) {
	// Some basic histos
	// Make sure that they exist
	assert(m_pCIRunAction->m_HEventPrimX);
	assert(m_pCIRunAction->m_HEventPrimY);
	assert(m_pCIRunAction->m_HEventPrimZ);
	assert(m_pCIRunAction->m_HEventBeamXY);
	assert(m_pCIRunAction->m_HEventBeamZY);



	const G4ThreeVector primaryVertexPos = pEvt->GetPrimaryVertex()->GetPosition();
	const double vX = primaryVertexPos.getX();
	const double vY = primaryVertexPos.getY();
	const double vZ = primaryVertexPos.getZ();
	const double vR = sqrt(vX*vX + vY*vY + vZ*vZ);
	assert(m_pCIRunAction->m_HEventPrimX);
  m_pCIRunAction->m_HEventPrimX->Fill(vX);
  m_pCIRunAction->m_HEventPrimY->Fill(vY);
  m_pCIRunAction->m_HEventPrimZ->Fill(vZ);
  G4ThreeVector pBeam = pEvt->GetPrimaryVertex()->GetPrimary()->GetMomentum();
  double E = sqrt(pBeam*pBeam);
  m_pCIRunAction->m_HEventBeamE->Fill(E);

  // Direction angles of the primary beam
	const double pX = pEvt->GetPrimaryVertex()->GetPrimary()->GetPx();
	const double pY = pEvt->GetPrimaryVertex()->GetPrimary()->GetPy();
	const double pZ = pEvt->GetPrimaryVertex()->GetPrimary()->GetPz();
	const double pR = sqrt(pX*pX+pY*pY+pZ*pZ);

	// Incoming beam position at the origin.
	const double x = pX/pR*vR+vX;
  const double y = pY/pR*vR+vY;
  const double z = pZ/pR*vR+vZ;

  // Plot the beam spot
  m_pCIRunAction->m_HEventBeamXY->Fill(x/mm,y/mm);
  m_pCIRunAction->m_HEventBeamZY->Fill(z/mm,y/mm);
}

//-----------------------------------------------------------------------------
bool CIEventAction::IsCoincidenceEvent() {

	// Spin through the Scinit Hits first to determine if there is more than one cell hit, i.e. a coincidence event
	// Then if we are saving only coincidences we can know.
	bool isCoincidence = false;
	CIScintiHitsCollection* theCIScintiHitsCollection = m_pCISensitiveScintiDetector->GetHitsCollection();
	const G4int nScintiHit = theCIScintiHitsCollection->entries();
	if (nScintiHit > 0) {
		CIScintiHit *theFirstHit = (*theCIScintiHitsCollection)[0];
		const G4int firstModuleID = theFirstHit->TheModuleID();
		for (int iScintiHit = 1; iScintiHit < theCIScintiHitsCollection->entries(); iScintiHit++) {
			CIScintiHit *theHit = (*theCIScintiHitsCollection)[iScintiHit];
			if (theHit->TheModuleID() != firstModuleID) {
				isCoincidence = true;
				break;
			}
		}
	}
	return isCoincidence;
}

//-----------------------------------------------------------------------------
int CIEventAction::GetNumComptons() {

	// Spin through the Scinit Hits and determine how many comptons there are
	int nCompton = 0;
	CIScintiHitsCollection* theCIScintiHitsCollection = m_pCISensitiveScintiDetector->GetHitsCollection();
	const G4int nScintiHit = theCIScintiHitsCollection->entries();
	if (nScintiHit > 0) {
		for (int iScintiHit = 0; iScintiHit < theCIScintiHitsCollection->entries(); iScintiHit++) {
			CIScintiHit *theHit = (*theCIScintiHitsCollection)[iScintiHit];
			const CIOutputEvent::HITTYPE Htype = m_pCIOutputEvent->GetHTypeFromName(theHit->TheInteractionProcessName());
			if (Htype == CIOutputEvent::HTYPE_COMPTON ||
				Htype == CIOutputEvent::HTYPE_LECOMPTON ||
				Htype == CIOutputEvent::HTYPE_LEPCOMPTON ) {
				nCompton++;
			}
		}
	}
	return nCompton;

}

//-----------------------------------------------------------------------------
void CIEventAction::SaveScintiHits() {

	const CIModuleTable* pModuleTable = m_pCISensitiveScintiDetector->GetCIModuleTable();
	TClonesArray& outScintHitArrary = *m_pCIOutputEvent->m_ScintiHitList;
	CIScintiHitsCollection* theCollection = m_pCISensitiveScintiDetector->GetHitsCollection();


	for (int iScintiHit = 0; iScintiHit < theCollection->entries(); iScintiHit++) {
		CIScintiHit *theHit = (*theCollection)[iScintiHit];
		const CIOutputEvent::HITTYPE Htype = m_pCIOutputEvent->GetHTypeFromName(theHit->TheInteractionProcessName());
		const CIOutputEvent::PARTTYPE Ptype = m_pCIOutputEvent->GetPTypeFromName(theHit->ThePartName());
		CIOutputEvent::SUBDET subDet = CIOutputEvent::SUBDET_OTHER;
		if (pModuleTable->GetSubDetector(theHit->TheModuleID()) == CIModuleTable::SUBDET_SCATTER)
			subDet = CIOutputEvent::SUBDET_SCATTER;
		else if (pModuleTable->GetSubDetector(theHit->TheModuleID()) == CIModuleTable::SUBDET_ABSORBER)
			subDet= CIOutputEvent::SUBDET_ABSORBER;
		//CIOutputHit* hit =
		new (outScintHitArrary[iScintiHit]) CIOutputScintiHit(theHit->GetPos().x(), theHit->GetPos().y(),
				theHit->GetPos().z(), theHit->TheTime(), theHit->TheEnergy(), theHit->TheEnergyDep(),
				theHit->TheModuleID(), subDet, theHit->TheTrackID(), theHit->TheParentTrackID(), Htype, Ptype);
//					G4cout << "Saved Scinti hit " << iScintiHit << " from particle type " << theHit->ThePartName() <<
//					theHit->GetPos().x()<< " " << theHit->GetPos().y() << " " <<theHit->GetPos().z() <<G4endl;


		//					<< " ID " << theHit->TheTrackID() << " and parent " << theHit->TheParentTrackID() << " Interacted by  "
		//					<< theHit->TheInteractionProcessName() << " in Cell " << theHit->TheModuleID() << G4endl;
		//hit->PPrint();

	}
	//

}

//-----------------------------------------------------------------------------
void CIEventAction::SaveOptiHits() {
 
	const CIModuleTable* pModuleTable = m_pCISensitiveScintiDetector->GetCIModuleTable();
	CIOpticalPhotonHitsCollection* theOptiCollection = m_pCISensitiveOpticalDetector->GetHitsCollection();
	TClonesArray & outOptiHitArrary = *m_pCIOutputEvent->m_OpticalHitList;
	CIScintiHitsCollection* theScintiCollection = m_pCISensitiveScintiDetector->GetHitsCollection();
	for (int iOptiHit = 0; iOptiHit < theOptiCollection->entries(); iOptiHit++) {
		CIOpticalPhotonHit *theHit = (*theOptiCollection)[iOptiHit];
		// Figure out which of the Scinti hits generated this optical hit
		int iScintiHitIndex = -1;
		for (int iScintiHit = 0; iScintiHit < theScintiCollection->entries(); iScintiHit++) {
			CIScintiHit *theScintiHit = (*theScintiCollection)[iScintiHit];
			if (theScintiHit->TheTrackID() == theHit->TheParentTrackID()) {
				iScintiHitIndex = iScintiHit;
				break;
			}
		}
		const CIOutputEvent::HITTYPE Htype = CIOutputEvent::HTYPE_SCINT;
		const CIOutputEvent::PARTTYPE Ptype = m_pCIOutputEvent->GetPTypeFromName(theHit->ThePartName());
		CIOutputEvent::SUBDET subDet = CIOutputEvent::SUBDET_OTHER;
		if (pModuleTable->GetSubDetector(theHit->TheModuleID()) == CIModuleTable::SUBDET_SCATTER)
			subDet = CIOutputEvent::SUBDET_SCATTER;
		else if (pModuleTable->GetSubDetector(theHit->TheModuleID()) == CIModuleTable::SUBDET_ABSORBER)
			subDet= CIOutputEvent::SUBDET_ABSORBER;
		new (outOptiHitArrary[iOptiHit]) CIOutputPhotoHit(theHit->GetPos().x(), theHit->GetPos().y(),
				theHit->GetPos().z(), theHit->TheTime(), theHit->TheEnergy(), theHit->TheModuleID(),
				subDet, theHit->TheTrackID(), theHit->TheParentTrackID(), Htype, Ptype, iScintiHitIndex);
		//G4cout << "Save opti hit "<<theHit->GetPos() <<" in det "<<theHit->TheModuleID()<< " subdet "<< subDet<<G4endl;
	}

}

//-----------------------------------------------------------------------------
void CIEventAction::SaveCellSummedData() {

	TClonesArray& outHitArrary = *m_pCIOutputEvent->m_OutputSummedHitList;
	CIScintiHitsCollection* theCollection = m_pCISensitiveScintiDetector->GetHitsCollection();
	const CIModuleTable* pModuleTable = m_pCISensitiveScintiDetector->GetCIModuleTable();

	//Audrey: ncells = MaxModules changed to ncells = maxmodules+1 here and elsewhere.
	const int nCells = pModuleTable->GetMaxModules()+1;
	vector<double> cellEnergy(nCells);
	vector<int> cellLayer(nCells);
	vector<double> cellSmearedEnergy(nCells);
	vector<double> cellTime(nCells);
	vector<CIModuleTable::SUBDET> cellSubDet(nCells);
	cellEnergy.assign(cellEnergy.size(), 0.0);
	cellLayer.assign(cellLayer.size(), 0);
	cellSmearedEnergy.assign(cellSmearedEnergy.size(), 0.0);
	cellTime.assign(cellTime.size(), 1000000.0);
	cellSubDet.assign(cellSubDet.size(), CIModuleTable::SUBDET_OTHER);
	for (int iScintiHit = 0; iScintiHit < theCollection->entries(); iScintiHit++) {
		CIScintiHit *theHit = (*theCollection)[iScintiHit];
		const int iCell = theHit->TheModuleID();
			assert(iCell<nCells);
		cellEnergy[iCell] += theHit->TheEnergyDep();
		CIModuleTable::SUBDET subDetector = pModuleTable->GetSubDetector(iCell);
		double Esmear=0.;
		if (subDetector == CIModuleTable::SUBDET_SCATTER)
			Esmear = GaussianSmear(theHit->TheEnergyDep(), m_dSmearFactorScat);
		else if (subDetector == CIModuleTable::SUBDET_ABSORBER)
			Esmear = GaussianSmear(theHit->TheEnergyDep(), m_dSmearFactorAbs);
		cellSmearedEnergy[iCell] += Esmear;
		cellSubDet[iCell] = subDetector;
		cellLayer[iCell] = pModuleTable->GetLayer(iCell);
		if (theHit->TheTime()<cellTime[iCell]) {
			cellTime[iCell] = theHit->TheTime();
		}
		//G4cout<<"cell # "<<iCell<<" has track "<<theHit->ThePartName()<<" from "<<  theHit->TheParentTrackID()<< theHit->TheTrackID()  <<" At time "<<theHit->TheTime() <<" and Z "<< theHit->GetPos().z() <<G4endl;
	}

	// Now created the output data
	int iHit = 0;
	for (int iCell = 0; iCell < nCells; iCell++) {
		if (cellEnergy[iCell] > 0) {
			new (outHitArrary[iHit]) CIOutputSummedHit();
			CIOutputSummedHit* theHit = dynamic_cast<CIOutputSummedHit*> (outHitArrary[iHit]);
			theHit->TheCellID() = iCell;
			theHit->TheEnergy() = cellEnergy[iCell];
			theHit->TheSmearedEnergy() = cellSmearedEnergy[iCell];
			//	G4cout << "icell is "<< iCell << G4endl;
			const G4ThreeVector position = m_pCISensitiveOpticalDetector->GetCIModuleTable()->GetActivePosition(iCell);
			theHit->SetHitPosition(ROOT::Math::XYZVector(position.getX(), position.getY(), position.getZ()));
			theHit->TheLayer() = cellLayer[iCell];
			theHit->SetT(cellTime[iCell]);
			//G4cout<<"Saving cell summed data "<< iCell<< " Energy deposited " <<theHit->TheSmearedEnergy()<<G4endl;
			//G4cout<<" Hit position is " << position << G4endl;


			if (cellSubDet[iCell] == CIModuleTable::SUBDET_SCATTER)
				theHit->TheSubDetector() = CIOutputSummedHit::SUBDET_SCATTER;
			else if (cellSubDet[iCell] == CIModuleTable::SUBDET_ABSORBER)
				theHit->TheSubDetector() = CIOutputSummedHit::SUBDET_ABSORBER;
			else
				theHit->TheSubDetector() = CIOutputSummedHit::SUBDET_OTHER;
			iHit++;
		}
	}


}

//-----------------------------------------------------------------------------
double CIEventAction::GaussianSmear(const double x, const double smearFactor) const {
	double sigma = smearFactor * sqrt(x);
	return CLHEP::RandGauss::shoot(x, sigma);
}

//-----------------------------------------------------------------------------
void CIEventAction::SaveASCIIScinData(const int eventID) {

	CIScintiHitsCollection* theCollection = m_pCISensitiveScintiDetector->GetHitsCollection();
	//outScintHitArrary.Clear();

	for (int iScintiHit = 0; iScintiHit < theCollection->entries(); iScintiHit++) {
	  CIScintiHit *theHit = (*theCollection)[iScintiHit];
	  const CIOutputEvent::HITTYPE Htype = m_pCIOutputEvent->GetHTypeFromName(theHit->TheInteractionProcessName());
	  const CIOutputEvent::PARTTYPE Ptype = m_pCIOutputEvent->GetPTypeFromName(theHit->ThePartName());


	  m_ScintiFile << eventID  << "  " << theHit->GetPos().x() << "  " << theHit->GetPos().y() << "  " <<
	    theHit->GetPos().z() << "  " << theHit->TheTime() << "  " << theHit->TheEnergy() << "  " <<theHit->TheEnergyDep() << "  " << theHit->TheModuleID() << "  " << theHit->TheTrackID() << "  " << theHit->TheParentTrackID() << "  " << Htype << "  " << Ptype << G4endl;
	}
}

//-----------------------------------------------------------------------------
void CIEventAction::SaveCellSummedOptiData(){

  	TClonesArray& outHitArrary = *m_pCIOutputEvent->m_SummedOptiHitList;
	CIOpticalPhotonHitsCollection* theCollection = m_pCISensitiveOpticalDetector->GetHitsCollection();
	const CIModuleTable* pModuleTable = m_pCISensitiveOpticalDetector->GetCIModuleTable();
	const int nCells = pModuleTable->GetMaxModules()+1;
	vector<double> cellSum(nCells);
	vector<int> cellLayer(nCells);
	vector<CIModuleTable::SUBDET> cellSubDet(nCells);
	cellSum.assign(cellSum.size(), 0.0);
	cellLayer.assign(cellLayer.size(), 0);
	cellSubDet.assign(cellSubDet.size(), CIModuleTable::SUBDET_OTHER);


	for (int iOptiHit = 0; iOptiHit < theCollection->entries(); iOptiHit++) {
		CIOpticalPhotonHit *theHit = (*theCollection)[iOptiHit];
		const int iCell = theHit->TheModuleID();
		//	G4cout << " icell is " << iCell << endl;
		//G4cout << " ncells is " << nCells << endl;
		//	cout << "icell is " << iCell << " and ncell is " << nCells << endl;;
		
		assert(iCell<nCells);
		if (iCell<0) G4cout<<"Got a neg cell "<<iCell<<G4endl;
		assert(iCell>=0);
		//cellSum[iCell]++;
		//Audrey: replace cellSum as being the total number of modules hit to the total number of photons detected in that run
		cellSum[iCell]= theCollection->entries();
	
		CIModuleTable::SUBDET subDetector = pModuleTable->GetSubDetector(iCell);
		cellSubDet[iCell] = subDetector;
		//cellLayer[iCell] = pModuleTable->GetLayer(iCell);
		//Audrey: replace increment cell layer for each module
		cellLayer[iCell]++;

	}

	// Now created the output data
	int iHit = 0;
	for (int iCell = 0; iCell < nCells; iCell++) {
		if (cellSum[iCell] > 0) {
			new (outHitArrary[iHit]) CIOutputPhotoDetectorHit();
			CIOutputPhotoDetectorHit* theHit = dynamic_cast<CIOutputPhotoDetectorHit*> (outHitArrary[iHit]);
			//Audrey: replace increment cell layer for each modulemodule id with left pmt photons (unjdo put in time instead)

			//	theHit->m_iModuleID = iCell;

			theHit->m_iModuleID = iCell;//left pmt photons
			//	cout <<" saving number of photons detected in " << iCell << " is " << cellLayer[iCell] << endl;
			theHit->m_dT = cellLayer[iCell];
			assert(iCell<nCells);
			//	cout << "icell is " << iCell << " and ncell is " << nCells;
			if (iCell<0) G4cout<<"Got a neg cell "<<iCell<<G4endl;
			assert(iCell>=0);
			theHit->m_dE= cellSum[iCell];
			//G4cout<<"Save cell " << iCell<< " with " <<cellSum[iCell]<<G4endl;
			const G4ThreeVector position = m_pCISensitiveOpticalDetector->GetCIModuleTable()->GetActivePosition(iCell);
			//G4cout<<"position "<< position<<G4endl;
			theHit->m_dX = position.getX();
			theHit->m_dY = position.getY();
			theHit->m_dZ = position.getZ();
			//cout << " the x position is "<< position.getX() << endl;
			//cout << " the y position is "<< position.getY() << endl;
			//theHit->TheLayer() = cellLayer[iCell];
			if (cellSubDet[iCell] == CIModuleTable::SUBDET_SCATTER)
				theHit->m_SubDetector = CIOutputEvent::SUBDET_SCATTER;
			else if (cellSubDet[iCell] == CIModuleTable::SUBDET_ABSORBER)
				theHit->m_SubDetector = CIOutputEvent::SUBDET_ABSORBER;
			else
				theHit->m_SubDetector = CIOutputEvent::SUBDET_OTHER;
			iHit++;
		}
	}

}


//-----------------------------------------------------------------------------
void CIEventAction::SaveASCIISummedData(const int eventID) {

	CIScintiHitsCollection* theCollection = m_pCISensitiveScintiDetector->GetHitsCollection();
	CIOpticalPhotonHitsCollection* theOptiCollection = m_pCISensitiveOpticalDetector->GetHitsCollection();

	const CIModuleTable* pModuleTable = m_pCISensitiveScintiDetector->GetCIModuleTable();
	const int nCells = pModuleTable->GetMaxModules()+1;
	vector<double> cellEnergy(nCells);
	vector<double> cellSmearedEnergy(nCells);
	vector<double> photonHits(nCells);
	vector<int> processHits(CIOutputEvent::HTYPE_LAST_IN_THE_LIST);
	cellEnergy.clear();
	cellSmearedEnergy.clear();
	photonHits.clear();
	processHits.clear();

	for (int iScintiHit = 0; iScintiHit < theCollection->entries(); iScintiHit++) {
		CIScintiHit *theHit = (*theCollection)[iScintiHit];

		const CIOutputEvent::HITTYPE Htype = m_pCIOutputEvent->GetHTypeFromName(theHit->TheInteractionProcessName());
		const int iCell = theHit->TheModuleID();
		cellEnergy[iCell] += theHit->TheEnergyDep();
		CIModuleTable::SUBDET subDetector = pModuleTable->GetSubDetector(iCell);

		double Esmear=0.;
		if (subDetector == CIModuleTable::SUBDET_SCATTER)
			Esmear = GaussianSmear(theHit->TheEnergyDep(), m_dSmearFactorScat);
		else if (subDetector == CIModuleTable::SUBDET_ABSORBER)
			Esmear = GaussianSmear(theHit->TheEnergyDep(), m_dSmearFactorAbs);


		cellSmearedEnergy[iCell] += Esmear;

		// How many different types of hits
		// Compton scatter is HTYPE=1;
		const int hcell=Htype;
		processHits[hcell]++;
	}

	for (int iOptiHit = 0; iOptiHit < theOptiCollection->entries(); iOptiHit++) {
	  CIOpticalPhotonHit *theOpHit = (*theOptiCollection)[iOptiHit];
	  const int oCell = theOpHit->TheModuleID();
	  photonHits[oCell] ++;
	}

	if (cellEnergy.size() > 0 && cellEnergy[0] > 0);
	  m_PhotonFile << eventID  << "  " << theCollection->entries() << "  " << theOptiCollection->entries() << "  " << processHits[1] << "  " << processHits[2] << "  " << processHits[5] << "  " << cellEnergy[0] << "  " << photonHits[2] << "  " << photonHits[3] << G4endl;
}




//-----------------------------------------------------------------------------
void CIEventAction::SummarizeRun() {

	const int nEvent = m_pROOTEventInfoTree->GetEntries();
	int nWHit=0;
	int nWComptons=0;
	int nWOneCompton=0;
	int nWPE=0;
	int nPECompt=0;

	for (int iEvt = 0; iEvt < nEvent; iEvt++) {
		m_pROOTEventInfoTree->GetEntry(iEvt);
		TClonesArray & scintiHits = *(m_pCIOutputEvent->m_ScintiHitList);
		int nScintiHits = scintiHits.GetEntries();
		if (nScintiHits>0) nWHit++;
		CIOutputScintiHit* theHit;
		TIter ScinHitIter(&scintiHits);

		int nCompton = 0;
		int nPE = 0;

		while ((theHit = dynamic_cast<CIOutputScintiHit*> (ScinHitIter.Next()))) {
			//if (theHit->m_dEDeposit<=0.01) continue;
			if (theHit->m_HitType == CIOutputEvent::HTYPE_COMPTON) {
				nCompton++;
			} else if (theHit->m_HitType == CIOutputEvent::HTYPE_PE || theHit->m_HitType == CIOutputEvent::HTYPE_LEPE) {
				nPE++;
			}
			//	G4cout << "Event " << iEvt<< " with " << nScintiHits << " hits was "<< (theHit->m_PartType) << endl;


			//	G4cout << "Event " << iEvt<< " with " << nScintiHits << " hits was "<< CIOutputScintiHit::GetNameFromPType(theHit->m_PartType) << " has " << CIOutputScintiHit::GetNameFromHType(theHit->m_HitType)<<G4endl;
		}
		if (nCompton==1) nWOneCompton++;
		if (nCompton>0) nWComptons++;
		if (nPE>0) nWPE++;
		if (nCompton>0 || nPE>0) nPECompt++;
	}
	G4cout<<"-----------------------------------------------------------"<<G4endl;
	G4cout<<"Number of events PE and/or Compt......... " << nPECompt<<G4endl;
	G4cout<<"Number of events with Comptons........... " << nWComptons<<G4endl;
	G4cout<<"Number of events with one Compton........ " << nWOneCompton<<G4endl;
	G4cout<<"Number of events with PE.......... ......." << nWPE<<G4endl;

}

//-----------------------------------------------------------------------------
void CIEventAction::PlotOptiHits(const G4Event* pEvt) {
	const G4double NMtoEV = 1240.0;
	const CIModuleTable* pModuleTable = m_pCISensitiveScintiDetector->GetCIModuleTable();
	CIOpticalPhotonHitsCollection* theOptiCollection = m_pCISensitiveOpticalDetector->GetHitsCollection();
	G4int nScat=0;
	G4int nAbs=0;
	for (int iOptiHit = 0; iOptiHit < theOptiCollection->entries(); iOptiHit++) {
		CIOpticalPhotonHit *theHit = (*theOptiCollection)[iOptiHit];
		const G4double Enm = NMtoEV/(theHit->TheEnergy()/eV);
		if (pModuleTable->GetSubDetector(theHit->TheModuleID()) == CIModuleTable::SUBDET_SCATTER) {
			m_pCIRunAction->m_HOpHitScatE->Fill(Enm);
			m_pCIRunAction->m_HOpHitScatT->Fill(theHit->TheTime()*ns);
			nScat++;
		} else if (pModuleTable->GetSubDetector(theHit->TheModuleID()) == CIModuleTable::SUBDET_ABSORBER) {
			m_pCIRunAction->m_HOpHitAbsE->Fill(Enm);
			m_pCIRunAction->m_HOpHitAbsT->Fill(theHit->TheTime()*ns);
			nAbs++;
		}
	}
	if (nScat>0) m_pCIRunAction->m_HOpHitScatMult->Fill(nScat);
	if (nAbs>0) m_pCIRunAction->m_HOpHitAbsMult->Fill(nAbs);
	// Get the optical path lengths
	G4TrajectoryContainer* trajectoryContainer = pEvt->GetTrajectoryContainer();
	G4int nTrajectories = 0;
	nScat=0;
	nAbs=0;
	if (trajectoryContainer) nTrajectories = trajectoryContainer->entries();
	for (G4int iTraj=0; iTraj < nTrajectories; iTraj++) {
		G4Trajectory* trj=(G4Trajectory*)((*(pEvt->GetTrajectoryContainer()))[iTraj]);
		if (trj->GetParticleDefinition() != G4OpticalPhoton::OpticalPhotonDefinition()) continue;
		G4ThreeVector firstPos = trj->GetPoint(0)-> GetPosition();
		CIModuleTable::SUBDET subdet;
		if (pModuleTable->IsPointInScatDet(firstPos)) {
			subdet = CIModuleTable::SUBDET_SCATTER;
			nScat++;
		} else if (pModuleTable->IsPointInAbsDet(firstPos)) {
			subdet = CIModuleTable::SUBDET_ABSORBER;
			nAbs++;
		}
		if (nScat>0) m_pCIRunAction->m_HOpScatMult->Fill(nScat);
		if (nAbs>0) m_pCIRunAction->m_HOpAbsMult->Fill(nAbs);
	}

}

//-----------------------------------------------------------------------------
int CIEventAction::CheckNCellsHit() {
	CIScintiHitsCollection* theCollection = m_pCISensitiveScintiDetector->GetHitsCollection();
	const CIModuleTable* pModuleTable = m_pCISensitiveScintiDetector->GetCIModuleTable();
	const int nCells = pModuleTable->GetMaxModules();
	vector<bool> cellHit(nCells);
	cellHit.assign(cellHit.size(), false);

	for (int iScintiHit = 0; iScintiHit < theCollection->entries(); iScintiHit++) {
		CIScintiHit *theHit = (*theCollection)[iScintiHit];
		const int iCell = theHit->TheModuleID();
		//	G4cout << "nCells are " << nCells << " icell is " << iCell << G4endl;

	assert(iCell<nCells);
		cellHit[iCell] = true;
	}
	int nCellsHit = 0;
	for (int iCell =0; iCell<nCells;iCell++) 
	  {
	    if (cellHit[iCell]) 
	      {
		nCellsHit++;
		//	cout << " iCell hit is " << iCell << endl;
	      }
	  }
	return nCellsHit;


}


//-----------------------------------------------------------------------------
void CIEventAction::SaveMaterialHits() {
	CIMaterialHitsCollection* theHitCollection = m_pCISensitiveMaterials->GetHitsCollection();

	TClonesArray & outMaterialHitArrary = *m_pCIOutputEvent->m_MaterialHitList;
	for (int iHit = 0; iHit < theHitCollection->entries(); iHit++) {
		CIMaterialHit *theHit = (*theHitCollection)[iHit];
		const CIOutputEvent::HITTYPE Htype = m_pCIOutputEvent->GetHTypeFromName(theHit->TheInteractionProcessName());
		const CIOutputEvent::PARTTYPE Ptype = m_pCIOutputEvent->GetPTypeFromName(theHit->ThePartName());


//		G4cout << "Saved Material hit " << iHit << " from particle type " << theHit->ThePartName() << " With Energy Dep " <<
//		theHit->TheEnergyDep()<< " In " <<theHit->TheMedium()<<G4endl;

		new (outMaterialHitArrary[iHit]) CIOutputMaterialHit(theHit->GetPos().x(), theHit->GetPos().y(),
				theHit->GetPos().z(), theHit->TheTime(), theHit->TheEnergy(), theHit->TheEnergyDep(),
				theHit->TheTrackID(), theHit->TheParentTrackID(), Htype, Ptype, theHit->TheMedium());


	}

}
