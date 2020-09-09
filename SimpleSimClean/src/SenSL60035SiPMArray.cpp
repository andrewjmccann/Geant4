/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.              *
 *   hseywerd@nrcan.gc.ca                                                  *
 *   Modified by Audrey Macleod                                            *
 ***************************************************************************/

/**
 * @file SenSL60035SiPMArray.cpp
 * @brief A logical volume representing an SiPM
 **/
#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4Box.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4Material.hh"

#include "SenSL60035SiPMArray.h"
#include "CIMaterials.h"
using namespace CLHEP;

G4OpticalSurface* SenSL60035SiPMArray::m_surfaceSensitiveOptical = NULL;

const G4ThreeVector SenSL60035SiPMArray::m_sipmHalfSize(7.1 * mm, 7.1 * mm, 1.45/2.0 * mm); //total size ignores solder bumps.

SenSL60035SiPMArray::SenSL60035SiPMArray(const G4String name, CISensitiveMaterials* pCISensitiveMaterials) :
	CIPhotoDetector(new G4Box(name + m_SolidSuffix, m_sipmHalfSize.x(), m_sipmHalfSize.y(), m_sipmHalfSize.z()), name, pCISensitiveMaterials),
			m_NumElementX(4), m_NumElementY(4)
{

	if (!m_surfaceSensitiveOptical)
		ConstructSensitiveOpticalSurface();

	// Some useful items
	G4RotationMatrix* pNullRotation = NULL;
	G4bool bMany = false;

	// Visualization attributes for the different parts of the device
	//Red
	G4VisAttributes* visAttGlass = new G4VisAttributes(G4Colour(0.9, 0.10, 0.2));
	visAttGlass->SetVisibility(m_bEnableVisability);
	//Cyan
	G4VisAttributes* visAttOptCompound = new G4VisAttributes(G4Colour(0.1, 0.50, 0.9));
	visAttOptCompound->SetVisibility(m_bEnableVisability);
	// Pale blue
	G4VisAttributes* visAttElement = new G4VisAttributes(G4Colour(0.1, 0.1, 0.5));
	visAttElement->SetVisibility(m_bEnableVisability);

	// Get the materials
	CIMaterials& materials = *CIMaterials::Instance();

	const G4String glassCover_Name("GlassCover");

	G4ThreeVector glassCoverHalfSize(7.1 * mm, 7.1 * mm, 0.65/2.0 * mm); //for now just consider one large piece of glass

	// Ensure that we have not defined a size too large for the device
	assert(m_sipmHalfSize>=glassCoverHalfSize);
	G4Box* glassCover_Solid = new G4Box(glassCover_Name + m_SolidSuffix, glassCoverHalfSize.x(),
			glassCoverHalfSize.y(), glassCoverHalfSize.z());
	G4LogicalVolume* glassCover_Log = new G4LogicalVolume(glassCover_Solid, materials.GetMaterial("SiO2"),
			glassCover_Name + m_LogicalVolumeSuffix);
	glassCover_Log->SetVisAttributes(visAttGlass);

	// Construct the logical volume for the Optical Compound
	const G4String PCB_Name("PCB_Board");
	G4ThreeVector PCBHalfSize(glassCoverHalfSize.x(), glassCoverHalfSize.y(), 0.8/2.0 * mm);
	// Ensure that we have not defined a size too large for the device
	assert(m_sipmHalfSize>=PCBHalfSize);
	G4Box* PCB_Solid = new G4Box(PCB_Name + m_SolidSuffix, PCBHalfSize.x(),
			PCBHalfSize.y(), PCBHalfSize.z());
	G4LogicalVolume* PCB_Log = new G4LogicalVolume(PCB_Solid, materials.GetMaterial(
			"FR4"), PCB_Name + m_LogicalVolumeSuffix);
	PCB_Log->SetVisAttributes(visAttOptCompound);

	// Position the glass at the front of the volume
	G4ThreeVector glass_placement(0.0, 0.0, -m_sipmHalfSize.z() + glassCoverHalfSize.z());
	m_Glass_Phys = new G4PVPlacement(pNullRotation, glass_placement, glassCover_Log, glassCover_Name
			+ m_PhysicalVolumeSuffix, this->GetLogicalVol(), bMany, 0, m_bVolPlacementCheck);
	G4cout << " placing SiO2 for SiPM at " << glass_placement << G4endl;


	//Position the PCB board behind the glass
	G4ThreeVector PCB_placement(0.0, 0.0, -m_sipmHalfSize.z() + 2* glassCoverHalfSize.z()
			+ PCBHalfSize.z());
	m_PCB_Phys = new G4PVPlacement(pNullRotation, PCB_placement,
	PCB_Log, PCB_Name + m_PhysicalVolumeSuffix, this->GetLogicalVol(), bMany, 0, m_bVolPlacementCheck);
}

//-----------------------------------------------------------------------------
SenSL60035SiPMArray::~SenSL60035SiPMArray() {

}

//-----------------------------------------------------------------------------
void SenSL60035SiPMArray::SetWhiteBoundary(G4VPhysicalVolume *theVolume) {
	if (!theVolume) return;
	G4OpticalSurface* theSurface = CIMaterials::Instance()->GetOpticalSurface("WhiteSurface");
	G4String borderName = "SiPMExternalBorder" + m_LogSurfaceSuffix;
	new G4LogicalBorderSurface(borderName, m_Glass_Phys, theVolume, theSurface);
	new G4LogicalBorderSurface(borderName, m_OpticalCompound_Phys, theVolume, theSurface);
	for (int iX = 0; iX < m_NumElementX; iX++) {
		for (int iY = 0; iY < m_NumElementY; iY++) {
			new G4LogicalBorderSurface(borderName, m_Elements_Phys[iX][iY], theVolume, theSurface);
		}
	}
}

//-----------------------------------------------------------------------------
void SenSL60035SiPMArray::ConstructSensitiveOpticalSurface() {
	// A very simple surface for the Coupling Compound to the SiPM element
	m_surfaceSensitiveOptical = new G4OpticalSurface("CouplingToElement" + m_OpticalSurfaceSuffix);

	m_surfaceSensitiveOptical-> SetType(dielectric_metal);
	m_surfaceSensitiveOptical-> SetModel(unified);
	m_surfaceSensitiveOptical-> SetFinish(polished);

	//Values extracted visually from SensL data sheets
	const int nEntries = 2;
	G4double photonEnergy[nEntries] = { 20.19 * eV, 0.55 * eV };
	G4double reflectivity[nEntries] = { 0., .0 };
	// Values extracted by eye from datasheet quantum efficiency graph, numbers are the Q.E.
	G4double photonEnergyEffic[] = { m_dNMtoEV / 200, m_dNMtoEV / 380., m_dNMtoEV / 400, m_dNMtoEV / 420,
			m_dNMtoEV / 440, m_dNMtoEV / 460, m_dNMtoEV / 480, m_dNMtoEV / 500, m_dNMtoEV / 520, m_dNMtoEV / 540,
			m_dNMtoEV / 560, m_dNMtoEV / 580, m_dNMtoEV / 600, m_dNMtoEV / 620, m_dNMtoEV / 640, m_dNMtoEV / 660,
			m_dNMtoEV / 680, m_dNMtoEV / 700, m_dNMtoEV / 720, m_dNMtoEV / 740, m_dNMtoEV / 760, m_dNMtoEV / 780 };
	const G4int nEntriesEffic = sizeof(photonEnergyEffic)/sizeof(G4double);
	G4double efficiency[] = { 0.0, 0.000, 0.062, 0.093, 0.110, 0.128, 0.132, 0.132, 0.135, 0.129, 0.118,
			0.116, 0.112, 0.105, 0.096, 0.090, 0.081, 0.079, 0.073, 0.068, 0.060, 0.053 };
	assert( nEntriesEffic == sizeof(efficiency)/sizeof(G4double));

	G4double PerfectEfficiency[] = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
			1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };
	assert( nEntriesEffic == sizeof(PerfectEfficiency)/sizeof(G4double));

	G4MaterialPropertiesTable* theMaterialProperties = new G4MaterialPropertiesTable();
	theMaterialProperties -> AddProperty(m_OpticDetectionEfficiencyName, photonEnergyEffic, PerfectEfficiency,
			nEntriesEffic);
	theMaterialProperties -> AddProperty(m_OpticReflectivityName, photonEnergy, reflectivity, nEntries);
	m_surfaceSensitiveOptical-> SetMaterialPropertiesTable(theMaterialProperties);

	return;
}

