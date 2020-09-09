/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.              *
 *   hseywerd@nrcan.gc.ca                                                  *
 *                                                                         *
 ***************************************************************************/

/**
 * @file CellVolume.h
 * @brief A logical volume representing a photodetector
 **/
#ifndef CellVolume_h
#define CellVolume_h 1

#include "G4LogicalVolume.hh"
#include "G4String.hh"
#include "G4Material.hh"
#include "G4SubtractionSolid.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"

class G4VPhysicalVolume;
class G4OpticalSurface;
class CISensitiveScintiDetector;
class CISensitiveMaterials;
#include "CIMaterials.h"
 

//Added by Audrey: will not compile without it

#include "CISensitiveScintiDetector.h"
#include "CISensitiveOpticalDetector.h"
#include "CISensitiveMaterials.h"

#include "CIPhotoDetector.h"


/**
 * @class CellVolume
 * @brief Defines a logical volume consisting of a photodetector and a crystal
 *
 * @author Henry Seywerd <hseywerd@nrcan.gc.ca>
 */
template<class PhotoDetetector> class CellVolume {
public:


	/**
	 * Create the volume
	 */
	CellVolume(const G4String name, G4VPhysicalVolume* pEnclosingVolume, CISensitiveScintiDetector* pCISensitiveScintiDetector,
			CISensitiveMaterials* pCISensitiveMaterials, const G4Material* xtalMaterial, const G4ThreeVector xtalHalfSize) :
		    m_strName(name), m_pEnclosingVolume(pEnclosingVolume),
				m_pCISensitiveScintiDetector(pCISensitiveScintiDetector), m_pCISensitiveMaterials(pCISensitiveMaterials),
				m_xtalHalfSize(xtalHalfSize), m_bEnableVisability(true), m_bVolPlacementCheck(false),  m_PhotoDet_Log(NULL), m_PhotoDet_Phy(NULL),
				m_OuterOpticalSurface(NULL), m_Xtal_Log(NULL), m_Xtal_Phy(NULL), m_dCasingThickness(0), m_dRearCasingThickness(m_dCasingThickness),
				m_visAttXtal(NULL), m_visAttCasing(NULL), m_visAttCell(NULL) {


		m_pLogicalVolume = new G4LogicalVolume(new G4Box(name + m_SolidSuffix, GetSize(xtalHalfSize).x(), GetSize(xtalHalfSize).y(), GetSize(xtalHalfSize).z()),
				CIMaterials::Instance()->GetMaterial("Opaque_AIR"), name);

		m_Materials = CIMaterials::Instance();

		// Some useful items
		G4RotationMatrix* pNullRotation = NULL;
		G4bool bMany = false;

		// Build a scintillator crystal
		const G4String xtal_Name = m_strName + "_xtal";
		G4Box* xtal_solid = new G4Box(xtal_Name + m_SolidSuffix, m_xtalHalfSize.x(), m_xtalHalfSize.y(), m_xtalHalfSize.z());


		m_Xtal_Log = new G4LogicalVolume(xtal_solid, const_cast<G4Material*> (xtalMaterial), xtal_Name + m_LogicalVolumeSuffix, NULL, m_pCISensitiveScintiDetector);
		//	m_Xtal_Log = new G4LogicalVolume(xtal_solid,const_cast<G4Material*> (xtalMaterial), xtal_Name + m_LogicalVolumeSuffix,NULL,m_pCISensitiveScintiDetector,NULL,NULL);

		assert (m_Xtal_Log != NULL);

		// Build a photodetector
		G4String photoDetName = m_strName + "_PDetec";
		//
		assert(m_PhotoDet_Log==NULL);
		PhotoDetetector* m_PhotoDet = new PhotoDetetector(photoDetName, pCISensitiveMaterials);

		m_PhotodetectorHalfSize = m_PhotoDet_Log->GetHalfSize();
		// Geant does not correctly update this if there is an internal change so we need the following step. (or maybe I'm confused)
		//m_PhotodetectorHalfSize.setZ( dynamic_cast<G4Tubs*>(m_PhotoDet_Log->GetSolid())->GetZHalfLength());
		m_PhotoDet_Log->SetWhiteBoundary(m_pEnclosingVolume);

		// Modify the enclosing logical volume
		G4Box* enclosingBox = dynamic_cast<G4Box*> (m_pLogicalVolume->GetSolid());
		assert(enclosingBox!=NULL);
		// Distance xtal extends past the front of the PD system
		double XtalExtension=0;
		if (m_xtalHalfSize.z()>(m_PhotoDet_Log->FrontFaceOffset()/2.)) XtalExtension = m_xtalHalfSize.z()-m_PhotoDet_Log->FrontFaceOffset()/2;
		enclosingBox->SetZHalfLength(m_PhotodetectorHalfSize.z()+XtalExtension);

		// Place the elements within the cell logical volume creating the physical volumes for them
		G4ThreeVector xtal_placement(0, 0, m_PhotodetectorHalfSize.z()-m_PhotoDet_Log->FrontFaceOffset());
		m_Xtal_Phy = new G4PVPlacement(pNullRotation, xtal_placement, m_Xtal_Log, m_strName + "XTAL" + m_PhysicalVolumeSuffix, m_pLogicalVolume, bMany, 0, m_bVolPlacementCheck);

		G4ThreeVector photodector_placement(0, 0, -1*XtalExtension); //-1*m_xtalHalfSize.z()+m_PhotoDet_Log->FrontFaceOffset()/2);
		photoDetName = photoDetName + m_PhysicalVolumeSuffix;
		m_PhotoDet_Phy = new G4PVPlacement(pNullRotation, photodector_placement, m_PhotoDet->GetLogicalVol(), photoDetName, m_pLogicalVolume, bMany, 0, m_bVolPlacementCheck);

		//Visualization attributes for the Xtal and Cell
		G4bool bEnableXtalVisualization = true;
		// Orange crystal
		m_visAttXtal = new G4VisAttributes(G4Colour(0.9, 0.50, 0.2));
		//
		m_visAttCell = new G4VisAttributes(G4Colour(0.5, 0.50, 0.90));
		m_visAttXtal->SetVisibility(bEnableXtalVisualization);
		m_visAttCell->SetVisibility(bEnableXtalVisualization);
		m_Xtal_Log->SetVisAttributes(m_visAttXtal);
		m_pLogicalVolume->SetVisAttributes(m_visAttCell);

	}
	//-----------------------------------------------------------------------------
	/**
	 * Clean up stuff not otherwise looked after
	 */
	virtual ~CellVolume() {
		if (m_OuterOpticalSurface) delete m_OuterOpticalSurface;
		if (m_visAttCell) delete m_visAttCell;
		if (m_visAttXtal) delete m_visAttXtal;
		if (m_visAttCasing) delete m_visAttCasing;
	}

	//-----------------------------------------------------------------------------
	void SetVisibility(const bool bEnableVisability) {
		m_bEnableVisability = bEnableVisability;
	}

	//-----------------------------------------------------------------------------
	const G4ThreeVector& GetxtalHalfSize() {
		return m_xtalHalfSize;
	}
	//-----------------------------------------------------------------------------
	/// Return the Logical volume for the photodetector
	G4LogicalVolume* GetLogicalVol() {return m_pLogicalVolume;}

	//-----------------------------------------------------------------------------
	/**
	 * Set the internal boundaries of the cell to be reflective.
	 * @param theVolume the external containing physical volume.
	 */
	void SetWhiteBoundary(G4VPhysicalVolume *theVolume) {
		if (!theVolume) return;
		m_OuterOpticalSurface = CIMaterials::Instance()->GetOpticalSurface("WhiteSurface");
		G4String borderName = "CellExternalBorder" + m_LogSurfaceSuffix;
		new G4LogicalBorderSurface(borderName, m_Xtal_Phy, theVolume, m_OuterOpticalSurface);

	}

	//-----------------------------------------------------------------------------
	/**
	 * Get the deviation of the position of the centre of the cell's active region (the Xtal) from the centre of the cell itself
	 * @param centrePos The position of the centre of the crystal w.r.t. cell centre
	 */
	void GetActiveCentre(G4ThreeVector& centrePos) const {
		centrePos =   m_Xtal_Phy->GetObjectTranslation();
	}

	//-----------------------------------------------------------------------------
	void AddCasing(const G4String materialName, const G4double casingThickness, const G4bool bWindow=false, const G4String windowMaterialName="",
		       const G4double rearCasingThickness=-1) {

		m_dCasingThickness = casingThickness;
		if (rearCasingThickness<0)
			m_dRearCasingThickness = casingThickness;
		else
			m_dRearCasingThickness = rearCasingThickness;

		const G4String casing_Name("Casing");
		const G4String window_Name("Window");

		// First we need to resize our enclosing volume to give space for the casing
		G4Box* enclosingBox = dynamic_cast<G4Box*>(m_pLogicalVolume->GetSolid());

		double XtalAssemblyExtension=0;
		if ((m_xtalHalfSize.z()+m_dCasingThickness)>(m_PhotoDet_Log->FrontFaceOffset()/2.)) XtalAssemblyExtension =
					m_xtalHalfSize.z()+m_dCasingThickness-m_PhotoDet_Log->FrontFaceOffset()/2;
		enclosingBox->SetZHalfLength(m_PhotodetectorHalfSize.z()+XtalAssemblyExtension);


		// Place the elements within the cell logical volume creating the physical volumes for them
		G4ThreeVector xtal_placement(0, 0, m_PhotodetectorHalfSize.z()-m_PhotoDet_Log->FrontFaceOffset()+XtalAssemblyExtension-m_xtalHalfSize.z()-m_dCasingThickness);
		m_Xtal_Phy->SetTranslation(xtal_placement);

		G4ThreeVector photodector_placement(0, 0, -1*XtalAssemblyExtension); //-1*m_xtalHalfSize.z()+m_PhotoDet_Log->FrontFaceOffset()/2);
		m_PhotoDet_Phy->SetTranslation(photodector_placement);

		// Create a new solid to represent the casing
		G4Box* xtalBox = dynamic_cast<G4Box*>(m_Xtal_Log->GetSolid());
		G4Box* outerBox = new G4Box("outer", xtalBox->GetXHalfLength()+m_dCasingThickness, xtalBox->GetYHalfLength()+m_dCasingThickness, xtalBox->GetZHalfLength()+m_dCasingThickness);
		G4Box* innerBox = new G4Box("inner", xtalBox->GetXHalfLength(), xtalBox->GetYHalfLength(), xtalBox->GetZHalfLength());

		// Then we need to make a box within a box to represent the case
		G4SubtractionSolid* casingSolid = new G4SubtractionSolid(casing_Name+m_SolidSuffix, outerBox, innerBox);


		// If we have a window, make a sold to represent it.
//		if (bWindow) {
//			G4Box* window_Box = new G4Box(window_Name+m_SolidSuffix, innerBox->GetXHalfLength(), innerBox->GetXHalfLength(), m_dCasingThickness/2);
//			G4Material* window_Material = m_Materials->GetMaterial(windowMaterialName);
//			G4LogicalVolume* window_Log = new G4LogicalVolume(window_Box, window_Material, window_Name + m_LogicalVolumeSuffix);
//		}

		G4LogicalVolume* casing_Log = new G4LogicalVolume(casingSolid, m_Materials->GetMaterial(materialName),
				casing_Name + m_LogicalVolumeSuffix, NULL, m_pCISensitiveMaterials);

		m_visAttCasing = new G4VisAttributes(G4Colour(0.3, 0.80, 0.0));
		m_visAttCasing->SetVisibility(true);
		casing_Log->SetVisAttributes(m_visAttCasing);
		// Place the elements within the cell logical volume creating the physical volumes for them
		G4ThreeVector casing_placement(0, 0, m_Xtal_Phy->GetObjectTranslation().z());
		new G4PVPlacement(NULL, casing_placement, casing_Log, casing_Name + m_PhysicalVolumeSuffix, m_pLogicalVolume, false, 0, m_bVolPlacementCheck);


	}

protected:


	/// The logical volume for the cell
	G4LogicalVolume* m_pLogicalVolume;

	/// Name of the device
	G4String m_strName;
	/// Physical volume enclosing the device
	G4VPhysicalVolume* m_pEnclosingVolume;
	/// The sensitive detector for scintillation behaviour
	CISensitiveScintiDetector* m_pCISensitiveScintiDetector;
	/// Handler for hits in other materials
	CISensitiveMaterials* m_pCISensitiveMaterials;
	/// Half size of the crystal
	G4ThreeVector m_xtalHalfSize;
	/// Enable display of the components of the SiPM
	bool m_bEnableVisability;
	/// Enable placement/overlap checks of the volumes
	bool m_bVolPlacementCheck;
	/// Logical Volume for the photodetector
	PhotoDetetector* m_PhotoDet_Log;
	/// The physical volume of the photodetector
	G4VPhysicalVolume* m_PhotoDet_Phy;
	/// Surface between the device (or its components and the outside world)
	G4OpticalSurface* m_OuterOpticalSurface;
	/// Logical Volume for the crystal
	G4LogicalVolume* m_Xtal_Log;
	/// The physical volume of the crystal
	G4VPhysicalVolume* m_Xtal_Phy;
	/// Thickness of the casing surrounding the crystal
	G4double m_dCasingThickness;
	/// Thickness of the casing surrounding the crystal - back end where it is coupled to the photodetector
	G4double m_dRearCasingThickness;
	/// Visual attributes for the crystal
	G4VisAttributes* m_visAttXtal;
	/// Visual attributes for the aluminum crystal casing
	G4VisAttributes* m_visAttCasing;
	/// Visual attributes for the complete cell
	G4VisAttributes* m_visAttCell;
	/// Access to the materials table
	CIMaterials* m_Materials;
	/// The sipm size
	G4ThreeVector m_PhotodetectorHalfSize;
	
	
	//Some useful string constants
	/// Indicates a logical volume
	static const G4String m_LogicalVolumeSuffix;
	/// Indicates a physical volume
	static const G4String m_PhysicalVolumeSuffix;
	/// Indicates an object representing a solid
	static const G4String m_SolidSuffix;
	/// Indicates an optical surface between two volumes
	static const G4String m_OpticalSurfaceSuffix;
	/// Indicates a logical surface between two volumes
	static const G4String m_LogSurfaceSuffix;
	// For use with the old G4 optical model - reflectivity
	static const G4String m_OpticReflectivityName;
	/// Detection efficiency for optical detection materials (photocathodes etc)

	
	static const G4String m_OpticDetectionEfficiencyName;
	
	/**
	 * Calculate and return the half size of the cell based on crystal size and SiPM size
	 * @param xtalHalfSize - crystal half size
	 * @return half size of the entire cell
	 */
	//-----------------------------------------------------------------------------
	G4ThreeVector GetSize(const G4ThreeVector xtalHalfSize) const {
		// A bit of buffer for optical gel etc.
		const G4double zExtraSpace = PhotoDetetector::GetExtraSpace();
		G4double x = PhotoDetetector::GetHalfSize().x() > xtalHalfSize.x() ? PhotoDetetector::GetHalfSize().x() : xtalHalfSize.x();
		G4double y = PhotoDetetector::GetHalfSize().y() > xtalHalfSize.y() ? PhotoDetetector::GetHalfSize().y() : xtalHalfSize.y();
		G4double z = PhotoDetetector::GetHalfSize().z() + xtalHalfSize.z() + zExtraSpace;
		return G4ThreeVector(x, y, z);
	}

};
template<class PhotoDetetector> const G4String CellVolume<PhotoDetetector>::m_LogicalVolumeSuffix = "_LOG";
template<class PhotoDetetector> const G4String CellVolume<PhotoDetetector>::m_PhysicalVolumeSuffix = "_VPHYS";
template<class PhotoDetetector> const G4String CellVolume<PhotoDetetector>::m_SolidSuffix = "_SOLID";
template<class PhotoDetetector> const G4String CellVolume<PhotoDetetector>::m_OpticalSurfaceSuffix = "_OPTSURF";
template<class PhotoDetetector> const G4String CellVolume<PhotoDetetector>::m_LogSurfaceSuffix = "_LOGSURF";
template<class PhotoDetetector> const G4String CellVolume<PhotoDetetector>::m_OpticDetectionEfficiencyName = "EFFICIENCY";
template<class PhotoDetetector> const G4String CellVolume<PhotoDetetector>::m_OpticReflectivityName = "REFLECTIVITY";
#endif
