/***************************************************************************
*   Copyright (C) Minister of Natural Resources Canada 2008.               *
*   hseywerd@nrcan.gc.ca                                                   *
*                                                                          *
***************************************************************************/
/**
 * @file CIGenericHit.h
 * @brief Represent hits in our detector, intended as a base class to specific hit types
 * @author Henry Seywerd hseywerd@nrcan.gc.ca
 **/
#ifndef CIGenericHit_h
#define CIGenericHit_h

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4ThreeVector.hh"

class CIGenericHit;
extern G4Allocator<CIGenericHit> CIGenericHitsAllocator;

/**
 * @class CIGenericHit
 * @brief Represent hits in our detector, intended as a base class to specific hit types
 *
 * @author Henry Seywerd <hseywerd@nrcan.gc.ca>
*/
class CIGenericHit : public G4VHit
{
  public:

   /**
     * Constructor
     */
    CIGenericHit();

    /**
    * Copy constructor
     * @param hit object to copy
    */
    CIGenericHit (const CIGenericHit& hit);

    /**
     * Assignment
     * @param hits object to copy
    */
    const CIGenericHit& operator= (const CIGenericHit& hits);

    /**
     * Assignment
     * @param hit object to copy
     */
    G4int operator== (const CIGenericHit& hit) const;

    /**
     * allocater method to override memory allocation with Geant's own
     * @param size size to allocate
     */
    inline void* operator new (size_t size);

    /**
     * deletetion method to override memory deletion with Geant's own
     */
    inline void  operator delete (void*);

    /**
     * Deletion
     */
    ~CIGenericHit();

    /**
     * Energy
     * @return reference to the energy associated with the track
     */
    inline G4double& TheEnergy() { return m_dEnergy;};


    /**
     * Hit time
     * @return reference to the time of occurrence of the hit.
     */
    inline G4double& TheTime() { return m_dTime;};


    /**
     * Module identifier
     * @return reference to the module identifier.
     */
    inline G4int& TheModuleID() { return m_iModuleID;};

    /**
     * Set the position of this hit
     * @param thePosition the position
     */
    inline void SetPos (const G4ThreeVector thePosition) { m_Pos = thePosition; };

    /**
     * Get the position of this hit
     * @return the position
     */
    inline G4ThreeVector GetPos() const { return m_Pos; };

    /**
     * @return Reference to the Physical Volume name where the hit occured
     */
    inline G4String& ThePVolName() {return m_strPVolName;}

    /**
     * Track identifier
     * @return reference to the parent track identifier.
     */
    inline G4int& TheTrackID() { return m_iTrackID;};

    /**
     * Parent Track identifier
     * @return reference to the parent track identifier.
     */
    inline G4int& TheParentTrackID() { return m_iParentTrackID;};

    /**
     * Particle name
     * @return reference to the particle name
     */
    inline G4String& ThePartName() { return m_strPartName;};

  protected:
    /// Energy of the track prior to the hit
    G4double      m_dEnergy;
    /// Time of the hit
    G4double      m_dTime;
    /// Position of this hit
    G4ThreeVector m_Pos;
    /// Physical Volume name of the hit element
    G4String m_strPVolName;
    /// The identifier for the detector module in which the hit occurred
    G4int m_iModuleID;
    /// The ID of the track
    G4int m_iTrackID;
    /// The ID of the parent track
    G4int m_iParentTrackID;
    /// The name of the particle
    G4String m_strPartName;

};


/**
 * Allocate a new CIGenericHit, using the CIGenericHitsAllocator
 * @param size its size (not used)
 * @return a pointer to the new CIGenericHit
 */
inline void* CIGenericHit::operator new (size_t size)
{
  void *aHit;
  aHit = (void *) CIGenericHitsAllocator.MallocSingle();
  return aHit;
}


/**
 * Delete the CIGenericHit, using the CIGenericHitsAllocator
 * @param aHit pointer to the CIGenericHit to be deleted
 */
inline void CIGenericHit::operator delete (void *aHit)
{
  CIGenericHitsAllocator.FreeSingle ( (CIGenericHit*) aHit);
}

#endif
