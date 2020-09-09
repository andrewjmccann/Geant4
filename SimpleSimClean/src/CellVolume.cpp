/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.              *
 *   hseywerd@nrcan.gc.ca                                                  *
 *                                                                         *
 ***************************************************************************/

/**
 * @file CellVolume.cpp
 * @brief A logical volume representing a photodetector
 **/
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4Box.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4Material.hh"

#include "CellVolume.h"
#include "CIMaterials.h"
//#include "CISiPM.h"
#include "CISensitiveScintiDetector.h"
/*
const G4String CellVolume::m_LogicalVolumeSuffix = "_LOG";
const G4String CellVolume::m_PhysicalVolumeSuffix = "_VPHYS";
const G4String CellVolume::m_SolidSuffix = "_SOLID";
const G4String CellVolume::m_OpticalSurfaceSuffix = "_OPTSURF";
const G4String CellVolume::m_LogSurfaceSuffix = "_LOGSURF";
const G4String CellVolume::m_OpticDetectionEfficiencyName = "EFFICIENCY";
const G4String CellVolume::m_OpticReflectivityName = "REFLECTIVITY";*/

//modified by Audrey: so that it would compile. 

//template <> char* X<G4String>::m_LogicalVolumeSuffix = "_LOG" ;
//static G4String m_LogicalVolumeSuffix::CellVolume<class CIPhotoDetector> = "_LOG";
//const G4String CellVolume::m_PhysicalVolumeSuffix = "_VPHYS";
//const G4String CellVolume::m_SolidSuffix = "_SOLID";
//const G4String CellVolume::m_OpticalSurfaceSuffix = "_OPTSURF";
//const G4String CellVolume::m_LogSurfaceSuffix = "_LOGSURF";
//const G4String CellVolume::m_OpticDetectionEfficiencyName = "EFFICIENCY";
//const G4String CellVolume::m_OpticReflectivityName = "REFLECTIVITY";

/*CellVolume::CellVolume(const G4String name, G4VPhysicalVolume* pEnclosingVolume,
		CISensitiveScintiDetector* pCISensitiveScintiDetector, const G4Material* xtalMaterial,
		const G4ThreeVector xtalHalfSize) :
	G4LogicalVolume(new G4Box(name + m_SolidSuffix, GetSize(xtalHalfSize).x(), GetSize(xtalHalfSize).y(), GetSize(
			xtalHalfSize).z()), CIMaterials::Instance()->GetMaterial("Opaque_AIR"), name), m_Materials(NULL), m_bEnableVisability(true),
			m_bVolPlacementCheck(false), m_strName(name), m_xtalHalfSize(xtalHalfSize), m_pCISensitiveScintiDetector(
					pCISensitiveScintiDetector), m_pEnclosingVolume(pEnclosingVolume), m_Xtal_phy(NULL) {

	// Some useful items
	// Get the materials
	CIMaterials& m_Materials = CIMaterials::Instance();

	G4RotationMatrix* pNullRotation = NULL;
	G4bool bMany = false;

	// Build a scintillator crystal
	const G4String xtal_Name = m_strName + "_xtal";
	G4Box* xtal_solid = new G4Box(xtal_Name + m_SolidSuffix, xtalHalfSize.x(), xtalHalfSize.y(), xtalHalfSize.z());
	G4LogicalVolume* xtal_Log = new G4LogicalVolume(xtal_solid, const_cast<G4Material*> (xtalMaterial), xtal_Name
			+ m_LogicalVolumeSuffix, NULL, m_pCISensitiveScintiDetector);
	assert (xtal_Log != NULL);

	// Build an SiPM
	const G4String sipm_Name = m_strName + "_sipm";
	//
	CISiPM* sipm_Log = new CISiPM(sipm_Name);
	m_sipmHalfSize = sipm_Log->GetHalfSize();
	sipm_Log->SetWhiteBoundary(m_pEnclosingVolume);

	// Build an enclosing logical volume
	G4Box* enclosingSolid = dynamic_cast<G4Box*> (this->GetSolid());
	assert(enclosingSolid!=NULL);
	G4ThreeVector cellHalfsize;
	cellHalfsize.set(enclosingSolid->GetXHalfLength(), enclosingSolid->GetYHalfLength(),
			enclosingSolid->GetZHalfLength());

	// Place the elements within the cell logical volume creating the physical volumes for them
	G4ThreeVector xtal_placement(0, 0, cellHalfsize.z() - xtalHalfSize.z());
	m_Xtal_phy = new G4PVPlacement(pNullRotation, xtal_placement, xtal_Log, m_strName + "XTAL" + m_PhysicalVolumeSuffix, this,
			bMany, 0, m_bVolPlacementCheck);

	G4ThreeVector sipm_placement(0, 0, cellHalfsize.z() - 2* xtalHalfSize .z() - m_sipmHalfSize.z());
	new G4PVPlacement(pNullRotation, sipm_placement, sipm_Log, sipm_Name + m_PhysicalVolumeSuffix, this, bMany, 0,
			m_bVolPlacementCheck);

	//Visualization attributes for the Xtal and Cell
	G4bool bEnableXtalVisualization = true;
	// Orange crystal
	G4VisAttributes* visAttXtal = new G4VisAttributes(G4Colour(0.9, 0.50, 0.2));
	//
	G4VisAttributes* visAttCell = new G4VisAttributes(G4Colour(0.3, 0.20, 0.0));
	visAttXtal->SetVisibility(bEnableXtalVisualization);
	visAttCell->SetVisibility(bEnableXtalVisualization);
	xtal_Log->SetVisAttributes(visAttXtal);
	this->SetVisAttributes(visAttCell);

}

//-----------------------------------------------------------------------------
G4ThreeVector CellVolume::GetSize(const G4ThreeVector xtalHalfSize) const {
	// A bit of buffer for optical gel etc.
	const G4double zExtraSpace = 1.0 * mm;
	G4double x = CISiPM::GetHalfSize().x() > xtalHalfSize.x() ? CISiPM::GetHalfSize().x() : xtalHalfSize.x();
	G4double y = CISiPM::GetHalfSize().y() > xtalHalfSize.y() ? CISiPM::GetHalfSize().y() : xtalHalfSize.y();
	G4double z = CISiPM::GetHalfSize().z() + xtalHalfSize.z() + zExtraSpace;
	return G4ThreeVector(x, y, z);
}

//-----------------------------------------------------------------------------
void CellVolume::SetWhiteBoundary(G4VPhysicalVolume *theVolume) {
	if (!theVolume)
		return;
	G4OpticalSurface* theSurface = m_Materials->GetOpticalSurface("WhiteSurface");
	G4String borderName = "CellExternalBorder" + m_LogSurfaceSuffix;
	new G4LogicalBorderSurface(borderName, m_Xtal_phy, theVolume, theSurface);

}


//-----------------------------------------------------------------------------
void CellVolume::GetActiveCentre(G4ThreeVector& centrePos) const {
	// The crystal is centred in x and y so that's easy.
	const G4double x = 0.;
	const G4double y = 0.;
    // z we get from the size of our total box, and the crystal
	G4Box* enclosingSolid = dynamic_cast<G4Box*> (this->GetSolid());
	const G4double z = enclosingSolid->GetZHalfLength() - m_xtalHalfSize.z();
	centrePos.set(x, y, z);
}

//-----------------------------------------------------------------------------
void CellVolume::AddCasing(const G4String materialName, const G4double casingThickness, const G4bool bWindow=false, const G4String windowMaterialName="") {

	const G4String casing_Name("XtalCasing");
	const G4String window_Name("Window");

	// First we need to resize our enclosing volume to give space for the casing
	G4Box* outerBox = dynamic_cast<G4Box*>(this->GetSolid());
	G4Box* innerBox = new G4Box(enclosingBox);

	outerBox->SetXHalfLength(outerBox->GetXHalfLength()+casingThickness);
	outerBox->SetXHalfLength(outerBox->GetXHalfLength()+casingThickness);
	outerBox->SetXHalfLength(outerBox->GetXHalfLength()+casingThickness);

	// Then we need to make a box within a box to represent the case
	G4SubtractionSolid* casingSolid(casing_Name+m_SolidSuffix, outerBox, innerBox);

	// If we have a window, make a sold to represent it.
	if (bWindow) {
		G4Box* window_Box = new G4Box(window_Name+m_SolidSuffix, innerBox->GetXHalfLength(), innerBox->GetXHalfLength(), casingThickness/2);
		G4Material* window_Material = m_Materials->GetMaterial(windowMaterialName);
		G4LogicalVolume* window_Log = new G4LogicalVolume(window_Box, window_Material, window_Name + m_LogicalVolumeSuffix);
	}


}
*/
