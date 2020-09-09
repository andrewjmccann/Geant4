/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.              *
 *   hseywerd@nrcan.gc.ca                                                  *
 *                                                                         *
 ***************************************************************************/

/**
 * @file CIRunAction.h
 * @brief
 **/
#ifndef CIRunAction_h
#define CIRunAction_h

#include "G4UserRunAction.hh"
#include "G4String.hh"
#include "CLHEP/Random/Randomize.h"

class TFile;
class TTree;
class TH1F;
class TH2F;
class G4Event;
class CIRootRunHeader;
class CIRunActionMessenger;
class CIEventAction;

/**
 * @class CIRunAction
 *
 * @brief Defines the user's action at the beginning and the end of each run.
 *
 * @author Henry Seywerd <hseywerd@nrcan.gc.ca>
*/
class CIRunAction : public G4UserRunAction
{
	friend class CIEventAction;
  public:
    CIRunAction();

    ~CIRunAction();

    /**
     * Invoked at the beginning of each run
     * @param aRun pointer to the run which is starting
     */
    virtual void BeginOfRunAction (const G4Run* aRun);

    /**
     * Invoked at the end of each run
     * @param aRun pointer to the run which is ending
     */
    virtual void EndOfRunAction (const G4Run* aRun);

    /**
     * Set whether root output files are to be generated
     * @param flag if true, then generate the file.
     */
    inline void SetRootOutput(const G4bool flag) {m_bEnableRootOutput = flag;};
    /**
     * Returns whether root output is generated
     * @return if true root output is generated.
     */
    inline G4bool GetRootOutput(void) const {return m_bEnableRootOutput;};


    /**
     * Sets the name of the file for the Root output file
     * @param fileName Name to set the file to
     */
    void SetRootFileName (const G4String fileName) {m_strRootFileName = fileName;};
    /**
     * @return Returns the file name of the current Root output file
     */
    inline G4String GetRootFileName() const {return m_strRootFileName;};

    /**
     * Set whether ASCII output files are to be generated
     * @param flag if true, then generate the file.
     */
    inline void SetASCIIOutput(const G4bool flag) {m_bEnableASCIIOutput = flag;};
    /**
     * Returns whether ASCII output is generated
     * @return if true ASCII output is generated.
     */
    inline G4bool GetASCIIOutput(void) const {return m_bEnableASCIIOutput;};

    /**
     * Sets the name of the file for the ASCII output file
     * @param fileName Name to set the file to
     */
    void SetASCIIFileName (const G4String fileName) {m_strASCIIFileName = fileName;};
    /**
     * @return Returns the file name of the current ASCII output file
     */
    inline G4String GetASCIIFileName() const {return m_strASCIIFileName;};

    /**
     * @return Returns a pointer to the Root tree of event information
     */
    inline TTree* GetROOTEventInfoTree() {return m_pROOTEventInfoTree;};

    /**
     * Specify if this run generates its own new output file
     * @param bFileForEachRun
     */
    inline void SetNewFileForThisRun(const bool bNewFileForThisRun) {m_bNewFileForThisRun = bNewFileForThisRun;}

    inline void SetSeed(const int iSeed) {m_RandomSeed = iSeed;  CLHEP::HepRandom::setTheSeed(iSeed);};

  private:

    /// Pointer to the UI messenger for RunAction information
    CIRunActionMessenger* m_pCIRunActionMessenger;


    /// The current run number
    G4int m_iRunNumber;
    /// Indicates which of the multiple processes this instance refers to
    G4int m_iMPIProcessNumber;

    G4int m_RandomSeed;

    /// If true enable output to Root file
    G4bool m_bEnableRootOutput;
    /// The file name for root output
    G4String m_strRootFileName;
    /// The root output file
    TFile* m_pROOTOutputFile;
    /// Tree of root objects for run specific data
    TTree* m_pROOTRunInfoTree;
    /// Run Header info for storing within root
    CIRootRunHeader* m_pCIRootRunHeader;
    /// Event information info for storing within root
    TTree* m_pROOTEventInfoTree;
    /// Specify if this run has its own separate output file
    bool m_bNewFileForThisRun;
    /// If true we close the output files at the end of this run.
    bool m_bCloseFilesWhenFinished;

    /// If true enable output to ASCII file
    G4bool m_bEnableASCIIOutput;
    /// Filename for ASCII output file
    G4String m_strASCIIFileName;

    // Some histograms accessible from CIEventAction
    /// Histogram for event primary vertex X
    TH1F* m_HEventPrimX;
    /// Histogram for event primary vertex X
    TH1F* m_HEventPrimY;
    /// Histogram for event primary vertex X
    TH1F* m_HEventPrimZ;
    /// Histogram Beam energy for each event
    TH1F* m_HEventBeamE;
    /// Incomming gamma distribution in the XY plane at the origin.
    TH2F* m_HEventBeamXY;
    /// Incomming gamma distribution in the ZY plane at the origin.
    TH2F* m_HEventBeamZY;

    // Same but related to optical hits
    /// Histogram for optical hit energy (scatter det)
    TH1F* m_HOpHitScatE;
    /// Histogram for optical hit energy (absorber det)
    TH1F* m_HOpHitAbsE;
    /// Histogram for optical hit time (scatter det)
    TH1F* m_HOpHitScatT;
    /// Histogram for optical hit time (absorber det)
    TH1F* m_HOpHitAbsT;
    /// Histogram for optical photon path length for those photons created in the scatter det
    TH1F* m_HOpHitScatL;
    /// Histogram for optical photon path length for those photons created in the absorber det
    TH1F* m_HOpHitAbsL;
    /// Histogram for optical photon hit multiplicity for those photons created in the scatter det
    TH1F* m_HOpHitScatMult;
    /// Histogram for optical photon hit multiplicity for those photons created in the abs det
    TH1F* m_HOpHitAbsMult;
    /// Histogram for optical photon multiplicity for those photons created in the scatter det, optical photons created vs those creating hits
    TH1F* m_HOpScatMult;
    /// Histogram for optical photon multiplicity for those photons created in the abs det, optical photons created vs those creating hits
    TH1F* m_HOpAbsMult;

    /**
     * Fill the run header information
     * @param theRun the current run
     */
    void FillRunHeader(const G4Run* theRun);


    /**
     * Create the output histogram file name for MPI running
     *
     * Does nothing if compiled without MPI
     */
    void SetOutputFileName();

    /**
     * Book the standard histograms
     */
    void BookHistograms();


    /**
     * Save the standard histograms to file
     */
    void SaveHistograms();

    /**
     * Clean up the standard histograms (deletions etc).
     */
    void CleanUpHistograms();

};

#endif
