// Event Action

#ifndef MLFBeamEventAction_h
#define MLFBeamEventAction_h 1

#include <map>

#include "G4UserEventAction.hh"
#include "G4Track.hh"
#include "globals.hh"

class MLFBeamRunAction;

class MLFBeamEventAction : public G4UserEventAction {
public:
	MLFBeamEventAction(MLFBeamRunAction* runAction);
	virtual ~MLFBeamEventAction();

	// Functions defining what to do at the beginning/end of an event
	virtual void BeginOfEventAction(const G4Event* event);
	virtual void EndOfEventAction(const G4Event* event);

	void FillMaps(const G4Track* aTrack);
	void IncrementNumNeutrino(int trackID) { numNeutrinoMap[trackID]++; }
	void ClearMaps();

private:
	MLFBeamRunAction* fRunAction;

	// Neutrino Parent Variable Maps
	// These go from the parent track IDs to the parent properties
	std::map<int, int> PDGCodeMap;
	std::map<int, double> kinEMap;
	std::map<int, G4ThreeVector> momMap;
	std::map<int, G4ThreeVector> posMap;
	std::map<int, int> volumeIDMap;
	std::map<int, int> numNeutrinoMap;
  std::map<int, double> timeMap;
};

#endif

    
