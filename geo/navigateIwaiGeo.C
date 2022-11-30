// Simple macro which navigates through the MLF geometry produced by Iwai-san
// and prints the properties of the volumes in that geometry.

{
	gSystem->Load("libGeom");
	TGeoManager::Import("mlf_geo_iwai.root");
	 
	TGeoVolume* topVolume = gGeoManager->GetTopVolume();

	for (int i = 0; i < topVolume->GetNdaughters(); ++i) {
		TGeoNode* node = topVolume->GetNode(i);
		TGeoVolume* volume = node->GetVolume();
		TGeoShape* shape = volume->GetShape();

		std::cout << "\n\n\n=================================================" << std::endl;
		std::cout << "Name: " << node->GetName() << std::endl;
		std::cout << "Material: " << volume->GetMaterial()->GetName() << std::endl;;
		volume->Print();
		node->GetMatrix()->Print();
	}
}
