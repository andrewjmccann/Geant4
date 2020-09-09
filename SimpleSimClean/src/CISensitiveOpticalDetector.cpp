/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.              *
 *   hseywerd@nrcan.gc.ca                                                  *
 *                                                                         *
 ***************************************************************************/
/**
 * @file CISensitiveOpticalDetector.cpp
 * @brief Define the regions of the scintillator detectors which can generate hits - implementation
 **/
#include "CISensitiveOpticalDetector.h"
#include "CIOpticalPhotonHit.h"
#include "CIModuleTable.h"
#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"
#include "G4VProcess.hh"
#include "G4OpticalPhoton.hh"

const G4String CISensitiveOpticalDetector::m_strOpticalPhotonHitsCollectionName = "OpticalPhotonHitCollection";

CISensitiveOpticalDetector::CISensitiveOpticalDetector(G4String name) :
	G4VSensitiveDetector(name), m_pOpticalPhotonHitsCollection(NULL) {
	G4String HCname;
	collectionName.insert(HCname = m_strOpticalPhotonHitsCollectionName);
}

//-----------------------------------------------------------------------------
CISensitiveOpticalDetector::~CISensitiveOpticalDetector() {

}

//-----------------------------------------------------------------------------
void CISensitiveOpticalDetector::Initialize(G4HCofThisEvent* HCE) {

	m_pOpticalPhotonHitsCollection = new CIOpticalPhotonHitsCollection(SensitiveDetectorName, collectionName[0]);

}

//-----------------------------------------------------------------------------
G4bool CISensitiveOpticalDetector::ProcessHits(G4Step* theStep, G4TouchableHistory* ROhist) {
	// I want to know if the non const version of this function is ever in fact called - it doesn't seem to be...
	// Only happens if called directly from the Geant4 framework, rather than out of CISteppingAction
	// i.e. if we are detecting optical photons at something other than a boundary.
	// This is not the current intent, but may change. Leave the Exception throw here just so we remember what we did and why.
	//G4Exception("CISensitiveOpticalDetector::ProcessHits == non-const version called. Should never happen");
	const G4Step* theConstStep = theStep;
	return ProcessHits(theConstStep, ROhist);

}

//-----------------------------------------------------------------------------
G4bool CISensitiveOpticalDetector::ProcessHits(const G4Step* theStep, const G4TouchableHistory* ROhist) {

  	assert(m_pCIModuleTable!=NULL);
	// Get the track
	const G4Track* theTrack = theStep->GetTrack();
	// We should never be fed anything but optical photons
	if (theTrack->GetDefinition() != G4OpticalPhoton::OpticalPhotonDefinition()) {
	  //G4Exception(
	  //		"CISensitiveOpticalDetector::ProcessHits == Somehow we were given something other than an optical photon, was "
	  //				+ theTrack->GetDefinition()->GetParticleName());
	}

	CIOpticalPhotonHit* theHit = new CIOpticalPhotonHit();

	const G4VPhysicalVolume* thePostPhysicalVolume = theStep->GetPostStepPoint()->GetPhysicalVolume();

	theHit->TheEnergy() = theTrack->GetTotalEnergy();
	theHit->TheTime() = theTrack->GetGlobalTime();
	theHit->SetPos(theStep->GetPostStepPoint()->GetPosition());

	//Print the position

	G4cout <<  theStep->GetPostStepPoint()->GetPosition() << G4endl;
	// This should be the name of the detector receiving the photon.
	theHit->ThePVolName() = thePostPhysicalVolume->GetName();
	theHit->TheInteractionProcessName() = theStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
	theHit->TheTrackID() = theTrack->GetTrackID();
	theHit->TheParentTrackID() = theTrack->GetParentID();
	theHit->ThePartName() = G4OpticalPhoton::OpticalPhotonDefinition()->GetParticleName();
	theHit->TheTime() = theTrack->GetGlobalTime();
	const G4VPhysicalVolume* theModulePhys = m_pCIModuleTable->GetModulePhysForOpticalHit(theStep->GetPostStepPoint()->GetPosition());
	if (theModulePhys == NULL) {
	  //	G4Exception(
	  //		"CISensitiveOpticalDetector::ProcessHits == Could not get the module physical volume, probably something wrong in the module heirarchy");
	}
	const G4String name = theModulePhys->GetName();
	theHit->ThePVolName() = name;
	theHit->TheModuleID() = m_pCIModuleTable->GetModuleID(name);

	// OK we have all the info, store it to the hit collection
	m_pOpticalPhotonHitsCollection->insert(theHit);

	if (verboseLevel > 2)
		theHit->Print();
	theHit->Draw();

	return true;
}

//-----------------------------------------------------------------------------
void CISensitiveOpticalDetector::EndOfEvent(G4HCofThisEvent* HCE) {
	G4int HCID = GetCollectionID(0);
	HCE->AddHitsCollection(HCID, m_pOpticalPhotonHitsCollection);
}

