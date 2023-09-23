/*
 * validateZDCEmulation.C: Macro to validate the L1 ZDC emluated information using the ZDC digi output. 
 * Input: Folder of L1Ntuples
 * Output: Set of summary statistics that validates the L1 ZDC emluated information.
 * Authors: Hannah Bossi <hannah.bossi@cern.ch>, Gian Michele Innocenti, <gian.michele.innocenti@cern.ch> 
 * 8/20/23
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

// ------ trigger type --------
// 0 - no trigger
// 1 - ZDC OR
// 2 - ZDC And
// ----------------------------

int perEventDigiPlots(
    char const *input =
        "/Users/hannahbossi/Documents/LocalCode/RunPrep/outputFiles/Run373784/") {
  /* read in all files in the input folder */
  vector<string> files;
  GetFiles(input, files);

  /* read in offline ZDC information */

  TChain offChainZDCDigi("zdcanalyzer/zdcdigi");
  FillChain(offChainZDCDigi, files);
  TTreeReader offReaderZDCDigi(&offChainZDCDigi);
  TTreeReaderArray<int> z_side(offReaderZDCDigi, "zside");
  TTreeReaderArray<int> sec(offReaderZDCDigi, "section");
  TTreeReaderArray<int> ch(offReaderZDCDigi, "channel"); 
  TTreeReaderArray<int> adc(offReaderZDCDigi, "adcTs3");
  TTreeReaderValue<int> N(offReaderZDCDigi, "n");

  /* create histograms for efficiency plots */
  Long64_t totalEvents = offReaderZDCDigi.GetEntries(true);

  const Int_t nChannels = 18;
  TH1D* zdcChannel_h[nChannels];
    std::stringstream ss;
  for(Int_t tI = 0; tI < nChannels; ++tI){
    ss << "zdcChannel_" << tI;
    zdcChannel_h[tI] = new TH1D(ss.str().c_str(), "", 255, 0,255);
    ss.str("");
  }
  TH1D* zdcTotalDigis = new TH1D("zdcTotalDigis", "", 255, 0, 255);

  /* read in information from TTrees */
  float maxSumPlus = 0;
  float maxSumMinus = 0;
  for (Long64_t i = 0; i < totalEvents; i++) {
    offReaderZDCDigi.Next();
    for (int j = 0; j < *N; j++) {
      if (z_side[j] != -1 && z_side[j] != 1)
        continue;
      if (sec[j] != 1 && sec[j] != 2)
        continue;
      if (sec[j] == 1 && (ch[j] < 1 || ch[j] > 5))
        continue;
      if (sec[j] == 2 && (ch[j] < 1 || ch[j] > 4))
        continue;
      int idet = (z_side[j] == 1 ? 9 : 0) + (sec[j] == 2 ? 5 : 0) + (ch[j] - 1);
      zdcChannel_h[idet]->Fill(adc[idet]);
       zdcTotalDigis->Fill(adc[idet]);
    }


  }
  for(int i = 0; i < nChannels; ++i){
    TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
    c1->cd();
    c1->SetLogy();
    zdcChannel_h[i]->GetXaxis()->SetTitle("ADC");
    zdcChannel_h[i]->GetYaxis()->SetTitle("Counts");
    zdcChannel_h[i]->SetLineColor(kBlue);
    zdcChannel_h[i]->SetLineWidth(2);
    zdcChannel_h[i]->SetTitle(Form("ZDC Channel %d", i)); 
    zdcChannel_h[i]->Draw();
    ss << "../plots/zdc373784/zdcChannel_" << i << ".png";
    c1->SaveAs(ss.str().c_str());
    ss.str("");
  }
    TCanvas *c2 = new TCanvas("c2", "c2", 800, 600);
    c2->cd();
    c2->SetLogy();
    zdcTotalDigis->GetXaxis()->SetTitle("ADC");
    zdcTotalDigis->GetYaxis()->SetTitle("Counts");
    zdcTotalDigis->SetLineColor(kBlue);
    zdcTotalDigis->SetTitle("ZDC Total Digis");
    zdcTotalDigis->SetLineWidth(2);
    zdcTotalDigis->Draw();
    c2->SaveAs("../plots/zdc373784/zdcTotalDigis.png");
  return 1;
}

int main(int argc, char *argv[]) {
  if (argc == 2)
    return perEventDigiPlots(argv[1]);
  else {
    cout << "ERROR" << endl;
    return -1;
  }
}