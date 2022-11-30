// Tracking Action

#ifndef MLFBeamTrackingAction_h
#define MLFBeamTrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include "G4Track.hh"
#include "globals.hh"

class MLFBeamRunAction;

class MLFBeamTrackingAction : public G4UserTrackingAction {
public:
	MLFBeamTrackingAction(MLFBeamRunAction* runAction);
	virtual ~MLFBeamTrackingAction();

	// Functions defining what happens when a track starts/ends
	virtual void PreUserTrackingAction(const G4Track* track);
	virtual void PostUserTrackingAction(const G4Track* track);

private:
	MLFBeamRunAction* fRunAction;
};

#endif

    
