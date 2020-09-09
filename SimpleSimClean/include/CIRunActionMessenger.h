/***************************************************************************
*   Copyright (C) Minister of Natural Resources Canada 2008.               *
*   hseywerd@nrcan.gc.ca                                                   *
*                                                                          *
***************************************************************************/
/**
 * @file CIRunActionMessenger.h
 * @brief Provide for user options to the Run setup
 * @author Henry Seywerd hseywerd@nrcan.gc.ca
 **/
#ifndef CIRunActionMessenger_h
#define CIRunActionMessenger_h

#include "G4UImessenger.hh"

class CIRunAction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithABool;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADouble;
class G4UIcmdWithAnInteger;

/**
 * @class CIRunActionMessenger
 * @brief Provide for user options to the Run setup
 * @author Henry Seywerd <hseywerd@nrcan.gc.ca>
 *
 **/
class CIRunActionMessenger : public G4UImessenger
{
  public:
    /**
     * Constructor
    * @param pCIRunAction pointer to the CIRunAction object which will accept the user commands
     */
    CIRunActionMessenger (CIRunAction* pCIRunAction);

    ~CIRunActionMessenger();
    /**
     * Process commands from the macro and invoke the appropriate response in CIRunAction
     * @param pCommand the command
     * @param newValue the value provided with the command
     */
    virtual void SetNewValue (G4UIcommand* pCommand, const G4String newValue);



  private:
    /// Pointer to the CIRunAction whose status is to be set
    CIRunAction*          m_pCIRunAction;
    /// The directory in which this set of commands is maintained
    G4UIdirectory*        m_pUIDirectory;
    /// String giving the directory name
    static const G4String m_strDirectoryName;
    /// String giving the name of the command to enable root file output
    static const G4String m_strEnableRootOutput;
    /// String giving the name of the command to specify the root output file name
    static const G4String m_strRootOutputFile;
    /// String giving the command to enable ASCII file output
    static const G4String m_strEnableASCIIOutput;
    /// String giving the name of the command to specify the ASCII output file name
    static const G4String m_strASCIIOutputFile;
    /// String giving the name of the command to specify whether each run creates its own histogram file
    static const G4String m_strOpenNewFileForRun;
    static const G4String m_strSetSeed;

    /// Command to enable the writing of data in root file format
    G4UIcmdWithABool*     m_pRootOutputEnableCmd;
    /// Command to set the name of the output root data file
    G4UIcmdWithAString*   m_pRootOutputFileCmd;
    /// Command to enable the writing of data in ASCII file format
    G4UIcmdWithABool*     m_pASCIIOutputEnableCmd;
    /// Command to set the name of the output ASCII data file
    G4UIcmdWithAString*   m_pASCIIOutputFileCmd;
    /// Command to specify whether each run creates its own histogram file
    G4UIcmdWithABool*   m_pOpenNewFileForRunCmd;
    /// Set Random Seeds
    G4UIcmdWithAnInteger*   m_pSetSeedCmd;

};

#endif
