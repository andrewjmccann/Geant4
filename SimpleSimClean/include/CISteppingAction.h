/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.              *
 *   hseywerd@nrcan.gc.ca                                                  *
 *                                                                         *
 ***************************************************************************/

/**
 * @file CISteppingAction.h
 * @brief Manage actions to be taken after each step in the tracking
 **/
#ifndef CISteppingAction_h
#define CISteppingAction_h

#include "G4UserSteppingAction.hh"
#include "G4String.hh"

class G4OpBoundaryProcess;

class CISensitiveOpticalDetector;

/**
 * @class CISteppingAction
 *
 * @brief Manage actions to be taken after each step in the tracking.
 *
 * Implement handling of optical photons as the cross into the logical skin surface of an optically sensitive detector.
 * So as to allow recording of optical photons into a photodetector
 *
 * @author Henry Seywerd <hseywerd@nrcan.gc.ca>
*/
class CISteppingAction : public G4UserSteppingAction
{
  public:
    CISteppingAction (CISensitiveOpticalDetector* pCISensitiveOpticalDetector);

    ~CISteppingAction();

    /**
     * Invoked to manage activities at the end of each step
     * @param theStep pointer to the step
     */
    virtual void UserSteppingAction (const G4Step* theStep);


  private:

    /// The sensitive detector for optical photons
    CISensitiveOpticalDetector* m_pCISensitiveOpticalDetector;

    /// Pointer to the optical boundary process.
    G4OpBoundaryProcess* m_pOpBoundaryProcess;


};

#endif
