/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.               *
 *   hseywerd@nrcan.gc.ca                                                   *
 *                                                                          *
 ***************************************************************************/
/**
 * @file CIOutputMaterialHit.h
 * @brief Class for hits in materials
 *
 * Declares a class to represent hits in the detector.
 *
 * See CIRootRunHeader for a description of how to build shared libs etc.
 *
 * @author Henry Seywerd hseywerd@nrcan.gc.ca
 **/

#ifndef CIOutputMaterialHit_H_
#define CIOutputMaterialHit_H_

#include "TROOT.h"
#include "TVector3.h"
#include "CIOutputHit.h"

/**
 * @class CIOutputMaterialHit
 * @brief Defines data recorded for a hit in the other material
 * @author Henry Seywerd <hseywerd@nrcan.gc.ca>
 *
 **/
class CIOutputMaterialHit: public CIOutputHit {
public:

	/**
	 * Construct a record containing information for a hit in a material
	 * @param x the x position of the hit
	 * @param y the y position of the hit
	 * @param z the z position of the hit
	 * @param T the time of the hit
	 * @param E energy of the incoming track
	 * @param EDep the energy deposited in the hit
	 * @param trackID the identifier of the track according to Geant
	 * @param parentID the identifier of the track's parent according to Geant
	 * @param Htype the hit-type
	 * @param Ptype the particle type
	 */
	CIOutputMaterialHit(const double x = 0, const double y = 0, const double z = 0, const double T = 0, const double E =
			0, const double EDep = 0, const int trackID = -1, const int parentID = -1,
			const CIOutputEvent::HITTYPE Htype = CIOutputEvent::HTYPE_OTHER, const CIOutputEvent::PARTTYPE Ptype = CIOutputEvent::PART_OTHER, const TString name="");
	~CIOutputMaterialHit();

	/**
	 * Copy constructor
	 * @param From copy from this
	 */
	CIOutputMaterialHit(CIOutputMaterialHit& From);

	/// Energy deposited in the hit
	double m_dEDeposit;
	TString Volume;
ClassDef(CIOutputMaterialHit, 5)

};
#endif

