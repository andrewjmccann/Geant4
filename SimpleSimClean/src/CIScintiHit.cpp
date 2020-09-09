/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.               *
 *   hseywerd@nrcan.gc.ca                                                   *
 *                                                                          *
 ***************************************************************************/
/**
 * @file CIScintiHit.cpp
 * @brief Represent hits in scintillators.
 * @author Henry Seywerd hseywerd@nrcan.gc.ca
 **/
#include "CIScintiHit.h"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

G4Allocator<CIScintiHit> CIScintiHitsAllocator;

CIScintiHit::CIScintiHit() :
	m_strPartName(""), m_strInteractionProcessName(""), m_dEnergyDep(0) {
}

//-----------------------------------------------------------------------------


CIScintiHit::~CIScintiHit() {
}

//-----------------------------------------------------------------------------


CIScintiHit::CIScintiHit(const CIScintiHit& right) :
	CIGenericHit(right) {
	m_strInteractionProcessName = right.m_strInteractionProcessName;
	m_strPartName = right.m_strPartName;
	m_dEnergyDep = right.m_dEnergyDep;
}
//-----------------------------------------------------------------------------

const CIScintiHit& CIScintiHit::operator=(const CIScintiHit & right) {
	CIGenericHit::operator=(right);
	m_strInteractionProcessName = right.m_strInteractionProcessName;
	m_strPartName = right.m_strPartName;
	m_dEnergyDep = right.m_dEnergyDep;
	return *this;
}
//-----------------------------------------------------------------------------


G4int CIScintiHit::operator==(const CIScintiHit& right) const {
	if (!CIGenericHit::operator==(right))
		return 0;
	return (this == &right) ? 1 : 0;
}
//-----------------------------------------------------------------------------


void CIScintiHit::Draw() {
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


void CIScintiHit::Print() {
  //	G4cout << "Scintillator Hit::: Particle: " << m_strPartName << " has " << m_dEnergy << " in detector element "	<< m_strPVolName << " interacts by process: " << m_strInteractionProcessName << G4endl;
}
