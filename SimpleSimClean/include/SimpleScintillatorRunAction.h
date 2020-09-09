/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.              *
 *   hseywerd@nrcan.gc.ca                                                  *
 *                                                                         *
 ***************************************************************************/

/**
 * @file SimpleScintillatorRunAction.h
 * @brief
 **/
#ifndef SimpleScintillatorRunAction_h
#define SimpleScintillatorRunAction_h

#include "globals.hh"
#include <G4UserRunAction.hh>
class TFile;
class TTree;
class TStopwatch;
class G4Event;

/**
 * @class SimpleScintillatorPhysicsList
 *
 * @brief Defines the user's action at the beginning and the end of each run.
 *
 * @author Henry Seywerd <hseywerd@nrcan.gc.ca>
*/
class SimpleScintillatorRunAction : public G4UserRunAction
{
  public:
    SimpleScintillatorRunAction();

    ~SimpleScintillatorRunAction();

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

  private:
    void OpenFile (const G4String filename, const G4bool outputMode);
    void CloseFile();
    void CreateTree();
    void FillData (const G4Event* pEvt);
    /// The root output file
    TFile* m_pROOTOutputFile;
    /// The tree of root objects to be output
    TTree* m_pROOTOutputTree;
    /// Tree of root objects for run specific data
    TTree* m_pROOTRunTree;
    int m_iRunID, m_iEventID;

};

#endif
