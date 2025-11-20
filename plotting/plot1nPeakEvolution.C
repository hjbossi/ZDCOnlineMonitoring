#include <TFile.h>
#include <TH1.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <iostream>
#include <vector>


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


void FillChainSingleFile(TChain &chain, string &file) {
    chain.Add(file.c_str());
}


void plot1nPeakEvolution() {
    // List of ROOT files

    // evolution during the fill


    std::vector<string> rootFiles = { "/eos/cms/store/group/phys_heavyions/hbossi/ZDC2025/Run399499/LS_50_100/L1Ntuple.root", "/eos/cms/store/group/phys_heavyions/hbossi/ZDC2025/Run399499/LS_100_150/L1Ntuple.root", "/eos/cms/store/group/phys_heavyions/hbossi/ZDC2025/Run399499/LS_150_200/L1Ntuple.root", "/eos/cms/store/group/phys_heavyions/hbossi/ZDC2025/Run399499/LS_250_300/L1Ntuple.root"};
    std::vector<std::string> legLabelsZDCp = {"ZDCp - Run 399499 LS (50,100)","ZDCp - Run 399499 LS (100,150)", "ZDCp - Run 399499 LS (150,200)",  "ZDCp - Run 399499 LS (250,300)"}; 
    std::vector<std::string> legLabelsZDCm = {"ZDCm - Run 399499 LS (50,100)","ZDCm - Run 399499 LS (100,150)", "ZDCm - Run 399499 LS (150,200)",  "ZDCm - Run 399499 LS (250,300)"}; 
    std::vector<int> meanLumi = {75, 125, 175, 225, 275}; 
    bool doPlus = true; 



    // Create a canvas
    TCanvas *c = new TCanvas("c", "ZDC Histograms", 800, 600);
    c->SetTickx(1); 
    c->SetTicky(1); 
    c->SetLogy(1); 
    gStyle->SetOptStat(0); 
    gStyle->SetOptTitle(0); 

    // Create a legend
    TLegend *legend = new TLegend(0.11, 0.7, 0.65, 0.88);
    legend->SetBorderSize(0);
    legend->SetFillStyle(0);
    legend->SetTextSize(0.03);
    legend->SetTextFont(42); 
    //legend->SetNColumns(2); 

    bool firstPlot = true;
    int colorIndex = 0; // Start from color index 2 to avoid white
    int rebinFactor = 2; 

    TFile* denomFile = (TFile*)TFile::Open(rootFiles.at(0).c_str()); 
    TH1 *denomP = dynamic_cast<TH1*>(denomFile->Get("hZDCP"));
    TH1 *denomM = dynamic_cast<TH1*>(denomFile->Get("hZDCM"));
    // denomM->Rebin(rebinFactor); 
    // denomP->Rebin(rebinFactor);
    // denomP->Scale(1./denomP->Integral());
    // denomM->Scale(1./denomM->Integral());
    std::string ColorStrings[10] = {"#3f90da", "#ffa90e", "#bd1f01", "#94a4a2", "#832db6", "#a96b59", "#e76300", "#b9ac70", "#717581", "#92dadd"};//{"#5790fc", "#f89c20", "#e42536", "#964a8b", "#9c9ca1", "#7a21dd"};

    TH1D* h1_mean_V_lumi_plus = new TH1D("h1_plus", "h1_plus", meanLumi.size(), meanLumi.at(0), meanLumi.at(meanLumi.size()-1)); 
    TH1D* h1_mean_V_lumi_minus = new TH1D("h1_minus", "h1_minus", meanLumi.size(), meanLumi.at(0), meanLumi.at(meanLumi.size()-1)); 

    TH1D* h1_stddev_V_lumi_plus = new TH1D("h1_plus_std", "h1_plus_std", meanLumi.size(), meanLumi.at(0), meanLumi.at(meanLumi.size()-1)); 
    TH1D* h1_stddev_V_lumi_minus = new TH1D("h1_minus_std", "h1_minus_std", meanLumi.size(), meanLumi.at(0), meanLumi.at(meanLumi.size()-1)); 


    TH1D* res_plus = new TH1D("res_plus", "res_plus", meanLumi.size(), meanLumi.at(0), meanLumi.at(meanLumi.size()-1)); 
    TH1D* res_minus = new TH1D("res_minus", "res_minus", meanLumi.size(), meanLumi.at(0), meanLumi.at(meanLumi.size()-1)); 

    TH1D* eff_plus = new TH1D("eff_plus", "eff_plus", meanLumi.size(), meanLumi.at(0), meanLumi.at(meanLumi.size()-1)); 
    TH1D* eff_minus = new TH1D("eff_minus", "eff_minus", meanLumi.size(), meanLumi.at(0), meanLumi.at(meanLumi.size()-1)); 



    int lumiIndex = 0; 
    for ( auto fileName : rootFiles) {
        std::cout << "----------------> Opening file: " << fileName << std::endl;

        TH1D* hZDCp = new TH1D(Form("hZDCP_%d", lumiIndex), Form("hZDCP_%d", lumiIndex), 100, 0, 15000);
        TH1D* hZDCm = new TH1D(Form("hZDCM_%d", lumiIndex), Form("hZDCM_%d", lumiIndex), 100, 0, 15000);

        TH1D* hZDCp_aux = new TH1D("hZDCP_aux", "ZDC Plus aux", 100, 0, 10000);
        TH1D* hZDCm_aux = new TH1D("hZDCM_aux", "ZDC Minus aux", 100, 0, 10000);


        // loop over the events to fill the histograms
        TChain zdcChain("zdcanalyzer/zdcrechit");
        FillChainSingleFile(zdcChain, fileName);
        TTreeReader zdcReader(&zdcChain);
        TTreeReaderArray<int> zside(zdcReader, "zside");
        TTreeReaderArray<int> section(zdcReader, "section");
        TTreeReaderArray<int> channel(zdcReader, "channel");
        TTreeReaderArray<float> energy(zdcReader, "energy");
        TTreeReaderValue<int> n(zdcReader, "n"); 
        TTreeReaderValue<float> sumPlus(zdcReader, "sumPlus");
        TTreeReaderValue<float> sumMinus(zdcReader, "sumMinus");
        // TTreeReaderValue<float> sumPlusAux(zdcReader, "sumPlus_Aux");
        // TTreeReaderValue<float> sumMinusAux(zdcReader, "sumMinus_Aux");
        // TTreeReaderArray<int> zside(zdcReader, "zdcrechit_side");
        // TTreeReaderArray<int> section(zdcReader, "zdcrechit_section");
        // TTreeReaderArray<int> channel(zdcReader, "zdcrechit_channel");
        // TTreeReaderArray<float> energy(zdcReader, "zdcrechit_Energy");
        // TTreeReaderValue<int> n(zdcReader, "zdcrechit_n");
        // TTreeReaderValue<float> sumPlus(zdcReader, "ZDCp_Energy");
        // TTreeReaderValue<float> sumMinus(zdcReader, "ZDCm_Energy");
        // TTreeReaderValue<float> sumPlusAux(zdcReader, "ZDCp_Aux_Energy");
        // TTreeReaderValue<float> sumMinusAux(zdcReader, "ZDCm_Aux_Energy");

        TChain l1TrigChain("l1uGTTree/L1uGTTree");
        FillChainSingleFile(l1TrigChain, fileName);
        TTreeReader emuTrigReader(&l1TrigChain);
        TTreeReaderValue<vector<bool>> initialTrigDecision(emuTrigReader, "m_algoDecisionFinal");

    Long64_t totalEvents = zdcReader.GetEntries(true);
    for (Long64_t i = 0; i < totalEvents; i++) {
        zdcReader.Next(); emuTrigReader.Next();

        if (i % 10000 == 0) {
        cout << "Event " << i << endl;
        }

        // select on zero bias
        if((*initialTrigDecision)[1] != 1 ) continue; 

        hZDCp->Fill(*sumPlus);
        hZDCm->Fill(*sumMinus);

        // //only fill aux distribution with things that would pass the trigger. 
        // if(*sumPlusAux > 800){
        //     hZDCp_aux->Fill(*sumPlus);
        // }
        // if(*sumMinusAux > 800){
        //     hZDCm_aux->Fill(*sumMinus);
        // }
    } // end loop over  the  number of events




        // Retrieve histograms
        hZDCp->Rebin(rebinFactor); 
        hZDCm->Rebin(rebinFactor);
        hZDCp_aux->Rebin(rebinFactor); 
        hZDCm_aux->Rebin(rebinFactor);
        int low = hZDCp_aux->FindBin(100); 
        int high = hZDCp_aux->FindBin(4000);
        hZDCp->Scale(1./hZDCp->Integral());
        hZDCm->Scale(1./hZDCm->Integral());
        hZDCp_aux->Scale(1./hZDCp_aux->Integral());
        hZDCm_aux->Scale(1./hZDCm_aux->Integral());
      

        // add a fit to the 1n peak centered around 2650 and with a width of 200
        TF1* fit1n = new TF1("fit1n", "gaus", 1000, 4500);
        fit1n->SetLineColor(TColor::GetColor(ColorStrings[colorIndex].c_str()));
        fit1n->SetLineWidth(2);
        fit1n->SetLineStyle(2);
        fit1n->SetRange(0.,5000);
        hZDCp->Fit(fit1n, "0", "", 1000, 4500);

        TF1* fit1n_aux = new TF1("fit1n_aux", "gaus", 1000, 4500);
        fit1n_aux->SetLineColor(TColor::GetColor(ColorStrings[colorIndex].c_str()));
        fit1n_aux->SetLineWidth(2);
        fit1n_aux->SetLineStyle(2);
        fit1n_aux->SetRange(0.,5000);
        hZDCp_aux->Fit(fit1n_aux, "0", "", 1000, 4500);

        TF1* fit1nM = new TF1("fit1nM", "gaus", 1000, 4500);
        fit1nM->SetLineColor(TColor::GetColor(ColorStrings[colorIndex].c_str()));
        fit1nM->SetLineWidth(2);
        fit1nM->SetLineStyle(2);
        fit1nM->SetRange(0.,5000);
        hZDCm->Fit(fit1nM, "0", "", 1000, 4500);

        TF1* fit1nM_aux = new TF1("fit1nM_aux", "gaus", 1000, 4500);
        fit1nM_aux->SetLineColor(TColor::GetColor(ColorStrings[colorIndex].c_str()));
        fit1nM_aux->SetLineWidth(2);
        fit1nM_aux->SetLineStyle(2);
        fit1nM_aux->SetRange(0.,5000);
        hZDCm_aux->Fit(fit1nM_aux, "0", "", 1000, 4500);



        double A = fit1n->GetParameter(0);
        double sigma = fit1n->GetParameter(2);
        double A_aux = fit1n_aux->GetParameter(0);
        double sigma_aux = fit1n_aux->GetParameter(2);


        double A_minus = fit1nM->GetParameter(0);
        double sigma_minus = fit1nM->GetParameter(2);
        double A_aux_minus = fit1nM_aux->GetParameter(0);
        double sigma_aux_minus = fit1nM_aux->GetParameter(2);

        // Calculate the integral
        double integral = A * sigma * sqrt(2 * M_PI);
        double integral_aux = A_aux * sigma_aux * sqrt(2 * M_PI);  
        double integral_minus = A_minus * sigma_minus * sqrt(2 * M_PI);
        double integral_aux_minus = A_aux_minus * sigma_aux_minus * sqrt(2 * M_PI);  
        double eff = integral_aux/integral; 
        double eff_minusval = integral_aux_minus/integral_minus; 
        eff_plus->SetBinContent(lumiIndex+1,eff) ;
        eff_plus->SetBinError(lumiIndex+1, 0); 
        eff_minus->SetBinContent(lumiIndex+1, eff_minusval);
        eff_minus->SetBinError(lumiIndex+1, 0); 

        std::cout << "eff plus " << eff << " eff minus" << eff_minusval << std::endl;

  

        h1_mean_V_lumi_plus->SetBinContent(lumiIndex+1, fit1n->GetParameter(1));
        h1_mean_V_lumi_plus->SetBinError(lumiIndex+1, fit1n->GetParError(1)); 

        h1_mean_V_lumi_minus->SetBinContent(lumiIndex+1, fit1nM->GetParameter(1));
        h1_mean_V_lumi_minus->SetBinError(lumiIndex+1,  fit1nM->GetParError(1)); 

        h1_stddev_V_lumi_plus->SetBinContent(lumiIndex+1, fit1n->GetParameter(2));
        h1_stddev_V_lumi_plus->SetBinError(lumiIndex+1,  fit1n->GetParError(1));


        h1_stddev_V_lumi_minus->SetBinContent(lumiIndex+1, fit1nM->GetParameter(2));
        h1_stddev_V_lumi_minus->SetBinError(lumiIndex+1,  fit1nM->GetParError(1));

        res_plus->SetBinContent(lumiIndex+1, fit1n->GetParameter(2)/fit1n->GetParameter(1));
        res_plus->SetBinError(lumiIndex+1, 0);
        res_minus->SetBinContent(lumiIndex+1, fit1nM->GetParameter(2)/fit1nM->GetParameter(1));
        res_minus->SetBinError(lumiIndex+1, 0);

        // Set colors for ZDCp and ZDCm with different shades
        hZDCp->SetLineColor(TColor::GetColor(ColorStrings[colorIndex].c_str()));  
        hZDCm->SetLineColor(TColor::GetColor(ColorStrings[colorIndex].c_str())); 
        hZDCm->SetMarkerColor(TColor::GetColor(ColorStrings[colorIndex].c_str()));
        hZDCm->SetMarkerStyle(20); 
        hZDCp->SetMarkerStyle(20);
        hZDCp->SetMarkerColor(TColor::GetColor(ColorStrings[colorIndex].c_str()));  
        hZDCp->SetLineWidth(2); 
        hZDCm->SetLineWidth(2);

        // Draw histograms on the same canvas
        if (firstPlot) {
            if(doPlus){
                hZDCp->GetXaxis()->SetTitle("ZDC Energy Sum (GeV)"); 
                hZDCp->Draw();
                fit1n->Draw("same");
            }
            else{
                hZDCm->GetXaxis()->SetTitle("ZDC Energy Sum (GeV)"); 
                hZDCm->Draw();
                fit1nM->Draw("same");
            }
            

            
            firstPlot = false;
        } else {
            if(doPlus){
                hZDCp->Draw("SAME");
                fit1n->Draw("same");
            }
            else{
                hZDCm->Draw("SAME");
                fit1nM->Draw("same"); 

            }
           
        }

        // Add entries to the legend
        if(doPlus)legend->AddEntry(hZDCp, (legLabelsZDCp.at(colorIndex) + Form(" #mu: %.2f GeV, #sigma: %.2f GeV", fit1n->GetParameter(1), fit1n->GetParameter(2))).c_str(), "pl");
        else legend->AddEntry(hZDCm, (legLabelsZDCm.at(colorIndex) + Form(" #mu: %.2f GeV, #sigma: %.2f GeV", fit1nM->GetParameter(1), fit1nM->GetParameter(2))).c_str(), "pl");
        // Increment color index for the next shade
        colorIndex++;
        lumiIndex++; 

        // Close the file
        //file->Close();
    }

    // Draw the legend
    legend->Draw();

    TLatex* cms = new TLatex(0.10,0.92,"#bf{CMS} #it{Internal} PbPb Run 399499");
    cms->SetNDC();
    cms->SetTextSize(0.05);
    cms->SetTextFont(42);

    cms->Draw(); 

    // Update canvas
    //c->Update();
    if(doPlus)c->SaveAs("ZDCOverTime_PbPb_Run399499_plus.pdf");
    else c->SaveAs("ZDCOverTime_PbPb_Run399499_minus.pdf");

        // Create a canvas
    TCanvas *c2 = new TCanvas("c2", "ZDC Histograms 2", 800, 600);
    c2->SetTickx(1); 
    c2->SetTicky(1); 
    c2->SetLeftMargin(0.11); 
    c2->SetRightMargin(0.05);

    h1_mean_V_lumi_minus->GetYaxis()->SetRangeUser(2000, 3000); 
    h1_mean_V_lumi_minus->GetYaxis()->SetTitle("Mean of 1n Peak"); 
    h1_mean_V_lumi_minus->GetXaxis()->SetTitle("Lumi Section"); 
    h1_mean_V_lumi_minus->SetMarkerStyle(20); 
    h1_mean_V_lumi_minus->SetMarkerColor(kBlue);
    h1_mean_V_lumi_minus->SetLineColor(kBlue);  
    h1_mean_V_lumi_minus->Draw("pl");

    h1_mean_V_lumi_plus->SetMarkerStyle(20); 
    h1_mean_V_lumi_plus->SetMarkerColor(kRed);
    h1_mean_V_lumi_plus->SetLineColor(kRed); 
    h1_mean_V_lumi_plus->Draw("lp same");
  

    TLegend *legend2 = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend2->SetBorderSize(0);
    legend2->SetFillStyle(0);
    legend2->SetTextSize(0.035);
    legend2->SetTextFont(42); 

    legend2->AddEntry(h1_mean_V_lumi_minus, "ZDCm");
    legend2->AddEntry(h1_mean_V_lumi_plus, "ZDCp");
    legend2->Draw(); 
    cms->Draw(); 

    c2->SaveAs("PeakMeanvLumi_399499.pdf"); 


    TCanvas *c3 = new TCanvas("c3", "ZDC Histograms 3", 800, 600);
    c3->SetTickx(1); 
    c3->SetTicky(1); 
    c3->SetLeftMargin(0.11); 
    c3->SetRightMargin(0.05);

    h1_stddev_V_lumi_minus->GetYaxis()->SetRangeUser(500, 800); 
   h1_stddev_V_lumi_minus->GetYaxis()->SetTitle("Sigma of 1n Peak"); 
   h1_stddev_V_lumi_minus->GetXaxis()->SetTitle("Lumi Section"); 
    h1_stddev_V_lumi_minus->SetMarkerStyle(20); 
    h1_stddev_V_lumi_minus->SetMarkerColor(kBlue);
    h1_stddev_V_lumi_minus->SetLineColor(kBlue);  
    h1_stddev_V_lumi_minus->Draw("pl");

    h1_stddev_V_lumi_plus->SetMarkerStyle(20); 
    h1_stddev_V_lumi_plus->SetMarkerColor(kRed);
    h1_stddev_V_lumi_plus->SetLineColor(kRed); 
    h1_stddev_V_lumi_plus->Draw("lp same");
  

    TLegend *legend3 = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend3->SetBorderSize(0);
    legend3->SetFillStyle(0);
    legend3->SetTextSize(0.035);
    legend3->SetTextFont(42); 

    legend3->AddEntry(h1_stddev_V_lumi_minus, "ZDCm");
    legend3->AddEntry(h1_stddev_V_lumi_plus, "ZDCp");
    legend3->Draw(); 
    cms->Draw(); 

    c3->SaveAs("PeakStdDevvLumi_399499.pdf"); 


    TCanvas *c4 = new TCanvas("c4", "ZDC Histograms 4", 800, 600);
    c4->SetTickx(1); 
    c4->SetTicky(1); 
    c4->SetLeftMargin(0.11); 
    c4->SetRightMargin(0.05);

    res_minus->GetYaxis()->SetRangeUser(0, 0.5); 
    res_minus->GetYaxis()->SetTitle("Resolution of 1n Peak"); 
    res_minus->GetXaxis()->SetTitle("Lumi Section"); 
    res_minus->SetMarkerStyle(20); 
    res_minus->SetMarkerColor(kBlue);
    res_minus->SetLineColor(kBlue);  
    res_minus->Draw("pl");

    res_plus->SetMarkerStyle(20); 
    res_plus->SetMarkerColor(kRed);
    res_plus->SetLineColor(kRed); 
    res_plus->Draw("lp same");
  

    TLegend *legend4 = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend4->SetBorderSize(0);
    legend4->SetFillStyle(0);
    legend4->SetTextSize(0.035);
    legend4->SetTextFont(42); 

    legend4->AddEntry(res_minus, "ZDCm");
    legend4->AddEntry(res_plus, "ZDCp");
    legend4->Draw(); 
    cms->Draw(); 

    c4->SaveAs("PeakResLumi_399499.pdf"); 

    
    TCanvas *c5 = new TCanvas("c5", "ZDC Histograms 5", 800, 600);
    c5->SetTickx(1); 
    c5->SetTicky(1); 
    c5->SetLeftMargin(0.11); 
    c5->SetRightMargin(0.05);


    //eff_minus->GetYaxis()->SetRangeUser(0.8, 1.05); 
    eff_minus->GetYaxis()->SetTitle("Efficiency of 1n Peak"); 
    eff_minus->GetXaxis()->SetTitle("Lumi Section"); 
    eff_minus->SetMarkerStyle(20); 
    eff_minus->SetMarkerColor(kBlue);
    eff_minus->SetLineColor(kBlue);  
    eff_minus->Draw("pl");

    eff_plus->SetMarkerStyle(20); 
    eff_plus->SetMarkerColor(kRed);
    eff_plus->SetLineColor(kRed); 
    eff_plus->Draw("lp same");
  

    TLegend *legend5 = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend5->SetBorderSize(0);
    legend5->SetFillStyle(0);
    legend5->SetTextSize(0.035);
    legend5->SetTextFont(42); 

    legend5->AddEntry(eff_minus, "ZDCm");
    legend5->AddEntry(eff_plus, "ZDCp");
    legend5->Draw(); 
    cms->Draw(); 

    c5->SaveAs("PeakEff_399499.pdf"); 

     
}
