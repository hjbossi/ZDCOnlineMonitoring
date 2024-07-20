/*
* plotZDCAnalyzer.C: Code to plot the sum plus and the sum minus from an l1ntuple (no jet info)
* Hannah Bossi, hannah.bossi@cern.ch
* 11/8/2023
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
#include "TF1.h"
#include "TLine.h"
#include "TLatex.h"

#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include <TROOT.h>
#include <TStyle.h>



#include <string>
#include <vector>
#include <iostream>

using namespace std;



// get the files from a specified input directory
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

// Fill a TChain from the specified files
void FillChain(TChain &chain, vector<string> &files) {
  for (auto file : files) {
    chain.Add(file.c_str());
  }
}


// main plotting macro
// Example Input file is a Zero Bias file located in the public directory of svmithi03
// should run out of the box on svmithi03
void plotZDCAnalyzer(string date, string tag){
  
  // plotting style
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  char const *input = "/eos/cms/store/group/phys_heavyions/hbossi/RunPrep/FrozenPerfPlots/ZBoutputFiles/"; 
  
  /* read in all files in the input folder */
  vector<string> files;
  GetFiles(input, files);
  

  /* read in ZDC information */  
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
    
  // /* read in emulated information */
  TChain emuChain("l1UpgradeEmuTree/L1UpgradeTree");
  FillChain(emuChain, files);
  TTreeReader emuReader(&emuChain);
  TTreeReaderValue<vector<float> > emuSum(emuReader, "sumZDCEt");
  TTreeReaderValue<vector<short>> emuType(emuReader, "sumZDCType"); 
  TTreeReaderValue<vector<float>>	emuBx(emuReader, "sumZDCBx");
  TTreeReaderValue<vector<float> > emuJetPt(emuReader, "jetEt");
  
  TChain trigChain("hltanalysis/HltTree");
  FillChain(trigChain, files);
  TTreeReader trigReader(&trigChain);
  TTreeReaderValue<int> zb(trigReader, "L1_ZeroBias");
  TTreeReaderValue<int> mb(trigReader, "L1_ZDC1n_OR_MinimumBiasHF1_AND_BptxAND");
  TTreeReaderValue<int> zdcOR(trigReader, "L1_ZDC1n_OR_BptxAND"); 
  
  TChain gtChain("l1uGTTree/L1uGTTree");
  FillChain(gtChain, files);
  TTreeReader gtReader(&gtChain);
  TTreeReaderValue<vector<bool>>  indexDecision(gtReader, "m_algoDecisionInitial");
  
  
  /* define the histograms */
  TH1D* hZDCP_Emu = new TH1D("hZDCP_Emu", "ZDC Plus Emulated", 50, 0, 100);
  TH1D* hZDCM_Emu = new TH1D("hZDCM_Emu", "ZDC Minus Emulated", 50, 0, 100);
  
  TH1D* hZDCP22_Emu = new TH1D("hZDCP22_Emu", "ZDC Plus 22 Emu", 50, 0, 100);
  TH1D* hZDCM22_Emu = new TH1D("hZDCP22_Emu", "ZDC Plus 22 Emu", 50, 0, 100);
  
  
  TH1D* hZDCP = new TH1D("hZDCP", "ZDC Plus", 100, 0, 8000);
  TH1D* hZDCM = new TH1D("hZDCM", "ZDC Minus", 100, 0, 8000);
  
  TH1D* hZDCP_16 = new TH1D("hZDCP_16", "ZDC Plus 16", 100, 0, 8000);
  TH1D* hZDCM_16 = new TH1D("hZDCM_16", "ZDC Minus 16", 100, 0, 8000);
  
  TH1D* hZDCP_AsymXOR = new TH1D("hZDCP_AsymXOR", "ZDC Asym XOR", 100, 0, 8000);
  TH1D* hZDCM_AsymXOR = new TH1D("hZDCM_AsymXOR", "ZDC Asym XOR", 100, 0, 8000);
  
  
  TH1D* hZDCP_AsymXOR_Jet8 = new TH1D("hZDCP_AsymXOR_Jet8", "ZDC Asym XOR - Jet 8", 100, 0, 8000);
  TH1D* hZDCM_AsymXOR_Jet8 = new TH1D("hZDCM_AsymXOR_Jet8", "ZDC Asym XOR - Jet 8", 100, 0, 8000);
  
  TH2D* hZDCP_corr = new TH2D("hZDCP_corr", "ZDC Plus Correlation", 50, 0, 100, 100, 0, 8000);
  
  Long64_t totalEvents = emuReader.GetEntries(true);
  int ZDCORcounts = 0;
  int ZDCAsymmXORcounts = 0;
  int ZDCAsymmXOR_Jet8counts = 0;
  int ZDCAsymmXOR_Jet12counts = 0;
  int ZDCAsymmXOR_Jet16counts = 0;
  int ZDCAsymmXOR_Jet20counts = 0;
  int ZDCAsymmXOR_Jet24counts = 0;
  int ZDCAsymmXOR_Jet28counts = 0;
  int counter_MB_selected = 0; 
  int onlineZDCMB = 0; 
  int onlineZDCOR = 0; 
  int onlineZB = 0; 
  for (Long64_t i = 0; i < totalEvents; i++) {
    emuReader.Next(); zdcReader.Next(); trigReader.Next(); gtReader.Next();
    
    float emuPlus = (*emuSum)[4]*2;
    float emuMinus = (*emuSum)[5]*2; 
    
    hZDCP_Emu->Fill(emuPlus);
    hZDCM_Emu->Fill(emuMinus);
    
    // fill the histograms based on the L1 uGT decision
    if((*indexDecision)[448] == 1){
      hZDCP22_Emu->Fill(emuPlus);
    }
    if((*indexDecision)[450] == 1){
      hZDCM22_Emu->Fill(emuMinus);
    }
    
    hZDCP->Fill(*sumPlus);
    hZDCM->Fill(*sumMinus);
    
    hZDCP_corr->Fill(emuPlus, *sumPlus);
    
    if(*zb == 1)onlineZB++;
    if(*mb == 1)onlineZDCMB++;
    if(*zdcOR == 1)onlineZDCOR++;
    

    float emuMaxJetPt = -999;
    float totl1jets = totl1jets + (*emuJetPt).size();
    /* iterate through emu jets and find matched and unmatched jets with max pT */
    for (size_t j = 0; j < (*emuJetPt).size(); ++j) {
      if ((*emuJetPt)[j] > emuMaxJetPt) {
	emuMaxJetPt = (*emuJetPt)[j];
      }
    }
    

      
    //std:: cout << emuPlus << std::endl;
      
    /*ZDC Asymm XOR*/
    int lowCut  = 16;
    int highCut = 28;  
    if(emuPlus > lowCut && emuMinus < highCut){
      hZDCP_AsymXOR->Fill(*sumPlus);
      if(emuMaxJetPt > 8){
	hZDCP_AsymXOR_Jet8->Fill(*sumPlus);
      }
      
    }
    if(emuPlus < highCut && emuMinus > lowCut){
      hZDCM_AsymXOR->Fill(*sumMinus);
      if(emuMaxJetPt > 8){
	hZDCM_AsymXOR_Jet8->Fill(*sumMinus);
      }
    }

    if((emuPlus > lowCut && emuMinus < highCut) || (emuPlus < highCut && emuMinus > lowCut)){
      ZDCAsymmXORcounts++;
    }

    /*~~~~~~~ ZDC Asymm XOR + Jet ~~~~~~*/
    if((emuPlus > lowCut && emuMinus < highCut) || (emuPlus < highCut && emuMinus > lowCut)){
      if(emuMaxJetPt > 8)ZDCAsymmXOR_Jet8counts++;
      if(emuMaxJetPt > 12)ZDCAsymmXOR_Jet12counts++;
      if(emuMaxJetPt > 16)ZDCAsymmXOR_Jet16counts++;
      if(emuMaxJetPt > 20)ZDCAsymmXOR_Jet20counts++;
      if(emuMaxJetPt > 24)ZDCAsymmXOR_Jet24counts++;
      if(emuMaxJetPt > 28)ZDCAsymmXOR_Jet28counts++;
    }
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~*/


    if(emuPlus > 16)hZDCP_16->Fill(*sumPlus);
    if(emuMinus> 16)hZDCM_16->Fill(*sumMinus);

    /* ZDCOR counts */
    if(emuPlus > 16 || emuMinus > 16){
      ZDCORcounts++;
      
    }
    

  } //end loop over the events 
  /* print out summary information */
  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl; 
  std::cout << "Total Events: " << totalEvents << std::endl;
  std::cout << "ZDC OR Rate/ ZB Rate: " << float(ZDCORcounts)/float(totalEvents) << std::endl;
  std::cout << "MB Rate/ ZB Rate: " << float(counter_MB_selected)/float(totalEvents) << std::endl;
  std::cout << "ZDC Asymm OR Rate /ZB Rate: " << float(ZDCAsymmXORcounts)/float(totalEvents) << std::endl;
  std::cout << "ZDC Asymm OR Rate + Jet 8 /ZB Rate: " << float(ZDCAsymmXOR_Jet8counts)/float(totalEvents) << std::endl;
  std::cout << "ZDC Asymm OR Rate + Jet 12 /ZB Rate: " << float(ZDCAsymmXOR_Jet12counts)/float(totalEvents) << std::endl;
  std::cout << "ZDC Asymm OR Rate + Jet 16 /ZB Rate: " << float(ZDCAsymmXOR_Jet16counts)/float(totalEvents) << std::endl;
  std::cout << "ZDC Asymm OR Rate + Jet 20 /ZB Rate: " << float(ZDCAsymmXOR_Jet20counts)/float(totalEvents) << std::endl;
  std::cout << "ZDC Asymm OR Rate + Jet 24 /ZB Rate: " << float(ZDCAsymmXOR_Jet24counts)/float(totalEvents) << std::endl;
  std::cout << "ZDC Asymm OR Rate + Jet 28 /ZB Rate: " << float(ZDCAsymmXOR_Jet28counts)/float(totalEvents) << std::endl;
  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
  std::cout << "Online Triggered stats " << std::endl;
  std::cout << "ZB Counts: " <<  onlineZB << std::endl;
  std::cout << "ZDC MB Counts: " <<  onlineZDCMB << std::endl;
  std::cout << "ZDC OR Counts: " <<  onlineZDCOR << std::endl; 
  TLatex* cms = new TLatex(0.10,0.92,"#bf{CMS} #it{Preliminary} Run 375549");
  cms->SetNDC();
  cms->SetTextSize(0.05);
  cms->SetTextFont(42);
  
  /*-----------------------------------------------------------*/
  // plot emulated values
  /* ----------------------------------------------------------*/
  TLegend* leg4 = new TLegend(0.71,0.7,0.9,0.8);
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
  
  // create tlatex for Time slice label
  TLatex* ts = new TLatex(0.71,0.82,"#bf{TS2 - 0.4*TS1}");
  ts->SetNDC();
  ts->SetTextSize(0.05);
  ts->SetTextFont(42);
  

  // zdc plus
  hZDCP_Emu->SetLineColor(kRed);
  hZDCP_Emu->SetLineWidth(2);
  hZDCP_Emu->GetXaxis()->SetTitleSize(0.05);
  hZDCP_Emu->SetMarkerStyle(20);
  hZDCP_Emu->GetXaxis()->SetTitle("ZDC Energy Sum (au.)");

  // zdc minus
  hZDCM_Emu->SetLineColor(kBlue);
  hZDCM_Emu->SetLineWidth(2);
  hZDCM_Emu->SetMarkerStyle(20);
  hZDCM_Emu->GetXaxis()->SetTitle("ZDC Energy Sum (au.)");
  hZDCM_Emu->GetXaxis()->SetTitleSize(0.05);
  hZDCM_Emu->Draw();
  hZDCP_Emu->Draw("same");
  leg4->AddEntry(hZDCP_Emu,"ZDC Plus","l");
  leg4->AddEntry(hZDCM_Emu,"ZDC Minus","l");
  leg4->Draw("same");
  cms->Draw("same");
  ts->Draw("same"); 
  c4->SaveAs(Form("./figures/%s/ZDCNeutronDistributionsEmulated_%s.pdf", date.c_str(), tag.c_str()));


 
    /*--------------------------------------------------------*/
    /* plot offline sums*/
   /*--------------------------------------------------------*/
    TLegend* leg1 = new TLegend(0.71,0.3,0.9,0.4);
    leg1->SetBorderSize(0);
    leg1->SetFillStyle(0);
    leg1->SetTextSize(0.045);


    TCanvas* c1 = new TCanvas("c1","c1",800,600);
    c1->cd();
    c1->SetTickx(1);
    c1->SetTicky(1);
    c1->SetLogy();
    c1->SetTopMargin(0.09);
    c1->SetBottomMargin(0.11);
    c1->SetLeftMargin(0.09);
    c1->SetRightMargin(0.05);

    // zdc plus
    hZDCP->SetLineColor(kRed);
    hZDCP->SetLineWidth(2);
    hZDCP->GetXaxis()->SetTitleSize(0.05);
    hZDCP->SetMarkerStyle(20);
    hZDCP->GetXaxis()->SetTitle("ZDC Energy Sum (GeV))");

    TLatex* ts2 = new TLatex(0.71,0.42,"#bf{TS2 - TS1}");
    ts2->SetNDC();
    ts2->SetTextSize(0.05);
    ts2->SetTextFont(42);

    // add a fit to the 1n peak centered around 2650 and with a width of 200
    TF1* fit1n = new TF1("fit1n", "gaus", 1000, 4000);
    fit1n->SetLineColor(kBlack);
    fit1n->SetLineWidth(2);
    fit1n->SetLineStyle(2);
    fit1n->SetRange(0.,4500);
    hZDCP->Fit(fit1n, "0", "", 1000, 4000);

    // print the fit parameters
    std::cout << "-----------------------------------------------------------------" << std::endl;
    std::cout << "1n Fit Parameters: " << std::endl;
    std::cout << "Mean: " << fit1n->GetParameter(1) << std::endl;
    std::cout << "Sigma: " << fit1n->GetParameter(2) << std::endl;
    float intFullPlus = fit1n->Integral(600, 4500); 
    float intPartialPlus = fit1n->Integral(1000, 4500);
    std::cout << "Integral over whole peak: " << intFullPlus << std::endl;
    std::cout << "Integral over efficient region: " << intPartialPlus << std::endl;
    std::cout << "Capturing " << (intPartialPlus/intFullPlus)*100 << "% of the 1n peak" << std::endl;
    std::cout << "-----------------------------------------------------------------" << std::endl;


    // do the same for the minus 
    TF1* fit1nM = new TF1("fit1nM", "gaus",  1000, 4500);
    fit1nM->SetLineColor(kGray+2);
    fit1nM->SetLineWidth(2);
    fit1nM->SetLineStyle(2);
    fit1nM->SetRange(0.,5000);
    hZDCM->Fit(fit1nM, "0", "", 1000, 4500);

    // print the fit parameters
    std::cout << "-----------------------------------------------------------------" << std::endl;
    std::cout << "1n Fit Parameters: " << std::endl;
    std::cout << "Mean: " << fit1nM->GetParameter(1) << std::endl;
    std::cout << "Sigma: " << fit1nM->GetParameter(2) << std::endl;
    float intFull = fit1nM->Integral(600, 4500); 
    float intPartial = fit1nM->Integral(1400, 4500);
    std::cout << "Integral over whole peak: " << intFull << std::endl;
    std::cout << "Integral over efficient region: " << intPartial << std::endl;
    std::cout << "Capturing " << (intPartial/intFull)*100 << "% of the 1n peak" << std::endl;
    std::cout << "-----------------------------------------------------------------" << std::endl;

    // // add fit for the 2n peak 
    TF1* fit2n = new TF1("fit2n", "gaus", 4000, 6500);
    fit2n->SetLineColor(kBlack);
    fit2n->SetLineWidth(2);
    fit2n->SetLineStyle(2);
    fit2n->SetRange(1000.,10000);
    hZDCP->Fit(fit2n, "0+", "", 4000, 6500);

    TF1* fit2nM = new TF1("fit2nM", "gaus", 4500, 7000);
    fit2nM->SetLineColor(kGray+2);
    fit2nM->SetLineWidth(2);
    fit2nM->SetLineStyle(2);
    fit2nM->SetRange(1000.,10000);
    hZDCM->Fit(fit2nM, "0+", "", 4500, 7000);


    TF1* fit3n = new TF1("fit3n", "gaus", 7000, 8500);
    fit3n->SetLineColor(kBlack);
    fit3n->SetLineWidth(2);
    fit3n->SetLineStyle(2);
    fit3n->SetRange(2000.,12000);
    hZDCP->Fit(fit3n, "0+", "", 7000, 8500);

    TF1* fit3nM = new TF1("fit2nM", "gaus", 7500, 8500);
    fit3nM->SetLineColor(kGray+2);
    fit3nM->SetLineWidth(2);
    fit3nM->SetLineStyle(2);
    fit3nM->SetRange(1000.,12000);
    hZDCM->Fit(fit3nM, "0+", "", 7500, 8500);

    TF1* total_plus = new TF1("mstotal","gaus(0)+gaus(3)+gaus(6)",1000,12000);
    Double_t par[9];
    // Get the parameters from the fit
    fit1n->GetParameters(&par[0]);
    fit2n->GetParameters(&par[3]);
    fit3n->GetParameters(&par[6]);

    TF1* total_minus = new TF1("mstotal","gaus(0)+gaus(3)+gaus(6)",1000,12000);
    Double_t parM[9];
    // Get the parameters from the fit
    fit1nM->GetParameters(&parM[0]);
    fit2nM->GetParameters(&parM[3]);
    fit3nM->GetParameters(&parM[6]);

   // Use the parameters on the sum
   total_plus->SetParameters(par);
   total_plus->SetLineColor(kRed);
   total_plus->SetLineWidth(3);
   hZDCP->Fit(total_plus,"R+");

    total_minus->SetParameters(parM);
    total_minus->SetLineColor(kBlue);
    total_minus->SetLineWidth(3);
    hZDCM->Fit(total_minus,"R+");



    // create tlatex for fit parameters
    TLatex* fit1nMean = new TLatex(0.14,0.82,Form("ZDC Plus 1n,  #mu: %.2f GeV, #sigma: %.2f GeV", fit1n->GetParameter(1), fit1n->GetParameter(2)));
    fit1nMean->SetNDC();
    fit1nMean->SetTextSize(0.045);
    fit1nMean->SetTextFont(42);

    // do the same for the minus
    TLatex* fit1nMeanM = new TLatex(0.14,0.77,Form("ZDC Minus 1n,  #mu: %.2f GeV, #sigma: %.2f GeV", fit1nM->GetParameter(1), fit1nM->GetParameter(2)));
    fit1nMeanM->SetNDC();
    fit1nMeanM->SetTextSize(0.045);
    fit1nMeanM->SetTextFont(42);

    TLatex* fit2nMean = new TLatex(0.14,0.72,Form("ZDC Plus 2n,  #mu: %.2f GeV, #sigma: %.2f GeV", fit2n->GetParameter(1), fit2n->GetParameter(2)));
    fit2nMean->SetNDC();
    fit2nMean->SetTextSize(0.045);
    fit2nMean->SetTextFont(42);

    // do the same for the minus
    TLatex* fit2nMeanM = new TLatex(0.14,0.67,Form("ZDC Minus 2n,  #mu: %.2f GeV, #sigma: %.2f GeV", fit2nM->GetParameter(1), fit2nM->GetParameter(2)));
    fit2nMeanM->SetNDC();
    fit2nMeanM->SetTextSize(0.045);
    fit2nMeanM->SetTextFont(42);

    // do the same for the minus
    TLatex* fit3nMean = new TLatex(0.14,0.62,Form("ZDC Plus 3n,  #mu: %.2f GeV, #sigma: %.2f GeV", fit3n->GetParameter(1), fit3n->GetParameter(2)));
    fit3nMean->SetNDC();
    fit3nMean->SetTextSize(0.045);
    fit3nMean->SetTextFont(42);

    // do the same for the minus
    TLatex* fit3nMeanM = new TLatex(0.14,0.57,Form("ZDC Minus 3n,  #mu: %.2f GeV #sigma: %.2f GeV", fit3nM->GetParameter(1), fit3nM->GetParameter(2)));
    fit3nMeanM->SetNDC();
    fit3nMeanM->SetTextSize(0.045);
    fit3nMeanM->SetTextFont(42);





    // zdc minus
    hZDCM->SetLineColor(kBlue);
    hZDCM->SetLineWidth(2);
    hZDCM->SetMarkerStyle(20);
    hZDCM->GetXaxis()->SetTitle("ZDC Offline Energy Sum (GeV)");
    hZDCM->GetXaxis()->SetTitleSize(0.05);
    hZDCM->Draw();
    hZDCP->Draw("same");
    leg1->AddEntry(hZDCP,"ZDC Plus","l");
    leg1->AddEntry(hZDCM,"ZDC Minus","l");
    leg1->Draw("same");
    cms->Draw("same");
    ts2->Draw("same");
    fit1n->Draw("same");
    fit1nM->Draw("same");
    fit2n->Draw("same");
    fit2nM->Draw("same");
    fit3n->Draw("same");
    fit3nM->Draw("same");
    fit1nMean->Draw("same");
    fit1nMeanM->Draw("same");
    fit2nMean->Draw("same");
    fit2nMeanM->Draw("same");
    fit3nMean->Draw("same");
    fit3nMeanM->Draw("same");

    c1->SaveAs(Form("./figures/%s/Fit_ZDCNeutronDistributions_ZeroBiasWithLabel_v4_%s.pdf", date.c_str(), tag.c_str()));

  

  /*--------------------------------------------------------*/
  /*plot ZDC OR triggered distributions*/
  /*--------------------------------------------------------*/
  TLegend* leg5 = new TLegend(0.65,0.72,0.85,0.87);
  leg5->SetBorderSize(0);
  leg5->SetFillStyle(0);
  leg5->SetTextSize(0.045);
  
  
  TCanvas* c5 = new TCanvas("c5","c5",800,600);
  c5->cd();
  c5->SetTickx(1);
  c5->SetTicky(1);
  c5->SetTopMargin(0.09);
  c5->SetBottomMargin(0.11);
  c5->SetLeftMargin(0.09);
  c5->SetRightMargin(0.05);
  
  // zdc plus
  hZDCP_16->SetLineColor(kRed);
  hZDCP_16->SetLineWidth(2);
  hZDCP_16->GetXaxis()->SetTitleSize(0.05);
  hZDCP_16->SetMarkerStyle(20);
  hZDCP_16->SetMarkerColor(kRed);
  hZDCP_16->GetXaxis()->SetTitle("ZDC Offline Energy Sum (GeV)");
  
  // zdc minus
  hZDCM_16->SetLineColor(kBlue);
  hZDCM_16->SetLineWidth(2);
  hZDCM_16->SetMarkerStyle(20);
  hZDCM_16->SetMarkerColor(kBlue);
  hZDCM_16->GetXaxis()->SetTitle("ZDC Offline Energy Sum (GeV)");
  hZDCM_16->GetYaxis()->SetTitle("Efficiency");
  hZDCM_16->GetYaxis()->SetRangeUser(0.0, 1.4);
  hZDCM_16->GetXaxis()->SetTitleSize(0.05);
  hZDCM_16->Divide(hZDCM); 
  hZDCP_16->Divide(hZDCP); 
  hZDCM_16->Draw("cxp0");
  hZDCP_16->Draw("cxp0 same");
  
  // draw a dashed line at 1
  TLine* line = new TLine(0,1,8000,1);
  line->SetLineStyle(2);
  line->Draw("same");
  
  
  // create tlatex for Time slice label
  TLatex* onlinets = new TLatex(0.16,0.82,"#bf{Online: TS2 - 0.4*TS1}");
  onlinets->SetNDC();
  onlinets->SetTextSize(0.05);
  onlinets->SetTextFont(42);
  
  TLatex* offlinets = new TLatex(0.16,0.76,"#bf{Offline: TS2 - TS1}");
  offlinets->SetNDC();
  offlinets->SetTextSize(0.05);
  offlinets->SetTextFont(42);
  
  leg5->AddEntry(hZDCP_16,"ZDC Plus 16","l");
  leg5->AddEntry(hZDCM_16,"ZDC Minus 16","l");
  leg5->Draw("same");
  cms->Draw("same");
  onlinets->Draw("same");
  offlinets->Draw("same");
  c5->SaveAs(Form("./figures/%s/ZDC1nTurnOnEmulated_%s.pdf", date.c_str(), tag.c_str()));
  
  /*--------------------------------------------------------*/
  /* plot the sanity check of the emulated values*/
  /*--------------------------------------------------------*/
  TLegend* leg6 = new TLegend(0.45,0.7,0.65,0.85);
  leg6->SetBorderSize(0);
  leg6->SetFillStyle(0);
  leg6->SetTextSize(0.045);
  

  TCanvas* c6 = new TCanvas("c6","c6",800,600);
  c6->cd();
  c6->SetTickx(1);
  c6->SetTicky(1);
  c6->SetTopMargin(0.09);
  c6->SetBottomMargin(0.11);
  c6->SetLeftMargin(0.09);
  c6->SetRightMargin(0.05);
  
  // zdc plus
  hZDCP22_Emu->Divide(hZDCP_Emu);
  hZDCP22_Emu->SetLineColor(kRed);
  hZDCP22_Emu->SetLineWidth(2);
  hZDCP22_Emu->GetXaxis()->SetTitleSize(0.05);
  hZDCP22_Emu->SetMarkerStyle(20);
  hZDCP22_Emu->SetMarkerColor(kRed);
  hZDCP22_Emu->GetXaxis()->SetTitle("ZDC Energy Sum (1 count = 50 GeV)");
  hZDCP22_Emu->GetYaxis()->SetTitle("Efficiency");
  hZDCP22_Emu->Draw("same"); 
  
  // draw a dashed line at 1
  TLine* lineEmu = new TLine(0,1,100,1);
  lineEmu->SetLineStyle(2);
  lineEmu->Draw("same");
  


  leg6->AddEntry(hZDCP22_Emu,"ZDC Plus 22 - Trigger Bit 448","l");
  leg6->Draw("same");
  cms->Draw("same");
  c6->SaveAs(Form("./figures/%s/SanityCheck_ZDCPlus_%s.pdf", date.c_str(), tag.c_str()));
  /*--------------------------------------------------------*/
  
  /*--------------------------------------------------------*/
  /* plot the sanity check of the emulated values*/
  /*--------------------------------------------------------*/
  TLegend* leg7 = new TLegend(0.45,0.7,0.65,0.85);
  leg7->SetBorderSize(0);
  leg7->SetFillStyle(0);
  leg7->SetTextSize(0.045);
  
  
  TCanvas* c7 = new TCanvas("c7","c7",800,600);
  c7->cd();
  c7->SetTickx(1);
  c7->SetTicky(1);
  c7->SetTopMargin(0.09);
  c7->SetBottomMargin(0.11);
  c7->SetLeftMargin(0.09);
  c7->SetRightMargin(0.05);
  
  // zdc plus
  hZDCM22_Emu->Divide(hZDCM_Emu);
  hZDCM22_Emu->SetLineColor(kBlue);
  hZDCM22_Emu->SetLineWidth(2);
  hZDCM22_Emu->GetXaxis()->SetTitleSize(0.05);
  hZDCM22_Emu->SetMarkerStyle(20);
  hZDCM22_Emu->SetMarkerColor(kBlue);
  hZDCM22_Emu->GetXaxis()->SetTitle("ZDC Energy Sum (1 count = 50 GeV)");
  hZDCM22_Emu->GetYaxis()->SetTitle("Efficiency");
  hZDCM22_Emu->Draw("same"); 
  lineEmu->Draw("same");
  


  leg7->AddEntry(hZDCM22_Emu,"ZDC Minus 22 - Trigger Bit 450","l");
  leg7->Draw("same");
  cms->Draw("same");
  c7->SaveAs(Form("./figures/%s/SanityCheck_ZDCMinus_%s.pdf", date.c_str(), tag.c_str()));
  /*--------------------------------------------------------*/
  
  /*--------------------------------------------------------*/
  /* plot correlations between the online and emulated*/
  /*--------------------------------------------------------*/
  TCanvas* c8 = new TCanvas("c8","c8",800,600);
  c8->cd();
  c8->SetTickx(1);
  c8->SetTicky(1);
  c8->SetLogz();
  c8->SetTopMargin(0.09);
  c8->SetBottomMargin(0.11);
  c8->SetLeftMargin(0.09);
  c8->SetRightMargin(0.05);
  
  cms->Draw("same");
  hZDCP_corr->Draw("colz");
  c8->SaveAs(Form("./figures/%s/ZDCPlusCorr_%s.pdf", date.c_str(), tag.c_str()));
  /*--------------------------------------------------------*/
  
  
  /*--------------------------------------------------------*/
  /* plot ZDC AsymmOR distributions*/
  /*--------------------------------------------------------*/
  TLegend* leg9 = new TLegend(0.14,0.6,0.4,0.7);
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
  hZDCP_AsymXOR->SetLineColor(kRed);
  hZDCP_AsymXOR->SetLineWidth(2);
  hZDCP_AsymXOR->GetXaxis()->SetTitleSize(0.05);
  hZDCP_AsymXOR->SetMarkerStyle(20);
  hZDCP_AsymXOR->GetXaxis()->SetTitle("ZDC Energy Sum (GeV))");
  
  // zdc minus
  hZDCM_AsymXOR->SetLineColor(kBlue);
  hZDCM_AsymXOR->SetLineWidth(2);
  hZDCM_AsymXOR->SetMarkerStyle(20);
  hZDCM_AsymXOR->GetXaxis()->SetTitle("ZDC Energy Sum (GeV)");
  hZDCM_AsymXOR->GetXaxis()->SetTitleSize(0.05);
  hZDCM_AsymXOR->GetYaxis()->SetRangeUser(100, 100000);
  
  // zdc minus
  hZDCM_AsymXOR->Draw();
  hZDCP_AsymXOR->Draw("same");
  leg9->AddEntry(hZDCP_AsymXOR,"ZDC Plus for ZDC Plus > 16 and ZDC Minus < 28","l");
  leg9->AddEntry(hZDCM_AsymXOR,"ZDC Minus for ZDC Minus > 16 and ZDC Plus < 28","l");
  leg9->Draw("same");
  cms->Draw("same");
  onlinets->Draw("same");
  offlinets->Draw("same");
  c9->SaveAs(Form("./figures/%s/ZDCAsymXOR_%s.pdf", date.c_str(), tag.c_str()));
  
  
  /*--------------------------------------------------------*/
  /* plot ZDC AsymmOR + Jet8 distributions*/
  /*--------------------------------------------------------*/
  TLegend* leg10 = new TLegend(0.14,0.6,0.4,0.7);
  leg10->SetBorderSize(0);
  leg10->SetFillStyle(0);
  leg10->SetTextSize(0.04);
  

  TCanvas* c10 = new TCanvas("c10","c10",800,600);
  c10->cd();
  c10->SetTickx(1);
  c10->SetTicky(1);
  // c10->SetLogy();
  c10->SetTopMargin(0.09);
  c10->SetBottomMargin(0.11);
  c10->SetLeftMargin(0.09);
  c10->SetRightMargin(0.05);
  
  // zdc plus
  hZDCP_AsymXOR_Jet8->SetLineColor(kRed);
  hZDCP_AsymXOR_Jet8->SetLineWidth(2);
  hZDCP_AsymXOR_Jet8->GetXaxis()->SetTitleSize(0.05);
  hZDCP_AsymXOR_Jet8->SetMarkerStyle(20);
  hZDCP_AsymXOR_Jet8->GetXaxis()->SetTitle("ZDC Energy Sum (GeV))");
  
    // zdc minus
  hZDCM_AsymXOR_Jet8->SetLineColor(kBlue);
  hZDCM_AsymXOR_Jet8->SetLineWidth(2);
  hZDCM_AsymXOR_Jet8->SetMarkerStyle(20);
  hZDCM_AsymXOR_Jet8->GetXaxis()->SetTitle("ZDC Energy Sum (GeV)");
  hZDCM_AsymXOR_Jet8->GetXaxis()->SetTitleSize(0.05);
  hZDCM_AsymXOR_Jet8->GetYaxis()->SetRangeUser(0, 10);
  
  // zdc minus
  hZDCM_AsymXOR_Jet8->Draw();
  hZDCP_AsymXOR_Jet8->Draw("same");
  leg10->AddEntry(hZDCP_AsymXOR_Jet8,"ZDC Plus for ZDC Plus > 16,  ZDC Minus < 28 & Jet > 8","l");
  leg10->AddEntry(hZDCM_AsymXOR_Jet8,"ZDC Minus for ZDC Minus > 16,  ZDC Plus < 28 & Jet > 8","l");
  leg10->Draw("same");
  cms->Draw("same");
  onlinets->Draw("same");
  offlinets->Draw("same");
  c10->SaveAs(Form("./figures/%s/ZDCAsymXOR_Jet8_%s.pdf",date.c_str(),  tag.c_str()));
}
