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
//input with fsc = /eos/cms/store/group/phys_heavyions/nbarnett/HiForest/DATA/2026PbPb/CRAB_UserFiles/crab_HiForest_run404350_RP_v5/260527_162844/0000/
// inpu with zdc = /eos/cms/store/group/phys_heavyions/wangj/L1PbPb2026/HIPhysicsRawPrime/crab_forestadc_260524_PhysicsHIPhysicsRawPrime_404359_ZB_partial/260527_123027/0000/
int plotBananaPlotExclusive(
		  char const *input = "/eos/cms/store/group/phys_heavyions/nbarnett/HiForest/DATA/2026PbPb/CRAB_UserFiles/crab_HiForest_run404350_RP_v5/260527_162844/0000/") {

    std::cout << "here" << std::endl;

    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);

    string tag = "Run404350"; 


  /* read in all files in the input folder */
  vector<string> files;
  GetFiles(input, files);

  /* read in the unpacked information */
  TChain zdcChain("zdcanalyzer/zdcrechit");
  FillChain(zdcChain, files);
  TTreeReader zdcReader(&zdcChain);
  TTreeReaderValue<float> sumPlus(zdcReader, "sumPlus");
  TTreeReaderValue<float> sumMinus(zdcReader, "sumMinus");

 TChain fscChain("fscanalyzer/fscdigi");
  FillChain(fscChain, files);
  TTreeReader fscReader(&fscChain);
  TTreeReaderValue<float> fscSumPlus(fscReader, "sumPlus");
  TTreeReaderValue<float> fscSumMinus(fscReader, "sumMinus");
  TTreeReaderArray<int> adc(fscReader, "adcTs2"); 
  TTreeReaderArray<int> ped(fscReader, "adcTs1"); 
  TTreeReaderArray<int> zside(fscReader, "zside");

    /* read in trigger information */
  TChain trigChain("hltanalysis/HltTree");
  FillChain(trigChain, files);
  TTreeReader trigReader(&trigChain);
  TTreeReaderValue<int> zb(trigReader, "L1_ZeroBias");
  TTreeReaderValue<int> minBias(trigReader, "HLT_HIMinimumBiasHF1AND_v8"); 


  /* read in the primary vertex filter*/
  TChain vertexChain("skimanalysis/HltTree");
  FillChain(vertexChain, files);
  TTreeReader vertexReader(&vertexChain);
  TTreeReaderValue<int> vertex(vertexReader, "pprimaryVertexFilter");
  TTreeReaderValue<int> coincidence(vertexReader, "pphfCoincFilterPF2Th7"); 


  /* read in the HF info */
  TChain eventChain("hiEvtAnalyzer/HiTree");
  FillChain(eventChain, files);
  TTreeReader eventReader(&eventChain);
  TTreeReaderValue<float> hfEsum(eventReader, "hiHF");
  TTreeReaderValue<float>   zVertex(eventReader, "vz");
  TTreeReaderValue<float> hFEsumPlus(eventReader, "hiHFPlus_pf"); 
  TTreeReaderValue<float> hFEsumMinus(eventReader, "hiHFMinus_pf");
  TTreeReaderValue<int> hNTracks(eventReader, "hiNtracks"); 

  /* create histograms */
  TH2D* bananaPlot         = new TH2D("bananaPlot", "", 100, 250, 7000, 1000, 0, 300000); 
  TH2D* bananaPlotFSCADC   = new TH2D("bananaPlotFSCADC", "", 100, 0, 7000, 1000, 0, 3060); 
  TH2D* bananaPlotFSCminus = new TH2D("bananaPlotFSCADCminus", "", 50, 0, 3500, 500, 0, 1530);
  TH2D* bananaPlotFSCplus  = new TH2D("bananaPlotFSCADCplus", "", 50, 0, 3500, 500, 0, 1530);
  TH2D* zdcFSCcorr_minus   = new TH2D("zdcFSCcorr_minus", "", 500, 0, 150000, 500, 0, 1530);
  TH2D* zdcFSCcorr_plus   = new TH2D("zdcFSCcorr_plus", "", 500, 0, 150000, 500, 0, 1530);


  double maxZDC = -1; 
  double maxHF = -1; 
  double maxFSCADC = -1; 
  Long64_t totalEvents = zdcReader.GetEntries(true);
  for (Long64_t i = 0; i < totalEvents; i++) {
    zdcReader.Next(); trigReader.Next(); vertexReader.Next(); eventReader.Next(); fscReader.Next(); 
    
    // zero bias selection
    if(*zb!= 1) continue;

    // event selection of exclusive events
    if(*hFEsumPlus > 10 || *hFEsumMinus > 10) continue; 
    if(*hNTracks != 0) continue; 

    if (i % 10000 == 0) {
      cout << "Event " << i << endl;
    }

    double sumFSCADC   = 0; 
    double sumFSCplus  = 0; 
    double sumFSCminus = 0; 
    for(int c = 0; c < 12; c++){
        sumFSCADC += adc[c]; 
        if(zside[c] < 0) sumFSCminus += adc[c]; 
        if(zside[c] > 0) sumFSCplus += adc[c];
    }   


    double sum = *sumPlus + *sumMinus; 
    double sumFSC = *fscSumPlus + *fscSumMinus;

    if(sum > maxZDC) maxZDC = sum; 
    if (*hfEsum > maxHF) maxHF = *hfEsum; 
    if(sumFSCADC > maxFSCADC) maxFSCADC= sumFSCADC; 


    //if(*hfEsum > 1000) std::cout << "ZDC sum: " << sum << " HF sum: " << *hfEsum << std::endl;

    bananaPlot->Fill(*hfEsum, sum); 
    bananaPlotFSCADC->Fill(*hfEsum, sumFSCADC); 
    bananaPlotFSCplus->Fill(*hFEsumPlus, sumFSCplus);
    bananaPlotFSCminus->Fill(*hFEsumMinus, sumFSCminus); 
    zdcFSCcorr_minus->Fill(*sumMinus, *fscSumMinus); 
    zdcFSCcorr_plus->Fill(*sumPlus, *fscSumPlus); 

  } // end loop over  the  number of events

    std::cout << "maxHF sum: " << maxHF << std::endl; 
    std::cout << "maxZDC sum: " << maxZDC << std::endl; 
    std::cout << "maxFSCADCSuM: " << maxFSCADC << std::endl;

    TFile* outfile = new TFile("BananaPlot_FSCCExclusive.root",  "RECREATE");
    outfile->cd();
    bananaPlot->Write(); 
    bananaPlotFSCADC->Write();
    bananaPlotFSCplus->Write(); 
    bananaPlotFSCminus->Write(); 
    zdcFSCcorr_minus->Write(); 
    zdcFSCcorr_plus->Write(); 
    outfile->Close();

  return 1;
}

int main(int argc, char *argv[]) {
  if (argc == 2)
    return plotBananaPlotExclusive(argv[1]);
  else {
    cout << "ERROR" << endl;
    return -1;
  }
}
