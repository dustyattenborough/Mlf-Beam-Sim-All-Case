// Event Action

#include "MLFBeamTrackingAction.hh"
#include "MLFBeamRunAction.hh"
#include "MLFBeamEventAction.hh"
#include "MLFBeamAnalysis.hh"

#include "G4Track.hh"
#include "G4RunManager.hh"
#include "G4TrackStatus.hh"
#include "G4SystemOfUnits.hh"
#include "MLFBeamGeometry.hh"

MLFBeamTrackingAction::MLFBeamTrackingAction(MLFBeamRunAction* runAction) : G4UserTrackingAction(),
  fRunAction(runAction)
{} 

MLFBeamTrackingAction::~MLFBeamTrackingAction() {}

void MLFBeamTrackingAction::PreUserTrackingAction(const G4Track* aTrack) {
    G4int PDGCode = aTrack->GetDynamicParticle()->GetPDGcode();
	if (PDGCode == 12 || PDGCode == -12 || PDGCode == 14 || PDGCode == -14) {
		// Increment the number of neutrinos from this parent
		G4int parentID = aTrack->GetParentID();
		MLFBeamEventAction* evAction = (MLFBeamEventAction*)G4RunManager::GetRunManager()->GetUserEventAction();
		evAction->IncrementNumNeutrino(parentID);
	}
}

void MLFBeamTrackingAction::PostUserTrackingAction(const G4Track* aTrack) {   
    G4int PDGCode = aTrack->GetDynamicParticle()->GetPDGcode();
    // Look for neutrino parents (muons, pions, kaons)
    if (PDGCode == 13 || PDGCode == -13 ||
        PDGCode == 211 || PDGCode == -211 ||
        PDGCode == 321 || PDGCode == -321 || PDGCode == 130 || PDGCode == 310) {
       
        // Check if the track has decayed. If so, add it to our n-tuples
        G4String procName = aTrack->GetStep()->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
		    G4bool isDecayProc = procName == "Decay" || procName == "muMinusCaptureAtRest";

        // at least process is "Decay" & and current track is already died
        if (aTrack->GetTrackStatus() == fStopAndKill && isDecayProc) {
			MLFBeamEventAction* evAction = (MLFBeamEventAction*)G4RunManager::GetRunManager()->GetUserEventAction();
			evAction->FillMaps(aTrack);
		  }
    }
    //if (PDGCode == 111){
    //    if (aTrack->GetTrackStatus() == fAlive) {
		//	  MLFBeamEventAction* evAction = (MLFBeamEventAction*)G4RunManager::GetRunManager()->GetUserEventAction();
		//	  evAction->FillMaps(aTrack);
		//    }
    //}

}
