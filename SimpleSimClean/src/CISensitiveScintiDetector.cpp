/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.              *
 *   hseywerd@nrcan.gc.ca                                                  *
 *                                                                         *
 ***************************************************************************/
/**
 * @file CISensitiveScintiDetector.cpp
 * @brief Define the regions of the scintillator detectors which can generate hits - implementation
 **/
#include "CISensitiveScintiDetector.h"
#include "CIScintiHit.h"
#include "CIModuleTable.h"
#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"
#include "G4VProcess.hh"
#include "G4VTouchable.hh"

const G4String CISensitiveScintiDetector::m_strScintiHitsCollectionName = "CIScintiHitCollection";

CISensitiveScintiDetector::CISensitiveScintiDetector(G4String name) :
	G4VSensitiveDetector(name), m_pScintiHitsCollection(NULL), m_pCIModuleTable(NULL) {
	G4String HCname;
	collectionName.insert(HCname = m_strScintiHitsCollectionName);
}
//-----------------------------------------------------------------------------


CISensitiveScintiDetector::~CISensitiveScintiDetector() {

}
//-----------------------------------------------------------------------------


void CISensitiveScintiDetector::Initialize(G4HCofThisEvent* HCE) {

	m_pScintiHitsCollection = new CIScintiHitsCollection(SensitiveDetectorName, collectionName[0]);

}
//-----------------------------------------------------------------------------


G4bool CISensitiveScintiDetector::ProcessHits(G4Step* theStep, G4TouchableHistory* ROhist) {

  	// Ignore hits with no energy deposit
	G4double edep = theStep->GetTotalEnergyDeposit();
//	if (edep == 0.)
//		return false;


	const G4Track* theTrack = theStep->GetTrack();

	// Determine which incoming particle caused the energy deposit
	const G4String particleName = theTrack->GetDefinition()->GetParticleName();
	if (particleName == "opticalphoton") return true;
	//G4cout << (theStep->GetPreStepPoint()->GetPosition()) << G4endl;

	const G4VPhysicalVolume* thePhysicalVolume = theStep->GetPreStepPoint()->GetPhysicalVolume();
	// Determine which physics process generated this energy deposit
	const G4String interactionProcessName = theStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();

	
	///////////This section has been completely rewritten by A. MacLeod /////////// The original relies onthe post-step position which may not always be the crystal. CIModuleTable does not seem to be working properly. So for now - just do something quick and easy with touchables.
	//old version
	/*
	const G4VPhysicalVolume* theModulePhys1 = m_pCIModuleTable->GetModulePhysForScintiHit(theStep->GetPostStepPoint()->GetPosition());
		if (theModulePhys1 == NULL) {

		G4cout << "CISensitiveScintiDetector::ProcessHits == Could not get the module physical volume, probably something wrong in the module heirarchy" <<G4endl;
		G4cout << " track volume is " << theTrack->GetVolume()->GetName() << G4endl;
		G4cout << "post x " << theStep->GetPostStepPoint()->GetPosition().x() << G4endl;
		G4cout << "post y " << theStep->GetPostStepPoint()->GetPosition().y() << G4endl;
		G4cout << "post z " << theStep->GetPostStepPoint()->GetPosition().z() << G4endl;
		const G4VTouchable *theTouchable2 = theStep->GetPostStepPoint()->GetTouchable();
		G4cout << "touchable volume2 is "<< theTouchable2->GetVolume(0)->GetName()  << G4endl;
		G4cout << "copy number is "<< theTouchable2->GetCopyNumber() << G4endl;
		G4cout << "mother  number is "<< theTouchable2->GetCopyNumber(1) << G4endl;
		G4cout << "grandmother number is "<< theTouchable2->GetCopyNumber(2) << G4endl;

		const G4VTouchable *theTouchable = theStep->GetPreStepPoint()->GetTouchable();
		G4cout << "touchable volume is "<< theTouchable->GetVolume(0)->GetName()  << G4endl;
		theModulePhys1 = theTouchable->GetVolume(0);
		G4cout << "pre x" << theStep->GetPreStepPoint()->GetPosition().x() << G4endl;
		G4cout << "pre y" << theStep->GetPreStepPoint()->GetPosition().y() << G4endl;
		G4cout << "pre z " << theStep->GetPreStepPoint()->GetPosition().z() << G4endl;
		G4cout << "copy number is "<< theTouchable->GetCopyNumber() << G4endl;
		G4cout << "mother  number is "<< theTouchable->GetCopyNumber(1) << G4endl;
		G4cout << "grandmother number is "<< theTouchable->GetCopyNumber(2) << G4endl;

		//	return true;
	}
		G4cout << " track volume is " << theTrack->GetVolume()->GetName() << G4endl;
		G4cout << "post x " << theStep->GetPostStepPoint()->GetPosition().x() << G4endl;
		G4cout << "post y " << theStep->GetPostStepPoint()->GetPosition().y() << G4endl;
		G4cout << "post z " << theStep->GetPostStepPoint()->GetPosition().z() << G4endl;


		const G4VTouchable *theTouchable2 = theStep->GetPreStepPoint()->GetTouchable();
		G4cout << "touchable volume is "<< theTouchable2->GetVolume(0)->GetName()  << G4endl;
		G4cout << "pre x" << theStep->GetPreStepPoint()->GetPosition().x() << G4endl;
		G4cout << "pre y" << theStep->GetPreStepPoint()->GetPosition().y() << G4endl;
		G4cout << "pre z " << theStep->GetPreStepPoint()->GetPosition().z() << G4endl;
		G4cout << "copy number is "<< theTouchable2->GetVolume(0)->GetCopyNo() << G4endl;
*/

		  //new version
	//		const G4VPhysicalVolume* theModulePhys
		
	const G4VTouchable *theTouchable = theStep->GetPreStepPoint()->GetTouchable();
	const G4VPhysicalVolume* theModulePhys = theTouchable->GetVolume(0);
		if (theModulePhys == NULL) {
		G4cout << "CISensitiveScintiDetector::ProcessHits == Could not get the module physical volume, probably something wrong in the module heirarchy" <<G4endl;

		return true;

		}

	G4String name = theModulePhys->GetName();
	//	G4cout << "sensitivescintidetector: name: " << name << G4endl;

	assert(m_pCIModuleTable!=NULL);
	const G4int ID =  m_pCIModuleTable->GetModuleID(name);
	// OK Create a hit
	CIScintiHit* theHit = new CIScintiHit();
	theHit->TheEnergy() = theTrack->GetTotalEnergy();
	theHit->TheEnergyDep() = edep;
	theHit->SetPos(theStep->GetPostStepPoint()->GetPosition());
	//	G4cout << "Position is" << theStep->GetPostStepPoint()->GetPosition() << G4endl;
	theHit->ThePVolName() = name;
	theHit->ThePartName() = particleName;
	theHit->TheTrackID() = theTrack->GetTrackID();
	theHit->TheParentTrackID() = theTrack->GetParentID();
	theHit->TheInteractionProcessName() = interactionProcessName;
	//	G4cout << " process is " << interactionProcessName << G4endl;

	theHit->ThePartName() = theTrack->GetDefinition()->GetParticleName();
	theHit->TheModuleID() = ID;
	//	G4cout << "the module ID is "<< ID << G4endl;
	theHit->TheTime() = theTrack->GetGlobalTime();
//	G4cout << "Track: " << theTrack->GetTrackID() << " Z "<< theStep->GetPostStepPoint()->GetPosition().z()<< "T "<<
//			theTrack->GetLocalTime()<< G4endl;

	//	G4cout << "Track: " << theTrack->GetTrackID() << G4endl << "  from " << theTrack->GetParentID() << " is a "
	//		<< theTrack->GetDefinition()->GetParticleName() << " and interacted via " << interactionProcessName
	//		<< " and has energy " << theTrack->GetTotalEnergy() / keV << "  and deposited " << edep / keV << "in "<< theModulePhys->GetName() << G4endl;
	m_pScintiHitsCollection->insert(theHit);

	theHit->Print();


	if (verboseLevel > 2)
		theHit->Print();
	theHit->Draw();

	return true;
}
//-----------------------------------------------------------------------------


void CISensitiveScintiDetector::EndOfEvent(G4HCofThisEvent* HCE) {
	G4int HCID = GetCollectionID(0);
	HCE->AddHitsCollection(HCID, m_pScintiHitsCollection);

}
