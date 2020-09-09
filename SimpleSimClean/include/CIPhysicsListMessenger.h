/***************************************************************************
*   Copyright (C) Minister of Natural Resources Canada 2008.               *
*   hseywerd@nrcan.gc.ca                                                   *
*                                                                          *
***************************************************************************/
/**
 * @file CIPhysicsListMessenger.h
 * @brief Set up control of the physics processes from the user interface.
 * @author Henry Seywerd hseywerd@nrcan.gc.ca
 **/
#ifndef CIPhysicsListMessenger_h
#define CIPhysicsListMessenger_h

#include "G4UImessenger.hh"

/**
 * @class CIPhysicsListMessenger
 * @brief Set up control of the physics processes from the user interface.
 * @author Henry Seywerd <hseywerd@nrcan.gc.ca>
 *
 **/

class CIPhysicsList;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithABool;
class G4UIcmdWithAnInteger;

class CIPhysicsListMessenger: public G4UImessenger
{
  public:
    /**
     * Constructor
     * At some time need to differentiate between G4LECS and the new G4 Low Energy Processes which are to replace G4LECS
     * @param pCIPhysicsList pointer to the CIPhysicsList object which will accept the user commands
    */
    CIPhysicsListMessenger (CIPhysicsList* pCIPhysicsList);

    virtual ~CIPhysicsListMessenger();

    /**
     * Process commands from the macro and invoke the appropriate response in CIPhysicsList
     * @param pCommand the command
     * @param newValue the value provided with the command
     */
    virtual void SetNewValue (G4UIcommand* pCommand, const G4String newValue);

  private:
    /// Pointer to the CIPhysicsList whose status is to be set
    CIPhysicsList*       m_pCIPhysicsList;
    /// The directory in which this set of commands is maintained
    G4UIdirectory*       m_pUIDirectory;
    /// String giving the directory name
    static const G4String m_strDirectoryName;
    /// Command to set up optical processes.
    G4UIcmdWithABool*  m_pOpticalProcessesCmd;
    /// Command to use G4LECS low energy photon processes rather than standard Geant
    G4UIcmdWithABool*  m_pG4LECSCmd;
    /// String to define command for optical processes
    static const G4String m_strOpticalProcessCmd;
    ///String to define help for optical processes
    static const G4String m_strOpticalProcessGuidance;
    /// String to define command for G4LECS
    static const G4String m_strG4LECScmd;
    ///String to define help for G4LECS
    static const G4String m_strG4LECSGuidance;
    /// Command to define which package to use for low energy processes.

};

#endif
