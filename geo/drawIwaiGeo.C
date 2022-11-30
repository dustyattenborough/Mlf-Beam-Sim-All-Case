// Simple macro which loads and draws the geometry produced by Iwai-san

{
	gSystem->Load("libGeom");
	TGeoManager::Import("mlf_geo_iwai.root");
	 
	TGeoVolume* topVolume = gGeoManager->GetTopVolume();

    for (int i = 0; i < topVolume->GetNdaughters(); ++i) {
        TGeoVolume* volume = topVolume->GetNode(i)->GetVolume();
        volume->SetTransparency(0);

        std::string matName = volume->GetMaterial()->GetName();
		std::cout << matName << std::endl;

        // Color code the volumes by material
        if (matName == "G4_Hg") {
            volume->SetLineColor(1);
        }
        else if (matName == "G4_Fe") {
            volume->SetLineColor(2);
        }
        else if (matName == "G4_lH2") {
            volume->SetLineColor(4);
        }
        else if (matName == "G4_Be") {
            volume->SetLineColor(8);
        }
    }
	
	gGeoManager->GetTopVolume()->Draw();

}
