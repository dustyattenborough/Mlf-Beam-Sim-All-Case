// MLF Beamline/Target Geometry

#ifndef MLFBeamGeometry_h
#define MLFBeamGeometry_h 1

#include <map>

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

// Mapping from physical volume names to ID numbers

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4GenericMessenger;

class MLFBeamGeometry : public G4VUserDetectorConstruction {
public:
    MLFBeamGeometry();
    virtual ~MLFBeamGeometry();

    virtual G4VPhysicalVolume* Construct();
    
	// Methods for volume ID mapping from name to unique ID number for output tree
	void SetVolumeMap(std::map<G4String, int> map) { volumeMap = map; }
	int GetVolumeID(G4String name) const { return volumeMap.at(name); }

private:
    G4GenericMessenger* fMessenger;
	
	// Mapping between physical volume names and a unique ID number
	std::map<G4String, int> volumeMap;
};

#endif

