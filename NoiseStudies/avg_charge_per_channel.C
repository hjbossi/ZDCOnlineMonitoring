// avg_charge_per_channel.C
// This macro makes scatter plots showing the average charge (avg TS0 and avg TS1 charge) for each channel in ZDC+ and ZDC-
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


void avg_charge_per_channel()
{
  // Read in file
  TFile *file = new TFile("../../../HiForestMiniAOD_10000.root");
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

  // hists
  int adcMax=260;
  const int zdc_channelNumber=28;
  vector<TH1F*> h_zdcPlus_adc0, h_zdcNeg_adc0;
  vector<TH1F*> h_zdcPlus_adc1, h_zdcNeg_adc1;
  h_zdcPlus_adc0.resize(zdc_channelNumber);
  h_zdcNeg_adc0.resize(zdc_channelNumber);
  h_zdcPlus_adc1.resize(zdc_channelNumber);
  h_zdcNeg_adc1.resize(zdc_channelNumber);

  // label the hists
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



  
  // find the mean charge for TS0 and TS1 for ZDC+ and ZDC-
  float mean_zdc0_Neg[28]={0}, mean_zdc0_Plus[28]={0}, mean_zdc1_Neg[28]={0}, mean_zdc1_Plus[28]={0};
  
  for (int i=0; i<zdc_channelNumber; i++)
    {      
      mean_zdc0_Neg[i]=h_zdcNeg_adc0.at(i)->GetMean();
      mean_zdc0_Plus[i]=h_zdcPlus_adc0.at(i)->GetMean();
      mean_zdc1_Neg[i]=h_zdcNeg_adc1.at(i)->GetMean();
      mean_zdc1_Plus[i]=h_zdcPlus_adc1.at(i)->GetMean();    
    }



  // scatter plot TS0 channels, Plus and Minus
  TCanvas *cScatter_ts0 = new TCanvas("cScatter_ts0", " ", 800, 600);
  const int nPoints = 28;
  float xNeg_ts0[nPoints]={0}, xPos_ts0[nPoints]={0};
  float yNeg_ts0[nPoints]={0}, yPos_ts0[nPoints]={0};
  
  for (int i=0; i<nPoints; i++)
    {
      xNeg_ts0[i] = (i+.95);
      yNeg_ts0[i] = mean_zdc0_Neg[i];
      xPos_ts0[i] = (i+1.05);
      yPos_ts0[i] = mean_zdc0_Plus[i];          
    }

  TGraph *grNeg_ts0 = new TGraph(nPoints, xNeg_ts0, yNeg_ts0);
  TGraph *grPos_ts0 = new TGraph(nPoints, xPos_ts0, yPos_ts0);

  grNeg_ts0->SetMarkerStyle(kFullDotLarge);
  grNeg_ts0->SetMarkerColor(kRed);
  grNeg_ts0->SetMarkerSize(2);
  grPos_ts0->SetMarkerStyle(kFullDotLarge);
  grPos_ts0->SetMarkerSize(2);
  grPos_ts0->GetYaxis()->SetRangeUser(0,100);
  grPos_ts0->SetTitle(";Channel [0-27];Mean ADC Value TS0");
  grPos_ts0->Draw("AP");
  grNeg_ts0->Draw("P SAME");

  TLegend *legend = new TLegend(0.75, 0.75, 0.85, 0.85);
  legend->AddEntry(grNeg_ts0, "ZDC-", "p");
  legend->AddEntry(grPos_ts0, "ZDC+", "p");
  legend->SetBorderSize(0);
  legend->Draw();

  cScatter_ts0->SaveAs("scatterPlot_ts0.png");



  // scatter plot TS1 channels, Plus and Minus
  TCanvas *cScatter_ts1 = new TCanvas("cScatter_ts1", " ", 800, 600);
  float xNeg_ts1[nPoints]={0}, xPos_ts1[nPoints]={0};
  float yNeg_ts1[nPoints]={0}, yPos_ts1[nPoints]={0};
  
  for (int i=0; i<nPoints; i++)
    {
      xNeg_ts1[i] = (i+.95);
      yNeg_ts1[i] = mean_zdc1_Neg[i];
      xPos_ts1[i] = (i+1.05);
      yPos_ts1[i] = mean_zdc1_Plus[i];          
    }

  TGraph *grNeg_ts1 = new TGraph(nPoints, xNeg_ts1, yNeg_ts1);
  TGraph *grPos_ts1 = new TGraph(nPoints, xPos_ts1, yPos_ts1);

  grNeg_ts1->SetMarkerStyle(kFullDotLarge);
  grNeg_ts1->SetMarkerColor(kRed);
  grNeg_ts1->SetMarkerSize(2);
  grPos_ts1->SetMarkerStyle(kFullDotLarge);
  grPos_ts1->SetMarkerSize(2);
  grPos_ts1->GetYaxis()->SetRangeUser(0,100);
  grPos_ts1->SetTitle(";Channel [0-27];Mean ADC Value TS1");
  grPos_ts1->Draw("AP");
  grNeg_ts1->Draw("P SAME");

  TLegend *legend1 = new TLegend(0.75, 0.75, 0.85, 0.85);
  legend1->AddEntry(grNeg_ts1, "ZDC-", "p");
  legend1->AddEntry(grPos_ts1, "ZDC+", "p");
  legend1->SetBorderSize(0);
  legend1->Draw();

  cScatter_ts1->SaveAs("scatterPlot_ts1.png");
  
  
  
}
