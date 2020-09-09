/***************************************************************************
 *   Copyright (C)NRC 2015                                                 *
 *   audrey.macleod@nrc.cnrg.gc.ca
 *                                                                         *
 ***************************************************************************/
/**
 * @file PixelImager.cpp
 * @brief Build the pixel imager including multiple layers of scatter and absorber detectors with SiPM/PMT readout
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


//Determine the crystal sizes, crystal materials and spacings in the constructor
// The gaps for scatterer (center to cetner) measures 9.3 cm
// the absorber scatter distance measures 266.7 mm (m_dasgap is meausred center)
// m_dSCellGap, and m_dACellGap, are the spacing between the crystals

//-----------------------------------------------------------------------------
FullDetectorConstruction::FullDetectorConstruction(CISensitiveScintiDetector* pCISensitiveScintiDetector, CISensitiveOpticalDetector* pCISensitiveOpticalDetector, CISensitiveMaterials* pCISensitiveMaterials) :
	m_pCISensitiveScintiDetector(pCISensitiveScintiDetector),
			m_pCISensitiveOpticalDetector(pCISensitiveOpticalDetector), m_pCISensitiveMaterials(pCISensitiveMaterials), m_WorldPhys(NULL), m_WorldLog(NULL),
			m_pNullFieldMgr(NULL), m_bVolPlacementCheck(false),m_strScatterDetectorMaterialName("G4_CESIUM_IODIDE"), m_strAbsorberDetectorMaterialName("G4_SODIUM_IODIDE"),
			m_worldSize(100* m , 100* m , 100* m ), m_sipmHalfSize(0,0, 0), m_xtalHalfSizeS(6.75 * mm, 6.75 * mm, 6.75 * mm), m_xtalHalfSizeA(12.5 * mm, 12.5 * mm, 20.0* mm), m_iNSCellX(9), m_iNSCellY(9), m_iNSCellZ(2), m_iNACellX(10), m_iNACellY(10), m_iNACellZ(1),
	m_dSCellGap(6.5 * mm, 6.5 * mm, 79.5 * mm), m_dACellGap(7.0 * mm, 7.0 * mm, 0 * mm), m_dASGap(266.7 * mm), m_dSTotalZ(0), m_pMessenger(NULL) {

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

  //This file positions.dat outputs the center positions of all the crystals
  outfilePos.open("positions.dat",ios::ate);

  //Construct the array of Scatter cells.
  ConstructScatter(iCell);
  G4cout << "#######################################################################"
	 << G4endl;
  ConstructAbsorber(iCell);
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

	char* name;

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


	//************************************************************************/
	//************************************************************************/
	// Build the Glass (SiPM equivalent)
	//************************************************************************/
	//************************************************************************/
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
	G4ThreeVector foamHalfSize(173.*mm,187.5*mm, 13.0*mm); //Size Unknown!. Up until carbon fibure

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
        
	const G4String carbonfibre_Name = "Scint_SCELL_CARBONFIBRE";
	G4ThreeVector carbonfibreHalfSize(173.*mm,187.5*mm, 0.4*mm); 

	G4Box* carbonfibre_solid = new G4Box(carbonfibre_Name + m_SolidSuffix,carbonfibreHalfSize.x(),carbonfibreHalfSize.y(),carbonfibreHalfSize.z());
	G4LogicalVolume* carbonfibre_Log = new G4LogicalVolume(carbonfibre_solid,  materials.GetMaterial("CARBONFIBRE"), carbonfibre_Name
							 + m_LogicalVolumeSuffix, NULL, NULL);
	assert (carbonfibre_Log != NULL);

	//Visualization attributes for the Xtal and Cell
	G4bool bEnableXtalVisualization = true;

	// Orange crystal
	G4VisAttributes* visAttXtal = new G4VisAttributes(G4Colour(0.9, 0.50, 0.2));
	G4VisAttributes* visAttSiPM = new G4VisAttributes(G4Colour(0.9, 0.20, 0.9));
	G4VisAttributes* visAttCarbonFibre = new G4VisAttributes(G4Colour(0,1,1));
	G4VisAttributes* visAttGlass = new G4VisAttributes(G4Colour(1,1,1));
	G4VisAttributes* visAttGold = new G4VisAttributes(G4Colour(0,0,1));
	G4VisAttributes* visAttFoam = new G4VisAttributes(G4Colour(0.5,0.5,0.5));

	visAttXtal->SetVisibility(bEnableXtalVisualization);
	visAttSiPM->SetVisibility(bEnableXtalVisualization);
	visAttCarbonFibre->SetVisibility(bEnableXtalVisualization);
	visAttGlass->SetVisibility(bEnableXtalVisualization);
	visAttGold->SetVisibility(bEnableXtalVisualization);
	visAttFoam->SetVisibility(bEnableXtalVisualization);	

	xtal_Log->SetVisAttributes(visAttXtal);
	xtal2_Log->SetVisAttributes(visAttXtal);
	carbonfibre_Log->SetVisAttributes(visAttCarbonFibre);
	glass_Log->SetVisAttributes(visAttGlass);
	glass2_Log->SetVisAttributes(visAttGlass);
	gold_Log->SetVisAttributes(visAttGold);
	gold2_Log->SetVisAttributes(visAttGold);

	foam_Log->SetVisAttributes(visAttFoam);
	foam2_Log->SetVisAttributes(visAttFoam);

	G4ThreeVector offset;
	G4VPhysicalVolume* pV;
	G4ThreeVector centrePos;

	G4VPhysicalVolume* foam_Phys;	
	G4VPhysicalVolume* foam2_Phys;		

	G4VPhysicalVolume* glass_Phys;	
	G4VPhysicalVolume* gold_Phys;	
	G4VPhysicalVolume* carbonfibre_Phys;	

	const G4String ScintAir_Name ("ScintAir");
	//Pixel Imager: Fixed values
	m_iNSCellX =3;
	m_iNSCellY= 3;
	m_iNSCellZ= 2;

	int placeFoam =0;
	int placeCarbon =0;
	int groupMax = 9; //nine groups of 3 by 3
	
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
		G4ThreeVector scint_placement((-m_iNSCellX + 1 + 2* iX ) * offset.x() / 2., (-m_iNSCellY + 1 + 2* iY )
					      * offset.y() / 2.,0); //position always relative to mother volume (foam)
		
		//************************************************************************/
		// Place the Foam - Once for each
		//************************************************************************/
		
		      G4ThreeVector foam_placement(0,-4.45*cm,0);
		      G4ThreeVector foam2_placement(0,-4.45*cm,1.0*offset.z());
		      
		      if (placeFoam==0)
			{
			  
			  foam_Phys = new G4PVPlacement(NULL, foam_placement, foam_Log, "foamS" + m_PhysicalVolumeSuffix, m_WorldLog, false,false, m_bVolPlacementCheck);
			  G4cout << "Foam placed " << foam_placement.x() << " " << foam_placement.y() <<  " " << foam_placement.z() << G4endl;
			  
			  foam2_Phys = new G4PVPlacement(NULL, foam2_placement, foam2_Log, "foam2S" + m_PhysicalVolumeSuffix, m_WorldLog, false,false, m_bVolPlacementCheck);
			  G4cout << "Foam2 placed " << foam2_placement.x() << " " << foam2_placement.y() <<  " " << foam2_placement.z() << G4endl;
			  
			  placeFoam=1;
			  
			}
		      
		      
		      scint_placement += G4ThreeVector(70.*mm,-70.*mm,0); //start in botteom left hand corner
		      
		      G4cout << "for group " << group << " group%3 is " << group%3 << " group/3 is " << group/3 << G4endl;
		      
		      for (int p =0; p < group%3; p++)
			{
			  scint_placement += G4ThreeVector(-70.*mm,0,0); 
			}
		      
		      for (int k =0; k< group/3; k++)
			{
			  scint_placement += G4ThreeVector(0,70.*mm,0);
		}

	      scint_placement += G4ThreeVector(0,+4.45*cm,0);

	      //************************************************************************/
	      // Place the Scintillator
	      //************************************************************************/

	      
		  G4ThreeVector absScinti_placement;
		  G4cout << "Scatter " << iY << " " << scint_placement.y() << " " << iX << " " << scint_placement.x() <<  " " <<iZ << " " << scint_placement.z() << G4endl;
		  if (iZ==0){
		    pV = new G4PVPlacement(NULL, scint_placement, xtal_Log, name + m_PhysicalVolumeSuffix, foam_Log, false,iCell, m_bVolPlacementCheck);
		    absScinti_placement = scint_placement + foam_placement;
		  }
		  else if(iZ==1)
		    {
		      pV = new G4PVPlacement(NULL, scint_placement, xtal2_Log, name + m_PhysicalVolumeSuffix, foam2_Log, false,iCell, m_bVolPlacementCheck);
		      absScinti_placement = scint_placement + foam2_placement;
		    }
		  
		  outfilePos << iCell << " "<< 0 << " " << 0 << " " << -1 << " " << absScinti_placement.getX() << " " << absScinti_placement.getY()  << " " << absScinti_placement.getZ()  << " " << 2.0*m_xtalHalfSizeS.x() << " " << 2.0*m_xtalHalfSizeS.y()<< " " << 2.0*m_xtalHalfSizeS.z() << G4endl;
		  centrePos=absScinti_placement;


	      // Make the Crystals sensitive and add them into the name table for tracking	 			
	      m_pCISensitiveScintiDetector->GetCIModuleTable()->InsertModule(iCell, iZ, centrePos, CIModuleTable::SUBDET_SCATTER, pV);
	      iCell++;
	      

	      //************************************************************************/
	      // Place the SIPM -Equivalent
	      //************************************************************************/
	      					
	      scint_placement += G4ThreeVector(0, 0, +m_xtalHalfSizeS.z()+glassHalfSize.z());
	      
	      if (iZ==0){
		glass_Phys = new G4PVPlacement(NULL, scint_placement, glass_Log, "siPM glass" + m_PhysicalVolumeSuffix, foam_Log, false,false, m_bVolPlacementCheck);
		G4cout << " glass is placed at " <<scint_placement << endl;
	      }
	          else if (iZ==1){glass_Phys = new G4PVPlacement(NULL, scint_placement, glass2_Log, "siPM2 glass" + m_PhysicalVolumeSuffix, foam2_Log, false,false, m_bVolPlacementCheck);
	      	G4cout << " glass is placed at " <<scint_placement << endl;}

	 
	      scint_placement += G4ThreeVector(0, 0, + glassHalfSize.z() + goldHalfSize.z());
	      if (iZ==0){gold_Phys = new G4PVPlacement(NULL, scint_placement, gold_Log, "siPM gold" + m_PhysicalVolumeSuffix, foam_Log, false,false, m_bVolPlacementCheck);}
	           else if (iZ==1){gold_Phys = new G4PVPlacement(NULL, scint_placement, gold2_Log, "siPM2 gold" + m_PhysicalVolumeSuffix, foam2_Log, false,false, m_bVolPlacementCheck);}
	      
	      //************************************************************************/
	      // Place the Carbon Fiber- 2 boards for scatter layer one in front and one in back
	      //************************************************************************/
	      
	      if (group==4 && placeCarbon <2)
		{
		  G4ThreeVector carbonfibreBack_placement =G4ThreeVector(0,-4.45*cm, + 13.0*mm + carbonfibreHalfSize.z()+ iZ*offset.z());
		  G4ThreeVector carbonfibreFront_placement = G4ThreeVector(0,-4.45*cm, - 13.0*mm - carbonfibreHalfSize.z()+ iZ*offset.z());

		  carbonfibre_Phys = new G4PVPlacement(NULL, carbonfibreFront_placement, carbonfibre_Log, "carbonfibre" + m_PhysicalVolumeSuffix, m_WorldLog, false,false, m_bVolPlacementCheck);	
		  carbonfibre_Phys = new G4PVPlacement(NULL, carbonfibreBack_placement, carbonfibre_Log, "carbonfibre" + m_PhysicalVolumeSuffix, m_WorldLog, false,false, m_bVolPlacementCheck);

		  placeCarbon++;

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
//This function is unused
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
void FullDetectorConstruction::ConstructAbsorber(G4int& iCell) {

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


	//************************************************************************/
	//************************************************************************/
	// Build an Air Box
	//************************************************************************/
	//************************************************************************/

	const G4String airBox_Name = "Scint_ACELL_AIRBOX";
	G4ThreeVector airBoxHalfSize((2.7/2.0)*cm, (2.7/2.0)*cm, (0.5/2.0)*cm);

	G4Box* airBox_solid = new G4Box(airBox_Name + m_SolidSuffix, airBoxHalfSize.x(),airBoxHalfSize.y(),airBoxHalfSize.z());
	G4LogicalVolume* airBox_Log = new G4LogicalVolume(airBox_solid,  materials.GetMaterial("G4_AIR"), airBox_Name
							 + m_LogicalVolumeSuffix, NULL, NULL);
	assert (airBox_Log != NULL);



	//************************************************************************/
	//************************************************************************/
	// Build the ALUMINUM BOXES
	//************************************************************************/
	//************************************************************************/
        //box size = 1.35 1.35 0.0002   # made slightly smaller. Pat seems to have  1.5mm on the sides 1 mm in the front (and back) in my case
	const G4String AlBox_Name = "Scint_ACELL_AlBox";	
	const G4String AlBox1_Name = "Scint_ACELL_OutsideAlBox";
	const G4String AlBox2_Name = "Scint_ACELL_InsideAlBox";

	G4ThreeVector AlBoxOuterHalfSize(16.*mm, 16.*mm, 28.*mm);
	G4ThreeVector AlBoxInnerHalfSize(AlBoxOuterHalfSize.x()-1.5*mm, AlBoxOuterHalfSize.y()-1.5*mm, AlBoxOuterHalfSize.z()-1*mm);

	G4Box* AlBoxInner_solid = new G4Box(AlBox1_Name + "1" + m_SolidSuffix, AlBoxInnerHalfSize.x(), AlBoxInnerHalfSize.y(), AlBoxInnerHalfSize.z());
	G4Box* AlBoxOuter_solid = new G4Box(AlBox1_Name + "2" + m_SolidSuffix, AlBoxOuterHalfSize.x(), AlBoxOuterHalfSize.y(), AlBoxOuterHalfSize.z());
	
	G4SubtractionSolid* AlBox1_solid = new G4SubtractionSolid(AlBox1_Name + m_SolidSuffix, AlBoxOuter_solid, AlBoxInner_solid);

	G4ThreeVector AlBoxOuterHalfSize2(AlBoxInnerHalfSize.x(), AlBoxInnerHalfSize.y(), airBoxHalfSize.z());
	G4ThreeVector AlBoxInnerHalfSize2(AlBoxInnerHalfSize.x()-1.0*mm, AlBoxInnerHalfSize.y()-1.0*mm, airBoxHalfSize.z());

	G4Box* AlBoxInner2_solid = new G4Box(AlBox2_Name + "1" + m_SolidSuffix, AlBoxInnerHalfSize2.x(), AlBoxInnerHalfSize2.y(), AlBoxInnerHalfSize2.z());
	G4Box* AlBoxOuter2_solid = new G4Box(AlBox2_Name + "2" + m_SolidSuffix, AlBoxOuterHalfSize2.x(), AlBoxOuterHalfSize2.y(), AlBoxOuterHalfSize2.z());
	
	G4SubtractionSolid* AlBox2_solid = new G4SubtractionSolid(AlBox2_Name + m_SolidSuffix, AlBoxOuter2_solid, AlBoxInner2_solid);

	G4ThreeVector translation(0,0,-2.45*cm);
	G4UnionSolid* MyUnion =    new G4UnionSolid("MyUnionBox", AlBox1_solid,AlBox2_solid,NULL,translation);
	//G4UnionSolid  MyUnion("MyUnionbox",AlBox1_solid,AlBox2_solid,NULL,NULL);
	G4LogicalVolume* AlBox_Log = new G4LogicalVolume(MyUnion, materials.GetMaterial("G4_ALUMINIUM"),AlBox_Name + m_LogicalVolumeSuffix,NULL,NULL);

	assert (AlBox_Log != NULL);

	//************************************************************************/
	//************************************************************************/
	// Build the Glass (SiPM equivalent)
	//************************************************************************/
	//************************************************************************/

	const G4String glass_Name = "Scint_ACELL_GLASS";

	G4ThreeVector glassHalfSize(m_xtalHalfSizeA.x(), m_xtalHalfSizeA.y(),3.*mm);
	G4Box* glass_solid = new G4Box(glass_Name + m_SolidSuffix, glassHalfSize.x(), glassHalfSize.y(), glassHalfSize.z());
		G4LogicalVolume* glass_Log = new G4LogicalVolume(glass_solid,  materials.GetMaterial("G4_GLASS_PLATE"), glass_Name
							 + m_LogicalVolumeSuffix, NULL, NULL);

	assert (glass_Log != NULL);

	//************************************************************************/
	//************************************************************************/
	// Build the Teflon
	//************************************************************************/
	//************************************************************************/

	//  box size = 2.9 2.9 4.899999  # made slightly smaller
	//  :start transformation:
	//   translation = 0, 0, 0.25  
	//  :stop transformation:
	//  name = abs_Teflon
	//  :start media input:
	//      media = Teflon521ICRU
	//It looks like there is 1.5 of Teflon 
	//  # at the front so put this at the rear as well to make it symmetric (on 
	//  # the side there is 2 mm of Tefln). Since there is 1mm Al at the front, put
	//  # that at the back as well. That
	//insert a new material fo rhits
	const G4String teflon_Name = "Scint_ACELL_TEFLON";

	G4ThreeVector TeflonOuterHalfSize(AlBoxInnerHalfSize.x(),AlBoxInnerHalfSize.y(),m_xtalHalfSizeA.z() +glassHalfSize.z() +1.5*mm);
	G4ThreeVector TeflonInnerHalfSize(AlBoxInnerHalfSize.x()-2*mm, AlBoxInnerHalfSize.y()-2*mm, m_xtalHalfSizeA.z() +glassHalfSize.z());

	G4Box* TeflonInner_solid = new G4Box(teflon_Name + "1" + m_SolidSuffix, TeflonInnerHalfSize.x(),TeflonInnerHalfSize.y(),TeflonInnerHalfSize.z());
	G4Box* TeflonOuter_solid = new G4Box(teflon_Name + "2" + m_SolidSuffix, TeflonOuterHalfSize.x(),TeflonOuterHalfSize.y(),TeflonOuterHalfSize.z());

	G4SubtractionSolid* Teflon_solid = new G4SubtractionSolid(teflon_Name + "solid", TeflonOuter_solid , TeflonInner_solid);
	G4LogicalVolume* Teflon_Log = new G4LogicalVolume(Teflon_solid,  materials.GetMaterial("G4_TEFLON"), teflon_Name
								 + m_LogicalVolumeSuffix, NULL, NULL);

	assert (Teflon_Log != NULL);

       
	//Visualization attributes for the Xtal and Cell
	G4bool bEnableXtalVisualization = true;

	G4VisAttributes* visAttXtal = new G4VisAttributes(G4Colour(0.9, 0.50, 0.2));
	G4VisAttributes* visAttAlCase = new G4VisAttributes(G4Colour(0.1, 0.50, 0.5));

	visAttXtal->SetVisibility(bEnableXtalVisualization);
	visAttAlCase->SetVisibility(bEnableXtalVisualization);

	xtal_Log->SetVisAttributes(visAttXtal);
	AlBox_Log->SetVisAttributes(visAttAlCase);

	G4ThreeVector offset;
	G4VPhysicalVolume* pV;
	G4VPhysicalVolume* AlBox_Phys;
	G4VPhysicalVolume* glass_Phys;
	G4VPhysicalVolume* Teflon_Phys;
	G4VPhysicalVolume* airBox_Phys;	

	G4ThreeVector centrePos;

	for (int iX = 0; iX < m_iNACellX; iX++) {
	  for (int iY = 0; iY < m_iNACellY; iY++) {
	    for (int iZ = 0; iZ < m_iNACellZ; iZ++) {
		      
	      asprintf(&name, "%s%s%02d.%02d.%02d", aCellName.data(),"XTAL", iX, iY, iZ);
	      G4cout <<  "absorber name is " << name << G4endl;

	      // We only have the one dimension  
	      // but we include all dimensions for completenss.

	      offset.set(m_xtalHalfSizeA.x(), m_xtalHalfSizeA.y(),m_xtalHalfSizeA.z());

	      offset = 2* offset + m_dACellGap;	     

	      G4ThreeVector scint_placement((-m_iNACellX + 1 + 2* iX ) * offset.x() / 2., (-m_iNACellY + 1 + 2* iY )
					    * offset.y() / 2., (-m_iNACellZ + 1 + 2* iZ )* offset.z());
	      scint_placement += G4ThreeVector(0, 0, m_dASGap);
	      
	      // Place the Aluminum Box 

	      G4ThreeVector AlBox_placement =scint_placement;
	      //push AlBox baclwards so that scintillator is at 0
	      AlBox_placement+= G4ThreeVector(0, 0, +0.05*cm);
	      AlBox_Phys = new G4PVPlacement(NULL, AlBox_placement, AlBox_Log, "AlBox Window_A" + m_PhysicalVolumeSuffix, m_WorldLog, false,false, m_bVolPlacementCheck);
	      G4cout << " AlBox is placed at " << AlBox_placement << endl;

	      // Place the airBox

	      G4ThreeVector airBox_placement =G4ThreeVector(0,0,-2.45*cm);
	      airBox_placement+=AlBox_placement;
	      airBox_Phys = new G4PVPlacement(NULL, airBox_placement, airBox_Log, "AirBox" + m_PhysicalVolumeSuffix, m_WorldLog, false,false, m_bVolPlacementCheck);
	      G4cout << " airBox is placed at " << airBox_placement << endl;

	      

	      // Place the Teflon	     		
	      G4ThreeVector Teflon_placement =G4ThreeVector(0,0,0.25*cm);
	      Teflon_placement+=AlBox_placement;
	      Teflon_Phys = new G4PVPlacement(NULL, Teflon_placement, Teflon_Log, "Teflon" + m_PhysicalVolumeSuffix,m_WorldLog , false,false, m_bVolPlacementCheck);

	      G4cout << " Teflon is placed at " << Teflon_placement << endl;
	      
	      // Place the Scintillator 
	      G4cout << "Absorber " << iY << " " << scint_placement.y() << G4endl;
	      G4ThreeVector nai_placement = G4ThreeVector(0,0,-.05*cm);
	      nai_placement+=AlBox_placement;	      
	      pV = new G4PVPlacement(NULL,nai_placement, xtal_Log, name + m_PhysicalVolumeSuffix,m_WorldLog , false,iCell, m_bVolPlacementCheck);
	      centrePos= nai_placement;
	      
	      // Make the Crystals sensitive and place them into the Module Table 
	       m_pCISensitiveScintiDetector->GetCIModuleTable()->InsertModule(iCell, iZ, centrePos, CIModuleTable::SUBDET_ABSORBER, pV);
	      
	       //output the crystal positions to a flie
	       outfilePos << iCell << " "<< 0 << " " << 0 << " " << -1 << " " << nai_placement.getX() << " " <<  nai_placement.getY()  << " " <<  nai_placement.getZ()  << " " << 2.0*m_xtalHalfSizeA.x() << " " << 2.0*m_xtalHalfSizeA.y()<< " " << 2.0*m_xtalHalfSizeA.z() << G4endl;
	       
	       
	      // Place the Glass Window		
	      G4ThreeVector Glass_placement = G4ThreeVector(0,0,2.25*cm);
	      Glass_placement+=AlBox_placement;
	      glass_Phys = new G4PVPlacement(NULL,Glass_placement , glass_Log, "Glass" + m_PhysicalVolumeSuffix,m_WorldLog , false,iCell, m_bVolPlacementCheck);
	      G4cout << " glass is placed at " << Glass_placement << G4endl; 
	      iCell++;
	      	      
	    }
	  }
	}


  G4cout << "#############   Constructed Absorber Detector  #########################"
  << G4endl;
	G4cout<<"Absorber Crystal Material:: "<<m_strAbsorberDetectorMaterialName<<G4endl;
	G4cout<<G4endl;


}
