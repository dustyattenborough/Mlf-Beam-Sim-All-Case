// Primary Generator Action

// Creates the 3 GeV proton beam incident on the mercury target

#include "MLFBeamPrimaryGenAction.hh"

#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

MLFBeamPrimaryGenAction::MLFBeamPrimaryGenAction() : G4VUserPrimaryGeneratorAction(),
	fParticleGun(0) 
{
	G4int n_particle = 1;
	fParticleGun  = new G4ParticleGun(n_particle);

	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	G4String particleName;
	G4ParticleDefinition* particle = particleTable->FindParticle(particleName="proton");
	fParticleGun->SetParticleDefinition(particle);
  
	fParticleGun->SetParticleEnergy(3.0*GeV);
}


MLFBeamPrimaryGenAction::~MLFBeamPrimaryGenAction() {
	delete fParticleGun;
}

void MLFBeamPrimaryGenAction::GeneratePrimaries(G4Event* anEvent) {
	// Roughly implement the primary proton spread over the mercury target surface
	G4double x = G4RandGauss::shoot(0.0, 3.7);
	G4double y = G4RandGauss::shoot(0.0, 1.7);
	//G4double z = G4RandGauss::shoot(-2500, 2500);

	//G4double xx = G4RandGauss::shoot(0.0, 3.7);
	//G4double yy = G4RandGauss::shoot(0.0, 1.7);
	//G4double zz = G4RandGauss::shoot(-1000, 20);

	// Start the particles 1 cm away from the front face of the target (z = 0.0 cm)
	fParticleGun->SetParticlePosition(G4ThreeVector(x*cm, y*cm, -1.0*cm));
	//fParticleGun->SetParticlePosition(G4ThreeVector(x*cm, y*cm, z*cm));
	//fParticleGun->SetParticlePosition(G4ThreeVector(xx*cm, yy*cm, zz*cm));

  //Time > test -ing
  G4double beam_time = G4RandFlat::shoot(0.0,100.0) + 540*(G4double)(G4int)G4RandFlat::shoot(0.0,2.0);
	fParticleGun->SetParticleTime(beam_time*ns);

	// Assume all protons hit the target at normal incidence
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.0, 0.0, 1.0));

	fParticleGun->GeneratePrimaryVertex(anEvent);
}
