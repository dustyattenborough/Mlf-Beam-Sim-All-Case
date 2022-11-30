// Primary Generator (Proton Beam)

#ifndef MLFBeamPrimaryGenAction_h
#define MLFBeamPrimaryGenAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;

class MLFBeamPrimaryGenAction : public G4VUserPrimaryGeneratorAction {
public:
	MLFBeamPrimaryGenAction();    
	virtual ~MLFBeamPrimaryGenAction();

	// Reimplemented method to generate primaries from the base class
	virtual void GeneratePrimaries(G4Event*); 
  
	// Access method for the particle gun
	const G4ParticleGun* GetParticleGun() const { return fParticleGun; }

private:
	G4ParticleGun* fParticleGun; // pointer a to G4 gun clas
  //G4double beam_time; //beam timing
};

#endif
