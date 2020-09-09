/***************************************************************************
*   Copyright (C) Minister of Natural Resources Canada 2008.               *
*   hseywerd@nrcan.gc.ca                                                   *
*                                                                          *
***************************************************************************/
/**
 * @file CIPrimaryGeneratorMessenger.cpp
 * @brief Provide for user options to the Primary Generator - generator of initial gammas
 * @author Henry Seywerd hseywerd@nrcan.gc.ca
 **/
#
#include "CIPrimaryGeneratorMessenger.h"
#include "CIPrimaryGeneratorAction.h"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithAnInteger.hh"

const G4String CIPrimaryGeneratorMessenger::m_strDirectoryName ("/ComptonImager/PrimaryGenerator/");
const G4String CIPrimaryGeneratorMessenger::m_strGammaEnergyName ("GammaEnergy");
const G4String CIPrimaryGeneratorMessenger::m_strNORMName ("GenerateNORM");
const G4String CIPrimaryGeneratorMessenger::m_strGenGPSName("GenerateByGPS");

CIPrimaryGeneratorMessenger::CIPrimaryGeneratorMessenger(CIPrimaryGeneratorAction* pCIPrimaryGenerator) :
	m_pCIPrimaryGenerator(pCIPrimaryGenerator), m_pUIDirectory(NULL), m_pGammaEnergyCmd(NULL),
	m_pGenerateNORMCmd (NULL), m_pGenerateGPSCmd(NULL)
{
  m_pUIDirectory = new G4UIdirectory (m_strDirectoryName);

  //To set the energy of the incomming gamma
  const G4String cmdGammaEnergy = m_strDirectoryName + m_strGammaEnergyName;
  m_pGammaEnergyCmd = new G4UIcmdWithADouble (cmdGammaEnergy, this);
  m_pGammaEnergyCmd->SetGuidance ("Set energy of initial gamma (keV)");
  m_pGammaEnergyCmd->SetParameterName ("value", true);
  m_pGammaEnergyCmd->SetDefaultValue (662.0);
  m_pGammaEnergyCmd->AvailableForStates (G4State_Idle);

  //To enable the generation of Naturally Occuring Radioactive Material Background distributions
  const G4String cmdNORM = m_strDirectoryName + m_strNORMName;
  m_pGenerateNORMCmd = new G4UIcmdWithABool (cmdNORM, this);
  m_pGenerateNORMCmd->SetGuidance ("Enable/Disable the generation of NORM background");
  m_pGenerateNORMCmd->SetParameterName ("value", true);
  m_pGenerateNORMCmd->SetDefaultValue (false);
  m_pGenerateNORMCmd->AvailableForStates (G4State_Idle);

  //To enable the generation of gamma from G4ParticleGun or point source using G4GPS
  const G4String cmdGenGPS = m_strDirectoryName + m_strGenGPSName;
  m_pGenerateGPSCmd = new G4UIcmdWithABool (cmdGenGPS, this);
  m_pGenerateGPSCmd->SetGuidance ("Enable/Disable the generation of primary gamma via G4GPS point source");
  m_pGenerateGPSCmd->SetParameterName ("value", true);
  m_pGenerateGPSCmd->SetDefaultValue (false);
  m_pGenerateGPSCmd->AvailableForStates (G4State_PreInit);
}
//-----------------------------------------------------------------------------

CIPrimaryGeneratorMessenger::~CIPrimaryGeneratorMessenger()
{
  if (m_pUIDirectory) delete m_pUIDirectory;
  if (m_pGammaEnergyCmd) delete m_pGammaEnergyCmd;
  if (m_pGenerateNORMCmd) delete m_pGenerateNORMCmd;
  if (m_pGenerateGPSCmd) delete m_pGenerateGPSCmd;

}
//-----------------------------------------------------------------------------

void CIPrimaryGeneratorMessenger::SetNewValue (G4UIcommand* pCommand, const G4String newValue)
{
  if (pCommand == m_pGammaEnergyCmd)
  {
    m_pCIPrimaryGenerator->SetPrimaryEnergy (m_pGammaEnergyCmd->GetNewDoubleValue (newValue));
  }
  else if (pCommand == m_pGenerateNORMCmd)
  {
    m_pCIPrimaryGenerator->SetNORMGeneration (m_pGenerateNORMCmd->GetNewBoolValue (newValue));
  }
  else if (pCommand == m_pGenerateGPSCmd)
  {
    m_pCIPrimaryGenerator->SetG4GPSPointSourceGeneration (m_pGenerateGPSCmd->GetNewBoolValue (newValue));
  }
}



