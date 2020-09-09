/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.               *
 *   hseywerd@nrcan.gc.ca                                                   *
 *                                                                          *
 ***************************************************************************/
/**
 * @file CIOutputPhotoHit.h
 * @brief Class for hits int he scintillator
 *
 * Declares a class to represent hits in the detector.
 *
 * See CIRootRunHeader for a description of how to build shared libs etc.
 *
 * @author Henry Seywerd hseywerd@nrcan.gc.ca
 **/

#ifndef CIOutputPhotoHit_H_
#define CIOutputPhotoHit_H_

#include "TROOT.h"
#include "Math/Vector3D.h"
#include "CIOutputHit.h"

/**
 * @class CIOutputPhotoHit
 * @brief Defines data recorded for a hit in the scintillator
 * @author Henry Seywerd <hseywerd@nrcan.gc.ca>
 *
 **/
class CIOutputPhotoHit: public CIOutputHit {
public:
	/**
	 *
	 * Construct a record containing information for the hit of a single optical photon
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
	 * @param scintiHitIndex an index to the corresponding scintillator hit
	 */
	CIOutputPhotoHit(const double x = 0, const double y = 0, const double z = 0, const double T = 0,
			const double E = 0, const int moduleID = 0, const CIOutputEvent::SUBDET subDet=CIOutputEvent::SUBDET_OTHER, const int trackID = -1, const int parentID = -1,
			const CIOutputEvent::HITTYPE Htype = CIOutputEvent::HTYPE_OTHER, const CIOutputEvent::PARTTYPE Ptype = CIOutputEvent::PART_OTHER,
			const int scintiHitIndex = -1);


	~CIOutputPhotoHit();

	/**
	 * Copy construct
	 * @param From build a new instance from this
	 */
	CIOutputPhotoHit(CIOutputPhotoHit& From);

	/**
	 * Sets the position of the event
	 * @param position a three vector of the events position
	 */
	inline void SetHitPosition(const ROOT::Math::XYZVector& position) {m_dXPos = position.x(); m_dYPos = position.y(); m_dZPos = position.z();};
	/**
	 * @return Returns the cell identifier of where the hit occured
	 */
	inline int&    TheCellID()  {return m_iCellID;}
	/**
	 * @return Returns the energy associated with the summed hit
	 */
	inline double& TheEnergy() {return m_dEnergy;}
	/**
	 * @return Returns which subdetector the hit occurred within
	 */
	inline CIOutputEvent::SUBDET& TheSubDetector() {return m_SubDetector;};
	/**
	 * @return Returns the layer in which the hit occurred
	 */
	inline int& TheLayer() {return m_iLayer;};

    /// Returns the index to the corresponding scintillator hit
	inline int GetScintiHitIndex() const {
		return m_iScintiHitIndex;
	}

	int m_iScintiHitIndex;
	/// The summed energy in the cell
	double m_dEnergy;
	/// The summed energy in the cell with smearing applied
	double m_dSmearedEnergy;
	/// The cell identifier
	int    m_iCellID;
	/// X Position of the hit (centre of cell)
	double m_dXPos;
	/// Y Position of the hit (centre of cell)
	double m_dYPos;
	/// Z Position of the hit (centre of cell)
	double m_dZPos;
	/// The layer within the subdetector
	int m_iLayer;

ClassDef (CIOutputPhotoHit, 6)
};
#endif
