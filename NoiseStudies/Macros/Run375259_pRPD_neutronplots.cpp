#include "TFile.h"
#include "TProfile.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TLegend.h"
#include <sstream>
#include <iostream>
#include <cstdio>
#include "TCanvas.h"
#include "TChain.h"
#include "THStack.h"

void Run375259_pRPD_neutronplots()
{
    TChain *zdcchain = new TChain();
    TChain *hichain = new TChain();
    for (int x = 1 ; x < 135 ; x++){
    if(x == 116) continue;
    zdcchain->Add(Form("/store/data/Runs_2023/375259/240112_203159/0000/HiForestMiniAOD_%i.root/zdcanalyzer/zdcdigi", x));
    hichain->Add(Form("/store/data/Runs_2023/375259/240112_203159/0000/HiForestMiniAOD_%i.root/hiEvtAnalyzer/HiTree", x));
    }

    zdcchain->AddFriend(hichain);


    int hibin = 0;
    int zside = 1;
    double zdcside;
    int section = 4;
    double  zdcsection;
    int channel; 


}