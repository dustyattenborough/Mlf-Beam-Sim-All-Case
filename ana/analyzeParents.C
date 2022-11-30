// Example parent property analysis macro
// Update the filename to your filename

{
	//std::string filename = "../test.root";
	std::string filename = "myOutputFile.root";

	TChain* parentTree = new TChain("parentTree");
	parentTree->Add(filename.c_str());

	int parentPDGCode, volumeID;
    double xMom, yMom, zMom, kinE, xPos, yPos, zPos;
    parentTree->SetBranchAddress("PDGCode", &parentPDGCode);
    parentTree->SetBranchAddress("xMom", &xMom);
    parentTree->SetBranchAddress("yMom", &yMom);
    parentTree->SetBranchAddress("zMom", &zMom);
    parentTree->SetBranchAddress("kinE", &kinE);
    parentTree->SetBranchAddress("xPos", &xPos);
    parentTree->SetBranchAddress("yPos", &yPos);
    parentTree->SetBranchAddress("zPos", &zPos);
    parentTree->SetBranchAddress("volumeID", &volumeID);

    int numEntries = parentTree->GetEntries();
	std::cout << "Number of parents: " << numEntries << std::endl;

	TFile* outputFile = new TFile("parentPlots.root", "RECREATE");
	
	TH1D* zPosParentHist = new TH1D("zPosParentHist", ";z Position (mm)", 200, -100.0, 900.0);
	TH1D* kinEParentHist = new TH1D("kinEParentHist", ";Energy (MeV);", 200, 0.0, 1000.0);

	for (int iParent = 0; iParent < numEntries; iParent++) {
		if (iParent % 100 == 0) std::cout << iParent << std::endl;
		parentTree->GetEntry(iParent);
		zPosParentHist->Fill(zPos);
		kinEParentHist->Fill(kinE);
	}

	std::cout << "Writing Histograms." << std::endl;
	outputFile->cd();
	zPosParentHist->Write();
	kinEParentHist->Write();
	outputFile->Close();

	std::cout << "Finished." << std::endl;
}
