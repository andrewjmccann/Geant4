/***************************************************************************
*   Copyright (C) Minister of Natural Resources Canada 2009.               *
*   hseywerd@nrcan.gc.ca                                                   *
*                                                                          *
***************************************************************************/
/**
 * @file CIEventActionMessenger.h
 * @brief Provide for user options to the per event processing
 * @author Henry Seywerd hseywerd@nrcan.gc.ca
 **/
#ifndef CIEventActionMessenger_h
#define CIEventActionMessenger_h

#include "G4UImessenger.hh"

class CIEventAction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithABool;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADouble;

/**
 * @class CIEventActionMessenger
 * @brief Provide for user options to the per event processing
 * @author Henry Seywerd <hseywerd@nrcan.gc.ca>
 *
 **/
class CIEventActionMessenger : public G4UImessenger
{
  public:
    /**
     * Constructor
    * @param pCIEventAction pointer to the CIEventAction object which will accept the user commands
     */
    CIEventActionMessenger (CIEventAction* pCIEventAction);

    ~CIEventActionMessenger();
    /**
     * Process commands from the macro and invoke the appropriate response in the instance of CIEventAction
     * @param pCommand the command
     * @param newValue the value provided with the command
     */
    virtual void SetNewValue (G4UIcommand* pCommand, const G4String newValue);



  private:
    /// Pointer to the CIEventAction whose status is to be set
    CIEventAction*        m_pCIEventAction;
    /// The directory in which this set of commands is maintained
    G4UIdirectory*        m_pUIDirectory;
    /// String giving the directory name
    static const G4String m_strDirectoryName;
    /// String giving the command name to save optical photon hits
    static const G4String m_strSaveOpticalPhotonHits;
    /// String giving the command name to save Scinti hits
    static const G4String m_strSaveScintiHits;
    /// String giving the command name to save processed hits
    static const G4String m_strSaveProcessedHits;
    /// String giving the command name to save only event data where there have been at least two cells hit
    static const G4String m_strSaveOnlyCoincidence;
    /// String giving the command name to apply smearing to the scintillator hit energies
    static const G4String m_strApplySmearFactor;
    /// String giving the command name to define the smear factor constant - scatter detector
    static const G4String m_strSmearFactorValueScat;
    /// String giving the command name to define the smear factor constant - absorber detector
    static const G4String m_strSmearFactorValueAbs;

    /// Command to enable/disable output of optical photon hits
    G4UIcmdWithABool*     m_pSaveOpticalPhotonHitsCmd;
    /// Command to enable/disable output of hits in the scintillator
    G4UIcmdWithABool*     m_pSaveScintiHitsCmd;
    /// Command to enable/disable output of processed hits, i.e. after optical photons have been turned into a signal
    G4UIcmdWithABool*     m_pSaveProcessedHitsCmd;
    /// Command to enable/disable save only event data where there have been at least two cells hit:
    /// Sets the coincidence level, 0 take all, 1, require at least one scinti hit, 2 require a coincidence
    G4UIcmdWithAnInteger*     m_pSaveOnlyCoincidenceCmd;
    /// Command set a enable application of a smear factor
    G4UIcmdWithABool*     m_pApplySmearFactorCmd;
    /// Command set a smearing factor  - scatter detector
    G4UIcmdWithADouble*   m_pSmearFactorValueScatCmd;
    /// Command set a smearing factor  - absorber detector
    G4UIcmdWithADouble*   m_pSmearFactorValueAbsCmd;
};

#endif
