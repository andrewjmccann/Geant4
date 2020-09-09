/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.               *
 *   hseywerd@nrcan.gc.ca                                                   *
 *                                                                          *
 ***************************************************************************/
/**
 * @file CIOutputHit.h
 * @brief Event output hit base class
 *
 * Declares a class to represent hits in the detector.
 *
 * Intended as a base class for specific hit types.
 * See CIRootRunHeader for a description of how to build shared libs etc.
 *
 * @author Henry Seywerd hseywerd@nrcan.gc.ca
 **/

#ifndef CIOUTPUTHIT_H_
#define CIOUTPUTHIT_H_

#include "TROOT.h"
#include <iostream>
#include "CIOutputEvent.h"

/**
 * @class CIOutputHit
 * @brief A base class for different types of hits to be written to external storage
 * @author Henry Seywerd <hseywerd@nrcan.gc.ca>
 *
 **/
class CIOutputHit: public TObject {
public:
//	/// Enumerates the different processes responsible for particle creation
//	typedef enum {
//		/// Other process
//		HTYPE_OTHER,
//		/// Energy deposit caused by a Compton scatter
//		HTYPE_COMPTON,
//		/// Energy deposit caused by photo-electric effect interaction
//		HTYPE_PE,
//		/// Energy deposit caused by primary track
//		HTYPE_PRIMARY,
//		/// Energy deposit caused by Bremsstrahlung
//		HTYPE_BREM,
//		/// Energy deposit caused by Low Energy Ionization
//		HTYPE_IONI,
//		/// Energy deposit caused by Scintillation
//		HTYPE_SCINT,
//		/// G4 Low Energy compton process -to replace G4LECS
//		HTYPE_LECOMPTON,
//		/// G4 Low Energy polar compton process -to replace G4LECS
//		HTYPE_LEPCOMPTON,
//		/// G4 Low Energy photoelectric process -to replace G4LECS
//		HTYPE_LEPE,
//		/// G4 Low Energy ionization process -to replace G4LECS
//		HTYPE_LEIONI,
//		/// G4 Low Energy pair production process -to replace G4LECS
//		HTYPE_LEPAIR,
//		/// G4 Low Energy bremsstrahlung process -to replace G4LECS
//		HTYPE_LEBREM,
//		/// Standard Compton - not low energy adapted
//		HTYPE_STDCOMPTON,
//		/// Marker not for actual use, always to be last in the ENUM list, so as to evaluate the number of elements in the enum
//		HTYPE_LAST_IN_THE_LIST
//	} HITTYPE;
//
//	/// Enumerates the particle types we handle
//	typedef enum {
//		/// Other particle
//		PART_OTHER,
//		/// Electrons
//		PART_ELECTRON,
//		/// Gamma ray photon
//		PART_GAMMA,
//		/// Optical photon
//		PART_OPTPHOTON
//	} PARTTYPE;
//	/// Enumerates the different detector parts
//	typedef enum {
//		/// Module is in the scatter detector
//		SUBDET_SCATTER,
//		/// Module is in the absorber detector
//		SUBDET_ABSORBER,
//		/// Module is something else
//		SUBDET_OTHER
//	} SUBDET;

	CIOutputHit(const double x = 0, const double y = 0, const double z = 0,
			const double T = 0, const double E = 0,
			const int moduleID = 0, const CIOutputEvent::SUBDET subDet=CIOutputEvent::SUBDET_OTHER, const int trackID = -1, const int parentID = -1,
			const CIOutputEvent::HITTYPE Htype = CIOutputEvent::HTYPE_OTHER,
			const CIOutputEvent::PARTTYPE Ptype = CIOutputEvent::PART_OTHER);
	~CIOutputHit();
	/**
	 * Copy constructor
	 * @param From copy it from this
	 */
	CIOutputHit(const CIOutputHit& From);


	ClassDef(CIOutputHit, 4);

public:
	/// X position of the hit
	double m_dX;
	/// Y position of the hit
	double m_dY;
	/// Z position of the hit
	double m_dZ;
	/// Time of the hit
	double m_dT;
	/// Energy of the track
	double m_dE;
	/// Identifier of the module affected by the hit
	int m_iModuleID;
  /// The subdetector
	CIOutputEvent::SUBDET m_SubDetector;
	/// The Geant track number of the current track - so we can sort out scinti hits from photoelectric effect/brems etc.
	int m_iCurrentTrackID;
	/// The Geant track number of the parent track - so we can sort out scinti hits from photoelectric effect/brems etc.
	int m_iParentTrackID;
	/// Process causing the hit
	CIOutputEvent::HITTYPE m_HitType;
	/// The particle causing the hit
	CIOutputEvent::PARTTYPE m_PartType;

	void PPrint() {
		std::cout << " " << m_dX << " " << m_dY << " " << m_dZ << " " << m_dT
				<< " " << m_dE << " " << m_iModuleID << m_iCurrentTrackID << m_iParentTrackID << std::endl;
	}
	;
	/*
	 * Print the x, y, z position of the hit.
	 */
	void PrintPosition() {
		std::cout<< " The hit position is (X,Y,Z) " << m_dX << " " << m_dY << " " << m_dZ <<std::endl;
	}


	/**
	 * Determine the hit type from the string used inside GEANT to define the creator process
	 * @param name a string giving the name
	 * @return the hit type code
	 */
	//static CIOutputEvent::HITTYPE GetHTypeFromName(const std::string name);

	/**
	 * Determine the hit type string from the hit type code
	 * @param type the hit type code
	 * @return the hit type name string
	 */
	//static std::string GetNameFromHType(const CIOutputEvent::HITTYPE type);

	/**
	 * Determine the particle type from the string name
	 * @param name a string giving the name
	 * @return the particle type code
	 */
	//static CIOutputEvent::PARTTYPE GetPTypeFromName(const std::string name);

	/**
	 * Determine the particle name string from the particle type code
	 * @param type the particle type code
	 * @return the particle name string
	 */
	//static std::string GetNameFromPType(const CIOutputEvent::PARTTYPE type);

private:
//	// Hit type name strings
//	static const std::string m_strPE_Name;
//	static const std::string m_strPrimary_Name;
//	static const std::string m_strCompton_Name;
//	static const std::string m_strBrem_Name;
//	static const std::string m_strScinti_Name;
//	static const std::string m_strIoni_Name;
//	static const std::string m_strOther_Name;
//	// Hit types associated with new G4 Low Energy Package (to replace G4LECS)
//	static const  std::string m_strLECompton_Name;
//	static const  std::string m_strLEPolarCompton_Name;
//	static const  std::string m_strLEPhotoElectric_Name;
//	static const  std::string m_strLEIoni_Name;
//	static const  std::string m_strLEPairProduction_Name;
//	static const  std::string m_strLEBrem_Name;
//	// Hit type for non-low energy compton process
//	static const  std::string m_strSTDCompton_Name;
//
//
//	// Particle type name strings
//	static const std::string m_strElectronName;
//	static const std::string m_strGammaName;
//	static const std::string m_strOpticalPhotonName;
//	static const std::string m_strOtherPartName;
};

#endif /* CIOUTPUTHIT_H_ */
