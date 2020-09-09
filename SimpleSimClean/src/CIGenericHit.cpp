/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.               *
 *   hseywerd@nrcan.gc.ca                                                   *
 *                                                                          *
 ***************************************************************************/
/**
 * @file CIGenericHit.cpp
 * @brief Represent hits in our detector, intended as a base class to specific hit types
 * @author Henry Seywerd hseywerd@nrcan.gc.ca
 **/
#include "CIGenericHit.h"

G4Allocator<CIGenericHit> CIGenericHitsAllocator;

CIGenericHit::CIGenericHit() :
	m_dEnergy(0), m_dTime(0), m_Pos(G4ThreeVector(0, 0, 0)), m_strPVolName(""), m_iModuleID(0), m_iTrackID(0),
			m_iParentTrackID(0), m_strPartName("") {
}
//-----------------------------------------------------------------------------

CIGenericHit::~CIGenericHit() {
}
//-----------------------------------------------------------------------------

CIGenericHit::CIGenericHit(const CIGenericHit& right) {
	m_dEnergy = right.m_dEnergy;
	m_Pos = right.m_Pos;
	m_dTime = right.m_dTime;
	m_iModuleID = right.m_iModuleID;
	m_strPVolName = right.m_strPVolName;
	m_iTrackID = right.m_iTrackID;
	m_iParentTrackID = right.m_iParentTrackID;
	m_strPartName = right.m_strPartName;
}
//-----------------------------------------------------------------------------


const CIGenericHit& CIGenericHit::operator=(const CIGenericHit & right) {
	m_dEnergy = right.m_dEnergy;
	m_Pos = right.m_Pos;
	m_dTime = right.m_dTime;
	m_iModuleID = right.m_iModuleID;
	m_strPVolName = right.m_strPVolName;
	m_iTrackID = right.m_iTrackID;
	m_iParentTrackID = right.m_iParentTrackID;
	m_strPartName = right.m_strPartName;
	return *this;
}
//-----------------------------------------------------------------------------


G4int CIGenericHit::operator==(const CIGenericHit& right) const {
	return (this == &right) ? 1 : 0;
}
//-----------------------------------------------------------------------------


