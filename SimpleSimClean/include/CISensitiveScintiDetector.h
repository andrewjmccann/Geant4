/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.              *
 *   hseywerd@nrcan.gc.ca                                                  *
 *                                                                         *
 ***************************************************************************/

/**
 * @file CISensitiveScintiDetector.h
 * @brief Define the regions of the scintillator detectors which can generate hits and manage their generation
 **/
#ifndef CISensitiveScintiDetector_h
#define CISensitiveScintiDetector_h

#include "G4VSensitiveDetector.hh"
#include "CIScintiHit.h"

class G4HCofThisEvent;
class CIModuleTable;

/**
 * @class CISensitiveScintiDetector
 * @brief Define the regions of the scintillator detectors which can generate hits
 *
 * This sensitive detector is for sensitivity to particles generating a hit in the scintillator and for
 * managing the energy deposits in the scintillators.
 * It does not handle optical photons.
 * @author Henry Seywerd <hseywerd@nrcan.gc.ca>
*/
class CISensitiveScintiDetector : public G4VSensitiveDetector
{
  public:
    /**
     * Constructs the sensitive detector
     * @param name the name of this sensitive detector
     */
    CISensitiveScintiDetector (G4String name);

    ~CISensitiveScintiDetector();

    /**
     * Generate and store for future reference hits in the detector
     * @param aStep the G4step object from which hits can be generated
     * @param ROhist history of the track
     * @return true if processed OK
     */
    G4bool ProcessHits (G4Step* aStep, G4TouchableHistory* ROhist);

    /**
     * Invoked at the beginning of each event, prepare the hits collection
     * @param HCE Hit collection of this event
     */
    void Initialize (G4HCofThisEvent* HCE);

    /**
     * Invoked at the end of each event, save the hits collection
     * @param HCE Hit collection of this event
     */
    void EndOfEvent (G4HCofThisEvent* HCE);

    /**
     * Get the scintillator hits collection
     * @return pointer to the hits collection
     */
    CIScintiHitsCollection* GetHitsCollection() const {return m_pScintiHitsCollection;};

    /**
     * Sets the module name/id number correspondence table pointer
     * @param pTable pointer to the table
     */
    inline void SetCIModuleTable(CIModuleTable* pTable) {m_pCIModuleTable = pTable;};

    /**
     * Gets a pointer to the module name/id number correspondence table
     * @return pointer to the table
     */
    inline CIModuleTable* GetCIModuleTable() const {return m_pCIModuleTable;};


  private:
    /// Collection of hits in the scintillator detector
    CIScintiHitsCollection* m_pScintiHitsCollection;
    /// Name of the hits collection
    static const G4String m_strScintiHitsCollectionName;
    /// The module name/ID mapping table.
    CIModuleTable* m_pCIModuleTable;
};

#endif
