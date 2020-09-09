/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.              *
 *   hseywerd@nrcan.gc.ca                                                  *
 *                                                                         *
 ***************************************************************************/

/**
 * @file CISensitiveOpticalDetector.h
 * @brief Define the regions of the optical (PMT/SiPM) detectors which can generate hits and manage their generation
 **/
#ifndef CISensitiveOpticalDetector_h
#define CISensitiveOpticalDetector_h

#include "G4HCofThisEvent.hh"
#include "G4VSensitiveDetector.hh"
#include "CIOpticalPhotonHit.h"
class CIModuleTable;

/**
 * @class CISensitiveOpticalDetector
 * @brief Define the regions of the optical detectors which can generate hits
 *
 * This sensitive detector is for sensitivity to particles generating a hit in a photodetector.
 * @author Henry Seywerd <hseywerd@nrcan.gc.ca>
*/
class CISensitiveOpticalDetector : public G4VSensitiveDetector
{
  public:
    /**
     * Constructs the sensitive detector
     * @param name the name of this sensitive detector
     */
    CISensitiveOpticalDetector (G4String name);

    ~CISensitiveOpticalDetector();

    /**
     * Generate and store for future reference hits in the detector
     * Calls the const version of this function -- will this cause problems??
     * @param aStep the G4step object from which hits can be generated
     * @param ROhist history of the track
     * @return
     */
    G4bool ProcessHits (G4Step* aStep, G4TouchableHistory* ROhist);
    /**
     * Generate and store for future reference hits in the detector
     * Note that this version deals with a const G4Step*
     * @param aStep the G4step object from which hits can be generated -- const
     * @param ROhist history of the track
     * @return true if processed OK
     */
    G4bool ProcessHits (const G4Step* aStep, const G4TouchableHistory* ROhist);

    /**
     * Invoked at the beginning of each event
     * @param HCE Hit collection of this event
     */
    void Initialize (G4HCofThisEvent* HCE);

    /**
     * Invoked at the end of each event
     * @param HCE Hit collection of this event
     */
    void EndOfEvent (G4HCofThisEvent* HCE);

    /**
     * Get the scintillator hits collection
     * @return pointer to the hits collection
     */
    CIOpticalPhotonHitsCollection* GetHitsCollection() const {return m_pOpticalPhotonHitsCollection;};

    /**
     * Sets the module name/id number correspondence table pointer
     * @param pTable pointer to the table
     */
    void SetCIModuleTable(CIModuleTable* pTable) {m_pCIModuleTable = pTable;};

    /**
     * Gets a pointer to the module name/id number correspondence table
     * @return pointer to the table
     */
    CIModuleTable* GetCIModuleTable() const {return m_pCIModuleTable;};


  private:
    /// Collection of hits in the scintillator detector
    CIOpticalPhotonHitsCollection* m_pOpticalPhotonHitsCollection;
    /// Name of the hits collection
    static const G4String m_strOpticalPhotonHitsCollectionName;
    /// The module name/ID mapping table.
    CIModuleTable* m_pCIModuleTable;
};

#endif
