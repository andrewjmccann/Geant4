/***************************************************************************
*   Copyright (C) Minister of Natural Resources Canada 2008.               *
*   hseywerd@nrcan.gc.ca                                                   *
*                                                                          *
***************************************************************************/
/**
 * @file CIRunActionMessenger.cpp
 * @brief Provide for user options to the Run setup
 * @author Henry Seywerd hseywerd@nrcan.gc.ca
 **/

#include "CIRunActionMessenger.h"
#include "CIRunAction.h"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithABool.hh"

const G4String CIRunActionMessenger::m_strDirectoryName ("/ComptonImager/RunAction/");
const G4String CIRunActionMessenger::m_strEnableRootOutput("EnableRootOutput");
const G4String CIRunActionMessenger::m_strRootOutputFile("RootOutputFile");
const G4String CIRunActionMessenger::m_strEnableASCIIOutput("EnableASCIIOutput");
const G4String CIRunActionMessenger::m_strASCIIOutputFile("ASCIIOutputFile");
const G4String CIRunActionMessenger::m_strOpenNewFileForRun("OpenNewFileForRun");
const G4String CIRunActionMessenger::m_strSetSeed("SetSeed");



CIRunActionMessenger::CIRunActionMessenger (CIRunAction* pCIRunAction) : m_pCIRunAction (pCIRunAction),  m_pUIDirectory (NULL)
{
  m_pUIDirectory = new G4UIdirectory (m_strDirectoryName);

  // Enable root file output
  G4String cmd = m_strDirectoryName + m_strEnableRootOutput;
  m_pRootOutputEnableCmd = new G4UIcmdWithABool (cmd, this);
  m_pRootOutputEnableCmd->SetGuidance ("Write output to a root format file");
  m_pRootOutputEnableCmd->SetParameterName ("value", true);
  m_pRootOutputEnableCmd->SetDefaultValue(pCIRunAction->GetRootOutput());
  m_pRootOutputEnableCmd->AvailableForStates (G4State_Idle);

  // File name for root output
  cmd = m_strDirectoryName + m_strRootOutputFile;
  m_pRootOutputFileCmd = new G4UIcmdWithAString (cmd, this);
  m_pRootOutputFileCmd->SetGuidance ("Set name of the root output file");
  // Default name is the current name as given by the RunAction object
  m_pRootOutputFileCmd->SetDefaultValue (pCIRunAction->GetRootFileName());
  m_pRootOutputFileCmd->AvailableForStates (G4State_Idle);

  // Enable ASCII file output
  cmd = m_strDirectoryName + m_strEnableASCIIOutput;
  m_pASCIIOutputEnableCmd = new G4UIcmdWithABool (cmd, this);
  m_pASCIIOutputEnableCmd->SetGuidance ("Write output to a ASCII format file");
  m_pASCIIOutputEnableCmd->SetParameterName ("value", true);
  m_pASCIIOutputEnableCmd->SetDefaultValue(pCIRunAction->GetASCIIOutput());
  m_pASCIIOutputEnableCmd->AvailableForStates (G4State_Idle);

  // File name for ASCII output
  cmd = m_strDirectoryName + m_strASCIIOutputFile;
  m_pASCIIOutputFileCmd = new G4UIcmdWithAString (cmd, this);
  m_pASCIIOutputFileCmd->SetGuidance ("Set name of the ASCII output file");
  // Default name is the current name as given by the RunAction object
  m_pASCIIOutputFileCmd->SetDefaultValue (pCIRunAction->GetASCIIFileName());
  m_pASCIIOutputFileCmd->AvailableForStates (G4State_Idle);

  // Does each run create its own output histogram file
  cmd = m_strDirectoryName + m_strOpenNewFileForRun;
  m_pOpenNewFileForRunCmd = new G4UIcmdWithABool (cmd, this);
  m_pOpenNewFileForRunCmd->SetGuidance ("If true run creates its own histogram file");
  // Default is false
  m_pOpenNewFileForRunCmd->SetDefaultValue (false);
  m_pOpenNewFileForRunCmd->AvailableForStates (G4State_Idle);

  // Set the seed
  cmd = m_strDirectoryName + m_strSetSeed;
  m_pSetSeedCmd = new G4UIcmdWithAnInteger(cmd, this);
  m_pSetSeedCmd->SetGuidance ("Set random seed for this run");
  // Default is false
  m_pSetSeedCmd->SetDefaultValue (false);
  m_pSetSeedCmd->AvailableForStates (G4State_Idle);

}
//-----------------------------------------------------------------------------
CIRunActionMessenger::~CIRunActionMessenger()
{
  if (m_pUIDirectory) delete m_pUIDirectory;
  if (m_pRootOutputEnableCmd) delete m_pRootOutputEnableCmd;
  if (m_pRootOutputFileCmd) delete m_pRootOutputFileCmd;
  if (m_pASCIIOutputEnableCmd) delete m_pASCIIOutputEnableCmd;
  if (m_pASCIIOutputFileCmd) delete m_pASCIIOutputFileCmd;
  if (m_pOpenNewFileForRunCmd) delete m_pOpenNewFileForRunCmd;
  if (m_pSetSeedCmd) delete m_pSetSeedCmd;

}
//-----------------------------------------------------------------------------


void CIRunActionMessenger::SetNewValue (G4UIcommand* pCommand, const G4String newValue)
{
  if (pCommand == m_pRootOutputEnableCmd) {
		m_pCIRunAction->SetRootOutput(G4UIcmdWithABool::GetNewBoolValue(newValue));
	} else if (pCommand == m_pRootOutputFileCmd) {
		m_pCIRunAction->SetRootFileName(newValue);
	} else if (pCommand == m_pASCIIOutputEnableCmd) {
		m_pCIRunAction->SetASCIIOutput(G4UIcmdWithABool::GetNewBoolValue(newValue));
	} else if (pCommand == m_pASCIIOutputFileCmd) {
		m_pCIRunAction->SetASCIIFileName(newValue);
	} else if (pCommand == m_pOpenNewFileForRunCmd) {
		m_pCIRunAction->SetNewFileForThisRun(G4UIcmdWithABool::GetNewBoolValue(newValue));
	} else	if (pCommand == m_pSetSeedCmd) {
		m_pCIRunAction->SetSeed (G4UIcmdWithAnInteger::GetNewIntValue(newValue));
	}

}


