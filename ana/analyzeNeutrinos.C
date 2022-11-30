// Example neutrino property analysis macro
// Change the filename to match your file
{
	//std::string filename = "../testDecay.root";	
	std::string filename = "myNeutrinoFile2.root";	
	// Get the tree with the neutrino properties
	// They are stored in vectors since there can be multiple neutrinos
	// for each parent, especially when we decay them many times
	TChain* neutrinoTree = new TChain("neutrinoTree");
	neutrinoTree->Add(filename.c_str());

	int numNu;
	std::vector<int>* nuPDGCode = 0;
	std::vector<double>* nuEnergy = 0;
    std::vector<double>* xDirNu = 0;
    std::vector<double>* yDirNu = 0;
    std::vector<double>* zDirNu = 0;
    std::vector<double>* xPosNu = 0;
    std::vector<double>* yPosNu = 0;
    std::vector<double>* zPosNu = 0;
    std::vector<double>* weightPL = 0;
	TBranch* bnuPDGCode = 0;
	TBranch* bnuEnergy = 0;
	TBranch* bxDirNu = 0;
	TBranch* byDirNu = 0;
	TBranch* bzDirNu = 0;
	TBranch* bxPosNu = 0;
	TBranch* byPosNu = 0;
	TBranch* bzPosNu = 0;
	TBranch* bweightPL = 0;
    neutrinoTree->SetBranchAddress("numNu", &numNu);
    neutrinoTree->SetBranchAddress("PDGCode", &nuPDGCode, &bnuPDGCode);
    neutrinoTree->SetBranchAddress("energy", &nuEnergy, &bnuEnergy);
    neutrinoTree->SetBranchAddress("xDir", &xDirNu, &bxDirNu);
    neutrinoTree->SetBranchAddress("yDir", &yDirNu, &byDirNu);
    neutrinoTree->SetBranchAddress("zDir", &zDirNu, &bzDirNu);
    neutrinoTree->SetBranchAddress("xPos", &xPosNu, &bxPosNu);
    neutrinoTree->SetBranchAddress("yPos", &yPosNu, &byPosNu);
    neutrinoTree->SetBranchAddress("zPos", &zPosNu, &bzPosNu);
    neutrinoTree->SetBranchAddress("weightPL", &weightPL, &bweightPL);	

	int numEntries = neutrinoTree->GetEntries();
	std::cout << "Number of parents: " << numEntries << "\n";

	TFile* inFile = new TFile(filename.c_str());
	TParameter<int>* numDecaysParam = (TParameter<int>*)inFile->Get("NUM_DECAYS");
	std::cout << "Each parent was decayed: " << numDecaysParam->GetVal() << " times.\n";

	TFile* outputFile = new TFile("neutrinoPlots2.root", "RECREATE");
	TH1D* nuMuFluxHist = new TH1D("nuMuFluxHist", ";E_{#nu} (MeV);", 200, 0.0, 400.0);

	for (int iParent = 0; iParent < numEntries; iParent++) {
		if (iParent % 100 == 0) std::cout << iParent << std::endl;
		neutrinoTree->GetEntry(iParent);

		// Loop over the neutrinos from this parent and look for muon neutrinos
		for (int iNu = 0; iNu < numNu; ++iNu) {
			if (nuPDGCode->at(iNu) == 14) {
				nuMuFluxHist->Fill(nuEnergy->at(iNu));
			}
		}
	}

	std::cout << "Writing Histograms." << std::endl;
	outputFile->cd();
	nuMuFluxHist->Write();
	outputFile->Close();

	std::cout << "Finished." << std::endl;
}
