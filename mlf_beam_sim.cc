// Main MLF Beam Simulation Program

// ROOT Includes
#include "TRandom3.h"

// Geant4 Manager/Control Classes
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4GDMLParser.hh"
#include "G4TransportationManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "MLFBeamAnalysis.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4VisManager.hh"

// User Initialization Classes
#include "MLFBeamGeometry.hh"
#include "MLFBeamActionInit.hh"

// Physics Lists
#include "QGSP_INCLXX.hh"
#include "FTFP_INCLXX.hh"
#include "QGSP_BERT.hh"
#include "QGSP_BIC.hh"
#include "FTFP_BERT.hh"

// Miscellaneous
#include "Randomize.hh"
#include "time.h"
#include <unistd.h>

int main(int argc, char* argv[])
{
    // Set the random number generator + seed
	// Geant4  does not appear to offer a simple way to set the seed
	// based on the process ID or anything else so we use ROOT for this
    G4Random::setTheEngine(new CLHEP::RanecuEngine);
	TRandom3 randGen(0);
	long seeds[2] = {randGen.Integer(INT_MAX), randGen.Integer(INT_MAX)};
	G4Random::setTheSeeds(seeds, 0);
	G4cout << "Random seeds set to: " << G4Random::getTheSeeds()[0] << " and " << G4Random::getTheSeeds()[1] << "\n";

    // Construct the default run manager
    G4RunManager* runManager = new G4RunManager;

    // Set mandatory initialization classes
    // Detector construction
    G4cout << "Constructing the geometry..." << G4endl;
    runManager->SetUserInitialization(new MLFBeamGeometry());
    G4cout << "Geometry Constructed!" << G4endl;

    // Physics list
    G4cout << "Loading the physics list..." << G4endl;
    QGSP_BERT* physicsList = new QGSP_BERT();
    //QGSP_INCLXX* physicsList = new QGSP_INCLXX();
    //FTFP_INCLXX* physicsList = new FTFP_INCLXX();
    //QGSP_BIC* physicsList = new QGSP_BIC();
	//FTFP_BERT* physicsList = new FTFP_BERT();
    runManager->SetUserInitialization(physicsList);
    G4cout << "Physics Loaded!" << G4endl;
    
    // User action initialization
    G4cout << "Setting the Action Initialization..." << G4endl;
    runManager->SetUserInitialization(new MLFBeamActionInit());
    G4cout << "Action Initialziation Complete!" << G4endl;

    // Initialize the run
    G4cout << "Initializing the run..." << G4endl;
    runManager->Initialize();
    G4cout << "Run Initialized!" << G4endl;

	// Print out some info about the geometry
	G4PhysicalVolumeStore* store = G4PhysicalVolumeStore::GetInstance();
    std::vector<G4VPhysicalVolume*>::iterator iter;
    for (iter = store->begin(); iter != store->end(); ++iter) {
		MLFBeamGeometry* geo = (MLFBeamGeometry*)G4RunManager::GetRunManager()->GetUserDetectorConstruction();
        G4cout << "Name: " << (*iter)->GetName() 
			   << ", Material: " << (*iter)->GetLogicalVolume()->GetMaterial()->GetName() 
			   << ", ID: " << geo->GetVolumeID((*iter)->GetName()) << G4endl;
    }
		
    G4cout << "Writing the geometry to a .gdml file." << G4endl;
    G4VPhysicalVolume* pWorld = G4TransportationManager::GetTransportationManager()->GetNavigatorForTracking()->GetWorldVolume();
    
	// Check if the gdml file already exists; if it does, delete it because
	// the Geant4 GDML parser cannot overwrite existing GDML files
	std::ifstream f("geo/mlf_beam_geometry.gdml");
	if (f.good()) remove("geo/mlf_beam_geometry.gdml");

	G4GDMLParser parser;
    //parser.Write("geo/mlf_beam_geometry.gdml", pWorld); //wshwang revise 1124

	// Do visualization
	G4VisManager* visManager = new G4VisExecutive;
	visManager->Initialize();

    // Get the pointer to the User Interface manager
	G4UImanager* UImanager = G4UImanager::GetUIpointer();

	G4cout << "argc = " << argc << G4endl;

	// Interactive session
	if (argc == 1) {
#ifdef G4UI_USE
		G4UIExecutive* ui = new G4UIExecutive(argc, argv);
		UImanager->ApplyCommand("/control/execute init.mac");
		ui->SessionStart();
		delete ui;
#endif
	}

    // Batch mode; process command line arguments + marco
	else {
		// Check for command line arguments (other than the macro)
		int argsLeft = argc - 1;
		G4cout << argsLeft << G4endl;
		while (argsLeft > 1) {
			G4String argFlag = argv[argc-argsLeft];
			if (argFlag == "-o") {
				G4String anaFilename = argv[argc-argsLeft+1];
				G4AnalysisManager::Instance()->SetFileName(anaFilename);
				argsLeft -= 2;
			}
			G4cout << argsLeft << G4endl;
		}
		// Last argument should be the macro
		G4String command = "/control/execute ";
		G4String macName = argv[argc-1];
		UImanager->ApplyCommand(command+macName);
	}
 
    delete runManager;
	delete visManager;

    return 0;
}

