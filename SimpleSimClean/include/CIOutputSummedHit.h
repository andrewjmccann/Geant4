/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.               *
 *   hseywerd@nrcan.gc.ca                                                   *
 *                                                                          *
 ***************************************************************************/
/**
 * @file CIOutputSummedHit.h
 * @brief Manages cell by cell hit information
 *
 * See CIRootRunHeader for a description of how to build shared libs etc.
 *
 * @author Henry Seywerd hseywerd@nrcan.gc.ca
 **/
#ifndef CIOutputSummedHit_H_
#define CIOutputSummedHit_H_

#include "TROOT.h"
#include "Math/Vector3D.h"

//-----------------------------------------------------------------------------
/**
 * @class CIOutputSummedHit
 * @brief Manages cell by cell hit information
 * @author Henry Seywerd <hseywerd@nrcan.gc.ca>
 *
 **/
class CIOutputSummedHit: public TObject {
public:
	/**
	 * Construct a record containing information for the hit in a scintillator cell, summing all individual scintillations
	 *
	 */
	CIOutputSummedHit() :
		m_dEnergy(0), m_dSmearedEnergy(0.), m_iCellID(0) {
	}

	~CIOutputSummedHit() {
	}

	/**
	 * Copy constructor
	 * @param From copy from this
	 * @return
	 */
	CIOutputSummedHit(CIOutputSummedHit& From);

	/// Enumerates the different detector parts
	typedef enum {
		/// Module is in the scatter detector
		SUBDET_SCATTER,
		/// Module is in the absorber detector
		SUBDET_ABSORBER,
		/// Module is something else
		SUBDET_OTHER
	} SUBDET;

	/**
	 * @return Returns the energy associated with the summed hit
	 */
	inline double& TheEnergy() {return m_dEnergy;}
	/**
	 * @return Returns the energy associated with the summed hit with smearing factors applied
	 */
	inline double& TheSmearedEnergy() {return m_dSmearedEnergy;}
	/**
	 * @return Returns the cell identifier of where the hit occured
	 */
	inline int&    TheCellID()  {return m_iCellID;}
	/**
	 * @return Returns the X position of the hit
	 */
	const inline double GetX() const {return m_dXPos;}
	/**
	 * @return Returns the y position of the hit
	 */
	const inline double GetY() const {return m_dYPos;}
	/**
	 * @return Returns the z position of the hit
	 */
	const inline double GetZ() const {return m_dZPos;}
	/**
	 * Sets the position of the event
	 * @param position a three vector of the events position
	 */
	inline void SetHitPosition(const ROOT::Math::XYZVector& position) {m_dXPos = position.x(); m_dYPos = position.y(); m_dZPos = position.z();}
	/**
	 * @return Returns the time of the hit
	 */
	const inline double GetT() const {return m_dTime;}
	/**
	 * @return Returns the time of the hit
	 */
	const inline void SetT(const double t)  {m_dTime = t;}
	/**
	 * @return Returns which subdetector the hit occurred within
	 */
	inline SUBDET& TheSubDetector() {return m_SubDetector;}
	/**
	 * @return Returns the layer in which the hit occurred
	 */
	inline int& TheLayer() {return m_iLayer;}
	/**
	 * Calculate the compton angle from the provided energies
	 * @param E1 - Outgoing photon energy
	 * @param E2 - Outgoing electron energy
	 * @return the angle
	 */
	static double CalculateComptonAngle(const double E1, const double E2);

	/**
	 * Calculate the angle between the normal and the vector between the two compton hits using the smeared positions
	 *
	 * Take the two compton hits to be the hit in the scatter detector and the highest energy hit in the absorber detector.
	 * If there is more than one hit in the scatter detector, the function uses the last one - Caution
	 * For the hit positions use the positions from the summedHits array which normally are set to the cell centre positions.
	 *
	 * @param summedHits TClonesArray of CIOutputSummedHit objects
	 * @return the angle between the normal and the vector between the two hits
	 */
	static double GetSmeardAngle(const TClonesArray& summedHits);

	ClassDef (CIOutputSummedHit, 4);

private:
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
	/// The time of the hit (in the case of summing multiple scinit hits, this is the time of the last occuring hit
	double m_dTime;
	/// The subdetector
	SUBDET m_SubDetector;
	/// The layer within the subdetector
	int m_iLayer;
};

#endif /* CIOutputSummedHit_H_ */
