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

void Run375259_posRPDandEM()
{
    gROOT->ProcessLine("gErrorIgnoreLevel = 6001;");
    gROOT->ProcessLine("gPrintViaErrorHandler = kTRUE;");

      TChain *zdcchain = new TChain();
      TChain *hichain = new TChain();
      for (int x = 0 ; x < 24 ; x++){
      zdcchain->Add(Form("/store/data/Runs_2023/skims/375259/Run375259_HiForest_SkimMinBias%i.root/zdcdigi", x));
      hichain->Add(Form("/store/data/Runs_2023/skims/375259/Run375259_HiForest_SkimMinBias%i.root/HiTree", x));
      }

      zdcchain->AddFriend(hichain);
      
     //Time slice distributions for EM, HAD, and RPD on Pos side
    TH1F *Run375259_pRPD_TS[16][11] = {0};

        Run375259_pRPD_TS[0][0] = new TH1F("","Run 375259 pRPD Block 0, 0 - <10% Centrality",6,0,6);
        Run375259_pRPD_TS[1][0] = new TH1F("","Run 375259 pRPD Block 1, 0 - <10% Centrality",6,0,6);
        Run375259_pRPD_TS[2][0] = new TH1F("","Run 375259 pRPD Block 2, 0 - <10% Centrality",6,0,6);
        Run375259_pRPD_TS[3][0] = new TH1F("","Run 375259 pRPD Block 3, 0 - <10% Centrality",6,0,6);
        Run375259_pRPD_TS[4][0] = new TH1F("","Run 375259 pRPD Block 4, 0 - <10% Centrality",6,0,6);
        Run375259_pRPD_TS[5][0] = new TH1F("","Run 375259 pRPD Block 5, 0 - <10% Centrality",6,0,6);
        Run375259_pRPD_TS[6][0] = new TH1F("","Run 375259 pRPD Block 6, 0 - <10% Centrality",6,0,6);
        Run375259_pRPD_TS[7][0] = new TH1F("","Run 375259 pRPD Block 7, 0 - <10% Centrality",6,0,6);
        Run375259_pRPD_TS[8][0] = new TH1F("","Run 375259 pRPD Block 8, 0 - <10% Centrality",6,0,6);
        Run375259_pRPD_TS[9][0] = new TH1F("","Run 375259 pRPD Block 9, 0 - <10% Centrality",6,0,6);
        Run375259_pRPD_TS[10][0] = new TH1F("","Run 375259 pRPD Block 10, 0 - <10% Centrality",6,0,6);
        Run375259_pRPD_TS[11][0] = new TH1F("","Run 375259 pRPD Block 11, 0 - <10% Centrality",6,0,6);
        Run375259_pRPD_TS[12][0] = new TH1F("","Run 375259 pRPD Block 12, 0 - <10% Centrality",6,0,6);
        Run375259_pRPD_TS[13][0] = new TH1F("","Run 375259 pRPD Block 13, 0 - <10% Centrality",6,0,6);
        Run375259_pRPD_TS[14][0] = new TH1F("","Run 375259 pRPD Block 14, 0 - <10% Centrality",6,0,6);
        Run375259_pRPD_TS[15][0] = new TH1F("","Run 375259 pRPD Block 15, 0 - <10% Centrality",6,0,6);
        
        Run375259_pRPD_TS[0][1] = new TH1F("","Run 375259 pRPD Block 0, 10 - <20% Centrality",6,0,6);
        Run375259_pRPD_TS[1][1] = new TH1F("","Run 375259 pRPD Block 1, 10 - <20% Centrality",6,0,6);
        Run375259_pRPD_TS[2][1] = new TH1F("","Run 375259 pRPD Block 2, 10 - <20% Centrality",6,0,6);
        Run375259_pRPD_TS[3][1] = new TH1F("","Run 375259 pRPD Block 3, 10 - <20% Centrality",6,0,6);
        Run375259_pRPD_TS[4][1] = new TH1F("","Run 375259 pRPD Block 4, 10 - <20% Centrality",6,0,6);
        Run375259_pRPD_TS[5][1] = new TH1F("","Run 375259 pRPD Block 5, 10 - <20% Centrality",6,0,6);
        Run375259_pRPD_TS[6][1] = new TH1F("","Run 375259 pRPD Block 6, 10 - <20% Centrality",6,0,6);
        Run375259_pRPD_TS[7][1] = new TH1F("","Run 375259 pRPD Block 7, 10 - <20% Centrality",6,0,6);
        Run375259_pRPD_TS[8][1] = new TH1F("","Run 375259 pRPD Block 8, 10 - <20% Centrality",6,0,6);
        Run375259_pRPD_TS[9][1] = new TH1F("","Run 375259 pRPD Block 9, 10 - <20% Centrality",6,0,6);
        Run375259_pRPD_TS[10][1] = new TH1F("","Run 375259 pRPD Block 10, 10 - <20% Centrality",6,0,6);
        Run375259_pRPD_TS[11][1] = new TH1F("","Run 375259 pRPD Block 11, 10 - <20% Centrality",6,0,6);
        Run375259_pRPD_TS[12][1] = new TH1F("","Run 375259 pRPD Block 12, 10 - <20% Centrality",6,0,6);
        Run375259_pRPD_TS[13][1] = new TH1F("","Run 375259 pRPD Block 13, 10 - <20% Centrality",6,0,6);
        Run375259_pRPD_TS[14][1] = new TH1F("","Run 375259 pRPD Block 14, 10 - <20% Centrality",6,0,6);
        Run375259_pRPD_TS[15][1] = new TH1F("","Run 375259 pRPD Block 15, 10 - <20% Centrality",6,0,6);

        Run375259_pRPD_TS[0][2] = new TH1F("","Run 375259 pRPD Block 0, 20 - <30% Centrality",6,0,6);
        Run375259_pRPD_TS[1][2] = new TH1F("","Run 375259 pRPD Block 1, 20 - <30% Centrality",6,0,6);
        Run375259_pRPD_TS[2][2] = new TH1F("","Run 375259 pRPD Block 2, 20 - <30% Centrality",6,0,6);
        Run375259_pRPD_TS[3][2] = new TH1F("","Run 375259 pRPD Block 3, 20 - <30% Centrality",6,0,6);
        Run375259_pRPD_TS[4][2] = new TH1F("","Run 375259 pRPD Block 4, 20 - <30% Centrality",6,0,6);
        Run375259_pRPD_TS[5][2] = new TH1F("","Run 375259 pRPD Block 5, 20 - <30% Centrality",6,0,6);
        Run375259_pRPD_TS[6][2] = new TH1F("","Run 375259 pRPD Block 6, 20 - <30% Centrality",6,0,6);
        Run375259_pRPD_TS[7][2] = new TH1F("","Run 375259 pRPD Block 7, 20 - <30% Centrality",6,0,6);
        Run375259_pRPD_TS[8][2] = new TH1F("","Run 375259 pRPD Block 8, 20 - <30% Centrality",6,0,6);
        Run375259_pRPD_TS[9][2] = new TH1F("","Run 375259 pRPD Block 9, 20 - <30% Centrality",6,0,6);
        Run375259_pRPD_TS[10][2] = new TH1F("","Run 375259 pRPD Block 10, 20 - <30% Centrality",6,0,6);
        Run375259_pRPD_TS[11][2] = new TH1F("","Run 375259 pRPD Block 11, 20 - <30% Centrality",6,0,6);
        Run375259_pRPD_TS[12][2] = new TH1F("","Run 375259 pRPD Block 12, 20 - <30% Centrality",6,0,6);
        Run375259_pRPD_TS[13][2] = new TH1F("","Run 375259 pRPD Block 13, 20 - <30% Centrality",6,0,6);
        Run375259_pRPD_TS[14][2] = new TH1F("","Run 375259 pRPD Block 14, 20 - <30% Centrality",6,0,6);
        Run375259_pRPD_TS[15][2] = new TH1F("","Run 375259 pRPD Block 15, 20 - <30% Centrality",6,0,6);

        Run375259_pRPD_TS[0][3] = new TH1F("","Run 375259 pRPD Block 0, 30 - <40% Centrality",6,0,6);
        Run375259_pRPD_TS[1][3] = new TH1F("","Run 375259 pRPD Block 1, 30 - <40% Centrality",6,0,6);
        Run375259_pRPD_TS[2][3] = new TH1F("","Run 375259 pRPD Block 2, 30 - <40% Centrality",6,0,6);
        Run375259_pRPD_TS[3][3] = new TH1F("","Run 375259 pRPD Block 3, 30 - <40% Centrality",6,0,6);
        Run375259_pRPD_TS[4][3] = new TH1F("","Run 375259 pRPD Block 4, 30 - <40% Centrality",6,0,6);
        Run375259_pRPD_TS[5][3] = new TH1F("","Run 375259 pRPD Block 5, 30 - <40% Centrality",6,0,6);
        Run375259_pRPD_TS[6][3] = new TH1F("","Run 375259 pRPD Block 6, 30 - <40% Centrality",6,0,6);
        Run375259_pRPD_TS[7][3] = new TH1F("","Run 375259 pRPD Block 7, 30 - <40% Centrality",6,0,6);
        Run375259_pRPD_TS[8][3] = new TH1F("","Run 375259 pRPD Block 8, 30 - <40% Centrality",6,0,6);
        Run375259_pRPD_TS[9][3] = new TH1F("","Run 375259 pRPD Block 9, 30 - <40% Centrality",6,0,6);
        Run375259_pRPD_TS[10][3] = new TH1F("","Run 375259 pRPD Block 10, 30 - <40% Centrality",6,0,6);
        Run375259_pRPD_TS[11][3] = new TH1F("","Run 375259 pRPD Block 11, 30 - <40% Centrality",6,0,6);
        Run375259_pRPD_TS[12][3] = new TH1F("","Run 375259 pRPD Block 12, 30 - <40% Centrality",6,0,6);
        Run375259_pRPD_TS[13][3] = new TH1F("","Run 375259 pRPD Block 13, 30 - <40% Centrality",6,0,6);
        Run375259_pRPD_TS[14][3] = new TH1F("","Run 375259 pRPD Block 14, 30 - <40% Centrality",6,0,6);
        Run375259_pRPD_TS[15][3] = new TH1F("","Run 375259 pRPD Block 15, 30 - <40% Centrality",6,0,6);

        Run375259_pRPD_TS[0][4] = new TH1F("","Run 375259 pRPD Block 0, 40 - <50% Centrality",6,0,6);
        Run375259_pRPD_TS[1][4] = new TH1F("","Run 375259 pRPD Block 1, 40 - <50% Centrality",6,0,6);
        Run375259_pRPD_TS[2][4] = new TH1F("","Run 375259 pRPD Block 2, 40 - <50% Centrality",6,0,6);
        Run375259_pRPD_TS[3][4] = new TH1F("","Run 375259 pRPD Block 3, 40 - <50% Centrality",6,0,6);
        Run375259_pRPD_TS[4][4] = new TH1F("","Run 375259 pRPD Block 4, 40 - <50% Centrality",6,0,6);
        Run375259_pRPD_TS[5][4] = new TH1F("","Run 375259 pRPD Block 5, 40 - <50% Centrality",6,0,6);
        Run375259_pRPD_TS[6][4] = new TH1F("","Run 375259 pRPD Block 6, 40 - <50% Centrality",6,0,6);
        Run375259_pRPD_TS[7][4] = new TH1F("","Run 375259 pRPD Block 7, 40 - <50% Centrality",6,0,6);
        Run375259_pRPD_TS[8][4] = new TH1F("","Run 375259 pRPD Block 8, 40 - <50% Centrality",6,0,6);
        Run375259_pRPD_TS[9][4] = new TH1F("","Run 375259 pRPD Block 9, 40 - <50% Centrality",6,0,6);
        Run375259_pRPD_TS[10][4] = new TH1F("","Run 375259 pRPD Block 10, 40 - <50% Centrality",6,0,6);
        Run375259_pRPD_TS[11][4] = new TH1F("","Run 375259 pRPD Block 11, 40 - <50% Centrality",6,0,6);
        Run375259_pRPD_TS[12][4] = new TH1F("","Run 375259 pRPD Block 12, 40 - <50% Centrality",6,0,6);
        Run375259_pRPD_TS[13][4] = new TH1F("","Run 375259 pRPD Block 13, 40 - <50% Centrality",6,0,6);
        Run375259_pRPD_TS[14][4] = new TH1F("","Run 375259 pRPD Block 14, 40 - <50% Centrality",6,0,6);
        Run375259_pRPD_TS[15][4] = new TH1F("","Run 375259 pRPD Block 15, 40 - <50% Centrality",6,0,6);

        Run375259_pRPD_TS[0][5] = new TH1F("","Run 375259 pRPD Block 0, 50 - <60% Centrality",6,0,6);
        Run375259_pRPD_TS[1][5] = new TH1F("","Run 375259 pRPD Block 1, 50 - <60% Centrality",6,0,6);
        Run375259_pRPD_TS[2][5] = new TH1F("","Run 375259 pRPD Block 2, 50 - <60% Centrality",6,0,6);
        Run375259_pRPD_TS[3][5] = new TH1F("","Run 375259 pRPD Block 3, 50 - <60% Centrality",6,0,6);
        Run375259_pRPD_TS[4][5] = new TH1F("","Run 375259 pRPD Block 4, 50 - <60% Centrality",6,0,6);
        Run375259_pRPD_TS[5][5] = new TH1F("","Run 375259 pRPD Block 5, 50 - <60% Centrality",6,0,6);
        Run375259_pRPD_TS[6][5] = new TH1F("","Run 375259 pRPD Block 6, 50 - <60% Centrality",6,0,6);
        Run375259_pRPD_TS[7][5] = new TH1F("","Run 375259 pRPD Block 7, 50 - <60% Centrality",6,0,6);
        Run375259_pRPD_TS[8][5] = new TH1F("","Run 375259 pRPD Block 8, 50 - <60% Centrality",6,0,6);
        Run375259_pRPD_TS[9][5] = new TH1F("","Run 375259 pRPD Block 9, 50 - <60% Centrality",6,0,6);
        Run375259_pRPD_TS[10][5] = new TH1F("","Run 375259 pRPD Block 10, 50 - <60% Centrality",6,0,6);
        Run375259_pRPD_TS[11][5] = new TH1F("","Run 375259 pRPD Block 11, 50 - <60% Centrality",6,0,6);
        Run375259_pRPD_TS[12][5] = new TH1F("","Run 375259 pRPD Block 12, 50 - <60% Centrality",6,0,6);
        Run375259_pRPD_TS[13][5] = new TH1F("","Run 375259 pRPD Block 13, 50 - <60% Centrality",6,0,6);
        Run375259_pRPD_TS[14][5] = new TH1F("","Run 375259 pRPD Block 14, 50 - <60% Centrality",6,0,6);
        Run375259_pRPD_TS[15][5] = new TH1F("","Run 375259 pRPD Block 15, 50 - <60% Centrality",6,0,6);

        Run375259_pRPD_TS[0][6] = new TH1F("","Run 375259 pRPD Block 0, 60 - <70% Centrality",6,0,6);
        Run375259_pRPD_TS[1][6] = new TH1F("","Run 375259 pRPD Block 1, 60 - <70% Centrality",6,0,6);
        Run375259_pRPD_TS[2][6] = new TH1F("","Run 375259 pRPD Block 2, 60 - <70% Centrality",6,0,6);
        Run375259_pRPD_TS[3][6] = new TH1F("","Run 375259 pRPD Block 3, 60 - <70% Centrality",6,0,6);
        Run375259_pRPD_TS[4][6] = new TH1F("","Run 375259 pRPD Block 4, 60 - <70% Centrality",6,0,6);
        Run375259_pRPD_TS[5][6] = new TH1F("","Run 375259 pRPD Block 5, 60 - <70% Centrality",6,0,6);
        Run375259_pRPD_TS[6][6] = new TH1F("","Run 375259 pRPD Block 6, 60 - <70% Centrality",6,0,6);
        Run375259_pRPD_TS[7][6] = new TH1F("","Run 375259 pRPD Block 7, 60 - <70% Centrality",6,0,6);
        Run375259_pRPD_TS[8][6] = new TH1F("","Run 375259 pRPD Block 8, 60 - <70% Centrality",6,0,6);
        Run375259_pRPD_TS[9][6] = new TH1F("","Run 375259 pRPD Block 9, 60 - <70% Centrality",6,0,6);
        Run375259_pRPD_TS[10][6] = new TH1F("","Run 375259 pRPD Block 10, 60 - <70% Centrality",6,0,6);
        Run375259_pRPD_TS[11][6] = new TH1F("","Run 375259 pRPD Block 11, 60 - <70% Centrality",6,0,6);
        Run375259_pRPD_TS[12][6] = new TH1F("","Run 375259 pRPD Block 12, 60 - <70% Centrality",6,0,6);
        Run375259_pRPD_TS[13][6] = new TH1F("","Run 375259 pRPD Block 13, 60 - <70% Centrality",6,0,6);
        Run375259_pRPD_TS[14][6] = new TH1F("","Run 375259 pRPD Block 14, 60 - <70% Centrality",6,0,6);
        Run375259_pRPD_TS[15][6] = new TH1F("","Run 375259 pRPD Block 15, 60 - <70% Centrality",6,0,6);

        Run375259_pRPD_TS[0][7] = new TH1F("","Run 375259 pRPD Block 0, 70 - <80% Centrality",6,0,6);
        Run375259_pRPD_TS[1][7] = new TH1F("","Run 375259 pRPD Block 1, 70 - <80% Centrality",6,0,6);
        Run375259_pRPD_TS[2][7] = new TH1F("","Run 375259 pRPD Block 2, 70 - <80% Centrality",6,0,6);
        Run375259_pRPD_TS[3][7] = new TH1F("","Run 375259 pRPD Block 3, 70 - <80% Centrality",6,0,6);
        Run375259_pRPD_TS[4][7] = new TH1F("","Run 375259 pRPD Block 4, 70 - <80% Centrality",6,0,6);
        Run375259_pRPD_TS[5][7] = new TH1F("","Run 375259 pRPD Block 5, 70 - <80% Centrality",6,0,6);
        Run375259_pRPD_TS[6][7] = new TH1F("","Run 375259 pRPD Block 6, 70 - <80% Centrality",6,0,6);
        Run375259_pRPD_TS[7][7] = new TH1F("","Run 375259 pRPD Block 7, 70 - <80% Centrality",6,0,6);
        Run375259_pRPD_TS[8][7] = new TH1F("","Run 375259 pRPD Block 8, 70 - <80% Centrality",6,0,6);
        Run375259_pRPD_TS[9][7] = new TH1F("","Run 375259 pRPD Block 9, 70 - <80% Centrality",6,0,6);
        Run375259_pRPD_TS[10][7] = new TH1F("","Run 375259 pRPD Block 10, 70 - <80% Centrality",6,0,6);
        Run375259_pRPD_TS[11][7] = new TH1F("","Run 375259 pRPD Block 11, 70 - <80% Centrality",6,0,6);
        Run375259_pRPD_TS[12][7] = new TH1F("","Run 375259 pRPD Block 12, 70 - <80% Centrality",6,0,6);
        Run375259_pRPD_TS[13][7] = new TH1F("","Run 375259 pRPD Block 13, 70 - <80% Centrality",6,0,6);
        Run375259_pRPD_TS[14][7] = new TH1F("","Run 375259 pRPD Block 14, 70 - <80% Centrality",6,0,6);
        Run375259_pRPD_TS[15][7] = new TH1F("","Run 375259 pRPD Block 15, 70 - <80% Centrality",6,0,6);

        Run375259_pRPD_TS[0][8] = new TH1F("","Run 375259 pRPD Block 0, 80 - <90% Centrality",6,0,6);
        Run375259_pRPD_TS[1][8] = new TH1F("","Run 375259 pRPD Block 1, 80 - <90% Centrality",6,0,6);
        Run375259_pRPD_TS[2][8] = new TH1F("","Run 375259 pRPD Block 2, 80 - <90% Centrality",6,0,6);
        Run375259_pRPD_TS[3][8] = new TH1F("","Run 375259 pRPD Block 3, 80 - <90% Centrality",6,0,6);
        Run375259_pRPD_TS[4][8] = new TH1F("","Run 375259 pRPD Block 4, 80 - <90% Centrality",6,0,6);
        Run375259_pRPD_TS[5][8] = new TH1F("","Run 375259 pRPD Block 5, 80 - <90% Centrality",6,0,6);
        Run375259_pRPD_TS[6][8] = new TH1F("","Run 375259 pRPD Block 6, 80 - <90% Centrality",6,0,6);
        Run375259_pRPD_TS[7][8] = new TH1F("","Run 375259 pRPD Block 7, 80 - <90% Centrality",6,0,6);
        Run375259_pRPD_TS[8][8] = new TH1F("","Run 375259 pRPD Block 8, 80 - <90% Centrality",6,0,6);
        Run375259_pRPD_TS[9][8] = new TH1F("","Run 375259 pRPD Block 9, 80 - <90% Centrality",6,0,6);
        Run375259_pRPD_TS[10][8] = new TH1F("","Run 375259 pRPD Block 10, 80 - <90% Centrality",6,0,6);
        Run375259_pRPD_TS[11][8] = new TH1F("","Run 375259 pRPD Block 11, 80 - <90% Centrality",6,0,6);
        Run375259_pRPD_TS[12][8] = new TH1F("","Run 375259 pRPD Block 12, 80 - <90% Centrality",6,0,6);
        Run375259_pRPD_TS[13][8] = new TH1F("","Run 375259 pRPD Block 13, 80 - <90% Centrality",6,0,6);
        Run375259_pRPD_TS[14][8] = new TH1F("","Run 375259 pRPD Block 14, 80 - <90% Centrality",6,0,6);
        Run375259_pRPD_TS[15][8] = new TH1F("","Run 375259 pRPD Block 15, 80 - <90% Centrality",6,0,6);

        Run375259_pRPD_TS[0][9] = new TH1F("","Run 375259 pRPD Block 0, 90 - <100% Centrality",6,0,6);
        Run375259_pRPD_TS[1][9] = new TH1F("","Run 375259 pRPD Block 1, 90 - <100% Centrality",6,0,6);
        Run375259_pRPD_TS[2][9] = new TH1F("","Run 375259 pRPD Block 2, 90 - <100% Centrality",6,0,6);
        Run375259_pRPD_TS[3][9] = new TH1F("","Run 375259 pRPD Block 3, 90 - <100% Centrality",6,0,6);
        Run375259_pRPD_TS[4][9] = new TH1F("","Run 375259 pRPD Block 4, 90 - <100% Centrality",6,0,6);
        Run375259_pRPD_TS[5][9] = new TH1F("","Run 375259 pRPD Block 5, 90 - <100% Centrality",6,0,6);
        Run375259_pRPD_TS[6][9] = new TH1F("","Run 375259 pRPD Block 6, 90 - <100% Centrality",6,0,6);
        Run375259_pRPD_TS[7][9] = new TH1F("","Run 375259 pRPD Block 7, 90 - <100% Centrality",6,0,6);
        Run375259_pRPD_TS[8][9] = new TH1F("","Run 375259 pRPD Block 8, 90 - <100% Centrality",6,0,6);
        Run375259_pRPD_TS[9][9] = new TH1F("","Run 375259 pRPD Block 9, 90 - <100% Centrality",6,0,6);
        Run375259_pRPD_TS[10][9] = new TH1F("","Run 375259 pRPD Block 10, 90 - <100% Centrality",6,0,6);
        Run375259_pRPD_TS[11][9] = new TH1F("","Run 375259 pRPD Block 11, 90 - <100% Centrality",6,0,6);
        Run375259_pRPD_TS[12][9] = new TH1F("","Run 375259 pRPD Block 12, 90 - <100% Centrality",6,0,6);
        Run375259_pRPD_TS[13][9] = new TH1F("","Run 375259 pRPD Block 13, 90 - <100% Centrality",6,0,6);
        Run375259_pRPD_TS[14][9] = new TH1F("","Run 375259 pRPD Block 14, 90 - <100% Centrality",6,0,6);
        Run375259_pRPD_TS[15][9] = new TH1F("","Run 375259 pRPD Block 15, 90 - <100% Centrality",6,0,6);

        Run375259_pRPD_TS[0][10] = new TH1F("","Run 375259 pRPD Block 0, All Centrality",6,0,6);
        Run375259_pRPD_TS[1][10] = new TH1F("","Run 375259 pRPD Block 1, All Centrality",6,0,6);
        Run375259_pRPD_TS[2][10] = new TH1F("","Run 375259 pRPD Block 2, All Centrality",6,0,6);
        Run375259_pRPD_TS[3][10] = new TH1F("","Run 375259 pRPD Block 3, All Centrality",6,0,6);
        Run375259_pRPD_TS[4][10] = new TH1F("","Run 375259 pRPD Block 4, All Centrality",6,0,6);
        Run375259_pRPD_TS[5][10] = new TH1F("","Run 375259 pRPD Block 5, All Centrality",6,0,6);
        Run375259_pRPD_TS[6][10] = new TH1F("","Run 375259 pRPD Block 6, All Centrality",6,0,6);
        Run375259_pRPD_TS[7][10] = new TH1F("","Run 375259 pRPD Block 7, All Centrality",6,0,6);
        Run375259_pRPD_TS[8][10] = new TH1F("","Run 375259 pRPD Block 8, All Centrality",6,0,6);
        Run375259_pRPD_TS[9][10] = new TH1F("","Run 375259 pRPD Block 9, All Centrality",6,0,6);
        Run375259_pRPD_TS[10][10] = new TH1F("","Run 375259 pRPD Block 10, All Centrality",6,0,6);
        Run375259_pRPD_TS[11][10] = new TH1F("","Run 375259 pRPD Block 11, All Centrality",6,0,6);
        Run375259_pRPD_TS[12][10] = new TH1F("","Run 375259 pRPD Block 12, All Centrality",6,0,6);
        Run375259_pRPD_TS[13][10] = new TH1F("","Run 375259 pRPD Block 13, All Centrality",6,0,6);
        Run375259_pRPD_TS[14][10] = new TH1F("","Run 375259 pRPD Block 14, All Centrality",6,0,6);
        Run375259_pRPD_TS[15][10] = new TH1F("","Run 375259 pRPD Block 15, All Centrality",6,0,6);
        
    //Ratios of time slice 2 to time slice 3 for EM, HAD, and RPD on pos side
    TH1F *Run375259_pRPD_TSratio[16][11] = {0};

        Run375259_pRPD_TSratio[0][0] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 0, 0 - <10% Centrality",50,0,5);
        Run375259_pRPD_TSratio[1][0] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 1, 0 - <10% Centrality",50,0,5);
        Run375259_pRPD_TSratio[2][0] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 2, 0 - <10% Centrality",50,0,5);
        Run375259_pRPD_TSratio[3][0] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 3, 0 - <10% Centrality",50,0,5);
        Run375259_pRPD_TSratio[4][0] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 4, 0 - <10% Centrality",50,0,5);
        Run375259_pRPD_TSratio[5][0] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 5, 0 - <10% Centrality",50,0,5);
        Run375259_pRPD_TSratio[6][0] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 6, 0 - <10% Centrality",50,0,5);
        Run375259_pRPD_TSratio[7][0] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 7, 0 - <10% Centrality",50,0,5);
        Run375259_pRPD_TSratio[8][0] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 8, 0 - <10% Centrality",50,0,5);
        Run375259_pRPD_TSratio[9][0] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 9, 0 - <10% Centrality",50,0,5);
        Run375259_pRPD_TSratio[10][0] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 10, 0 - <10% Centrality",50,0,5);
        Run375259_pRPD_TSratio[11][0] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 11, 0 - <10% Centrality",50,0,5);
        Run375259_pRPD_TSratio[12][0] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 12, 0 - <10% Centrality",50,0,5);
        Run375259_pRPD_TSratio[13][0] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 13, 0 - <10% Centrality",50,0,5);
        Run375259_pRPD_TSratio[14][0] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 14, 0 - <10% Centrality",50,0,5);
        Run375259_pRPD_TSratio[15][0] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 15, 0 - <10% Centrality",50,0,5);

        Run375259_pRPD_TSratio[0][1] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 0, 10 - <20% Centrality",50,0,5);
        Run375259_pRPD_TSratio[1][1] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 1, 10 - <20% Centrality",50,0,5);
        Run375259_pRPD_TSratio[2][1] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 2, 10 - <20% Centrality",50,0,5);
        Run375259_pRPD_TSratio[3][1] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 3, 10 - <20% Centrality",50,0,5);
        Run375259_pRPD_TSratio[4][1] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 4, 10 - <20% Centrality",50,0,5);
        Run375259_pRPD_TSratio[5][1] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 5, 10 - <20% Centrality",50,0,5);
        Run375259_pRPD_TSratio[6][1] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 6, 10 - <20% Centrality",50,0,5);
        Run375259_pRPD_TSratio[7][1] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 7, 10 - <20% Centrality",50,0,5);
        Run375259_pRPD_TSratio[8][1] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 8, 10 - <20% Centrality",50,0,5);
        Run375259_pRPD_TSratio[9][1] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 9, 10 - <20% Centrality",50,0,5);
        Run375259_pRPD_TSratio[10][1] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 10, 10 - <20% Centrality",50,0,5);
        Run375259_pRPD_TSratio[11][1] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 11, 10 - <20% Centrality",50,0,5);
        Run375259_pRPD_TSratio[12][1] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 12, 10 - <20% Centrality",50,0,5);
        Run375259_pRPD_TSratio[13][1] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 13, 10 - <20% Centrality",50,0,5);
        Run375259_pRPD_TSratio[14][1] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 14, 10 - <20% Centrality",50,0,5);
        Run375259_pRPD_TSratio[15][1] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 15, 10 - <20% Centrality",50,0,5);

        Run375259_pRPD_TSratio[0][2] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 0, 20 - <30% Centrality",50,0,5);
        Run375259_pRPD_TSratio[1][2] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 1, 20 - <30% Centrality",50,0,5);
        Run375259_pRPD_TSratio[2][2] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 2, 20 - <30% Centrality",50,0,5);
        Run375259_pRPD_TSratio[3][2] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 3, 20 - <30% Centrality",50,0,5);
        Run375259_pRPD_TSratio[4][2] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 4, 20 - <30% Centrality",50,0,5);
        Run375259_pRPD_TSratio[5][2] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 5, 20 - <30% Centrality",50,0,5);
        Run375259_pRPD_TSratio[6][2] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 6, 20 - <30% Centrality",50,0,5);
        Run375259_pRPD_TSratio[7][2] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 7, 20 - <30% Centrality",50,0,5);
        Run375259_pRPD_TSratio[8][2] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 8, 20 - <30% Centrality",50,0,5);
        Run375259_pRPD_TSratio[9][2] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 9, 20 - <30% Centrality",50,0,5);
        Run375259_pRPD_TSratio[10][2] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 10, 20 - <30% Centrality",50,0,5);
        Run375259_pRPD_TSratio[11][2] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 11, 20 - <30% Centrality",50,0,5);
        Run375259_pRPD_TSratio[12][2] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 12, 20 - <30% Centrality",50,0,5);
        Run375259_pRPD_TSratio[13][2] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 13, 20 - <30% Centrality",50,0,5);
        Run375259_pRPD_TSratio[14][2] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 14, 20 - <30% Centrality",50,0,5);
        Run375259_pRPD_TSratio[15][2] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 15, 20 - <30% Centrality",50,0,5);

        Run375259_pRPD_TSratio[0][3] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 0, 30 - <40% Centrality",50,0,5);
        Run375259_pRPD_TSratio[1][3] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 1, 30 - <40% Centrality",50,0,5);
        Run375259_pRPD_TSratio[2][3] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 2, 30 - <40% Centrality",50,0,5);
        Run375259_pRPD_TSratio[3][3] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 3, 30 - <40% Centrality",50,0,5);
        Run375259_pRPD_TSratio[4][3] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 4, 30 - <40% Centrality",50,0,5);
        Run375259_pRPD_TSratio[5][3] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 5, 30 - <40% Centrality",50,0,5);
        Run375259_pRPD_TSratio[6][3] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 6, 30 - <40% Centrality",50,0,5);
        Run375259_pRPD_TSratio[7][3] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 7, 30 - <40% Centrality",50,0,5);
        Run375259_pRPD_TSratio[8][3] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 8, 30 - <40% Centrality",50,0,5);
        Run375259_pRPD_TSratio[9][3] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 9, 30 - <40% Centrality",50,0,5);
        Run375259_pRPD_TSratio[10][3] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 10, 30 - <40% Centrality",50,0,5);
        Run375259_pRPD_TSratio[11][3] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 11, 30 - <40% Centrality",50,0,5);
        Run375259_pRPD_TSratio[12][3] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 12, 30 - <40% Centrality",50,0,5);
        Run375259_pRPD_TSratio[13][3] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 13, 30 - <40% Centrality",50,0,5);
        Run375259_pRPD_TSratio[14][3] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 14, 30 - <40% Centrality",50,0,5);
        Run375259_pRPD_TSratio[15][3] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 15, 30 - <40% Centrality",50,0,5);

        Run375259_pRPD_TSratio[0][4] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 0, 40 - <50% Centrality",50,0,5);
        Run375259_pRPD_TSratio[1][4] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 1, 40 - <50% Centrality",50,0,5);
        Run375259_pRPD_TSratio[2][4] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 2, 40 - <50% Centrality",50,0,5);
        Run375259_pRPD_TSratio[3][4] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 3, 40 - <50% Centrality",50,0,5);
        Run375259_pRPD_TSratio[4][4] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 4, 40 - <50% Centrality",50,0,5);
        Run375259_pRPD_TSratio[5][4] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 5, 40 - <50% Centrality",50,0,5);
        Run375259_pRPD_TSratio[6][4] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 6, 40 - <50% Centrality",50,0,5);
        Run375259_pRPD_TSratio[7][4] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 7, 40 - <50% Centrality",50,0,5);
        Run375259_pRPD_TSratio[8][4] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 8, 40 - <50% Centrality",50,0,5);
        Run375259_pRPD_TSratio[9][4] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 9, 40 - <50% Centrality",50,0,5);
        Run375259_pRPD_TSratio[10][4] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 10, 40 - <50% Centrality",50,0,5);
        Run375259_pRPD_TSratio[11][4] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 11, 40 - <50% Centrality",50,0,5);
        Run375259_pRPD_TSratio[12][4] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 12, 40 - <50% Centrality",50,0,5);
        Run375259_pRPD_TSratio[13][4] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 13, 40 - <50% Centrality",50,0,5);
        Run375259_pRPD_TSratio[14][4] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 14, 40 - <50% Centrality",50,0,5);
        Run375259_pRPD_TSratio[15][4] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 15, 40 - <50% Centrality",50,0,5);

        Run375259_pRPD_TSratio[0][5] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 0, 50 - <60% Centrality",50,0,5);
        Run375259_pRPD_TSratio[1][5] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 1, 50 - <60% Centrality",50,0,5);
        Run375259_pRPD_TSratio[2][5] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 2, 50 - <60% Centrality",50,0,5);
        Run375259_pRPD_TSratio[3][5] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 3, 50 - <60% Centrality",50,0,5);
        Run375259_pRPD_TSratio[4][5] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 4, 50 - <60% Centrality",50,0,5);
        Run375259_pRPD_TSratio[5][5] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 5, 50 - <60% Centrality",50,0,5);
        Run375259_pRPD_TSratio[6][5] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 6, 50 - <60% Centrality",50,0,5);
        Run375259_pRPD_TSratio[7][5] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 7, 50 - <60% Centrality",50,0,5);
        Run375259_pRPD_TSratio[8][5] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 8, 50 - <60% Centrality",50,0,5);
        Run375259_pRPD_TSratio[9][5] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 9, 50 - <60% Centrality",50,0,5);
        Run375259_pRPD_TSratio[10][5] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 10, 50 - <60% Centrality",50,0,5);
        Run375259_pRPD_TSratio[11][5] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 11, 50 - <60% Centrality",50,0,5);
        Run375259_pRPD_TSratio[12][5] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 12, 50 - <60% Centrality",50,0,5);
        Run375259_pRPD_TSratio[13][5] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 13, 50 - <60% Centrality",50,0,5);
        Run375259_pRPD_TSratio[14][5] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 14, 50 - <60% Centrality",50,0,5);
        Run375259_pRPD_TSratio[15][5] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 15, 50 - <60% Centrality",50,0,5);

        Run375259_pRPD_TSratio[0][6] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 0, 60 - <70% Centrality",50,0,5);
        Run375259_pRPD_TSratio[1][6] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 1, 60 - <70% Centrality",50,0,5);
        Run375259_pRPD_TSratio[2][6] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 2, 60 - <70% Centrality",50,0,5);
        Run375259_pRPD_TSratio[3][6] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 3, 60 - <70% Centrality",50,0,5);
        Run375259_pRPD_TSratio[4][6] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 4, 60 - <70% Centrality",50,0,5);
        Run375259_pRPD_TSratio[5][6] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 5, 60 - <70% Centrality",50,0,5);
        Run375259_pRPD_TSratio[6][6] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 6, 60 - <70% Centrality",50,0,5);
        Run375259_pRPD_TSratio[7][6] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 7, 60 - <70% Centrality",50,0,5);
        Run375259_pRPD_TSratio[8][6] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 8, 60 - <70% Centrality",50,0,5);
        Run375259_pRPD_TSratio[9][6] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 9, 60 - <70% Centrality",50,0,5);
        Run375259_pRPD_TSratio[10][6] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 10, 60 - <70% Centrality",50,0,5);
        Run375259_pRPD_TSratio[11][6] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 11, 60 - <70% Centrality",50,0,5);
        Run375259_pRPD_TSratio[12][6] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 12, 60 - <70% Centrality",50,0,5);
        Run375259_pRPD_TSratio[13][6] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 13, 60 - <70% Centrality",50,0,5);
        Run375259_pRPD_TSratio[14][6] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 14, 60 - <70% Centrality",50,0,5);
        Run375259_pRPD_TSratio[15][6] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 15, 60 - <70% Centrality",50,0,5);

        Run375259_pRPD_TSratio[0][7] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 0, 70 - <80% Centrality",50,0,5);
        Run375259_pRPD_TSratio[1][7] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 1, 70 - <80% Centrality",50,0,5);
        Run375259_pRPD_TSratio[2][7] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 2, 70 - <80% Centrality",50,0,5);
        Run375259_pRPD_TSratio[3][7] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 3, 70 - <80% Centrality",50,0,5);
        Run375259_pRPD_TSratio[4][7] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 4, 70 - <80% Centrality",50,0,5);
        Run375259_pRPD_TSratio[5][7] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 5, 70 - <80% Centrality",50,0,5);
        Run375259_pRPD_TSratio[6][7] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 6, 70 - <80% Centrality",50,0,5);
        Run375259_pRPD_TSratio[7][7] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 7, 70 - <80% Centrality",50,0,5);
        Run375259_pRPD_TSratio[8][7] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 8, 70 - <80% Centrality",50,0,5);
        Run375259_pRPD_TSratio[9][7] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 9, 70 - <80% Centrality",50,0,5);
        Run375259_pRPD_TSratio[10][7] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 10, 70 - <80% Centrality",50,0,5);
        Run375259_pRPD_TSratio[11][7] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 11, 70 - <80% Centrality",50,0,5);
        Run375259_pRPD_TSratio[12][7] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 12, 70 - <80% Centrality",50,0,5);
        Run375259_pRPD_TSratio[13][7] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 13, 70 - <80% Centrality",50,0,5);
        Run375259_pRPD_TSratio[14][7] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 14, 70 - <80% Centrality",50,0,5);
        Run375259_pRPD_TSratio[15][7] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 15, 70 - <80% Centrality",50,0,5);

        Run375259_pRPD_TSratio[0][8] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 0, 80 - <90% Centrality",50,0,5);
        Run375259_pRPD_TSratio[1][8] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 1, 80 - <90% Centrality",50,0,5);
        Run375259_pRPD_TSratio[2][8] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 2, 80 - <90% Centrality",50,0,5);
        Run375259_pRPD_TSratio[3][8] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 3, 80 - <90% Centrality",50,0,5);
        Run375259_pRPD_TSratio[4][8] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 4, 80 - <90% Centrality",50,0,5);
        Run375259_pRPD_TSratio[5][8] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 5, 80 - <90% Centrality",50,0,5);
        Run375259_pRPD_TSratio[6][8] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 6, 80 - <90% Centrality",50,0,5);
        Run375259_pRPD_TSratio[7][8] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 7, 80 - <90% Centrality",50,0,5);
        Run375259_pRPD_TSratio[8][8] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 8, 80 - <90% Centrality",50,0,5);
        Run375259_pRPD_TSratio[9][8] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 9, 80 - <90% Centrality",50,0,5);
        Run375259_pRPD_TSratio[10][8] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 10, 80 - <90% Centrality",50,0,5);
        Run375259_pRPD_TSratio[11][8] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 11, 80 - <90% Centrality",50,0,5);
        Run375259_pRPD_TSratio[12][8] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 12, 80 - <90% Centrality",50,0,5);
        Run375259_pRPD_TSratio[13][8] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 13, 80 - <90% Centrality",50,0,5);
        Run375259_pRPD_TSratio[14][8] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 14, 80 - <90% Centrality",50,0,5);
        Run375259_pRPD_TSratio[15][8] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 15, 80 - <90% Centrality",50,0,5);

        Run375259_pRPD_TSratio[0][9] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 0, 90 - <100% Centrality",50,0,5);
        Run375259_pRPD_TSratio[1][9] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 1, 90 - <100% Centrality",50,0,5);
        Run375259_pRPD_TSratio[2][9] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 2, 90 - <100% Centrality",50,0,5);
        Run375259_pRPD_TSratio[3][9] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 3, 90 - <100% Centrality",50,0,5);
        Run375259_pRPD_TSratio[4][9] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 4, 90 - <100% Centrality",50,0,5);
        Run375259_pRPD_TSratio[5][9] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 5, 90 - <100% Centrality",50,0,5);
        Run375259_pRPD_TSratio[6][9] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 6, 90 - <100% Centrality",50,0,5);
        Run375259_pRPD_TSratio[7][9] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 7, 90 - <100% Centrality",50,0,5);
        Run375259_pRPD_TSratio[8][9] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 8, 90 - <100% Centrality",50,0,5);
        Run375259_pRPD_TSratio[9][9] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 9, 90 - <100% Centrality",50,0,5);
        Run375259_pRPD_TSratio[10][9] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 10, 90 - <100% Centrality",50,0,5);
        Run375259_pRPD_TSratio[11][9] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 11, 90 - <100% Centrality",50,0,5);
        Run375259_pRPD_TSratio[12][9] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 12, 90 - <100% Centrality",50,0,5);
        Run375259_pRPD_TSratio[13][9] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 13, 90 - <100% Centrality",50,0,5);
        Run375259_pRPD_TSratio[14][9] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 14, 90 - <100% Centrality",50,0,5);
        Run375259_pRPD_TSratio[15][9] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 15, 90 - <100% Centrality",50,0,5);

        Run375259_pRPD_TSratio[0][10] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 0, All Centrality",50,0,5);
        Run375259_pRPD_TSratio[1][10] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 1, All Centrality",50,0,5);
        Run375259_pRPD_TSratio[2][10] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 2, All Centrality",50,0,5);
        Run375259_pRPD_TSratio[3][10] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 3, All Centrality",50,0,5);
        Run375259_pRPD_TSratio[4][10] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 4, All Centrality",50,0,5);
        Run375259_pRPD_TSratio[5][10] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 5, All Centrality",50,0,5);
        Run375259_pRPD_TSratio[6][10] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 6, All Centrality",50,0,5);
        Run375259_pRPD_TSratio[7][10] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 7, All Centrality",50,0,5);
        Run375259_pRPD_TSratio[8][10] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 8, All Centrality",50,0,5);
        Run375259_pRPD_TSratio[9][10] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 9, All Centrality",50,0,5);
        Run375259_pRPD_TSratio[10][10] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 10, All Centrality",50,0,5);
        Run375259_pRPD_TSratio[11][10] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 11, All Centrality",50,0,5);
        Run375259_pRPD_TSratio[12][10] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 12, All Centrality",50,0,5);
        Run375259_pRPD_TSratio[13][10] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 13, All Centrality",50,0,5);
        Run375259_pRPD_TSratio[14][10] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 14, All Centrality",50,0,5);
        Run375259_pRPD_TSratio[15][10] = new TH1F("","Run 375259 pRPD Ratio TS2 : TS3 Block 15, All Centrality",50,0,5);

    //fC distributions for all centralities for EM, HAD, and RPD on pos side

    TH1F *Run375259_pRPD_fC[16][11] = {0};

        Run375259_pRPD_fC[0][0] = new TH1F("","Run 375259 pRPD Block 0 fC Distribution, 0 - <10% Cent ",100,0,400000);
        Run375259_pRPD_fC[1][0] = new TH1F("","Run 375259 pRPD Block 1 fC Distribution, 0 - <10% Cent ",100,0,400000);
        Run375259_pRPD_fC[2][0] = new TH1F("","Run 375259 pRPD Block 2 fC Distribution, 0 - <10% Cent ",100,0,400000);
        Run375259_pRPD_fC[3][0] = new TH1F("","Run 375259 pRPD Block 3 fC Distribution, 0 - <10% Cent ",100,0,400000);
        Run375259_pRPD_fC[4][0] = new TH1F("","Run 375259 pRPD Block 4 fC Distribution, 0 - <10% Cent ",100,0,400000);
        Run375259_pRPD_fC[5][0] = new TH1F("","Run 375259 pRPD Block 5 fC Distribution, 0 - <10% Cent ",100,0,400000);
        Run375259_pRPD_fC[6][0] = new TH1F("","Run 375259 pRPD Block 6 fC Distribution, 0 - <10% Cent ",100,0,400000);
        Run375259_pRPD_fC[7][0] = new TH1F("","Run 375259 pRPD Block 7 fC Distribution, 0 - <10% Cent ",100,0,400000);
        Run375259_pRPD_fC[8][0] = new TH1F("","Run 375259 pRPD Block 8 fC Distribution, 0 - <10% Cent ",100,0,400000);
        Run375259_pRPD_fC[9][0] = new TH1F("","Run 375259 pRPD Block 9 fC Distribution, 0 - <10% Cent ",100,0,400000);
        Run375259_pRPD_fC[10][0] = new TH1F("","Run 375259 pRPD Block 10 fC Distribution, 0 - <10% Cent ",100,0,400000);
        Run375259_pRPD_fC[11][0] = new TH1F("","Run 375259 pRPD Block 11 fC Distribution, 0 - <10% Cent ",100,0,400000);
        Run375259_pRPD_fC[12][0] = new TH1F("","Run 375259 pRPD Block 12 fC Distribution, 0 - <10% Cent ",100,0,400000);
        Run375259_pRPD_fC[13][0] = new TH1F("","Run 375259 pRPD Block 13 fC Distribution, 0 - <10% Cent ",100,0,400000);
        Run375259_pRPD_fC[14][0] = new TH1F("","Run 375259 pRPD Block 14 fC Distribution, 0 - <10% Cent ",100,0,400000);
        Run375259_pRPD_fC[15][0] = new TH1F("","Run 375259 pRPD Block 15 fC Distribution, 0 - <10% Cent ",100,0,400000);

        Run375259_pRPD_fC[0][1] = new TH1F("","Run 375259 pRPD Block 0 fC Distribution, 10 - <20% Cent ",100,0,400000);
        Run375259_pRPD_fC[1][1] = new TH1F("","Run 375259 pRPD Block 1 fC Distribution, 10 - <20% Cent ",100,0,400000);
        Run375259_pRPD_fC[2][1] = new TH1F("","Run 375259 pRPD Block 2 fC Distribution, 10 - <20% Cent ",100,0,400000);
        Run375259_pRPD_fC[3][1] = new TH1F("","Run 375259 pRPD Block 3 fC Distribution, 10 - <20% Cent ",100,0,400000);
        Run375259_pRPD_fC[4][1] = new TH1F("","Run 375259 pRPD Block 4 fC Distribution, 10 - <20% Cent ",100,0,400000);
        Run375259_pRPD_fC[5][1] = new TH1F("","Run 375259 pRPD Block 5 fC Distribution, 10 - <20% Cent ",100,0,400000);
        Run375259_pRPD_fC[6][1] = new TH1F("","Run 375259 pRPD Block 6 fC Distribution, 10 - <20% Cent ",100,0,400000);
        Run375259_pRPD_fC[7][1] = new TH1F("","Run 375259 pRPD Block 7 fC Distribution, 10 - <20% Cent ",100,0,400000);
        Run375259_pRPD_fC[8][1] = new TH1F("","Run 375259 pRPD Block 8 fC Distribution, 10 - <20% Cent ",100,0,400000);
        Run375259_pRPD_fC[9][1] = new TH1F("","Run 375259 pRPD Block 9 fC Distribution, 10 - <20% Cent ",100,0,400000);
        Run375259_pRPD_fC[10][1] = new TH1F("","Run 375259 pRPD Block 10 fC Distribution, 10 - <20% Cent ",100,0,400000);
        Run375259_pRPD_fC[11][1] = new TH1F("","Run 375259 pRPD Block 11 fC Distribution, 10 - <20% Cent ",100,0,400000);
        Run375259_pRPD_fC[12][1] = new TH1F("","Run 375259 pRPD Block 12 fC Distribution, 10 - <20% Cent ",100,0,400000);
        Run375259_pRPD_fC[13][1] = new TH1F("","Run 375259 pRPD Block 13 fC Distribution, 10 - <20% Cent ",100,0,400000);
        Run375259_pRPD_fC[14][1] = new TH1F("","Run 375259 pRPD Block 14 fC Distribution, 10 - <20% Cent ",100,0,400000);
        Run375259_pRPD_fC[15][1] = new TH1F("","Run 375259 pRPD Block 15 fC Distribution, 10 - <20% Cent ",100,0,400000);

        Run375259_pRPD_fC[0][2] = new TH1F("","Run 375259 pRPD Block 0 fC Distribution, 20 - <30% Cent ",100,0,400000);
        Run375259_pRPD_fC[1][2] = new TH1F("","Run 375259 pRPD Block 1 fC Distribution, 20 - <30% Cent ",100,0,400000);
        Run375259_pRPD_fC[2][2] = new TH1F("","Run 375259 pRPD Block 2 fC Distribution, 20 - <30% Cent ",100,0,400000);
        Run375259_pRPD_fC[3][2] = new TH1F("","Run 375259 pRPD Block 3 fC Distribution, 20 - <30% Cent ",100,0,400000);
        Run375259_pRPD_fC[4][2] = new TH1F("","Run 375259 pRPD Block 4 fC Distribution, 20 - <30% Cent ",100,0,400000);
        Run375259_pRPD_fC[5][2] = new TH1F("","Run 375259 pRPD Block 5 fC Distribution, 20 - <30% Cent ",100,0,400000);
        Run375259_pRPD_fC[6][2] = new TH1F("","Run 375259 pRPD Block 6 fC Distribution, 20 - <30% Cent ",100,0,400000);
        Run375259_pRPD_fC[7][2] = new TH1F("","Run 375259 pRPD Block 7 fC Distribution, 20 - <30% Cent ",100,0,400000);
        Run375259_pRPD_fC[8][2] = new TH1F("","Run 375259 pRPD Block 8 fC Distribution, 20 - <30% Cent ",100,0,400000);
        Run375259_pRPD_fC[9][2] = new TH1F("","Run 375259 pRPD Block 9 fC Distribution, 20 - <30% Cent ",100,0,400000);
        Run375259_pRPD_fC[10][2] = new TH1F("","Run 375259 pRPD Block 10 fC Distribution, 20 - <30% Cent ",100,0,400000);
        Run375259_pRPD_fC[11][2] = new TH1F("","Run 375259 pRPD Block 11 fC Distribution, 20 - <30% Cent ",100,0,400000);
        Run375259_pRPD_fC[12][2] = new TH1F("","Run 375259 pRPD Block 12 fC Distribution, 20 - <30% Cent ",100,0,400000);
        Run375259_pRPD_fC[13][2] = new TH1F("","Run 375259 pRPD Block 13 fC Distribution, 20 - <30% Cent ",100,0,400000);
        Run375259_pRPD_fC[14][2] = new TH1F("","Run 375259 pRPD Block 14 fC Distribution, 20 - <30% Cent ",100,0,400000);
        Run375259_pRPD_fC[15][2] = new TH1F("","Run 375259 pRPD Block 15 fC Distribution, 20 - <30% Cent ",100,0,400000);

        Run375259_pRPD_fC[0][3] = new TH1F("","Run 375259 pRPD Block 0 fC Distribution, 30 - <40% Cent ",100,0,400000);
        Run375259_pRPD_fC[1][3] = new TH1F("","Run 375259 pRPD Block 1 fC Distribution, 30 - <40% Cent ",100,0,400000);
        Run375259_pRPD_fC[2][3] = new TH1F("","Run 375259 pRPD Block 2 fC Distribution, 30 - <40% Cent ",100,0,400000);
        Run375259_pRPD_fC[3][3] = new TH1F("","Run 375259 pRPD Block 3 fC Distribution, 30 - <40% Cent ",100,0,400000);
        Run375259_pRPD_fC[4][3] = new TH1F("","Run 375259 pRPD Block 4 fC Distribution, 30 - <40% Cent ",100,0,400000);
        Run375259_pRPD_fC[5][3] = new TH1F("","Run 375259 pRPD Block 5 fC Distribution, 30 - <40% Cent ",100,0,400000);
        Run375259_pRPD_fC[6][3] = new TH1F("","Run 375259 pRPD Block 6 fC Distribution, 30 - <40% Cent ",100,0,400000);
        Run375259_pRPD_fC[7][3] = new TH1F("","Run 375259 pRPD Block 7 fC Distribution, 30 - <40% Cent ",100,0,400000);
        Run375259_pRPD_fC[8][3] = new TH1F("","Run 375259 pRPD Block 8 fC Distribution, 30 - <40% Cent ",100,0,400000);
        Run375259_pRPD_fC[9][3] = new TH1F("","Run 375259 pRPD Block 9 fC Distribution, 30 - <40% Cent ",100,0,400000);
        Run375259_pRPD_fC[10][3] = new TH1F("","Run 375259 pRPD Block 10 fC Distribution, 30 - <40% Cent ",100,0,400000);
        Run375259_pRPD_fC[11][3] = new TH1F("","Run 375259 pRPD Block 11 fC Distribution, 30 - <40% Cent ",100,0,400000);
        Run375259_pRPD_fC[12][3] = new TH1F("","Run 375259 pRPD Block 12 fC Distribution, 30 - <40% Cent ",100,0,400000);
        Run375259_pRPD_fC[13][3] = new TH1F("","Run 375259 pRPD Block 13 fC Distribution, 30 - <40% Cent ",100,0,400000);
        Run375259_pRPD_fC[14][3] = new TH1F("","Run 375259 pRPD Block 14 fC Distribution, 30 - <40% Cent ",100,0,400000);
        Run375259_pRPD_fC[15][3] = new TH1F("","Run 375259 pRPD Block 15 fC Distribution, 30 - <40% Cent ",100,0,400000);

        Run375259_pRPD_fC[0][4] = new TH1F("","Run 375259 pRPD Block 0 fC Distribution, 40 - <50% Cent ",100,0,400000);
        Run375259_pRPD_fC[1][4] = new TH1F("","Run 375259 pRPD Block 1 fC Distribution, 40 - <50% Cent ",100,0,400000);
        Run375259_pRPD_fC[2][4] = new TH1F("","Run 375259 pRPD Block 2 fC Distribution, 40 - <50% Cent ",100,0,400000);
        Run375259_pRPD_fC[3][4] = new TH1F("","Run 375259 pRPD Block 3 fC Distribution, 40 - <50% Cent ",100,0,400000);
        Run375259_pRPD_fC[4][4] = new TH1F("","Run 375259 pRPD Block 4 fC Distribution, 40 - <50% Cent ",100,0,400000);
        Run375259_pRPD_fC[5][4] = new TH1F("","Run 375259 pRPD Block 5 fC Distribution, 40 - <50% Cent ",100,0,400000);
        Run375259_pRPD_fC[6][4] = new TH1F("","Run 375259 pRPD Block 6 fC Distribution, 40 - <50% Cent ",100,0,400000);
        Run375259_pRPD_fC[7][4] = new TH1F("","Run 375259 pRPD Block 7 fC Distribution, 40 - <50% Cent ",100,0,400000);
        Run375259_pRPD_fC[8][4] = new TH1F("","Run 375259 pRPD Block 8 fC Distribution, 40 - <50% Cent ",100,0,400000);
        Run375259_pRPD_fC[9][4] = new TH1F("","Run 375259 pRPD Block 9 fC Distribution, 40 - <50% Cent ",100,0,400000);
        Run375259_pRPD_fC[10][4] = new TH1F("","Run 375259 pRPD Block 10 fC Distribution, 40 - <50% Cent ",100,0,400000);
        Run375259_pRPD_fC[11][4] = new TH1F("","Run 375259 pRPD Block 11 fC Distribution, 40 - <50% Cent ",100,0,400000);
        Run375259_pRPD_fC[12][4] = new TH1F("","Run 375259 pRPD Block 12 fC Distribution, 40 - <50% Cent ",100,0,400000);
        Run375259_pRPD_fC[13][4] = new TH1F("","Run 375259 pRPD Block 13 fC Distribution, 40 - <50% Cent ",100,0,400000);
        Run375259_pRPD_fC[14][4] = new TH1F("","Run 375259 pRPD Block 14 fC Distribution, 40 - <50% Cent ",100,0,400000);
        Run375259_pRPD_fC[15][4] = new TH1F("","Run 375259 pRPD Block 15 fC Distribution, 40 - <50% Cent ",100,0,400000);

        Run375259_pRPD_fC[0][5] = new TH1F("","Run 375259 pRPD Block 0 fC Distribution, 50 - <60% Cent ",100,0,400000);
        Run375259_pRPD_fC[1][5] = new TH1F("","Run 375259 pRPD Block 1 fC Distribution, 50 - <60% Cent ",100,0,400000);
        Run375259_pRPD_fC[2][5] = new TH1F("","Run 375259 pRPD Block 2 fC Distribution, 50 - <60% Cent ",100,0,400000);
        Run375259_pRPD_fC[3][5] = new TH1F("","Run 375259 pRPD Block 3 fC Distribution, 50 - <60% Cent ",100,0,400000);
        Run375259_pRPD_fC[4][5] = new TH1F("","Run 375259 pRPD Block 4 fC Distribution, 50 - <60% Cent ",100,0,400000);
        Run375259_pRPD_fC[5][5] = new TH1F("","Run 375259 pRPD Block 5 fC Distribution, 50 - <60% Cent ",100,0,400000);
        Run375259_pRPD_fC[6][5] = new TH1F("","Run 375259 pRPD Block 6 fC Distribution, 50 - <60% Cent ",100,0,400000);
        Run375259_pRPD_fC[7][5] = new TH1F("","Run 375259 pRPD Block 7 fC Distribution, 50 - <60% Cent ",100,0,400000);
        Run375259_pRPD_fC[8][5] = new TH1F("","Run 375259 pRPD Block 8 fC Distribution, 50 - <60% Cent ",100,0,400000);
        Run375259_pRPD_fC[9][5] = new TH1F("","Run 375259 pRPD Block 9 fC Distribution, 50 - <60% Cent ",100,0,400000);
        Run375259_pRPD_fC[10][5] = new TH1F("","Run 375259 pRPD Block 10 fC Distribution, 50 - <60% Cent ",100,0,400000);
        Run375259_pRPD_fC[11][5] = new TH1F("","Run 375259 pRPD Block 11 fC Distribution, 50 - <60% Cent ",100,0,400000);
        Run375259_pRPD_fC[12][5] = new TH1F("","Run 375259 pRPD Block 12 fC Distribution, 50 - <60% Cent ",100,0,400000);
        Run375259_pRPD_fC[13][5] = new TH1F("","Run 375259 pRPD Block 13 fC Distribution, 50 - <60% Cent ",100,0,400000);
        Run375259_pRPD_fC[14][5] = new TH1F("","Run 375259 pRPD Block 14 fC Distribution, 50 - <60% Cent ",100,0,400000);
        Run375259_pRPD_fC[15][5] = new TH1F("","Run 375259 pRPD Block 15 fC Distribution, 50 - <60% Cent ",100,0,400000);

        Run375259_pRPD_fC[0][6] = new TH1F("","Run 375259 pRPD Block 0 fC Distribution, 60 - <70% Cent ",100,0,400000);
        Run375259_pRPD_fC[1][6] = new TH1F("","Run 375259 pRPD Block 1 fC Distribution, 60 - <70% Cent ",100,0,400000);
        Run375259_pRPD_fC[2][6] = new TH1F("","Run 375259 pRPD Block 2 fC Distribution, 60 - <70% Cent ",100,0,400000);
        Run375259_pRPD_fC[3][6] = new TH1F("","Run 375259 pRPD Block 3 fC Distribution, 60 - <70% Cent ",100,0,400000);
        Run375259_pRPD_fC[4][6] = new TH1F("","Run 375259 pRPD Block 4 fC Distribution, 60 - <70% Cent ",100,0,400000);
        Run375259_pRPD_fC[5][6] = new TH1F("","Run 375259 pRPD Block 5 fC Distribution, 60 - <70% Cent ",100,0,400000);
        Run375259_pRPD_fC[6][6] = new TH1F("","Run 375259 pRPD Block 6 fC Distribution, 60 - <70% Cent ",100,0,400000);
        Run375259_pRPD_fC[7][6] = new TH1F("","Run 375259 pRPD Block 7 fC Distribution, 60 - <70% Cent ",100,0,400000);
        Run375259_pRPD_fC[8][6] = new TH1F("","Run 375259 pRPD Block 8 fC Distribution, 60 - <70% Cent ",100,0,400000);
        Run375259_pRPD_fC[9][6] = new TH1F("","Run 375259 pRPD Block 9 fC Distribution, 60 - <70% Cent ",100,0,400000);
        Run375259_pRPD_fC[10][6] = new TH1F("","Run 375259 pRPD Block 10 fC Distribution, 60 - <70% Cent ",100,0,400000);
        Run375259_pRPD_fC[11][6] = new TH1F("","Run 375259 pRPD Block 11 fC Distribution, 60 - <70% Cent ",100,0,400000);
        Run375259_pRPD_fC[12][6] = new TH1F("","Run 375259 pRPD Block 12 fC Distribution, 60 - <70% Cent ",100,0,400000);
        Run375259_pRPD_fC[13][6] = new TH1F("","Run 375259 pRPD Block 13 fC Distribution, 60 - <70% Cent ",100,0,400000);
        Run375259_pRPD_fC[14][6] = new TH1F("","Run 375259 pRPD Block 14 fC Distribution, 60 - <70% Cent ",100,0,400000);
        Run375259_pRPD_fC[15][6] = new TH1F("","Run 375259 pRPD Block 15 fC Distribution, 60 - <70% Cent ",100,0,400000);

        Run375259_pRPD_fC[0][7] = new TH1F("","Run 375259 pRPD Block 0 fC Distribution, 70 - <80% Cent ",100,0,400000);
        Run375259_pRPD_fC[1][7] = new TH1F("","Run 375259 pRPD Block 1 fC Distribution, 70 - <80% Cent ",100,0,400000);
        Run375259_pRPD_fC[2][7] = new TH1F("","Run 375259 pRPD Block 2 fC Distribution, 70 - <80% Cent ",100,0,400000);
        Run375259_pRPD_fC[3][7] = new TH1F("","Run 375259 pRPD Block 3 fC Distribution, 70 - <80% Cent ",100,0,400000);
        Run375259_pRPD_fC[4][7] = new TH1F("","Run 375259 pRPD Block 4 fC Distribution, 70 - <80% Cent ",100,0,400000);
        Run375259_pRPD_fC[5][7] = new TH1F("","Run 375259 pRPD Block 5 fC Distribution, 70 - <80% Cent ",100,0,400000);
        Run375259_pRPD_fC[6][7] = new TH1F("","Run 375259 pRPD Block 6 fC Distribution, 70 - <80% Cent ",100,0,400000);
        Run375259_pRPD_fC[7][7] = new TH1F("","Run 375259 pRPD Block 7 fC Distribution, 70 - <80% Cent ",100,0,400000);
        Run375259_pRPD_fC[8][7] = new TH1F("","Run 375259 pRPD Block 8 fC Distribution, 70 - <80% Cent ",100,0,400000);
        Run375259_pRPD_fC[9][7] = new TH1F("","Run 375259 pRPD Block 9 fC Distribution, 70 - <80% Cent ",100,0,400000);
        Run375259_pRPD_fC[10][7] = new TH1F("","Run 375259 pRPD Block 10 fC Distribution, 70 - <80% Cent ",100,0,400000);
        Run375259_pRPD_fC[11][7] = new TH1F("","Run 375259 pRPD Block 11 fC Distribution, 70 - <80% Cent ",100,0,400000);
        Run375259_pRPD_fC[12][7] = new TH1F("","Run 375259 pRPD Block 12 fC Distribution, 70 - <80% Cent ",100,0,400000);
        Run375259_pRPD_fC[13][7] = new TH1F("","Run 375259 pRPD Block 13 fC Distribution, 70 - <80% Cent ",100,0,400000);
        Run375259_pRPD_fC[14][7] = new TH1F("","Run 375259 pRPD Block 14 fC Distribution, 70 - <80% Cent ",100,0,400000);
        Run375259_pRPD_fC[15][7] = new TH1F("","Run 375259 pRPD Block 15 fC Distribution, 70 - <80% Cent ",100,0,400000);

        Run375259_pRPD_fC[0][8] = new TH1F("","Run 375259 pRPD Block 0 fC Distribution, 80 - <90% Cent ",100,0,400000);
        Run375259_pRPD_fC[1][8] = new TH1F("","Run 375259 pRPD Block 1 fC Distribution, 80 - <90% Cent ",100,0,400000);
        Run375259_pRPD_fC[2][8] = new TH1F("","Run 375259 pRPD Block 2 fC Distribution, 80 - <90% Cent ",100,0,400000);
        Run375259_pRPD_fC[3][8] = new TH1F("","Run 375259 pRPD Block 3 fC Distribution, 80 - <90% Cent ",100,0,400000);
        Run375259_pRPD_fC[4][8] = new TH1F("","Run 375259 pRPD Block 4 fC Distribution, 80 - <90% Cent ",100,0,400000);
        Run375259_pRPD_fC[5][8] = new TH1F("","Run 375259 pRPD Block 5 fC Distribution, 80 - <90% Cent ",100,0,400000);
        Run375259_pRPD_fC[6][8] = new TH1F("","Run 375259 pRPD Block 6 fC Distribution, 80 - <90% Cent ",100,0,400000);
        Run375259_pRPD_fC[7][8] = new TH1F("","Run 375259 pRPD Block 7 fC Distribution, 80 - <90% Cent ",100,0,400000);
        Run375259_pRPD_fC[8][8] = new TH1F("","Run 375259 pRPD Block 8 fC Distribution, 80 - <90% Cent ",100,0,400000);
        Run375259_pRPD_fC[9][8] = new TH1F("","Run 375259 pRPD Block 9 fC Distribution, 80 - <90% Cent ",100,0,400000);
        Run375259_pRPD_fC[10][8] = new TH1F("","Run 375259 pRPD Block 10 fC Distribution, 80 - <90% Cent ",100,0,400000);
        Run375259_pRPD_fC[11][8] = new TH1F("","Run 375259 pRPD Block 11 fC Distribution, 80 - <90% Cent ",100,0,400000);
        Run375259_pRPD_fC[12][8] = new TH1F("","Run 375259 pRPD Block 12 fC Distribution, 80 - <90% Cent ",100,0,400000);
        Run375259_pRPD_fC[13][8] = new TH1F("","Run 375259 pRPD Block 13 fC Distribution, 80 - <90% Cent ",100,0,400000);
        Run375259_pRPD_fC[14][8] = new TH1F("","Run 375259 pRPD Block 14 fC Distribution, 80 - <90% Cent ",100,0,400000);
        Run375259_pRPD_fC[15][8] = new TH1F("","Run 375259 pRPD Block 15 fC Distribution, 80 - <90% Cent ",100,0,400000);

        Run375259_pRPD_fC[0][9] = new TH1F("","Run 375259 pRPD Block 0 fC Distribution, 90 - <100% Cent ",100,0,400000);
        Run375259_pRPD_fC[1][9] = new TH1F("","Run 375259 pRPD Block 1 fC Distribution, 90 - <100% Cent ",100,0,400000);
        Run375259_pRPD_fC[2][9] = new TH1F("","Run 375259 pRPD Block 2 fC Distribution, 90 - <100% Cent ",100,0,400000);
        Run375259_pRPD_fC[3][9] = new TH1F("","Run 375259 pRPD Block 3 fC Distribution, 90 - <100% Cent ",100,0,400000);
        Run375259_pRPD_fC[4][9] = new TH1F("","Run 375259 pRPD Block 4 fC Distribution, 90 - <100% Cent ",100,0,400000);
        Run375259_pRPD_fC[5][9] = new TH1F("","Run 375259 pRPD Block 5 fC Distribution, 90 - <100% Cent ",100,0,400000);
        Run375259_pRPD_fC[6][9] = new TH1F("","Run 375259 pRPD Block 6 fC Distribution, 90 - <100% Cent ",100,0,400000);
        Run375259_pRPD_fC[7][9] = new TH1F("","Run 375259 pRPD Block 7 fC Distribution, 90 - <100% Cent ",100,0,400000);
        Run375259_pRPD_fC[8][9] = new TH1F("","Run 375259 pRPD Block 8 fC Distribution, 90 - <100% Cent ",100,0,400000);
        Run375259_pRPD_fC[9][9] = new TH1F("","Run 375259 pRPD Block 9 fC Distribution, 90 - <100% Cent ",100,0,400000);
        Run375259_pRPD_fC[10][9] = new TH1F("","Run 375259 pRPD Block 10 fC Distribution, 90 - <100% Cent ",100,0,400000);
        Run375259_pRPD_fC[11][9] = new TH1F("","Run 375259 pRPD Block 11 fC Distribution, 90 - <100% Cent ",100,0,400000);
        Run375259_pRPD_fC[12][9] = new TH1F("","Run 375259 pRPD Block 12 fC Distribution, 90 - <100% Cent ",100,0,400000);
        Run375259_pRPD_fC[13][9] = new TH1F("","Run 375259 pRPD Block 13 fC Distribution, 90 - <100% Cent ",100,0,400000);
        Run375259_pRPD_fC[14][9] = new TH1F("","Run 375259 pRPD Block 14 fC Distribution, 90 - <100% Cent ",100,0,400000);
        Run375259_pRPD_fC[15][9] = new TH1F("","Run 375259 pRPD Block 15 fC Distribution, 90 - <100% Cent ",100,0,400000);

        Run375259_pRPD_fC[0][10] = new TH1F("","Run 375259 pRPD Block 0 fC Distribution, All Cent ",100,0,400000);
        Run375259_pRPD_fC[1][10] = new TH1F("","Run 375259 pRPD Block 1 fC Distribution, All Cent ",100,0,400000);
        Run375259_pRPD_fC[2][10] = new TH1F("","Run 375259 pRPD Block 2 fC Distribution, All Cent ",100,0,400000);
        Run375259_pRPD_fC[3][10] = new TH1F("","Run 375259 pRPD Block 3 fC Distribution, All Cent ",100,0,400000);
        Run375259_pRPD_fC[4][10] = new TH1F("","Run 375259 pRPD Block 4 fC Distribution, All Cent ",100,0,400000);
        Run375259_pRPD_fC[5][10] = new TH1F("","Run 375259 pRPD Block 5 fC Distribution, All Cent ",100,0,400000);
        Run375259_pRPD_fC[6][10] = new TH1F("","Run 375259 pRPD Block 6 fC Distribution, All Cent ",100,0,400000);
        Run375259_pRPD_fC[7][10] = new TH1F("","Run 375259 pRPD Block 7 fC Distribution, All Cent ",100,0,400000);
        Run375259_pRPD_fC[8][10] = new TH1F("","Run 375259 pRPD Block 8 fC Distribution, All Cent ",100,0,400000);
        Run375259_pRPD_fC[9][10] = new TH1F("","Run 375259 pRPD Block 9 fC Distribution, All Cent ",100,0,400000);
        Run375259_pRPD_fC[10][10] = new TH1F("","Run 375259 pRPD Block 10 fC Distribution, All Cent ",100,0,400000);
        Run375259_pRPD_fC[11][10] = new TH1F("","Run 375259 pRPD Block 11 fC Distribution, All Cent ",100,0,400000);
        Run375259_pRPD_fC[12][10] = new TH1F("","Run 375259 pRPD Block 12 fC Distribution, All Cent ",100,0,400000);
        Run375259_pRPD_fC[13][10] = new TH1F("","Run 375259 pRPD Block 13 fC Distribution, All Cent ",100,0,400000);
        Run375259_pRPD_fC[14][10] = new TH1F("","Run 375259 pRPD Block 14 fC Distribution, All Cent ",100,0,400000);
        Run375259_pRPD_fC[15][10] = new TH1F("","Run 375259 pRPD Block 15 fC Distribution, All Cent ",100,0,400000);

    //COM Plot for entire pos RPD

    TH2F *Run375259_pRPD_COM[11] = {0};

        Run375259_pRPD_COM[0] = new TH2F("","Run 375259 pRPD COM 0 to <10% Cent",200,-4,4,200,-4,4);
        Run375259_pRPD_COM[1] = new TH2F("","Run 375259 pRPD COM 10 to <20% Cent",200,-4,4,200,-4,4);
        Run375259_pRPD_COM[2] = new TH2F("","Run 375259 pRPD COM 20 to <30% Cent",200,-4,4,200,-4,4);
        Run375259_pRPD_COM[3] = new TH2F("","Run 375259 pRPD COM 30 to <40% Cent",200,-4,4,200,-4,4);
        Run375259_pRPD_COM[4] = new TH2F("","Run 375259 pRPD COM 40 to <50% Cent",200,-4,4,200,-4,4);
        Run375259_pRPD_COM[5] = new TH2F("","Run 375259 pRPD COM 50 to <60% Cent",200,-4,4,200,-4,4);
        Run375259_pRPD_COM[6] = new TH2F("","Run 375259 pRPD COM 60 to <70% Cent",200,-4,4,200,-4,4);
        Run375259_pRPD_COM[7] = new TH2F("","Run 375259 pRPD COM 70 to <80% Cent",200,-4,4,200,-4,4);
        Run375259_pRPD_COM[8] = new TH2F("","Run 375259 pRPD COM 80 to <90% Cent",200,-4,4,200,-4,4);
        Run375259_pRPD_COM[9] = new TH2F("","Run 375259 pRPD COM 90 to <100% Cent",200,-4,4,200,-4,4);
        Run375259_pRPD_COM[10] = new TH2F("","Run 375259 pRPD COM All Cent",200,-4,4,200,-4,4);

    // TProfiles for pos RPD
    TProfile *Run375259_pRPD_prof[11] = {0};

        Run375259_pRPD_prof[0] = new TProfile("","Run 375259 pRPD Average X Signal 0 to 10 cent",4,0,4);
        Run375259_pRPD_prof[1] = new TProfile("","Run 375259 pRPD Average X Signal 10 to 20 cent",4,0,4);
        Run375259_pRPD_prof[2] = new TProfile("","Run 375259 pRPD Average X Signal 20 to 30 cent",4,0,4);
        Run375259_pRPD_prof[3] = new TProfile("","Run 375259 pRPD Average X Signal 30 to 40 cent",4,0,4);
        Run375259_pRPD_prof[4] = new TProfile("","Run 375259 pRPD Average X Signal 40 to 50 cent",4,0,4);
        Run375259_pRPD_prof[5] = new TProfile("","Run 375259 pRPD Average X Signal 50 to 60 cent",4,0,4);
        Run375259_pRPD_prof[6] = new TProfile("","Run 375259 pRPD Average X Signal 60 to 70 cent",4,0,4);
        Run375259_pRPD_prof[7] = new TProfile("","Run 375259 pRPD Average X Signal 70 to 80 cent",4,0,4);
        Run375259_pRPD_prof[8] = new TProfile("","Run 375259 pRPD Average X Signal 80 to 90 cent",4,0,4);
        Run375259_pRPD_prof[9] = new TProfile("","Run 375259 pRPD Average X Signal 90 to 100 cent",4,0,4);
        Run375259_pRPD_prof[10] = new TProfile("","Run 375259 pRPD Average X Signal all cent",4,0,4);

    //Stack for all COM Projection Histograms
    TH1F *pos_rpd_xprojection[11] = {0};

        pos_rpd_xprojection[0] = new TH1F("", "X Projection 0 to 10", 200, -1, 2.5);
        pos_rpd_xprojection[1] = new TH1F("", "X Projection 10 to 20", 200, -1, 2.5);
        pos_rpd_xprojection[2] = new TH1F("", "X Projection 20 to 30", 200, -1, 2.5);
        pos_rpd_xprojection[3] = new TH1F("", "X Projection 30 to 40", 200, -1, 2.5);
        pos_rpd_xprojection[4] = new TH1F("", "X Projection 40 to 50", 200, -1, 2.5);
        pos_rpd_xprojection[5] = new TH1F("", "X Projection 50 to 60", 200, -1, 2.5);
        pos_rpd_xprojection[6] = new TH1F("", "X Projection 60 to 70", 200, -1, 2.5);
        pos_rpd_xprojection[7] = new TH1F("", "X Projection 70 to 80", 200, -1, 2.5);
        pos_rpd_xprojection[8] = new TH1F("", "X Projection 80 to 90", 200, -1, 2.5);
        pos_rpd_xprojection[9] = new TH1F("", "X Projection 90 to 100", 200, -1, 2.5);
        pos_rpd_xprojection[10] = new TH1F("", "X Projection 90 to 100", 200, -1, 2.5);

    THStack *pRPD_stack = new THStack("", "Run375259 pRPD X Distribution with Centrality");

     TH1F *Run375259_pEM_TS[5][11] = {0};

        Run375259_pEM_TS[0][0] = new TH1F("","Run 375259 pEM section 1, 0 - <10% Centrality",6,0,6);
        Run375259_pEM_TS[1][0] = new TH1F("","Run 375259 pEM section 2, 0 - <10% Centrality",6,0,6);
        Run375259_pEM_TS[2][0] = new TH1F("","Run 375259 pEM section 3, 0 - <10% Centrality",6,0,6);
        Run375259_pEM_TS[3][0] = new TH1F("","Run 375259 pEM section 4, 0 - <10% Centrality",6,0,6);
        Run375259_pEM_TS[4][0] = new TH1F("","Run 375259 pEM section 5, 0 - <10% Centrality",6,0,6);

        Run375259_pEM_TS[0][1] = new TH1F("","Run 375259 pEM section 1, 10 - <20% Centrality",6,0,6);
        Run375259_pEM_TS[1][1] = new TH1F("","Run 375259 pEM section 2, 10 - <20% Centrality",6,0,6);
        Run375259_pEM_TS[2][1] = new TH1F("","Run 375259 pEM section 3, 10 - <20% Centrality",6,0,6);
        Run375259_pEM_TS[3][1] = new TH1F("","Run 375259 pEM section 4, 10 - <20% Centrality",6,0,6);
        Run375259_pEM_TS[4][1] = new TH1F("","Run 375259 pEM section 5, 10 - <20% Centrality",6,0,6);

        Run375259_pEM_TS[0][2] = new TH1F("","Run 375259 pEM section 1, 20 - <30% Centrality",6,0,6);
        Run375259_pEM_TS[1][2] = new TH1F("","Run 375259 pEM section 2, 20 - <30% Centrality",6,0,6);
        Run375259_pEM_TS[2][2] = new TH1F("","Run 375259 pEM section 3, 20 - <30% Centrality",6,0,6);
        Run375259_pEM_TS[3][2] = new TH1F("","Run 375259 pEM section 4, 20 - <30% Centrality",6,0,6);
        Run375259_pEM_TS[4][2] = new TH1F("","Run 375259 pEM section 5, 20 - <30% Centrality",6,0,6);

        Run375259_pEM_TS[0][3] = new TH1F("","Run 375259 pEM section 1, 30 - <40% Centrality",6,0,6);
        Run375259_pEM_TS[1][3] = new TH1F("","Run 375259 pEM section 2, 30 - <40% Centrality",6,0,6);
        Run375259_pEM_TS[2][3] = new TH1F("","Run 375259 pEM section 3, 30 - <40% Centrality",6,0,6);
        Run375259_pEM_TS[3][3] = new TH1F("","Run 375259 pEM section 4, 30 - <40% Centrality",6,0,6);
        Run375259_pEM_TS[4][3] = new TH1F("","Run 375259 pEM section 5, 30 - <40% Centrality",6,0,6);

        Run375259_pEM_TS[0][4] = new TH1F("","Run 375259 pEM section 1, 40 - <50% Centrality",6,0,6);
        Run375259_pEM_TS[1][4] = new TH1F("","Run 375259 pEM section 2, 40 - <50% Centrality",6,0,6);
        Run375259_pEM_TS[2][4] = new TH1F("","Run 375259 pEM section 3, 40 - <50% Centrality",6,0,6);
        Run375259_pEM_TS[3][4] = new TH1F("","Run 375259 pEM section 4, 40 - <50% Centrality",6,0,6);
        Run375259_pEM_TS[4][4] = new TH1F("","Run 375259 pEM section 5, 40 - <50% Centrality",6,0,6);

        Run375259_pEM_TS[0][5] = new TH1F("","Run 375259 pEM section 1, 50 - <60% Centrality",6,0,6);
        Run375259_pEM_TS[1][5] = new TH1F("","Run 375259 pEM section 2, 50 - <60% Centrality",6,0,6);
        Run375259_pEM_TS[2][5] = new TH1F("","Run 375259 pEM section 3, 50 - <60% Centrality",6,0,6);
        Run375259_pEM_TS[3][5] = new TH1F("","Run 375259 pEM section 4, 50 - <60% Centrality",6,0,6);
        Run375259_pEM_TS[4][5] = new TH1F("","Run 375259 pEM section 5, 50 - <60% Centrality",6,0,6);

        Run375259_pEM_TS[0][6] = new TH1F("","Run 375259 pEM section 1, 60 - <70% Centrality",6,0,6);
        Run375259_pEM_TS[1][6] = new TH1F("","Run 375259 pEM section 2, 60 - <70% Centrality",6,0,6);
        Run375259_pEM_TS[2][6] = new TH1F("","Run 375259 pEM section 3, 60 - <70% Centrality",6,0,6);
        Run375259_pEM_TS[3][6] = new TH1F("","Run 375259 pEM section 4, 60 - <70% Centrality",6,0,6);
        Run375259_pEM_TS[4][6] = new TH1F("","Run 375259 pEM section 5, 60 - <70% Centrality",6,0,6);

        Run375259_pEM_TS[0][7] = new TH1F("","Run 375259 pEM section 1, 70 - <80% Centrality",6,0,6);
        Run375259_pEM_TS[1][7] = new TH1F("","Run 375259 pEM section 2, 70 - <80% Centrality",6,0,6);
        Run375259_pEM_TS[2][7] = new TH1F("","Run 375259 pEM section 3, 70 - <80% Centrality",6,0,6);
        Run375259_pEM_TS[3][7] = new TH1F("","Run 375259 pEM section 4, 70 - <80% Centrality",6,0,6);
        Run375259_pEM_TS[4][7] = new TH1F("","Run 375259 pEM section 5, 70 - <80% Centrality",6,0,6);

        Run375259_pEM_TS[0][8] = new TH1F("","Run 375259 pEM section 1, 80 - <90% Centrality",6,0,6);
        Run375259_pEM_TS[1][8] = new TH1F("","Run 375259 pEM section 2, 80 - <90% Centrality",6,0,6);
        Run375259_pEM_TS[2][8] = new TH1F("","Run 375259 pEM section 3, 80 - <90% Centrality",6,0,6);
        Run375259_pEM_TS[3][8] = new TH1F("","Run 375259 pEM section 4, 80 - <90% Centrality",6,0,6);
        Run375259_pEM_TS[4][8] = new TH1F("","Run 375259 pEM section 5, 80 - <90% Centrality",6,0,6);

        Run375259_pEM_TS[0][9] = new TH1F("","Run 375259 pEM section 1, 90 - <100% Centrality",6,0,6);
        Run375259_pEM_TS[1][9] = new TH1F("","Run 375259 pEM section 2, 90 - <100% Centrality",6,0,6);
        Run375259_pEM_TS[2][9] = new TH1F("","Run 375259 pEM section 3, 90 - <100% Centrality",6,0,6);
        Run375259_pEM_TS[3][9] = new TH1F("","Run 375259 pEM section 4, 90 - <100% Centrality",6,0,6);
        Run375259_pEM_TS[4][9] = new TH1F("","Run 375259 pEM section 5, 90 - <100% Centrality",6,0,6);

        Run375259_pEM_TS[0][10] = new TH1F("","Run 375259 pEM section 1, All Centrality",6,0,6);
        Run375259_pEM_TS[1][10] = new TH1F("","Run 375259 pEM section 2, All Centrality",6,0,6);
        Run375259_pEM_TS[2][10] = new TH1F("","Run 375259 pEM section 3, All Centrality",6,0,6);
        Run375259_pEM_TS[3][10] = new TH1F("","Run 375259 pEM section 4, All Centrality",6,0,6);
        Run375259_pEM_TS[4][10] = new TH1F("","Run 375259 pEM section 5, All Centrality",6,0,6);
    
    TH1F *Run375259_pEM_TSratio[5][11] = {0};

        Run375259_pEM_TSratio[0][0] = new TH1F("","Run 375259 pEM TS Ratio Section 1, 0 - <10% Centrality",60,0,6);
        Run375259_pEM_TSratio[1][0] = new TH1F("","Run 375259 pEM TS Ratio Section 2, 0 - <10% Centrality",60,0,6);
        Run375259_pEM_TSratio[2][0] = new TH1F("","Run 375259 pEM TS Ratio Section 3, 0 - <10% Centrality",60,0,6);
        Run375259_pEM_TSratio[3][0] = new TH1F("","Run 375259 pEM TS Ratio Section 4, 0 - <10% Centrality",60,0,6);
        Run375259_pEM_TSratio[4][0] = new TH1F("","Run 375259 pEM TS Ratio Section 5, 0 - <10% Centrality",60,0,6);

        Run375259_pEM_TSratio[0][1] = new TH1F("","Run 375259 pEM TS Ratio Section 1, 10 - <20% Centrality",60,0,6);
        Run375259_pEM_TSratio[1][1] = new TH1F("","Run 375259 pEM TS Ratio Section 2, 10 - <20% Centrality",60,0,6);
        Run375259_pEM_TSratio[2][1] = new TH1F("","Run 375259 pEM TS Ratio Section 3, 10 - <20% Centrality",60,0,6);
        Run375259_pEM_TSratio[3][1] = new TH1F("","Run 375259 pEM TS Ratio Section 4, 10 - <20% Centrality",60,0,6);
        Run375259_pEM_TSratio[4][1] = new TH1F("","Run 375259 pEM TS Ratio Section 5, 10 - <20% Centrality",60,0,6);

        Run375259_pEM_TSratio[0][2] = new TH1F("","Run 375259 pEM TS Ratio Section 1, 20 - <30% Centrality",60,0,6);
        Run375259_pEM_TSratio[1][2] = new TH1F("","Run 375259 pEM TS Ratio Section 2, 20 - <30% Centrality",60,0,6);
        Run375259_pEM_TSratio[2][2] = new TH1F("","Run 375259 pEM TS Ratio Section 3, 20 - <30% Centrality",60,0,6);
        Run375259_pEM_TSratio[3][2] = new TH1F("","Run 375259 pEM TS Ratio Section 4, 20 - <30% Centrality",60,0,6);
        Run375259_pEM_TSratio[4][2] = new TH1F("","Run 375259 pEM TS Ratio Section 5, 20 - <30% Centrality",60,0,6);

        Run375259_pEM_TSratio[0][3] = new TH1F("","Run 375259 pEM TS Ratio Section 1, 30 - <40% Centrality",60,0,6);
        Run375259_pEM_TSratio[1][3] = new TH1F("","Run 375259 pEM TS Ratio Section 2, 30 - <40% Centrality",60,0,6);
        Run375259_pEM_TSratio[2][3] = new TH1F("","Run 375259 pEM TS Ratio Section 3, 30 - <40% Centrality",60,0,6);
        Run375259_pEM_TSratio[3][3] = new TH1F("","Run 375259 pEM TS Ratio Section 4, 30 - <40% Centrality",60,0,6);
        Run375259_pEM_TSratio[4][3] = new TH1F("","Run 375259 pEM TS Ratio Section 5, 30 - <40% Centrality",60,0,6);

        Run375259_pEM_TSratio[0][4] = new TH1F("","Run 375259 pEM TS Ratio Section 1, 40 - <50% Centrality",60,0,6);
        Run375259_pEM_TSratio[1][4] = new TH1F("","Run 375259 pEM TS Ratio Section 2, 40 - <50% Centrality",60,0,6);
        Run375259_pEM_TSratio[2][4] = new TH1F("","Run 375259 pEM TS Ratio Section 3, 40 - <50% Centrality",60,0,6);
        Run375259_pEM_TSratio[3][4] = new TH1F("","Run 375259 pEM TS Ratio Section 4, 40 - <50% Centrality",60,0,6);
        Run375259_pEM_TSratio[4][4] = new TH1F("","Run 375259 pEM TS Ratio Section 5, 40 - <50% Centrality",60,0,6);

        Run375259_pEM_TSratio[0][5] = new TH1F("","Run 375259 pEM TS Ratio Section 1, 50 - <60% Centrality",60,0,6);
        Run375259_pEM_TSratio[1][5] = new TH1F("","Run 375259 pEM TS Ratio Section 2, 50 - <60% Centrality",60,0,6);
        Run375259_pEM_TSratio[2][5] = new TH1F("","Run 375259 pEM TS Ratio Section 3, 50 - <60% Centrality",60,0,6);
        Run375259_pEM_TSratio[3][5] = new TH1F("","Run 375259 pEM TS Ratio Section 4, 50 - <60% Centrality",60,0,6);
        Run375259_pEM_TSratio[4][5] = new TH1F("","Run 375259 pEM TS Ratio Section 5, 50 - <60% Centrality",60,0,6);

        Run375259_pEM_TSratio[0][6] = new TH1F("","Run 375259 pEM TS Ratio Section 1, 60 - <70% Centrality",60,0,6);
        Run375259_pEM_TSratio[1][6] = new TH1F("","Run 375259 pEM TS Ratio Section 2, 60 - <70% Centrality",60,0,6);
        Run375259_pEM_TSratio[2][6] = new TH1F("","Run 375259 pEM TS Ratio Section 3, 60 - <70% Centrality",60,0,6);
        Run375259_pEM_TSratio[3][6] = new TH1F("","Run 375259 pEM TS Ratio Section 4, 60 - <70% Centrality",60,0,6);
        Run375259_pEM_TSratio[4][6] = new TH1F("","Run 375259 pEM TS Ratio Section 5, 60 - <70% Centrality",60,0,6);

        Run375259_pEM_TSratio[0][7] = new TH1F("","Run 375259 pEM TS Ratio Section 1, 70 - <80% Centrality",60,0,6);
        Run375259_pEM_TSratio[1][7] = new TH1F("","Run 375259 pEM TS Ratio Section 2, 70 - <80% Centrality",60,0,6);
        Run375259_pEM_TSratio[2][7] = new TH1F("","Run 375259 pEM TS Ratio Section 3, 70 - <80% Centrality",60,0,6);
        Run375259_pEM_TSratio[3][7] = new TH1F("","Run 375259 pEM TS Ratio Section 4, 70 - <80% Centrality",60,0,6);
        Run375259_pEM_TSratio[4][7] = new TH1F("","Run 375259 pEM TS Ratio Section 5, 70 - <80% Centrality",60,0,6);

        Run375259_pEM_TSratio[0][8] = new TH1F("","Run 375259 pEM TS Ratio Section 1, 80 - <90% Centrality",60,0,6);
        Run375259_pEM_TSratio[1][8] = new TH1F("","Run 375259 pEM TS Ratio Section 2, 80 - <90% Centrality",60,0,6);
        Run375259_pEM_TSratio[2][8] = new TH1F("","Run 375259 pEM TS Ratio Section 3, 80 - <90% Centrality",60,0,6);
        Run375259_pEM_TSratio[3][8] = new TH1F("","Run 375259 pEM TS Ratio Section 4, 80 - <90% Centrality",60,0,6);
        Run375259_pEM_TSratio[4][8] = new TH1F("","Run 375259 pEM TS Ratio Section 5, 80 - <90% Centrality",60,0,6);

        Run375259_pEM_TSratio[0][9] = new TH1F("","Run 375259 pEM TS Ratio Section 1, 90 - <100% Centrality",60,0,6);
        Run375259_pEM_TSratio[1][9] = new TH1F("","Run 375259 pEM TS Ratio Section 2, 90 - <100% Centrality",60,0,6);
        Run375259_pEM_TSratio[2][9] = new TH1F("","Run 375259 pEM TS Ratio Section 3, 90 - <100% Centrality",60,0,6);
        Run375259_pEM_TSratio[3][9] = new TH1F("","Run 375259 pEM TS Ratio Section 4, 90 - <100% Centrality",60,0,6);
        Run375259_pEM_TSratio[4][9] = new TH1F("","Run 375259 pEM TS Ratio Section 5, 90 - <100% Centrality",60,0,6);

        Run375259_pEM_TSratio[0][10] = new TH1F("","Run 375259 pEM TS Ratio Section 1, All Centrality",60,0,6);
        Run375259_pEM_TSratio[1][10] = new TH1F("","Run 375259 pEM TS Ratio Section 2, All Centrality",60,0,6);
        Run375259_pEM_TSratio[2][10] = new TH1F("","Run 375259 pEM TS Ratio Section 3, All Centrality",60,0,6);
        Run375259_pEM_TSratio[3][10] = new TH1F("","Run 375259 pEM TS Ratio Section 4, All Centrality",60,0,6);
        Run375259_pEM_TSratio[4][10] = new TH1F("","Run 375259 pEM TS Ratio Section 5, All Centrality",60,0,6);

    TH1F *Run375259_pEM_fC[5][11] = {0};

        Run375259_pEM_fC[0][0] = new TH1F("","Run 375259 pEM Section 0 fC Distribution, 0 - <10% Cent",100,0,200000);
        Run375259_pEM_fC[1][0] = new TH1F("","Run 375259 pEM Section 1 fC Distribution, 0 - <10% Cent",100,0,200000);    
        Run375259_pEM_fC[2][0] = new TH1F("","Run 375259 pEM Section 2 fC Distribution, 0 - <10% Cent",100,0,200000);
        Run375259_pEM_fC[3][0] = new TH1F("","Run 375259 pEM Section 3 fC Distribution, 0 - <10% Cent",100,0,200000);
        Run375259_pEM_fC[4][0] = new TH1F("","Run 375259 pEM Section 4 fC Distribution, 0 - <10% Cent",100,0,200000);

        Run375259_pEM_fC[0][1] = new TH1F("","Run 375259 pEM Section 0 fC Distribution, 10 - <20% Cent",100,0,200000);
        Run375259_pEM_fC[1][1] = new TH1F("","Run 375259 pEM Section 1 fC Distribution, 10 - <20% Cent",100,0,200000);    
        Run375259_pEM_fC[2][1] = new TH1F("","Run 375259 pEM Section 2 fC Distribution, 10 - <20% Cent",100,0,200000);
        Run375259_pEM_fC[3][1] = new TH1F("","Run 375259 pEM Section 3 fC Distribution, 10 - <20% Cent",100,0,200000);
        Run375259_pEM_fC[4][1] = new TH1F("","Run 375259 pEM Section 4 fC Distribution, 10 - <20% Cent",100,0,200000);

        Run375259_pEM_fC[0][2] = new TH1F("","Run 375259 pEM Section 0 fC Distribution, 20 - <30% Cent",100,0,200000);
        Run375259_pEM_fC[1][2] = new TH1F("","Run 375259 pEM Section 1 fC Distribution, 20 - <30% Cent",100,0,200000);    
        Run375259_pEM_fC[2][2] = new TH1F("","Run 375259 pEM Section 2 fC Distribution, 20 - <30% Cent",100,0,200000);
        Run375259_pEM_fC[3][2] = new TH1F("","Run 375259 pEM Section 3 fC Distribution, 20 - <30% Cent",100,0,200000);
        Run375259_pEM_fC[4][2] = new TH1F("","Run 375259 pEM Section 4 fC Distribution, 20 - <30% Cent",100,0,200000);

        Run375259_pEM_fC[0][3] = new TH1F("","Run 375259 pEM Section 0 fC Distribution, 30 - <40% Cent",100,0,200000);
        Run375259_pEM_fC[1][3] = new TH1F("","Run 375259 pEM Section 1 fC Distribution, 30 - <40% Cent",100,0,200000);    
        Run375259_pEM_fC[2][3] = new TH1F("","Run 375259 pEM Section 2 fC Distribution, 30 - <40% Cent",100,0,200000);
        Run375259_pEM_fC[3][3] = new TH1F("","Run 375259 pEM Section 3 fC Distribution, 30 - <40% Cent",100,0,200000);
        Run375259_pEM_fC[4][3] = new TH1F("","Run 375259 pEM Section 4 fC Distribution, 30 - <40% Cent",100,0,200000);

        Run375259_pEM_fC[0][4] = new TH1F("","Run 375259 pEM Section 0 fC Distribution, 40 - <50% Cent",100,0,200000);
        Run375259_pEM_fC[1][4] = new TH1F("","Run 375259 pEM Section 1 fC Distribution, 40 - <50% Cent",100,0,200000);    
        Run375259_pEM_fC[2][4] = new TH1F("","Run 375259 pEM Section 2 fC Distribution, 40 - <50% Cent",100,0,200000);
        Run375259_pEM_fC[3][4] = new TH1F("","Run 375259 pEM Section 3 fC Distribution, 40 - <50% Cent",100,0,200000);
        Run375259_pEM_fC[4][4] = new TH1F("","Run 375259 pEM Section 4 fC Distribution, 40 - <50% Cent",100,0,200000);

        Run375259_pEM_fC[0][5] = new TH1F("","Run 375259 pEM Section 0 fC Distribution, 50 - <60% Cent",100,0,200000);
        Run375259_pEM_fC[1][5] = new TH1F("","Run 375259 pEM Section 1 fC Distribution, 50 - <60% Cent",100,0,200000);    
        Run375259_pEM_fC[2][5] = new TH1F("","Run 375259 pEM Section 2 fC Distribution, 50 - <60% Cent",100,0,200000);
        Run375259_pEM_fC[3][5] = new TH1F("","Run 375259 pEM Section 3 fC Distribution, 50 - <60% Cent",100,0,200000);
        Run375259_pEM_fC[4][5] = new TH1F("","Run 375259 pEM Section 4 fC Distribution, 50 - <60% Cent",100,0,200000);

        Run375259_pEM_fC[0][6] = new TH1F("","Run 375259 pEM Section 0 fC Distribution, 60 - <70% Cent",100,0,200000);
        Run375259_pEM_fC[1][6] = new TH1F("","Run 375259 pEM Section 1 fC Distribution, 60 - <70% Cent",100,0,200000);    
        Run375259_pEM_fC[2][6] = new TH1F("","Run 375259 pEM Section 2 fC Distribution, 60 - <70% Cent",100,0,200000);
        Run375259_pEM_fC[3][6] = new TH1F("","Run 375259 pEM Section 3 fC Distribution, 60 - <70% Cent",100,0,200000);
        Run375259_pEM_fC[4][6] = new TH1F("","Run 375259 pEM Section 4 fC Distribution, 60 - <70% Cent",100,0,200000);

        Run375259_pEM_fC[0][7] = new TH1F("","Run 375259 pEM Section 0 fC Distribution, 70 - <80% Cent",100,0,200000);
        Run375259_pEM_fC[1][7] = new TH1F("","Run 375259 pEM Section 1 fC Distribution, 70 - <80% Cent",100,0,200000);    
        Run375259_pEM_fC[2][7] = new TH1F("","Run 375259 pEM Section 2 fC Distribution, 70 - <80% Cent",100,0,200000);
        Run375259_pEM_fC[3][7] = new TH1F("","Run 375259 pEM Section 3 fC Distribution, 70 - <80% Cent",100,0,200000);
        Run375259_pEM_fC[4][7] = new TH1F("","Run 375259 pEM Section 4 fC Distribution, 70 - <80% Cent",100,0,200000);

        Run375259_pEM_fC[0][8] = new TH1F("","Run 375259 pEM Section 0 fC Distribution, 80 - <90% Cent",100,0,200000);
        Run375259_pEM_fC[1][8] = new TH1F("","Run 375259 pEM Section 1 fC Distribution, 80 - <90% Cent",100,0,200000);    
        Run375259_pEM_fC[2][8] = new TH1F("","Run 375259 pEM Section 2 fC Distribution, 80 - <90% Cent",100,0,200000);
        Run375259_pEM_fC[3][8] = new TH1F("","Run 375259 pEM Section 3 fC Distribution, 80 - <90% Cent",100,0,200000);
        Run375259_pEM_fC[4][8] = new TH1F("","Run 375259 pEM Section 4 fC Distribution, 80 - <90% Cent",100,0,200000);

        Run375259_pEM_fC[0][9] = new TH1F("","Run 375259 pEM Section 0 fC Distribution, 90 - <100% Cent",100,0,200000);
        Run375259_pEM_fC[1][9] = new TH1F("","Run 375259 pEM Section 1 fC Distribution, 90 - <100% Cent",100,0,200000);    
        Run375259_pEM_fC[2][9] = new TH1F("","Run 375259 pEM Section 2 fC Distribution, 90 - <100% Cent",100,0,200000);
        Run375259_pEM_fC[3][9] = new TH1F("","Run 375259 pEM Section 3 fC Distribution, 90 - <100% Cent",100,0,200000);
        Run375259_pEM_fC[4][9] = new TH1F("","Run 375259 pEM Section 4 fC Distribution, 90 - <100% Cent",100,0,200000);

        Run375259_pEM_fC[0][10] = new TH1F("","Run 375259 pEM Section 0 fC Distribution, All Cent",100,0,200000);
        Run375259_pEM_fC[1][10] = new TH1F("","Run 375259 pEM Section 1 fC Distribution, All Cent",100,0,200000);    
        Run375259_pEM_fC[2][10] = new TH1F("","Run 375259 pEM Section 2 fC Distribution, All Cent",100,0,200000);
        Run375259_pEM_fC[3][10] = new TH1F("","Run 375259 pEM Section 3 fC Distribution, All Cent",100,0,200000);
        Run375259_pEM_fC[4][10] = new TH1F("","Run 375259 pEM Section 4 fC Distribution, All Cent",100,0,200000);

    TH1F *Run375259_pEM_COMvsCent[11] = {0};

        Run375259_pEM_COMvsCent[0] = new TH1F("","Run 375259 pEM COM 0 to <10% Centrality", 100, -1, 4);
        Run375259_pEM_COMvsCent[1] = new TH1F("","Run 375259 pEM COM 10 to <20% Centrality", 100, -1, 4);
        Run375259_pEM_COMvsCent[2] = new TH1F("","Run 375259 pEM COM 20 to <30% Centrality", 100, -1, 4);
        Run375259_pEM_COMvsCent[3] = new TH1F("","Run 375259 pEM COM 30 to <40% Centrality", 100, -1, 4);
        Run375259_pEM_COMvsCent[4] = new TH1F("","Run 375259 pEM COM 40 to <50% Centrality", 100, -1, 4);
        Run375259_pEM_COMvsCent[5] = new TH1F("","Run 375259 pEM COM 50 to <60% Centrality", 100, -1, 4);
        Run375259_pEM_COMvsCent[6] = new TH1F("","Run 375259 pEM COM 60 to <70% Centrality", 100, -1, 4);
        Run375259_pEM_COMvsCent[7] = new TH1F("","Run 375259 pEM COM 70 to <80% Centrality", 100, -1, 4);
        Run375259_pEM_COMvsCent[8] = new TH1F("","Run 375259 pEM COM 80 to <90% Centrality", 100, -1, 4);
        Run375259_pEM_COMvsCent[9] = new TH1F("","Run 375259 pEM COM 90 to <100% Centrality", 100, -1, 4);
        Run375259_pEM_COMvsCent[10] = new TH1F("","Run 375259 pEM COM All Centrality", 100, -1, 4);

    TProfile *Run375259_pEM_Profile[11] = {0};

        Run375259_pEM_Profile[0] = new TProfile("","Run 375259 pEM Average X Signal 0 to 10 Centrality",5,0,5);
        Run375259_pEM_Profile[1] = new TProfile("","Run 375259 pEM Average X Signal 10 to 20 Centrality",5,0,5);
        Run375259_pEM_Profile[2] = new TProfile("","Run 375259 pEM Average X Signal 20 to 30 Centrality",5,0,5);
        Run375259_pEM_Profile[3] = new TProfile("","Run 375259 pEM Average X Signal 30 to 40 Centrality",5,0,5);
        Run375259_pEM_Profile[4] = new TProfile("","Run 375259 pEM Average X Signal 40 to 50 Centrality",5,0,5);
        Run375259_pEM_Profile[5] = new TProfile("","Run 375259 pEM Average X Signal 50 to 60 Centrality",5,0,5);
        Run375259_pEM_Profile[6] = new TProfile("","Run 375259 pEM Average X Signal 60 to 70 Centrality",5,0,5);
        Run375259_pEM_Profile[7] = new TProfile("","Run 375259 pEM Average X Signal 70 to 80 Centrality",5,0,5);
        Run375259_pEM_Profile[8] = new TProfile("","Run 375259 pEM Average X Signal 80 to 90 Centrality",5,0,5);
        Run375259_pEM_Profile[9] = new TProfile("","Run 375259 pEM Average X Signal 90 to 100 Centrality",5,0,5);
        Run375259_pEM_Profile[10] = new TProfile("","Run 375259 pEM Average X Signal All Centrality",5,0,5);

    THStack *pEM_stack = new THStack("","Run 375259 pEM X Distribution with Centrality");

    TH2F *Run375259_pRPDx_vs_pEMx[11] = {0};
        
        Run375259_pRPDx_vs_pEMx[0] = new TH2F("","Run 375259 pEM X Position vs pRPD X Position 0 to <10% Centrality",200,-4,4,200,-4,4);
        Run375259_pRPDx_vs_pEMx[1] = new TH2F("","Run 375259 pEM X Position vs pRPD X Position 10 to <20% Centrality",200,-4,4,200,-4,4);
        Run375259_pRPDx_vs_pEMx[2] = new TH2F("","Run 375259 pEM X Position vs pRPD X Position 20 to <30% Centrality",200,-4,4,200,-4,4);
        Run375259_pRPDx_vs_pEMx[3] = new TH2F("","Run 375259 pEM X Position vs pRPD X Position 30 to <40% Centrality",200,-4,4,200,-4,4);
        Run375259_pRPDx_vs_pEMx[4] = new TH2F("","Run 375259 pEM X Position vs pRPD X Position 40 to <50% Centrality",200,-4,4,200,-4,4);
        Run375259_pRPDx_vs_pEMx[5] = new TH2F("","Run 375259 pEM X Position vs pRPD X Position 50 to <60% Centrality",200,-4,4,200,-4,4);
        Run375259_pRPDx_vs_pEMx[6] = new TH2F("","Run 375259 pEM X Position vs pRPD X Position 60 to <70% Centrality",200,-4,4,200,-4,4);
        Run375259_pRPDx_vs_pEMx[7] = new TH2F("","Run 375259 pEM X Position vs pRPD X Position 70 to <80% Centrality",200,-4,4,200,-4,4);
        Run375259_pRPDx_vs_pEMx[8] = new TH2F("","Run 375259 pEM X Position vs pRPD X Position 80 to <90% Centrality",200,-4,4,200,-4,4);
        Run375259_pRPDx_vs_pEMx[9] = new TH2F("","Run 375259 pEM X Position vs pRPD X Position 90 to <100% Centrality",200,-4,4,200,-4,4);
        Run375259_pRPDx_vs_pEMx[10] = new TH2F("","Run 375259 pEM X Position vs pRPD X Position All Centrality",200,-4,4,200,-4,4);

    TH1F *Run375259_pHAD_TS[4][11] = {0};

        Run375259_pHAD_TS[0][0] = new TH1F("","Run 375259 pHAD Section 1 TS Distribution 0 - <10% Cent",6,0,6);
        Run375259_pHAD_TS[1][0] = new TH1F("","Run 375259 pHAD Section 2 TS Distribution 0 - <10% Cent",6,0,6);
        Run375259_pHAD_TS[2][0] = new TH1F("","Run 375259 pHAD Section 3 TS Distribution 0 - <10% Cent",6,0,6);
        Run375259_pHAD_TS[3][0] = new TH1F("","Run 375259 pHAD Section 4 TS Distribution 0 - <10% Cent",6,0,6);

        Run375259_pHAD_TS[0][1] = new TH1F("","Run 375259 pHAD Section 1 TS Distribution 10 - <20% Cent",6,0,6);
        Run375259_pHAD_TS[1][1] = new TH1F("","Run 375259 pHAD Section 2 TS Distribution 10 - <20% Cent",6,0,6);
        Run375259_pHAD_TS[2][1] = new TH1F("","Run 375259 pHAD Section 3 TS Distribution 10 - <20% Cent",6,0,6);
        Run375259_pHAD_TS[3][1] = new TH1F("","Run 375259 pHAD Section 4 TS Distribution 10 - <20% Cent",6,0,6);

        Run375259_pHAD_TS[0][2] = new TH1F("","Run 375259 pHAD Section 1 TS Distribution 20 - <30% Cent",6,0,6);
        Run375259_pHAD_TS[1][2] = new TH1F("","Run 375259 pHAD Section 2 TS Distribution 20 - <30% Cent",6,0,6);
        Run375259_pHAD_TS[2][2] = new TH1F("","Run 375259 pHAD Section 3 TS Distribution 20 - <30% Cent",6,0,6);
        Run375259_pHAD_TS[3][2] = new TH1F("","Run 375259 pHAD Section 4 TS Distribution 20 - <30% Cent",6,0,6);

        Run375259_pHAD_TS[0][3] = new TH1F("","Run 375259 pHAD Section 1 TS Distribution 30 - <40% Cent",6,0,6);
        Run375259_pHAD_TS[1][3] = new TH1F("","Run 375259 pHAD Section 2 TS Distribution 30 - <40% Cent",6,0,6);
        Run375259_pHAD_TS[2][3] = new TH1F("","Run 375259 pHAD Section 3 TS Distribution 30 - <40% Cent",6,0,6);
        Run375259_pHAD_TS[3][3] = new TH1F("","Run 375259 pHAD Section 4 TS Distribution 30 - <40% Cent",6,0,6);

        Run375259_pHAD_TS[0][4] = new TH1F("","Run 375259 pHAD Section 1 TS Distribution 40 - <50% Cent",6,0,6);
        Run375259_pHAD_TS[1][4] = new TH1F("","Run 375259 pHAD Section 2 TS Distribution 40 - <50% Cent",6,0,6);
        Run375259_pHAD_TS[2][4] = new TH1F("","Run 375259 pHAD Section 3 TS Distribution 40 - <50% Cent",6,0,6);
        Run375259_pHAD_TS[3][4] = new TH1F("","Run 375259 pHAD Section 4 TS Distribution 40 - <50% Cent",6,0,6);

        Run375259_pHAD_TS[0][5] = new TH1F("","Run 375259 pHAD Section 1 TS Distribution 50 - <60% Cent",6,0,6);
        Run375259_pHAD_TS[1][5] = new TH1F("","Run 375259 pHAD Section 2 TS Distribution 50 - <60% Cent",6,0,6);
        Run375259_pHAD_TS[2][5] = new TH1F("","Run 375259 pHAD Section 3 TS Distribution 50 - <60% Cent",6,0,6);
        Run375259_pHAD_TS[3][5] = new TH1F("","Run 375259 pHAD Section 4 TS Distribution 50 - <60% Cent",6,0,6);
        
        Run375259_pHAD_TS[0][6] = new TH1F("","Run 375259 pHAD Section 1 TS Distribution 60 - <70% Cent",6,0,6);
        Run375259_pHAD_TS[1][6] = new TH1F("","Run 375259 pHAD Section 2 TS Distribution 60 - <70% Cent",6,0,6);
        Run375259_pHAD_TS[2][6] = new TH1F("","Run 375259 pHAD Section 3 TS Distribution 60 - <70% Cent",6,0,6);
        Run375259_pHAD_TS[3][6] = new TH1F("","Run 375259 pHAD Section 4 TS Distribution 60 - <70% Cent",6,0,6);

        Run375259_pHAD_TS[0][7] = new TH1F("","Run 375259 pHAD Section 1 TS Distribution 70 - <80% Cent",6,0,6);
        Run375259_pHAD_TS[1][7] = new TH1F("","Run 375259 pHAD Section 2 TS Distribution 70 - <80% Cent",6,0,6);
        Run375259_pHAD_TS[2][7] = new TH1F("","Run 375259 pHAD Section 3 TS Distribution 70 - <80% Cent",6,0,6);
        Run375259_pHAD_TS[3][7] = new TH1F("","Run 375259 pHAD Section 4 TS Distribution 70 - <80% Cent",6,0,6);

        Run375259_pHAD_TS[0][8] = new TH1F("","Run 375259 pHAD Section 1 TS Distribution 80 - <90% Cent",6,0,6);
        Run375259_pHAD_TS[1][8] = new TH1F("","Run 375259 pHAD Section 2 TS Distribution 80 - <90% Cent",6,0,6);
        Run375259_pHAD_TS[2][8] = new TH1F("","Run 375259 pHAD Section 3 TS Distribution 80 - <90% Cent",6,0,6);
        Run375259_pHAD_TS[3][8] = new TH1F("","Run 375259 pHAD Section 4 TS Distribution 80 - <90% Cent",6,0,6);

        Run375259_pHAD_TS[0][9] = new TH1F("","Run 375259 pHAD Section 1 TS Distribution 90 - <100% Cent",6,0,6);
        Run375259_pHAD_TS[1][9] = new TH1F("","Run 375259 pHAD Section 2 TS Distribution 90 - <100% Cent",6,0,6);
        Run375259_pHAD_TS[2][9] = new TH1F("","Run 375259 pHAD Section 3 TS Distribution 90 - <100% Cent",6,0,6);
        Run375259_pHAD_TS[3][9] = new TH1F("","Run 375259 pHAD Section 4 TS Distribution 90 - <100% Cent",6,0,6);

        Run375259_pHAD_TS[0][10] = new TH1F("","Run 375259 pHAD Section 1 TS Distribution All Cent",6,0,6);
        Run375259_pHAD_TS[1][10] = new TH1F("","Run 375259 pHAD Section 2 TS Distribution All Cent",6,0,6);
        Run375259_pHAD_TS[2][10] = new TH1F("","Run 375259 pHAD Section 3 TS Distribution All Cent",6,0,6);
        Run375259_pHAD_TS[3][10] = new TH1F("","Run 375259 pHAD Section 4 TS Distribution All Cent",6,0,6);

    TH1F* pHAD_TSratio[4][11] = {0};

        pHAD_TSratio[0][0] = new TH1F("","Run 375259 TS2 : TS3 pHAD 1, 0 - 10% Centrality",100,0,10);
        pHAD_TSratio[1][0] = new TH1F("","Run 375259 TS2 : TS3 pHAD 2, 0 - 10% Centrality",100,0,10);
        pHAD_TSratio[2][0] = new TH1F("","Run 375259 TS2 : TS3 pHAD 3, 0 - 10% Centrality",100,0,10);
        pHAD_TSratio[3][0] = new TH1F("","Run 375259 TS2 : TS3 pHAD 4, 0 - 10% Centrality",100,0,10);

        pHAD_TSratio[0][1] = new TH1F("","Run 375259 TS2 : TS3 pHAD 1, 10 - 20% Centrality",100,0,10);
        pHAD_TSratio[1][1] = new TH1F("","Run 375259 TS2 : TS3 pHAD 2, 10 - 20% Centrality",100,0,10);
        pHAD_TSratio[2][1] = new TH1F("","Run 375259 TS2 : TS3 pHAD 3, 10 - 20% Centrality",100,0,10);
        pHAD_TSratio[3][1] = new TH1F("","Run 375259 TS2 : TS3 pHAD 4, 10 - 20% Centrality",100,0,10);

        pHAD_TSratio[0][2] = new TH1F("","Run 375259 TS2 : TS3 pHAD 1, 20 - 30% Centrality",100,0,10);
        pHAD_TSratio[1][2] = new TH1F("","Run 375259 TS2 : TS3 pHAD 2, 20 - 30% Centrality",100,0,10);
        pHAD_TSratio[2][2] = new TH1F("","Run 375259 TS2 : TS3 pHAD 3, 20 - 30% Centrality",100,0,10);
        pHAD_TSratio[3][2] = new TH1F("","Run 375259 TS2 : TS3 pHAD 4, 20 - 30% Centrality",100,0,10);

        pHAD_TSratio[0][3] = new TH1F("","Run 375259 TS2 : TS3 pHAD 1, 30 - 40% Centrality",100,0,10);
        pHAD_TSratio[1][3] = new TH1F("","Run 375259 TS2 : TS3 pHAD 2, 30 - 40% Centrality",100,0,10);
        pHAD_TSratio[2][3] = new TH1F("","Run 375259 TS2 : TS3 pHAD 3, 30 - 40% Centrality",100,0,10);
        pHAD_TSratio[3][3] = new TH1F("","Run 375259 TS2 : TS3 pHAD 4, 30 - 40% Centrality",100,0,10);

        pHAD_TSratio[0][4] = new TH1F("","Run 375259 TS2 : TS3 pHAD 1, 40 - 50% Centrality",100,0,10);
        pHAD_TSratio[1][4] = new TH1F("","Run 375259 TS2 : TS3 pHAD 2, 40 - 50% Centrality",100,0,10);
        pHAD_TSratio[2][4] = new TH1F("","Run 375259 TS2 : TS3 pHAD 3, 40 - 50% Centrality",100,0,10);
        pHAD_TSratio[3][4] = new TH1F("","Run 375259 TS2 : TS3 pHAD 4, 40 - 50% Centrality",100,0,10);

        pHAD_TSratio[0][5] = new TH1F("","Run 375259 TS2 : TS3 pHAD 1, 50 - 60% Centrality",100,0,10);
        pHAD_TSratio[1][5] = new TH1F("","Run 375259 TS2 : TS3 pHAD 2, 50 - 60% Centrality",100,0,10);
        pHAD_TSratio[2][5] = new TH1F("","Run 375259 TS2 : TS3 pHAD 3, 50 - 60% Centrality",100,0,10);
        pHAD_TSratio[3][5] = new TH1F("","Run 375259 TS2 : TS3 pHAD 4, 50 - 60% Centrality",100,0,10);

        pHAD_TSratio[0][6] = new TH1F("","Run 375259 TS2 : TS3 pHAD 1, 60 - 70% Centrality",100,0,10);
        pHAD_TSratio[1][6] = new TH1F("","Run 375259 TS2 : TS3 pHAD 2, 60 - 70% Centrality",100,0,10);
        pHAD_TSratio[2][6] = new TH1F("","Run 375259 TS2 : TS3 pHAD 3, 60 - 70% Centrality",100,0,10);
        pHAD_TSratio[3][6] = new TH1F("","Run 375259 TS2 : TS3 pHAD 4, 60 - 70% Centrality",100,0,10);

        pHAD_TSratio[0][7] = new TH1F("","Run 375259 TS2 : TS3 pHAD 1, 70 - 80% Centrality",100,0,10);
        pHAD_TSratio[1][7] = new TH1F("","Run 375259 TS2 : TS3 pHAD 2, 70 - 80% Centrality",100,0,10);
        pHAD_TSratio[2][7] = new TH1F("","Run 375259 TS2 : TS3 pHAD 3, 70 - 80% Centrality",100,0,10);
        pHAD_TSratio[3][7] = new TH1F("","Run 375259 TS2 : TS3 pHAD 4, 70 - 80% Centrality",100,0,10);

        pHAD_TSratio[0][8] = new TH1F("","Run 375259 TS2 : TS3 pHAD 1, 80 - 90% Centrality",100,0,10);
        pHAD_TSratio[1][8] = new TH1F("","Run 375259 TS2 : TS3 pHAD 2, 80 - 90% Centrality",100,0,10);
        pHAD_TSratio[2][8] = new TH1F("","Run 375259 TS2 : TS3 pHAD 3, 80 - 90% Centrality",100,0,10);
        pHAD_TSratio[3][8] = new TH1F("","Run 375259 TS2 : TS3 pHAD 4, 80 - 90% Centrality",100,0,10);

        pHAD_TSratio[0][9] = new TH1F("","Run 375259 TS2 : TS3 pHAD 1, 90 - 100% Centrality",100,0,10);
        pHAD_TSratio[1][9] = new TH1F("","Run 375259 TS2 : TS3 pHAD 2, 90 - 100% Centrality",100,0,10);
        pHAD_TSratio[2][9] = new TH1F("","Run 375259 TS2 : TS3 pHAD 3, 90 - 100% Centrality",100,0,10);
        pHAD_TSratio[3][9] = new TH1F("","Run 375259 TS2 : TS3 pHAD 4, 90 - 100% Centrality",100,0,10);

        pHAD_TSratio[0][10] = new TH1F("","Run 375259 TS2 : TS3 pHAD 1, All Centrality",100,0,10);
        pHAD_TSratio[1][10] = new TH1F("","Run 375259 TS2 : TS3 pHAD 2, All Centrality",100,0,10);
        pHAD_TSratio[2][10] = new TH1F("","Run 375259 TS2 : TS3 pHAD 3, All Centrality",100,0,10);
        pHAD_TSratio[3][10] = new TH1F("","Run 375259 TS2 : TS3 pHAD 4, All Centrality",100,0,10);


    TH1F *Run375259_pHAD_fC[4][11] = {0};

        Run375259_pHAD_fC[0][0] = new TH1F("","Run 375259 pHAD Section 1 fC, 0 - <10% Cent",200,0,200000);
        Run375259_pHAD_fC[1][0] = new TH1F("","Run 375259 pHAD Section 2 fC, 0 - <10% Cent",200,0,200000);
        Run375259_pHAD_fC[2][0] = new TH1F("","Run 375259 pHAD Section 3 fC, 0 - <10% Cent",200,0,200000);
        Run375259_pHAD_fC[3][0] = new TH1F("","Run 375259 pHAD Section 4 fC, 0 - <10% Cent",200,0,200000);

        Run375259_pHAD_fC[0][1] = new TH1F("","Run 375259 pHAD Section 1 fC, 10 - <20% Cent",200,0,200000);
        Run375259_pHAD_fC[1][1] = new TH1F("","Run 375259 pHAD Section 2 fC, 10 - <20% Cent",200,0,200000);
        Run375259_pHAD_fC[2][1] = new TH1F("","Run 375259 pHAD Section 3 fC, 10 - <20% Cent",200,0,200000);
        Run375259_pHAD_fC[3][1] = new TH1F("","Run 375259 pHAD Section 4 fC, 10 - <20% Cent",200,0,200000);

        Run375259_pHAD_fC[0][2] = new TH1F("","Run 375259 pHAD Section 1 fC, 20 - <30% Cent",200,0,200000);
        Run375259_pHAD_fC[1][2] = new TH1F("","Run 375259 pHAD Section 2 fC, 20 - <30% Cent",200,0,200000);
        Run375259_pHAD_fC[2][2] = new TH1F("","Run 375259 pHAD Section 3 fC, 20 - <30% Cent",200,0,200000);
        Run375259_pHAD_fC[3][2] = new TH1F("","Run 375259 pHAD Section 4 fC, 20 - <30% Cent",200,0,200000);

        Run375259_pHAD_fC[0][3] = new TH1F("","Run 375259 pHAD Section 1 fC, 30 - <40% Cent",200,0,200000);
        Run375259_pHAD_fC[1][3] = new TH1F("","Run 375259 pHAD Section 2 fC, 30 - <40% Cent",200,0,200000);
        Run375259_pHAD_fC[2][3] = new TH1F("","Run 375259 pHAD Section 3 fC, 30 - <40% Cent",200,0,200000);
        Run375259_pHAD_fC[3][3] = new TH1F("","Run 375259 pHAD Section 4 fC, 30 - <40% Cent",200,0,200000);

        Run375259_pHAD_fC[0][4] = new TH1F("","Run 375259 pHAD Section 1 fC, 40 - <50% Cent",200,0,200000);
        Run375259_pHAD_fC[1][4] = new TH1F("","Run 375259 pHAD Section 2 fC, 40 - <50% Cent",200,0,200000);
        Run375259_pHAD_fC[2][4] = new TH1F("","Run 375259 pHAD Section 3 fC, 40 - <50% Cent",200,0,200000);
        Run375259_pHAD_fC[3][4] = new TH1F("","Run 375259 pHAD Section 4 fC, 40 - <50% Cent",200,0,200000);

        Run375259_pHAD_fC[0][5] = new TH1F("","Run 375259 pHAD Section 1 fC, 50 - <60% Cent",200,0,200000);
        Run375259_pHAD_fC[1][5] = new TH1F("","Run 375259 pHAD Section 2 fC, 50 - <60% Cent",200,0,200000);
        Run375259_pHAD_fC[2][5] = new TH1F("","Run 375259 pHAD Section 3 fC, 50 - <60% Cent",200,0,200000);
        Run375259_pHAD_fC[3][5] = new TH1F("","Run 375259 pHAD Section 4 fC, 50 - <60% Cent",200,0,200000);

        Run375259_pHAD_fC[0][6] = new TH1F("","Run 375259 pHAD Section 1 fC, 60 - <70% Cent",200,0,200000);
        Run375259_pHAD_fC[1][6] = new TH1F("","Run 375259 pHAD Section 2 fC, 60 - <70% Cent",200,0,200000);
        Run375259_pHAD_fC[2][6] = new TH1F("","Run 375259 pHAD Section 3 fC, 60 - <70% Cent",200,0,200000);
        Run375259_pHAD_fC[3][6] = new TH1F("","Run 375259 pHAD Section 4 fC, 60 - <70% Cent",200,0,200000);

        Run375259_pHAD_fC[0][7] = new TH1F("","Run 375259 pHAD Section 1 fC, 70 - <80% Cent",200,0,200000);
        Run375259_pHAD_fC[1][7] = new TH1F("","Run 375259 pHAD Section 2 fC, 70 - <80% Cent",200,0,200000);
        Run375259_pHAD_fC[2][7] = new TH1F("","Run 375259 pHAD Section 3 fC, 70 - <80% Cent",200,0,200000);
        Run375259_pHAD_fC[3][7] = new TH1F("","Run 375259 pHAD Section 4 fC, 70 - <80% Cent",200,0,200000);

        Run375259_pHAD_fC[0][8] = new TH1F("","Run 375259 pHAD Section 1 fC, 80 - <90% Cent",200,0,200000);
        Run375259_pHAD_fC[1][8] = new TH1F("","Run 375259 pHAD Section 2 fC, 80 - <90% Cent",200,0,200000);
        Run375259_pHAD_fC[2][8] = new TH1F("","Run 375259 pHAD Section 3 fC, 80 - <90% Cent",200,0,200000);
        Run375259_pHAD_fC[3][8] = new TH1F("","Run 375259 pHAD Section 4 fC, 80 - <90% Cent",200,0,200000);

        Run375259_pHAD_fC[0][9] = new TH1F("","Run 375259 pHAD Section 1 fC, 90 - <100% Cent",200,0,200000);
        Run375259_pHAD_fC[1][9] = new TH1F("","Run 375259 pHAD Section 2 fC, 90 - <100% Cent",200,0,200000);
        Run375259_pHAD_fC[2][9] = new TH1F("","Run 375259 pHAD Section 3 fC, 90 - <100% Cent",200,0,200000);
        Run375259_pHAD_fC[3][9] = new TH1F("","Run 375259 pHAD Section 4 fC, 90 - <100% Cent",200,0,200000);

        Run375259_pHAD_fC[0][10] = new TH1F("","Run 375259 pHAD Section 1 fC, All Cent",200,0,200000);
        Run375259_pHAD_fC[1][10] = new TH1F("","Run 375259 pHAD Section 2 fC, All Cent",200,0,200000);
        Run375259_pHAD_fC[2][10] = new TH1F("","Run 375259 pHAD Section 3 fC, All Cent",200,0,200000);
        Run375259_pHAD_fC[3][10] = new TH1F("","Run 375259 pHAD Section 4 fC, All Cent",200,0,200000);

    TProfile *Run375259_pRPD_Avg_Y_Sig[11] = {0};

        Run375259_pRPD_Avg_Y_Sig[0] = new TProfile("","Run 375259 Average Y Signal 0 - <10% Centrality",4,0,4);
        Run375259_pRPD_Avg_Y_Sig[1] = new TProfile("","Run 375259 Average Y Signal 10 - <20% Centrality",4,0,4);
        Run375259_pRPD_Avg_Y_Sig[2] = new TProfile("","Run 375259 Average Y Signal 20 - <30% Centrality",4,0,4);
        Run375259_pRPD_Avg_Y_Sig[3] = new TProfile("","Run 375259 Average Y Signal 30 - <40% Centrality",4,0,4);
        Run375259_pRPD_Avg_Y_Sig[4] = new TProfile("","Run 375259 Average Y Signal 40 - <50% Centrality",4,0,4);
        Run375259_pRPD_Avg_Y_Sig[5] = new TProfile("","Run 375259 Average Y Signal 50 - <60% Centrality",4,0,4);
        Run375259_pRPD_Avg_Y_Sig[6] = new TProfile("","Run 375259 Average Y Signal 60 - <70% Centrality",4,0,4);
        Run375259_pRPD_Avg_Y_Sig[7] = new TProfile("","Run 375259 Average Y Signal 70 - <80% Centrality",4,0,4);
        Run375259_pRPD_Avg_Y_Sig[8] = new TProfile("","Run 375259 Average Y Signal 80 - <90% Centrality",4,0,4);
        Run375259_pRPD_Avg_Y_Sig[9] = new TProfile("","Run 375259 Average Y Signal 90 - <100% Centrality",4,0,4);
        Run375259_pRPD_Avg_Y_Sig[10] = new TProfile("","Run 375259 Average Y Signal All Centrality",4,0,4);

    TH2 *Run375259_pRPD_HeatMap[11] = {0};

        Run375259_pRPD_HeatMap[0] = new TH2F("","Run 375259 pRPD Heat Map 0 - <10% Centrality",4,0,4,4,0,4);
        Run375259_pRPD_HeatMap[1] = new TH2F("","Run 375259 pRPD Heat Map 10 - <20% Centrality",4,0,4,4,0,4);
        Run375259_pRPD_HeatMap[2] = new TH2F("","Run 375259 pRPD Heat Map 20 - <30% Centrality",4,0,4,4,0,4);
        Run375259_pRPD_HeatMap[3] = new TH2F("","Run 375259 pRPD Heat Map 30 - <40% Centrality",4,0,4,4,0,4);
        Run375259_pRPD_HeatMap[4] = new TH2F("","Run 375259 pRPD Heat Map 40 - <50% Centrality",4,0,4,4,0,4);
        Run375259_pRPD_HeatMap[5] = new TH2F("","Run 375259 pRPD Heat Map 50 - <60% Centrality",4,0,4,4,0,4);
        Run375259_pRPD_HeatMap[6] = new TH2F("","Run 375259 pRPD Heat Map 60 - <70% Centrality",4,0,4,4,0,4);
        Run375259_pRPD_HeatMap[7] = new TH2F("","Run 375259 pRPD Heat Map 70 - <80% Centrality",4,0,4,4,0,4);
        Run375259_pRPD_HeatMap[8] = new TH2F("","Run 375259 pRPD Heat Map 80 - <90% Centrality",4,0,4,4,0,4);
        Run375259_pRPD_HeatMap[9] = new TH2F("","Run 375259 pRPD Heat Map 90 - <100% Centrality",4,0,4,4,0,4);
        Run375259_pRPD_HeatMap[10] = new TH2F("","Run 375259 pRPD Heat Map All Centrality",4,0,4,4,0,4);

    TH2F *Run375259_pRPD_position_vstotalsignal[11] = {0};

        Run375259_pRPD_position_vstotalsignal[0] = new TH2F("","Run 375259 pRPD Position vs Total Signal 0 - <10% Centrality",200,0,100000,100,-3,3);
        Run375259_pRPD_position_vstotalsignal[1] = new TH2F("","Run 375259 pRPD Position vs Total Signal 10 - <20% Centrality",200,0,100000,100,-3,3);
        Run375259_pRPD_position_vstotalsignal[2] = new TH2F("","Run 375259 pRPD Position vs Total Signal 20 - <30% Centrality",200,0,100000,100,-3,3);
        Run375259_pRPD_position_vstotalsignal[3] = new TH2F("","Run 375259 pRPD Position vs Total Signal 30 - <40% Centrality",200,0,100000,100,-3,3);
        Run375259_pRPD_position_vstotalsignal[4] = new TH2F("","Run 375259 pRPD Position vs Total Signal 40 - <50% Centrality",200,0,100000,100,-3,3);
        Run375259_pRPD_position_vstotalsignal[5] = new TH2F("","Run 375259 pRPD Position vs Total Signal 50 - <60% Centrality",200,0,100000,100,-3,3);
        Run375259_pRPD_position_vstotalsignal[6] = new TH2F("","Run 375259 pRPD Position vs Total Signal 60 - <70% Centrality",200,0,100000,100,-3,3);
        Run375259_pRPD_position_vstotalsignal[7] = new TH2F("","Run 375259 pRPD Position vs Total Signal 70 - <80% Centrality",200,0,100000,100,-3,3);
        Run375259_pRPD_position_vstotalsignal[8] = new TH2F("","Run 375259 pRPD Position vs Total Signal 80 - <90% Centrality",200,0,20000,100,-3,3);
        Run375259_pRPD_position_vstotalsignal[9] = new TH2F("","Run 375259 pRPD Position vs Total Signal 90 - <100% Centrality",200,0,20000,100,-3,3);
        Run375259_pRPD_position_vstotalsignal[10] = new TH2F("","Run 375259 pRPD Position vs Total Signal All Centrality",200,0,400000,100,-3,3);

    TH2F *Run375259_pEM_position_vstotalsignal[11] = {0};

        Run375259_pEM_position_vstotalsignal[0] = new TH2F("","Run 375259 pEM Position vs Total Signal 0 - <10% Centrality",200,0,100000,100,-5,5);
        Run375259_pEM_position_vstotalsignal[1] = new TH2F("","Run 375259 pEM Position vs Total Signal 10 - <20% Centrality",200,0,100000,100,-5,5);
        Run375259_pEM_position_vstotalsignal[2] = new TH2F("","Run 375259 pEM Position vs Total Signal 20 - <30% Centrality",200,0,100000,100,-5,5);
        Run375259_pEM_position_vstotalsignal[3] = new TH2F("","Run 375259 pEM Position vs Total Signal 30 - <40% Centrality",200,0,100000,100,-5,5);
        Run375259_pEM_position_vstotalsignal[4] = new TH2F("","Run 375259 pEM Position vs Total Signal 40 - <50% Centrality",200,0,100000,100,-5,5);
        Run375259_pEM_position_vstotalsignal[5] = new TH2F("","Run 375259 pEM Position vs Total Signal 50 - <60% Centrality",200,0,100000,100,-5,5);
        Run375259_pEM_position_vstotalsignal[6] = new TH2F("","Run 375259 pEM Position vs Total Signal 60 - <70% Centrality",200,0,100000,100,-5,5);
        Run375259_pEM_position_vstotalsignal[7] = new TH2F("","Run 375259 pEM Position vs Total Signal 70 - <80% Centrality",200,0,100000,100,-5,5);
        Run375259_pEM_position_vstotalsignal[8] = new TH2F("","Run 375259 pEM Position vs Total Signal 80 - <90% Centrality",200,0,100000,100,-5,5);
        Run375259_pEM_position_vstotalsignal[9] = new TH2F("","Run 375259 pEM Position vs Total Signal 90 - <100% Centrality",200,0,100000,100,-5,5);
        Run375259_pEM_position_vstotalsignal[10] = new TH2F("","Run 375259 pEM Position vs Total Signal All Centrality",200,0,100000,100,-5,5);

    TH1F *hibindist = new TH1F("","Run 375259 hiBin distribution",200,0,200);

    TH2F *Run375259_NeutronPlot[11] = {0};

        Run375259_NeutronPlot[0] = new TH2F("","Run 375259 Neutron Plot 0 - <10% Centrality",200,0,100000,200,0,100000);
        Run375259_NeutronPlot[1] = new TH2F("","Run 375259 Neutron Plot 10 - <20% Centrality",200,0,100000,200,0,100000);
        Run375259_NeutronPlot[2] = new TH2F("","Run 375259 Neutron Plot 20 - <30% Centrality",200,0,100000,200,0,100000);
        Run375259_NeutronPlot[3] = new TH2F("","Run 375259 Neutron Plot 30 - <40% Centrality",200,0,100000,200,0,100000);
        Run375259_NeutronPlot[4] = new TH2F("","Run 375259 Neutron Plot 40 - <50% Centrality",200,0,100000,200,0,100000);
        Run375259_NeutronPlot[5] = new TH2F("","Run 375259 Neutron Plot 50 - <60% Centrality",200,0,100000,200,0,100000);
        Run375259_NeutronPlot[6] = new TH2F("","Run 375259 Neutron Plot 60 - <70% Centrality",200,0,100000,200,0,100000);
        Run375259_NeutronPlot[7] = new TH2F("","Run 375259 Neutron Plot 70 - <80% Centrality",200,0,100000,200,0,100000);
        Run375259_NeutronPlot[8] = new TH2F("","Run 375259 Neutron Plot 80 - <90% Centrality",200,0,100000,200,0,100000);
        Run375259_NeutronPlot[9] = new TH2F("","Run 375259 Neutron Plot 90 - <100% Centrality",200,0,100000,200,0,100000);
        Run375259_NeutronPlot[10] = new TH2F("","Run 375259 Neutron Plot All Centrality",200,0,100000,200,0,100000);

    TH1F *Run375259_NeutronPlotProjection[11] = {0};

        Run375259_NeutronPlotProjection[0] = new TH1F("","Run 375259 Total Energy Distribution 0 - <10% Centrality",200,0,100000);
        Run375259_NeutronPlotProjection[1] = new TH1F("","Run 375259 Total Energy Distribution 10 - <20% Centrality",200,0,100000);
        Run375259_NeutronPlotProjection[2] = new TH1F("","Run 375259 Total Energy Distribution 20 - <30% Centrality",200,0,100000);
        Run375259_NeutronPlotProjection[3] = new TH1F("","Run 375259 Total Energy Distribution 30 - <40% Centrality",200,0,100000);
        Run375259_NeutronPlotProjection[4] = new TH1F("","Run 375259 Total Energy Distribution 40 - <50% Centrality",200,0,100000);
        Run375259_NeutronPlotProjection[5] = new TH1F("","Run 375259 Total Energy Distribution 50 - <60% Centrality",200,0,100000);
        Run375259_NeutronPlotProjection[6] = new TH1F("","Run 375259 Total Energy Distribution 60 - <70% Centrality",200,0,100000);
        Run375259_NeutronPlotProjection[7] = new TH1F("","Run 375259 Total Energy Distribution 70 - <80% Centrality",200,0,100000);
        Run375259_NeutronPlotProjection[8] = new TH1F("","Run 375259 Total Energy Distribution 80 - <90% Centrality",200,0,100000);
        Run375259_NeutronPlotProjection[9] = new TH1F("","Run 375259 Total Energy Distribution 90 - <100% Centrality",200,0,100000);
        Run375259_NeutronPlotProjection[10] = new TH1F("","Run 375259 Total Energy Distribution All Centrality",200,0,100000);

    TH1F *pEM_JunkTS[5] = {0};

        pEM_JunkTS[0] = new TH1F("","Run 375259 pEM 90 - 100% Centrality Junk TS Distributions Section 1",6,0,6);
        pEM_JunkTS[1] = new TH1F("","Run 375259 pEM 90 - 100% Centrality Junk TS Distributions Section 2",6,0,6);
        pEM_JunkTS[2] = new TH1F("","Run 375259 pEM 90 - 100% Centrality Junk TS Distributions Section 3",6,0,6);
        pEM_JunkTS[3] = new TH1F("","Run 375259 pEM 90 - 100% Centrality Junk TS Distributions Section 4",6,0,6);
        pEM_JunkTS[4] = new TH1F("","Run 375259 pEM 90 - 100% Centrality Junk TS Distributions Section 5",6,0,6);

        TH1F *pEM_GoodTS[5] = {0};

        pEM_GoodTS[0] = new TH1F("","Run 375259 pEM 90 - 100% Centrality Good TS Distributions Section 1",6,0,6);
        pEM_GoodTS[1] = new TH1F("","Run 375259 pEM 90 - 100% Centrality Good TS Distributions Section 2",6,0,6);
        pEM_GoodTS[2] = new TH1F("","Run 375259 pEM 90 - 100% Centrality Good TS Distributions Section 3",6,0,6);
        pEM_GoodTS[3] = new TH1F("","Run 375259 pEM 90 - 100% Centrality Good TS Distributions Section 4",6,0,6);
        pEM_GoodTS[4] = new TH1F("","Run 375259 pEM 90 - 100% Centrality Good TS Distributions Section 5",6,0,6);

    TH1F *pHAD_JunkTS[4] = {0};

        pHAD_JunkTS[0] = new TH1F("","Run 375259 pHAD 90 - 100% Centrality Junk TS Distributions Section 1",6,0,6);
        pHAD_JunkTS[1] = new TH1F("","Run 375259 pHAD 90 - 100% Centrality Junk TS Distributions Section 2",6,0,6);
        pHAD_JunkTS[2] = new TH1F("","Run 375259 pHAD 90 - 100% Centrality Junk TS Distributions Section 3",6,0,6);
        pHAD_JunkTS[3] = new TH1F("","Run 375259 pHAD 90 - 100% Centrality Junk TS Distributions Section 4",6,0,6);

    TH1F *pHAD_GoodTS[4] = {0};

        pHAD_GoodTS[0] = new TH1F("","Run 375259 pHAD 90 - 100% Centrality Good TS Distributions Section 1",6,0,6);
        pHAD_GoodTS[1] = new TH1F("","Run 375259 pHAD 90 - 100% Centrality Good TS Distributions Section 2",6,0,6);
        pHAD_GoodTS[2] = new TH1F("","Run 375259 pHAD 90 - 100% Centrality Good TS Distributions Section 3",6,0,6);
        pHAD_GoodTS[3] = new TH1F("","Run 375259 pHAD 90 - 100% Centrality Good TS Distributions Section 4",6,0,6);

    int hibin = 0;
    int zside[56];
    int section[56];
    int channel[56];

    float pRPDX1[11];
    float pRPDX2[11];
    float pRPDX3[11];
    float pRPDX4[11];

    float pRPDY1[11];
    float pRPDY2[11];
    float pRPDY3[11];
    float pRPDY4[11];

    float pRPD_ratio[16][11] = {0};
    float pRPD_signal[16][11] = {0};

    float pRPD_signal_col[11];
    float pRPD_signal_row[11];
    float pRPD_total_signal_col[11][4];

    float pRPD_sum;
    float pRPD_signal_total[11];

    float pEM_ratio[5][11] = {0};
    float pEM_signal[5][11] = {0};

    float pHAD_sum;
    float pHAD_ratio[4][11] = {0};
    float pHAD_signal[4][11] = {0};
    float pHAD_signal_total[11] = {0};

    float pEM_sum;
    float pEM_signal_col[11];
    float pEM_signal_total[11];

    float ZDC[11];

    float TS0[56];
    float TS1[56];
    float TS2[56];
    float TS3[56];
    float TS4[56];
    float TS5[56];

    zdcchain->SetBranchAddress("hiBin",&hibin);
    zdcchain->SetBranchAddress("zside",&zside);
    zdcchain->SetBranchAddress("section",&section);
    zdcchain->SetBranchAddress("channel",&channel);
    zdcchain->SetBranchAddress("chargefCTs0",&TS0);
    zdcchain->SetBranchAddress("chargefCTs1",&TS1);
    zdcchain->SetBranchAddress("chargefCTs2",&TS2);
    zdcchain->SetBranchAddress("chargefCTs3",&TS3);
    zdcchain->SetBranchAddress("chargefCTs4",&TS4);
    zdcchain->SetBranchAddress("chargefCTs5",&TS5);

    // Event loop for all events in the run
    Int_t NumofEvents = zdcchain->GetEntries();
	    cout << "Total # of events = " << NumofEvents << endl;
        NumofEvents = 100000;
            for (int i = 0; i < NumofEvents; i++) {           
		        zdcchain->GetEntry(i);  
                hichain->GetEntry(i);
                if ( i % 100000 == 0){
                    cout << "Event Processed" << i << endl;}
                
                for (int n = 0; n < 56; n++) {
                        if (zside[n] == 1 && section[n] == 4) {
                        pRPD_sum += TS2[n] + TS3[n];
                        }
                }
                for (int n = 0; n < 56; n++) {
                        if (zside[n] == 1 && section[n] == 1) {
                            //cout << (TS2[n] + TS3[n]) << endl;
                        pEM_sum += TS2[n] + TS3[n];
                        }
                }
                 for (int n = 0; n < 56; n++) {
                        if (zside[n] == 1 && section[n] == 2) {
                            //cout << (TS2[n] + TS3[n]) << endl;
                        pHAD_sum += TS2[n] + TS3[n];
                        }
                }
                //if (pRPD_sum > 3200 && pEM_sum > 1000 && pHAD_sum > 1000){
                if (hibin >=0 && hibin < 20 ){ 
                            for (int n = 0; n < 56; n++) {
                                if (zside[n] == 1 && section[n] == 4) {
                                    if (channel[n] == 1) {
                                    Run375259_pRPD_TS[10][0]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[10][0]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[10][0]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[10][0]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[10][0]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[10][0]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[10][0] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[10][0]->Fill(pRPD_ratio[10][0]);

                                    //if (pRPD_ratio[10][0] > 1.5 && pRPD_ratio[10][0] < 2.0) {
                                    pRPD_signal[10][0] = TS2[n] + TS3[n];
                                    //}
                                    Run375259_pRPD_fC[10][0]->Fill(pRPD_signal[10][0]);
                                    
                                    }
                                    if (channel[n] == 2) {
                                    Run375259_pRPD_TS[6][0]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[6][0]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[6][0]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[6][0]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[6][0]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[6][0]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[6][0] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[6][0]->Fill(pRPD_ratio[6][0]);
                                    
                                    if (pRPD_ratio[6][0] > 1.5 && pRPD_ratio[6][0] < 2.1) {
                                    pRPD_signal[6][0] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[6][0]->Fill(pRPD_signal[6][0]);
                                    
                                    } 
                                    if (channel[n] == 3) {
                                    Run375259_pRPD_TS[2][0]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[2][0]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[2][0]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[2][0]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[2][0]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[2][0]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[2][0] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[2][0]->Fill(pRPD_ratio[2][0]);
                                    
                                    if (pRPD_ratio[2][0] > 1.5 && pRPD_ratio[2][0] < 2.0) {
                                    pRPD_signal[2][0] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[2][0]->Fill(pRPD_signal[2][0]);
                                    
                                    }      
                                    if (channel[n] == 4) {
                                    Run375259_pRPD_TS[14][0]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[14][0]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[14][0]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[14][0]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[14][0]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[14][0]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[14][0] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[14][0]->Fill(pRPD_ratio[14][0]);

                                    if (pRPD_ratio[14][0] > 1.5 && pRPD_ratio[14][0] < 2.0) {
                                    pRPD_signal[14][0] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[14][0]->Fill(pRPD_signal[14][0]);
                                    
                                    }   
                                    if (channel[n] == 5) {
                                    Run375259_pRPD_TS[11][0]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[11][0]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[11][0]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[11][0]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[11][0]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[11][0]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[11][0] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[11][0]->Fill(pRPD_ratio[11][0]);
                                    
                                    if (pRPD_ratio[11][0] > 1.5 && pRPD_ratio[11][0] < 2.1) {
                                    pRPD_signal[11][0] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[11][0]->Fill(pRPD_signal[11][0]);
                                    
                                    }   
                                    if (channel[n] == 6) {
                                    Run375259_pRPD_TS[7][0]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[7][0]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[7][0]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[7][0]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[7][0]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[7][0]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[7][0] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[7][0]->Fill(pRPD_ratio[7][0]);
                                    
                                    if (pRPD_ratio[7][0] > 1.6 && pRPD_ratio[7][0] < 2.4) {
                                    pRPD_signal[7][0] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[7][0]->Fill(pRPD_signal[7][0]);
                                    
                                    }   
                                    if (channel[n] == 7) {
                                    Run375259_pRPD_TS[3][0]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[3][0]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[3][0]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[3][0]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[3][0]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[3][0]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[3][0] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[3][0]->Fill(pRPD_ratio[3][0]);
                                    
                                    if (pRPD_ratio[3][0] > 1.5 && pRPD_ratio[3][0] < 2.4) {
                                    pRPD_signal[3][0] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[3][0]->Fill(pRPD_signal[3][0]);
                                    
                                    }   
                                    if (channel[n] == 8) {
                                    Run375259_pRPD_TS[15][0]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[15][0]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[15][0]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[15][0]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[15][0]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[15][0]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[15][0] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[15][0]->Fill(pRPD_ratio[15][0]);

                                    if (pRPD_ratio[15][0] > 1.6 && pRPD_ratio[15][0] < 2.2) {
                                    pRPD_signal[15][0] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[15][0]->Fill(pRPD_signal[15][0]);
                                    }   
                                    if (channel[n] == 9) {
                                    Run375259_pRPD_TS[4][0]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[4][0]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[4][0]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[4][0]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[4][0]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[4][0]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[4][0] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[4][0]->Fill(pRPD_ratio[4][0]);

                                    if (pRPD_ratio[4][0] > 1.5 && pRPD_ratio[4][0] < 2.4 ) {
                                    pRPD_signal[4][0] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[4][0]->Fill(pRPD_signal[4][0]);
                                    }   
                                    if (channel[n] == 10) {
                                    Run375259_pRPD_TS[8][0]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[8][0]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[8][0]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[8][0]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[8][0]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[8][0]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[8][0] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[8][0]->Fill(pRPD_ratio[8][0]);

                                    if (pRPD_ratio[8][0] > 1.5 && pRPD_ratio[8][0] < 2.3) {
                                    pRPD_signal[8][0] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[8][0]->Fill(pRPD_signal[8][0]);
                                    }   
                                    if (channel[n] == 11) {
                                    Run375259_pRPD_TS[12][0]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[12][0]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[12][0]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[12][0]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[12][0]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[12][0]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[12][0] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[12][0]->Fill(pRPD_ratio[12][0]);

                                    if (pRPD_ratio[12][0] > 1.5 && pRPD_ratio[12][0] < 2.2){
                                    pRPD_signal[12][0] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[12][0]->Fill(pRPD_signal[12][0]);
                                    }   
                                    if (channel[n] == 12) {
                                    Run375259_pRPD_TS[0][0]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[0][0]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[0][0]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[0][0]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[0][0]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[0][0]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[0][0] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[0][0]->Fill(pRPD_ratio[0][0]);

                                    if (pRPD_ratio[0][0] > 1.5 && pRPD_ratio[0][0] < 2.3){
                                    pRPD_signal[0][0] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[0][0]->Fill(pRPD_signal[0][0]);
                                    }   
                                    if (channel[n] == 13) {
                                    Run375259_pRPD_TS[5][0]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[5][0]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[5][0]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[5][0]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[5][0]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[5][0]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[5][0] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[5][0]->Fill(pRPD_ratio[5][0]);

                                    if (pRPD_ratio[5][0] > 1.7 && pRPD_ratio[5][0] < 2.5){
                                    pRPD_signal[5][0] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[5][0]->Fill(pRPD_signal[5][0]);
                                    }   
                                    if (channel[n] == 14) {
                                    Run375259_pRPD_TS[9][0]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[9][0]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[9][0]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[9][0]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[9][0]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[9][0]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[9][0] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[9][0]->Fill(pRPD_ratio[9][0]);
                                    
                                    if (pRPD_ratio[9][0] > 1.6 && pRPD_ratio[9][0] < 2.4) {
                                    pRPD_signal[9][0] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[9][0]->Fill(pRPD_signal[9][0]);
                                    }   
                                    if (channel[n] == 15) {
                                    Run375259_pRPD_TS[13][0]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[13][0]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[13][0]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[13][0]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[13][0]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[13][0]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[13][0] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[13][0]->Fill(pRPD_ratio[13][0]);

                                    if (pRPD_ratio[13][0] > 1.6 && pRPD_ratio[13][0] < 2.4) {
                                    pRPD_signal[13][0] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[13][0]->Fill(pRPD_signal[13][0]);
                                    }   
                                    if (channel[n] == 16) {
                                    Run375259_pRPD_TS[1][0]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[1][0]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[1][0]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[1][0]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[1][0]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[1][0]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[1][0] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[1][0]->Fill(pRPD_ratio[1][0]);

                                    if (pRPD_ratio[1][0] > 1.5 && pRPD_ratio[1][0] < 2.5) {
                                    pRPD_signal[1][0] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[1][0]->Fill(pRPD_signal[1][0]);
                                    }            
                                    pRPDX1[0] = pRPD_signal[0][0] + pRPD_signal[4][0] + pRPD_signal[8][0] + pRPD_signal[12][0];                   
                                    pRPDX2[0] = pRPD_signal[1][0] + pRPD_signal[5][0] + pRPD_signal[9][0] + pRPD_signal[13][0];  
                                    pRPDX3[0] = pRPD_signal[2][0] + pRPD_signal[6][0] + pRPD_signal[10][0] + pRPD_signal[14][0];  
                                    pRPDX4[0] = pRPD_signal[3][0] + pRPD_signal[7][0] + pRPD_signal[11][0] + pRPD_signal[15][0];  

                                    pRPDY1[0] = pRPD_signal[0][0] + pRPD_signal[1][0] + pRPD_signal[2][0] + pRPD_signal[3][0];  
                                    pRPDY2[0] = pRPD_signal[4][0] + pRPD_signal[5][0] + pRPD_signal[6][0] + pRPD_signal[7][0];  
                                    pRPDY3[0] = pRPD_signal[8][0] + pRPD_signal[9][0] + pRPD_signal[10][0] + pRPD_signal[11][0];  
                                    pRPDY4[0] = pRPD_signal[12][0] + pRPD_signal[13][0] + pRPD_signal[14][0] + pRPD_signal[15][0];  

                                    pRPD_signal_total[0] = pRPDX1[0] + pRPDX2[0] + pRPDX3[0] + pRPDX4[0];

                                    pRPD_signal_col[0] = ((-3*pRPDX1[0]) + (-1*pRPDX2[0]) + (1*pRPDX3[0]) + (3*pRPDX4[0])) / pRPD_signal_total[0];
                                    pRPD_signal_row[0] = ((-3*pRPDY4[0]) + (-1*pRPDY3[0]) + (1*pRPDY2[0]) + (3*pRPDY1[0])) / pRPD_signal_total[0];

                                } // end of RPD side and section
                                                      
                                if (zside[n] == 1 && section[n] == 1) { 
                                if (channel[n] == 1) {
                                    Run375259_pEM_TS[0][0]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[0][0]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[0][0]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[0][0]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[0][0]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[0][0]->Fill(5.0, TS5[n]);

                                    pEM_ratio[0][0] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[0][0]->Fill(pEM_ratio[0][0]);

                                    //if (pEM_ratio[0][0] > 0.8 && pEM_ratio[0][0] < 1.2){
                                        pEM_signal[0][0] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[0][0]->Fill(pEM_signal[0][0]);

                                }
                                if (channel[n] == 2) {
                                    Run375259_pEM_TS[1][0]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[1][0]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[1][0]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[1][0]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[1][0]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[1][0]->Fill(5.0, TS5[n]);

                                    pEM_ratio[1][0] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[1][0]->Fill(pEM_ratio[1][0]);

                                    //if (pEM_ratio[1][0] > 0.8 && pEM_ratio[1][0] < 1.2){
                                        pEM_signal[1][0] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[1][0]->Fill(pEM_signal[1][0]);
                                }
                                if (channel[n] == 3){
                                    Run375259_pEM_TS[2][0]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[2][0]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[2][0]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[2][0]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[2][0]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[2][0]->Fill(5.0, TS5[n]);

                                    pEM_ratio[2][0] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[2][0]->Fill(pEM_ratio[2][0]);

                                    //if (pEM_ratio[2][0] > 0.8 && pEM_ratio[2][0] < 1.2){
                                        pEM_signal[2][0] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[2][0]->Fill(pEM_signal[2][0]);
                                }
                                if (channel[n] == 4){
                                    Run375259_pEM_TS[3][0]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[3][0]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[3][0]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[3][0]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[3][0]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[3][0]->Fill(5.0, TS5[n]);

                                    pEM_ratio[3][0] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[3][0]->Fill(pEM_ratio[3][0]);

                                    //if (pEM_ratio[3][0] > 0.8 && pEM_ratio[3][0] < 1.2){
                                        pEM_signal[3][0] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[3][0]->Fill(pEM_signal[3][0]);
                                }
                                if (channel[n] == 5){
                                    Run375259_pEM_TS[4][0]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[4][0]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[4][0]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[4][0]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[4][0]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[4][0]->Fill(5.0, TS5[n]);

                                    pEM_ratio[4][0] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[4][0]->Fill(pEM_ratio[4][0]);

                                    //if (pEM_ratio[4][0] > 0.8 && pEM_ratio[4][0] < 1.2){
                                        pEM_signal[4][0] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[4][0]->Fill(pEM_signal[4][0]);
                                }
                                pEM_signal_total[0] = (0.6 * pEM_signal[0][0]) + (0.89 * pEM_signal[1][0]) + (1 * pEM_signal[2][0]) + (1.29 * pEM_signal[3][0]) + (0.57 * pEM_signal[4][0]);
                                pEM_signal_col[0] = ((-3.6 * 0.6 * pEM_signal[0][0]) + (-1.8 * 0.89 * pEM_signal[1][0]) + (0 * 1 * pEM_signal[2][0]) + (1.8 * 1.29 * pEM_signal[3][0]) + (3.6 * 0.57 * pEM_signal[4][0])) / pEM_signal_total[0];

                            } // end of side and section EM
                        
                    if (zside[n] == 1 && section[n] == 2){
                        
                        if (channel[n] == 1){
                            Run375259_pHAD_TS[0][0]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[0][0]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[0][0]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[0][0]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[0][0]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[0][0]->Fill(5.0,TS5[n]);

                            pHAD_ratio[0][0] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[0][0]->Fill(pHAD_ratio[0][0]);

                            //if (pHAD_ratio[0][0] > 3.5 && pHAD_ratio[0][0] < 4){
                                pHAD_signal[0][0] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[0][0]->Fill(pHAD_signal[0][0]);
                        }
                        if (channel[n] == 2){
                            Run375259_pHAD_TS[0][1]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[1][0]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[1][0]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[1][0]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[1][0]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[1][0]->Fill(5.0,TS5[n]);

                            pHAD_ratio[1][0] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[1][0]->Fill(pHAD_ratio[1][0]);

                            //if (pHAD_ratio[1][0] > 3.5 && pHAD_ratio[1][0] < 4.5){
                                pHAD_signal[1][0] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[1][0]->Fill(pHAD_signal[1][0]);
                        }
                        if (channel[n] == 3){
                            Run375259_pHAD_TS[2][0]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[2][0]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[2][0]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[2][0]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[2][0]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[2][0]->Fill(5.0,TS5[n]);

                            pHAD_ratio[2][0] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[2][0]->Fill(pHAD_ratio[2][0]);

                            //if (pHAD_ratio[2][0] > 3.5 && pHAD_ratio[2][0] < 5){
                                pHAD_signal[2][0] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[2][0]->Fill(pHAD_signal[2][0]);
                        }
                        if (channel[n] == 4){
                            Run375259_pHAD_TS[3][0]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[3][0]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[3][0]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[3][0]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[3][0]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[3][0]->Fill(5.0,TS5[n]);

                            pHAD_ratio[3][0] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[3][0]->Fill(pHAD_ratio[3][0]);

                            //if (pHAD_ratio[3][0] > 4 && pHAD_ratio[3][0] < 5){
                                pHAD_signal[3][0] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[3][0]->Fill(pHAD_signal[3][0]);
                        }
                        pHAD_signal_total[0] = pHAD_signal[0][0] + pHAD_signal[1][0] + pHAD_signal[2][0] + pHAD_signal[3][0];
                        } // end  HAD 
                    } //end channel loop

                    Run375259_pEM_COMvsCent[0]->Fill(pEM_signal_col[0]);

                    Run375259_pEM_Profile[0]->Fill(0.0 , pEM_signal[0][0]);
                    Run375259_pEM_Profile[0]->Fill(1.0 , pEM_signal[1][0]);
                    Run375259_pEM_Profile[0]->Fill(2.0 , pEM_signal[2][0]);
                    Run375259_pEM_Profile[0]->Fill(3.0 , pEM_signal[3][0]);
                    Run375259_pEM_Profile[0]->Fill(4.0 , pEM_signal[4][0]);

                    Run375259_pRPD_COM[0]->Fill(pRPD_signal_col[0], pRPD_signal_row[0]);
                    pos_rpd_xprojection[0]->Fill(pRPD_signal_col[0]);
                    Run375259_pRPD_prof[0]->Fill(0.0,pRPDX1[0]);
                    Run375259_pRPD_prof[0]->Fill(1.0,pRPDX2[0]);
                    Run375259_pRPD_prof[0]->Fill(2.0,pRPDX3[0]);
                    Run375259_pRPD_prof[0]->Fill(3.0,pRPDX4[0]);

                    Run375259_pRPD_Avg_Y_Sig[0]->Fill(0.0, pRPDY1[0]);
                    Run375259_pRPD_Avg_Y_Sig[0]->Fill(1.0, pRPDY2[0]);
                    Run375259_pRPD_Avg_Y_Sig[0]->Fill(2.0, pRPDY3[0]);
                    Run375259_pRPD_Avg_Y_Sig[0]->Fill(3.0, pRPDY4[0]);

                    Run375259_pRPD_HeatMap[0]->Fill(0.5,3.5,pRPD_signal[0][0]);
                    Run375259_pRPD_HeatMap[0]->Fill(1.5,3.5,pRPD_signal[1][0]);
                    Run375259_pRPD_HeatMap[0]->Fill(2.5,3.5,pRPD_signal[2][0]);
                    Run375259_pRPD_HeatMap[0]->Fill(3.5,3.5,pRPD_signal[3][0]);

                    Run375259_pRPD_HeatMap[0]->Fill(0.5,2.5,pRPD_signal[4][0]);
                    Run375259_pRPD_HeatMap[0]->Fill(1.5,2.5,pRPD_signal[5][0]);
                    Run375259_pRPD_HeatMap[0]->Fill(2.5,2.5,pRPD_signal[6][0]);
                    Run375259_pRPD_HeatMap[0]->Fill(3.5,2.5,pRPD_signal[7][0]);

                    Run375259_pRPD_HeatMap[0]->Fill(0.5,1.5,pRPD_signal[8][0]);
                    Run375259_pRPD_HeatMap[0]->Fill(1.5,1.5,pRPD_signal[9][0]);
                    Run375259_pRPD_HeatMap[0]->Fill(2.5,1.5,pRPD_signal[10][0]);
                    Run375259_pRPD_HeatMap[0]->Fill(3.5,1.5,pRPD_signal[11][0]);

                    Run375259_pRPD_HeatMap[0]->Fill(0.5,0.5,pRPD_signal[12][0]);
                    Run375259_pRPD_HeatMap[0]->Fill(1.5,0.5,pRPD_signal[13][0]);
                    Run375259_pRPD_HeatMap[0]->Fill(2.5,0.5,pRPD_signal[14][0]);
                    Run375259_pRPD_HeatMap[0]->Fill(3.5,0.5,pRPD_signal[15][0]);

                    ZDC[0] = 0.1 * pEM_signal_total[0] + pHAD_signal_total[0];
                    Run375259_pRPD_position_vstotalsignal[0]->Fill(ZDC[0], pRPD_signal_col[0]);
                    Run375259_pEM_position_vstotalsignal[0]->Fill(ZDC[0], pEM_signal_col[0]);
                    Run375259_NeutronPlotProjection[0]->Fill(ZDC[0]);
                    
                    Run375259_pRPDx_vs_pEMx[0]->Fill(pRPD_signal_col[0], pEM_signal_col[0]);
                    Run375259_NeutronPlot[0]->Fill(ZDC[0],pEM_signal_total[0]);
                } // end of hibin 0 - 20   
                if (hibin >20 && hibin < 40 ){ 
                            for (int n = 0; n < 56; n++) {
                                if (zside[n] == 1 && section[n] == 4) {
                                    if (channel[n] == 1) {
                                    Run375259_pRPD_TS[10][1]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[10][1]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[10][1]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[10][1]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[10][1]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[10][1]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[10][1] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[10][1]->Fill(pRPD_ratio[10][1]);

                                    if (pRPD_ratio[10][1] > 1.5 && pRPD_ratio[10][1] < 2.0) {
                                    pRPD_signal[10][1] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[10][1]->Fill(pRPD_signal[10][1]);
                                    
                                    }
                                    if (channel[n] == 2) {
                                    Run375259_pRPD_TS[6][1]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[6][1]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[6][1]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[6][1]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[6][1]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[6][1]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[6][1] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[6][1]->Fill(pRPD_ratio[6][1]);
                                    
                                    if (pRPD_ratio[6][1] > 1.5 && pRPD_ratio[6][1] < 2.1) {
                                    pRPD_signal[6][1] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[6][1]->Fill(pRPD_signal[6][1]);
                                    
                                    } 
                                    if (channel[n] == 3) {
                                    Run375259_pRPD_TS[2][1]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[2][1]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[2][1]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[2][1]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[2][1]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[2][1]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[2][1] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[2][1]->Fill(pRPD_ratio[2][1]);
                                    
                                    if (pRPD_ratio[2][1] > 1.5 && pRPD_ratio[2][1] < 2.0) {
                                    pRPD_signal[2][1] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[2][1]->Fill(pRPD_signal[2][1]);
                                    
                                    }      
                                    if (channel[n] == 4) {
                                    Run375259_pRPD_TS[14][1]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[14][1]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[14][1]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[14][1]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[14][1]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[14][1]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[14][1] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[14][1]->Fill(pRPD_ratio[14][1]);

                                    if (pRPD_ratio[14][1] > 1.5 && pRPD_ratio[14][1] < 2.0) {
                                    pRPD_signal[14][1] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[14][1]->Fill(pRPD_signal[14][1]);
                                    
                                    }   
                                    if (channel[n] == 5) {
                                    Run375259_pRPD_TS[11][1]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[11][1]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[11][1]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[11][1]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[11][1]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[11][1]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[11][1] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[11][1]->Fill(pRPD_ratio[11][1]);
                                    
                                    if (pRPD_ratio[11][1] > 1.5 && pRPD_ratio[11][1] < 2.1) {
                                    pRPD_signal[11][1] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[11][1]->Fill(pRPD_signal[11][1]);
                                    
                                    }   
                                    if (channel[n] == 6) {
                                    Run375259_pRPD_TS[7][1]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[7][1]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[7][1]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[7][1]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[7][1]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[7][1]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[7][1] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[7][1]->Fill(pRPD_ratio[7][1]);
                                    
                                    if (pRPD_ratio[7][1] > 1.6 && pRPD_ratio[7][1] < 2.4) {
                                    pRPD_signal[7][1] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[7][1]->Fill(pRPD_signal[7][1]);
                                    
                                    }   
                                    if (channel[n] == 7) {
                                    Run375259_pRPD_TS[3][1]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[3][1]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[3][1]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[3][1]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[3][1]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[3][1]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[3][1] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[3][1]->Fill(pRPD_ratio[3][1]);
                                    
                                    if (pRPD_ratio[3][1] > 1.5 && pRPD_ratio[3][1] < 2.4) {
                                    pRPD_signal[3][1] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[3][1]->Fill(pRPD_signal[3][1]);
                                    
                                    }   
                                    if (channel[n] == 8) {
                                    Run375259_pRPD_TS[15][1]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[15][1]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[15][1]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[15][1]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[15][1]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[15][1]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[15][1] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[15][1]->Fill(pRPD_ratio[15][1]);

                                    if (pRPD_ratio[15][1] > 1.6 && pRPD_ratio[15][1] < 2.2) {
                                    pRPD_signal[15][1] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[15][1]->Fill(pRPD_signal[15][1]);
                                    }   
                                    if (channel[n] == 9) {
                                    Run375259_pRPD_TS[4][1]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[4][1]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[4][1]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[4][1]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[4][1]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[4][1]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[4][1] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[4][1]->Fill(pRPD_ratio[4][1]);

                                    if (pRPD_ratio[4][1] > 1.5 && pRPD_ratio[4][1] < 2.4 ) {
                                    pRPD_signal[4][1] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[4][1]->Fill(pRPD_signal[4][1]);
                                    }   
                                    if (channel[n] == 10) {
                                    Run375259_pRPD_TS[8][1]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[8][1]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[8][1]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[8][1]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[8][1]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[8][1]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[8][1] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[8][1]->Fill(pRPD_ratio[8][1]);

                                    if (pRPD_ratio[8][1] > 1.5 && pRPD_ratio[8][1] < 2.3) {
                                    pRPD_signal[8][1] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[8][1]->Fill(pRPD_signal[8][1]);
                                    }   
                                    if (channel[n] == 11) {
                                    Run375259_pRPD_TS[12][1]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[12][1]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[12][1]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[12][1]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[12][1]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[12][1]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[12][1] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[12][1]->Fill(pRPD_ratio[12][1]);

                                    if (pRPD_ratio[12][1] > 1.5 && pRPD_ratio[12][1] < 2.2){
                                    pRPD_signal[12][1] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[12][1]->Fill(pRPD_signal[12][1]);
                                    }   
                                    if (channel[n] == 12) {
                                    Run375259_pRPD_TS[0][1]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[0][1]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[0][1]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[0][1]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[0][1]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[0][1]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[0][1] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[0][1]->Fill(pRPD_ratio[0][1]);

                                    if (pRPD_ratio[0][1] > 1.5 && pRPD_ratio[0][1] < 2.3){
                                    pRPD_signal[0][1] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[0][1]->Fill(pRPD_signal[0][1]);
                                    }   
                                    if (channel[n] == 13) {
                                    Run375259_pRPD_TS[5][1]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[5][1]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[5][1]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[5][1]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[5][1]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[5][1]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[5][1] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[5][1]->Fill(pRPD_ratio[5][1]);

                                    if (pRPD_ratio[5][1] > 1.7 && pRPD_ratio[5][1] < 2.5){
                                    pRPD_signal[5][1] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[5][1]->Fill(pRPD_signal[5][1]);
                                    }   
                                    if (channel[n] == 14) {
                                    Run375259_pRPD_TS[9][1]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[9][1]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[9][1]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[9][1]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[9][1]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[9][1]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[9][1] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[9][1]->Fill(pRPD_ratio[9][1]);
                                    
                                    if (pRPD_ratio[9][1] > 1.6 && pRPD_ratio[9][1] < 2.4) {
                                    pRPD_signal[9][1] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[9][1]->Fill(pRPD_signal[9][1]);
                                    }   
                                    if (channel[n] == 15) {
                                    Run375259_pRPD_TS[13][1]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[13][1]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[13][1]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[13][1]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[13][1]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[13][1]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[13][1] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[13][1]->Fill(pRPD_ratio[13][1]);

                                    if (pRPD_ratio[13][1] > 1.6 && pRPD_ratio[13][1] < 2.4) {
                                    pRPD_signal[13][1] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[13][1]->Fill(pRPD_signal[13][1]);
                                    }   
                                    if (channel[n] == 16) {
                                    Run375259_pRPD_TS[1][1]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[1][1]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[1][1]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[1][1]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[1][1]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[1][1]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[1][1] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[1][1]->Fill(pRPD_ratio[1][1]);

                                    if (pRPD_ratio[1][1] > 1.5 && pRPD_ratio[1][1] < 2.5) {
                                    pRPD_signal[1][1] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[1][1]->Fill(pRPD_signal[1][1]);
                                    }            
                                    pRPDX1[1] = pRPD_signal[0][1] + pRPD_signal[4][1] + pRPD_signal[8][1] + pRPD_signal[12][1];                   
                                    pRPDX2[1] = pRPD_signal[1][1] + pRPD_signal[5][1] + pRPD_signal[9][1] + pRPD_signal[13][1];  
                                    pRPDX3[1] = pRPD_signal[2][1] + pRPD_signal[6][1] + pRPD_signal[10][1] + pRPD_signal[14][1];  
                                    pRPDX4[1] = pRPD_signal[3][1] + pRPD_signal[7][1] + pRPD_signal[11][1] + pRPD_signal[15][1];  

                                    pRPDY1[1] = pRPD_signal[0][1] + pRPD_signal[1][1] + pRPD_signal[2][1] + pRPD_signal[3][1];  
                                    pRPDY2[1] = pRPD_signal[4][1] + pRPD_signal[5][1] + pRPD_signal[6][1] + pRPD_signal[7][1];  
                                    pRPDY3[1] = pRPD_signal[8][1] + pRPD_signal[9][1] + pRPD_signal[10][1] + pRPD_signal[11][1];  
                                    pRPDY4[1] = pRPD_signal[12][1] + pRPD_signal[13][1] + pRPD_signal[14][1] + pRPD_signal[15][1];  

                                    pRPD_signal_total[1] = pRPDX1[1] + pRPDX2[1] + pRPDX3[1] + pRPDX4[1];

                                    pRPD_signal_col[1] = ((-3*pRPDX1[1]) + (-1*pRPDX2[1]) + (1*pRPDX3[1]) + (3*pRPDX4[1])) / pRPD_signal_total[1];
                                    pRPD_signal_row[1] = ((-3*pRPDY4[1]) + (-1*pRPDY3[1]) + (1*pRPDY2[1]) + (3*pRPDY1[1])) / pRPD_signal_total[1];

                                } // end of side and section
                            
                                if (zside[n] == 1 && section[n] == 1) {
                                if (channel[n] == 1) {
                                    Run375259_pEM_TS[0][1]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[0][1]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[0][1]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[0][1]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[0][1]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[0][1]->Fill(5.0, TS5[n]);

                                    pEM_ratio[0][1] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[0][1]->Fill(pEM_ratio[0][1]);

                                    //if (pEM_ratio[0][1] > 0.8 && pEM_ratio[0][1] < 1.2){
                                        pEM_signal[0][1] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[0][1]->Fill(pEM_signal[0][1]);

                                }
                                if (channel[n] == 2) {
                                    Run375259_pEM_TS[1][1]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[1][1]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[1][1]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[1][1]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[1][1]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[1][1]->Fill(5.0, TS5[n]);

                                    pEM_ratio[1][1] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[1][1]->Fill(pEM_ratio[1][1]);

                                    //if (pEM_ratio[1][1] > 0.8 && pEM_ratio[1][1] < 1.2){
                                        pEM_signal[1][1] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[1][1]->Fill(pEM_signal[1][1]);
                                }
                                if (channel[n] == 3){
                                    Run375259_pEM_TS[2][1]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[2][1]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[2][1]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[2][1]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[2][1]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[2][1]->Fill(5.0, TS5[n]);

                                    pEM_ratio[2][1] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[2][1]->Fill(pEM_ratio[2][1]);

                                    //if (pEM_ratio[2][1] > 0.8 && pEM_ratio[2][1] < 1.2){
                                        pEM_signal[2][1] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[2][1]->Fill(pEM_signal[2][1]);
                                }
                                if (channel[n] == 4){
                                    Run375259_pEM_TS[3][1]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[3][1]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[3][1]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[3][1]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[3][1]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[3][1]->Fill(5.0, TS5[n]);

                                    pEM_ratio[3][1] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[3][1]->Fill(pEM_ratio[3][1]);

                                    //if (pEM_ratio[3][1] > 0.8 && pEM_ratio[3][1] < 1.2){
                                        pEM_signal[3][1] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[3][1]->Fill(pEM_signal[3][1]);
                                }
                                if (channel[n] == 5){
                                    Run375259_pEM_TS[4][1]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[4][1]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[4][1]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[4][1]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[4][1]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[4][1]->Fill(5.0, TS5[n]);

                                    pEM_ratio[4][1] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[4][1]->Fill(pEM_ratio[4][1]);

                                    //if (pEM_ratio[4][1] > 0.8 && pEM_ratio[4][1] < 1.2){
                                        pEM_signal[4][1] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[4][1]->Fill(pEM_signal[4][1]);
                                }
                                 pEM_signal_total[1] = (0.6 * pEM_signal[0][1]) + (0.89 * pEM_signal[1][1]) + (1 * pEM_signal[2][1]) + (1.29 * pEM_signal[3][1]) + (0.57 * pEM_signal[4][1]);
                                 pEM_signal_col[1] = ((-3.6 * 0.6 * pEM_signal[0][1]) + (-1.8 * 0.89 * pEM_signal[1][1]) + (0 * 1 * pEM_signal[2][1]) + (1.8 * 1.29 * pEM_signal[3][1]) + (3.6 * 0.57 * pEM_signal[4][1])) / pEM_signal_total[1];
                            } // end of side & section
                       
                    if (zside[n] == 1 && section[n] == 2){
                        if (channel[n] == 1){
                            Run375259_pHAD_TS[0][1]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[0][1]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[0][1]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[0][1]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[0][1]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[0][1]->Fill(5.0,TS5[n]);
                            pHAD_ratio[0][1] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[0][1]->Fill(pHAD_ratio[0][1]);
                            //if (pHAD_ratio[0][1] > 3.5 && pHAD_ratio[0][1] < 4){
                                pHAD_signal[0][1] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[0][1]->Fill(pHAD_signal[0][1]);
                        }
                        if (channel[n] == 2){
                            Run375259_pHAD_TS[1][1]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[1][1]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[1][1]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[1][1]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[1][1]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[1][1]->Fill(5.0,TS5[n]);
                            pHAD_ratio[1][1] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[1][1]->Fill(pHAD_ratio[1][1]);
                            //if (pHAD_ratio[1][1] > 3.5 && pHAD_ratio[1][1] < 4.5){
                                pHAD_signal[1][1] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[1][1]->Fill(pHAD_signal[1][1]);
                        }
                        if (channel[n] == 3){
                            Run375259_pHAD_TS[2][1]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[2][1]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[2][1]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[2][1]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[2][1]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[2][1]->Fill(5.0,TS5[n]);
                            pHAD_ratio[2][1] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[2][1]->Fill(pHAD_ratio[2][1]);
                            //if (pHAD_ratio[2][1] > 3.5 && pHAD_ratio[2][1] < 5){
                                pHAD_signal[2][1] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[2][1]->Fill(pHAD_signal[2][1]);
                        }
                        if (channel[n] == 4){
                            Run375259_pHAD_TS[3][1]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[3][1]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[3][1]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[3][1]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[3][1]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[3][1]->Fill(5.0,TS5[n]);
                            pHAD_ratio[3][1] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[3][1]->Fill(pHAD_ratio[3][1]);
                            //if (pHAD_ratio[3][1] > 4 && pHAD_ratio[3][1] < 5){
                                pHAD_signal[3][1] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[3][1]->Fill(pHAD_signal[3][1]);
                        }
                        pHAD_signal_total[1] = pHAD_signal[0][1] + pHAD_signal[1][1] + pHAD_signal[2][1] + pHAD_signal[3][1];
                        } // end  HAD 
                    } //end channel loop
                            Run375259_pEM_COMvsCent[1]->Fill(pEM_signal_col[1]);

                            Run375259_pEM_Profile[1]->Fill(0.0 , pEM_signal[0][1]);
                            Run375259_pEM_Profile[1]->Fill(1.0 , pEM_signal[1][1]);
                            Run375259_pEM_Profile[1]->Fill(2.0 , pEM_signal[2][1]);
                            Run375259_pEM_Profile[1]->Fill(3.0 , pEM_signal[3][1]);
                            Run375259_pEM_Profile[1]->Fill(4.0 , pEM_signal[4][1]);

                            Run375259_pRPD_COM[1]->Fill(pRPD_signal_col[1], pRPD_signal_row[1]);

                            pos_rpd_xprojection[1]->Fill(pRPD_signal_col[1]);

                            Run375259_pRPD_prof[1]->Fill(0.0,pRPDX1[1]);
                            Run375259_pRPD_prof[1]->Fill(1.0,pRPDX2[1]);
                            Run375259_pRPD_prof[1]->Fill(2.0,pRPDX3[1]);
                            Run375259_pRPD_prof[1]->Fill(3.0,pRPDX4[1]);

                            Run375259_pRPD_Avg_Y_Sig[1]->Fill(0.0, pRPDY1[1]);
                            Run375259_pRPD_Avg_Y_Sig[1]->Fill(1.0, pRPDY2[1]);
                            Run375259_pRPD_Avg_Y_Sig[1]->Fill(2.0, pRPDY3[1]);
                            Run375259_pRPD_Avg_Y_Sig[1]->Fill(3.0, pRPDY4[1]);

                            Run375259_pRPD_HeatMap[1]->Fill(0.5,3.5,pRPD_signal[0][1]);
                            Run375259_pRPD_HeatMap[1]->Fill(1.5,3.5,pRPD_signal[1][1]);
                            Run375259_pRPD_HeatMap[1]->Fill(2.5,3.5,pRPD_signal[2][1]);
                            Run375259_pRPD_HeatMap[1]->Fill(3.5,3.5,pRPD_signal[3][1]);

                            Run375259_pRPD_HeatMap[1]->Fill(0.5,2.5,pRPD_signal[4][1]);
                            Run375259_pRPD_HeatMap[1]->Fill(1.5,2.5,pRPD_signal[5][1]);
                            Run375259_pRPD_HeatMap[1]->Fill(2.5,2.5,pRPD_signal[6][1]);
                            Run375259_pRPD_HeatMap[1]->Fill(3.5,2.5,pRPD_signal[7][1]);

                            Run375259_pRPD_HeatMap[1]->Fill(0.5,1.5,pRPD_signal[8][1]);
                            Run375259_pRPD_HeatMap[1]->Fill(1.5,1.5,pRPD_signal[9][1]);
                            Run375259_pRPD_HeatMap[1]->Fill(2.5,1.5,pRPD_signal[10][1]);
                            Run375259_pRPD_HeatMap[1]->Fill(3.5,1.5,pRPD_signal[11][1]);

                            Run375259_pRPD_HeatMap[1]->Fill(0.5,0.5,pRPD_signal[12][1]);
                            Run375259_pRPD_HeatMap[1]->Fill(1.5,0.5,pRPD_signal[13][1]);
                            Run375259_pRPD_HeatMap[1]->Fill(2.5,0.5,pRPD_signal[14][1]);
                            Run375259_pRPD_HeatMap[1]->Fill(3.5,0.5,pRPD_signal[15][1]);

                            ZDC[1] = 0.1 * pEM_signal_total[1] + pHAD_signal_total[1];

                            Run375259_pRPD_position_vstotalsignal[1]->Fill(ZDC[1], pRPD_signal_col[1]);

                            Run375259_pRPDx_vs_pEMx[1]->Fill(pRPD_signal_col[1], pEM_signal_col[1]);

                            Run375259_pEM_position_vstotalsignal[1]->Fill(ZDC[1],pEM_signal_col[1]);

                            Run375259_NeutronPlotProjection[1]->Fill(ZDC[1]);

                            Run375259_NeutronPlot[1]->Fill(ZDC[1],pEM_signal_total[1]);
                } // end of hibin 20 - 40

                if (hibin >=40 && hibin < 60 ){ 
                            for (int n = 0; n < 56; n++) {
                                if (zside[n] == 1 && section[n] == 4) {
                                    if (channel[n] == 1) {
                                    Run375259_pRPD_TS[10][2]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[10][2]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[10][2]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[10][2]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[10][2]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[10][2]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[10][2] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[10][2]->Fill(pRPD_ratio[10][2]);

                                    if (pRPD_ratio[10][2] > 1.5 && pRPD_ratio[10][2] < 2.0) {
                                    pRPD_signal[10][2] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[10][2]->Fill(pRPD_signal[10][2]);
                                    
                                    }
                                    if (channel[n] == 2) {
                                    Run375259_pRPD_TS[6][2]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[6][2]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[6][2]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[6][2]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[6][2]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[6][2]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[6][2] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[6][2]->Fill(pRPD_ratio[6][2]);
                                    
                                    if (pRPD_ratio[6][2] > 1.5 && pRPD_ratio[6][2] < 2.1) {
                                    pRPD_signal[6][2] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[6][2]->Fill(pRPD_signal[6][2]);
                                    
                                    } 
                                    if (channel[n] == 3) {
                                    Run375259_pRPD_TS[2][2]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[2][2]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[2][2]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[2][2]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[2][2]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[2][2]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[2][2] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[2][2]->Fill(pRPD_ratio[2][2]);
                                    
                                    if (pRPD_ratio[2][2] > 1.5 && pRPD_ratio[2][2] < 2.0) {
                                    pRPD_signal[2][2] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[2][2]->Fill(pRPD_signal[2][2]);
                                    
                                    }      
                                    if (channel[n] == 4) {
                                    Run375259_pRPD_TS[14][2]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[14][2]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[14][2]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[14][2]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[14][2]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[14][2]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[14][2] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[14][2]->Fill(pRPD_ratio[14][2]);

                                    if (pRPD_ratio[14][2] > 1.5 && pRPD_ratio[14][2] < 2.0) {
                                    pRPD_signal[14][2] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[14][2]->Fill(pRPD_signal[14][2]);
                                    
                                    }   
                                    if (channel[n] == 5) {
                                    Run375259_pRPD_TS[11][2]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[11][2]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[11][2]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[11][2]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[11][2]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[11][2]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[11][2] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[11][2]->Fill(pRPD_ratio[11][2]);
                                    
                                    if (pRPD_ratio[11][2] > 1.5 && pRPD_ratio[11][2] < 2.1) {
                                    pRPD_signal[11][2] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[11][2]->Fill(pRPD_signal[11][2]);
                                    
                                    }   
                                    if (channel[n] == 6) {
                                    Run375259_pRPD_TS[7][2]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[7][2]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[7][2]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[7][2]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[7][2]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[7][2]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[7][2] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[7][2]->Fill(pRPD_ratio[7][2]);
                                    
                                    if (pRPD_ratio[7][2] > 1.6 && pRPD_ratio[7][2] < 2.4) {
                                    pRPD_signal[7][2] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[7][2]->Fill(pRPD_signal[7][2]);
                                    
                                    }   
                                    if (channel[n] == 7) {
                                    Run375259_pRPD_TS[3][2]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[3][2]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[3][2]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[3][2]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[3][2]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[3][2]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[3][2] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[3][2]->Fill(pRPD_ratio[3][2]);
                                    
                                    if (pRPD_ratio[3][2] > 1.5 && pRPD_ratio[3][2] < 2.4) {
                                    pRPD_signal[3][2] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[3][2]->Fill(pRPD_signal[3][2]);
                                    
                                    }   
                                    if (channel[n] == 8) {
                                    Run375259_pRPD_TS[15][2]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[15][2]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[15][2]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[15][2]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[15][2]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[15][2]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[15][2] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[15][2]->Fill(pRPD_ratio[15][2]);

                                    if (pRPD_ratio[15][2] > 1.6 && pRPD_ratio[15][2] < 2.2) {
                                    pRPD_signal[15][2] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[15][2]->Fill(pRPD_signal[15][2]);
                                    }   
                                    if (channel[n] == 9) {
                                    Run375259_pRPD_TS[4][2]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[4][2]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[4][2]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[4][2]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[4][2]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[4][2]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[4][2] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[4][2]->Fill(pRPD_ratio[4][2]);

                                    if (pRPD_ratio[4][2] > 1.5 && pRPD_ratio[4][2] < 2.4 ) {
                                    pRPD_signal[4][2] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[4][2]->Fill(pRPD_signal[4][2]);
                                    }   
                                    if (channel[n] == 10) {
                                    Run375259_pRPD_TS[8][2]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[8][2]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[8][2]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[8][2]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[8][2]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[8][2]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[8][2] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[8][2]->Fill(pRPD_ratio[8][2]);

                                    if (pRPD_ratio[8][2] > 1.5 && pRPD_ratio[8][2] < 2.3) {
                                    pRPD_signal[8][2] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[8][2]->Fill(pRPD_signal[8][2]);
                                    }   
                                    if (channel[n] == 11) {
                                    Run375259_pRPD_TS[12][2]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[12][2]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[12][2]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[12][2]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[12][2]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[12][2]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[12][2] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[12][2]->Fill(pRPD_ratio[12][2]);

                                    if (pRPD_ratio[12][2] > 1.5 && pRPD_ratio[12][2] < 2.2){
                                    pRPD_signal[12][2] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[12][2]->Fill(pRPD_signal[12][2]);
                                    }   
                                    if (channel[n] == 12) {
                                    Run375259_pRPD_TS[0][2]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[0][2]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[0][2]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[0][2]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[0][2]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[0][2]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[0][2] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[0][2]->Fill(pRPD_ratio[0][2]);

                                    if (pRPD_ratio[0][2] > 1.5 && pRPD_ratio[0][2] < 2.3){
                                    pRPD_signal[0][2] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[0][2]->Fill(pRPD_signal[0][2]);
                                    }   
                                    if (channel[n] == 13) {
                                    Run375259_pRPD_TS[5][2]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[5][2]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[5][2]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[5][2]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[5][2]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[5][2]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[5][2] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[5][2]->Fill(pRPD_ratio[5][2]);

                                    if (pRPD_ratio[5][2] > 1.7 && pRPD_ratio[5][2] < 2.5){
                                    pRPD_signal[5][2] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[5][2]->Fill(pRPD_signal[5][2]);
                                    }   
                                    if (channel[n] == 14) {
                                    Run375259_pRPD_TS[9][2]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[9][2]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[9][2]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[9][2]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[9][2]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[9][2]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[9][2] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[9][2]->Fill(pRPD_ratio[9][2]);
                                    
                                    if (pRPD_ratio[9][2] > 1.6 && pRPD_ratio[9][2] < 2.4) {
                                    pRPD_signal[9][2] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[9][2]->Fill(pRPD_signal[9][2]);
                                    }   
                                    if (channel[n] == 15) {
                                    Run375259_pRPD_TS[13][2]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[13][2]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[13][2]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[13][2]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[13][2]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[13][2]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[13][2] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[13][2]->Fill(pRPD_ratio[13][2]);

                                    if (pRPD_ratio[13][2] > 1.6 && pRPD_ratio[13][2] < 2.4) {
                                    pRPD_signal[13][2] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[13][2]->Fill(pRPD_signal[13][2]);
                                    }   
                                    if (channel[n] == 16) {
                                    Run375259_pRPD_TS[1][2]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[1][2]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[1][2]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[1][2]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[1][2]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[1][2]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[1][2] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[1][2]->Fill(pRPD_ratio[1][2]);

                                    if (pRPD_ratio[1][2] > 1.5 && pRPD_ratio[1][2] < 2.5) {
                                    pRPD_signal[1][2] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[1][2]->Fill(pRPD_signal[1][2]);
                                    }            
                                    pRPDX1[2] = pRPD_signal[0][2] + pRPD_signal[4][2] + pRPD_signal[8][2] + pRPD_signal[12][2];                   
                                    pRPDX2[2] = pRPD_signal[1][2] + pRPD_signal[5][2] + pRPD_signal[9][2] + pRPD_signal[13][2];  
                                    pRPDX3[2] = pRPD_signal[2][2] + pRPD_signal[6][2] + pRPD_signal[10][2] + pRPD_signal[14][2];  
                                    pRPDX4[2] = pRPD_signal[3][2] + pRPD_signal[7][2] + pRPD_signal[11][2] + pRPD_signal[15][2];  

                                    pRPDY1[2] = pRPD_signal[0][2] + pRPD_signal[1][2] + pRPD_signal[2][2] + pRPD_signal[3][2];  
                                    pRPDY2[2] = pRPD_signal[4][2] + pRPD_signal[5][2] + pRPD_signal[6][2] + pRPD_signal[7][2];  
                                    pRPDY3[2] = pRPD_signal[8][2] + pRPD_signal[9][2] + pRPD_signal[10][2] + pRPD_signal[11][2];  
                                    pRPDY4[2] = pRPD_signal[12][2] + pRPD_signal[13][2] + pRPD_signal[14][2] + pRPD_signal[15][2];  

                                    pRPD_signal_total[2] = pRPDX1[2] + pRPDX2[2] + pRPDX3[2] + pRPDX4[2];

                                    pRPD_signal_col[2] = ((-3*pRPDX1[2]) + (-1*pRPDX2[2]) + (1*pRPDX3[2]) + (3*pRPDX4[2])) / pRPD_signal_total[2];
                                    pRPD_signal_row[2] = ((-3*pRPDY4[2]) + (-1*pRPDY3[2]) + (1*pRPDY2[2]) + (3*pRPDY1[2])) / pRPD_signal_total[2];

                                } // end of side and section
                            
                                if (zside[n] == 1 && section[n] == 1) {
                                if (channel[n] == 1) {
                                    Run375259_pEM_TS[0][2]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[0][2]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[0][2]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[0][2]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[0][2]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[0][2]->Fill(5.0, TS5[n]);

                                    pEM_ratio[0][2] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[0][2]->Fill(pEM_ratio[0][2]);

                                    //if (pEM_ratio[0][2] > 0.8 && pEM_ratio[0][2] < 1.2){
                                        pEM_signal[0][2] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[0][2]->Fill(pEM_signal[0][2]);
                                }
                                if (channel[n] == 2) {
                                    Run375259_pEM_TS[1][2]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[1][2]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[1][2]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[1][2]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[1][2]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[1][2]->Fill(5.0, TS5[n]);

                                    pEM_ratio[1][2] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[1][2]->Fill(pEM_ratio[1][2]);

                                    //if (pEM_ratio[1][2] > 0.8 && pEM_ratio[1][2] < 1.2){
                                        pEM_signal[1][2] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[1][2]->Fill(pEM_signal[1][2]);
                                }
                                if (channel[n] == 3){
                                    Run375259_pEM_TS[2][2]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[2][2]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[2][2]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[2][2]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[2][2]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[2][2]->Fill(5.0, TS5[n]);

                                    pEM_ratio[2][2] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[2][2]->Fill(pEM_ratio[2][2]);

                                    //if (pEM_ratio[2][2] > 0.8 && pEM_ratio[2][2] < 1.2){
                                        pEM_signal[2][2] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[2][2]->Fill(pEM_signal[2][2]);
                                }
                                if (channel[n] == 4){
                                    Run375259_pEM_TS[3][2]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[3][2]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[3][2]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[3][2]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[3][2]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[3][2]->Fill(5.0, TS5[n]);

                                    pEM_ratio[3][2] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[3][2]->Fill(pEM_ratio[3][2]);

                                    //if (pEM_ratio[3][2] > 0.8 && pEM_ratio[3][2] < 1.2){
                                        pEM_signal[3][2] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[3][2]->Fill(pEM_signal[3][2]);
                                }
                                if (channel[n] == 5){
                                    Run375259_pEM_TS[4][2]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[4][2]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[4][2]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[4][2]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[4][2]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[4][2]->Fill(5.0, TS5[n]);

                                    pEM_ratio[4][2] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[4][2]->Fill(pEM_ratio[4][2]);

                                    //if (pEM_ratio[4][2] > 0.8 && pEM_ratio[4][2] < 1.2){
                                        pEM_signal[4][2] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[4][2]->Fill(pEM_signal[4][2]);
                                }
                                 pEM_signal_total[2] = (0.6 * pEM_signal[0][2]) + (0.89 * pEM_signal[1][2]) + (1 * pEM_signal[2][2]) + (1.29 * pEM_signal[3][2]) + (0.57 * pEM_signal[4][2]);
                                 pEM_signal_col[2] = ((-3.6 * 0.6 * pEM_signal[0][2]) + (-1.8 * 0.89 * pEM_signal[1][2]) + (0 * 1 * pEM_signal[2][2]) + (1.8 * 1.29 * pEM_signal[3][2]) + (3.6 * 0.57 * pEM_signal[4][2])) / pEM_signal_total[2];
                            } // end of side & section

                    if (zside[n] == 1 && section[n] == 2){
                        
                        if (channel[n] == 1){
                            Run375259_pHAD_TS[0][2]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[0][2]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[0][2]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[0][2]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[0][2]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[0][2]->Fill(5.0,TS5[n]);
                            pHAD_ratio[0][2] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[0][2]->Fill(pHAD_ratio[0][2]);
                            //if (pHAD_ratio[0][2] > 3.5 && pHAD_ratio[0][2] < 4){
                                pHAD_signal[0][2] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[0][2]->Fill(pHAD_signal[0][2]);
                        }
                        if (channel[n] == 2){
                            Run375259_pHAD_TS[1][2]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[1][2]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[1][2]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[1][2]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[1][2]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[1][2]->Fill(5.0,TS5[n]);
                            pHAD_ratio[1][2] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[1][2]->Fill(pHAD_ratio[1][2]);
                            //if (pHAD_ratio[1][2] > 3.5 && pHAD_ratio[1][2] < 4.5){
                                pHAD_signal[1][2] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[1][2]->Fill(pHAD_signal[1][2]);
                        }
                        if (channel[n] == 3){
                            Run375259_pHAD_TS[2][2]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[2][2]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[2][2]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[2][2]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[2][2]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[2][2]->Fill(5.0,TS5[n]);
                            pHAD_ratio[2][2] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[2][2]->Fill(pHAD_ratio[2][2]);
                            //if (pHAD_ratio[2][2] > 3.5 && pHAD_ratio[2][2] < 5){
                                pHAD_signal[2][2] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[2][2]->Fill(pHAD_signal[2][2]);
                        }
                        if (channel[n] == 4){
                            Run375259_pHAD_TS[3][2]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[3][2]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[3][2]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[3][2]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[3][2]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[3][2]->Fill(5.0,TS5[n]);
                            pHAD_ratio[3][2] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[3][2]->Fill(pHAD_ratio[3][2]);
                            //if (pHAD_ratio[3][2] > 4 && pHAD_ratio[3][2] < 5){
                                pHAD_signal[3][2] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[3][2]->Fill(pHAD_signal[3][2]);
                        }
                        pHAD_signal_total[2] = pHAD_signal[0][2] + pHAD_signal[1][2] + pHAD_signal[2][2] + pHAD_signal[3][2];
                        } // end  HAD 
                    } //end channel loop
                            Run375259_pEM_COMvsCent[2]->Fill(pEM_signal_col[2]);

                            Run375259_pEM_Profile[2]->Fill(0.0 , pEM_signal[0][2]);
                            Run375259_pEM_Profile[2]->Fill(1.0 , pEM_signal[1][2]);
                            Run375259_pEM_Profile[2]->Fill(2.0 , pEM_signal[2][2]);
                            Run375259_pEM_Profile[2]->Fill(3.0 , pEM_signal[3][2]);
                            Run375259_pEM_Profile[2]->Fill(4.0 , pEM_signal[4][2]);

                            Run375259_pRPDx_vs_pEMx[2]->Fill(pRPD_signal_col[2], pEM_signal_col[2]);
                            
                            Run375259_pRPD_COM[2]->Fill(pRPD_signal_col[2], pRPD_signal_row[2]);
                            pos_rpd_xprojection[2]->Fill(pRPD_signal_col[2]);
                            Run375259_pRPD_prof[2]->Fill(0.0,pRPDX1[2]);
                            Run375259_pRPD_prof[2]->Fill(1.0,pRPDX2[2]);
                            Run375259_pRPD_prof[2]->Fill(2.0,pRPDX3[2]);
                            Run375259_pRPD_prof[2]->Fill(3.0,pRPDX4[2]);

                            Run375259_pRPD_Avg_Y_Sig[2]->Fill(0.0, pRPDY1[2]);
                            Run375259_pRPD_Avg_Y_Sig[2]->Fill(1.0, pRPDY2[2]);
                            Run375259_pRPD_Avg_Y_Sig[2]->Fill(2.0, pRPDY3[2]);
                            Run375259_pRPD_Avg_Y_Sig[2]->Fill(3.0, pRPDY4[2]);

                            Run375259_pRPD_HeatMap[2]->Fill(0.5,3.5,pRPD_signal[0][2]);
                            Run375259_pRPD_HeatMap[2]->Fill(1.5,3.5,pRPD_signal[1][2]);
                            Run375259_pRPD_HeatMap[2]->Fill(2.5,3.5,pRPD_signal[2][2]);
                            Run375259_pRPD_HeatMap[2]->Fill(3.5,3.5,pRPD_signal[3][2]);

                            Run375259_pRPD_HeatMap[2]->Fill(0.5,2.5,pRPD_signal[4][2]);
                            Run375259_pRPD_HeatMap[2]->Fill(1.5,2.5,pRPD_signal[5][2]);
                            Run375259_pRPD_HeatMap[2]->Fill(2.5,2.5,pRPD_signal[6][2]);
                            Run375259_pRPD_HeatMap[2]->Fill(3.5,2.5,pRPD_signal[7][2]);

                            Run375259_pRPD_HeatMap[2]->Fill(0.5,1.5,pRPD_signal[8][2]);
                            Run375259_pRPD_HeatMap[2]->Fill(1.5,1.5,pRPD_signal[9][2]);
                            Run375259_pRPD_HeatMap[2]->Fill(2.5,1.5,pRPD_signal[10][2]);
                            Run375259_pRPD_HeatMap[2]->Fill(3.5,1.5,pRPD_signal[11][2]);

                            Run375259_pRPD_HeatMap[2]->Fill(0.5,0.5,pRPD_signal[12][2]);
                            Run375259_pRPD_HeatMap[2]->Fill(1.5,0.5,pRPD_signal[13][2]);
                            Run375259_pRPD_HeatMap[2]->Fill(2.5,0.5,pRPD_signal[14][2]);
                            Run375259_pRPD_HeatMap[2]->Fill(3.5,0.5,pRPD_signal[15][2]);

                            ZDC[2] = 0.1 * pEM_signal_total[2] + pHAD_signal_total[2];
                            Run375259_pRPD_position_vstotalsignal[2]->Fill(ZDC[2], pRPD_signal_col[2]);
                            Run375259_pEM_position_vstotalsignal[2]->Fill(ZDC[2], pEM_signal_col[2]);
                            Run375259_NeutronPlotProjection[2]->Fill(ZDC[2]);
                            Run375259_NeutronPlot[2]->Fill(ZDC[2],pEM_signal_total[2]);
                } // end of hibin 40 - 60%

                if (hibin >=60 && hibin < 80 ){ 
                            for (int n = 0; n < 56; n++) {
                                if (zside[n] == 1 && section[n] == 4) {
                                    if (channel[n] == 1) {
                                    Run375259_pRPD_TS[10][3]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[10][3]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[10][3]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[10][3]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[10][3]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[10][3]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[10][3] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[10][3]->Fill(pRPD_ratio[10][3]);

                                    if (pRPD_ratio[10][3] > 1.5 && pRPD_ratio[10][3] < 2.0) {
                                    pRPD_signal[10][3] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[10][3]->Fill(pRPD_signal[10][3]);
                                    
                                    }
                                    if (channel[n] == 2) {
                                    Run375259_pRPD_TS[6][3]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[6][3]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[6][3]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[6][3]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[6][3]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[6][3]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[6][3] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[6][3]->Fill(pRPD_ratio[6][3]);
                                    
                                    if (pRPD_ratio[6][3] > 1.5 && pRPD_ratio[6][3] < 2.1) {
                                    pRPD_signal[6][3] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[6][3]->Fill(pRPD_signal[6][3]);
                                    
                                    } 
                                    if (channel[n] == 3) {
                                    Run375259_pRPD_TS[2][3]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[2][3]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[2][3]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[2][3]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[2][3]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[2][3]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[2][3] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[2][3]->Fill(pRPD_ratio[2][3]);
                                    
                                    if (pRPD_ratio[2][3] > 1.5 && pRPD_ratio[2][3] < 2.0) {
                                    pRPD_signal[2][3] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[2][3]->Fill(pRPD_signal[2][3]);
                                    
                                    }      
                                    if (channel[n] == 4) {
                                    Run375259_pRPD_TS[14][3]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[14][3]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[14][3]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[14][3]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[14][3]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[14][3]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[14][3] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[14][3]->Fill(pRPD_ratio[14][3]);

                                    if (pRPD_ratio[14][3] > 1.5 && pRPD_ratio[14][3] < 2.0) {
                                    pRPD_signal[14][3] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[14][3]->Fill(pRPD_signal[14][3]);
                                    
                                    }   
                                    if (channel[n] == 5) {
                                    Run375259_pRPD_TS[11][3]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[11][3]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[11][3]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[11][3]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[11][3]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[11][3]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[11][3] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[11][3]->Fill(pRPD_ratio[11][3]);
                                    
                                    if (pRPD_ratio[11][3] > 1.5 && pRPD_ratio[11][3] < 2.1) {
                                    pRPD_signal[11][3] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[11][3]->Fill(pRPD_signal[11][3]);
                                    
                                    }   
                                    if (channel[n] == 6) {
                                    Run375259_pRPD_TS[7][3]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[7][3]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[7][3]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[7][3]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[7][3]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[7][3]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[7][3] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[7][3]->Fill(pRPD_ratio[7][3]);
                                    
                                    if (pRPD_ratio[7][3] > 1.6 && pRPD_ratio[7][3] < 2.4) {
                                    pRPD_signal[7][3] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[7][3]->Fill(pRPD_signal[7][3]);
                                    
                                    }   
                                    if (channel[n] == 7) {
                                    Run375259_pRPD_TS[3][3]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[3][3]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[3][3]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[3][3]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[3][3]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[3][3]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[3][3] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[3][3]->Fill(pRPD_ratio[3][3]);
                                    
                                    if (pRPD_ratio[3][3] > 1.5 && pRPD_ratio[3][3] < 2.4) {
                                    pRPD_signal[3][3] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[3][3]->Fill(pRPD_signal[3][3]);
                                    
                                    }   
                                    if (channel[n] == 8) {
                                    Run375259_pRPD_TS[15][3]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[15][3]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[15][3]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[15][3]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[15][3]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[15][3]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[15][3] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[15][3]->Fill(pRPD_ratio[15][3]);

                                    if (pRPD_ratio[15][3] > 1.6 && pRPD_ratio[15][3] < 2.2) {
                                    pRPD_signal[15][3] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[15][3]->Fill(pRPD_signal[15][3]);
                                    }   
                                    if (channel[n] == 9) {
                                    Run375259_pRPD_TS[4][3]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[4][3]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[4][3]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[4][3]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[4][3]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[4][3]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[4][3] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[4][3]->Fill(pRPD_ratio[4][3]);

                                    if (pRPD_ratio[4][3] > 1.5 && pRPD_ratio[4][3] < 2.4 ) {
                                    pRPD_signal[4][3] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[4][3]->Fill(pRPD_signal[4][3]);
                                    }   
                                    if (channel[n] == 10) {
                                    Run375259_pRPD_TS[8][3]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[8][3]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[8][3]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[8][3]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[8][3]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[8][3]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[8][3] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[8][3]->Fill(pRPD_ratio[8][3]);

                                    if (pRPD_ratio[8][3] > 1.5 && pRPD_ratio[8][3] < 2.3) {
                                    pRPD_signal[8][3] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[8][3]->Fill(pRPD_signal[8][3]);
                                    }   
                                    if (channel[n] == 11) {
                                    Run375259_pRPD_TS[12][3]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[12][3]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[12][3]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[12][3]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[12][3]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[12][3]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[12][3] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[12][3]->Fill(pRPD_ratio[12][3]);

                                    if (pRPD_ratio[12][3] > 1.5 && pRPD_ratio[12][3] < 2.2){
                                    pRPD_signal[12][3] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[12][3]->Fill(pRPD_signal[12][3]);
                                    }   
                                    if (channel[n] == 12) {
                                    Run375259_pRPD_TS[0][3]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[0][3]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[0][3]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[0][3]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[0][3]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[0][3]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[0][3] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[0][3]->Fill(pRPD_ratio[0][3]);

                                    if (pRPD_ratio[0][3] > 1.5 && pRPD_ratio[0][3] < 2.3){
                                    pRPD_signal[0][3] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[0][3]->Fill(pRPD_signal[0][3]);
                                    }   
                                    if (channel[n] == 13) {
                                    Run375259_pRPD_TS[5][3]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[5][3]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[5][3]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[5][3]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[5][3]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[5][3]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[5][3] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[5][3]->Fill(pRPD_ratio[5][3]);

                                    if (pRPD_ratio[5][3] > 1.7 && pRPD_ratio[5][3] < 2.5){
                                    pRPD_signal[5][3] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[5][3]->Fill(pRPD_signal[5][3]);
                                    }   
                                    if (channel[n] == 14) {
                                    Run375259_pRPD_TS[9][3]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[9][3]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[9][3]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[9][3]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[9][3]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[9][3]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[9][3] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[9][3]->Fill(pRPD_ratio[9][3]);
                                    
                                    if (pRPD_ratio[9][3] > 1.6 && pRPD_ratio[9][3] < 2.4) {
                                    pRPD_signal[9][3] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[9][3]->Fill(pRPD_signal[9][3]);
                                    }   
                                    if (channel[n] == 15) {
                                    Run375259_pRPD_TS[13][3]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[13][3]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[13][3]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[13][3]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[13][3]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[13][3]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[13][3] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[13][3]->Fill(pRPD_ratio[13][3]);

                                    if (pRPD_ratio[13][3] > 1.6 && pRPD_ratio[13][3] < 2.4) {
                                    pRPD_signal[13][3] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[13][3]->Fill(pRPD_signal[13][3]);
                                    }   
                                    if (channel[n] == 16) {
                                    Run375259_pRPD_TS[1][3]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[1][3]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[1][3]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[1][3]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[1][3]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[1][3]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[1][3] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[1][3]->Fill(pRPD_ratio[1][3]);

                                    if (pRPD_ratio[1][3] > 1.5 && pRPD_ratio[1][3] < 2.5) {
                                    pRPD_signal[1][3] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[1][3]->Fill(pRPD_signal[1][3]);
                                    }            
                                    pRPDX1[3] = pRPD_signal[0][3] + pRPD_signal[4][3] + pRPD_signal[8][3] + pRPD_signal[12][3];                   
                                    pRPDX2[3] = pRPD_signal[1][3] + pRPD_signal[5][3] + pRPD_signal[9][3] + pRPD_signal[13][3];  
                                    pRPDX3[3] = pRPD_signal[2][3] + pRPD_signal[6][3] + pRPD_signal[10][3] + pRPD_signal[14][3];  
                                    pRPDX4[3] = pRPD_signal[3][3] + pRPD_signal[7][3] + pRPD_signal[11][3] + pRPD_signal[15][3];  

                                    pRPDY1[3] = pRPD_signal[0][3] + pRPD_signal[1][3] + pRPD_signal[2][3] + pRPD_signal[3][3];  
                                    pRPDY2[3] = pRPD_signal[4][3] + pRPD_signal[5][3] + pRPD_signal[6][3] + pRPD_signal[7][3];  
                                    pRPDY3[3] = pRPD_signal[8][3] + pRPD_signal[9][3] + pRPD_signal[10][3] + pRPD_signal[11][3];  
                                    pRPDY4[3] = pRPD_signal[12][3] + pRPD_signal[13][3] + pRPD_signal[14][3] + pRPD_signal[15][3];  

                                    pRPD_signal_total[3] = pRPDX1[3] + pRPDX2[3] + pRPDX3[3] + pRPDX4[3];

                                    pRPD_signal_col[3] = ((-3*pRPDX1[3]) + (-1*pRPDX2[3]) + (1*pRPDX3[3]) + (3*pRPDX4[3])) / pRPD_signal_total[3];
                                    pRPD_signal_row[3] = ((-3*pRPDY4[3]) + (-1*pRPDY3[3]) + (1*pRPDY2[3]) + (3*pRPDY1[3])) / pRPD_signal_total[3];

                                } // end of side and section
                            
                                if (zside[n] == 1 && section[n] == 1) {
                                if (channel[n] == 1) {
                                    Run375259_pEM_TS[0][3]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[0][3]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[0][3]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[0][3]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[0][3]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[0][3]->Fill(5.0, TS5[n]);

                                    pEM_ratio[0][3] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[0][3]->Fill(pEM_ratio[0][3]);

                                    //if (pEM_ratio[0][3] > 0.8 && pEM_ratio[0][3] < 1.2){
                                        pEM_signal[0][3] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[0][3]->Fill(pEM_signal[0][3]);

                                }
                                if (channel[n] == 2) {
                                    Run375259_pEM_TS[1][3]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[1][3]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[1][3]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[1][3]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[1][3]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[1][3]->Fill(5.0, TS5[n]);

                                    pEM_ratio[1][3] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[1][3]->Fill(pEM_ratio[1][3]);

                                    //if (pEM_ratio[1][3] > 0.8 && pEM_ratio[1][3] < 1.2){
                                        pEM_signal[1][3] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[1][3]->Fill(pEM_signal[1][3]);
                                }
                                if (channel[n] == 3){
                                    Run375259_pEM_TS[2][3]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[2][3]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[2][3]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[2][3]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[2][3]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[2][3]->Fill(5.0, TS5[n]);

                                    pEM_ratio[2][3] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[2][3]->Fill(pEM_ratio[2][3]);

                                    //if (pEM_ratio[2][3] > 0.8 && pEM_ratio[2][3] < 1.2){
                                        pEM_signal[2][3] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[2][3]->Fill(pEM_signal[2][3]);
                                }
                                if (channel[n] == 4){
                                    Run375259_pEM_TS[3][3]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[3][3]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[3][3]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[3][3]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[3][3]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[3][3]->Fill(5.0, TS5[n]);

                                    pEM_ratio[3][3] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[3][3]->Fill(pEM_ratio[3][3]);

                                    //if (pEM_ratio[3][3] > 0.8 && pEM_ratio[3][3] < 1.2){
                                        pEM_signal[3][3] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[3][3]->Fill(pEM_signal[3][3]);
                                }
                                if (channel[n] == 5){
                                    Run375259_pEM_TS[4][3]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[4][3]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[4][3]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[4][3]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[4][3]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[4][3]->Fill(5.0, TS5[n]);

                                    pEM_ratio[4][3] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[4][3]->Fill(pEM_ratio[4][3]);

                                    //if (pEM_ratio[4][3] > 0.8 && pEM_ratio[4][3] < 1.2){
                                        pEM_signal[4][3] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[4][3]->Fill(pEM_signal[4][3]);
                                }
                                 pEM_signal_total[3] = (0.6 * pEM_signal[0][3]) + (0.89 * pEM_signal[1][3]) + (1 * pEM_signal[2][3]) + (1.29 * pEM_signal[3][3]) + (0.57 * pEM_signal[4][3]);
                                pEM_signal_col[3] = ((-3.6 * 0.6 * pEM_signal[0][3]) + (-1.8 * 0.89 * pEM_signal[1][3]) + (0 * 1 * pEM_signal[2][3]) + (1.8 * 1.29 * pEM_signal[3][3]) + (3.6 * 0.57 * pEM_signal[4][3])) / pEM_signal_total[3];
                            } // end of side & section
                        
                    
                    if (zside[n] == 1 && section[n] == 2){
                        
                        if (channel[n] == 1){
                            Run375259_pHAD_TS[0][3]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[0][3]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[0][3]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[0][3]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[0][3]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[0][3]->Fill(5.0,TS5[n]);
                            pHAD_ratio[0][3] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[0][3]->Fill(pHAD_ratio[0][3]);
                            //if (pHAD_ratio[0][3] > 3.5 && pHAD_ratio[0][3] < 4){
                                pHAD_signal[0][3] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[0][3]->Fill(pHAD_signal[0][3]);
                        }
                        if (channel[n] == 2){
                            Run375259_pHAD_TS[1][3]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[1][3]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[1][3]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[1][3]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[1][3]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[1][3]->Fill(5.0,TS5[n]);
                            pHAD_ratio[1][3] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[1][3]->Fill(pHAD_ratio[1][3]);
                            //if (pHAD_ratio[1][3] > 3.5 && pHAD_ratio[1][3] < 4.5){
                                pHAD_signal[1][3] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[1][3]->Fill(pHAD_signal[2][3]);
                        }
                        if (channel[n] == 3){
                            Run375259_pHAD_TS[2][3]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[2][3]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[2][3]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[2][3]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[2][3]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[2][3]->Fill(5.0,TS5[n]);
                            pHAD_ratio[2][3] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[2][3]->Fill(pHAD_ratio[2][3]);
                            //if (pHAD_ratio[2][3] > 3.5 && pHAD_ratio[2][3] < 5){
                                pHAD_signal[2][3] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[2][3]->Fill(pHAD_signal[2][3]);
                        }
                        if (channel[n] == 4){
                            Run375259_pHAD_TS[3][3]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[3][3]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[3][3]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[3][3]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[3][3]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[3][3]->Fill(5.0,TS5[n]);
                            pHAD_ratio[3][3] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[3][3]->Fill(pHAD_ratio[3][3]);
                            //if (pHAD_ratio[3][3] > 4 && pHAD_ratio[3][3] < 5){
                                pHAD_signal[3][3] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[3][3]->Fill(pHAD_signal[3][3]);
                        }
                        pHAD_signal_total[3] = pHAD_signal[0][3] + pHAD_signal[1][3] + pHAD_signal[2][3] + pHAD_signal[3][3];
                        } // end  HAD 
                    } //end channel loop
                            Run375259_pRPDx_vs_pEMx[3]->Fill(pRPD_signal_col[3], pEM_signal_col[3]);
                            Run375259_pEM_COMvsCent[3]->Fill(pEM_signal_col[3]);

                            Run375259_pEM_Profile[3]->Fill(0.0 , pEM_signal[0][3]);
                            Run375259_pEM_Profile[3]->Fill(1.0 , pEM_signal[1][3]);
                            Run375259_pEM_Profile[3]->Fill(2.0 , pEM_signal[2][3]);
                            Run375259_pEM_Profile[3]->Fill(3.0 , pEM_signal[3][3]);
                            Run375259_pEM_Profile[3]->Fill(4.0 , pEM_signal[4][3]);

                            Run375259_pRPD_COM[3]->Fill(pRPD_signal_col[3], pRPD_signal_row[3]);

                            pos_rpd_xprojection[3]->Fill(pRPD_signal_col[3]);

                            Run375259_pRPD_prof[3]->Fill(0.0,pRPDX1[3]);
                            Run375259_pRPD_prof[3]->Fill(1.0,pRPDX2[3]);
                            Run375259_pRPD_prof[3]->Fill(2.0,pRPDX3[3]);
                            Run375259_pRPD_prof[3]->Fill(3.0,pRPDX4[3]);

                            Run375259_pRPD_Avg_Y_Sig[3]->Fill(0.0, pRPDY1[3]);
                            Run375259_pRPD_Avg_Y_Sig[3]->Fill(1.0, pRPDY2[3]);
                            Run375259_pRPD_Avg_Y_Sig[3]->Fill(2.0, pRPDY3[3]);
                            Run375259_pRPD_Avg_Y_Sig[3]->Fill(3.0, pRPDY4[3]);

                            Run375259_pRPD_HeatMap[3]->Fill(0.5,3.5,pRPD_signal[0][3]);
                            Run375259_pRPD_HeatMap[3]->Fill(1.5,3.5,pRPD_signal[1][3]);
                            Run375259_pRPD_HeatMap[3]->Fill(2.5,3.5,pRPD_signal[2][3]);
                            Run375259_pRPD_HeatMap[3]->Fill(3.5,3.5,pRPD_signal[3][3]);

                            Run375259_pRPD_HeatMap[3]->Fill(0.5,2.5,pRPD_signal[4][3]);
                            Run375259_pRPD_HeatMap[3]->Fill(1.5,2.5,pRPD_signal[5][3]);
                            Run375259_pRPD_HeatMap[3]->Fill(2.5,2.5,pRPD_signal[6][3]);
                            Run375259_pRPD_HeatMap[3]->Fill(3.5,2.5,pRPD_signal[7][3]);

                            Run375259_pRPD_HeatMap[3]->Fill(0.5,1.5,pRPD_signal[8][3]);
                            Run375259_pRPD_HeatMap[3]->Fill(1.5,1.5,pRPD_signal[9][3]);
                            Run375259_pRPD_HeatMap[3]->Fill(2.5,1.5,pRPD_signal[10][3]);
                            Run375259_pRPD_HeatMap[3]->Fill(3.5,1.5,pRPD_signal[11][3]);

                            Run375259_pRPD_HeatMap[3]->Fill(0.5,0.5,pRPD_signal[12][3]);
                            Run375259_pRPD_HeatMap[3]->Fill(1.5,0.5,pRPD_signal[13][3]);
                            Run375259_pRPD_HeatMap[3]->Fill(2.5,0.5,pRPD_signal[14][3]);
                            Run375259_pRPD_HeatMap[3]->Fill(3.5,0.5,pRPD_signal[15][3]);

                            ZDC[3] = 0.1 * pEM_signal_total[3] + pHAD_signal_total[3];
                            Run375259_pRPD_position_vstotalsignal[3]->Fill(ZDC[3], pRPD_signal_col[3]);
                            Run375259_pEM_position_vstotalsignal[3]->Fill(ZDC[3], pEM_signal_col[3]);
                            Run375259_NeutronPlotProjection[3]->Fill(ZDC[3]);
                            Run375259_NeutronPlot[3]->Fill(ZDC[3],pEM_signal_total[3]);
                } // end of hibin 60 to 80
                if (hibin >=80 && hibin < 100 ){ 
                            for (int n = 0; n < 56; n++) {
                                if (zside[n] == 1 && section[n] == 4) {
                                    if (channel[n] == 1) {
                                    Run375259_pRPD_TS[10][4]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[10][4]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[10][4]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[10][4]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[10][4]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[10][4]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[10][4] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[10][4]->Fill(pRPD_ratio[10][4]);

                                    if (pRPD_ratio[10][4] > 1.5 && pRPD_ratio[10][4] < 2.0) {
                                    pRPD_signal[10][4] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[10][4]->Fill(pRPD_signal[10][4]);
                                    
                                    }
                                    if (channel[n] == 2) {
                                    Run375259_pRPD_TS[6][4]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[6][4]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[6][4]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[6][4]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[6][4]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[6][4]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[6][4] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[6][4]->Fill(pRPD_ratio[6][4]);
                                    
                                    if (pRPD_ratio[6][4] > 1.5 && pRPD_ratio[6][4] < 2.1) {
                                    pRPD_signal[6][4] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[6][4]->Fill(pRPD_signal[6][4]);
                                    
                                    } 
                                    if (channel[n] == 3) {
                                    Run375259_pRPD_TS[2][4]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[2][4]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[2][4]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[2][4]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[2][4]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[2][4]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[2][4] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[2][4]->Fill(pRPD_ratio[2][4]);
                                    
                                    if (pRPD_ratio[2][4] > 1.5 && pRPD_ratio[2][4] < 2.0) {
                                    pRPD_signal[2][4] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[2][4]->Fill(pRPD_signal[2][4]);
                                    
                                    }      
                                    if (channel[n] == 4) {
                                    Run375259_pRPD_TS[14][4]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[14][4]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[14][4]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[14][4]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[14][4]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[14][4]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[14][4] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[14][4]->Fill(pRPD_ratio[14][4]);

                                    if (pRPD_ratio[14][4] > 1.5 && pRPD_ratio[14][4] < 2.0) {
                                    pRPD_signal[14][4] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[14][4]->Fill(pRPD_signal[14][4]);
                                    
                                    }   
                                    if (channel[n] == 5) {
                                    Run375259_pRPD_TS[11][4]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[11][4]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[11][4]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[11][4]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[11][4]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[11][4]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[11][4] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[11][4]->Fill(pRPD_ratio[11][4]);
                                    
                                    if (pRPD_ratio[11][4] > 1.5 && pRPD_ratio[11][4] < 2.1) {
                                    pRPD_signal[11][4] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[11][4]->Fill(pRPD_signal[11][4]);
                                    
                                    }   
                                    if (channel[n] == 6) {
                                    Run375259_pRPD_TS[7][4]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[7][4]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[7][4]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[7][4]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[7][4]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[7][4]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[7][4] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[7][4]->Fill(pRPD_ratio[7][4]);
                                    
                                    if (pRPD_ratio[7][4] > 1.6 && pRPD_ratio[7][4] < 2.4) {
                                    pRPD_signal[7][4] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[7][4]->Fill(pRPD_signal[7][4]);
                                    
                                    }   
                                    if (channel[n] == 7) {
                                    Run375259_pRPD_TS[3][4]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[3][4]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[3][4]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[3][4]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[3][4]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[3][4]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[3][4] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[3][4]->Fill(pRPD_ratio[3][4]);
                                    
                                    if (pRPD_ratio[3][4] > 1.5 && pRPD_ratio[3][4] < 2.4) {
                                    pRPD_signal[3][4] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[3][4]->Fill(pRPD_signal[3][4]);
                                    
                                    }   
                                    if (channel[n] == 8) {
                                    Run375259_pRPD_TS[15][4]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[15][4]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[15][4]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[15][4]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[15][4]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[15][4]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[15][4] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[15][4]->Fill(pRPD_ratio[15][4]);

                                    if (pRPD_ratio[15][4] > 1.6 && pRPD_ratio[15][4] < 2.2) {
                                    pRPD_signal[15][4] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[15][4]->Fill(pRPD_signal[15][4]);
                                    }   
                                    if (channel[n] == 9) {
                                    Run375259_pRPD_TS[4][4]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[4][4]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[4][4]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[4][4]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[4][4]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[4][4]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[4][4] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[4][4]->Fill(pRPD_ratio[4][4]);

                                    if (pRPD_ratio[4][4] > 1.5 && pRPD_ratio[4][4] < 2.4 ) {
                                    pRPD_signal[4][4] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[4][4]->Fill(pRPD_signal[4][4]);
                                    }   
                                    if (channel[n] == 10) {
                                    Run375259_pRPD_TS[8][4]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[8][4]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[8][4]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[8][4]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[8][4]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[8][4]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[8][4] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[8][4]->Fill(pRPD_ratio[8][4]);

                                    if (pRPD_ratio[8][4] > 1.5 && pRPD_ratio[8][4] < 2.3) {
                                    pRPD_signal[8][4] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[8][4]->Fill(pRPD_signal[8][4]);
                                    }   
                                    if (channel[n] == 11) {
                                    Run375259_pRPD_TS[12][4]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[12][4]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[12][4]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[12][4]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[12][4]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[12][4]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[12][4] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[12][4]->Fill(pRPD_ratio[12][4]);

                                    if (pRPD_ratio[12][4] > 1.5 && pRPD_ratio[12][4] < 2.2){
                                    pRPD_signal[12][4] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[12][4]->Fill(pRPD_signal[12][4]);
                                    }   
                                    if (channel[n] == 12) {
                                    Run375259_pRPD_TS[0][4]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[0][4]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[0][4]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[0][4]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[0][4]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[0][4]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[0][4] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[0][4]->Fill(pRPD_ratio[0][4]);

                                    if (pRPD_ratio[0][4] > 1.5 && pRPD_ratio[0][4] < 2.3){
                                    pRPD_signal[0][4] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[0][4]->Fill(pRPD_signal[0][4]);
                                    }   
                                    if (channel[n] == 13) {
                                    Run375259_pRPD_TS[5][4]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[5][4]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[5][4]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[5][4]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[5][4]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[5][4]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[5][4] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[5][4]->Fill(pRPD_ratio[5][4]);

                                    if (pRPD_ratio[5][4] > 1.7 && pRPD_ratio[5][4] < 2.5){
                                    pRPD_signal[5][4] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[5][4]->Fill(pRPD_signal[5][4]);
                                    }   
                                    if (channel[n] == 14) {
                                    Run375259_pRPD_TS[9][4]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[9][4]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[9][4]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[9][4]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[9][4]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[9][4]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[9][4] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[9][4]->Fill(pRPD_ratio[9][4]);
                                    
                                    if (pRPD_ratio[9][4] > 1.6 && pRPD_ratio[9][4] < 2.4) {
                                    pRPD_signal[9][4] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[9][4]->Fill(pRPD_signal[9][4]);
                                    }   
                                    if (channel[n] == 15) {
                                    Run375259_pRPD_TS[13][4]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[13][4]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[13][4]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[13][4]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[13][4]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[13][4]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[13][4] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[13][4]->Fill(pRPD_ratio[13][4]);

                                    if (pRPD_ratio[13][4] > 1.6 && pRPD_ratio[13][4] < 2.4) {
                                    pRPD_signal[13][4] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[13][4]->Fill(pRPD_signal[13][4]);
                                    }   
                                    if (channel[n] == 16) {
                                    Run375259_pRPD_TS[1][4]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[1][4]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[1][4]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[1][4]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[1][4]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[1][4]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[1][4] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[1][4]->Fill(pRPD_ratio[1][4]);

                                    if (pRPD_ratio[1][4] > 1.5 && pRPD_ratio[1][4] < 2.5) {
                                    pRPD_signal[1][4] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[1][4]->Fill(pRPD_signal[1][4]);
                                    }            
                                    pRPDX1[4] = pRPD_signal[0][4] + pRPD_signal[4][4] + pRPD_signal[8][4] + pRPD_signal[12][4];                   
                                    pRPDX2[4] = pRPD_signal[1][4] + pRPD_signal[5][4] + pRPD_signal[9][4] + pRPD_signal[13][4];  
                                    pRPDX3[4] = pRPD_signal[2][4] + pRPD_signal[6][4] + pRPD_signal[10][4] + pRPD_signal[14][4];  
                                    pRPDX4[4] = pRPD_signal[3][4] + pRPD_signal[7][4] + pRPD_signal[11][4] + pRPD_signal[15][4];  

                                    pRPDY1[4] = pRPD_signal[0][4] + pRPD_signal[1][4] + pRPD_signal[2][4] + pRPD_signal[3][4];  
                                    pRPDY2[4] = pRPD_signal[4][4] + pRPD_signal[5][4] + pRPD_signal[6][4] + pRPD_signal[7][4];  
                                    pRPDY3[4] = pRPD_signal[8][4] + pRPD_signal[9][4] + pRPD_signal[10][4] + pRPD_signal[11][4];  
                                    pRPDY4[4] = pRPD_signal[12][4] + pRPD_signal[13][4] + pRPD_signal[14][4] + pRPD_signal[15][4];  

                                    pRPD_signal_total[4] = pRPDX1[4] + pRPDX2[4] + pRPDX3[4] + pRPDX4[4];

                                    pRPD_signal_col[4] = ((-3*pRPDX1[4]) + (-1*pRPDX2[4]) + (1*pRPDX3[4]) + (3*pRPDX4[4])) / pRPD_signal_total[4];
                                    pRPD_signal_row[4] = ((-3*pRPDY4[4]) + (-1*pRPDY3[4]) + (1*pRPDY2[4]) + (3*pRPDY1[4])) / pRPD_signal_total[4];

                                } // end of side and section
                            
                                if (zside[n] == 1 && section[n] == 1) {
                                if (channel[n] == 1) {
                                    Run375259_pEM_TS[0][4]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[0][4]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[0][4]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[0][4]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[0][4]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[0][4]->Fill(5.0, TS5[n]);

                                    pEM_ratio[0][4] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[0][4]->Fill(pEM_ratio[0][4]);

                                    //if (pEM_ratio[0][4] > 0.8 && pEM_ratio[0][4] < 1.2){
                                        pEM_signal[0][4] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[0][4]->Fill(pEM_signal[0][4]);

                                }
                                if (channel[n] == 2) {
                                    Run375259_pEM_TS[1][4]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[1][4]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[1][4]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[1][4]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[1][4]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[1][4]->Fill(5.0, TS5[n]);

                                    pEM_ratio[1][4] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[1][4]->Fill(pEM_ratio[1][4]);

                                    //if (pEM_ratio[1][4] > 0.8 && pEM_ratio[1][4] < 1.2){
                                        pEM_signal[1][4] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[1][4]->Fill(pEM_signal[1][4]);
                                }
                                if (channel[n] == 3){
                                    Run375259_pEM_TS[2][4]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[2][4]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[2][4]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[2][4]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[2][4]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[2][4]->Fill(5.0, TS5[n]);

                                    pEM_ratio[2][4] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[2][4]->Fill(pEM_ratio[2][4]);

                                    //if (pEM_ratio[2][4] > 0.8 && pEM_ratio[2][4] < 1.2){
                                        pEM_signal[2][4] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[2][4]->Fill(pEM_signal[2][4]);
                                }
                                if (channel[n] == 4){
                                    Run375259_pEM_TS[3][4]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[3][4]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[3][4]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[3][4]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[3][4]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[3][4]->Fill(5.0, TS5[n]);

                                    pEM_ratio[3][4] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[3][4]->Fill(pEM_ratio[3][4]);

                                    //if (pEM_ratio[3][4] > 0.8 && pEM_ratio[3][4] < 1.2){
                                        pEM_signal[3][4] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[3][4]->Fill(pEM_signal[3][4]);
                                }
                                if (channel[n] == 5){
                                    Run375259_pEM_TS[4][4]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[4][4]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[4][4]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[4][4]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[4][4]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[4][4]->Fill(5.0, TS5[n]);

                                    pEM_ratio[4][4] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[4][4]->Fill(pEM_ratio[4][4]);

                                    //if (pEM_ratio[4][4] > 0.8 && pEM_ratio[4][4] < 1.2){
                                        pEM_signal[4][4] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[4][4]->Fill(pEM_signal[4][4]);
                                }
                                 pEM_signal_total[4] = (0.6 * pEM_signal[0][4]) + (0.89 * pEM_signal[1][4]) + (1 * pEM_signal[2][4]) + (1.29 * pEM_signal[3][4]) + (0.57 * pEM_signal[4][4]);
                                pEM_signal_col[4] = ((-3.6 * 0.6 * pEM_signal[0][4]) + (-1.8 * 0.89 * pEM_signal[1][4]) + (0 * 1 * pEM_signal[2][4]) + (1.8 * 1.29 * pEM_signal[3][4]) + (3.6 * 0.57 * pEM_signal[4][4])) / pEM_signal_total[4];
                            } // end of side & section
                        
                    if (zside[n] == 1 && section[n] == 2){
                        
                        if (channel[n] == 1){
                            Run375259_pHAD_TS[0][4]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[0][4]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[0][4]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[0][4]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[0][4]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[0][4]->Fill(5.0,TS5[n]);
                            pHAD_ratio[0][4] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[0][4]->Fill(pHAD_ratio[0][4]);
                            //if (pHAD_ratio[0][4] > 3.5 && pHAD_ratio[0][4] < 4){
                                pHAD_signal[0][4] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[0][4]->Fill(pHAD_signal[0][4]);
                        }
                        if (channel[n] == 2){
                            Run375259_pHAD_TS[1][4]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[1][4]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[1][4]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[1][4]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[1][4]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[1][4]->Fill(5.0,TS5[n]);
                            pHAD_ratio[1][4] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[1][4]->Fill(pHAD_ratio[1][4]);
                            //if (pHAD_ratio[1][4] > 3.5 && pHAD_ratio[1][4] < 4.5){
                                pHAD_signal[1][4] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[1][4]->Fill(pHAD_signal[1][4]);
                        }
                        if (channel[n] == 3){
                            Run375259_pHAD_TS[2][4]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[2][4]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[2][4]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[2][4]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[2][4]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[2][4]->Fill(5.0,TS5[n]);
                            pHAD_ratio[2][4] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[2][4]->Fill(pHAD_ratio[2][4]);
                            //if (pHAD_ratio[2][4] > 3.5 && pHAD_ratio[2][4] < 5){
                                pHAD_signal[2][4] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[2][4]->Fill(pHAD_signal[2][4]);
                        }
                        if (channel[n] == 4){
                            Run375259_pHAD_TS[3][4]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[3][4]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[3][4]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[3][4]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[3][4]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[3][4]->Fill(5.0,TS5[n]);
                            pHAD_ratio[3][4] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[3][4]->Fill(pHAD_ratio[3][4]);
                            //if (pHAD_ratio[3][4] > 4 && pHAD_ratio[3][4] < 5){
                                pHAD_signal[3][4] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[3][4]->Fill(pHAD_signal[3][4]);
                        }
                        pHAD_signal_total[4] = pHAD_signal[0][4] + pHAD_signal[1][4] + pHAD_signal[2][4] + pHAD_signal[3][4];
                        } // end  HAD 
                    } //end channel loop
                    Run375259_pEM_COMvsCent[4]->Fill(pEM_signal_col[4]);
                        Run375259_pEM_Profile[4]->Fill(0.0 , pEM_signal[0][4]);
                        Run375259_pEM_Profile[4]->Fill(1.0 , pEM_signal[1][4]);
                        Run375259_pEM_Profile[4]->Fill(2.0 , pEM_signal[2][4]);
                        Run375259_pEM_Profile[4]->Fill(3.0 , pEM_signal[3][4]);
                        Run375259_pEM_Profile[4]->Fill(4.0 , pEM_signal[4][4]);
                    Run375259_pRPDx_vs_pEMx[4]->Fill(pRPD_signal_col[4], pEM_signal_col[4]);
                    Run375259_pRPD_COM[4]->Fill(pRPD_signal_col[4], pRPD_signal_row[4]);
                            pos_rpd_xprojection[4]->Fill(pRPD_signal_col[4]);
                            Run375259_pRPD_prof[4]->Fill(0.0,pRPDX1[4]);
                            Run375259_pRPD_prof[4]->Fill(1.0,pRPDX2[4]);
                            Run375259_pRPD_prof[4]->Fill(2.0,pRPDX3[4]);
                            Run375259_pRPD_prof[4]->Fill(3.0,pRPDX4[4]);

                            Run375259_pRPD_Avg_Y_Sig[4]->Fill(0.0, pRPDY1[4]);
                            Run375259_pRPD_Avg_Y_Sig[4]->Fill(1.0, pRPDY2[4]);
                            Run375259_pRPD_Avg_Y_Sig[4]->Fill(2.0, pRPDY3[4]);
                            Run375259_pRPD_Avg_Y_Sig[4]->Fill(3.0, pRPDY4[4]);

                            Run375259_pRPD_HeatMap[4]->Fill(0.5,3.5,pRPD_signal[0][4]);
                            Run375259_pRPD_HeatMap[4]->Fill(1.5,3.5,pRPD_signal[1][4]);
                            Run375259_pRPD_HeatMap[4]->Fill(2.5,3.5,pRPD_signal[2][4]);
                            Run375259_pRPD_HeatMap[4]->Fill(3.5,3.5,pRPD_signal[3][4]);

                            Run375259_pRPD_HeatMap[4]->Fill(0.5,2.5,pRPD_signal[4][4]);
                            Run375259_pRPD_HeatMap[4]->Fill(1.5,2.5,pRPD_signal[5][4]);
                            Run375259_pRPD_HeatMap[4]->Fill(2.5,2.5,pRPD_signal[6][4]);
                            Run375259_pRPD_HeatMap[4]->Fill(3.5,2.5,pRPD_signal[7][4]);

                            Run375259_pRPD_HeatMap[4]->Fill(0.5,1.5,pRPD_signal[8][4]);
                            Run375259_pRPD_HeatMap[4]->Fill(1.5,1.5,pRPD_signal[9][4]);
                            Run375259_pRPD_HeatMap[4]->Fill(2.5,1.5,pRPD_signal[10][4]);
                            Run375259_pRPD_HeatMap[4]->Fill(3.5,1.5,pRPD_signal[11][4]);

                            Run375259_pRPD_HeatMap[4]->Fill(0.5,0.5,pRPD_signal[12][4]);
                            Run375259_pRPD_HeatMap[4]->Fill(1.5,0.5,pRPD_signal[13][4]);
                            Run375259_pRPD_HeatMap[4]->Fill(2.5,0.5,pRPD_signal[14][4]);
                            Run375259_pRPD_HeatMap[4]->Fill(3.5,0.5,pRPD_signal[15][4]);
                    ZDC[4] = 0.1 * pEM_signal_total[4] + pHAD_signal_total[4];
                    Run375259_pRPD_position_vstotalsignal[4]->Fill(ZDC[4], pRPD_signal_col[4]);
                    Run375259_pEM_position_vstotalsignal[4]->Fill(ZDC[4], pEM_signal_col[4]);
                    Run375259_NeutronPlotProjection[4]->Fill(ZDC[4]);
                    Run375259_NeutronPlot[4]->Fill(ZDC[4],pEM_signal_total[4]);
                } // end of hibin 
                if (hibin >=100 && hibin < 120 ){ 
                            for (int n = 0; n < 56; n++) {
                                if (zside[n] == 1 && section[n] == 4) {
                                    if (channel[n] == 1) {
                                    Run375259_pRPD_TS[10][5]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[10][5]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[10][5]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[10][5]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[10][5]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[10][5]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[10][5] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[10][5]->Fill(pRPD_ratio[10][5]);

                                    if (pRPD_ratio[10][5] > 1.5 && pRPD_ratio[10][5] < 2.0) {
                                    pRPD_signal[10][5] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[10][5]->Fill(pRPD_signal[10][5]);
                                    
                                    }
                                    if (channel[n] == 2) {
                                    Run375259_pRPD_TS[6][5]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[6][5]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[6][5]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[6][5]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[6][5]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[6][5]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[6][5] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[6][5]->Fill(pRPD_ratio[6][5]);
                                    
                                    if (pRPD_ratio[6][5] > 1.5 && pRPD_ratio[6][5] < 2.1) {
                                    pRPD_signal[6][5] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[6][5]->Fill(pRPD_signal[6][5]);
                                    
                                    } 
                                    if (channel[n] == 3) {
                                    Run375259_pRPD_TS[2][5]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[2][5]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[2][5]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[2][5]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[2][5]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[2][5]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[2][5] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[2][5]->Fill(pRPD_ratio[2][5]);
                                    
                                    if (pRPD_ratio[2][5] > 1.5 && pRPD_ratio[2][5] < 2.0) {
                                    pRPD_signal[2][5] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[2][5]->Fill(pRPD_signal[2][5]);
                                    
                                    }      
                                    if (channel[n] == 4) {
                                    Run375259_pRPD_TS[14][5]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[14][5]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[14][5]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[14][5]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[14][5]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[14][5]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[14][5] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[14][5]->Fill(pRPD_ratio[14][5]);

                                    if (pRPD_ratio[14][5] > 1.5 && pRPD_ratio[14][5] < 2.0) {
                                    pRPD_signal[14][5] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[14][5]->Fill(pRPD_signal[14][5]);
                                    
                                    }   
                                    if (channel[n] == 5) {
                                    Run375259_pRPD_TS[11][5]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[11][5]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[11][5]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[11][5]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[11][5]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[11][5]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[11][5] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[11][5]->Fill(pRPD_ratio[11][5]);
                                    
                                    if (pRPD_ratio[11][5] > 1.5 && pRPD_ratio[11][5] < 2.1) {
                                    pRPD_signal[11][5] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[11][5]->Fill(pRPD_signal[11][5]);
                                    
                                    }   
                                    if (channel[n] == 6) {
                                    Run375259_pRPD_TS[7][5]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[7][5]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[7][5]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[7][5]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[7][5]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[7][5]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[7][5] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[7][5]->Fill(pRPD_ratio[7][5]);
                                    
                                    if (pRPD_ratio[7][5] > 1.6 && pRPD_ratio[7][5] < 2.4) {
                                    pRPD_signal[7][5] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[7][5]->Fill(pRPD_signal[7][5]);
                                    
                                    }   
                                    if (channel[n] == 7) {
                                    Run375259_pRPD_TS[3][5]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[3][5]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[3][5]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[3][5]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[3][5]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[3][5]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[3][5] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[3][5]->Fill(pRPD_ratio[3][5]);
                                    
                                    if (pRPD_ratio[3][5] > 1.5 && pRPD_ratio[3][5] < 2.4) {
                                    pRPD_signal[3][5] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[3][5]->Fill(pRPD_signal[3][5]);
                                    
                                    }   
                                    if (channel[n] == 8) {
                                    Run375259_pRPD_TS[15][5]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[15][5]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[15][5]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[15][5]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[15][5]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[15][5]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[15][5] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[15][5]->Fill(pRPD_ratio[15][5]);

                                    if (pRPD_ratio[15][5] > 1.6 && pRPD_ratio[15][5] < 2.2) {
                                    pRPD_signal[15][5] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[15][5]->Fill(pRPD_signal[15][5]);
                                    }   
                                    if (channel[n] == 9) {
                                    Run375259_pRPD_TS[4][5]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[4][5]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[4][5]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[4][5]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[4][5]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[4][5]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[4][5] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[4][5]->Fill(pRPD_ratio[4][5]);

                                    if (pRPD_ratio[4][5] > 1.5 && pRPD_ratio[4][5] < 2.4 ) {
                                    pRPD_signal[4][5] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[4][5]->Fill(pRPD_signal[4][5]);
                                    }   
                                    if (channel[n] == 10) {
                                    Run375259_pRPD_TS[8][5]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[8][5]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[8][5]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[8][5]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[8][5]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[8][5]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[8][5] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[8][5]->Fill(pRPD_ratio[8][5]);

                                    if (pRPD_ratio[8][5] > 1.5 && pRPD_ratio[8][5] < 2.3) {
                                    pRPD_signal[8][5] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[8][5]->Fill(pRPD_signal[8][5]);
                                    }   
                                    if (channel[n] == 11) {
                                    Run375259_pRPD_TS[12][5]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[12][5]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[12][5]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[12][5]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[12][5]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[12][5]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[12][5] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[12][5]->Fill(pRPD_ratio[12][5]);

                                    if (pRPD_ratio[12][5] > 1.5 && pRPD_ratio[12][5] < 2.2){
                                    pRPD_signal[12][5] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[12][5]->Fill(pRPD_signal[12][5]);
                                    }   
                                    if (channel[n] == 12) {
                                    Run375259_pRPD_TS[0][5]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[0][5]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[0][5]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[0][5]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[0][5]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[0][5]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[0][5] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[0][5]->Fill(pRPD_ratio[0][5]);

                                    if (pRPD_ratio[0][5] > 1.5 && pRPD_ratio[0][5] < 2.3){
                                    pRPD_signal[0][5] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[0][5]->Fill(pRPD_signal[0][5]);
                                    }   
                                    if (channel[n] == 13) {
                                    Run375259_pRPD_TS[5][5]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[5][5]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[5][5]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[5][5]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[5][5]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[5][5]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[5][5] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[5][5]->Fill(pRPD_ratio[5][5]);

                                    if (pRPD_ratio[5][5] > 1.7 && pRPD_ratio[5][5] < 2.5){
                                    pRPD_signal[5][5] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[5][5]->Fill(pRPD_signal[5][5]);
                                    }   
                                    if (channel[n] == 14) {
                                    Run375259_pRPD_TS[9][5]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[9][5]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[9][5]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[9][5]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[9][5]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[9][5]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[9][5] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[9][5]->Fill(pRPD_ratio[9][5]);
                                    
                                    if (pRPD_ratio[9][5] > 1.6 && pRPD_ratio[9][5] < 2.4) {
                                    pRPD_signal[9][5] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[9][5]->Fill(pRPD_signal[9][5]);
                                    }   
                                    if (channel[n] == 15) {
                                    Run375259_pRPD_TS[13][5]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[13][5]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[13][5]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[13][5]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[13][5]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[13][5]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[13][5] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[13][5]->Fill(pRPD_ratio[13][5]);

                                    if (pRPD_ratio[13][5] > 1.6 && pRPD_ratio[13][5] < 2.4) {
                                    pRPD_signal[13][5] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[13][5]->Fill(pRPD_signal[13][5]);
                                    }   
                                    if (channel[n] == 16) {
                                    Run375259_pRPD_TS[1][5]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[1][5]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[1][5]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[1][5]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[1][5]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[1][5]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[1][5] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[1][5]->Fill(pRPD_ratio[1][5]);

                                    if (pRPD_ratio[1][5] > 1.5 && pRPD_ratio[1][5] < 2.5) {
                                    pRPD_signal[1][5] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[1][5]->Fill(pRPD_signal[1][5]);
                                    }            
                                    pRPDX1[5] = pRPD_signal[0][5] + pRPD_signal[4][5] + pRPD_signal[8][5] + pRPD_signal[12][5];                   
                                    pRPDX2[5] = pRPD_signal[1][5] + pRPD_signal[5][5] + pRPD_signal[9][5] + pRPD_signal[13][5];  
                                    pRPDX3[5] = pRPD_signal[2][5] + pRPD_signal[6][5] + pRPD_signal[10][5] + pRPD_signal[14][5];  
                                    pRPDX4[5] = pRPD_signal[3][5] + pRPD_signal[7][5] + pRPD_signal[11][5] + pRPD_signal[15][5];  

                                    pRPDY1[5] = pRPD_signal[0][5] + pRPD_signal[1][5] + pRPD_signal[2][5] + pRPD_signal[3][5];  
                                    pRPDY2[5] = pRPD_signal[4][5] + pRPD_signal[5][5] + pRPD_signal[6][5] + pRPD_signal[7][5];  
                                    pRPDY3[5] = pRPD_signal[8][5] + pRPD_signal[9][5] + pRPD_signal[10][5] + pRPD_signal[11][5];  
                                    pRPDY4[5] = pRPD_signal[12][5] + pRPD_signal[13][5] + pRPD_signal[14][5] + pRPD_signal[15][5];  

                                    pRPD_signal_total[5] = pRPDX1[5] + pRPDX2[5] + pRPDX3[5] + pRPDX4[5];

                                    pRPD_signal_col[5] = ((-3*pRPDX1[5]) + (-1*pRPDX2[5]) + (1*pRPDX3[5]) + (3*pRPDX4[5])) / pRPD_signal_total[5];
                                    pRPD_signal_row[5] = ((-3*pRPDY4[5]) + (-1*pRPDY3[5]) + (1*pRPDY2[5]) + (3*pRPDY1[5])) / pRPD_signal_total[5];

                                } // end of side and section
                            
                                if (zside[n] == 1 && section[n] == 1) {
                                if (channel[n] == 1) {
                                    Run375259_pEM_TS[0][5]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[0][5]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[0][5]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[0][5]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[0][5]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[0][5]->Fill(5.0, TS5[n]);

                                    pEM_ratio[0][5] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[0][5]->Fill(pEM_ratio[0][5]);

                                    //if (pEM_ratio[0][5] > 0.8 && pEM_ratio[0][5] < 1.2){
                                        pEM_signal[0][5] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[0][5]->Fill(pEM_signal[0][5]);
                                }
                                if (channel[n] == 2) {
                                    Run375259_pEM_TS[1][5]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[1][5]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[1][5]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[1][5]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[1][5]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[1][5]->Fill(5.0, TS5[n]);

                                    pEM_ratio[1][5] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[1][5]->Fill(pEM_ratio[1][5]);

                                    //if (pEM_ratio[1][5] > 0.8 && pEM_ratio[1][5] < 1.2){
                                        pEM_signal[1][5] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[1][5]->Fill(pEM_signal[1][5]);
                                }
                                if (channel[n] == 3){
                                    Run375259_pEM_TS[2][5]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[2][5]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[2][5]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[2][5]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[2][5]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[2][5]->Fill(5.0, TS5[n]);

                                    pEM_ratio[2][5] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[2][5]->Fill(pEM_ratio[2][5]);

                                    //if (pEM_ratio[2][5] > 0.8 && pEM_ratio[2][5] < 1.2){
                                        pEM_signal[2][5] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[2][5]->Fill(pEM_signal[2][5]);
                                }
                                if (channel[n] == 4){
                                    Run375259_pEM_TS[3][5]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[3][5]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[3][5]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[3][5]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[3][5]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[3][5]->Fill(5.0, TS5[n]);

                                    pEM_ratio[3][5] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[3][5]->Fill(pEM_ratio[3][5]);

                                    //if (pEM_ratio[3][5] > 0.8 && pEM_ratio[3][5] < 1.2){
                                        pEM_signal[3][5] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[3][5]->Fill(pEM_signal[3][5]);
                                }
                                if (channel[n] == 5){
                                    Run375259_pEM_TS[4][5]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[4][5]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[4][5]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[4][5]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[4][5]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[4][5]->Fill(5.0, TS5[n]);

                                    pEM_ratio[4][5] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[4][5]->Fill(pEM_ratio[4][5]);

                                    //if (pEM_ratio[4][5] > 0.8 && pEM_ratio[4][5] < 1.2){
                                        pEM_signal[4][5] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[4][5]->Fill(pEM_signal[4][5]);
                                }
                                 pEM_signal_total[5] = (0.6 * pEM_signal[0][5]) + (0.89 * pEM_signal[1][5]) + (1 * pEM_signal[2][5]) + (1.29 * pEM_signal[3][5]) + (0.57 * pEM_signal[4][5]);
                                pEM_signal_col[5] = ((-3.6 * 0.6 * pEM_signal[0][5]) + (-1.8 * 0.89 * pEM_signal[1][5]) + (0 * 1 * pEM_signal[2][5]) + (1.8 * 1.29 * pEM_signal[3][5]) + (3.6 * 0.57 * pEM_signal[4][5])) / pEM_signal_total[5];
                            } // end of side & section
                        
                    Run375259_pRPDx_vs_pEMx[5]->Fill(pRPD_signal_col[5], pEM_signal_col[5]);
                    if (zside[n] == 1 && section[n] == 2){
                        
                        if (channel[n] == 1){
                            Run375259_pHAD_TS[0][5]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[0][5]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[0][5]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[0][5]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[0][5]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[0][5]->Fill(5.0,TS5[n]);
                            pHAD_ratio[0][5] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[0][5]->Fill(pHAD_ratio[0][5]);
                            //if (pHAD_ratio[0][5] > 3.5 && pHAD_ratio[0][5] < 4){
                                pHAD_signal[0][5] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[0][5]->Fill(pHAD_signal[0][5]);
                        }
                        if (channel[n] == 2){
                            Run375259_pHAD_TS[1][5]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[1][5]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[1][5]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[1][5]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[1][5]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[1][5]->Fill(5.0,TS5[n]);
                            pHAD_ratio[1][5] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[1][5]->Fill(pHAD_ratio[1][5]);
                            //if (pHAD_ratio[1][5] > 3.5 && pHAD_ratio[1][5] < 4.5){
                                pHAD_signal[1][5] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[1][5]->Fill(pHAD_signal[1][5]);
                        }
                        if (channel[n] == 3){
                            Run375259_pHAD_TS[2][5]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[2][5]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[2][5]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[2][5]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[2][5]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[2][5]->Fill(5.0,TS5[n]);
                            pHAD_ratio[2][5] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[2][5]->Fill(pHAD_ratio[2][5]);
                            //if (pHAD_ratio[2][5] > 3.5 && pHAD_ratio[2][5] < 5){
                                pHAD_signal[2][5] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[2][5]->Fill(pHAD_signal[2][5]);
                        }
                        if (channel[n] == 4){
                            Run375259_pHAD_TS[3][5]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[3][5]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[3][5]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[3][5]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[3][5]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[3][5]->Fill(5.0,TS5[n]);
                            pHAD_ratio[3][5] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[3][5]->Fill(pHAD_ratio[3][5]);
                            //if (pHAD_ratio[3][5] > 4 && pHAD_ratio[3][5] < 5){
                                pHAD_signal[3][5] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[3][5]->Fill(pHAD_signal[3][5]);
                        }
                        pHAD_signal_total[5] = pHAD_signal[0][5] + pHAD_signal[1][5] + pHAD_signal[2][5] + pHAD_signal[3][5];
                    
                        } // end  HAD 
                    } //end channel loop
                    Run375259_pEM_COMvsCent[5]->Fill(pEM_signal_col[5]);
                        Run375259_pEM_Profile[5]->Fill(0.0 , pEM_signal[0][5]);
                        Run375259_pEM_Profile[5]->Fill(1.0 , pEM_signal[1][5]);
                        Run375259_pEM_Profile[5]->Fill(2.0 , pEM_signal[2][5]);
                        Run375259_pEM_Profile[5]->Fill(3.0 , pEM_signal[3][5]);
                        Run375259_pEM_Profile[5]->Fill(4.0 , pEM_signal[4][5]);
                    Run375259_pRPD_COM[5]->Fill(pRPD_signal_col[5], pRPD_signal_row[5]);
                            pos_rpd_xprojection[5]->Fill(pRPD_signal_col[5]);
                            Run375259_pRPD_prof[5]->Fill(0.0,pRPDX1[5]);
                            Run375259_pRPD_prof[5]->Fill(1.0,pRPDX2[5]);
                            Run375259_pRPD_prof[5]->Fill(2.0,pRPDX3[5]);
                            Run375259_pRPD_prof[5]->Fill(3.0,pRPDX4[5]);

                            Run375259_pRPD_Avg_Y_Sig[5]->Fill(0.0, pRPDY1[5]);
                            Run375259_pRPD_Avg_Y_Sig[5]->Fill(1.0, pRPDY2[5]);
                            Run375259_pRPD_Avg_Y_Sig[5]->Fill(2.0, pRPDY3[5]);
                            Run375259_pRPD_Avg_Y_Sig[5]->Fill(3.0, pRPDY4[5]);

                            Run375259_pRPD_HeatMap[5]->Fill(0.5,3.5,pRPD_signal[0][5]);
                            Run375259_pRPD_HeatMap[5]->Fill(1.5,3.5,pRPD_signal[1][5]);
                            Run375259_pRPD_HeatMap[5]->Fill(2.5,3.5,pRPD_signal[2][5]);
                            Run375259_pRPD_HeatMap[5]->Fill(3.5,3.5,pRPD_signal[3][5]);

                            Run375259_pRPD_HeatMap[5]->Fill(0.5,2.5,pRPD_signal[4][5]);
                            Run375259_pRPD_HeatMap[5]->Fill(1.5,2.5,pRPD_signal[5][5]);
                            Run375259_pRPD_HeatMap[5]->Fill(2.5,2.5,pRPD_signal[6][5]);
                            Run375259_pRPD_HeatMap[5]->Fill(3.5,2.5,pRPD_signal[7][5]);

                            Run375259_pRPD_HeatMap[5]->Fill(0.5,1.5,pRPD_signal[8][5]);
                            Run375259_pRPD_HeatMap[5]->Fill(1.5,1.5,pRPD_signal[9][5]);
                            Run375259_pRPD_HeatMap[5]->Fill(2.5,1.5,pRPD_signal[10][5]);
                            Run375259_pRPD_HeatMap[5]->Fill(3.5,1.5,pRPD_signal[11][5]);

                            Run375259_pRPD_HeatMap[5]->Fill(0.5,0.5,pRPD_signal[12][5]);
                            Run375259_pRPD_HeatMap[5]->Fill(1.5,0.5,pRPD_signal[13][5]);
                            Run375259_pRPD_HeatMap[5]->Fill(2.5,0.5,pRPD_signal[14][5]);
                            Run375259_pRPD_HeatMap[5]->Fill(3.5,0.5,pRPD_signal[15][5]);
                    ZDC[5] = 0.1 * pEM_signal_total[5] + pHAD_signal_total[5];
                    Run375259_pRPD_position_vstotalsignal[5]->Fill(ZDC[5], pRPD_signal_col[5]);
                    Run375259_pEM_position_vstotalsignal[5]->Fill(ZDC[5], pEM_signal_col[5]);
                    Run375259_NeutronPlotProjection[5]->Fill(ZDC[5]);
                    Run375259_NeutronPlot[5]->Fill(ZDC[5],pEM_signal_total[5]);
                } // end of hibin 100 to 120
                if (hibin >=120 && hibin < 140 ){ 
                            for (int n = 0; n < 56; n++) {
                                if (zside[n] == 1 && section[n] == 4) {
                                    if (channel[n] == 1) {
                                    Run375259_pRPD_TS[10][6]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[10][6]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[10][6]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[10][6]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[10][6]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[10][6]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[10][6] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[10][6]->Fill(pRPD_ratio[10][6]);

                                    if (pRPD_ratio[10][6] > 1.5 && pRPD_ratio[10][6] < 2.0) {
                                    pRPD_signal[10][6] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[10][6]->Fill(pRPD_signal[10][6]);
                                    
                                    }
                                    if (channel[n] == 2) {
                                    Run375259_pRPD_TS[6][6]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[6][6]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[6][6]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[6][6]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[6][6]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[6][6]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[6][6] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[6][6]->Fill(pRPD_ratio[6][6]);
                                    
                                    if (pRPD_ratio[6][6] > 1.5 && pRPD_ratio[6][6] < 2.1) {
                                    pRPD_signal[6][6] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[6][6]->Fill(pRPD_signal[6][6]);
                                    
                                    } 
                                    if (channel[n] == 3) {
                                    Run375259_pRPD_TS[2][6]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[2][6]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[2][6]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[2][6]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[2][6]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[2][6]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[2][6] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[2][6]->Fill(pRPD_ratio[2][6]);
                                    
                                    if (pRPD_ratio[2][6] > 1.5 && pRPD_ratio[2][6] < 2.0) {
                                    pRPD_signal[2][6] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[2][6]->Fill(pRPD_signal[2][6]);
                                    
                                    }      
                                    if (channel[n] == 4) {
                                    Run375259_pRPD_TS[14][6]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[14][6]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[14][6]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[14][6]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[14][6]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[14][6]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[14][6] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[14][6]->Fill(pRPD_ratio[14][6]);

                                    if (pRPD_ratio[14][6] > 1.5 && pRPD_ratio[14][6] < 2.0) {
                                    pRPD_signal[14][6] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[14][6]->Fill(pRPD_signal[14][6]);
                                    
                                    }   
                                    if (channel[n] == 5) {
                                    Run375259_pRPD_TS[11][6]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[11][6]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[11][6]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[11][6]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[11][6]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[11][6]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[11][6] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[11][6]->Fill(pRPD_ratio[11][6]);
                                    
                                    if (pRPD_ratio[11][6] > 1.5 && pRPD_ratio[11][6] < 2.1) {
                                    pRPD_signal[11][6] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[11][6]->Fill(pRPD_signal[11][6]);
                                    
                                    }   
                                    if (channel[n] == 6) {
                                    Run375259_pRPD_TS[7][6]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[7][6]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[7][6]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[7][6]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[7][6]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[7][6]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[7][6] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[7][6]->Fill(pRPD_ratio[7][6]);
                                    
                                    if (pRPD_ratio[7][6] > 1.6 && pRPD_ratio[7][6] < 2.4) {
                                    pRPD_signal[7][6] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[7][6]->Fill(pRPD_signal[7][6]);
                                    
                                    }   
                                    if (channel[n] == 7) {
                                    Run375259_pRPD_TS[3][6]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[3][6]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[3][6]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[3][6]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[3][6]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[3][6]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[3][6] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[3][6]->Fill(pRPD_ratio[3][6]);
                                    
                                    if (pRPD_ratio[3][6] > 1.5 && pRPD_ratio[3][6] < 2.4) {
                                    pRPD_signal[3][6] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[3][6]->Fill(pRPD_signal[3][6]);
                                    
                                    }   
                                    if (channel[n] == 8) {
                                    Run375259_pRPD_TS[15][6]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[15][6]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[15][6]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[15][6]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[15][6]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[15][6]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[15][6] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[15][6]->Fill(pRPD_ratio[15][6]);

                                    if (pRPD_ratio[15][6] > 1.6 && pRPD_ratio[15][6] < 2.2) {
                                    pRPD_signal[15][6] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[15][6]->Fill(pRPD_signal[15][6]);
                                    }   
                                    if (channel[n] == 9) {
                                    Run375259_pRPD_TS[4][6]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[4][6]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[4][6]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[4][6]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[4][6]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[4][6]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[4][6] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[4][6]->Fill(pRPD_ratio[4][6]);

                                    if (pRPD_ratio[4][6] > 1.5 && pRPD_ratio[4][6] < 2.4 ) {
                                    pRPD_signal[4][6] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[4][6]->Fill(pRPD_signal[4][6]);
                                    }   
                                    if (channel[n] == 10) {
                                    Run375259_pRPD_TS[8][6]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[8][6]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[8][6]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[8][6]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[8][6]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[8][6]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[8][6] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[8][6]->Fill(pRPD_ratio[8][6]);

                                    if (pRPD_ratio[8][6] > 1.5 && pRPD_ratio[8][6] < 2.3) {
                                    pRPD_signal[8][6] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[8][6]->Fill(pRPD_signal[8][6]);
                                    }   
                                    if (channel[n] == 11) {
                                    Run375259_pRPD_TS[12][6]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[12][6]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[12][6]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[12][6]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[12][6]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[12][6]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[12][6] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[12][6]->Fill(pRPD_ratio[12][6]);

                                    if (pRPD_ratio[12][6] > 1.5 && pRPD_ratio[12][6] < 2.2){
                                    pRPD_signal[12][6] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[12][6]->Fill(pRPD_signal[12][6]);
                                    }   
                                    if (channel[n] == 12) {
                                    Run375259_pRPD_TS[0][6]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[0][6]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[0][6]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[0][6]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[0][6]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[0][6]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[0][6] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[0][6]->Fill(pRPD_ratio[0][6]);

                                    if (pRPD_ratio[0][6] > 1.5 && pRPD_ratio[0][6] < 2.3){
                                    pRPD_signal[0][6] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[0][6]->Fill(pRPD_signal[0][6]);
                                    }   
                                    if (channel[n] == 13) {
                                    Run375259_pRPD_TS[5][6]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[5][6]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[5][6]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[5][6]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[5][6]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[5][6]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[5][6] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[5][6]->Fill(pRPD_ratio[5][6]);

                                    if (pRPD_ratio[5][6] > 1.7 && pRPD_ratio[5][6] < 2.5){
                                    pRPD_signal[5][6] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[5][6]->Fill(pRPD_signal[5][6]);
                                    }   
                                    if (channel[n] == 14) {
                                    Run375259_pRPD_TS[9][6]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[9][6]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[9][6]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[9][6]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[9][6]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[9][6]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[9][6] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[9][6]->Fill(pRPD_ratio[9][6]);
                                    
                                    if (pRPD_ratio[9][6] > 1.6 && pRPD_ratio[9][6] < 2.4) {
                                    pRPD_signal[9][6] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[9][6]->Fill(pRPD_signal[9][6]);
                                    }   
                                    if (channel[n] == 15) {
                                    Run375259_pRPD_TS[13][6]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[13][6]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[13][6]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[13][6]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[13][6]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[13][6]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[13][6] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[13][6]->Fill(pRPD_ratio[13][6]);

                                    if (pRPD_ratio[13][6] > 1.6 && pRPD_ratio[13][6] < 2.4) {
                                    pRPD_signal[13][6] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[13][6]->Fill(pRPD_signal[13][6]);
                                    }   
                                    if (channel[n] == 16) {
                                    Run375259_pRPD_TS[1][6]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[1][6]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[1][6]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[1][6]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[1][6]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[1][6]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[1][6] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[1][6]->Fill(pRPD_ratio[1][6]);

                                    if (pRPD_ratio[1][6] > 1.5 && pRPD_ratio[1][6] < 2.5) {
                                    pRPD_signal[1][6] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[1][6]->Fill(pRPD_signal[1][6]);
                                    }            
                                    pRPDX1[6] = pRPD_signal[0][6] + pRPD_signal[4][6] + pRPD_signal[8][6] + pRPD_signal[12][6];                   
                                    pRPDX2[6] = pRPD_signal[1][6] + pRPD_signal[5][6] + pRPD_signal[9][6] + pRPD_signal[13][6];  
                                    pRPDX3[6] = pRPD_signal[2][6] + pRPD_signal[6][6] + pRPD_signal[10][6] + pRPD_signal[14][6];  
                                    pRPDX4[6] = pRPD_signal[3][6] + pRPD_signal[7][6] + pRPD_signal[11][6] + pRPD_signal[15][6];  

                                    pRPDY1[6] = pRPD_signal[0][6] + pRPD_signal[1][6] + pRPD_signal[2][6] + pRPD_signal[3][6];  
                                    pRPDY2[6] = pRPD_signal[4][6] + pRPD_signal[5][6] + pRPD_signal[6][6] + pRPD_signal[7][6];  
                                    pRPDY3[6] = pRPD_signal[8][6] + pRPD_signal[9][6] + pRPD_signal[10][6] + pRPD_signal[11][6];  
                                    pRPDY4[6] = pRPD_signal[12][6] + pRPD_signal[13][6] + pRPD_signal[14][6] + pRPD_signal[15][6];  

                                    pRPD_signal_total[6] = pRPDX1[6] + pRPDX2[6] + pRPDX3[6] + pRPDX4[6];

                                    pRPD_signal_col[6] = ((-3*pRPDX1[6]) + (-1*pRPDX2[6]) + (1*pRPDX3[6]) + (3*pRPDX4[6])) / pRPD_signal_total[6];
                                    pRPD_signal_row[6] = ((-3*pRPDY4[6]) + (-1*pRPDY3[6]) + (1*pRPDY2[6]) + (3*pRPDY1[6])) / pRPD_signal_total[6];

                                } // end of side and section
                            
                                if (zside[n] == 1 && section[n] == 1) {
                                if (channel[n] == 1) {
                                    Run375259_pEM_TS[0][6]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[0][6]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[0][6]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[0][6]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[0][6]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[0][6]->Fill(5.0, TS5[n]);

                                    pEM_ratio[0][6] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[0][6]->Fill(pEM_ratio[0][6]);

                                    //if (pEM_ratio[0][6] > 0.8 && pEM_ratio[0][6] < 1.2){
                                        pEM_signal[0][6] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[0][6]->Fill(pEM_signal[0][6]);

                                }
                                if (channel[n] == 2) {
                                    Run375259_pEM_TS[1][6]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[1][6]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[1][6]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[1][6]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[1][6]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[1][6]->Fill(5.0, TS5[n]);

                                    pEM_ratio[1][6] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[1][6]->Fill(pEM_ratio[1][6]);

                                    //if (pEM_ratio[1][6] > 0.8 && pEM_ratio[1][6] < 1.2){
                                        pEM_signal[1][6] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[1][6]->Fill(pEM_signal[1][6]);
                                }
                                if (channel[n] == 3){
                                    Run375259_pEM_TS[2][6]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[2][6]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[2][6]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[2][6]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[2][6]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[2][6]->Fill(5.0, TS5[n]);

                                    pEM_ratio[2][6] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[2][6]->Fill(pEM_ratio[2][6]);

                                    //if (pEM_ratio[2][6] > 0.8 && pEM_ratio[2][6] < 1.2){
                                        pEM_signal[2][6] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[2][6]->Fill(pEM_signal[2][6]);
                                }
                                if (channel[n] == 4){
                                    Run375259_pEM_TS[3][6]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[3][6]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[3][6]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[3][6]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[3][6]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[3][6]->Fill(5.0, TS5[n]);

                                    pEM_ratio[3][6] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[3][6]->Fill(pEM_ratio[3][6]);

                                    //if (pEM_ratio[3][6] > 0.8 && pEM_ratio[3][6] < 1.2){
                                        pEM_signal[3][6] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[3][6]->Fill(pEM_signal[3][6]);
                                }
                                if (channel[n] == 5){
                                    Run375259_pEM_TS[4][6]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[4][6]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[4][6]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[4][6]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[4][6]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[4][6]->Fill(5.0, TS5[n]);

                                    pEM_ratio[4][6] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[4][6]->Fill(pEM_ratio[4][6]);

                                    //if (pEM_ratio[4][6] > 0.8 && pEM_ratio[4][6] < 1.2){
                                        pEM_signal[4][6] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[4][6]->Fill(pEM_signal[4][6]);
                                }
                                 pEM_signal_total[6] = (0.6 * pEM_signal[0][6]) + (0.89 * pEM_signal[1][6]) + (1 * pEM_signal[2][6]) + (1.29 * pEM_signal[3][6]) + (0.57 * pEM_signal[4][6]);
                                pEM_signal_col[6] = ((-3.6 * 0.6 * pEM_signal[0][6]) + (-1.8 * 0.89 * pEM_signal[1][6]) + (0 * 1 * pEM_signal[2][6]) + (1.8 * 1.29 * pEM_signal[3][6]) + (3.6 * 0.57 * pEM_signal[4][6])) / pEM_signal_total[6];
                            } // end of side & section
                       
                    if (zside[n] == 1 && section[n] == 2){
                        
                        if (channel[n] == 1){
                            Run375259_pHAD_TS[0][6]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[0][6]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[0][6]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[0][6]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[0][6]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[0][6]->Fill(5.0,TS5[n]);
                            pHAD_ratio[0][6] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[0][6]->Fill(pHAD_ratio[0][6]);
                            //if (pHAD_ratio[0][6] > 3.5 && pHAD_ratio[0][6] < 4){
                                pHAD_signal[0][6] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[0][6]->Fill(pHAD_signal[0][6]);
                        }
                        if (channel[n] == 2){
                            Run375259_pHAD_TS[1][6]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[1][6]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[1][6]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[1][6]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[1][6]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[1][6]->Fill(5.0,TS5[n]);
                            pHAD_ratio[1][6] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[1][6]->Fill(pHAD_ratio[1][6]);
                            //if (pHAD_ratio[1][6] > 3.5 && pHAD_ratio[1][6] < 4.5){
                                pHAD_signal[1][6] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[1][6]->Fill(pHAD_signal[1][6]);
                        }
                        if (channel[n] == 3){
                            Run375259_pHAD_TS[2][6]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[2][6]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[2][6]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[2][6]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[2][6]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[2][6]->Fill(5.0,TS5[n]);
                            pHAD_ratio[2][6] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[2][6]->Fill(pHAD_ratio[2][6]);
                            //if (pHAD_ratio[2][6] > 3.5 && pHAD_ratio[2][6] < 5){
                                pHAD_signal[2][6] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[2][6]->Fill(pHAD_signal[2][6]);
                        }
                        if (channel[n] == 4){
                            Run375259_pHAD_TS[3][6]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[3][6]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[3][6]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[3][6]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[3][6]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[3][6]->Fill(5.0,TS5[n]);
                            pHAD_ratio[3][6] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[3][6]->Fill(pHAD_ratio[3][6]);
                            //if (pHAD_ratio[3][6] > 4 && pHAD_ratio[3][6] < 5){
                                pHAD_signal[3][6] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[3][6]->Fill(pHAD_signal[3][6]);
                        }
                        pHAD_signal_total[6] = pHAD_signal[0][6] + pHAD_signal[1][6] + pHAD_signal[2][6] + pHAD_signal[3][6];
                        } // end  HAD 
                    } //end channel loop
                     Run375259_pEM_COMvsCent[6]->Fill(pEM_signal_col[6]);
                        Run375259_pEM_Profile[6]->Fill(0.0 , pEM_signal[0][6]);
                        Run375259_pEM_Profile[6]->Fill(1.0 , pEM_signal[1][6]);
                        Run375259_pEM_Profile[6]->Fill(2.0 , pEM_signal[2][6]);
                        Run375259_pEM_Profile[6]->Fill(3.0 , pEM_signal[3][6]);
                        Run375259_pEM_Profile[6]->Fill(4.0 , pEM_signal[4][6]);
                    Run375259_pRPDx_vs_pEMx[6]->Fill(pRPD_signal_col[6], pEM_signal_col[6]);
                    Run375259_pRPD_COM[6]->Fill(pRPD_signal_col[6], pRPD_signal_row[6]);
                            pos_rpd_xprojection[6]->Fill(pRPD_signal_col[6]);
                            Run375259_pRPD_prof[6]->Fill(0.0,pRPDX1[6]);
                            Run375259_pRPD_prof[6]->Fill(1.0,pRPDX2[6]);
                            Run375259_pRPD_prof[6]->Fill(2.0,pRPDX3[6]);
                            Run375259_pRPD_prof[6]->Fill(3.0,pRPDX4[6]);

                            Run375259_pRPD_Avg_Y_Sig[6]->Fill(0.0, pRPDY1[6]);
                            Run375259_pRPD_Avg_Y_Sig[6]->Fill(1.0, pRPDY2[6]);
                            Run375259_pRPD_Avg_Y_Sig[6]->Fill(2.0, pRPDY3[6]);
                            Run375259_pRPD_Avg_Y_Sig[6]->Fill(3.0, pRPDY4[6]);

                            Run375259_pRPD_HeatMap[6]->Fill(0.5,3.5,pRPD_signal[0][6]);
                            Run375259_pRPD_HeatMap[6]->Fill(1.5,3.5,pRPD_signal[1][6]);
                            Run375259_pRPD_HeatMap[6]->Fill(2.5,3.5,pRPD_signal[2][6]);
                            Run375259_pRPD_HeatMap[6]->Fill(3.5,3.5,pRPD_signal[3][6]);

                            Run375259_pRPD_HeatMap[6]->Fill(0.5,2.5,pRPD_signal[4][6]);
                            Run375259_pRPD_HeatMap[6]->Fill(1.5,2.5,pRPD_signal[5][6]);
                            Run375259_pRPD_HeatMap[6]->Fill(2.5,2.5,pRPD_signal[6][6]);
                            Run375259_pRPD_HeatMap[6]->Fill(3.5,2.5,pRPD_signal[7][6]);

                            Run375259_pRPD_HeatMap[6]->Fill(0.5,1.5,pRPD_signal[8][6]);
                            Run375259_pRPD_HeatMap[6]->Fill(1.5,1.5,pRPD_signal[9][6]);
                            Run375259_pRPD_HeatMap[6]->Fill(2.5,1.5,pRPD_signal[10][6]);
                            Run375259_pRPD_HeatMap[6]->Fill(3.5,1.5,pRPD_signal[11][6]);

                            Run375259_pRPD_HeatMap[6]->Fill(0.5,0.5,pRPD_signal[12][6]);
                            Run375259_pRPD_HeatMap[6]->Fill(1.5,0.5,pRPD_signal[13][6]);
                            Run375259_pRPD_HeatMap[6]->Fill(2.5,0.5,pRPD_signal[14][6]);
                            Run375259_pRPD_HeatMap[6]->Fill(3.5,0.5,pRPD_signal[15][6]);
                    ZDC[6] = 0.1 * pEM_signal_total[6] + pHAD_signal_total[6];
                    Run375259_pRPD_position_vstotalsignal[6]->Fill(ZDC[6], pRPD_signal_col[6]);
                    Run375259_pEM_position_vstotalsignal[6]->Fill(ZDC[6], pEM_signal_col[6]);
                    Run375259_NeutronPlotProjection[6]->Fill(ZDC[6]);
                    Run375259_NeutronPlot[6]->Fill(ZDC[6],pEM_signal_total[6]);
                } // end of hibin 
                if (hibin >=140 && hibin < 160 ){ 
                            for (int n = 0; n < 56; n++) {
                                if (zside[n] == 1 && section[n] == 4) {
                                    if (channel[n] == 1) {
                                    Run375259_pRPD_TS[10][7]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[10][7]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[10][7]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[10][7]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[10][7]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[10][7]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[10][7] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[10][7]->Fill(pRPD_ratio[10][7]);

                                    if (pRPD_ratio[10][7] > 1.5 && pRPD_ratio[10][7] < 2.0) {
                                    pRPD_signal[10][7] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[10][7]->Fill(pRPD_signal[10][7]);
                                    
                                    }
                                    if (channel[n] == 2) {
                                    Run375259_pRPD_TS[6][7]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[6][7]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[6][7]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[6][7]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[6][7]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[6][7]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[6][7] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[6][7]->Fill(pRPD_ratio[6][7]);
                                    
                                    if (pRPD_ratio[6][7] > 1.5 && pRPD_ratio[6][7] < 2.1) {
                                    pRPD_signal[6][7] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[6][7]->Fill(pRPD_signal[6][7]);
                                    
                                    } 
                                    if (channel[n] == 3) {
                                    Run375259_pRPD_TS[2][7]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[2][7]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[2][7]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[2][7]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[2][7]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[2][7]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[2][7] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[2][7]->Fill(pRPD_ratio[2][7]);
                                    
                                    if (pRPD_ratio[2][7] > 1.5 && pRPD_ratio[2][7] < 2.0) {
                                    pRPD_signal[2][7] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[2][7]->Fill(pRPD_signal[2][7]);
                                    
                                    }      
                                    if (channel[n] == 4) {
                                    Run375259_pRPD_TS[14][7]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[14][7]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[14][7]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[14][7]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[14][7]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[14][7]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[14][7] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[14][7]->Fill(pRPD_ratio[14][7]);

                                    if (pRPD_ratio[14][7] > 1.5 && pRPD_ratio[14][7] < 2.0) {
                                    pRPD_signal[14][7] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[14][7]->Fill(pRPD_signal[14][7]);
                                    
                                    }   
                                    if (channel[n] == 5) {
                                    Run375259_pRPD_TS[11][7]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[11][7]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[11][7]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[11][7]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[11][7]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[11][7]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[11][7] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[11][7]->Fill(pRPD_ratio[11][7]);
                                    
                                    if (pRPD_ratio[11][7] > 1.5 && pRPD_ratio[11][7] < 2.1) {
                                    pRPD_signal[11][7] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[11][7]->Fill(pRPD_signal[11][7]);
                                    
                                    }   
                                    if (channel[n] == 6) {
                                    Run375259_pRPD_TS[7][7]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[7][7]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[7][7]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[7][7]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[7][7]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[7][7]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[7][7] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[7][7]->Fill(pRPD_ratio[7][7]);
                                    
                                    if (pRPD_ratio[7][7] > 1.6 && pRPD_ratio[7][7] < 2.4) {
                                    pRPD_signal[7][7] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[7][7]->Fill(pRPD_signal[7][7]);
                                    
                                    }   
                                    if (channel[n] == 7) {
                                    Run375259_pRPD_TS[3][7]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[3][7]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[3][7]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[3][7]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[3][7]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[3][7]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[3][7] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[3][7]->Fill(pRPD_ratio[3][7]);
                                    
                                    if (pRPD_ratio[3][7] > 1.5 && pRPD_ratio[3][7] < 2.4) {
                                    pRPD_signal[3][7] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[3][7]->Fill(pRPD_signal[3][7]);
                                    
                                    }   
                                    if (channel[n] == 8) {
                                    Run375259_pRPD_TS[15][7]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[15][7]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[15][7]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[15][7]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[15][7]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[15][7]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[15][7] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[15][7]->Fill(pRPD_ratio[15][7]);

                                    if (pRPD_ratio[15][7] > 1.6 && pRPD_ratio[15][7] < 2.2) {
                                    pRPD_signal[15][7] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[15][7]->Fill(pRPD_signal[15][7]);
                                    }   
                                    if (channel[n] == 9) {
                                    Run375259_pRPD_TS[4][7]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[4][7]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[4][7]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[4][7]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[4][7]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[4][7]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[4][7] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[4][7]->Fill(pRPD_ratio[4][7]);

                                    if (pRPD_ratio[4][7] > 1.5 && pRPD_ratio[4][7] < 2.4 ) {
                                    pRPD_signal[4][7] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[4][7]->Fill(pRPD_signal[4][7]);
                                    }   
                                    if (channel[n] == 10) {
                                    Run375259_pRPD_TS[8][7]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[8][7]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[8][7]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[8][7]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[8][7]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[8][7]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[8][7] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[8][7]->Fill(pRPD_ratio[8][7]);

                                    if (pRPD_ratio[8][7] > 1.5 && pRPD_ratio[8][7] < 2.3) {
                                    pRPD_signal[8][7] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[8][7]->Fill(pRPD_signal[8][7]);
                                    }   
                                    if (channel[n] == 11) {
                                    Run375259_pRPD_TS[12][7]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[12][7]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[12][7]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[12][7]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[12][7]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[12][7]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[12][7] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[12][7]->Fill(pRPD_ratio[12][7]);

                                    if (pRPD_ratio[12][7] > 1.5 && pRPD_ratio[12][7] < 2.2){
                                    pRPD_signal[12][7] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[12][7]->Fill(pRPD_signal[12][7]);
                                    }   
                                    if (channel[n] == 12) {
                                    Run375259_pRPD_TS[0][7]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[0][7]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[0][7]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[0][7]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[0][7]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[0][7]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[0][7] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[0][7]->Fill(pRPD_ratio[0][7]);

                                    if (pRPD_ratio[0][7] > 1.5 && pRPD_ratio[0][7] < 2.3){
                                    pRPD_signal[0][7] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[0][7]->Fill(pRPD_signal[0][7]);
                                    }   
                                    if (channel[n] == 13) {
                                    Run375259_pRPD_TS[5][7]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[5][7]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[5][7]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[5][7]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[5][7]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[5][7]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[5][7] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[5][7]->Fill(pRPD_ratio[5][7]);

                                    if (pRPD_ratio[5][7] > 1.7 && pRPD_ratio[5][7] < 2.5){
                                    pRPD_signal[5][7] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[5][7]->Fill(pRPD_signal[5][7]);
                                    }   
                                    if (channel[n] == 14) {
                                    Run375259_pRPD_TS[9][7]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[9][7]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[9][7]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[9][7]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[9][7]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[9][7]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[9][7] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[9][7]->Fill(pRPD_ratio[9][7]);
                                    
                                    if (pRPD_ratio[9][7] > 1.6 && pRPD_ratio[9][7] < 2.4) {
                                    pRPD_signal[9][7] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[9][7]->Fill(pRPD_signal[9][7]);
                                    }   
                                    if (channel[n] == 15) {
                                    Run375259_pRPD_TS[13][7]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[13][7]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[13][7]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[13][7]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[13][7]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[13][7]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[13][7] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[13][7]->Fill(pRPD_ratio[13][7]);

                                    if (pRPD_ratio[13][7] > 1.6 && pRPD_ratio[13][7] < 2.4) {
                                    pRPD_signal[13][7] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[13][7]->Fill(pRPD_signal[13][7]);
                                    }   
                                    if (channel[n] == 16) {
                                    Run375259_pRPD_TS[1][7]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[1][7]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[1][7]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[1][7]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[1][7]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[1][7]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[1][7] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[1][7]->Fill(pRPD_ratio[1][7]);

                                    if (pRPD_ratio[1][7] > 1.5 && pRPD_ratio[1][7] < 2.5) {
                                    pRPD_signal[1][7] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[1][7]->Fill(pRPD_signal[1][7]);
                                    }            
                                    pRPDX1[7] = pRPD_signal[0][7] + pRPD_signal[4][7] + pRPD_signal[8][7] + pRPD_signal[12][7];                   
                                    pRPDX2[7] = pRPD_signal[1][7] + pRPD_signal[5][7] + pRPD_signal[9][7] + pRPD_signal[13][7];  
                                    pRPDX3[7] = pRPD_signal[2][7] + pRPD_signal[6][7] + pRPD_signal[10][7] + pRPD_signal[14][7];  
                                    pRPDX4[7] = pRPD_signal[3][7] + pRPD_signal[7][7] + pRPD_signal[11][7] + pRPD_signal[15][7];  

                                    pRPDY1[7] = pRPD_signal[0][7] + pRPD_signal[1][7] + pRPD_signal[2][7] + pRPD_signal[3][7];  
                                    pRPDY2[7] = pRPD_signal[4][7] + pRPD_signal[5][7] + pRPD_signal[6][7] + pRPD_signal[7][7];  
                                    pRPDY3[7] = pRPD_signal[8][7] + pRPD_signal[9][7] + pRPD_signal[10][7] + pRPD_signal[11][7];  
                                    pRPDY4[7] = pRPD_signal[12][7] + pRPD_signal[13][7] + pRPD_signal[14][7] + pRPD_signal[15][7];  

                                    pRPD_signal_total[7] = pRPDX1[7] + pRPDX2[7] + pRPDX3[7] + pRPDX4[7];

                                    pRPD_signal_col[7] = ((-3*pRPDX1[7]) + (-1*pRPDX2[7]) + (1*pRPDX3[7]) + (3*pRPDX4[7])) / pRPD_signal_total[7];
                                    pRPD_signal_row[7] = ((-3*pRPDY4[7]) + (-1*pRPDY3[7]) + (1*pRPDY2[7]) + (3*pRPDY1[7])) / pRPD_signal_total[7];

                                } // end of side and section
                            
                                if (zside[n] == 1 && section[n] == 1) {
                                if (channel[n] == 1) {
                                    Run375259_pEM_TS[0][7]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[0][7]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[0][7]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[0][7]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[0][7]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[0][7]->Fill(5.0, TS5[n]);

                                    pEM_ratio[0][7] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[0][7]->Fill(pEM_ratio[0][7]);

                                    //if (pEM_ratio[0][7] > 0.8 && pEM_ratio[0][7] < 1.2){
                                        pEM_signal[0][7] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[0][7]->Fill(pEM_signal[0][7]);

                                }
                                if (channel[n] == 2) {
                                    Run375259_pEM_TS[1][7]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[1][7]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[1][7]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[1][7]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[1][7]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[1][7]->Fill(5.0, TS5[n]);

                                    pEM_ratio[1][7] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[1][7]->Fill(pEM_ratio[1][7]);

                                    //if (pEM_ratio[1][7] > 0.8 && pEM_ratio[1][7] < 1.2){
                                        pEM_signal[1][7] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[1][7]->Fill(pEM_signal[1][7]);
                                }
                                if (channel[n] == 3){
                                    Run375259_pEM_TS[2][7]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[2][7]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[2][7]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[2][7]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[2][7]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[2][7]->Fill(5.0, TS5[n]);

                                    pEM_ratio[2][7] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[2][7]->Fill(pEM_ratio[2][7]);

                                    //if (pEM_ratio[2][7] > 0.8 && pEM_ratio[2][7] < 1.2){
                                        pEM_signal[2][7] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[2][7]->Fill(pEM_signal[2][7]);
                                }
                                if (channel[n] == 4){
                                    Run375259_pEM_TS[3][7]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[3][7]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[3][7]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[3][7]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[3][7]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[3][7]->Fill(5.0, TS5[n]);

                                    pEM_ratio[3][7] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[3][7]->Fill(pEM_ratio[3][7]);

                                    //if (pEM_ratio[3][7] > 0.8 && pEM_ratio[3][7] < 1.2){
                                        pEM_signal[3][7] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[3][7]->Fill(pEM_signal[3][7]);
                                }
                                if (channel[n] == 5){
                                    Run375259_pEM_TS[4][7]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[4][7]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[4][7]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[4][7]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[4][7]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[4][7]->Fill(5.0, TS5[n]);

                                    pEM_ratio[4][7] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[4][7]->Fill(pEM_ratio[4][7]);

                                    //if (pEM_ratio[4][7] > 0.8 && pEM_ratio[4][7] < 1.2){
                                        pEM_signal[4][7] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[4][7]->Fill(pEM_signal[4][7]);
                                }
                                 pEM_signal_total[7] = (0.6 * pEM_signal[0][7]) + (0.89 * pEM_signal[1][7]) + (1 * pEM_signal[2][7]) + (1.29 * pEM_signal[3][7]) + (0.57 * pEM_signal[4][7]);
                                pEM_signal_col[7] = ((-3.6 * 0.6 * pEM_signal[0][7]) + (-1.8 * 0.89 * pEM_signal[1][7]) + (0 * 1 * pEM_signal[2][7]) + (1.8 * 1.29 * pEM_signal[3][7]) + (3.6 * 0.57 * pEM_signal[4][7])) / pEM_signal_total[7];
                            } // end of side & section
                        
                    if (zside[n] == 1 && section[n] == 2){
                        
                        if (channel[n] == 1){
                            Run375259_pHAD_TS[0][7]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[0][7]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[0][7]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[0][7]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[0][7]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[0][7]->Fill(5.0,TS5[n]);
                            pHAD_ratio[0][7] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[0][7]->Fill(pHAD_ratio[0][7]);
                            //if (pHAD_ratio[0][7] > 3.5 && pHAD_ratio[0][7] < 4){
                                pHAD_signal[0][7] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[0][7]->Fill(pHAD_signal[0][7]);
                        }
                        if (channel[n] == 2){
                            Run375259_pHAD_TS[1][7]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[1][7]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[1][7]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[1][7]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[1][7]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[1][7]->Fill(5.0,TS5[n]);
                            pHAD_ratio[1][7] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[1][7]->Fill(pHAD_ratio[1][7]);
                            //if (pHAD_ratio[1][7] > 3.5 && pHAD_ratio[1][7] < 4.5){
                                pHAD_signal[1][7] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[1][7]->Fill(pHAD_signal[1][7]);
                        }
                        if (channel[n] == 3){
                            Run375259_pHAD_TS[2][7]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[2][7]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[2][7]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[2][7]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[2][7]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[2][7]->Fill(5.0,TS5[n]);
                            pHAD_ratio[2][7] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[2][7]->Fill(pHAD_ratio[2][7]);
                            //if (pHAD_ratio[2][7] > 3.5 && pHAD_ratio[2][7] < 5){
                                pHAD_signal[2][7] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[2][7]->Fill(pHAD_signal[2][7]);
                        }
                        if (channel[n] == 4){
                            Run375259_pHAD_TS[3][7]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[3][7]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[3][7]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[3][7]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[3][7]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[3][7]->Fill(5.0,TS5[n]);
                            pHAD_ratio[3][7] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[3][7]->Fill(pHAD_ratio[3][7]);
                            //if (pHAD_ratio[3][7] > 4 && pHAD_ratio[3][7] < 5){
                                pHAD_signal[3][7] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[3][7]->Fill(pHAD_signal[3][7]);
                        }
                        pHAD_signal_total[7] = pHAD_signal[0][7] + pHAD_signal[1][7] + pHAD_signal[2][7] + pHAD_signal[3][7];
                        } // end  HAD 
                    } //end channel loop
                    Run375259_pEM_COMvsCent[7]->Fill(pEM_signal_col[7]);
                    Run375259_pEM_Profile[7]->Fill(0.0 , pEM_signal[0][7]);
                    Run375259_pEM_Profile[7]->Fill(1.0 , pEM_signal[1][7]);
                    Run375259_pEM_Profile[7]->Fill(2.0 , pEM_signal[2][7]);
                    Run375259_pEM_Profile[7]->Fill(3.0 , pEM_signal[3][7]);
                    Run375259_pEM_Profile[7]->Fill(4.0 , pEM_signal[4][7]);
                    Run375259_pRPDx_vs_pEMx[7]->Fill(pRPD_signal_col[7], pEM_signal_col[7]);
                    Run375259_pRPD_COM[7]->Fill(pRPD_signal_col[7], pRPD_signal_row[7]);
                    pos_rpd_xprojection[7]->Fill(pRPD_signal_col[7]);
                    Run375259_pRPD_prof[7]->Fill(0.0,pRPDX1[7]);
                    Run375259_pRPD_prof[7]->Fill(1.0,pRPDX2[7]);
                    Run375259_pRPD_prof[7]->Fill(2.0,pRPDX3[7]);
                    Run375259_pRPD_prof[7]->Fill(3.0,pRPDX4[7]);

                    Run375259_pRPD_Avg_Y_Sig[7]->Fill(0.0, pRPDY1[7]);
                    Run375259_pRPD_Avg_Y_Sig[7]->Fill(1.0, pRPDY2[7]);
                    Run375259_pRPD_Avg_Y_Sig[7]->Fill(2.0, pRPDY3[7]);
                    Run375259_pRPD_Avg_Y_Sig[7]->Fill(3.0, pRPDY4[7]);

                    Run375259_pRPD_HeatMap[7]->Fill(0.5,3.5,pRPD_signal[0][7]);
                    Run375259_pRPD_HeatMap[7]->Fill(1.5,3.5,pRPD_signal[1][7]);
                    Run375259_pRPD_HeatMap[7]->Fill(2.5,3.5,pRPD_signal[2][7]);
                    Run375259_pRPD_HeatMap[7]->Fill(3.5,3.5,pRPD_signal[3][7]);

                    Run375259_pRPD_HeatMap[7]->Fill(0.5,2.5,pRPD_signal[4][7]);
                    Run375259_pRPD_HeatMap[7]->Fill(1.5,2.5,pRPD_signal[5][7]);
                    Run375259_pRPD_HeatMap[7]->Fill(2.5,2.5,pRPD_signal[6][7]);
                    Run375259_pRPD_HeatMap[7]->Fill(3.5,2.5,pRPD_signal[7][7]);

                    Run375259_pRPD_HeatMap[7]->Fill(0.5,1.5,pRPD_signal[8][7]);
                    Run375259_pRPD_HeatMap[7]->Fill(1.5,1.5,pRPD_signal[9][7]);
                    Run375259_pRPD_HeatMap[7]->Fill(2.5,1.5,pRPD_signal[10][7]);
                    Run375259_pRPD_HeatMap[7]->Fill(3.5,1.5,pRPD_signal[11][7]);

                    Run375259_pRPD_HeatMap[7]->Fill(0.5,0.5,pRPD_signal[12][7]);
                    Run375259_pRPD_HeatMap[7]->Fill(1.5,0.5,pRPD_signal[13][7]);
                    Run375259_pRPD_HeatMap[7]->Fill(2.5,0.5,pRPD_signal[14][7]);
                    Run375259_pRPD_HeatMap[7]->Fill(3.5,0.5,pRPD_signal[15][7]);
                    ZDC[7] = 0.1 * pEM_signal_total[7] + pHAD_signal_total[7];
                    Run375259_pRPD_position_vstotalsignal[7]->Fill(ZDC[7], pRPD_signal_col[7]);
                    Run375259_pEM_position_vstotalsignal[7]->Fill(ZDC[7], pEM_signal_col[7]);
                    Run375259_NeutronPlotProjection[7]->Fill(ZDC[7]);
                    Run375259_NeutronPlot[7]->Fill(ZDC[7],pEM_signal_total[7]);
                } // end of hibin 140 to 160
                if (hibin >=160 && hibin < 180 ){ 
                            for (int n = 0; n < 56; n++) {
                                if (zside[n] == 1 && section[n] == 4) {
                                    if (channel[n] == 1) {
                                    Run375259_pRPD_TS[10][8]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[10][8]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[10][8]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[10][8]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[10][8]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[10][8]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[10][8] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[10][8]->Fill(pRPD_ratio[10][8]);

                                    if (pRPD_ratio[10][8] > 1.5 && pRPD_ratio[10][8] < 2.0) {
                                    pRPD_signal[10][8] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[10][8]->Fill(pRPD_signal[10][8]);
                                    
                                    }
                                    if (channel[n] == 2) {
                                    Run375259_pRPD_TS[6][8]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[6][8]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[6][8]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[6][8]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[6][8]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[6][8]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[6][8] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[6][8]->Fill(pRPD_ratio[6][8]);
                                    
                                    if (pRPD_ratio[6][8] > 1.5 && pRPD_ratio[6][8] < 2.1) {
                                    pRPD_signal[6][8] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[6][8]->Fill(pRPD_signal[6][8]);
                                    
                                    } 
                                    if (channel[n] == 3) {
                                    Run375259_pRPD_TS[2][8]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[2][8]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[2][8]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[2][8]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[2][8]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[2][8]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[2][8] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[2][8]->Fill(pRPD_ratio[2][8]);
                                    
                                    if (pRPD_ratio[2][8] > 1.5 && pRPD_ratio[2][8] < 2.0) {
                                    pRPD_signal[2][8] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[2][8]->Fill(pRPD_signal[2][8]);
                                    
                                    }      
                                    if (channel[n] == 4) {
                                    Run375259_pRPD_TS[14][8]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[14][8]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[14][8]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[14][8]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[14][8]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[14][8]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[14][8] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[14][8]->Fill(pRPD_ratio[14][8]);

                                    if (pRPD_ratio[14][8] > 1.5 && pRPD_ratio[14][8] < 2.0) {
                                    pRPD_signal[14][8] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[14][8]->Fill(pRPD_signal[14][8]);
                                    
                                    }   
                                    if (channel[n] == 5) {
                                    Run375259_pRPD_TS[11][8]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[11][8]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[11][8]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[11][8]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[11][8]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[11][8]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[11][8] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[11][8]->Fill(pRPD_ratio[11][8]);
                                    
                                    if (pRPD_ratio[11][8] > 1.5 && pRPD_ratio[11][8] < 2.1) {
                                    pRPD_signal[11][8] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[11][8]->Fill(pRPD_signal[11][8]);
                                    
                                    }   
                                    if (channel[n] == 6) {
                                    Run375259_pRPD_TS[7][8]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[7][8]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[7][8]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[7][8]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[7][8]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[7][8]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[7][8] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[7][8]->Fill(pRPD_ratio[7][8]);
                                    
                                    if (pRPD_ratio[7][8] > 1.6 && pRPD_ratio[7][8] < 2.4) {
                                    pRPD_signal[7][8] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[7][8]->Fill(pRPD_signal[7][8]);
                                    
                                    }   
                                    if (channel[n] == 7) {
                                    Run375259_pRPD_TS[3][8]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[3][8]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[3][8]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[3][8]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[3][8]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[3][8]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[3][8] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[3][8]->Fill(pRPD_ratio[3][8]);
                                    
                                    if (pRPD_ratio[3][8] > 1.5 && pRPD_ratio[3][8] < 2.4) {
                                    pRPD_signal[3][8] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[8][8]->Fill(pRPD_signal[3][8]);
                                    
                                    }   
                                    if (channel[n] == 8) {
                                    Run375259_pRPD_TS[15][8]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[15][8]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[15][8]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[15][8]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[15][8]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[15][8]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[15][8] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[15][8]->Fill(pRPD_ratio[15][8]);

                                    if (pRPD_ratio[15][8] > 1.6 && pRPD_ratio[15][8] < 2.2) {
                                    pRPD_signal[15][8] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[15][8]->Fill(pRPD_signal[15][8]);
                                    }   
                                    if (channel[n] == 9) {
                                    Run375259_pRPD_TS[4][8]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[4][8]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[4][8]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[4][8]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[4][8]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[4][8]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[4][8] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[4][8]->Fill(pRPD_ratio[4][8]);

                                    if (pRPD_ratio[4][8] > 1.5 && pRPD_ratio[4][8] < 2.4 ) {
                                    pRPD_signal[4][8] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[4][8]->Fill(pRPD_signal[4][8]);
                                    }   
                                    if (channel[n] == 10) {
                                    Run375259_pRPD_TS[8][8]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[8][8]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[8][8]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[8][8]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[8][8]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[8][8]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[8][8] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[8][8]->Fill(pRPD_ratio[8][8]);

                                    if (pRPD_ratio[8][8] > 1.5 && pRPD_ratio[8][8] < 2.3) {
                                    pRPD_signal[8][8] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[8][8]->Fill(pRPD_signal[8][8]);
                                    }   
                                    if (channel[n] == 11) {
                                    Run375259_pRPD_TS[12][8]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[12][8]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[12][8]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[12][8]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[12][8]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[12][8]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[12][8] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[12][8]->Fill(pRPD_ratio[12][8]);

                                    if (pRPD_ratio[12][8] > 1.5 && pRPD_ratio[12][8] < 2.2){
                                    pRPD_signal[12][8] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[12][8]->Fill(pRPD_signal[12][8]);
                                    }   
                                    if (channel[n] == 12) {
                                    Run375259_pRPD_TS[0][8]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[0][8]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[0][8]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[0][8]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[0][8]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[0][8]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[0][8] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[0][8]->Fill(pRPD_ratio[0][8]);

                                    if (pRPD_ratio[0][8] > 1.5 && pRPD_ratio[0][8] < 2.3){
                                    pRPD_signal[0][8] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[0][8]->Fill(pRPD_signal[0][8]);
                                    }   
                                    if (channel[n] == 13) {
                                    Run375259_pRPD_TS[5][8]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[5][8]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[5][8]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[5][8]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[5][8]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[5][8]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[5][8] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[5][8]->Fill(pRPD_ratio[5][8]);

                                    if (pRPD_ratio[5][8] > 1.7 && pRPD_ratio[5][8] < 2.5){
                                    pRPD_signal[5][8] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[5][8]->Fill(pRPD_signal[5][8]);
                                    }   
                                    if (channel[n] == 14) {
                                    Run375259_pRPD_TS[9][8]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[9][8]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[9][8]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[9][8]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[9][8]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[9][8]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[9][8] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[9][8]->Fill(pRPD_ratio[9][8]);
                                    
                                    if (pRPD_ratio[9][8] > 1.6 && pRPD_ratio[9][8] < 2.4) {
                                    pRPD_signal[9][8] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[9][8]->Fill(pRPD_signal[9][8]);
                                    }   
                                    if (channel[n] == 15) {
                                    Run375259_pRPD_TS[13][8]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[13][8]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[13][8]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[13][8]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[13][8]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[13][8]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[13][8] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[13][8]->Fill(pRPD_ratio[13][8]);

                                    if (pRPD_ratio[13][8] > 1.6 && pRPD_ratio[13][8] < 2.4) {
                                    pRPD_signal[13][8] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[13][8]->Fill(pRPD_signal[13][8]);
                                    }   
                                    if (channel[n] == 16) {
                                    Run375259_pRPD_TS[1][8]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[1][8]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[1][8]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[1][8]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[1][8]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[1][8]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[1][8] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[1][8]->Fill(pRPD_ratio[1][8]);

                                    if (pRPD_ratio[1][8] > 1.5 && pRPD_ratio[1][8] < 2.5) {
                                    pRPD_signal[1][8] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[1][8]->Fill(pRPD_signal[1][8]);
                                    }            
                                    pRPDX1[8] = pRPD_signal[0][8] + pRPD_signal[4][8] + pRPD_signal[8][8] + pRPD_signal[12][8];                   
                                    pRPDX2[8] = pRPD_signal[1][8] + pRPD_signal[5][8] + pRPD_signal[9][8] + pRPD_signal[13][8];  
                                    pRPDX3[8] = pRPD_signal[2][8] + pRPD_signal[6][8] + pRPD_signal[10][8] + pRPD_signal[14][8];  
                                    pRPDX4[8] = pRPD_signal[3][8] + pRPD_signal[7][8] + pRPD_signal[11][8] + pRPD_signal[15][8];  

                                    pRPDY1[8] = pRPD_signal[0][8] + pRPD_signal[1][8] + pRPD_signal[2][8] + pRPD_signal[3][8];  
                                    pRPDY2[8] = pRPD_signal[4][8] + pRPD_signal[5][8] + pRPD_signal[6][8] + pRPD_signal[7][8];  
                                    pRPDY3[8] = pRPD_signal[8][8] + pRPD_signal[9][8] + pRPD_signal[10][8] + pRPD_signal[11][8];  
                                    pRPDY4[8] = pRPD_signal[12][8] + pRPD_signal[13][8] + pRPD_signal[14][8] + pRPD_signal[15][8];  

                                    pRPD_signal_total[8] = pRPDX1[8] + pRPDX2[8] + pRPDX3[8] + pRPDX4[8];

                                    pRPD_signal_col[8] = ((-3*pRPDX1[8]) + (-1*pRPDX2[8]) + (1*pRPDX3[8]) + (3*pRPDX4[8])) / pRPD_signal_total[8];
                                    pRPD_signal_row[8] = ((-3*pRPDY4[8]) + (-1*pRPDY3[8]) + (1*pRPDY2[8]) + (3*pRPDY1[8])) / pRPD_signal_total[8];

                                } // end of side and section
                            
                                if (zside[n] == 1 && section[n] == 1) {
                                if (channel[n] == 1) {
                                    Run375259_pEM_TS[0][8]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[0][8]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[0][8]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[0][8]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[0][8]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[0][8]->Fill(5.0, TS5[n]);

                                    pEM_ratio[0][8] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[0][8]->Fill(pEM_ratio[0][8]);

                                    //if (pEM_ratio[0][8] > 0.8 && pEM_ratio[0][8] < 1.2){
                                        pEM_signal[0][8] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[0][8]->Fill(pEM_signal[0][8]);

                                }
                                if (channel[n] == 2) {
                                    Run375259_pEM_TS[1][8]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[1][8]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[1][8]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[1][8]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[1][8]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[1][8]->Fill(5.0, TS5[n]);

                                    pEM_ratio[1][8] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[1][8]->Fill(pEM_ratio[1][8]);

                                    //if (pEM_ratio[1][8] > 0.8 && pEM_ratio[1][8] < 1.2){
                                        pEM_signal[1][8] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[1][8]->Fill(pEM_signal[1][8]);
                                }
                                if (channel[n] == 3){
                                    Run375259_pEM_TS[2][8]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[2][8]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[2][8]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[2][8]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[2][8]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[2][8]->Fill(5.0, TS5[n]);

                                    pEM_ratio[2][8] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[2][8]->Fill(pEM_ratio[2][8]);

                                    //if (pEM_ratio[2][8] > 0.8 && pEM_ratio[2][8] < 1.2){
                                        pEM_signal[2][8] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[2][8]->Fill(pEM_signal[2][8]);
                                }
                                if (channel[n] == 4){
                                    Run375259_pEM_TS[3][8]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[3][8]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[3][8]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[3][8]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[3][8]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[3][8]->Fill(5.0, TS5[n]);

                                    pEM_ratio[3][8] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[3][8]->Fill(pEM_ratio[3][8]);

                                    //if (pEM_ratio[3][8] > 0.8 && pEM_ratio[3][8] < 1.2){
                                        pEM_signal[3][8] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[3][8]->Fill(pEM_signal[3][8]);
                                }
                                if (channel[n] == 5){
                                    Run375259_pEM_TS[4][8]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[4][8]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[4][8]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[4][8]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[4][8]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[4][8]->Fill(5.0, TS5[n]);

                                    pEM_ratio[4][8] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[4][8]->Fill(pEM_ratio[4][8]);

                                    //if (pEM_ratio[4][8] > 0.8 && pEM_ratio[4][8] < 1.2){
                                        pEM_signal[4][8] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[4][8]->Fill(pEM_signal[4][8]);
                                }
                                 pEM_signal_total[8] = (0.6 * pEM_signal[0][8]) + (0.89 * pEM_signal[1][8]) + (1 * pEM_signal[2][8]) + (1.29 * pEM_signal[3][8]) + (0.57 * pEM_signal[4][8]);
                                pEM_signal_col[8] = ((-3.6 * 0.6 * pEM_signal[0][8]) + (-1.8 * 0.89 * pEM_signal[1][8]) + (0 * 1 * pEM_signal[2][8]) + (1.8 * 1.29 * pEM_signal[3][8]) + (3.6 * 0.57 * pEM_signal[4][8])) / pEM_signal_total[8];
                            } // end of side & section
                        
                    if (zside[n] == 1 && section[n] == 2){
                        
                        if (channel[n] == 1){
                            Run375259_pHAD_TS[0][8]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[0][8]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[0][8]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[0][8]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[0][8]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[0][8]->Fill(5.0,TS5[n]);
                            pHAD_ratio[0][8] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[0][8]->Fill(pHAD_ratio[0][8]);
                            //if (pHAD_ratio[0][8] > 3.5 && pHAD_ratio[0][8] < 4){
                                pHAD_signal[0][8] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[0][8]->Fill(pHAD_signal[0][8]);
                        }
                        if (channel[n] == 2){
                            Run375259_pHAD_TS[1][8]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[1][8]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[1][8]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[1][8]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[1][8]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[1][8]->Fill(5.0,TS5[n]);
                            pHAD_ratio[1][8] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[1][8]->Fill(pHAD_ratio[1][8]);
                            //if (pHAD_ratio[1][8] > 3.5 && pHAD_ratio[1][8] < 4.5){
                                pHAD_signal[1][8] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[1][8]->Fill(pHAD_signal[1][8]);
                        }
                        if (channel[n] == 3){
                            Run375259_pHAD_TS[2][8]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[2][8]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[2][8]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[2][8]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[2][8]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[2][8]->Fill(5.0,TS5[n]);
                            pHAD_ratio[2][8] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[2][8]->Fill(pHAD_ratio[2][8]);
                            //if (pHAD_ratio[2][8] > 3.5 && pHAD_ratio[2][8] < 5){
                                pHAD_signal[2][8] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[2][8]->Fill(pHAD_signal[2][8]);
                        }
                        if (channel[n] == 4){
                            Run375259_pHAD_TS[3][8]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[3][8]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[3][8]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[3][8]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[3][8]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[3][8]->Fill(5.0,TS5[n]);
                            pHAD_ratio[3][8] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[3][8]->Fill(pHAD_ratio[3][8]);
                            //if (pHAD_ratio[3][8] > 4 && pHAD_ratio[3][8] < 5){
                                pHAD_signal[3][8] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[3][8]->Fill(pHAD_signal[3][8]);
                        }
                        pHAD_signal_total[8] = pHAD_signal[0][8] + pHAD_signal[1][8] + pHAD_signal[2][8] + pHAD_signal[3][8];
                        } // end  HAD 
                    } //end channel loop
                    Run375259_pEM_COMvsCent[8]->Fill(pEM_signal_col[8]);
                        Run375259_pEM_Profile[8]->Fill(0.0 , pEM_signal[0][8]);
                        Run375259_pEM_Profile[8]->Fill(1.0 , pEM_signal[1][8]);
                        Run375259_pEM_Profile[8]->Fill(2.0 , pEM_signal[2][8]);
                        Run375259_pEM_Profile[8]->Fill(3.0 , pEM_signal[3][8]);
                        Run375259_pEM_Profile[8]->Fill(4.0 , pEM_signal[4][8]);
                    Run375259_pRPDx_vs_pEMx[8]->Fill(pRPD_signal_col[8], pEM_signal_col[8]);
                    Run375259_pRPD_COM[8]->Fill(pRPD_signal_col[8], pRPD_signal_row[8]);
                            pos_rpd_xprojection[8]->Fill(pRPD_signal_col[8]);
                            Run375259_pRPD_prof[8]->Fill(0.0,pRPDX1[8]);
                            Run375259_pRPD_prof[8]->Fill(1.0,pRPDX2[8]);
                            Run375259_pRPD_prof[8]->Fill(2.0,pRPDX3[8]);
                            Run375259_pRPD_prof[8]->Fill(3.0,pRPDX4[8]);

                            Run375259_pRPD_Avg_Y_Sig[8]->Fill(0.0, pRPDY1[8]);
                            Run375259_pRPD_Avg_Y_Sig[8]->Fill(1.0, pRPDY2[8]);
                            Run375259_pRPD_Avg_Y_Sig[8]->Fill(2.0, pRPDY3[8]);
                            Run375259_pRPD_Avg_Y_Sig[8]->Fill(3.0, pRPDY4[8]);

                            Run375259_pRPD_HeatMap[8]->Fill(0.5,3.5,pRPD_signal[0][8]);
                            Run375259_pRPD_HeatMap[8]->Fill(1.5,3.5,pRPD_signal[1][8]);
                            Run375259_pRPD_HeatMap[8]->Fill(2.5,3.5,pRPD_signal[2][8]);
                            Run375259_pRPD_HeatMap[8]->Fill(3.5,3.5,pRPD_signal[3][8]);

                            Run375259_pRPD_HeatMap[8]->Fill(0.5,2.5,pRPD_signal[4][8]);
                            Run375259_pRPD_HeatMap[8]->Fill(1.5,2.5,pRPD_signal[5][8]);
                            Run375259_pRPD_HeatMap[8]->Fill(2.5,2.5,pRPD_signal[6][8]);
                            Run375259_pRPD_HeatMap[8]->Fill(3.5,2.5,pRPD_signal[7][8]);

                            Run375259_pRPD_HeatMap[8]->Fill(0.5,1.5,pRPD_signal[8][8]);
                            Run375259_pRPD_HeatMap[8]->Fill(1.5,1.5,pRPD_signal[9][8]);
                            Run375259_pRPD_HeatMap[8]->Fill(2.5,1.5,pRPD_signal[10][8]);
                            Run375259_pRPD_HeatMap[8]->Fill(3.5,1.5,pRPD_signal[11][8]);

                            Run375259_pRPD_HeatMap[8]->Fill(0.5,0.5,pRPD_signal[12][8]);
                            Run375259_pRPD_HeatMap[8]->Fill(1.5,0.5,pRPD_signal[13][8]);
                            Run375259_pRPD_HeatMap[8]->Fill(2.5,0.5,pRPD_signal[14][8]);
                            Run375259_pRPD_HeatMap[8]->Fill(3.5,0.5,pRPD_signal[15][8]);
                    ZDC[8] = 0.1 * pEM_signal_total[8] + pHAD_signal_total[8];
                    Run375259_pRPD_position_vstotalsignal[8]->Fill(ZDC[8], pRPD_signal_col[8]);
                    Run375259_pEM_position_vstotalsignal[8]->Fill(ZDC[8], pEM_signal_col[8]);
                    Run375259_NeutronPlotProjection[8]->Fill(ZDC[8]);
                    Run375259_NeutronPlot[8]->Fill(ZDC[8],pEM_signal_total[8]);
                } // end of hibin 160 to 180
                if (hibin >=180 && hibin < 200 ){ 
                            for (int n = 0; n < 56; n++) {
                                if (zside[n] == 1 && section[n] == 4) {
                                    if (channel[n] == 1) {
                                    Run375259_pRPD_TS[10][9]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[10][9]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[10][9]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[10][9]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[10][9]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[10][9]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[10][9] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[10][9]->Fill(pRPD_ratio[10][9]);

                                    if (pRPD_ratio[10][9] > 1.5 && pRPD_ratio[10][9] < 2.0) {
                                    pRPD_signal[10][9] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[10][9]->Fill(pRPD_signal[10][9]);
                                    
                                    }
                                    if (channel[n] == 2) {
                                    Run375259_pRPD_TS[6][9]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[6][9]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[6][9]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[6][9]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[6][9]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[6][9]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[6][9] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[6][9]->Fill(pRPD_ratio[6][9]);
                                    
                                    if (pRPD_ratio[6][9] > 1.5 && pRPD_ratio[6][9] < 2.1) {
                                    pRPD_signal[6][9] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[6][9]->Fill(pRPD_signal[6][9]);
                                    
                                    } 
                                    if (channel[n] == 3) {
                                    Run375259_pRPD_TS[2][9]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[2][9]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[2][9]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[2][9]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[2][9]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[2][9]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[2][9] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[2][9]->Fill(pRPD_ratio[2][9]);
                                    
                                    if (pRPD_ratio[2][9] > 1.5 && pRPD_ratio[2][9] < 2.0) {
                                    pRPD_signal[2][9] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[2][9]->Fill(pRPD_signal[2][9]);
                                    
                                    }      
                                    if (channel[n] == 4) {
                                    Run375259_pRPD_TS[14][9]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[14][9]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[14][9]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[14][9]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[14][9]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[14][9]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[14][9] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[14][9]->Fill(pRPD_ratio[14][9]);

                                    if (pRPD_ratio[14][9] > 1.5 && pRPD_ratio[14][9] < 2.0) {
                                    pRPD_signal[14][9] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[14][9]->Fill(pRPD_signal[14][9]);
                                    
                                    }   
                                    if (channel[n] == 5) {
                                    Run375259_pRPD_TS[11][9]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[11][9]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[11][9]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[11][9]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[11][9]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[11][9]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[11][9] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[11][9]->Fill(pRPD_ratio[11][9]);
                                    
                                    if (pRPD_ratio[11][9] > 1.5 && pRPD_ratio[11][9] < 2.1) {
                                    pRPD_signal[11][9] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[11][9]->Fill(pRPD_signal[11][9]);
                                    
                                    }   
                                    if (channel[n] == 6) {
                                    Run375259_pRPD_TS[7][9]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[7][9]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[7][9]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[7][9]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[7][9]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[7][9]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[7][9] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[7][9]->Fill(pRPD_ratio[7][9]);
                                    
                                    if (pRPD_ratio[7][9] > 1.6 && pRPD_ratio[7][9] < 2.4) {
                                    pRPD_signal[7][9] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[7][9]->Fill(pRPD_signal[7][9]);
                                    
                                    }   
                                    if (channel[n] == 7) {
                                    Run375259_pRPD_TS[3][9]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[3][9]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[3][9]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[3][9]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[3][9]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[3][9]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[3][9] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[3][9]->Fill(pRPD_ratio[3][9]);
                                    
                                    if (pRPD_ratio[3][9] > 1.5 && pRPD_ratio[3][9] < 2.4) {
                                    pRPD_signal[3][9] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[3][9]->Fill(pRPD_signal[3][9]);
                                    
                                    }   
                                    if (channel[n] == 8) {
                                    Run375259_pRPD_TS[15][9]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[15][9]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[15][9]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[15][9]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[15][9]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[15][9]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[15][9] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[15][9]->Fill(pRPD_ratio[15][9]);

                                    if (pRPD_ratio[15][9] > 1.6 && pRPD_ratio[15][9] < 2.2) {
                                    pRPD_signal[15][9] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[15][9]->Fill(pRPD_signal[15][9]);
                                    }   
                                    if (channel[n] == 9) {
                                    Run375259_pRPD_TS[4][9]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[4][9]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[4][9]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[4][9]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[4][9]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[4][9]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[4][9] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[4][9]->Fill(pRPD_ratio[4][9]);

                                    if (pRPD_ratio[4][9] > 1.5 && pRPD_ratio[4][9] < 2.4 ) {
                                    pRPD_signal[4][9] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[4][9]->Fill(pRPD_signal[4][9]);
                                    }   
                                    if (channel[n] == 10) {
                                    Run375259_pRPD_TS[8][9]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[8][9]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[8][9]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[8][9]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[8][9]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[8][9]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[8][9] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[8][9]->Fill(pRPD_ratio[8][9]);

                                    if (pRPD_ratio[8][9] > 1.5 && pRPD_ratio[8][9] < 2.3) {
                                    pRPD_signal[8][9] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[8][9]->Fill(pRPD_signal[8][9]);
                                    }   
                                    if (channel[n] == 11) {
                                    Run375259_pRPD_TS[12][9]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[12][9]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[12][9]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[12][9]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[12][9]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[12][9]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[12][9] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[12][9]->Fill(pRPD_ratio[12][9]);

                                    if (pRPD_ratio[12][9] > 1.5 && pRPD_ratio[12][9] < 2.2){
                                    pRPD_signal[12][9] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[12][9]->Fill(pRPD_signal[12][9]);
                                    }   
                                    if (channel[n] == 12) {
                                    Run375259_pRPD_TS[0][9]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[0][9]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[0][9]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[0][9]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[0][9]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[0][9]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[0][9] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[0][9]->Fill(pRPD_ratio[0][9]);

                                    if (pRPD_ratio[0][9] > 1.5 && pRPD_ratio[0][9] < 2.3){
                                    pRPD_signal[0][9] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[0][9]->Fill(pRPD_signal[0][9]);
                                    }   
                                    if (channel[n] == 13) {
                                    Run375259_pRPD_TS[5][9]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[5][9]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[5][9]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[5][9]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[5][9]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[5][9]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[5][9] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[5][9]->Fill(pRPD_ratio[5][9]);

                                    if (pRPD_ratio[5][9] > 1.7 && pRPD_ratio[5][9] < 2.5){
                                    pRPD_signal[5][9] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[5][9]->Fill(pRPD_signal[5][9]);
                                    }   
                                    if (channel[n] == 14) {
                                    Run375259_pRPD_TS[9][9]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[9][9]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[9][9]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[9][9]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[9][9]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[9][9]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[9][9] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[9][9]->Fill(pRPD_ratio[9][9]);
                                    
                                    if (pRPD_ratio[9][9] > 1.6 && pRPD_ratio[9][9] < 2.4) {
                                    pRPD_signal[9][9] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[9][9]->Fill(pRPD_signal[9][9]);
                                    }   
                                    if (channel[n] == 15) {
                                    Run375259_pRPD_TS[13][9]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[13][9]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[13][9]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[13][9]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[13][9]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[13][9]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[13][9] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[13][9]->Fill(pRPD_ratio[13][9]);

                                    if (pRPD_ratio[13][9] > 1.6 && pRPD_ratio[13][9] < 2.4) {
                                    pRPD_signal[13][9] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[13][9]->Fill(pRPD_signal[13][9]);
                                    }   
                                    if (channel[n] == 16) {
                                    Run375259_pRPD_TS[1][9]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[1][9]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[1][9]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[1][9]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[1][9]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[1][9]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[1][9] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[1][9]->Fill(pRPD_ratio[1][9]);

                                    if (pRPD_ratio[1][9] > 1.5 && pRPD_ratio[1][9] < 2.5) {
                                    pRPD_signal[1][9] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[1][9]->Fill(pRPD_signal[1][9]);
                                    }            
                                    pRPDX1[9] = pRPD_signal[0][9] + pRPD_signal[4][9] + pRPD_signal[8][9] + pRPD_signal[12][9];                   
                                    pRPDX2[9] = pRPD_signal[1][9] + pRPD_signal[5][9] + pRPD_signal[9][9] + pRPD_signal[13][9];  
                                    pRPDX3[9] = pRPD_signal[2][9] + pRPD_signal[6][9] + pRPD_signal[10][9] + pRPD_signal[14][9];  
                                    pRPDX4[9] = pRPD_signal[3][9] + pRPD_signal[7][9] + pRPD_signal[11][9] + pRPD_signal[15][9];  

                                    pRPDY1[9] = pRPD_signal[0][9] + pRPD_signal[1][9] + pRPD_signal[2][9] + pRPD_signal[3][9];  
                                    pRPDY2[9] = pRPD_signal[4][9] + pRPD_signal[5][9] + pRPD_signal[6][9] + pRPD_signal[7][9];  
                                    pRPDY3[9] = pRPD_signal[8][9] + pRPD_signal[9][9] + pRPD_signal[10][9] + pRPD_signal[11][9];  
                                    pRPDY4[9] = pRPD_signal[12][9] + pRPD_signal[13][9] + pRPD_signal[14][9] + pRPD_signal[15][9];  

                                    pRPD_signal_total[9] = pRPDX1[9] + pRPDX2[9] + pRPDX3[9] + pRPDX4[9];

                                    pRPD_signal_col[9] = ((-3*pRPDX1[9]) + (-1*pRPDX2[9]) + (1*pRPDX3[9]) + (3*pRPDX4[9])) / pRPD_signal_total[9];
                                    pRPD_signal_row[9] = ((-3*pRPDY4[9]) + (-1*pRPDY3[9]) + (1*pRPDY2[9]) + (3*pRPDY1[9])) / pRPD_signal_total[9];

                                } // end of side and section
                                /*
                            
                                if (zside[n] == 1 && section[n] == 1) {
                                if (channel[n] == 1) {
                                    Run375259_pEM_TS[0][9]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[0][9]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[0][9]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[0][9]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[0][9]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[0][9]->Fill(5.0, TS5[n]);

                                    pEM_ratio[0][9] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[0][9]->Fill(pEM_ratio[0][9]);

                                    //if (pEM_ratio[0][9] > 0.8 && pEM_ratio[0][9] < 1.2){
                                        pEM_signal[0][9] = TS2[n] - TS1[n];
                                    //}
                                    if (pEM_ratio[0][9] < 2){
                                        pEM_JunkTS[0]->Fill(0.0,TS0[n]);
                                        pEM_JunkTS[0]->Fill(1.0,TS1[n]);
                                        pEM_JunkTS[0]->Fill(2.0,TS2[n]);
                                        pEM_JunkTS[0]->Fill(3.0,TS3[n]);
                                        pEM_JunkTS[0]->Fill(4.0,TS4[n]);
                                        pEM_JunkTS[0]->Fill(5.0,TS5[n]);
                                    }
                                    if (pEM_ratio[0][9] > 2){
                                        pEM_GoodTS[0]->Fill(0.0,TS0[n]);
                                        pEM_GoodTS[0]->Fill(1.0,TS1[n]);
                                        pEM_GoodTS[0]->Fill(2.0,TS2[n]);
                                        pEM_GoodTS[0]->Fill(3.0,TS3[n]);
                                        pEM_GoodTS[0]->Fill(4.0,TS4[n]);
                                        pEM_GoodTS[0]->Fill(5.0,TS5[n]);
                                    }
                                    Run375259_pEM_fC[0][9]->Fill(pEM_signal[0][9]);
                                }
                                if (channel[n] == 2) {
                                    Run375259_pEM_TS[1][9]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[1][9]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[1][9]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[1][9]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[1][9]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[1][9]->Fill(5.0, TS5[n]);

                                    pEM_ratio[1][9] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[1][9]->Fill(pEM_ratio[1][9]);

                                    //if (pEM_ratio[1][9] > 0.8 && pEM_ratio[1][9] < 1.2){
                                        pEM_signal[1][9] = TS2[n] - TS1[n];
                                    //}
                                    if (pEM_ratio[1][9] < 2){
                                        pEM_JunkTS[1]->Fill(0.0,TS0[n]);
                                        pEM_JunkTS[1]->Fill(1.0,TS1[n]);
                                        pEM_JunkTS[1]->Fill(2.0,TS2[n]);
                                        pEM_JunkTS[1]->Fill(3.0,TS3[n]);
                                        pEM_JunkTS[1]->Fill(4.0,TS4[n]);
                                        pEM_JunkTS[1]->Fill(5.0,TS5[n]);
                                    }
                                    if (pEM_ratio[1][9] > 2){
                                        pEM_GoodTS[1]->Fill(0.0,TS0[n]);
                                        pEM_GoodTS[1]->Fill(1.0,TS1[n]);
                                        pEM_GoodTS[1]->Fill(2.0,TS2[n]);
                                        pEM_GoodTS[1]->Fill(3.0,TS3[n]);
                                        pEM_GoodTS[1]->Fill(4.0,TS4[n]);
                                        pEM_GoodTS[1]->Fill(5.0,TS5[n]);
                                    }
                                    Run375259_pEM_fC[1][9]->Fill(pEM_signal[1][9]);
                                }
                                if (channel[n] == 3){
                                    Run375259_pEM_TS[2][9]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[2][9]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[2][9]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[2][9]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[2][9]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[2][9]->Fill(5.0, TS5[n]);

                                    pEM_ratio[2][9] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[2][9]->Fill(pEM_ratio[2][9]);

                                    //if (pEM_ratio[2][9] > 0.8 && pEM_ratio[2][9] < 1.2){
                                        pEM_signal[2][9] = TS2[n] - TS1[n];
                                    //}
                                    if (pEM_ratio[2][9] < 2){
                                        pEM_JunkTS[2]->Fill(0.0,TS0[n]);
                                        pEM_JunkTS[2]->Fill(1.0,TS1[n]);
                                        pEM_JunkTS[2]->Fill(2.0,TS2[n]);
                                        pEM_JunkTS[2]->Fill(3.0,TS3[n]);
                                        pEM_JunkTS[2]->Fill(4.0,TS4[n]);
                                        pEM_JunkTS[2]->Fill(5.0,TS5[n]);
                                    }
                                    if (pEM_ratio[2][9] > 2){
                                        pEM_GoodTS[2]->Fill(0.0,TS0[n]);
                                        pEM_GoodTS[2]->Fill(1.0,TS1[n]);
                                        pEM_GoodTS[2]->Fill(2.0,TS2[n]);
                                        pEM_GoodTS[2]->Fill(3.0,TS3[n]);
                                        pEM_GoodTS[2]->Fill(4.0,TS4[n]);
                                        pEM_GoodTS[2]->Fill(5.0,TS5[n]);
                                    }
                                    Run375259_pEM_fC[2][9]->Fill(pEM_signal[2][9]);
                                }
                                if (channel[n] == 4){
                                    Run375259_pEM_TS[3][9]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[3][9]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[3][9]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[3][9]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[3][9]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[3][9]->Fill(5.0, TS5[n]);

                                    pEM_ratio[3][9] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[3][9]->Fill(pEM_ratio[3][9]);

                                    //if (pEM_ratio[3][9] > 0.8 && pEM_ratio[3][9] < 1.2){
                                        pEM_signal[3][9] = TS2[n] - TS1[n];
                                    //}
                                    if (pEM_ratio[3][9] < 2){
                                        pEM_JunkTS[3]->Fill(0.0,TS0[n]);
                                        pEM_JunkTS[3]->Fill(1.0,TS1[n]);
                                        pEM_JunkTS[3]->Fill(2.0,TS2[n]);
                                        pEM_JunkTS[3]->Fill(3.0,TS3[n]);
                                        pEM_JunkTS[3]->Fill(4.0,TS4[n]);
                                        pEM_JunkTS[3]->Fill(5.0,TS5[n]);
                                    }
                                    if (pEM_ratio[3][9] > 2){
                                        pEM_GoodTS[3]->Fill(0.0,TS0[n]);
                                        pEM_GoodTS[3]->Fill(1.0,TS1[n]);
                                        pEM_GoodTS[3]->Fill(2.0,TS2[n]);
                                        pEM_GoodTS[3]->Fill(3.0,TS3[n]);
                                        pEM_GoodTS[3]->Fill(4.0,TS4[n]);
                                        pEM_GoodTS[3]->Fill(5.0,TS5[n]);
                                    }
                                    Run375259_pEM_fC[3][9]->Fill(pEM_signal[3][9]);
                                }
                                if (channel[n] == 5){
                                    Run375259_pEM_TS[4][9]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[4][9]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[4][9]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[4][9]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[4][9]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[4][9]->Fill(5.0, TS5[n]);

                                    pEM_ratio[4][9] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[4][9]->Fill(pEM_ratio[4][9]);

                                    //if (pEM_ratio[4][9] > 0.8 && pEM_ratio[4][9] < 1.2){
                                        pEM_signal[4][9] = TS2[n] - TS1[n];
                                    //}
                                    if (pEM_ratio[4][9] < 2){
                                        pEM_JunkTS[4]->Fill(0.0,TS0[n]);
                                        pEM_JunkTS[4]->Fill(1.0,TS1[n]);
                                        pEM_JunkTS[4]->Fill(2.0,TS2[n]);
                                        pEM_JunkTS[4]->Fill(3.0,TS3[n]);
                                        pEM_JunkTS[4]->Fill(4.0,TS4[n]);
                                        pEM_JunkTS[4]->Fill(5.0,TS5[n]);
                                    }
                                    if (pEM_ratio[4][9] > 2){
                                        pEM_GoodTS[4]->Fill(0.0,TS0[n]);
                                        pEM_GoodTS[4]->Fill(1.0,TS1[n]);
                                        pEM_GoodTS[4]->Fill(2.0,TS2[n]);
                                        pEM_GoodTS[4]->Fill(3.0,TS3[n]);
                                        pEM_GoodTS[4]->Fill(4.0,TS4[n]);
                                        pEM_GoodTS[4]->Fill(5.0,TS5[n]);
                                    }
                                    Run375259_pEM_fC[4][9]->Fill(pEM_signal[4][9]);
                                }
                                 pEM_signal_total[9] = (0.6 * pEM_signal[0][9]) + (0.89 * pEM_signal[1][9]) + (1 * pEM_signal[2][9]) + (1.29 * pEM_signal[3][9]) + (0.57 * pEM_signal[4][9]);
                                pEM_signal_col[9] = ((-3.6 * 0.6 * pEM_signal[0][9]) + (-1.8 * 0.89 * pEM_signal[1][9]) + (0 * 1 * pEM_signal[2][9]) + (1.8 * 1.29 * pEM_signal[3][9]) + (3.6 * 0.59 * pEM_signal[4][9])) / pEM_signal_total[9];
                            } // end of side & section
                       
                    if (zside[n] == 1 && section[n] == 2){
                        
                        if (channel[n] == 1){
                            Run375259_pHAD_TS[0][9]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[0][9]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[0][9]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[0][9]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[0][9]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[0][9]->Fill(5.0,TS5[n]);
                            pHAD_ratio[0][9] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[0][9]->Fill(pHAD_ratio[0][9]);
                            //if (pHAD_ratio[0][9] > 3.5 && pHAD_ratio[0][9] < 4){
                                pHAD_signal[0][9] = TS2[n] - TS1[n];
                            //}
                            if (pHAD_ratio[0][9] < 2){
                                        pHAD_JunkTS[0]->Fill(0.0,TS0[n]);
                                        pHAD_JunkTS[0]->Fill(1.0,TS1[n]);
                                        pHAD_JunkTS[0]->Fill(2.0,TS2[n]);
                                        pHAD_JunkTS[0]->Fill(3.0,TS3[n]);
                                        pHAD_JunkTS[0]->Fill(4.0,TS4[n]);
                                        pHAD_JunkTS[0]->Fill(5.0,TS5[n]);
                                    }
                            if (pHAD_ratio[0][9] > 2){
                                        pHAD_GoodTS[0]->Fill(0.0,TS0[n]);
                                        pHAD_GoodTS[0]->Fill(1.0,TS1[n]);
                                        pHAD_GoodTS[0]->Fill(2.0,TS2[n]);
                                        pHAD_GoodTS[0]->Fill(3.0,TS3[n]);
                                        pHAD_GoodTS[0]->Fill(4.0,TS4[n]);
                                        pHAD_GoodTS[0]->Fill(5.0,TS5[n]);
                                    }
                            Run375259_pHAD_fC[0][9]->Fill(pHAD_signal[0][9]);
                        }
                        if (channel[n] == 2){
                            Run375259_pHAD_TS[1][9]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[1][9]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[1][9]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[1][9]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[1][9]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[1][9]->Fill(5.0,TS5[n]);
                            pHAD_ratio[1][9] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[1][9]->Fill(pHAD_ratio[1][9]);
                            //if (pHAD_ratio[1][9] > 3.5 && pHAD_ratio[1][9] < 4.5){
                                pHAD_signal[1][9] = TS2[n] - TS1[n];
                            //}
                            if (pHAD_ratio[1][9] < 2){
                                        pHAD_JunkTS[1]->Fill(0.0,TS0[n]);
                                        pHAD_JunkTS[1]->Fill(1.0,TS1[n]);
                                        pHAD_JunkTS[1]->Fill(2.0,TS2[n]);
                                        pHAD_JunkTS[1]->Fill(3.0,TS3[n]);
                                        pHAD_JunkTS[1]->Fill(4.0,TS4[n]);
                                        pHAD_JunkTS[1]->Fill(5.0,TS5[n]);
                                    }
                            if (pHAD_ratio[1][9] > 2){
                                        pHAD_GoodTS[1]->Fill(0.0,TS0[n]);
                                        pHAD_GoodTS[1]->Fill(1.0,TS1[n]);
                                        pHAD_GoodTS[1]->Fill(2.0,TS2[n]);
                                        pHAD_GoodTS[1]->Fill(3.0,TS3[n]);
                                        pHAD_GoodTS[1]->Fill(4.0,TS4[n]);
                                        pHAD_GoodTS[1]->Fill(5.0,TS5[n]);
                                    }
                            Run375259_pHAD_fC[1][9]->Fill(pHAD_signal[1][9]);
                        }
                        if (channel[n] == 3){
                            Run375259_pHAD_TS[2][9]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[2][9]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[2][9]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[2][9]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[2][9]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[2][9]->Fill(5.0,TS5[n]);

                            pHAD_ratio[2][9] = (TS2[n] / TS3[n]);

                            pHAD_TSratio[2][9]->Fill(pHAD_ratio[2][9]);
                            //if (pHAD_ratio[2][9] > 3.5 && pHAD_ratio[2][9] < 5){
                                pHAD_signal[2][9] = TS2[n] - TS1[n];
                            //}
                            if (pHAD_ratio[2][9] < 2){
                                        pHAD_JunkTS[2]->Fill(0.0,TS0[n]);
                                        pHAD_JunkTS[2]->Fill(1.0,TS1[n]);
                                        pHAD_JunkTS[2]->Fill(2.0,TS2[n]);
                                        pHAD_JunkTS[2]->Fill(3.0,TS3[n]);
                                        pHAD_JunkTS[2]->Fill(4.0,TS4[n]);
                                        pHAD_JunkTS[2]->Fill(5.0,TS5[n]);
                                    }
                            if (pHAD_ratio[0][9] > 2){
                                        pHAD_GoodTS[2]->Fill(0.0,TS0[n]);
                                        pHAD_GoodTS[2]->Fill(1.0,TS1[n]);
                                        pHAD_GoodTS[2]->Fill(2.0,TS2[n]);
                                        pHAD_GoodTS[2]->Fill(3.0,TS3[n]);
                                        pHAD_GoodTS[2]->Fill(4.0,TS4[n]);
                                        pHAD_GoodTS[2]->Fill(5.0,TS5[n]);
                                    }
                            Run375259_pHAD_fC[2][9]->Fill(pHAD_signal[2][9]);
                        }
                        if (channel[n] == 4){
                            Run375259_pHAD_TS[3][9]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[3][9]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[3][9]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[3][9]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[3][9]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[3][9]->Fill(5.0,TS5[n]);
                            pHAD_ratio[3][9] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[3][9]->Fill(pHAD_ratio[3][9]);
                            //if (pHAD_ratio[3][9] > 4 && pHAD_ratio[3][9] < 5){
                                pHAD_signal[3][9] = TS2[n] - TS1[n];
                            //}
                            if (pHAD_ratio[3][9] < 2){
                                        pHAD_JunkTS[3]->Fill(0.0,TS0[n]);
                                        pHAD_JunkTS[3]->Fill(1.0,TS1[n]);
                                        pHAD_JunkTS[3]->Fill(2.0,TS2[n]);
                                        pHAD_JunkTS[3]->Fill(3.0,TS3[n]);
                                        pHAD_JunkTS[3]->Fill(4.0,TS4[n]);
                                        pHAD_JunkTS[3]->Fill(5.0,TS5[n]);
                                    }
                            if (pHAD_ratio[3][9] > 2){
                                        pHAD_GoodTS[3]->Fill(0.0,TS0[n]);
                                        pHAD_GoodTS[3]->Fill(1.0,TS1[n]);
                                        pHAD_GoodTS[3]->Fill(2.0,TS2[n]);
                                        pHAD_GoodTS[3]->Fill(3.0,TS3[n]);
                                        pHAD_GoodTS[3]->Fill(4.0,TS4[n]);
                                        pHAD_GoodTS[3]->Fill(5.0,TS5[n]);
                                    }
                            Run375259_pHAD_fC[3][9]->Fill(pHAD_signal[3][9]);
                        }
                        pHAD_signal_total[9] = pHAD_signal[0][9] + pHAD_signal[1][9] + pHAD_signal[2][9] + pHAD_signal[3][9];
                        } // end  HAD 
                        */
                    } //end channel loop
                     Run375259_pEM_COMvsCent[9]->Fill(pEM_signal_col[9]);
                    Run375259_pEM_Profile[9]->Fill(0.0 , pEM_signal[0][9]);
                    Run375259_pEM_Profile[9]->Fill(1.0 , pEM_signal[1][9]);
                    Run375259_pEM_Profile[9]->Fill(2.0 , pEM_signal[2][9]);
                    Run375259_pEM_Profile[9]->Fill(3.0 , pEM_signal[3][9]);
                    Run375259_pEM_Profile[9]->Fill(4.0 , pEM_signal[4][9]);
                    Run375259_pRPDx_vs_pEMx[9]->Fill(pRPD_signal_col[9], pEM_signal_col[9]);
                    Run375259_pRPD_COM[9]->Fill(pRPD_signal_col[9], pRPD_signal_row[9]);
                    pos_rpd_xprojection[9]->Fill(pRPD_signal_col[9]);
                    Run375259_pRPD_prof[9]->Fill(0.0,pRPDX1[9]);
                    Run375259_pRPD_prof[9]->Fill(1.0,pRPDX2[9]);
                    Run375259_pRPD_prof[9]->Fill(2.0,pRPDX3[9]);
                    Run375259_pRPD_prof[9]->Fill(3.0,pRPDX4[9]);

                    Run375259_pRPD_Avg_Y_Sig[9]->Fill(0.0, pRPDY1[9]);
                    Run375259_pRPD_Avg_Y_Sig[9]->Fill(1.0, pRPDY2[9]);
                    Run375259_pRPD_Avg_Y_Sig[9]->Fill(2.0, pRPDY3[9]);
                    Run375259_pRPD_Avg_Y_Sig[9]->Fill(3.0, pRPDY4[9]);

                    Run375259_pRPD_HeatMap[9]->Fill(0.5,3.5,pRPD_signal[0][9]);
                    Run375259_pRPD_HeatMap[9]->Fill(1.5,3.5,pRPD_signal[1][9]);
                    Run375259_pRPD_HeatMap[9]->Fill(2.5,3.5,pRPD_signal[2][9]);
                    Run375259_pRPD_HeatMap[9]->Fill(3.5,3.5,pRPD_signal[3][9]);

                    Run375259_pRPD_HeatMap[9]->Fill(0.5,2.5,pRPD_signal[4][9]);
                    Run375259_pRPD_HeatMap[9]->Fill(1.5,2.5,pRPD_signal[5][9]);
                    Run375259_pRPD_HeatMap[9]->Fill(2.5,2.5,pRPD_signal[6][9]);
                    Run375259_pRPD_HeatMap[9]->Fill(3.5,2.5,pRPD_signal[7][9]);

                    Run375259_pRPD_HeatMap[9]->Fill(0.5,1.5,pRPD_signal[8][9]);
                    Run375259_pRPD_HeatMap[9]->Fill(1.5,1.5,pRPD_signal[9][9]);
                    Run375259_pRPD_HeatMap[9]->Fill(2.5,1.5,pRPD_signal[10][9]);
                    Run375259_pRPD_HeatMap[9]->Fill(3.5,1.5,pRPD_signal[11][9]);

                    Run375259_pRPD_HeatMap[9]->Fill(0.5,0.5,pRPD_signal[12][9]);
                    Run375259_pRPD_HeatMap[9]->Fill(1.5,0.5,pRPD_signal[13][9]);
                    Run375259_pRPD_HeatMap[9]->Fill(2.5,0.5,pRPD_signal[14][9]);
                    Run375259_pRPD_HeatMap[9]->Fill(3.5,0.5,pRPD_signal[15][9]);
                    ZDC[9] = 0.1 * pEM_signal_total[9] + pHAD_signal_total[9];
                    Run375259_pRPD_position_vstotalsignal[9]->Fill(ZDC[9], pRPD_signal_col[9]);
                    Run375259_pEM_position_vstotalsignal[9]->Fill(ZDC[9], pEM_signal_col[9]);
                    Run375259_NeutronPlotProjection[9]->Fill(ZDC[9]);
                    Run375259_NeutronPlot[9]->Fill(ZDC[9],pEM_signal_total[9]);
                } // end of hibin
                if (hibin >=0 && hibin <= 200){
                    for (int n = 0; n < 56; n++) {
                        if (zside[n] == 1 && section[n] == 4) {
                                    if (channel[n] == 1) {
                                    Run375259_pRPD_TS[10][10]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[10][10]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[10][10]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[10][10]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[10][10]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[10][10]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[10][10] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[10][10]->Fill(pRPD_ratio[10][10]);

                                    if (pRPD_ratio[10][10] > 1.5 && pRPD_ratio[10][10] < 2.0) {
                                    pRPD_signal[10][10] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[10][10]->Fill(pRPD_signal[10][10]);
                                    
                                    }
                                    if (channel[n] == 2) {
                                    Run375259_pRPD_TS[6][10]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[6][10]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[6][10]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[6][10]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[6][10]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[6][10]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[6][10] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[6][10]->Fill(pRPD_ratio[6][10]);
                                    
                                    if (pRPD_ratio[6][10] > 1.5 && pRPD_ratio[6][10] < 2.1) {
                                    pRPD_signal[6][10] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[6][10]->Fill(pRPD_signal[6][10]);
                                    
                                    } 
                                    if (channel[n] == 3) {
                                    Run375259_pRPD_TS[2][10]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[2][10]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[2][10]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[2][10]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[2][10]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[2][10]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[2][10] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[2][10]->Fill(pRPD_ratio[2][10]);
                                    
                                    if (pRPD_ratio[2][10] > 1.5 && pRPD_ratio[2][10] < 2.0) {
                                    pRPD_signal[2][10] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[2][10]->Fill(pRPD_signal[2][10]);
                                    
                                    }      
                                    if (channel[n] == 4) {
                                    Run375259_pRPD_TS[14][10]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[14][10]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[14][10]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[14][10]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[14][10]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[14][10]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[14][10] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[14][10]->Fill(pRPD_ratio[14][10]);

                                    if (pRPD_ratio[14][10] > 1.5 && pRPD_ratio[14][10] < 2.0) {
                                    pRPD_signal[14][10] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[14][10]->Fill(pRPD_signal[14][10]);
                                    
                                    }   
                                    if (channel[n] == 5) {
                                    Run375259_pRPD_TS[11][10]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[11][10]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[11][10]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[11][10]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[11][10]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[11][10]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[11][10] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[11][10]->Fill(pRPD_ratio[11][10]);
                                    
                                    if (pRPD_ratio[11][10] > 1.5 && pRPD_ratio[11][10] < 2.1) {
                                    pRPD_signal[11][10] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[11][10]->Fill(pRPD_signal[11][10]);
                                    
                                    }   
                                    if (channel[n] == 6) {
                                    Run375259_pRPD_TS[7][10]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[7][10]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[7][10]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[7][10]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[7][10]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[7][10]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[7][10] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[7][10]->Fill(pRPD_ratio[7][10]);
                                    
                                    if (pRPD_ratio[7][10] > 1.6 && pRPD_ratio[7][10] < 2.4) {
                                    pRPD_signal[7][10] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[7][10]->Fill(pRPD_signal[7][10]);
                                    
                                    }   
                                    if (channel[n] == 7) {
                                    Run375259_pRPD_TS[3][10]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[3][10]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[3][10]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[3][10]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[3][10]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[3][10]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[3][10] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[3][10]->Fill(pRPD_ratio[3][10]);
                                    
                                    if (pRPD_ratio[3][10] > 1.5 && pRPD_ratio[3][10] < 2.4) {
                                    pRPD_signal[3][10] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[3][10]->Fill(pRPD_signal[3][10]);
                                    
                                    }   
                                    if (channel[n] == 8) {
                                    Run375259_pRPD_TS[15][10]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[15][10]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[15][10]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[15][10]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[15][10]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[15][10]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[15][10] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[15][10]->Fill(pRPD_ratio[15][10]);

                                    if (pRPD_ratio[15][10] > 1.6 && pRPD_ratio[15][10] < 2.2) {
                                    pRPD_signal[15][10] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[15][10]->Fill(pRPD_signal[15][10]);
                                    }   
                                    if (channel[n] == 9) {
                                    Run375259_pRPD_TS[4][10]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[4][10]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[4][10]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[4][10]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[4][10]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[4][10]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[4][10] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[4][10]->Fill(pRPD_ratio[4][10]);

                                    if (pRPD_ratio[4][10] > 1.5 && pRPD_ratio[4][10] < 2.4 ) {
                                    pRPD_signal[4][10] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[4][10]->Fill(pRPD_signal[4][10]);
                                    }   
                                    if (channel[n] == 10) {
                                    Run375259_pRPD_TS[8][10]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[8][10]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[8][10]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[8][10]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[8][10]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[8][10]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[8][10] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[8][10]->Fill(pRPD_ratio[8][10]);

                                    if (pRPD_ratio[8][10] > 1.5 && pRPD_ratio[8][10] < 2.3) {
                                    pRPD_signal[8][10] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[8][10]->Fill(pRPD_signal[8][10]);
                                    }   
                                    if (channel[n] == 11) {
                                    Run375259_pRPD_TS[12][10]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[12][10]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[12][10]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[12][10]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[12][10]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[12][10]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[12][10] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[12][10]->Fill(pRPD_ratio[12][10]);

                                    if (pRPD_ratio[12][10] > 1.5 && pRPD_ratio[12][10] < 2.2){
                                    pRPD_signal[12][10] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[12][10]->Fill(pRPD_signal[12][10]);
                                    }   
                                    if (channel[n] == 12) {
                                    Run375259_pRPD_TS[0][10]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[0][10]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[0][10]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[0][10]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[0][10]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[0][10]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[0][10] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[0][10]->Fill(pRPD_ratio[0][10]);

                                    if (pRPD_ratio[0][10] > 1.5 && pRPD_ratio[0][10] < 2.3){
                                    pRPD_signal[0][10] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[0][10]->Fill(pRPD_signal[0][10]);
                                    }   
                                    if (channel[n] == 13) {
                                    Run375259_pRPD_TS[5][10]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[5][10]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[5][10]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[5][10]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[5][10]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[5][10]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[5][10] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[5][10]->Fill(pRPD_ratio[5][10]);

                                    if (pRPD_ratio[5][10] > 1.7 && pRPD_ratio[5][10] < 2.5){
                                    pRPD_signal[5][10] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[5][10]->Fill(pRPD_signal[5][10]);
                                    }   
                                    if (channel[n] == 14) {
                                    Run375259_pRPD_TS[9][10]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[9][10]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[9][10]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[9][10]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[9][10]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[9][10]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[9][10] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[9][10]->Fill(pRPD_ratio[9][10]);
                                    
                                    if (pRPD_ratio[9][10] > 1.6 && pRPD_ratio[9][10] < 2.4) {
                                    pRPD_signal[9][10] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[9][10]->Fill(pRPD_signal[9][10]);
                                    }   
                                    if (channel[n] == 15) {
                                    Run375259_pRPD_TS[13][10]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[13][10]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[13][10]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[13][10]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[13][10]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[13][10]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[13][10] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[13][10]->Fill(pRPD_ratio[13][10]);

                                    if (pRPD_ratio[13][10] > 1.6 && pRPD_ratio[13][10] < 2.4) {
                                    pRPD_signal[13][10] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[13][10]->Fill(pRPD_signal[13][10]);
                                    }   
                                    if (channel[n] == 16) {
                                    Run375259_pRPD_TS[1][10]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[1][10]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[1][10]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[1][10]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[1][10]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[1][10]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[1][10] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[1][10]->Fill(pRPD_ratio[1][10]);

                                    if (pRPD_ratio[1][10] > 1.5 && pRPD_ratio[1][10] < 2.5) {
                                    pRPD_signal[1][10] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[1][10]->Fill(pRPD_signal[1][10]);
                                    }            
                                    pRPDX1[10] = pRPD_signal[0][10] + pRPD_signal[4][10] + pRPD_signal[8][10] + pRPD_signal[12][10];                   
                                    pRPDX2[10] = pRPD_signal[1][10] + pRPD_signal[5][10] + pRPD_signal[9][10] + pRPD_signal[13][10];  
                                    pRPDX3[10] = pRPD_signal[2][10] + pRPD_signal[6][10] + pRPD_signal[10][10] + pRPD_signal[14][10];  
                                    pRPDX4[10] = pRPD_signal[3][10] + pRPD_signal[7][10] + pRPD_signal[11][10] + pRPD_signal[15][10];  

                                    pRPDY1[10] = pRPD_signal[0][10] + pRPD_signal[1][10] + pRPD_signal[2][10] + pRPD_signal[3][10];  
                                    pRPDY2[10] = pRPD_signal[4][10] + pRPD_signal[5][10] + pRPD_signal[6][10] + pRPD_signal[7][10];  
                                    pRPDY3[10] = pRPD_signal[8][10] + pRPD_signal[9][10] + pRPD_signal[10][10] + pRPD_signal[11][10];  
                                    pRPDY4[10] = pRPD_signal[12][10] + pRPD_signal[13][10] + pRPD_signal[14][10] + pRPD_signal[15][10];  

                                    pRPD_signal_total[10] = pRPDX1[10] + pRPDX2[10] + pRPDX3[10] + pRPDX4[10];

                                    pRPD_signal_col[10] = ((-3*pRPDX1[10]) + (-1*pRPDX2[10]) + (1*pRPDX3[10]) + (3*pRPDX4[10])) / pRPD_signal_total[10];
                                    pRPD_signal_row[10] = ((-3*pRPDY4[10]) + (-1*pRPDY3[10]) + (1*pRPDY2[10]) + (3*pRPDY1[10])) / pRPD_signal_total[10];

                                } // end of side and section
                            
                                if (zside[n] == 1 && section[n] == 1) {
                                if (channel[n] == 1) {
                                    Run375259_pEM_TS[0][10]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[0][10]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[0][10]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[0][10]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[0][10]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[0][10]->Fill(5.0, TS5[n]);

                                    pEM_ratio[0][10] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[0][10]->Fill(pEM_ratio[0][10]);

                                    //if (pEM_ratio[0][10] > 0.8 && pEM_ratio[0][10] < 1.2){
                                        pEM_signal[0][10] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[0][10]->Fill(pEM_signal[0][10]);
                                }
                                if (channel[n] == 2) {
                                    Run375259_pEM_TS[1][10]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[1][10]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[1][10]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[1][10]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[1][10]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[1][10]->Fill(5.0, TS5[n]);

                                    pEM_ratio[1][10] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[1][10]->Fill(pEM_ratio[1][10]);

                                    //if (pEM_ratio[1][10] > 0.8 && pEM_ratio[1][10] < 1.2){
                                        pEM_signal[1][10] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[1][10]->Fill(pEM_signal[1][10]);
                                }
                                if (channel[n] == 3){
                                    Run375259_pEM_TS[2][10]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[2][10]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[2][10]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[2][10]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[2][10]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[2][10]->Fill(5.0, TS5[n]);

                                    pEM_ratio[2][10] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[2][10]->Fill(pEM_ratio[2][10]);

                                    //if (pEM_ratio[2][10] > 0.8 && pEM_ratio[2][10] < 1.2){
                                        pEM_signal[2][10] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[2][10]->Fill(pEM_signal[2][10]);
                                }
                                if (channel[n] == 4){
                                    Run375259_pEM_TS[3][10]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[3][10]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[3][10]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[3][10]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[3][10]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[3][10]->Fill(5.0, TS5[n]);

                                    pEM_ratio[3][10] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[3][10]->Fill(pEM_ratio[3][10]);

                                    //if (pEM_ratio[3][10] > 0.8 && pEM_ratio[3][10] < 1.2){
                                        pEM_signal[3][10] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[3][10]->Fill(pEM_signal[3][10]);
                                }
                                if (channel[n] == 5){
                                    Run375259_pEM_TS[4][10]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[4][10]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[4][10]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[4][10]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[4][10]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[4][10]->Fill(5.0, TS5[n]);

                                    pEM_ratio[4][10] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[4][10]->Fill(pEM_ratio[4][10]);

                                    //if (pEM_ratio[4][10] > 0.8 && pEM_ratio[4][10] < 1.2){
                                        pEM_signal[4][10] = TS2[n] - TS1[n];
                                    //}
                                    Run375259_pEM_fC[4][10]->Fill(pEM_signal[4][10]);
                                }
                                 pEM_signal_total[10] = (0.6 * pEM_signal[0][10]) + (0.89 * pEM_signal[1][10]) + (1 * pEM_signal[2][10]) + (1.29 * pEM_signal[3][10]) + (0.57 * pEM_signal[4][10]);
                                pEM_signal_col[10] = ((-3.6 * 0.6 * pEM_signal[0][10]) + (-1.8 * 0.89 * pEM_signal[1][10]) + (0 * 1 * pEM_signal[2][10]) + (1.8 * 1.29 * pEM_signal[3][10]) + (3.6 * 0.59 * pEM_signal[4][10])) / pEM_signal_total[10];
                            } // end of side & section
                       
                    if (zside[n] == 1 && section[n] == 2){
                        
                        if (channel[n] == 1){
                            Run375259_pHAD_TS[0][10]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[0][10]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[0][10]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[0][10]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[0][10]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[0][10]->Fill(5.0,TS5[n]);
                            pHAD_ratio[0][10] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[0][10]->Fill(pHAD_ratio[0][10]);
                            //if (pHAD_ratio[0][10] > 3.5 && pHAD_ratio[0][10] < 4){
                                pHAD_signal[0][10] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[0][10]->Fill(pHAD_signal[0][10]);
                        }
                        if (channel[n] == 2){
                            Run375259_pHAD_TS[1][10]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[1][10]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[1][10]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[1][10]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[1][10]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[1][10]->Fill(5.0,TS5[n]);
                            pHAD_ratio[1][10] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[1][10]->Fill(pHAD_ratio[1][10]);
                            //if (pHAD_ratio[1][10] > 3.5 && pHAD_ratio[1][10] < 4.5){
                                pHAD_signal[1][10] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[1][10]->Fill(pHAD_signal[1][10]);
                        }
                        if (channel[n] == 3){
                            Run375259_pHAD_TS[2][10]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[2][10]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[2][10]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[2][10]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[2][10]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[2][10]->Fill(5.0,TS5[n]);
                            pHAD_ratio[2][10] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[2][10]->Fill(pHAD_ratio[2][10]);
                            //if (pHAD_ratio[2][10] > 3.5 && pHAD_ratio[2][10] < 5){
                                pHAD_signal[2][10] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[2][10]->Fill(pHAD_signal[2][10]);
                        }
                        if (channel[n] == 4){
                            Run375259_pHAD_TS[3][10]->Fill(0.0,TS0[n]);
                            Run375259_pHAD_TS[3][10]->Fill(1.0,TS1[n]);
                            Run375259_pHAD_TS[3][10]->Fill(2.0,TS2[n]);
                            Run375259_pHAD_TS[3][10]->Fill(3.0,TS3[n]);
                            Run375259_pHAD_TS[3][10]->Fill(4.0,TS4[n]);
                            Run375259_pHAD_TS[3][10]->Fill(5.0,TS5[n]);
                            pHAD_ratio[3][10] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[3][10]->Fill(pHAD_ratio[3][10]);
                            //if (pHAD_ratio[3][10] > 4 && pHAD_ratio[3][10] < 5){
                                pHAD_signal[3][10] = TS2[n] - TS1[n];
                            //}
                            Run375259_pHAD_fC[3][10]->Fill(pHAD_signal[3][10]);
                        }
                        pHAD_signal_total[10] = pHAD_signal[0][10] + pHAD_signal[1][10] + pHAD_signal[2][10] + pHAD_signal[3][10];
                        } // end  HAD 
                    } //end channel loop
                    Run375259_pEM_COMvsCent[10]->Fill(pEM_signal_col[10]);
                    Run375259_pEM_Profile[10]->Fill(0.0 , pEM_signal[0][10]);
                    Run375259_pEM_Profile[10]->Fill(1.0 , pEM_signal[1][10]);
                    Run375259_pEM_Profile[10]->Fill(2.0 , pEM_signal[2][10]);
                    Run375259_pEM_Profile[10]->Fill(3.0 , pEM_signal[3][10]);
                    Run375259_pEM_Profile[10]->Fill(4.0 , pEM_signal[4][10]);
                    Run375259_pRPDx_vs_pEMx[10]->Fill(pRPD_signal_col[10], pEM_signal_col[10]);
                    Run375259_pRPD_COM[10]->Fill(pRPD_signal_col[10], pRPD_signal_row[10]);
                    pos_rpd_xprojection[10]->Fill(pRPD_signal_col[10]);
                    Run375259_pRPD_prof[10]->Fill(0.0,pRPDX1[10]);
                    Run375259_pRPD_prof[10]->Fill(1.0,pRPDX2[10]);
                    Run375259_pRPD_prof[10]->Fill(2.0,pRPDX3[10]);
                    Run375259_pRPD_prof[10]->Fill(3.0,pRPDX4[10]);

                    Run375259_pRPD_Avg_Y_Sig[10]->Fill(0.0, pRPDY1[10]);
                    Run375259_pRPD_Avg_Y_Sig[10]->Fill(1.0, pRPDY2[10]);
                    Run375259_pRPD_Avg_Y_Sig[10]->Fill(2.0, pRPDY3[10]);
                    Run375259_pRPD_Avg_Y_Sig[10]->Fill(3.0, pRPDY4[10]);

                    Run375259_pRPD_HeatMap[10]->Fill(0.5,3.5,pRPD_signal[0][10]);
                    Run375259_pRPD_HeatMap[10]->Fill(1.5,3.5,pRPD_signal[1][10]);
                    Run375259_pRPD_HeatMap[10]->Fill(2.5,3.5,pRPD_signal[2][10]);
                    Run375259_pRPD_HeatMap[10]->Fill(3.5,3.5,pRPD_signal[3][10]);

                    Run375259_pRPD_HeatMap[10]->Fill(0.5,2.5,pRPD_signal[4][10]);
                    Run375259_pRPD_HeatMap[10]->Fill(1.5,2.5,pRPD_signal[5][10]);
                    Run375259_pRPD_HeatMap[10]->Fill(2.5,2.5,pRPD_signal[6][10]);
                    Run375259_pRPD_HeatMap[10]->Fill(3.5,2.5,pRPD_signal[7][10]);

                    Run375259_pRPD_HeatMap[10]->Fill(0.5,1.5,pRPD_signal[8][10]);
                    Run375259_pRPD_HeatMap[10]->Fill(1.5,1.5,pRPD_signal[9][10]);
                    Run375259_pRPD_HeatMap[10]->Fill(2.5,1.5,pRPD_signal[10][10]);
                    Run375259_pRPD_HeatMap[10]->Fill(3.5,1.5,pRPD_signal[11][10]);

                    Run375259_pRPD_HeatMap[10]->Fill(0.5,0.5,pRPD_signal[12][10]);
                    Run375259_pRPD_HeatMap[10]->Fill(1.5,0.5,pRPD_signal[13][10]);
                    Run375259_pRPD_HeatMap[10]->Fill(2.5,0.5,pRPD_signal[14][10]);
                    Run375259_pRPD_HeatMap[10]->Fill(3.5,0.5,pRPD_signal[15][10]);
                    ZDC[10] = 0.1 * pEM_signal_total[10] + pHAD_signal_total[10];
                    Run375259_pRPD_position_vstotalsignal[10]->Fill(ZDC[10], pRPD_signal_col[10]);
                    Run375259_pEM_position_vstotalsignal[10]->Fill(ZDC[10], pEM_signal_col[10]);
                    Run375259_NeutronPlot[10]->Fill(ZDC[10],pEM_signal_total[10]);
                    Run375259_NeutronPlotProjection[10]->Fill(ZDC[10]);
                            
                    } // end hibin    
                //} // end sum cut for all detectors 
                //hibindist->Fill(hibin);

            } // end of event loop
    
    gStyle->SetOptFit();

    for (int n = 0; n < 11; n++){
        Run375259_pRPD_position_vstotalsignal[n]->SetXTitle("0.1 EM + HAD");
        Run375259_pRPD_position_vstotalsignal[n]->SetYTitle("pRPD Position");
    }

    TCanvas *c36 = new TCanvas();
    c36->Divide(4,3);
    for (int n = 0; n < 11; n++){
        c36->cd(n+1);
        Run375259_pRPD_position_vstotalsignal[n]->Draw("colz");
    }

    TCanvas *m1 = new TCanvas();
    Run375259_pRPD_position_vstotalsignal[8]->Draw("colz");

    TCanvas *m2 = new TCanvas();
    Run375259_pRPD_position_vstotalsignal[9]->Draw("colz");

    TCanvas *m3 = new TCanvas();
    Run375259_pRPD_position_vstotalsignal[10]->Draw("colz");
    
    for (int n = 0; n < 11; n++){
       Run375259_pEM_position_vstotalsignal[n]->SetXTitle("0.1EM + HAD");
       Run375259_pEM_position_vstotalsignal[n]->SetYTitle("pos EM Position"); 
    }

    TCanvas *c37 = new TCanvas();
    c37->Divide(4,3);
    for (int n = 0; n < 11; n++){
        c37->cd(n+1);
        Run375259_pEM_position_vstotalsignal[n]->Draw("colz");
    }

    TCanvas *x1 = new TCanvas();
    Run375259_pEM_position_vstotalsignal[0]->Draw("colz");
    TCanvas *x2 = new TCanvas();
    Run375259_pEM_position_vstotalsignal[1]->Draw("colz");
    TCanvas *x3 = new TCanvas();
    Run375259_pEM_position_vstotalsignal[2]->Draw("colz");
    TCanvas *x4 = new TCanvas();
    Run375259_pEM_position_vstotalsignal[3]->Draw("colz");
    TCanvas *x5 = new TCanvas();
    Run375259_pEM_position_vstotalsignal[4]->Draw("colz");
    TCanvas *x6 = new TCanvas();
    Run375259_pEM_position_vstotalsignal[5]->Draw("colz");
    TCanvas *x7 = new TCanvas();
    Run375259_pEM_position_vstotalsignal[6]->Draw("colz");
    TCanvas *x8 = new TCanvas();
    Run375259_pEM_position_vstotalsignal[7]->Draw("colz");
    TCanvas *x9 = new TCanvas();
    Run375259_pEM_position_vstotalsignal[8]->Draw("colz");
    TCanvas *x10 = new TCanvas();
    Run375259_pEM_position_vstotalsignal[9]->Draw("colz");
    TCanvas *x11 = new TCanvas();
    Run375259_pEM_position_vstotalsignal[10]->Draw("colz");

    for (int n = 0; n < 11; n++){
       Run375259_NeutronPlotProjection[n]->SetXTitle("0.1EM + HAD");
       Run375259_NeutronPlotProjection[n]->SetYTitle("Counts"); 
    }

    TCanvas *c38 = new TCanvas();
    c38->Divide(4,3);
    for (int n = 0; n <11; n++){
        c38->cd(n+1);
        Run375259_NeutronPlotProjection[n]->Draw();
    }

    for (int n = 0; n < 11; n++){
       Run375259_NeutronPlot[n]->SetXTitle("0.1EM + HAD");
       Run375259_NeutronPlot[n]->SetYTitle("EM"); 
    }

    TCanvas *c39 = new TCanvas();
    c39->Divide(4,3);
    for (int n = 0; n <11; n++){
        c39->cd(n+1);
        Run375259_NeutronPlot[n]->Draw("colz");
    }

    TCanvas *n1 = new TCanvas();
    Run375259_NeutronPlot[10]->Draw("colz");

    TCanvas *n2 = new TCanvas();
    Run375259_NeutronPlot[9]->Draw("colz");

    TCanvas *n3 = new TCanvas();
    Run375259_NeutronPlotProjection[10]->Draw();

    TCanvas *n4 = new TCanvas();
    Run375259_NeutronPlotProjection[9]->Draw();

    for (int n = 0; n < 5;){
        pEM_JunkTS[n]->SetXTitle("Time Slice");
        pEM_JunkTS[n]->SetXTitle("Total Charge per Time Slice (fC)");
    }

    for (int n = 0; n < 4;){
        pHAD_JunkTS[n]->SetXTitle("Time Slice");
        pHAD_JunkTS[n]->SetXTitle("Total Charge per Time Slice (fC)");
    }

    for (int n = 0; n < 5;){
        pEM_GoodTS[n]->SetXTitle("Time Slice");
        pEM_GoodTS[n]->SetXTitle("Total Charge per Time Slice (fC)");
    }

    for (int n = 0; n < 4;){
        pHAD_GoodTS[n]->SetXTitle("Time Slice");
        pHAD_GoodTS[n]->SetXTitle("Total Charge per Time Slice (fC)");
    }

    TCanvas *j1 = new TCanvas();
    j1->Divide(3,2);
    for(int n = 0; n < 5; n++){
        j1->cd(n+1);
        pEM_JunkTS[n]->Draw("hist e");
    }

    TCanvas *j2 = new TCanvas();
    j2->Divide(2,2);
    for(int n = 0; n < 4; n++){
        j2->cd(n+1);
        pHAD_JunkTS[n]->Draw("hist e");
    }

    TCanvas *j3 = new TCanvas();
    j3->Divide(3,2);
    for(int n = 0; n < 5; n++){
        j3->cd(n+1);
        pEM_GoodTS[n]->Draw("hist e");
    }

    TCanvas *j4 = new TCanvas();
    j4->Divide(2,2);
    for(int n = 0; n < 4; n++){
        j4->cd(n+1);
        pHAD_GoodTS[n]->Draw("hist e");
    }

    j1->Update();
    j2->Update();
    j3->Update();
    j4->Update();
    n1->Update();
    n2->Update();
    n3->Update();
    n4->Update();

    j1->SaveAs("/home/mwrotny/EM/Run375259_pEM_JunkTS.pdf");
    j2->SaveAs("/home/mwrotny/EM/Run375259_pEM_GoodTS.pdf");
    j3->SaveAs("/home/mwrotny/EM/Run375259_pHAD_JunkTS.pdf");
    j4->SaveAs("/home/mwrotny/EM/Run375259_pHAD_GoodTS.pdf");

    n1->SaveAs("/home/mwrotny/RPD/Run375259_NeutronPlotAllCent.pdf");
    n2->SaveAs("/home/mwrotny/RPD/Run375259_NeutronPlot90-100Cent.pdf");
    n3->SaveAs("/home/mwrotny/RPD/Run375259_TotalEnergyDistAllCent.pdf");
    n4->SaveAs("/home/mwrotny/RPD/Run375259_TotalEnergyDist90-100Cent.pdf");
}

