/***************************************************************************
 *   Copyright (C) NRC 2015              *
 *   audrey.macleod@nrc.cnrg.gc.ca                                               *
 *                                                                         *
 ***************************************************************************/

/**
 * @file SenSL60035SiPMArray.h
 * @brief A logical volume representing a silicon photomultiplier
 **/
#ifndef SenSL60035SiPMArray_h
#define SenSL60035SiPMArray_h

#include "G4VUserDetectorConstruction.hh"
#include "CIPhotoDetector.h"

class G4VPhysicalVolume;
class G4OpticalSurface;
class CISensitiveMaterials;

#include "DynamicArray.h"

/**
 * @class SenSL60035SiPMArray
 * @brief A logical volume representing a silicon photomultiplier
 *
 * @author Henry Seywerd <hseywerd@nrcan.gc.ca>
 */
class SenSL60035SiPMArray: public CIPhotoDetector {
public:
	/**
	 * Create the SiPM
	 * * @param name the name to assign to the device
	 */
	SenSL60035SiPMArray(const G4String name, CISensitiveMaterials* pCISensitiveMaterials);

	/**
	 * Clean up
	 */
	virtual ~SenSL60035SiPMArray();

	/**
	 * Sets the boundary between internal components and the provided physical volume to reflective
	 * and light tight
	 * @param theVolume the physical volume to which the boundary is to be set up.
	 */
	void SetWhiteBoundary(G4VPhysicalVolume* theVolume);

	/// Return the half size of the SiPM
	static const G4ThreeVector& GetHalfSize() {return m_sipmHalfSize;};

	/// Return the extra space required in z for ancillary stuff
	static const  G4double GetExtraSpace() {return 1.0;};


	/// Spacing backwards in z into the photodetector where the sensitive face is located.
	G4double FrontFaceOffset() const {return 0;}
	/**
         * Returns device total length
         */
	G4double GetLength() const {return 0;}

public:



	/// Physical volume for the covering glass plate
	G4VPhysicalVolume* m_Glass_Phys;
	/// Physical volume for the PCB
	G4VPhysicalVolume* m_PCB_Phys;

	/// Physical volume for the optical compound between the glass and the elements
	G4VPhysicalVolume* m_OpticalCompound_Phys;
	/// An array of pointers to the individual elements
	DynamicArray<G4VPhysicalVolume*> m_Elements_Phys;

	///Number of SiPM elements in the device -- X
	const int m_NumElementX;
	///Number of SiPM elements in the device -- Y
	const int m_NumElementY;

	/**
	 * Build the sensitive optical surface of the device
	 *
	 * Static as we only need one for all of the devices
	 */
	static void ConstructSensitiveOpticalSurface();
	/// The sensitive optical surface of the device
	static G4OpticalSurface* m_surfaceSensitiveOptical;
	/// The sipm size
	static const G4ThreeVector m_sipmHalfSize;


};

#endif
