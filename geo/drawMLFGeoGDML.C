// Simple macro which draws the MLF beamline geometry from the GDML file
// produced each time the simulation is run

{
	gSystem->Load("libGeom");
  std::cout<<" Wah "<<std::endl;
	TGeoManager::Import("/users/wonsang1995/work/mlf-beam-sim_Add_Time/geo/mlf-beam-geometry.gdml");
	TGeoVolume* topVolume = gGeoManager->GetTopVolume();	

	for (int i = 0; i < topVolume->GetNdaughters(); ++i) {
		TGeoVolume* volume = topVolume->GetNode(i)->GetVolume();
		volume->SetTransparency(0);

		std::string matName = volume->GetMaterial()->GetName();

		// Color code the volumes by material
		if (matName == "liquidMercury") {
			volume->SetLineColor(1);
		}
		else if (matName == "iron") {
			volume->SetLineColor(2);
		}
		else if (matName == "liquidHydrogen") {
			volume->SetLineColor(4);
		}
		else if (matName == "beryllium") {
			volume->SetLineColor(8);
		}
	}

	topVolume->Draw();
}
