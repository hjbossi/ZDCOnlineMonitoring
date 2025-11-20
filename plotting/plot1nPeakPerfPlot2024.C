//
/*
 * perfPlot2024: Minimal macro to make the performance plot from 2024. 
 * Input: Folder of L1Ntuples
 * Output: A root file of histograms relevant to checking the unpacking. 
 * Authors: Hannah Bossi <hannah.bossi@cern.ch>
 * 03/07/2024
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

// void FillChain(TChain &chain, vector<string> &files) {
//   for (auto file : files) {
//     chain.Add(file.c_str());
//   }
// }

void FillChain(TChain &chain, vector<string> &files) {
  for (auto file : files) {
    if(file.find("ls0104") != std::string::npos){
      if(file.find("HIForward0") != std::string::npos) continue;
      if(file.find("HIForward6") != std::string::npos) continue;
      if(file.find("HIForward12") != std::string::npos) continue;
      if(file.find("HIForward15") != std::string::npos) continue;
      if(file.find("HIForward17") != std::string::npos) continue;
    }
    chain.Add(file.c_str());
  }
}

void FillChainSingleFile(TChain &chain, string &file) {
    chain.Add(file.c_str());
}

// params
// input: folder of l1ntuples to read from - must contain the branches specified above
// verbose: whether or not to print out the full output (error messgaes will always be printed)
int plot1nPeakPerfPlot2024(
	char const *input = "/eos/cms/store/group/phys_heavyions/cmcginn/Run2025/") {


    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);

    string tag = "Run399499_v6_4nSearch"; 

    TLatex* cms = new TLatex(0.10,0.92,"#bf{CMS} #it{Preliminary} Run 399499");
    cms->SetNDC();
    cms->SetTextSize(0.05);
    cms->SetTextFont(42);

    TLatex* cms2 = new TLatex(0.61,0.92,"2025 PbPb (5.36 TeV)");
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


   /* read in information on the emulated trigger fires*/
  TChain l1TrigChain("l1uGTTree/L1uGTTree");
  FillChain(l1TrigChain, files);
  TTreeReader emuTrigReader(&l1TrigChain);
  TTreeReaderValue<vector<bool>> initialTrigDecision(emuTrigReader, "m_algoDecisionFinal");
 

  /* create histograms */

    TH1D* hZDCP = new TH1D("hZDCP", "ZDC Plus", 50, 0, 15000);
    TH1D* hZDCM = new TH1D("hZDCM", "ZDC Minus", 50, 0, 15000);

 
  Long64_t totalEvents = zdcReader.GetEntries(true);
  for (Long64_t i = 0; i < totalEvents; i++) {
    zdcReader.Next(); emuTrigReader.Next(); 

    // select on zero bias
     if((*initialTrigDecision)[1] != 1 ) continue; 

    if (i % 10000 == 0) {
      cout << "Event " << i << endl;
    }


    hZDCP->Fill(*sumPlus);
    hZDCM->Fill(*sumMinus);

  } // end loop over  the  number of events


    TFile* outfile = new TFile(Form("1nPeak_%s.root", tag.c_str()), "RECREATE");
    outfile->cd();
    hZDCP->Write();
    hZDCM->Write();
    outfile->Close();




    // ------------------------------------------
    /* ZDC Plus and Minus */
    // ------------------------------------------
    TLegend* leg3 = new TLegend(0.14, 0.57, 0.45, 0.86);
    leg3->SetBorderSize(0);
    leg3->SetFillStyle(0);
    leg3->SetTextSize(0.045);

    TLatex* cms3 = new TLatex(0.7,0.50,"Zero Bias");
    cms3->SetNDC();
    cms3->SetTextSize(0.05);
    cms3->SetTextFont(42);
    
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
    hZDCP->GetXaxis()->SetTitle("ZDC Offline Energy Sum (GeV)");


    // add a fit to the 1n peak centered around 2650 and with a width of 200
    TF1* fit1n = new TF1("fit1n", "gaus", 500, 4000);
    fit1n->SetLineColor(kRed);
    fit1n->SetLineWidth(2);
    fit1n->SetLineStyle(2);
    fit1n->SetRange(0.,4500);
    hZDCP->Fit(fit1n, "0", "", 500, 4000);

    // print the fit parameters
    std::cout << "-----------------------------------------------------------------" << std::endl;
    std::cout << "1n Fit Parameters: " << std::endl;
    std::cout << "Mean: " << fit1n->GetParameter(1) << std::endl;
    std::cout << "Sigma: " << fit1n->GetParameter(2) << std::endl;
    float intFullPlus = fit1n->Integral(fit1n->GetParameter(1)-2*fit1n->GetParameter(2), fit1n->GetParameter(1)+2*fit1n->GetParameter(2)); 
    float intPartialPlus = fit1n->Integral(800, fit1n->GetParameter(1)+2*fit1n->GetParameter(2));
    std::cout << "Integral over whole peak: " << intFullPlus << std::endl;
    std::cout << "Integral over efficient region: " << intPartialPlus << std::endl;
    std::cout << "Capturing " << (intPartialPlus/intFullPlus)*100 << "% of the 1n peak" << std::endl;
    std::cout << "-----------------------------------------------------------------" << std::endl;


    // do the same for the minus 
    TF1* fit1nM = new TF1("fit1nM", "gaus",  500, 4500);
    fit1nM->SetLineColor(kBlue);
    fit1nM->SetLineWidth(2);
    fit1nM->SetLineStyle(2);
    fit1nM->SetRange(500.,5000);
    hZDCM->Fit(fit1nM, "0", "", 500, 4500);

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
    TF1* fit2n = new TF1("fit2n", "gaus", 4500, 7000);
    fit2n->SetLineColor(kRed);
    fit2n->SetLineWidth(2);
    fit2n->SetLineStyle(2);
    fit2n->SetRange(1000.,10000);
    hZDCP->Fit(fit2n, "0+", "", 4500, 7000);

    TF1* fit2nM = new TF1("fit2nM", "gaus", 4500, 7000);
    fit2nM->SetLineColor(kBlue);
    fit2nM->SetLineWidth(2);
    fit2nM->SetLineStyle(2);
    fit2nM->SetRange(1000.,10000);
    hZDCM->Fit(fit2nM, "0+", "", 4500, 7000);


    TF1* fit3n = new TF1("fit3n", "gaus", 7500, 9000);
    fit3n->SetLineColor(kRed);
    fit3n->SetLineWidth(2);
    fit3n->SetLineStyle(2);
    fit3n->SetRange(4000.,12000);
    hZDCP->Fit(fit3n, "0+", "", 7500, 9000);

    TF1* fit3nM = new TF1("fit3nM", "gaus", 7500, 9500);
    fit3nM->SetLineColor(kBlue);
    fit3nM->SetLineWidth(2);
    fit3nM->SetLineStyle(2);
    fit3nM->SetRange(4000, 12000);
    hZDCM->Fit(fit3nM, "0+", "", 7500, 9500);

    TF1* fit4n = new TF1("fit4n", "gaus", 10000, 12000);
    fit4n->SetLineColor(kRed);
    fit4n->SetLineWidth(2);
    fit4n->SetLineStyle(2);
    fit4n->SetRange(10000, 12000);
    hZDCP->Fit(fit4n, "0+", "", 10000, 12000);

    TF1* fit4nM = new TF1("fit4nM", "gaus",10000, 12000);
    fit4nM->SetLineColor(kBlue);
    fit4nM->SetLineWidth(2);
    fit4nM->SetLineStyle(2);
    fit4nM->SetRange(10000, 12000);
    hZDCM->Fit(fit4nM, "0+", "", 10000, 12000);


    TF1* noiseFitm = new TF1("noisefit","expo", 0., 20.);

    TF1* total_plus = new TF1("pstotal","gaus(0)+gaus(3)+gaus(6)",1000,10000);
    Double_t par[9];
    // Get the parameters from the fit
    fit1n->GetParameters(&par[0]);
    fit2n->GetParameters(&par[3]);
    fit3n->GetParameters(&par[6]);
    fit4n->GetParameters(&par[9]); 

    TF1* total_minus = new TF1("mstotal","gaus(0)+gaus(3)+gaus(6)",1000,10000);
    Double_t parM[9];
    // Get the parameters from the fit
    fit1nM->GetParameters(&parM[0]);
    fit2nM->GetParameters(&parM[3]);
    fit3nM->GetParameters(&parM[6]);
    fit4nM->GetParameters(&parM[9]); 

   // Use the parameters on the sum
   total_plus->SetParameters(par);
   total_plus->SetLineColor(kRed);
   total_plus->SetLineWidth(4);

    total_minus->SetParameters(parM);
    total_minus->SetLineColor(kBlue);
    total_minus->SetLineWidth(4);



    // create tlatex for fit parameters
    TLatex* fit1nMean = new TLatex(0.14,0.82,Form("ZDC Plus 1n, #mu: %.2f TeV, #sigma: %.2f TeV", fit1n->GetParameter(1)*0.001, fit1n->GetParameter(2)*0.001));
    fit1nMean->SetNDC();
    fit1nMean->SetTextSize(0.045);
    fit1nMean->SetTextFont(42);

    // do the same for the minus
    TLatex* fit1nMeanM = new TLatex(0.14,0.77,Form("ZDC Minus 1n, #mu: %.2f TeV, #sigma: %.2f TeV", fit1nM->GetParameter(1)*0.001, fit1nM->GetParameter(2)*0.001));
    fit1nMeanM->SetNDC();
    fit1nMeanM->SetTextSize(0.045);
    fit1nMeanM->SetTextFont(42);

    TLatex* fit2nMean = new TLatex(0.14,0.72,Form("ZDC Plus 2n, #mu: %.2f TeV, #sigma: %.2f TeV", fit2n->GetParameter(1)*0.001, fit2n->GetParameter(2)*0.001));
    fit2nMean->SetNDC();
    fit2nMean->SetTextSize(0.045);
    fit2nMean->SetTextFont(42);

    // do the same for the minus
    TLatex* fit2nMeanM = new TLatex(0.14,0.67,Form("ZDC Minus 2n, #mu: %.2f TeV, #sigma: %.2f TeV", fit2nM->GetParameter(1)*0.001, fit2nM->GetParameter(2)*0.001));
    fit2nMeanM->SetNDC();
    fit2nMeanM->SetTextSize(0.045);
    fit2nMeanM->SetTextFont(42);

    // do the same for the minus
    TLatex* fit3nMean = new TLatex(0.14,0.62,Form("ZDC Plus 3n, #mu: %.2f TeV, #sigma: %.2f TeV", fit3n->GetParameter(1)*0.001, fit3n->GetParameter(2)*0.001));
    fit3nMean->SetNDC();
    fit3nMean->SetTextSize(0.045);
    fit3nMean->SetTextFont(42);

    // do the same for the minus
    TLatex* fit3nMeanM = new TLatex(0.14,0.57,Form("ZDC Minus 3n, #mu: %.2f TeV #sigma: %.2f TeV", fit3nM->GetParameter(1)*0.001, fit3nM->GetParameter(2)*0.001));
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
    leg3->AddEntry(fit1n,Form("ZDC Plus 1n,  #mu: %.2f TeV, #sigma: %.2f TeV", fit1n->GetParameter(1)*0.001, fit1n->GetParameter(2)*0.001), "l"); 
    leg3->AddEntry(fit1nM, Form("ZDC Minus 1n, #mu: %.2f TeV, #sigma: %.2f TeV", fit1nM->GetParameter(1)*0.001, fit1nM->GetParameter(2)*0.001), "l");
    leg3->AddEntry(fit2n, Form("ZDC Plus 2n, #mu: %.2f TeV, #sigma: %.2f TeV", fit2n->GetParameter(1)*0.001, fit2n->GetParameter(2)*0.001), "l"); 
    leg3->AddEntry(fit2nM, Form("ZDC Minus 2n, #mu: %.2f TeV, #sigma: %.2f TeV", fit2nM->GetParameter(1)*0.001, fit2nM->GetParameter(2)*0.001), "l"); 
    leg3->AddEntry(fit3n, Form("ZDC Plus 3n, #mu: %.2f TeV, #sigma: %.2f TeV", fit3n->GetParameter(1)*0.001, fit3n->GetParameter(2)*0.001), "l"); 
    leg3->AddEntry(fit3nM,Form("ZDC Minus 3n, #mu: %.2f TeV #sigma: %.2f TeV", fit3nM->GetParameter(1)*0.001, fit3nM->GetParameter(2)*0.001), "l" ); 
     leg3->AddEntry(fit4n, Form("ZDC Plus 4n, #mu: %.2f TeV, #sigma: %.2f TeV", fit4n->GetParameter(1)*0.001, fit4n->GetParameter(2)*0.001), "l"); 
    leg3->AddEntry(fit4nM,Form("ZDC Minus 4n, #mu: %.2f TeV #sigma: %.2f TeV", fit4nM->GetParameter(1)*0.001, fit4nM->GetParameter(2)*0.001), "l" ); 
    leg3->AddEntry(total_plus, "ZDC Plus + Combined Fit", "l");
    leg3->AddEntry(total_minus, "ZDC Minus + Combined Fit", "l");


    leg3->Draw("same");
    cms->Draw("same");
    cms2->Draw("same"); 
    cms3->Draw("same"); 
    fit1n->Draw("same");
    fit1nM->Draw("same");
    fit2n->Draw("same");
    fit2nM->Draw("same");
    fit3n->Draw("same");
    fit3nM->Draw("same");
    hZDCP->Fit(total_plus,"R+");
    hZDCM->Fit(total_minus,"R+");

    c3->SaveAs(Form("PerfPlot2025_%s.pdf", tag.c_str()));





  return 1;
}

int main(int argc, char *argv[]) {
  if (argc == 2)
    return plot1nPeakPerfPlot2024(argv[1]);
  else {
    cout << "ERROR" << endl;
    return -1;
  }
}
