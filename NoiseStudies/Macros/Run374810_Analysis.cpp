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

void Run374810_Analysis()
{
    gROOT->ProcessLine("gErrorIgnoreLevel = 6001;");
    gROOT->ProcessLine("gPrintViaErrorHandler = kTRUE;");

    TChain *zdcchain = new TChain();
    TChain *hichain = new TChain();
    for (int x = 0 ; x < 24 ; x++)
    {
    zdcchain->Add(Form("/store/data/Runs_2023/skims/374810/Run374810_MinBias%i.root/zdcdigi", x));
    hichain->Add(Form("/store/data/Runs_2023/skims/374810/Run374810_MinBias%i.root/HiTree", x));
    }
    zdcchain->AddFriend(hichain);

    int hibin;
    int zside[56];
    int section[56];
    int channel[56];

    float TS0[56];
    float TS1[56];
    float TS2[56];
    float TS3[56];
    float TS4[56];
    float TS5[56];

    float pRPD_ratio[16][11];
    float pEM_ratio[5][11];
    float pHAD_ratio[4][11];

    float pRPD_sig[16][11];
    float pEM_sig[5][11];
    float pHAD_sig[4][11];

    float sumPlus;
    float sumMinus;

    float ZDC[11];
    float pHAD_sigtot[11];
    float pEM_sigtot[11];

    zdcchain->SetBranchAddress("chargefCTs0",&TS0);
    zdcchain->SetBranchAddress("chargefCTs1",&TS1);
    zdcchain->SetBranchAddress("chargefCTs2",&TS2);
    zdcchain->SetBranchAddress("chargefCTs3",&TS3);
    zdcchain->SetBranchAddress("chargefCTs4",&TS4);
    zdcchain->SetBranchAddress("chargefCTs5",&TS5);
    zdcchain->SetBranchAddress("hiBin",&hibin);
    zdcchain->SetBranchAddress("zside",&zside);
    zdcchain->SetBranchAddress("section",&section);
    zdcchain->SetBranchAddress("channel",&channel);
    zdcchain->SetBranchAddress("sumPlus",&sumPlus);
    zdcchain->SetBranchAddress("sumMinus",&sumMinus);

    TH1F *hi = new TH1F("","Run 374810 hiBin Distribution",200,0,200);
    TH1F *SP = new TH1F("","Run 374810 SumPlus Hardcoded Variable (TS2 - TS1)",100,-10000,10000);
    TH1F *SM = new TH1F("","Run 374810 SumMinus Hardcoded Variable (TS2 - TS1)",100,-10000,10000);

    TH1F *pRPD_TSDist[16][11] = {0};

        pRPD_TSDist[0][0] = new TH1F("","Run 374810 Pos RPD TS Distribution All Centrality Block 0",6,0,6);
        pRPD_TSDist[1][0] = new TH1F("","Run 374810 Pos RPD TS Distribution All Centrality Block 1",6,0,6);
        pRPD_TSDist[2][0] = new TH1F("","Run 374810 Pos RPD TS Distribution All Centrality Block 2",6,0,6);
        pRPD_TSDist[3][0] = new TH1F("","Run 374810 Pos RPD TS Distribution All Centrality Block 3",6,0,6);
        pRPD_TSDist[4][0] = new TH1F("","Run 374810 Pos RPD TS Distribution All Centrality Block 4",6,0,6);
        pRPD_TSDist[5][0] = new TH1F("","Run 374810 Pos RPD TS Distribution All Centrality Block 5",6,0,6);
        pRPD_TSDist[6][0] = new TH1F("","Run 374810 Pos RPD TS Distribution All Centrality Block 6",6,0,6);
        pRPD_TSDist[7][0] = new TH1F("","Run 374810 Pos RPD TS Distribution All Centrality Block 7",6,0,6);
        pRPD_TSDist[8][0] = new TH1F("","Run 374810 Pos RPD TS Distribution All Centrality Block 8",6,0,6);
        pRPD_TSDist[9][0] = new TH1F("","Run 374810 Pos RPD TS Distribution All Centrality Block 9",6,0,6);
        pRPD_TSDist[10][0] = new TH1F("","Run 374810 Pos RPD TS Distribution All Centrality Block 10",6,0,6);
        pRPD_TSDist[11][0] = new TH1F("","Run 374810 Pos RPD TS Distribution All Centrality Block 11",6,0,6);
        pRPD_TSDist[12][0] = new TH1F("","Run 374810 Pos RPD TS Distribution All Centrality Block 12",6,0,6);
        pRPD_TSDist[13][0] = new TH1F("","Run 374810 Pos RPD TS Distribution All Centrality Block 13",6,0,6);
        pRPD_TSDist[14][0] = new TH1F("","Run 374810 Pos RPD TS Distribution All Centrality Block 14",6,0,6);
        pRPD_TSDist[15][0] = new TH1F("","Run 374810 Pos RPD TS Distribution All Centrality Block 15",6,0,6);

        pRPD_TSDist[0][1] = new TH1F("","Run 374810 Pos RPD TS Distribution 0 - 9.5% Centrality Block 0",6,0,6);
        pRPD_TSDist[1][1] = new TH1F("","Run 374810 Pos RPD TS Distribution 0 - 9.5% Centrality Block 1",6,0,6);
        pRPD_TSDist[2][1] = new TH1F("","Run 374810 Pos RPD TS Distribution 0 - 9.5% Centrality Block 2",6,0,6);
        pRPD_TSDist[3][1] = new TH1F("","Run 374810 Pos RPD TS Distribution 0 - 9.5% Centrality Block 3",6,0,6);
        pRPD_TSDist[4][1] = new TH1F("","Run 374810 Pos RPD TS Distribution 0 - 9.5% Centrality Block 4",6,0,6);
        pRPD_TSDist[5][1] = new TH1F("","Run 374810 Pos RPD TS Distribution 0 - 9.5% Centrality Block 5",6,0,6);
        pRPD_TSDist[6][1] = new TH1F("","Run 374810 Pos RPD TS Distribution 0 - 9.5% Centrality Block 6",6,0,6);
        pRPD_TSDist[7][1] = new TH1F("","Run 374810 Pos RPD TS Distribution 0 - 9.5% Centrality Block 7",6,0,6);
        pRPD_TSDist[8][1] = new TH1F("","Run 374810 Pos RPD TS Distribution 0 - 9.5% Centrality Block 8",6,0,6);
        pRPD_TSDist[9][1] = new TH1F("","Run 374810 Pos RPD TS Distribution 0 - 9.5% Centrality Block 9",6,0,6);
        pRPD_TSDist[10][1] = new TH1F("","Run 374810 Pos RPD TS Distribution 0 - 9.5% Centrality Block 10",6,0,6);
        pRPD_TSDist[11][1] = new TH1F("","Run 374810 Pos RPD TS Distribution 0 - 9.5% Centrality Block 11",6,0,6);
        pRPD_TSDist[12][1] = new TH1F("","Run 374810 Pos RPD TS Distribution 0 - 9.5% Centrality Block 12",6,0,6);
        pRPD_TSDist[13][1] = new TH1F("","Run 374810 Pos RPD TS Distribution 0 - 9.5% Centrality Block 13",6,0,6);
        pRPD_TSDist[14][1] = new TH1F("","Run 374810 Pos RPD TS Distribution 0 - 9.5% Centrality Block 14",6,0,6);
        pRPD_TSDist[15][1] = new TH1F("","Run 374810 Pos RPD TS Distribution 0 - 9.5% Centrality Block 15",6,0,6);

        pRPD_TSDist[0][2] = new TH1F("","Run 374810 Pos RPD TS Distribution 10 - 19.5% Centrality Block 0",6,0,6);
        pRPD_TSDist[1][2] = new TH1F("","Run 374810 Pos RPD TS Distribution 10 - 19.5% Centrality Block 1",6,0,6);
        pRPD_TSDist[2][2] = new TH1F("","Run 374810 Pos RPD TS Distribution 10 - 19.5% Centrality Block 2",6,0,6);
        pRPD_TSDist[3][2] = new TH1F("","Run 374810 Pos RPD TS Distribution 10 - 19.5% Centrality Block 3",6,0,6);
        pRPD_TSDist[4][2] = new TH1F("","Run 374810 Pos RPD TS Distribution 10 - 19.5% Centrality Block 4",6,0,6);
        pRPD_TSDist[5][2] = new TH1F("","Run 374810 Pos RPD TS Distribution 10 - 19.5% Centrality Block 5",6,0,6);
        pRPD_TSDist[6][2] = new TH1F("","Run 374810 Pos RPD TS Distribution 10 - 19.5% Centrality Block 6",6,0,6);
        pRPD_TSDist[7][2] = new TH1F("","Run 374810 Pos RPD TS Distribution 10 - 19.5% Centrality Block 7",6,0,6);
        pRPD_TSDist[8][2] = new TH1F("","Run 374810 Pos RPD TS Distribution 10 - 19.5% Centrality Block 8",6,0,6);
        pRPD_TSDist[9][2] = new TH1F("","Run 374810 Pos RPD TS Distribution 10 - 19.5% Centrality Block 9",6,0,6);
        pRPD_TSDist[10][2] = new TH1F("","Run 374810 Pos RPD TS Distribution 10 - 19.5% Centrality Block 10",6,0,6);
        pRPD_TSDist[11][2] = new TH1F("","Run 374810 Pos RPD TS Distribution 10 - 19.5% Centrality Block 11",6,0,6);
        pRPD_TSDist[12][2] = new TH1F("","Run 374810 Pos RPD TS Distribution 10 - 19.5% Centrality Block 12",6,0,6);
        pRPD_TSDist[13][2] = new TH1F("","Run 374810 Pos RPD TS Distribution 10 - 19.5% Centrality Block 13",6,0,6);
        pRPD_TSDist[14][2] = new TH1F("","Run 374810 Pos RPD TS Distribution 10 - 19.5% Centrality Block 14",6,0,6);
        pRPD_TSDist[15][2] = new TH1F("","Run 374810 Pos RPD TS Distribution 10 - 19.5% Centrality Block 15",6,0,6);

        pRPD_TSDist[0][3] = new TH1F("","Run 374810 Pos RPD TS Distribution 20 - 29.5% Centrality Block 0",6,0,6);
        pRPD_TSDist[1][3] = new TH1F("","Run 374810 Pos RPD TS Distribution 20 - 29.5% Centrality Block 1",6,0,6);
        pRPD_TSDist[2][3] = new TH1F("","Run 374810 Pos RPD TS Distribution 20 - 29.5% Centrality Block 2",6,0,6);
        pRPD_TSDist[3][3] = new TH1F("","Run 374810 Pos RPD TS Distribution 20 - 29.5% Centrality Block 3",6,0,6);
        pRPD_TSDist[4][3] = new TH1F("","Run 374810 Pos RPD TS Distribution 20 - 29.5% Centrality Block 4",6,0,6);
        pRPD_TSDist[5][3] = new TH1F("","Run 374810 Pos RPD TS Distribution 20 - 29.5% Centrality Block 5",6,0,6);
        pRPD_TSDist[6][3] = new TH1F("","Run 374810 Pos RPD TS Distribution 20 - 29.5% Centrality Block 6",6,0,6);
        pRPD_TSDist[7][3] = new TH1F("","Run 374810 Pos RPD TS Distribution 20 - 29.5% Centrality Block 7",6,0,6);
        pRPD_TSDist[8][3] = new TH1F("","Run 374810 Pos RPD TS Distribution 20 - 29.5% Centrality Block 8",6,0,6);
        pRPD_TSDist[9][3] = new TH1F("","Run 374810 Pos RPD TS Distribution 20 - 29.5% Centrality Block 9",6,0,6);
        pRPD_TSDist[10][3] = new TH1F("","Run 374810 Pos RPD TS Distribution 20 - 29.5% Centrality Block 10",6,0,6);
        pRPD_TSDist[11][3] = new TH1F("","Run 374810 Pos RPD TS Distribution 20 - 29.5% Centrality Block 11",6,0,6);
        pRPD_TSDist[12][3] = new TH1F("","Run 374810 Pos RPD TS Distribution 20 - 29.5% Centrality Block 12",6,0,6);
        pRPD_TSDist[13][3] = new TH1F("","Run 374810 Pos RPD TS Distribution 20 - 29.5% Centrality Block 13",6,0,6);
        pRPD_TSDist[14][3] = new TH1F("","Run 374810 Pos RPD TS Distribution 20 - 29.5% Centrality Block 14",6,0,6);
        pRPD_TSDist[15][3] = new TH1F("","Run 374810 Pos RPD TS Distribution 20 - 29.5% Centrality Block 15",6,0,6);

        pRPD_TSDist[0][4] = new TH1F("","Run 374810 Pos RPD TS Distribution 30 - 39.5% Centrality Block 0",6,0,6);
        pRPD_TSDist[1][4] = new TH1F("","Run 374810 Pos RPD TS Distribution 30 - 39.5% Centrality Block 1",6,0,6);
        pRPD_TSDist[2][4] = new TH1F("","Run 374810 Pos RPD TS Distribution 30 - 39.5% Centrality Block 2",6,0,6);
        pRPD_TSDist[3][4] = new TH1F("","Run 374810 Pos RPD TS Distribution 30 - 39.5% Centrality Block 3",6,0,6);
        pRPD_TSDist[4][4] = new TH1F("","Run 374810 Pos RPD TS Distribution 30 - 39.5% Centrality Block 4",6,0,6);
        pRPD_TSDist[5][4] = new TH1F("","Run 374810 Pos RPD TS Distribution 30 - 39.5% Centrality Block 5",6,0,6);
        pRPD_TSDist[6][4] = new TH1F("","Run 374810 Pos RPD TS Distribution 30 - 39.5% Centrality Block 6",6,0,6);
        pRPD_TSDist[7][4] = new TH1F("","Run 374810 Pos RPD TS Distribution 30 - 39.5% Centrality Block 7",6,0,6);
        pRPD_TSDist[8][4] = new TH1F("","Run 374810 Pos RPD TS Distribution 30 - 39.5% Centrality Block 8",6,0,6);
        pRPD_TSDist[9][4] = new TH1F("","Run 374810 Pos RPD TS Distribution 30 - 39.5% Centrality Block 9",6,0,6);
        pRPD_TSDist[10][4] = new TH1F("","Run 374810 Pos RPD TS Distribution 30 - 39.5% Centrality Block 10",6,0,6);
        pRPD_TSDist[11][4] = new TH1F("","Run 374810 Pos RPD TS Distribution 30 - 39.5% Centrality Block 11",6,0,6);
        pRPD_TSDist[12][4] = new TH1F("","Run 374810 Pos RPD TS Distribution 30 - 39.5% Centrality Block 12",6,0,6);
        pRPD_TSDist[13][4] = new TH1F("","Run 374810 Pos RPD TS Distribution 30 - 39.5% Centrality Block 13",6,0,6);
        pRPD_TSDist[14][4] = new TH1F("","Run 374810 Pos RPD TS Distribution 30 - 39.5% Centrality Block 14",6,0,6);
        pRPD_TSDist[15][4] = new TH1F("","Run 374810 Pos RPD TS Distribution 30 - 39.5% Centrality Block 15",6,0,6);

        pRPD_TSDist[0][5] = new TH1F("","Run 374810 Pos RPD TS Distribution 40 - 49.5% Centrality Block 0",6,0,6);
        pRPD_TSDist[1][5] = new TH1F("","Run 374810 Pos RPD TS Distribution 40 - 49.5% Centrality Block 1",6,0,6);
        pRPD_TSDist[2][5] = new TH1F("","Run 374810 Pos RPD TS Distribution 40 - 49.5% Centrality Block 2",6,0,6);
        pRPD_TSDist[3][5] = new TH1F("","Run 374810 Pos RPD TS Distribution 40 - 49.5% Centrality Block 3",6,0,6);
        pRPD_TSDist[4][5] = new TH1F("","Run 374810 Pos RPD TS Distribution 40 - 49.5% Centrality Block 4",6,0,6);
        pRPD_TSDist[5][5] = new TH1F("","Run 374810 Pos RPD TS Distribution 40 - 49.5% Centrality Block 5",6,0,6);
        pRPD_TSDist[6][5] = new TH1F("","Run 374810 Pos RPD TS Distribution 40 - 49.5% Centrality Block 6",6,0,6);
        pRPD_TSDist[7][5] = new TH1F("","Run 374810 Pos RPD TS Distribution 40 - 49.5% Centrality Block 7",6,0,6);
        pRPD_TSDist[8][5] = new TH1F("","Run 374810 Pos RPD TS Distribution 40 - 49.5% Centrality Block 8",6,0,6);
        pRPD_TSDist[9][5] = new TH1F("","Run 374810 Pos RPD TS Distribution 40 - 49.5% Centrality Block 9",6,0,6);
        pRPD_TSDist[10][5] = new TH1F("","Run 374810 Pos RPD TS Distribution 40 - 49.5% Centrality Block 10",6,0,6);
        pRPD_TSDist[11][5] = new TH1F("","Run 374810 Pos RPD TS Distribution 40 - 49.5% Centrality Block 11",6,0,6);
        pRPD_TSDist[12][5] = new TH1F("","Run 374810 Pos RPD TS Distribution 40 - 49.5% Centrality Block 12",6,0,6);
        pRPD_TSDist[13][5] = new TH1F("","Run 374810 Pos RPD TS Distribution 40 - 49.5% Centrality Block 13",6,0,6);
        pRPD_TSDist[14][5] = new TH1F("","Run 374810 Pos RPD TS Distribution 40 - 49.5% Centrality Block 14",6,0,6);
        pRPD_TSDist[15][5] = new TH1F("","Run 374810 Pos RPD TS Distribution 40 - 49.5% Centrality Block 15",6,0,6);

        pRPD_TSDist[0][6] = new TH1F("","Run 374810 Pos RPD TS Distribution 50 - 59.5% Centrality Block 0",6,0,6);
        pRPD_TSDist[1][6] = new TH1F("","Run 374810 Pos RPD TS Distribution 50 - 59.5% Centrality Block 1",6,0,6);
        pRPD_TSDist[2][6] = new TH1F("","Run 374810 Pos RPD TS Distribution 50 - 59.5% Centrality Block 2",6,0,6);
        pRPD_TSDist[3][6] = new TH1F("","Run 374810 Pos RPD TS Distribution 50 - 59.5% Centrality Block 3",6,0,6);
        pRPD_TSDist[4][6] = new TH1F("","Run 374810 Pos RPD TS Distribution 50 - 59.5% Centrality Block 4",6,0,6);
        pRPD_TSDist[5][6] = new TH1F("","Run 374810 Pos RPD TS Distribution 50 - 59.5% Centrality Block 5",6,0,6);
        pRPD_TSDist[6][6] = new TH1F("","Run 374810 Pos RPD TS Distribution 50 - 59.5% Centrality Block 6",6,0,6);
        pRPD_TSDist[7][6] = new TH1F("","Run 374810 Pos RPD TS Distribution 50 - 59.5% Centrality Block 7",6,0,6);
        pRPD_TSDist[8][6] = new TH1F("","Run 374810 Pos RPD TS Distribution 50 - 59.5% Centrality Block 8",6,0,6);
        pRPD_TSDist[9][6] = new TH1F("","Run 374810 Pos RPD TS Distribution 50 - 59.5% Centrality Block 9",6,0,6);
        pRPD_TSDist[10][6] = new TH1F("","Run 374810 Pos RPD TS Distribution 50 - 59.5% Centrality Block 10",6,0,6);
        pRPD_TSDist[11][6] = new TH1F("","Run 374810 Pos RPD TS Distribution 50 - 59.5% Centrality Block 11",6,0,6);
        pRPD_TSDist[12][6] = new TH1F("","Run 374810 Pos RPD TS Distribution 50 - 59.5% Centrality Block 12",6,0,6);
        pRPD_TSDist[13][6] = new TH1F("","Run 374810 Pos RPD TS Distribution 50 - 59.5% Centrality Block 13",6,0,6);
        pRPD_TSDist[14][6] = new TH1F("","Run 374810 Pos RPD TS Distribution 50 - 59.5% Centrality Block 14",6,0,6);
        pRPD_TSDist[15][6] = new TH1F("","Run 374810 Pos RPD TS Distribution 50 - 59.5% Centrality Block 15",6,0,6);

        pRPD_TSDist[0][7] = new TH1F("","Run 374810 Pos RPD TS Distribution 60 - 69.5% Centrality Block 0",6,0,6);
        pRPD_TSDist[1][7] = new TH1F("","Run 374810 Pos RPD TS Distribution 60 - 69.5% Centrality Block 1",6,0,6);
        pRPD_TSDist[2][7] = new TH1F("","Run 374810 Pos RPD TS Distribution 60 - 69.5% Centrality Block 2",6,0,6);
        pRPD_TSDist[3][7] = new TH1F("","Run 374810 Pos RPD TS Distribution 60 - 69.5% Centrality Block 3",6,0,6);
        pRPD_TSDist[4][7] = new TH1F("","Run 374810 Pos RPD TS Distribution 60 - 69.5% Centrality Block 4",6,0,6);
        pRPD_TSDist[5][7] = new TH1F("","Run 374810 Pos RPD TS Distribution 60 - 69.5% Centrality Block 5",6,0,6);
        pRPD_TSDist[6][7] = new TH1F("","Run 374810 Pos RPD TS Distribution 60 - 69.5% Centrality Block 6",6,0,6);
        pRPD_TSDist[7][7] = new TH1F("","Run 374810 Pos RPD TS Distribution 60 - 69.5% Centrality Block 7",6,0,6);
        pRPD_TSDist[8][7] = new TH1F("","Run 374810 Pos RPD TS Distribution 60 - 69.5% Centrality Block 8",6,0,6);
        pRPD_TSDist[9][7] = new TH1F("","Run 374810 Pos RPD TS Distribution 60 - 69.5% Centrality Block 9",6,0,6);
        pRPD_TSDist[10][7] = new TH1F("","Run 374810 Pos RPD TS Distribution 60 - 69.5% Centrality Block 10",6,0,6);
        pRPD_TSDist[11][7] = new TH1F("","Run 374810 Pos RPD TS Distribution 60 - 69.5% Centrality Block 11",6,0,6);
        pRPD_TSDist[12][7] = new TH1F("","Run 374810 Pos RPD TS Distribution 60 - 69.5% Centrality Block 12",6,0,6);
        pRPD_TSDist[13][7] = new TH1F("","Run 374810 Pos RPD TS Distribution 60 - 69.5% Centrality Block 13",6,0,6);
        pRPD_TSDist[14][7] = new TH1F("","Run 374810 Pos RPD TS Distribution 60 - 69.5% Centrality Block 14",6,0,6);
        pRPD_TSDist[15][7] = new TH1F("","Run 374810 Pos RPD TS Distribution 60 - 69.5% Centrality Block 15",6,0,6);

        pRPD_TSDist[0][8] = new TH1F("","Run 374810 Pos RPD TS Distribution 70 - 79.5% Centrality Block 0",6,0,6);
        pRPD_TSDist[1][8] = new TH1F("","Run 374810 Pos RPD TS Distribution 70 - 79.5% Centrality Block 1",6,0,6);
        pRPD_TSDist[2][8] = new TH1F("","Run 374810 Pos RPD TS Distribution 70 - 79.5% Centrality Block 2",6,0,6);
        pRPD_TSDist[3][8] = new TH1F("","Run 374810 Pos RPD TS Distribution 70 - 79.5% Centrality Block 3",6,0,6);
        pRPD_TSDist[4][8] = new TH1F("","Run 374810 Pos RPD TS Distribution 70 - 79.5% Centrality Block 4",6,0,6);
        pRPD_TSDist[5][8] = new TH1F("","Run 374810 Pos RPD TS Distribution 70 - 79.5% Centrality Block 5",6,0,6);
        pRPD_TSDist[6][8] = new TH1F("","Run 374810 Pos RPD TS Distribution 70 - 79.5% Centrality Block 6",6,0,6);
        pRPD_TSDist[7][8] = new TH1F("","Run 374810 Pos RPD TS Distribution 70 - 79.5% Centrality Block 7",6,0,6);
        pRPD_TSDist[8][8] = new TH1F("","Run 374810 Pos RPD TS Distribution 70 - 79.5% Centrality Block 8",6,0,6);
        pRPD_TSDist[9][8] = new TH1F("","Run 374810 Pos RPD TS Distribution 70 - 79.5% Centrality Block 9",6,0,6);
        pRPD_TSDist[10][8] = new TH1F("","Run 374810 Pos RPD TS Distribution 70 - 79.5% Centrality Block 10",6,0,6);
        pRPD_TSDist[11][8] = new TH1F("","Run 374810 Pos RPD TS Distribution 70 - 79.5% Centrality Block 11",6,0,6);
        pRPD_TSDist[12][8] = new TH1F("","Run 374810 Pos RPD TS Distribution 70 - 79.5% Centrality Block 12",6,0,6);
        pRPD_TSDist[13][8] = new TH1F("","Run 374810 Pos RPD TS Distribution 70 - 79.5% Centrality Block 13",6,0,6);
        pRPD_TSDist[14][8] = new TH1F("","Run 374810 Pos RPD TS Distribution 70 - 79.5% Centrality Block 14",6,0,6);
        pRPD_TSDist[15][8] = new TH1F("","Run 374810 Pos RPD TS Distribution 70 - 79.5% Centrality Block 15",6,0,6);

        pRPD_TSDist[0][9] = new TH1F("","Run 374810 Pos RPD TS Distribution 80 - 89.5% Centrality Block 0",6,0,6);
        pRPD_TSDist[1][9] = new TH1F("","Run 374810 Pos RPD TS Distribution 80 - 89.5% Centrality Block 1",6,0,6);
        pRPD_TSDist[2][9] = new TH1F("","Run 374810 Pos RPD TS Distribution 80 - 89.5% Centrality Block 2",6,0,6);
        pRPD_TSDist[3][9] = new TH1F("","Run 374810 Pos RPD TS Distribution 80 - 89.5% Centrality Block 3",6,0,6);
        pRPD_TSDist[4][9] = new TH1F("","Run 374810 Pos RPD TS Distribution 80 - 89.5% Centrality Block 4",6,0,6);
        pRPD_TSDist[5][9] = new TH1F("","Run 374810 Pos RPD TS Distribution 80 - 89.5% Centrality Block 5",6,0,6);
        pRPD_TSDist[6][9] = new TH1F("","Run 374810 Pos RPD TS Distribution 80 - 89.5% Centrality Block 6",6,0,6);
        pRPD_TSDist[7][9] = new TH1F("","Run 374810 Pos RPD TS Distribution 80 - 89.5% Centrality Block 7",6,0,6);
        pRPD_TSDist[8][9] = new TH1F("","Run 374810 Pos RPD TS Distribution 80 - 89.5% Centrality Block 8",6,0,6);
        pRPD_TSDist[9][9] = new TH1F("","Run 374810 Pos RPD TS Distribution 80 - 89.5% Centrality Block 9",6,0,6);
        pRPD_TSDist[10][9] = new TH1F("","Run 374810 Pos RPD TS Distribution 80 - 89.5% Centrality Block 10",6,0,6);
        pRPD_TSDist[11][9] = new TH1F("","Run 374810 Pos RPD TS Distribution 80 - 89.5% Centrality Block 11",6,0,6);
        pRPD_TSDist[12][9] = new TH1F("","Run 374810 Pos RPD TS Distribution 80 - 89.5% Centrality Block 12",6,0,6);
        pRPD_TSDist[13][9] = new TH1F("","Run 374810 Pos RPD TS Distribution 80 - 89.5% Centrality Block 13",6,0,6);
        pRPD_TSDist[14][9] = new TH1F("","Run 374810 Pos RPD TS Distribution 80 - 89.5% Centrality Block 14",6,0,6);
        pRPD_TSDist[15][9] = new TH1F("","Run 374810 Pos RPD TS Distribution 80 - 89.5% Centrality Block 15",6,0,6);

        pRPD_TSDist[0][10] = new TH1F("","Run 374810 Pos RPD TS Distribution 90 - 100% Centrality Block 0",6,0,6);
        pRPD_TSDist[1][10] = new TH1F("","Run 374810 Pos RPD TS Distribution 90 - 100% Centrality Block 1",6,0,6);
        pRPD_TSDist[2][10] = new TH1F("","Run 374810 Pos RPD TS Distribution 90 - 100% Centrality Block 2",6,0,6);
        pRPD_TSDist[3][10] = new TH1F("","Run 374810 Pos RPD TS Distribution 90 - 100% Centrality Block 3",6,0,6);
        pRPD_TSDist[4][10] = new TH1F("","Run 374810 Pos RPD TS Distribution 90 - 100% Centrality Block 4",6,0,6);
        pRPD_TSDist[5][10] = new TH1F("","Run 374810 Pos RPD TS Distribution 90 - 100% Centrality Block 5",6,0,6);
        pRPD_TSDist[6][10] = new TH1F("","Run 374810 Pos RPD TS Distribution 90 - 100% Centrality Block 6",6,0,6);
        pRPD_TSDist[7][10] = new TH1F("","Run 374810 Pos RPD TS Distribution 90 - 100% Centrality Block 7",6,0,6);
        pRPD_TSDist[8][10] = new TH1F("","Run 374810 Pos RPD TS Distribution 90 - 100% Centrality Block 8",6,0,6);
        pRPD_TSDist[9][10] = new TH1F("","Run 374810 Pos RPD TS Distribution 90 - 100% Centrality Block 9",6,0,6);
        pRPD_TSDist[10][10] = new TH1F("","Run 374810 Pos RPD TS Distribution 90 - 100% Centrality Block 10",6,0,6);
        pRPD_TSDist[11][10] = new TH1F("","Run 374810 Pos RPD TS Distribution 90 - 100% Centrality Block 11",6,0,6);
        pRPD_TSDist[12][10] = new TH1F("","Run 374810 Pos RPD TS Distribution 90 - 100% Centrality Block 12",6,0,6);
        pRPD_TSDist[13][10] = new TH1F("","Run 374810 Pos RPD TS Distribution 90 - 100% Centrality Block 13",6,0,6);
        pRPD_TSDist[14][10] = new TH1F("","Run 374810 Pos RPD TS Distribution 90 - 100% Centrality Block 14",6,0,6);
        pRPD_TSDist[15][10] = new TH1F("","Run 374810 Pos RPD TS Distribution 90 - 100% Centrality Block 15",6,0,6);

    TH1F *pEM_TSDist[5][11] = {0};

        pEM_TSDist[0][0] = new TH1F("","Run 374810 pos EM 1 TS Distribution All Centrality",6,0,6);
        pEM_TSDist[1][0] = new TH1F("","Run 374810 pos EM 2 TS Distribution All Centrality",6,0,6);
        pEM_TSDist[2][0] = new TH1F("","Run 374810 pos EM 3 TS Distribution All Centrality",6,0,6);
        pEM_TSDist[3][0] = new TH1F("","Run 374810 pos EM 4 TS Distribution All Centrality",6,0,6);
        pEM_TSDist[4][0] = new TH1F("","Run 374810 pos EM 5 TS Distribution All Centrality",6,0,6);

        pEM_TSDist[0][1] = new TH1F("","Run 374810 pos EM 1 TS Distribution 0 - 9.5% Centrality",6,0,6);
        pEM_TSDist[1][1] = new TH1F("","Run 374810 pos EM 2 TS Distribution 0 - 9.5% Centrality",6,0,6);
        pEM_TSDist[2][1] = new TH1F("","Run 374810 pos EM 3 TS Distribution 0 - 9.5% Centrality",6,0,6);
        pEM_TSDist[3][1] = new TH1F("","Run 374810 pos EM 4 TS Distribution 0 - 9.5% Centrality",6,0,6);
        pEM_TSDist[4][1] = new TH1F("","Run 374810 pos EM 5 TS Distribution 0 - 9.5% Centrality",6,0,6);

        pEM_TSDist[0][2] = new TH1F("","Run 374810 pos EM 1 TS Distribution 10 - 19.5% Centrality",6,0,6);
        pEM_TSDist[1][2] = new TH1F("","Run 374810 pos EM 2 TS Distribution 10 - 19.5% Centrality",6,0,6);
        pEM_TSDist[2][2] = new TH1F("","Run 374810 pos EM 3 TS Distribution 10 - 19.5% Centrality",6,0,6);
        pEM_TSDist[3][2] = new TH1F("","Run 374810 pos EM 4 TS Distribution 10 - 19.5% Centrality",6,0,6);
        pEM_TSDist[4][2] = new TH1F("","Run 374810 pos EM 5 TS Distribution 10 - 19.5% Centrality",6,0,6);

        pEM_TSDist[0][3] = new TH1F("","Run 374810 pos EM 1 TS Distribution 20 - 29.5% Centrality",6,0,6);
        pEM_TSDist[1][3] = new TH1F("","Run 374810 pos EM 2 TS Distribution 20 - 29.5% Centrality",6,0,6);
        pEM_TSDist[2][3] = new TH1F("","Run 374810 pos EM 3 TS Distribution 20 - 29.5% Centrality",6,0,6);
        pEM_TSDist[3][3] = new TH1F("","Run 374810 pos EM 4 TS Distribution 20 - 29.5% Centrality",6,0,6);
        pEM_TSDist[4][3] = new TH1F("","Run 374810 pos EM 5 TS Distribution 20 - 29.5% Centrality",6,0,6);

        pEM_TSDist[0][4] = new TH1F("","Run 374810 pos EM 1 TS Distribution 30 - 39.5% Centrality",6,0,6);
        pEM_TSDist[1][4] = new TH1F("","Run 374810 pos EM 2 TS Distribution 30 - 39.5% Centrality",6,0,6);
        pEM_TSDist[2][4] = new TH1F("","Run 374810 pos EM 3 TS Distribution 30 - 39.5% Centrality",6,0,6);
        pEM_TSDist[3][4] = new TH1F("","Run 374810 pos EM 4 TS Distribution 30 - 39.5% Centrality",6,0,6);
        pEM_TSDist[4][4] = new TH1F("","Run 374810 pos EM 5 TS Distribution 30 - 39.5% Centrality",6,0,6);

        pEM_TSDist[0][5] = new TH1F("","Run 374810 pos EM 1 TS Distribution 40 - 49.5% Centrality",6,0,6);
        pEM_TSDist[1][5] = new TH1F("","Run 374810 pos EM 2 TS Distribution 40 - 49.5% Centrality",6,0,6);
        pEM_TSDist[2][5] = new TH1F("","Run 374810 pos EM 3 TS Distribution 40 - 49.5% Centrality",6,0,6);
        pEM_TSDist[3][5] = new TH1F("","Run 374810 pos EM 4 TS Distribution 40 - 49.5% Centrality",6,0,6);
        pEM_TSDist[4][5] = new TH1F("","Run 374810 pos EM 5 TS Distribution 40 - 49.5% Centrality",6,0,6);

        pEM_TSDist[0][6] = new TH1F("","Run 374810 pos EM 1 TS Distribution 50 - 59.5% Centrality",6,0,6);
        pEM_TSDist[1][6] = new TH1F("","Run 374810 pos EM 2 TS Distribution 50 - 59.5% Centrality",6,0,6);
        pEM_TSDist[2][6] = new TH1F("","Run 374810 pos EM 3 TS Distribution 50 - 59.5% Centrality",6,0,6);
        pEM_TSDist[3][6] = new TH1F("","Run 374810 pos EM 4 TS Distribution 50 - 59.5% Centrality",6,0,6);
        pEM_TSDist[4][6] = new TH1F("","Run 374810 pos EM 5 TS Distribution 50 - 59.5% Centrality",6,0,6);

        pEM_TSDist[0][7] = new TH1F("","Run 374810 pos EM 1 TS Distribution 60 - 69.5% Centrality",6,0,6);
        pEM_TSDist[1][7] = new TH1F("","Run 374810 pos EM 2 TS Distribution 60 - 69.5% Centrality",6,0,6);
        pEM_TSDist[2][7] = new TH1F("","Run 374810 pos EM 3 TS Distribution 60 - 69.5% Centrality",6,0,6);
        pEM_TSDist[3][7] = new TH1F("","Run 374810 pos EM 4 TS Distribution 60 - 69.5% Centrality",6,0,6);
        pEM_TSDist[4][7] = new TH1F("","Run 374810 pos EM 5 TS Distribution 60 - 69.5% Centrality",6,0,6);

        pEM_TSDist[0][8] = new TH1F("","Run 374810 pos EM 1 TS Distribution 70 - 79.5% Centrality",6,0,6);
        pEM_TSDist[1][8] = new TH1F("","Run 374810 pos EM 2 TS Distribution 70 - 79.5% Centrality",6,0,6);
        pEM_TSDist[2][8] = new TH1F("","Run 374810 pos EM 3 TS Distribution 70 - 79.5% Centrality",6,0,6);
        pEM_TSDist[3][8] = new TH1F("","Run 374810 pos EM 4 TS Distribution 70 - 79.5% Centrality",6,0,6);
        pEM_TSDist[4][8] = new TH1F("","Run 374810 pos EM 5 TS Distribution 70 - 79.5% Centrality",6,0,6);

        pEM_TSDist[0][9] = new TH1F("","Run 374810 pos EM 1 TS Distribution 80 - 89.5% Centrality",6,0,6);
        pEM_TSDist[1][9] = new TH1F("","Run 374810 pos EM 2 TS Distribution 80 - 89.5% Centrality",6,0,6);
        pEM_TSDist[2][9] = new TH1F("","Run 374810 pos EM 3 TS Distribution 80 - 89.5% Centrality",6,0,6);
        pEM_TSDist[3][9] = new TH1F("","Run 374810 pos EM 4 TS Distribution 80 - 89.5% Centrality",6,0,6);
        pEM_TSDist[4][9] = new TH1F("","Run 374810 pos EM 5 TS Distribution 80 - 89.5% Centrality",6,0,6);

        pEM_TSDist[0][10] = new TH1F("","Run 374810 pos EM 1 TS Distribution 90 - 100% Centrality",6,0,6);
        pEM_TSDist[1][10] = new TH1F("","Run 374810 pos EM 2 TS Distribution 90 - 100% Centrality",6,0,6);
        pEM_TSDist[2][10] = new TH1F("","Run 374810 pos EM 3 TS Distribution 90 - 100% Centrality",6,0,6);
        pEM_TSDist[3][10] = new TH1F("","Run 374810 pos EM 4 TS Distribution 90 - 100% Centrality",6,0,6);
        pEM_TSDist[4][10] = new TH1F("","Run 374810 pos EM 5 TS Distribution 90 - 100% Centrality",6,0,6);

    TH1F *pHAD_TSDist[4][11] = {0};

        pHAD_TSDist[0][0] = new TH1F("","Run 374810 pos HAD 1 TS Distribution All Centrality",6,0,6);
        pHAD_TSDist[1][0] = new TH1F("","Run 374810 pos HAD 2 TS Distribution All Centrality",6,0,6);
        pHAD_TSDist[2][0] = new TH1F("","Run 374810 pos HAD 3 TS Distribution All Centrality",6,0,6);
        pHAD_TSDist[3][0] = new TH1F("","Run 374810 pos HAD 4 TS Distribution All Centrality",6,0,6);

        pHAD_TSDist[0][1] = new TH1F("","Run 374810 pos HAD 1 TS Distribution 0 - 9.5% Centrality",6,0,6);
        pHAD_TSDist[1][1] = new TH1F("","Run 374810 pos HAD 2 TS Distribution 0 - 9.5% Centrality",6,0,6);
        pHAD_TSDist[2][1] = new TH1F("","Run 374810 pos HAD 3 TS Distribution 0 - 9.5% Centrality",6,0,6);
        pHAD_TSDist[3][1] = new TH1F("","Run 374810 pos HAD 4 TS Distribution 0 - 9.5% Centrality",6,0,6);

        pHAD_TSDist[0][2] = new TH1F("","Run 374810 pos HAD 1 TS Distribution 10 - 19.5% Centrality",6,0,6);
        pHAD_TSDist[1][2] = new TH1F("","Run 374810 pos HAD 2 TS Distribution 10 - 19.5% Centrality",6,0,6);
        pHAD_TSDist[2][2] = new TH1F("","Run 374810 pos HAD 3 TS Distribution 10 - 19.5% Centrality",6,0,6);
        pHAD_TSDist[3][2] = new TH1F("","Run 374810 pos HAD 4 TS Distribution 10 - 19.5% Centrality",6,0,6);

        pHAD_TSDist[0][3] = new TH1F("","Run 374810 pos HAD 1 TS Distribution 20 - 29.5% Centrality",6,0,6);
        pHAD_TSDist[1][3] = new TH1F("","Run 374810 pos HAD 2 TS Distribution 20 - 29.5% Centrality",6,0,6);
        pHAD_TSDist[2][3] = new TH1F("","Run 374810 pos HAD 3 TS Distribution 20 - 29.5% Centrality",6,0,6);
        pHAD_TSDist[3][3] = new TH1F("","Run 374810 pos HAD 4 TS Distribution 20 - 29.5% Centrality",6,0,6);

        pHAD_TSDist[0][4] = new TH1F("","Run 374810 pos HAD 1 TS Distribution 30 - 39.5% Centrality",6,0,6);
        pHAD_TSDist[1][4] = new TH1F("","Run 374810 pos HAD 2 TS Distribution 30 - 39.5% Centrality",6,0,6);
        pHAD_TSDist[2][4] = new TH1F("","Run 374810 pos HAD 3 TS Distribution 30 - 39.5% Centrality",6,0,6);
        pHAD_TSDist[3][4] = new TH1F("","Run 374810 pos HAD 4 TS Distribution 30 - 39.5% Centrality",6,0,6);

        pHAD_TSDist[0][5] = new TH1F("","Run 374810 pos HAD 1 TS Distribution 40 - 49.5% Centrality",6,0,6);
        pHAD_TSDist[1][5] = new TH1F("","Run 374810 pos HAD 2 TS Distribution 40 - 49.5% Centrality",6,0,6);
        pHAD_TSDist[2][5] = new TH1F("","Run 374810 pos HAD 3 TS Distribution 40 - 49.5% Centrality",6,0,6);
        pHAD_TSDist[3][5] = new TH1F("","Run 374810 pos HAD 4 TS Distribution 40 - 49.5% Centrality",6,0,6);

        pHAD_TSDist[0][6] = new TH1F("","Run 374810 pos HAD 1 TS Distribution 50 - 59.5% Centrality",6,0,6);
        pHAD_TSDist[1][6] = new TH1F("","Run 374810 pos HAD 2 TS Distribution 50 - 59.5% Centrality",6,0,6);
        pHAD_TSDist[2][6] = new TH1F("","Run 374810 pos HAD 3 TS Distribution 50 - 59.5% Centrality",6,0,6);
        pHAD_TSDist[3][6] = new TH1F("","Run 374810 pos HAD 4 TS Distribution 50 - 59.5% Centrality",6,0,6);

        pHAD_TSDist[0][7] = new TH1F("","Run 374810 pos HAD 1 TS Distribution 60 - 69.5% Centrality",6,0,6);
        pHAD_TSDist[1][7] = new TH1F("","Run 374810 pos HAD 2 TS Distribution 60 - 69.5% Centrality",6,0,6);
        pHAD_TSDist[2][7] = new TH1F("","Run 374810 pos HAD 3 TS Distribution 60 - 69.5% Centrality",6,0,6);
        pHAD_TSDist[3][7] = new TH1F("","Run 374810 pos HAD 4 TS Distribution 60 - 69.5% Centrality",6,0,6);

        pHAD_TSDist[0][8] = new TH1F("","Run 374810 pos HAD 1 TS Distribution 70 - 79.5% Centrality",6,0,6);
        pHAD_TSDist[1][8] = new TH1F("","Run 374810 pos HAD 2 TS Distribution 70 - 79.5% Centrality",6,0,6);
        pHAD_TSDist[2][8] = new TH1F("","Run 374810 pos HAD 3 TS Distribution 70 - 79.5% Centrality",6,0,6);
        pHAD_TSDist[3][8] = new TH1F("","Run 374810 pos HAD 4 TS Distribution 70 - 79.5% Centrality",6,0,6);

        pHAD_TSDist[0][9] = new TH1F("","Run 374810 pos HAD 1 TS Distribution 80 - 89.5% Centrality",6,0,6);
        pHAD_TSDist[1][9] = new TH1F("","Run 374810 pos HAD 2 TS Distribution 80 - 89.5% Centrality",6,0,6);
        pHAD_TSDist[2][9] = new TH1F("","Run 374810 pos HAD 3 TS Distribution 80 - 89.5% Centrality",6,0,6);
        pHAD_TSDist[3][9] = new TH1F("","Run 374810 pos HAD 4 TS Distribution 80 - 89.5% Centrality",6,0,6);

        pHAD_TSDist[0][10] = new TH1F("","Run 374810 pos HAD 1 TS Distribution 90 - 100% Centrality",6,0,6);
        pHAD_TSDist[1][10] = new TH1F("","Run 374810 pos HAD 2 TS Distribution 90 - 100% Centrality",6,0,6);
        pHAD_TSDist[2][10] = new TH1F("","Run 374810 pos HAD 3 TS Distribution 90 - 100% Centrality",6,0,6);
        pHAD_TSDist[3][10] = new TH1F("","Run 374810 pos HAD 4 TS Distribution 90 - 100% Centrality",6,0,6);

    TH1F *pRPD_RatioDist[16][11] = {0};

        pRPD_RatioDist[0][0] = new TH1F("","Run 374810 Ratio Distribution All Centrality Block 0",100,0,10);
        pRPD_RatioDist[1][0] = new TH1F("","Run 374810 Ratio Distribution All Centrality Block 1",100,0,10);
        pRPD_RatioDist[2][0] = new TH1F("","Run 374810 Ratio Distribution All Centrality Block 2",100,0,10);
        pRPD_RatioDist[3][0] = new TH1F("","Run 374810 Ratio Distribution All Centrality Block 3",100,0,10);
        pRPD_RatioDist[4][0] = new TH1F("","Run 374810 Ratio Distribution All Centrality Block 4",100,0,10);
        pRPD_RatioDist[5][0] = new TH1F("","Run 374810 Ratio Distribution All Centrality Block 5",100,0,10);
        pRPD_RatioDist[6][0] = new TH1F("","Run 374810 Ratio Distribution All Centrality Block 6",100,0,10);
        pRPD_RatioDist[7][0] = new TH1F("","Run 374810 Ratio Distribution All Centrality Block 7",100,0,10);
        pRPD_RatioDist[8][0] = new TH1F("","Run 374810 Ratio Distribution All Centrality Block 8",100,0,10);
        pRPD_RatioDist[9][0] = new TH1F("","Run 374810 Ratio Distribution All Centrality Block 9",100,0,10);
        pRPD_RatioDist[10][0] = new TH1F("","Run 374810 Ratio Distribution All Centrality Block 10",100,0,10);
        pRPD_RatioDist[11][0] = new TH1F("","Run 374810 Ratio Distribution All Centrality Block 11",100,0,10);
        pRPD_RatioDist[12][0] = new TH1F("","Run 374810 Ratio Distribution All Centrality Block 12",100,0,10);
        pRPD_RatioDist[13][0] = new TH1F("","Run 374810 Ratio Distribution All Centrality Block 13",100,0,10);
        pRPD_RatioDist[14][0] = new TH1F("","Run 374810 Ratio Distribution All Centrality Block 14",100,0,10);
        pRPD_RatioDist[15][0] = new TH1F("","Run 374810 Ratio Distribution All Centrality Block 15",100,0,10);

        pRPD_RatioDist[0][1] = new TH1F("","Run 374810 Ratio Distribution 0 - 9.5% Centrality Block 0",50,0,5);
        pRPD_RatioDist[1][1] = new TH1F("","Run 374810 Ratio Distribution 0 - 9.5% Centrality Block 1",50,0,5);
        pRPD_RatioDist[2][1] = new TH1F("","Run 374810 Ratio Distribution 0 - 9.5% Centrality Block 2",50,0,5);
        pRPD_RatioDist[3][1] = new TH1F("","Run 374810 Ratio Distribution 0 - 9.5% Centrality Block 3",50,0,5);
        pRPD_RatioDist[4][1] = new TH1F("","Run 374810 Ratio Distribution 0 - 9.5% Centrality Block 4",50,0,5);
        pRPD_RatioDist[5][1] = new TH1F("","Run 374810 Ratio Distribution 0 - 9.5% Centrality Block 5",50,0,5);
        pRPD_RatioDist[6][1] = new TH1F("","Run 374810 Ratio Distribution 0 - 9.5% Centrality Block 6",50,0,5);
        pRPD_RatioDist[7][1] = new TH1F("","Run 374810 Ratio Distribution 0 - 9.5% Centrality Block 7",50,0,5);
        pRPD_RatioDist[8][1] = new TH1F("","Run 374810 Ratio Distribution 0 - 9.5% Centrality Block 8",50,0,5);
        pRPD_RatioDist[9][1] = new TH1F("","Run 374810 Ratio Distribution 0 - 9.5% Centrality Block 9",50,0,5);
        pRPD_RatioDist[10][1] = new TH1F("","Run 374810 Ratio Distribution 0 - 9.5% Centrality Block 10",50,0,5);
        pRPD_RatioDist[11][1] = new TH1F("","Run 374810 Ratio Distribution 0 - 9.5% Centrality Block 11",50,0,5);
        pRPD_RatioDist[12][1] = new TH1F("","Run 374810 Ratio Distribution 0 - 9.5% Centrality Block 12",50,0,5);
        pRPD_RatioDist[13][1] = new TH1F("","Run 374810 Ratio Distribution 0 - 9.5% Centrality Block 13",50,0,5);
        pRPD_RatioDist[14][1] = new TH1F("","Run 374810 Ratio Distribution 0 - 9.5% Centrality Block 14",50,0,5);
        pRPD_RatioDist[15][1] = new TH1F("","Run 374810 Ratio Distribution 0 - 9.5% Centrality Block 15",50,0,5);

        pRPD_RatioDist[0][2] = new TH1F("","Run 374810 Ratio Distribution 10 - 19.5% Centrality Block 0",50,0,5);
        pRPD_RatioDist[1][2] = new TH1F("","Run 374810 Ratio Distribution 10 - 19.5% Centrality Block 1",50,0,5);
        pRPD_RatioDist[2][2] = new TH1F("","Run 374810 Ratio Distribution 10 - 19.5% Centrality Block 2",50,0,5);
        pRPD_RatioDist[3][2] = new TH1F("","Run 374810 Ratio Distribution 10 - 19.5% Centrality Block 3",50,0,5);
        pRPD_RatioDist[4][2] = new TH1F("","Run 374810 Ratio Distribution 10 - 19.5% Centrality Block 4",50,0,5);
        pRPD_RatioDist[5][2] = new TH1F("","Run 374810 Ratio Distribution 10 - 19.5% Centrality Block 5",50,0,5);
        pRPD_RatioDist[6][2] = new TH1F("","Run 374810 Ratio Distribution 10 - 19.5% Centrality Block 6",50,0,5);
        pRPD_RatioDist[7][2] = new TH1F("","Run 374810 Ratio Distribution 10 - 19.5% Centrality Block 7",50,0,5);
        pRPD_RatioDist[8][2] = new TH1F("","Run 374810 Ratio Distribution 10 - 19.5% Centrality Block 8",50,0,5);
        pRPD_RatioDist[9][2] = new TH1F("","Run 374810 Ratio Distribution 10 - 19.5% Centrality Block 9",50,0,5);
        pRPD_RatioDist[10][2] = new TH1F("","Run 374810 Ratio Distribution 10 - 19.5% Centrality Block 10",50,0,5);
        pRPD_RatioDist[11][2] = new TH1F("","Run 374810 Ratio Distribution 10 - 19.5% Centrality Block 11",50,0,5);
        pRPD_RatioDist[12][2] = new TH1F("","Run 374810 Ratio Distribution 10 - 19.5% Centrality Block 12",50,0,5);
        pRPD_RatioDist[13][2] = new TH1F("","Run 374810 Ratio Distribution 10 - 19.5% Centrality Block 13",50,0,5);
        pRPD_RatioDist[14][2] = new TH1F("","Run 374810 Ratio Distribution 10 - 19.5% Centrality Block 14",50,0,5);
        pRPD_RatioDist[15][2] = new TH1F("","Run 374810 Ratio Distribution 10 - 19.5% Centrality Block 15",50,0,5);

        pRPD_RatioDist[0][3] = new TH1F("","Run 374810 Ratio Distribution 20 - 29.5% Centrality Block 0",50,0,5);
        pRPD_RatioDist[1][3] = new TH1F("","Run 374810 Ratio Distribution 20 - 29.5% Centrality Block 1",50,0,5);
        pRPD_RatioDist[2][3] = new TH1F("","Run 374810 Ratio Distribution 20 - 29.5% Centrality Block 2",50,0,5);
        pRPD_RatioDist[3][3] = new TH1F("","Run 374810 Ratio Distribution 20 - 29.5% Centrality Block 3",50,0,5);
        pRPD_RatioDist[4][3] = new TH1F("","Run 374810 Ratio Distribution 20 - 29.5% Centrality Block 4",50,0,5);
        pRPD_RatioDist[5][3] = new TH1F("","Run 374810 Ratio Distribution 20 - 29.5% Centrality Block 5",50,0,5);
        pRPD_RatioDist[6][3] = new TH1F("","Run 374810 Ratio Distribution 20 - 29.5% Centrality Block 6",50,0,5);
        pRPD_RatioDist[7][3] = new TH1F("","Run 374810 Ratio Distribution 20 - 29.5% Centrality Block 7",50,0,5);
        pRPD_RatioDist[8][3] = new TH1F("","Run 374810 Ratio Distribution 20 - 29.5% Centrality Block 8",50,0,5);
        pRPD_RatioDist[9][3] = new TH1F("","Run 374810 Ratio Distribution 20 - 29.5% Centrality Block 9",50,0,5);
        pRPD_RatioDist[10][3] = new TH1F("","Run 374810 Ratio Distribution 20 - 29.5% Centrality Block 10",50,0,5);
        pRPD_RatioDist[11][3] = new TH1F("","Run 374810 Ratio Distribution 20 - 29.5% Centrality Block 11",50,0,5);
        pRPD_RatioDist[12][3] = new TH1F("","Run 374810 Ratio Distribution 20 - 29.5% Centrality Block 12",50,0,5);
        pRPD_RatioDist[13][3] = new TH1F("","Run 374810 Ratio Distribution 20 - 29.5% Centrality Block 13",50,0,5);
        pRPD_RatioDist[14][3] = new TH1F("","Run 374810 Ratio Distribution 20 - 29.5% Centrality Block 14",50,0,5);
        pRPD_RatioDist[15][3] = new TH1F("","Run 374810 Ratio Distribution 20 - 29.5% Centrality Block 15",50,0,5);

        pRPD_RatioDist[0][4] = new TH1F("","Run 374810 Ratio Distribution 30 - 39.5% Centrality Block 0",50,0,5);
        pRPD_RatioDist[1][4] = new TH1F("","Run 374810 Ratio Distribution 30 - 39.5% Centrality Block 1",50,0,5);
        pRPD_RatioDist[2][4] = new TH1F("","Run 374810 Ratio Distribution 30 - 39.5% Centrality Block 2",50,0,5);
        pRPD_RatioDist[3][4] = new TH1F("","Run 374810 Ratio Distribution 30 - 39.5% Centrality Block 3",50,0,5);
        pRPD_RatioDist[4][4] = new TH1F("","Run 374810 Ratio Distribution 30 - 39.5% Centrality Block 4",50,0,5);
        pRPD_RatioDist[5][4] = new TH1F("","Run 374810 Ratio Distribution 30 - 39.5% Centrality Block 5",50,0,5);
        pRPD_RatioDist[6][4] = new TH1F("","Run 374810 Ratio Distribution 30 - 39.5% Centrality Block 6",50,0,5);
        pRPD_RatioDist[7][4] = new TH1F("","Run 374810 Ratio Distribution 30 - 39.5% Centrality Block 7",50,0,5);
        pRPD_RatioDist[8][4] = new TH1F("","Run 374810 Ratio Distribution 30 - 39.5% Centrality Block 8",50,0,5);
        pRPD_RatioDist[9][4] = new TH1F("","Run 374810 Ratio Distribution 30 - 39.5% Centrality Block 9",50,0,5);
        pRPD_RatioDist[10][4] = new TH1F("","Run 374810 Ratio Distribution 30 - 39.5% Centrality Block 10",50,0,5);
        pRPD_RatioDist[11][4] = new TH1F("","Run 374810 Ratio Distribution 30 - 39.5% Centrality Block 11",50,0,5);
        pRPD_RatioDist[12][4] = new TH1F("","Run 374810 Ratio Distribution 30 - 39.5% Centrality Block 12",50,0,5);
        pRPD_RatioDist[13][4] = new TH1F("","Run 374810 Ratio Distribution 30 - 39.5% Centrality Block 13",50,0,5);
        pRPD_RatioDist[14][4] = new TH1F("","Run 374810 Ratio Distribution 30 - 39.5% Centrality Block 14",50,0,5);
        pRPD_RatioDist[15][4] = new TH1F("","Run 374810 Ratio Distribution 30 - 39.5% Centrality Block 15",50,0,5);

        pRPD_RatioDist[0][5] = new TH1F("","Run 374810 Ratio Distribution 40 - 49.5% Centrality Block 0",50,0,5);
        pRPD_RatioDist[1][5] = new TH1F("","Run 374810 Ratio Distribution 40 - 49.5% Centrality Block 1",50,0,5);
        pRPD_RatioDist[2][5] = new TH1F("","Run 374810 Ratio Distribution 40 - 49.5% Centrality Block 2",50,0,5);
        pRPD_RatioDist[3][5] = new TH1F("","Run 374810 Ratio Distribution 40 - 49.5% Centrality Block 3",50,0,5);
        pRPD_RatioDist[4][5] = new TH1F("","Run 374810 Ratio Distribution 40 - 49.5% Centrality Block 4",50,0,5);
        pRPD_RatioDist[5][5] = new TH1F("","Run 374810 Ratio Distribution 40 - 49.5% Centrality Block 5",50,0,5);
        pRPD_RatioDist[6][5] = new TH1F("","Run 374810 Ratio Distribution 40 - 49.5% Centrality Block 6",50,0,5);
        pRPD_RatioDist[7][5] = new TH1F("","Run 374810 Ratio Distribution 40 - 49.5% Centrality Block 7",50,0,5);
        pRPD_RatioDist[8][5] = new TH1F("","Run 374810 Ratio Distribution 40 - 49.5% Centrality Block 8",50,0,5);
        pRPD_RatioDist[9][5] = new TH1F("","Run 374810 Ratio Distribution 40 - 49.5% Centrality Block 9",50,0,5);
        pRPD_RatioDist[10][5] = new TH1F("","Run 374810 Ratio Distribution 40 - 49.5% Centrality Block 10",50,0,5);
        pRPD_RatioDist[11][5] = new TH1F("","Run 374810 Ratio Distribution 40 - 49.5% Centrality Block 11",50,0,5);
        pRPD_RatioDist[12][5] = new TH1F("","Run 374810 Ratio Distribution 40 - 49.5% Centrality Block 12",50,0,5);
        pRPD_RatioDist[13][5] = new TH1F("","Run 374810 Ratio Distribution 40 - 49.5% Centrality Block 13",50,0,5);
        pRPD_RatioDist[14][5] = new TH1F("","Run 374810 Ratio Distribution 40 - 49.5% Centrality Block 14",50,0,5);
        pRPD_RatioDist[15][5] = new TH1F("","Run 374810 Ratio Distribution 40 - 49.5% Centrality Block 15",50,0,5);

        pRPD_RatioDist[0][6] = new TH1F("","Run 374810 Ratio Distribution 50 - 59.5% Centrality Block 0",50,0,5);
        pRPD_RatioDist[1][6] = new TH1F("","Run 374810 Ratio Distribution 50 - 59.5% Centrality Block 1",50,0,5);
        pRPD_RatioDist[2][6] = new TH1F("","Run 374810 Ratio Distribution 50 - 59.5% Centrality Block 2",50,0,5);
        pRPD_RatioDist[3][6] = new TH1F("","Run 374810 Ratio Distribution 50 - 59.5% Centrality Block 3",50,0,5);
        pRPD_RatioDist[4][6] = new TH1F("","Run 374810 Ratio Distribution 50 - 59.5% Centrality Block 4",50,0,5);
        pRPD_RatioDist[5][6] = new TH1F("","Run 374810 Ratio Distribution 50 - 59.5% Centrality Block 5",50,0,5);
        pRPD_RatioDist[6][6] = new TH1F("","Run 374810 Ratio Distribution 50 - 59.5% Centrality Block 6",50,0,5);
        pRPD_RatioDist[7][6] = new TH1F("","Run 374810 Ratio Distribution 50 - 59.5% Centrality Block 7",50,0,5);
        pRPD_RatioDist[8][6] = new TH1F("","Run 374810 Ratio Distribution 50 - 59.5% Centrality Block 8",50,0,5);
        pRPD_RatioDist[9][6] = new TH1F("","Run 374810 Ratio Distribution 50 - 59.5% Centrality Block 9",50,0,5);
        pRPD_RatioDist[10][6] = new TH1F("","Run 374810 Ratio Distribution 50 - 59.5% Centrality Block 10",50,0,5);
        pRPD_RatioDist[11][6] = new TH1F("","Run 374810 Ratio Distribution 50 - 59.5% Centrality Block 11",50,0,5);
        pRPD_RatioDist[12][6] = new TH1F("","Run 374810 Ratio Distribution 50 - 59.5% Centrality Block 12",50,0,5);
        pRPD_RatioDist[13][6] = new TH1F("","Run 374810 Ratio Distribution 50 - 59.5% Centrality Block 13",50,0,5);
        pRPD_RatioDist[14][6] = new TH1F("","Run 374810 Ratio Distribution 50 - 59.5% Centrality Block 14",50,0,5);
        pRPD_RatioDist[15][6] = new TH1F("","Run 374810 Ratio Distribution 50 - 59.5% Centrality Block 15",50,0,5);

        pRPD_RatioDist[0][7] = new TH1F("","Run 374810 Ratio Distribution 60 - 69.5% Centrality Block 0",50,0,5);
        pRPD_RatioDist[1][7] = new TH1F("","Run 374810 Ratio Distribution 60 - 69.5% Centrality Block 1",50,0,5);
        pRPD_RatioDist[2][7] = new TH1F("","Run 374810 Ratio Distribution 60 - 69.5% Centrality Block 2",50,0,5);
        pRPD_RatioDist[3][7] = new TH1F("","Run 374810 Ratio Distribution 60 - 69.5% Centrality Block 3",50,0,5);
        pRPD_RatioDist[4][7] = new TH1F("","Run 374810 Ratio Distribution 60 - 69.5% Centrality Block 4",50,0,5);
        pRPD_RatioDist[5][7] = new TH1F("","Run 374810 Ratio Distribution 60 - 69.5% Centrality Block 5",50,0,5);
        pRPD_RatioDist[6][7] = new TH1F("","Run 374810 Ratio Distribution 60 - 69.5% Centrality Block 6",50,0,5);
        pRPD_RatioDist[7][7] = new TH1F("","Run 374810 Ratio Distribution 60 - 69.5% Centrality Block 7",50,0,5);
        pRPD_RatioDist[8][7] = new TH1F("","Run 374810 Ratio Distribution 60 - 69.5% Centrality Block 8",50,0,5);
        pRPD_RatioDist[9][7] = new TH1F("","Run 374810 Ratio Distribution 60 - 69.5% Centrality Block 9",50,0,5);
        pRPD_RatioDist[10][7] = new TH1F("","Run 374810 Ratio Distribution 60 - 69.5% Centrality Block 10",50,0,5);
        pRPD_RatioDist[11][7] = new TH1F("","Run 374810 Ratio Distribution 60 - 69.5% Centrality Block 11",50,0,5);
        pRPD_RatioDist[12][7] = new TH1F("","Run 374810 Ratio Distribution 60 - 69.5% Centrality Block 12",50,0,5);
        pRPD_RatioDist[13][7] = new TH1F("","Run 374810 Ratio Distribution 60 - 69.5% Centrality Block 13",50,0,5);
        pRPD_RatioDist[14][7] = new TH1F("","Run 374810 Ratio Distribution 60 - 69.5% Centrality Block 14",50,0,5);
        pRPD_RatioDist[15][7] = new TH1F("","Run 374810 Ratio Distribution 60 - 69.5% Centrality Block 15",50,0,5);

        pRPD_RatioDist[0][8] = new TH1F("","Run 374810 Ratio Distribution 70 - 79.5% Centrality Block 0",50,0,5);
        pRPD_RatioDist[1][8] = new TH1F("","Run 374810 Ratio Distribution 70 - 79.5% Centrality Block 1",50,0,5);
        pRPD_RatioDist[2][8] = new TH1F("","Run 374810 Ratio Distribution 70 - 79.5% Centrality Block 2",50,0,5);
        pRPD_RatioDist[3][8] = new TH1F("","Run 374810 Ratio Distribution 70 - 79.5% Centrality Block 3",50,0,5);
        pRPD_RatioDist[4][8] = new TH1F("","Run 374810 Ratio Distribution 70 - 79.5% Centrality Block 4",50,0,5);
        pRPD_RatioDist[5][8] = new TH1F("","Run 374810 Ratio Distribution 70 - 79.5% Centrality Block 5",50,0,5);
        pRPD_RatioDist[6][8] = new TH1F("","Run 374810 Ratio Distribution 70 - 79.5% Centrality Block 6",50,0,5);
        pRPD_RatioDist[7][8] = new TH1F("","Run 374810 Ratio Distribution 70 - 79.5% Centrality Block 7",50,0,5);
        pRPD_RatioDist[8][8] = new TH1F("","Run 374810 Ratio Distribution 70 - 79.5% Centrality Block 8",50,0,5);
        pRPD_RatioDist[9][8] = new TH1F("","Run 374810 Ratio Distribution 70 - 79.5% Centrality Block 9",50,0,5);
        pRPD_RatioDist[10][8] = new TH1F("","Run 374810 Ratio Distribution 70 - 79.5% Centrality Block 10",50,0,5);
        pRPD_RatioDist[11][8] = new TH1F("","Run 374810 Ratio Distribution 70 - 79.5% Centrality Block 11",50,0,5);
        pRPD_RatioDist[12][8] = new TH1F("","Run 374810 Ratio Distribution 70 - 79.5% Centrality Block 12",50,0,5);
        pRPD_RatioDist[13][8] = new TH1F("","Run 374810 Ratio Distribution 70 - 79.5% Centrality Block 13",50,0,5);
        pRPD_RatioDist[14][8] = new TH1F("","Run 374810 Ratio Distribution 70 - 79.5% Centrality Block 14",50,0,5);
        pRPD_RatioDist[15][8] = new TH1F("","Run 374810 Ratio Distribution 70 - 79.5% Centrality Block 15",50,0,5);

        pRPD_RatioDist[0][9] = new TH1F("","Run 374810 Ratio Distribution 80 - 89.5% Centrality Block 0",50,0,5);
        pRPD_RatioDist[1][9] = new TH1F("","Run 374810 Ratio Distribution 80 - 89.5% Centrality Block 1",50,0,5);
        pRPD_RatioDist[2][9] = new TH1F("","Run 374810 Ratio Distribution 80 - 89.5% Centrality Block 2",50,0,5);
        pRPD_RatioDist[3][9] = new TH1F("","Run 374810 Ratio Distribution 80 - 89.5% Centrality Block 3",50,0,5);
        pRPD_RatioDist[4][9] = new TH1F("","Run 374810 Ratio Distribution 80 - 89.5% Centrality Block 4",50,0,5);
        pRPD_RatioDist[5][9] = new TH1F("","Run 374810 Ratio Distribution 80 - 89.5% Centrality Block 5",50,0,5);
        pRPD_RatioDist[6][9] = new TH1F("","Run 374810 Ratio Distribution 80 - 89.5% Centrality Block 6",50,0,5);
        pRPD_RatioDist[7][9] = new TH1F("","Run 374810 Ratio Distribution 80 - 89.5% Centrality Block 7",50,0,5);
        pRPD_RatioDist[8][9] = new TH1F("","Run 374810 Ratio Distribution 80 - 89.5% Centrality Block 8",50,0,5);
        pRPD_RatioDist[9][9] = new TH1F("","Run 374810 Ratio Distribution 80 - 89.5% Centrality Block 9",50,0,5);
        pRPD_RatioDist[10][9] = new TH1F("","Run 374810 Ratio Distribution 80 - 89.5% Centrality Block 10",50,0,5);
        pRPD_RatioDist[11][9] = new TH1F("","Run 374810 Ratio Distribution 80 - 89.5% Centrality Block 11",50,0,5);
        pRPD_RatioDist[12][9] = new TH1F("","Run 374810 Ratio Distribution 80 - 89.5% Centrality Block 12",50,0,5);
        pRPD_RatioDist[13][9] = new TH1F("","Run 374810 Ratio Distribution 80 - 89.5% Centrality Block 13",50,0,5);
        pRPD_RatioDist[14][9] = new TH1F("","Run 374810 Ratio Distribution 80 - 89.5% Centrality Block 14",50,0,5);
        pRPD_RatioDist[15][9] = new TH1F("","Run 374810 Ratio Distribution 80 - 89.5% Centrality Block 15",50,0,5);

        pRPD_RatioDist[0][10] = new TH1F("","Run 374810 Ratio Distribution 90 - 100% Centrality Block 0",50,0,5);
        pRPD_RatioDist[1][10] = new TH1F("","Run 374810 Ratio Distribution 90 - 100% Centrality Block 1",50,0,5);
        pRPD_RatioDist[2][10] = new TH1F("","Run 374810 Ratio Distribution 90 - 100% Centrality Block 2",50,0,5);
        pRPD_RatioDist[3][10] = new TH1F("","Run 374810 Ratio Distribution 90 - 100% Centrality Block 3",50,0,5);
        pRPD_RatioDist[4][10] = new TH1F("","Run 374810 Ratio Distribution 90 - 100% Centrality Block 4",50,0,5);
        pRPD_RatioDist[5][10] = new TH1F("","Run 374810 Ratio Distribution 90 - 100% Centrality Block 5",50,0,5);
        pRPD_RatioDist[6][10] = new TH1F("","Run 374810 Ratio Distribution 90 - 100% Centrality Block 6",50,0,5);
        pRPD_RatioDist[7][10] = new TH1F("","Run 374810 Ratio Distribution 90 - 100% Centrality Block 7",50,0,5);
        pRPD_RatioDist[8][10] = new TH1F("","Run 374810 Ratio Distribution 90 - 100% Centrality Block 8",50,0,5);
        pRPD_RatioDist[9][10] = new TH1F("","Run 374810 Ratio Distribution 90 - 100% Centrality Block 9",50,0,5);
        pRPD_RatioDist[10][10] = new TH1F("","Run 374810 Ratio Distribution 90 - 100% Centrality Block 10",50,0,5);
        pRPD_RatioDist[11][10] = new TH1F("","Run 374810 Ratio Distribution 90 - 100% Centrality Block 11",50,0,5);
        pRPD_RatioDist[12][10] = new TH1F("","Run 374810 Ratio Distribution 90 - 100% Centrality Block 12",50,0,5);
        pRPD_RatioDist[13][10] = new TH1F("","Run 374810 Ratio Distribution 90 - 100% Centrality Block 13",50,0,5);
        pRPD_RatioDist[14][10] = new TH1F("","Run 374810 Ratio Distribution 90 - 100% Centrality Block 14",50,0,5);
        pRPD_RatioDist[15][10] = new TH1F("","Run 374810 Ratio Distribution 90 - 100% Centrality Block 15",50,0,5);

    TH1F *pEM_RatioDist[5][11] = {0};

        pEM_RatioDist[0][0] = new TH1F("","Run 374810 Ratio Distribution All Centrality pos EM 1",100,0,10);
        pEM_RatioDist[1][0] = new TH1F("","Run 374810 Ratio Distribution All Centrality pos EM 2",100,0,10);
        pEM_RatioDist[2][0] = new TH1F("","Run 374810 Ratio Distribution All Centrality pos EM 3",100,0,10);
        pEM_RatioDist[3][0] = new TH1F("","Run 374810 Ratio Distribution All Centrality pos EM 4",100,0,10);
        pEM_RatioDist[4][0] = new TH1F("","Run 374810 Ratio Distribution All Centrality pos EM 5",100,0,10);

        pEM_RatioDist[0][1] = new TH1F("","Run 374810 Ratio Distribution 0 - 9.5% Centrality pos EM 1",100,0,10);
        pEM_RatioDist[1][1] = new TH1F("","Run 374810 Ratio Distribution 0 - 9.5% Centrality pos EM 2",100,0,10);
        pEM_RatioDist[2][1] = new TH1F("","Run 374810 Ratio Distribution 0 - 9.5% Centrality pos EM 3",100,0,10);
        pEM_RatioDist[3][1] = new TH1F("","Run 374810 Ratio Distribution 0 - 9.5% Centrality pos EM 4",100,0,10);
        pEM_RatioDist[4][1] = new TH1F("","Run 374810 Ratio Distribution 0 - 9.5% Centrality pos EM 5",100,0,10);

        pEM_RatioDist[0][2] = new TH1F("","Run 374810 Ratio Distribution 10 - 19.5% Centrality pos EM 1",100,0,10);
        pEM_RatioDist[1][2] = new TH1F("","Run 374810 Ratio Distribution 10 - 19.5% Centrality pos EM 2",100,0,10);
        pEM_RatioDist[2][2] = new TH1F("","Run 374810 Ratio Distribution 10 - 19.5% Centrality pos EM 3",100,0,10);
        pEM_RatioDist[3][2] = new TH1F("","Run 374810 Ratio Distribution 10 - 19.5% Centrality pos EM 4",100,0,10);
        pEM_RatioDist[4][2] = new TH1F("","Run 374810 Ratio Distribution 10 - 19.5% Centrality pos EM 5",100,0,10);

        pEM_RatioDist[0][3] = new TH1F("","Run 374810 Ratio Distribution 20 - 29.5% Centrality pos EM 1",100,0,10);
        pEM_RatioDist[1][3] = new TH1F("","Run 374810 Ratio Distribution 20 - 29.5% Centrality pos EM 2",100,0,10);
        pEM_RatioDist[2][3] = new TH1F("","Run 374810 Ratio Distribution 20 - 29.5% Centrality pos EM 3",100,0,10);
        pEM_RatioDist[3][3] = new TH1F("","Run 374810 Ratio Distribution 20 - 29.5% Centrality pos EM 4",100,0,10);
        pEM_RatioDist[4][3] = new TH1F("","Run 374810 Ratio Distribution 20 - 29.5% Centrality pos EM 5",100,0,10);

        pEM_RatioDist[0][4] = new TH1F("","Run 374810 Ratio Distribution 30 - 39.5% Centrality pos EM 1",100,0,10);
        pEM_RatioDist[1][4] = new TH1F("","Run 374810 Ratio Distribution 30 - 39.5% Centrality pos EM 2",100,0,10);
        pEM_RatioDist[2][4] = new TH1F("","Run 374810 Ratio Distribution 30 - 39.5% Centrality pos EM 3",100,0,10);
        pEM_RatioDist[3][4] = new TH1F("","Run 374810 Ratio Distribution 30 - 39.5% Centrality pos EM 4",100,0,10);
        pEM_RatioDist[4][4] = new TH1F("","Run 374810 Ratio Distribution 30 - 39.5% Centrality pos EM 5",100,0,10);

        pEM_RatioDist[0][5] = new TH1F("","Run 374810 Ratio Distribution 40 - 49.5% Centrality pos EM 1",100,0,10);
        pEM_RatioDist[1][5] = new TH1F("","Run 374810 Ratio Distribution 40 - 49.5% Centrality pos EM 2",100,0,10);
        pEM_RatioDist[2][5] = new TH1F("","Run 374810 Ratio Distribution 40 - 49.5% Centrality pos EM 3",100,0,10);
        pEM_RatioDist[3][5] = new TH1F("","Run 374810 Ratio Distribution 40 - 49.5% Centrality pos EM 4",100,0,10);
        pEM_RatioDist[4][5] = new TH1F("","Run 374810 Ratio Distribution 40 - 49.5% Centrality pos EM 5",100,0,10);

        pEM_RatioDist[0][6] = new TH1F("","Run 374810 Ratio Distribution 50 - 59.5% Centrality pos EM 1",100,0,10);
        pEM_RatioDist[1][6] = new TH1F("","Run 374810 Ratio Distribution 50 - 59.5% Centrality pos EM 2",100,0,10);
        pEM_RatioDist[2][6] = new TH1F("","Run 374810 Ratio Distribution 50 - 59.5% Centrality pos EM 3",100,0,10);
        pEM_RatioDist[3][6] = new TH1F("","Run 374810 Ratio Distribution 50 - 59.5% Centrality pos EM 4",100,0,10);
        pEM_RatioDist[4][6] = new TH1F("","Run 374810 Ratio Distribution 50 - 59.5% Centrality pos EM 5",100,0,10);

        pEM_RatioDist[0][7] = new TH1F("","Run 374810 Ratio Distribution 60 - 69.5% Centrality pos EM 1",100,0,10);
        pEM_RatioDist[1][7] = new TH1F("","Run 374810 Ratio Distribution 60 - 69.5% Centrality pos EM 2",100,0,10);
        pEM_RatioDist[2][7] = new TH1F("","Run 374810 Ratio Distribution 60 - 69.5% Centrality pos EM 3",100,0,10);
        pEM_RatioDist[3][7] = new TH1F("","Run 374810 Ratio Distribution 60 - 69.5% Centrality pos EM 4",100,0,10);
        pEM_RatioDist[4][7] = new TH1F("","Run 374810 Ratio Distribution 60 - 69.5% Centrality pos EM 5",100,0,10);

        pEM_RatioDist[0][8] = new TH1F("","Run 374810 Ratio Distribution 70 - 79.5% Centrality pos EM 1",100,0,10);
        pEM_RatioDist[1][8] = new TH1F("","Run 374810 Ratio Distribution 70 - 79.5% Centrality pos EM 2",100,0,10);
        pEM_RatioDist[2][8] = new TH1F("","Run 374810 Ratio Distribution 70 - 79.5% Centrality pos EM 3",100,0,10);
        pEM_RatioDist[3][8] = new TH1F("","Run 374810 Ratio Distribution 70 - 79.5% Centrality pos EM 4",100,0,10);
        pEM_RatioDist[4][8] = new TH1F("","Run 374810 Ratio Distribution 70 - 79.5% Centrality pos EM 5",100,0,10);

        pEM_RatioDist[0][9] = new TH1F("","Run 374810 Ratio Distribution 80 - 89.5% Centrality pos EM 1",100,0,10);
        pEM_RatioDist[1][9] = new TH1F("","Run 374810 Ratio Distribution 80 - 89.5% Centrality pos EM 2",100,0,10);
        pEM_RatioDist[2][9] = new TH1F("","Run 374810 Ratio Distribution 80 - 89.5% Centrality pos EM 3",100,0,10);
        pEM_RatioDist[3][9] = new TH1F("","Run 374810 Ratio Distribution 80 - 89.5% Centrality pos EM 4",100,0,10);
        pEM_RatioDist[4][9] = new TH1F("","Run 374810 Ratio Distribution 80 - 89.5% Centrality pos EM 5",100,0,10);

        pEM_RatioDist[0][10] = new TH1F("","Run 374810 Ratio Distribution 90 - 100% Centrality pos EM 1",100,0,10);
        pEM_RatioDist[1][10] = new TH1F("","Run 374810 Ratio Distribution 90 - 100% Centrality pos EM 2",100,0,10);
        pEM_RatioDist[2][10] = new TH1F("","Run 374810 Ratio Distribution 90 - 100% Centrality pos EM 3",100,0,10);
        pEM_RatioDist[3][10] = new TH1F("","Run 374810 Ratio Distribution 90 - 100% Centrality pos EM 4",100,0,10);
        pEM_RatioDist[4][10] = new TH1F("","Run 374810 Ratio Distribution 90 - 100% Centrality pos EM 5",100,0,10);

    TH1F *pHAD_RatioDist[4][11] = {0};

        pHAD_RatioDist[0][0] = new TH1F("","Run 374810 Ratio Distribution All Centrality pos HAD 1",70,0,7);
        pHAD_RatioDist[1][0] = new TH1F("","Run 374810 Ratio Distribution All Centrality pos HAD 2",70,0,7);
        pHAD_RatioDist[2][0] = new TH1F("","Run 374810 Ratio Distribution All Centrality pos HAD 3",70,0,7);
        pHAD_RatioDist[3][0] = new TH1F("","Run 374810 Ratio Distribution All Centrality pos HAD 4",70,0,7);

        pHAD_RatioDist[0][1] = new TH1F("","Run 374810 Ratio Distribution 0 - 9.5% Centrality pos HAD 1",70,0,7);
        pHAD_RatioDist[1][1] = new TH1F("","Run 374810 Ratio Distribution 0 - 9.5% Centrality pos HAD 2",70,0,7);
        pHAD_RatioDist[2][1] = new TH1F("","Run 374810 Ratio Distribution 0 - 9.5% Centrality pos HAD 3",70,0,7);
        pHAD_RatioDist[3][1] = new TH1F("","Run 374810 Ratio Distribution 0 - 9.5% Centrality pos HAD 4",70,0,7);

        pHAD_RatioDist[0][2] = new TH1F("","Run 374810 Ratio Distribution 10 - 19.5% Centrality pos HAD 1",70,0,7);
        pHAD_RatioDist[1][2] = new TH1F("","Run 374810 Ratio Distribution 10 - 19.5% Centrality pos HAD 2",70,0,7);
        pHAD_RatioDist[2][2] = new TH1F("","Run 374810 Ratio Distribution 10 - 19.5% Centrality pos HAD 3",70,0,7);
        pHAD_RatioDist[3][2] = new TH1F("","Run 374810 Ratio Distribution 10 - 19.5% Centrality pos HAD 4",70,0,7);

        pHAD_RatioDist[0][3] = new TH1F("","Run 374810 Ratio Distribution 20 - 29.5% Centrality pos HAD 1",70,0,7);
        pHAD_RatioDist[1][3] = new TH1F("","Run 374810 Ratio Distribution 20 - 29.5% Centrality pos HAD 2",70,0,7);
        pHAD_RatioDist[2][3] = new TH1F("","Run 374810 Ratio Distribution 20 - 29.5% Centrality pos HAD 3",70,0,7);
        pHAD_RatioDist[3][3] = new TH1F("","Run 374810 Ratio Distribution 20 - 29.5% Centrality pos HAD 4",70,0,7);

        pHAD_RatioDist[0][4] = new TH1F("","Run 374810 Ratio Distribution 30 - 39.5% Centrality pos HAD 1",70,0,7);
        pHAD_RatioDist[1][4] = new TH1F("","Run 374810 Ratio Distribution 30 - 39.5% Centrality pos HAD 2",70,0,7);
        pHAD_RatioDist[2][4] = new TH1F("","Run 374810 Ratio Distribution 30 - 39.5% Centrality pos HAD 3",70,0,7);
        pHAD_RatioDist[3][4] = new TH1F("","Run 374810 Ratio Distribution 30 - 39.5% Centrality pos HAD 4",70,0,7);

        pHAD_RatioDist[0][5] = new TH1F("","Run 374810 Ratio Distribution 40 - 49.5% Centrality pos HAD 1",70,0,7);
        pHAD_RatioDist[1][5] = new TH1F("","Run 374810 Ratio Distribution 40 - 49.5% Centrality pos HAD 2",70,0,7);
        pHAD_RatioDist[2][5] = new TH1F("","Run 374810 Ratio Distribution 40 - 49.5% Centrality pos HAD 3",70,0,7);
        pHAD_RatioDist[3][5] = new TH1F("","Run 374810 Ratio Distribution 40 - 49.5% Centrality pos HAD 4",70,0,7);

        pHAD_RatioDist[0][6] = new TH1F("","Run 374810 Ratio Distribution 50 - 59.5% Centrality pos HAD 1",70,0,7);
        pHAD_RatioDist[1][6] = new TH1F("","Run 374810 Ratio Distribution 50 - 59.5% Centrality pos HAD 2",70,0,7);
        pHAD_RatioDist[2][6] = new TH1F("","Run 374810 Ratio Distribution 50 - 59.5% Centrality pos HAD 3",70,0,7);
        pHAD_RatioDist[3][6] = new TH1F("","Run 374810 Ratio Distribution 50 - 59.5% Centrality pos HAD 4",70,0,7);

        pHAD_RatioDist[0][7] = new TH1F("","Run 374810 Ratio Distribution 60 - 69.5% Centrality pos HAD 1",70,0,7);
        pHAD_RatioDist[1][7] = new TH1F("","Run 374810 Ratio Distribution 60 - 69.5% Centrality pos HAD 2",70,0,7);
        pHAD_RatioDist[2][7] = new TH1F("","Run 374810 Ratio Distribution 60 - 69.5% Centrality pos HAD 3",70,0,7);
        pHAD_RatioDist[3][7] = new TH1F("","Run 374810 Ratio Distribution 60 - 69.5% Centrality pos HAD 4",70,0,7);

        pHAD_RatioDist[0][8] = new TH1F("","Run 374810 Ratio Distribution 70 - 79.5% Centrality pos HAD 1",70,0,7);
        pHAD_RatioDist[1][8] = new TH1F("","Run 374810 Ratio Distribution 70 - 79.5% Centrality pos HAD 2",70,0,7);
        pHAD_RatioDist[2][8] = new TH1F("","Run 374810 Ratio Distribution 70 - 79.5% Centrality pos HAD 3",70,0,7);
        pHAD_RatioDist[3][8] = new TH1F("","Run 374810 Ratio Distribution 70 - 79.5% Centrality pos HAD 4",70,0,7);

        pHAD_RatioDist[0][9] = new TH1F("","Run 374810 Ratio Distribution 80 - 89.5% Centrality pos HAD 1",70,0,7);
        pHAD_RatioDist[1][9] = new TH1F("","Run 374810 Ratio Distribution 80 - 89.5% Centrality pos HAD 2",70,0,7);
        pHAD_RatioDist[2][9] = new TH1F("","Run 374810 Ratio Distribution 80 - 89.5% Centrality pos HAD 3",70,0,7);
        pHAD_RatioDist[3][9] = new TH1F("","Run 374810 Ratio Distribution 80 - 89.5% Centrality pos HAD 4",70,0,7);

        pHAD_RatioDist[0][10] = new TH1F("","Run 374810 Ratio Distribution 90 - 100% Centrality pos HAD 1",70,0,7);
        pHAD_RatioDist[1][10] = new TH1F("","Run 374810 Ratio Distribution 90 - 100% Centrality pos HAD 2",70,0,7);
        pHAD_RatioDist[2][10] = new TH1F("","Run 374810 Ratio Distribution 90 - 100% Centrality pos HAD 3",70,0,7);
        pHAD_RatioDist[3][10] = new TH1F("","Run 374810 Ratio Distribution 90 - 100% Centrality pos HAD 4",70,0,7);

    TH1F *pRPD_fCDist[16][11] = {0};

        pRPD_fCDist[0][0] = new TH1F("","Run 374810 pos RPD fC Distribution All Centrality Block 0",100,0,400000);
        pRPD_fCDist[1][0] = new TH1F("","Run 374810 pos RPD fC Distribution All Centrality Block 1",100,0,400000);
        pRPD_fCDist[2][0] = new TH1F("","Run 374810 pos RPD fC Distribution All Centrality Block 2",100,0,400000);
        pRPD_fCDist[3][0] = new TH1F("","Run 374810 pos RPD fC Distribution All Centrality Block 3",100,0,400000);
        pRPD_fCDist[4][0] = new TH1F("","Run 374810 pos RPD fC Distribution All Centrality Block 4",100,0,400000);
        pRPD_fCDist[5][0] = new TH1F("","Run 374810 pos RPD fC Distribution All Centrality Block 5",100,0,400000);
        pRPD_fCDist[6][0] = new TH1F("","Run 374810 pos RPD fC Distribution All Centrality Block 6",100,0,400000);
        pRPD_fCDist[7][0] = new TH1F("","Run 374810 pos RPD fC Distribution All Centrality Block 7",100,0,400000);
        pRPD_fCDist[8][0] = new TH1F("","Run 374810 pos RPD fC Distribution All Centrality Block 8",100,0,400000);
        pRPD_fCDist[9][0] = new TH1F("","Run 374810 pos RPD fC Distribution All Centrality Block 9",100,0,400000);
        pRPD_fCDist[10][0] = new TH1F("","Run 374810 pos RPD fC Distribution All Centrality Block 10",100,0,400000);
        pRPD_fCDist[11][0] = new TH1F("","Run 374810 pos RPD fC Distribution All Centrality Block 11",100,0,400000);
        pRPD_fCDist[12][0] = new TH1F("","Run 374810 pos RPD fC Distribution All Centrality Block 12",100,0,400000);
        pRPD_fCDist[13][0] = new TH1F("","Run 374810 pos RPD fC Distribution All Centrality Block 13",100,0,400000);
        pRPD_fCDist[14][0] = new TH1F("","Run 374810 pos RPD fC Distribution All Centrality Block 14",100,0,400000);
        pRPD_fCDist[15][0] = new TH1F("","Run 374810 pos RPD fC Distribution All Centrality Block 15",100,0,400000);

        pRPD_fCDist[0][1] = new TH1F("","Run 374810 pos RPD fC Distribution 0 - 9.5% Centrality Block 0",100,0,400000);
        pRPD_fCDist[1][1] = new TH1F("","Run 374810 pos RPD fC Distribution 0 - 9.5% Centrality Block 1",100,0,400000);
        pRPD_fCDist[2][1] = new TH1F("","Run 374810 pos RPD fC Distribution 0 - 9.5% Centrality Block 2",100,0,400000);
        pRPD_fCDist[3][1] = new TH1F("","Run 374810 pos RPD fC Distribution 0 - 9.5% Centrality Block 3",100,0,400000);
        pRPD_fCDist[4][1] = new TH1F("","Run 374810 pos RPD fC Distribution 0 - 9.5% Centrality Block 4",100,0,400000);
        pRPD_fCDist[5][1] = new TH1F("","Run 374810 pos RPD fC Distribution 0 - 9.5% Centrality Block 5",100,0,400000);
        pRPD_fCDist[6][1] = new TH1F("","Run 374810 pos RPD fC Distribution 0 - 9.5% Centrality Block 6",100,0,400000);
        pRPD_fCDist[7][1] = new TH1F("","Run 374810 pos RPD fC Distribution 0 - 9.5% Centrality Block 7",100,0,400000);
        pRPD_fCDist[8][1] = new TH1F("","Run 374810 pos RPD fC Distribution 0 - 9.5% Centrality Block 8",100,0,400000);
        pRPD_fCDist[9][1] = new TH1F("","Run 374810 pos RPD fC Distribution 0 - 9.5% Centrality Block 9",100,0,400000);
        pRPD_fCDist[10][1] = new TH1F("","Run 374810 pos RPD fC Distribution 0 - 9.5% Centrality Block 10",100,0,400000);
        pRPD_fCDist[11][1] = new TH1F("","Run 374810 pos RPD fC Distribution 0 - 9.5% Centrality Block 11",100,0,400000);
        pRPD_fCDist[12][1] = new TH1F("","Run 374810 pos RPD fC Distribution 0 - 9.5% Centrality Block 12",100,0,400000);
        pRPD_fCDist[13][1] = new TH1F("","Run 374810 pos RPD fC Distribution 0 - 9.5% Centrality Block 13",100,0,400000);
        pRPD_fCDist[14][1] = new TH1F("","Run 374810 pos RPD fC Distribution 0 - 9.5% Centrality Block 14",100,0,400000);
        pRPD_fCDist[15][1] = new TH1F("","Run 374810 pos RPD fC Distribution 0 - 9.5% Centrality Block 15",100,0,400000);

        pRPD_fCDist[0][2] = new TH1F("","Run 374810 pos RPD fC Distribution 10 - 19.5% Centrality Block 0",100,0,400000);
        pRPD_fCDist[1][2] = new TH1F("","Run 374810 pos RPD fC Distribution 10 - 19.5% Centrality Block 1",100,0,400000);
        pRPD_fCDist[2][2] = new TH1F("","Run 374810 pos RPD fC Distribution 10 - 19.5% Centrality Block 2",100,0,400000);
        pRPD_fCDist[3][2] = new TH1F("","Run 374810 pos RPD fC Distribution 10 - 19.5% Centrality Block 3",100,0,400000);
        pRPD_fCDist[4][2] = new TH1F("","Run 374810 pos RPD fC Distribution 10 - 19.5% Centrality Block 4",100,0,400000);
        pRPD_fCDist[5][2] = new TH1F("","Run 374810 pos RPD fC Distribution 10 - 19.5% Centrality Block 5",100,0,400000);
        pRPD_fCDist[6][2] = new TH1F("","Run 374810 pos RPD fC Distribution 10 - 19.5% Centrality Block 6",100,0,400000);
        pRPD_fCDist[7][2] = new TH1F("","Run 374810 pos RPD fC Distribution 10 - 19.5% Centrality Block 7",100,0,400000);
        pRPD_fCDist[8][2] = new TH1F("","Run 374810 pos RPD fC Distribution 10 - 19.5% Centrality Block 8",100,0,400000);
        pRPD_fCDist[9][2] = new TH1F("","Run 374810 pos RPD fC Distribution 10 - 19.5% Centrality Block 9",100,0,400000);
        pRPD_fCDist[10][2] = new TH1F("","Run 374810 pos RPD fC Distribution 10 - 19.5% Centrality Block 10",100,0,400000);
        pRPD_fCDist[11][2] = new TH1F("","Run 374810 pos RPD fC Distribution 10 - 19.5% Centrality Block 11",100,0,400000);
        pRPD_fCDist[12][2] = new TH1F("","Run 374810 pos RPD fC Distribution 10 - 19.5% Centrality Block 12",100,0,400000);
        pRPD_fCDist[13][2] = new TH1F("","Run 374810 pos RPD fC Distribution 10 - 19.5% Centrality Block 13",100,0,400000);
        pRPD_fCDist[14][2] = new TH1F("","Run 374810 pos RPD fC Distribution 10 - 19.5% Centrality Block 14",100,0,400000);
        pRPD_fCDist[15][2] = new TH1F("","Run 374810 pos RPD fC Distribution 10 - 19.5% Centrality Block 15",100,0,400000);

        pRPD_fCDist[0][3] = new TH1F("","Run 374810 pos RPD fC Distribution 20 - 29.5% Centrality Block 0",100,0,400000);
        pRPD_fCDist[1][3] = new TH1F("","Run 374810 pos RPD fC Distribution 20 - 29.5% Centrality Block 1",100,0,400000);
        pRPD_fCDist[2][3] = new TH1F("","Run 374810 pos RPD fC Distribution 20 - 29.5% Centrality Block 2",100,0,400000);
        pRPD_fCDist[3][3] = new TH1F("","Run 374810 pos RPD fC Distribution 20 - 29.5% Centrality Block 3",100,0,400000);
        pRPD_fCDist[4][3] = new TH1F("","Run 374810 pos RPD fC Distribution 20 - 29.5% Centrality Block 4",100,0,400000);
        pRPD_fCDist[5][3] = new TH1F("","Run 374810 pos RPD fC Distribution 20 - 29.5% Centrality Block 5",100,0,400000);
        pRPD_fCDist[6][3] = new TH1F("","Run 374810 pos RPD fC Distribution 20 - 29.5% Centrality Block 6",100,0,400000);
        pRPD_fCDist[7][3] = new TH1F("","Run 374810 pos RPD fC Distribution 20 - 29.5% Centrality Block 7",100,0,400000);
        pRPD_fCDist[8][3] = new TH1F("","Run 374810 pos RPD fC Distribution 20 - 29.5% Centrality Block 8",100,0,400000);
        pRPD_fCDist[9][3] = new TH1F("","Run 374810 pos RPD fC Distribution 20 - 29.5% Centrality Block 9",100,0,400000);
        pRPD_fCDist[10][3] = new TH1F("","Run 374810 pos RPD fC Distribution 20 - 29.5% Centrality Block 10",100,0,400000);
        pRPD_fCDist[11][3] = new TH1F("","Run 374810 pos RPD fC Distribution 20 - 29.5% Centrality Block 11",100,0,400000);
        pRPD_fCDist[12][3] = new TH1F("","Run 374810 pos RPD fC Distribution 20 - 29.5% Centrality Block 12",100,0,400000);
        pRPD_fCDist[13][3] = new TH1F("","Run 374810 pos RPD fC Distribution 20 - 29.5% Centrality Block 13",100,0,400000);
        pRPD_fCDist[14][3] = new TH1F("","Run 374810 pos RPD fC Distribution 20 - 29.5% Centrality Block 14",100,0,400000);
        pRPD_fCDist[15][3] = new TH1F("","Run 374810 pos RPD fC Distribution 20 - 29.5% Centrality Block 15",100,0,400000);

        pRPD_fCDist[0][4] = new TH1F("","Run 374810 pos RPD fC Distribution 30 - 39.5% Centrality Block 0",100,0,400000);
        pRPD_fCDist[1][4] = new TH1F("","Run 374810 pos RPD fC Distribution 30 - 39.5% Centrality Block 1",100,0,400000);
        pRPD_fCDist[2][4] = new TH1F("","Run 374810 pos RPD fC Distribution 30 - 39.5% Centrality Block 2",100,0,400000);
        pRPD_fCDist[3][4] = new TH1F("","Run 374810 pos RPD fC Distribution 30 - 39.5% Centrality Block 3",100,0,400000);
        pRPD_fCDist[4][4] = new TH1F("","Run 374810 pos RPD fC Distribution 30 - 39.5% Centrality Block 4",100,0,400000);
        pRPD_fCDist[5][4] = new TH1F("","Run 374810 pos RPD fC Distribution 30 - 39.5% Centrality Block 5",100,0,400000);
        pRPD_fCDist[6][4] = new TH1F("","Run 374810 pos RPD fC Distribution 30 - 39.5% Centrality Block 6",100,0,400000);
        pRPD_fCDist[7][4] = new TH1F("","Run 374810 pos RPD fC Distribution 30 - 39.5% Centrality Block 7",100,0,400000);
        pRPD_fCDist[8][4] = new TH1F("","Run 374810 pos RPD fC Distribution 30 - 39.5% Centrality Block 8",100,0,400000);
        pRPD_fCDist[9][4] = new TH1F("","Run 374810 pos RPD fC Distribution 30 - 39.5% Centrality Block 9",100,0,400000);
        pRPD_fCDist[10][4] = new TH1F("","Run 374810 pos RPD fC Distribution 30 - 39.5% Centrality Block 10",100,0,400000);
        pRPD_fCDist[11][4] = new TH1F("","Run 374810 pos RPD fC Distribution 30 - 39.5% Centrality Block 11",100,0,400000);
        pRPD_fCDist[12][4] = new TH1F("","Run 374810 pos RPD fC Distribution 30 - 39.5% Centrality Block 12",100,0,400000);
        pRPD_fCDist[13][4] = new TH1F("","Run 374810 pos RPD fC Distribution 30 - 39.5% Centrality Block 13",100,0,400000);
        pRPD_fCDist[14][4] = new TH1F("","Run 374810 pos RPD fC Distribution 30 - 39.5% Centrality Block 14",100,0,400000);
        pRPD_fCDist[15][4] = new TH1F("","Run 374810 pos RPD fC Distribution 30 - 39.5% Centrality Block 15",100,0,400000);

        pRPD_fCDist[0][5] = new TH1F("","Run 374810 pos RPD fC Distribution 40 - 49.5% Centrality Block 0",100,0,400000);
        pRPD_fCDist[1][5] = new TH1F("","Run 374810 pos RPD fC Distribution 40 - 49.5% Centrality Block 1",100,0,400000);
        pRPD_fCDist[2][5] = new TH1F("","Run 374810 pos RPD fC Distribution 40 - 49.5% Centrality Block 2",100,0,400000);
        pRPD_fCDist[3][5] = new TH1F("","Run 374810 pos RPD fC Distribution 40 - 49.5% Centrality Block 3",100,0,400000);
        pRPD_fCDist[4][5] = new TH1F("","Run 374810 pos RPD fC Distribution 40 - 49.5% Centrality Block 4",100,0,400000);
        pRPD_fCDist[5][5] = new TH1F("","Run 374810 pos RPD fC Distribution 40 - 49.5% Centrality Block 5",100,0,400000);
        pRPD_fCDist[6][5] = new TH1F("","Run 374810 pos RPD fC Distribution 40 - 49.5% Centrality Block 6",100,0,400000);
        pRPD_fCDist[7][5] = new TH1F("","Run 374810 pos RPD fC Distribution 40 - 49.5% Centrality Block 7",100,0,400000);
        pRPD_fCDist[8][5] = new TH1F("","Run 374810 pos RPD fC Distribution 40 - 49.5% Centrality Block 8",100,0,400000);
        pRPD_fCDist[9][5] = new TH1F("","Run 374810 pos RPD fC Distribution 40 - 49.5% Centrality Block 9",100,0,400000);
        pRPD_fCDist[10][5] = new TH1F("","Run 374810 pos RPD fC Distribution 40 - 49.5% Centrality Block 10",100,0,400000);
        pRPD_fCDist[11][5] = new TH1F("","Run 374810 pos RPD fC Distribution 40 - 49.5% Centrality Block 11",100,0,400000);
        pRPD_fCDist[12][5] = new TH1F("","Run 374810 pos RPD fC Distribution 40 - 49.5% Centrality Block 12",100,0,400000);
        pRPD_fCDist[13][5] = new TH1F("","Run 374810 pos RPD fC Distribution 40 - 49.5% Centrality Block 13",100,0,400000);
        pRPD_fCDist[14][5] = new TH1F("","Run 374810 pos RPD fC Distribution 40 - 49.5% Centrality Block 14",100,0,400000);
        pRPD_fCDist[15][5] = new TH1F("","Run 374810 pos RPD fC Distribution 40 - 49.5% Centrality Block 15",100,0,400000);

        pRPD_fCDist[0][6] = new TH1F("","Run 374810 pos RPD fC Distribution 50 - 59.5% Centrality Block 0",100,0,400000);
        pRPD_fCDist[1][6] = new TH1F("","Run 374810 pos RPD fC Distribution 50 - 59.5% Centrality Block 1",100,0,400000);
        pRPD_fCDist[2][6] = new TH1F("","Run 374810 pos RPD fC Distribution 50 - 59.5% Centrality Block 2",100,0,400000);
        pRPD_fCDist[3][6] = new TH1F("","Run 374810 pos RPD fC Distribution 50 - 59.5% Centrality Block 3",100,0,400000);
        pRPD_fCDist[4][6] = new TH1F("","Run 374810 pos RPD fC Distribution 50 - 59.5% Centrality Block 4",100,0,400000);
        pRPD_fCDist[5][6] = new TH1F("","Run 374810 pos RPD fC Distribution 50 - 59.5% Centrality Block 5",100,0,400000);
        pRPD_fCDist[6][6] = new TH1F("","Run 374810 pos RPD fC Distribution 50 - 59.5% Centrality Block 6",100,0,400000);
        pRPD_fCDist[7][6] = new TH1F("","Run 374810 pos RPD fC Distribution 50 - 59.5% Centrality Block 7",100,0,400000);
        pRPD_fCDist[8][6] = new TH1F("","Run 374810 pos RPD fC Distribution 50 - 59.5% Centrality Block 8",100,0,400000);
        pRPD_fCDist[9][6] = new TH1F("","Run 374810 pos RPD fC Distribution 50 - 59.5% Centrality Block 9",100,0,400000);
        pRPD_fCDist[10][6] = new TH1F("","Run 374810 pos RPD fC Distribution 50 - 59.5% Centrality Block 10",100,0,400000);
        pRPD_fCDist[11][6] = new TH1F("","Run 374810 pos RPD fC Distribution 50 - 59.5% Centrality Block 11",100,0,400000);
        pRPD_fCDist[12][6] = new TH1F("","Run 374810 pos RPD fC Distribution 50 - 59.5% Centrality Block 12",100,0,400000);
        pRPD_fCDist[13][6] = new TH1F("","Run 374810 pos RPD fC Distribution 50 - 59.5% Centrality Block 13",100,0,400000);
        pRPD_fCDist[14][6] = new TH1F("","Run 374810 pos RPD fC Distribution 50 - 59.5% Centrality Block 14",100,0,400000);
        pRPD_fCDist[15][6] = new TH1F("","Run 374810 pos RPD fC Distribution 50 - 59.5% Centrality Block 15",100,0,400000);

        pRPD_fCDist[0][7] = new TH1F("","Run 374810 pos RPD fC Distribution 60 - 69.5% Centrality Block 0",100,0,400000);
        pRPD_fCDist[1][7] = new TH1F("","Run 374810 pos RPD fC Distribution 60 - 69.5% Centrality Block 1",100,0,400000);
        pRPD_fCDist[2][7] = new TH1F("","Run 374810 pos RPD fC Distribution 60 - 69.5% Centrality Block 2",100,0,400000);
        pRPD_fCDist[3][7] = new TH1F("","Run 374810 pos RPD fC Distribution 60 - 69.5% Centrality Block 3",100,0,400000);
        pRPD_fCDist[4][7] = new TH1F("","Run 374810 pos RPD fC Distribution 60 - 69.5% Centrality Block 4",100,0,400000);
        pRPD_fCDist[5][7] = new TH1F("","Run 374810 pos RPD fC Distribution 60 - 69.5% Centrality Block 5",100,0,400000);
        pRPD_fCDist[6][7] = new TH1F("","Run 374810 pos RPD fC Distribution 60 - 69.5% Centrality Block 6",100,0,400000);
        pRPD_fCDist[7][7] = new TH1F("","Run 374810 pos RPD fC Distribution 60 - 69.5% Centrality Block 7",100,0,400000);
        pRPD_fCDist[8][7] = new TH1F("","Run 374810 pos RPD fC Distribution 60 - 69.5% Centrality Block 8",100,0,400000);
        pRPD_fCDist[9][7] = new TH1F("","Run 374810 pos RPD fC Distribution 60 - 69.5% Centrality Block 9",100,0,400000);
        pRPD_fCDist[10][7] = new TH1F("","Run 374810 pos RPD fC Distribution 60 - 69.5% Centrality Block 10",100,0,400000);
        pRPD_fCDist[11][7] = new TH1F("","Run 374810 pos RPD fC Distribution 60 - 69.5% Centrality Block 11",100,0,400000);
        pRPD_fCDist[12][7] = new TH1F("","Run 374810 pos RPD fC Distribution 60 - 69.5% Centrality Block 12",100,0,400000);
        pRPD_fCDist[13][7] = new TH1F("","Run 374810 pos RPD fC Distribution 60 - 69.5% Centrality Block 13",100,0,400000);
        pRPD_fCDist[14][7] = new TH1F("","Run 374810 pos RPD fC Distribution 60 - 69.5% Centrality Block 14",100,0,400000);
        pRPD_fCDist[15][7] = new TH1F("","Run 374810 pos RPD fC Distribution 60 - 69.5% Centrality Block 15",100,0,400000);

        pRPD_fCDist[0][8] = new TH1F("","Run 374810 pos RPD fC Distribution 70 - 79.5% Centrality Block 0",100,0,400000);
        pRPD_fCDist[1][8] = new TH1F("","Run 374810 pos RPD fC Distribution 70 - 79.5% Centrality Block 1",100,0,400000);
        pRPD_fCDist[2][8] = new TH1F("","Run 374810 pos RPD fC Distribution 70 - 79.5% Centrality Block 2",100,0,400000);
        pRPD_fCDist[3][8] = new TH1F("","Run 374810 pos RPD fC Distribution 70 - 79.5% Centrality Block 3",100,0,400000);
        pRPD_fCDist[4][8] = new TH1F("","Run 374810 pos RPD fC Distribution 70 - 79.5% Centrality Block 4",100,0,400000);
        pRPD_fCDist[5][8] = new TH1F("","Run 374810 pos RPD fC Distribution 70 - 79.5% Centrality Block 5",100,0,400000);
        pRPD_fCDist[6][8] = new TH1F("","Run 374810 pos RPD fC Distribution 70 - 79.5% Centrality Block 6",100,0,400000);
        pRPD_fCDist[7][8] = new TH1F("","Run 374810 pos RPD fC Distribution 70 - 79.5% Centrality Block 7",100,0,400000);
        pRPD_fCDist[8][8] = new TH1F("","Run 374810 pos RPD fC Distribution 70 - 79.5% Centrality Block 8",100,0,400000);
        pRPD_fCDist[9][8] = new TH1F("","Run 374810 pos RPD fC Distribution 70 - 79.5% Centrality Block 9",100,0,400000);
        pRPD_fCDist[10][8] = new TH1F("","Run 374810 pos RPD fC Distribution 70 - 79.5% Centrality Block 10",100,0,400000);
        pRPD_fCDist[11][8] = new TH1F("","Run 374810 pos RPD fC Distribution 70 - 79.5% Centrality Block 11",100,0,400000);
        pRPD_fCDist[12][8] = new TH1F("","Run 374810 pos RPD fC Distribution 70 - 79.5% Centrality Block 12",100,0,400000);
        pRPD_fCDist[13][8] = new TH1F("","Run 374810 pos RPD fC Distribution 70 - 79.5% Centrality Block 13",100,0,400000);
        pRPD_fCDist[14][8] = new TH1F("","Run 374810 pos RPD fC Distribution 70 - 79.5% Centrality Block 14",100,0,400000);
        pRPD_fCDist[15][8] = new TH1F("","Run 374810 pos RPD fC Distribution 70 - 79.5% Centrality Block 15",100,0,400000);

        pRPD_fCDist[0][9] = new TH1F("","Run 374810 pos RPD fC Distribution 80 - 89.5% Centrality Block 0",100,0,400000);
        pRPD_fCDist[1][9] = new TH1F("","Run 374810 pos RPD fC Distribution 80 - 89.5% Centrality Block 1",100,0,400000);
        pRPD_fCDist[2][9] = new TH1F("","Run 374810 pos RPD fC Distribution 80 - 89.5% Centrality Block 2",100,0,400000);
        pRPD_fCDist[3][9] = new TH1F("","Run 374810 pos RPD fC Distribution 80 - 89.5% Centrality Block 3",100,0,400000);
        pRPD_fCDist[4][9] = new TH1F("","Run 374810 pos RPD fC Distribution 80 - 89.5% Centrality Block 4",100,0,400000);
        pRPD_fCDist[5][9] = new TH1F("","Run 374810 pos RPD fC Distribution 80 - 89.5% Centrality Block 5",100,0,400000);
        pRPD_fCDist[6][9] = new TH1F("","Run 374810 pos RPD fC Distribution 80 - 89.5% Centrality Block 6",100,0,400000);
        pRPD_fCDist[7][9] = new TH1F("","Run 374810 pos RPD fC Distribution 80 - 89.5% Centrality Block 7",100,0,400000);
        pRPD_fCDist[8][9] = new TH1F("","Run 374810 pos RPD fC Distribution 80 - 89.5% Centrality Block 8",100,0,400000);
        pRPD_fCDist[9][9] = new TH1F("","Run 374810 pos RPD fC Distribution 80 - 89.5% Centrality Block 9",100,0,400000);
        pRPD_fCDist[10][9] = new TH1F("","Run 374810 pos RPD fC Distribution 80 - 89.5% Centrality Block 10",100,0,400000);
        pRPD_fCDist[11][9] = new TH1F("","Run 374810 pos RPD fC Distribution 80 - 89.5% Centrality Block 11",100,0,400000);
        pRPD_fCDist[12][9] = new TH1F("","Run 374810 pos RPD fC Distribution 80 - 89.5% Centrality Block 12",100,0,400000);
        pRPD_fCDist[13][9] = new TH1F("","Run 374810 pos RPD fC Distribution 80 - 89.5% Centrality Block 13",100,0,400000);
        pRPD_fCDist[14][9] = new TH1F("","Run 374810 pos RPD fC Distribution 80 - 89.5% Centrality Block 14",100,0,400000);
        pRPD_fCDist[15][9] = new TH1F("","Run 374810 pos RPD fC Distribution 80 - 89.5% Centrality Block 15",100,0,400000);

        pRPD_fCDist[0][10] = new TH1F("","Run 374810 pos RPD fC Distribution 90 - 100% Centrality Block 0",100,0,400000);
        pRPD_fCDist[1][10] = new TH1F("","Run 374810 pos RPD fC Distribution 90 - 100% Centrality Block 1",100,0,400000);
        pRPD_fCDist[2][10] = new TH1F("","Run 374810 pos RPD fC Distribution 90 - 100% Centrality Block 2",100,0,400000);
        pRPD_fCDist[3][10] = new TH1F("","Run 374810 pos RPD fC Distribution 90 - 100% Centrality Block 3",100,0,400000);
        pRPD_fCDist[4][10] = new TH1F("","Run 374810 pos RPD fC Distribution 90 - 100% Centrality Block 4",100,0,400000);
        pRPD_fCDist[5][10] = new TH1F("","Run 374810 pos RPD fC Distribution 90 - 100% Centrality Block 5",100,0,400000);
        pRPD_fCDist[6][10] = new TH1F("","Run 374810 pos RPD fC Distribution 90 - 100% Centrality Block 6",100,0,400000);
        pRPD_fCDist[7][10] = new TH1F("","Run 374810 pos RPD fC Distribution 90 - 100% Centrality Block 7",100,0,400000);
        pRPD_fCDist[8][10] = new TH1F("","Run 374810 pos RPD fC Distribution 90 - 100% Centrality Block 8",100,0,400000);
        pRPD_fCDist[9][10] = new TH1F("","Run 374810 pos RPD fC Distribution 90 - 100% Centrality Block 9",100,0,400000);
        pRPD_fCDist[10][10] = new TH1F("","Run 374810 pos RPD fC Distribution 90 - 100% Centrality Block 10",100,0,400000);
        pRPD_fCDist[11][10] = new TH1F("","Run 374810 pos RPD fC Distribution 90 - 100% Centrality Block 11",100,0,400000);
        pRPD_fCDist[12][10] = new TH1F("","Run 374810 pos RPD fC Distribution 90 - 100% Centrality Block 12",100,0,400000);
        pRPD_fCDist[13][10] = new TH1F("","Run 374810 pos RPD fC Distribution 90 - 100% Centrality Block 13",100,0,400000);
        pRPD_fCDist[14][10] = new TH1F("","Run 374810 pos RPD fC Distribution 90 - 100% Centrality Block 14",100,0,400000);
        pRPD_fCDist[15][10] = new TH1F("","Run 374810 pos RPD fC Distribution 90 - 100% Centrality Block 15",100,0,400000);

    TH1F *pEM_fCDist[5][11] = {0};

        pEM_fCDist[0][0] = new TH1F("","Run 374810 pos EM 1 fC Distribution All Centrality",200,0,200000);
        pEM_fCDist[1][0] = new TH1F("","Run 374810 pos EM 2 fC Distribution All Centrality",200,0,200000);
        pEM_fCDist[2][0] = new TH1F("","Run 374810 pos EM 3 fC Distribution All Centrality",200,0,200000);
        pEM_fCDist[3][0] = new TH1F("","Run 374810 pos EM 4 fC Distribution All Centrality",200,0,200000);
        pEM_fCDist[4][0] = new TH1F("","Run 374810 pos EM 5 fC Distribution All Centrality",200,0,200000);

        pEM_fCDist[0][1] = new TH1F("","Run 374810 pos EM 1 fC Distribution 0 - 9.5% Centrality",200,0,200000);
        pEM_fCDist[1][1] = new TH1F("","Run 374810 pos EM 2 fC Distribution 0 - 9.5% Centrality",200,0,200000);
        pEM_fCDist[2][1] = new TH1F("","Run 374810 pos EM 3 fC Distribution 0 - 9.5% Centrality",200,0,200000);
        pEM_fCDist[3][1] = new TH1F("","Run 374810 pos EM 4 fC Distribution 0 - 9.5% Centrality",200,0,200000);
        pEM_fCDist[4][1] = new TH1F("","Run 374810 pos EM 5 fC Distribution 0 - 9.5% Centrality",200,0,200000);

        pEM_fCDist[0][2] = new TH1F("","Run 374810 pos EM 1 fC Distribution 10 - 19.5% Centrality",200,0,200000);
        pEM_fCDist[1][2] = new TH1F("","Run 374810 pos EM 2 fC Distribution 10 - 19.5% Centrality",200,0,200000);
        pEM_fCDist[2][2] = new TH1F("","Run 374810 pos EM 3 fC Distribution 10 - 19.5% Centrality",200,0,200000);
        pEM_fCDist[3][2] = new TH1F("","Run 374810 pos EM 4 fC Distribution 10 - 19.5% Centrality",200,0,200000);
        pEM_fCDist[4][2] = new TH1F("","Run 374810 pos EM 5 fC Distribution 10 - 19.5% Centrality",200,0,200000);

        pEM_fCDist[0][3] = new TH1F("","Run 374810 pos EM 1 fC Distribution 20 - 29.5% Centrality",200,0,200000);
        pEM_fCDist[1][3] = new TH1F("","Run 374810 pos EM 2 fC Distribution 20 - 29.5% Centrality",200,0,200000);
        pEM_fCDist[2][3] = new TH1F("","Run 374810 pos EM 3 fC Distribution 20 - 29.5% Centrality",200,0,200000);
        pEM_fCDist[3][3] = new TH1F("","Run 374810 pos EM 4 fC Distribution 20 - 29.5% Centrality",200,0,200000);
        pEM_fCDist[4][3] = new TH1F("","Run 374810 pos EM 5 fC Distribution 20 - 29.5% Centrality",200,0,200000);

        pEM_fCDist[0][4] = new TH1F("","Run 374810 pos EM 1 fC Distribution 30 - 39.5% Centrality",200,0,200000);
        pEM_fCDist[1][4] = new TH1F("","Run 374810 pos EM 2 fC Distribution 30 - 39.5% Centrality",200,0,200000);
        pEM_fCDist[2][4] = new TH1F("","Run 374810 pos EM 3 fC Distribution 30 - 39.5% Centrality",200,0,200000);
        pEM_fCDist[3][4] = new TH1F("","Run 374810 pos EM 4 fC Distribution 30 - 39.5% Centrality",200,0,200000);
        pEM_fCDist[4][4] = new TH1F("","Run 374810 pos EM 5 fC Distribution 30 - 39.5% Centrality",200,0,200000);

        pEM_fCDist[0][5] = new TH1F("","Run 374810 pos EM 1 fC Distribution 40 - 49.5% Centrality",200,0,200000);
        pEM_fCDist[1][5] = new TH1F("","Run 374810 pos EM 2 fC Distribution 40 - 49.5% Centrality",200,0,200000);
        pEM_fCDist[2][5] = new TH1F("","Run 374810 pos EM 3 fC Distribution 40 - 49.5% Centrality",200,0,200000);
        pEM_fCDist[3][5] = new TH1F("","Run 374810 pos EM 4 fC Distribution 40 - 49.5% Centrality",200,0,200000);
        pEM_fCDist[4][5] = new TH1F("","Run 374810 pos EM 5 fC Distribution 40 - 49.5% Centrality",200,0,200000);

        pEM_fCDist[0][6] = new TH1F("","Run 374810 pos EM 1 fC Distribution 50 - 59.5% Centrality",200,0,200000);
        pEM_fCDist[1][6] = new TH1F("","Run 374810 pos EM 2 fC Distribution 50 - 59.5% Centrality",200,0,200000);
        pEM_fCDist[2][6] = new TH1F("","Run 374810 pos EM 3 fC Distribution 50 - 59.5% Centrality",200,0,200000);
        pEM_fCDist[3][6] = new TH1F("","Run 374810 pos EM 4 fC Distribution 50 - 59.5% Centrality",200,0,200000);
        pEM_fCDist[4][6] = new TH1F("","Run 374810 pos EM 5 fC Distribution 50 - 59.5% Centrality",200,0,200000);

        pEM_fCDist[0][7] = new TH1F("","Run 374810 pos EM 1 fC Distribution 60 - 69.5% Centrality",200,0,200000);
        pEM_fCDist[1][7] = new TH1F("","Run 374810 pos EM 2 fC Distribution 60 - 69.5% Centrality",200,0,200000);
        pEM_fCDist[2][7] = new TH1F("","Run 374810 pos EM 3 fC Distribution 60 - 69.5% Centrality",200,0,200000);
        pEM_fCDist[3][7] = new TH1F("","Run 374810 pos EM 4 fC Distribution 60 - 69.5% Centrality",200,0,200000);
        pEM_fCDist[4][7] = new TH1F("","Run 374810 pos EM 5 fC Distribution 60 - 69.5% Centrality",200,0,200000);

        pEM_fCDist[0][8] = new TH1F("","Run 374810 pos EM 1 fC Distribution 70 - 79.5% Centrality",200,0,200000);
        pEM_fCDist[1][8] = new TH1F("","Run 374810 pos EM 2 fC Distribution 70 - 79.5% Centrality",200,0,200000);
        pEM_fCDist[2][8] = new TH1F("","Run 374810 pos EM 3 fC Distribution 70 - 79.5% Centrality",200,0,200000);
        pEM_fCDist[3][8] = new TH1F("","Run 374810 pos EM 4 fC Distribution 70 - 79.5% Centrality",200,0,200000);
        pEM_fCDist[4][8] = new TH1F("","Run 374810 pos EM 5 fC Distribution 70 - 79.5% Centrality",200,0,200000);

        pEM_fCDist[0][9] = new TH1F("","Run 374810 pos EM 1 fC Distribution 80 - 89.5% Centrality",200,0,200000);
        pEM_fCDist[1][9] = new TH1F("","Run 374810 pos EM 2 fC Distribution 80 - 89.5% Centrality",200,0,200000);
        pEM_fCDist[2][9] = new TH1F("","Run 374810 pos EM 3 fC Distribution 80 - 89.5% Centrality",200,0,200000);
        pEM_fCDist[3][9] = new TH1F("","Run 374810 pos EM 4 fC Distribution 80 - 89.5% Centrality",200,0,200000);
        pEM_fCDist[4][9] = new TH1F("","Run 374810 pos EM 5 fC Distribution 80 - 89.5% Centrality",200,0,200000);

        pEM_fCDist[0][10] = new TH1F("","Run 374810 pos EM 1 fC Distribution 90 - 100% Centrality",200,0,200000);
        pEM_fCDist[1][10] = new TH1F("","Run 374810 pos EM 2 fC Distribution 90 - 100% Centrality",200,0,200000);
        pEM_fCDist[2][10] = new TH1F("","Run 374810 pos EM 3 fC Distribution 90 - 100% Centrality",200,0,200000);
        pEM_fCDist[3][10] = new TH1F("","Run 374810 pos EM 4 fC Distribution 90 - 100% Centrality",200,0,200000);
        pEM_fCDist[4][10] = new TH1F("","Run 374810 pos EM 5 fC Distribution 90 - 100% Centrality",200,0,200000);

    TH1F *pHAD_fCDist[4][11] = {0};

        pHAD_fCDist[0][0] = new TH1F("","Run 374810 pos HAD 1 fC Distribution All Centrality",150,0,150000);
        pHAD_fCDist[1][0] = new TH1F("","Run 374810 pos HAD 2 fC Distribution All Centrality",150,0,150000);
        pHAD_fCDist[2][0] = new TH1F("","Run 374810 pos HAD 3 fC Distribution All Centrality",150,0,150000);
        pHAD_fCDist[3][0] = new TH1F("","Run 374810 pos HAD 4 fC Distribution All Centrality",150,0,150000);

        pHAD_fCDist[0][1] = new TH1F("","Run 374810 pos HAD 1 fC Distribution 0 - 9.5% Centrality",150,0,150000);
        pHAD_fCDist[1][1] = new TH1F("","Run 374810 pos HAD 2 fC Distribution 0 - 9.5% Centrality",150,0,150000);
        pHAD_fCDist[2][1] = new TH1F("","Run 374810 pos HAD 3 fC Distribution 0 - 9.5% Centrality",150,0,150000);
        pHAD_fCDist[3][1] = new TH1F("","Run 374810 pos HAD 4 fC Distribution 0 - 9.5% Centrality",150,0,150000);

        pHAD_fCDist[0][2] = new TH1F("","Run 374810 pos HAD 1 fC Distribution 10 - 19.5% Centrality",150,0,150000);
        pHAD_fCDist[1][2] = new TH1F("","Run 374810 pos HAD 2 fC Distribution 10 - 19.5% Centrality",150,0,150000);
        pHAD_fCDist[2][2] = new TH1F("","Run 374810 pos HAD 3 fC Distribution 10 - 19.5% Centrality",150,0,150000);
        pHAD_fCDist[3][2] = new TH1F("","Run 374810 pos HAD 4 fC Distribution 10 - 19.5% Centrality",150,0,150000);

        pHAD_fCDist[0][3] = new TH1F("","Run 374810 pos HAD 1 fC Distribution 20 - 29.5% Centrality",150,0,150000);
        pHAD_fCDist[1][3] = new TH1F("","Run 374810 pos HAD 2 fC Distribution 20 - 29.5% Centrality",150,0,150000);
        pHAD_fCDist[2][3] = new TH1F("","Run 374810 pos HAD 3 fC Distribution 20 - 29.5% Centrality",150,0,150000);
        pHAD_fCDist[3][3] = new TH1F("","Run 374810 pos HAD 4 fC Distribution 20 - 29.5% Centrality",150,0,150000);

        pHAD_fCDist[0][4] = new TH1F("","Run 374810 pos HAD 1 fC Distribution 30 - 39.5% Centrality",150,0,150000);
        pHAD_fCDist[1][4] = new TH1F("","Run 374810 pos HAD 2 fC Distribution 30 - 39.5% Centrality",150,0,150000);
        pHAD_fCDist[2][4] = new TH1F("","Run 374810 pos HAD 3 fC Distribution 30 - 39.5% Centrality",150,0,150000);
        pHAD_fCDist[3][4] = new TH1F("","Run 374810 pos HAD 4 fC Distribution 30 - 39.5% Centrality",150,0,150000);

        pHAD_fCDist[0][5] = new TH1F("","Run 374810 pos HAD 1 fC Distribution 40 - 49.5% Centrality",150,0,150000);
        pHAD_fCDist[1][5] = new TH1F("","Run 374810 pos HAD 2 fC Distribution 40 - 49.5% Centrality",150,0,150000);
        pHAD_fCDist[2][5] = new TH1F("","Run 374810 pos HAD 3 fC Distribution 40 - 49.5% Centrality",150,0,150000);
        pHAD_fCDist[3][5] = new TH1F("","Run 374810 pos HAD 4 fC Distribution 40 - 49.5% Centrality",150,0,150000);

        pHAD_fCDist[0][6] = new TH1F("","Run 374810 pos HAD 1 fC Distribution 50 - 59.5% Centrality",150,0,150000);
        pHAD_fCDist[1][6] = new TH1F("","Run 374810 pos HAD 2 fC Distribution 50 - 59.5% Centrality",150,0,150000);
        pHAD_fCDist[2][6] = new TH1F("","Run 374810 pos HAD 3 fC Distribution 50 - 59.5% Centrality",150,0,150000);
        pHAD_fCDist[3][6] = new TH1F("","Run 374810 pos HAD 4 fC Distribution 50 - 59.5% Centrality",150,0,150000);

        pHAD_fCDist[0][7] = new TH1F("","Run 374810 pos HAD 1 fC Distribution 60 - 69.5% Centrality",150,0,150000);
        pHAD_fCDist[1][7] = new TH1F("","Run 374810 pos HAD 2 fC Distribution 60 - 69.5% Centrality",150,0,150000);
        pHAD_fCDist[2][7] = new TH1F("","Run 374810 pos HAD 3 fC Distribution 60 - 69.5% Centrality",150,0,150000);
        pHAD_fCDist[3][7] = new TH1F("","Run 374810 pos HAD 4 fC Distribution 60 - 69.5% Centrality",150,0,150000);

        pHAD_fCDist[0][8] = new TH1F("","Run 374810 pos HAD 1 fC Distribution 70 - 79.5% Centrality",150,0,150000);
        pHAD_fCDist[1][8] = new TH1F("","Run 374810 pos HAD 2 fC Distribution 70 - 79.5% Centrality",150,0,150000);
        pHAD_fCDist[2][8] = new TH1F("","Run 374810 pos HAD 3 fC Distribution 70 - 79.5% Centrality",150,0,150000);
        pHAD_fCDist[3][8] = new TH1F("","Run 374810 pos HAD 4 fC Distribution 70 - 79.5% Centrality",150,0,150000);

        pHAD_fCDist[0][9] = new TH1F("","Run 374810 pos HAD 1 fC Distribution 80 - 89.5% Centrality",150,0,150000);
        pHAD_fCDist[1][9] = new TH1F("","Run 374810 pos HAD 2 fC Distribution 80 - 89.5% Centrality",150,0,150000);
        pHAD_fCDist[2][9] = new TH1F("","Run 374810 pos HAD 3 fC Distribution 80 - 89.5% Centrality",150,0,150000);
        pHAD_fCDist[3][9] = new TH1F("","Run 374810 pos HAD 4 fC Distribution 80 - 89.5% Centrality",150,0,150000);

        pHAD_fCDist[0][10] = new TH1F("","Run 374810 pos HAD 1 fC Distribution 90 - 100% Centrality",150,0,150000);
        pHAD_fCDist[1][10] = new TH1F("","Run 374810 pos HAD 2 fC Distribution 90 - 100% Centrality",150,0,150000);
        pHAD_fCDist[2][10] = new TH1F("","Run 374810 pos HAD 3 fC Distribution 90 - 100% Centrality",150,0,150000);
        pHAD_fCDist[3][10] = new TH1F("","Run 374810 pos HAD 4 fC Distribution 90 - 100% Centrality",150,0,150000);

    TH1F *ZDCEnergyDist[11] = {0};

        ZDCEnergyDist[0] = new TH1F("","Run 374810 pos ZDC Energy Distribution All Centrality",200,-10000,20000);
        ZDCEnergyDist[1] = new TH1F("","Run 374810 pos ZDC Energy Distribution 0 - 9.5% Centrality",200,-10000,20000);
        ZDCEnergyDist[2] = new TH1F("","Run 374810 pos ZDC Energy Distribution 10 - 19.5% Centrality",200,-10000,20000);
        ZDCEnergyDist[3] = new TH1F("","Run 374810 pos ZDC Energy Distribution 20 - 29.5% Centrality",200,-10000,20000);
        ZDCEnergyDist[4] = new TH1F("","Run 374810 pos ZDC Energy Distribution 30 - 39.5% Centrality",200,-10000,20000);
        ZDCEnergyDist[5] = new TH1F("","Run 374810 pos ZDC Energy Distribution 40 - 49.5% Centrality",200,-10000,20000);
        ZDCEnergyDist[6] = new TH1F("","Run 374810 pos ZDC Energy Distribution 50 - 59.5% Centrality",200,-10000,20000);
        ZDCEnergyDist[7] = new TH1F("","Run 374810 pos ZDC Energy Distribution 60 - 69.5% Centrality",200,-10000,20000);
        ZDCEnergyDist[8] = new TH1F("","Run 374810 pos ZDC Energy Distribution 70 - 79.5% Centrality",200,-10000,20000);
        ZDCEnergyDist[9] = new TH1F("","Run 374810 pos ZDC Energy Distribution 80 - 89.5% Centrality",200,-10000,20000);
        ZDCEnergyDist[10] = new TH1F("","Run 374810 pos ZDC Energy Distribution 90 - 100% Centrality",200,-10000,20000);
    
    TProfile *AvgSigRPD[16] = {0};

        AvgSigRPD[0] = new TProfile("","Run 374810 Avg Signal pos RPD 40 - 49.5% Centrality Block 0",6,0,6);
        AvgSigRPD[1] = new TProfile("","Run 374810 Avg Signal pos RPD 40 - 49.5% Centrality Block 1",6,0,6);
        AvgSigRPD[2] = new TProfile("","Run 374810 Avg Signal pos RPD 40 - 49.5% Centrality Block 2",6,0,6);
        AvgSigRPD[3] = new TProfile("","Run 374810 Avg Signal pos RPD 40 - 49.5% Centrality Block 3",6,0,6);
        AvgSigRPD[4] = new TProfile("","Run 374810 Avg Signal pos RPD 40 - 49.5% Centrality Block 4",6,0,6);
        AvgSigRPD[5] = new TProfile("","Run 374810 Avg Signal pos RPD 40 - 49.5% Centrality Block 5",6,0,6);
        AvgSigRPD[6] = new TProfile("","Run 374810 Avg Signal pos RPD 40 - 49.5% Centrality Block 6",6,0,6);
        AvgSigRPD[7] = new TProfile("","Run 374810 Avg Signal pos RPD 40 - 49.5% Centrality Block 7",6,0,6);
        AvgSigRPD[8] = new TProfile("","Run 374810 Avg Signal pos RPD 40 - 49.5% Centrality Block 8",6,0,6);
        AvgSigRPD[9] = new TProfile("","Run 374810 Avg Signal pos RPD 40 - 49.5% Centrality Block 9",6,0,6);
        AvgSigRPD[10] = new TProfile("","Run 374810 Avg Signal pos RPD 40 - 49.5% Centrality Block 10",6,0,6);
        AvgSigRPD[11] = new TProfile("","Run 374810 Avg Signal pos RPD 40 - 49.5% Centrality Block 11",6,0,6);
        AvgSigRPD[12] = new TProfile("","Run 374810 Avg Signal pos RPD 40 - 49.5% Centrality Block 12",6,0,6);
        AvgSigRPD[13] = new TProfile("","Run 374810 Avg Signal pos RPD 40 - 49.5% Centrality Block 13",6,0,6);
        AvgSigRPD[14] = new TProfile("","Run 374810 Avg Signal pos RPD 40 - 49.5% Centrality Block 14",6,0,6);
        AvgSigRPD[15] = new TProfile("","Run 374810 Avg Signal pos RPD 40 - 49.5% Centrality Block 15",6,0,6);
    
    Int_t NumberEvents = zdcchain->GetEntries();
    cout << "Total Number of Events in Run 374810 is " << NumberEvents << endl;
    //NumberEvents = 10000;
    for (int i = 0; i < NumberEvents; i++)
    {
        zdcchain->GetEntry(i);  
        hichain->GetEntry(i);
        if ( i % 100000 == 0)
        {
            cout << "Event " << i << " has been processed" << endl;
        }
        for (int n = 0; n < 56; n++)
        {
            if (hibin >= 0 && hibin <= 200)
            {
            if (zside[n] == 1 && section[n] == 4)
            {
                if (channel[n] == 1)
                {
                    pRPD_TSDist[10][0]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[10][0]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[10][0]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[10][0]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[10][0]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[10][0]->Fill(5.0,TS5[n]);

                    pRPD_ratio[10][0] = TS2[n] / TS3[n];
                    pRPD_RatioDist[10][0]->Fill(pRPD_ratio[10][0]);

                    if (pRPD_ratio[10][0] > 1.1893 && pRPD_ratio[10][0] < 1.8067)
                    {
                        pRPD_sig[10][0] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[10][0]->Fill(pRPD_sig[10][0]);
                }
                if (channel[n] == 2)                                                                                                
                {
                    pRPD_TSDist[6][0]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[6][0]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[6][0]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[6][0]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[6][0]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[6][0]->Fill(5.0,TS5[n]);

                    pRPD_ratio[6][0] = TS2[n] / TS3[n];
                    pRPD_RatioDist[6][0]->Fill(pRPD_ratio[6][0]);

                    if (pRPD_ratio[6][0] > 1.2832 && pRPD_ratio[6][0] < 1.8688)
                    {
                        pRPD_sig[6][0] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[6][0]->Fill(pRPD_sig[6][0]);
                }
                if (channel[n] == 3)
                {
                    pRPD_TSDist[2][0]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[2][0]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[2][0]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[2][0]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[2][0]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[2][0]->Fill(5.0,TS5[n]);

                    pRPD_ratio[2][0] = TS2[n] / TS3[n];
                    pRPD_RatioDist[2][0]->Fill(pRPD_ratio[2][0]);

                    if (pRPD_ratio[2][0] > 1.8 && pRPD_ratio[2][0] < 2.2)
                    {
                        pRPD_sig[2][0] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[2][0]->Fill(pRPD_sig[2][0]);
                }
                if (channel[n] == 4)
                {
                    pRPD_TSDist[14][0]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[14][0]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[14][0]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[14][0]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[14][0]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[14][0]->Fill(5.0,TS5[n]);

                    pRPD_ratio[14][0] = TS2[n] / TS3[n];
                    pRPD_RatioDist[14][0]->Fill(pRPD_ratio[14][0]);

                    if (pRPD_ratio[14][0] > 1.1645 && pRPD_ratio[14][0] < 1.8515)
                    {
                        pRPD_sig[14][0] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[14][0]->Fill(pRPD_sig[14][0]);
                }
                if (channel[n] == 5)
                {
                    pRPD_TSDist[11][0]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[11][0]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[11][0]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[11][0]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[11][0]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[11][0]->Fill(5.0,TS5[n]);

                    pRPD_ratio[11][0] = TS2[n] / TS3[n];
                    pRPD_RatioDist[11][0]->Fill(pRPD_ratio[11][0]);

                    if (pRPD_ratio[11][0] > 1.2069 && pRPD_ratio[11][0] < 1.8411)
                    {
                        pRPD_sig[11][0] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[11][0]->Fill(pRPD_sig[11][0]);
                }
                if (channel[n] == 6)
                {
                    pRPD_TSDist[7][0]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[7][0]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[7][0]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[7][0]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[7][0]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[7][0]->Fill(5.0,TS5[n]);

                    pRPD_ratio[7][0] = TS2[n] / TS3[n];
                    pRPD_RatioDist[7][0]->Fill(pRPD_ratio[7][0]);

                    if (pRPD_ratio[7][0] > 1.4011 && pRPD_ratio[7][0] < 2.0589)
                    {
                        pRPD_sig[7][0] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[7][0]->Fill(pRPD_sig[7][0]);
                }
                if (channel[n] == 7)
                {
                    pRPD_TSDist[3][0]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[3][0]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[3][0]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[3][0]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[3][0]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[3][0]->Fill(5.0,TS5[n]);

                    pRPD_ratio[3][0] = TS2[n] / TS3[n];
                    pRPD_RatioDist[3][0]->Fill(pRPD_ratio[3][0]);

                    if (pRPD_ratio[3][0] > 1.4039 && pRPD_ratio[3][0] < 2.0881)
                    {
                        pRPD_sig[3][0] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[3][0]->Fill(pRPD_sig[3][0]);
                }
                if (channel[n] == 8)
                {
                    pRPD_TSDist[15][0]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[15][0]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[15][0]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[15][0]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[15][0]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[15][0]->Fill(5.0,TS5[n]);

                    pRPD_ratio[15][0] = TS2[n] / TS3[n];
                    pRPD_RatioDist[15][0]->Fill(pRPD_ratio[15][0]);

                    if (pRPD_ratio[15][0] > 1.1942 && pRPD_ratio[15][0] < 1.9038)
                    {
                        pRPD_sig[15][0] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[15][0]->Fill(pRPD_sig[15][0]);
                }
                if (channel[n] == 9)
                {
                    pRPD_TSDist[4][0]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[4][0]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[4][0]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[4][0]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[4][0]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[4][0]->Fill(5.0,TS5[n]);

                    pRPD_ratio[4][0] = TS2[n] / TS3[n];
                    pRPD_RatioDist[4][0]->Fill(pRPD_ratio[4][0]);

                    if (pRPD_ratio[4][0] > 1.252 && pRPD_ratio[4][0] < 2.268)
                    {
                        pRPD_sig[4][0] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[4][0]->Fill(pRPD_sig[4][0]);
                }
                if (channel[n] == 10)
                {
                    pRPD_TSDist[8][0]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[8][0]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[8][0]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[8][0]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[8][0]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[8][0]->Fill(5.0,TS5[n]);

                    pRPD_ratio[8][0] = TS2[n] / TS3[n];
                    pRPD_RatioDist[8][0]->Fill(pRPD_ratio[8][0]);

                    if (pRPD_ratio[8][0] > 1.2955 && pRPD_ratio[8][0] < 2.1905)
                    {
                        pRPD_sig[8][0] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[8][0]->Fill(pRPD_sig[8][0]);
                }
                if (channel[n] == 11)
                {
                    pRPD_TSDist[12][0]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[12][0]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[12][0]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[12][0]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[12][0]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[12][0]->Fill(5.0,TS5[n]);

                    pRPD_ratio[12][0] = TS2[n] / TS3[n];
                    pRPD_RatioDist[12][0]->Fill(pRPD_ratio[12][0]);

                    if (pRPD_ratio[12][0] > 1.2688 && pRPD_ratio[12][0] < 2.1392)
                    {
                        pRPD_sig[12][0] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[12][0]->Fill(pRPD_sig[12][0]);
                }
                if (channel[n] == 12)
                {
                    pRPD_TSDist[0][0]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[0][0]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[0][0]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[0][0]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[0][0]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[0][0]->Fill(5.0,TS5[n]);

                    pRPD_ratio[0][0] = TS2[n] / TS3[n];
                    pRPD_RatioDist[0][0]->Fill(pRPD_ratio[0][0]);

                    if (pRPD_ratio[0][0] > 1.2082 && pRPD_ratio[0][0] < 2.2878)
                    {
                        pRPD_sig[0][0] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[0][0]->Fill(pRPD_sig[0][0]);
                }
                if (channel[n] == 13)
                {
                    pRPD_TSDist[5][0]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[5][0]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[5][0]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[5][0]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[5][0]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[5][0]->Fill(5.0,TS5[n]);

                    pRPD_ratio[5][0] = TS2[n] / TS3[n];
                    pRPD_RatioDist[5][0]->Fill(pRPD_ratio[5][0]);

                    if (pRPD_ratio[5][0] > 1.6077 && pRPD_ratio[5][0] < 2.5083)
                    {
                        pRPD_sig[5][0] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[5][0]->Fill(pRPD_sig[5][0]);
                }
                if (channel[n] == 14)
                {
                    pRPD_TSDist[9][0]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[9][0]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[9][0]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[9][0]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[9][0]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[9][0]->Fill(5.0,TS5[n]);

                    pRPD_ratio[9][0] = TS2[n] / TS3[n];
                    pRPD_RatioDist[9][0]->Fill(pRPD_ratio[9][0]);

                    if (pRPD_ratio[9][0] > 1.5316 && pRPD_ratio[9][0] < 2.4484)
                    {
                        pRPD_sig[9][0] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[9][0]->Fill(pRPD_sig[9][0]);
                }
                if (channel[n] == 15)
                {
                    pRPD_TSDist[13][0]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[13][0]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[13][0]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[13][0]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[13][0]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[13][0]->Fill(5.0,TS5[n]);

                    pRPD_ratio[13][0] = TS2[n] / TS3[n];
                    pRPD_RatioDist[13][0]->Fill(pRPD_ratio[13][0]);

                    if (pRPD_ratio[13][0] > 1.4921 && pRPD_ratio[13][0] < 2.2959)
                    {
                        pRPD_sig[13][0] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[13][0]->Fill(pRPD_sig[13][0]);
                }
                if (channel[n] == 16)
                {
                    pRPD_TSDist[1][0]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[1][0]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[1][0]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[1][0]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[1][0]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[1][0]->Fill(5.0,TS5[n]);

                    pRPD_ratio[1][0] = TS2[n] / TS3[n];
                    pRPD_RatioDist[1][0]->Fill(pRPD_ratio[1][0]);

                    if (pRPD_ratio[1][0] > 1.5232 && pRPD_ratio[1][0] < 2.5228)
                    {
                        pRPD_sig[1][0] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[1][0]->Fill(pRPD_sig[1][0]);
                }
            } // end pos RPD ALL CENT 
            if (zside[n] == 1 && section[n] == 1)
            {
                if (channel[n] == 1)
                {
                    pEM_TSDist[0][0]->Fill(0.0,TS0[n]);
                    pEM_TSDist[0][0]->Fill(1.0,TS1[n]);
                    pEM_TSDist[0][0]->Fill(2.0,TS2[n]);
                    pEM_TSDist[0][0]->Fill(3.0,TS3[n]);
                    pEM_TSDist[0][0]->Fill(4.0,TS4[n]);
                    pEM_TSDist[0][0]->Fill(5.0,TS5[n]);

                    pEM_ratio[0][0] = TS2[n] / TS3[n];
                    pEM_RatioDist[0][0]->Fill(pEM_ratio[0][0]);

                    pEM_sig[0][0] = TS2[n] - TS1[n];

                    pEM_fCDist[0][0]->Fill(pEM_sig[0][0]);
                }
                if (channel[n] == 2)
                {
                    pEM_TSDist[1][0]->Fill(0.0,TS0[n]);
                    pEM_TSDist[1][0]->Fill(1.0,TS1[n]);
                    pEM_TSDist[1][0]->Fill(2.0,TS2[n]);
                    pEM_TSDist[1][0]->Fill(3.0,TS3[n]);
                    pEM_TSDist[1][0]->Fill(4.0,TS4[n]);
                    pEM_TSDist[1][0]->Fill(5.0,TS5[n]);

                    pEM_ratio[1][0] = TS2[n] / TS3[n];
                    pEM_RatioDist[1][0]->Fill(pEM_ratio[1][0]);

                    pEM_sig[1][0] = TS2[n] - TS1[n];

                    pEM_fCDist[1][0]->Fill(pEM_sig[1][0]);
                }
                if (channel[n] == 3)
                {
                    pEM_TSDist[2][0]->Fill(0.0,TS0[n]);
                    pEM_TSDist[2][0]->Fill(1.0,TS1[n]);
                    pEM_TSDist[2][0]->Fill(2.0,TS2[n]);
                    pEM_TSDist[2][0]->Fill(3.0,TS3[n]);
                    pEM_TSDist[2][0]->Fill(4.0,TS4[n]);
                    pEM_TSDist[2][0]->Fill(5.0,TS5[n]);

                    pEM_ratio[2][0] = TS2[n] / TS3[n];
                    pEM_RatioDist[2][0]->Fill(pEM_ratio[2][0]);

                    pEM_sig[2][0] = TS2[n] - TS1[n];

                    pEM_fCDist[2][0]->Fill(pEM_sig[2][0]);
                }
                if (channel[n] == 4)
                {
                    pEM_TSDist[3][0]->Fill(0.0,TS0[n]);
                    pEM_TSDist[3][0]->Fill(1.0,TS1[n]);
                    pEM_TSDist[3][0]->Fill(2.0,TS2[n]);
                    pEM_TSDist[3][0]->Fill(3.0,TS3[n]);
                    pEM_TSDist[3][0]->Fill(4.0,TS4[n]);
                    pEM_TSDist[3][0]->Fill(5.0,TS5[n]);

                    pEM_ratio[3][0] = TS2[n] / TS3[n];
                    pEM_RatioDist[3][0]->Fill(pEM_ratio[3][0]);

                    pEM_sig[3][0] = TS2[n] - TS1[n];

                    pEM_fCDist[3][0]->Fill(pEM_sig[3][0]);
                }
                if (channel[n] == 5)
                {
                    pEM_TSDist[4][0]->Fill(0.0,TS0[n]);
                    pEM_TSDist[4][0]->Fill(1.0,TS1[n]);
                    pEM_TSDist[4][0]->Fill(2.0,TS2[n]);
                    pEM_TSDist[4][0]->Fill(3.0,TS3[n]);
                    pEM_TSDist[4][0]->Fill(4.0,TS4[n]);
                    pEM_TSDist[4][0]->Fill(5.0,TS5[n]);

                    pEM_ratio[4][0] = TS2[n] / TS3[n];
                    pEM_RatioDist[4][0]->Fill(pEM_ratio[4][0]);

                    pEM_sig[4][0] = TS2[n] - TS1[n];

                    pEM_fCDist[4][0]->Fill(pEM_sig[4][0]);
                }
                pEM_sigtot[0] = pEM_sig[0][0] + pEM_sig[1][0] + pEM_sig[2][0] + pEM_sig[3][0] + pEM_sig[4][0];
            } // end pos em all cent
            
            if (zside[n] == 1 && section[n] == 2)
            {
                if (channel[n] == 1)
                {
                    pHAD_TSDist[0][0]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[0][0]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[0][0]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[0][0]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[0][0]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[0][0]->Fill(5.0,TS5[n]);

                    pHAD_ratio[0][0] = TS2[n] / TS3[n];
                    pHAD_RatioDist[0][0]->Fill(pHAD_ratio[0][0]);

                    pHAD_sig[0][0] = TS2[n] - TS1[n];

                    pHAD_fCDist[0][0]->Fill(pHAD_sig[0][0]);
                }
                if (channel[n] == 2)
                {
                    pHAD_TSDist[1][0]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[1][0]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[1][0]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[1][0]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[1][0]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[1][0]->Fill(5.0,TS5[n]);

                    pHAD_ratio[1][0] = TS2[n] / TS3[n];
                    pHAD_RatioDist[1][0]->Fill(pHAD_ratio[1][0]);

                    pHAD_sig[1][0] = TS2[n] - TS1[n];

                    pHAD_fCDist[1][0]->Fill(pHAD_sig[1][0]);
                }
                if (channel[n] == 3)
                {
                    pHAD_TSDist[2][0]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[2][0]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[2][0]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[2][0]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[2][0]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[2][0]->Fill(5.0,TS5[n]);

                    pHAD_ratio[2][0] = TS2[n] / TS3[n];
                    pHAD_RatioDist[2][0]->Fill(pHAD_ratio[2][0]);

                    pHAD_sig[2][0] = TS2[n] - TS1[n];

                    pHAD_fCDist[2][0]->Fill(pHAD_sig[2][0]);
                }
                if (channel[n] == 4)
                {
                    pHAD_TSDist[3][0]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[3][0]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[3][0]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[3][0]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[3][0]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[3][0]->Fill(5.0,TS5[n]);

                    pHAD_ratio[3][0] = TS2[n] / TS3[n];
                    pHAD_RatioDist[3][0]->Fill(pHAD_ratio[3][0]);

                    pHAD_sig[3][0] = TS2[n] - TS1[n];

                    pHAD_fCDist[3][0]->Fill(pHAD_sig[3][0]);
                }
                pHAD_sigtot[0] = pHAD_sig[0][0] + pHAD_sig[1][0] + pHAD_sig[1][0] + pHAD_sig[1][0];
            } // end of pos had all cent
            ZDC[0] = 0.1 * pEM_sigtot[0] + pHAD_sigtot[0];
        } // end of all cent

        /* 0 - 10 % Centrality Analysis*/
        if (hibin >= 0 && hibin < 20)
            {
            if (zside[n] == 1 && section[n] == 4)
            {
                if (channel[n] == 1)
                {
                    pRPD_TSDist[10][1]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[10][1]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[10][1]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[10][1]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[10][1]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[10][1]->Fill(5.0,TS5[n]);

                    pRPD_ratio[10][1] = TS2[n] / TS3[n];
                    pRPD_RatioDist[10][1]->Fill(pRPD_ratio[10][1]);

                    if (pRPD_ratio[10][1] > 1.1893 && pRPD_ratio[10][1] < 1.8067)
                    {
                        pRPD_sig[10][1] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[10][1]->Fill(pRPD_sig[10][1]);
                }
                if (channel[n] == 2)                                                                                                
                {
                    pRPD_TSDist[6][1]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[6][1]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[6][1]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[6][1]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[6][1]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[6][1]->Fill(5.0,TS5[n]);

                    pRPD_ratio[6][1] = TS2[n] / TS3[n];
                    pRPD_RatioDist[6][1]->Fill(pRPD_ratio[6][1]);

                    if (pRPD_ratio[6][1] > 1.2832 && pRPD_ratio[6][1] < 1.8688)
                    {
                        pRPD_sig[6][1] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[6][1]->Fill(pRPD_sig[6][1]);
                }
                if (channel[n] == 3)
                {
                    pRPD_TSDist[2][1]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[2][1]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[2][1]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[2][1]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[2][1]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[2][1]->Fill(5.0,TS5[n]);

                    pRPD_ratio[2][1] = TS2[n] / TS3[n];
                    pRPD_RatioDist[2][1]->Fill(pRPD_ratio[2][1]);

                    if (pRPD_ratio[2][1] > 1.8 && pRPD_ratio[2][1] < 2.2)
                    {
                        pRPD_sig[2][1] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[2][1]->Fill(pRPD_sig[2][1]);
                }
                if (channel[n] == 4)
                {
                    pRPD_TSDist[14][1]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[14][1]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[14][1]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[14][1]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[14][1]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[14][1]->Fill(5.0,TS5[n]);

                    pRPD_ratio[14][1] = TS2[n] / TS3[n];
                    pRPD_RatioDist[14][1]->Fill(pRPD_ratio[14][1]);

                    if (pRPD_ratio[14][1] > 1.1645 && pRPD_ratio[14][1] < 1.8515)
                    {
                        pRPD_sig[14][1] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[14][1]->Fill(pRPD_sig[14][1]);
                }
                if (channel[n] == 5)
                {
                    pRPD_TSDist[11][1]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[11][1]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[11][1]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[11][1]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[11][1]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[11][1]->Fill(5.0,TS5[n]);

                    pRPD_ratio[11][1] = TS2[n] / TS3[n];
                    pRPD_RatioDist[11][1]->Fill(pRPD_ratio[11][1]);

                    if (pRPD_ratio[11][1] > 1.2069 && pRPD_ratio[11][1] < 1.8411)
                    {
                        pRPD_sig[11][1] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[11][1]->Fill(pRPD_sig[11][1]);
                }
                if (channel[n] == 6)
                {
                    pRPD_TSDist[7][1]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[7][1]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[7][1]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[7][1]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[7][1]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[7][1]->Fill(5.0,TS5[n]);

                    pRPD_ratio[7][1] = TS2[n] / TS3[n];
                    pRPD_RatioDist[7][1]->Fill(pRPD_ratio[7][1]);

                    if (pRPD_ratio[7][1] > 1.4011 && pRPD_ratio[7][1] < 2.0589)
                    {
                        pRPD_sig[7][1] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[7][1]->Fill(pRPD_sig[7][1]);
                }
                if (channel[n] == 7)
                {
                    pRPD_TSDist[3][1]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[3][1]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[3][1]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[3][1]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[3][1]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[3][1]->Fill(5.0,TS5[n]);

                    pRPD_ratio[3][1] = TS2[n] / TS3[n];
                    pRPD_RatioDist[3][1]->Fill(pRPD_ratio[3][1]);

                    if (pRPD_ratio[3][1] > 1.4039 && pRPD_ratio[3][1] < 2.0881)
                    {
                        pRPD_sig[3][1] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[3][1]->Fill(pRPD_sig[3][1]);
                }
                if (channel[n] == 8)
                {
                    pRPD_TSDist[15][1]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[15][1]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[15][1]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[15][1]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[15][1]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[15][1]->Fill(5.0,TS5[n]);

                    pRPD_ratio[15][1] = TS2[n] / TS3[n];
                    pRPD_RatioDist[15][1]->Fill(pRPD_ratio[15][1]);

                    if (pRPD_ratio[15][1] > 1.1942 && pRPD_ratio[15][1] < 1.9038)
                    {
                        pRPD_sig[15][1] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[15][1]->Fill(pRPD_sig[15][1]);
                }
                if (channel[n] == 9)
                {
                    pRPD_TSDist[4][1]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[4][1]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[4][1]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[4][1]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[4][1]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[4][1]->Fill(5.0,TS5[n]);

                    pRPD_ratio[4][1] = TS2[n] / TS3[n];
                    pRPD_RatioDist[4][1]->Fill(pRPD_ratio[4][1]);

                    if (pRPD_ratio[4][1] > 1.252 && pRPD_ratio[4][1] < 2.268)
                    {
                        pRPD_sig[4][1] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[4][1]->Fill(pRPD_sig[4][1]);
                }
                if (channel[n] == 10)
                {
                    pRPD_TSDist[8][1]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[8][1]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[8][1]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[8][1]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[8][1]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[8][1]->Fill(5.0,TS5[n]);

                    pRPD_ratio[8][1] = TS2[n] / TS3[n];
                    pRPD_RatioDist[8][1]->Fill(pRPD_ratio[8][1]);

                    if (pRPD_ratio[8][1] > 1.2955 && pRPD_ratio[8][1] < 2.1905)
                    {
                        pRPD_sig[8][1] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[8][1]->Fill(pRPD_sig[8][1]);
                }
                if (channel[n] == 11)
                {
                    pRPD_TSDist[12][1]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[12][1]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[12][1]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[12][1]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[12][1]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[12][1]->Fill(5.0,TS5[n]);

                    pRPD_ratio[12][1] = TS2[n] / TS3[n];
                    pRPD_RatioDist[12][1]->Fill(pRPD_ratio[12][1]);

                    if (pRPD_ratio[12][1] > 1.2688 && pRPD_ratio[12][1] < 2.1392)
                    {
                        pRPD_sig[12][1] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[12][1]->Fill(pRPD_sig[12][1]);
                }
                if (channel[n] == 12)
                {
                    pRPD_TSDist[0][1]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[0][1]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[0][1]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[0][1]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[0][1]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[0][1]->Fill(5.0,TS5[n]);

                    pRPD_ratio[0][1] = TS2[n] / TS3[n];
                    pRPD_RatioDist[0][1]->Fill(pRPD_ratio[0][1]);

                    if (pRPD_ratio[0][1] > 1.2082 && pRPD_ratio[0][1] < 2.2878)
                    {
                        pRPD_sig[0][1] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[0][1]->Fill(pRPD_sig[0][1]);
                }
                if (channel[n] == 13)
                {
                    pRPD_TSDist[5][1]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[5][1]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[5][1]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[5][1]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[5][1]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[5][1]->Fill(5.0,TS5[n]);

                    pRPD_ratio[5][1] = TS2[n] / TS3[n];
                    pRPD_RatioDist[5][1]->Fill(pRPD_ratio[5][1]);

                    if (pRPD_ratio[5][1] > 1.6077 && pRPD_ratio[5][1] < 2.5083)
                    {
                        pRPD_sig[5][1] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[5][1]->Fill(pRPD_sig[5][1]);
                }
                if (channel[n] == 14)
                {
                    pRPD_TSDist[9][1]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[9][1]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[9][1]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[9][1]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[9][1]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[9][1]->Fill(5.0,TS5[n]);

                    pRPD_ratio[9][1] = TS2[n] / TS3[n];
                    pRPD_RatioDist[9][1]->Fill(pRPD_ratio[9][1]);

                    if (pRPD_ratio[9][1] > 1.5316 && pRPD_ratio[9][1] < 2.4484)
                    {
                        pRPD_sig[9][1] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[9][1]->Fill(pRPD_sig[9][1]);
                }
                if (channel[n] == 15)
                {
                    pRPD_TSDist[13][1]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[13][1]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[13][1]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[13][1]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[13][1]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[13][1]->Fill(5.0,TS5[n]);

                    pRPD_ratio[13][1] = TS2[n] / TS3[n];
                    pRPD_RatioDist[13][1]->Fill(pRPD_ratio[13][1]);

                    if (pRPD_ratio[13][1] > 1.4921 && pRPD_ratio[13][1] < 2.2959)
                    {
                        pRPD_sig[13][1] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[13][1]->Fill(pRPD_sig[13][1]);
                }
                if (channel[n] == 16)
                {
                    pRPD_TSDist[1][1]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[1][1]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[1][1]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[1][1]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[1][1]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[1][1]->Fill(5.0,TS5[n]);

                    pRPD_ratio[1][1] = TS2[n] / TS3[n];
                    pRPD_RatioDist[1][1]->Fill(pRPD_ratio[1][1]);

                    if (pRPD_ratio[1][1] > 1.5232 && pRPD_ratio[1][1] < 2.5228)
                    {
                        pRPD_sig[1][1] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[1][1]->Fill(pRPD_sig[1][1]);
                }
            } // end pos RPD 0 - 10 cent 
            if (zside[n] == 1 && section[n] == 1)
            {
                if (channel[n] == 1)
                {
                    pEM_TSDist[0][1]->Fill(0.0,TS0[n]);
                    pEM_TSDist[0][1]->Fill(1.0,TS1[n]);
                    pEM_TSDist[0][1]->Fill(2.0,TS2[n]);
                    pEM_TSDist[0][1]->Fill(3.0,TS3[n]);
                    pEM_TSDist[0][1]->Fill(4.0,TS4[n]);
                    pEM_TSDist[0][1]->Fill(5.0,TS5[n]);

                    pEM_ratio[0][1] = TS2[n] / TS3[n];
                    pEM_RatioDist[0][1]->Fill(pEM_ratio[0][1]);

                    pEM_sig[0][1] = TS2[n] - TS1[n];

                    pEM_fCDist[0][1]->Fill(pEM_sig[0][1]);
                }
                if (channel[n] == 2)
                {
                    pEM_TSDist[1][1]->Fill(0.0,TS0[n]);
                    pEM_TSDist[1][1]->Fill(1.0,TS1[n]);
                    pEM_TSDist[1][1]->Fill(2.0,TS2[n]);
                    pEM_TSDist[1][1]->Fill(3.0,TS3[n]);
                    pEM_TSDist[1][1]->Fill(4.0,TS4[n]);
                    pEM_TSDist[1][1]->Fill(5.0,TS5[n]);

                    pEM_ratio[1][1] = TS2[n] / TS3[n];
                    pEM_RatioDist[1][1]->Fill(pEM_ratio[1][1]);

                    pEM_sig[1][1] = TS2[n] - TS1[n];

                    pEM_fCDist[1][1]->Fill(pEM_sig[1][1]);
                }
                if (channel[n] == 3)
                {
                    pEM_TSDist[2][1]->Fill(0.0,TS0[n]);
                    pEM_TSDist[2][1]->Fill(1.0,TS1[n]);
                    pEM_TSDist[2][1]->Fill(2.0,TS2[n]);
                    pEM_TSDist[2][1]->Fill(3.0,TS3[n]);
                    pEM_TSDist[2][1]->Fill(4.0,TS4[n]);
                    pEM_TSDist[2][1]->Fill(5.0,TS5[n]);

                    pEM_ratio[2][1] = TS2[n] / TS3[n];
                    pEM_RatioDist[2][1]->Fill(pEM_ratio[2][1]);

                    pEM_sig[2][1] = TS2[n] - TS1[n];

                    pEM_fCDist[2][1]->Fill(pEM_sig[2][1]);
                }
                if (channel[n] == 4)
                {
                    pEM_TSDist[3][1]->Fill(0.0,TS0[n]);
                    pEM_TSDist[3][1]->Fill(1.0,TS1[n]);
                    pEM_TSDist[3][1]->Fill(2.0,TS2[n]);
                    pEM_TSDist[3][1]->Fill(3.0,TS3[n]);
                    pEM_TSDist[3][1]->Fill(4.0,TS4[n]);
                    pEM_TSDist[3][1]->Fill(5.0,TS5[n]);

                    pEM_ratio[3][1] = TS2[n] / TS3[n];
                    pEM_RatioDist[3][1]->Fill(pEM_ratio[3][1]);

                    pEM_sig[3][1] = TS2[n] - TS1[n];

                    pEM_fCDist[3][1]->Fill(pEM_sig[3][1]);
                }
                if (channel[n] == 5)
                {
                    pEM_TSDist[4][1]->Fill(0.0,TS0[n]);
                    pEM_TSDist[4][1]->Fill(1.0,TS1[n]);
                    pEM_TSDist[4][1]->Fill(2.0,TS2[n]);
                    pEM_TSDist[4][1]->Fill(3.0,TS3[n]);
                    pEM_TSDist[4][1]->Fill(4.0,TS4[n]);
                    pEM_TSDist[4][1]->Fill(5.0,TS5[n]);

                    pEM_ratio[4][1] = TS2[n] / TS3[n];
                    pEM_RatioDist[4][1]->Fill(pEM_ratio[4][1]);

                    pEM_sig[4][1] = TS2[n] - TS1[n];

                    pEM_fCDist[4][1]->Fill(pEM_sig[4][1]);
                }
                pEM_sigtot[1] = pEM_sig[0][1] + pEM_sig[1][1] + pEM_sig[2][1] + pEM_sig[3][1] + pEM_sig[4][1];
            } // end pos em 0 - 10 cent
            
            if (zside[n] == 1 && section[n] == 2)
            {
                if (channel[n] == 1)
                {
                    pHAD_TSDist[0][1]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[0][1]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[0][1]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[0][1]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[0][1]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[0][1]->Fill(5.0,TS5[n]);

                    pHAD_ratio[0][1] = TS2[n] / TS3[n];
                    pHAD_RatioDist[0][1]->Fill(pHAD_ratio[0][1]);

                    pHAD_sig[0][1] = TS2[n] - TS1[n];

                    pHAD_fCDist[0][1]->Fill(pHAD_sig[0][1]);
                }
                if (channel[n] == 2)
                {
                    pHAD_TSDist[1][1]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[1][1]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[1][1]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[1][1]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[1][1]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[1][1]->Fill(5.0,TS5[n]);

                    pHAD_ratio[1][1] = TS2[n] / TS3[n];
                    pHAD_RatioDist[1][1]->Fill(pHAD_ratio[1][1]);

                    pHAD_sig[1][1] = TS2[n] - TS1[n];

                    pHAD_fCDist[1][1]->Fill(pHAD_sig[1][1]);
                }
                if (channel[n] == 3)
                {
                    pHAD_TSDist[2][1]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[2][1]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[2][1]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[2][1]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[2][1]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[2][1]->Fill(5.0,TS5[n]);

                    pHAD_ratio[2][1] = TS2[n] / TS3[n];
                    pHAD_RatioDist[2][1]->Fill(pHAD_ratio[2][1]);

                    pHAD_sig[2][1] = TS2[n] - TS1[n];

                    pHAD_fCDist[2][1]->Fill(pHAD_sig[2][1]);
                }
                if (channel[n] == 4)
                {
                    pHAD_TSDist[3][1]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[3][1]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[3][1]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[3][1]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[3][1]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[3][1]->Fill(5.0,TS5[n]);

                    pHAD_ratio[3][1] = TS2[n] / TS3[n];
                    pHAD_RatioDist[3][1]->Fill(pHAD_ratio[3][1]);

                    pHAD_sig[3][1] = TS2[n] - TS1[n];

                    pHAD_fCDist[3][1]->Fill(pHAD_sig[3][1]);
                }
                pHAD_sigtot[1] = pHAD_sig[0][1] + pHAD_sig[1][1] + pHAD_sig[2][1] + pHAD_sig[3][1];
            } // end of pos had 0 - 10 cent
            ZDC[1] = 0.1 * pEM_sigtot[1] + pHAD_sigtot[1];
        } // end of 0 - 10 cent 

        /* 10 - 20 % Centrality Analysis*/
        if (hibin >= 20 && hibin < 40)
            {
            if (zside[n] == 1 && section[n] == 4)
            {
                if (channel[n] == 1)
                {
                    pRPD_TSDist[10][2]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[10][2]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[10][2]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[10][2]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[10][2]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[10][2]->Fill(5.0,TS5[n]);

                    pRPD_ratio[10][2] = TS2[n] / TS3[n];
                    pRPD_RatioDist[10][2]->Fill(pRPD_ratio[10][2]);

                    if (pRPD_ratio[10][2] > 1.1893 && pRPD_ratio[10][2] < 1.8067)
                    {
                        pRPD_sig[10][2] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[10][2]->Fill(pRPD_sig[10][2]);
                }
                if (channel[n] == 2)                                                                                                
                {
                    pRPD_TSDist[6][2]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[6][2]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[6][2]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[6][2]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[6][2]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[6][2]->Fill(5.0,TS5[n]);

                    pRPD_ratio[6][2] = TS2[n] / TS3[n];
                    pRPD_RatioDist[6][2]->Fill(pRPD_ratio[6][2]);

                    if (pRPD_ratio[6][2] > 1.2832 && pRPD_ratio[6][2] < 1.8688)
                    {
                        pRPD_sig[6][2] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[6][2]->Fill(pRPD_sig[6][2]);
                }
                if (channel[n] == 3)
                {
                    pRPD_TSDist[2][2]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[2][2]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[2][2]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[2][2]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[2][2]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[2][2]->Fill(5.0,TS5[n]);

                    pRPD_ratio[2][2] = TS2[n] / TS3[n];
                    pRPD_RatioDist[2][2]->Fill(pRPD_ratio[2][2]);

                    if (pRPD_ratio[2][2] > 1.8 && pRPD_ratio[2][2] < 2.2)
                    {
                        pRPD_sig[2][2] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[2][2]->Fill(pRPD_sig[2][2]);
                }
                if (channel[n] == 4)
                {
                    pRPD_TSDist[14][2]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[14][2]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[14][2]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[14][2]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[14][2]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[14][2]->Fill(5.0,TS5[n]);

                    pRPD_ratio[14][2] = TS2[n] / TS3[n];
                    pRPD_RatioDist[14][2]->Fill(pRPD_ratio[14][2]);

                    if (pRPD_ratio[14][2] > 1.1645 && pRPD_ratio[14][2] < 1.8515)
                    {
                        pRPD_sig[14][2] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[14][2]->Fill(pRPD_sig[14][2]);
                }
                if (channel[n] == 5)
                {
                    pRPD_TSDist[11][2]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[11][2]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[11][2]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[11][2]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[11][2]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[11][2]->Fill(5.0,TS5[n]);

                    pRPD_ratio[11][2] = TS2[n] / TS3[n];
                    pRPD_RatioDist[11][2]->Fill(pRPD_ratio[11][2]);

                    if (pRPD_ratio[11][2] > 1.2069 && pRPD_ratio[11][2] < 1.8411)
                    {
                        pRPD_sig[11][2] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[11][2]->Fill(pRPD_sig[11][2]);
                }
                if (channel[n] == 6)
                {
                    pRPD_TSDist[7][2]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[7][2]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[7][2]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[7][2]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[7][2]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[7][2]->Fill(5.0,TS5[n]);

                    pRPD_ratio[7][2] = TS2[n] / TS3[n];
                    pRPD_RatioDist[7][2]->Fill(pRPD_ratio[7][2]);

                    if (pRPD_ratio[7][2] > 1.4011 && pRPD_ratio[7][2] < 2.0589)
                    {
                        pRPD_sig[7][2] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[7][2]->Fill(pRPD_sig[7][2]);
                }
                if (channel[n] == 7)
                {
                    pRPD_TSDist[3][2]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[3][2]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[3][2]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[3][2]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[3][2]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[3][2]->Fill(5.0,TS5[n]);

                    pRPD_ratio[3][2] = TS2[n] / TS3[n];
                    pRPD_RatioDist[3][2]->Fill(pRPD_ratio[3][2]);

                    if (pRPD_ratio[3][2] > 1.4039 && pRPD_ratio[3][2] < 2.0881)
                    {
                        pRPD_sig[3][2] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[3][2]->Fill(pRPD_sig[3][2]);
                }
                if (channel[n] == 8)
                {
                    pRPD_TSDist[15][2]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[15][2]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[15][2]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[15][2]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[15][2]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[15][2]->Fill(5.0,TS5[n]);

                    pRPD_ratio[15][2] = TS2[n] / TS3[n];
                    pRPD_RatioDist[15][2]->Fill(pRPD_ratio[15][2]);

                    if (pRPD_ratio[15][2] > 1.1942 && pRPD_ratio[15][2] < 1.9038)
                    {
                        pRPD_sig[15][2] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[15][2]->Fill(pRPD_sig[15][2]);
                }
                if (channel[n] == 9)
                {
                    pRPD_TSDist[4][2]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[4][2]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[4][2]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[4][2]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[4][2]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[4][2]->Fill(5.0,TS5[n]);

                    pRPD_ratio[4][2] = TS2[n] / TS3[n];
                    pRPD_RatioDist[4][2]->Fill(pRPD_ratio[4][2]);

                    if (pRPD_ratio[4][2] > 1.252 && pRPD_ratio[4][2] < 2.268)
                    {
                        pRPD_sig[4][2] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[4][2]->Fill(pRPD_sig[4][2]);
                }
                if (channel[n] == 10)
                {
                    pRPD_TSDist[8][2]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[8][2]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[8][2]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[8][2]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[8][2]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[8][2]->Fill(5.0,TS5[n]);

                    pRPD_ratio[8][2] = TS2[n] / TS3[n];
                    pRPD_RatioDist[8][2]->Fill(pRPD_ratio[8][2]);

                    if (pRPD_ratio[8][2] > 1.2955 && pRPD_ratio[8][2] < 2.1905)
                    {
                        pRPD_sig[8][2] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[8][2]->Fill(pRPD_sig[8][2]);
                }
                if (channel[n] == 11)
                {
                    pRPD_TSDist[12][2]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[12][2]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[12][2]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[12][2]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[12][2]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[12][2]->Fill(5.0,TS5[n]);

                    pRPD_ratio[12][2] = TS2[n] / TS3[n];
                    pRPD_RatioDist[12][2]->Fill(pRPD_ratio[12][2]);

                    if (pRPD_ratio[12][2] > 1.2688 && pRPD_ratio[12][2] < 2.1392)
                    {
                        pRPD_sig[12][2] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[12][2]->Fill(pRPD_sig[12][2]);
                }
                if (channel[n] == 12)
                {
                    pRPD_TSDist[0][2]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[0][2]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[0][2]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[0][2]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[0][2]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[0][2]->Fill(5.0,TS5[n]);

                    pRPD_ratio[0][2] = TS2[n] / TS3[n];
                    pRPD_RatioDist[0][2]->Fill(pRPD_ratio[0][2]);

                    if (pRPD_ratio[0][2] > 1.2082 && pRPD_ratio[0][2] < 2.2878)
                    {
                        pRPD_sig[0][2] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[0][2]->Fill(pRPD_sig[0][2]);
                }
                if (channel[n] == 13)
                {
                    pRPD_TSDist[5][2]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[5][2]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[5][2]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[5][2]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[5][2]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[5][2]->Fill(5.0,TS5[n]);

                    pRPD_ratio[5][2] = TS2[n] / TS3[n];
                    pRPD_RatioDist[5][2]->Fill(pRPD_ratio[5][2]);

                    if (pRPD_ratio[5][2] > 1.6077 && pRPD_ratio[5][2] < 2.5083)
                    {
                        pRPD_sig[5][2] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[5][2]->Fill(pRPD_sig[5][2]);
                }
                if (channel[n] == 14)
                {
                    pRPD_TSDist[9][2]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[9][2]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[9][2]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[9][2]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[9][2]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[9][2]->Fill(5.0,TS5[n]);

                    pRPD_ratio[9][2] = TS2[n] / TS3[n];
                    pRPD_RatioDist[9][2]->Fill(pRPD_ratio[9][2]);

                    if (pRPD_ratio[9][2] > 1.5316 && pRPD_ratio[9][2] < 2.4484)
                    {
                        pRPD_sig[9][2] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[9][2]->Fill(pRPD_sig[9][2]);
                }
                if (channel[n] == 15)
                {
                    pRPD_TSDist[13][2]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[13][2]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[13][2]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[13][2]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[13][2]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[13][2]->Fill(5.0,TS5[n]);

                    pRPD_ratio[13][2] = TS2[n] / TS3[n];
                    pRPD_RatioDist[13][2]->Fill(pRPD_ratio[13][2]);

                    if (pRPD_ratio[13][2] > 1.4921 && pRPD_ratio[13][2] < 2.2959)
                    {
                        pRPD_sig[13][2] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[13][2]->Fill(pRPD_sig[13][2]);
                }
                if (channel[n] == 16)
                {
                    pRPD_TSDist[1][2]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[1][2]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[1][2]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[1][2]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[1][2]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[1][2]->Fill(5.0,TS5[n]);

                    pRPD_ratio[1][2] = TS2[n] / TS3[n];
                    pRPD_RatioDist[1][2]->Fill(pRPD_ratio[1][2]);

                    if (pRPD_ratio[1][2] > 1.5232 && pRPD_ratio[1][2] < 2.5228)
                    {
                        pRPD_sig[1][2] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[1][2]->Fill(pRPD_sig[1][2]);
                }
            } // end pos RPD 10 - 20 cent 
            if (zside[n] == 1 && section[n] == 1)
            {
                if (channel[n] == 1)
                {
                    pEM_TSDist[0][2]->Fill(0.0,TS0[n]);
                    pEM_TSDist[0][2]->Fill(1.0,TS1[n]);
                    pEM_TSDist[0][2]->Fill(2.0,TS2[n]);
                    pEM_TSDist[0][2]->Fill(3.0,TS3[n]);
                    pEM_TSDist[0][2]->Fill(4.0,TS4[n]);
                    pEM_TSDist[0][2]->Fill(5.0,TS5[n]);

                    pEM_ratio[0][2] = TS2[n] / TS3[n];
                    pEM_RatioDist[0][2]->Fill(pEM_ratio[0][2]);

                    pEM_sig[0][2] = TS2[n] - TS1[n];

                    pEM_fCDist[0][2]->Fill(pEM_sig[0][2]);
                }
                if (channel[n] == 2)
                {
                    pEM_TSDist[1][2]->Fill(0.0,TS0[n]);
                    pEM_TSDist[1][2]->Fill(1.0,TS1[n]);
                    pEM_TSDist[1][2]->Fill(2.0,TS2[n]);
                    pEM_TSDist[1][2]->Fill(3.0,TS3[n]);
                    pEM_TSDist[1][2]->Fill(4.0,TS4[n]);
                    pEM_TSDist[1][2]->Fill(5.0,TS5[n]);

                    pEM_ratio[1][2] = TS2[n] / TS3[n];
                    pEM_RatioDist[1][2]->Fill(pEM_ratio[1][2]);

                    pEM_sig[1][2] = TS2[n] - TS1[n];

                    pEM_fCDist[1][2]->Fill(pEM_sig[1][2]);
                }
                if (channel[n] == 3)
                {
                    pEM_TSDist[2][2]->Fill(0.0,TS0[n]);
                    pEM_TSDist[2][2]->Fill(1.0,TS1[n]);
                    pEM_TSDist[2][2]->Fill(2.0,TS2[n]);
                    pEM_TSDist[2][2]->Fill(3.0,TS3[n]);
                    pEM_TSDist[2][2]->Fill(4.0,TS4[n]);
                    pEM_TSDist[2][2]->Fill(5.0,TS5[n]);

                    pEM_ratio[2][2] = TS2[n] / TS3[n];
                    pEM_RatioDist[2][2]->Fill(pEM_ratio[2][2]);

                    pEM_sig[2][2] = TS2[n] - TS1[n];

                    pEM_fCDist[2][2]->Fill(pEM_sig[2][2]);
                }
                if (channel[n] == 4)
                {
                    pEM_TSDist[3][2]->Fill(0.0,TS0[n]);
                    pEM_TSDist[3][2]->Fill(1.0,TS1[n]);
                    pEM_TSDist[3][2]->Fill(2.0,TS2[n]);
                    pEM_TSDist[3][2]->Fill(3.0,TS3[n]);
                    pEM_TSDist[3][2]->Fill(4.0,TS4[n]);
                    pEM_TSDist[3][2]->Fill(5.0,TS5[n]);

                    pEM_ratio[3][2] = TS2[n] / TS3[n];
                    pEM_RatioDist[3][2]->Fill(pEM_ratio[3][2]);

                    pEM_sig[3][2] = TS2[n] - TS1[n];

                    pEM_fCDist[3][2]->Fill(pEM_sig[3][2]);
                }
                if (channel[n] == 5)
                {
                    pEM_TSDist[4][2]->Fill(0.0,TS0[n]);
                    pEM_TSDist[4][2]->Fill(1.0,TS1[n]);
                    pEM_TSDist[4][2]->Fill(2.0,TS2[n]);
                    pEM_TSDist[4][2]->Fill(3.0,TS3[n]);
                    pEM_TSDist[4][2]->Fill(4.0,TS4[n]);
                    pEM_TSDist[4][2]->Fill(5.0,TS5[n]);

                    pEM_ratio[4][2] = TS2[n] / TS3[n];
                    pEM_RatioDist[4][2]->Fill(pEM_ratio[4][2]);

                    pEM_sig[4][2] = TS2[n] - TS1[n];

                    pEM_fCDist[4][2]->Fill(pEM_sig[4][2]);
                }
                pEM_sigtot[2] = pEM_sig[0][2] + pEM_sig[1][2] + pEM_sig[2][2] + pEM_sig[3][2] + pEM_sig[4][2];
            } // end pos em 10 - 20 cent
            
            if (zside[n] == 1 && section[n] == 2)
            {
                if (channel[n] == 1)
                {
                    pHAD_TSDist[0][2]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[0][2]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[0][2]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[0][2]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[0][2]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[0][2]->Fill(5.0,TS5[n]);

                    pHAD_ratio[0][2] = TS2[n] / TS3[n];
                    pHAD_RatioDist[0][2]->Fill(pHAD_ratio[0][2]);

                    pHAD_sig[0][2] = TS2[n] - TS1[n];

                    pHAD_fCDist[0][2]->Fill(pHAD_sig[0][2]);
                }
                if (channel[n] == 2)
                {
                    pHAD_TSDist[1][2]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[1][2]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[1][2]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[1][2]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[1][2]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[1][2]->Fill(5.0,TS5[n]);

                    pHAD_ratio[1][2] = TS2[n] / TS3[n];
                    pHAD_RatioDist[1][2]->Fill(pHAD_ratio[1][2]);

                    pHAD_sig[1][2] = TS2[n] - TS1[n];

                    pHAD_fCDist[1][2]->Fill(pHAD_sig[1][2]);
                }
                if (channel[n] == 3)
                {
                    pHAD_TSDist[2][2]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[2][2]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[2][2]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[2][2]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[2][2]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[2][2]->Fill(5.0,TS5[n]);

                    pHAD_ratio[2][2] = TS2[n] / TS3[n];
                    pHAD_RatioDist[2][2]->Fill(pHAD_ratio[2][2]);

                    pHAD_sig[2][2] = TS2[n] - TS1[n];

                    pHAD_fCDist[2][2]->Fill(pHAD_sig[2][2]);
                }
                if (channel[n] == 4)
                {
                    pHAD_TSDist[3][2]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[3][2]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[3][2]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[3][2]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[3][2]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[3][2]->Fill(5.0,TS5[n]);

                    pHAD_ratio[3][2] = TS2[n] / TS3[n];
                    pHAD_RatioDist[3][2]->Fill(pHAD_ratio[3][2]);

                    pHAD_sig[3][2] = TS2[n] - TS1[n];

                    pHAD_fCDist[3][2]->Fill(pHAD_sig[3][2]);
                }
                pHAD_sigtot[2] = pHAD_sig[0][2] + pHAD_sig[1][2] + pHAD_sig[2][2] + pHAD_sig[3][2];
            } // end of pos had 10-20 cent
            ZDC[2] = 0.1 * pEM_sigtot[2] + pHAD_sigtot[2];
        } // end of 10 - 20 cent   

        /*pos ZDC 20 - 30 cent analysis*/
        if (hibin >= 40 && hibin < 60)
            {
            if (zside[n] == 1 && section[n] == 4)
            {
                if (channel[n] == 1)
                {
                    pRPD_TSDist[10][3]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[10][3]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[10][3]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[10][3]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[10][3]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[10][3]->Fill(5.0,TS5[n]);

                    pRPD_ratio[10][3] = TS2[n] / TS3[n];
                    pRPD_RatioDist[10][3]->Fill(pRPD_ratio[10][3]);

                    if (pRPD_ratio[10][3] > 1.1893 && pRPD_ratio[10][3] < 1.8067)
                    {
                        pRPD_sig[10][3] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[10][3]->Fill(pRPD_sig[10][3]);
                }
                if (channel[n] == 2)                                                                                                
                {
                    pRPD_TSDist[6][3]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[6][3]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[6][3]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[6][3]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[6][3]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[6][3]->Fill(5.0,TS5[n]);

                    pRPD_ratio[6][3] = TS2[n] / TS3[n];
                    pRPD_RatioDist[6][3]->Fill(pRPD_ratio[6][3]);

                    if (pRPD_ratio[6][3] > 1.2832 && pRPD_ratio[6][3] < 1.8688)
                    {
                        pRPD_sig[6][3] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[6][3]->Fill(pRPD_sig[6][3]);
                }
                if (channel[n] == 3)
                {
                    pRPD_TSDist[2][3]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[2][3]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[2][3]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[2][3]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[2][3]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[2][3]->Fill(5.0,TS5[n]);

                    pRPD_ratio[2][3] = TS2[n] / TS3[n];
                    pRPD_RatioDist[2][3]->Fill(pRPD_ratio[2][3]);

                    if (pRPD_ratio[2][3] > 1.8 && pRPD_ratio[2][3] < 2.2)
                    {
                        pRPD_sig[2][3] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[2][3]->Fill(pRPD_sig[2][3]);
                }
                if (channel[n] == 4)
                {
                    pRPD_TSDist[14][3]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[14][3]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[14][3]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[14][3]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[14][3]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[14][3]->Fill(5.0,TS5[n]);

                    pRPD_ratio[14][3] = TS2[n] / TS3[n];
                    pRPD_RatioDist[14][3]->Fill(pRPD_ratio[14][3]);

                    if (pRPD_ratio[14][3] > 1.1645 && pRPD_ratio[14][3] < 1.8515)
                    {
                        pRPD_sig[14][3] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[14][3]->Fill(pRPD_sig[14][3]);
                }
                if (channel[n] == 5)
                {
                    pRPD_TSDist[11][3]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[11][3]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[11][3]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[11][3]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[11][3]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[11][3]->Fill(5.0,TS5[n]);

                    pRPD_ratio[11][3] = TS2[n] / TS3[n];
                    pRPD_RatioDist[11][3]->Fill(pRPD_ratio[11][3]);

                    if (pRPD_ratio[11][3] > 1.2069 && pRPD_ratio[11][3] < 1.8411)
                    {
                        pRPD_sig[11][3] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[11][3]->Fill(pRPD_sig[11][3]);
                }
                if (channel[n] == 6)
                {
                    pRPD_TSDist[7][3]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[7][3]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[7][3]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[7][3]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[7][3]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[7][3]->Fill(5.0,TS5[n]);

                    pRPD_ratio[7][3] = TS2[n] / TS3[n];
                    pRPD_RatioDist[7][3]->Fill(pRPD_ratio[7][3]);

                    if (pRPD_ratio[7][3] > 1.4011 && pRPD_ratio[7][3] < 2.0589)
                    {
                        pRPD_sig[7][3] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[7][3]->Fill(pRPD_sig[7][3]);
                }
                if (channel[n] == 7)
                {
                    pRPD_TSDist[3][3]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[3][3]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[3][3]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[3][3]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[3][3]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[3][3]->Fill(5.0,TS5[n]);

                    pRPD_ratio[3][3] = TS2[n] / TS3[n];
                    pRPD_RatioDist[3][3]->Fill(pRPD_ratio[3][3]);

                    if (pRPD_ratio[3][3] > 1.4039 && pRPD_ratio[3][3] < 2.0881)
                    {
                        pRPD_sig[3][3] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[3][3]->Fill(pRPD_sig[3][3]);
                }
                if (channel[n] == 8)
                {
                    pRPD_TSDist[15][3]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[15][3]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[15][3]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[15][3]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[15][3]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[15][3]->Fill(5.0,TS5[n]);

                    pRPD_ratio[15][3] = TS2[n] / TS3[n];
                    pRPD_RatioDist[15][3]->Fill(pRPD_ratio[15][3]);

                    if (pRPD_ratio[15][3] > 1.1942 && pRPD_ratio[15][3] < 1.9038)
                    {
                        pRPD_sig[15][3] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[15][3]->Fill(pRPD_sig[15][3]);
                }
                if (channel[n] == 9)
                {
                    pRPD_TSDist[4][3]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[4][3]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[4][3]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[4][3]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[4][3]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[4][3]->Fill(5.0,TS5[n]);

                    pRPD_ratio[4][3] = TS2[n] / TS3[n];
                    pRPD_RatioDist[4][3]->Fill(pRPD_ratio[4][3]);

                    if (pRPD_ratio[4][3] > 1.252 && pRPD_ratio[4][3] < 2.268)
                    {
                        pRPD_sig[4][3] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[4][3]->Fill(pRPD_sig[4][3]);
                }
                if (channel[n] == 10)
                {
                    pRPD_TSDist[8][3]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[8][3]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[8][3]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[8][3]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[8][3]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[8][3]->Fill(5.0,TS5[n]);

                    pRPD_ratio[8][3] = TS2[n] / TS3[n];
                    pRPD_RatioDist[8][3]->Fill(pRPD_ratio[8][3]);

                    if (pRPD_ratio[8][3] > 1.2955 && pRPD_ratio[8][3] < 2.1905)
                    {
                        pRPD_sig[8][3] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[8][3]->Fill(pRPD_sig[8][3]);
                }
                if (channel[n] == 11)
                {
                    pRPD_TSDist[12][3]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[12][3]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[12][3]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[12][3]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[12][3]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[12][3]->Fill(5.0,TS5[n]);

                    pRPD_ratio[12][3] = TS2[n] / TS3[n];
                    pRPD_RatioDist[12][3]->Fill(pRPD_ratio[12][3]);

                    if (pRPD_ratio[12][3] > 1.2688 && pRPD_ratio[12][3] < 2.1392)
                    {
                        pRPD_sig[12][3] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[12][3]->Fill(pRPD_sig[12][3]);
                }
                if (channel[n] == 12)
                {
                    pRPD_TSDist[0][3]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[0][3]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[0][3]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[0][3]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[0][3]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[0][3]->Fill(5.0,TS5[n]);

                    pRPD_ratio[0][3] = TS2[n] / TS3[n];
                    pRPD_RatioDist[0][3]->Fill(pRPD_ratio[0][3]);

                    if (pRPD_ratio[0][3] > 1.2082 && pRPD_ratio[0][3] < 2.2878)
                    {
                        pRPD_sig[0][3] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[0][3]->Fill(pRPD_sig[0][3]);
                }
                if (channel[n] == 13)
                {
                    pRPD_TSDist[5][3]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[5][3]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[5][3]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[5][3]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[5][3]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[5][3]->Fill(5.0,TS5[n]);

                    pRPD_ratio[5][3] = TS2[n] / TS3[n];
                    pRPD_RatioDist[5][3]->Fill(pRPD_ratio[5][3]);

                    if (pRPD_ratio[5][3] > 1.6077 && pRPD_ratio[5][3] < 2.5083)
                    {
                        pRPD_sig[5][3] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[5][3]->Fill(pRPD_sig[5][3]);
                }
                if (channel[n] == 14)
                {
                    pRPD_TSDist[9][3]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[9][3]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[9][3]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[9][3]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[9][3]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[9][3]->Fill(5.0,TS5[n]);

                    pRPD_ratio[9][3] = TS2[n] / TS3[n];
                    pRPD_RatioDist[9][3]->Fill(pRPD_ratio[9][3]);

                    if (pRPD_ratio[9][3] > 1.5316 && pRPD_ratio[9][3] < 2.4484)
                    {
                        pRPD_sig[9][3] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[9][3]->Fill(pRPD_sig[9][3]);
                }
                if (channel[n] == 15)
                {
                    pRPD_TSDist[13][3]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[13][3]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[13][3]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[13][3]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[13][3]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[13][3]->Fill(5.0,TS5[n]);

                    pRPD_ratio[13][3] = TS2[n] / TS3[n];
                    pRPD_RatioDist[13][3]->Fill(pRPD_ratio[13][3]);

                    if (pRPD_ratio[13][3] > 1.4921 && pRPD_ratio[13][3] < 2.2959)
                    {
                        pRPD_sig[13][3] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[13][3]->Fill(pRPD_sig[13][3]);
                }
                if (channel[n] == 16)
                {
                    pRPD_TSDist[1][3]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[1][3]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[1][3]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[1][3]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[1][3]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[1][3]->Fill(5.0,TS5[n]);

                    pRPD_ratio[1][3] = TS2[n] / TS3[n];
                    pRPD_RatioDist[1][3]->Fill(pRPD_ratio[1][3]);

                    if (pRPD_ratio[1][3] > 1.5232 && pRPD_ratio[1][3] < 2.5228)
                    {
                        pRPD_sig[1][3] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[1][3]->Fill(pRPD_sig[1][3]);
                }
            } // end pos RPD 20 - 30 cent 
            if (zside[n] == 1 && section[n] == 1)
            {
                if (channel[n] == 1)
                {
                    pEM_TSDist[0][3]->Fill(0.0,TS0[n]);
                    pEM_TSDist[0][3]->Fill(1.0,TS1[n]);
                    pEM_TSDist[0][3]->Fill(2.0,TS2[n]);
                    pEM_TSDist[0][3]->Fill(3.0,TS3[n]);
                    pEM_TSDist[0][3]->Fill(4.0,TS4[n]);
                    pEM_TSDist[0][3]->Fill(5.0,TS5[n]);

                    pEM_ratio[0][3] = TS2[n] / TS3[n];
                    pEM_RatioDist[0][3]->Fill(pEM_ratio[0][3]);

                    pEM_sig[0][3] = TS2[n] - TS1[n];

                    pEM_fCDist[0][3]->Fill(pEM_sig[0][3]);
                }
                if (channel[n] == 2)
                {
                    pEM_TSDist[1][3]->Fill(0.0,TS0[n]);
                    pEM_TSDist[1][3]->Fill(1.0,TS1[n]);
                    pEM_TSDist[1][3]->Fill(2.0,TS2[n]);
                    pEM_TSDist[1][3]->Fill(3.0,TS3[n]);
                    pEM_TSDist[1][3]->Fill(4.0,TS4[n]);
                    pEM_TSDist[1][3]->Fill(5.0,TS5[n]);

                    pEM_ratio[1][3] = TS2[n] / TS3[n];
                    pEM_RatioDist[1][3]->Fill(pEM_ratio[1][3]);

                    pEM_sig[1][3] = TS2[n] - TS1[n];

                    pEM_fCDist[1][3]->Fill(pEM_sig[1][3]);
                }
                if (channel[n] == 3)
                {
                    pEM_TSDist[2][3]->Fill(0.0,TS0[n]);
                    pEM_TSDist[2][3]->Fill(1.0,TS1[n]);
                    pEM_TSDist[2][3]->Fill(2.0,TS2[n]);
                    pEM_TSDist[2][3]->Fill(3.0,TS3[n]);
                    pEM_TSDist[2][3]->Fill(4.0,TS4[n]);
                    pEM_TSDist[2][3]->Fill(5.0,TS5[n]);

                    pEM_ratio[2][3] = TS2[n] / TS3[n];
                    pEM_RatioDist[2][3]->Fill(pEM_ratio[2][3]);

                    pEM_sig[2][3] = TS2[n] - TS1[n];

                    pEM_fCDist[2][3]->Fill(pEM_sig[2][3]);
                }
                if (channel[n] == 4)
                {
                    pEM_TSDist[3][3]->Fill(0.0,TS0[n]);
                    pEM_TSDist[3][3]->Fill(1.0,TS1[n]);
                    pEM_TSDist[3][3]->Fill(2.0,TS2[n]);
                    pEM_TSDist[3][3]->Fill(3.0,TS3[n]);
                    pEM_TSDist[3][3]->Fill(4.0,TS4[n]);
                    pEM_TSDist[3][3]->Fill(5.0,TS5[n]);

                    pEM_ratio[3][3] = TS2[n] / TS3[n];
                    pEM_RatioDist[3][3]->Fill(pEM_ratio[3][3]);

                    pEM_sig[3][3] = TS2[n] - TS1[n];

                    pEM_fCDist[3][3]->Fill(pEM_sig[3][3]);
                }
                if (channel[n] == 5)
                {
                    pEM_TSDist[4][3]->Fill(0.0,TS0[n]);
                    pEM_TSDist[4][3]->Fill(1.0,TS1[n]);
                    pEM_TSDist[4][3]->Fill(2.0,TS2[n]);
                    pEM_TSDist[4][3]->Fill(3.0,TS3[n]);
                    pEM_TSDist[4][3]->Fill(4.0,TS4[n]);
                    pEM_TSDist[4][3]->Fill(5.0,TS5[n]);

                    pEM_ratio[4][3] = TS2[n] / TS3[n];
                    pEM_RatioDist[4][3]->Fill(pEM_ratio[4][3]);

                    pEM_sig[4][3] = TS2[n] - TS1[n];

                    pEM_fCDist[4][3]->Fill(pEM_sig[4][3]);
                }
                pEM_sigtot[3] = pEM_sig[0][3] + pEM_sig[1][3] + pEM_sig[2][3] + pEM_sig[3][3] + pEM_sig[4][3];
            } // end pos em 20 - 30 cent
            
            if (zside[n] == 1 && section[n] == 2)
            {
                if (channel[n] == 1)
                {
                    pHAD_TSDist[0][3]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[0][3]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[0][3]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[0][3]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[0][3]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[0][3]->Fill(5.0,TS5[n]);

                    pHAD_ratio[0][3] = TS2[n] / TS3[n];
                    pHAD_RatioDist[0][3]->Fill(pHAD_ratio[0][3]);

                    pHAD_sig[0][3] = TS2[n] - TS1[n];

                    pHAD_fCDist[0][3]->Fill(pHAD_sig[0][3]);
                }
                if (channel[n] == 2)
                {
                    pHAD_TSDist[1][3]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[1][3]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[1][3]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[1][3]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[1][3]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[1][3]->Fill(5.0,TS5[n]);

                    pHAD_ratio[1][3] = TS2[n] / TS3[n];
                    pHAD_RatioDist[1][3]->Fill(pHAD_ratio[1][3]);

                    pHAD_sig[1][3] = TS2[n] - TS1[n];

                    pHAD_fCDist[1][3]->Fill(pHAD_sig[1][3]);
                }
                if (channel[n] == 3)
                {
                    pHAD_TSDist[2][3]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[2][3]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[2][3]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[2][3]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[2][3]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[2][3]->Fill(5.0,TS5[n]);

                    pHAD_ratio[2][3] = TS2[n] / TS3[n];
                    pHAD_RatioDist[2][3]->Fill(pHAD_ratio[2][3]);

                    pHAD_sig[2][3] = TS2[n] - TS1[n];

                    pHAD_fCDist[2][3]->Fill(pHAD_sig[2][3]);
                }
                if (channel[n] == 4)
                {
                    pHAD_TSDist[3][3]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[3][3]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[3][3]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[3][3]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[3][3]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[3][3]->Fill(5.0,TS5[n]);

                    pHAD_ratio[3][3] = TS2[n] / TS3[n];
                    pHAD_RatioDist[3][3]->Fill(pHAD_ratio[3][3]);

                    pHAD_sig[3][3] = TS2[n] - TS1[n];

                    pHAD_fCDist[3][3]->Fill(pHAD_sig[3][3]);
                }
                pHAD_sigtot[3] = pHAD_sig[0][3] + pHAD_sig[1][3] + pHAD_sig[2][3] + pHAD_sig[3][3];
            } // end of pos had 20-30 cent
            ZDC[3] = 0.1 * pEM_sigtot[3] + pHAD_sigtot[3];
        } // end of 20 - 30 cent  

        /*pos ZDC 30 - 40 cent analysis*/
        if (hibin >= 60 && hibin < 80)
            {
            if (zside[n] == 1 && section[n] == 4)
            {
                if (channel[n] == 1)
                {
                    pRPD_TSDist[10][4]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[10][4]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[10][4]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[10][4]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[10][4]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[10][4]->Fill(5.0,TS5[n]);

                    pRPD_ratio[10][4] = TS2[n] / TS3[n];
                    pRPD_RatioDist[10][4]->Fill(pRPD_ratio[10][4]);

                    if (pRPD_ratio[10][4] > 1.1893 && pRPD_ratio[10][4] < 1.8067)
                    {
                        pRPD_sig[10][4] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[10][4]->Fill(pRPD_sig[10][4]);
                }
                if (channel[n] == 2)                                                                                                
                {
                    pRPD_TSDist[6][4]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[6][4]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[6][4]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[6][4]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[6][4]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[6][4]->Fill(5.0,TS5[n]);

                    pRPD_ratio[6][4] = TS2[n] / TS3[n];
                    pRPD_RatioDist[6][4]->Fill(pRPD_ratio[6][4]);

                    if (pRPD_ratio[6][4] > 1.2832 && pRPD_ratio[6][4] < 1.8688)
                    {
                        pRPD_sig[6][4] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[6][4]->Fill(pRPD_sig[6][4]);
                }
                if (channel[n] == 3)
                {
                    pRPD_TSDist[2][4]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[2][4]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[2][4]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[2][4]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[2][4]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[2][4]->Fill(5.0,TS5[n]);

                    pRPD_ratio[2][4] = TS2[n] / TS3[n];
                    pRPD_RatioDist[2][4]->Fill(pRPD_ratio[2][4]);

                    if (pRPD_ratio[2][4] > 1.8 && pRPD_ratio[2][4] < 2.2)
                    {
                        pRPD_sig[2][4] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[2][4]->Fill(pRPD_sig[2][4]);
                }
                if (channel[n] == 4)
                {
                    pRPD_TSDist[14][4]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[14][4]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[14][4]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[14][4]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[14][4]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[14][4]->Fill(5.0,TS5[n]);

                    pRPD_ratio[14][4] = TS2[n] / TS3[n];
                    pRPD_RatioDist[14][4]->Fill(pRPD_ratio[14][4]);

                    if (pRPD_ratio[14][4] > 1.1645 && pRPD_ratio[14][4] < 1.8515)
                    {
                        pRPD_sig[14][4] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[14][4]->Fill(pRPD_sig[14][4]);
                }
                if (channel[n] == 5)
                {
                    pRPD_TSDist[11][4]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[11][4]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[11][4]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[11][4]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[11][4]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[11][4]->Fill(5.0,TS5[n]);

                    pRPD_ratio[11][4] = TS2[n] / TS3[n];
                    pRPD_RatioDist[11][4]->Fill(pRPD_ratio[11][4]);

                    if (pRPD_ratio[11][4] > 1.2069 && pRPD_ratio[11][4] < 1.8411)
                    {
                        pRPD_sig[11][4] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[11][4]->Fill(pRPD_sig[11][4]);
                }
                if (channel[n] == 6)
                {
                    pRPD_TSDist[7][4]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[7][4]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[7][4]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[7][4]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[7][4]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[7][4]->Fill(5.0,TS5[n]);

                    pRPD_ratio[7][4] = TS2[n] / TS3[n];
                    pRPD_RatioDist[7][4]->Fill(pRPD_ratio[7][4]);

                    if (pRPD_ratio[7][4] > 1.4011 && pRPD_ratio[7][4] < 2.0589)
                    {
                        pRPD_sig[7][4] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[7][4]->Fill(pRPD_sig[7][4]);
                }
                if (channel[n] == 7)
                {
                    pRPD_TSDist[3][4]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[3][4]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[3][4]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[3][4]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[3][4]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[3][4]->Fill(5.0,TS5[n]);

                    pRPD_ratio[3][4] = TS2[n] / TS3[n];
                    pRPD_RatioDist[3][4]->Fill(pRPD_ratio[3][4]);

                    if (pRPD_ratio[3][4] > 1.4039 && pRPD_ratio[3][4] < 2.0881)
                    {
                        pRPD_sig[3][4] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[3][4]->Fill(pRPD_sig[3][4]);
                }
                if (channel[n] == 8)
                {
                    pRPD_TSDist[15][4]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[15][4]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[15][4]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[15][4]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[15][4]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[15][4]->Fill(5.0,TS5[n]);

                    pRPD_ratio[15][4] = TS2[n] / TS3[n];
                    pRPD_RatioDist[15][4]->Fill(pRPD_ratio[15][4]);

                    if (pRPD_ratio[15][4] > 1.1942 && pRPD_ratio[15][4] < 1.9038)
                    {
                        pRPD_sig[15][4] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[15][4]->Fill(pRPD_sig[15][4]);
                }
                if (channel[n] == 9)
                {
                    pRPD_TSDist[4][4]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[4][4]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[4][4]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[4][4]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[4][4]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[4][4]->Fill(5.0,TS5[n]);

                    pRPD_ratio[4][4] = TS2[n] / TS3[n];
                    pRPD_RatioDist[4][4]->Fill(pRPD_ratio[4][4]);

                    if (pRPD_ratio[4][4] > 1.252 && pRPD_ratio[4][4] < 2.268)
                    {
                        pRPD_sig[4][4] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[4][4]->Fill(pRPD_sig[4][4]);
                }
                if (channel[n] == 10)
                {
                    pRPD_TSDist[8][4]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[8][4]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[8][4]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[8][4]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[8][4]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[8][4]->Fill(5.0,TS5[n]);

                    pRPD_ratio[8][4] = TS2[n] / TS3[n];
                    pRPD_RatioDist[8][4]->Fill(pRPD_ratio[8][4]);

                    if (pRPD_ratio[8][4] > 1.2955 && pRPD_ratio[8][4] < 2.1905)
                    {
                        pRPD_sig[8][4] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[8][4]->Fill(pRPD_sig[8][4]);
                }
                if (channel[n] == 11)
                {
                    pRPD_TSDist[12][4]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[12][4]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[12][4]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[12][4]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[12][4]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[12][4]->Fill(5.0,TS5[n]);

                    pRPD_ratio[12][4] = TS2[n] / TS3[n];
                    pRPD_RatioDist[12][4]->Fill(pRPD_ratio[12][4]);

                    if (pRPD_ratio[12][4] > 1.2688 && pRPD_ratio[12][4] < 2.1392)
                    {
                        pRPD_sig[12][4] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[12][4]->Fill(pRPD_sig[12][4]);
                }
                if (channel[n] == 12)
                {
                    pRPD_TSDist[0][4]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[0][4]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[0][4]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[0][4]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[0][4]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[0][4]->Fill(5.0,TS5[n]);

                    pRPD_ratio[0][4] = TS2[n] / TS3[n];
                    pRPD_RatioDist[0][4]->Fill(pRPD_ratio[0][4]);

                    if (pRPD_ratio[0][4] > 1.2082 && pRPD_ratio[0][4] < 2.2878)
                    {
                        pRPD_sig[0][4] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[0][4]->Fill(pRPD_sig[0][4]);
                }
                if (channel[n] == 13)
                {
                    pRPD_TSDist[5][4]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[5][4]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[5][4]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[5][4]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[5][4]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[5][4]->Fill(5.0,TS5[n]);

                    pRPD_ratio[5][4] = TS2[n] / TS3[n];
                    pRPD_RatioDist[5][4]->Fill(pRPD_ratio[5][4]);

                    if (pRPD_ratio[5][4] > 1.6077 && pRPD_ratio[5][4] < 2.5083)
                    {
                        pRPD_sig[5][4] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[5][4]->Fill(pRPD_sig[5][4]);
                }
                if (channel[n] == 14)
                {
                    pRPD_TSDist[9][4]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[9][4]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[9][4]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[9][4]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[9][4]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[9][4]->Fill(5.0,TS5[n]);

                    pRPD_ratio[9][4] = TS2[n] / TS3[n];
                    pRPD_RatioDist[9][4]->Fill(pRPD_ratio[9][4]);

                    if (pRPD_ratio[9][4] > 1.5316 && pRPD_ratio[9][4] < 2.4484)
                    {
                        pRPD_sig[9][4] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[9][4]->Fill(pRPD_sig[9][4]);
                }
                if (channel[n] == 15)
                {
                    pRPD_TSDist[13][4]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[13][4]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[13][4]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[13][4]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[13][4]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[13][4]->Fill(5.0,TS5[n]);

                    pRPD_ratio[13][4] = TS2[n] / TS3[n];
                    pRPD_RatioDist[13][4]->Fill(pRPD_ratio[13][4]);

                    if (pRPD_ratio[13][4] > 1.4921 && pRPD_ratio[13][4] < 2.2959)
                    {
                        pRPD_sig[13][4] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[13][4]->Fill(pRPD_sig[13][4]);
                }
                if (channel[n] == 16)
                {
                    pRPD_TSDist[1][4]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[1][4]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[1][4]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[1][4]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[1][4]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[1][4]->Fill(5.0,TS5[n]);

                    pRPD_ratio[1][4] = TS2[n] / TS3[n];
                    pRPD_RatioDist[1][4]->Fill(pRPD_ratio[1][4]);

                    if (pRPD_ratio[1][4] > 1.5232 && pRPD_ratio[1][4] < 2.5228)
                    {
                        pRPD_sig[1][4] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[1][4]->Fill(pRPD_sig[1][4]);
                }
            } // end pos RPD 20 - 30 cent 
            if (zside[n] == 1 && section[n] == 1)
            {
                if (channel[n] == 1)
                {
                    pEM_TSDist[0][4]->Fill(0.0,TS0[n]);
                    pEM_TSDist[0][4]->Fill(1.0,TS1[n]);
                    pEM_TSDist[0][4]->Fill(2.0,TS2[n]);
                    pEM_TSDist[0][4]->Fill(3.0,TS3[n]);
                    pEM_TSDist[0][4]->Fill(4.0,TS4[n]);
                    pEM_TSDist[0][4]->Fill(5.0,TS5[n]);

                    pEM_ratio[0][4] = TS2[n] / TS3[n];
                    pEM_RatioDist[0][4]->Fill(pEM_ratio[0][4]);

                    pEM_sig[0][4] = TS2[n] - TS1[n];

                    pEM_fCDist[0][4]->Fill(pEM_sig[0][4]);
                }
                if (channel[n] == 2)
                {
                    pEM_TSDist[1][4]->Fill(0.0,TS0[n]);
                    pEM_TSDist[1][4]->Fill(1.0,TS1[n]);
                    pEM_TSDist[1][4]->Fill(2.0,TS2[n]);
                    pEM_TSDist[1][4]->Fill(3.0,TS3[n]);
                    pEM_TSDist[1][4]->Fill(4.0,TS4[n]);
                    pEM_TSDist[1][4]->Fill(5.0,TS5[n]);

                    pEM_ratio[1][4] = TS2[n] / TS3[n];
                    pEM_RatioDist[1][4]->Fill(pEM_ratio[1][4]);

                    pEM_sig[1][4] = TS2[n] - TS1[n];

                    pEM_fCDist[1][4]->Fill(pEM_sig[1][4]);
                }
                if (channel[n] == 3)
                {
                    pEM_TSDist[2][4]->Fill(0.0,TS0[n]);
                    pEM_TSDist[2][4]->Fill(1.0,TS1[n]);
                    pEM_TSDist[2][4]->Fill(2.0,TS2[n]);
                    pEM_TSDist[2][4]->Fill(3.0,TS3[n]);
                    pEM_TSDist[2][4]->Fill(4.0,TS4[n]);
                    pEM_TSDist[2][4]->Fill(5.0,TS5[n]);

                    pEM_ratio[2][4] = TS2[n] / TS3[n];
                    pEM_RatioDist[2][4]->Fill(pEM_ratio[2][4]);

                    pEM_sig[2][4] = TS2[n] - TS1[n];

                    pEM_fCDist[2][4]->Fill(pEM_sig[2][4]);
                }
                if (channel[n] == 4)
                {
                    pEM_TSDist[3][4]->Fill(0.0,TS0[n]);
                    pEM_TSDist[3][4]->Fill(1.0,TS1[n]);
                    pEM_TSDist[3][4]->Fill(2.0,TS2[n]);
                    pEM_TSDist[3][4]->Fill(3.0,TS3[n]);
                    pEM_TSDist[3][4]->Fill(4.0,TS4[n]);
                    pEM_TSDist[3][4]->Fill(5.0,TS5[n]);

                    pEM_ratio[3][4] = TS2[n] / TS3[n];
                    pEM_RatioDist[3][4]->Fill(pEM_ratio[3][4]);

                    pEM_sig[3][4] = TS2[n] - TS1[n];

                    pEM_fCDist[3][4]->Fill(pEM_sig[3][4]);
                }
                if (channel[n] == 5)
                {
                    pEM_TSDist[4][4]->Fill(0.0,TS0[n]);
                    pEM_TSDist[4][4]->Fill(1.0,TS1[n]);
                    pEM_TSDist[4][4]->Fill(2.0,TS2[n]);
                    pEM_TSDist[4][4]->Fill(3.0,TS3[n]);
                    pEM_TSDist[4][4]->Fill(4.0,TS4[n]);
                    pEM_TSDist[4][4]->Fill(5.0,TS5[n]);

                    pEM_ratio[4][4] = TS2[n] / TS3[n];
                    pEM_RatioDist[4][4]->Fill(pEM_ratio[4][4]);

                    pEM_sig[4][4] = TS2[n] - TS1[n];

                    pEM_fCDist[4][4]->Fill(pEM_sig[4][4]);
                }
                pEM_sigtot[4] = pEM_sig[0][4] + pEM_sig[1][4] + pEM_sig[2][4] + pEM_sig[3][4] + pEM_sig[4][4];
            } // end pos em 30 - 40 cent
            
            if (zside[n] == 1 && section[n] == 2)
            {
                if (channel[n] == 1)
                {
                    pHAD_TSDist[0][4]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[0][4]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[0][4]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[0][4]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[0][4]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[0][4]->Fill(5.0,TS5[n]);

                    pHAD_ratio[0][4] = TS2[n] / TS3[n];
                    pHAD_RatioDist[0][4]->Fill(pHAD_ratio[0][4]);

                    pHAD_sig[0][4] = TS2[n] - TS1[n];

                    pHAD_fCDist[0][4]->Fill(pHAD_sig[0][4]);
                }
                if (channel[n] == 2)
                {
                    pHAD_TSDist[1][4]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[1][4]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[1][4]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[1][4]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[1][4]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[1][4]->Fill(5.0,TS5[n]);

                    pHAD_ratio[1][4] = TS2[n] / TS3[n];
                    pHAD_RatioDist[1][4]->Fill(pHAD_ratio[1][4]);

                    pHAD_sig[1][4] = TS2[n] - TS1[n];

                    pHAD_fCDist[1][4]->Fill(pHAD_sig[1][4]);
                }
                if (channel[n] == 3)
                {
                    pHAD_TSDist[2][4]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[2][4]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[2][4]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[2][4]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[2][4]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[2][4]->Fill(5.0,TS5[n]);

                    pHAD_ratio[2][4] = TS2[n] / TS3[n];
                    pHAD_RatioDist[2][4]->Fill(pHAD_ratio[2][4]);

                    pHAD_sig[2][4] = TS2[n] - TS1[n];

                    pHAD_fCDist[2][4]->Fill(pHAD_sig[2][4]);
                }
                if (channel[n] == 4)
                {
                    pHAD_TSDist[3][4]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[3][4]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[3][4]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[3][4]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[3][4]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[3][4]->Fill(5.0,TS5[n]);

                    pHAD_ratio[3][4] = TS2[n] / TS3[n];
                    pHAD_RatioDist[3][4]->Fill(pHAD_ratio[3][4]);

                    pHAD_sig[3][4] = TS2[n] - TS1[n];

                    pHAD_fCDist[3][4]->Fill(pHAD_sig[3][4]);
                }
                pHAD_sigtot[4] = pHAD_sig[0][4] + pHAD_sig[1][4] + pHAD_sig[2][4] + pHAD_sig[3][4];
            } // end of pos had 30-40 cent
            ZDC[4] = 0.1 * pEM_sigtot[4] + pHAD_sigtot[4];
        } // end of 30 - 40 cent  

        /*pos ZDC 40 - 50 cent analysis*/
        if (hibin >= 80 && hibin < 100)
            {
            if (zside[n] == 1 && section[n] == 4)
            {
                if (channel[n] == 1)
                {
                    pRPD_TSDist[10][5]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[10][5]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[10][5]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[10][5]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[10][5]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[10][5]->Fill(5.0,TS5[n]);

                    AvgSigRPD[10]->Fill(0.0,TS0[n]);
                    AvgSigRPD[10]->Fill(1.0,TS1[n]);
                    AvgSigRPD[10]->Fill(2.0,TS2[n]);
                    AvgSigRPD[10]->Fill(3.0,TS3[n]);
                    AvgSigRPD[10]->Fill(4.0,TS4[n]);
                    AvgSigRPD[10]->Fill(5.0,TS5[n]);

                    pRPD_ratio[10][5] = TS2[n] / TS3[n];
                    pRPD_RatioDist[10][5]->Fill(pRPD_ratio[10][5]);

                    if (pRPD_ratio[10][5] > 1.1893 && pRPD_ratio[10][5] < 1.8067)
                    {
                        pRPD_sig[10][5] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[10][5]->Fill(pRPD_sig[10][5]);
                }
                if (channel[n] == 2)                                                                                                
                {
                    pRPD_TSDist[6][5]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[6][5]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[6][5]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[6][5]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[6][5]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[6][5]->Fill(5.0,TS5[n]);

                    AvgSigRPD[6]->Fill(0.0,TS0[n]);
                    AvgSigRPD[6]->Fill(1.0,TS1[n]);
                    AvgSigRPD[6]->Fill(2.0,TS2[n]);
                    AvgSigRPD[6]->Fill(3.0,TS3[n]);
                    AvgSigRPD[6]->Fill(4.0,TS4[n]);
                    AvgSigRPD[6]->Fill(5.0,TS5[n]);

                    pRPD_ratio[6][5] = TS2[n] / TS3[n];
                    pRPD_RatioDist[6][5]->Fill(pRPD_ratio[6][5]);

                    if (pRPD_ratio[6][5] > 1.2832 && pRPD_ratio[6][5] < 1.8688)
                    {
                        pRPD_sig[6][5] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[6][5]->Fill(pRPD_sig[6][5]);
                }
                if (channel[n] == 3)
                {
                    pRPD_TSDist[2][5]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[2][5]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[2][5]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[2][5]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[2][5]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[2][5]->Fill(5.0,TS5[n]);

                    AvgSigRPD[2]->Fill(0.0,TS0[n]);
                    AvgSigRPD[2]->Fill(1.0,TS1[n]);
                    AvgSigRPD[2]->Fill(2.0,TS2[n]);
                    AvgSigRPD[2]->Fill(3.0,TS3[n]);
                    AvgSigRPD[2]->Fill(4.0,TS4[n]);
                    AvgSigRPD[2]->Fill(5.0,TS5[n]);

                    pRPD_ratio[2][5] = TS2[n] / TS3[n];
                    pRPD_RatioDist[2][5]->Fill(pRPD_ratio[2][5]);

                    if (pRPD_ratio[2][5] > 1.8 && pRPD_ratio[2][5] < 2.2)
                    {
                        pRPD_sig[2][5] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[2][5]->Fill(pRPD_sig[2][5]);
                }
                if (channel[n] == 4)
                {
                    pRPD_TSDist[14][5]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[14][5]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[14][5]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[14][5]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[14][5]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[14][5]->Fill(5.0,TS5[n]);

                    AvgSigRPD[14]->Fill(0.0,TS0[n]);
                    AvgSigRPD[14]->Fill(1.0,TS1[n]);
                    AvgSigRPD[14]->Fill(2.0,TS2[n]);
                    AvgSigRPD[14]->Fill(3.0,TS3[n]);
                    AvgSigRPD[14]->Fill(4.0,TS4[n]);
                    AvgSigRPD[14]->Fill(5.0,TS5[n]);

                    pRPD_ratio[14][5] = TS2[n] / TS3[n];
                    pRPD_RatioDist[14][5]->Fill(pRPD_ratio[14][5]);

                    if (pRPD_ratio[14][5] > 1.1645 && pRPD_ratio[14][5] < 1.8515)
                    {
                        pRPD_sig[14][5] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[14][5]->Fill(pRPD_sig[14][5]);
                }
                if (channel[n] == 5)
                {
                    pRPD_TSDist[11][5]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[11][5]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[11][5]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[11][5]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[11][5]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[11][5]->Fill(5.0,TS5[n]);

                    AvgSigRPD[11]->Fill(0.0,TS0[n]);
                    AvgSigRPD[11]->Fill(1.0,TS1[n]);
                    AvgSigRPD[11]->Fill(2.0,TS2[n]);
                    AvgSigRPD[11]->Fill(3.0,TS3[n]);
                    AvgSigRPD[11]->Fill(4.0,TS4[n]);
                    AvgSigRPD[11]->Fill(5.0,TS5[n]);

                    pRPD_ratio[11][5] = TS2[n] / TS3[n];
                    pRPD_RatioDist[11][5]->Fill(pRPD_ratio[11][5]);

                    if (pRPD_ratio[11][5] > 1.2069 && pRPD_ratio[11][5] < 1.8411)
                    {
                        pRPD_sig[11][5] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[11][5]->Fill(pRPD_sig[11][5]);
                }
                if (channel[n] == 6)
                {
                    pRPD_TSDist[7][5]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[7][5]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[7][5]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[7][5]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[7][5]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[7][5]->Fill(5.0,TS5[n]);

                    AvgSigRPD[7]->Fill(0.0,TS0[n]);
                    AvgSigRPD[7]->Fill(1.0,TS1[n]);
                    AvgSigRPD[7]->Fill(2.0,TS2[n]);
                    AvgSigRPD[7]->Fill(3.0,TS3[n]);
                    AvgSigRPD[7]->Fill(4.0,TS4[n]);
                    AvgSigRPD[7]->Fill(5.0,TS5[n]);

                    pRPD_ratio[7][5] = TS2[n] / TS3[n];
                    pRPD_RatioDist[7][5]->Fill(pRPD_ratio[7][5]);

                    if (pRPD_ratio[7][5] > 1.4011 && pRPD_ratio[7][5] < 2.0589)
                    {
                        pRPD_sig[7][5] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[7][5]->Fill(pRPD_sig[7][5]);
                }
                if (channel[n] == 7)
                {
                    pRPD_TSDist[3][5]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[3][5]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[3][5]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[3][5]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[3][5]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[3][5]->Fill(5.0,TS5[n]);

                    AvgSigRPD[3]->Fill(0.0,TS0[n]);
                    AvgSigRPD[3]->Fill(1.0,TS1[n]);
                    AvgSigRPD[3]->Fill(2.0,TS2[n]);
                    AvgSigRPD[3]->Fill(3.0,TS3[n]);
                    AvgSigRPD[3]->Fill(4.0,TS4[n]);
                    AvgSigRPD[3]->Fill(5.0,TS5[n]);

                    pRPD_ratio[3][5] = TS2[n] / TS3[n];
                    pRPD_RatioDist[3][5]->Fill(pRPD_ratio[3][5]);

                    if (pRPD_ratio[3][5] > 1.4039 && pRPD_ratio[3][5] < 2.0881)
                    {
                        pRPD_sig[3][5] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[3][5]->Fill(pRPD_sig[3][5]);
                }
                if (channel[n] == 8)
                {
                    pRPD_TSDist[15][5]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[15][5]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[15][5]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[15][5]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[15][5]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[15][5]->Fill(5.0,TS5[n]);

                    AvgSigRPD[15]->Fill(0.0,TS0[n]);
                    AvgSigRPD[15]->Fill(1.0,TS1[n]);
                    AvgSigRPD[15]->Fill(2.0,TS2[n]);
                    AvgSigRPD[15]->Fill(3.0,TS3[n]);
                    AvgSigRPD[15]->Fill(4.0,TS4[n]);
                    AvgSigRPD[15]->Fill(5.0,TS5[n]);

                    pRPD_ratio[15][5] = TS2[n] / TS3[n];
                    pRPD_RatioDist[15][5]->Fill(pRPD_ratio[15][5]);

                    if (pRPD_ratio[15][5] > 1.1942 && pRPD_ratio[15][5] < 1.9038)
                    {
                        pRPD_sig[15][5] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[15][5]->Fill(pRPD_sig[15][5]);
                }
                if (channel[n] == 9)
                {
                    pRPD_TSDist[4][5]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[4][5]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[4][5]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[4][5]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[4][5]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[4][5]->Fill(5.0,TS5[n]);

                    AvgSigRPD[4]->Fill(0.0,TS0[n]);
                    AvgSigRPD[4]->Fill(1.0,TS1[n]);
                    AvgSigRPD[4]->Fill(2.0,TS2[n]);
                    AvgSigRPD[4]->Fill(3.0,TS3[n]);
                    AvgSigRPD[4]->Fill(4.0,TS4[n]);
                    AvgSigRPD[4]->Fill(5.0,TS5[n]);

                    pRPD_ratio[4][5] = TS2[n] / TS3[n];
                    pRPD_RatioDist[4][5]->Fill(pRPD_ratio[4][5]);

                    if (pRPD_ratio[4][5] > 1.252 && pRPD_ratio[4][5] < 2.268)
                    {
                        pRPD_sig[4][5] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[4][5]->Fill(pRPD_sig[4][5]);
                }
                if (channel[n] == 10)
                {
                    pRPD_TSDist[8][5]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[8][5]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[8][5]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[8][5]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[8][5]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[8][5]->Fill(5.0,TS5[n]);

                    AvgSigRPD[8]->Fill(0.0,TS0[n]);
                    AvgSigRPD[8]->Fill(1.0,TS1[n]);
                    AvgSigRPD[8]->Fill(2.0,TS2[n]);
                    AvgSigRPD[8]->Fill(3.0,TS3[n]);
                    AvgSigRPD[8]->Fill(4.0,TS4[n]);
                    AvgSigRPD[8]->Fill(5.0,TS5[n]);

                    pRPD_ratio[8][5] = TS2[n] / TS3[n];
                    pRPD_RatioDist[8][5]->Fill(pRPD_ratio[8][5]);

                    if (pRPD_ratio[8][5] > 1.2955 && pRPD_ratio[8][5] < 2.1905)
                    {
                        pRPD_sig[8][5] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[8][5]->Fill(pRPD_sig[8][5]);
                }
                if (channel[n] == 11)
                {
                    pRPD_TSDist[12][5]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[12][5]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[12][5]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[12][5]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[12][5]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[12][5]->Fill(5.0,TS5[n]);

                    AvgSigRPD[12]->Fill(0.0,TS0[n]);
                    AvgSigRPD[12]->Fill(1.0,TS1[n]);
                    AvgSigRPD[12]->Fill(2.0,TS2[n]);
                    AvgSigRPD[12]->Fill(3.0,TS3[n]);
                    AvgSigRPD[12]->Fill(4.0,TS4[n]);
                    AvgSigRPD[12]->Fill(5.0,TS5[n]);

                    pRPD_ratio[12][5] = TS2[n] / TS3[n];
                    pRPD_RatioDist[12][5]->Fill(pRPD_ratio[12][5]);

                    if (pRPD_ratio[12][5] > 1.2688 && pRPD_ratio[12][5] < 2.1392)
                    {
                        pRPD_sig[12][5] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[12][5]->Fill(pRPD_sig[12][5]);
                }
                if (channel[n] == 12)
                {
                    pRPD_TSDist[0][5]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[0][5]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[0][5]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[0][5]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[0][5]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[0][5]->Fill(5.0,TS5[n]);

                    AvgSigRPD[0]->Fill(0.0,TS0[n]);
                    AvgSigRPD[0]->Fill(1.0,TS1[n]);
                    AvgSigRPD[0]->Fill(2.0,TS2[n]);
                    AvgSigRPD[0]->Fill(3.0,TS3[n]);
                    AvgSigRPD[0]->Fill(4.0,TS4[n]);
                    AvgSigRPD[0]->Fill(5.0,TS5[n]);

                    pRPD_ratio[0][5] = TS2[n] / TS3[n];
                    pRPD_RatioDist[0][5]->Fill(pRPD_ratio[0][5]);

                    if (pRPD_ratio[0][5] > 1.2082 && pRPD_ratio[0][5] < 2.2878)
                    {
                        pRPD_sig[0][5] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[0][5]->Fill(pRPD_sig[0][5]);
                }
                if (channel[n] == 13)
                {
                    pRPD_TSDist[5][5]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[5][5]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[5][5]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[5][5]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[5][5]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[5][5]->Fill(5.0,TS5[n]);

                    AvgSigRPD[5]->Fill(0.0,TS0[n]);
                    AvgSigRPD[5]->Fill(1.0,TS1[n]);
                    AvgSigRPD[5]->Fill(2.0,TS2[n]);
                    AvgSigRPD[5]->Fill(3.0,TS3[n]);
                    AvgSigRPD[5]->Fill(4.0,TS4[n]);
                    AvgSigRPD[5]->Fill(5.0,TS5[n]);

                    pRPD_ratio[5][5] = TS2[n] / TS3[n];
                    pRPD_RatioDist[5][5]->Fill(pRPD_ratio[5][5]);

                    if (pRPD_ratio[5][5] > 1.6077 && pRPD_ratio[5][5] < 2.5083)
                    {
                        pRPD_sig[5][5] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[5][5]->Fill(pRPD_sig[5][5]);
                }
                if (channel[n] == 14)
                {
                    pRPD_TSDist[9][5]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[9][5]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[9][5]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[9][5]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[9][5]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[9][5]->Fill(5.0,TS5[n]);

                    AvgSigRPD[9]->Fill(0.0,TS0[n]);
                    AvgSigRPD[9]->Fill(1.0,TS1[n]);
                    AvgSigRPD[9]->Fill(2.0,TS2[n]);
                    AvgSigRPD[9]->Fill(3.0,TS3[n]);
                    AvgSigRPD[9]->Fill(4.0,TS4[n]);
                    AvgSigRPD[9]->Fill(5.0,TS5[n]);

                    pRPD_ratio[9][5] = TS2[n] / TS3[n];
                    pRPD_RatioDist[9][5]->Fill(pRPD_ratio[9][5]);

                    if (pRPD_ratio[9][5] > 1.5316 && pRPD_ratio[9][5] < 2.4484)
                    {
                        pRPD_sig[9][5] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[9][5]->Fill(pRPD_sig[9][5]);
                }
                if (channel[n] == 15)
                {
                    pRPD_TSDist[13][5]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[13][5]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[13][5]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[13][5]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[13][5]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[13][5]->Fill(5.0,TS5[n]);

                    AvgSigRPD[13]->Fill(0.0,TS0[n]);
                    AvgSigRPD[13]->Fill(1.0,TS1[n]);
                    AvgSigRPD[13]->Fill(2.0,TS2[n]);
                    AvgSigRPD[13]->Fill(3.0,TS3[n]);
                    AvgSigRPD[13]->Fill(4.0,TS4[n]);
                    AvgSigRPD[13]->Fill(5.0,TS5[n]);

                    pRPD_ratio[13][5] = TS2[n] / TS3[n];
                    pRPD_RatioDist[13][5]->Fill(pRPD_ratio[13][5]);

                    if (pRPD_ratio[13][5] > 1.4921 && pRPD_ratio[13][5] < 2.2959)
                    {
                        pRPD_sig[13][5] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[13][5]->Fill(pRPD_sig[13][5]);
                }
                if (channel[n] == 16)
                {
                    pRPD_TSDist[1][5]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[1][5]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[1][5]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[1][5]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[1][5]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[1][5]->Fill(5.0,TS5[n]);

                    AvgSigRPD[1]->Fill(0.0,TS0[n]);
                    AvgSigRPD[1]->Fill(1.0,TS1[n]);
                    AvgSigRPD[1]->Fill(2.0,TS2[n]);
                    AvgSigRPD[1]->Fill(3.0,TS3[n]);
                    AvgSigRPD[1]->Fill(4.0,TS4[n]);
                    AvgSigRPD[1]->Fill(5.0,TS5[n]);

                    pRPD_ratio[1][5] = TS2[n] / TS3[n];
                    pRPD_RatioDist[1][5]->Fill(pRPD_ratio[1][5]);

                    if (pRPD_ratio[1][5] > 1.5232 && pRPD_ratio[1][5] < 2.5228)
                    {
                        pRPD_sig[1][5] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[1][5]->Fill(pRPD_sig[1][5]);
                }
            } // end pos RPD 40 - 50 cent 
            if (zside[n] == 1 && section[n] == 1)
            {
                if (channel[n] == 1)
                {
                    pEM_TSDist[0][5]->Fill(0.0,TS0[n]);
                    pEM_TSDist[0][5]->Fill(1.0,TS1[n]);
                    pEM_TSDist[0][5]->Fill(2.0,TS2[n]);
                    pEM_TSDist[0][5]->Fill(3.0,TS3[n]);
                    pEM_TSDist[0][5]->Fill(4.0,TS4[n]);
                    pEM_TSDist[0][5]->Fill(5.0,TS5[n]);

                    pEM_ratio[0][5] = TS2[n] / TS3[n];
                    pEM_RatioDist[0][5]->Fill(pEM_ratio[0][5]);

                    pEM_sig[0][5] = TS2[n] - TS1[n];

                    pEM_fCDist[0][5]->Fill(pEM_sig[0][5]);
                }
                if (channel[n] == 2)
                {
                    pEM_TSDist[1][5]->Fill(0.0,TS0[n]);
                    pEM_TSDist[1][5]->Fill(1.0,TS1[n]);
                    pEM_TSDist[1][5]->Fill(2.0,TS2[n]);
                    pEM_TSDist[1][5]->Fill(3.0,TS3[n]);
                    pEM_TSDist[1][5]->Fill(4.0,TS4[n]);
                    pEM_TSDist[1][5]->Fill(5.0,TS5[n]);

                    pEM_ratio[1][5] = TS2[n] / TS3[n];
                    pEM_RatioDist[1][5]->Fill(pEM_ratio[1][5]);

                    pEM_sig[1][5] = TS2[n] - TS1[n];

                    pEM_fCDist[1][5]->Fill(pEM_sig[1][5]);
                }
                if (channel[n] == 3)
                {
                    pEM_TSDist[2][5]->Fill(0.0,TS0[n]);
                    pEM_TSDist[2][5]->Fill(1.0,TS1[n]);
                    pEM_TSDist[2][5]->Fill(2.0,TS2[n]);
                    pEM_TSDist[2][5]->Fill(3.0,TS3[n]);
                    pEM_TSDist[2][5]->Fill(4.0,TS4[n]);
                    pEM_TSDist[2][5]->Fill(5.0,TS5[n]);

                    pEM_ratio[2][5] = TS2[n] / TS3[n];
                    pEM_RatioDist[2][5]->Fill(pEM_ratio[2][5]);

                    pEM_sig[2][5] = TS2[n] - TS1[n];

                    pEM_fCDist[2][5]->Fill(pEM_sig[2][5]);
                }
                if (channel[n] == 4)
                {
                    pEM_TSDist[3][5]->Fill(0.0,TS0[n]);
                    pEM_TSDist[3][5]->Fill(1.0,TS1[n]);
                    pEM_TSDist[3][5]->Fill(2.0,TS2[n]);
                    pEM_TSDist[3][5]->Fill(3.0,TS3[n]);
                    pEM_TSDist[3][5]->Fill(4.0,TS4[n]);
                    pEM_TSDist[3][5]->Fill(5.0,TS5[n]);

                    pEM_ratio[3][5] = TS2[n] / TS3[n];
                    pEM_RatioDist[3][5]->Fill(pEM_ratio[3][5]);

                    pEM_sig[3][5] = TS2[n] - TS1[n];

                    pEM_fCDist[3][5]->Fill(pEM_sig[3][5]);
                }
                if (channel[n] == 5)
                {
                    pEM_TSDist[4][5]->Fill(0.0,TS0[n]);
                    pEM_TSDist[4][5]->Fill(1.0,TS1[n]);
                    pEM_TSDist[4][5]->Fill(2.0,TS2[n]);
                    pEM_TSDist[4][5]->Fill(3.0,TS3[n]);
                    pEM_TSDist[4][5]->Fill(4.0,TS4[n]);
                    pEM_TSDist[4][5]->Fill(5.0,TS5[n]);

                    pEM_ratio[4][5] = TS2[n] / TS3[n];
                    pEM_RatioDist[4][5]->Fill(pEM_ratio[4][5]);

                    pEM_sig[4][5] = TS2[n] - TS1[n];

                    pEM_fCDist[4][5]->Fill(pEM_sig[4][5]);
                }
                pEM_sigtot[5] = pEM_sig[0][5] + pEM_sig[1][5] + pEM_sig[2][5] + pEM_sig[3][5] + pEM_sig[4][5];
            } // end pos em 40 - 50 cent
            
            if (zside[n] == 1 && section[n] == 2)
            {
                if (channel[n] == 1)
                {
                    pHAD_TSDist[0][5]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[0][5]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[0][5]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[0][5]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[0][5]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[0][5]->Fill(5.0,TS5[n]);

                    pHAD_ratio[0][5] = TS2[n] / TS3[n];
                    pHAD_RatioDist[0][5]->Fill(pHAD_ratio[0][5]);

                    pHAD_sig[0][5] = TS2[n] - TS1[n];

                    pHAD_fCDist[0][5]->Fill(pHAD_sig[0][5]);
                }
                if (channel[n] == 2)
                {
                    pHAD_TSDist[1][5]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[1][5]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[1][5]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[1][5]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[1][5]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[1][5]->Fill(5.0,TS5[n]);

                    pHAD_ratio[1][5] = TS2[n] / TS3[n];
                    pHAD_RatioDist[1][5]->Fill(pHAD_ratio[1][5]);

                    pHAD_sig[1][5] = TS2[n] - TS1[n];

                    pHAD_fCDist[1][5]->Fill(pHAD_sig[1][5]);
                }
                if (channel[n] == 3)
                {
                    pHAD_TSDist[2][5]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[2][5]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[2][5]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[2][5]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[2][5]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[2][5]->Fill(5.0,TS5[n]);

                    pHAD_ratio[2][5] = TS2[n] / TS3[n];
                    pHAD_RatioDist[2][5]->Fill(pHAD_ratio[2][5]);

                    pHAD_sig[2][5] = TS2[n] - TS1[n];

                    pHAD_fCDist[2][5]->Fill(pHAD_sig[2][5]);
                }
                if (channel[n] == 4)
                {
                    pHAD_TSDist[3][5]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[3][5]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[3][5]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[3][5]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[3][5]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[3][5]->Fill(5.0,TS5[n]);

                    pHAD_ratio[3][5] = TS2[n] / TS3[n];
                    pHAD_RatioDist[3][5]->Fill(pHAD_ratio[3][5]);

                    pHAD_sig[3][5] = TS2[n] - TS1[n];

                    pHAD_fCDist[3][5]->Fill(pHAD_sig[3][5]);
                }
                pHAD_sigtot[5] = pHAD_sig[0][5] + pHAD_sig[1][5] + pHAD_sig[2][5] + pHAD_sig[3][5];
            } // end of pos had 40-50 cent
            ZDC[5] = 0.1 * pEM_sigtot[5] + pHAD_sigtot[5];
        } // end of 40 - 50 cent 

        /*pos ZDC 50 - 60 cent analysis*/
        if (hibin >= 100 && hibin < 120)
            {
            if (zside[n] == 1 && section[n] == 4)
            {
                if (channel[n] == 1)
                {
                    pRPD_TSDist[10][6]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[10][6]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[10][6]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[10][6]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[10][6]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[10][6]->Fill(5.0,TS5[n]);

                    pRPD_ratio[10][6] = TS2[n] / TS3[n];
                    pRPD_RatioDist[10][6]->Fill(pRPD_ratio[10][6]);

                    if (pRPD_ratio[10][6] > 1.1893 && pRPD_ratio[10][6] < 1.8067)
                    {
                        pRPD_sig[10][6] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[10][6]->Fill(pRPD_sig[10][6]);
                }
                if (channel[n] == 2)                                                                                                
                {
                    pRPD_TSDist[6][6]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[6][6]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[6][6]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[6][6]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[6][6]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[6][6]->Fill(5.0,TS5[n]);

                    pRPD_ratio[6][6] = TS2[n] / TS3[n];
                    pRPD_RatioDist[6][6]->Fill(pRPD_ratio[6][6]);

                    if (pRPD_ratio[6][6] > 1.2832 && pRPD_ratio[6][6] < 1.8688)
                    {
                        pRPD_sig[6][6] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[6][6]->Fill(pRPD_sig[6][6]);
                }
                if (channel[n] == 3)
                {
                    pRPD_TSDist[2][6]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[2][6]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[2][6]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[2][6]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[2][6]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[2][6]->Fill(5.0,TS5[n]);

                    pRPD_ratio[2][6] = TS2[n] / TS3[n];
                    pRPD_RatioDist[2][6]->Fill(pRPD_ratio[2][6]);

                    if (pRPD_ratio[2][6] > 1.8 && pRPD_ratio[2][6] < 2.2)
                    {
                        pRPD_sig[2][6] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[2][6]->Fill(pRPD_sig[2][6]);
                }
                if (channel[n] == 4)
                {
                    pRPD_TSDist[14][6]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[14][6]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[14][6]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[14][6]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[14][6]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[14][6]->Fill(5.0,TS5[n]);

                    pRPD_ratio[14][6] = TS2[n] / TS3[n];
                    pRPD_RatioDist[14][6]->Fill(pRPD_ratio[14][6]);

                    if (pRPD_ratio[14][6] > 1.1645 && pRPD_ratio[14][6] < 1.8515)
                    {
                        pRPD_sig[14][6] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[14][6]->Fill(pRPD_sig[14][6]);
                }
                if (channel[n] == 5)
                {
                    pRPD_TSDist[11][6]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[11][6]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[11][6]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[11][6]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[11][6]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[11][6]->Fill(5.0,TS5[n]);

                    pRPD_ratio[11][6] = TS2[n] / TS3[n];
                    pRPD_RatioDist[11][6]->Fill(pRPD_ratio[11][6]);

                    if (pRPD_ratio[11][6] > 1.2069 && pRPD_ratio[11][6] < 1.8411)
                    {
                        pRPD_sig[11][6] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[11][6]->Fill(pRPD_sig[11][6]);
                }
                if (channel[n] == 6)
                {
                    pRPD_TSDist[7][6]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[7][6]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[7][6]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[7][6]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[7][6]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[7][6]->Fill(5.0,TS5[n]);

                    pRPD_ratio[7][6] = TS2[n] / TS3[n];
                    pRPD_RatioDist[7][6]->Fill(pRPD_ratio[7][6]);

                    if (pRPD_ratio[7][6] > 1.4011 && pRPD_ratio[7][6] < 2.0589)
                    {
                        pRPD_sig[7][6] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[7][6]->Fill(pRPD_sig[7][6]);
                }
                if (channel[n] == 7)
                {
                    pRPD_TSDist[3][6]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[3][6]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[3][6]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[3][6]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[3][6]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[3][6]->Fill(5.0,TS5[n]);

                    pRPD_ratio[3][6] = TS2[n] / TS3[n];
                    pRPD_RatioDist[3][6]->Fill(pRPD_ratio[3][6]);

                    if (pRPD_ratio[3][6] > 1.4039 && pRPD_ratio[3][6] < 2.0881)
                    {
                        pRPD_sig[3][6] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[3][6]->Fill(pRPD_sig[3][6]);
                }
                if (channel[n] == 8)
                {
                    pRPD_TSDist[15][6]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[15][6]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[15][6]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[15][6]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[15][6]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[15][6]->Fill(5.0,TS5[n]);

                    pRPD_ratio[15][6] = TS2[n] / TS3[n];
                    pRPD_RatioDist[15][6]->Fill(pRPD_ratio[15][6]);

                    if (pRPD_ratio[15][6] > 1.1942 && pRPD_ratio[15][6] < 1.9038)
                    {
                        pRPD_sig[15][6] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[15][6]->Fill(pRPD_sig[15][6]);
                }
                if (channel[n] == 9)
                {
                    pRPD_TSDist[4][6]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[4][6]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[4][6]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[4][6]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[4][6]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[4][6]->Fill(5.0,TS5[n]);

                    pRPD_ratio[4][6] = TS2[n] / TS3[n];
                    pRPD_RatioDist[4][6]->Fill(pRPD_ratio[4][6]);

                    if (pRPD_ratio[4][6] > 1.252 && pRPD_ratio[4][6] < 2.268)
                    {
                        pRPD_sig[4][6] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[4][6]->Fill(pRPD_sig[4][6]);
                }
                if (channel[n] == 10)
                {
                    pRPD_TSDist[8][6]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[8][6]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[8][6]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[8][6]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[8][6]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[8][6]->Fill(5.0,TS5[n]);

                    pRPD_ratio[8][6] = TS2[n] / TS3[n];
                    pRPD_RatioDist[8][6]->Fill(pRPD_ratio[8][6]);

                    if (pRPD_ratio[8][6] > 1.2955 && pRPD_ratio[8][6] < 2.1905)
                    {
                        pRPD_sig[8][6] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[8][6]->Fill(pRPD_sig[8][6]);
                }
                if (channel[n] == 11)
                {
                    pRPD_TSDist[12][6]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[12][6]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[12][6]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[12][6]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[12][6]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[12][6]->Fill(5.0,TS5[n]);

                    pRPD_ratio[12][6] = TS2[n] / TS3[n];
                    pRPD_RatioDist[12][6]->Fill(pRPD_ratio[12][6]);

                    if (pRPD_ratio[12][6] > 1.2688 && pRPD_ratio[12][6] < 2.1392)
                    {
                        pRPD_sig[12][6] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[12][6]->Fill(pRPD_sig[12][6]);
                }
                if (channel[n] == 12)
                {
                    pRPD_TSDist[0][6]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[0][6]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[0][6]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[0][6]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[0][6]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[0][6]->Fill(5.0,TS5[n]);

                    pRPD_ratio[0][6] = TS2[n] / TS3[n];
                    pRPD_RatioDist[0][6]->Fill(pRPD_ratio[0][6]);

                    if (pRPD_ratio[0][6] > 1.2082 && pRPD_ratio[0][6] < 2.2878)
                    {
                        pRPD_sig[0][6] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[0][6]->Fill(pRPD_sig[0][6]);
                }
                if (channel[n] == 13)
                {
                    pRPD_TSDist[5][6]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[5][6]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[5][6]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[5][6]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[5][6]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[5][6]->Fill(5.0,TS5[n]);

                    pRPD_ratio[5][6] = TS2[n] / TS3[n];
                    pRPD_RatioDist[5][6]->Fill(pRPD_ratio[5][6]);

                    if (pRPD_ratio[5][6] > 1.6077 && pRPD_ratio[5][6] < 2.5083)
                    {
                        pRPD_sig[5][6] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[5][6]->Fill(pRPD_sig[5][6]);
                }
                if (channel[n] == 14)
                {
                    pRPD_TSDist[9][6]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[9][6]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[9][6]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[9][6]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[9][6]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[9][6]->Fill(5.0,TS5[n]);

                    pRPD_ratio[9][6] = TS2[n] / TS3[n];
                    pRPD_RatioDist[9][6]->Fill(pRPD_ratio[9][6]);

                    if (pRPD_ratio[9][6] > 1.5316 && pRPD_ratio[9][6] < 2.4484)
                    {
                        pRPD_sig[9][6] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[9][6]->Fill(pRPD_sig[9][6]);
                }
                if (channel[n] == 15)
                {
                    pRPD_TSDist[13][6]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[13][6]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[13][6]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[13][6]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[13][6]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[13][6]->Fill(5.0,TS5[n]);

                    pRPD_ratio[13][6] = TS2[n] / TS3[n];
                    pRPD_RatioDist[13][6]->Fill(pRPD_ratio[13][6]);

                    if (pRPD_ratio[13][6] > 1.4921 && pRPD_ratio[13][6] < 2.2959)
                    {
                        pRPD_sig[13][6] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[13][6]->Fill(pRPD_sig[13][6]);
                }
                if (channel[n] == 16)
                {
                    pRPD_TSDist[1][6]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[1][6]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[1][6]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[1][6]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[1][6]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[1][6]->Fill(5.0,TS5[n]);

                    pRPD_ratio[1][6] = TS2[n] / TS3[n];
                    pRPD_RatioDist[1][6]->Fill(pRPD_ratio[1][6]);

                    if (pRPD_ratio[1][6] > 1.5232 && pRPD_ratio[1][6] < 2.5228)
                    {
                        pRPD_sig[1][6] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[1][6]->Fill(pRPD_sig[1][6]);
                }
            } // end pos RPD 50 - 60 cent 
            if (zside[n] == 1 && section[n] == 1)
            {
                if (channel[n] == 1)
                {
                    pEM_TSDist[0][6]->Fill(0.0,TS0[n]);
                    pEM_TSDist[0][6]->Fill(1.0,TS1[n]);
                    pEM_TSDist[0][6]->Fill(2.0,TS2[n]);
                    pEM_TSDist[0][6]->Fill(3.0,TS3[n]);
                    pEM_TSDist[0][6]->Fill(4.0,TS4[n]);
                    pEM_TSDist[0][6]->Fill(5.0,TS5[n]);

                    pEM_ratio[0][6] = TS2[n] / TS3[n];
                    pEM_RatioDist[0][6]->Fill(pEM_ratio[0][6]);

                    pEM_sig[0][6] = TS2[n] - TS1[n];

                    pEM_fCDist[0][6]->Fill(pEM_sig[0][6]);
                }
                if (channel[n] == 2)
                {
                    pEM_TSDist[1][6]->Fill(0.0,TS0[n]);
                    pEM_TSDist[1][6]->Fill(1.0,TS1[n]);
                    pEM_TSDist[1][6]->Fill(2.0,TS2[n]);
                    pEM_TSDist[1][6]->Fill(3.0,TS3[n]);
                    pEM_TSDist[1][6]->Fill(4.0,TS4[n]);
                    pEM_TSDist[1][6]->Fill(5.0,TS5[n]);

                    pEM_ratio[1][6] = TS2[n] / TS3[n];
                    pEM_RatioDist[1][6]->Fill(pEM_ratio[1][6]);

                    pEM_sig[1][6] = TS2[n] - TS1[n];

                    pEM_fCDist[1][6]->Fill(pEM_sig[1][6]);
                }
                if (channel[n] == 3)
                {
                    pEM_TSDist[2][6]->Fill(0.0,TS0[n]);
                    pEM_TSDist[2][6]->Fill(1.0,TS1[n]);
                    pEM_TSDist[2][6]->Fill(2.0,TS2[n]);
                    pEM_TSDist[2][6]->Fill(3.0,TS3[n]);
                    pEM_TSDist[2][6]->Fill(4.0,TS4[n]);
                    pEM_TSDist[2][6]->Fill(5.0,TS5[n]);

                    pEM_ratio[2][6] = TS2[n] / TS3[n];
                    pEM_RatioDist[2][6]->Fill(pEM_ratio[2][6]);

                    pEM_sig[2][6] = TS2[n] - TS1[n];

                    pEM_fCDist[2][6]->Fill(pEM_sig[2][6]);
                }
                if (channel[n] == 4)
                {
                    pEM_TSDist[3][6]->Fill(0.0,TS0[n]);
                    pEM_TSDist[3][6]->Fill(1.0,TS1[n]);
                    pEM_TSDist[3][6]->Fill(2.0,TS2[n]);
                    pEM_TSDist[3][6]->Fill(3.0,TS3[n]);
                    pEM_TSDist[3][6]->Fill(4.0,TS4[n]);
                    pEM_TSDist[3][6]->Fill(5.0,TS5[n]);

                    pEM_ratio[3][6] = TS2[n] / TS3[n];
                    pEM_RatioDist[3][6]->Fill(pEM_ratio[3][6]);

                    pEM_sig[3][6] = TS2[n] - TS1[n];

                    pEM_fCDist[3][6]->Fill(pEM_sig[3][6]);
                }
                if (channel[n] == 5)
                {
                    pEM_TSDist[4][6]->Fill(0.0,TS0[n]);
                    pEM_TSDist[4][6]->Fill(1.0,TS1[n]);
                    pEM_TSDist[4][6]->Fill(2.0,TS2[n]);
                    pEM_TSDist[4][6]->Fill(3.0,TS3[n]);
                    pEM_TSDist[4][6]->Fill(4.0,TS4[n]);
                    pEM_TSDist[4][6]->Fill(5.0,TS5[n]);

                    pEM_ratio[4][6] = TS2[n] / TS3[n];
                    pEM_RatioDist[4][6]->Fill(pEM_ratio[4][6]);

                    pEM_sig[4][6] = TS2[n] - TS1[n];

                    pEM_fCDist[4][6]->Fill(pEM_sig[4][6]);
                }
                pEM_sigtot[6] = pEM_sig[0][6] + pEM_sig[1][6] + pEM_sig[2][6] + pEM_sig[3][6] + pEM_sig[4][6];
            } // end pos em 50 - 60 cent
            
            if (zside[n] == 1 && section[n] == 2)
            {
                if (channel[n] == 1)
                {
                    pHAD_TSDist[0][6]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[0][6]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[0][6]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[0][6]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[0][6]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[0][6]->Fill(5.0,TS5[n]);

                    pHAD_ratio[0][6] = TS2[n] / TS3[n];
                    pHAD_RatioDist[0][6]->Fill(pHAD_ratio[0][6]);

                    pHAD_sig[0][6] = TS2[n] - TS1[n];

                    pHAD_fCDist[0][6]->Fill(pHAD_sig[0][6]);
                }
                if (channel[n] == 2)
                {
                    pHAD_TSDist[1][6]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[1][6]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[1][6]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[1][6]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[1][6]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[1][6]->Fill(5.0,TS5[n]);

                    pHAD_ratio[1][6] = TS2[n] / TS3[n];
                    pHAD_RatioDist[1][6]->Fill(pHAD_ratio[1][6]);

                    pHAD_sig[1][6] = TS2[n] - TS1[n];

                    pHAD_fCDist[1][6]->Fill(pHAD_sig[1][6]);
                }
                if (channel[n] == 3)
                {
                    pHAD_TSDist[2][6]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[2][6]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[2][6]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[2][6]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[2][6]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[2][6]->Fill(5.0,TS5[n]);

                    pHAD_ratio[2][6] = TS2[n] / TS3[n];
                    pHAD_RatioDist[2][6]->Fill(pHAD_ratio[2][6]);

                    pHAD_sig[2][6] = TS2[n] - TS1[n];

                    pHAD_fCDist[2][6]->Fill(pHAD_sig[2][6]);
                }
                if (channel[n] == 4)
                {
                    pHAD_TSDist[3][6]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[3][6]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[3][6]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[3][6]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[3][6]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[3][6]->Fill(5.0,TS5[n]);

                    pHAD_ratio[3][6] = TS2[n] / TS3[n];
                    pHAD_RatioDist[3][6]->Fill(pHAD_ratio[3][6]);

                    pHAD_sig[3][6] = TS2[n] - TS1[n];

                    pHAD_fCDist[3][6]->Fill(pHAD_sig[3][6]);
                }
                pHAD_sigtot[6] = pHAD_sig[0][6] + pHAD_sig[1][6] + pHAD_sig[2][6] + pHAD_sig[3][6];
            } // end of pos had 50-60 cent
            ZDC[6] = 0.1 * pEM_sigtot[6] + pHAD_sigtot[6];
        } // end of 50 - 60 cent 

        /*pos ZDC 60 - 70 cent analysis*/
        if (hibin >= 120 && hibin < 140)
            {
            if (zside[n] == 1 && section[n] == 4)
            {
                if (channel[n] == 1)
                {
                    pRPD_TSDist[10][7]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[10][7]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[10][7]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[10][7]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[10][7]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[10][7]->Fill(5.0,TS5[n]);

                    pRPD_ratio[10][7] = TS2[n] / TS3[n];
                    pRPD_RatioDist[10][7]->Fill(pRPD_ratio[10][7]);

                    if (pRPD_ratio[10][7] > 1.1893 && pRPD_ratio[10][7] < 1.8067)
                    {
                        pRPD_sig[10][7] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[10][7]->Fill(pRPD_sig[10][7]);
                }
                if (channel[n] == 2)                                                                                                
                {
                    pRPD_TSDist[6][7]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[6][7]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[6][7]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[6][7]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[6][7]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[6][7]->Fill(5.0,TS5[n]);

                    pRPD_ratio[6][7] = TS2[n] / TS3[n];
                    pRPD_RatioDist[6][7]->Fill(pRPD_ratio[6][7]);

                    if (pRPD_ratio[6][7] > 1.2832 && pRPD_ratio[6][7] < 1.8688)
                    {
                        pRPD_sig[6][7] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[6][7]->Fill(pRPD_sig[6][7]);
                }
                if (channel[n] == 3)
                {
                    pRPD_TSDist[2][7]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[2][7]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[2][7]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[2][7]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[2][7]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[2][7]->Fill(5.0,TS5[n]);

                    pRPD_ratio[2][7] = TS2[n] / TS3[n];
                    pRPD_RatioDist[2][7]->Fill(pRPD_ratio[2][7]);

                    if (pRPD_ratio[2][7] > 1.8 && pRPD_ratio[2][7] < 2.2)
                    {
                        pRPD_sig[2][7] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[2][7]->Fill(pRPD_sig[2][7]);
                }
                if (channel[n] == 4)
                {
                    pRPD_TSDist[14][7]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[14][7]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[14][7]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[14][7]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[14][7]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[14][7]->Fill(5.0,TS5[n]);

                    pRPD_ratio[14][7] = TS2[n] / TS3[n];
                    pRPD_RatioDist[14][7]->Fill(pRPD_ratio[14][7]);

                    if (pRPD_ratio[14][7] > 1.1645 && pRPD_ratio[14][7] < 1.8515)
                    {
                        pRPD_sig[14][7] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[14][7]->Fill(pRPD_sig[14][7]);
                }
                if (channel[n] == 5)
                {
                    pRPD_TSDist[11][7]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[11][7]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[11][7]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[11][7]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[11][7]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[11][7]->Fill(5.0,TS5[n]);

                    pRPD_ratio[11][7] = TS2[n] / TS3[n];
                    pRPD_RatioDist[11][7]->Fill(pRPD_ratio[11][7]);

                    if (pRPD_ratio[11][7] > 1.2069 && pRPD_ratio[11][7] < 1.8411)
                    {
                        pRPD_sig[11][7] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[11][7]->Fill(pRPD_sig[11][7]);
                }
                if (channel[n] == 6)
                {
                    pRPD_TSDist[7][7]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[7][7]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[7][7]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[7][7]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[7][7]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[7][7]->Fill(5.0,TS5[n]);

                    pRPD_ratio[7][7] = TS2[n] / TS3[n];
                    pRPD_RatioDist[7][7]->Fill(pRPD_ratio[7][7]);

                    if (pRPD_ratio[7][7] > 1.4011 && pRPD_ratio[7][7] < 2.0589)
                    {
                        pRPD_sig[7][7] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[7][7]->Fill(pRPD_sig[7][7]);
                }
                if (channel[n] == 7)
                {
                    pRPD_TSDist[3][7]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[3][7]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[3][7]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[3][7]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[3][7]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[3][7]->Fill(5.0,TS5[n]);

                    pRPD_ratio[3][7] = TS2[n] / TS3[n];
                    pRPD_RatioDist[3][7]->Fill(pRPD_ratio[3][7]);

                    if (pRPD_ratio[3][7] > 1.4039 && pRPD_ratio[3][7] < 2.0881)
                    {
                        pRPD_sig[3][7] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[3][7]->Fill(pRPD_sig[3][7]);
                }
                if (channel[n] == 8)
                {
                    pRPD_TSDist[15][7]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[15][7]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[15][7]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[15][7]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[15][7]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[15][7]->Fill(5.0,TS5[n]);

                    pRPD_ratio[15][7] = TS2[n] / TS3[n];
                    pRPD_RatioDist[15][7]->Fill(pRPD_ratio[15][7]);

                    if (pRPD_ratio[15][7] > 1.1942 && pRPD_ratio[15][7] < 1.9038)
                    {
                        pRPD_sig[15][7] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[15][7]->Fill(pRPD_sig[15][7]);
                }
                if (channel[n] == 9)
                {
                    pRPD_TSDist[4][7]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[4][7]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[4][7]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[4][7]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[4][7]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[4][7]->Fill(5.0,TS5[n]);

                    pRPD_ratio[4][7] = TS2[n] / TS3[n];
                    pRPD_RatioDist[4][7]->Fill(pRPD_ratio[4][7]);

                    if (pRPD_ratio[4][7] > 1.252 && pRPD_ratio[4][7] < 2.268)
                    {
                        pRPD_sig[4][7] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[4][7]->Fill(pRPD_sig[4][7]);
                }
                if (channel[n] == 10)
                {
                    pRPD_TSDist[8][7]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[8][7]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[8][7]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[8][7]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[8][7]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[8][7]->Fill(5.0,TS5[n]);

                    pRPD_ratio[8][7] = TS2[n] / TS3[n];
                    pRPD_RatioDist[8][7]->Fill(pRPD_ratio[8][7]);

                    if (pRPD_ratio[8][7] > 1.2955 && pRPD_ratio[8][7] < 2.1905)
                    {
                        pRPD_sig[8][7] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[8][7]->Fill(pRPD_sig[8][7]);
                }
                if (channel[n] == 11)
                {
                    pRPD_TSDist[12][7]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[12][7]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[12][7]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[12][7]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[12][7]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[12][7]->Fill(5.0,TS5[n]);

                    pRPD_ratio[12][7] = TS2[n] / TS3[n];
                    pRPD_RatioDist[12][7]->Fill(pRPD_ratio[12][7]);

                    if (pRPD_ratio[12][7] > 1.2688 && pRPD_ratio[12][7] < 2.1392)
                    {
                        pRPD_sig[12][7] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[12][7]->Fill(pRPD_sig[12][7]);
                }
                if (channel[n] == 12)
                {
                    pRPD_TSDist[0][7]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[0][7]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[0][7]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[0][7]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[0][7]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[0][7]->Fill(5.0,TS5[n]);

                    pRPD_ratio[0][7] = TS2[n] / TS3[n];
                    pRPD_RatioDist[0][7]->Fill(pRPD_ratio[0][7]);

                    if (pRPD_ratio[0][7] > 1.2082 && pRPD_ratio[0][7] < 2.2878)
                    {
                        pRPD_sig[0][7] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[0][7]->Fill(pRPD_sig[0][7]);
                }
                if (channel[n] == 13)
                {
                    pRPD_TSDist[5][7]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[5][7]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[5][7]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[5][7]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[5][7]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[5][7]->Fill(5.0,TS5[n]);

                    pRPD_ratio[5][7] = TS2[n] / TS3[n];
                    pRPD_RatioDist[5][7]->Fill(pRPD_ratio[5][7]);

                    if (pRPD_ratio[5][7] > 1.6077 && pRPD_ratio[5][7] < 2.5083)
                    {
                        pRPD_sig[5][7] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[5][7]->Fill(pRPD_sig[5][7]);
                }
                if (channel[n] == 14)
                {
                    pRPD_TSDist[9][7]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[9][7]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[9][7]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[9][7]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[9][7]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[9][7]->Fill(5.0,TS5[n]);

                    pRPD_ratio[9][7] = TS2[n] / TS3[n];
                    pRPD_RatioDist[9][7]->Fill(pRPD_ratio[9][7]);

                    if (pRPD_ratio[9][7] > 1.5316 && pRPD_ratio[9][7] < 2.4484)
                    {
                        pRPD_sig[9][7] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[9][7]->Fill(pRPD_sig[9][7]);
                }
                if (channel[n] == 15)
                {
                    pRPD_TSDist[13][7]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[13][7]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[13][7]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[13][7]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[13][7]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[13][7]->Fill(5.0,TS5[n]);

                    pRPD_ratio[13][7] = TS2[n] / TS3[n];
                    pRPD_RatioDist[13][7]->Fill(pRPD_ratio[13][7]);

                    if (pRPD_ratio[13][7] > 1.4921 && pRPD_ratio[13][7] < 2.2959)
                    {
                        pRPD_sig[13][7] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[13][7]->Fill(pRPD_sig[13][7]);
                }
                if (channel[n] == 16)
                {
                    pRPD_TSDist[1][7]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[1][7]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[1][7]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[1][7]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[1][7]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[1][7]->Fill(5.0,TS5[n]);

                    pRPD_ratio[1][7] = TS2[n] / TS3[n];
                    pRPD_RatioDist[1][7]->Fill(pRPD_ratio[1][7]);

                    if (pRPD_ratio[1][7] > 1.5232 && pRPD_ratio[1][7] < 2.5228)
                    {
                        pRPD_sig[1][7] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[1][7]->Fill(pRPD_sig[1][7]);
                }
            } // end pos RPD 60 - 70 cent 
            if (zside[n] == 1 && section[n] == 1)
            {
                if (channel[n] == 1)
                {
                    pEM_TSDist[0][7]->Fill(0.0,TS0[n]);
                    pEM_TSDist[0][7]->Fill(1.0,TS1[n]);
                    pEM_TSDist[0][7]->Fill(2.0,TS2[n]);
                    pEM_TSDist[0][7]->Fill(3.0,TS3[n]);
                    pEM_TSDist[0][7]->Fill(4.0,TS4[n]);
                    pEM_TSDist[0][7]->Fill(5.0,TS5[n]);

                    pEM_ratio[0][7] = TS2[n] / TS3[n];
                    pEM_RatioDist[0][7]->Fill(pEM_ratio[0][7]);

                    pEM_sig[0][7] = TS2[n] - TS1[n];

                    pEM_fCDist[0][7]->Fill(pEM_sig[0][7]);
                }
                if (channel[n] == 2)
                {
                    pEM_TSDist[1][7]->Fill(0.0,TS0[n]);
                    pEM_TSDist[1][7]->Fill(1.0,TS1[n]);
                    pEM_TSDist[1][7]->Fill(2.0,TS2[n]);
                    pEM_TSDist[1][7]->Fill(3.0,TS3[n]);
                    pEM_TSDist[1][7]->Fill(4.0,TS4[n]);
                    pEM_TSDist[1][7]->Fill(5.0,TS5[n]);

                    pEM_ratio[1][7] = TS2[n] / TS3[n];
                    pEM_RatioDist[1][7]->Fill(pEM_ratio[1][7]);

                    pEM_sig[1][7] = TS2[n] - TS1[n];

                    pEM_fCDist[1][7]->Fill(pEM_sig[1][7]);
                }
                if (channel[n] == 3)
                {
                    pEM_TSDist[2][7]->Fill(0.0,TS0[n]);
                    pEM_TSDist[2][7]->Fill(1.0,TS1[n]);
                    pEM_TSDist[2][7]->Fill(2.0,TS2[n]);
                    pEM_TSDist[2][7]->Fill(3.0,TS3[n]);
                    pEM_TSDist[2][7]->Fill(4.0,TS4[n]);
                    pEM_TSDist[2][7]->Fill(5.0,TS5[n]);

                    pEM_ratio[2][7] = TS2[n] / TS3[n];
                    pEM_RatioDist[2][7]->Fill(pEM_ratio[2][7]);

                    pEM_sig[2][7] = TS2[n] - TS1[n];

                    pEM_fCDist[2][7]->Fill(pEM_sig[2][7]);
                }
                if (channel[n] == 4)
                {
                    pEM_TSDist[3][7]->Fill(0.0,TS0[n]);
                    pEM_TSDist[3][7]->Fill(1.0,TS1[n]);
                    pEM_TSDist[3][7]->Fill(2.0,TS2[n]);
                    pEM_TSDist[3][7]->Fill(3.0,TS3[n]);
                    pEM_TSDist[3][7]->Fill(4.0,TS4[n]);
                    pEM_TSDist[3][7]->Fill(5.0,TS5[n]);

                    pEM_ratio[3][7] = TS2[n] / TS3[n];
                    pEM_RatioDist[3][7]->Fill(pEM_ratio[3][7]);

                    pEM_sig[3][7] = TS2[n] - TS1[n];

                    pEM_fCDist[3][7]->Fill(pEM_sig[3][7]);
                }
                if (channel[n] == 5)
                {
                    pEM_TSDist[4][7]->Fill(0.0,TS0[n]);
                    pEM_TSDist[4][7]->Fill(1.0,TS1[n]);
                    pEM_TSDist[4][7]->Fill(2.0,TS2[n]);
                    pEM_TSDist[4][7]->Fill(3.0,TS3[n]);
                    pEM_TSDist[4][7]->Fill(4.0,TS4[n]);
                    pEM_TSDist[4][7]->Fill(5.0,TS5[n]);

                    pEM_ratio[4][7] = TS2[n] / TS3[n];
                    pEM_RatioDist[4][7]->Fill(pEM_ratio[4][7]);

                    pEM_sig[4][7] = TS2[n] - TS1[n];

                    pEM_fCDist[4][7]->Fill(pEM_sig[4][7]);
                }
                pEM_sigtot[7] = pEM_sig[0][7] + pEM_sig[1][7] + pEM_sig[2][7] + pEM_sig[3][7] + pEM_sig[4][7];
            } // end pos em 60 - 70 cent
            
            if (zside[n] == 1 && section[n] == 2)
            {
                if (channel[n] == 1)
                {
                    pHAD_TSDist[0][7]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[0][7]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[0][7]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[0][7]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[0][7]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[0][7]->Fill(5.0,TS5[n]);

                    pHAD_ratio[0][7] = TS2[n] / TS3[n];
                    pHAD_RatioDist[0][7]->Fill(pHAD_ratio[0][7]);

                    pHAD_sig[0][7] = TS2[n] - TS1[n];

                    pHAD_fCDist[0][7]->Fill(pHAD_sig[0][7]);
                }
                if (channel[n] == 2)
                {
                    pHAD_TSDist[1][7]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[1][7]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[1][7]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[1][7]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[1][7]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[1][7]->Fill(5.0,TS5[n]);

                    pHAD_ratio[1][7] = TS2[n] / TS3[n];
                    pHAD_RatioDist[1][7]->Fill(pHAD_ratio[1][7]);

                    pHAD_sig[1][7] = TS2[n] - TS1[n];

                    pHAD_fCDist[1][7]->Fill(pHAD_sig[1][7]);
                }
                if (channel[n] == 3)
                {
                    pHAD_TSDist[2][7]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[2][7]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[2][7]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[2][7]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[2][7]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[2][7]->Fill(5.0,TS5[n]);

                    pHAD_ratio[2][7] = TS2[n] / TS3[n];
                    pHAD_RatioDist[2][7]->Fill(pHAD_ratio[2][7]);

                    pHAD_sig[2][7] = TS2[n] - TS1[n];

                    pHAD_fCDist[2][7]->Fill(pHAD_sig[2][7]);
                }
                if (channel[n] == 4)
                {
                    pHAD_TSDist[3][7]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[3][7]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[3][7]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[3][7]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[3][7]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[3][7]->Fill(5.0,TS5[n]);

                    pHAD_ratio[3][7] = TS2[n] / TS3[n];
                    pHAD_RatioDist[3][7]->Fill(pHAD_ratio[3][7]);

                    pHAD_sig[3][7] = TS2[n] - TS1[n];

                    pHAD_fCDist[3][7]->Fill(pHAD_sig[3][7]);
                }
                pHAD_sigtot[7] = pHAD_sig[0][7] + pHAD_sig[1][7] + pHAD_sig[2][7] + pHAD_sig[3][7];
            } // end of pos had 60-70 cent
            ZDC[7] = 0.1 * pEM_sigtot[7] + pHAD_sigtot[7];
        } // end of 60 - 70 cent 

        /*pos ZDC 70 - 80 cent analysis*/
        if (hibin >= 140 && hibin < 160)
            {
            if (zside[n] == 1 && section[n] == 4)
            {
                if (channel[n] == 1)
                {
                    pRPD_TSDist[10][8]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[10][8]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[10][8]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[10][8]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[10][8]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[10][8]->Fill(5.0,TS5[n]);

                    pRPD_ratio[10][8] = TS2[n] / TS3[n];
                    pRPD_RatioDist[10][8]->Fill(pRPD_ratio[10][8]);

                    if (pRPD_ratio[10][8] > 1.1893 && pRPD_ratio[10][8] < 1.8067)
                    {
                        pRPD_sig[10][8] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[10][8]->Fill(pRPD_sig[10][8]);
                }
                if (channel[n] == 2)                                                                                                
                {
                    pRPD_TSDist[6][8]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[6][8]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[6][8]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[6][8]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[6][8]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[6][8]->Fill(5.0,TS5[n]);

                    pRPD_ratio[6][8] = TS2[n] / TS3[n];
                    pRPD_RatioDist[6][8]->Fill(pRPD_ratio[6][8]);

                    if (pRPD_ratio[6][8] > 1.2832 && pRPD_ratio[6][8] < 1.8688)
                    {
                        pRPD_sig[6][8] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[6][8]->Fill(pRPD_sig[6][8]);
                }
                if (channel[n] == 3)
                {
                    pRPD_TSDist[2][8]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[2][8]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[2][8]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[2][8]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[2][8]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[2][8]->Fill(5.0,TS5[n]);

                    pRPD_ratio[2][8] = TS2[n] / TS3[n];
                    pRPD_RatioDist[2][8]->Fill(pRPD_ratio[2][8]);

                    if (pRPD_ratio[2][8] > 1.8 && pRPD_ratio[2][8] < 2.2)
                    {
                        pRPD_sig[2][8] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[2][8]->Fill(pRPD_sig[2][8]);
                }
                if (channel[n] == 4)
                {
                    pRPD_TSDist[14][8]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[14][8]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[14][8]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[14][8]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[14][8]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[14][8]->Fill(5.0,TS5[n]);

                    pRPD_ratio[14][8] = TS2[n] / TS3[n];
                    pRPD_RatioDist[14][8]->Fill(pRPD_ratio[14][8]);

                    if (pRPD_ratio[14][8] > 1.1645 && pRPD_ratio[14][8] < 1.8515)
                    {
                        pRPD_sig[14][8] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[14][8]->Fill(pRPD_sig[14][8]);
                }
                if (channel[n] == 5)
                {
                    pRPD_TSDist[11][8]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[11][8]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[11][8]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[11][8]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[11][8]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[11][8]->Fill(5.0,TS5[n]);

                    pRPD_ratio[11][8] = TS2[n] / TS3[n];
                    pRPD_RatioDist[11][8]->Fill(pRPD_ratio[11][8]);

                    if (pRPD_ratio[11][8] > 1.2069 && pRPD_ratio[11][8] < 1.8411)
                    {
                        pRPD_sig[11][8] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[11][8]->Fill(pRPD_sig[11][8]);
                }
                if (channel[n] == 6)
                {
                    pRPD_TSDist[7][8]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[7][8]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[7][8]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[7][8]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[7][8]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[7][8]->Fill(5.0,TS5[n]);

                    pRPD_ratio[7][8] = TS2[n] / TS3[n];
                    pRPD_RatioDist[7][8]->Fill(pRPD_ratio[7][8]);

                    if (pRPD_ratio[7][8] > 1.4011 && pRPD_ratio[7][8] < 2.0589)
                    {
                        pRPD_sig[7][8] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[7][8]->Fill(pRPD_sig[7][8]);
                }
                if (channel[n] == 7)
                {
                    pRPD_TSDist[3][8]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[3][8]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[3][8]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[3][8]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[3][8]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[3][8]->Fill(5.0,TS5[n]);

                    pRPD_ratio[3][8] = TS2[n] / TS3[n];
                    pRPD_RatioDist[3][8]->Fill(pRPD_ratio[3][8]);

                    if (pRPD_ratio[3][8] > 1.4039 && pRPD_ratio[3][8] < 2.0881)
                    {
                        pRPD_sig[3][8] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[3][8]->Fill(pRPD_sig[3][8]);
                }
                if (channel[n] == 8)
                {
                    pRPD_TSDist[15][8]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[15][8]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[15][8]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[15][8]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[15][8]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[15][8]->Fill(5.0,TS5[n]);

                    pRPD_ratio[15][8] = TS2[n] / TS3[n];
                    pRPD_RatioDist[15][8]->Fill(pRPD_ratio[15][8]);

                    if (pRPD_ratio[15][8] > 1.1942 && pRPD_ratio[15][8] < 1.9038)
                    {
                        pRPD_sig[15][8] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[15][8]->Fill(pRPD_sig[15][8]);
                }
                if (channel[n] == 9)
                {
                    pRPD_TSDist[4][8]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[4][8]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[4][8]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[4][8]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[4][8]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[4][8]->Fill(5.0,TS5[n]);

                    pRPD_ratio[4][8] = TS2[n] / TS3[n];
                    pRPD_RatioDist[4][8]->Fill(pRPD_ratio[4][8]);

                    if (pRPD_ratio[4][8] > 1.252 && pRPD_ratio[4][8] < 2.268)
                    {
                        pRPD_sig[4][8] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[4][8]->Fill(pRPD_sig[4][8]);
                }
                if (channel[n] == 10)
                {
                    pRPD_TSDist[8][8]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[8][8]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[8][8]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[8][8]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[8][8]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[8][8]->Fill(5.0,TS5[n]);

                    pRPD_ratio[8][8] = TS2[n] / TS3[n];
                    pRPD_RatioDist[8][8]->Fill(pRPD_ratio[8][8]);

                    if (pRPD_ratio[8][8] > 1.2955 && pRPD_ratio[8][8] < 2.1905)
                    {
                        pRPD_sig[8][8] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[8][8]->Fill(pRPD_sig[8][8]);
                }
                if (channel[n] == 11)
                {
                    pRPD_TSDist[12][8]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[12][8]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[12][8]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[12][8]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[12][8]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[12][8]->Fill(5.0,TS5[n]);

                    pRPD_ratio[12][8] = TS2[n] / TS3[n];
                    pRPD_RatioDist[12][8]->Fill(pRPD_ratio[12][8]);

                    if (pRPD_ratio[12][8] > 1.2688 && pRPD_ratio[12][8] < 2.1392)
                    {
                        pRPD_sig[12][8] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[12][8]->Fill(pRPD_sig[12][8]);
                }
                if (channel[n] == 12)
                {
                    pRPD_TSDist[0][8]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[0][8]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[0][8]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[0][8]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[0][8]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[0][8]->Fill(5.0,TS5[n]);

                    pRPD_ratio[0][8] = TS2[n] / TS3[n];
                    pRPD_RatioDist[0][8]->Fill(pRPD_ratio[0][8]);

                    if (pRPD_ratio[0][8] > 1.2082 && pRPD_ratio[0][8] < 2.2878)
                    {
                        pRPD_sig[0][8] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[0][8]->Fill(pRPD_sig[0][8]);
                }
                if (channel[n] == 13)
                {
                    pRPD_TSDist[5][8]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[5][8]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[5][8]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[5][8]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[5][8]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[5][8]->Fill(5.0,TS5[n]);

                    pRPD_ratio[5][8] = TS2[n] / TS3[n];
                    pRPD_RatioDist[5][8]->Fill(pRPD_ratio[5][8]);

                    if (pRPD_ratio[5][8] > 1.6077 && pRPD_ratio[5][8] < 2.5083)
                    {
                        pRPD_sig[5][8] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[5][8]->Fill(pRPD_sig[5][8]);
                }
                if (channel[n] == 14)
                {
                    pRPD_TSDist[9][8]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[9][8]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[9][8]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[9][8]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[9][8]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[9][8]->Fill(5.0,TS5[n]);

                    pRPD_ratio[9][8] = TS2[n] / TS3[n];
                    pRPD_RatioDist[9][8]->Fill(pRPD_ratio[9][8]);

                    if (pRPD_ratio[9][8] > 1.5316 && pRPD_ratio[9][8] < 2.4484)
                    {
                        pRPD_sig[9][8] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[9][8]->Fill(pRPD_sig[9][8]);
                }
                if (channel[n] == 15)
                {
                    pRPD_TSDist[13][8]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[13][8]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[13][8]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[13][8]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[13][8]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[13][8]->Fill(5.0,TS5[n]);

                    pRPD_ratio[13][8] = TS2[n] / TS3[n];
                    pRPD_RatioDist[13][8]->Fill(pRPD_ratio[13][8]);

                    if (pRPD_ratio[13][8] > 1.4921 && pRPD_ratio[13][8] < 2.2959)
                    {
                        pRPD_sig[13][8] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[13][8]->Fill(pRPD_sig[13][8]);
                }
                if (channel[n] == 16)
                {
                    pRPD_TSDist[1][8]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[1][8]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[1][8]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[1][8]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[1][8]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[1][8]->Fill(5.0,TS5[n]);

                    pRPD_ratio[1][8] = TS2[n] / TS3[n];
                    pRPD_RatioDist[1][8]->Fill(pRPD_ratio[1][8]);

                    if (pRPD_ratio[1][8] > 1.5232 && pRPD_ratio[1][8] < 2.5228)
                    {
                        pRPD_sig[1][8] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[1][8]->Fill(pRPD_sig[1][8]);
                }
            } // end pos RPD 70 - 80 cent 
            if (zside[n] == 1 && section[n] == 1)
            {
                if (channel[n] == 1)
                {
                    pEM_TSDist[0][8]->Fill(0.0,TS0[n]);
                    pEM_TSDist[0][8]->Fill(1.0,TS1[n]);
                    pEM_TSDist[0][8]->Fill(2.0,TS2[n]);
                    pEM_TSDist[0][8]->Fill(3.0,TS3[n]);
                    pEM_TSDist[0][8]->Fill(4.0,TS4[n]);
                    pEM_TSDist[0][8]->Fill(5.0,TS5[n]);

                    pEM_ratio[0][8] = TS2[n] / TS3[n];
                    pEM_RatioDist[0][8]->Fill(pEM_ratio[0][8]);

                    pEM_sig[0][8] = TS2[n] - TS1[n];

                    pEM_fCDist[0][8]->Fill(pEM_sig[0][8]);
                }
                if (channel[n] == 2)
                {
                    pEM_TSDist[1][8]->Fill(0.0,TS0[n]);
                    pEM_TSDist[1][8]->Fill(1.0,TS1[n]);
                    pEM_TSDist[1][8]->Fill(2.0,TS2[n]);
                    pEM_TSDist[1][8]->Fill(3.0,TS3[n]);
                    pEM_TSDist[1][8]->Fill(4.0,TS4[n]);
                    pEM_TSDist[1][8]->Fill(5.0,TS5[n]);

                    pEM_ratio[1][8] = TS2[n] / TS3[n];
                    pEM_RatioDist[1][8]->Fill(pEM_ratio[1][8]);

                    pEM_sig[1][8] = TS2[n] - TS1[n];

                    pEM_fCDist[1][8]->Fill(pEM_sig[1][8]);
                }
                if (channel[n] == 3)
                {
                    pEM_TSDist[2][8]->Fill(0.0,TS0[n]);
                    pEM_TSDist[2][8]->Fill(1.0,TS1[n]);
                    pEM_TSDist[2][8]->Fill(2.0,TS2[n]);
                    pEM_TSDist[2][8]->Fill(3.0,TS3[n]);
                    pEM_TSDist[2][8]->Fill(4.0,TS4[n]);
                    pEM_TSDist[2][8]->Fill(5.0,TS5[n]);

                    pEM_ratio[2][8] = TS2[n] / TS3[n];
                    pEM_RatioDist[2][8]->Fill(pEM_ratio[2][8]);

                    pEM_sig[2][8] = TS2[n] - TS1[n];

                    pEM_fCDist[2][8]->Fill(pEM_sig[2][8]);
                }
                if (channel[n] == 4)
                {
                    pEM_TSDist[3][8]->Fill(0.0,TS0[n]);
                    pEM_TSDist[3][8]->Fill(1.0,TS1[n]);
                    pEM_TSDist[3][8]->Fill(2.0,TS2[n]);
                    pEM_TSDist[3][8]->Fill(3.0,TS3[n]);
                    pEM_TSDist[3][8]->Fill(4.0,TS4[n]);
                    pEM_TSDist[3][8]->Fill(5.0,TS5[n]);

                    pEM_ratio[3][8] = TS2[n] / TS3[n];
                    pEM_RatioDist[3][8]->Fill(pEM_ratio[3][8]);

                    pEM_sig[3][8] = TS2[n] - TS1[n];

                    pEM_fCDist[3][8]->Fill(pEM_sig[3][8]);
                }
                if (channel[n] == 5)
                {
                    pEM_TSDist[4][8]->Fill(0.0,TS0[n]);
                    pEM_TSDist[4][8]->Fill(1.0,TS1[n]);
                    pEM_TSDist[4][8]->Fill(2.0,TS2[n]);
                    pEM_TSDist[4][8]->Fill(3.0,TS3[n]);
                    pEM_TSDist[4][8]->Fill(4.0,TS4[n]);
                    pEM_TSDist[4][8]->Fill(5.0,TS5[n]);

                    pEM_ratio[4][8] = TS2[n] / TS3[n];
                    pEM_RatioDist[4][8]->Fill(pEM_ratio[4][8]);

                    pEM_sig[4][8] = TS2[n] - TS1[n];

                    pEM_fCDist[4][8]->Fill(pEM_sig[4][8]);
                }
                pEM_sigtot[8] = pEM_sig[0][8] + pEM_sig[1][8] + pEM_sig[2][8] + pEM_sig[3][8] + pEM_sig[4][8];
            } // end pos em 70 - 80 cent
            
            if (zside[n] == 1 && section[n] == 2)
            {
                if (channel[n] == 1)
                {
                    pHAD_TSDist[0][8]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[0][8]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[0][8]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[0][8]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[0][8]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[0][8]->Fill(5.0,TS5[n]);

                    pHAD_ratio[0][8] = TS2[n] / TS3[n];
                    pHAD_RatioDist[0][8]->Fill(pHAD_ratio[0][8]);

                    pHAD_sig[0][8] = TS2[n] - TS1[n];

                    pHAD_fCDist[0][8]->Fill(pHAD_sig[0][8]);
                }
                if (channel[n] == 2)
                {
                    pHAD_TSDist[1][8]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[1][8]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[1][8]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[1][8]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[1][8]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[1][8]->Fill(5.0,TS5[n]);

                    pHAD_ratio[1][8] = TS2[n] / TS3[n];
                    pHAD_RatioDist[1][8]->Fill(pHAD_ratio[1][8]);

                    pHAD_sig[1][8] = TS2[n] - TS1[n];

                    pHAD_fCDist[1][8]->Fill(pHAD_sig[1][8]);
                }
                if (channel[n] == 3)
                {
                    pHAD_TSDist[2][8]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[2][8]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[2][8]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[2][8]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[2][8]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[2][8]->Fill(5.0,TS5[n]);

                    pHAD_ratio[2][8] = TS2[n] / TS3[n];
                    pHAD_RatioDist[2][8]->Fill(pHAD_ratio[2][8]);

                    pHAD_sig[2][8] = TS2[n] - TS1[n];

                    pHAD_fCDist[2][8]->Fill(pHAD_sig[2][8]);
                }
                if (channel[n] == 4)
                {
                    pHAD_TSDist[3][8]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[3][8]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[3][8]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[3][8]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[3][8]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[3][8]->Fill(5.0,TS5[n]);

                    pHAD_ratio[3][8] = TS2[n] / TS3[n];
                    pHAD_RatioDist[3][8]->Fill(pHAD_ratio[3][8]);

                    pHAD_sig[3][8] = TS2[n] - TS1[n];

                    pHAD_fCDist[3][8]->Fill(pHAD_sig[3][8]);
                }
                pHAD_sigtot[8] = pHAD_sig[0][8] + pHAD_sig[1][8] + pHAD_sig[2][8] + pHAD_sig[3][8];
            } // end of pos had 70-80 cent
            ZDC[8] = 0.1 * pEM_sigtot[8] + pHAD_sigtot[8];
        } // end of 70 - 80 cent 

        /*pos ZDC 80 - 90 cent analysis*/
        if (hibin >= 160 && hibin < 180)
            {
            if (zside[n] == 1 && section[n] == 4)
            {
                if (channel[n] == 1)
                {
                    pRPD_TSDist[10][9]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[10][9]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[10][9]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[10][9]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[10][9]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[10][9]->Fill(5.0,TS5[n]);

                    pRPD_ratio[10][9] = TS2[n] / TS3[n];
                    pRPD_RatioDist[10][9]->Fill(pRPD_ratio[10][9]);

                    if (pRPD_ratio[10][9] > 1.1893 && pRPD_ratio[10][9] < 1.8067)
                    {
                        pRPD_sig[10][9] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[10][9]->Fill(pRPD_sig[10][9]);
                }
                if (channel[n] == 2)                                                                                                
                {
                    pRPD_TSDist[6][9]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[6][9]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[6][9]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[6][9]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[6][9]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[6][9]->Fill(5.0,TS5[n]);

                    pRPD_ratio[6][9] = TS2[n] / TS3[n];
                    pRPD_RatioDist[6][9]->Fill(pRPD_ratio[6][9]);

                    if (pRPD_ratio[6][9] > 1.2832 && pRPD_ratio[6][9] < 1.8688)
                    {
                        pRPD_sig[6][9] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[6][9]->Fill(pRPD_sig[6][9]);
                }
                if (channel[n] == 3)
                {
                    pRPD_TSDist[2][9]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[2][9]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[2][9]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[2][9]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[2][9]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[2][9]->Fill(5.0,TS5[n]);

                    pRPD_ratio[2][9] = TS2[n] / TS3[n];
                    pRPD_RatioDist[2][9]->Fill(pRPD_ratio[2][9]);

                    if (pRPD_ratio[2][9] > 1.8 && pRPD_ratio[2][9] < 2.2)
                    {
                        pRPD_sig[2][9] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[2][9]->Fill(pRPD_sig[2][9]);
                }
                if (channel[n] == 4)
                {
                    pRPD_TSDist[14][9]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[14][9]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[14][9]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[14][9]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[14][9]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[14][9]->Fill(5.0,TS5[n]);

                    pRPD_ratio[14][9] = TS2[n] / TS3[n];
                    pRPD_RatioDist[14][9]->Fill(pRPD_ratio[14][9]);

                    if (pRPD_ratio[14][9] > 1.1645 && pRPD_ratio[14][9] < 1.8515)
                    {
                        pRPD_sig[14][9] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[14][9]->Fill(pRPD_sig[14][9]);
                }
                if (channel[n] == 5)
                {
                    pRPD_TSDist[11][9]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[11][9]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[11][9]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[11][9]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[11][9]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[11][9]->Fill(5.0,TS5[n]);

                    pRPD_ratio[11][9] = TS2[n] / TS3[n];
                    pRPD_RatioDist[11][9]->Fill(pRPD_ratio[11][9]);

                    if (pRPD_ratio[11][9] > 1.2069 && pRPD_ratio[11][9] < 1.8411)
                    {
                        pRPD_sig[11][9] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[11][9]->Fill(pRPD_sig[11][9]);
                }
                if (channel[n] == 6)
                {
                    pRPD_TSDist[7][9]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[7][9]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[7][9]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[7][9]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[7][9]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[7][9]->Fill(5.0,TS5[n]);

                    pRPD_ratio[7][9] = TS2[n] / TS3[n];
                    pRPD_RatioDist[7][9]->Fill(pRPD_ratio[7][9]);

                    if (pRPD_ratio[7][9] > 1.4011 && pRPD_ratio[7][9] < 2.0589)
                    {
                        pRPD_sig[7][9] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[7][9]->Fill(pRPD_sig[7][9]);
                }
                if (channel[n] == 7)
                {
                    pRPD_TSDist[3][9]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[3][9]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[3][9]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[3][9]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[3][9]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[3][9]->Fill(5.0,TS5[n]);

                    pRPD_ratio[3][9] = TS2[n] / TS3[n];
                    pRPD_RatioDist[3][9]->Fill(pRPD_ratio[3][9]);

                    if (pRPD_ratio[3][9] > 1.4039 && pRPD_ratio[3][9] < 2.0881)
                    {
                        pRPD_sig[3][9] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[3][9]->Fill(pRPD_sig[3][9]);
                }
                if (channel[n] == 8)
                {
                    pRPD_TSDist[15][9]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[15][9]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[15][9]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[15][9]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[15][9]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[15][9]->Fill(5.0,TS5[n]);

                    pRPD_ratio[15][9] = TS2[n] / TS3[n];
                    pRPD_RatioDist[15][9]->Fill(pRPD_ratio[15][9]);

                    if (pRPD_ratio[15][9] > 1.1942 && pRPD_ratio[15][9] < 1.9038)
                    {
                        pRPD_sig[15][9] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[15][9]->Fill(pRPD_sig[15][9]);
                }
                if (channel[n] == 9)
                {
                    pRPD_TSDist[4][9]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[4][9]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[4][9]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[4][9]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[4][9]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[4][9]->Fill(5.0,TS5[n]);

                    pRPD_ratio[4][9] = TS2[n] / TS3[n];
                    pRPD_RatioDist[4][9]->Fill(pRPD_ratio[4][9]);

                    if (pRPD_ratio[4][9] > 1.252 && pRPD_ratio[4][9] < 2.268)
                    {
                        pRPD_sig[4][9] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[4][9]->Fill(pRPD_sig[4][9]);
                }
                if (channel[n] == 10)
                {
                    pRPD_TSDist[8][9]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[8][9]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[8][9]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[8][9]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[8][9]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[8][9]->Fill(5.0,TS5[n]);

                    pRPD_ratio[8][9] = TS2[n] / TS3[n];
                    pRPD_RatioDist[8][9]->Fill(pRPD_ratio[8][9]);

                    if (pRPD_ratio[8][9] > 1.2955 && pRPD_ratio[8][9] < 2.1905)
                    {
                        pRPD_sig[8][9] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[8][9]->Fill(pRPD_sig[8][9]);
                }
                if (channel[n] == 11)
                {
                    pRPD_TSDist[12][9]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[12][9]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[12][9]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[12][9]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[12][9]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[12][9]->Fill(5.0,TS5[n]);

                    pRPD_ratio[12][9] = TS2[n] / TS3[n];
                    pRPD_RatioDist[12][9]->Fill(pRPD_ratio[12][9]);

                    if (pRPD_ratio[12][9] > 1.2688 && pRPD_ratio[12][9] < 2.1392)
                    {
                        pRPD_sig[12][9] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[12][9]->Fill(pRPD_sig[12][9]);
                }
                if (channel[n] == 12)
                {
                    pRPD_TSDist[0][9]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[0][9]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[0][9]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[0][9]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[0][9]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[0][9]->Fill(5.0,TS5[n]);

                    pRPD_ratio[0][9] = TS2[n] / TS3[n];
                    pRPD_RatioDist[0][9]->Fill(pRPD_ratio[0][9]);

                    if (pRPD_ratio[0][9] > 1.2082 && pRPD_ratio[0][9] < 2.2878)
                    {
                        pRPD_sig[0][9] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[0][9]->Fill(pRPD_sig[0][9]);
                }
                if (channel[n] == 13)
                {
                    pRPD_TSDist[5][9]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[5][9]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[5][9]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[5][9]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[5][9]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[5][9]->Fill(5.0,TS5[n]);

                    pRPD_ratio[5][9] = TS2[n] / TS3[n];
                    pRPD_RatioDist[5][9]->Fill(pRPD_ratio[5][9]);

                    if (pRPD_ratio[5][9] > 1.6077 && pRPD_ratio[5][9] < 2.5083)
                    {
                        pRPD_sig[5][9] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[5][9]->Fill(pRPD_sig[5][9]);
                }
                if (channel[n] == 14)
                {
                    pRPD_TSDist[9][9]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[9][9]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[9][9]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[9][9]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[9][9]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[9][9]->Fill(5.0,TS5[n]);

                    pRPD_ratio[9][9] = TS2[n] / TS3[n];
                    pRPD_RatioDist[9][9]->Fill(pRPD_ratio[9][9]);

                    if (pRPD_ratio[9][9] > 1.5316 && pRPD_ratio[9][9] < 2.4484)
                    {
                        pRPD_sig[9][9] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[9][9]->Fill(pRPD_sig[9][9]);
                }
                if (channel[n] == 15)
                {
                    pRPD_TSDist[13][9]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[13][9]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[13][9]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[13][9]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[13][9]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[13][9]->Fill(5.0,TS5[n]);

                    pRPD_ratio[13][9] = TS2[n] / TS3[n];
                    pRPD_RatioDist[13][9]->Fill(pRPD_ratio[13][9]);

                    if (pRPD_ratio[13][9] > 1.4921 && pRPD_ratio[13][9] < 2.2959)
                    {
                        pRPD_sig[13][9] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[13][9]->Fill(pRPD_sig[13][9]);
                }
                if (channel[n] == 16)
                {
                    pRPD_TSDist[1][9]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[1][9]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[1][9]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[1][9]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[1][9]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[1][9]->Fill(5.0,TS5[n]);

                    pRPD_ratio[1][9] = TS2[n] / TS3[n];
                    pRPD_RatioDist[1][9]->Fill(pRPD_ratio[1][9]);

                    if (pRPD_ratio[1][9] > 1.5232 && pRPD_ratio[1][9] < 2.5228)
                    {
                        pRPD_sig[1][9] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[1][9]->Fill(pRPD_sig[1][9]);
                }
            } // end pos RPD 80 - 90 cent 
            if (zside[n] == 1 && section[n] == 1)
            {
                if (channel[n] == 1)
                {
                    pEM_TSDist[0][9]->Fill(0.0,TS0[n]);
                    pEM_TSDist[0][9]->Fill(1.0,TS1[n]);
                    pEM_TSDist[0][9]->Fill(2.0,TS2[n]);
                    pEM_TSDist[0][9]->Fill(3.0,TS3[n]);
                    pEM_TSDist[0][9]->Fill(4.0,TS4[n]);
                    pEM_TSDist[0][9]->Fill(5.0,TS5[n]);

                    pEM_ratio[0][9] = TS2[n] / TS3[n];
                    pEM_RatioDist[0][9]->Fill(pEM_ratio[0][9]);

                    pEM_sig[0][9] = TS2[n] - TS1[n];

                    pEM_fCDist[0][9]->Fill(pEM_sig[0][9]);
                }
                if (channel[n] == 2)
                {
                    pEM_TSDist[1][9]->Fill(0.0,TS0[n]);
                    pEM_TSDist[1][9]->Fill(1.0,TS1[n]);
                    pEM_TSDist[1][9]->Fill(2.0,TS2[n]);
                    pEM_TSDist[1][9]->Fill(3.0,TS3[n]);
                    pEM_TSDist[1][9]->Fill(4.0,TS4[n]);
                    pEM_TSDist[1][9]->Fill(5.0,TS5[n]);

                    pEM_ratio[1][9] = TS2[n] / TS3[n];
                    pEM_RatioDist[1][9]->Fill(pEM_ratio[1][9]);

                    pEM_sig[1][9] = TS2[n] - TS1[n];

                    pEM_fCDist[1][9]->Fill(pEM_sig[1][9]);
                }
                if (channel[n] == 3)
                {
                    pEM_TSDist[2][9]->Fill(0.0,TS0[n]);
                    pEM_TSDist[2][9]->Fill(1.0,TS1[n]);
                    pEM_TSDist[2][9]->Fill(2.0,TS2[n]);
                    pEM_TSDist[2][9]->Fill(3.0,TS3[n]);
                    pEM_TSDist[2][9]->Fill(4.0,TS4[n]);
                    pEM_TSDist[2][9]->Fill(5.0,TS5[n]);

                    pEM_ratio[2][9] = TS2[n] / TS3[n];
                    pEM_RatioDist[2][9]->Fill(pEM_ratio[2][9]);

                    pEM_sig[2][9] = TS2[n] - TS1[n];

                    pEM_fCDist[2][9]->Fill(pEM_sig[2][9]);
                }
                if (channel[n] == 4)
                {
                    pEM_TSDist[3][9]->Fill(0.0,TS0[n]);
                    pEM_TSDist[3][9]->Fill(1.0,TS1[n]);
                    pEM_TSDist[3][9]->Fill(2.0,TS2[n]);
                    pEM_TSDist[3][9]->Fill(3.0,TS3[n]);
                    pEM_TSDist[3][9]->Fill(4.0,TS4[n]);
                    pEM_TSDist[3][9]->Fill(5.0,TS5[n]);

                    pEM_ratio[3][9] = TS2[n] / TS3[n];
                    pEM_RatioDist[3][9]->Fill(pEM_ratio[3][9]);

                    pEM_sig[3][9] = TS2[n] - TS1[n];

                    pEM_fCDist[3][9]->Fill(pEM_sig[3][9]);
                }
                if (channel[n] == 5)
                {
                    pEM_TSDist[4][9]->Fill(0.0,TS0[n]);
                    pEM_TSDist[4][9]->Fill(1.0,TS1[n]);
                    pEM_TSDist[4][9]->Fill(2.0,TS2[n]);
                    pEM_TSDist[4][9]->Fill(3.0,TS3[n]);
                    pEM_TSDist[4][9]->Fill(4.0,TS4[n]);
                    pEM_TSDist[4][9]->Fill(5.0,TS5[n]);

                    pEM_ratio[4][9] = TS2[n] / TS3[n];
                    pEM_RatioDist[4][9]->Fill(pEM_ratio[4][9]);

                    pEM_sig[4][9] = TS2[n] - TS1[n];

                    pEM_fCDist[4][9]->Fill(pEM_sig[4][9]);
                }
                pEM_sigtot[9] = pEM_sig[0][9] + pEM_sig[1][9] + pEM_sig[2][9] + pEM_sig[3][9] + pEM_sig[4][9];
            } // end pos em 80 - 90 cent
            
            if (zside[n] == 1 && section[n] == 2)
            {
                if (channel[n] == 1)
                {
                    pHAD_TSDist[0][9]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[0][9]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[0][9]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[0][9]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[0][9]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[0][9]->Fill(5.0,TS5[n]);

                    pHAD_ratio[0][9] = TS2[n] / TS3[n];
                    pHAD_RatioDist[0][9]->Fill(pHAD_ratio[0][9]);

                    pHAD_sig[0][9] = TS2[n] - TS1[n];

                    pHAD_fCDist[0][9]->Fill(pHAD_sig[0][9]);
                }
                if (channel[n] == 2)
                {
                    pHAD_TSDist[1][9]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[1][9]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[1][9]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[1][9]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[1][9]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[1][9]->Fill(5.0,TS5[n]);

                    pHAD_ratio[1][9] = TS2[n] / TS3[n];
                    pHAD_RatioDist[1][9]->Fill(pHAD_ratio[1][9]);

                    pHAD_sig[1][9] = TS2[n] - TS1[n];

                    pHAD_fCDist[1][9]->Fill(pHAD_sig[1][9]);
                }
                if (channel[n] == 3)
                {
                    pHAD_TSDist[2][9]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[2][9]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[2][9]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[2][9]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[2][9]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[2][9]->Fill(5.0,TS5[n]);

                    pHAD_ratio[2][9] = TS2[n] / TS3[n];
                    pHAD_RatioDist[2][9]->Fill(pHAD_ratio[2][9]);

                    pHAD_sig[2][9] = TS2[n] - TS1[n];

                    pHAD_fCDist[2][9]->Fill(pHAD_sig[2][9]);
                }
                if (channel[n] == 4)
                {
                    pHAD_TSDist[3][9]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[3][9]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[3][9]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[3][9]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[3][9]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[3][9]->Fill(5.0,TS5[n]);

                    pHAD_ratio[3][9] = TS2[n] / TS3[n];
                    pHAD_RatioDist[3][9]->Fill(pHAD_ratio[3][9]);

                    pHAD_sig[3][9] = TS2[n] - TS1[n];

                    pHAD_fCDist[3][9]->Fill(pHAD_sig[3][9]);
                }
                pHAD_sigtot[9] = pHAD_sig[0][9] + pHAD_sig[1][9] + pHAD_sig[2][9] + pHAD_sig[3][9];
            } // end of pos had 80-90 cent
            ZDC[9] = 0.1 * pEM_sigtot[9] + pHAD_sigtot[9];
        } // end of 80 - 90 cent 

        /*pos ZDC 90 - 100 cent analysis*/
        if (hibin >= 180 && hibin <= 200)
            {
            if (zside[n] == 1 && section[n] == 4)
            {
                if (channel[n] == 1)
                {
                    pRPD_TSDist[10][10]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[10][10]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[10][10]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[10][10]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[10][10]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[10][10]->Fill(5.0,TS5[n]);

                    pRPD_ratio[10][10] = TS2[n] / TS3[n];
                    pRPD_RatioDist[10][10]->Fill(pRPD_ratio[10][10]);

                    if (pRPD_ratio[10][10] > 1.1893 && pRPD_ratio[10][10] < 1.8067)
                    {
                        pRPD_sig[10][10] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[10][10]->Fill(pRPD_sig[10][10]);
                }
                if (channel[n] == 2)                                                                                                
                {
                    pRPD_TSDist[6][10]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[6][10]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[6][10]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[6][10]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[6][10]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[6][10]->Fill(5.0,TS5[n]);

                    pRPD_ratio[6][10] = TS2[n] / TS3[n];
                    pRPD_RatioDist[6][10]->Fill(pRPD_ratio[6][10]);

                    if (pRPD_ratio[6][10] > 1.2832 && pRPD_ratio[6][10] < 1.8688)
                    {
                        pRPD_sig[6][10] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[6][10]->Fill(pRPD_sig[6][10]);
                }
                if (channel[n] == 3)
                {
                    pRPD_TSDist[2][10]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[2][10]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[2][10]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[2][10]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[2][10]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[2][10]->Fill(5.0,TS5[n]);

                    pRPD_ratio[2][10] = TS2[n] / TS3[n];
                    pRPD_RatioDist[2][10]->Fill(pRPD_ratio[2][10]);

                    if (pRPD_ratio[2][10] > 1.8 && pRPD_ratio[2][10] < 2.2)
                    {
                        pRPD_sig[2][10] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[2][10]->Fill(pRPD_sig[2][10]);
                }
                if (channel[n] == 4)
                {
                    pRPD_TSDist[14][10]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[14][10]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[14][10]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[14][10]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[14][10]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[14][10]->Fill(5.0,TS5[n]);

                    pRPD_ratio[14][10] = TS2[n] / TS3[n];
                    pRPD_RatioDist[14][10]->Fill(pRPD_ratio[14][10]);

                    if (pRPD_ratio[14][10] > 1.1645 && pRPD_ratio[14][10] < 1.8515)
                    {
                        pRPD_sig[14][10] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[14][10]->Fill(pRPD_sig[14][10]);
                }
                if (channel[n] == 5)
                {
                    pRPD_TSDist[11][10]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[11][10]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[11][10]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[11][10]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[11][10]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[11][10]->Fill(5.0,TS5[n]);

                    pRPD_ratio[11][10] = TS2[n] / TS3[n];
                    pRPD_RatioDist[11][10]->Fill(pRPD_ratio[11][10]);

                    if (pRPD_ratio[11][10] > 1.2069 && pRPD_ratio[11][10] < 1.8411)
                    {
                        pRPD_sig[11][10] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[11][10]->Fill(pRPD_sig[11][10]);
                }
                if (channel[n] == 6)
                {
                    pRPD_TSDist[7][10]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[7][10]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[7][10]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[7][10]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[7][10]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[7][10]->Fill(5.0,TS5[n]);

                    pRPD_ratio[7][10] = TS2[n] / TS3[n];
                    pRPD_RatioDist[7][10]->Fill(pRPD_ratio[7][10]);

                    if (pRPD_ratio[7][10] > 1.4011 && pRPD_ratio[7][10] < 2.0589)
                    {
                        pRPD_sig[7][10] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[7][10]->Fill(pRPD_sig[7][10]);
                }
                if (channel[n] == 7)
                {
                    pRPD_TSDist[3][10]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[3][10]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[3][10]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[3][10]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[3][10]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[3][10]->Fill(5.0,TS5[n]);

                    pRPD_ratio[3][10] = TS2[n] / TS3[n];
                    pRPD_RatioDist[3][10]->Fill(pRPD_ratio[3][10]);

                    if (pRPD_ratio[3][10] > 1.4039 && pRPD_ratio[3][10] < 2.0881)
                    {
                        pRPD_sig[3][10] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[3][10]->Fill(pRPD_sig[3][10]);
                }
                if (channel[n] == 8)
                {
                    pRPD_TSDist[15][10]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[15][10]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[15][10]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[15][10]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[15][10]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[15][10]->Fill(5.0,TS5[n]);

                    pRPD_ratio[15][10] = TS2[n] / TS3[n];
                    pRPD_RatioDist[15][10]->Fill(pRPD_ratio[15][10]);

                    if (pRPD_ratio[15][10] > 1.1942 && pRPD_ratio[15][10] < 1.9038)
                    {
                        pRPD_sig[15][10] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[15][10]->Fill(pRPD_sig[15][10]);
                }
                
                if (channel[n] == 9)
                {
                    pRPD_TSDist[4][10]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[4][10]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[4][10]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[4][10]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[4][10]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[4][10]->Fill(5.0,TS5[n]);

                    pRPD_ratio[4][10] = TS2[n] / TS3[n];
                    pRPD_RatioDist[4][10]->Fill(pRPD_ratio[4][10]);

                    if (pRPD_ratio[4][10] > 1.252 && pRPD_ratio[4][10] < 2.268)
                    {
                        pRPD_sig[4][10] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[4][10]->Fill(pRPD_sig[4][10]);
                }
                if (channel[n] == 10)
                {
                    pRPD_TSDist[8][10]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[8][10]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[8][10]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[8][10]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[8][10]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[8][10]->Fill(5.0,TS5[n]);

                    pRPD_ratio[8][10] = TS2[n] / TS3[n];
                    pRPD_RatioDist[8][10]->Fill(pRPD_ratio[8][10]);

                    if (pRPD_ratio[8][10] > 1.2955 && pRPD_ratio[8][10] < 2.1905)
                    {
                        pRPD_sig[8][10] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[8][10]->Fill(pRPD_sig[8][10]);
                }
                if (channel[n] == 11)
                {
                    pRPD_TSDist[12][10]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[12][10]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[12][10]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[12][10]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[12][10]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[12][10]->Fill(5.0,TS5[n]);

                    pRPD_ratio[12][10] = TS2[n] / TS3[n];
                    pRPD_RatioDist[12][10]->Fill(pRPD_ratio[12][10]);

                    if (pRPD_ratio[12][10] > 1.2688 && pRPD_ratio[12][10] < 2.1392)
                    {
                        pRPD_sig[12][10] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[12][10]->Fill(pRPD_sig[12][10]);
                }
                if (channel[n] == 12)
                {
                    pRPD_TSDist[0][10]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[0][10]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[0][10]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[0][10]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[0][10]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[0][10]->Fill(5.0,TS5[n]);

                    pRPD_ratio[0][10] = TS2[n] / TS3[n];
                    pRPD_RatioDist[0][10]->Fill(pRPD_ratio[0][10]);

                    if (pRPD_ratio[0][10] > 1.2082 && pRPD_ratio[0][10] < 2.2878)
                    {
                        pRPD_sig[0][10] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[0][10]->Fill(pRPD_sig[0][10]);
                }
                if (channel[n] == 13)
                {
                    pRPD_TSDist[5][10]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[5][10]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[5][10]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[5][10]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[5][10]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[5][10]->Fill(5.0,TS5[n]);

                    pRPD_ratio[5][10] = TS2[n] / TS3[n];
                    pRPD_RatioDist[5][10]->Fill(pRPD_ratio[5][10]);

                    if (pRPD_ratio[5][10] > 1.6077 && pRPD_ratio[5][10] < 2.5083)
                    {
                        pRPD_sig[5][10] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[5][10]->Fill(pRPD_sig[5][10]);
                }
                if (channel[n] == 14)
                {
                    pRPD_TSDist[9][10]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[9][10]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[9][10]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[9][10]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[9][10]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[9][10]->Fill(5.0,TS5[n]);

                    pRPD_ratio[9][10] = TS2[n] / TS3[n];
                    pRPD_RatioDist[9][10]->Fill(pRPD_ratio[9][10]);

                    if (pRPD_ratio[9][10] > 1.5316 && pRPD_ratio[9][10] < 2.4484)
                    {
                        pRPD_sig[9][10] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[9][10]->Fill(pRPD_sig[9][10]);
                }
                if (channel[n] == 15)
                {
                    pRPD_TSDist[13][10]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[13][10]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[13][10]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[13][10]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[13][10]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[13][10]->Fill(5.0,TS5[n]);

                    pRPD_ratio[13][10] = TS2[n] / TS3[n];
                    pRPD_RatioDist[13][10]->Fill(pRPD_ratio[13][10]);

                    if (pRPD_ratio[13][10] > 1.4921 && pRPD_ratio[13][10] < 2.2959)
                    {
                        pRPD_sig[13][10] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[13][10]->Fill(pRPD_sig[13][10]);
                }
                if (channel[n] == 16)
                {
                    pRPD_TSDist[1][10]->Fill(0.0,TS0[n]);
                    pRPD_TSDist[1][10]->Fill(1.0,TS1[n]);
                    pRPD_TSDist[1][10]->Fill(2.0,TS2[n]);
                    pRPD_TSDist[1][10]->Fill(3.0,TS3[n]);
                    pRPD_TSDist[1][10]->Fill(4.0,TS4[n]);
                    pRPD_TSDist[1][10]->Fill(5.0,TS5[n]);

                    pRPD_ratio[1][10] = TS2[n] / TS3[n];
                    pRPD_RatioDist[1][10]->Fill(pRPD_ratio[1][10]);

                    if (pRPD_ratio[1][10] > 1.5232 && pRPD_ratio[1][10] < 2.5228)
                    {
                        pRPD_sig[1][10] = TS2[n] - TS1[n];
                    }

                    pRPD_fCDist[1][10]->Fill(pRPD_sig[1][10]);
                }
            } // end pos RPD 90 - 100 cent 
            if (zside[n] == 1 && section[n] == 1)
            {
                if (channel[n] == 1)
                {
                    pEM_TSDist[0][10]->Fill(0.0,TS0[n]);
                    pEM_TSDist[0][10]->Fill(1.0,TS1[n]);
                    pEM_TSDist[0][10]->Fill(2.0,TS2[n]);
                    pEM_TSDist[0][10]->Fill(3.0,TS3[n]);
                    pEM_TSDist[0][10]->Fill(4.0,TS4[n]);
                    pEM_TSDist[0][10]->Fill(5.0,TS5[n]);

                    pEM_ratio[0][10] = TS2[n] / TS3[n];
                    pEM_RatioDist[0][10]->Fill(pEM_ratio[0][10]);

                    pEM_sig[0][10] = TS2[n] - TS1[n];

                    pEM_fCDist[0][10]->Fill(pEM_sig[0][10]);
                }
                if (channel[n] == 2)
                {
                    pEM_TSDist[1][10]->Fill(0.0,TS0[n]);
                    pEM_TSDist[1][10]->Fill(1.0,TS1[n]);
                    pEM_TSDist[1][10]->Fill(2.0,TS2[n]);
                    pEM_TSDist[1][10]->Fill(3.0,TS3[n]);
                    pEM_TSDist[1][10]->Fill(4.0,TS4[n]);
                    pEM_TSDist[1][10]->Fill(5.0,TS5[n]);

                    pEM_ratio[1][10] = TS2[n] / TS3[n];
                    pEM_RatioDist[1][10]->Fill(pEM_ratio[1][10]);

                    pEM_sig[1][10] = TS2[n] - TS1[n];

                    pEM_fCDist[1][10]->Fill(pEM_sig[1][10]);
                }
                if (channel[n] == 3)
                {
                    pEM_TSDist[2][10]->Fill(0.0,TS0[n]);
                    pEM_TSDist[2][10]->Fill(1.0,TS1[n]);
                    pEM_TSDist[2][10]->Fill(2.0,TS2[n]);
                    pEM_TSDist[2][10]->Fill(3.0,TS3[n]);
                    pEM_TSDist[2][10]->Fill(4.0,TS4[n]);
                    pEM_TSDist[2][10]->Fill(5.0,TS5[n]);

                    pEM_ratio[2][10] = TS2[n] / TS3[n];
                    pEM_RatioDist[2][10]->Fill(pEM_ratio[2][10]);

                    pEM_sig[2][10] = TS2[n] - TS1[n];

                    pEM_fCDist[2][10]->Fill(pEM_sig[2][10]);
                }
                if (channel[n] == 4)
                {
                    pEM_TSDist[3][10]->Fill(0.0,TS0[n]);
                    pEM_TSDist[3][10]->Fill(1.0,TS1[n]);
                    pEM_TSDist[3][10]->Fill(2.0,TS2[n]);
                    pEM_TSDist[3][10]->Fill(3.0,TS3[n]);
                    pEM_TSDist[3][10]->Fill(4.0,TS4[n]);
                    pEM_TSDist[3][10]->Fill(5.0,TS5[n]);

                    pEM_ratio[3][10] = TS2[n] / TS3[n];
                    pEM_RatioDist[3][10]->Fill(pEM_ratio[3][10]);

                    pEM_sig[3][10] = TS2[n] - TS1[n];

                    pEM_fCDist[3][10]->Fill(pEM_sig[3][10]);
                }
                if (channel[n] == 5)
                {
                    pEM_TSDist[4][10]->Fill(0.0,TS0[n]);
                    pEM_TSDist[4][10]->Fill(1.0,TS1[n]);
                    pEM_TSDist[4][10]->Fill(2.0,TS2[n]);
                    pEM_TSDist[4][10]->Fill(3.0,TS3[n]);
                    pEM_TSDist[4][10]->Fill(4.0,TS4[n]);
                    pEM_TSDist[4][10]->Fill(5.0,TS5[n]);

                    pEM_ratio[4][10] = TS2[n] / TS3[n];
                    pEM_RatioDist[4][10]->Fill(pEM_ratio[4][10]);

                    pEM_sig[4][10] = TS2[n] - TS1[n];

                    pEM_fCDist[4][10]->Fill(pEM_sig[4][10]);
                }
                pEM_sigtot[10] = pEM_sig[0][10] + pEM_sig[1][10] + pEM_sig[2][10] + pEM_sig[3][10] + pEM_sig[4][10];
            } // end pos em 90 - 100 cent
            
            if (zside[n] == 1 && section[n] == 2)
            {
                if (channel[n] == 1)
                {
                    pHAD_TSDist[0][10]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[0][10]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[0][10]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[0][10]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[0][10]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[0][10]->Fill(5.0,TS5[n]);

                    pHAD_ratio[0][10] = TS2[n] / TS3[n];
                    pHAD_RatioDist[0][10]->Fill(pHAD_ratio[0][10]);

                    pHAD_sig[0][10] = TS2[n] - TS1[n];

                    pHAD_fCDist[0][10]->Fill(pHAD_sig[0][10]);
                }
                if (channel[n] == 2)
                {
                    pHAD_TSDist[1][10]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[1][10]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[1][10]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[1][10]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[1][10]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[1][10]->Fill(5.0,TS5[n]);

                    pHAD_ratio[1][10] = TS2[n] / TS3[n];
                    pHAD_RatioDist[1][10]->Fill(pHAD_ratio[1][10]);

                    pHAD_sig[1][10] = TS2[n] - TS1[n];

                    pHAD_fCDist[1][10]->Fill(pHAD_sig[1][10]);
                }
                if (channel[n] == 3)
                {
                    pHAD_TSDist[2][10]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[2][10]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[2][10]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[2][10]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[2][10]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[2][10]->Fill(5.0,TS5[n]);

                    pHAD_ratio[2][10] = TS2[n] / TS3[n];
                    pHAD_RatioDist[2][10]->Fill(pHAD_ratio[2][10]);

                    pHAD_sig[2][10] = TS2[n] - TS1[n];

                    pHAD_fCDist[2][10]->Fill(pHAD_sig[2][10]);
                }
                if (channel[n] == 4)
                {
                    pHAD_TSDist[3][10]->Fill(0.0,TS0[n]);
                    pHAD_TSDist[3][10]->Fill(1.0,TS1[n]);
                    pHAD_TSDist[3][10]->Fill(2.0,TS2[n]);
                    pHAD_TSDist[3][10]->Fill(3.0,TS3[n]);
                    pHAD_TSDist[3][10]->Fill(4.0,TS4[n]);
                    pHAD_TSDist[3][10]->Fill(5.0,TS5[n]);

                    pHAD_ratio[3][10] = TS2[n] / TS3[n];
                    pHAD_RatioDist[3][10]->Fill(pHAD_ratio[3][10]);

                    pHAD_sig[3][10] = TS2[n] - TS1[n];

                    pHAD_fCDist[3][10]->Fill(pHAD_sig[3][10]);
                }
                pHAD_sigtot[10] = pHAD_sig[0][10] + pHAD_sig[1][10] + pHAD_sig[2][10] + pHAD_sig[3][10];
            } // end of pos had 90-100 cent
            ZDC[10] = 0.1 * pEM_sigtot[10] + pHAD_sigtot[10];
        } // end of 90 - 100 cent 
        } // end channel loop
        hi->Fill(hibin);
        SM->Fill(sumMinus);
        SP->Fill(sumPlus);

        if (hibin >= 0 && hibin <= 200)
        {
        ZDCEnergyDist[0]->Fill(ZDC[0]);
        }

        if (hibin >= 0 && hibin < 20)
        {
        ZDCEnergyDist[1]->Fill(ZDC[1]);
        }

        if (hibin >= 20 && hibin < 40)
        {
        ZDCEnergyDist[2]->Fill(ZDC[2]);
        }

        if (hibin >= 40 && hibin < 60)
        {
        ZDCEnergyDist[3]->Fill(ZDC[3]);
        }

        if (hibin >= 60 && hibin < 80)
        {
        ZDCEnergyDist[4]->Fill(ZDC[4]);
        }

        if (hibin >= 80 && hibin < 100)
        {
        ZDCEnergyDist[5]->Fill(ZDC[5]);
        }

        if (hibin >= 100 && hibin < 140)
        {
            ZDCEnergyDist[6]->Fill(ZDC[6]);
        }

        if (hibin >= 120 && hibin < 140)
        {
            ZDCEnergyDist[7]->Fill(ZDC[7]);
        }

        if (hibin >= 140 && hibin < 160)
        {
            ZDCEnergyDist[8]->Fill(ZDC[8]);
        }

        if (hibin >= 160 && hibin < 180)
        {
            ZDCEnergyDist[9]->Fill(ZDC[9]);
        }

        if (hibin >= 180 && hibin <= 200)
        {
            ZDCEnergyDist[10]->Fill(ZDC[10]);
        }
        
    } // end event loop
    gStyle->SetOptFit();

    
   for (int n = 0; n < 11; n++)
   {
        ZDCEnergyDist[n]->SetXTitle("0.1 EM + HAD, Signal is TS2 - TS1 (fC)");
        ZDCEnergyDist[n]->SetYTitle("Counts");
   }
   
    TCanvas *c1 = new TCanvas();
    c1->Divide(4,3);
    for (int n = 0; n < 11; n++)
    {
        c1->cd(n+1);
        ZDCEnergyDist[n]->Draw();
    }
    

   TCanvas *c2 = new TCanvas();
   c2->Divide(4,4);
   for (int n = 0; n < 16; n++)
   {
    c2->cd(n+1);
    AvgSigRPD[n]->Draw("hist e");
   }


    // first part of array is 6 bins, second part is 16 blocks
   float BinContent[6][16];
   int bin[6] = {1, 2, 3, 4, 5, 6};

   for (int n = 0; n < 6; n++)
   {
        BinContent[n][0] = AvgSigRPD[0]->GetBinContent(bin[n]);
        cout << "The Average Signal (fC) for block 0 in the pos RPD for 40 - 49.5% Centrality in bin number " << bin[n] << " is " << BinContent[n][0] << endl;
   }

   for (int n = 0; n < 6; n++)
   {
        BinContent[n][1] = AvgSigRPD[1]->GetBinContent(bin[n]);
        cout << "The Average Signal (fC) for block 1 in the pos RPD for 40 - 49.5% Centrality in bin number " << bin[n] << " is " << BinContent[n][1] << endl;
   }

   for (int n = 0; n < 6; n++)
   {
        BinContent[n][2] = AvgSigRPD[2]->GetBinContent(bin[n]);
        cout << "The Average Signal (fC) for block 2 in the pos RPD for 40 - 49.5% Centrality in bin number " << bin[n] << " is " << BinContent[n][2] << endl;
   }

   for (int n = 0; n < 6; n++)
   {
        BinContent[n][3] = AvgSigRPD[3]->GetBinContent(bin[n]);
        cout << "The Average Signal (fC) for block 3 in the pos RPD for 40 - 49.5% Centrality in bin number " << bin[n] << " is " << BinContent[n][3] << endl;
   }

   for (int n = 0; n < 6; n++)
   {
        BinContent[n][4] = AvgSigRPD[4]->GetBinContent(bin[n]);
        cout << "The Average Signal (fC) for block 4 in the pos RPD for 40 - 49.5% Centrality in bin number " << bin[n] << " is " << BinContent[n][4] << endl;
   }

   for (int n = 0; n < 6; n++)
   {
        BinContent[n][5] = AvgSigRPD[5]->GetBinContent(bin[n]);
        cout << "The Average Signal (fC) for block 5 in the pos RPD for 40 - 49.5% Centrality in bin number " << bin[n] << " is " << BinContent[n][5] << endl;
   }

   for (int n = 0; n < 6; n++)
   {
        BinContent[n][6] = AvgSigRPD[6]->GetBinContent(bin[n]);
        cout << "The Average Signal (fC) for block 6 in the pos RPD for 40 - 49.5% Centrality in bin number " << bin[n] << " is " << BinContent[n][6] << endl;
   }

   for (int n = 0; n < 6; n++)
   {
        BinContent[n][7] = AvgSigRPD[7]->GetBinContent(bin[n]);
        cout << "The Average Signal (fC) for block 7 in the pos RPD for 40 - 49.5% Centrality in bin number " << bin[n] << " is " << BinContent[n][7] << endl;
   }

   for (int n = 0; n < 6; n++)
   {
        BinContent[n][8] = AvgSigRPD[8]->GetBinContent(bin[n]);
        cout << "The Average Signal (fC) for block 8 in the pos RPD for 40 - 49.5% Centrality in bin number " << bin[n] << " is " << BinContent[n][8] << endl;
   }

   for (int n = 0; n < 6; n++)
   {
        BinContent[n][9] = AvgSigRPD[9]->GetBinContent(bin[n]);
        cout << "The Average Signal (fC) for block 9 in the pos RPD for 40 - 49.5% Centrality in bin number " << bin[n] << " is " << BinContent[n][9] << endl;
   }

   for (int n = 0; n < 6; n++)
   {
        BinContent[n][10] = AvgSigRPD[10]->GetBinContent(bin[n]);
        cout << "The Average Signal (fC) for block 10 in the pos RPD for 40 - 49.5% Centrality in bin number " << bin[n] << " is " << BinContent[n][10] << endl;
   }

   for (int n = 0; n < 6; n++)
   {
        BinContent[n][11] = AvgSigRPD[11]->GetBinContent(bin[n]);
        cout << "The Average Signal (fC) for block 11 in the pos RPD for 40 - 49.5% Centrality in bin number " << bin[n] << " is " << BinContent[n][11] << endl;
   }

   for (int n = 0; n < 6; n++)
   {
        BinContent[n][12] = AvgSigRPD[12]->GetBinContent(bin[n]);
        cout << "The Average Signal (fC) for block 12 in the pos RPD for 40 - 49.5% Centrality in bin number " << bin[n] << " is " << BinContent[n][12] << endl;
   }

   for (int n = 0; n < 6; n++)
   {
        BinContent[n][13] = AvgSigRPD[13]->GetBinContent(bin[n]);
        cout << "The Average Signal (fC) for block 13 in the pos RPD for 40 - 49.5% Centrality in bin number " << bin[n] << " is " << BinContent[n][13] << endl;
   }

   for (int n = 0; n < 6; n++)
   {
        BinContent[n][14] = AvgSigRPD[14]->GetBinContent(bin[n]);
        cout << "The Average Signal (fC) for block 14 in the pos RPD for 40 - 49.5% Centrality in bin number " << bin[n] << " is " << BinContent[n][14] << endl;
   }

   for (int n = 0; n < 6; n++)
   {
        BinContent[n][15] = AvgSigRPD[15]->GetBinContent(bin[n]);
        cout << "The Average Signal (fC) for block 15 in the pos RPD for 40 - 49.5% Centrality in bin number " << bin[n] << " is " << BinContent[n][15] << endl;
   } 
   
} 