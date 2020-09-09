/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.               *
 *   hseywerd@nrcan.gc.ca                                                   *
 *                                                                          *
 ***************************************************************************/
/**
 * @file CIOutputScintiHit.h
 * @brief Class for hits int he scintillator
 *
 * Declares a class to represent hits in the detector.
 *
 * See CIRootRunHeader for a description of how to build shared libs etc.
 *
 * @author Henry Seywerd hseywerd@nrcan.gc.ca
 **/

#ifndef CIOUTPUTSCINTIHIT_H_
#define CIOUTPUTSCINTIHIT_H_

#include "TROOT.h"
#include "TVector3.h"
#include "CIOutputHit.h"

/**
 * @class CIOutputScintiHit
 * @brief Defines data recorded for a hit in the scintillator
 * @author Henry Seywerd <hseywerd@nrcan.gc.ca>
 *
 **/
class CIOutputScintiHit: public CIOutputHit {
public:

	/**
	 * Construct a record containing information for a hit in a scintillator cell, multiple hits per cell are possible.
	 * For information on summed hits see CIOutputSummedHit
	 * @param x the x position of the hit
	 * @param y the y position of the hit
	 * @param z the z position of the hit
	 * @param T the time of the hit
	 * @param E energy of the incoming track
	 * @param EDep the energy deposited in the hit
	 * @param moduleID the identifier of the hit module
	 * @param subDet the subdetector in which the hit occured
	 * @param trackID the identifier of the track according to Geant
	 * @param parentID the identifier of the track's parent according to Geant
	 * @param Htype the hit-type
	 * @param Ptype the particle type
	 */
	CIOutputScintiHit(const double x = 0, const double y = 0, const double z = 0, const double T = 0, const double E =
			0, const double EDep = 0, const int moduleID = 0,  const CIOutputEvent::SUBDET subDet=CIOutputEvent::SUBDET_OTHER, const int trackID = -1, const int parentID = -1,
			const CIOutputEvent::HITTYPE Htype = CIOutputEvent::HTYPE_OTHER, const CIOutputEvent::PARTTYPE Ptype = CIOutputEvent::PART_OTHER);
	~CIOutputScintiHit();


	/**
	 * Copy constructor
	 * @param pFrom copy from this
	 */
	CIOutputScintiHit(CIOutputScintiHit& From);


	/**
	 * Gets the true incident angle of the incomming photon as determined from the positions of the energy deposits in the detector
	 * @return
	 */
	static double GetTrueIncidentAngle(const TClonesArray& scintiHits);

	/**
	 * Gets the true incident angle of the incomming photon as determined from the positions of the energy deposits in the detector
	 * This version uses the truth information to get the first compton hit.
	 * @return
	 */
	static double GetTrueComptonAngle(const TClonesArray& scintiHits);

	static double GetTrueComptonAngle(const TClonesArray& scintiHits, TVector3& srcPos);
	static double GetTrueComptonAngle(TVector3& v1, TVector3& v2, TVector3& srcPos);

	/// Energy deposited in the hit
	double m_dEDeposit;
ClassDef(CIOutputScintiHit, 5)

};
#endif

