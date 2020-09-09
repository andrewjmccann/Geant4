/*   Copyright (C) Minister of Natural Resources Canada 2008.              *
 *   hseywerd@nrcan.gc.ca                                                  *
 *                                                                         *
 ***************************************************************************/
/**
 * @file CIMaterials.h
 * @brief Create all the materials required for the Compton Imager.
 * @date 2008/12/08
 * @author HCJ Seywerd hseywerd@nrcan.gc.ca
 **/

#pragma once
class G4NistManager;
class G4Optical;
class G4OpticalSurface;

/**
 * @class CIMaterials
 *
 * @brief Create all the materials required for the Compton Imager.
 *
 * This is a singleton and so invoked once for the entire application. Callers may then access its member variables to get
 * specific material properties.
 *
 * If we were really serious we should define a database class and then access the constants in some data driven way.
 * As it is, at least we isolate the material definitions and parameters from the outside world.
 *
 * @author HCJ Seywerd hseywerd@nrcan.gc.ca
 *
 */

class CIMaterials {
public:
	virtual ~CIMaterials(void);
	/**
	 * Access the single instance of this class
	 * @return Pointer to the instance.
	 */
	static CIMaterials* Instance();

	/**
	 * Return a pointer to the requested element.
	 * If element not set up will generate and exception
	 * @param elementName String giving the name of the element
	 * @return pointer to the element
	 */
	G4Element* GetElement(const G4String elementName) const;

	/**
	 * Return a pointer to the requested material.
	 * If material not set up will generate and exception
	 * @param materialName String giving the name of the material
	 * @return pointer to the material
	 */
	G4Material* GetMaterial(const G4String materialName) const;

	/**
	 * Return a pointer to the requested optical .
	 * If optical  not set up will generate and exception
	 * @param surfaceName gives the name of the optical surface
	 * @return pointer to the optical surface
	 */
	G4OpticalSurface* GetOpticalSurface(const G4String surfaceName) const;

private:
	/**
	 * Protected constructor as this is a singleton
	 */
	CIMaterials();

	/**
	 * Copy constructor
	 * @param materials object to copy
	 */
	CIMaterials(const CIMaterials& materials);

	/**
	 * Copy operator
	 * @param materials object to copy
	 */
	CIMaterials& operator=(const CIMaterials& materials);
private:
	/// Static pointer to the single instance of the class
	static CIMaterials* m_pInstance;

	/// Pointer to the NIST manager object from which material and element database information is obtained
	G4NistManager* m_pNistManager;

private:

	// List of elements
	/// Element Hydrogen
	G4Element* m_elementH;
	/// Element Carbon
	G4Element* m_elementC;
	/// Element Oxygen
	G4Element* m_elementO;
	/// Element Lutetium
	G4Element* m_elementLu;
	/// Element  Ytrium
	G4Element* m_elementY;
	/// Element  Silicon
	G4Element* m_elementSi;
	/// Element  Nitrogen
	G4Element* m_elementN;
	/// Element  Sodium
	G4Element* m_elementNa;
	/// Element Iodine
	G4Element* m_elementI;
	/// Element  Calcium
	G4Element* m_elementCa;
	/// Element  Fluorine
	G4Element* m_elementF;
	/// Element Lanthanum
	G4Element* m_elementLa;
	/// Element Bromine
	G4Element* m_elementBr;
	/// Element Aluminum
	G4Element* m_elementAl;
	/// Element Nickel
	G4Element*  m_elementNi;
	/// Element Iron
	G4Element* m_elementFe;
	/// Element Copper
	G4Element* m_elementCu;
	/// Element Chromium
	G4Element* m_elementCr;
	/// Element Zinc
	G4Element* m_elementZn;
	/// Element Gd
	G4Element* m_elementGd;
	/// Element Ga
	G4Element* m_elementGa;


	// List of composite materials
	/// Composite material Air - optically transparent
	G4Material* m_materialAir;
	/// Composite material Vacuum - optically transparent
	G4Material* m_materialVacuum;
	/// Composite material Air - but optically opaque to use for a convenience when building optical systems
	G4Material* m_materialOpaqueAir;
	/// Composite material Optical coupling compound - probably not needed but for completeness include
	G4Material* m_materialOpticalCompound;
	/// Composite material scintillator BGO
	G4Material* m_materialBGO;
	/// Composite material, scintillator LYSO
	G4Material* m_materialLYSO;
	/// Composite material, scintillator Sodium Iodide
	G4Material* m_materialNaI;
	/// Composite material, scintillator Sodium Iodide with Inifinte attenuation length
	G4Material* m_materialGAGG;
	/// Composite material, scintillator Sodium Iodide with Inifinte attenuation length
	G4Material* m_materialNaIinfAtten;
	/// Composite material, scintillator Calcium Fluroide
	G4Material* m_materialCaF;
	/// Composite material, scintillator Lanthanum Bromide
	G4Material* m_materialLaBr3;
	/// Composite material plastic scintillator
	G4Material* m_materialPVT;
	/// Composite material glass - generic
	G4Material* m_materialGlass;
	/// Composite material FR4 - generic
	G4Material* m_materialFR4;
	/// Composite material Carbon Fibre
	G4Material* m_materialCarbonFibre;
	/// Composite material Plastazote
	G4Material* m_materialPlastazote;
	/// Composite material quartz - generic
	G4Material* m_materialQuartz;
	G4Material* m_materialAluminium;
	G4Material* m_materialTeflon;
	G4Material* m_materialGold;
	/// Composite material glass - generic
	G4Material* m_materialPolyethylene;
	/// Composite material borosilicate glass

	/// Composite material borosilicate glass
	G4Material* m_materialBorosilicateGlass;
	/// Composite material the SiPM itself
	G4Material* m_materialSiPM;
	/// Composite material the Glass for the SiPM
	G4Material* m_materialSiO2;
	/// Composite material Wavelength Shifter EJ280
	G4Material* m_materialEJ280;
	/// Composite material Cesium Iodide scintillator (Tl)
	G4Material* m_materialCsI;
	/// Composite material YAP - Yttrium Aluminum Perovskite (Ce3+)
	G4Material* m_materialYAP;
	/// Material Iron
	G4Material* m_materialFe;
	/// Material Iron
	G4Material* m_materialPb;
	/// Material Aluminum
	G4Material* m_materialAl;
	/// Material - Mu metal
	G4Material* m_materialMuMetal;
	/// Material - Concrete
	G4Material* m_materialConcrete;
	/// Material - Brass
	G4Material* m_materialBrass;


	// List of optically sensitive surfaces
	/// Sensitive optical surface of a SensL standard SiPMT
	G4OpticalSurface* m_surfaceSPM3035X08;
	/// Sensitive optical surface of a Hamamatsu MPPC S11064 based on the S10362 chip.
	G4OpticalSurface* m_surfaceSPMS11064_100;
	/// Black (non-reflective) optical surface
	G4OpticalSurface* m_surfaceBlack;
	/// Perfect mirror surface
	G4OpticalSurface* m_surfaceMirror;
	/// Optical surface for tests
	G4OpticalSurface* m_surfaceTest;
	/// Optical surface: White painted back
	G4OpticalSurface* m_surfaceWhite;
	/// Optical sufrace between material and Tyvek wrapping
	G4OpticalSurface* m_surfaceWrapTYVEK;

	/// Sensitive optical surface of a Hamamatsu Bialkali PMT
	G4OpticalSurface* m_surfaceHammaBialkali;
	/// Sensitive optical surface of a Hamamatsu Super-Bialkali PMT
	G4OpticalSurface* m_surfaceHammaSBA;
	/// Sensitive optical surface of a Hamamatsu Ultra-Bialkali PMT
	G4OpticalSurface* m_surfaceHammaUBA;
	/// Polished optical surface between dielectric material and air
	G4OpticalSurface* m_surfacePolishedDielectric;
	/// Ground optical surface between dielectric material and air
	G4OpticalSurface* m_surfaceGroundDielectric;

	/// Material Properties table for YAP



	G4MaterialPropertiesTable* m_NaIMaterialProperties;
	G4MaterialPropertiesTable* m_GAGGMaterialProperties;
	G4MaterialPropertiesTable* m_NaIinfAttenMaterialProperties;
	G4MaterialPropertiesTable* m_LYSOMaterialProperties;
	G4MaterialPropertiesTable* m_CaF2MaterialProperties;
	G4MaterialPropertiesTable* m_CsIMaterialProperties;
	G4MaterialPropertiesTable* m_YAPMaterialProperties;
	G4MaterialPropertiesTable* m_LaBr3MaterialProperties;
	G4MaterialPropertiesTable* m_PVTMaterialProperties;
	G4MaterialPropertiesTable* m_OpticalCompoundMaterialProperties;
	G4MaterialPropertiesTable* m_AirMaterialProperties;
	G4MaterialPropertiesTable* m_VacuumMaterialProperties;
	G4MaterialPropertiesTable* m_OpaqueAirMaterialProperties;
	G4MaterialPropertiesTable* m_GlassMaterialProperties;
	G4MaterialPropertiesTable* m_QuartzMaterialProperties;	
	G4MaterialPropertiesTable* m_SiPMMaterialProperties;
	G4MaterialPropertiesTable* m_SPM3035X08MaterialProperties;
	G4MaterialPropertiesTable* m_EJ280MaterialProperties;
	G4MaterialPropertiesTable* m_TestMaterialProperties;
	G4MaterialPropertiesTable* m_SurfaceWhiteMaterialProperties;
	G4MaterialPropertiesTable* m_SurfaceBlackMaterialProperties;
	G4MaterialPropertiesTable* m_SurfaceMirrorMaterialProperties;
	G4MaterialPropertiesTable* m_TyvekMaterialProperties;


	/**
	 * Construct composite materials
	 * @return true if successful
	 */
	bool ConstructMaterials();

	/**
	 * Construct the elements needed
	 * @return true if successful
	 */
	bool ConstructElements();

	/**
	 * Construct Sodium Iodide scintillator
	 * @return true if successful
	 *
	 * Optical data sources:
	 * - Absorption length: More or less a guess, from other optical materials.
	 * - Refractive index: St. Gobain data sheet 415nm + http://refractiveindex.info (NaI undoped and from calculation)
	 * - Emission spectrum: St. Gobain data sheet, extracted from the graph by Audrey
	 * - Yield: St. Gobain data sheet
	 * - Resolution Scale: Taken to be 1 with no justification, can adjust later.
	 * - Time Constant: From PDG
	 *
	 */
	bool ConstructNaI();
	bool ConstructGAGG();
	bool ConstructNaIinfAtten();


	/**
	 * Construct LYSO scintillator
	 * @return true if successful
	 *
	 *   Optical data sources:
	 * - Absorption length:
	 * - Refractive index: Optical and Scintillation Properties of Inorganic Scintillators in High Energy Physics, Rihua Mao IEEE TRANSACTIONS ON NUCLEAR SCIENCE, VOL. 55, NO. 4, Aug 2008
	 * - Emission spectrum: St. Gobain data sheet, extracted from the graph by Henry
	 * - Yield: St. Gobain data sheet
	 * - Resolution Scale: Taken to be 1 with no justification, can adjust later.
	 * - Time Constant: St. Gobain data sheet
	 *
	 */
	bool ConstructLYSO();

	/**
	 * Construct BGO scintillator
	 * @return true if successful
	 *
	 *   Optical data sources:
	 * - Absorption length:
	 * - Refractive index:
	 * - Emission spectrum:
	 * - Yield:
	 * - Resolution Scale:
	 * - Time Constant:
	 */
	bool ConstructBGO();

	/**
	 * Construct CaF2 scintillator
	 * @return true if successful
	 *
	 *   Optical data sources:
	 * - Absorption length: From Korth Kristalle GMBH plot www.korth.de, ignoring cutoffs.
	 * - Refractive index: Table of values from Melles-Griot - see http://www.mellesgriot.com/
	 * - Emission spectrum:
	 * - Yield:
	 * - Resolution Scale:
	 * - Time Constant:
	 *
	 */
	bool ConstructCaF2();

	/**
	 * Construct Lanthanum Bromide scintillator
	 * @return true if successful
	 *
	 *   Optical data sources:
	 * - Absorption length: Guess
	 * - Refractive index:  St. Gobain, no wavelength dependence available.
	 * - Emission spectrum: St. Gobain, interpolating from graph
	 * - Yield: St. Gobain - single component
	 * - Resolution Scale: Taken to be 1 with no justification, can adjust later.
	 * - Time Constant: St. Gobain data sheet
	 *
	 */
	bool ConstructLaBr3();

	/**
	 * Construct CsI-Tl activated scintillator
	 * @return true if successful
	 *
	 *   Optical data sources:
	 * - Absorption length: PDG (2008) table 28.4
	 * - Refractive index: Alkor.net data sheet.
	 * - Emission spectrum: extracted from the St. Gobain data sheet.
	 * - Yield: extracted from the St. Gobain data sheet.
	 * - Resolution Scale: set to 1
	 * - Time Constant: extracted from the St. Gobain data sheet.
	 *
	 */
	bool ConstructCsI();

	/**
	 * Construct PVT scintillator
	 * @return true if successful
	 *
	 * - Absorption length: St. Gobain, no wavelength dependence available.
	 * - Refractive index:  www.alkor.net, for pure, seems consistent with the value of Tl dopped CsI from St. Gobain.
	 * - Emission spectrum: St. Gobain, interpolating from graph - Henry
	 * - Yield: St. Gobain - single component (.64*Anthracence - Anthracence = .4-.5 of NaI
	 * - Resolution Scale: Taken to be 1 with no justification, can adjust later.
	 * - Time Constant: St. Gobain data sheet
	 *
	 */
	bool ConstructPVT();


	/**
	 * Construct YAP scintillator -- (Yttrium Aluminum Perovskite activated by Ce3+)
	 * @return true if successful
	 *
	 * - Absorption length: S. Baccaro et. al NIMA 406 p 479
	 * - Refractive index: S. Baccaro et. al NIMA 406 p 479
	 * - Emission spectrum: Petr Wandrol and Petr Horák, Microsc Microanal 13 (Suppl 3), 2007.
	 * - Yield: St. Gobain specs
	 * - Resolution Scale: Taken to be 1
	 * - Time Constant: St. Gobain specs
	 *
	 */
	bool ConstructYAP();

	/**
	 * Construct optical coupling compound
	 * @return true if successful
	 *
	 *   Optical data sources:
	 * - Absorption length:
	 *
	 */
	bool ConstructOpticalCompound();

	/**
	 * Construct Vacuum
	 * @return true if successful
	 *
	 *
	 */
	bool ConstructVacuum();


	/**
	 * Construct air
	 * @return true if successful
	 *
	 *   Optical data sources:
	 * - Absorption length:
	 *
	 */
	bool ConstructAir();

	/**
	 * Construct air, optically opaque
	 *
	 *
	 * @return true if successful
	 */
	bool ConstructOpaqueAir();

	/**
	 * Construct glass
	 * @return true if successful
	 *
	 *  Jojo pointed out an error in this function, in order to make total internal reflection work
	 *  it is necessary that the optical photon pass the boundary and be reflected back in.
	 *  Consequently a zero attentuation length makes this fail, and the attenuation length has been changed
	 *  to be small but non-zero.
	 *
	 * - Optical data sources:
	 * - Absorption length:
	 */
	bool ConstructGlass();
	/**
	 * Construct FR4
	 * @return true if successful
	 */
	bool ConstructFR4();

	/**
	 * Construct CarbonFibre
	 * @return true if successful
	 */
	bool ConstructCarbonFibre();

	/**
	 * Construct Plastazote
	 * @return true if successful
	 */
	bool ConstructPlastazote();
	/**
	 * Construct quartz
	 * @return true if successful
	 *
	 *  Jojo pointed out an error in this function, in order to make total internal reflection work
	 *  it is necessary that the optical photon pass the boundary and be reflected back in.
	 *  Consequently a zero attentuation length makes this fail, and the attenuation length has been changed
	 *  to be small but non-zero.
	 *
	 * - Optical data sources:
	 * - Absorption length:
	 */
	bool ConstructQuartz();

	/**
	 * Construct Mu Metal shielding material
	 * @return true if successful
	 *
	 * Data for mu metal from CRC Introduction to Magnetism and Magnetic Materials.
	 * 77% Ni,
	 * 16% Fe
	 * 5% Cu
	 * 2% Cr
	 *
	 * Density http://mumetal.co.uk/
	 *
	 */
	bool ConstructMuMetal();

	/**
	 * Construct Brass shielding material
	 * @return true if successful
	 *
	 * Brass composition varies, here is a Wikipedia example\
	 * Common brass, or rivet brass, is a 37% zinc brass, cheap and standard for cold working.
	 * 37% Zn,
	 * 63% Cu
	 *
	 * Density 8.4 gm/cm^
	 */
	bool ConstructBrass();


	/**
	 * Construct silicon photomultiplier materials
	 * @return true if successful
	 */
	bool ConstructSiPM();

	/**
	 * Construct quartz for SiPMs
	 * @return true if successful
	 */
	bool ConstructSiO2();

	/**
	 * Construct ELJEN EJ280 Wavelength Shifter
	 * @author JoJo
	 * @return true if successful
	 *
	 * - Absorption length: ELJEN Tech EJ280 spec
	 * - Refractive index:  ELJEN Tech EJ280 spec
	 * - Emission spectrum: ELJEN Tech EJ280 spec
	 * - Time Constant: ELJEN Tech EJ280 spec
	 *
	 */
	bool ConstructEJ280();

	/**
	 * Construct silicon photomultiplier sensitive surface.
	 * The surface is defined by the spectral efficiency and reflectivity provided by
	 * SensL for the SPMMini3035X08 SiPM, from the SPM Mini Data sheet Feb 2009
	 */
	void ConstructSurfaceSPM3035X08();

	/**
	 * Construct silicon photomultiplier sensitive surface.
	 * The surface is defined by the spectral efficiency and reflectivity provided by
	 * Hamamatsu from spec sheet.
	 */
	void ConstructSurfaceSPMS11064_100();

	/**
	 * Construct a sensitive surface for test purposes
	 */
	void ConstructSurfaceTest();

	/**
	 * Construct a optical surface with absolute absorption.
	 */
	void ConstructSurfaceBlack();

	/**
	 * Construct a optical surface with absolute reflection.
	 */
	void ConstructSurfaceMirror();

	/**
	 * Construct a optical surface with white reflection.
	 */
	void ConstructSurfaceWhite();

	/**
	 * Construct a optical surface between two polished dielectrics
	 */
	void ConstructSurfacePolishedDielectric();

	/**
	 * Construct a optical surface two ground dielectrics
	 */
	void ConstructSurfaceGroundDielectric();

	/**
	 * Construct a optical surface simulating a surface wraped in Tyvek
	 * Defined as a 99% reflectivity material
	 */
	void ConstructSurfaceWrapTYVEK();

	/**
	 * Normalize the contents of the given input vector so the sum is unity.
	 * @param vector the vector of quantities to normalize
	 * @param size  the number of elements in the vector.
	 */
	void NormalizeSumToUnity(double* vector, const int size);

        bool ConstructPolyethylene();

        bool ConstructAluminium();
        bool ConstructTeflon();

        bool ConstructGold();

private:
	// Scintillator characteristics name strings
	static const G4String m_ScintiFastSpectrumName;
	static const G4String m_ScintiSlowSpectrumName;
	static const G4String m_ScintiFastTimeConstName;
	static const G4String m_ScintiSlowTimeConstName;
	static const G4String m_ScintiYieldName;
	static const G4String m_ScintiYieldRatioName;
	static const G4String m_ScintiResScaleName;

	// Optical characteristics name strings
	static const G4String m_OpticRefractiveIndexName;
	static const G4String m_OpticAbsorptionLengthName;
	// For use with the old G4 optical model - reflectivity
	static const G4String m_OpticReflectivityName;

	/// Detection efficiency for optical detection materials (photocathodes etc)
	static const G4String m_OpticDetectionEfficiencyName;

	static const G4String m_OpticalSurfaceSuffix;

	/// Conversion of optical photon wavelength from nm to eV \f$ E(eV) = hc/\lambda(nm) \approx 1240/\lambda\f$
	static const G4double m_dNMtoEV;

	// Element name strings
	static const G4String m_H_Name;
	static const G4String m_C_Name;
	static const G4String m_N_Name;
	static const G4String m_O_Name;
	static const G4String m_Lu_Name;
	static const G4String m_Si_Name;
	static const G4String m_Y_Name;
	static const G4String m_Na_Name;
	static const G4String m_I_Name;
	static const G4String m_Ca_Name;
	static const G4String m_F_Name;
	static const G4String m_La_Name;
	static const G4String m_Br_Name;
	static const G4String m_Al_Name;
	static const G4String m_Ni_Name;
	static const G4String m_Fe_Name;
	static const G4String m_Cu_Name;
	static const G4String m_Cr_Name;
	static const G4String m_Zn_Name;
	static const G4String m_Gd_Name;
	static const G4String m_Ga_Name;

	static const G4String m_Air_Name;
	static const G4String m_Vacuum_Name;
	static const G4String m_OpaqueAir_Name;
	static const G4String m_OpticalCompound_Name;
	static const G4String m_BGO_Name;
	static const G4String m_LYSO_Name;
	static const G4String m_NaI_Name;
	static const G4String m_GAGG_Name;
	static const G4String m_NaIinfAtten_Name;
	static const G4String m_CaF_Name;
	static const G4String m_CsI_Name;
	static const G4String m_YAP_Name;
	static const G4String m_LaBr3_Name;
	static const G4String m_PVT_Name;
	static const G4String m_Fe_MatName;
	static const G4String m_Pb_MatName;
	static const G4String m_Al_MatName;
	static const G4String m_MuMetal_MatName;
	static const G4String m_Concrete_MatName;
	static const G4String m_Brass_MatName;
	static const G4String m_Glass_Name;
	static const G4String m_FR4_Name;
	static const G4String m_CarbonFibre_Name;
	static const G4String m_Plastazote_Name;
	static const G4String m_Quartz_Name;
	static const G4String m_BorosilicateGlass_Name;
	static const G4String m_SiPM_Name;
	static const G4String m_SiO2_Name;
	static const G4String m_EJ280_Name;
        static const G4String m_Polyethylene_Name;
        static const G4String m_Aluminium_Name;
        static const G4String m_Teflon_Name;
        static const G4String m_Gold_Name;


	static const G4String m_SPM3035X08_Name;
	static const G4String m_SPMS11064_100_Name;
	static const G4String m_TestSurface_Name;
	static const G4String m_BlackSurface_Name;
	static const G4String m_MirrorSurface_Name;
	static const G4String m_WhiteSurface_Name;

	static const G4String m_PolishedDielectricSurface_Name;
	static const G4String m_GroundDielectricSurface_Name;
	static const G4String m_WrapTYVEKSurface_Name;

	static const G4String m_WLSComponentName;
	static const G4String m_WLSTimeConstantName;
	static const G4String m_WLSAbsLengthName;
};

