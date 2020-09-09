/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.              *
 *   hseywerd@nrcan.gc.ca                                                  *
 *                                                                         *
 ***************************************************************************/
/**
 * @file CIPrimaryGeneratorAction.cpp
 * @brief
 **/
#include "CIPrimaryGeneratorAction.h"
#include "CIPrimaryGeneratorMessenger.h"
#include "SimpleScintillatorDetectorConstruction.h"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
using namespace CLHEP;

CIPrimaryGeneratorAction::CIPrimaryGeneratorAction() :
	G4VUserPrimaryGeneratorAction(), m_pParticleGun(NULL),
			m_dGammaEnergy(662.0), m_PrimaryVertexPos(0,0,0), m_bGenerateNORM(false), m_bGenerateG4GPS(true), m_pG4GPS(NULL),
			m_pCIPrimaryGeneratorMessenger(NULL) {
	m_pG4GPS = new G4GeneralParticleSource();
	G4int n_particle = 1;
	m_pParticleGun = new G4ParticleGun(n_particle);
	m_bGenerateG4GPS=true;
	// default particle kinematic
	G4String theParticleName;
	G4ParticleDefinition* theParticle =
			G4ParticleTable::GetParticleTable()->FindParticle(theParticleName
					= "gamma");
	m_pParticleGun->SetParticleDefinition(theParticle);
	// gamma in +z direction
	m_pParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., -1.));
	m_pParticleGun->SetParticlePosition(G4ThreeVector(0. * cm, 0. * cm, 200. * cm));
	m_pParticleGun->SetParticleEnergy(m_dGammaEnergy * keV);
	m_pCIPrimaryGeneratorMessenger = new CIPrimaryGeneratorMessenger(this);
	

}
//-----------------------------------------------------------------------------


CIPrimaryGeneratorAction::~CIPrimaryGeneratorAction() {
	if (m_pCIPrimaryGeneratorMessenger) delete m_pCIPrimaryGeneratorMessenger;
	if (m_pParticleGun) delete m_pParticleGun;
	if (m_pG4GPS) delete m_pG4GPS;
}
//-----------------------------------------------------------------------------


void CIPrimaryGeneratorAction::GeneratePrimaries(G4Event* event) {
	if (m_bGenerateG4GPS) {
		assert(m_pG4GPS!=NULL);
		m_pG4GPS->GeneratePrimaryVertex(event);
	 

	} else {
	  G4cout << " particle gun being used " << G4endl;
//		m_pParticleGun->SetParticlePosition(G4ThreeVector(0. * cm, 0. * cm, 200. * cm));
//		m_pParticleGun->SetParticleEnergy(m_dGammaEnergy * keV);
		m_pParticleGun->GeneratePrimaryVertex(event);
	}
}


//-----------------------------------------------------------------------------
G4double CIPrimaryGeneratorAction::GetESource1()  const {
	if (m_bGenerateG4GPS) {
		double E = m_pG4GPS->GetCurrentSource()->GetParticleEnergy();
		return E;
	} else {
		return m_dGammaEnergy;
	}
}

//-----------------------------------------------------------------------------
G4ThreeVector CIPrimaryGeneratorAction::GetSource1Postion() const {
	if (m_bGenerateG4GPS) {
		assert(m_pG4GPS!=NULL);
		G4ThreeVector pos = m_pG4GPS->GetCurrentSource()->GetPosDist()->GetCentreCoords();
		return pos;
	} else
		return m_PrimaryVertexPos;
}

