/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.              *
 *   hseywerd@nrcan.gc.ca                                                  *
 *                                                                         *
 ***************************************************************************/

/**
 * @file CISensitiveMaterials.h
 * @brief Define the regions of the materials that have hits in them
 *
 * Allows us to trace energy deposits in materials prior to hits in the scintillators
 **/
#ifndef CISensitiveMaterials_h
#define CISensitiveMaterials_h

#include "G4VSensitiveDetector.hh"
#include "CIMaterialHit.h"

class G4HCofThisEvent;

/**
 * @class CISensitiveMaterials
 * @brief Define the regions of the materials wherein there can be deposits
 *
 * Allows us to trace energy deposits in materials prior to hits in the scintillators
 * @author Henry Seywerd <hseywerd@nrcan.gc.ca>
*/
class CISensitiveMaterials : public G4VSensitiveDetector
{
  public:
    /**
     * Constructs the sensitive detector
     * @param name the name of this sensitive detector
     */
    CISensitiveMaterials (G4String name);

    ~CISensitiveMaterials();

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
    CIMaterialHitsCollection* GetHitsCollection() const {return m_pMaterialHitsCollection;};


  private:
    /// Collection of hits in the scintillator detector
    CIMaterialHitsCollection* m_pMaterialHitsCollection;
    /// Name of the hits collection
    static const G4String m_strMaterialHitsCollectionName;

};

#endif
