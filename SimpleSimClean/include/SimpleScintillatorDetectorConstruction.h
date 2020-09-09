/***************************************************************************
*   Copyright (C) Minister of Natural Resources Canada 2008.              *
*   hseywerd@nrcan.gc.ca                                                  *
*                                                                         *
***************************************************************************/
/**
 * @file SimpleScintillatorDetectorConstruction.h
 * @brief Build the detector.
 *
 * @date 2008/12/08
 *
 *
 * @author HCJ Seywerd hseywerd@nrcan.gc.ca
 **/

#ifndef SimpleScintillatorDetectorConstruction_h
#define SimpleScintillatorDetectorConstruction_h 1


#include "G4VUserDetectorConstruction.hh"
class CISensitiveScintiDetector;
class CISensitiveOpticalDetector;

class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4VPVParameterisation;
class G4UserLimits;


/**
 * @class SimpleScintillatorDetectorConstruction
 *
 * @brief Build a simple scintillator detector
 *
 * @author HCJ Seywerd hseywerd@nrcan.gc.ca
 *
 */
class SimpleScintillatorDetectorConstruction : public G4VUserDetectorConstruction
{
public:

  /**
   * Construct the actual detector
 * @param  pCISensitiveScintiDetector Pointer to the sensitive detector for managing hits in the scintillator
 * @param  pCISensitiveOpticalDetector Pointer to the sensitive detector for managing hits of optical photons in a photodetector
   */
  SimpleScintillatorDetectorConstruction(CISensitiveScintiDetector* pCISensitiveScintiDetector, CISensitiveOpticalDetector* pCISensitiveOpticalDetector);
	~SimpleScintillatorDetectorConstruction();

public:
    /**
     * Construct the detector
     * @return a pointer to the detector
     */
	G4VPhysicalVolume* Construct();

private:
  /// The sensitive detector for scintillation behaviour
  CISensitiveScintiDetector* m_pCISensitiveScintiDetector;

  /// The sensitive detector for optical photons
  CISensitiveOpticalDetector* m_pCISensitiveOpticalDetector;

    /**
   * Constructs a Silicon Photomultiplier - this version for the SenSL
   *
   * Each SiPM is constructed from the following subcomponents
   * * A layer of glass
   * * A layer of optical coupling compound
   * * A layer of SiPM elements
   * * A housing for the SiPM, with connector etc.
   *
   * @param SiPM_Log  the logical volume representing the SiPM
   * @param SiPM_Name a name for this instance of the SiPM
     */
  void ConstructSiPM(G4LogicalVolume** SiPM_Log, const G4String& SiPM_Name);

  //Some useful string constants
  /// Indicates a logical volume
  static const G4String m_LogicalVolumeSuffix;
  /// Indicates a physical volume
  static const G4String m_PhysicalVolumeSuffix;
  /// Indicates an object representing a volume
  static const G4String m_VolumeSuffix;
  /// Indicates an optical surface between two volumes
  static const G4String m_OpticalSurfaceSuffix;
  /// Indicates a logical surface between two volumes
  static const G4String m_LogSurfaceSuffix;

};

#endif
