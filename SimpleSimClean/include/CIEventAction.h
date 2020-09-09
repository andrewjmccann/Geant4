/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2009.              *
 *   hseywerd@nrcan.gc.ca                                                  *
 *                                                                         *
 ***************************************************************************/

/**
 * @file CIEventAction.h
 * @brief Pre/post event processing
 **/
#ifndef CIEventAction_h
#define CIEventAction_h
#include "G4UserEventAction.hh"
#include "CIOutputEvent.h"

class CIEventActionMessenger;
class CISensitiveScintiDetector;
class CISensitiveOpticalDetector;
class CISensitiveMaterials;
class CIModuleTable;
class CIRunAction;

class TFile;
class TTree;
class CIOutputEvent;

#include <fstream>


/**
 * @class CIEventAction
 * @brief Action class for event managment
 *
 * Provides ability to do things to the events before and after processing
 *
 * @author Henry Seywerd <hseywerd@nrcan.gc.ca>
*/
class CIEventAction : public G4UserEventAction
{
  public:
    /**
     * Get pointers to the hit collections
     * Initialize histograms
     */
    CIEventAction();

    /**
     * Save histograms to root file
     */
    ~CIEventAction();

    /**
     * @brief Invoked at the beginning of the processing of the event.
     *
     * The primary vertexes/particles have already been made by the primary generator.
     * In case the user wants to do something before generating
     * primaries (i.e., store random number status), do it in  the G4VUserPrimaryGeneratorAction concrete class.
     * @param  pEvt Pointer to the event
     */
    void BeginOfEventAction (const G4Event* pEvt) ;

    /**
     * @brief Invoked at the end of the processing of the event.
     * @param pEvt Pointer to the event
     */
    void EndOfEventAction (const G4Event* pEvt);

    /**
     * Set up to write out root trees and ASCII data files
     *
     * Root file output is enabled from the card /ComptonImager/RunAction/EnableRootOutput (default true) and is given a name
     * taken from the card /ComptonImager/RunAction/RootOutputFile.
     *
     * ASCII file output is enabled from the card /ComptonImager/RunAction/EnableASCIIOutput (default false) and is given a name
     * taken from the card /ComptonImager/RunAction/ASCIIOutputFile. Two files are generated NPHOTON.name and SCINIT.name, where
     * where name is taken from the card.
     */
    void PrepareOutput();

    /**
     * Save the root data trees to file, and close ASCII files as applicable
     */
    void CloseOutput();

    /**
     * Sets the pointer to the sensitive detector for scintillation hits
     * @param pSensitiveScintiDetector pointer to the sensitive detector
     */
    void SetScintiSDetector (CISensitiveScintiDetector* pSensitiveScintiDetector) { m_pCISensitiveScintiDetector = pSensitiveScintiDetector;}

    /**
     * Sets the pointer to the sensitive detector for optical photons hits
     * @param pSensitiveOpticalDetector pointer to the sensitive detector
     */
    void SetOpticalSDetector (CISensitiveOpticalDetector* pSensitiveOpticalDetector) { m_pCISensitiveOpticalDetector = pSensitiveOpticalDetector;}


    /**
      * Sets the pointer to the sensitive detector for optical photons hits
      * @param pSensitiveOpticalDetector pointer to the sensitive detector
      */
     void SetSensitiveMaterials (CISensitiveMaterials* pCISensitiveMaterials) { m_pCISensitiveMaterials = pCISensitiveMaterials;}

    inline void SetSaveOpticalPhotonHits (const bool flag) { m_bSaveOpticalPhotonHits = flag;}
    inline void SetSaveScintiHits (const bool flag)        { m_bSaveScintiHits = flag;}
    inline void SetSaveProcessedHits (const bool flag)     { m_bSaveProcessedHits = flag;}
    inline void SetSaveOnlyCoincidence (const int iVal)    { m_iSaveOnlyCoincidence = iVal;}
    inline void SetApplySmear (const bool flag)            { m_bApplySmear = flag;}
    inline void SetSmearValueScat (const double value)     { m_dSmearFactorScat = value;}
    inline void SetSmearValueAbs (const double value)      { m_dSmearFactorAbs = value;}

    /**
     * Summarize run statistics
     */
    void SummarizeRun();

  private:

    /**
     * Generate some basic statistics/histograms about the event
     * @param pEvt pointer to the event to be processed
     */
    void CheckEvent(const G4Event* pEvt);


  	/**
  	 * Determine if this is a coincidence event, and return the total number of scintillator hits
  	 * @return returns true if at least two cells have hits
  	 */
  	bool IsCoincidenceEvent();

  	/**
  	 * Determine the number of Compton scatters in this event (from truth data)
  	 * @return
  	 */
  	int GetNumComptons();

  	/**
  	 * Save scintillator hits to the root file
  	 */
  	void SaveScintiHits();

  	/**
  	 * Save optical photon hits to root file
  	 */
  	void SaveOptiHits();

  	/**
  	 * Plot optical photon hit information
  	 */
  	void PlotOptiHits(const G4Event* pEvt);

  	/**
  	 * Save hit cells
  	 *
  	 * For each cell sum all hit information for the cell
  	 * If the flag m_bApplySmear is set also smear the data and save it too
  	 */
  	void SaveCellSummedData();

  	/**
  	 * Save hit cells, based on optical hits
  	 *
  	 * For each cell sum all optical hit information for the cell
  	 */
  	void SaveCellSummedOptiData();

  	/**
  	 * Save material hits to trace energy losses prior to the interaction in the scintillator
  	 *
  	 */
  	void SaveMaterialHits();

  	/**
  	 * Smear the input value by a gaussian with width given by sqrt of the value of x multiplied by smearFactor
  	 * @param x value to be smeared
  	 * @param smearFactor widen by this value of the gaussian
  	 * @return the smeared value
  	 */
  	double GaussianSmear(const double x, const double smearFactor) const;

  	/**
  	 * Save summed data into an ascii format file, i.e. not ROOT file
  	 * @param eventID The event indentifier
  	 */
  	void SaveASCIISummedData(const int eventID);

  	/**
  	 * Save scintillatio hit data into an ascii format file, i.e. not ROOT file
  	 * @param eventID The event indentifier
  	 */
  	void SaveASCIIScinData(const int eventID);

  	/**
  	 * Determine the number of scintillator cells with hits
  	 * @return The number of cells hit
  	 */
  	int CheckNCellsHit();

    /// Provide access to the RunAction for various data saving information
    CIRunAction* m_pCIRunAction;

    /// User interface handler
    CIEventActionMessenger* m_pCIEventActionMessenger;

    /// Tree of root objects for event specific data, obtained from CIRunAction
    TTree* m_pROOTEventInfoTree;
    /// Pointer to the object containing information on the event to be stored
    CIOutputEvent* m_pCIOutputEvent;

    /// The sensitive detector for scintillation hits
    CISensitiveScintiDetector* m_pCISensitiveScintiDetector;
    /// The sensitive detector for optical photons hits
    CISensitiveOpticalDetector* m_pCISensitiveOpticalDetector;
    /// The sensitive detector for hits in materials
    CISensitiveMaterials* m_pCISensitiveMaterials;

    /// If true save optical photon hits to the root output file
    bool m_bSaveOpticalPhotonHits;
    /// If true save scinitllator hits to the root output file
    bool m_bSaveScintiHits;
    /// If true save processed hits to the root output file
    bool m_bSaveProcessedHits;
    /// Sets the coincidence level, 0 take all, 1, require at least one scinti hit, 2 require a coincidence
    int m_iSaveOnlyCoincidence;
    /// If true apply smearing to scintillator hits
    bool m_bApplySmear;
    /// Value of the smear factor to be applied - scatter detector
    double m_dSmearFactorScat;
    /// Value of the smear factor to be applied - absorber detector
    double m_dSmearFactorAbs;
    /// Table of module name, ID number correspondences
    CIModuleTable* m_pModuleTable;

    /// If true enable output to Root file
    G4bool m_bEnableRootOutput;
    /// If true enable output to ASCII file
    G4bool m_bEnableASCIIOutput;
    /// Filename for ASCII output file
    G4String m_strASCIIFileName;
    /// Output ASCII file for summed hit information
    std::ofstream m_PhotonFile;
    /// Output ASCII file for scinti hit information
    std::ofstream m_ScintiFile;


    G4int m_iNTraj;
};

#endif
