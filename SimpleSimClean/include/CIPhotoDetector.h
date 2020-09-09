/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.              *
 *   hseywerd@nrcan.gc.ca                                                  *
 *                                                                         *
 ***************************************************************************/

/**
 * @file CIPhotoDetector.h
 * @brief A logical volume representing a photodetector
 **/
#ifndef CIPhotoDetector_h
#define CIPhotoDetector_h

#include "G4Types.hh"
#include "G4VPhysicalVolume.hh"
class G4VSolid;
class G4LogicalVolume;
class G4OpticalSurface;
class CISensitiveMaterials;


/**
 * @class CIPhotoDetector
 * @brief Abstract base class for photodetectors.
 *
 * Intended as a base class for SiPM's of various types as well as PMT's
 *
 * @author Henry Seywerd <hseywerd@nrcan.gc.ca>
 */
class CIPhotoDetector  {
public:
	/**
	 * Create the photodetector
	 */
	CIPhotoDetector(G4VSolid* pSolid, const G4String name, CISensitiveMaterials* pCISensitiveMaterials);

	/**
	 * Construct a physical volume for this device
	 * @return a pointer to the physical volume of the detector
	 */
	G4VPhysicalVolume* ConstructPhysical(G4RotationMatrix *pRot, const G4ThreeVector &tlate, const G4String& pName, G4LogicalVolume *pMotherLogical);
	void SetVisibility(const bool bEnableVisability) {
		m_bEnableVisability = bEnableVisability;
	}

	virtual ~CIPhotoDetector() {
	}


	/// Return the Logical volume for the photodetector
	G4LogicalVolume* GetLogicalVol() {return m_pLogicalVolume;}

	//	 virtual  const  G4ThreeVector GetHalfSize() {
	//	}

protected:
  /// The logical volume for the photodetector
	G4LogicalVolume* m_pLogicalVolume;

	/// Sensitive material for storing energy deposits
	CISensitiveMaterials* m_pCISensitiveMaterials;

	/// Enable display of the components of the SiPM
	bool m_bEnableVisability;
	/// Enable placement/overlap checks of the volumes
	bool m_bVolPlacementCheck;
	/// Name of the device
	G4String m_strName;

	//Some useful string constants
	/// Indicates a logical volume
	static const G4String m_LogicalVolumeSuffix;
	/// Indicates a physical volume
	static const G4String m_PhysicalVolumeSuffix;
	/// Indicates an object representing a solid
	static const G4String m_SolidSuffix;
	/// Indicates an optical surface between two volumes
	static const G4String m_OpticalSurfaceSuffix;
	/// Indicates a logical surface between two volumes
	static const G4String m_LogSurfaceSuffix;
	// For use with the old G4 optical model - reflectivity
	static const G4String m_OpticReflectivityName;
	/// Detection efficiency for optical detection materials (photocathodes etc)
	static const G4String m_OpticDetectionEfficiencyName;

	/// Conversion of optical photon wavelength from nm to eV \f$ E(eV) = hc/\lambda(nm) \approx 1240/\lambda\f$
	static const G4double m_dNMtoEV;
};

#endif
