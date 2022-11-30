// Action Intialization

#include "MLFBeamActionInit.hh"
#include "MLFBeamPrimaryGenAction.hh"
#include "MLFBeamRunAction.hh"
#include "MLFBeamEventAction.hh"
#include "MLFBeamTrackingAction.hh"

MLFBeamActionInit::MLFBeamActionInit() : G4VUserActionInitialization() {}

MLFBeamActionInit::~MLFBeamActionInit() {}

void MLFBeamActionInit::BuildForMaster() const {
	MLFBeamRunAction* runAction = new MLFBeamRunAction;
	SetUserAction(runAction);
}

void MLFBeamActionInit::Build() const {
	// Setup the primary generator
	SetUserAction(new MLFBeamPrimaryGenAction);

	// Setup the user actions to be taken at the beginning/end of runs, events, and tracks
	MLFBeamRunAction* runAction = new MLFBeamRunAction;
	SetUserAction(runAction);

	MLFBeamEventAction* eventAction = new MLFBeamEventAction(runAction);
	SetUserAction(eventAction);

	MLFBeamTrackingAction* trackingAction = new MLFBeamTrackingAction(runAction);
	SetUserAction(trackingAction);
}  

