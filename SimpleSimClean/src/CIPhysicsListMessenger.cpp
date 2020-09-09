/***************************************************************************
*   Copyright (C) Minister of Natural Resources Canada 2008.               *
*   hseywerd@nrcan.gc.ca                                                   *
*                                                                          *
***************************************************************************/
/**
 * @file CIPhysicsListMessenger.cpp
 * @brief Set up control of the physics processes from the user interface.
 * @author Henry Seywerd hseywerd@nrcan.gc.ca
 **/
#include "CIPhysicsListMessenger.h"
#include "CIPhysicsList.h"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAnInteger.hh"


const G4String CIPhysicsListMessenger::m_strDirectoryName ("/ComptonImager/PhysicsList/");
const G4String CIPhysicsListMessenger::m_strOpticalProcessCmd ("OpticalProcesses");
const G4String CIPhysicsListMessenger::m_strOpticalProcessGuidance ("Select which optical processes to model");
const G4String CIPhysicsListMessenger::m_strG4LECScmd ("G4LECS");
const G4String CIPhysicsListMessenger::m_strG4LECSGuidance ("If true selects G4LECS package, otherwise the standard Geant package for low energy electromagnetic interactions");


CIPhysicsListMessenger::CIPhysicsListMessenger (CIPhysicsList* pCIPhysicsList)
    :  m_pCIPhysicsList (pCIPhysicsList), m_pUIDirectory (NULL), m_pOpticalProcessesCmd (NULL), m_pG4LECSCmd (NULL)
{
  m_pUIDirectory = new G4UIdirectory (m_strDirectoryName);

  // Optical Photon processes
  G4String cmd = m_strDirectoryName + m_strOpticalProcessCmd;
  m_pOpticalProcessesCmd = new G4UIcmdWithABool (cmd, this);
  m_pOpticalProcessesCmd->SetGuidance (m_strOpticalProcessGuidance);
  m_pOpticalProcessesCmd->SetParameterName ("choice", false);
  m_pOpticalProcessesCmd->AvailableForStates (G4State_PreInit);

  // Low energy electromagnetic processes via G4LECS package
  cmd = m_strDirectoryName + m_strG4LECScmd;
  m_pG4LECSCmd = new G4UIcmdWithABool (cmd, this);
  m_pG4LECSCmd->SetGuidance (m_strG4LECSGuidance);
  m_pG4LECSCmd->SetParameterName ("choice", false);
  m_pG4LECSCmd->AvailableForStates (G4State_PreInit);


}
//-----------------------------------------------------------------------------


CIPhysicsListMessenger::~CIPhysicsListMessenger()
{
  if (m_pUIDirectory) delete m_pUIDirectory;
  if (m_pOpticalProcessesCmd) delete m_pOpticalProcessesCmd;
  if (m_pG4LECSCmd) delete m_pG4LECSCmd;
}
//-----------------------------------------------------------------------------


void CIPhysicsListMessenger::SetNewValue (G4UIcommand* pCommand, const G4String newValue)
{
  if (pCommand == m_pOpticalProcessesCmd)
  {
    m_pCIPhysicsList->SetOpticalProcesses (m_pOpticalProcessesCmd->GetNewBoolValue (newValue));
  }
  else if (pCommand == m_pG4LECSCmd)
  {
    m_pCIPhysicsList->SetG4LECS (m_pG4LECSCmd->GetNewBoolValue (newValue));
  }
}
