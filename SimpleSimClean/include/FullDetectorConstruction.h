/***************************************************************************
*   Copyright (C) Minister of Natural Resources Canada 2008.              *
*   hseywerd@nrcan.gc.ca                                                  *
*                                                                         *
***************************************************************************/
/**
 * @file FullDetectorConstruction.h
 * @brief Build the detector.
 *
 * @date 2009/04/15
 *
 *
 * @author HCJ Seywerd hseywerd@nrcan.gc.ca
 **/

#ifndef FullDetectorConstruction_h
#define FullDetectorConstruction_h 1


#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"


#include "CIDetectorConstruction.h"
#include "CellVolume.h"

class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4VPVParameterisation;
class G4UserLimits;
class G4FieldManager;
class G4VisAttributes;


class CIPrimaryGeneratorAction;
class CISensitiveScintiDetector;
class CISensitiveOpticalDetector;
class CISensitiveMaterials;
class FullDetectorConstructionMessenger;
class CsSourceAssembly;




/**
 * @class FullDetectorConstruction
 *
 * @brief Build a detector including multiple layers of scatter and abosrber detectors with SiPM readout
 *
 * Detector is located at the centre of the volume.
 *
 * @author HCJ Seywerd hseywerd@nrcan.gc.ca
 *
 */
class FullDetectorConstruction : public CIDetectorConstruction
{
public:

  /**
   * Constructor, initializations
 * @param  pCISensitiveScintiDetector Pointer to the sensitive detector for managing hits in the scintillator
 * @param  pCISensitiveOpticalDetector Pointer to the sensitive detector for managing hits of optical photons in a photodetector
   */
  FullDetectorConstruction(CISensitiveScintiDetector* pCISensitiveScintiDetector, CISensitiveOpticalDetector* pCISensitiveOpticalDetector, CISensitiveMaterials* pCISensitiveMaterials);
	~FullDetectorConstruction();

  /// Return the material used in the absorber detector
	std::string  GetMaterialAbsorber() const {
		return (m_strAbsorberDetectorMaterialName);
	}
	/// Return the material used in the scatter detector
	std::string GetMaterialScatter() const {
		return (m_strScatterDetectorMaterialName);
	}
	/// Get the smearing method used
	CIRootRunHeader::SMEAR GetSmearType() const  {if (m_bApplySmear) return CIRootRunHeader::SMEAR_SINGLE_GAUSS; else return CIRootRunHeader::SMEAR_OTHER;}

	/// Allow the scatter detector material to be set from the messenger
	void SetScatterMaterial(const G4String materialName) {m_strScatterDetectorMaterialName = materialName;}
	/// Allow the absorber detector material to be set from the messenger
	void SetScatterConfig( const G4ThreeVector& config) {m_iNSCellX = (int)config.getX(), m_iNSCellY=(int)config.getY(), m_iNSCellZ = (int)config.getZ();}
	/// Set the scatter detector crystal size - convert to half size.
	void SetScatterXtalSize( const G4ThreeVector& size) {m_xtalHalfSizeS = 0.5*size;}
	/// Set the scatter detector inter-cell gap.
	void SetScatterCellGap( const G4ThreeVector& gap) {m_dSCellGap = gap;}

	void SetAbsorberMaterial(const G4String materialName) {m_strAbsorberDetectorMaterialName = materialName;}
	/// Allow Absorber detector configuration to be set from the messenger
	void SetAbsorberConfig( const G4ThreeVector& config) {m_iNACellX = (int)config.getX(), m_iNACellY=(int)config.getY(), m_iNACellZ = (int)config.getZ();}
	/// Set the Absorber detector crystal size - convert to half size.
	void SetAbsorberXtalSize( const G4ThreeVector& size) {m_xtalHalfSizeA = 0.5*size;}
	/// Set the Absorber detector inter-cell spacing.
	void SetAbsorberCellGap( const G4ThreeVector& gap) {m_dACellGap = gap;}

	/// Set the scatter to absorber detector distance
	void SetScatterAbsorberZGap(const G4double gap) { m_dASGap = gap;
	  G4cout << "m_dASGap is " << m_dASGap << G4endl;
}

	/// Set the scatter to absorber detector distance
	void SetScatterZPos(const G4double ZPos) {m_dScatterZPos = ZPos;
	  G4cout << "m_dScatterZPos is " << m_dScatterZPos << G4endl;

}

	/// Set the scatter to absorber detector distance
	void SetAbsorberZPos(const G4double ZPos) {m_dAbsorberZPos = ZPos;
	  G4cout << "m_dAbsorberZPos is " << m_dAbsorberZPos << G4endl;

}


	void SetTPAbsorberPixelLoc(const G4ThreeVector location);

	/// Create a particular absorber cell
	void PlaceTheAbsorberCell(const G4ThreeVector pixelLoc);

	/// Set the source assembly type, 0=none, 1=Pat's
	void SetSourceAssembly(const int sourceAssemblyType) {m_iSourceAssemblyType=sourceAssemblyType;}

  /**
   * Actually construct the detector
    * @return a pointer to the detector
  */
	G4VPhysicalVolume* Construct();

private:
	/**
	 * Construct the absorber detector
	 * @param iCell on input the initial cell number to be used, returned as the next cell number
	 */
	void ConstructAbsorber(G4int& iCell);
	/**
	 * Construct the scatter detector
	 * @param iCell on input the initial cell number to be used, returned as the next cell number
	 */
	void ConstructAbsorberCsISiPM(G4int& iCell);
	/**
	 * Construct the scatter detector
	 * @param iCell on input the initial cell number to be used, returned as the next cell number
	 */

	void ConstructAbsorber2(G4int& iCell);
	/**
	 * Construct the scatter detector
	 * @param iCell on input the initial cell number to be used, returned as the next cell number
	 */
	void ConstructConcreteWall();

	void ConstructScatter(G4int& iCell);

	/**
	 * Construct a single crystal detector for checking.
	 *
	 * Use parameters from the "Scatter Detector" inputs.
	 */
	void ConstructSingleXtal();

	/**
	 * Construct the scatter detector
	 * @param iCell on input the initial cell number to be used, returned as the next cell number
	 */
	void ConstructSORMAScatter(G4int& iCell);
	/**
	 * Construct the absorber detector per SORMA paper specifications
	 * @param iCell on input the initial cell number to be used, returned as the next cell number
	 */
	void ConstructSORMAAbsorber(G4int& iCell);

	/**
	 * Construct the absorber detector using the CIAbsorberDetector class
	 * @param iCell on input the initial cell number to be used, returned as the next cell number
	 */
	void ConstructGeneralAbsorber(G4int& iCell);

	/**
	 * Construct a "Two-Pixel" imager
	 */
	void ConstructTwoPixel();

	/**
	 * Construct a "Two-Pixel" imager lead shield - original version
	 */
	void ConstructTwoPixelOldShield();

	/**
	 * Construct a "Two-Pixel" imager imager lead shield - improved monolithic version
	 */
	void ConstructTwoPixelNewShield();


	/// Access to the event generator
	const CIPrimaryGeneratorAction* m_pCIPrimaryGeneratorAction;

  /// The sensitive detector for scintillation behaviour
  CISensitiveScintiDetector* m_pCISensitiveScintiDetector;

  /// The sensitive detector for optical photons
  CISensitiveOpticalDetector* m_pCISensitiveOpticalDetector;

  /// For storing energy deposits in other materials
  CISensitiveMaterials* m_pCISensitiveMaterials;

  /// The physical volume representing the experimental hall (world)
  G4VPhysicalVolume* m_WorldPhys;
  G4LogicalVolume* m_WorldLog;

  /// Magnetic Field manager, here we don't have one so in implementation we fix to NULL
  G4FieldManager* m_pNullFieldMgr;

  /// If true perform surface interference checks in placement of volumes
  G4bool m_bVolPlacementCheck;

  // Some other parameters for the detectors
  /// Material for the scatter detector, must be defined in CIMaterials
  G4String m_strScatterDetectorMaterialName;
  /// Material for the scatter detector, must be defined in CIMaterials
  G4String m_strAbsorberDetectorMaterialName;


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

  // Some sizes
  /// Size of the world volume
  const G4ThreeVector m_worldSize;
  /// The sipm size
  G4ThreeVector m_sipmHalfSize;
  /// The crystal size for the scatter detectors
  G4ThreeVector m_xtalHalfSizeS;
  /// The crystal size for the absorber detectors
  G4ThreeVector m_xtalHalfSizeA;

  // Some numbers indicating the number of cells in the detector
  /// Number of cells in the scatter detector in x, y, and z
  G4int m_iNSCellX, m_iNSCellY, m_iNSCellZ;
  /// Number of cells in the absorber detector in x, y, and z
  G4int m_iNACellX, m_iNACellY, m_iNACellZ;
  /// Offset between individual cells for scatter - in addition to cell size
  G4ThreeVector m_dSCellGap;
  /// Offset between individual cells for absorber - in addition to cell size
  G4ThreeVector m_dACellGap;
  /// Offset between scatter and absorber layers - distance between centre of scatter and front of absorber
  G4double m_dASGap;
  /// Z Position of Center of the Scatter
  G4double m_dScatterZPos;
  /// Z Position of Center of the Absorber
  G4double m_dAbsorberZPos;
  /// Size of scatter detector system in Z
  G4double m_dSTotalZ;
  /// Location of the absorber pixel in the two-pixel detector
  G4ThreeVector m_TPAbsorberPixelLoc;
  /// Logical volume for the absorber cell
  G4LogicalVolume* m_pAbsorberCellLog;
  /// Physical volume for the absorber cell (to allow it to be translated between runs).
	G4VPhysicalVolume* m_pAbsorberCellPhys;
  /// Base placement of the absorber pixel in the TP, i.e. at (0,0,0)
  G4ThreeVector m_TPAbsorberPixelBasePlacement;
  /// Base placement of the absorber pixel in the TP, i.e. at (0,0,0)
  G4ThreeVector m_TPAbsorberPixelCurrentPlacement;

  /// Type of source assembly to implement, 0=none;
  G4int m_iSourceAssemblyType;
  /// And the source assembly itself
  CsSourceAssembly* m_pCsSourceAssembly;

  /// The messenger class to allow receiving from the UI
  FullDetectorConstructionMessenger* m_pMessenger;

  /// Visual attributes -- for the shielding
  G4VisAttributes* m_visAttShield;


  G4RotationMatrix* m_ScatterRotation;
  G4RotationMatrix* m_AbsorberRotation;
	G4RotationMatrix* m_AssemblyRotation;

};

#endif
