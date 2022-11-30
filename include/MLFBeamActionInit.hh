// Action Initialization

#ifndef MLFBeamActionInit_h
#define MLFBeamActionInit_h 1

#include "G4VUserActionInitialization.hh"

class MLFBeamActionInit : public G4VUserActionInitialization {
public:
	MLFBeamActionInit();
    virtual ~MLFBeamActionInit();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

#endif

    
