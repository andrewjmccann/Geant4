/***************************************************************************
*   Copyright (C) Minister of Natural Resources Canada 2008.               *
*   hseywerd@nrcan.gc.ca                                                   *
*                                                                          *
***************************************************************************/
/**
 * @file CIOpticalPhotonHit.cpp
 * @brief Represent optical  photon hits in photodetectors
 * @author Henry Seywerd hseywerd@nrcan.gc.ca
 **/
#include "CIOpticalPhotonHit.h"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

G4Allocator<CIOpticalPhotonHit> CIOpticalPhotonHitsAllocator;


CIOpticalPhotonHit::CIOpticalPhotonHit() :
	m_strInteractionProcessName ("")
{}
//-----------------------------------------------------------------------------

CIOpticalPhotonHit::~CIOpticalPhotonHit()
{}
//-----------------------------------------------------------------------------

CIOpticalPhotonHit::CIOpticalPhotonHit (const CIOpticalPhotonHit& right) : CIGenericHit (right)
{
	m_strInteractionProcessName = right.m_strInteractionProcessName;
}
//-----------------------------------------------------------------------------


const CIOpticalPhotonHit& CIOpticalPhotonHit::operator= (const CIOpticalPhotonHit & right)
{
  CIGenericHit::operator= (right);
  m_strInteractionProcessName = right.m_strInteractionProcessName;
  return *this;
}
//-----------------------------------------------------------------------------


G4int CIOpticalPhotonHit::operator== (const CIOpticalPhotonHit& right) const
{
  if (!CIGenericHit::operator== (right)) return 0;
  return (this == &right) ? 1 : 0;
}
//-----------------------------------------------------------------------------

void CIOpticalPhotonHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if (pVVisManager)
  {
    G4Circle circle (m_Pos);
    circle.SetScreenSize (2.);
    circle.SetFillStyle (G4Circle::filled);
    G4Colour colour (1., 0., 0.);
    G4VisAttributes attribs (colour);
    circle.SetVisAttributes (attribs);
    pVVisManager->Draw (circle);
  }
}
//-----------------------------------------------------------------------------

void CIOpticalPhotonHit::Print()
{
  G4cout << "Optical Photon Hit:::  Energy " << m_dEnergy << " hit " << m_strPVolName <<
  " interacted by process: " << m_strInteractionProcessName << G4endl;
}
