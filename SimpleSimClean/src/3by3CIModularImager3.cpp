/***************************************************************************
 *   Copyright (C)NRC 2015              *
 *   audrey.macleod@nrc.cnrg.gc.ca
 *   All SiPM Modular imager design - Large Module
 *                                                                         *
 ***************************************************************************/
/**
 * @file 3by3CIModularImager3.cpp
 * @brief Build a detector including multiple layers of scatter and absorber detectors with SiPM readout
 *
 * @date 2008/12/08
 *
 * @original author HCJ Seywerd hseywerd@nrcan.gc.ca
 * @modified by Audrey MacLeod 
 **/

#include <stdlib.h>

#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "G4LogicalVolume.hh"
#include "G4UnionSolid.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4SubtractionSolid.hh"

#include "FullDetectorConstruction.h"
#include "FullDetectorConstructionMessenger.h"
#include "CISensitiveScintiDetector.h"
#include "CISensitiveOpticalDetector.h"
#include "CIMaterials.h"
#include "CIModuleTable.h"
#include "SenSL60035SiPMArray.h"
//#include "LargeArraySenSLSiPM.h"

//#include "CIPMT.h"
//#include "CellVolume.h"
//#include "CIAbsorberDetector.h"
#include "G4Tubs.hh"
#include "G4GeometryMessenger.hh"

using namespace std;
using namespace CLHEP;

const G4String FullDetectorConstruction::m_LogicalVolumeSuffix = "_LOG";
const G4String FullDetectorConstruction::m_PhysicalVolumeSuffix = "_PHYS";
const G4String FullDetectorConstruction::m_SolidSuffix = "_SOLID";
const G4String FullDetectorConstruction::m_OpticalSurfaceSuffix = "_OPTSURF";
const G4String FullDetectorConstruction::m_LogSurfaceSuffix = "_LOGSURF";
ofstream outfilePos;


//-----------------------------------------------------------------------------
//FullDetectorConstruction::FullDetectorConstruction(CISensitiveScintiDetector* pCISensitiveScintiDetector,
//		CISensitiveOpticalDetector* pCISensitiveOpticalDetector) 
FullDetectorConstruction::FullDetectorConstruction(CISensitiveScintiDetector* pCISensitiveScintiDetector, CISensitiveOpticalDetector* pCISensitiveOpticalDetector, CISensitiveMaterials* pCISensitiveMaterials) :
	m_pCISensitiveScintiDetector(pCISensitiveScintiDetector),
			m_pCISensitiveOpticalDetector(pCISensitiveOpticalDetector), m_pCISensitiveMaterials(pCISensitiveMaterials), m_WorldPhys(NULL), m_WorldLog(NULL),
			m_pNullFieldMgr(NULL), m_bVolPlacementCheck(true),m_strScatterDetectorMaterialName("G4_CESIUM_IODIDE"), m_strAbsorberDetectorMaterialName("G4_CESIUM_IODIDE"),
			m_worldSize(100* m , 100* m , 100* m ), m_sipmHalfSize(0,0, 0), m_xtalHalfSizeS(6.75 * mm, 6.75 * mm, 6.75 * mm), m_xtalHalfSizeA(14.0 * mm, 14.0 * mm, 14.0* mm), m_iNSCellX(4), m_iNSCellY(4), m_iNSCellZ(1), m_iNACellX(12), m_iNACellY(12), m_iNACellZ(1), m_dSCellGap(6.5 * mm, 6.5 * mm, 79.5 * mm), m_dACellGap(4.0 * mm, 4.0 * mm, 0 * mm), m_dASGap(85 * mm), m_dSTotalZ(0), m_pMessenger(NULL) {

	m_pMessenger = new FullDetectorConstructionMessenger(this);

}

//-----------------------------------------------------------------------------
FullDetectorConstruction::~FullDetectorConstruction() {

	if (m_pMessenger) delete m_pMessenger;

}

//-----------------------------------------------------------------------------
G4VPhysicalVolume* FullDetectorConstruction::Construct() {

	// Get the materials
	CIMaterials& materials = *CIMaterials::Instance();
	// Define sensitive detectors, i.e. the scintillator and the SensitiveDetectorManager
	G4SDManager* SDManager = G4SDManager::GetSDMpointer();
	SDManager-> AddNewDetector(m_pCISensitiveScintiDetector);
	SDManager-> AddNewDetector(m_pCISensitiveOpticalDetector);
	SDManager-> AddNewDetector(m_pCISensitiveMaterials);

	// Define experimental hall as real and logical volumes, and map the two
	const G4String World_Name = "World";

	G4Box* World_Solid = new G4Box(World_Name + m_SolidSuffix, m_worldSize.x(), m_worldSize.y(), m_worldSize.z());

	m_WorldLog = new G4LogicalVolume(World_Solid, materials.GetMaterial("G4_AIR"), World_Name + m_LogicalVolumeSuffix);

	m_WorldPhys = new G4PVPlacement(NULL, G4ThreeVector(), World_Name + m_PhysicalVolumeSuffix, m_WorldLog, NULL,
			false, 0, m_bVolPlacementCheck);

	//Cell number
	G4int iCell = 0;

  G4cout << "#######################################################################"
  << G4endl
  <<        "#############   FullDetectorConstruction::Construct()  ################"
  << G4endl;
  outfilePos.open("positions.dat",ios::ate);

	//Construct the array of Scatter cells.
  ConstructScatter(iCell);
  G4cout << "#######################################################################"  << G4endl;
  ConstructAbsorberCsISiPM( iCell);
   //ConstructConcreteWall();
  G4cout << "#######################################################################"
  << G4endl;
	G4cout<<"Inter Detector Gap:: "<<m_dASGap<<G4endl;
  G4cout << "#######################################################################"
  << G4endl;
  outfilePos.close();

    return m_WorldPhys;
}

//-----------------------------------------------------------------------------
void FullDetectorConstruction::ConstructScatter(G4int& iCell) {

	// Get the materials
	CIMaterials& materials = *CIMaterials::Instance();
	const G4Material* xtalMaterialS = materials.GetMaterial(m_strScatterDetectorMaterialName);
	const G4String sCellName = CIModuleTable::GetScatterCellName();

	// Place the PMT
	G4RotationMatrix* pNullRotation = NULL;
	
	G4RotationMatrix *Rot_180 = new G4RotationMatrix(G4ThreeVector(0.0,1.0,0.0), - 180.0*deg); 
	G4RotationMatrix *Rot_p90 = new G4RotationMatrix(G4ThreeVector(0.0,1.0,0.0), + 90.0*deg); 
	G4RotationMatrix *Rot_m90 = new G4RotationMatrix(G4ThreeVector(0.0,1.0,0.0), - 90.0*deg); 

	//	const G4String PVT_Name = "PVT";

	char* name;
	char* name2;

	//	const G4String xtal_Name = m_strName + "_xtal";

	//************************************************************************/
	//************************************************************************/
	// Build the scintillator
	//************************************************************************/
	//************************************************************************/

	
	const G4String xtal_Name = "Scint_SCELL_XTAL";
	G4Box* xtal_solid = new G4Box(xtal_Name + m_SolidSuffix, m_xtalHalfSizeS.x(), m_xtalHalfSizeS.y(), m_xtalHalfSizeS.z());
	G4Box* xtal2_solid = new G4Box(xtal_Name + "2" + m_SolidSuffix, m_xtalHalfSizeS.x(), m_xtalHalfSizeS.y(), m_xtalHalfSizeS.z());

	G4LogicalVolume* xtal_Log = new G4LogicalVolume(xtal_solid, const_cast<G4Material*> (xtalMaterialS), xtal_Name
			+ m_LogicalVolumeSuffix, NULL, m_pCISensitiveScintiDetector);
	G4LogicalVolume* xtal2_Log = new G4LogicalVolume(xtal2_solid, const_cast<G4Material*> (xtalMaterialS), xtal_Name + "2"
			+ m_LogicalVolumeSuffix, NULL, m_pCISensitiveScintiDetector);

	assert (xtal_Log != NULL);
	assert (xtal2_Log != NULL);

	//distance between groups is 7 cm
	//************************************************************************/
	//************************************************************************/
	// Build the Glass (SiPM equivalent)
	//************************************************************************/
	//************************************************************************/
	//box size = 1.35 1.35 0.1  # made slightly smaller
	const G4String glass_Name = "Scint_SCELL_GLASS";

	G4ThreeVector glassHalfSize(m_xtalHalfSizeS.x(), m_xtalHalfSizeS.y(),0.5*mm);
	G4Box* glass_solid = new G4Box(glass_Name + m_SolidSuffix, glassHalfSize.x(), glassHalfSize.y(), glassHalfSize.z());
	G4LogicalVolume* glass_Log = new G4LogicalVolume(glass_solid,  materials.GetMaterial("G4_GLASS_PLATE"), glass_Name
							 + m_LogicalVolumeSuffix, NULL, NULL);
	G4LogicalVolume* glass2_Log = new G4LogicalVolume(glass_solid,  materials.GetMaterial("G4_GLASS_PLATE"), glass_Name
							 + "2" + m_LogicalVolumeSuffix, NULL, NULL);

	assert (glass_Log != NULL);
	assert (glass2_Log != NULL);

	//************************************************************************/
	//************************************************************************/
	// Build the Gold
	//************************************************************************/
	//************************************************************************/
        //box size = 1.35 1.35 0.0002   # made slightly smaller
	const G4String gold_Name = "Scint_SCELL_GOLD";

	G4ThreeVector goldHalfSize(m_xtalHalfSizeS.x(), m_xtalHalfSizeS.y(), 0.001*mm);
	G4Box* gold_solid = new G4Box(gold_Name + m_SolidSuffix, goldHalfSize.x(), goldHalfSize.y(), goldHalfSize.z());
	G4LogicalVolume* gold_Log = new G4LogicalVolume(gold_solid,  materials.GetMaterial("G4_Au"), gold_Name
							 + m_LogicalVolumeSuffix, NULL, NULL);
	G4LogicalVolume* gold2_Log = new G4LogicalVolume(gold_solid,  materials.GetMaterial("G4_Au"), gold_Name
							 + "2" + m_LogicalVolumeSuffix, NULL, NULL);

	assert (gold_Log != NULL);
	assert (gold2_Log != NULL);

	//************************************************************************/
	//************************************************************************/
	// Build the FOAM
	//************************************************************************/
	//************************************************************************/
	//# Foam is Plastazote LD45 which is polyethylene at 45kg/m^3 or 0.45g/cm3.  
	  //# I measured 42+/-2 g/cm^3.

	const G4String foam_Name = "Scint_SCELL_FOAM";
	const G4String foam2_Name = "Scint_SCELL_FOAM2";
	G4ThreeVector foamHalfSize(64.*mm,64.*mm, 13.0*mm); //Size Unknown!. Up until carbon fibure

	G4Box* foam_solid = new G4Box(foam_Name + m_SolidSuffix, foamHalfSize.x(),foamHalfSize.y(),foamHalfSize.z());
	G4Box* foam2_solid = new G4Box(foam2_Name + m_SolidSuffix, foamHalfSize.x(),foamHalfSize.y(),foamHalfSize.z());
	
	G4LogicalVolume* foam_Log = new G4LogicalVolume(foam_solid,  materials.GetMaterial("PLASTAZOTE"), foam_Name
							+ m_LogicalVolumeSuffix, NULL, NULL);
	G4LogicalVolume* foam2_Log = new G4LogicalVolume(foam2_solid,  materials.GetMaterial("PLASTAZOTE"), foam2_Name
							 + m_LogicalVolumeSuffix, NULL, NULL);
	
	assert (foam_Log != NULL);
	assert (foam2_Log != NULL);

	//************************************************************************/
	//************************************************************************/
	// Build the PCB
	//************************************************************************/
	//************************************************************************/

	const G4String PCB_Name = "Scint_SCELL_PCB";

	G4ThreeVector PCBHalfSize(24.0/2.0 *cm, 24.0/2.0 *cm, 1.58/2.0*mm); //Size Unknown!. Up until carbon fibure

	G4Box* PCB_solid = new G4Box(PCB_Name + m_SolidSuffix,PCBHalfSize.x(),PCBHalfSize.y(),PCBHalfSize.z());
	G4LogicalVolume* PCB_Log = new G4LogicalVolume(PCB_solid,  materials.GetMaterial("FR4"), PCB_Name
							 + m_LogicalVolumeSuffix, NULL, NULL);
	assert (PCB_Log != NULL);



	//************************************************************************/
	//************************************************************************/
	// Build the CARBON FIBRE
	//************************************************************************/
	//************************************************************************/
	// # carbon fibre density:
	// # weight is 22.13 g for sheet 1/32" sheet 15.3 cm x 11.8 cm 
	// # 1/32"=0.03125; thickness measured to be between 0.030 and 0.033
	//# use 0.03125 == 0.079375 cm ; assume 0.08 ==> volume= 14.44 cm^3
	//# density = 22.13/14.44 = 1.533
	
	//  # the front-back distance between CF faces is 18 mm @edge and 21 mm @ctr 
	// # pixels are mostly in central region so use 20 mm as front back spacing 
	//# therefore, rear CF is shifted by 2.0-0.08 = 1.92 mm wrt to front
	
	// # boards are  15x12x0.8 cm, shifted so 12x12 part centres on symmetry axis CFIBRE521ICRU
        //box size = 30 30 0.08 //I'm not 100 percent clear bout size
	const G4String carbonfibre_Name = "Scint_SCELL_CARBONFIBRE";

	G4ThreeVector carbonfibreHalfSize(24.0/2.0 *cm, 24.0/2.0 *cm, 0.4*mm); //Size Unknown!. Up until carbon fibure

	G4Box* carbonfibre_solid = new G4Box(carbonfibre_Name + m_SolidSuffix,carbonfibreHalfSize.x(),carbonfibreHalfSize.y(),carbonfibreHalfSize.z());
	G4LogicalVolume* carbonfibre_Log = new G4LogicalVolume(carbonfibre_solid,  materials.GetMaterial("CARBONFIBRE"), carbonfibre_Name
							 + m_LogicalVolumeSuffix, NULL, NULL);
	assert (carbonfibre_Log != NULL);

	//************************************************************************/
	//************************************************************************/
	// Build the SiPM
	//************************************************************************/
	//************************************************************************/
	const G4String sipm_Name = "scatter_sipm";
	SenSL60035SiPMArray* sipm_Log = new SenSL60035SiPMArray(sipm_Name, m_pCISensitiveMaterials);
      	G4LogicalVolume* sipm_LogVolume =  sipm_Log->GetLogicalVol();
       	G4ThreeVector m_sipmHalfSize = sipm_Log->GetHalfSize();
	
	//Visualization attributes for the Xtal and Cell
	G4bool bEnableXtalVisualization = true;
	// Orange crystal
	G4VisAttributes* visAttXtal = new G4VisAttributes(G4Colour(0.9, 0.50, 0.2));
	G4VisAttributes* visAttSiPM = new G4VisAttributes(G4Colour(0.9, 0.20, 0.9));
	G4VisAttributes* visAttCarbonFibre = new G4VisAttributes(G4Colour(0,1,1));
	G4VisAttributes* visAttPCB = new G4VisAttributes(G4Colour(0,0,1));
	G4VisAttributes* visAttGlass = new G4VisAttributes(G4Colour(1,1,1));
	G4VisAttributes* visAttGold = new G4VisAttributes(G4Colour(0,0,1));
	G4VisAttributes* visAttFoam = new G4VisAttributes(G4Colour(0.5,0.5,0.5));
	

	visAttXtal->SetVisibility(bEnableXtalVisualization);
	visAttSiPM->SetVisibility(bEnableXtalVisualization);
	visAttCarbonFibre->SetVisibility(bEnableXtalVisualization);
	visAttGlass->SetVisibility(bEnableXtalVisualization);
	visAttGold->SetVisibility(bEnableXtalVisualization);
	visAttFoam->SetVisibility(bEnableXtalVisualization);	
	visAttPCB->SetVisibility(bEnableXtalVisualization);

	xtal_Log->SetVisAttributes(visAttXtal);
	xtal2_Log->SetVisAttributes(visAttXtal);
	carbonfibre_Log->SetVisAttributes(visAttCarbonFibre);
	glass_Log->SetVisAttributes(visAttGlass);
	glass2_Log->SetVisAttributes(visAttGlass);
	gold_Log->SetVisAttributes(visAttGold);
	gold2_Log->SetVisAttributes(visAttGold);
	PCB_Log->SetVisAttributes(visAttPCB);
	sipm_LogVolume->SetVisAttributes(visAttSiPM);
	foam_Log->SetVisAttributes(visAttFoam);
	foam2_Log->SetVisAttributes(visAttFoam);

	G4ThreeVector offset;
	G4VPhysicalVolume* pV;
	G4VPhysicalVolume* sipm_Phys;
	G4VPhysicalVolume* PCB_Phys;

	G4ThreeVector centrePos;

	G4VPhysicalVolume* alCan_Phys;	
	G4VPhysicalVolume* alCase_Phys;	
	G4VPhysicalVolume* foam_Phys;	
	G4VPhysicalVolume* foam2_Phys;		

	G4VPhysicalVolume* glass_Phys;	
	G4VPhysicalVolume* gold_Phys;	
	G4VPhysicalVolume* carbonfibre_Phys;	

	const G4String ScintAir_Name ("ScintAir");
	//Pixel Imager: Fixed values
	m_iNSCellX =12;
	m_iNSCellY= 12;
	m_iNSCellZ= 1;

	int placeFoam =0;
	int placeCarbon =0;
	int placePCB =0;
	int groupMax = 1; 
	
	for (int group = 0; group < groupMax; group++) {
	  for (int iX = 0; iX < m_iNSCellX; iX++) {
	    for (int iY = 0; iY < m_iNSCellY; iY++) {
	      for (int iZ = 0; iZ < m_iNSCellZ; iZ++) {
		
		asprintf(&name, "%s%s%02d.%02d.%02d.%02d", sCellName.data(),"XTAL", iX, iY, iZ,group);

	      //************************************************************************/
	      // Place the Scintillator
	      //************************************************************************/

	      offset.set(m_xtalHalfSizeS.x(), m_xtalHalfSizeS.y(),m_xtalHalfSizeS.z());

	      offset = 2* offset + m_dSCellGap;
	      G4cout << "offset is " << offset << " with a cell gap that was " << m_dSCellGap << endl;
	      G4ThreeVector scint_placement((-m_iNSCellX + 1 + 2* iX ) * offset.x() / 2., (-m_iNSCellY + 1 + 2* iY )* offset.y() / 2.,0); //position always relative to mother volume (foam)

		  G4cout << "Scatter " << iY << " " << scint_placement.y() << " " << iX << " " << scint_placement.x() <<  " " <<iZ << " " << scint_placement.z() << G4endl;
		  if (iZ==0){
		    pV = new G4PVPlacement(NULL, scint_placement, xtal_Log, name + m_PhysicalVolumeSuffix, m_WorldLog, false,iCell, m_bVolPlacementCheck);
		  }
		  else if(iZ==1)
		    {
		      pV = new G4PVPlacement(NULL, scint_placement, xtal2_Log, name + m_PhysicalVolumeSuffix, m_WorldLog, false,iCell, m_bVolPlacementCheck);
		    }
		  
		  outfilePos << iCell << " "<< 0 << " " << 0 << " " << -1 << " " << scint_placement.getX() << " " << scint_placement.getY()  << " " << scint_placement.getZ()  << " " << 2.0*m_xtalHalfSizeS.x() << " " << 2.0*m_xtalHalfSizeS.y()<< " " << 2.0*m_xtalHalfSizeS.z() << G4endl;

		  centrePos=scint_placement;
		  m_pCISensitiveScintiDetector->GetCIModuleTable()->InsertModule(iCell, iZ, centrePos, CIModuleTable::SUBDET_SCATTER, pV);
		  iCell++;
	      

	      //************************************************************************/
	      // Place the SIPM -Equivalent
	      //************************************************************************/
	      G4ThreeVector sipm_placement = scint_placement;			
	      sipm_placement += G4ThreeVector(0, 0, +m_xtalHalfSizeS.z() + m_sipmHalfSize.z());
	      sipm_Phys = new G4PVPlacement(NULL, sipm_placement, sipm_LogVolume, sipm_Name + m_PhysicalVolumeSuffix, m_WorldLog, false,false, m_bVolPlacementCheck);
	      	G4cout << " scatter sipm is placed at " <<sipm_placement << endl;

	      //************************************************************************/
	      // Place the Carbon Fiber - 1 boards in front of scatter layer.
	      //************************************************************************/
	      
	      if (group==0 && placeCarbon <1)
		{
		  G4ThreeVector carbonfibreFront_placement = G4ThreeVector(0,0, -m_xtalHalfSizeS.z()- carbonfibreHalfSize.z()+ iZ*offset.z());
		  G4cout << "placing carbon at " << carbonfibreFront_placement << G4endl;
		  carbonfibre_Phys = new G4PVPlacement(NULL, carbonfibreFront_placement, carbonfibre_Log, "carbonfibre" + m_PhysicalVolumeSuffix, m_WorldLog, false,false, m_bVolPlacementCheck);	

		  placeCarbon++;

		}
	      //************************************************************************/
	      // Place the PCB - 1 board in back of scatter layer.
	      //************************************************************************/
	      
	      if (group==0 && placePCB <1)
		{
		  G4ThreeVector PCB_placement = G4ThreeVector(0,0, +m_xtalHalfSizeS.z() +2.0*m_sipmHalfSize.z()+  PCBHalfSize.z()+ iZ*offset.z());
		  G4cout << "placing PCB at " << PCB_placement << G4endl;
		  PCB_Phys = new G4PVPlacement(NULL, PCB_placement, PCB_Log, "PCB_Scat" + m_PhysicalVolumeSuffix, m_WorldLog, false,false, m_bVolPlacementCheck);	
		  placePCB++;
		}

	      
	    }
	  }
	}
	}


G4cout << "#############   Constructed Scatter Detector  #########################" << G4endl;
	G4cout<<"Scatter Crystal Material:: "<<m_strScatterDetectorMaterialName<<G4endl;
	G4cout<<G4endl;

}
//-----------------------------------------------------------------------------
void FullDetectorConstruction::ConstructConcreteWall() {

  // Define the materials
  CIMaterials& materials = *CIMaterials::Instance();
 G4double wall_Thickness_m = 1.0*m;

 G4ThreeVector wall_Halfsize(10.0*m,10.0*m,10.0*m);
 G4ThreeVector wall_placement(0*m,0*m,0.0*m);
  const G4String wall_Name = "Wall";

  G4VSolid* wall_outer_box_solid = new G4Box("a_acase_outer", wall_Halfsize.x() + wall_Thickness_m/2.0, wall_Halfsize.y()+ wall_Thickness_m/2.0, wall_Halfsize.z() + wall_Thickness_m/2.0);	
  G4VSolid* wall_inner_box_solid = new G4Box("a_acase_inner", wall_Halfsize.x(), wall_Halfsize.y(), wall_Halfsize.z());  

  G4VSolid* wall_box_solid = new G4SubtractionSolid(wall_Name + m_SolidSuffix, wall_outer_box_solid, wall_inner_box_solid);   
  G4LogicalVolume* wall_Log = new G4LogicalVolume(wall_box_solid,  materials.GetMaterial("G4_CONCRETE"), wall_Name
						  + m_LogicalVolumeSuffix, NULL, NULL);

  assert (wall_Log != NULL);

  G4VisAttributes* visAttWallCase = new G4VisAttributes(G4Colour(0.0, 1.0, 1.0));

  wall_Log->SetVisAttributes(visAttWallCase);

  G4bool bEnableXtalVisualization = true;

  visAttWallCase->SetVisibility(bEnableXtalVisualization);

   G4VPhysicalVolume* wall_Phys;	
   wall_Phys = new G4PVPlacement(NULL, wall_placement, wall_Log, wall_Name + m_PhysicalVolumeSuffix, m_WorldLog, false,false, m_bVolPlacementCheck);



}

//-----------------------------------------------------------------------------
void FullDetectorConstruction::ConstructAbsorberCsISiPM(G4int& iCell) {

	// Get the materials
	CIMaterials& materials = *CIMaterials::Instance();
	const G4Material* xtalMaterialA = materials.GetMaterial(m_strAbsorberDetectorMaterialName);
	const G4String aCellName = CIModuleTable::GetAbsorberCellName();

	char* name;
		    
	// Build the scintillator

	const G4String xtal_Name = "Scint_ACELL_XTAL";
	G4Box* xtal_solid = new G4Box(xtal_Name + m_SolidSuffix, m_xtalHalfSizeA.x(), m_xtalHalfSizeA.y(), m_xtalHalfSizeA.z());

	G4LogicalVolume* xtal_Log = new G4LogicalVolume(xtal_solid, const_cast<G4Material*> (xtalMaterialA), xtal_Name
			+ m_LogicalVolumeSuffix, NULL, m_pCISensitiveScintiDetector);
	assert (xtal_Log != NULL);


	const G4String carbonfibre_Name = "Scint_ACELL_CARBONFIBRE";
	G4ThreeVector carbonfibreHalfSize((38.4/2.0)*cm,(38.4/2.0)*cm, 0.4*mm); 

	G4Box* carbonfibre_solid = new G4Box(carbonfibre_Name + m_SolidSuffix,carbonfibreHalfSize.x(),carbonfibreHalfSize.y(),carbonfibreHalfSize.z());
	G4LogicalVolume* carbonfibre_Log = new G4LogicalVolume(carbonfibre_solid,  materials.GetMaterial("CARBONFIBRE"), carbonfibre_Name
							 + m_LogicalVolumeSuffix, NULL, NULL);
	assert (carbonfibre_Log != NULL);


	//************************************************************************/
	//************************************************************************/
	// Build the PCB
	//************************************************************************/
	//************************************************************************/

	const G4String PCB_Name = "Scint_ACELL_PCB";

	G4ThreeVector PCBHalfSize((38.4/2.0)*cm,(38.4/2.0)*cm, 1.58/2.0*mm);

	G4Box* PCB_solid = new G4Box(PCB_Name + m_SolidSuffix,PCBHalfSize.x(),PCBHalfSize.y(),PCBHalfSize.z());
	G4LogicalVolume* PCB_Log = new G4LogicalVolume(PCB_solid,  materials.GetMaterial("FR4"), PCB_Name
							 + m_LogicalVolumeSuffix, NULL, NULL);
	assert (PCB_Log != NULL);

	//************************************************************************/
	//************************************************************************/
	// Build the SiPM
	//************************************************************************/
	//************************************************************************/
	const G4String sipm_Name = "absorber_sipm";
	SenSL60035SiPMArray* sipm_Log = new SenSL60035SiPMArray(sipm_Name, m_pCISensitiveMaterials);
      	G4LogicalVolume* sipm_LogVolume =  sipm_Log->GetLogicalVol();
       	G4ThreeVector m_sipmHalfSize = sipm_Log->GetHalfSize();

       
	//Visualization attributes for the Xtal and Cell
	G4bool bEnableXtalVisualization = true;

	G4VisAttributes* visAttXtal = new G4VisAttributes(G4Colour(0.9, 0.50, 0.2));
	G4VisAttributes* visAttSiPM = new G4VisAttributes(G4Colour(0.9, 0.20, 0.9));
	G4VisAttributes* visAttPCB = new G4VisAttributes(G4Colour(0,0,1));
	G4VisAttributes* visAttCarbonFibre = new G4VisAttributes(G4Colour(0,1,1));
	visAttCarbonFibre->SetVisibility(bEnableXtalVisualization);
	carbonfibre_Log->SetVisAttributes(visAttCarbonFibre);

	visAttXtal->SetVisibility(bEnableXtalVisualization);
	visAttSiPM->SetVisibility(bEnableXtalVisualization);
	visAttPCB->SetVisibility(bEnableXtalVisualization);

	xtal_Log->SetVisAttributes(visAttXtal);
	PCB_Log->SetVisAttributes(visAttPCB);
	sipm_LogVolume->SetVisAttributes(visAttSiPM);

	G4ThreeVector offset;
	G4VPhysicalVolume* pV;
	G4VPhysicalVolume* sipm_Phys;
	G4VPhysicalVolume* PCB_Phys;
	G4VPhysicalVolume* carbonfibre_Phys;	

	G4ThreeVector centrePos;
	int	placePCB =0;
	int placeCarbon=0;
	for (int iX = 0; iX < m_iNACellX; iX++) {
	  for (int iY = 0; iY < m_iNACellY; iY++) {
	    for (int iZ = 0; iZ < m_iNACellZ; iZ++) {
			  
	      
	      asprintf(&name, "%s%s%02d.%02d.%02d", aCellName.data(),"XTAL", iX, iY, iZ);
	      G4cout <<  "absorber name is " << name << G4endl;
	      offset.set(m_xtalHalfSizeA.x(), m_xtalHalfSizeA.y(),m_xtalHalfSizeA.z());

	      offset = 2* offset + m_dACellGap;	     

	      G4ThreeVector scint_placement((-m_iNACellX + 1 + 2* iX ) * offset.x() / 2., (-m_iNACellY + 1 + 2* iY )
					    * offset.y() / 2., (-m_iNACellZ + 1 + 2* iZ )* offset.z());
	      scint_placement += G4ThreeVector(0, 0, m_dASGap);
	      
	      
	      // Place the Scintillator 

	      G4cout << "Absorber " << iY << " " << scint_placement.y() << G4endl;
	      
	      pV = new G4PVPlacement(NULL,scint_placement, xtal_Log, name + m_PhysicalVolumeSuffix,m_WorldLog , false,iCell, m_bVolPlacementCheck);

	      centrePos= scint_placement;
	      

	       m_pCISensitiveScintiDetector->GetCIModuleTable()->InsertModule(iCell, iZ, centrePos, CIModuleTable::SUBDET_ABSORBER, pV);
	       
	       outfilePos << iCell << " "<< 0 << " " << 0 << " " << -1 << " " << scint_placement.getX() << " " <<  scint_placement.getY()  << " " <<  scint_placement.getZ()  << " " << 2.0*m_xtalHalfSizeA.x() << " " << 2.0*m_xtalHalfSizeA.y()<< " " << 2.0*m_xtalHalfSizeA.z() << G4endl;
	       
	       
	      // Place the SiPM
		
	       G4ThreeVector sipm_placement = scint_placement;
	       

	       sipm_placement+= G4ThreeVector(0, 0, +m_xtalHalfSizeA.z()+m_sipmHalfSize.z());
	       sipm_placement+= G4ThreeVector(+7.2*mm, +7.2*mm, 0);
	       G4cout << " sipm1 is placed at " << sipm_placement<< G4endl; 
	       sipm_Phys = new G4PVPlacement(NULL,sipm_placement, sipm_LogVolume, sipm_Name + "1" + m_PhysicalVolumeSuffix,m_WorldLog , false,0, m_bVolPlacementCheck);
	   	     
	       sipm_placement = scint_placement;
	       sipm_placement+= G4ThreeVector(0, 0, +m_xtalHalfSizeA.z()+m_sipmHalfSize.z());
	       sipm_placement+= G4ThreeVector(-7.2*mm,-7.2*mm, 0);
	       G4cout << " sipm2 is placed at " << sipm_placement<< G4endl; 
	       sipm_Phys = new G4PVPlacement(NULL,sipm_placement, sipm_LogVolume, sipm_Name + "2"  + m_PhysicalVolumeSuffix,m_WorldLog , false,0, m_bVolPlacementCheck);

	       sipm_placement = scint_placement;
	       sipm_placement+= G4ThreeVector(0, 0, +m_xtalHalfSizeA.z()+m_sipmHalfSize.z());
	       sipm_placement+= G4ThreeVector(-7.2*mm, +7.2*mm, 0);
	       G4cout << " sipm3 is placed at " << sipm_placement<< G4endl; 
	       sipm_Phys  = new G4PVPlacement(NULL,sipm_placement, sipm_LogVolume, sipm_Name + "3" + m_PhysicalVolumeSuffix,m_WorldLog, false,0, m_bVolPlacementCheck); 

	       sipm_placement = scint_placement;
	       sipm_placement+= G4ThreeVector(0, 0, +m_xtalHalfSizeA.z()+m_sipmHalfSize.z());
	       sipm_placement+= G4ThreeVector(+7.2*mm, -7.2*mm, 0);
	       G4cout << " sipm4 is placed at " << sipm_placement<< G4endl; 
	       sipm_Phys  = new G4PVPlacement(NULL,sipm_placement, sipm_LogVolume, sipm_Name + "4" + m_PhysicalVolumeSuffix,m_WorldLog, false,0, m_bVolPlacementCheck);
	       	      
	       //************************************************************************/
	      // Place the Carbon Fiber - 1 boards in front of absorber layer.
	      //************************************************************************/
	      
	      if (placeCarbon <1)
		{
		  G4ThreeVector carbonfibreFront_placement = G4ThreeVector(0,0, +m_dASGap -m_xtalHalfSizeA.z()- carbonfibreHalfSize.z());
		  G4cout << "placing carbon at " << carbonfibreFront_placement << G4endl;
		  carbonfibre_Phys = new G4PVPlacement(NULL, carbonfibreFront_placement, carbonfibre_Log, "carbonfibre" + m_PhysicalVolumeSuffix, m_WorldLog, false,false, m_bVolPlacementCheck);	
		  placeCarbon++;

		}

	      //************************************************************************/
	      // Place the PCB - 1 board in back of absorber layer.
	      //************************************************************************/
	      
	      if (placePCB <1)
		{
		  G4ThreeVector PCB_placement = G4ThreeVector(0,0, +m_dASGap +m_xtalHalfSizeA.z()+2.0*m_sipmHalfSize.z() + PCBHalfSize.z()+ iZ*offset.z());
		  G4cout << "placing PCB at " << PCB_placement << G4endl;
		  PCB_Phys = new G4PVPlacement(NULL, PCB_placement, PCB_Log, "PCBAbs"+ m_PhysicalVolumeSuffix, m_WorldLog, false,false, m_bVolPlacementCheck);	
		  placePCB++;
		}

	      iCell++;
	      	      
	    }
	  }
	}


  G4cout << "#############   Constructed Absorber Detector  #########################"
  << G4endl;
	G4cout<<"Absorber Crystal Material:: "<<m_strAbsorberDetectorMaterialName<<G4endl;
	G4cout<<G4endl;


}

