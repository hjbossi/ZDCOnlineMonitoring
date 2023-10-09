/*
* plotZDCAnalyzer.C: Code to plot the sum plus and the sum minus from an l1ntuple (no trigger info)
*
*/

#include "TFile.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TTreeReaderArray.h"

#include "TDirectory.h"
#include "TSystemDirectory.h"
#include "TSystemFile.h"
#include "TChain.h"

#include "TMath.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLegend.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;




void GetFiles(char const *input, vector<string> &files) {
  TSystemDirectory dir(input, input);
  TList *list = dir.GetListOfFiles();

  if (list) {
    TSystemFile *file;
    string fname;
    TIter next(list);
    while ((file = (TSystemFile *)next())) {
      fname = file->GetName();

      if (file->IsDirectory() && (fname.find(".") == string::npos)) {
        string newDir = string(input) + fname + "/";
        GetFiles(newDir.c_str(), files);
      } else if ((fname.find(".root") != string::npos)) {
        files.push_back(string(input) + fname);
        cout << files.back() << endl;
      }
    }
  }

  return;
}

void FillChain(TChain &chain, vector<string> &files) {
  for (auto file : files) {
    chain.Add(file.c_str());
  }
}


void plotZDCAnalyzer( char const *input = "/home/hbossi/CMSSW_13_2_4/src/Run373730_Pedestal1_OOTPU04/"){


    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);

    string tag = "ZDCTestHADONLY_TS2-TS1"; 

    /* read in all files in the input folder */
    vector<string> files;
    GetFiles(input, files);
  

    /*
    TChain zdcChain("zdcanalyzer/zdcdigi");
    FillChain(zdcChain, files);
    TTreeReader zdcReader(&zdcChain);
    TTreeReaderValue<float> sumPlus(zdcReader, "sumPlus");
    TTreeReaderValue<float> sumMinus(zdcReader, "sumMinus");
    TTreeReaderArray<int> z_side(zdcReader, "zside");
    TTreeReaderArray<int> sec(zdcReader, "section");
    TTreeReaderArray<int> ch(zdcReader, "channel");
    TTreeReaderArray<int> adc(zdcReader, "adcTs2");
    TTreeReaderValue<int> N(zdcReader, "n");
    */
    // /* read in emulated information */
    TChain emuChain("l1UpgradeEmuTree/L1UpgradeTree");
    FillChain(emuChain, files);
    TTreeReader emuReader(&emuChain);
    TTreeReaderValue<vector<float> > emuSum(emuReader, "sumZDCEt");
    TTreeReaderValue<vector<short>> emuType(emuReader, "sumZDCType"); 
    TTreeReaderValue<vector<float>>	emuBx(emuReader, "sumZDCBx");


    TH1D* hZDCP = new TH1D("hZDCP", "ZDC Plus", 100, 0, 8000);
    TH1D* hZDCM = new TH1D("hZDCM", "ZDC Minus", 100, 0, 8000);

    TH1D* hZDCP_Emu = new TH1D("hZDCP_Emu", "ZDC Plus Emulated", 50, 0, 100);
    TH1D* hZDCM_Emu = new TH1D("hZDCM_Emu", "ZDC Minus Emulated", 50, 0, 100);

    TH1D* hHADM1 = new TH1D("hHAD1", "hHAD1", 1000, 0 , 5000); 
    TH1D* hHADM1_2023 = new TH1D("hHAD1_2023", "hHAD1_2023", 1000, 0 , 5000); 

    TH1D* hHADM2 = new TH1D("hHAD2", "hHAD2", 1000, 0 , 5000); 
    TH1D* hHADM2_2023 = new TH1D("hHAD2_2023", "hHAD2_2023", 1000, 0 , 5000); 

    TH2D* had2023 = new TH2D("had2023", "had2023", 1000, 0, 350000, 100, 1000, 350000);  

    Long64_t totalEvents = emuReader.GetEntries(true);
    int ZDCORcounts = 0; 
    for (Long64_t i = 0; i < totalEvents; i++) {
        emuReader.Next();
	float emuPlus = (*emuSum)[4]*2;
	float emuMinus = (*emuSum)[5]*2; 
	if(emuPlus > 12 || emuMinus > 12){
	  ZDCORcounts++; 
	}
	
        hZDCP_Emu->Fill(emuPlus);  
        hZDCM_Emu->Fill(emuMinus);  

    } //end loop over the events 

    std::cout << "ZDC OR Rate: " << float(ZDCORcounts)/float(totalEvents) << std::endl;

    TLatex* cms = new TLatex(0.10,0.92,"#bf{CMS} #it{Internal} Run 374730");
    cms->SetNDC();
    cms->SetTextSize(0.05);
    cms->SetTextFont(42);


    // plot emulated values
     // plot
    TLegend* leg4 = new TLegend(0.4,0.7,0.55,0.85);
    leg4->SetBorderSize(0);
    leg4->SetFillStyle(0);
    leg4->SetTextSize(0.045);


    TCanvas* c4 = new TCanvas("c4","c4",800,600);
    c4->cd();
    c4->SetTickx(1);
    c4->SetTicky(1);
    c4->SetLogy();
    c4->SetTopMargin(0.09);
    c4->SetBottomMargin(0.11);
    c4->SetLeftMargin(0.09);
    c4->SetRightMargin(0.05);

    // zdc plus
    hZDCP_Emu->SetLineColor(kRed);
    hZDCP_Emu->SetLineWidth(2);
    hZDCP_Emu->GetXaxis()->SetTitleSize(0.05);
    hZDCP_Emu->SetMarkerStyle(20);
    hZDCP_Emu->GetXaxis()->SetTitle("ZDC Energy Sum (GeV)");

    // zdc minus
    hZDCM_Emu->SetLineColor(kBlue);
    hZDCM_Emu->SetLineWidth(2);
    hZDCM_Emu->SetMarkerStyle(20);
    hZDCM_Emu->GetXaxis()->SetTitle("ZDC Energy Sum (GeV)");
    hZDCM_Emu->GetXaxis()->SetTitleSize(0.05);
    hZDCM_Emu->Draw();
    hZDCP_Emu->Draw("same");
    leg4->AddEntry(hZDCP_Emu,"ZDC Plus Emulated - HAD ONLY","l");
    leg4->AddEntry(hZDCM_Emu,"ZDC Minus Emulated - HAD ONLY","l");
    leg4->Draw("same");
    cms->Draw("same");
    c4->SaveAs(Form("ZDCNeutronDistributionsEmulated_%s.pdf", tag.c_str()));


}
