/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.               *
 *   hseywerd@nrcan.gc.ca                                                   *
 *                                                                          *
 ***************************************************************************/
/**
 * @file CIOutputEvent.cpp
 * @brief Event output data
 * @author Henry Seywerd hseywerd@nrcan.gc.ca
 **/
#include "CIOutputEvent.h"
#include "CIOutputHit.h"
#include "CIOutputPhotoHit.h"
#include "CIOutputScintiHit.h"
#include "CIOutputSummedHit.h"
#include "CIOutputMaterialHit.h"
#include "CIOutputPhotoDetectorHit.h"
// Need this stuff for compiling without/with rootcint to make the appropriate shared library
#if !defined(__CINT__)
ClassImp(CIOutputEvent)
ClassImp(CIOutputHit)
ClassImp(CIOutputScintiHit)
ClassImp(CIOutputPhotoHit)
ClassImp(CIOutputSummedHit)
ClassImp(CIOutputMaterialHit)
ClassImp(CIOutputPhotoDetectorHit)
#endif

#include <fstream>
using namespace std;

CIOutputEvent::CIOutputEvent() :
	m_ScintiHitList(NULL), m_OpticalHitList(NULL), m_OutputSummedHitList(NULL), m_SummedOptiHitList(NULL), m_strPE_Name("phot"),
	m_strPrimary_Name("Primary"), m_strCompton_Name("compt"), m_strBrem_Name("brem"), m_strScinti_Name("Scintillation"), m_strIoni_Name("eIoni"),
	m_strOther_Name("OtherProcess"), m_strLECompton_Name("LowEnCompton"), m_strLEPolarCompton_Name("polarLowEnCompt"),
	m_strLEPhotoElectric_Name("LowEnPhotoElec"), m_strLEIoni_Name("LowEnergyIoni"), m_strLEPairProduction_Name("LowEnConversion"), m_strLEBrem_Name("LowEnBrem"),
	m_strSTDCompton_Name("compt2"), m_strElectronName("e-"), m_strGammaName("gamma"), m_strOpticalPhotonName("opticalphoton"), m_strOtherPartName("Other") {
	m_ScintiHitList = new TClonesArray("CIOutputScintiHit", 10);
	m_OpticalHitList = new TClonesArray("CIOutputPhotoHit", 1000);
	m_OutputSummedHitList = new TClonesArray("CIOutputSummedHit", 10);
	m_SummedOptiHitList = new TClonesArray("CIOutputPhotoDetectorHit", 10);
	m_MaterialHitList = new TClonesArray("CIOutputMaterialHit", 10);
}


//-----------------------------------------------------------------------------
CIOutputEvent::~CIOutputEvent() {
	if (m_ScintiHitList) delete m_ScintiHitList;
	if (m_OpticalHitList) delete m_OpticalHitList;
	if (m_OutputSummedHitList) delete m_OutputSummedHitList;
	if (m_SummedOptiHitList) delete m_SummedOptiHitList;
	if (m_MaterialHitList) delete m_MaterialHitList;
}


//-----------------------------------------------------------------------------
CIOutputEvent& CIOutputEvent::operator=(const CIOutputEvent &From) {
  // Check for self-assignment!
  if (this == &From) return *this;

	this->m_dEventNum = From.m_dEventNum;
	this->m_dRunNum = From.m_dRunNum;
	this->m_dPrimaryVertexX = From.m_dPrimaryVertexX; 
	this->m_dPrimaryVertexY = From.m_dPrimaryVertexY; 
	this->m_dPrimaryVertexZ = From.m_dPrimaryVertexZ; 
	this->m_dPrimaryVertexPX= From.m_dPrimaryVertexPX;
	this->m_dPrimaryVertexPY= From.m_dPrimaryVertexPY;
	this->m_dPrimaryVertexPZ= From.m_dPrimaryVertexPZ;


	TClonesArray & summedHits = *(From.m_OutputSummedHitList);
	TClonesArray & scintiHits = *(From.m_ScintiHitList);
	TClonesArray & materialHits = *(From.m_MaterialHitList);
	TClonesArray & OsummedHits = *(this->m_OutputSummedHitList);
	TClonesArray & OscintiHits = *(this->m_ScintiHitList);
	TClonesArray & OmaterialHits = *(this->m_MaterialHitList);
	cout << " N is " << summedHits.GetEntries() << endl;
	int ii;
	for (ii = 0; ii < summedHits.GetEntries(); ii++) {
		//CIOutputSummedHit& zz =  (static_cast<CIOutputSummedHit&>(*summedHits[ii]));
		new (OsummedHits[ii]) CIOutputSummedHit(static_cast<CIOutputSummedHit&>(*summedHits[ii]));
	}
	for (ii = 0; ii < scintiHits.GetEntries(); ii++)
		new (OscintiHits[ii]) CIOutputScintiHit(static_cast<CIOutputScintiHit&> (*scintiHits[ii]));
	for (ii = 0; ii < materialHits.GetEntries(); ii++)
		new (OmaterialHits[ii]) CIOutputMaterialHit(static_cast<CIOutputMaterialHit&> (*materialHits[ii]));

  return *this;
}


//-----------------------------------------------------------------------------
CIOutputEvent::HITTYPE CIOutputEvent::GetHTypeFromName(const TString name) {

	if (name == m_strPE_Name)
		return HTYPE_PE;
	else if (name == m_strPrimary_Name)
		return HTYPE_PRIMARY;
	else if (name == m_strCompton_Name)
		return HTYPE_COMPTON;
	else if (name == m_strBrem_Name)
		return HTYPE_BREM;
	else if (name == m_strScinti_Name)
		return HTYPE_SCINT;
	else if (name == m_strIoni_Name)
		return HTYPE_IONI;
	else if (name == m_strLECompton_Name)
		return HTYPE_LECOMPTON;
	else if (name == m_strLEPolarCompton_Name)
		return HTYPE_LEPCOMPTON;
	else if (name == m_strLEPhotoElectric_Name)
		return HTYPE_LEPE;
	else if (name == m_strLEIoni_Name)
		return HTYPE_LEIONI;
	else if (name == m_strLEPairProduction_Name)
		return HTYPE_LEPAIR;
	else if (name == m_strLEBrem_Name)
		return HTYPE_LEBREM;
	else if (name == m_strSTDCompton_Name)
		return HTYPE_STDCOMPTON;
	else
		return HTYPE_OTHER;
}

//-----------------------------------------------------------------------------
TString CIOutputEvent::GetNameFromHType(const CIOutputEvent::HITTYPE type) {
	switch (type) {
	case HTYPE_PE:
		return m_strPE_Name;
	case HTYPE_PRIMARY:
		return m_strPrimary_Name;
	case HTYPE_COMPTON:
		return m_strCompton_Name;
	case HTYPE_BREM:
		return m_strBrem_Name;
	case HTYPE_SCINT:
		return m_strScinti_Name;
	case HTYPE_IONI:
		return m_strIoni_Name;
	case HTYPE_LECOMPTON:
		return m_strLECompton_Name;
	case HTYPE_LEPCOMPTON:
		return m_strLEPolarCompton_Name;
	case HTYPE_LEPE:
		return m_strLEPhotoElectric_Name;
	case HTYPE_LEIONI:
		return m_strLEIoni_Name;
	case HTYPE_LEPAIR:
		return m_strLEPairProduction_Name;
	case HTYPE_LEBREM:
		return m_strLEBrem_Name;
	case HTYPE_STDCOMPTON:
		return m_strSTDCompton_Name;
	default:
		return m_strOther_Name;
	}
}

//-----------------------------------------------------------------------------
CIOutputEvent::PARTTYPE CIOutputEvent::GetPTypeFromName(const TString name) {

	if (name == m_strElectronName)
		return PART_ELECTRON;
	else if (name == m_strGammaName)
		return PART_GAMMA;
	else if (name == m_strOpticalPhotonName)
		return PART_OPTPHOTON;
	else
		return PART_OTHER;
}

//-----------------------------------------------------------------------------
TString CIOutputEvent::GetNameFromPType(const CIOutputEvent::PARTTYPE type) {
	switch (type) {
	case PART_ELECTRON:
		return m_strElectronName;
	case PART_GAMMA:
		return m_strGammaName;
	case PART_OPTPHOTON:
		return m_strOpticalPhotonName;
	default:
		return m_strOtherPartName;
	}
}



//-----------------------------------------------------------------------------
CIOutputHit::CIOutputHit(const double x, const double y, const double z, const double T, const double E,
		const int moduleID,  const CIOutputEvent::SUBDET subDet, const int trackID, const int parentID, const CIOutputEvent::HITTYPE Htype,
		const CIOutputEvent::PARTTYPE Ptype) :
	m_dX(x), m_dY(y), m_dZ(z), m_dT(T), m_dE(E), m_iModuleID(moduleID), m_SubDetector(subDet), m_iCurrentTrackID(trackID), m_iParentTrackID(
			parentID), m_HitType(Htype), m_PartType(Ptype) {

}
//-----------------------------------------------------------------------------
CIOutputHit::~CIOutputHit() {
}

//-----------------------------------------------------------------------------
CIOutputHit::CIOutputHit(const CIOutputHit& From) : TObject(From) {
	this->m_dX = From.m_dX;
	this->m_dY = From.m_dY;
	this->m_dZ = From.m_dZ;
	this->m_dT = From.m_dT;
	this->m_dE = From.m_dE;
	this->m_iModuleID = From.m_iModuleID;
	this->m_SubDetector = From.m_SubDetector;
	this->m_iCurrentTrackID = From.m_iCurrentTrackID;
	this->m_iParentTrackID = From.m_iParentTrackID;
	this->m_HitType = From.m_HitType;
	this->m_PartType = From.m_PartType;
}



//-----------------------------------------------------------------------------

// Define the process names
// Extracted from the GEANT code
//const TString CIOutputHit::m_strPE_Name = "LowEnPhotoElec";
//const TString CIOutputHit::m_strPrimary_Name = "Primary";
//const TString CIOutputHit::m_strCompton_Name = "G4LECSComp1.07";
//const TString CIOutputHit::m_strBrem_Name = "LowEnBrem";
//const TString CIOutputHit::m_strScinti_Name = "Scintillation";
//const TString CIOutputHit::m_strIoni_Name = "LowEnergyIoni";
//const TString CIOutputHit::m_strOther_Name = "OtherProcess";
//
//const TString CIOutputHit::m_strLECompton_Name = "LowEnCompton";
//const TString CIOutputHit::m_strLEPolarCompton_Name = "polarLowEnCompt";
//const TString CIOutputHit::m_strLEPhotoElectric_Name = "LowEnPhotoElec";
//const TString CIOutputHit::m_strLEIoni_Name = "LowEnergyIoni";
//const TString CIOutputHit::m_strLEPairProduction_Name = "LowEnConversion";
//const TString CIOutputHit::m_strLEBrem_Name = "LowEnBrem";
//
//const TString CIOutputHit::m_strSTDCompton_Name = "compt";
//
//const TString CIOutputHit::m_strElectronName = "e-";
//const TString CIOutputHit::m_strGammaName = "gamma";
//const TString CIOutputHit::m_strOpticalPhotonName = "opticalphoton";
//const TString CIOutputHit::m_strOtherPartName = "Other";

////-----------------------------------------------------------------------------
//CIOutputHit::HITTYPE CIOutputHit::GetHTypeFromName(const TString name) {
//
//	if (name == m_strPE_Name)
//		return HTYPE_PE;
//	else if (name == m_strPrimary_Name)
//		return HTYPE_PRIMARY;
//	else if (name == m_strCompton_Name)
//		return HTYPE_COMPTON;
//	else if (name == m_strBrem_Name)
//		return HTYPE_BREM;
//	else if (name == m_strScinti_Name)
//		return HTYPE_SCINT;
//	else if (name == m_strIoni_Name)
//		return HTYPE_IONI;
//	else if (name == m_strLECompton_Name)
//		return HTYPE_LECOMPTON;
//	else if (name == m_strLEPolarCompton_Name)
//		return HTYPE_LEPCOMPTON;
//	else if (name == m_strLEPhotoElectric_Name)
//		return HTYPE_LEPE;
//	else if (name == m_strLEIoni_Name)
//		return HTYPE_LEIONI;
//	else if (name == m_strLEPairProduction_Name)
//		return HTYPE_LEPAIR;
//	else if (name == m_strLEBrem_Name)
//		return HTYPE_LEBREM;
//	else if (name == m_strSTDCompton_Name)
//		return HTYPE_STDCOMPTON;
//	else
//		return HTYPE_OTHER;
//}
//
////-----------------------------------------------------------------------------
//TString CIOutputHit::GetNameFromHType(const CIOutputHit::HITTYPE type) {
//	switch (type) {
//	case HTYPE_PE:
//		return m_strPE_Name;
//	case HTYPE_PRIMARY:
//		return m_strPrimary_Name;
//	case HTYPE_COMPTON:
//		return m_strCompton_Name;
//	case HTYPE_BREM:
//		return m_strBrem_Name;
//	case HTYPE_SCINT:
//		return m_strScinti_Name;
//	case HTYPE_IONI:
//		return m_strIoni_Name;
//	case HTYPE_LECOMPTON:
//		return m_strLECompton_Name;
//	case HTYPE_LEPCOMPTON:
//		return m_strLEPolarCompton_Name;
//	case HTYPE_LEPE:
//		return m_strLEPhotoElectric_Name;
//	case HTYPE_LEIONI:
//		return m_strLEIoni_Name;
//	case HTYPE_LEPAIR:
//		return m_strLEPairProduction_Name;
//	case HTYPE_LEBREM:
//		return m_strLEBrem_Name;
//	case HTYPE_STDCOMPTON:
//		return m_strSTDCompton_Name;
//	default:
//		return m_strOther_Name;
//	}
//}
//
////-----------------------------------------------------------------------------
//CIOutputHit::PARTTYPE CIOutputHit::GetPTypeFromName(const TString name) {
//
//	if (name == m_strElectronName)
//		return PART_ELECTRON;
//	else if (name == m_strGammaName)
//		return PART_GAMMA;
//	else if (name == m_strOpticalPhotonName)
//		return PART_OPTPHOTON;
//	else
//		return PART_OTHER;
//}
//
////-----------------------------------------------------------------------------
//TString CIOutputHit::GetNameFromPType(const CIOutputHit::PARTTYPE type) {
//	switch (type) {
//	case PART_ELECTRON:
//		return m_strElectronName;
//	case PART_GAMMA:
//		return m_strGammaName;
//	case PART_OPTPHOTON:
//		return m_strOpticalPhotonName;
//	default:
//		return m_strOtherPartName;
//	}
//}

//-----------------------------------------------------------------------------
CIOutputScintiHit::CIOutputScintiHit(const double x, const double y, const double z, const double T, const double E,
		const double EDep, const int moduleID, const CIOutputEvent::SUBDET subDet, const int trackID, const int parentID, const CIOutputEvent::HITTYPE Htype,
		const CIOutputEvent::PARTTYPE Ptype) :
	CIOutputHit(x, y, z, T, E, moduleID, subDet, trackID, parentID, Htype, Ptype), m_dEDeposit(EDep) {
}

//-----------------------------------------------------------------------------
CIOutputScintiHit::~CIOutputScintiHit() {
}

//-----------------------------------------------------------------------------
CIOutputScintiHit::CIOutputScintiHit(CIOutputScintiHit& From) : CIOutputHit(From) {
	this->m_dEDeposit = From.m_dEDeposit;
}

//-----------------------------------------------------------------------------
double CIOutputScintiHit::GetTrueIncidentAngle(const TClonesArray& scintiHits) {

	//int nScintiHits = scintiHits.GetEntries();
	const CIOutputScintiHit* theScHit1 = dynamic_cast<const CIOutputScintiHit*> (scintiHits[0]);
	const CIOutputScintiHit* theScHit2 = dynamic_cast<const CIOutputScintiHit*> (scintiHits[1]);
	TVector3 VH1(theScHit1->m_dX,theScHit1->m_dY, theScHit1->m_dZ);
	TVector3 VH2(theScHit2->m_dX,theScHit2->m_dY, theScHit2->m_dZ);
	TVector3 v1 = VH2-VH1;
	TVector3 v1U = v1.Unit();

	TVector3 v0(0,0,-1);
	double costPhi = v0.Dot(v1U);
	return acos(costPhi);
}

//-----------------------------------------------------------------------------
double CIOutputScintiHit::GetTrueComptonAngle(const TClonesArray& scintiHits) {

	CIOutputScintiHit* theScHit1=NULL;
	CIOutputScintiHit* theScHit2=NULL;
	CIOutputScintiHit* theHit;

	// Get the first compton hit, and then take the next as the second hit.
	TIter ScinHitIter(&scintiHits);
	while ((theHit = dynamic_cast<CIOutputScintiHit*> (ScinHitIter.Next()))) {
		if (theHit->m_HitType == CIOutputEvent::HTYPE_COMPTON) {
			theScHit1 = theHit;
			theScHit2 = dynamic_cast<CIOutputScintiHit*> (ScinHitIter.Next());
			break;
		}
	}
	if (theScHit1 == NULL || theScHit2 == NULL) return 10000;

	// Build the vectors from the hit locations, and normalize
	TVector3 VH1(theScHit1->m_dX,theScHit1->m_dY, theScHit1->m_dZ);
	TVector3 VH2(theScHit2->m_dX,theScHit2->m_dY, theScHit2->m_dZ);
	TVector3 v1 = VH2-VH1;
	TVector3 v1U = v1.Unit();

	// Take the dot product with the normal, to get the cosine of the angle.
	TVector3 v0(0,0,-1);
	double costPhi = v0.Dot(v1U);
	double aphi = acos(costPhi);
	return aphi;

}

//-----------------------------------------------------------------------------
double CIOutputScintiHit::GetTrueComptonAngle(const TClonesArray& scintiHits, TVector3& srcPos) {

	CIOutputScintiHit* theScHit1=NULL;
	CIOutputScintiHit* theScHit2=NULL;
	CIOutputScintiHit* theHit;

	// Get the first compton hit, and then take the next as the second hit.
	TIter ScinHitIter(&scintiHits);
	while ((theHit = dynamic_cast<CIOutputScintiHit*> (ScinHitIter.Next()))) {
		if (theHit->m_HitType == CIOutputEvent::HTYPE_COMPTON) {
			theScHit1 = theHit;
			theScHit2 = dynamic_cast<CIOutputScintiHit*> (ScinHitIter.Next());
			break;
		}
	}
	if (theScHit1 == NULL || theScHit2 == NULL) return 10000;

	// Build the vectors from the hit locations, and normalize
	TVector3 VH1(theScHit1->m_dX,theScHit1->m_dY, theScHit1->m_dZ);
	TVector3 VH2(theScHit2->m_dX,theScHit2->m_dY, theScHit2->m_dZ);
	TVector3 v1 = VH2-VH1;
	TVector3 v1U = v1.Unit();

	// Take the dot product with the normal, to get the cosine of the angle.

	srcPos.Unit();
	double costPhi = srcPos.Dot(v1U);
	double aphi = acos(costPhi);
	return aphi;

}


//-----------------------------------------------------------------------------
double CIOutputScintiHit::GetTrueComptonAngle(TVector3&  v1, TVector3& v2, TVector3& srcPos) {



	// Build the vectors from the hit locations, and normalize
//	TVector3 VH1(v1[0],v1[1], v1[2]);
//	TVector3 VH2(v2[0],v2[1], v2[2]);
	TVector3 vv = v2-v1;
	vv = vv.Unit();
	cout<<"VV " << vv.X() << " "<< vv.Y()<<endl;

	// Take the dot product with the normal, to get the cosine of the angle.

	TVector3 ss = srcPos.Unit();

	cout<<"srcPos " << ss.X() << " "<< ss.Y()<<endl;
	double costPhi = ss.Dot(vv);
	double aphi = acos(costPhi)*180/M_PI;
	return aphi;

//	double mvx1 = dp1[0] - dpam[0];
//	double mvy1 = dp1[1] - dpam[1];
//	double mvz1 = dp1[2] - dpam[2];
//	double mR = sqrt(mvx1*mvx1  + mvy1*mvy1  + mvz1*mvz1);
//	if (mR>0) {
//		mvx1 = mvx1/mR;
//		mvy1 = mvy1/mR;
//		mvz1 = mvz1/mR;
//		//const double thisangle = 36*M_PI/180;
//		double v0x = 22.5;
//		double v0y = 0;
//		double v0z = -31.5;
//		double mS = sqrt(v0x*v0x + v0y*v0y + v0z*v0z);
//		v0x /= mS;
//		v0y /= mS;
//		v0z /= mS;
//		return acos(v0x*mvx1 + v0y*mvy1 + v0z*mvz1)*180/M_PI;
//	}
//	return -9000;


}

//-----------------------------------------------------------------------------
CIOutputPhotoHit::CIOutputPhotoHit(const double x, const double y, const double z, const double T, const double E,
		const int moduleID, const CIOutputEvent::SUBDET subDet, const int trackID, const int parentID, const CIOutputEvent::HITTYPE Htype,
		const CIOutputEvent::PARTTYPE Ptype, const int scintiHitIndex) :
	CIOutputHit(x, y, z, T, E, moduleID, subDet, trackID, parentID, Htype, Ptype), m_iScintiHitIndex(scintiHitIndex) {
}

//-----------------------------------------------------------------------------
CIOutputPhotoHit::~CIOutputPhotoHit() {
}

//-----------------------------------------------------------------------------
CIOutputPhotoHit::CIOutputPhotoHit(CIOutputPhotoHit& From)  : CIOutputHit(From) {
	this->m_iScintiHitIndex = From.m_iScintiHitIndex;

	this->m_iScintiHitIndex = From.m_iScintiHitIndex;
	this->m_dEnergy         = m_dEnergy;
	this->m_dSmearedEnergy  = From.m_dSmearedEnergy;
	this->m_iCellID         = From.m_iCellID;
	this->m_dXPos           = From.m_dXPos;
	this->m_dYPos           = From.m_dYPos;
	this->m_dZPos           = From.m_dZPos;
	this->m_iLayer          = From.m_iLayer;
}

//-----------------------------------------------------------------------------
CIOutputSummedHit::CIOutputSummedHit(CIOutputSummedHit& From) : TObject(From) {
	this->m_dEnergy = From.m_dEnergy;
	this->m_dSmearedEnergy = From.m_dSmearedEnergy;
	this->m_iCellID = From.m_iCellID;
	this->m_dXPos = From.m_dXPos;
	this->m_dYPos = From.m_dZPos;
	this->m_dYPos = From.m_dZPos;
	this->m_dTime = From.m_dTime;
	this->m_SubDetector = From.m_SubDetector;
	this->m_iLayer = From.m_iLayer;
}

//-----------------------------------------------------------------------------
double CIOutputSummedHit::CalculateComptonAngle(const double E1, const double E2) {
	const double mElectron=0.511; //(MeV)
	const double cosT = 1.0+mElectron*(1/(E1+E2)-1/E2);
	return cosT;
}


//-----------------------------------------------------------------------------
double CIOutputSummedHit::GetSmeardAngle(const TClonesArray& summedHits) {
	TVector3 VH1, VH2;

	// Get the first compton hit, and then take the next as the second hit.
	TIter summedHitIter(&summedHits);
	double eMax=0;
	CIOutputSummedHit* theHit;
	// Take the cell positions as position of the hit
	while ((theHit = dynamic_cast<CIOutputSummedHit*> (summedHitIter.Next()))) {
		CIOutputSummedHit::SUBDET subdet = theHit->TheSubDetector();
		const double E = theHit->TheSmearedEnergy();
		if (subdet == CIOutputSummedHit::SUBDET_SCATTER) {
			VH1 = TVector3(theHit->GetX(),theHit->GetY(), theHit->GetZ());
		} else if (subdet == CIOutputSummedHit::SUBDET_ABSORBER && E>eMax) {
 			eMax = E;
			VH2 = TVector3(theHit->GetX(),theHit->GetY(), theHit->GetZ());
		}
	}
		TVector3 v1 = VH2-VH1;
		TVector3 v1U = v1.Unit();
		TVector3 v0(0,0,-1);
		double cosPhi = v0.Dot(v1U);
		double phi = acos(cosPhi);
		return phi;

}

//-----------------------------------------------------------------------------
CIOutputMaterialHit::CIOutputMaterialHit(const double x, const double y, const double z, const double T, const double E,
		const double EDep, const int trackID, const int parentID, const CIOutputEvent::HITTYPE Htype,
		const CIOutputEvent::PARTTYPE Ptype, const TString name) :
	CIOutputHit(x, y, z, T, E, -1, CIOutputEvent::SUBDET_OTHER, trackID, parentID, Htype, Ptype), m_dEDeposit(EDep), Volume(name) {
}

//-----------------------------------------------------------------------------
CIOutputMaterialHit::~CIOutputMaterialHit() {
}

//-----------------------------------------------------------------------------
CIOutputMaterialHit::CIOutputMaterialHit(CIOutputMaterialHit& From) : CIOutputHit(From) {
		this->m_dEDeposit = From.m_dEDeposit;
		this->Volume = From.Volume;
}


