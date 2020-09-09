/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.               *
 *   hseywerd@nrcan.gc.ca                                                   *
 *                                                                          *
 ***************************************************************************/
/**
 * @file CIMaterialHit.h
 * @brief Represent hits in materials.
 * @author Henry Seywerd hseywerd@nrcan.gc.ca
 **/
#ifndef CIMaterialHit_h
#define CIMaterialHit_h

#include "CIGenericHit.h"

/**
 * @class CIMaterialHit
 * @brief Represent hits in materials.
 *
 * @author Henry Seywerd <hseywerd@nrcan.gc.ca>
 */
class CIMaterialHit: public CIGenericHit {
public:
	/**
	 * Constructor
	 */
	CIMaterialHit();

	/**
	 * Copy constructor
	 * @param hit object to copy
	 */
	CIMaterialHit(const CIMaterialHit& hit);

	/**
	 * Assignment
	 * @param hits object to copy
	 */
	const CIMaterialHit& operator=(const CIMaterialHit& hits);

	/**
	 * Assignment
	 * @param hit object to copy
	 */
	G4int operator==(const CIMaterialHit& hit) const;

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
	~CIMaterialHit();

	/**
	 * @return Reference to the name of the incoming particle
	 */
	inline G4String& ThePartName() {
		return m_strPartName;
	}

	/**
	 * @return Reference to the name of the incoming particle
	 */
	inline G4String& TheMedium() {
		return m_strMediumName;
	}


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
	/// The energy deposited
  G4double      m_dEnergyDep;
  /// The name of the medium where the deposit occureed
  G4String m_strMediumName;
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------


/**
 * @class CIMaterialHitsCollection
 * @brief Collection of scintillator hits (CIMaterialHits)
 *
 * Use G4Allocator to allocate the object
 *
 * @author Henry Seywerd <hseywerd@nrcan.gc.ca>
 */

typedef G4THitsCollection<CIMaterialHit> CIMaterialHitsCollection;

extern G4Allocator<CIMaterialHit> CIMaterialHitsAllocator;

/**
 * Allocate a new CIMaterialHit, using the CIMaterialHitsAllocator
 * @param size its size (not used)
 * @return a pointer to the new CIMaterialHit
 */
inline void* CIMaterialHit::operator new(size_t size) {
	void *aHit;
	aHit = (void *) CIMaterialHitsAllocator.MallocSingle();
	return aHit;
}

/**
 * Delete the CIMaterialHit, using the CIMaterialHitsAllocator
 * @param aHit pointer to the CIMaterialHit to be deleted
 */
inline void CIMaterialHit::operator delete(void *aHit) {
	CIMaterialHitsAllocator.FreeSingle((CIMaterialHit*) aHit);
}

#endif
