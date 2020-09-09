/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.              *
 *   hseywerd@nrcan.gc.ca                                                  *
 *                                                                         *
 ***************************************************************************/
/**
 * @file CISensitiveMaterials.cpp
 * @brief Define the regions of the scintillator detectors which can generate hits - implementation
 **/
#include "CISensitiveMaterials.h"
#include "CIMaterialHit.h"
#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"
#include "G4VProcess.hh"
#include "G4VTouchable.hh"

const G4String CISensitiveMaterials::m_strMaterialHitsCollectionName = "CIMaterialHitCollection";

CISensitiveMaterials::CISensitiveMaterials(G4String name) :
	G4VSensitiveDetector(name), m_pMaterialHitsCollection(NULL) {
	G4String HCname;
	collectionName.insert(HCname = m_strMaterialHitsCollectionName);
}
//-----------------------------------------------------------------------------


CISensitiveMaterials::~CISensitiveMaterials() {

}
//-----------------------------------------------------------------------------


void CISensitiveMaterials::Initialize(G4HCofThisEvent* HCE) {

	m_pMaterialHitsCollection = new CIMaterialHitsCollection(SensitiveDetectorName, collectionName[0]);

}
//-----------------------------------------------------------------------------


G4bool CISensitiveMaterials::ProcessHits(G4Step* theStep, G4TouchableHistory* ROhist) {
	// Ignore hits with no energy deposit
	G4double edep = theStep->GetTotalEnergyDeposit();
//	if (edep == 0.)
//		return false;

	const G4Track* theTrack = theStep->GetTrack();

	// Determine which incoming particle caused the energy deposit
	const G4String particleName = theTrack->GetDefinition()->GetParticleName();
	if (particleName == "opticalphoton") return true;

	const G4VPhysicalVolume* thePhysicalVolume = theStep->GetPreStepPoint()->GetPhysicalVolume();
	// Determine which physics process generated this energy deposit
	const G4String interactionProcessName = theStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();


	// OK Create a hit
	CIMaterialHit* theHit = new CIMaterialHit();
	theHit->TheEnergy() = theTrack->GetTotalEnergy();
	theHit->TheEnergyDep() = edep;
	theHit->SetPos(theStep->GetPostStepPoint()->GetPosition());
	//theHit->TheMedium() = name;
	theHit->ThePartName() = particleName;
	theHit->TheTrackID() = theTrack->GetTrackID();
	theHit->TheParentTrackID() = theTrack->GetParentID();
	theHit->TheInteractionProcessName() = interactionProcessName;
	theHit->ThePartName() = theTrack->GetDefinition()->GetParticleName();
	theHit->TheTime() = theTrack->GetGlobalTime();
	theHit->TheMedium() = thePhysicalVolume->GetName();
//	G4cout << "Track: " << theTrack->GetTrackID() << " Z "<< theStep->GetPostStepPoint()->GetPosition().z()<< "T "<<
//			theTrack->GetLocalTime()<< G4endl;

	//	G4cout << "Track: " << theTrack->GetTrackID() << G4endl << "  from " << theTrack->GetParentID() << " is a "
	//			<< theTrack->GetDefinition()->GetParticleName() << " and interacted via " << interactionProcessName
	//			<< " and has energy " << theTrack->GetTotalEnergy() / keV << "  and deposited " << edep / keV << "in "<< theModulePhys->GetName() << G4endl;
	m_pMaterialHitsCollection->insert(theHit);

	if (verboseLevel > 2)
		theHit->Print();
	theHit->Draw();

	return true;
}
//-----------------------------------------------------------------------------


void CISensitiveMaterials::EndOfEvent(G4HCofThisEvent* HCE) {
	G4int HCID = GetCollectionID(0);
	HCE->AddHitsCollection(HCID, m_pMaterialHitsCollection);

}
