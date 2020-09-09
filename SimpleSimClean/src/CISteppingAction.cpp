/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.              *
 *   hseywerd@nrcan.gc.ca                                                  *
 *                                                                         *
 ***************************************************************************/
/**
 * @file CISteppingAction.cpp
 * @brief Manage actions to be taken after each step in the tracking
 *
 **/
#include "CISteppingAction.h"
#include "G4Track.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"
#include "G4SDManager.hh"
#include "CISensitiveOpticalDetector.h"

CISteppingAction::CISteppingAction(
		CISensitiveOpticalDetector* pCISensitiveOpticalDetector) :
	m_pCISensitiveOpticalDetector(pCISensitiveOpticalDetector),
			m_pOpBoundaryProcess(NULL) {

	assert (m_pCISensitiveOpticalDetector != NULL);

}
//-----------------------------------------------------------------------------


CISteppingAction::~CISteppingAction() {
}
//-----------------------------------------------------------------------------

void CISteppingAction::UserSteppingAction(const G4Step* theStep) {
		

	// Get the track information
	G4Track* theTrack = theStep->GetTrack();

	// We want to look at optical photons only
	if (theTrack->GetDefinition() != G4OpticalPhoton::OpticalPhotonDefinition())
		return;
	if ( theTrack->GetCurrentStepNumber() == 1)
	  //G4cout << " A new photon is produced " << G4endl;
	// Try until we find an G4OpBoundaryProcess process which we can continue to use.
	// If in the future we define different optical boundary processes, requiring different handling,
	// we can differentiate them via the process name.
	if (m_pOpBoundaryProcess == NULL) {
		G4ProcessManager* theProcessManager =
				theTrack->GetDefinition()->GetProcessManager();
		G4ProcessVector* theProcessList = theProcessManager->GetProcessList();
		for (int iProcess = 0; iProcess
				< theProcessManager->GetProcessListLength(); iProcess++) {
			m_pOpBoundaryProcess
					= dynamic_cast<G4OpBoundaryProcess*> ((*theProcessList)[iProcess]);
			if (m_pOpBoundaryProcess)
				break;
		}
	}

	// Determine if we have a detection of the optical photon on the boundary, if so we can process it.
	if (m_pOpBoundaryProcess) {
		// Now check that we really are on the geometrical boundary
		// Otherwise we can get some wierd points that seem to be in the middle of the scintillator
		// This may be some kind of bug in Geant, I will inquire.
		

		if (theStep->GetPostStepPoint()->GetStepStatus() == fGeomBoundary) {
		

			G4OpBoundaryProcessStatus boundaryStatus = Undefined;
			boundaryStatus = m_pOpBoundaryProcess->GetStatus();
			       

			const G4VPhysicalVolume* thePhysicalVolume =
					theStep->GetPostStepPoint()->GetPhysicalVolume();
			switch (boundaryStatus) {
			case Absorption:			 
				break;
			case Detection: {
			
			  const G4VPhysicalVolume* thePhysicalVolume =
			    theStep->GetPostStepPoint()->GetPhysicalVolume();
			  m_pCISensitiveOpticalDetector->ProcessHits(theStep, NULL);
			}
			  break;
			case StepTooSmall:
			  //G4cout<<"Step too small "<< theStep->GetPostStepPoint()->GetPhysicalVolume()->GetName() <<  " " <<  thePhysicalVolume->GetName() <<G4endl;
				break;
			case FresnelReflection:
			case TotalInternalReflection:
			case SpikeReflection:
			default:

				break;
			}
		}
	}
}
