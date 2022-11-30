// Event Action

#include "MLFBeamEventAction.hh"
#include "MLFBeamRunAction.hh"
#include "MLFBeamAnalysis.hh"
#include "MLFBeamGeometry.hh"
#include "MLFBeamPrimaryGenAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Track.hh"

MLFBeamEventAction::MLFBeamEventAction(MLFBeamRunAction* runAction) : G4UserEventAction(), 
	fRunAction(runAction)
{} 

MLFBeamEventAction::~MLFBeamEventAction() {}

void MLFBeamEventAction::BeginOfEventAction(const G4Event* event) {    
    // Get the primary particle and fill the beam histograms
    G4ThreeVector vertex = event->GetPrimaryVertex()->GetPosition();
    G4PrimaryParticle* primary = event->GetPrimaryVertex()->GetPrimary();

    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	
	// Fill primary vertex position into a histogram
    analysisManager->FillH2(0, vertex.x()/cm, vertex.y()/cm);
}

void MLFBeamEventAction::EndOfEventAction(const G4Event*) {
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	
	// Loop over the parents and fill the n-tuples
	std::map<int, int>::iterator iter;
	for (iter = PDGCodeMap.begin(); iter != PDGCodeMap.end(); ++iter) {
		int trackID = iter->first;
    //if (PDGCodeMap[trackID]==111) std::cout << "PDG is 111: "<<PDGCodeMap[trackID]<<std::endl; // wshwang 
		analysisManager->FillNtupleIColumn(0, 0, PDGCodeMap[trackID]);
		analysisManager->FillNtupleDColumn(0, 1, kinEMap[trackID]);
		analysisManager->FillNtupleDColumn(0, 2, momMap[trackID].x());
		analysisManager->FillNtupleDColumn(0, 3, momMap[trackID].y());
		analysisManager->FillNtupleDColumn(0, 4, momMap[trackID].z());
		analysisManager->FillNtupleDColumn(0, 5, posMap[trackID].x());
		analysisManager->FillNtupleDColumn(0, 6, posMap[trackID].y());
		analysisManager->FillNtupleDColumn(0, 7, posMap[trackID].z());
		analysisManager->FillNtupleIColumn(0, 8, volumeIDMap[trackID]);
		analysisManager->FillNtupleIColumn(0, 9, numNeutrinoMap[trackID]);
		analysisManager->FillNtupleIColumn(0, 10, timeMap[trackID]);
		analysisManager->AddNtupleRow(0);
	}
	// Clear out the neutrino parent variables
	ClearMaps();	
}

void MLFBeamEventAction::FillMaps(const G4Track* aTrack) {
	int trackID = aTrack->GetTrackID();
  timeMap.insert(std::pair<int,double>(trackID,aTrack->GetGlobalTime()));
	PDGCodeMap.insert(std::pair<int, int>(trackID, aTrack->GetDynamicParticle()->GetPDGcode()));
	kinEMap.insert(std::pair<int, double>(trackID, aTrack->GetKineticEnergy()));
	momMap.insert(std::pair<int, G4ThreeVector>(trackID, aTrack->GetMomentum()));
	posMap.insert(std::pair<int, G4ThreeVector>(trackID, aTrack->GetPosition()));
	G4String volume = aTrack->GetVolume()->GetName();
	const MLFBeamGeometry* det = (MLFBeamGeometry*)G4RunManager::GetRunManager()->GetUserDetectorConstruction();
	int volumeID = det->GetVolumeID(volume);
	volumeIDMap.insert(std::pair<int, int>(trackID, volumeID));
	numNeutrinoMap.insert(std::pair<int, int>(trackID, 0));
}

void MLFBeamEventAction::ClearMaps() {
	PDGCodeMap.clear();
	kinEMap.clear();
	momMap.clear();
	posMap.clear();
	volumeIDMap.clear();
	numNeutrinoMap.clear();
  timeMap.clear();
}
