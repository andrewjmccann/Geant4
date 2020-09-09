/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.              *
 *   hseywerd@nrcan.gc.ca                                                  *
 *                                                                         *
 ***************************************************************************/
/**
 * @file CIAbsorberDetector.h
 * @brief
 *
 * @date 2009-10-05
 *
 * @author hseywerd@nrcan.gc.ca
 **/

#ifndef CIABSORBERDETECTOR_H_
#define CIABSORBERDETECTOR_H_
#include "G4LogicalVolume.hh"


class G4OpticalSurface;

class CISensitiveScintiDetector;
class CISensitiveOpticalDetector;
class CIMaterials;


class CIAbsorberDetector : public G4LogicalVolume {
public:
	CIAbsorberDetector(const G4String name, G4VPhysicalVolume* pEnclosingVolume, CISensitiveScintiDetector* pCISensitiveScintiDetector, CISensitiveOpticalDetector* pCISensitiveOpticalDetector, G4int& iCell);
	virtual ~CIAbsorberDetector() {};

	void SetAbsorberMaterial(const G4String materialName) {m_strAbsorberDetectorMaterialName = materialName;};
	/// Allow Absorber detector configuration to be set from the messenger
//	void SetAbsorberConfig( const G4ThreeVector& config) {m_iNACellX = (int)config.getX(), m_iNACellY=(int)config.getY(), m_iNACellZ = (int)config.getZ();};
//	/// Set the Absorber detector crystal size - convert to half size.
//	void SetAbsorberCrystalSize( const G4ThreeVector& size) {m_CrystalHalfSizeA = 0.5*size;};
//	/// Set the Absorber detector inter-cell spacing.
//	void SetAbsorberCellGap( const G4ThreeVector& gap) {m_dACellGap = gap;};
//
//	/// Set the scatter to absorber detector distance
//	void SetScatterAbsorberZGap(const G4double gap) {m_dASGap = gap;};

  /**
   * Actually construct the detector
    * @return a pointer to the detector
    *
    * This detector consists of a crystal, a front and rear window, and an aluminum housing to provide mechanical support and sealinmg
    * Between the glass and the crystal is a layer of optical compound. At the side edges of the crystal is a white reflecting medium.
    * The aluminum housing model is simplified, in that it contains no steps or flanges for recessing the glass, and there is mo
    * modelling of any sealing materials.
    * Feel welcome to refine this.
  */
	G4VPhysicalVolume* Construct();

private:

	/***
	 * Build the housing for the crystal
	 * @return pointer to a logical volume representing the crystal housing.
	 */
	void ConstructHousing();


	/***
	 * Build the crystal/assembly of crystals
	 * @return pointer to a logical volume representing the crystal assembly.
	 */
	void ConstructCrystalAssembly();

	/***
	 * Build the front detector assembly
	 * @return pointer to a logical volume representing the front detector assembly.
	 */
	void ConstructFrontDetector();

	/***
	 * Build the read detector assembly
	 * @return pointer to a logical volume representing the rear detector assembly.
	 */
	void ConstructRearDetector();


	/**
	 * Construct the absorber detector
	 * @param iCell on input the intial cell number to be used, returned as the next cell number
	 */
	void ConstructAbsorber(G4int& iCell);

	/**
	 * Construct a single crystal detector for checking.
	 *
	 */
	void ConstructSingleCrystal();

	void ConstructCrystalArray();

	void ConstructSensitiveOpticalSurface();

  /// The sensitive detector for scintillation behaviour
  CISensitiveScintiDetector* m_pCISensitiveScintiDetector;

  /// The sensitive detector for optical photons
  CISensitiveOpticalDetector* m_pCISensitiveOpticalDetector;

  /// Magnetic Field manager, here we don't have one so in implementation we fix to NULL
  G4FieldManager* m_pNullFieldMgr;

  /// If true perform surface interference checks in placement of volumes
  G4bool m_bVolPlacementCheck;

  // Some other parameters for the detectors
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

  /// The crystal assembly overall half-size for the entire absorber detector
  static const G4ThreeVector  m_HSize;

  /// Thickness of glass at front and behind the NaI.
  static const G4double m_dGlassThickness;
  /// The half-size of the front glass plane
  static const G4ThreeVector m_FrontGlassHSize;
  /// The half-size of the rear glass plane
  static const G4ThreeVector m_RearGlassHSize;
  /// Thickness of optical compound between glass and crystal
  const G4double m_dOpticalCompoundThickness;
  /// Outer dimensions of crystal housing (half-size)
  static const G4ThreeVector m_CrystalHousingOuterHSize;
  /// Inner dimensions of the crystal housing (half-size)
  static const G4ThreeVector m_CrystalHousingInnerHSize;
  /// Thickness of the housing wall
  static const G4double m_dHousingWallThickness;
  /// Crystal assembly, i.e. the crystals themselves outside dimensions (half-size)
  static const G4ThreeVector m_CrystalAssemblyHSize;
  /// Crystal sizes for pixelated detector
  static const G4ThreeVector m_CrystalPixelHSize;
  /// Number of crystals pixelated in X and Y
  static const G4int m_iNPixelX, m_iNPixelY;
  /// Thickness of the detector
  static const G4double m_dDetectorThickness;


  static const G4String m_HousingName;
  static const G4String m_CrystalAssemblyName;
  static const G4String m_FrontDetectorName;
  static const G4String m_RearDetectorName;


  /// Logical volume for the crystal housing
  G4LogicalVolume* m_HousingLog;
  /// Logical volume for the enclosing glass of the crystal housing - front
  G4LogicalVolume* m_FrontGlassLog;
  /// Logical volume for the enclosing glass of the crystal housing - rear
  G4LogicalVolume* m_RearGlassLog;


  /// Logical volume for the crystal assembly
  G4LogicalVolume* m_CrystalAssemblyLog;
  /// Logical volume for the front detector
  G4LogicalVolume* m_FrontDetectorLog;
  /// Logical volume for the rear detector
  G4LogicalVolume* m_RearDetectorLog;

  /// The materials database
  CIMaterials* m_Materials;


  G4OpticalSurface* m_surfaceSensitiveOptical;

};

#endif /* CIABSORBERDETECTOR_H_ */
