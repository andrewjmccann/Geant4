/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.               *
 *   hseywerd@nrcan.gc.ca                                                   *
 *                                                                          *
 ***************************************************************************/
/**
 * @file CIOutputEvent.h
 * @brief Event output data.
 *
 * Defines several classes to manage the output data including different classes for different types of hits.
 * These classes are intended for sharing between geant and root (and possibly other systems as well).
 * So define in terms of standard types, not the Geant types.
 * If we were really careful we would include some type comparison code to ensure that these types were
 * really the same in both systems, but we are not...
 *
 * See CIRootRunHeader for a description of how to build shared libs etc.
 *
 * @author Henry Seywerd hseywerd@nrcan.gc.ca
 **/
#ifndef CIOutputEvent_h
#define CIOutputEvent_h

#include "TROOT.h"
#include "TClonesArray.h"

/**
 * @class CIOutputEvent
 * @brief Event output data
 * @author Henry Seywerd <hseywerd@nrcan.gc.ca>
 *
 **/
class CIOutputEvent: public TObject {
public:
	CIOutputEvent();

	~CIOutputEvent();

	CIOutputEvent & operator=(const CIOutputEvent &From);

	/// Enumerates the different processes responsible for particle creation
	typedef enum {
		/// Other process
		HTYPE_OTHER,
		/// Energy deposit caused by a Compton scatter
		HTYPE_COMPTON,
		/// Energy deposit caused by photo-electric effect interaction
		HTYPE_PE,
		/// Energy deposit caused by primary track
		HTYPE_PRIMARY,
		/// Energy deposit caused by Bremsstrahlung
		HTYPE_BREM,
		/// Energy deposit caused by Low Energy Ionization
		HTYPE_IONI,
		/// Energy deposit caused by Scintillation
		HTYPE_SCINT,
		/// G4 Low Energy compton process -to replace G4LECS
		HTYPE_LECOMPTON,
		/// G4 Low Energy polar compton process -to replace G4LECS
		HTYPE_LEPCOMPTON,
		/// G4 Low Energy photoelectric process -to replace G4LECS
		HTYPE_LEPE,
		/// G4 Low Energy ionization process -to replace G4LECS
		HTYPE_LEIONI,
		/// G4 Low Energy pair production process -to replace G4LECS
		HTYPE_LEPAIR,
		/// G4 Low Energy bremsstrahlung process -to replace G4LECS
		HTYPE_LEBREM,
		/// Standard Compton - not low energy adapted
		HTYPE_STDCOMPTON,
		/// Marker not for actual use, always to be last in the ENUM list, so as to evaluate the number of elements in the enum
		HTYPE_LAST_IN_THE_LIST
	} HITTYPE;

	/// Enumerates the particle types we handle
	typedef enum {
		/// Other particle
		PART_OTHER,
		/// Electrons
		PART_ELECTRON,
		/// Gamma ray photon
		PART_GAMMA,
		/// Optical photon
		PART_OPTPHOTON
	} PARTTYPE;
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
	 * Determine the hit type from the string used inside GEANT to define the creator process
	 * @param name a string giving the name
	 * @return the hit type code
	 */
	HITTYPE GetHTypeFromName(const TString name);

	/**
	 * Determine the hit type string from the hit type code
	 * @param type the hit type code
	 * @return the hit type name string
	 */
	TString GetNameFromHType(const HITTYPE type);

	/**
	 * Determine the particle type from the string name
	 * @param name a string giving the name
	 * @return the particle type code
	 */
	PARTTYPE GetPTypeFromName(const TString name);

	/**
	 * Determine the particle name string from the particle type code
	 * @param type the particle type code
	 * @return the particle name string
	 */
	TString GetNameFromPType(const PARTTYPE type);


public:
	int m_dEventNum;
	int m_dRunNum;
	double m_dPrimaryVertexX;
	double m_dPrimaryVertexY;
	double m_dPrimaryVertexZ;
	double m_dPrimaryVertexPX;
	double m_dPrimaryVertexPY;
	double m_dPrimaryVertexPZ;

	TClonesArray* m_ScintiHitList;
	TClonesArray* m_OpticalHitList;
	TClonesArray* m_OutputSummedHitList;
	TClonesArray* m_SummedOptiHitList;
	TClonesArray* m_MaterialHitList;



	// Hit type name strings
	const TString m_strPE_Name;
	const TString m_strPrimary_Name;
	const TString m_strCompton_Name;
	const TString m_strBrem_Name;
	const TString m_strScinti_Name;
	const TString m_strIoni_Name;
	const TString m_strOther_Name;
	// Hit types associated with new G4 Low Energy Package (to replace G4LECS)
	const  TString m_strLECompton_Name;
	const  TString m_strLEPolarCompton_Name;
	const  TString m_strLEPhotoElectric_Name;
	const  TString m_strLEIoni_Name;
	const  TString m_strLEPairProduction_Name;
	const  TString m_strLEBrem_Name;
	// Hit type for non-low energy compton process
	const  TString m_strSTDCompton_Name;


	// Particle type name strings
	const TString m_strElectronName;
	const TString m_strGammaName;
	const TString m_strOpticalPhotonName;
	const TString m_strOtherPartName;



ClassDef (CIOutputEvent, 5)

};

#endif
