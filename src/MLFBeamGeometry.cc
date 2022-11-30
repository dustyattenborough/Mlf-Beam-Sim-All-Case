// MLF Beamline/Target Geometry

#include "MLFBeamGeometry.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Trd.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4LogicalVolume.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericMessenger.hh"

MLFBeamGeometry::MLFBeamGeometry() : G4VUserDetectorConstruction(),
	fMessenger(0) 
{}

MLFBeamGeometry::~MLFBeamGeometry()
{ 
    delete fMessenger;
}

G4VPhysicalVolume* MLFBeamGeometry::Construct()
{  
    // Option to switch on/off checking of volumes overlaps
    G4bool checkOverlaps = true;
  
    // World Box
	G4Box* solidWorld = new G4Box("World", 1000.0*cm, 1000.0*cm, 1000.0*cm);

	// Target Components
    G4Trd* solidTargetFront = new G4Trd("TargetFront", 12.6*cm, 21.45*cm, 3.88*cm, 3.88*cm, 20.65*cm);
	G4Box* solidTargetSide = new G4Box("TargetSide", 6.975*cm, 3.88*cm, 28.025*cm); 
	G4Box* solidTargetCenter = new G4Box("TargetCenter", 7.5*cm, 3.88*cm, 19.525*cm); 
	G4Box* solidTargetStop = new G4Box("TargetStop", 7.5*cm, 3.88*cm, 10.0*cm); 

	// Liquid Hydrogen Moderators
	G4Tubs* solidModeratorBottom = new G4Tubs("ModeratorBottom", 0.0*cm, 10.0*cm, 5.0*cm, 0.0*deg, 360.0*deg);
	G4Box* solidModeratorTop = new G4Box("ModeratorTop", 2.5*cm, 5.0*cm, 7.5*cm);

	// Beryllium Reflectors
	G4Tubs* solidReflectorInner = new G4Tubs("ReflectorInner", 0.0*cm, 25.0*cm, 15.0*cm, 0.0*deg, 360.0*deg);
	G4Tubs* solidReflectorBottom1 = new G4Tubs("ReflectorBottom1", 10.0*cm, 25.0*cm, 5.0*cm, 242.0*deg, 121.5*deg);
	G4Tubs* solidReflectorBottom2 = new G4Tubs("ReflectorBottom2", 10.0*cm, 25.0*cm, 5.0*cm, 54.5*deg, 130.7*deg);
	G4Tubs* solidReflectorTop = new G4Tubs("ReflectorTop", 10.0*cm, 35.0*cm, 5.0*cm, 147.5*deg, 20.0*deg);
   
	// Iron Shielding
	G4Tubs* solidShieldInner = new G4Tubs("ShieldInner", 25.0*cm, 85.0*cm, 15.0*cm, 0.0*deg, 360.0*deg);
	G4Tubs* solidShieldBottomFan1 = new G4Tubs("ShieldBottomFan1", 25.0*cm, 85.0*cm, 5.0*cm, 242.0*deg, 121.5*deg);
	G4Tubs* solidShieldBottomFan2 = new G4Tubs("ShieldBottomFan2", 25.0*cm, 85.0*cm, 5.0*cm, 54.5*deg, 130.7*deg);
	G4Tubs* solidShieldTopFan1 = new G4Tubs("ShieldTopFan1", 25.0*cm, 85.0*cm, 5.0*cm, 182.3*deg, 130.7*deg);
	G4Tubs* solidShieldTopFan2 = new G4Tubs("ShieldTopFan2", 25.0*cm, 85.0*cm, 5.0*cm, 3.8*deg, 125.0*deg);
	G4Tubs* solidShieldOuter = new G4Tubs("ShieldOuter", 85.0*cm, 220.0*cm, 50.0*cm, 0.0*deg, 360.0*deg);
	G4Tubs* solidShieldBottom = new G4Tubs("ShieldBottom", 0.0*cm, 85.0*cm, 25.0*cm, 0.0*deg, 360.0*deg);
	G4Tubs* solidShieldTop = new G4Tubs("ShieldTop", 0.0*cm, 85.0*cm, 75.0*cm, 0.0*deg, 360.0*deg);
 
	// Detector Materials

    G4NistManager* nistManager = G4NistManager::Instance();
	G4Element* H = nistManager->FindOrBuildElement("H");
	G4Element* Be = nistManager->FindOrBuildElement("Be");
	G4Element* C = nistManager->FindOrBuildElement("C");
	G4Element* N = nistManager->FindOrBuildElement("N");
	G4Element* O = nistManager->FindOrBuildElement("O");
	G4Element* Ar = nistManager->FindOrBuildElement("Ar");
	G4Element* Fe = nistManager->FindOrBuildElement("Fe");
	G4Element* Hg = nistManager->FindOrBuildElement("Hg");
    
	G4Material* air = new G4Material("air", 1.20479*kg/m3, 4, kStateGas, 300.0*kelvin, 1.0*atmosphere);
	air->AddElement(C, 0.000124);
	air->AddElement(N, 0.755268);
	air->AddElement(O, 0.231781);
	air->AddElement(Ar, 0.012827);

	G4Material* lMercury = new G4Material("liquidMercury", 13.546*g/cm3, 1);
	lMercury->AddElement(Hg, 1.0);

	G4Material* iron = new G4Material("iron", 7.874*g/cm3, 1);
	iron->AddElement(Fe, 1.0);

	G4Material* lHydrogen = new G4Material("liquidHydrogen", 0.0708*g/cm3, 1);
	lHydrogen->AddElement(H, 1.0);
	
	G4Material* beryllium = new G4Material("beryllium", 1.848*g/cm3, 1);
	beryllium->AddElement(Be, 1.0);

	// Logical Volumes
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, air, "World");
    G4LogicalVolume* logicTargetFront = new G4LogicalVolume(solidTargetFront, lMercury, "TargetFront");
    G4LogicalVolume* logicTargetSide = new G4LogicalVolume(solidTargetSide, lMercury, "TargetSide");
    G4LogicalVolume* logicTargetCenter = new G4LogicalVolume(solidTargetCenter, lMercury, "TargetCenter");
    G4LogicalVolume* logicTargetStop = new G4LogicalVolume(solidTargetStop, iron, "TargetStop");
    G4LogicalVolume* logicModeratorBottom = new G4LogicalVolume(solidModeratorBottom, lHydrogen, "ModeratorBottom");
    G4LogicalVolume* logicModeratorTop = new G4LogicalVolume(solidModeratorTop, lHydrogen, "ModeratorTop");
	G4LogicalVolume* logicReflectorInner = new G4LogicalVolume(solidReflectorInner, beryllium, "ReflectorInner");
	G4LogicalVolume* logicReflectorBottom1 = new G4LogicalVolume(solidReflectorBottom1, beryllium, "ReflectorBottom1");
	G4LogicalVolume* logicReflectorBottom2 = new G4LogicalVolume(solidReflectorBottom2, beryllium, "ReflectorBottom2");
	G4LogicalVolume* logicReflectorTop = new G4LogicalVolume(solidReflectorTop, beryllium, "ReflectorTop");
	G4LogicalVolume* logicShieldInner = new G4LogicalVolume(solidShieldInner, iron, "ShieldInner");
	G4LogicalVolume* logicShieldBottomFan1 = new G4LogicalVolume(solidShieldBottomFan1, iron, "ShieldBottomFan1");
	G4LogicalVolume* logicShieldBottomFan2 = new G4LogicalVolume(solidShieldBottomFan2, iron, "ShieldBottomFan2");
	G4LogicalVolume* logicShieldTopFan1 = new G4LogicalVolume(solidShieldTopFan1, iron, "ShieldTopFan1");
	G4LogicalVolume* logicShieldTopFan2 = new G4LogicalVolume(solidShieldTopFan2, iron, "ShieldTopFan2");
	G4LogicalVolume* logicShieldOuter = new G4LogicalVolume(solidShieldOuter, iron, "ShieldOuter");
	G4LogicalVolume* logicShieldBottom = new G4LogicalVolume(solidShieldBottom, iron, "ShieldBottom");
	G4LogicalVolume* logicShieldTop = new G4LogicalVolume(solidShieldTop, iron, "ShieldTop");

	// Rotation matrices
	G4RotationMatrix* xRot = new G4RotationMatrix;
	xRot->rotateX(-90.0*deg);
	G4RotationMatrix* yRot45 = new G4RotationMatrix;
	yRot45->rotateY(-45.0*deg);  
 
    // Physical volumes                              
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0, checkOverlaps);
    new G4PVPlacement(0, G4ThreeVector(0.0*cm, 0.0*cm, 20.65*cm), logicTargetFront, "TargetFront", logicWorld, false, 0, checkOverlaps);
    new G4PVPlacement(0, G4ThreeVector(14.475*cm, 0.0*cm, 69.325*cm), logicTargetSide, "TargetLeft", logicWorld, false, 0, checkOverlaps);
    new G4PVPlacement(0, G4ThreeVector(-14.475*cm, 0.0*cm, 69.325*cm), logicTargetSide, "TargetRight", logicWorld, false, 0, checkOverlaps);
    new G4PVPlacement(0, G4ThreeVector(0.0*cm, 0.0*cm, 60.825*cm), logicTargetCenter, "TargetCenter", logicWorld, false, 0, checkOverlaps);
    new G4PVPlacement(0, G4ThreeVector(0.0*cm, 0.0*cm, 90.35*cm), logicTargetStop, "TargetStop", logicWorld, false, 0, checkOverlaps);
	new G4PVPlacement(xRot, G4ThreeVector(0.0*cm, -12.5*cm, 16.0*cm), logicModeratorBottom, "ModeratorBottom", logicWorld, false, 0, checkOverlaps);
	new G4PVPlacement(0, G4ThreeVector(0.0*cm, 12.5*cm, 5.425*cm), logicModeratorTop, "ModeratorTopFront", logicWorld, false, 0, checkOverlaps);
	new G4PVPlacement(yRot45, G4ThreeVector(7.5*cm, 12.5*cm, 23.5*cm), logicModeratorTop, "ModeratorTopBack", logicWorld, false, 0, checkOverlaps); 
	new G4PVPlacement(xRot, G4ThreeVector(0.0*cm, -32.5*cm, 16.0*cm), logicReflectorInner, "ReflectorInnerBottom", logicWorld, false, 0, checkOverlaps);
	new G4PVPlacement(xRot, G4ThreeVector(0.0*cm, 32.5*cm, 16.0*cm), logicReflectorInner, "ReflectorInnerTop", logicWorld, false, 0, checkOverlaps);
	new G4PVPlacement(xRot, G4ThreeVector(0.0*cm, -12.5*cm, 16.0*cm), logicReflectorBottom1, "ReflectorBottom1", logicWorld, false, 0, checkOverlaps);
	new G4PVPlacement(xRot, G4ThreeVector(0.0*cm, -12.5*cm, 16.0*cm), logicReflectorBottom2, "ReflectorBottom2", logicWorld, false, 0, checkOverlaps);
	new G4PVPlacement(xRot, G4ThreeVector(10.0*cm, 12.5*cm, 11.88*cm), logicReflectorTop, "ReflectorTop", logicWorld, false, 0, checkOverlaps);
	new G4PVPlacement(xRot, G4ThreeVector(0.0*cm, -32.5*cm, 16.0*cm), logicShieldInner, "ShieldInnerBottom", logicWorld, false, 0, checkOverlaps);
	new G4PVPlacement(xRot, G4ThreeVector(0.0*cm, 32.5*cm, 16.0*cm), logicShieldInner, "ShieldInnerTop", logicWorld, false, 0, checkOverlaps);
	new G4PVPlacement(xRot, G4ThreeVector(0.0*cm, -12.5*cm, 16.0*cm), logicShieldBottomFan1, "ShieldBottomFan1", logicWorld, false, 0, checkOverlaps);
	new G4PVPlacement(xRot, G4ThreeVector(0.0*cm, -12.5*cm, 16.0*cm), logicShieldBottomFan2, "ShieldBottomFan2", logicWorld, false, 0, checkOverlaps);
	new G4PVPlacement(xRot, G4ThreeVector(0.0*cm, 12.5*cm, 16.0*cm), logicShieldTopFan1, "ShieldTopFan1", logicWorld, false, 0, checkOverlaps);
	new G4PVPlacement(xRot, G4ThreeVector(0.0*cm, 12.5*cm, 16.0*cm), logicShieldTopFan2, "ShieldTopFan2", logicWorld, false, 0, checkOverlaps);
	new G4PVPlacement(xRot, G4ThreeVector(0.0*cm, 0.0*cm, 16.0*cm), logicShieldOuter, "ShieldOuter", logicWorld, false, 0, checkOverlaps);
	new G4PVPlacement(xRot, G4ThreeVector(0.0*cm, -75.0*cm, 16.0*cm), logicShieldBottom, "ShieldBottom", logicWorld, false, 0, checkOverlaps);
	new G4PVPlacement(xRot, G4ThreeVector(0.0*cm, 125.0*cm, 16.0*cm), logicShieldTop, "ShieldTop", logicWorld, false, 0, checkOverlaps);
  
	// Give each volume a unique ID number that we can put in the output tree 
	int volumeID = 0;
	G4PhysicalVolumeStore* store = G4PhysicalVolumeStore::GetInstance();
	std::vector<G4VPhysicalVolume*>::iterator iter;
	for (iter = store->begin(); iter != store->end(); ++iter) {
		volumeMap.insert(std::pair<G4String, int>((*iter)->GetName(), volumeID));
		volumeID++;
	}
 
	// Return the physical World
    return physWorld;
}
