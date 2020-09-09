/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.              *
 *   hseywerd@nrcan.gc.ca                                                  *
 *                                                                         *
 ***************************************************************************/
/**
 * @file CIMaterials.cpp
 * @brief Create all the materials required for the Compton Imager.
 *
 * @date 2008/12/08
 *
 * @author HCJ Seywerd hseywerd@nrcan.gc.ca
 **/

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4OpticalSurface.hh"
#include "CIMaterials.h"
using namespace CLHEP;

const G4String CIMaterials::m_ScintiFastSpectrumName = "FASTCOMPONENT";
const G4String CIMaterials::m_ScintiSlowSpectrumName = "SLOWCOMPONENT";
const G4String CIMaterials::m_ScintiFastTimeConstName = "FASTTIMECONSTANT";
const G4String CIMaterials::m_ScintiSlowTimeConstName = "SLOWTIMECONSTANT";
const G4String CIMaterials::m_ScintiYieldName = "SCINTILLATIONYIELD";
const G4String CIMaterials::m_ScintiYieldRatioName = "YIELDRATIO";
const G4String CIMaterials::m_ScintiResScaleName = "RESOLUTIONSCALE";

const G4String CIMaterials::m_OpticRefractiveIndexName = "RINDEX";
const G4String CIMaterials::m_OpticAbsorptionLengthName = "ABSLENGTH";

const G4String CIMaterials::m_OpticDetectionEfficiencyName = "EFFICIENCY";
const G4String CIMaterials::m_OpticReflectivityName = "REFLECTIVITY";


const G4String CIMaterials::m_WLSComponentName = "WLSCOMPONENT";
const G4String CIMaterials::m_WLSTimeConstantName = "WLSTIMECONSTANT";
const G4String CIMaterials::m_WLSAbsLengthName = "WLSABSLENGTH";


const G4String CIMaterials::m_OpticalSurfaceSuffix = "_OSURF";

const G4double CIMaterials::m_dNMtoEV = 1240.0 * eV;

const G4String CIMaterials::m_H_Name = "H";
const G4String CIMaterials::m_Gd_Name = "Gd";
const G4String CIMaterials::m_Ga_Name = "Ga";
const G4String CIMaterials::m_C_Name = "C";
const G4String CIMaterials::m_N_Name = "N";
const G4String CIMaterials::m_O_Name = "O";
const G4String CIMaterials::m_Lu_Name = "Lu";
const G4String CIMaterials::m_Si_Name = "Si";
const G4String CIMaterials::m_Y_Name = "Y";
const G4String CIMaterials::m_Na_Name = "Na";
const G4String CIMaterials::m_I_Name = "I";
const G4String CIMaterials::m_Ca_Name = "Ca";
const G4String CIMaterials::m_F_Name = "F";
const G4String CIMaterials::m_La_Name = "La";
const G4String CIMaterials::m_Br_Name = "Br";
const G4String CIMaterials::m_Al_Name = "Al";
const G4String CIMaterials::m_Ni_Name = "Ni";
const G4String CIMaterials::m_Fe_Name = "Fe";
const G4String CIMaterials::m_Cu_Name = "Cu";
const G4String CIMaterials::m_Cr_Name = "Cr";
const G4String CIMaterials::m_Zn_Name = "Zn";

const G4String CIMaterials::m_Vacuum_Name = "G4_VACUUM";
const G4String CIMaterials::m_Air_Name = "G4_AIR";
const G4String CIMaterials::m_OpaqueAir_Name = "Opaque_AIR";
const G4String CIMaterials::m_OpticalCompound_Name = "OpticalCompound";
const G4String CIMaterials::m_BGO_Name = "G4_BGO";
const G4String CIMaterials::m_LYSO_Name = "LYSO";
const G4String CIMaterials::m_NaI_Name = "G4_SODIUM_IODIDE";
const G4String CIMaterials::m_GAGG_Name = "G4_GAGG";
const G4String CIMaterials::m_CaF_Name = "G4_CALCIUM_FLUORIDE";
const G4String CIMaterials::m_CsI_Name = "G4_CESIUM_IODIDE";
const G4String CIMaterials::m_YAP_Name = "YAP";
const G4String CIMaterials::m_LaBr3_Name = "LaBr3";
const G4String CIMaterials::m_PVT_Name = "G4_PLASTIC_SC_VINYLTOLUENE";
const G4String CIMaterials::m_Glass_Name = "G4_GLASS_PLATE";
const G4String CIMaterials::m_SiO2_Name = "SiO2";
const G4String CIMaterials::m_CarbonFibre_Name = "CARBONFIBRE";
const G4String CIMaterials::m_Plastazote_Name = "PLASTAZOTE";
const G4String CIMaterials::m_FR4_Name = "FR4";
const G4String CIMaterials::m_Quartz_Name = "G4_QUARTZ";
const G4String CIMaterials::m_BorosilicateGlass_Name = "BOROSILICATE";
const G4String CIMaterials::m_SiPM_Name = "SiPM";
const G4String CIMaterials::m_EJ280_Name = "EJ280";
const G4String CIMaterials::m_Fe_MatName = "G4_Fe";
const G4String CIMaterials::m_Pb_MatName = "G4_Pb";
const G4String CIMaterials::m_Al_MatName = "G4_Al";
const G4String CIMaterials::m_MuMetal_MatName = "MuMetal";
const G4String CIMaterials::m_Concrete_MatName = "G4_CONCRETE";
const G4String CIMaterials::m_Brass_MatName = "Brass";
const G4String CIMaterials::m_Polyethylene_Name = "G4_POLYETHYLENE";
const G4String CIMaterials::m_Aluminium_Name = "G4_ALUMINIUM";
const G4String CIMaterials::m_Teflon_Name = "G4_TEFLON";
const G4String CIMaterials::m_Gold_Name = "G4_Au";

const G4String CIMaterials::m_SPM3035X08_Name = "SPM3035X08";
const G4String CIMaterials::m_SPMS11064_100_Name = "SPMS11064-100";
const G4String CIMaterials::m_TestSurface_Name = "TestSurface";
const G4String CIMaterials::m_BlackSurface_Name = "BlackSurface";
const G4String CIMaterials::m_MirrorSurface_Name = "MirrorSurface";
const G4String CIMaterials::m_WhiteSurface_Name = "WhiteSurface";
const G4String CIMaterials::m_PolishedDielectricSurface_Name = "PolishedDielectricSurface";
const G4String CIMaterials::m_GroundDielectricSurface_Name = "GroundDielectricSurface";
const G4String CIMaterials::m_WrapTYVEKSurface_Name = "WrapTYVEKSurface";



CIMaterials* CIMaterials::m_pInstance = 0;// initializpointer
CIMaterials* CIMaterials::Instance() {
	if (m_pInstance == 0) // is it the first call?
	{
		m_pInstance = new CIMaterials; // create sole instance
	}
	return m_pInstance; // address of sole instance
}
//-----------------------------------------------------------------------------


CIMaterials::CIMaterials(void) :
	m_pNistManager(NULL), m_elementH(NULL), m_elementC(NULL), m_elementO(NULL), m_elementLu(NULL), m_elementY(NULL), m_elementSi(NULL),  m_elementN(NULL),
			m_elementNa(NULL), m_elementI(NULL), m_elementCa(NULL), m_elementF(NULL), m_elementLa(NULL), m_elementBr(NULL), m_elementAl(NULL),m_elementGa(NULL), m_elementGd(NULL),  m_elementNi(NULL),
			m_elementFe(NULL), m_elementCu(NULL), m_elementCr(NULL), m_elementZn(NULL), m_materialAir(NULL), m_materialVacuum(NULL), m_materialOpaqueAir(NULL), m_materialOpticalCompound(NULL), m_materialBGO(
																								   NULL), m_materialLYSO(NULL), m_materialNaI(NULL),m_materialGAGG(NULL), m_materialCaF(NULL), m_materialLaBr3(NULL), m_materialPVT(NULL), m_materialGlass(NULL),  m_materialCarbonFibre(NULL), m_materialPlastazote(NULL), m_materialFR4(NULL),m_materialQuartz(NULL),
			m_materialBorosilicateGlass(NULL), m_materialSiPM(NULL), m_materialSiO2(NULL),m_materialEJ280(NULL), m_materialCsI(NULL), m_materialYAP(NULL), m_materialFe(NULL),
			m_materialAl(NULL), m_materialMuMetal(NULL), m_materialConcrete(NULL), m_surfaceSPM3035X08(NULL), m_surfaceSPMS11064_100(NULL), m_surfaceBlack(NULL), m_surfaceMirror(NULL),
			m_surfaceTest(NULL), m_surfaceWhite(NULL), m_surfaceWrapTYVEK(NULL), m_surfaceHammaBialkali(NULL), m_surfaceHammaSBA(NULL), m_surfaceHammaUBA(NULL),
			m_surfacePolishedDielectric(NULL), m_surfaceGroundDielectric(NULL),
			m_NaIMaterialProperties(NULL), 	m_GAGGMaterialProperties(NULL), m_LYSOMaterialProperties(NULL), m_CaF2MaterialProperties(NULL),
			m_CsIMaterialProperties(NULL), m_YAPMaterialProperties(NULL), m_LaBr3MaterialProperties(NULL), m_PVTMaterialProperties(NULL),
			m_OpticalCompoundMaterialProperties(NULL), m_AirMaterialProperties(NULL),m_VacuumMaterialProperties(NULL),  m_OpaqueAirMaterialProperties(NULL), m_GlassMaterialProperties(NULL), m_QuartzMaterialProperties(NULL),
			m_SiPMMaterialProperties(NULL), m_SPM3035X08MaterialProperties(NULL), m_EJ280MaterialProperties(NULL), m_TestMaterialProperties(NULL), m_SurfaceWhiteMaterialProperties(NULL),
			m_SurfaceBlackMaterialProperties(NULL), m_SurfaceMirrorMaterialProperties(NULL), m_TyvekMaterialProperties(NULL)
{

	m_pNistManager = G4NistManager::Instance();
	ConstructElements();
	ConstructMaterials();
}
//-----------------------------------------------------------------------------

CIMaterials::~CIMaterials(void) {
	if (m_NaIMaterialProperties) delete (m_NaIMaterialProperties);
	if (m_GAGGMaterialProperties) delete (m_GAGGMaterialProperties);
	if (m_CsIMaterialProperties) delete (m_CsIMaterialProperties);
	if (m_YAPMaterialProperties) delete (m_YAPMaterialProperties);
	if (m_LaBr3MaterialProperties) delete (m_LaBr3MaterialProperties);
	if (m_PVTMaterialProperties) delete (m_PVTMaterialProperties);
	if (m_OpticalCompoundMaterialProperties) delete (m_OpticalCompoundMaterialProperties);
	if (m_AirMaterialProperties) delete (m_AirMaterialProperties);
	if (m_VacuumMaterialProperties) delete (m_VacuumMaterialProperties);
	if (m_OpaqueAirMaterialProperties) delete (m_OpaqueAirMaterialProperties);
	if (m_GlassMaterialProperties) delete (m_GlassMaterialProperties);
	if (m_QuartzMaterialProperties) delete (m_QuartzMaterialProperties);

	if (m_SiPMMaterialProperties) delete m_SiPMMaterialProperties;
	if (m_SPM3035X08MaterialProperties) delete (m_SPM3035X08MaterialProperties);
	if (m_TestMaterialProperties) delete m_TestMaterialProperties;
	if (m_SurfaceWhiteMaterialProperties) delete (m_SurfaceWhiteMaterialProperties);
	if (m_SurfaceBlackMaterialProperties) delete (m_SurfaceBlackMaterialProperties);
	if (m_SurfaceMirrorMaterialProperties) delete (m_SurfaceMirrorMaterialProperties);
	if (m_TyvekMaterialProperties) delete (m_TyvekMaterialProperties);
}
//-----------------------------------------------------------------------------
bool CIMaterials::ConstructElements() {

	//***Elements
	m_elementH = m_pNistManager->FindOrBuildElement(m_H_Name);
	m_elementC = m_pNistManager->FindOrBuildElement(m_C_Name);
	m_elementN = m_pNistManager->FindOrBuildElement(m_N_Name);
	m_elementO = m_pNistManager->FindOrBuildElement(m_O_Name);
	m_elementLu = m_pNistManager->FindOrBuildElement(m_Lu_Name);
	m_elementSi = m_pNistManager->FindOrBuildElement(m_Si_Name);
	m_elementY = m_pNistManager->FindOrBuildElement(m_Y_Name);
	m_elementNa = m_pNistManager->FindOrBuildElement(m_Na_Name);
	m_elementI = m_pNistManager->FindOrBuildElement(m_I_Name);
	m_elementCa = m_pNistManager->FindOrBuildElement(m_Ca_Name);
	m_elementF = m_pNistManager->FindOrBuildElement(m_F_Name);
	m_elementLa = m_pNistManager->FindOrBuildElement(m_La_Name);
	m_elementBr = m_pNistManager->FindOrBuildElement(m_Br_Name);
	m_elementAl = m_pNistManager->FindOrBuildElement(m_Al_Name);
	m_elementNi = m_pNistManager->FindOrBuildElement(m_Ni_Name);
	m_elementFe = m_pNistManager->FindOrBuildElement(m_Fe_Name);
	m_elementCu = m_pNistManager->FindOrBuildElement(m_Cu_Name);
	m_elementCr = m_pNistManager->FindOrBuildElement(m_Cr_Name);
	m_elementZn = m_pNistManager->FindOrBuildElement(m_Zn_Name);
	m_elementGd = m_pNistManager->FindOrBuildElement(m_Gd_Name);
	m_elementGa = m_pNistManager->FindOrBuildElement(m_Ga_Name);

	return true;
}
//-----------------------------------------------------------------------------


G4Element* CIMaterials::GetElement(const G4String elementName) const {

	if (elementName == m_H_Name) {
		return m_elementH;
	} else if (elementName == m_C_Name) {
		return m_elementC;
	} else if (elementName == m_N_Name) {
		return m_elementN;
	} else if (elementName == m_O_Name) {
		return m_elementO;
	} else if (elementName == m_Lu_Name) {
		return m_elementLu;
	} else if (elementName == m_Si_Name) {
		return m_elementSi;
	} else if (elementName == m_Y_Name) {
		return m_elementY;
	} else if (elementName == m_Na_Name) {
		return m_elementNa;
	} else if (elementName == m_I_Name) {
		return m_elementI;
	} else if (elementName == m_Ca_Name) {
		return m_elementCa;
	} else if (elementName == m_F_Name) {
		return m_elementF;
	} else if (elementName == m_La_Name) {
		return m_elementLa;
	} else if (elementName == m_Br_Name) {
		return m_elementBr;
	} else if (elementName == m_Al_Name) {
		return m_elementAl;
	} else if (elementName == m_Ga_Name) {
		return m_elementGa;
	} else if (elementName == m_Gd_Name) {
		return m_elementGd;
	} else if (elementName == m_Ni_Name) {
		return m_elementNi;
	} else if (elementName == m_Fe_Name) {
		return m_elementFe;
	} else if (elementName == m_Cu_Name) {
		return m_elementCu;
	} else if (elementName == m_Cr_Name) {
		return m_elementCr;
	} else if (elementName == m_Zn_Name) {
		return m_elementZn;
	} else {
	  //G4Exception("CIMaterials::GetElement == Unknown Element: " + elementName);
		return NULL;
	}
}
//-----------------------------------------------------------------------------


G4Material* CIMaterials::GetMaterial(const G4String materialName) const {

	if (materialName == m_Air_Name) {
		return m_materialAir;
	} else if (materialName == m_Vacuum_Name) {
		return m_materialVacuum;
	} else if (materialName == m_OpaqueAir_Name) {
		return m_materialOpaqueAir;
	} else if (materialName == m_OpticalCompound_Name) {
		return m_materialOpticalCompound;
	} else if (materialName == m_BGO_Name) {
		return m_materialBGO;
	} else if (materialName == m_LYSO_Name) {
		return m_materialLYSO;
	} else if (materialName == m_NaI_Name) {
		return m_materialNaI;
	} else if (materialName == m_GAGG_Name) {
		return m_materialGAGG;
	} else if (materialName == m_CaF_Name) {
		return m_materialCaF;
	} else if (materialName == m_LaBr3_Name) {
		return m_materialLaBr3;
	} else if (materialName == m_PVT_Name) {
	        return m_materialPVT;
	} else if (materialName == m_Polyethylene_Name) {
		return m_materialPolyethylene;
	} else if (materialName == m_Aluminium_Name) {
		return m_materialAluminium;
	} else if (materialName == m_Teflon_Name) {
		return m_materialTeflon;
	} else if (materialName == m_Gold_Name) {
		return m_materialGold;
	} else if (materialName == m_Glass_Name) {
	        return m_materialGlass;
	} else if (materialName == m_FR4_Name) {
	        return m_materialFR4;
	} else if (materialName == m_CarbonFibre_Name) {
	        return m_materialCarbonFibre;
	} else if (materialName == m_Plastazote_Name) {
	        return m_materialPlastazote;
	} else if (materialName == m_Quartz_Name) {
	       return m_materialQuartz;
	} else if (materialName == m_BorosilicateGlass_Name) {
		return m_materialBorosilicateGlass;
	} else if (materialName == m_SiPM_Name) {
		return m_materialSiPM;
	} else if (materialName == m_SiO2_Name) {
		return m_materialSiO2;
	} else if (materialName == m_EJ280_Name) {
		return m_materialEJ280;
	} else if (materialName == m_CsI_Name) {
		return m_materialCsI;
	} else if (materialName == m_YAP_Name) {
		return m_materialYAP;
	} else if (materialName == m_Fe_MatName) {
		return m_materialFe;
	} else if (materialName == m_Pb_MatName) {
		return m_materialPb;
	} else if (materialName == m_Al_MatName) {
		return m_materialAl;
	} else if (materialName == m_MuMetal_MatName) {
		return m_materialMuMetal;
	} else if (materialName == m_Concrete_MatName) {
		return m_materialConcrete;
	} else if (materialName == m_Brass_MatName) {
		return m_materialBrass;
	}	else {
		G4cout<< "CIMaterials::GetMaterial == Unknown Material: " + materialName + ". Try the NIST database." <<G4endl;
		return m_pNistManager->FindOrBuildMaterial(materialName);
	}
}
//-----------------------------------------------------------------------------

G4OpticalSurface* CIMaterials::GetOpticalSurface(const G4String surfaceName) const {
	if (surfaceName == m_SPM3035X08_Name) {
		return m_surfaceSPM3035X08;
	} else if (surfaceName == m_TestSurface_Name) {
		return m_surfaceTest;
	} else if (surfaceName == m_BlackSurface_Name) {
		return m_surfaceBlack;
	} else if (surfaceName == m_MirrorSurface_Name) {
		return m_surfaceMirror;
	} else if (surfaceName == m_WhiteSurface_Name) {
		return m_surfaceWhite;
	} else if (surfaceName == m_PolishedDielectricSurface_Name) {
		return m_surfacePolishedDielectric;
	} else if (surfaceName == m_GroundDielectricSurface_Name) {
		return m_surfaceGroundDielectric;
	} else if (surfaceName == m_WrapTYVEKSurface_Name) {
		return m_surfaceWrapTYVEK;
	} else {
	  //	G4Exception("CIMaterials::GetOpticalSurface == Unknown Optical Surface: " + surfaceName);
		return NULL;
	}
}
//-----------------------------------------------------------------------------


bool CIMaterials::ConstructMaterials() {
	ConstructNaI();
	ConstructGAGG();
	ConstructAir();
	ConstructVacuum();
	ConstructOpaqueAir();
	ConstructGlass();
	ConstructFR4();
	ConstructCarbonFibre();
	ConstructPlastazote();
	ConstructQuartz();
	ConstructAluminium();
	ConstructTeflon();
	ConstructGold();
	ConstructPolyethylene();
	ConstructBGO();
	ConstructLYSO();
	ConstructCaF2();
	ConstructLaBr3();
	ConstructPVT();
	ConstructOpticalCompound();
	ConstructSiPM();
	ConstructSiO2();
	ConstructSurfaceSPM3035X08();
	ConstructSurfaceTest();
	ConstructSurfaceBlack();
	ConstructSurfaceMirror();
	ConstructSurfaceWhite();
	ConstructSurfacePolishedDielectric();
	ConstructSurfaceGroundDielectric();
	ConstructSurfaceWrapTYVEK();
	ConstructEJ280();
	ConstructCsI();
	ConstructYAP();
	m_materialFe = m_pNistManager->FindOrBuildMaterial(m_Fe_MatName);
	assert (m_materialFe != NULL);
	m_materialPb = m_pNistManager->FindOrBuildMaterial(m_Pb_MatName);
	assert (m_materialPb != NULL);
	m_materialAl = m_pNistManager->FindOrBuildMaterial(m_Al_MatName);
	assert (m_materialAl != NULL);
	ConstructMuMetal();
	m_materialConcrete = m_pNistManager->FindOrBuildMaterial(m_Concrete_MatName);
	assert (m_materialConcrete != NULL);
	ConstructBrass();


	// Print all the materials defined.
	//
	G4cout << G4endl << "The materials defined are : " << G4endl << G4endl;
	G4cout << *(G4Material::GetMaterialTable()) << G4endl;
	return true;
}
//-----------------------------------------------------------------------------

bool CIMaterials::ConstructNaI() {
	// Physical properties from St. Gobain data sheet.

	// Define the composition
	m_materialNaI = m_pNistManager->FindOrBuildMaterial(m_NaI_Name);
	assert (m_materialNaI != NULL);

	// Define scintillation properties
	const G4double TimeConstant = 230.0 * ns;
	const G4double ScintillationYield = 38000. / MeV;
	// Only one time constant.
	const G4double ScintillationYieldRatio = 1.0;
	const G4double ScintillationResolutionScale = 1.0;

	// Define optical properperties
	// Refractive index from: Refractive Index of the Alkali Halides - strictly speaking for undoped NaI but I image we are close enough
	const G4int nRefractiveI = 7;
	G4double RefractiveIndexEnergy[nRefractiveI] = { m_dNMtoEV / 600., m_dNMtoEV / 550., m_dNMtoEV / 500., m_dNMtoEV
			/ 450., m_dNMtoEV / 400., m_dNMtoEV / 350., m_dNMtoEV / 300. };
	G4double RefractiveIndex[nRefractiveI] = { 1.773, 1.780, 1.791, 1.807, 1.83, 1.866, 1.933 };

	// Obtained from Figure 2 of Optical and Scintillation Properties of NaI(Tl) Crystals - these are values for annealed NaI, which St. Gobain implies is the case.
	//const G4int nAbsorption = 5;
	//G4double AbsorptionEnergy[nAbsorption] = { m_dNMtoEV / 200, m_dNMtoEV / 350, m_dNMtoEV / 380, m_dNMtoEV / 440,
	//		m_dNMtoEV / 1000 };
	//G4double AbsorptionLength[nAbsorption] = { 0.* cm, 3.3* cm, 40.* cm, 125.* cm, 330.0* cm };

	//Audrey's interpretation of same plot as henry's
       
        const G4int nAbsorption = 7;
	G4double AbsorptionEnergy[nAbsorption] = { m_dNMtoEV / 200,  m_dNMtoEV / 335, m_dNMtoEV / 350, m_dNMtoEV / 400, m_dNMtoEV / 450, m_dNMtoEV / 500, m_dNMtoEV / 1000 };
	G4double AbsorptionLength[nAbsorption] = { 0.* cm, 25.*cm, 33.*cm, 50.*cm, 67.*cm, 143.*cm, 330.*cm};


	//From Audrey by extraction from the St. Gobain data sheet plot
	const G4int nSpectrum = 13;
	G4double SpectrumEnergy[nSpectrum] = { 2.3 * eV, 2.36 * eV, 2.48 * eV, 2.53 * eV, 2.58 * eV, 2.76 * eV, 2.82 * eV,
			2.97 * eV, 3.04 * eV, 3.11 * eV, 3.22 * eV, 3.41 * eV, 3.74 * eV };
	G4double SpectrumFraction[nSpectrum] = { 0.016, 0.019, 0.034, 0.063, 0.090, 0.145, 0.164, 0.145, 0.119, 0.090,
			0.063, 0.034, 0.0190 };
	//Normalize the spectrum so that the sum is unity.
	NormalizeSumToUnity(SpectrumFraction, nSpectrum);

	m_NaIMaterialProperties = new G4MaterialPropertiesTable();
	m_NaIMaterialProperties->AddProperty(m_ScintiFastSpectrumName, SpectrumEnergy, SpectrumFraction, nSpectrum);
	m_NaIMaterialProperties->AddConstProperty(m_ScintiFastTimeConstName, TimeConstant);
	m_NaIMaterialProperties->AddConstProperty(m_ScintiYieldName, ScintillationYield);
	m_NaIMaterialProperties->AddConstProperty(m_ScintiYieldRatioName, ScintillationYieldRatio);
	m_NaIMaterialProperties->AddConstProperty(m_ScintiResScaleName, ScintillationResolutionScale);

	m_NaIMaterialProperties->AddProperty(m_OpticRefractiveIndexName, RefractiveIndexEnergy, RefractiveIndex, nRefractiveI);
	m_NaIMaterialProperties->AddProperty(m_OpticAbsorptionLengthName, AbsorptionEnergy, AbsorptionLength, nAbsorption);

	m_materialNaI->SetMaterialPropertiesTable(m_NaIMaterialProperties);

	return true;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

bool CIMaterials::ConstructGAGG() {
	// Physical properties from  Composition Engineering in Cerium-Doped ... Single-Crystal Scintillators Kamada, Endo, Tsutumi

	// Define the composition
	G4double density;
	const G4int nComponents = 4;
	m_materialGAGG = new G4Material(m_GAGG_Name, density = 6.5 * g / cm3, nComponents);
	assert (m_materialGAGG != NULL);

	m_materialGAGG->AddElement(m_elementGd, 3);
	m_materialGAGG->AddElement(m_elementAl, 2);
	m_materialGAGG->AddElement(m_elementGa, 3);
	m_materialGAGG->AddElement(m_elementO, 12);

	// Define scintillation properties
	const G4double TimeConstant = 52.8 * ns;// (73%); //main only. secondary is 282 (27 percent)
	const G4double ScintillationYield = 42217. / MeV;
	const G4double ScintillationYieldRatio = 1.0;
	const G4double ScintillationResolutionScale = 1.0;

	// instrinsic resolution = 5.2%

	return true;
}
//-----------------------------------------------------------------------------

bool CIMaterials::ConstructLYSO() {

	// This is St. Gobain formulation
	// Amount of Yttrium can vary
	// This is Lu(1.8), Y(0.2) Si O(5)

	// Other parameters from Siccas email 2009/03/24

	// Define the composition
	G4double density;
	const G4int nComponents = 4;
	m_materialLYSO = new G4Material(m_LYSO_Name, density = 7.3 * g / cm3, nComponents);
	assert (m_materialLYSO != NULL);

	const G4double mass = 8.0;
	m_materialLYSO->AddElement(m_elementLu, 1.8 / mass);
	m_materialLYSO->AddElement(m_elementY, 0.2 / mass);
	m_materialLYSO->AddElement(m_elementSi, 1.0 / mass);
	m_materialLYSO->AddElement(m_elementO, 5.0 / mass);

	// St. Gobain is 41ns: Siccas is 50ns, use the St. Gobain
	const G4double TimeConstant = 41.0 * ns;
	//St Gobain is 32000/MeV, Mao et al say 29860, Siccass is 75%NaI, use the latter to be conservative
	const G4double ScintillationYield = 28500. / MeV;
	// Only one time constant.
	const G4double ScintillationYieldRatio = 1.0;
	const G4double ScintillationResolutionScale = 1.0;

	// Define optical properties
	const G4int nRefractiveI = 6;
	//Only the values between 405 and 546 nm are given by the measurement.
	// We need to extend these to cover the full range of the spectrum by adding some artificial values on the ends
	// From Mao et al.
	G4double RefractiveIndexEnergy[nRefractiveI] = { m_dNMtoEV / 650., m_dNMtoEV / 546., m_dNMtoEV / 486., m_dNMtoEV
			/ 436., m_dNMtoEV / 405., m_dNMtoEV / 300. };
	G4double RefractiveIndex[nRefractiveI] = { 1.806, 1.806, 1.813, 1.822, 1.833, 1.833 };

	//From Henry extracted from the St. Gobain data sheet.
	const G4int nSpectrum = 15;
	G4double SpectrumEnergy[nSpectrum] = { m_dNMtoEV / 625.0, m_dNMtoEV / 600.0, m_dNMtoEV / 575.0, m_dNMtoEV / 550.0,
			m_dNMtoEV / 525.0, m_dNMtoEV / 500.0, m_dNMtoEV / 475.0, m_dNMtoEV / 450.0, m_dNMtoEV / 425.0, m_dNMtoEV
					/ 420.0, m_dNMtoEV / 410.0, m_dNMtoEV / 400.0, m_dNMtoEV / 385.0, m_dNMtoEV / 375.0, m_dNMtoEV
					/ 350. };
	G4double SpectrumFraction[nSpectrum] = { 0.5, 1.0, 2.0, 4.0, 7.0, 13.0, 18.0, 23.0, 24.0, 25.0, 18.0, 14.0, 4.0,
			1.0, 0.1 };
	//Normalize the spectrum so that the sum is unity.
	NormalizeSumToUnity(SpectrumFraction, nSpectrum);

	// Calculated from information in the Mao Paper + GEM TN-92-148 (Ma and Zu).
	const G4int nAbsorption = 5;
	G4double AbsorptionEnergy[nAbsorption] = { m_dNMtoEV / 350., m_dNMtoEV / 375., m_dNMtoEV / 425, m_dNMtoEV / 450,
			m_dNMtoEV / 1000. };
	G4double AbsorptionLength[nAbsorption] = { 0.1 *cm, 35.0* cm };

	m_LYSOMaterialProperties = new G4MaterialPropertiesTable();
	m_LYSOMaterialProperties->AddProperty(m_ScintiFastSpectrumName, SpectrumEnergy, SpectrumFraction, nSpectrum);
	m_LYSOMaterialProperties->AddConstProperty(m_ScintiFastTimeConstName, TimeConstant);
	m_LYSOMaterialProperties->AddConstProperty(m_ScintiYieldName, ScintillationYield);
	m_LYSOMaterialProperties->AddConstProperty(m_ScintiYieldRatioName, ScintillationYieldRatio);
	m_LYSOMaterialProperties->AddConstProperty(m_ScintiResScaleName, ScintillationResolutionScale);

	m_LYSOMaterialProperties->AddProperty(m_OpticRefractiveIndexName, RefractiveIndexEnergy, RefractiveIndex, nRefractiveI);
	m_LYSOMaterialProperties->AddProperty(m_OpticAbsorptionLengthName, AbsorptionEnergy, AbsorptionLength, nAbsorption);

	m_materialLYSO->SetMaterialPropertiesTable(m_LYSOMaterialProperties);
	return true;
}
//-----------------------------------------------------------------------------

bool CIMaterials::ConstructBGO() {
	m_materialBGO = m_pNistManager->FindOrBuildMaterial("G4_BGO");
	assert (m_materialBGO != NULL);
	return true;
}

//-----------------------------------------------------------------------------

bool CIMaterials::ConstructPolyethylene() {
	m_materialPolyethylene = m_pNistManager->FindOrBuildMaterial("G4_POLYETHYLENE");
	assert (m_materialPolyethylene != NULL);
	return true;
}

//-----------------------------------------------------------------------------

bool CIMaterials::ConstructAluminium() {
	m_materialAluminium = m_pNistManager->FindOrBuildMaterial("G4_Al");
	assert (m_materialAluminium != NULL);
	return true;
}
//-----------------------------------------------------------------------------

bool CIMaterials::ConstructTeflon() {
	m_materialTeflon = m_pNistManager->FindOrBuildMaterial("G4_TEFLON");
	assert (m_materialTeflon != NULL);
	return true;
}

//-----------------------------------------------------------------------------

bool CIMaterials::ConstructGold() {
	m_materialGold = m_pNistManager->FindOrBuildMaterial("G4_Au");
	assert (m_materialGold != NULL);
	return true;
}


//-----------------------------------------------------------------------------

bool CIMaterials::ConstructCaF2() {
	m_materialCaF = m_pNistManager->FindOrBuildMaterial(m_CaF_Name);
	assert (m_materialCaF != NULL);

	// Define scintillation properties
	const G4double TimeConstant = 940.0 * ns;
	const G4double ScintillationYield = 19000. / MeV;
	// Only one time constant.
	const G4double ScintillationYieldRatio = 1.0;
	const G4double ScintillationResolutionScale = 1.0;

	// Define optical properties -- Melles  Griot + info from Hilger email
	const G4int nRefractiveI = 4;
	G4double RefractiveIndexEnergy[nRefractiveI] = { m_dNMtoEV / 355., m_dNMtoEV / 400., m_dNMtoEV / 486., m_dNMtoEV
			/ 587. };
	G4double RefractiveIndex[nRefractiveI] = { 1.446, 1.4419, 1.437, 1.433 };

	//From Henry extracted from the St. Gobain data sheet.
	const G4int nSpectrum = 13;
	G4double SpectrumEnergy[nSpectrum] = { m_dNMtoEV / 395., m_dNMtoEV / 400.0, m_dNMtoEV / 410.0, m_dNMtoEV / 415.0,
			m_dNMtoEV / 425.0, m_dNMtoEV / 435.0, m_dNMtoEV / 440.0, m_dNMtoEV / 450.0, m_dNMtoEV / 463.0, m_dNMtoEV
					/ 475.0, m_dNMtoEV / 500.0, m_dNMtoEV / 510.0, m_dNMtoEV / 520.0 };
	G4double
			SpectrumFraction[nSpectrum] = { 0.0, 0.015, 0.06, 0.2, 0.75, 1.0, 0.75, 0.5, 0.2, 0.11, 0.03, 0.01, 0.005 };
	//Normalize the spectrum so that the sum is unity.
	NormalizeSumToUnity(SpectrumFraction, nSpectrum);

	//From Melles Griot data (transmittance of 0.91) in region of interest and method of Ma et al (GEM TN-92-148) see also the Mao paper.
	// Probably not very accurate, but the transmittance is very high and good in a large range.
	const G4int nAbsorption = 2;
	G4double AbsorptionEnergy[nAbsorption] = { m_dNMtoEV / 350.0, m_dNMtoEV / 800. };
	G4double AbsorptionLength[nAbsorption] = { 147.* cm, 147. * cm};

	m_CaF2MaterialProperties = new G4MaterialPropertiesTable();
	m_CaF2MaterialProperties->AddProperty(m_ScintiFastSpectrumName, SpectrumEnergy, SpectrumFraction, nSpectrum);
	m_CaF2MaterialProperties->AddConstProperty(m_ScintiFastTimeConstName, TimeConstant);
	m_CaF2MaterialProperties->AddConstProperty(m_ScintiYieldName, ScintillationYield);
	m_CaF2MaterialProperties->AddConstProperty(m_ScintiYieldRatioName, ScintillationYieldRatio);
	m_CaF2MaterialProperties->AddConstProperty(m_ScintiResScaleName, ScintillationResolutionScale);

	m_CaF2MaterialProperties->AddProperty(m_OpticRefractiveIndexName, RefractiveIndexEnergy, RefractiveIndex, nRefractiveI);
	m_CaF2MaterialProperties->AddProperty(m_OpticAbsorptionLengthName, AbsorptionEnergy, AbsorptionLength, nAbsorption);

	m_materialCaF->SetMaterialPropertiesTable(m_CaF2MaterialProperties);

	return true;
}
//-----------------------------------------------------------------------------

bool CIMaterials::ConstructCsI() {
	m_materialCsI = m_pNistManager->FindOrBuildMaterial(m_CsI_Name);
	assert (m_materialCsI != NULL);

	// Define scintillation properties
	const G4double TimeConstant = 1000.0 * ns;
	const G4double ScintillationYield = 54000. / MeV;
	// Only one time constant.
	const G4double ScintillationYieldRatio = 1.0;
	const G4double ScintillationResolutionScale = 1.0;

	// Define optical properties Alkor.net data sheet.
	G4double RefractiveIndexEnergy[] = { m_dNMtoEV / 320., m_dNMtoEV / 350., m_dNMtoEV / 390., m_dNMtoEV / 460., m_dNMtoEV
			/ 520., m_dNMtoEV / 640., m_dNMtoEV / 920.};
	const G4int nRefractiveIndex = sizeof(RefractiveIndexEnergy)/sizeof(G4double);
	G4double RefractiveIndex[] = {1.94, 1.90, 1.86, 1.82, 1.80, 1.78, 1.76};
	assert(nRefractiveIndex == sizeof(RefractiveIndex)/sizeof(G4double));

	//From Henry extracted from the St. Gobain data sheet.
	G4double SpectrumEnergy[] = { m_dNMtoEV / 350., m_dNMtoEV / 375., m_dNMtoEV / 400., m_dNMtoEV / 425., m_dNMtoEV
			/ 450., m_dNMtoEV / 475., m_dNMtoEV / 500., m_dNMtoEV / 525., m_dNMtoEV / 550., m_dNMtoEV / 575., m_dNMtoEV / 600.,
			m_dNMtoEV / 625., m_dNMtoEV / 650., m_dNMtoEV / 675.  , m_dNMtoEV / 700.};
	const G4int nSpectrum = sizeof(SpectrumEnergy)/sizeof(G4double);
	G4double  SpectrumFraction[] = { 0.0, 0.007, 0.11, 0.18, 0.29, .40, 0.72, 0.93, 0.99, 0.86, 0.71, 0.56, 0.40, 0.24, 0.16 };
	assert(nSpectrum == sizeof(SpectrumFraction)/sizeof(G4double));
	//Normalize the spectrum so that the sum is unity.
	NormalizeSumToUnity(SpectrumFraction, nSpectrum);

	// From PDG (2008) table 28.4
	const G4int nAbsorption = 2;
	G4double AbsorptionEnergy[nAbsorption] = { m_dNMtoEV / 350.0, m_dNMtoEV / 800. };
	//G4double AbsorptionLength[nAbsorption] = { 39.3* cm, 39.3* cm };
	G4double AbsorptionLength[nAbsorption] = { 120.0* cm, 120.0* cm };

	m_CsIMaterialProperties = new G4MaterialPropertiesTable();
	m_CsIMaterialProperties->AddProperty(m_ScintiFastSpectrumName, SpectrumEnergy, SpectrumFraction, nSpectrum);
	m_CsIMaterialProperties->AddConstProperty(m_ScintiFastTimeConstName, TimeConstant);
	m_CsIMaterialProperties->AddConstProperty(m_ScintiYieldName, ScintillationYield);
	m_CsIMaterialProperties->AddConstProperty(m_ScintiYieldRatioName, ScintillationYieldRatio);
	m_CsIMaterialProperties->AddConstProperty(m_ScintiResScaleName, ScintillationResolutionScale);

	m_CsIMaterialProperties->AddProperty(m_OpticRefractiveIndexName, RefractiveIndexEnergy, RefractiveIndex, nRefractiveIndex);
	m_CsIMaterialProperties->AddProperty(m_OpticAbsorptionLengthName, AbsorptionEnergy, AbsorptionLength, nAbsorption);

	m_materialCsI->SetMaterialPropertiesTable(m_CsIMaterialProperties);

	return true;
}
//-----------------------------------------------------------------------------

bool CIMaterials::ConstructYAP() {

	// This is St. Gobain formulation
	// This is Y Al O3

	// Define the composition
	G4double density;
	const G4int nComponents = 3;
	m_materialYAP = new G4Material(m_YAP_Name, density = 5.55 * g / cm3, nComponents);
	assert (m_materialYAP != NULL);

	const G4double mass = 5.0;
	m_materialYAP->AddElement(m_elementY, 1.0 / mass);
	m_materialYAP->AddElement(m_elementAl, 1.0 / mass);
	m_materialYAP->AddElement(m_elementO, 3.0 / mass);

	// St. Gobain is 27ns
	const G4double TimeConstant = 27.0 * ns;
	//St Gobain is 18000/MeV
	const G4double ScintillationYield = 18000. / MeV;
	// Only one time constant.
	const G4double ScintillationYieldRatio = 1.0;
	const G4double ScintillationResolutionScale = 1.0;

	// Define optical properties
	// Obtained from S. Baccaro et. al NIMA 406 p 479
	G4double RefractiveIndexEnergy[] = {m_dNMtoEV / 300., m_dNMtoEV / 350., m_dNMtoEV / 400., m_dNMtoEV / 450., m_dNMtoEV / 500., m_dNMtoEV / 550.};
	G4double RefractiveIndex[] = { 1.963, 1.938, 1.923, 1.915, 1.909, 1.905};
	const G4int nRefractiveI = sizeof(RefractiveIndexEnergy)/sizeof(G4double);
	assert(nRefractiveI == sizeof(RefractiveIndex)/sizeof(G4double));

	//From Henry extracted from Petr Wandrol and Petr HorÃÂ¡k, Microsc Microanal 13 (Suppl 3), 2007.
	G4double SpectrumEnergy[] = { m_dNMtoEV / 475., m_dNMtoEV / 450., m_dNMtoEV / 425., m_dNMtoEV / 400., m_dNMtoEV
			/ 375., m_dNMtoEV / 350., m_dNMtoEV / 325., m_dNMtoEV / 300.};
	const G4int nSpectrum = sizeof(SpectrumEnergy)/sizeof(G4double);
	G4double SpectrumFraction[] = {0.00, 0.02, 0.075, 0.32, 0.85, 0.80, 0.03, 0.00};
	assert(nSpectrum == sizeof(SpectrumFraction)/sizeof(G4double));
	//Normalize the spectrum so that the sum is unity.
	NormalizeSumToUnity(SpectrumFraction, nSpectrum);

	// Obtained from S. Baccaro et. al NIMA 406 p 479
	G4double AbsorptionEnergy[] = { m_dNMtoEV / 500.,  m_dNMtoEV / 450., m_dNMtoEV / 425., m_dNMtoEV / 400., m_dNMtoEV
			/ 375., m_dNMtoEV / 350., m_dNMtoEV / 325., m_dNMtoEV / 250.};
	G4double AbsorptionLength[] = { 20*cm, 16*cm, 18*cm, 16*cm, 13*cm, 8*cm, 0*cm, 0*cm};
	const G4int nAbsorption = sizeof(AbsorptionEnergy)/sizeof(G4double);
	assert(nAbsorption == sizeof(AbsorptionLength)/sizeof(G4double));

	m_YAPMaterialProperties = new G4MaterialPropertiesTable();
	m_YAPMaterialProperties->AddProperty(m_ScintiFastSpectrumName, SpectrumEnergy, SpectrumFraction, nSpectrum);
	m_YAPMaterialProperties->AddConstProperty(m_ScintiFastTimeConstName, TimeConstant);
	m_YAPMaterialProperties->AddConstProperty(m_ScintiYieldName, ScintillationYield);
	m_YAPMaterialProperties->AddConstProperty(m_ScintiYieldRatioName, ScintillationYieldRatio);
	m_YAPMaterialProperties->AddConstProperty(m_ScintiResScaleName, ScintillationResolutionScale);

	m_YAPMaterialProperties->AddProperty(m_OpticRefractiveIndexName, RefractiveIndexEnergy, RefractiveIndex, nRefractiveI);
	m_YAPMaterialProperties->AddProperty(m_OpticAbsorptionLengthName, AbsorptionEnergy, AbsorptionLength, nAbsorption);

	m_materialYAP->SetMaterialPropertiesTable(m_YAPMaterialProperties);
	return true;


	return true;
}
//-----------------------------------------------------------------------------

bool CIMaterials::ConstructLaBr3() {

	// This is St. Gobain formulation
	// Leave out the Ce dopant, concentration probably small, not indicated in St. Gobain data sheet.
	// This is La(1), Br(3)

	// Define the composition
	G4double density;
	const G4int nComponents = 2;
	m_materialLaBr3 = new G4Material(m_LaBr3_Name, density = 5.08 * g / cm3, nComponents);
	assert (m_materialLaBr3 != NULL);

	m_materialLaBr3->AddElement(m_elementLa, 1);
	m_materialLaBr3->AddElement(m_elementBr, 3);

	const G4double TimeConstant = 16.0 * ns;
	const G4double ScintillationYield = 63000. / MeV;
	// Only one time constant.
	const G4double ScintillationYieldRatio = 1.0;
	const G4double ScintillationResolutionScale = 1.0;

	// Define optical properties
	const G4int nRefractiveI = 2;
	// No wavelength dependence has been measured, value is approximate
	G4double RefractiveIndexEnergy[nRefractiveI] = { m_dNMtoEV / 650., m_dNMtoEV / 200. };
	G4double RefractiveIndex[nRefractiveI] = { 1.9, 1.9 };

	//From Henry extracted from the St. Gobain data sheet.
	const G4int nSpectrum = 12;
	G4double SpectrumEnergy[nSpectrum] = { m_dNMtoEV / 450.0, m_dNMtoEV / 445.5, m_dNMtoEV / 441.0, m_dNMtoEV / 423.0,
			m_dNMtoEV / 413.5, m_dNMtoEV / 405.0, m_dNMtoEV / 386.0, m_dNMtoEV / 368.0, m_dNMtoEV / 357.0, m_dNMtoEV
					/ 350.0, m_dNMtoEV / 342.0, m_dNMtoEV / 335.0 };
	G4double SpectrumFraction[nSpectrum] = { 0.1, 0.5, 1.0, 2.0, 16.0, 22.5, 29.0, 29.0, 23.5, 18.0, 0.6, 0.0 };

	//   G4double SpectrumEnergy[nSpectrum]    = {m_dNMtoEV / 450.0, m_dNMtoEV / 441.0, m_dNMtoEV / 423.0, m_dNMtoEV / 405.0, m_dNMtoEV / 386.0,  m_dNMtoEV / 368.0, m_dNMtoEV / 350.0, m_dNMtoEV / 342.0, m_dNMtoEV / 335.0};
	//   G4double SpectrumFraction[nSpectrum]  = {1.0,             1.0,             1.0,             1.0,            1.0,             1.0,            1.0,            1.0,             1.0};

	//Normalize the spectrum so that the sum is unity.
	NormalizeSumToUnity(SpectrumFraction, nSpectrum);

	// Guess that LaBr3 and LYSO are about the same, i.e. poorer than NaI
	const G4int nAbsorption = 5;
	G4double AbsorptionEnergy[nAbsorption] = { m_dNMtoEV / 200., m_dNMtoEV / 375., m_dNMtoEV / 425, m_dNMtoEV / 450,
			m_dNMtoEV / 1000. };
	G4double AbsorptionLength[nAbsorption] = { 0.1* cm, 7.* cm, 25.* cm, 35.0* cm, 35.0* cm };

	m_LaBr3MaterialProperties = new G4MaterialPropertiesTable();
	m_LaBr3MaterialProperties->AddProperty(m_ScintiFastSpectrumName, SpectrumEnergy, SpectrumFraction, nSpectrum);
	m_LaBr3MaterialProperties->AddConstProperty(m_ScintiFastTimeConstName, TimeConstant);
	m_LaBr3MaterialProperties->AddConstProperty(m_ScintiYieldName, ScintillationYield);
	m_LaBr3MaterialProperties->AddConstProperty(m_ScintiYieldRatioName, ScintillationYieldRatio);
	m_LaBr3MaterialProperties->AddConstProperty(m_ScintiResScaleName, ScintillationResolutionScale);

	m_LaBr3MaterialProperties->AddProperty(m_OpticRefractiveIndexName, RefractiveIndexEnergy, RefractiveIndex, nRefractiveI);
	m_LaBr3MaterialProperties->AddProperty(m_OpticAbsorptionLengthName, AbsorptionEnergy, AbsorptionLength, nAbsorption);

	m_materialLaBr3->SetMaterialPropertiesTable(m_LaBr3MaterialProperties);
	return true;
}
//-----------------------------------------------------------------------------

bool CIMaterials::ConstructPVT() {

	m_materialPVT = m_pNistManager->FindOrBuildMaterial(m_PVT_Name);
	assert (m_materialPVT != NULL);

	const G4double TimeConstant = 2.1 * ns;
	const G4double ScintillationYield = 10000. / MeV;
	// Only one time constant.
	const G4double ScintillationYieldRatio = 1.0;
	const G4double ScintillationResolutionScale = 1.0;

	// Define optical properties
	const G4int nRefractiveI = 2;
	// No wavelength dependence has been found, value is approximate
	G4double RefractiveIndexEnergy[nRefractiveI] = { m_dNMtoEV / 650., m_dNMtoEV / 200. };
	G4double RefractiveIndex[nRefractiveI] = { 1.58, 1.58 };

	//From Audrey extracted from the St. Gobain data sheet.
	const G4int nSpectrum = 12;
	G4double SpectrumEnergy[nSpectrum] = { 2.08 * eV, 2.38 * eV, 2.58 * eV, 2.7 * eV, 2.76 * eV, 2.82 * eV, 2.92 * eV,
			2.95 * eV, 3.02 * eV, 3.1 * eV, 3.26 * eV, 3.44 * eV };
	G4double SpectrumFraction[nSpectrum] = { 0.0, 0.03, 0.17, 0.40, 0.55, 0.83, 1.00, 0.84, 0.49, 0.20, 0.07, 0.04 };
	//Normalize the spectrum so that the sum is unity.
	NormalizeSumToUnity(SpectrumFraction, nSpectrum);

	// Given from St. Gobain data sheet
	const G4int nAbsorption = 2;
	G4double AbsorptionEnergy[nAbsorption] = { 1.5 * eV, 5.0 * eV };
	//G4double AbsorptionLength[nAbsorption] = { 210. * cm, 210. * cm };
	//	G4double AbsorptionLength[nAbsorption] = { 150. * cm, 150. * cm }; //made up value.. chnage back
		G4double AbsorptionLength[nAbsorption] = { 500. * cm, 500. * cm }; //made up value.. chnage back


	m_PVTMaterialProperties = new G4MaterialPropertiesTable();
	m_PVTMaterialProperties->AddProperty(m_ScintiFastSpectrumName, SpectrumEnergy, SpectrumFraction, nSpectrum);
	m_PVTMaterialProperties->AddConstProperty(m_ScintiFastTimeConstName, TimeConstant);
	m_PVTMaterialProperties->AddConstProperty(m_ScintiYieldName, ScintillationYield);
	m_PVTMaterialProperties->AddConstProperty(m_ScintiYieldRatioName, ScintillationYieldRatio);
	m_PVTMaterialProperties->AddConstProperty(m_ScintiResScaleName, ScintillationResolutionScale);

	m_PVTMaterialProperties->AddProperty(m_OpticRefractiveIndexName, RefractiveIndexEnergy, RefractiveIndex, nRefractiveI);
	m_PVTMaterialProperties->AddProperty(m_OpticAbsorptionLengthName, AbsorptionEnergy, AbsorptionLength, nAbsorption);

	m_materialPVT->SetMaterialPropertiesTable(m_PVTMaterialProperties);
	return true;

}

//-----------------------------------------------------------------------------

bool CIMaterials::ConstructOpticalCompound() {

	// Define the composition: Visilox V-788 is methyl-phenyl polysiloxane, Wikipedia indicates Polydimethylsiloxane = (C2-H6-O-Si)n
	// which should be close enough
	G4double density;
	const G4int nComponent = 4;
	m_materialOpticalCompound = new G4Material(m_OpticalCompound_Name, density = 1.06 * g / cm3, nComponent);
	assert (m_materialOpticalCompound != NULL);
	m_materialOpticalCompound->AddElement(m_elementC, 2);
	m_materialOpticalCompound->AddElement(m_elementH, 6);
	m_materialOpticalCompound->AddElement(m_elementO, 1);
	m_materialOpticalCompound->AddElement(m_elementSi, 1);

	// Refractive Index is from Visilox V-788 data sheet. Dow Corning Q23067 has 1.4658
	const G4int nRefr = 2, nAbs = 2;
	G4double RefractiveIndexEnergy[nRefr] = { 1.55 * eV, 6.19 * eV };
	G4double RefractiveIndex[nRefr] = { 1.463, 1.463 };

	G4double AbsorptionEnergy[nAbs] = { 6.19 * eV, 1.55 * eV };
	G4double AbsorptionLength[nAbs] = { 30. * cm, 30. * cm };
	m_OpticalCompoundMaterialProperties = new G4MaterialPropertiesTable();

	m_OpticalCompoundMaterialProperties->AddProperty(m_OpticRefractiveIndexName, RefractiveIndexEnergy, RefractiveIndex, nRefr);
	m_OpticalCompoundMaterialProperties->AddProperty(m_OpticAbsorptionLengthName, AbsorptionEnergy, AbsorptionLength, nAbs);

	m_materialOpticalCompound->SetMaterialPropertiesTable(m_OpticalCompoundMaterialProperties);

	return true;
}
//-----------------------------------------------------------------------------


bool CIMaterials::ConstructAir() {

	m_materialAir = m_pNistManager->FindOrBuildMaterial(m_Air_Name);
	assert (m_materialAir != NULL);

	const G4int nRefr = 2, nAbs = 2;
	G4double RefractiveIndexEnergy[nRefr] = { 10.0 * eV, 1.0 * eV };
	G4double RefractiveIndex[nRefr] = { 1.0, 1.0 };

	G4double AbsorptionEnergy[nAbs] = { 10.0 * eV, 1.0 * eV };
	G4double AbsorptionLength[nAbs] = { 30. * m, 30. * m };

	m_AirMaterialProperties = new G4MaterialPropertiesTable();

	m_AirMaterialProperties->AddProperty(m_OpticRefractiveIndexName, RefractiveIndexEnergy, RefractiveIndex, nRefr);
	m_AirMaterialProperties->AddProperty(m_OpticAbsorptionLengthName, AbsorptionEnergy, AbsorptionLength, nAbs);

	m_materialAir->SetMaterialPropertiesTable(m_AirMaterialProperties);

	return true;
}
//-----------------------------------------------------------------------------


bool CIMaterials::ConstructVacuum() {

  //	m_materialAir = m_pNistManager->FindOrBuildMaterial(m_Vacuum_Name);
  //	assert (m_materialVacuum != NULL);

	G4double density     = universe_mean_density;                //from PhysicalConstants.h
	G4double pressure    = 1.e-19*pascal;
	G4double temperature = 0.1*kelvin;
	
	m_materialVacuum = new G4Material(m_Vacuum_Name, density, 1,
					  kStateGas, temperature, pressure);
	m_materialVacuum->AddMaterial(GetMaterial(m_Air_Name), 1);
	
	assert (m_materialVacuum != NULL);

	return true;
}

//-----------------------------------------------------------------------------


bool CIMaterials::ConstructOpaqueAir() {

	m_materialOpaqueAir = m_pNistManager->FindOrBuildMaterial(m_Air_Name);
	assert (m_materialOpaqueAir != NULL);


	const G4int nRefr = 2, nAbs = 2;
	G4double RefractiveIndexEnergy[nRefr] = { 10.0 * eV, 1.0 * eV };
	G4double RefractiveIndex[nRefr] = { 1.00, 1.00 };

	G4double AbsorptionEnergy[nAbs] = { 100.0 * eV, 0.001 * eV };
	// Per Jojo
	// Non zero absorbtion length so that total internal reflection works correctly.
	//	G4double AbsorptionLength[nAbs] = { 0.00001* cm, 0.00001 * cm}; //put back
	G4double AbsorptionLength[nAbs] = { 30. * m, 30. * m };


	m_OpaqueAirMaterialProperties = new G4MaterialPropertiesTable();

	m_OpaqueAirMaterialProperties->AddProperty(m_OpticRefractiveIndexName, RefractiveIndexEnergy, RefractiveIndex, nRefr);
	m_OpaqueAirMaterialProperties->AddProperty(m_OpticAbsorptionLengthName, AbsorptionEnergy, AbsorptionLength, nAbs);

	m_materialOpaqueAir->SetMaterialPropertiesTable(m_OpaqueAirMaterialProperties);

	return true;
}

//-----------------------------------------------------------------------------


bool CIMaterials::ConstructGlass() {

	m_materialGlass = m_pNistManager->FindOrBuildMaterial(m_Glass_Name);
	assert (m_materialGlass != NULL);
	// Define optical properties
	// Refractive Index and Absorption length are obtained from the list of materials for borosilicate glass according to the GLG4 database,
	// TODO review that these values are correct for the K+ glass too.
	const G4int nRefr = 7, nAbs = 2;
	G4double RefractiveIndexEnergy[nRefr] = { 6.19 * eV, 4.13 * eV, 3.10 * eV, 2.76 * eV, 2.47 * eV, 2.07 * eV, 1.55
			* eV };
	G4double RefractiveIndex[nRefr] = { 1.57, 1.51, 1.496, 1.491, 1.487, 1.482, 1.478 };

	G4double AbsorptionEnergy[nAbs] = { 6.19 * eV, 1.55 * eV };
	G4double AbsorptionLength[nAbs] = { 300. * mm, 300. * m };
	// Extracted from the data sheet: SPM_Plus Aug 2008
	//G4double photonEnergyAbs[nEntriesEffic] = { 300, 400, 500, 700, 1000, 1500};
	//G4double Absorption[nEntriesEffic]      = { 0,                 0.90               0.92               0.91               0.90,               0.93};


	m_GlassMaterialProperties = new G4MaterialPropertiesTable();

	m_GlassMaterialProperties->AddProperty(m_OpticRefractiveIndexName, RefractiveIndexEnergy, RefractiveIndex, nRefr);
	m_GlassMaterialProperties->AddProperty(m_OpticAbsorptionLengthName, AbsorptionEnergy, AbsorptionLength, nAbs);

	m_materialGlass->SetMaterialPropertiesTable(m_GlassMaterialProperties);

	return true;
}
//-----------------------------------------------------------------------------

bool CIMaterials::ConstructFR4() {
	G4double density;
        G4int nComponent = 2;

	G4Material* SiO2 = 
	  new G4Material("quartz",density= 2.61*g/cm3, nComponent);
	SiO2->AddElement(m_elementSi, 1);
	SiO2->AddElement(m_elementO ,2);
	//	m_elementSi = m_pNistManager->FindOrBuildElement(m_Si_Name
	//http://www.phenix.bnl.gov/~suhanov/ncc/geant/rad-source/src/ExN03DetectorConstruction.cc
	// materials for rad-source setup
	//
	//from http://www.physi.uni-heidelberg.de/~adler/TRD/TRDunterlagen/RadiatonLength/tgc2.htmno
	//Epoxy (for FR4 )

	density = 1.19*g/cm3;
	nComponent=3;
	G4Material* Epoxy = new G4Material("Epoxy" , density, nComponent);
	Epoxy->AddElement(m_elementH,20);
	Epoxy->AddElement(m_elementC,19);
	Epoxy->AddElement(m_elementO,4);

	nComponent =2;
	//FR4 (Glass + Epoxy)
        density = 1.7*g/cm3;

	m_materialFR4 = new G4Material("FR4"  , density, nComponent);
	assert (m_materialFR4 != NULL);
	
	m_materialFR4->AddMaterial(SiO2, 0.6);
	m_materialFR4->AddMaterial(Epoxy, 0.4);

	return true;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

bool CIMaterials::ConstructCarbonFibre() {

	G4double density =1.533*g/cm3;

	//	G4NistManager* man = G4NistManager::Instance();
	//	m_materialCarbonFibre= man->BuildMaterialWithNewDensity(m_CarbonFibre_Name,"G4_C",density);
	const G4int nComponent = 2;

	// Materials from Combination
	m_materialCarbonFibre = new G4Material(m_CarbonFibre_Name, density, nComponent);
	m_materialCarbonFibre->AddElement(m_elementC,2);
	m_materialCarbonFibre->AddElement(m_elementH,1);
	
	assert (m_materialCarbonFibre != NULL);
	return true;







}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

bool CIMaterials::ConstructPlastazote() {


   G4double density;

  density = 45*kg/m3;
  G4NistManager* man = G4NistManager::Instance();
  m_materialPlastazote = man->BuildMaterialWithNewDensity(m_Plastazote_Name,"G4_POLYETHYLENE",density);

  assert (m_materialPlastazote != NULL);

  return true;
}
//-----------------------------------------------------------------------------


bool CIMaterials::ConstructQuartz() {

	m_materialQuartz = m_pNistManager->FindOrBuildMaterial(m_Glass_Name);
	assert (m_materialQuartz != NULL);
	// Define optical properties
	// Refractive Index and Absorption length are obtained from the list of materials for borosilicate glass according to the GLG4 database,
	// TODO review that these values are correct for the K+ glass too.
	const G4int nRefr = 7, nAbs = 2;
	G4double RefractiveIndexEnergy[nRefr] = { 6.19 * eV, 4.13 * eV, 3.10 * eV, 2.76 * eV, 2.47 * eV, 2.07 * eV, 1.55* eV };
	G4double RefractiveIndex[nRefr] = { 1.45, 1.45, 1.45, 1.45, 1.45, 1.45, 1.45};

	G4double AbsorptionEnergy[nAbs] = { 6.19 * eV, 1.55 * eV };
	G4double AbsorptionLength[nAbs] = { 300. * mm, 300. * m };
	// Extracted from the data sheet: SPM_Plus Aug 2008
	//G4double photonEnergyAbs[nEntriesEffic] = { 300, 400, 500, 700, 1000, 1500};
	//G4double Absorption[nEntriesEffic]      = { 0,                 0.90               0.92               0.91               0.90,               0.93};

	m_QuartzMaterialProperties = new G4MaterialPropertiesTable();

	m_QuartzMaterialProperties->AddProperty(m_OpticRefractiveIndexName, RefractiveIndexEnergy, RefractiveIndex, nRefr);
	m_QuartzMaterialProperties->AddProperty(m_OpticAbsorptionLengthName, AbsorptionEnergy, AbsorptionLength, nAbs);

	m_materialQuartz->SetMaterialPropertiesTable(m_QuartzMaterialProperties);

	return true;
}

//-----------------------------------------------------------------------------
bool CIMaterials::ConstructMuMetal() {

	G4double density;
	const G4int nComponent = 4;
	m_materialMuMetal = new G4Material(m_MuMetal_MatName, density = 8.7 * g / cm3, nComponent);
	assert (m_materialMuMetal != NULL);

	m_materialMuMetal->AddElement(m_elementNi, 0.77);
	m_materialMuMetal->AddElement(m_elementFe, 0.16);
	m_materialMuMetal->AddElement(m_elementCu, 0.05);
	m_materialMuMetal->AddElement(m_elementCr, 0.02);
	return true;
}

//-----------------------------------------------------------------------------
bool CIMaterials::ConstructBrass() {

	G4double density;
	const G4int nComponent = 2;
	m_materialBrass = new G4Material(m_Brass_MatName, density = 8.4 * g / cm3, nComponent);
	assert (m_materialBrass != NULL);

	m_materialBrass->AddElement(m_elementCu, 0.63);
	m_materialBrass->AddElement(m_elementZn, 0.37);
	return true;
}

//-----------------------------------------------------------------------------
bool CIMaterials::ConstructSiPM() {

	//For simplicities sake we assume pure silicon, and set to be optically opaque
	// Define the composition
	G4double density;
	const G4int nComponents = 1;
	m_materialSiPM = new G4Material(m_SiPM_Name, density = 2.33 * g / cm3, nComponents);
	m_materialSiPM->AddElement(m_elementSi, 2);
	assert (m_materialSiPM != NULL);

	const G4int nAbs = 2;
	G4double AbsorptionEnergy[nAbs] = { 1.0 * eV, 10.0 * eV };
	G4double AbsorptionLength[nAbs] = { 0,        0 };

	m_SiPMMaterialProperties = new G4MaterialPropertiesTable();
	m_SiPMMaterialProperties->AddProperty(m_OpticAbsorptionLengthName, AbsorptionEnergy, AbsorptionLength, nAbs);
	m_materialSiPM->SetMaterialPropertiesTable(m_SiPMMaterialProperties);

	return true;
}

//-----------------------------------------------------------------------------
bool CIMaterials::ConstructSiO2() {

	//For simplicities sake we assume pure silicon, and set to be optically opaque
	// Define the composition
	G4double density;
	const int nComponents = 2;
	m_materialSiO2 = new G4Material(m_SiO2_Name, density = 2.65 * g / cm3, nComponents);
	m_materialSiO2->AddElement(m_elementSi, 1);
	m_materialSiO2->AddElement(m_elementO, 2);
	assert (m_materialSiO2 != NULL);

	return true;
}
//-----------------------------------------------------------------------------

void CIMaterials::ConstructSurfaceSPM3035X08() {
	// A very simple surface for the Coupling Compound to the SiPM element
	m_surfaceSPM3035X08 = new G4OpticalSurface("CouplingToElement" + m_OpticalSurfaceSuffix);

	m_surfaceSPM3035X08 -> SetType(dielectric_metal);
	m_surfaceSPM3035X08 -> SetModel(unified);
	m_surfaceSPM3035X08 -> SetFinish(polished);

	//TODO Verify values
	const int nEntries = 2;
	G4double photonEnergy[nEntries] = { 20.19 * eV, 0.55 * eV };
	G4double reflectivity[nEntries] = { 0., .0 };
	// Values extracted by eye from datashee quantum efficiency graph, numbers are the Q.E.
	const int nEntriesEffic = 23;
	G4double photonEnergyEffic[nEntriesEffic] = { m_dNMtoEV / 200, m_dNMtoEV / 380., m_dNMtoEV / 400, m_dNMtoEV / 420,
			m_dNMtoEV / 440, m_dNMtoEV / 460, m_dNMtoEV / 480, m_dNMtoEV / 500, m_dNMtoEV / 520, m_dNMtoEV / 540,
			m_dNMtoEV / 560, m_dNMtoEV / 580, m_dNMtoEV / 600, m_dNMtoEV / 620, m_dNMtoEV / 640, m_dNMtoEV / 660,
			m_dNMtoEV / 680, m_dNMtoEV / 700, m_dNMtoEV / 720, m_dNMtoEV / 740, m_dNMtoEV / 760, m_dNMtoEV / 780 };
	G4double efficiency[nEntriesEffic] = { 0.0, 0.000, 0.062, 0.093, 0.110, 0.128, 0.132, 0.132, 0.135, 0.129, 0.118,
			0.116, 0.112, 0.105, 0.096, 0.090, 0.081, 0.079, 0.073, 0.068, 0.060, 0.053 };
	/*                                                G4double efficiency[nEntriesEffic]        = { 0.0,           0.031, 0.062,         0.0062,         0.062,        0.062,          0.0,         0.0,         0.0,
	 0.0,         0.0,         0.0,         0.0,         0.0,         0.0,         0.0,         0.0,         0.0,         0.0,         0.0,         0.0,         0.0
	 };*/
//	G4double PerfectEfficiency[nEntriesEffic] = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
//			1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };

	m_SPM3035X08MaterialProperties = new G4MaterialPropertiesTable();
	m_SPM3035X08MaterialProperties -> AddProperty(m_OpticDetectionEfficiencyName, photonEnergyEffic, efficiency,
			nEntriesEffic);
	m_SPM3035X08MaterialProperties -> AddProperty(m_OpticReflectivityName, photonEnergy, reflectivity, nEntries);
	m_surfaceSPM3035X08 -> SetMaterialPropertiesTable(m_SPM3035X08MaterialProperties);

	// Additional information for the module from the data sheet: SPM_Plus Aug 2008
	// Glass thickness 550um - size 20.1, 15.5
	// Metal tracks CrNi -50nm, Ti -100nm, Au -2000nm, 150-300um width
	// Macro pixel spacing 3.3mm
	return;
}

//-----------------------------------------------------------------------------

void CIMaterials::ConstructSurfaceTest() {
	// A very simple surface for the testing optical photon detection
	m_surfaceTest = new G4OpticalSurface(m_TestSurface_Name + m_OpticalSurfaceSuffix);

	m_surfaceTest -> SetType(dielectric_metal);
	m_surfaceTest -> SetModel(unified);
	m_surfaceTest -> SetFinish(polished);

	const int nEntries = 2;
	G4double photonEnergy[nEntries] = { 20.19 * eV, 0.55 * eV };
	G4double reflectivity[nEntries] = { 0., .0 };
	// For the test surface we have perfect efficiency
	const int nEntriesEffic = 22;
	G4double photonEnergyEffic[nEntriesEffic] = { m_dNMtoEV / 200, m_dNMtoEV / 380, m_dNMtoEV / 400, m_dNMtoEV / 420,
			m_dNMtoEV / 440, m_dNMtoEV / 460, m_dNMtoEV / 480, m_dNMtoEV / 500, m_dNMtoEV / 520, m_dNMtoEV / 540,
			m_dNMtoEV / 560, m_dNMtoEV / 580, m_dNMtoEV / 600, m_dNMtoEV / 620, m_dNMtoEV / 640, m_dNMtoEV / 660,
			m_dNMtoEV / 680, m_dNMtoEV / 700, m_dNMtoEV / 720, m_dNMtoEV / 740, m_dNMtoEV / 760, m_dNMtoEV / 780 };
	G4double PerfectEfficiency[nEntriesEffic] = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
			1.0, 1.0, 1.0, 1.0, 1.0, 1.0, };

	m_TestMaterialProperties = new G4MaterialPropertiesTable();
	m_TestMaterialProperties -> AddProperty(m_OpticDetectionEfficiencyName, photonEnergyEffic, PerfectEfficiency,
			nEntriesEffic);
	m_TestMaterialProperties -> AddProperty(m_OpticReflectivityName, photonEnergy, reflectivity, nEntries);
	m_surfaceTest -> SetMaterialPropertiesTable(m_TestMaterialProperties);

	return;
}

//-----------------------------------------------------------------------------

void CIMaterials::ConstructSurfaceWhite() {
	// A very simple surface for reflection

	m_surfaceWhite = new G4OpticalSurface(m_WhiteSurface_Name + m_OpticalSurfaceSuffix);

	m_surfaceWhite -> SetType(dielectric_metal);

	//	m_surfaceWhite -> SetType(dielectric_dielectric);
	m_surfaceWhite -> SetModel(unified);
	m_surfaceWhite -> SetFinish(polishedfrontpainted);

	//Surface reflects almost perfectly over entire range of interest
	const int nEntries = 2;
	G4double photonEnergy[nEntries] = { 20. * eV, 0.5 * eV };
	G4double reflectivity[nEntries] = { 0.96, 0.96 };
	


	m_SurfaceWhiteMaterialProperties = new G4MaterialPropertiesTable();

	m_SurfaceWhiteMaterialProperties -> AddProperty(m_OpticReflectivityName, photonEnergy, reflectivity, nEntries);

	m_surfaceWhite -> SetMaterialPropertiesTable(m_SurfaceWhiteMaterialProperties);

	return;
}

//-----------------------------------------------------------------------------

void CIMaterials::ConstructSurfaceBlack() {
	// A very simple surface for absolute absorption
	m_surfaceBlack = new G4OpticalSurface(m_BlackSurface_Name + m_OpticalSurfaceSuffix);

	m_surfaceBlack -> SetType(dielectric_dielectric);
	m_surfaceBlack -> SetModel(unified);
	m_surfaceBlack -> SetFinish(polishedfrontpainted);

	//Surface absorbs over entire range of interest
	const int nEntries = 2;
	G4double photonEnergy[nEntries] = { 20. * eV, 0.5 * eV };
	G4double reflectivity[nEntries] = { 0., 0. };

	m_SurfaceBlackMaterialProperties = new G4MaterialPropertiesTable();
	m_SurfaceBlackMaterialProperties -> AddProperty(m_OpticReflectivityName, photonEnergy, reflectivity, nEntries);
	m_surfaceBlack -> SetMaterialPropertiesTable(m_SurfaceBlackMaterialProperties);

	return;
}

//-----------------------------------------------------------------------------

void CIMaterials::ConstructSurfaceMirror() {
	// A very simple surface for absolute reflection
	m_surfaceMirror = new G4OpticalSurface(m_MirrorSurface_Name + m_OpticalSurfaceSuffix);

	m_surfaceMirror -> SetType(dielectric_metal);
	m_surfaceMirror -> SetModel(unified);
	m_surfaceMirror -> SetFinish(polished);

	//Surface reflects perfectly over entire range of interst
	const int nEntries = 2;
	G4double photonEnergy[nEntries] = { 20. * eV, 0.5 * eV };
	G4double reflectivity[nEntries] = { 1.0, 1.0 };

	m_SurfaceMirrorMaterialProperties = new G4MaterialPropertiesTable();
	m_SurfaceMirrorMaterialProperties -> AddProperty(m_OpticReflectivityName, photonEnergy, reflectivity, nEntries);
	m_surfaceMirror -> SetMaterialPropertiesTable(m_SurfaceMirrorMaterialProperties);

	return;
}


//-----------------------------------------------------------------------------

void CIMaterials::ConstructSurfacePolishedDielectric() {
	// A polished surface for reflection

	m_surfacePolishedDielectric = new G4OpticalSurface(m_PolishedDielectricSurface_Name + m_OpticalSurfaceSuffix);

	m_surfacePolishedDielectric -> SetType(dielectric_dielectric);
	m_surfacePolishedDielectric -> SetModel(unified);
	m_surfacePolishedDielectric -> SetFinish(polished);

	return;
}



//-----------------------------------------------------------------------------

void CIMaterials::ConstructSurfaceWrapTYVEK() {

	// A polished surface for reflection

	m_surfaceWrapTYVEK = new G4OpticalSurface(m_WrapTYVEKSurface_Name + m_OpticalSurfaceSuffix);

	m_surfaceWrapTYVEK -> SetType(dielectric_metal);
	m_surfaceWrapTYVEK -> SetModel(unified);
	m_surfaceWrapTYVEK -> SetFinish(polished);

	const G4int NUM = 2;

	G4double pp[NUM] = {1.0*eV, 20.0*eV};
	G4double reflectivity[NUM] = {0.99, 0.99};
	G4double efficiency[NUM] = {0.0, 0.0};

	m_TyvekMaterialProperties = new G4MaterialPropertiesTable();

	m_TyvekMaterialProperties->AddProperty("REFLECTIVITY",pp,reflectivity,NUM);
	m_TyvekMaterialProperties->AddProperty("EFFICIENCY",pp,efficiency,NUM);

	m_surfaceWrapTYVEK->SetMaterialPropertiesTable(m_TyvekMaterialProperties);

	return;
}

//-----------------------------------------------------------------------------

void CIMaterials::ConstructSurfaceGroundDielectric() {
	// A polished surface for reflection

	m_surfaceGroundDielectric = new G4OpticalSurface(m_GroundDielectricSurface_Name + m_OpticalSurfaceSuffix);

	m_surfaceGroundDielectric -> SetType(dielectric_dielectric);
	m_surfaceGroundDielectric -> SetModel(unified);
	m_surfaceGroundDielectric -> SetFinish(ground);

	return;
}


//-----------------------------------------------------------------------------

void CIMaterials::ConstructSurfaceSPMS11064_100() {
	// A very simple surface for the Coupling Compound to the SiPM element
	m_surfaceSPM3035X08 = new G4OpticalSurface("CouplingToElement" + m_OpticalSurfaceSuffix);

	m_surfaceSPM3035X08 -> SetType(dielectric_metal);
	m_surfaceSPM3035X08 -> SetModel(unified);
	m_surfaceSPM3035X08 -> SetFinish(polished);

	//TODO Verify values
	const int nEntries = 2;
	G4double photonEnergy[nEntries] = { 20.19 * eV, 0.55 * eV };
	G4double reflectivity[nEntries] = { 0., .0 };
	// Values extracted by eye from datashee quantum efficiency graph, numbers are the Q.E.
	const int nEntriesEffic = 23;
	G4double photonEnergyEffic[nEntriesEffic] = { m_dNMtoEV / 200, m_dNMtoEV / 380., m_dNMtoEV / 400, m_dNMtoEV / 420,
			m_dNMtoEV / 440, m_dNMtoEV / 460, m_dNMtoEV / 480, m_dNMtoEV / 500, m_dNMtoEV / 520, m_dNMtoEV / 540,
			m_dNMtoEV / 560, m_dNMtoEV / 580, m_dNMtoEV / 600, m_dNMtoEV / 620, m_dNMtoEV / 640, m_dNMtoEV / 660,
			m_dNMtoEV / 680, m_dNMtoEV / 700, m_dNMtoEV / 720, m_dNMtoEV / 740, m_dNMtoEV / 760, m_dNMtoEV / 780 };
	G4double efficiency[nEntriesEffic] = { 0.0, 0.000, 0.062, 0.093, 0.110, 0.128, 0.132, 0.132, 0.135, 0.129, 0.118,
			0.116, 0.112, 0.105, 0.096, 0.090, 0.081, 0.079, 0.073, 0.068, 0.060, 0.053 };

//	G4double PerfectEfficiency[nEntriesEffic] = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
//			1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };

	G4MaterialPropertiesTable* theMaterialProperties = new G4MaterialPropertiesTable();
	theMaterialProperties -> AddProperty(m_OpticDetectionEfficiencyName, photonEnergyEffic, efficiency,
			nEntriesEffic);
	theMaterialProperties -> AddProperty(m_OpticReflectivityName, photonEnergy, reflectivity, nEntries);
	m_surfaceSPM3035X08 -> SetMaterialPropertiesTable(theMaterialProperties);

	// Additional information for the module from the data sheet: SPM_Plus Aug 2008
	// Glass thickness 550um - size 20.1, 15.5
	// Metal tracks CrNi -50nm, Ti -100nm, Au -2000nm, 150-300um width
	// Macro pixel spacing 3.3mm
	return;
}

//-----------------------------------------------------------------------------
void CIMaterials::NormalizeSumToUnity(double* vector, const int size) {
	double sum = 0.0;
	for (int i = 0; i < size; i++)
		sum += vector[i];
	for (int i = 0; i < size; i++)
		vector[i] /= sum;
}



//-----------------------------------------------------------------------------
bool CIMaterials::ConstructEJ280() {
	// Define the composition
	G4double density;
	const G4int nComponents = 2;

	m_materialEJ280 = new G4Material(m_EJ280_Name, density = 1.023 * g / cm3, nComponents);
	assert (m_materialEJ280 != NULL);

	m_materialEJ280->AddElement(m_elementH, 10);
	m_materialEJ280->AddElement(m_elementC, 11);

	// TEST VALUES -- NOT REAL VALUES

	const G4int WLS_NUMENTRIES = 5;

	//	G4double SpectrumEnergy[nSpectrum] = {m_dNMtoEV / 300.0, m_dNMtoEV / 400.0};

	G4double WLS_Energy[WLS_NUMENTRIES]={m_dNMtoEV / 200.0, m_dNMtoEV / 400.0, m_dNMtoEV / 500.0, m_dNMtoEV / 600.0, m_dNMtoEV / 700.0};
	G4double RefractiveIndexFiber[WLS_NUMENTRIES]={1.58, 1.58, 1.58, 1.58, 1.58};

	G4double WLS_AbsLengthEnergy[] = {m_dNMtoEV /200, m_dNMtoEV /300, m_dNMtoEV /350, m_dNMtoEV /375, m_dNMtoEV /400, m_dNMtoEV /425, m_dNMtoEV /435, m_dNMtoEV /450, m_dNMtoEV /460, m_dNMtoEV /470, m_dNMtoEV /480};
	G4double WLS_AbsLength[]       = {0.,             .05,            .05,            .10,            .50,            1.00,           0.75,           0.88,           0.40,           .05,            0.0};
	const G4int WLS_AbsN = sizeof(WLS_AbsLengthEnergy)/sizeof(G4double);
	assert( WLS_AbsN == sizeof(WLS_AbsLength)/sizeof(G4double));


	G4double WLS_EmissionEnergy[] = 	{m_dNMtoEV /460., m_dNMtoEV /470., m_dNMtoEV /490., m_dNMtoEV /500., m_dNMtoEV /520., m_dNMtoEV /525., m_dNMtoEV /550., m_dNMtoEV /600.};
	G4double WLS_Emission[]       = 	{0.00,            0.20,            0.40,            0.90,            0.55,            0.58,            0.15,            0.0};
	const G4int WLS_EmisN = sizeof(WLS_EmissionEnergy)/sizeof(G4double);
	assert( WLS_EmisN == sizeof(WLS_Emission)/sizeof(G4double));

	m_EJ280MaterialProperties = new G4MaterialPropertiesTable();

	m_EJ280MaterialProperties->AddProperty("RINDEX",WLS_Energy, RefractiveIndexFiber, WLS_NUMENTRIES);
	m_EJ280MaterialProperties->AddProperty("WLSABSLENGTH",WLS_AbsLengthEnergy, WLS_AbsLength, WLS_AbsN);
	m_EJ280MaterialProperties->AddProperty("WLSCOMPONENT",WLS_EmissionEnergy, WLS_Emission, WLS_NUMENTRIES);
	m_EJ280MaterialProperties->AddConstProperty("WLSTIMECONSTANT", 8.5*ns);


	m_materialEJ280->SetMaterialPropertiesTable(m_EJ280MaterialProperties);

  return true;
}


//http://www.compositesworld.com/articles/the-making-of-carbon-fiber
//http://geant4.cern.ch/support/source/geant4/examples/advanced/xray_telescope/src/XrayTelDetectorConstruction.cc
//density 1.5
//  G4int nel;
//  G4String symbol;

  // Elements
//  G4Element* C = new G4Element("Carbon", symbol="C", 6., 12.011*g/mole);
//  G4Element* H = new G4Element("Hydrogen",symbol="H", 1., 1.00794*g/mole);

  // Materials from Combination
//  G4Material* Cf = new G4Material("Carbon Fibre", 2.0*g/cm3, nel=2);
//  Cf->AddElement(C,1);
//  Cf->AddElement(H,2);
  // Carbon Fiber
