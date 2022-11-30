// Run Action

#include "MLFBeamRunAction.hh"
#include "MLFBeamPrimaryGenAction.hh"
#include "MLFBeamAnalysis.hh"

//#include "G4RunManager.hh"
#include "G4Run.hh"
//#include "G4LogicalVolumeStore.hh"
//#include "G4LogicalVolume.hh"
//#include "G4UnitsTable.hh"
//#include "G4SystemOfUnits.hh"

MLFBeamRunAction::MLFBeamRunAction(): G4UserRunAction() {   
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	G4cout << "Using " << analysisManager->GetType() << G4endl;

	// This n-tuple will keep track of the neutrino parent properties
	// Parent properties are saved when a neutrino parent decays
	analysisManager->CreateNtuple("parentTree", "Neutrino Parent Variables");
	analysisManager->CreateNtupleIColumn(0, "PDGCode");
	analysisManager->CreateNtupleDColumn(0, "kinE");
	analysisManager->CreateNtupleDColumn(0, "xMom");
	analysisManager->CreateNtupleDColumn(0, "yMom");
	analysisManager->CreateNtupleDColumn(0, "zMom");
	analysisManager->CreateNtupleDColumn(0, "xPos");
	analysisManager->CreateNtupleDColumn(0, "yPos");
	analysisManager->CreateNtupleDColumn(0, "zPos");
	analysisManager->CreateNtupleIColumn(0, "volumeID");
	analysisManager->CreateNtupleIColumn(0, "numNeutrinos");
  analysisManager->CreateNtupleIColumn(0, "pre_time");
	analysisManager->FinishNtuple();

	// Plot of the beam profile on the target surface (units are cm)
	analysisManager->CreateH2("beamProfile2D", "beamProfile2D", 50, -15.0, 15.0, 50, -15.0, 15.0);
}

MLFBeamRunAction::~MLFBeamRunAction() {
	delete G4AnalysisManager::Instance();
}

void MLFBeamRunAction::BeginOfRunAction(const G4Run*) { 
	// Create the output file; filename should be set in the macro
	// using the /analysis/setFileName "filename" command or passed to
	// the program via the -o option 
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	analysisManager->OpenFile();
}

void MLFBeamRunAction::EndOfRunAction(const G4Run* run) {
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  G4int nEvents = run->GetNumberOfEvent();
  if (nEvents == 0) return;

  // Write the output file with the analysis data
  analysisManager->Write();
  analysisManager->CloseFile();
}
