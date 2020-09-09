/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.               *
 *   hseywerd@nrcan.gc.ca                                                   *
 *                                                                          *
 ***************************************************************************/
/**
 * @file CIMaterialHit.cpp
 * @brief Represent hits in materials.
 * @author Henry Seywerd hseywerd@nrcan.gc.ca
 **/
#include "CIMaterialHit.h"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

G4Allocator<CIMaterialHit> CIMaterialHitsAllocator;

CIMaterialHit::CIMaterialHit() :
	m_strPartName(""), m_strInteractionProcessName(""), m_dEnergyDep(0) {
}

//-----------------------------------------------------------------------------


CIMaterialHit::~CIMaterialHit() {
}

//-----------------------------------------------------------------------------


CIMaterialHit::CIMaterialHit(const CIMaterialHit& right) :
	CIGenericHit(right) {
	m_strInteractionProcessName = right.m_strInteractionProcessName;
	m_strPartName = right.m_strPartName;
	m_dEnergyDep = right.m_dEnergyDep;
	m_strMediumName = right.m_strMediumName;
}
//-----------------------------------------------------------------------------

const CIMaterialHit& CIMaterialHit::operator=(const CIMaterialHit & right) {
	CIGenericHit::operator=(right);
	m_strInteractionProcessName = right.m_strInteractionProcessName;
	m_strPartName = right.m_strPartName;
	m_dEnergyDep = right.m_dEnergyDep;
	m_strMediumName = right.m_strMediumName;
	return *this;
}
//-----------------------------------------------------------------------------


G4int CIMaterialHit::operator==(const CIMaterialHit& right) const {
	if (!CIGenericHit::operator==(right))
		return 0;
	return (this == &right) ? 1 : 0;
}
//-----------------------------------------------------------------------------


void CIMaterialHit::Draw() {
	G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
	if (pVVisManager) {
		G4Circle circle(m_Pos);
		circle.SetScreenSize(2.);
		circle.SetFillStyle(G4Circle::filled);
		G4Colour colour(0., 0., 1.);
		G4VisAttributes attribs(colour);
		circle.SetVisAttributes(attribs);
		pVVisManager->Draw(circle);
	}
}
//-----------------------------------------------------------------------------


void CIMaterialHit::Print() {
	G4cout << "Material Hit::: Particle: " << m_strPartName << " has " << m_dEnergy << " in detector element "
			<< m_strPVolName << " interacts by process: " << m_strInteractionProcessName << " with "<<
			m_strMediumName << G4endl;
}
