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


TChain *CreateChain(string inFile, const char* treeName){
  TChain* chain = new TChain(treeName);//declares a TChain called chain where a tree name is fed into the argument

  chain->Add(inFile.c_str());
  return chain;
}



void plotTurnOnCurve_ZDC(){
    string infile = "/Users/hannahbossi/Documents/LocalCode/RunPrep/macros/ZDCTurnON/ZDCTurnOn_TS100.root"; 
    string tag = "TS100"; 
    int lowerThreshold = 22;

    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);

    // ZDC unpacker
    TChain* outChain =  CreateChain(infile, "outTree");  
    TTreeReader outReader(outChain);
    TTreeReaderValue<double> unpackerSumM(outReader, "unpacker_zdcm_energy");
    TTreeReaderValue<double> unpackerSumP(outReader, "unpacker_zdcp_energy");
    TTreeReaderValue<double> offlineEnergyM(outReader, "zdcm_Energy");
    TTreeReaderValue<double> offlineEnergyP(outReader, "zdcp_Energy");
    TTreeReaderValue<bool> isL1ZDCM22(outReader, "l1_ZDCM22");
    TTreeReaderValue<bool> isL1ZDCP22(outReader, "l1_ZDCP22");
    TTreeReaderValue<bool> isL1ZDCM80(outReader, "l1_ZDCM80");
    TTreeReaderValue<bool> isL1ZDCP80(outReader, "l1_ZDCP80");
    TTreeReaderValue<bool> isL1ZDCM133(outReader, "l1_ZDCM133");
    TTreeReaderValue<bool> isL1ZDCP133(outReader, "l1_ZDCP133");

    TTreeReaderValue<int> hfSum(outReader, "hfSum");


    TH1D* hZDCP = new TH1D("hZDCP", "ZDC Plus", 100, 0, 10000);
    TH1D* hZDCM = new TH1D("hZDCM", "ZDC Minus", 100, 0, 10000);


    TH1D* hZDCP_NotTriggered = new TH1D("hZDCPNotTrig", "ZDC Plus Not Triggered", 100, 0, 10000);
    TH1D* hZDCM_NotTriggered = new TH1D("hZDCMNotTrig", "ZDC Minus Not Triggered", 100, 0, 10000);

    TH1D* hZDCP22 = new TH1D("hZDCP22", "ZDC Plus 22", 100, 0, 10000);
    TH1D* hZDCM22 = new TH1D("hZDCM22", "ZDC Minus 22", 100, 0, 10000);


    TH1D* hZDCP80= new TH1D("hZDCP80", "ZDC Plus 80", 100, 0, 10000);
    TH1D* hZDCM80 = new TH1D("hZDCM80", "ZDC Minus 80", 100, 0, 10000);


    TH1D* hZDCP133= new TH1D("hZDCP133", "ZDC Plus 133", 100, 0, 10000);
    TH1D* hZDCM133 = new TH1D("hZDCM133", "ZDC Minus 133", 100, 0, 10000);

    TH2D* hHFSumZDCSum = new TH2D("hHFSumZDCSum", "HF Sum vs ZDC Sum", 60, 0, 120, 50, 0, 10000);
  


    bool doDebug = false;

    // loop over trees and fill the histograms
    Long64_t totalEvents = outReader.GetEntries(true);
    for (Long64_t i = 0; i < totalEvents; i++) {
      outReader.Next();
      if (i % 100000 == 0) {
        cout << "Processing event " << i << " out of " << totalEvents << endl;
      }
      if(doDebug){
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
        std::cout << "ZDCP: " << *unpackerSumP << std::endl;
        std::cout << "ZDCM: " << *unpackerSumM << std::endl;
        std::cout << "ZDCP: " << *offlineEnergyP << std::endl;
        std::cout << "ZDCM: " << *offlineEnergyM << std::endl;
        std::cout << "ZDCP22: " << *isL1ZDCP22 << std::endl;
        std::cout << "ZDCM22: " << *isL1ZDCM22 << std::endl;
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
      }
   
  
      /* ZDC Plus and Minus Energy Sums */
      hZDCP->Fill(*offlineEnergyP);
      hZDCM->Fill(*offlineEnergyM);

      hHFSumZDCSum->Fill(*hfSum, *offlineEnergyM + *offlineEnergyP);
    


      //if(!*isL1ZDCP22){
      if(*unpackerSumP < 22){
        hZDCP_NotTriggered->Fill(*offlineEnergyP);
      }
      //if(!*isL1ZDCM22){
      if(*unpackerSumM < lowerThreshold){
        hZDCM_NotTriggered->Fill(*offlineEnergyM);
      }
  
      /* ZDC 1n Thresholds */
      //if (*isL1ZDCP22) {
      if (*unpackerSumP > 22) {
        hZDCP22->Fill(*offlineEnergyP);
      }
      //if (*isL1ZDCM22) {
      if (*unpackerSumM > lowerThreshold) {
        hZDCM22->Fill(*offlineEnergyM);
      }

      /* ZDC 2n Thresholds */
      //if (*isL1ZDCP80) {
      if (*unpackerSumP > 80) {
        hZDCP80->Fill(*offlineEnergyP);
      }
      //if (*isL1ZDCM80) {
      if (*unpackerSumM > 80) {
        hZDCM80->Fill(*offlineEnergyM);
      }

      /* ZDC 3n Thresholds */
      //if (*isL1ZDCP133) {
      if (*unpackerSumP > 133) {
        hZDCP133->Fill(*offlineEnergyP);
      }
      //if (*isL1ZDCM133) {
      if (*unpackerSumM > 133) {
        hZDCM133->Fill(*offlineEnergyM);
      }


    }

    // ------------------------------------------
    /* Now do the plotting */
    // ------------------------------------------

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
    c3->SetTopMargin(0.05);
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
    c3->SaveAs(Form("UnpackerCut_ZDCNeutronDistributions_%s.pdf", tag.c_str()));

    // ------------------------------------------
    /* ZDC 1n Threshold */
    // ------------------------------------------

    TLegend* leg2 = new TLegend(0.65,0.7,0.8,0.85);
    leg2->SetBorderSize(0);
    leg2->SetFillStyle(0);
    leg2->SetTextSize(0.045);
    
    TCanvas* c2 = new TCanvas("c2","c2",800,600);
    c2->cd();
    c2->SetTickx(1);
    c2->SetTicky(1);
    c2->SetLogy(); 
    c2->SetTopMargin(0.05);
    c2->SetBottomMargin(0.11);
    c2->SetLeftMargin(0.09);
    c2->SetRightMargin(0.05);

    // zdc plus
    hZDCP22->SetLineColor(kRed);
    hZDCP22->SetLineWidth(2);
    hZDCP22->SetMarkerStyle(20);
    hZDCP22->GetXaxis()->SetTitle("ZDC Energy Sum (GeV)");
  

    // zdc minus
    hZDCM22->SetLineColor(kBlue);
    hZDCM22->SetLineWidth(2);
    hZDCM22->SetMarkerStyle(20);
    hZDCM22->GetXaxis()->SetTitle("ZDC Energy Sum (GeV)");
    hZDCM22->GetXaxis()->SetTitleSize(0.05);
    hZDCM22->GetYaxis()->SetRangeUser(0.1,1000);
    hZDCM22->Draw();
    hZDCP22->Draw("same");
    leg2->AddEntry(hZDCP22,"ZDC Plus 22","l");
    leg2->AddEntry(hZDCM22,"ZDC Minus 22","l");
    leg2->Draw("same");
    c2->SaveAs(Form("UnpackerCut_ZDC1nDistributions_22ThresholdTest_15ThresholdTest_%s.pdf", tag.c_str()));


    // ------------------------------------------
    /* ZDC 2n Threshold */
    // ------------------------------------------

    TLegend* leg = new TLegend(0.65,0.7,0.8,0.85);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->SetTextSize(0.045);


    
    TCanvas* c1 = new TCanvas("c1","c1",800,600);
    c1->cd();
    c1->SetTickx(1);
    c1->SetTicky(1);
    c1->SetLogy(); 

    c1->SetTopMargin(0.05);
    c1->SetBottomMargin(0.11);
    c1->SetLeftMargin(0.09);
    c1->SetRightMargin(0.05);

    // zdc plus
    hZDCP80->SetLineColor(kRed);
    hZDCP80->SetLineWidth(2);
    hZDCP80->SetMarkerStyle(20);
    hZDCP80->GetXaxis()->SetTitle("ZDC Energy Sum (GeV)");
  

    // zdc minus
    hZDCM80->SetLineColor(kBlue);
    hZDCM80->SetLineWidth(2);
    hZDCM80->SetMarkerStyle(20);
    hZDCM80->GetXaxis()->SetTitle("ZDC Energy Sum (GeV)");
    hZDCM80->GetXaxis()->SetTitleSize(0.05);
    hZDCM80->GetYaxis()->SetRangeUser(0.1,1000);
    hZDCM80->Draw();
    hZDCP80->Draw("same");
    leg->AddEntry(hZDCP80,"ZDC Plus 80","l");
    leg->AddEntry(hZDCM80,"ZDC Minus 80","l");
    leg->Draw("same");
    c1->SaveAs(Form("UnpackerCut_ZDC2nDistributions_80ThresholdTest_%s.pdf", tag.c_str()));


    // ------------------------------------------
    /* ZDC 3n Threshold */
    // ------------------------------------------

    TLegend* leg4 = new TLegend(0.65,0.7,0.8,0.85);
    leg4->SetBorderSize(0);
    leg4->SetFillStyle(0);
    leg4->SetTextSize(0.045);


    
    TCanvas* c4 = new TCanvas("c4","c4",800,600);
    c4->cd();
    c4->SetTickx(1);
    c4->SetTicky(1);
    c4->SetLogy(); 

    c4->SetTopMargin(0.05);
    c4->SetBottomMargin(0.11);
    c4->SetLeftMargin(0.09);
    c4->SetRightMargin(0.05);

    // zdc plus
    hZDCP133->SetLineColor(kRed);
    hZDCP133->SetLineWidth(2);
    hZDCP133->SetMarkerStyle(20);
    hZDCP133->GetXaxis()->SetTitle("ZDC Energy Sum (GeV)");
  

    // zdc minus
    hZDCM133->SetLineColor(kBlue);
    hZDCM133->SetLineWidth(2);
    hZDCM133->SetMarkerStyle(20);
    hZDCM133->GetXaxis()->SetTitle("ZDC Energy Sum (GeV)");
    hZDCM133->GetXaxis()->SetTitleSize(0.05);
    hZDCM133->GetYaxis()->SetRangeUser(0.1,1000);
    hZDCM133->Draw();
    hZDCP133->Draw("same");
    leg4->AddEntry(hZDCP133,"ZDC Plus 133","l");
    leg4->AddEntry(hZDCM133,"ZDC Minus 133","l");
    leg4->Draw("same");
    c4->SaveAs(Form("UnpackerCut_ZDC3nDistributions_133ThresholdTest_%s.pdf", tag.c_str()));


    // ------------------------------------------
    /* ZDC Sum Plus Stacked Threshold */
    // ------------------------------------------
       
    TCanvas* c5 = new TCanvas("c5","c5",800,600);
    c5->cd();
    c5->SetTickx(1);
    c5->SetTicky(1);
    c5->SetLogy(); 

    hZDCP->Draw();
    TH1D* hZDCP_22_copy = (TH1D*)hZDCP22->Clone();
    hZDCP_22_copy->SetName("hZDCP_22_copy"); 
    hZDCP_22_copy->SetLineColor(kViolet-2); 
    hZDCP_22_copy->Draw("same");

    TH1D* hZDCP_80_copy = (TH1D*)hZDCP80->Clone();
    hZDCP_80_copy->SetName("hZDCP_80_copy");
    hZDCP_80_copy->SetLineColor(kGreen+2);
    hZDCP_80_copy->Draw("same");
    
    TH1D* hZDCP_133_copy = (TH1D*)hZDCP133->Clone();
    hZDCP_133_copy->SetName("hZDCP_133_copy");
    hZDCP_133_copy->SetLineColor(kAzure-2);
    hZDCP_133_copy->Draw("same");

    TLegend* leg5 = new TLegend(0.65,0.7,0.8,0.85);
    leg5->SetBorderSize(0);
    leg5->SetFillStyle(0);
    leg5->SetTextSize(0.045);
    leg5->AddEntry(hZDCP,"ZDC Plus","l");
    leg5->AddEntry(hZDCP_22_copy,"ZDC Plus 22","l");
    leg5->AddEntry(hZDCP_80_copy,"ZDC Plus 80","l");
    leg5->AddEntry(hZDCP_133_copy,"ZDC Plus 133","l");
    leg5->Draw("same");
    c5->SaveAs(Form("UnpackerCut_ZDCPlusStackedThresholds_%s.pdf", tag.c_str()));

    // ------------------------------------------
    /* ZDC Sum Minus Stacked Threshold */
    // ------------------------------------------

    TCanvas* c6 = new TCanvas("c6","c6",800,600);
    c6->cd();
    c6->SetTickx(1);
    c6->SetTicky(1);
    c6->SetLogy();

    hZDCM->Draw();
    TH1D* hZDCM_22_copy = (TH1D*)hZDCM22->Clone();
    hZDCM_22_copy->SetName("hZDCM_22_copy");
    hZDCM_22_copy->SetLineColor(kViolet-2);
    hZDCM_22_copy->Draw("same");

    TH1D* hZDCM_80_copy = (TH1D*)hZDCM80->Clone();
    hZDCM_80_copy->SetName("hZDCM_80_copy");
    hZDCM_80_copy->SetLineColor(kGreen+2);
    hZDCM_80_copy->Draw("same");

    TH1D* hZDCM_133_copy = (TH1D*)hZDCM133->Clone();
    hZDCM_133_copy->SetName("hZDCM_133_copy");
    hZDCM_133_copy->SetLineColor(kAzure-2);
    hZDCM_133_copy->Draw("same");

    TLegend* leg6 = new TLegend(0.65,0.7,0.8,0.85);
    leg6->SetBorderSize(0);
    leg6->SetFillStyle(0);
    leg6->SetTextSize(0.045);
    leg6->AddEntry(hZDCM,"ZDC Minus","l");
    leg6->AddEntry(hZDCM_22_copy,"ZDC Minus 22","l");
    leg6->AddEntry(hZDCM_80_copy,"ZDC Minus 80","l");
    leg6->AddEntry(hZDCM_133_copy,"ZDC Minus 133","l");
    leg6->Draw("same");
    c6->SaveAs(Form("UnpackerCut_ZDCMinusStackedThresholds_%s.pdf",  tag.c_str()));


    // ------------------------------------------
    /* ZDC Plus and Minus Not Triggered */
    // ------------------------------------------

    TLegend* leg7 = new TLegend(0.45,0.7,0.6,0.85);
    leg7->SetBorderSize(0);
    leg7->SetFillStyle(0);
    leg7->SetTextSize(0.045);
    
    TCanvas* c7 = new TCanvas("c7","c7",800,600);
    c7->cd();
    c7->SetTickx(1);
    c7->SetTicky(1);
    c7->SetLogy(); 
    c7->SetTopMargin(0.05);
    c7->SetBottomMargin(0.11);
    c7->SetLeftMargin(0.09);
    c7->SetRightMargin(0.05);

    // zdc plus
    hZDCP_NotTriggered->SetLineColor(kRed);
    hZDCP_NotTriggered->SetLineWidth(2);
    hZDCP_NotTriggered->GetXaxis()->SetTitleSize(0.05);
    hZDCP_NotTriggered->SetMarkerStyle(20);
    hZDCP_NotTriggered->GetXaxis()->SetTitle("ZDC Energy Sum (GeV)");
  

    // zdc minus
    hZDCM_NotTriggered->SetLineColor(kBlue);
    hZDCM_NotTriggered->SetLineWidth(2);
    hZDCM_NotTriggered->SetMarkerStyle(20);
    hZDCM_NotTriggered->GetXaxis()->SetTitle("ZDC Energy Sum (GeV)");
    hZDCM_NotTriggered->GetXaxis()->SetTitleSize(0.05);
    hZDCM_NotTriggered->Draw();
    hZDCP_NotTriggered->Draw("same");
    leg7->AddEntry(hZDCP_NotTriggered,"ZDC Plus Not Triggered","l");
    leg7->AddEntry(hZDCM_NotTriggered,"ZDC Minus Not Triggered","l");
    leg7->Draw("same");
    c7->SaveAs(Form("UnpackerCut_ZDCNoTriggerDistributions_%s.pdf", tag.c_str()));


     // ------------------------------------------
    /* HF Plus Sum vs ZDC Plus Sum */
    // ------------------------------------------

    // TCanvas* c8 = new TCanvas("c8","c8",800,600);
    // c8->cd();
    // c8->SetTickx(1);
    // c8->SetTicky(1);
    // c8->SetLogz();
    // // c8->SetLogx();
    // hHFSumZDCSum->GetYaxis()->SetTitle("ZDC Sum (GeV)");
    // hHFSumZDCSum->GetYaxis()->SetTitleOffset(1.5);
    // hHFSumZDCSum->GetXaxis()->SetTitle("HF Sum (GeV)");
    // hHFSumZDCSum->Draw("colz");
    // c8->SaveAs("HFSumZDCSum.pdf");






}
