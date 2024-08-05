// adcDistributions.C
// This macro makes ADC distributions for Time Slice 0 and 1 for all ZDC+ and ZDC- channels
// The first line reads in HiForest output

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "TString.h"
#include "TTree.h"
#include "TLatex.h"
#include "TStyle.h"
#include "TBranch.h"
#include "TFile.h"
#include <TTree.h>
#include <TChain.h>
#include "TCanvas.h"
#include "THStack.h"
#include "TLine.h"
#include "TPaveStats.h"
#include "TMath.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TF1.h"
#include "TProfile.h"
#include "TH1.h"
#include "TH2.h"
#include "TLorentzVector.h"
//#include "/home/colelemahieu/Research2023/commonUtility.h"
using namespace std;

// draw text function
void drawText(float xp, float yp, const char *text, int textColor=kBlack, double textSize=22){
  TLatex *tex = new TLatex(xp,yp,text);
  tex->SetTextFont(43);
  tex->SetTextSize(textSize);
  tex->SetTextColor(textColor);
  tex->SetLineWidth(1);
  tex->SetNDC();
  tex->Draw();
}

void adcDistributions()
{
  // Read in file
  TFile *file = new TFile("../HiForestMiniAOD_10000.root");
  TTree *zdcTree = (TTree*)file->Get("zdcanalyzer/zdcdigi");
  TTree *hltAnalysisTree = (TTree*)file->Get("hltanalysis/HltTree");
  float zdcEnt = zdcTree->GetEntries();

  // Read in Variables for ADCs TS0 and TS1
  int Run=0, n=0;
  unsigned long long Event=0;
  const int channelNumber=56;
  int zside[channelNumber]={0}, section[channelNumber]={0}, channel[channelNumber]={0};
  int adc_0[channelNumber]={0}, adc_1[channelNumber]={0};
  hltAnalysisTree->SetBranchAddress("Event", &Event);
  hltAnalysisTree->SetBranchAddress("Run", &Run);
  zdcTree->SetBranchAddress("n", &n);
  zdcTree->SetBranchAddress("zside", &zside);
  zdcTree->SetBranchAddress("section", &section);
  zdcTree->SetBranchAddress("channel", &channel);
  zdcTree->SetBranchAddress("adcTs0", &adc_0);
  zdcTree->SetBranchAddress("adcTs1", &adc_1);

  // Define hists
  int adcMax=260;
  const int zdc_channelNumber=28;
  vector<TH1F*> h_zdcPlus_adc0, h_zdcNeg_adc0;
  vector<TH1F*> h_zdcPlus_adc1, h_zdcNeg_adc1;
  h_zdcPlus_adc0.resize(zdc_channelNumber);
  h_zdcNeg_adc0.resize(zdc_channelNumber);
  h_zdcPlus_adc1.resize(zdc_channelNumber);
  h_zdcNeg_adc1.resize(zdc_channelNumber);

  // Label hists
  for (int i=0; i<zdc_channelNumber; i++)
    {

      if (i<5)
	{
	  h_zdcNeg_adc0.at(i) = new TH1F(Form("ZDC- TS0, EM%d",i+1), Form("ZDC- TS0, EM%d",i+1), adcMax,0,adcMax);
	  h_zdcPlus_adc0.at(i) = new TH1F(Form("ZDC+ TS0, EM%d",i+1), Form("ZDC+ TS0, EM%d",i+1), adcMax,0,adcMax);
	  h_zdcNeg_adc1.at(i) = new TH1F(Form("ZDC- TS1, EM%d",i+1), Form("ZDC- TS1, EM%d",i+1), adcMax,0,adcMax);
	  h_zdcPlus_adc1.at(i) = new TH1F(Form("ZDC+ TS1, EM%d",i+1), Form("ZDC+ TS1, EM%d",i+1), adcMax,0,adcMax);
	}
      if (i>4 && i<8)
	{
	  h_zdcNeg_adc0.at(i) = new TH1F(Form("ZDC- TS0, Dummy %d",i-4), Form("ZDC- TS0, Dummy %d",i-4), adcMax,0,adcMax);
	  h_zdcPlus_adc0.at(i) = new TH1F(Form("ZDC+ TS0, Dummy %d",i-4), Form("ZDC+ TS0, Dummy %d",i-4), adcMax,0,adcMax);
	  h_zdcNeg_adc1.at(i) = new TH1F(Form("ZDC- TS1, Dummy %d",i-4), Form("ZDC- TS1, Dummy %d",i-4), adcMax,0,adcMax);
	  h_zdcPlus_adc1.at(i) = new TH1F(Form("ZDC+ TS1, Dummy %d",i-4), Form("ZDC+ TS1, Dummy %d",i-4), adcMax,0,adcMax);
	}
      if (i>7 && i<12)
	{
	  h_zdcNeg_adc0.at(i) = new TH1F(Form("ZDC- TS0, HAD%d",i-7), Form("ZDC- TS0, HAD%d",i-7), adcMax,0,adcMax);
	  h_zdcPlus_adc0.at(i) = new TH1F(Form("ZDC+ TS0, HAD%d",i-7), Form("ZDC+ TS0, HAD%d",i-7), adcMax,0,adcMax);
	  h_zdcNeg_adc1.at(i) = new TH1F(Form("ZDC- TS1, HAD%d",i-7), Form("ZDC- TS1, HAD%d",i-7), adcMax,0,adcMax);
	  h_zdcPlus_adc1.at(i) = new TH1F(Form("ZDC+ TS1, HAD%d",i-7), Form("ZDC+ TS1, HAD%d",i-7), adcMax,0,adcMax);
	}
      if (i>11 && i<28)
	{
	  h_zdcNeg_adc0.at(i) = new TH1F(Form("ZDC- TS0, RPD%d",i-11), Form("ZDC- TS0, RPD%d",i-11), adcMax,0,adcMax);
	  h_zdcPlus_adc0.at(i) = new TH1F(Form("ZDC+ TS0, RPD%d",i-11), Form("ZDC+ TS0, RPD%d",i-11), adcMax,0,adcMax);
	  h_zdcNeg_adc1.at(i) = new TH1F(Form("ZDC- TS1, RPD%d",i-11), Form("ZDC- TS1, RPD%d",i-11), adcMax,0,adcMax);
	  h_zdcPlus_adc1.at(i) = new TH1F(Form("ZDC+ TS1, RPD%d",i-11), Form("ZDC+ TS1, RPD%d",i-11), adcMax,0,adcMax);
	}
    }


  vector<float> temp0_adcPlus_array, temp0_adcNeg_array;
  vector<float> temp1_adcPlus_array, temp1_adcNeg_array;
 
  
  // evt loop
  for (int i=0; i<zdcEnt; i++)
    {
      zdcTree->GetEntry(i);
      hltAnalysisTree->GetEntry(i);

      temp0_adcPlus_array.resize(0), temp0_adcNeg_array.resize(0);
      temp1_adcPlus_array.resize(0), temp1_adcNeg_array.resize(0);


      for (int ch=0; ch<n; ch++)
	{
	  // neg zSide
	  if (ch<12 || (ch>23 && ch<40))
	    {
	      temp0_adcNeg_array.push_back(adc_0[ch]);
	      temp1_adcNeg_array.push_back(adc_1[ch]);
	    }
	  // pos zSide
	  if ((ch>11 && ch<24) || (ch>39 && ch<56))
	    {
	      temp0_adcPlus_array.push_back(adc_0[ch]);
	      temp1_adcPlus_array.push_back(adc_1[ch]);
	    }
	} // end ch loop

      
      for (int j=0; j<28; j++)
	{
	  h_zdcNeg_adc0.at(j)->Fill(temp0_adcNeg_array.at(j));
	  h_zdcPlus_adc0.at(j)->Fill(temp0_adcPlus_array.at(j));
	  h_zdcNeg_adc1.at(j)->Fill(temp1_adcNeg_array.at(j));
	  h_zdcPlus_adc1.at(j)->Fill(temp1_adcPlus_array.at(j));
	}

      
    } // end evt loop

 

  float mean_zdc0_Neg[28]={0}, mean_zdc0_Plus[28]={0}, mean_zdc1_Neg[28]={0}, mean_zdc1_Plus[28]={0};
  

  // Plotting
  TCanvas *c0Plus[zdc_channelNumber], *c0Neg[zdc_channelNumber], *c1Plus[zdc_channelNumber], *c1Neg[zdc_channelNumber];
  
  for (int i=0; i<zdc_channelNumber; i++)
    {
      // Neg TS0
      c0Neg[i] = new TCanvas(Form("c0Neg_%d",i), Form("c0Neg_%d",i),850,850);
      c0Neg[i]->SetLogy();
      mean_zdc0_Neg[i]=h_zdcNeg_adc0.at(i)->GetMean();
      h_zdcNeg_adc0.at(i)->GetXaxis()->SetTitle("ADC Value, TS0");
      h_zdcNeg_adc0.at(i)->GetYaxis()->SetTitle("Counts");
      h_zdcNeg_adc0.at(i)->Draw();
      drawText(0.15,0.85,"ZDC-",kBlack,28);
      drawText(0.15,0.8,Form("mean=%.2f",mean_zdc0_Neg[i]),kBlack,28);

      // Plus TS0
      c0Plus[i] = new TCanvas(Form("c0Plus_%d",i), Form("c0Plus_%d",i),850,850);
      c0Plus[i]->SetLogy();
      mean_zdc0_Plus[i]=h_zdcPlus_adc0.at(i)->GetMean();
      h_zdcPlus_adc0.at(i)->GetXaxis()->SetTitle("ADC Value, TS0");
      h_zdcPlus_adc0.at(i)->GetYaxis()->SetTitle("Counts");
      h_zdcPlus_adc0.at(i)->Draw();
      drawText(0.15,0.85,"ZDC+",kBlack,28);
      drawText(0.15,0.8,Form("mean=%.2f",mean_zdc0_Plus[i]),kBlack,28);

      // Neg TS1
      c1Neg[i] = new TCanvas(Form("c1Neg_%d",i), Form("c1Neg_%d",i),850,850);
      c1Neg[i]->SetLogy();
      mean_zdc1_Neg[i]=h_zdcNeg_adc1.at(i)->GetMean();
      h_zdcNeg_adc1.at(i)->GetXaxis()->SetTitle("ADC Value, TS1");
      h_zdcNeg_adc1.at(i)->GetYaxis()->SetTitle("Counts");
      h_zdcNeg_adc1.at(i)->Draw();
      drawText(0.15,0.85,"ZDC-",kBlack,28);
      drawText(0.15,0.8,Form("mean=%.2f",mean_zdc1_Neg[i]),kBlack,28);

      // Plus TS1
      c1Plus[i] = new TCanvas(Form("c1Plus_%d",i), Form("c1Plus_%d",i),850,850);
      c1Plus[i]->SetLogy();
      mean_zdc1_Plus[i]=h_zdcPlus_adc1.at(i)->GetMean();
      h_zdcPlus_adc1.at(i)->GetXaxis()->SetTitle("ADC Value, TS1");
      h_zdcPlus_adc1.at(i)->GetYaxis()->SetTitle("Counts");
      h_zdcPlus_adc1.at(i)->Draw();
      drawText(0.15,0.85,"ZDC+",kBlack,28);
      drawText(0.15,0.8,Form("mean=%.2f",mean_zdc1_Plus[i]),kBlack,28);
    }

  
  // Print ZDC+ and ZDC-, ADC TS0 and ADCTS1 distrubtions to 4 seperate PDFs
  c0Neg[0]->Print("zdcNeg_adc0.pdf(","pdf");
  c0Plus[0]->Print("zdcPlus_adc0.pdf(","pdf");
  c1Neg[0]->Print("zdcNeg_adc1.pdf(","pdf");
  c1Plus[0]->Print("zdcPlus_adc1.pdf(","pdf");
  for (int j=1; j<(zdc_channelNumber-1); j++)
    {
      c0Neg[j]->Print("zdcNeg_adc0.pdf","pdf");
      c0Plus[j]->Print("zdcPlus_adc0.pdf","pdf");
      c1Neg[j]->Print("zdcNeg_adc1.pdf","pdf");
      c1Plus[j]->Print("zdcPlus_adc1.pdf","pdf");
    }
  c0Neg[27]->Print("zdcNeg_adc0.pdf)","pdf");
  c0Plus[27]->Print("zdcPlus_adc0.pdf)","pdf");
  c1Neg[27]->Print("zdcNeg_adc1.pdf)","pdf");
  c1Plus[27]->Print("zdcPlus_adc1.pdf)","pdf");

  
  
}
