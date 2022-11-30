// Run Action

#ifndef MLFBeamRunAction_h
#define MLFBeamRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;

class MLFBeamRunAction : public G4UserRunAction {
public:
	MLFBeamRunAction();
	virtual ~MLFBeamRunAction();

	// Functions which determine what happens when a run begins/ends
	virtual void BeginOfRunAction(const G4Run*);
	virtual void EndOfRunAction(const G4Run*);
};

#endif

