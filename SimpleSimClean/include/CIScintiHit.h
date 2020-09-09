/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.               *
 *   hseywerd@nrcan.gc.ca                                                   *
 *                                                                          *
 ***************************************************************************/
/**
 * @file CIScintiHit.h
 * @brief Represent hits in scintillators.
 * @author Henry Seywerd hseywerd@nrcan.gc.ca
 **/
#ifndef CIScintiHit_h
#define CIScintiHit_h

#include "CIGenericHit.h"

/**
 * @class CIScintiHit
 * @brief Represent hits in scintillators.
 *
 * @author Henry Seywerd <hseywerd@nrcan.gc.ca>
 */
class CIScintiHit: public CIGenericHit {
public:
	/**
	 * Constructor
	 */
	CIScintiHit();

	/**
	 * Copy constructor
	 * @param hit object to copy
	 */
	CIScintiHit(const CIScintiHit& hit);

	/**
	 * Assignment
	 * @param hits object to copy
	 */
	const CIScintiHit& operator=(const CIScintiHit& hits);

	/**
	 * Assignment
	 * @param hit object to copy
	 */
	G4int operator==(const CIScintiHit& hit) const;

	/**
	 * allocater method to override memory allocation with Geant's own
	 * @param size the size to allocate
	 */
	inline void* operator new(size_t size);

	/**
	 * deletetion method to override memory deletion with Geant's own
	 */
	inline void operator delete(void*);

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
	~CIScintiHit();

	/**
	 * @return Reference to the name of the incoming particle
	 */
	inline G4String& ThePartName() {
		return m_strPartName;
	}
	;

	/**
	 * @return Reference to the name of the process involved in the hit interaction
	 */
	inline G4String& TheInteractionProcessName() {return m_strInteractionProcessName;	}

  /**
   * Energy
   * @return reference to the energy deposited by this track
   */
  inline G4double& TheEnergyDep() { return m_dEnergyDep;}

private:
	/// The name of the particle initiating the hit
	G4String m_strPartName;
	/// The process whereby ther particle is interactng
	G4String m_strInteractionProcessName;

  G4double      m_dEnergyDep;
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------


/**
 * @class CIScintiHitsCollection
 * @brief Collection of scintillator hits (CIScintiHits)
 *
 * Use G4Allocator to allocate the object
 *
 * @author Henry Seywerd <hseywerd@nrcan.gc.ca>
 */

typedef G4THitsCollection<CIScintiHit> CIScintiHitsCollection;

extern G4Allocator<CIScintiHit> CIScintiHitsAllocator;

/**
 * Allocate a new CIScintiHit, using the CIScintiHitsAllocator
 * @param size its size (not used)
 * @return a pointer to the new CIScintiHit
 */
inline void* CIScintiHit::operator new(size_t size) {
	void *aHit;
	aHit = (void *) CIScintiHitsAllocator.MallocSingle();
	return aHit;
}

/**
 * Delete the CIScintiHit, using the CIScintiHitsAllocator
 * @param aHit pointer to the CIScintiHit to be deleted
 */
inline void CIScintiHit::operator delete(void *aHit) {
	CIScintiHitsAllocator.FreeSingle((CIScintiHit*) aHit);
}

#endif
