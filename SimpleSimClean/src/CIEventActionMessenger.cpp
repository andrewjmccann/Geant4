/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2009.               *
 *   hseywerd@nrcan.gc.ca                                                   *
 *                                                                          *
 ***************************************************************************/
/**
 * @file CIEventActionMessenger.cpp
 * @brief Provide for user options to the Run setup
 * @author Henry Seywerd hseywerd@nrcan.gc.ca
 **/
#
#include "CIEventActionMessenger.h"
#include "CIEventAction.h"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithABool.hh"

const G4String CIEventActionMessenger::m_strDirectoryName(
		"/ComptonImager/EventAction/");
const G4String CIEventActionMessenger::m_strSaveOpticalPhotonHits(
		"SaveOpticalPhotonHits");
const G4String CIEventActionMessenger::m_strSaveScintiHits("SaveScintiHits");
const G4String CIEventActionMessenger::m_strSaveProcessedHits(
		"SaveProcessedHits");
const G4String CIEventActionMessenger::m_strSaveOnlyCoincidence(
		"SetCoincidenceLevel");
const G4String CIEventActionMessenger::m_strApplySmearFactor("ApplySmear");
const G4String CIEventActionMessenger::m_strSmearFactorValueScat("SmearFactorValueScat");
const G4String CIEventActionMessenger::m_strSmearFactorValueAbs("SmearFactorValueAbs");


CIEventActionMessenger::CIEventActionMessenger(CIEventAction* pCIEventAction) :
	m_pCIEventAction(pCIEventAction), m_pUIDirectory(NULL),
			m_pSaveOpticalPhotonHitsCmd(NULL), m_pSaveScintiHitsCmd(NULL),
			m_pSaveProcessedHitsCmd(NULL), m_pSaveOnlyCoincidenceCmd(NULL),
			m_pApplySmearFactorCmd(NULL), m_pSmearFactorValueScatCmd(NULL), m_pSmearFactorValueAbsCmd(NULL) {
	m_pUIDirectory = new G4UIdirectory(m_strDirectoryName);

	// Command to enable the save to the output file the optical photon hits
	G4String cmd = m_strDirectoryName + m_strSaveOpticalPhotonHits;
	m_pSaveOpticalPhotonHitsCmd = new G4UIcmdWithABool(cmd, this);
	m_pSaveOpticalPhotonHitsCmd->SetGuidance(
			"Enable/Disable save optical photon hits");
	m_pSaveOpticalPhotonHitsCmd->SetParameterName("value", true);
	m_pSaveOpticalPhotonHitsCmd->SetDefaultValue(true);
	m_pSaveOpticalPhotonHitsCmd->AvailableForStates(G4State_Idle);

	// Command to enable the save to the output file the scintillator hits
	cmd = m_strDirectoryName + m_strSaveScintiHits;
	m_pSaveScintiHitsCmd = new G4UIcmdWithABool(cmd, this);
	m_pSaveScintiHitsCmd->SetGuidance("Enable/Disable save scintillator hits");
	m_pSaveScintiHitsCmd->SetParameterName("value", true);
	m_pSaveScintiHitsCmd->SetDefaultValue(true);
	m_pSaveScintiHitsCmd->AvailableForStates(G4State_Idle);

	// Command to enable the save to the output file the processed hits
	cmd = m_strDirectoryName + m_strSaveProcessedHits;
	m_pSaveProcessedHitsCmd = new G4UIcmdWithABool(cmd, this);
	m_pSaveProcessedHitsCmd->SetGuidance("Enable/Disable save processed hits");
	m_pSaveProcessedHitsCmd->SetParameterName("value", true);
	m_pSaveProcessedHitsCmd->SetDefaultValue(true);
	m_pSaveProcessedHitsCmd->AvailableForStates(G4State_Idle);

	// Command to enable the save to the output file the processed hits
	cmd = m_strDirectoryName + m_strSaveOnlyCoincidence;
	m_pSaveOnlyCoincidenceCmd = new G4UIcmdWithAnInteger(cmd, this);
	m_pSaveOnlyCoincidenceCmd->SetGuidance(
					       "Sets the coincidence level, 0 take all, 1, require at least one scinti hit, 2 require a coincidence");
	m_pSaveOnlyCoincidenceCmd->SetParameterName("value", false);
	m_pSaveOnlyCoincidenceCmd->SetDefaultValue(true);
	m_pSaveOnlyCoincidenceCmd->AvailableForStates(G4State_Idle);

	// Command to enable the enable smearing of hit energy
	cmd = m_strDirectoryName + m_strApplySmearFactor;
	m_pApplySmearFactorCmd = new G4UIcmdWithABool(cmd, this);
	m_pApplySmearFactorCmd->SetGuidance(
			"If true apply smearing to scintillator energy deposit");
	m_pApplySmearFactorCmd->SetParameterName("value", false);
	m_pApplySmearFactorCmd->SetDefaultValue(false);
	m_pApplySmearFactorCmd->AvailableForStates(G4State_Idle);

	// Command to set value of energy smear factor - scatter
	cmd = m_strDirectoryName + m_strSmearFactorValueScat;
	m_pSmearFactorValueScatCmd = new G4UIcmdWithADouble(cmd, this);
	m_pSmearFactorValueScatCmd->SetGuidance(
			"Value of smearing to be applied to scintillator energy deposits in scatter detector");
	m_pSmearFactorValueScatCmd->SetParameterName("value", false);
	m_pSmearFactorValueScatCmd->SetDefaultValue(0.10);
	m_pSmearFactorValueScatCmd->AvailableForStates(G4State_Idle);

	// Command to set value of energy smear factor- absorber
	cmd = m_strDirectoryName + m_strSmearFactorValueAbs;
	m_pSmearFactorValueAbsCmd = new G4UIcmdWithADouble(cmd, this);
	m_pSmearFactorValueAbsCmd->SetGuidance(
			"Value of smearing to be applied to scintillator energy deposits in absorber detector");
	m_pSmearFactorValueAbsCmd->SetParameterName("value", false);
	m_pSmearFactorValueAbsCmd->SetDefaultValue(0.10);
	m_pSmearFactorValueAbsCmd->AvailableForStates(G4State_Idle);

}
//-----------------------------------------------------------------------------

CIEventActionMessenger::~CIEventActionMessenger() {
	if (m_pUIDirectory)
		delete m_pUIDirectory;
	if (m_pSaveOpticalPhotonHitsCmd)
		delete m_pSaveOpticalPhotonHitsCmd;
	if (m_pSaveScintiHitsCmd)
		delete m_pSaveScintiHitsCmd;
	if (m_pSaveProcessedHitsCmd)
		delete m_pSaveProcessedHitsCmd;
	if (m_pSaveOnlyCoincidenceCmd)
		delete m_pSaveOnlyCoincidenceCmd;
	if (m_pApplySmearFactorCmd)
		delete m_pApplySmearFactorCmd;
	if (m_pSmearFactorValueScatCmd)
		delete m_pSmearFactorValueScatCmd;
	if (m_pSmearFactorValueAbsCmd)
		delete m_pSmearFactorValueAbsCmd;

}
//-----------------------------------------------------------------------------

void CIEventActionMessenger::SetNewValue(G4UIcommand* pCommand,
		const G4String newValue) {
	if (pCommand == m_pSaveOpticalPhotonHitsCmd) {
		m_pCIEventAction->SetSaveOpticalPhotonHits(
				m_pSaveOpticalPhotonHitsCmd->GetNewBoolValue(newValue));
	} else if (pCommand == m_pSaveScintiHitsCmd) {
		m_pCIEventAction->SetSaveScintiHits(m_pSaveScintiHitsCmd->GetNewBoolValue(
				newValue));
	} else if (pCommand == m_pSaveProcessedHitsCmd) {
		m_pCIEventAction->SetSaveProcessedHits(
				m_pSaveProcessedHitsCmd->GetNewBoolValue(newValue));
	} else if (pCommand == m_pSaveOnlyCoincidenceCmd) {
		m_pCIEventAction->SetSaveOnlyCoincidence(
				m_pSaveOnlyCoincidenceCmd->GetNewIntValue(newValue));
	} else if (pCommand == m_pApplySmearFactorCmd) {
		m_pCIEventAction->SetApplySmear(
				m_pApplySmearFactorCmd->GetNewBoolValue(newValue));
	} else if (pCommand == m_pSmearFactorValueScatCmd) {
		m_pCIEventAction->SetSmearValueScat(
				m_pSmearFactorValueScatCmd->GetNewDoubleValue(newValue));
	} else if (pCommand == m_pSmearFactorValueAbsCmd) {
		m_pCIEventAction->SetSmearValueAbs(
				m_pSmearFactorValueAbsCmd->GetNewDoubleValue(newValue));
	}
}
