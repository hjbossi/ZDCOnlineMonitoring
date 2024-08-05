// noise_correlations.C
// This macro makes PDFs showing noise correlations between different time slices, specifically TS5,TS4,TS3,TS2,TS1 vs TS0.
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


void noise_correlations()
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
  int adc_0[channelNumber]={0}, adc_1[channelNumber]={0}, adc_2[channelNumber]={0}, adc_3[channelNumber]={0}, adc_4[channelNumber]={0}, adc_5[channelNumber]={0};
  hltAnalysisTree->SetBranchAddress("Event", &Event);
  hltAnalysisTree->SetBranchAddress("Run", &Run);
  zdcTree->SetBranchAddress("n", &n);
  zdcTree->SetBranchAddress("zside", &zside);
  zdcTree->SetBranchAddress("section", &section);
  zdcTree->SetBranchAddress("channel", &channel);
  zdcTree->SetBranchAddress("adcTs0", &adc_0);
  zdcTree->SetBranchAddress("adcTs1", &adc_1);
  zdcTree->SetBranchAddress("adcTs2", &adc_2);
  zdcTree->SetBranchAddress("adcTs3", &adc_3);
  zdcTree->SetBranchAddress("adcTs4", &adc_4);
  zdcTree->SetBranchAddress("adcTs5", &adc_5);

  // hist array for 56 channels
  int adcMax=260;
  const int zdc_channelNumber=28; 
  vector<TH1F*> h_zdcPlus_adc, h_zdcNeg_adc;
  vector<TH2F*> h2_zdcPlus_adcTS0_adcTS1, h2_zdcNeg_adcTS0_adcTS1;
  vector<TH2F*> h2_zdcPlus_adcTS0_adcTS2, h2_zdcNeg_adcTS0_adcTS2;
  vector<TH2F*> h2_zdcPlus_adcTS0_adcTS3, h2_zdcNeg_adcTS0_adcTS3;
  vector<TH2F*> h2_zdcPlus_adcTS0_adcTS4, h2_zdcNeg_adcTS0_adcTS4;
  vector<TH2F*> h2_zdcPlus_adcTS0_adcTS5, h2_zdcNeg_adcTS0_adcTS5;
  h_zdcPlus_adc.resize(zdc_channelNumber);
  h_zdcNeg_adc.resize(zdc_channelNumber);
  h2_zdcPlus_adcTS0_adcTS1.resize(zdc_channelNumber);
  h2_zdcNeg_adcTS0_adcTS1.resize(zdc_channelNumber);
  h2_zdcPlus_adcTS0_adcTS2.resize(zdc_channelNumber);
  h2_zdcNeg_adcTS0_adcTS2.resize(zdc_channelNumber);
  h2_zdcPlus_adcTS0_adcTS3.resize(zdc_channelNumber);
  h2_zdcNeg_adcTS0_adcTS3.resize(zdc_channelNumber);
  h2_zdcPlus_adcTS0_adcTS4.resize(zdc_channelNumber);
  h2_zdcNeg_adcTS0_adcTS4.resize(zdc_channelNumber);
  h2_zdcPlus_adcTS0_adcTS5.resize(zdc_channelNumber);
  h2_zdcNeg_adcTS0_adcTS5.resize(zdc_channelNumber);

  
  for (int i=0; i<zdc_channelNumber; i++)
    {
      h_zdcPlus_adc.at(i) = new TH1F(Form("h_zdcPlus_adcTS0_%d",i), Form("h_zdcPlus_adcTS0_%d",i), adcMax,0,adcMax);
      h_zdcNeg_adc.at(i) = new TH1F(Form("h_zdcNeg_adcTS0_%d",i), Form("h_zdcNeg_adcTS0_%d",i), adcMax,0,adcMax);

      

      // 2D histogram titles
      if (i<5)
	{
	  h2_zdcPlus_adcTS0_adcTS1.at(i) = new TH2F(Form("ZDC+, EM%d",i+1), Form("ZDC+, EM%d",i+1), adcMax,0,adcMax, adcMax,0,adcMax);
      h2_zdcNeg_adcTS0_adcTS1.at(i) = new TH2F(Form("ZDC-, EM%d",i+1), Form("ZDC-, EM%d",i+1), adcMax,0,adcMax, adcMax,0,adcMax);

          h2_zdcPlus_adcTS0_adcTS2.at(i) = new TH2F(Form("TS2 vs TS0: ZDC+, EM%d",i+1), Form("TS2 vs TS0: ZDC+, EM%d",i+1), adcMax,0,adcMax, adcMax,0,adcMax);
      h2_zdcNeg_adcTS0_adcTS2.at(i) = new TH2F(Form("TS2 vs TS0: ZDC-, EM%d",i+1), Form("TS2 vs TS0: ZDC-, EM%d",i+1), adcMax,0,adcMax, adcMax,0,adcMax);

          h2_zdcPlus_adcTS0_adcTS3.at(i) = new TH2F(Form("TS3 vs TS0: ZDC+, EM%d",i+1), Form("TS3 vs TS0: ZDC+, EM%d",i+1), adcMax,0,adcMax, adcMax,0,adcMax);
      h2_zdcNeg_adcTS0_adcTS3.at(i) = new TH2F(Form("TS3 vs TS0: ZDC-, EM%d",i+1), Form("TS3 vs TS0: ZDC-, EM%d",i+1), adcMax,0,adcMax, adcMax,0,adcMax);

      h2_zdcPlus_adcTS0_adcTS4.at(i) = new TH2F(Form("TS4 vs TS0: ZDC+, EM%d",i+1), Form("TS4 vs TS0: ZDC+, EM%d",i+1), adcMax,0,adcMax, adcMax,0,adcMax);
      h2_zdcNeg_adcTS0_adcTS4.at(i) = new TH2F(Form("TS4 vs TS0: ZDC-, EM%d",i+1), Form("TS4 vs TS0: ZDC-, EM%d",i+1), adcMax,0,adcMax, adcMax,0,adcMax);

      h2_zdcPlus_adcTS0_adcTS5.at(i) = new TH2F(Form("TS5 vs TS0: ZDC+, EM%d",i+1), Form("TS5 vs TS0: ZDC+, EM%d",i+1), adcMax,0,adcMax, adcMax,0,adcMax);
      h2_zdcNeg_adcTS0_adcTS5.at(i) = new TH2F(Form("TS5 vs TS0: ZDC-, EM%d",i+1), Form("TS5 vs TS0: ZDC-, EM%d",i+1), adcMax,0,adcMax, adcMax,0,adcMax);
	}
      if (i>4 && i<8)
	{
	  h2_zdcPlus_adcTS0_adcTS1.at(i) = new TH2F(Form("ZDC+, Dummy %d",i-4), Form("ZDC+, Dummy %d",i-4), adcMax,0,adcMax, adcMax,0,adcMax);
      h2_zdcNeg_adcTS0_adcTS1.at(i) = new TH2F(Form("ZDC-, Dummy %d",i-4), Form("ZDC-, Dummy %d",i-4), adcMax,0,adcMax, adcMax,0,adcMax);

      h2_zdcPlus_adcTS0_adcTS2.at(i) = new TH2F(Form("TS2 vs TS0: ZDC+, Dummy %d",i-4), Form("TS2 vs TS0: ZDC+, Dummy %d",i-4), adcMax,0,adcMax, adcMax,0,adcMax);
      h2_zdcNeg_adcTS0_adcTS2.at(i) = new TH2F(Form("TS2 vs TS0: ZDC-, Dummy %d",i-4), Form("TS2 vs TS0: ZDC-, Dummy %d",i-4), adcMax,0,adcMax, adcMax,0,adcMax);

      h2_zdcPlus_adcTS0_adcTS3.at(i) = new TH2F(Form("TS3 vs TS0: ZDC+, Dummy %d",i-4), Form("TS3 vs TS0: ZDC+, Dummy %d",i-4), adcMax,0,adcMax, adcMax,0,adcMax);
      h2_zdcNeg_adcTS0_adcTS3.at(i) = new TH2F(Form("TS3 vs TS0: ZDC-, Dummy %d",i-4), Form("TS3 vs TS0: ZDC-, Dummy %d",i-4), adcMax,0,adcMax, adcMax,0,adcMax);

      h2_zdcPlus_adcTS0_adcTS4.at(i) = new TH2F(Form("TS4 vs TS0: ZDC+, Dummy %d",i-4), Form("TS4 vs TS0: ZDC+, Dummy %d",i-4), adcMax,0,adcMax, adcMax,0,adcMax);
      h2_zdcNeg_adcTS0_adcTS4.at(i) = new TH2F(Form("TS4 vs TS0: ZDC-, Dummy %d",i-4), Form("TS4 vs TS0: ZDC-, Dummy %d",i-4), adcMax,0,adcMax, adcMax,0,adcMax);

      h2_zdcPlus_adcTS0_adcTS5.at(i) = new TH2F(Form("TS5 vs TS0: ZDC+, Dummy %d",i-4), Form("TS5 vs TS0: ZDC+, Dummy %d",i-4), adcMax,0,adcMax, adcMax,0,adcMax);
      h2_zdcNeg_adcTS0_adcTS5.at(i) = new TH2F(Form("TS5 vs TS0: ZDC-, Dummy %d",i-4), Form("TS5 vs TS0: ZDC-, Dummy %d",i-4), adcMax,0,adcMax, adcMax,0,adcMax);
	}
      if (i>7 && i<12)
	{
	  h2_zdcPlus_adcTS0_adcTS1.at(i) = new TH2F(Form("ZDC+, HAD%d",i-7), Form("ZDC+, HAD%d",i-7), adcMax,0,adcMax, adcMax,0,adcMax);
          h2_zdcNeg_adcTS0_adcTS1.at(i) = new TH2F(Form("ZDC-, HAD%d",i-7), Form("ZDC-, HAD%d",i-7), adcMax,0,adcMax, adcMax,0,adcMax);

	  h2_zdcPlus_adcTS0_adcTS2.at(i) = new TH2F(Form("TS2 vs TS1: ZDC+, HAD%d",i-7), Form("TS2 vs TS1: ZDC+, HAD%d",i-7), adcMax,0,adcMax, adcMax,0,adcMax);
          h2_zdcNeg_adcTS0_adcTS2.at(i) = new TH2F(Form("TS2 vs TS1: ZDC-, HAD%d",i-7), Form("TS2 vs TS1: ZDC-, HAD%d",i-7), adcMax,0,adcMax, adcMax,0,adcMax);

	  h2_zdcPlus_adcTS0_adcTS3.at(i) = new TH2F(Form("TS3 vs TS1: ZDC+, HAD%d",i-7), Form("TS3 vs TS1: ZDC+, HAD%d",i-7), adcMax,0,adcMax, adcMax,0,adcMax);
          h2_zdcNeg_adcTS0_adcTS3.at(i) = new TH2F(Form("TS3 vs TS1: ZDC-, HAD%d",i-7), Form("TS3 vs TS1: ZDC-, HAD%d",i-7), adcMax,0,adcMax, adcMax,0,adcMax);

	  h2_zdcPlus_adcTS0_adcTS4.at(i) = new TH2F(Form("TS4 vs TS1: ZDC+, HAD%d",i-7), Form("TS4 vs TS1: ZDC+, HAD%d",i-7), adcMax,0,adcMax, adcMax,0,adcMax);
          h2_zdcNeg_adcTS0_adcTS4.at(i) = new TH2F(Form("TS4 vs TS1: ZDC-, HAD%d",i-7), Form("TS4 vs TS1: ZDC-, HAD%d",i-7), adcMax,0,adcMax, adcMax,0,adcMax);

	  h2_zdcPlus_adcTS0_adcTS5.at(i) = new TH2F(Form("TS5 vs TS0: ZDC+, HAD%d",i-7), Form("TS5 vs TS0: ZDC+, HAD%d",i-7), adcMax,0,adcMax, adcMax,0,adcMax);
          h2_zdcNeg_adcTS0_adcTS5.at(i) = new TH2F(Form("TS5 vs TS0: ZDC-, HAD%d",i-7), Form("TS5 vs TS0: ZDC-, HAD%d",i-7), adcMax,0,adcMax, adcMax,0,adcMax);

	  
	  
	}
      if (i>11 && i<28)
	{
	  h2_zdcPlus_adcTS0_adcTS1.at(i) = new TH2F(Form("ZDC+, RPD%d",i-11), Form("ZDC+, RPD%d",i-11), adcMax,0,adcMax, adcMax,0,adcMax);
          h2_zdcNeg_adcTS0_adcTS1.at(i) = new TH2F(Form("ZDC-, RPD%d",i-11), Form("ZDC-, RPD%d",i-11), adcMax,0,adcMax, adcMax,0,adcMax);

	  h2_zdcPlus_adcTS0_adcTS2.at(i) = new TH2F(Form("TS2 vs TS0: ZDC+, RPD%d",i-11), Form("TS2 vs TS0: ZDC+, RPD%d",i-11), adcMax,0,adcMax, adcMax,0,adcMax);
          h2_zdcNeg_adcTS0_adcTS2.at(i) = new TH2F(Form("TS2 vs TS0: ZDC-, RPD%d",i-11), Form("TS2 vs TS0: ZDC-, RPD%d",i-11), adcMax,0,adcMax, adcMax,0,adcMax);

	  h2_zdcPlus_adcTS0_adcTS3.at(i) = new TH2F(Form("TS3 vs TS0: ZDC+, RPD%d",i-11), Form("TS3 vs TS0: ZDC+, RPD%d",i-11), adcMax,0,adcMax, adcMax,0,adcMax);
          h2_zdcNeg_adcTS0_adcTS3.at(i) = new TH2F(Form("TS3 vs TS0: ZDC-, RPD%d",i-11), Form("TS3 vs TS0: ZDC-, RPD%d",i-11), adcMax,0,adcMax, adcMax,0,adcMax);

	  h2_zdcPlus_adcTS0_adcTS4.at(i) = new TH2F(Form("TS4 vs TS0: ZDC+, RPD%d",i-11), Form("TS4 vs TS0: ZDC+, RPD%d",i-11), adcMax,0,adcMax, adcMax,0,adcMax);
          h2_zdcNeg_adcTS0_adcTS4.at(i) = new TH2F(Form("TS4 vs TS0: ZDC-, RPD%d",i-11), Form("TS4 vs TS0: ZDC-, RPD%d",i-11), adcMax,0,adcMax, adcMax,0,adcMax);

	  h2_zdcPlus_adcTS0_adcTS5.at(i) = new TH2F(Form("TS5 vs TS0: ZDC+, RPD%d",i-11), Form("TS5 vs TS0: ZDC+, RPD%d",i-11), adcMax,0,adcMax, adcMax,0,adcMax);
          h2_zdcNeg_adcTS0_adcTS5.at(i) = new TH2F(Form("TS5 vs TS0: ZDC-, RPD%d",i-11), Form("TS5 vs TS0: ZDC-, RPD%d",i-11), adcMax,0,adcMax, adcMax,0,adcMax);

	  
	}
      
    }


  vector<float> temp0_adcPlus_array, temp0_adcNeg_array;
  vector<float> temp1_adcPlus_array, temp1_adcNeg_array;
  vector<float> temp2_adcPlus_array, temp2_adcNeg_array;
  vector<float> temp3_adcPlus_array, temp3_adcNeg_array;
  vector<float> temp4_adcPlus_array, temp4_adcNeg_array;
  vector<float> temp5_adcPlus_array, temp5_adcNeg_array;


  // evt loop
  for (int i=0; i<zdcEnt; i++)
    {
      zdcTree->GetEntry(i);
      hltAnalysisTree->GetEntry(i);

      
      // channels 0-11 and 24-39 are neg
      // channels 12-23 and 40-55 are pos

      //cout << "EVENT==============================" << i << endl;
      //cout << "Evt Number============" << Event << endl;
      
      
      temp0_adcPlus_array.resize(0), temp0_adcNeg_array.resize(0);
      temp1_adcPlus_array.resize(0), temp1_adcNeg_array.resize(0);
      temp2_adcPlus_array.resize(0), temp2_adcNeg_array.resize(0);
      temp3_adcPlus_array.resize(0), temp3_adcNeg_array.resize(0);
      temp4_adcPlus_array.resize(0), temp4_adcNeg_array.resize(0);
      temp5_adcPlus_array.resize(0), temp5_adcNeg_array.resize(0);
      
      for (int ch=0; ch<n; ch++)
	{
	  // neg zSide
	  if (ch<12 || (ch>23 && ch<40))
	    {
	      temp0_adcNeg_array.push_back(adc_0[ch]);
	      temp1_adcNeg_array.push_back(adc_1[ch]);
	      temp2_adcNeg_array.push_back(adc_2[ch]);
	      temp3_adcNeg_array.push_back(adc_3[ch]);
	      temp4_adcNeg_array.push_back(adc_4[ch]);
	      temp5_adcNeg_array.push_back(adc_5[ch]);
	      
	    }
	  // pos zSide
	  if ((ch>11 && ch<24) || (ch>39 && ch<56))
	    {
	      temp0_adcPlus_array.push_back(adc_0[ch]);
	      temp1_adcPlus_array.push_back(adc_1[ch]);
	      temp2_adcPlus_array.push_back(adc_2[ch]);
	      temp3_adcPlus_array.push_back(adc_3[ch]);
	      temp4_adcPlus_array.push_back(adc_4[ch]);
	      temp5_adcPlus_array.push_back(adc_5[ch]);
	      
	    }
	} // end ch loop

      for (int j=0; j<28; j++)
	{
	  h_zdcNeg_adc.at(j)->Fill(temp0_adcNeg_array.at(j));
	  h_zdcPlus_adc.at(j)->Fill(temp0_adcPlus_array.at(j));

	  // TS0 TS1
	  h2_zdcPlus_adcTS0_adcTS1.at(j)->Fill(temp0_adcPlus_array.at(j), temp1_adcPlus_array.at(j));
	  h2_zdcNeg_adcTS0_adcTS1.at(j)->Fill(temp0_adcNeg_array.at(j), temp1_adcNeg_array.at(j));

	  // TS0 TS2
	  h2_zdcPlus_adcTS0_adcTS2.at(j)->Fill(temp0_adcPlus_array.at(j), temp2_adcPlus_array.at(j));
	  h2_zdcNeg_adcTS0_adcTS2.at(j)->Fill(temp0_adcNeg_array.at(j), temp2_adcNeg_array.at(j));

	  // TS0 TS3
	  h2_zdcPlus_adcTS0_adcTS3.at(j)->Fill(temp0_adcPlus_array.at(j), temp3_adcPlus_array.at(j));
	  h2_zdcNeg_adcTS0_adcTS3.at(j)->Fill(temp0_adcNeg_array.at(j), temp3_adcNeg_array.at(j));

	  // TS0 TS4
	  h2_zdcPlus_adcTS0_adcTS4.at(j)->Fill(temp0_adcPlus_array.at(j), temp4_adcPlus_array.at(j));
	  h2_zdcNeg_adcTS0_adcTS4.at(j)->Fill(temp0_adcNeg_array.at(j), temp4_adcNeg_array.at(j));

	  // TS0 TS5
	  h2_zdcPlus_adcTS0_adcTS5.at(j)->Fill(temp0_adcPlus_array.at(j), temp5_adcPlus_array.at(j));
	  h2_zdcNeg_adcTS0_adcTS5.at(j)->Fill(temp0_adcNeg_array.at(j), temp5_adcNeg_array.at(j));
	}     
      
      
    } // end evt loop


  float coeffPos[5] = {0};
  float coeffNeg[5] = {0};
  
  // Plotting
  TCanvas *canvasPlus[zdc_channelNumber], *canvasNeg[zdc_channelNumber], *c2[zdc_channelNumber], *c4[zdc_channelNumber], *c3[zdc_channelNumber];
  for (int i=0; i<zdc_channelNumber; i++)
    {
      canvasPlus[i] = new TCanvas(Form("canvasPlus_%d",i), Form("canvasPlus_%d",i),850,850);
      canvasPlus[i]->Divide(2,1);
      canvasPlus[i]->cd(1);
      h2_zdcNeg_adcTS0_adcTS1.at(i)->GetXaxis()->SetTitle("ADC Value (TS0)");
      h2_zdcNeg_adcTS0_adcTS1.at(i)->GetYaxis()->SetTitle("ADC Value (TS1)");
      h2_zdcNeg_adcTS0_adcTS1.at(i)->Draw();
      float corrFactor_1M = h2_zdcNeg_adcTS0_adcTS1.at(i)->GetCorrelationFactor();
      if (i==8) coeffNeg[0]=corrFactor_1M;
      drawText(0.15, 0.7, Form("corr Factor = %.2f", corrFactor_1M));
      
      canvasPlus[i]->cd(2);
      h2_zdcPlus_adcTS0_adcTS1.at(i)->GetXaxis()->SetTitle("ADC Value (TS0)");
      h2_zdcPlus_adcTS0_adcTS1.at(i)->GetYaxis()->SetTitle("ADC Value (TS1)");
      h2_zdcPlus_adcTS0_adcTS1.at(i)->Draw();
      float corrFactor_1P = h2_zdcPlus_adcTS0_adcTS1.at(i)->GetCorrelationFactor();
      if (i==8) coeffPos[0]=corrFactor_1P;
      drawText(0.15, 0.7, Form("corr Factor = %.2f", corrFactor_1P));

      canvasPlus[i]->Update();


      c2[i] = new TCanvas(Form("c2_%d",i), Form("c2_%d",i),850,850);
      c2[i]->Divide(2,1);
      c2[i]->cd(1);
      h2_zdcNeg_adcTS0_adcTS2.at(i)->GetXaxis()->SetTitle("ADC Value (TS0)");
      h2_zdcNeg_adcTS0_adcTS2.at(i)->GetYaxis()->SetTitle("ADC Value (TS2)");
      h2_zdcNeg_adcTS0_adcTS2.at(i)->Draw();
      float corrFactor_2M = h2_zdcNeg_adcTS0_adcTS2.at(i)->GetCorrelationFactor();
      if (i==8) coeffNeg[1]=corrFactor_2M;
      drawText(0.15, 0.7, Form("corr Factor = %.2f", corrFactor_2M));

      c2[i]->cd(2);
      h2_zdcPlus_adcTS0_adcTS2.at(i)->GetXaxis()->SetTitle("ADC Value (TS0)");
      h2_zdcPlus_adcTS0_adcTS2.at(i)->GetYaxis()->SetTitle("ADC Value (TS2");
      h2_zdcPlus_adcTS0_adcTS2.at(i)->Draw();
      float corrFactor_2P = h2_zdcPlus_adcTS0_adcTS2.at(i)->GetCorrelationFactor();
      if (i==8) coeffPos[1]=corrFactor_2P;
      drawText(0.15, 0.7, Form("corr Factor = %.2f", corrFactor_2P));

      

      canvasNeg[i] = new TCanvas(Form("canvasNeg_%d",i), Form("canvasNeg_%d",i),850,850);
      canvasNeg[i]->Divide(2,1);
      canvasNeg[i]->cd(1);
      h2_zdcNeg_adcTS0_adcTS3.at(i)->GetXaxis()->SetTitle("ADC Value (TS0)");
      h2_zdcNeg_adcTS0_adcTS3.at(i)->GetYaxis()->SetTitle("ADC Value (TS3)");
      h2_zdcNeg_adcTS0_adcTS3.at(i)->Draw();
      float corrFactor_3M = h2_zdcNeg_adcTS0_adcTS3.at(i)->GetCorrelationFactor();
      if (i==8) coeffNeg[2]=corrFactor_3M;
      drawText(0.15, 0.7, Form("corr Factor = %.2f", corrFactor_3M));

      canvasNeg[i]->cd(2);
      h2_zdcPlus_adcTS0_adcTS3.at(i)->GetXaxis()->SetTitle("ADC Value (TS0)");
      h2_zdcPlus_adcTS0_adcTS3.at(i)->GetYaxis()->SetTitle("ADC Value (TS3)");
      h2_zdcPlus_adcTS0_adcTS3.at(i)->Draw();
      float corrFactor_3P = h2_zdcPlus_adcTS0_adcTS3.at(i)->GetCorrelationFactor();
      if (i==8) coeffPos[2]=corrFactor_3P;
      drawText(0.15, 0.7, Form("corr Factor = %.2f", corrFactor_3P));





      c4[i] = new TCanvas(Form("c4_%d",i), Form("c4_%d",i),850,850);
      c4[i]->Divide(2,1);
      c4[i]->cd(1);
      h2_zdcNeg_adcTS0_adcTS4.at(i)->GetXaxis()->SetTitle("ADC Value (TS0)");
      h2_zdcNeg_adcTS0_adcTS4.at(i)->GetYaxis()->SetTitle("ADC Value (TS4)");
      h2_zdcNeg_adcTS0_adcTS4.at(i)->Draw();
      float corrFactor_4M = h2_zdcNeg_adcTS0_adcTS4.at(i)->GetCorrelationFactor();
      if (i==8) coeffNeg[3]=corrFactor_4M;
      drawText(0.15, 0.7, Form("corr Factor = %.2f", corrFactor_4M));

      c4[i]->cd(2);
      h2_zdcPlus_adcTS0_adcTS4.at(i)->GetXaxis()->SetTitle("ADC Value (TS0)");
      h2_zdcPlus_adcTS0_adcTS4.at(i)->GetYaxis()->SetTitle("ADC Value (TS4");
      h2_zdcPlus_adcTS0_adcTS4.at(i)->Draw();
      float corrFactor_4P = h2_zdcPlus_adcTS0_adcTS4.at(i)->GetCorrelationFactor();
      if (i==8) coeffPos[3]=corrFactor_4P;
      drawText(0.15, 0.7, Form("corr Factor = %.2f", corrFactor_4P));




      
      c3[i] = new TCanvas(Form("c3_%d",i), Form("c3_%d",i),850,850);
      c3[i]->Divide(2,1);
      c3[i]->cd(1);
      h2_zdcNeg_adcTS0_adcTS5.at(i)->GetXaxis()->SetTitle("ADC Value (TS0)");
      h2_zdcNeg_adcTS0_adcTS5.at(i)->GetYaxis()->SetTitle("ADC Value (TS5)");
      h2_zdcNeg_adcTS0_adcTS5.at(i)->Draw();
      float corrFactor_5M = h2_zdcNeg_adcTS0_adcTS5.at(i)->GetCorrelationFactor();
      if (i==8) coeffNeg[4]=corrFactor_5M;
      drawText(0.15, 0.7, Form("corr Factor = %.2f", corrFactor_5M));

      c3[i]->cd(2);
      h2_zdcPlus_adcTS0_adcTS5.at(i)->GetXaxis()->SetTitle("ADC Value (TS0)");
      h2_zdcPlus_adcTS0_adcTS5.at(i)->GetYaxis()->SetTitle("ADC Value (TS5)");
      h2_zdcPlus_adcTS0_adcTS5.at(i)->Draw();
      float corrFactor_5P = h2_zdcPlus_adcTS0_adcTS5.at(i)->GetCorrelationFactor();
      if (i==8) coeffPos[4]=corrFactor_5P;
      drawText(0.15, 0.7, Form("corr Factor = %.2f", corrFactor_5P));
      
    } // end canvas loop


  // Print on PDF
  canvasPlus[0]->Print("adcts1_vs_adcts0.pdf(","pdf");
  canvasNeg[0]->Print("adcts3_vs_adcts0.pdf(","pdf");
  c2[0]->Print("adcts2_vs_adcts0.pdf(","pdf");
  c4[0]->Print("adcts4_vs_adcts0.pdf(","pdf");
  c3[0]->Print("adcts5_vs_adcts0.pdf(","pdf");
  for (int j=1; j<(zdc_channelNumber-1); j++)
    {
      canvasPlus[j]->Print("adcts1_vs_adcts0.pdf","pdf");
      canvasNeg[j]->Print("adcts3_vs_adcts0.pdf","pdf");
      c2[j]->Print("adcts2_vs_adcts0.pdf","pdf");
      c4[j]->Print("adcts4_vs_adcts0.pdf","pdf");
      c3[j]->Print("adcts5_vs_adcts0.pdf","pdf");
    }
  canvasPlus[27]->Print("adcts1_vs_adcts0.pdf)","pdf");
  canvasNeg[27]->Print("adcts3_vs_adcts0.pdf)","pdf");
  c2[27]->Print("adcts2_vs_adcts0.pdf)","pdf");
  c4[27]->Print("adcts4_vs_adcts0.pdf)","pdf");
  c3[27]->Print("adcts5_vs_adcts0.pdf)","pdf");



  



  


  
  
}
