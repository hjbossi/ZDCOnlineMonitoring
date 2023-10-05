//
/*
 * checkUnpacker.C: Macro to check that the unpacked sums and the emulated sums are equivalent.
 * Input: Folder of L1Ntuples
 * Output: A root file of histograms relevant to checking the unpacking. 
 * Authors: Hannah Bossi <hannah.bossi@cern.ch>, Gian Michele Innocenti, <gian.michele.innocenti@cern.ch> 
 * 9/10/23
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

// params
// input: folder of l1ntuples to read from - must contain the branches specified above
// verbose: whether or not to print out the full output (error messgaes will always be printed)
int plotQuick1nPeak(
		  char const *input = "/eos/cms/store/group/phys_heavyions/yuchenc/run3RapidValidation/run374730_0003/231005_110505/0000/") {


    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);

    string tag = "Run347730"; 


  /* read in all files in the input folder */
  vector<string> files;
  GetFiles(input, files);

  /* read in the unpacked information */
  TChain zdcChain("zdcanalyzer/zdcdigi");
  FillChain(zdcChain, files);
  TTreeReader zdcReader(&zdcChain);
  TTreeReaderValue<float> sumPlus(zdcReader, "sumPlus");
  TTreeReaderValue<float> sumMinus(zdcReader, "sumMinus");
  

    /* read in trigger information */
  TChain trigChain("hltanalysis/HltTree");
  FillChain(trigChain, files);
  TTreeReader trigReader(&trigChain);
  TTreeReaderValue<int> zb(trigReader, "L1_ZeroBias");
  TTreeReaderValue<int> zdcOR(trigReader, "L1_ZDC1n_OR_BptxAND");
  TTreeReaderValue<int> zdcJet8(trigReader, "L1_SingleJet8_ZDC1n_XOR_BptxAND");
  TTreeReaderValue<int> zdcJet12(trigReader, "L1_SingleJet12_ZDC1n_XOR_BptxAND");
  TTreeReaderValue<int> zdcJet16(trigReader, "L1_SingleJet16_ZDC1n_XOR_BptxAND");
  TTreeReaderValue<int> zdcJet20(trigReader, "L1_SingleJet20_ZDC1n_XOR_BptxAND");
  TTreeReaderValue<int> zdcJet24(trigReader, "L1_SingleJet24_ZDC1n_XOR_BptxAND");
  TTreeReaderValue<int> zdcJet28(trigReader, "L1_SingleJet28_ZDC1n_XOR_BptxAND");


  /* read in the primary vertex filter*/
  TChain vertexChain("skimanalysis/HltTree");
  FillChain(vertexChain, files);
  TTreeReader vertexReader(&vertexChain);
  TTreeReaderValue<int> vertex(vertexReader, "pprimaryVertexFilter");

    /* read in the primary vertex filter*/
  TChain l1tChain("l1object/L1UpgradeFlatTree");
  FillChain(l1tChain, files);
  TTreeReader emuReader(&l1tChain);
  TTreeReaderValue<vector<float>> emuJetPt(emuReader, "jetEt");


  /* create histograms */

    TH1D* hZDCP = new TH1D("hZDCP", "ZDC Plus", 100, 0, 8000);
    TH1D* hZDCM = new TH1D("hZDCM", "ZDC Minus", 100, 0, 8000);

    TH1D* hZDCP_1n = new TH1D("hZDCP_1n", "ZDC Plus 1n", 100, 0, 8000);
    TH1D* hZDCM_1n = new TH1D("hZDCM_1n", "ZDC Minus 1n", 100, 0, 8000);
 
    TH1D* hZDCP_ZDCOR = new TH1D("hZDCP_ZDCOR", "ZDC Plus - ZDC OR", 100, 0, 8000);
    TH1D* hZDCM_ZDCOR = new TH1D("hZDCM_ZDCOR", "ZDC Minus - ZDC OR", 100, 0, 8000);

    TH1D* hZDCP_ZDCXOR_Mock = new TH1D("hZDCP_ZDCXOR Mock", "ZDC Plus - ZDC OR", 100, 0, 8000);
    TH1D* hZDCM_ZDCXOR_Mock = new TH1D("hZDCM_ZDCXOR Mock", "ZDC Minus - ZDC OR", 100, 0, 8000);

    TH1D* hZDCP_ZDCJet8 = new TH1D("hZDCP_ZDCJet8", "ZDC Plus - ZDC Jet 8", 100, 0, 8000);
    TH1D* hZDCM_ZDCJet8 = new TH1D("hZDCM_ZDCJet8", "ZDC Minus - ZDC Jet 8", 100, 0, 8000);

    TH1D* hZDCP_ZDCJet12 = new TH1D("hZDCP_ZDCJet12", "ZDC Plus - ZDC Jet 12", 100, 0, 8000);
    TH1D* hZDCM_ZDCJet12 = new TH1D("hZDCM_ZDCJet12", "ZDC Minus - ZDC Jet 12", 100, 0, 8000);

    TH1D* hZDCP_ZDCJet16 = new TH1D("hZDCP_ZDCJet16", "ZDC Plus - ZDC Jet 16", 100, 0, 8000);
    TH1D* hZDCM_ZDCJet16 = new TH1D("hZDCM_ZDCJet16", "ZDC Minus - ZDC Jet 16", 100, 0, 8000);

    TH1D* hZDCP_ZDCJet20 = new TH1D("hZDCP_ZDCJet20", "ZDC Plus - ZDC Jet 20", 100, 0, 8000);
    TH1D* hZDCM_ZDCJet20 = new TH1D("hZDCM_ZDCJet20", "ZDC Minus - ZDC Jet 20", 100, 0, 8000);

    TH1D* hZDCP_ZDCJet24 = new TH1D("hZDCP_ZDCJet24", "ZDC Plus - ZDC Jet 24", 100, 0, 8000);
    TH1D* hZDCM_ZDCJet24 = new TH1D("hZDCM_ZDCJet24", "ZDC Minus - ZDC Jet 24", 100, 0, 8000);

    TH1D* hZDCP_ZDCJet28 = new TH1D("hZDCP_ZDCJet28", "ZDC Plus - ZDC Jet 28", 100, 0, 8000);
    TH1D* hZDCM_ZDCJet28 = new TH1D("hZDCM_ZDCJet28", "ZDC Minus - ZDC Jet 28", 100, 0, 8000);


  int countZDCOROnline = 0; 
  int countZDCXORMock = 0; 
  int countZDCXORConservative = 0; 
  int countZDCjet8 = 0;
  int countZDCjet8_Conservative = 0;
  int countMockZDCORJet8 = 0; 
  Long64_t totalEvents = zdcReader.GetEntries(true);
  for (Long64_t i = 0; i < totalEvents; i++) {
    zdcReader.Next(); trigReader.Next(); vertexReader.Next(); emuReader.Next();
    //if(*vertex != 1) continue;

    if (i % 10000 == 0) {
      cout << "Event " << i << endl;
    }

    float emuMaxJetPt = -999;
    float totl1jets = totl1jets + (*emuJetPt).size();
    /* iterate through emu jets and find matched and unmatched jets with max pT */
    for (size_t j = 0; j < (*emuJetPt).size(); ++j) {
        if ((*emuJetPt)[j] > emuMaxJetPt) {
            emuMaxJetPt = (*emuJetPt)[j];
        }
    }

    hZDCP->Fill(*sumPlus);
    hZDCM->Fill(*sumMinus);

    int lowThreshold = 1050; 
    int highThreshold = 1150; 

    if(*sumPlus > lowThreshold && *sumMinus < highThreshold){
      countZDCXORConservative++;
       if(emuMaxJetPt >= 8){
        countZDCjet8_Conservative++;
      }
    }

    if(*sumPlus < highThreshold && *sumMinus > lowThreshold){
      countZDCXORConservative++;
        if(emuMaxJetPt >= 8){
        countZDCjet8_Conservative++;
      }
    }

    if(*sumPlus < 1100 && *zdcOR == 1){
      countZDCXORMock++;
      hZDCM_ZDCXOR_Mock->Fill(*sumMinus);
      if(emuMaxJetPt >= 8){
        countMockZDCORJet8++; 
      }
    }
    if(*sumMinus < 1100 && *zdcOR == 1){
      countZDCXORMock++;
      hZDCP_ZDCXOR_Mock->Fill(*sumPlus);
      if(emuMaxJetPt >= 8){
        countMockZDCORJet8++; 
      }
    }

    if(*sumPlus > 1100){
      hZDCP_1n->Fill(*sumPlus);
    }
    if(*sumMinus > 1100){
      hZDCM_1n->Fill(*sumMinus);
    }


    if(*zdcOR == 1){
      countZDCOROnline++; 
      hZDCP_ZDCOR->Fill(*sumPlus);
      hZDCM_ZDCOR->Fill(*sumMinus);
    }

    if(*zdcJet8 == 1){
      countZDCjet8++;
      hZDCP_ZDCJet8->Fill(*sumPlus);
      hZDCM_ZDCJet8->Fill(*sumMinus);
    }

    if(*zdcJet12 == 1){
      hZDCP_ZDCJet12->Fill(*sumPlus);
      hZDCM_ZDCJet12->Fill(*sumMinus);
    }

    if(*zdcJet16 == 1){
      hZDCP_ZDCJet16->Fill(*sumPlus);
      hZDCM_ZDCJet16->Fill(*sumMinus);
    }

     if(*zdcJet20 == 1){
      hZDCP_ZDCJet20->Fill(*sumPlus);
      hZDCM_ZDCJet20->Fill(*sumMinus);
    }

    if(*zdcJet24 == 1){
      hZDCP_ZDCJet24->Fill(*sumPlus);
      hZDCM_ZDCJet24->Fill(*sumMinus);
    }

     if(*zdcJet28 == 1){
      hZDCP_ZDCJet28->Fill(*sumPlus);
      hZDCM_ZDCJet28->Fill(*sumMinus);
    }



  } // end loop over  the  number of events
  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
  std::cout << "Finished processing " << totalEvents << " events." << std::endl;
  std::cout << "ZDC OR fired " << countZDCOROnline << " times for a fraction of " << double(countZDCOROnline)/double(totalEvents) << std::endl;
  std::cout << "ZDC XOR fired " << countZDCXORMock << " times for a fraction of " << double(countZDCXORMock)/double(totalEvents) << std::endl;
  std::cout << "ZDC Conservative XOR fired " << countZDCXORConservative << " times for a fraction of " << double(countZDCXORConservative)/double(totalEvents) << std::endl;
  std::cout << "ZDC XOR Jet 8 fired " << countZDCjet8 << " times for a fraction of " << double(countZDCjet8)/double(totalEvents) << std::endl;
  std::cout << "Mock ZDC XOR  + Jet 8 fired " << countMockZDCORJet8 << " times for a fraction of " << double(countMockZDCORJet8)/double(totalEvents) << std::endl;
  std::cout << "ZDC Conservative Jet 8 fired " << countZDCjet8_Conservative << " times for a fraction of " << double(countZDCjet8_Conservative)/double(totalEvents) << std::endl;
  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;


    TFile* outfile = new TFile(Form("TriggerCheck_October5th_%s.root", tag.c_str()), "RECREATE");
    outfile->cd();
    hZDCP->Write();
    hZDCM->Write();
    hZDCM_ZDCXOR_Mock->Write(); 
    hZDCP_ZDCXOR_Mock->Write();
    hZDCP_ZDCOR->Write();
    hZDCM_ZDCOR->Write();
    hZDCP_ZDCJet8->Write();
    hZDCM_ZDCJet8->Write();
    hZDCP_ZDCJet12->Write();
    hZDCM_ZDCJet12->Write();
    hZDCP_ZDCJet16->Write();
    hZDCM_ZDCJet16->Write();
    hZDCP_ZDCJet20->Write();
    hZDCM_ZDCJet20->Write();
    hZDCP_ZDCJet24->Write();
    hZDCM_ZDCJet24->Write();
    hZDCP_ZDCJet28->Write();
    hZDCM_ZDCJet28->Write();
    hZDCP_1n->Write();
    hZDCM_1n->Write();
    outfile->Close();


    TLatex* cms = new TLatex(0.10,0.92,"#bf{CMS} #it{Internal} Run 374730");
    cms->SetNDC();
    cms->SetTextSize(0.05);
    cms->SetTextFont(42);

    // ------------------------------------------
    /* ZDC Plus and Minus */
    // ------------------------------------------

   

    TLegend* leg3 = new TLegend(0.65,0.7,0.8,0.85);
    leg3->SetBorderSize(0);
    leg3->SetFillStyle(0);
    leg3->SetTextSize(0.045);
    
    TCanvas* c3 = new TCanvas("c3","c3",800,600);
    c3->cd();
    c3->SetTickx(1);
    c3->SetTicky(1);
    c3->SetLogy(); 
    c3->SetTopMargin(0.09);
    c3->SetBottomMargin(0.11);
    c3->SetLeftMargin(0.09);
    c3->SetRightMargin(0.05);

    // zdc plus
    hZDCP->SetLineColor(kRed);
    hZDCP->SetLineWidth(2);
    hZDCP->GetXaxis()->SetTitleSize(0.05);
    hZDCP->SetMarkerStyle(20);
    hZDCP->GetXaxis()->SetTitle("ZDC Energy Sum (GeV)");
  

    // zdc minus
    hZDCM->SetLineColor(kBlue);
    hZDCM->SetLineWidth(2);
    hZDCM->SetMarkerStyle(20);
    hZDCM->GetXaxis()->SetTitle("ZDC Energy Sum (GeV)");
    hZDCM->GetXaxis()->SetTitleSize(0.05);
    hZDCM->Draw();
    hZDCP->Draw("same");
    leg3->AddEntry(hZDCP,"ZDC Plus","l");
    leg3->AddEntry(hZDCM,"ZDC Minus","l");
    leg3->Draw("same");
    cms->Draw("same");
    c3->SaveAs(Form("Online_ZDCNeutronDistributions_%s.pdf", tag.c_str()));


     // ------------------------------------------
    /* ZDC OR */
    // ------------------------------------------

    TLegend* leg4 = new TLegend(0.4,0.7,0.6,0.85);
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
    hZDCP_ZDCOR->SetLineColor(kRed);
    hZDCP_ZDCOR->SetLineWidth(2);
    hZDCP_ZDCOR->GetXaxis()->SetTitleSize(0.05);
    hZDCP_ZDCOR->SetMarkerStyle(20);
    hZDCP_ZDCOR->GetXaxis()->SetTitle("ZDC Energy Sum (GeV)");
  

    // zdc minus
    hZDCM_ZDCOR->SetLineColor(kBlue);
    hZDCM_ZDCOR->SetLineWidth(2);
    hZDCM_ZDCOR->SetMarkerStyle(20);
    hZDCM_ZDCOR->GetXaxis()->SetTitle("ZDC Energy Sum (GeV)");
    hZDCM_ZDCOR->GetXaxis()->SetTitleSize(0.05);
    hZDCM_ZDCOR->Draw();
    hZDCP_ZDCOR->Draw("same");
    leg4->AddEntry(hZDCP_ZDCOR,"ZDC Plus ZDC OR","l");
    leg4->AddEntry(hZDCM,"ZDC Minus ZDC OR","l");
    leg4->Draw("same");
     cms->Draw("same");
    c4->SaveAs(Form("Online_ZDCORTriggered_%s.pdf", tag.c_str()));


    // ------------------------------------------
    /* ZDC jet 8 */
    // ------------------------------------------

    TLegend* leg5 = new TLegend(0.4,0.7,0.6,0.85);
    leg5->SetBorderSize(0);
    leg5->SetFillStyle(0);
    leg5->SetTextSize(0.045);

    TCanvas* c5 = new TCanvas("c5","c5",800,600);
    c5->cd();
    c5->SetTickx(1);
    c5->SetTicky(1);
    c5->SetLogy();
    c5->SetTopMargin(0.09);
    c5->SetBottomMargin(0.11);
    c5->SetLeftMargin(0.09);
    c5->SetRightMargin(0.05);

    // zdc plus
    hZDCP_ZDCJet8->SetLineColor(kRed);
    hZDCP_ZDCJet8->SetLineWidth(2);
    hZDCP_ZDCJet8->GetXaxis()->SetTitleSize(0.05);
    hZDCP_ZDCJet8->SetMarkerStyle(20);
    hZDCP_ZDCJet8->GetXaxis()->SetTitle("ZDC Energy Sum (GeV)");

    // zdc minus
    hZDCM_ZDCJet8->SetLineColor(kBlue);
    hZDCM_ZDCJet8->SetLineWidth(2);
    hZDCM_ZDCJet8->SetMarkerStyle(20);
    hZDCM_ZDCJet8->GetXaxis()->SetTitle("ZDC Energy Sum (GeV)");
    hZDCM_ZDCJet8->GetXaxis()->SetTitleSize(0.05);
    hZDCM_ZDCJet8->Draw();

    hZDCP_ZDCJet8->Draw("same");
    leg5->AddEntry(hZDCP_ZDCJet8,"ZDC Plus ZDC Jet 8","l");
    leg5->AddEntry(hZDCM,"ZDC Minus ZDC Jet 8","l");
    leg5->Draw("same");
     cms->Draw("same");
    c5->SaveAs(Form("Online_ZDCJet8Triggered_%s.pdf", tag.c_str()));

     // ------------------------------------------
    /* ZDC jet 12 */
    // ------------------------------------------

    TLegend* leg6 = new TLegend(0.4,0.7,0.6,0.85);
    leg6->SetBorderSize(0);
    leg6->SetFillStyle(0);
    leg6->SetTextSize(0.045);

    TCanvas* c6 = new TCanvas("c6","c6",800,600);
    c6->cd();
    c6->SetTickx(1);
    c6->SetTicky(1);
    c6->SetLogy();
    c6->SetTopMargin(0.09);
    c6->SetBottomMargin(0.11);
    c6->SetLeftMargin(0.09);
    c6->SetRightMargin(0.05);

    // zdc plus
    hZDCP_ZDCJet12->SetLineColor(kRed);
    hZDCP_ZDCJet12->SetLineWidth(2);
    hZDCP_ZDCJet12->GetXaxis()->SetTitleSize(0.05);
    hZDCP_ZDCJet12->SetMarkerStyle(20);
    hZDCP_ZDCJet12->GetXaxis()->SetTitle("ZDC Energy Sum (GeV)");

    // zdc minus
    hZDCM_ZDCJet12->SetLineColor(kBlue);
    hZDCM_ZDCJet12->SetLineWidth(2);
    hZDCM_ZDCJet12->SetMarkerStyle(20);
    hZDCM_ZDCJet12->GetXaxis()->SetTitle("ZDC Energy Sum (GeV)");
    hZDCM_ZDCJet12->GetXaxis()->SetTitleSize(0.05);
    hZDCM_ZDCJet12->Draw();

    hZDCP_ZDCJet12->Draw("same");
    leg6->AddEntry(hZDCP_ZDCJet12,"ZDC Plus ZDC Jet 12","l");
    leg6->AddEntry(hZDCM,"ZDC Minus ZDC Jet 12","l");
    leg6->Draw("same");
     cms->Draw("same");

    c6->SaveAs(Form("Online_ZDCJet12Triggered_%s.pdf", tag.c_str()));

     // ------------------------------------------
    /* ZDC jet 16 */
    // ------------------------------------------

    TLegend* leg7 = new TLegend(0.4,0.7,0.6,0.85);
    leg7->SetBorderSize(0);
    leg7->SetFillStyle(0);
    leg7->SetTextSize(0.045);

    TCanvas* c7 = new TCanvas("c7","c7",800,600);
    c7->cd();
    c7->SetTickx(1);
    c7->SetTicky(1);
    c7->SetLogy();
    c7->SetTopMargin(0.09);
    c7->SetBottomMargin(0.11);
    c7->SetLeftMargin(0.09);
    c7->SetRightMargin(0.05);

    // zdc plus
    hZDCP_ZDCJet16->SetLineColor(kRed);
    hZDCP_ZDCJet16->SetLineWidth(2);
    hZDCP_ZDCJet16->GetXaxis()->SetTitleSize(0.05);
    hZDCP_ZDCJet16->SetMarkerStyle(20);
    hZDCP_ZDCJet16->GetXaxis()->SetTitle("ZDC Energy Sum (GeV)");

    // zdc minus
    hZDCM_ZDCJet16->SetLineColor(kBlue);
    hZDCM_ZDCJet16->SetLineWidth(2);
    hZDCM_ZDCJet16->SetMarkerStyle(20);
    hZDCM_ZDCJet16->GetXaxis()->SetTitle("ZDC Energy Sum (GeV)");
    hZDCM_ZDCJet16->GetXaxis()->SetTitleSize(0.05);
    hZDCM_ZDCJet16->Draw();

    hZDCP_ZDCJet16->Draw("same");
    leg7->AddEntry(hZDCP_ZDCJet16,"ZDC Plus ZDC Jet 16","l");
    leg7->AddEntry(hZDCM,"ZDC Minus ZDC Jet 16","l");
    leg7->Draw("same");
     cms->Draw("same");

    c7->SaveAs(Form("Online_ZDCJet16Triggered_%s.pdf", tag.c_str()));

     // ------------------------------------------
    /* ZDC jet 20 */
    // ------------------------------------------

    TLegend* leg8 = new TLegend(0.4,0.7,0.6,0.85);
    leg8->SetBorderSize(0);
    leg8->SetFillStyle(0);
    leg8->SetTextSize(0.045);

    TCanvas* c8 = new TCanvas("c8","c8",800,600);
    c8->cd();
    c8->SetTickx(1);
    c8->SetTicky(1);
    c8->SetLogy();
    c8->SetTopMargin(0.09);
    c8->SetBottomMargin(0.11);
    c8->SetLeftMargin(0.09);
    c8->SetRightMargin(0.05);

    // zdc plus
    hZDCP_ZDCJet20->SetLineColor(kRed);
    hZDCP_ZDCJet20->SetLineWidth(2);
    hZDCP_ZDCJet20->GetXaxis()->SetTitleSize(0.05);
    hZDCP_ZDCJet20->SetMarkerStyle(20);
    hZDCP_ZDCJet20->GetXaxis()->SetTitle("ZDC Energy Sum (GeV)");

    // zdc minus
    hZDCM_ZDCJet20->SetLineColor(kBlue);
    hZDCM_ZDCJet20->SetLineWidth(2);
    hZDCM_ZDCJet20->SetMarkerStyle(20);
    hZDCM_ZDCJet20->GetXaxis()->SetTitle("ZDC Energy Sum (GeV)");
    hZDCM_ZDCJet20->GetXaxis()->SetTitleSize(0.05);
    hZDCM_ZDCJet20->Draw();

    hZDCP_ZDCJet20->Draw("same");
    leg8->AddEntry(hZDCP_ZDCJet20,"ZDC Plus ZDC Jet 20","l");
    leg8->AddEntry(hZDCM,"ZDC Minus ZDC Jet 20","l");
    leg8->Draw("same");
     cms->Draw("same");

    c8->SaveAs(Form("Online_ZDCJet20Triggered_%s.pdf", tag.c_str()));

     // ------------------------------------------
    /* ZDC jet 24 */
    // ------------------------------------------

    TLegend* leg9 = new TLegend(0.4,0.7,0.6,0.85);
    leg9->SetBorderSize(0);
    leg9->SetFillStyle(0);
    leg9->SetTextSize(0.045);

    TCanvas* c9 = new TCanvas("c9","c9",800,600);
    c9->cd();
    c9->SetTickx(1);
    c9->SetTicky(1);
    c9->SetLogy();
    c9->SetTopMargin(0.09);
    c9->SetBottomMargin(0.11);
    c9->SetLeftMargin(0.09);
    c9->SetRightMargin(0.05);

    // zdc plus
    hZDCP_ZDCJet24->SetLineColor(kRed);
    hZDCP_ZDCJet24->SetLineWidth(2);
    hZDCP_ZDCJet24->GetXaxis()->SetTitleSize(0.05);
    hZDCP_ZDCJet24->SetMarkerStyle(20);
    hZDCP_ZDCJet24->GetXaxis()->SetTitle("ZDC Energy Sum (GeV)");

    // zdc minus
    hZDCM_ZDCJet24->SetLineColor(kBlue);
    hZDCM_ZDCJet24->SetLineWidth(2);
    hZDCM_ZDCJet24->SetMarkerStyle(20);
    hZDCM_ZDCJet24->GetXaxis()->SetTitle("ZDC Energy Sum (GeV)");
    hZDCM_ZDCJet24->GetXaxis()->SetTitleSize(0.05);

    hZDCM_ZDCJet24->Draw();
    hZDCP_ZDCJet24->Draw("same");
    leg9->AddEntry(hZDCP_ZDCJet24,"ZDC Plus ZDC Jet 24","l");
    leg9->AddEntry(hZDCM,"ZDC Minus ZDC Jet 24","l");
    leg9->Draw("same");
     cms->Draw("same");

    c9->SaveAs(Form("Online_ZDCJet24Triggered_%s.pdf", tag.c_str()));

     // ------------------------------------------

    /* ZDC jet 28 */
    // ------------------------------------------

    TLegend* leg10 = new TLegend(0.4,0.7,0.6,0.85);
    leg10->SetBorderSize(0);
    leg10->SetFillStyle(0);
    leg10->SetTextSize(0.045);

    TCanvas* c10 = new TCanvas("c10","c10",800,600);
    c10->cd();
    c10->SetTickx(1);
    c10->SetTicky(1);
    c10->SetLogy();
    c10->SetTopMargin(0.09);
    c10->SetBottomMargin(0.11);
    c10->SetLeftMargin(0.09);
    c10->SetRightMargin(0.05);

    // zdc plus
    hZDCP_ZDCJet28->SetLineColor(kRed);
    hZDCP_ZDCJet28->SetLineWidth(2);
    hZDCP_ZDCJet28->GetXaxis()->SetTitleSize(0.05);
    hZDCP_ZDCJet28->SetMarkerStyle(20);
    hZDCP_ZDCJet28->GetXaxis()->SetTitle("ZDC Energy Sum (GeV)");

    // zdc minus
    hZDCM_ZDCJet28->SetLineColor(kBlue);
    hZDCM_ZDCJet28->SetLineWidth(2);
    hZDCM_ZDCJet28->SetMarkerStyle(20);
    hZDCM_ZDCJet28->GetXaxis()->SetTitle("ZDC Energy Sum (GeV)");
    hZDCM_ZDCJet28->GetXaxis()->SetTitleSize(0.05);

    hZDCM_ZDCJet28->Draw();
    hZDCP_ZDCJet28->Draw("same");
    leg10->AddEntry(hZDCP_ZDCJet28,"ZDC Plus ZDC Jet 28","l");
    leg10->AddEntry(hZDCM,"ZDC Minus ZDC Jet 28","l");
    leg10->Draw("same");
     cms->Draw("same");

    c10->SaveAs(Form("Online_ZDCJet28Triggered_%s.pdf", tag.c_str()));

    // ------------------------------------------
    /* ZDC OR TURN ON */
    // ------------------------------------------

    TLegend* leg11 = new TLegend(0.4,0.7,0.6,0.85);
    leg11->SetBorderSize(0);
    leg11->SetFillStyle(0);
    leg11->SetTextSize(0.045);
    
    TCanvas* c11 = new TCanvas("c11","c11",800,600);
    c11->cd();
    c11->SetTickx(1);
    c11->SetTicky(1);
    // c4->SetLogy(); 
    c11->SetTopMargin(0.09);
    c11->SetBottomMargin(0.11);
    c11->SetLeftMargin(0.09);
    c11->SetRightMargin(0.05);

    // clone zdc OR hists
    TH1D* hZDCP_ZDCOR_clone = (TH1D*)hZDCP_1n->Clone();
    TH1D* hZDCM_ZDCOR_clone = (TH1D*)hZDCM_1n->Clone();

    // divide by hZDCP and hZDCM
    hZDCP_ZDCOR_clone->Divide(hZDCP);
    hZDCM_ZDCOR_clone->Divide(hZDCM);

    // zdc plus
    hZDCP_ZDCOR_clone->SetLineColor(kRed);
    hZDCP_ZDCOR_clone->SetLineWidth(2);
    hZDCP_ZDCOR_clone->SetMarkerStyle(20);
    hZDCP_ZDCOR_clone->GetXaxis()->SetTitleSize(0.05);
    hZDCP_ZDCOR_clone->SetMarkerStyle(20);
    hZDCP_ZDCOR_clone->GetXaxis()->SetTitle("ZDC Energy Sum (GeV)");
  

    // zdc minus
    hZDCM_ZDCOR_clone->SetLineColor(kBlue);
    hZDCM_ZDCOR_clone->SetLineWidth(2);
    hZDCM_ZDCOR_clone->SetMarkerStyle(20);
    hZDCM_ZDCOR_clone->GetXaxis()->SetTitle("ZDC Energy Sum (GeV)");
    hZDCM_ZDCOR_clone->GetYaxis()->SetTitle("Efficiency");
    hZDCM_ZDCOR_clone->GetXaxis()->SetTitleSize(0.05);
    hZDCM_ZDCOR_clone->GetYaxis()->SetRangeUser(0,1.1);
    hZDCM_ZDCOR_clone->Draw();
    hZDCP_ZDCOR_clone->Draw("same");
    leg11->AddEntry(hZDCP_ZDCOR_clone,"ZDC Plus ZDC OR","l");
    leg11->AddEntry(hZDCM_ZDCOR_clone,"ZDC Minus ZDC OR","l");
    leg11->Draw("same");
     cms->Draw("same");
    c11->SaveAs(Form("TurnOn_Online_ZDCORTriggered%s.pdf", tag.c_str()));


    // ------------------------------------------
    /* ZDC XOR */
    // ------------------------------------------

    TLegend* leg12 = new TLegend(0.4,0.7,0.6,0.85);
    leg12->SetBorderSize(0);
    leg12->SetFillStyle(0);
    leg12->SetTextSize(0.045);
    
    TCanvas* c12 = new TCanvas("c12","c12",800,600);
    c12->cd();
    c12->SetTickx(1);
    c12->SetTicky(1);
    c12->SetLogy(); 
    c12->SetTopMargin(0.09);
    c12->SetBottomMargin(0.11);
    c12->SetLeftMargin(0.09);
    c12->SetRightMargin(0.05);

    // zdc plus
    hZDCP_ZDCXOR_Mock->SetLineColor(kRed);
    hZDCP_ZDCXOR_Mock->SetLineWidth(2);
    hZDCP_ZDCXOR_Mock->GetXaxis()->SetTitleSize(0.05);
    hZDCP_ZDCXOR_Mock->SetMarkerStyle(20);
    hZDCP_ZDCXOR_Mock->GetXaxis()->SetTitle("ZDC Energy Sum (GeV)");
  

    // zdc minus
    hZDCM_ZDCXOR_Mock->SetLineColor(kBlue);
    hZDCM_ZDCXOR_Mock->SetLineWidth(2);
    hZDCM_ZDCXOR_Mock->SetMarkerStyle(20);
    hZDCM_ZDCXOR_Mock->GetXaxis()->SetTitle("ZDC Energy Sum (GeV)");
    hZDCM_ZDCXOR_Mock->GetXaxis()->SetTitleSize(0.05);
    hZDCM_ZDCXOR_Mock->Draw();
    hZDCP_ZDCXOR_Mock->Draw("same");
    leg12->AddEntry(hZDCP_ZDCXOR_Mock,"ZDC Plus ZDC XOR Mock","l");
    leg12->AddEntry(hZDCM_ZDCXOR_Mock,"ZDC Minus ZDC XOR Mock","l");
    leg12->Draw("same");
     cms->Draw("same");
    c12->SaveAs(Form("Online_ZDCXORMockTriggered_%s.pdf", tag.c_str()));

  return 1;
}

int main(int argc, char *argv[]) {
  if (argc == 2)
    return plotQuick1nPeak(argv[1]);
  else {
    cout << "ERROR" << endl;
    return -1;
  }
}
