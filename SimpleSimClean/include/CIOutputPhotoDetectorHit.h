/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.               *
 *   hseywerd@nrcan.gc.ca                                                   *
 *                                                                          *
 ***************************************************************************/
/**
 * @file CIOutputPhotoDetectorHit.h
 * @brief Class for hits int he scintillator
 *
 * Defines data recorded for a hit photodetector, where all optical photons in the event are summed together.
 *
 * See CIRootRunHeader for a description of how to build shared libs etc.
 *
 * @author Henry Seywerd hseywerd@nrcan.gc.ca
 **/
#ifndef CIOUTPUTPHOTODETECTORHIT_H_
#define CIOUTPUTPHOTODETECTORHIT_H_

#include "TROOT.h"
#include "CIOutputHit.h"

//-----------------------------------------------------------------------------
/**
 * @class CIOutputPhotoDetectorHit
 * @brief Defines data recorded for a hit photodetector, where all optical photons in the event are summed together.
 * @author Henry Seywerd <hseywerd@nrcan.gc.ca>
 *
 **/
class CIOutputPhotoDetectorHit: public CIOutputHit {
public:
	/**
	 * Construct a record containing information for a hit in a photodetector
	 * @param x the x position of the hit
	 * @param y the y position of the hit
	 * @param z the z position of the hit
	 * @param T the time of the hit
	 * @param E the energy deposited in the hit
	 * @param moduleID the identifier of the hit module
	 * @param trackID the identifier of the track according to Geant
	 * @param parentID the identifier of the track's parent according to Geant
	 * @param Htype the hit-type
	 * @param Ptype the particle type
	 */
	CIOutputPhotoDetectorHit(const double x = 0, const double y = 0, const double z = 0, const double T = 0,
			const double E = 0, const int moduleID = 0, const CIOutputEvent::SUBDET subDet=CIOutputEvent::SUBDET_OTHER, const int trackID = -1, const int parentID = -1,
			const CIOutputEvent::HITTYPE Htype = CIOutputEvent::HTYPE_OTHER, const CIOutputEvent::PARTTYPE Ptype = CIOutputEvent::PART_OTHER) :
		CIOutputHit(x, y, z, T, E, moduleID, subDet, trackID, parentID, Htype, Ptype) {
	}

	~CIOutputPhotoDetectorHit() {
	}

ClassDef (CIOutputPhotoDetectorHit, 5)

};

#endif /* CIOUTPUTPHOTODETECTORHIT_H_ */
