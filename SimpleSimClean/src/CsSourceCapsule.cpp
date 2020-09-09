/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.              *
 *   hseywerd@nrcan.gc.ca                                                  *
 *                                                                         *
 ***************************************************************************/
/**
 * @file CsSourceCapsule.cpp
 * @brief
 *
 * @date Mar 4, 2010
 *
 * @author hseywerd@nrcan.gc.ca
 **/

#include "G4PVPlacement.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"
#include "G4Material.hh"

#include "CsSourceAssembly.h"

#include "CIMaterials.h"
#include "CISensitiveMaterials.h"
using namespace CLHEP;

// Numbers from Pat
const G4double CsSourceAssembly::m_dOuterRadius = 1.27 / 2 * cm;
const G4double CsSourceAssembly::m_dInnerRadius = 1.07 / 2 * cm;
const G4double CsSourceAssembly::m_HalfLength = 2.4 * cm;

const G4double CsSourceAssembly::m_dCapsuleRadius = 4.0 * mm;
const G4double CsSourceAssembly::m_CapsuleHalfLength = 4.65 * mm;

const G4double CsSourceAssembly::m_dPlugRadius = CsSourceAssembly::m_dInnerRadius;
const G4double CsSourceAssembly::m_PlugHalfLength = 1.4 / 2 * cm;


CsSourceAssembly::CsSourceAssembly(const G4String name, CISensitiveMaterials* pCISensitiveMaterials, const int type) :
	G4LogicalVolume(new G4Tubs(name, 0, m_dOuterRadius, m_HalfLength, 0, 2 * M_PI), CIMaterials::Instance()->GetMaterial("G4_Al"), name),
			m_pCISensitiveMaterials(pCISensitiveMaterials), m_iCapsuleType(type), m_VisAttcapsule(NULL) {

	// Get the materials
	m_Materials = CIMaterials::Instance();

	if (m_iCapsuleType != 2) {
		// Create the brass outer tube
		const G4String tube_Name("BrassTube");
		G4Tubs* tube_Solid = new G4Tubs(tube_Name, m_dInnerRadius, m_dOuterRadius, m_HalfLength, 0, 2 * M_PI);
		G4LogicalVolume* tube_Log = new G4LogicalVolume(tube_Solid, m_Materials->GetMaterial("Brass"), tube_Name + m_LogicalVolumeSuffix, NULL,
				m_pCISensitiveMaterials);
		G4VisAttributes* visAtttube = new G4VisAttributes(G4Colour(0.5, 0.10, 0.6));
		visAtttube->SetVisibility(true);
		tube_Log->SetVisAttributes(visAtttube);

		this->SetVisAttributes(visAtttube);
		G4ThreeVector tube_Placement(0, 0, 0);
		new G4PVPlacement(NULL, tube_Placement, tube_Log, tube_Name + m_PhysicalVolumeSuffix, this, 0, 0, true);
	}

	// Create the source capsule
	const G4String capsule_Name("SourceCapsule");
	G4Tubs* capsule_Solid = new G4Tubs(capsule_Name, 0, m_dCapsuleRadius, m_CapsuleHalfLength, 0, 2 * M_PI);
	G4LogicalVolume* capsule_Log = new G4LogicalVolume(capsule_Solid, m_Materials->GetMaterial("G4_Fe"), capsule_Name + m_LogicalVolumeSuffix, NULL,
			m_pCISensitiveMaterials);
	G4VisAttributes* visAttcapsule = new G4VisAttributes(G4Colour(0.5, 0.10, 0.1));
	visAttcapsule->SetVisibility(true);
	capsule_Log->SetVisAttributes(visAttcapsule);
	G4ThreeVector capsule_Placement(0, 0, -1 * m_HalfLength + 2 * m_PlugHalfLength + 2*m_CapsuleHalfLength);
	new G4PVPlacement(NULL, capsule_Placement, capsule_Log, capsule_Name + m_PhysicalVolumeSuffix, this, 0, 0, true);

	if (m_iCapsuleType != 2) {
		// Create the lead end plug
		const G4String plug_Name("EndPlug");
		G4Tubs* plug_Solid = new G4Tubs(plug_Name, 0, m_dPlugRadius, m_PlugHalfLength, 0, 2 * M_PI);
		G4LogicalVolume* plug_Log = new G4LogicalVolume(plug_Solid, m_Materials->GetMaterial("G4_Pb"), plug_Name + m_LogicalVolumeSuffix, NULL,
				m_pCISensitiveMaterials);
		G4VisAttributes* visAttplug = new G4VisAttributes(G4Colour(0.1, 0.10, 0.6));
		visAttplug->SetVisibility(true);
		plug_Log->SetVisAttributes(visAttplug);
		G4ThreeVector plug_Placement(0, 0, -1 * m_HalfLength + m_PlugHalfLength);
		new G4PVPlacement(NULL, plug_Placement, plug_Log, plug_Name + m_PhysicalVolumeSuffix, this, 0, 0, true);
	}

}

CsSourceAssembly::~CsSourceAssembly() {
	if (m_VisAttcapsule) delete m_VisAttcapsule;

}

const G4String CsSourceAssembly::m_LogicalVolumeSuffix = "_LOG";
const G4String CsSourceAssembly::m_PhysicalVolumeSuffix = "_PHYS";
const G4String CsSourceAssembly::m_SolidSuffix = "_SOLID";

