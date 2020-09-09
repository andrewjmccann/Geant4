/***************************************************************************
*   Copyright (C) Minister of Natural Resources Canada 2008.               *
*   hseywerd@nrcan.gc.ca                                                   *
*                                                                          *
***************************************************************************/
/**
 * @file CIOpticalPhotonHit.h
 * @brief Represent optical  photon hits in photodetectors
 * @author Henry Seywerd hseywerd@nrcan.gc.ca
 **/
#ifndef CIOpticalPhotonHit_h
#define CIOpticalPhotonHit_h

#include "CIGenericHit.h"

/**
 * @class CIOpticalPhotonHit
 * @brief Represent optical  photon hits in photodetectors
 *
 * @author Henry Seywerd <hseywerd@nrcan.gc.ca>
*/
class CIOpticalPhotonHit : public CIGenericHit
{
  public:
    /**
     * Constructor
     */
    CIOpticalPhotonHit();

    /**
    * Copy constructor
     * @param hit object to copy
    */
    CIOpticalPhotonHit (const CIOpticalPhotonHit& hit);

    /**
     * Assignment
     * @param hits object to copy
    */
    const CIOpticalPhotonHit& operator= (const CIOpticalPhotonHit& hits);

    /**
     * Assignment
     * @param hit object to copy
     */
    G4int operator== (const CIOpticalPhotonHit& hit) const;

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
    * Override for drawing a hit
    */
    void Draw();

    /**
     * Override for printing a hit
    */
    void Print();

    /**
     * Deletion
     */
    ~CIOpticalPhotonHit();

    /**
     * @return Reference to the name of the process creating the particle
     */
    inline G4String& TheInteractionProcessName() {return m_strInteractionProcessName;};

  private:
    /// The process by which interaction is occuring
    G4String m_strInteractionProcessName;
};


/**
 * @class CIOpticalPhotonHitsCollection
 * @brief Collection of optical photon hits (CIOpticalPhotonHits)
 *
 * Use G4Allocator to allocate the object
 *
 * @author Henry Seywerd <hseywerd@nrcan.gc.ca>
*/

typedef G4THitsCollection<CIOpticalPhotonHit> CIOpticalPhotonHitsCollection;

extern G4Allocator<CIOpticalPhotonHit> CIOpticalPhotonHitsAllocator;


/**
 * Allocate a new CIOpticalPhotonHit, using the CIOpticalPhotonHitsAllocator
 * @param size its size (not used)
 * @return a pointer to the new CIOpticalPhotonHit
 */
inline void* CIOpticalPhotonHit::operator new (size_t size)
{
  void *aHit;
  aHit = (void *) CIOpticalPhotonHitsAllocator.MallocSingle();
  return aHit;
}


/**
 * Delete the CIOpticalPhotonHit, using the CIOpticalPhotonHitsAllocator
 * @param aHit pointer to the CIOpticalPhotonHit to be deleted
 */
inline void CIOpticalPhotonHit::operator delete (void *aHit)
{
  CIOpticalPhotonHitsAllocator.FreeSingle ( (CIOpticalPhotonHit*) aHit);
}


#endif
