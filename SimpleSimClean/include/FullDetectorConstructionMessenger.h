/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.              *
 *   hseywerd@nrcan.gc.ca                                                  *
 *                                                                         *
 ***************************************************************************/
/**
 * @file FullDetectorConstructionMessenger.h
 * @brief
 *
 * @date Sep 8, 2009
 *
 * @author hseywerd
 **/

#ifndef FULLDETECTORCONSTRUCTIONMESSENGER_H_
#define FULLDETECTORCONSTRUCTIONMESSENGER_H_

#include "G4UImessenger.hh"

class FullDetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithABool;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADouble;
class G4UIcmdWith3Vector;

/**
 * @class FullDetectorConstructionMessenger
 * @brief Messenger class for setting up detetector construction details from the command line
 *
 *
 * @author hseywerd@nrcan.gc.ca
 *
 */
class FullDetectorConstructionMessenger : public G4UImessenger {
public:
	FullDetectorConstructionMessenger(FullDetectorConstruction* pFullDetectorConstruction);
	virtual ~FullDetectorConstructionMessenger();

  /**
   * Process commands from the macro and invoke the appropriate response in FullDetectorConstruction
   * @param pCommand the command
   * @param newValue the value provided with the command
   */
  virtual void SetNewValue (G4UIcommand* pCommand, const G4String newValue);

protected:
  /// Pointer to the FullDetectorConstruction whose details are to be set
	FullDetectorConstruction*          m_pFullDetectorConstruction;
  /// The directory in which this set of commands is maintained
  G4UIdirectory*        m_pUIDirectory;
  /// String giving the directory name
  static const G4String m_strDirectoryName;
  /// String giving the name of the command to set scatter detector material
  static const G4String m_strSetScatterMaterial;
  /// String giving the name of the command to set scatter detector crystal configuration
  static const G4String m_strSetScatterConfig;
  /// String giving the name of the command to set scatter detector crystal size (mm)
  static const G4String m_strSetScatterXtalSize;
  /// String giving the name of the command to set inter-cell gap for scatter detector
  static const G4String m_strSetScatterCellGap;

  /// String giving the name of the command to set absorber detector material
  static const G4String m_strSetAbsorberMaterial;
  /// String giving the name of the command to set Absorber detector crystal configuration
  static const G4String m_strSetAbsorberConfig;
  /// String giving the name of the command to set Absorber detector crystal size (mm)
  static const G4String m_strSetAbsorberXtalSize;
  /// String giving the name of the command to set inter-cell gap for Absorber detector
  static const G4String m_strSetAbsorberCellGap;

  /// String giving the name of the command to set gap between centre of scatter and front of absorber detector
  static const G4String m_strSetScatterAbsorberZGap;

  //Set the position of the scatter
  static const G4String m_strSetScatterZPos;

  //Set the position of the scatter
  static const G4String m_strSetAbsorberZPos;

  /// String giving the command name to apply smearing to the scintillator hit energies
  static const G4String m_strApplySmearFactor;
  /// String giving the command name to define the smear factor constant - scatter detector
  static const G4String m_strSmearFactorValueScat;
  /// String giving the command name to define the smear factor constant - absorber detector
  static const G4String m_strSmearFactorValueAbs;

  /// String giving the identifiers of the location of the absorber pixel for the two pixel detector
  static const G4String m_strTPSetAbsorberPixelLoc;

  /// String giving the command to allow setting the source capsule material
  static const G4String m_strSetSourceCapsule;

  /// Command to set the name of the scatter detector material
  G4UIcmdWithAString*   m_pSetScatterMaterialCmd;
  /// Command to set the name of the scatter detector crystal configuration
  G4UIcmdWith3Vector*   m_pSetScatterConfigCmd;
  /// Command to set the name of the scatter detector crystal size
  G4UIcmdWith3Vector*   m_pSetScatterXtalSizeCmd;
  /// Command to set inter-cell gape for scatter detector
  G4UIcmdWith3Vector*   m_pSetScatterCellGapCmd;

  /// Command to set the name of the absorber detector material
  G4UIcmdWithAString*   m_pSetAbsorberMaterialCmd;
  /// Command to set the name of the Absorber detector crystal configuration
  G4UIcmdWith3Vector*   m_pSetAbsorberConfigCmd;
  /// Command to set the name of the Absorber detector crystal size
  G4UIcmdWith3Vector*   m_pSetAbsorberXtalSizeCmd;
  /// Command to set inter-cell gape for Absorber detector
  G4UIcmdWith3Vector*   m_pSetAbsorberCellGapCmd;


  /// Command to set position of Scatter
  G4UIcmdWithADouble*   m_pSetScatterZPosCmd;

  /// Command to set position of Absorber
  G4UIcmdWithADouble*   m_pSetAbsorberZPosCmd;

  /// Command to set gap between absorber and scatter detector
  G4UIcmdWithADouble*   m_pSetScatterAbsorberZGapCmd;

  /// Command set a enable application of a smear factor
  G4UIcmdWithABool*     m_pApplySmearFactorCmd;
  /// Command set a smearing factor  - scatter detector
  G4UIcmdWithADouble*   m_pSmearFactorValueScatCmd;
  /// Command set a smearing factor  - absorber detector
  G4UIcmdWithADouble*   m_pSmearFactorValueAbsCmd;

  /// Command to set the location of the absorber pixel for the two pixel detector
  G4UIcmdWith3Vector*   m_pTPSetAbsorberPixelLocCmd;

  /// Command to set the setting the source capsule material
  G4UIcmdWithAnInteger*   m_pSourceCapsuleCmd;
};

#endif /* FULLDETECTORCONSTRUCTIONMESSENGER_H_ */
