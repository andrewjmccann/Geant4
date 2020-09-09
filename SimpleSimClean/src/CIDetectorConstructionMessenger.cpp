/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.              *
 *   hseywerd@nrcan.gc.ca                                                  *
 *                                                                         *
 ***************************************************************************/
/**
 * @file CIDetectorConstructionMessenger.cpp
 * @brief
 *
 * @date Sep 8, 2009
 *
 * @author hseywerd
 **/
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWith3Vector.hh"

#include "CIDetectorConstructionMessenger.h"
#include "CIDetectorConstruction.h"

const G4String CIDetectorConstructionMessenger::m_strDirectoryName ("/ComptonImager/FullDetector/");
const G4String CIDetectorConstructionMessenger::m_strSetScatterMaterial("ScatterMaterial");
const G4String CIDetectorConstructionMessenger::m_strSetScatterConfig("ScatterConfig");
const G4String CIDetectorConstructionMessenger::m_strSetScatterXtalSize("ScatterXtalSize");
const G4String CIDetectorConstructionMessenger::m_strSetScatterCellGap("ScatterGap");

const G4String CIDetectorConstructionMessenger::m_strSetAbsorberMaterial("AbsorberMaterial");
const G4String CIDetectorConstructionMessenger::m_strSetAbsorberConfig("AbsorberConfig");
const G4String CIDetectorConstructionMessenger::m_strSetAbsorberXtalSize("AbsorberXtalSize");
const G4String CIDetectorConstructionMessenger::m_strSetAbsorberCellGap("AbsorberGap");

const G4String CIDetectorConstructionMessenger::m_strSetScatterAbsorberZGap("ScatAbsZGap");

const G4String CIDetectorConstructionMessenger::m_strApplySmearFactor("ApplySmear");
const G4String CIDetectorConstructionMessenger::m_strSmearFactorValueScat("SmearFactorValueScat");
const G4String CIDetectorConstructionMessenger::m_strSmearFactorValueAbs("SmearFactorValueAbs");
const G4String CIDetectorConstructionMessenger::m_strTPSetAbsorberPixelLoc("AbsorberPixelXYZ");


const G4String CIDetectorConstructionMessenger::m_strSetSourceCapsule("SourceCapsule");


CIDetectorConstructionMessenger::CIDetectorConstructionMessenger(CIDetectorConstruction* pCIDetectorConstruction) :
	m_pCIDetectorConstruction(pCIDetectorConstruction) {
  m_pUIDirectory = new G4UIdirectory (m_strDirectoryName);

  // Scatter Detector material config
  G4String cmdName = m_strDirectoryName + m_strSetScatterMaterial;
  m_pSetScatterMaterialCmd = new G4UIcmdWithAString(cmdName, this);
  m_pSetScatterMaterialCmd->SetGuidance ("Material to use for scatter detector");
  m_pSetScatterMaterialCmd->AvailableForStates (G4State_PreInit, G4State_Init);

  // Layout of scatter detector cells
  cmdName = m_strDirectoryName + m_strSetScatterConfig;
  m_pSetScatterConfigCmd = new G4UIcmdWith3Vector(cmdName, this);
  m_pSetScatterConfigCmd->SetGuidance ("Cell configuration to use for scatter detector (nX, nY, nZ)");
  m_pSetScatterConfigCmd->AvailableForStates (G4State_PreInit, G4State_Init);

  // Scatter detector crystal size
  cmdName = m_strDirectoryName + m_strSetScatterXtalSize;
  m_pSetScatterXtalSizeCmd = new G4UIcmdWith3Vector(cmdName, this);
  m_pSetScatterXtalSizeCmd->SetGuidance ("Crystal size to use for scatter detector (X, Y, Z)");
  m_pSetScatterXtalSizeCmd->AvailableForStates (G4State_PreInit, G4State_Init);

  // Space between scatter cells
  cmdName = m_strDirectoryName + m_strSetScatterCellGap;
  m_pSetScatterCellGapCmd = new G4UIcmdWith3Vector(cmdName, this);
  m_pSetScatterCellGapCmd->SetGuidance ("Inter Cell Gap for scatter detector");
  m_pSetScatterCellGapCmd->AvailableForStates (G4State_PreInit, G4State_Init);


  // Absorber Detector material config
  cmdName = m_strDirectoryName + m_strSetAbsorberMaterial;
  m_pSetAbsorberMaterialCmd = new G4UIcmdWithAString(cmdName, this);
  m_pSetAbsorberMaterialCmd->SetGuidance ("Material to use for absorber detector");
  m_pSetAbsorberMaterialCmd->AvailableForStates (G4State_PreInit, G4State_Init);

  // Layout of Absorber detector cells
  cmdName = m_strDirectoryName + m_strSetAbsorberConfig;
  m_pSetAbsorberConfigCmd = new G4UIcmdWith3Vector(cmdName, this);
  m_pSetAbsorberConfigCmd->SetGuidance ("Cell configuration to use for Absorber detector (nX, nY, nZ)");
  m_pSetAbsorberConfigCmd->AvailableForStates (G4State_PreInit, G4State_Init);

  // Absorber detector crystal size
  cmdName = m_strDirectoryName + m_strSetAbsorberXtalSize;
  m_pSetAbsorberXtalSizeCmd = new G4UIcmdWith3Vector(cmdName, this);
  m_pSetAbsorberXtalSizeCmd->SetGuidance ("Crystal size to use for Absorber detector (X, Y, Z)");
  m_pSetAbsorberXtalSizeCmd->AvailableForStates (G4State_PreInit, G4State_Init);

  // Space between Absorber cells
  cmdName = m_strDirectoryName + m_strSetAbsorberCellGap;
  m_pSetAbsorberCellGapCmd = new G4UIcmdWith3Vector(cmdName, this);
  m_pSetAbsorberCellGapCmd->SetGuidance ("Inter Cell Gap for Absorber detector");
  m_pSetAbsorberCellGapCmd->AvailableForStates (G4State_PreInit, G4State_Init);


  // Space between Scatter and Absorber detector (centre of scatter to front of absorber) in z
  cmdName = m_strDirectoryName + m_strSetScatterAbsorberZGap;
  m_pSetScatterAbsorberZGapCmd = new G4UIcmdWithADouble(cmdName, this);
  m_pSetScatterAbsorberZGapCmd->SetGuidance ("Detector Gap (centre-scatter to front absorber in z");
  m_pSetScatterAbsorberZGapCmd->AvailableForStates (G4State_PreInit, G4State_Init);

	// Command to enable the enable smearing of hit energy
  cmdName = m_strDirectoryName + m_strApplySmearFactor;
	m_pApplySmearFactorCmd = new G4UIcmdWithABool(cmdName, this);
	m_pApplySmearFactorCmd->SetGuidance("If true apply smearing to scintillator energy deposit");
	m_pApplySmearFactorCmd->SetParameterName("value", false);
	m_pApplySmearFactorCmd->SetDefaultValue(false);
	m_pApplySmearFactorCmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle);

	// Command to set value of energy smear factor - scatter
	cmdName = m_strDirectoryName + m_strSmearFactorValueScat;
	m_pSmearFactorValueScatCmd = new G4UIcmdWithADouble(cmdName, this);
	m_pSmearFactorValueScatCmd->SetGuidance(
			"Value of smearing to be applied to scintillator energy deposits in scatter detector");
	m_pSmearFactorValueScatCmd->SetParameterName("value", false);
	m_pSmearFactorValueScatCmd->SetDefaultValue(0.10);
	m_pSmearFactorValueScatCmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle);

	// Command to set value of energy smear factor- absorber
	cmdName = m_strDirectoryName + m_strSmearFactorValueAbs;
	m_pSmearFactorValueAbsCmd = new G4UIcmdWithADouble(cmdName, this);
	m_pSmearFactorValueAbsCmd->SetGuidance(
			"Value of smearing to be applied to scintillator energy deposits in absorber detector");
	m_pSmearFactorValueAbsCmd->SetParameterName("value", false);
	m_pSmearFactorValueAbsCmd->SetDefaultValue(0.10);
	m_pSmearFactorValueAbsCmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle);

  // Location of the absorber pixel for the two pixel detector
  cmdName = m_strDirectoryName + m_strTPSetAbsorberPixelLoc;
  m_pTPSetAbsorberPixelLocCmd = new G4UIcmdWith3Vector(cmdName, this);
  m_pTPSetAbsorberPixelLocCmd->SetGuidance ("Two pixel detector - location of absorber pixel");
  m_pTPSetAbsorberPixelLocCmd->AvailableForStates (G4State_PreInit, G4State_Init, G4State_Idle);

  // Turn on the source capsule material
  cmdName = m_strDirectoryName + m_strSetSourceCapsule;
  m_pSourceCapsuleCmd = new G4UIcmdWithAnInteger(cmdName, this);
  m_pSourceCapsuleCmd->SetGuidance ("Turn on source encapsulation material, 0 off, N>0 choose which type");
  m_pSourceCapsuleCmd->AvailableForStates (G4State_PreInit, G4State_Init, G4State_Idle);


}

//-----------------------------------------------------------------------------
CIDetectorConstructionMessenger::~CIDetectorConstructionMessenger() {


  if (m_pUIDirectory) delete m_pUIDirectory;

  if (m_pSetScatterMaterialCmd) delete m_pSetScatterMaterialCmd;
  if (m_pSetScatterConfigCmd) delete m_pSetScatterConfigCmd;
  if (m_pSetScatterXtalSizeCmd) delete m_pSetScatterXtalSizeCmd;
  if (m_pSetScatterCellGapCmd) delete m_pSetScatterCellGapCmd;

  if (m_pSetAbsorberMaterialCmd) delete m_pSetAbsorberMaterialCmd;
  if (m_pSetAbsorberConfigCmd) delete m_pSetAbsorberConfigCmd;
  if (m_pSetAbsorberXtalSizeCmd) delete m_pSetAbsorberXtalSizeCmd;
  if (m_pSetAbsorberCellGapCmd) delete m_pSetAbsorberCellGapCmd;

  if (m_pSetScatterAbsorberZGapCmd) delete m_pSetScatterAbsorberZGapCmd;

	if (m_pApplySmearFactorCmd) delete m_pApplySmearFactorCmd;
	if (m_pSmearFactorValueScatCmd) delete m_pSmearFactorValueScatCmd;
	if (m_pSmearFactorValueAbsCmd) delete m_pSmearFactorValueAbsCmd;

  if (m_pTPSetAbsorberPixelLocCmd) delete m_pTPSetAbsorberPixelLocCmd;
  if (m_pSourceCapsuleCmd) delete m_pSourceCapsuleCmd;



}

//-----------------------------------------------------------------------------
void CIDetectorConstructionMessenger::SetNewValue (G4UIcommand* pCommand, const G4String newValue)
{
  if (pCommand == m_pSetScatterMaterialCmd) {
  	m_pCIDetectorConstruction->SetScatterMaterial(newValue);
  } else if (pCommand == m_pSetScatterConfigCmd) {
  	m_pCIDetectorConstruction->SetScatterConfig(G4UIcmdWith3Vector::GetNew3VectorValue(newValue));
  } else if (pCommand == m_pSetScatterXtalSizeCmd) {
  	m_pCIDetectorConstruction->SetScatterXtalSize(G4UIcmdWith3Vector::GetNew3VectorValue(newValue));
  } else if (pCommand == m_pSetScatterXtalSizeCmd) {
  	m_pCIDetectorConstruction->SetScatterXtalSize(G4UIcmdWith3Vector::GetNew3VectorValue(newValue));
  } else if (pCommand == m_pSetScatterCellGapCmd) {
  	m_pCIDetectorConstruction->SetScatterCellGap(G4UIcmdWith3Vector::GetNew3VectorValue(newValue));
//
  } else if (pCommand == m_pSetAbsorberMaterialCmd) {
  	m_pCIDetectorConstruction->SetAbsorberMaterial(newValue);
  } else if (pCommand == m_pSetAbsorberConfigCmd) {
  	m_pCIDetectorConstruction->SetAbsorberConfig(G4UIcmdWith3Vector::GetNew3VectorValue(newValue));
  } else if (pCommand == m_pSetAbsorberXtalSizeCmd) {
  	m_pCIDetectorConstruction->SetAbsorberXtalSize(G4UIcmdWith3Vector::GetNew3VectorValue(newValue));
  } else if (pCommand == m_pSetAbsorberCellGapCmd) {
  	m_pCIDetectorConstruction->SetAbsorberCellGap(G4UIcmdWith3Vector::GetNew3VectorValue(newValue));
//
  } else if (pCommand == m_pSetScatterAbsorberZGapCmd ) {
  	m_pCIDetectorConstruction->SetScatterAbsorberZGap(G4UIcmdWithADouble::GetNewDoubleValue(newValue));
  }
//
  else if (pCommand == m_pApplySmearFactorCmd) {
  	m_pCIDetectorConstruction->SetApplySmear(m_pApplySmearFactorCmd->GetNewBoolValue(newValue));
 	} else if (pCommand == m_pSmearFactorValueScatCmd) {
 		m_pCIDetectorConstruction->SetSmearValueScat(m_pSmearFactorValueScatCmd->GetNewDoubleValue(newValue));
 	} else if (pCommand == m_pSmearFactorValueAbsCmd) {
 		m_pCIDetectorConstruction->SetSmearValueAbs(m_pSmearFactorValueAbsCmd->GetNewDoubleValue(newValue));
  } else if (pCommand == m_pTPSetAbsorberPixelLocCmd ) {
	  m_pCIDetectorConstruction->SetTPAbsorberPixelLoc(G4UIcmdWith3Vector::GetNew3VectorValue(newValue));
  } else if (pCommand == m_pSourceCapsuleCmd ) {
	  m_pCIDetectorConstruction->SetSourceAssembly(G4UIcmdWithAnInteger::GetNewIntValue(newValue));
  }
}
