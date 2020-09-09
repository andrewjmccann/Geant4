/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.              *
 *   hseywerd@nrcan.gc.ca                                                  *
 *                                                                         *
 ***************************************************************************/

/**
 * @file CIPhotoDetector.cpp
 * @brief A logical volume representing a photodetector
 **/
#include "G4SDManager.hh"
#include "G4LogicalVolume.hh"
#include "G4OpticalSurface.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolume.hh"

#include "CIPhotoDetector.h"
#include "CIMaterials.h"
using namespace CLHEP;

const G4String CIPhotoDetector::m_LogicalVolumeSuffix = "_LOG";
const G4String CIPhotoDetector::m_PhysicalVolumeSuffix = "_PHYS";
const G4String CIPhotoDetector::m_SolidSuffix = "_SOLID";
const G4String CIPhotoDetector::m_OpticalSurfaceSuffix = "_OPTSURF";
const G4String CIPhotoDetector::m_LogSurfaceSuffix = "_LOGSURF";
const G4String CIPhotoDetector::m_OpticDetectionEfficiencyName = "EFFICIENCY";
const G4String CIPhotoDetector::m_OpticReflectivityName = "REFLECTIVITY";

const G4double CIPhotoDetector::m_dNMtoEV = 1240.0 * eV;

CIPhotoDetector::CIPhotoDetector(G4VSolid* pSolid, const G4String name, CISensitiveMaterials* pCISensitiveMaterials) :
	m_bEnableVisability(true), m_bVolPlacementCheck(false),
	m_strName(name) {

	m_pLogicalVolume =  new G4LogicalVolume(pSolid, CIMaterials::Instance()->GetMaterial("G4_AIR"), name);

}

//-----------------------------------------------------------------------------

G4VPhysicalVolume* CIPhotoDetector::ConstructPhysical(G4RotationMatrix *pRot,
		const G4ThreeVector &tlate, const G4String& pName,
		G4LogicalVolume *pMotherLogical) {

	return new G4PVPlacement(pRot, tlate, m_pLogicalVolume, pName, pMotherLogical, false, 0,
			m_bVolPlacementCheck);
}




// $Id: CSIMPMTLogicalVolume.cc,v 1.3 2000/07/11 15:14:59 mcgrew Exp $
//
// A class that inherits from G4LogicalVolume (and is a LogicalVolume in all
// ways except some extra information has been added.
//
//
//#include "globals.hh"
//
//#include "CSIMPMTLogicalVolume.hh"
//
//CSIMPMTLogicalVolume
//::CSIMPMTLogicalVolume(G4VSolid *pSolid, G4Material *pMaterial,
//		       const G4String& name,
//		       G4FieldManager *pFieldMgr,
//		       G4VSensitiveDetector *pSDetector,
//		       G4UserLimits *pULimits)
//    : G4LogicalVolume(pSolid, pMaterial, "CSIMPMTLogicalVolume",
//		      pFieldMgr,
//		      pSDetector,
//		      pULimits) {
//    pmtName = name;
//    serialNumber = -1;
//}
//
//CSIMPMTLogicalVolume *CSIMPMTLVfromG4LV(G4LogicalVolume* v) {
//    // Safely convert a G4LogicalVolume into a CSIMPMTLogicalVolume.
//    G4String name = v->GetName();
//    if (name!="CSIMPMTLogicalVolume") {
//	return NULL;
//    }
//    return (CSIMPMTLogicalVolume *) v;
//}
