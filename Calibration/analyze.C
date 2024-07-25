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
#include "TStyle.h"

#include <string>
#include <iomanip>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

int analyze(char const *filename="/afs/cern.ch/user/m/mcsanad/zdc2023calib_temp_dir_for_crab/L1Ntuple.374828.root", long unsigned int firstEvent=0, long unsigned int lastEvent=0)
{
  TStyle* gStyle = new TStyle();
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  string tag(filename);
  tag.erase(tag.size()-5);
  size_t pos = tag.find_last_of('/');
  tag = (pos != std::string::npos) ? tag.substr(pos+1) : tag;

  vector<string> files;
  string fn(filename);
  if(fn.substr(fn.size()-4)=="root")
    files.push_back(filename);
  else
  {
    ifstream infile(filename);
    string rootfile("");
    while(infile >> rootfile)
      files.push_back(rootfile);
  }

  cout << "Read " << files.size() << " files: " << endl;
  for(auto& it : files) cout << it.c_str() << endl;

  TChain zdcChain("zdcanalyzer/zdcdigi");
  for (auto file : files) zdcChain.Add(file.c_str());
  TTreeReader zdcReader(&zdcChain);
  TTreeReaderValue<float> sumPlus(zdcReader, "sumPlus");
  TTreeReaderValue<float> sumMinus(zdcReader, "sumMinus");
  TTreeReaderArray<int> zside(zdcReader, "zside"); //0->plus, 1->minus
  TTreeReaderArray<int> section(zdcReader, "section"); //1->EM, 2->HAD, 4->RPD
  TTreeReaderArray<int> channel(zdcReader, "channel"); //1-5->EM, 1-4->HAD, 1-16->RPD
  TTreeReaderArray<float> fCTS0(zdcReader, "chargefCTs0");
  TTreeReaderArray<float> fCTS1(zdcReader, "chargefCTs1");
  TTreeReaderArray<float> fCTS2(zdcReader, "chargefCTs2");
  TTreeReaderArray<float> fCTS3(zdcReader, "chargefCTs3");
  TTreeReaderArray<float> fCTS4(zdcReader, "chargefCTs4");
  TTreeReaderArray<float> fCTS5(zdcReader, "chargefCTs5");
  TTreeReaderArray<float> fCTS6(zdcReader, "chargefCTs6");
  TTreeReaderArray<float> fCTS7(zdcReader, "chargefCTs7");
  TTreeReaderArray<float> fCTS8(zdcReader, "chargefCTs8");
  TTreeReaderArray<float> fCTS9(zdcReader, "chargefCTs9");

  const float cTSbkg = 0.4;
  //const float cTSbkg = 1.0;
  const int NSide = 2; //0: plus, 1: minus
  const char* sSide[NSide] = {"P","M"};
  const char* tSide[NSide] = {"#plus","#minus"};
  const int NEMHAD = 10;
  const float cEMHAD[NEMHAD][NSide] = {{0.08,0.08},{0.10,0.10},{0.12,0.12},{0.14,0.14},{0.16,0.16},{0.18,0.18},{0.20,0.20},{0.22,0.22},{0.24,0.24},{0.26,0.26}}; 
  const int NCh = 9; //5 EM + 4 HAD
  const float cEM = 0.1;
  const float cfCTeV[NSide] = {0.5031, 0.9397};
  //const float cMinus = 0.5031;
  //const float cPlus = 0.9397;
  //double calibconst[NSide][NCh] = { {1, 1, 1, 1, 1,   1, 1, 1, 1},
  //                                  {1, 1, 1, 1, 1,   1, 1, 1, 1} };
  // EM calib parameters from Alice M, testbeam_summary_20230922.pdf 
  double calibconst[NSide][NCh] = { {0.60, 0.89, 1.00, 1.29, 0.57, 1, 1, 1, 1},
                                    {1.41, 1.87, 1.00, 1.28, 1.25, 1, 1, 1, 1} };
  // After MC-based intercalibration, does not improve resolution
  //double calibconst[NSide][NCh] = { {1, 1, 1, 1, 1,   1.86, 0.86, 0.97, 0.84},
  //                                  {1, 1, 1, 1, 1,   1.00, 1.93, 1.17, 1.26} };

  //TH1D* hZDCP_sumvar = new TH1D("hZDCP_sumvar", "ZDC sumPlus variable", 100, 1000, 200000);
  TH1D* hZDC[NSide];
  TH1D* hZDC_1n[NSide];
  TH1 *ZDC_1n_EMHAD[NSide][NEMHAD];
  TH2 *ZDC_EMHAD[NSide][NEMHAD];
  for(int iSide=0;iSide<NSide;iSide++)
  {
    hZDC[iSide] = new TH1D(Form("hZDC%s",sSide[iSide]), Form("ZDC%s  Energy",tSide[iSide]), 20000, 0, 200000);
    hZDC_1n[iSide] = new TH1D(Form("hZDC%s_1n",sSide[iSide]), Form("ZDC%s Energy",tSide[iSide]), 2000, 0, 20000);
    for(int iEMHAD=0;iEMHAD<NEMHAD;iEMHAD++)
    {
      ZDC_1n_EMHAD[iSide][iEMHAD] = new TH1D(Form("ZDC%s_1n_EMHAD_%i",sSide[iSide],iEMHAD),Form("ZDC%s;E_{HAD}+%.2fE_{EM} [TeV];N [a.u.]",tSide[iSide],cEMHAD[iEMHAD][0]),2e3,0,2.0e4);
      ZDC_EMHAD[iSide][iEMHAD] = new TH2D(Form("ZDC%s_EMHAD_%i",sSide[iSide],iEMHAD),Form("ZDC%s, EM vs HAD;E_{HAD}+%.2fE_{EM} [TeV];E_{EM} [fC]",tSide[iSide],cEMHAD[iEMHAD][0]),100,0,10000,100,0,2000);
    }
  }

  long unsigned int totalEvents = zdcReader.GetEntries(true);
  cerr << "Tree has " << totalEvents << " events, analyzing range " << firstEvent << "-" << lastEvent << endl;
  if(firstEvent<=1 || firstEvent>=totalEvents) firstEvent=0;
  if(lastEvent<=1  || lastEvent>=totalEvents) lastEvent=totalEvents;
  zdcReader.SetEntriesRange(firstEvent,lastEvent);
  for (long unsigned int iEvent = 0; iEvent < lastEvent-firstEvent; iEvent++) 
  {
    zdcReader.Next();
    if(iEvent % 1000 == 0) cerr << "Event " << iEvent << endl;

    float ZDCsig[NSide][NEMHAD] = {0};
    float EMsig[NSide] = {0};
    float HADsig[NSide] = {0};
    for(int iSide=0;iSide<NSide;iSide++)
    {
      for(int iCh=0; iCh<5; iCh++)   EMsig[iSide] +=  (fCTS2[iCh+iSide*NCh]-cTSbkg*fCTS1[iCh+iSide*NCh])*calibconst[iSide][iCh]*cfCTeV[iSide];
      for(int iCh=5; iCh<NCh; iCh++) HADsig[iSide] += (fCTS2[iCh+iSide*NCh]-cTSbkg*fCTS1[iCh+iSide*NCh])*calibconst[iSide][iCh]*cfCTeV[iSide];
      for(int iEMHAD=0;iEMHAD<NEMHAD;iEMHAD++) ZDCsig[iSide][iEMHAD] = EMsig[iSide]*cEMHAD[iEMHAD][iSide] + HADsig[iSide]; 
        //ZDCPsig[iEMHAD] += (fCTS2[iCh  ]-cTSbkg*fCTS1[iCh  ])*calibconst[0][iCh]*(iCh<5?cEMHAD[iEMHAD]:1.0)*cMinus;
        //ZDCMsig[iEMHAD] += (fCTS2[iCh+9]-cTSbkg*fCTS1[iCh+9])*calibconst[1][iCh]*(iCh<5?cEMHAD[iEMHAD]:1.0)*cPlus;
      int thisEMHAD = 1; //(c=0.1)
      hZDC[iSide]->Fill(ZDCsig[iSide][thisEMHAD]);
      hZDC_1n[iSide]->Fill(ZDCsig[iSide][thisEMHAD]);
      for(int iEMHAD=0;iEMHAD<NEMHAD;iEMHAD++)
      {
        ZDC_1n_EMHAD[iSide][iEMHAD]->Fill(ZDCsig[iSide][iEMHAD]);
        ZDC_EMHAD[iSide][iEMHAD]->Fill(ZDCsig[iSide][iEMHAD],EMsig[iSide]);
      }
    }
    //hZDCP_sumvar->Fill(*sumPlus);
    //if(iEvent % 1000 == 0) cout << "ZDC signal: " << *sumPlus << "\t" << *sumMinus << "\t" << ZDCPsig << "\t" << ZDCMsig << endl;
  }
  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
  std::cout << "Finished processing " << totalEvents << " events." << std::endl;
  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

  TFile* outfile = new TFile(Form("histograms_%s_%lu-%lu.root", tag.c_str(), firstEvent, lastEvent), "RECREATE");
  outfile->cd();
  for(int iSide=0;iSide<NSide;iSide++)
  {
    hZDC[iSide]->Write();
    hZDC_1n[iSide]->Write();
    for(int iEMHAD=0;iEMHAD<NEMHAD;iEMHAD++)
    {
      ZDC_EMHAD[iSide][iEMHAD]->Write();
      ZDC_1n_EMHAD[iSide][iEMHAD]->Write();
    }
  }
  outfile->Close();

  TCanvas* c = new TCanvas("c","c",800,600);
  c->SetLogy(1);

  c->SetLogx(1);
  hZDC[0]->SetLineColor(kRed);
  hZDC[1]->SetLineColor(kBlue);
  hZDC[0]->SetLineWidth(2);
  hZDC[1]->SetLineWidth(2);
  hZDC[1]->GetXaxis()->SetRangeUser(1000,200000);;
  hZDC[1]->GetXaxis()->SetTitle("ZDC Sum");
  hZDC[1]->SetTitle("ZDC Energy, calibrated sum");
  hZDC[1]->Draw();
  hZDC[0]->Draw("same");
  c->SaveAs(Form("../figs/ZDCEnCalibPM_%s_%lu-%lu.png", tag.c_str(), firstEvent, lastEvent));

  c->SetLogx(0);
  hZDC_1n[0]->SetLineColor(kRed);
  hZDC_1n[1]->SetLineColor(kBlue);
  hZDC_1n[0]->SetLineWidth(2);
  hZDC_1n[1]->SetLineWidth(2);
  hZDC_1n[1]->GetXaxis()->SetRangeUser(1000,15000);
  hZDC_1n[1]->GetXaxis()->SetTitle("ZDC Sum");
  hZDC_1n[1]->SetTitle("ZDC Energy, calibrated sum");
  hZDC_1n[1]->Draw();
  hZDC_1n[0]->Draw("same");
  c->SaveAs(Form("../figs/ZDCEnCalibPM_1n_%s_%lu-%lu.png", tag.c_str(), firstEvent, lastEvent));

  return 1;
}

int main(int argc, char *argv[]) {
  if (argc==1)      return analyze();
  else if (argc==2) return analyze(argv[1]);
  else if (argc==3) return analyze(argv[1],atoi(argv[2]));
  else if (argc==4) return analyze(argv[1],atoi(argv[2]),atoi(argv[3]));
  else {
    cout << "ERROR" << endl;
    return -1;
  }
}
