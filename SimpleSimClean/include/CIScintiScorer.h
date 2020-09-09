/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.              *
 *   hseywerd@nrcan.gc.ca                                                  *
 *                                                                         *
 ***************************************************************************/

/**
 * @file CIScintiScorer.h
 * @brief Define the regions of the scintillator detectors which can generate hits and manage their generation
 **/
#ifndef CIScintiScorer_h
#define CIScintiScorer_h

#include "G4HCofThisEvent.hh"
#include "G4VSensitiveDetector.hh"
#include "CIScintiHit.h"

/**
 * @class CIScintiScorer
 * @brief Define the regions of the scintillator detectors which can generate hits
 *
 * This sensitive detector is for sensitivity to particles generating a hit in the scintillator and for
 * managing the energy deposits in the scintillators.
 * It does not handle optical photons.
 * @author Henry Seywerd <hseywerd@nrcan.gc.ca>
*/
class CIScintiScorer : public G4VSensitiveDetector
{
  public:
    /**
     * Constructs the sensitive detector
     * @param name the name of this sensitive detector
     */
    CIScintiScorer(G4String name);

    ~CIScintiScorer();

    /**
     * Constructs the sensitivitity of an element of the detector.
     *
     * For each element:
     * * Register the energy deposit scorer
     * * Register the scorer which counts number of electrons
     * * Register the scorer which counts number of gammas
     *
     * @param iElement index of the element
     * @param pDetector pointer to the detector element object
     */
    void ConstructMultiFunctionalDetectorElement(const int iElement, G4MultiFunctionalDetector* pDetector);


  protected:


  private:
  /// Name of Energy Deposit scorer Name
  static const G4String m_strEDepScorerName;
  /// Name of scorer for number of electrons in the interaction
  static const G4String m_strNElectronScorerName;
  /// Name of scorer for number of gammas in the interaction
  static const G4String m_strNGammaScorerName;

  /// The name of the filter to be used to select out gammas
  static const G4String m_strGammaFilterName;
  /// The filter to be used to select out gammas
  G4SDParticleFilter m_pGammaFilter;

  /// The name of the filter to be used to select out electrons
  static const G4String m_strElectronFilterName;
  /// The filter to be used to select out electrons
  G4SDParticleFilter m_pElectronFilter;

};

#endif




