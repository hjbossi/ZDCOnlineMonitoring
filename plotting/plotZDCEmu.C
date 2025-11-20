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
int plotZDCEmu(
		  char const *input = "/eos/cms/store/group/phys_heavyions/cmcginn/Run2025/HIExpress/399/572/") {
      
    std::cout << "Running over " << input << std::endl; 

    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);

    string tag = "Run399572_LS_85_108"; 

    TLatex* cms = new TLatex(0.10,0.92,"#bf{CMS}#it{Preliminary} 2025 PbPb (5.36 TeV) Empty Bx");
    cms->SetNDC();
    cms->SetTextSize(0.05);
    cms->SetTextFont(42);


    TLatex* cms2 = new TLatex(0.10,0.92,"#bf{CMS}#it{Preliminary} 2025 PbPb (5.36 TeV)");
    cms2->SetNDC();
    cms2->SetTextSize(0.05);
    cms2->SetTextFont(42);



  /* read in all files in the input folder */
  vector<string> files;
  GetFiles(input, files);

  /* read in the unpacked information */
  TChain zdcChain("zdcanalyzer/zdcrechit");
  FillChain(zdcChain, files);
  TTreeReader zdcReader(&zdcChain);
  TTreeReaderValue<float> sumPlus(zdcReader, "sumPlus");
  TTreeReaderValue<float> sumMinus(zdcReader, "sumMinus");

  /* read in the unpacked information */
  TChain unpackerChain("l1UpgradeTree/L1UpgradeTree");
  FillChain(unpackerChain, files);
  TTreeReader unpackerReader(&unpackerChain);
  TTreeReaderValue<unsigned short> nEtSums(unpackerReader, "nSums"); 
  TTreeReaderValue<vector<float> > unpackerEtSum(unpackerReader, "sumEt");
  TTreeReaderValue<vector<float>>	unpackerEtSumBx(unpackerReader, "sumBx");
  TTreeReaderValue<vector<short>>	unpackerEtSumType(unpackerReader, "sumType");
  TTreeReaderValue<vector<short> > unpackerSum(unpackerReader, "sumZDCIEt");
  TTreeReaderValue<vector<short>>	unpackerType(unpackerReader, "sumZDCType");
  TTreeReaderValue<vector<float>>	unpackerBx(unpackerReader, "sumZDCBx");
  TTreeReaderValue<unsigned short> nJets(unpackerReader, "nJets"); 
  TTreeReaderValue<vector<float>>	jetEt(unpackerReader, "jetEt");
  TTreeReaderValue<vector<float>>	jetEta(unpackerReader, "jetEta");

   TChain hiEventChain("l1EventTree/L1EventTree"); 
    FillChain(hiEventChain, files); 
    TTreeReader eventReader(&hiEventChain);
    TTreeReaderValue<uint> runNumber(eventReader, "run"); 
    TTreeReaderValue<ULong64_t> eventNumber(eventReader, "event"); 
    TTreeReaderValue<uint> lumiSection(eventReader, "lumi"); 

  TChain emuChain("l1UpgradeEmuTree/L1UpgradeTree");
  FillChain(emuChain, files);
  TTreeReader emuReader(&emuChain);
  TTreeReaderValue<vector<short>> emuSum(emuReader, "sumZDCIEt");
  TTreeReaderValue<vector<short>> emuType(emuReader, "sumZDCType"); 
  TTreeReaderValue<vector<float>>	emuBx(emuReader, "sumZDCBx");
  TTreeReaderValue<unsigned short> nSums(emuReader, "nSumsZDC"); 

   /* read in information on the emulated trigger fires*/
  TChain l1TrigChain("l1uGTTree/L1uGTTree");
  FillChain(l1TrigChain, files);
  TTreeReader emuTrigReader(&l1TrigChain);
  TTreeReaderValue<vector<bool>> initialTrigDecision(emuTrigReader, "m_algoDecisionFinal");

  /* create histograms */



    TH1D* hZDCP_Emu = new TH1D("hZDCP_Emu", "ZDC Plus Emulated", 100, 0, 1024);
    TH1D* hZDCM_Emu = new TH1D("hZDCM_Emu", "ZDC Minus Emulated", 100, 0, 1024);
    TH1D* hZDCP_withTrig = new TH1D("hZDCP_withTrig", "ZDC Plus", 100, 0, 15000);
    TH1D* hZDCM_withTrig = new TH1D("hZDCM_withTrig", "ZDC Minus", 100, 0, 15000);
    TH1D* hZDCP = new TH1D("hZDCP", "ZDC Plus", 100, 0, 15000);
    TH1D* hZDCM = new TH1D("hZDCM", "ZDC Minus", 100, 0, 15000);
    TH1D* hZDCP_EmuScaled = new TH1D("hZDCP_EmuScaled", "ZDC Plus", 100, 0, 15000);
    TH1D* hZDCM_EmuScaled = new TH1D("hZDCM_EmuScaled", "ZDC Minus", 100, 0, 15000);
    TH1D* hZDC_Asymm = new TH1D("Asymm", "", 20, -2, 2); 
    TH2D* hZDCAsymCorr = new TH2D("AsymmCorr", "",  50, 0, 300,  50, 0, 300); 
    TH2D* hZDCAsymCorrJet = new TH2D("AsymmCorrJet", "",  40, -5.0, 5.0,40, -2, 2); 

  Long64_t totalEvents = emuReader.GetEntries(true);
  for (Long64_t i = 0; i < totalEvents; i++) {
    emuReader.Next(); emuTrigReader.Next(); zdcReader.Next(); unpackerReader.Next(); eventReader.Next(); 

    // zero bias
    //if((*initialTrigDecision)[1] != 1 ) continue; 

    if (i % 10000 == 0) {
      cout << "Event " << i << endl;
    }

    if(*lumiSection > 108 || *lumiSection < 85) continue; 
    std::cout << *lumiSection << std::endl;
    
    //std::cout << *nSums << std::endl;
    int unpackerSumPlus = -1; 
    int unpackerSumMinus = -1; 
    for(int j = 0; j < *nSums; j++){
        if((*unpackerType)[j] == 27 && (*unpackerBx)[j] == 0){
            hZDCP_Emu->Fill((*unpackerSum)[j]);
            unpackerSumPlus = (*unpackerSum)[j]; 
        }
        else if((*unpackerType)[j] == 28 && (*unpackerBx)[j] == 0) {
            hZDCM_Emu->Fill((*unpackerSum)[j]);
            unpackerSumMinus = (*unpackerSum)[j]; 
        }
    }
//std::cout << "Run: " <<  *runNumber << " lumi: " << *lumiSection << " event: " <<  *eventNumber << " sumZDCp: " << unpackerSumPlus << " sumZDCm: " << unpackerSumMinus << std::endl; 

    // float hfp = -1.0; 
    // float hfm = -1.0; 
    // for(int j = 0; j < *nEtSums; j++){
    //   //std::cout << "Sum type: " << (*unpackerEtSumType)[j] << std::endl;
    //     if((*unpackerEtSumType)[j] == 11){
    //         hfp = (*unpackerEtSum)[j]; 
    //     }
    //     if((*unpackerEtSumType)[j] == 12) {
    //         std::cout << " (*unpackerEtSumBx)[j]: " <<  (*unpackerEtSumBx)[j] << " (*unpackerEtSum)[j]: " <<  (*unpackerEtSum)[j] << std::endl;
    //         hfm = (*unpackerEtSum)[j]; 
    //     }
    // }
    // std::cout << "plus: " << hfp << " minus: " << hfm << std::endl; 

    float emuMinus = (*unpackerSum)[4]*2;
    float emuPlus = (*unpackerSum)[5]*2; 

    //std::cout << "emuPlus: " << emuPlus << " sumPlus: " << *sumPlus << std::endl;

    if(emuPlus > 40)hZDCP_withTrig->Fill(*sumPlus);
    if(emuMinus> 40)hZDCM_withTrig->Fill(*sumMinus);

    hZDCM_EmuScaled->Fill(emuMinus*16); 
    hZDCP_EmuScaled->Fill(emuPlus*16); 
   
    double maxJetEt = -1.0;  
    for(int j = 0; j < *nJets; j++){
      if((*jetEt)[j] > 20) hZDCAsymCorrJet->Fill((*jetEta)[j],float(unpackerSumPlus - unpackerSumMinus)/(unpackerSumPlus + unpackerSumMinus)); 
    }
    hZDC_Asymm->Fill(float(unpackerSumPlus - unpackerSumMinus)/(unpackerSumPlus + unpackerSumMinus)); 
    hZDCAsymCorr->Fill(unpackerSumPlus, unpackerSumMinus); 

    hZDCP->Fill(*sumPlus);
    hZDCM->Fill(*sumMinus);


  } // end loop over  the  number of events





  
     // ------------------------------------------
    /* ZDC Emu */
    // ------------------------------------------

    TLegend* leg = new TLegend(0.4,0.7,0.6,0.85);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->SetTextSize(0.045);
    
    TCanvas* c = new TCanvas("c","c",800,600);
    c->cd();
    c->SetTickx(1);
    c->SetTicky(1);
    c->SetLogy(); 
    c->SetTopMargin(0.09);
    c->SetBottomMargin(0.11);
    c->SetLeftMargin(0.09);
    c->SetRightMargin(0.05);

    // zdc plus
    hZDCP_Emu->SetLineColor(kRed);
    hZDCP_Emu->SetLineWidth(2);
    hZDCP_Emu->GetXaxis()->SetTitleSize(0.05);
    hZDCP_Emu->SetMarkerStyle(20);
    hZDCP_Emu->GetXaxis()->SetTitle("ZDC L1 Energy Sum");
    //hZDCM_Emu->GetXaxis()->SetRangeUser(0, 200);


    // zdc minus
    hZDCM_Emu->SetLineColor(kBlue);
    hZDCM_Emu->SetLineWidth(2);
    hZDCM_Emu->SetMarkerStyle(20);
    hZDCM_Emu->GetXaxis()->SetTitle("ZDC L1 Energy Sum");
    hZDCM_Emu->GetXaxis()->SetTitleSize(0.05);
    //hZDCM_Emu->GetXaxis()->SetRangeUser(0, 200);
    hZDCM_Emu->Draw();
    hZDCP_Emu->Draw("same");
    leg->AddEntry(hZDCP_Emu,"ZDC Plus","l");
    leg->AddEntry(hZDCM_Emu,"ZDC Minus","l");
    leg->Draw("same");
    cms->Draw("same");
    c->SaveAs(Form("Online_ZDCEmu_%s.pdf", tag.c_str()));




     // ------------------------------------------
    /* ZDC Emu Ratio */
    // ------------------------------------------

    
    TCanvas* c12 = new TCanvas("c12","c12",800,600);
    c12->cd();
    c12->SetTickx(1);
    c12->SetTicky(1);
    // c12->SetLogy(); 
    c12->SetTopMargin(0.09);
    c12->SetBottomMargin(0.11);
    c12->SetLeftMargin(0.09);
    c12->SetRightMargin(0.05);

    TLine* l = new TLine(0, 1.0, 1023, 1.0); 
    l->SetLineStyle(2); 
    l->SetLineColor(kGray+2); 
    // zdc plus
    TH1D* ratioPlus = (TH1D*)hZDCP_Emu->Clone("ratioPlus"); 
    ratioPlus->Divide(hZDCM_Emu); 
    ratioPlus->GetYaxis()->SetTitle("Ratio of Plus / Minus"); 
    ratioPlus->GetYaxis()->SetRangeUser(0.0,3.0);

    ratioPlus->Draw(); 
    l->Draw(); 
    leg->Draw("same");
    cms->Draw("same");
    c12->SaveAs(Form("Online_ZDCEmuRatio_%s.pdf", tag.c_str()));

         // ------------------------------------------
    /* ZDCCorr*/
    // ------------------------------------------

   
    
    TCanvas* cC = new TCanvas("cC","cC",600,600);
    cC->cd();
    cC->SetTickx(1);
    cC->SetTicky(1); 
    cC->SetLogz(1); 
    cC->SetTopMargin(0.09);
    cC->SetBottomMargin(0.11);
    cC->SetLeftMargin(0.11);
    cC->SetRightMargin(0.11);


    // zdc plus
    hZDCAsymCorr->GetXaxis()->SetTitle("ZDCp L1 sum");
    hZDCAsymCorr->GetYaxis()->SetTitle("ZDCm L1 sum");

    hZDCAsymCorr->Draw("colz");
    // asymm->Draw("same");  
    //leg->Draw("same");
    cms2->Draw("same");
    cC->SaveAs(Form("Online_CorrAsymm_%s.pdf", tag.c_str()));




         // ------------------------------------------
    /* ZDCCorrJet*/
    // ------------------------------------------

   
    
    TCanvas* cCj = new TCanvas("cCj","cCj",600,600);
    cCj->cd();
    cCj->SetTickx(1);
    cCj->SetTicky(1); 
    //cCj->SetLogz(1); 
    cCj->SetTopMargin(0.09);
    cCj->SetBottomMargin(0.11);
    cCj->SetLeftMargin(0.15);
    cCj->SetRightMargin(0.11);


    // zdc plus
    hZDCAsymCorrJet->GetYaxis()->SetTitle("(ZDCp - ZDCm)/(ZDCp + ZDCm)");
    hZDCAsymCorrJet->GetXaxis()->SetTitle("Jet Eta");

    hZDCAsymCorrJet->Draw("colz");
    // asymm->Draw("same");  
    //leg->Draw("same");
    cms2->Draw("same");
    cCj->SaveAs(Form("Online_CorrAsymmJet_%s.pdf", tag.c_str()));

      // ------------------------------------------
    /* ZDCAsymm */
    // ------------------------------------------

   
    
    TCanvas* cA = new TCanvas("cA","cA",600,600);
    cA->cd();
    cA->SetTickx(1);
    cA->SetTicky(1);
    //cA->SetLogy(); 
    cA->SetTopMargin(0.09);
    cA->SetBottomMargin(0.11);
    cA->SetLeftMargin(0.09);
    cA->SetRightMargin(0.05);


    TLatex* asymm = new TLatex(0.19,0.8,Form("#mu : %0.2f", hZDC_Asymm->GetMean()));
    asymm->SetNDC();
    asymm->SetTextSize(0.035);
    asymm->SetTextFont(42);

    

    TLatex* lumi = new TLatex(0.19,0.7,"Run: 399572, Fill: 11303, nBunches: 374 ");
    lumi->SetNDC();
    lumi->SetTextSize(0.035);
    lumi->SetTextFont(42);

    // zdc plus
    hZDC_Asymm->SetLineColor(kRed);
    hZDC_Asymm->SetLineWidth(2);
    hZDC_Asymm->GetXaxis()->SetTitleSize(0.05);
    hZDC_Asymm->SetMarkerStyle(20);
    hZDC_Asymm->GetXaxis()->SetTitle("(ZDCp - ZDCm)/(ZDCp + ZDCm)");


    hZDC_Asymm->Draw();
    asymm->Draw("same"); 
    lumi->Draw("same");  
    //leg->Draw("same");
    cms2->Draw("same");
    cA->SaveAs(Form("Online_Asymm_%s.pdf", tag.c_str()));

    // ------------------------------------------
    /* Online to GeV */
    // ------------------------------------------

    TLegend* leg2 = new TLegend(0.4,0.7,0.6,0.85);
    leg2->SetBorderSize(0);
    leg2->SetFillStyle(0);
    leg2->SetTextSize(0.045);
    
    TCanvas* c2 = new TCanvas("c2","c2",800,600);
    c2->cd();
    c2->SetTickx(1);
    c2->SetTicky(1);
    c2->SetLogy(); 
    c2->SetTopMargin(0.09);
    c2->SetBottomMargin(0.11);
    c2->SetLeftMargin(0.09);
    c2->SetRightMargin(0.05);

    // zdc plus
    hZDCP_withTrig->SetLineColor(kRed);
    hZDCP_withTrig->SetLineWidth(2);
    hZDCP_withTrig->GetXaxis()->SetTitleSize(0.05);
    hZDCP_withTrig->SetMarkerStyle(20);

    TF1* fit1n = new TF1("fit1n", "gaus", 1000, 3000);
    fit1n->SetLineColor(kBlack);
    fit1n->SetLineWidth(2);
    fit1n->SetLineStyle(2);
    fit1n->SetRange(0.,6000);
    hZDCP_withTrig->Fit(fit1n, "0", "", 1000, 3000);

    TF1* fit1nM = new TF1("fit1nM", "gaus",  1000, 3000);
    fit1nM->SetLineColor(kGray+2);
    fit1nM->SetLineWidth(2);
    fit1nM->SetLineStyle(2);
    fit1nM->SetRange(0.,6000);
    hZDCM_withTrig->Fit(fit1nM, "0", "", 1000, 3000);

    // zdc minus
    hZDCM_withTrig->SetLineColor(kBlue);
    hZDCM_withTrig->SetLineWidth(2);
    hZDCM_withTrig->SetMarkerStyle(20);
    hZDCM_withTrig->GetXaxis()->SetTitle("ZDC Offline Energy Sum (GeV)");
    hZDCM_withTrig->GetXaxis()->SetTitleSize(0.05);
    hZDCM_withTrig->GetXaxis()->SetRangeUser(0, 10000);
    hZDCM_withTrig->GetYaxis()->SetRangeUser(1, 1e5);
    hZDCM_withTrig->Draw();
    hZDCP_withTrig->Draw("same");
    // std::cout << "Integral Plus: " << hZDCP_withTrig->Integral() << std::endl;
    // std::cout << "Integral Minus: " << hZDCM_withTrig->Integral() << std::endl;

    leg2->AddEntry(hZDCP_withTrig,"ZDC Plus ","l");
    leg2->AddEntry(hZDCM_withTrig,"ZDC Minus","l");
    leg2->Draw("same");
    cms->Draw("same");
    fit1n->Draw("same"); 
    fit1nM->Draw("same");
    c2->SaveAs(Form("Online_ZDCNeutronWithTrig_%s.pdf", tag.c_str()));


   // ------------------------------------------
    /* ratio */
    // ------------------------------------------
    TH1D* clonePlusHist = (TH1D*)hZDCP_withTrig->Clone("numeratorPlus");
    TH1D* cloneMinusHist = (TH1D*)hZDCM_withTrig->Clone("numeratorMinus");

    TGraphAsymmErrors clonePlus(clonePlusHist, hZDCP, "cl=0.683 b(1,1) mode");
    TGraphAsymmErrors cloneMinus(cloneMinusHist, hZDCM, "cl=0.683 b(1,1) mode");


    TLegend* leg4 = new TLegend(0.3,0.2,0.8,0.3);
    leg4->SetBorderSize(0);
    leg4->SetFillStyle(0);
    leg4->SetTextSize(0.045);

    TCanvas* c4 = new TCanvas("c4","c4",800,600);
    c4->cd();
    c4->SetTickx(1);
    c4->SetTicky(1);
    c4->SetTopMargin(0.09);
    c4->SetBottomMargin(0.11);
    c4->SetLeftMargin(0.09);
    c4->SetRightMargin(0.05);
    clonePlus.SetLineWidth(2);
    cloneMinus.SetLineWidth(2);
    clonePlus.SetLineStyle(1);
    clonePlus.SetMarkerStyle(20);
    cloneMinus.SetMarkerStyle(20);
    cloneMinus.SetMarkerColor(kBlue);
    clonePlus.SetMarkerColor(kRed);
    cloneMinus.SetLineColor(kBlue);
    clonePlus.SetLineColor(kRed);
    clonePlus.GetXaxis()->SetTitle("ZDC Offline Energy Sum (GeV)");
    clonePlus.GetYaxis()->SetTitle("Efficiency");

    leg4->AddEntry(&clonePlus, "ZDC plus", "lp");
    leg4->AddEntry(&cloneMinus, "ZDC minus", "lp");

    cloneMinus.SetLineStyle(1);
    clonePlus.GetYaxis()->SetRangeUser(0, 1.1);
    clonePlus.GetXaxis()->SetRangeUser(0, 10000);
    clonePlus.Draw("");
    cloneMinus.Draw("lp same");
    cms->Draw("same");
    leg4->Draw("same"); 
    c4->SaveAs(Form("TurnOn_%s.pdf", tag.c_str()));


  return 1;
}

int main(int argc, char *argv[]) {
  if (argc == 2)
    return plotZDCEmu(argv[1]);
  else {
    cout << "ERROR" << endl;
    return -1;
  }
}
