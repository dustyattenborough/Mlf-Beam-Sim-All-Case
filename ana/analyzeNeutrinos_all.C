// Example neutrino property analysis macro
// Change the filename to match your file
{
	//std::string filename = "../nu_beamOn1e6_1000.root";	
	std::string filename = "../result_geant4-10.7.4/myNeutrinoFile.root";	
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

	//TFile* outputFile = new TFile("neutrinoPlots2.root", "RECREATE");

  TCanvas *c1 = new TCanvas();

	TH1D* nuE_FluxHist = new TH1D("#nu_{e}", ";E_{#nu} (MeV);", 200, 0.0, 300.0);
	TH1D* nuE_bar_FluxHist = new TH1D("#bar{#nu}_{e}", ";E_{#nu} (MeV);", 200, 0.0, 300.0);
	TH1D* nuMu_FluxHist = new TH1D("#nu_{#mu}", ";E_{#nu} (MeV);", 200, 0.0, 300.0);
	TH1D* nuMu_bar_FluxHist = new TH1D("#bar{#nu}_{#mu}", ";E_{#nu} (MeV);", 200, 0.0, 300.0);




	for (int iParent = 0; iParent < numEntries; iParent++) {
		if (iParent % 100 == 0) std::cout << iParent << std::endl;
		neutrinoTree->GetEntry(iParent);

		// Loop over the neutrinos from this parent and look for muon neutrinos
		for (int iNu = 0; iNu < numNu; ++iNu) {
			if (nuPDGCode->at(iNu) == 12) {
				nuE_FluxHist->Fill(nuEnergy->at(iNu));
      }
			if (nuPDGCode->at(iNu) == 14) {
				nuMu_FluxHist->Fill(nuEnergy->at(iNu));
      }
			if (nuPDGCode->at(iNu) == -12) {
				nuE_bar_FluxHist->Fill(nuEnergy->at(iNu));
      }
			if (nuPDGCode->at(iNu) == -14) {
				nuMu_bar_FluxHist->Fill(nuEnergy->at(iNu));

			}
		}
	}

	std::cout << "Draw Histograms." << std::endl;

  gStyle->SetOptTitle(kFALSE);
  gStyle->SetOptStat(0);
  //gStyle->SetFillStyle(0);

  c1->SetLogy();
	//outputFile->cd();
  //c1->cd();
  nuE_FluxHist->SetLineColor(kOrange);
	nuE_FluxHist->Draw("SAME");
  //c1->cd();
  nuE_bar_FluxHist->SetLineColor(kBlue);
	nuE_bar_FluxHist->Draw("SAME");
  //c1->cd();
  nuMu_FluxHist->SetLineColor(kRed);
	nuMu_FluxHist->Draw("SAME");
  //c1->cd();
  //nuMu_bar_FluxHist->SetLineColor(kGreen);
	nuMu_bar_FluxHist->Draw("SAME");

  gPad->BuildLegend();
	//outputFile->Close();

	std::cout << "Finished." << std::endl;
}
