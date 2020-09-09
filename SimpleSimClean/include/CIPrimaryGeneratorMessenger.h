/***************************************************************************
*   Copyright (C) Minister of Natural Resources Canada 2008.               *
*   hseywerd@nrcan.gc.ca                                                   *
*                                                                          *
***************************************************************************/
/**
 * @file CIPrimaryGeneratorMessenger.h
 * @brief Provide for user options to the Primary Generator - generator of initial gammas
 * @author Henry Seywerd hseywerd@nrcan.gc.ca
 **/
#ifndef CIPrimaryGeneratorMessenger_h
#define CIPrimaryGeneratorMessenger_h

#include "G4UImessenger.hh"

class CIPrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithABool;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADouble;

/**
 * @class CIPrimaryGeneratorMessenger
 * @brief Provide for user options to the Primary Generator - generator of initial gammas
 * @author Henry Seywerd <hseywerd@nrcan.gc.ca>
 *
 **/
class CIPrimaryGeneratorMessenger : public G4UImessenger
{
  public:
    /**
     * Constructor
    * @param pCIPrimaryGenerator pointer to the CIPrimaryGenerator object which will accept the user commands
     */
    CIPrimaryGeneratorMessenger (CIPrimaryGeneratorAction* pCIPrimaryGenerator);

    ~CIPrimaryGeneratorMessenger();
    /**
     * Process commands from the macro and invoke the appropriate response in CIPrimaryGenerator
     * @param pCommand the command
     * @param newValue the value provided with the command
     */
    virtual void SetNewValue (G4UIcommand* pCommand, const G4String newValue);


  private:
    /// Pointer to the CIPrimaryGenerator whose status is to be set
    CIPrimaryGeneratorAction*          m_pCIPrimaryGenerator;
    /// The directory in which this set of commands is maintained
    G4UIdirectory*    m_pUIDirectory;
    /// String giving the directory name
    static const G4String m_strDirectoryName;
    /// String giving the command name for the incomming gamma energy
    static const G4String m_strGammaEnergyName;
    /// String giving the command name for enabling generation of NORM
    static const G4String m_strNORMName;
    /// String giving command name for enabling point source generation
    static const G4String m_strGenGPSName;
    /// Command to set the energy of the initial gammas
    G4UIcmdWithADouble*   m_pGammaEnergyCmd;
    /// Command to enable generation of NORM
    G4UIcmdWithABool*     m_pGenerateNORMCmd;
    /// Command to enable genration via point source
    G4UIcmdWithABool*     m_pGenerateGPSCmd;
};

#endif
