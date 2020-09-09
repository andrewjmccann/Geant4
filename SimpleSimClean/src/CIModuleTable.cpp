/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.              *
 *   hseywerd@nrcan.gc.ca                                                  *
 *                                                                         *
 ***************************************************************************/
/**
 * @file CIModuleTable.cpp
 * @brief
 *
 * @date Oct 1, 2009
 *
 * @author hseywerd
 * @brief Define a class to map module identifier strings to a module ID code
 **/

#include "G4Navigator.hh"
#include "G4TransportationManager.hh"

#include "CIModuleTable.h"

const G4String CIModuleTable::m_strScatterCellName = "SCELL";
const G4String CIModuleTable::m_strAbsorberCellName = "ACELL";

//-----------------------------------------------------------------------------
CIModuleTable::CIModuleTable() {
}

//-----------------------------------------------------------------------------
CIModuleTable::~CIModuleTable() {
}

//-----------------------------------------------------------------------------
G4bool CIModuleTable::IsPointInScatDet(const G4ThreeVector pos) const {
	G4Navigator* theNavigator = G4TransportationManager::GetTransportationManager()->GetNavigatorForTracking();
	G4VPhysicalVolume* theVolume = theNavigator->LocateGlobalPointAndSetup(pos);
	const G4String theName = theVolume->GetName();
	if (theName.contains(m_strScatterCellName)) return true;
	return false;

}

//-----------------------------------------------------------------------------
bool CIModuleTable::IsPointInAbsDet(const G4ThreeVector pos) const {
	G4Navigator* theNavigator = G4TransportationManager::GetTransportationManager()->GetNavigatorForTracking();
	G4VPhysicalVolume* theVolume = theNavigator->LocateGlobalPointAndSetup(pos);
	const G4String theName = theVolume->GetName();
	if (theName.contains(m_strAbsorberCellName)) return true;
	return false;
}

//-----------------------------------------------------------------------------
const G4VPhysicalVolume* CIModuleTable::GetModulePhysForOpticalHit(const G4ThreeVector pos) {
	G4Navigator* theNavigator = G4TransportationManager::GetTransportationManager()->GetNavigatorForTracking();
	theNavigator->LocateGlobalPointAndSetup(pos);
	G4TouchableHistoryHandle theTouchable = theNavigator->CreateTouchableHistoryHandle();

	
	// Go up to steps, this requires that the bottom volume be what we want
	for (int iDepth =0; iDepth< theTouchable->GetHistoryDepth(); iDepth++) {
		if (theTouchable->GetVolume(iDepth) && GetModuleID(theTouchable->GetVolume(iDepth)->GetName()) >= 0)
			return theTouchable->GetVolume(iDepth);
	}

	return NULL;
}

//-----------------------------------------------------------------------------
const G4VPhysicalVolume* CIModuleTable::GetModulePhysForScintiHit(const G4ThreeVector pos) {
	G4Navigator* theNavigator = G4TransportationManager::GetTransportationManager()->GetNavigatorForTracking();
		theNavigator->LocateGlobalPointAndSetup(pos);
		G4TouchableHistoryHandle theTouchable = theNavigator->CreateTouchableHistoryHandle();
		//	G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
		//	G4TouchableHandle theTouchable = preStepPoint->GetTouchableHandle();

	// Go up to steps, this requires thatc the bottom volume be what we want
	
	       	G4cout<< "1 Touchable name " << theTouchable->GetVolume(0)->GetName() << " and " << theTouchable->GetVolume(0) << G4endl;

		if (theTouchable->GetVolume(0) && theTouchable->GetVolume(0)->GetName().contains("XTAL")) {
	 		for (int iDepth = 0; iDepth < theTouchable->GetHistoryDepth(); iDepth++) {
			  //		if (theTouchable->GetVolume(iDepth)) G4cout << "2 Touchable name " << theTouchable->GetVolume(iDepth)->GetName() << G4endl;
			if (theTouchable->GetVolume(iDepth) && GetModuleID(theTouchable->GetVolume(iDepth)->GetName()) >= 0) return theTouchable->GetVolume(iDepth);
		}
	}
	
	return NULL;
}

