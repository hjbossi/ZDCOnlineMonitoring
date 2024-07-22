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

void Run375259_374810_fC()
{

    // 30 to 50% centrality, log scale, go to 200k + fC
    gROOT->ProcessLine("gErrorIgnoreLevel = 6001;");
    gROOT->ProcessLine("gPrintViaErrorHandler = kTRUE;");

    TChain *bzdcchain = new TChain();
    TChain *bhichain = new TChain();
    TChain *azdcchain = new TChain();
    TChain *ahichain = new TChain();
    // b is run 375259, a is run 374810
    for (int x = 0 ; x < 24 ; x++)
    {
    bzdcchain->Add(Form("/store/User/mwrotny/Run375259_HiForest_SkimMinBias%i.root/zdcdigi", x));
    bhichain->Add(Form("/store/User/mwrotny/Run375259_HiForest_SkimMinBias%i.root/HiTree", x));

    azdcchain->Add(Form("/store/data/Runs_2023/skims/374810/Run374810_MinBias%i.root/zdcdigi", x));
    ahichain->Add(Form("/store/data/Runs_2023/skims/374810/Run374810_MinBias%i.root/HiTree", x));
    }
    bzdcchain->AddFriend(bhichain);
    bzdcchain->AddFriend(azdcchain);
    bzdcchain->AddFriend(ahichain);

    int bzside[56];
    int bsection[56];
    int bchannel[56];
    int bhibin;

    float bTS0[56];
    float bTS1[56];
    float bTS2[56];
    float bTS3[56];
    float bTS4[56];
    float bTS5[56];

    float bpRPD_ratio[16][2];
    float bpRPD_sig[16][2];

    bzdcchain->SetBranchAddress("zside",&bzside);
    bzdcchain->SetBranchAddress("section",&bsection);
    bzdcchain->SetBranchAddress("channel",&bchannel);
    bhichain->SetBranchAddress("hiBin",&bhibin);

    bzdcchain->SetBranchAddress("chargefCTs0",&bTS0);
    bzdcchain->SetBranchAddress("chargefCTs1",&bTS1);
    bzdcchain->SetBranchAddress("chargefCTs2",&bTS2);
    bzdcchain->SetBranchAddress("chargefCTs3",&bTS3);
    bzdcchain->SetBranchAddress("chargefCTs4",&bTS4);
    bzdcchain->SetBranchAddress("chargefCTs5",&bTS5);

    //run 374810
    int azside[56];
    int asection[56];
    int achannel[56];
    int ahibin;

    float aTS0[56];
    float aTS1[56];
    float aTS2[56];
    float aTS3[56];
    float aTS4[56];
    float aTS5[56];

    float apRPD_ratio[16][2];
    float apRPD_sig[16][2];

    azdcchain->SetBranchAddress("zside",&azside);
    azdcchain->SetBranchAddress("section",&asection);
    azdcchain->SetBranchAddress("channel",&achannel);
    ahichain->SetBranchAddress("hiBin",&ahibin);

    azdcchain->SetBranchAddress("chargefCTs0",&aTS0);
    azdcchain->SetBranchAddress("chargefCTs1",&aTS1);
    azdcchain->SetBranchAddress("chargefCTs2",&aTS2);
    azdcchain->SetBranchAddress("chargefCTs3",&aTS3);
    azdcchain->SetBranchAddress("chargefCTs4",&aTS4);
    azdcchain->SetBranchAddress("chargefCTs5",&aTS5);

    TH1F *fCDist[16][2] = {0};

    fCDist[0][0] = new TH1F("374810 Block 0","fC Distribution Block 0, 30 - 70% Centrality",50,0,500000);
    fCDist[1][0] = new TH1F("374810 Block 1","fC Distribution Block 1, 30 - 70% Centrality",50,0,500000);
    fCDist[2][0] = new TH1F("374810 Block 2","fC Distribution Block 2, 30 - 70% Centrality",50,0,500000);
    fCDist[3][0] = new TH1F("374810 Block 3","fC Distribution Block 3, 30 - 70% Centrality",50,0,500000);
    fCDist[4][0] = new TH1F("374810 Block 4","fC Distribution Block 4, 30 - 70% Centrality",50,0,500000);
    fCDist[5][0] = new TH1F("374810 Block 5","fC Distribution Block 5, 30 - 70% Centrality",50,0,500000);
    fCDist[6][0] = new TH1F("374810 Block 6","fC Distribution Block 6, 30 - 70% Centrality",50,0,500000);
    fCDist[7][0] = new TH1F("374810 Block 7","fC Distribution Block 7, 30 - 70% Centrality",50,0,500000);
    fCDist[8][0] = new TH1F("374810 Block 8","fC Distribution Block 8, 30 - 70% Centrality",50,0,500000);
    fCDist[9][0] = new TH1F("374810 Block 9","fC Distribution Block 9, 30 - 70% Centrality",50,0,500000);
    fCDist[10][0] = new TH1F("374810 Block 10","fC Distribution Block 10, 30 - 70% Centrality",50,0,500000);
    fCDist[11][0] = new TH1F("374810 Block 11","fC Distribution Block 11, 30 - 70% Centrality",50,0,500000);
    fCDist[12][0] = new TH1F("374810 Block 12","fC Distribution Block 12, 30 - 70% Centrality",50,0,500000);
    fCDist[13][0] = new TH1F("374810 Block 13","fC Distribution Block 13, 30 - 70% Centrality",50,0,500000);
    fCDist[14][0] = new TH1F("374810 Block 14","fC Distribution Block 14, 30 - 70% Centrality",50,0,500000);
    fCDist[15][0] = new TH1F("374810 Block 15","fC Distribution Block 15, 30 - 70% Centrality",50,0,500000);

    fCDist[0][1] = new TH1F("375259 Block 0","fC Distribution Block 0, 30 - 70% Centrality",50,0,500000);
    fCDist[1][1] = new TH1F("375259 Block 1","fC Distribution Block 1, 30 - 70% Centrality",50,0,500000);
    fCDist[2][1] = new TH1F("375259 Block 2","fC Distribution Block 2, 30 - 70% Centrality",50,0,500000);
    fCDist[3][1] = new TH1F("375259 Block 3","fC Distribution Block 3, 30 - 70% Centrality",50,0,500000);
    fCDist[4][1] = new TH1F("375259 Block 4","fC Distribution Block 4, 30 - 70% Centrality",50,0,500000);
    fCDist[5][1] = new TH1F("375259 Block 5","fC Distribution Block 5, 30 - 70% Centrality",50,0,500000);
    fCDist[6][1] = new TH1F("375259 Block 6","fC Distribution Block 6, 30 - 70% Centrality",50,0,500000);
    fCDist[7][1] = new TH1F("375259 Block 7","fC Distribution Block 7, 30 - 70% Centrality",50,0,500000);
    fCDist[8][1] = new TH1F("375259 Block 8","fC Distribution Block 8, 30 - 70% Centrality",50,0,500000);
    fCDist[9][1] = new TH1F("375259 Block 9","fC Distribution Block 9, 30 - 70% Centrality",50,0,500000);
    fCDist[10][1] = new TH1F("375259 Block 10","fC Distribution Block 10, 30 - 70% Centrality",50,0,500000);
    fCDist[11][1] = new TH1F("375259 Block 11","fC Distribution Block 11, 30 - 70% Centrality",50,0,500000);
    fCDist[12][1] = new TH1F("375259 Block 12","fC Distribution Block 12, 30 - 70% Centrality",50,0,500000);
    fCDist[13][1] = new TH1F("375259 Block 13","fC Distribution Block 13, 30 - 70% Centrality",50,0,500000);
    fCDist[14][1] = new TH1F("375259 Block 14","fC Distribution Block 14, 30 - 70% Centrality",50,0,500000);
    fCDist[15][1] = new TH1F("375259 Block 15","fC Distribution Block 15, 30 - 70% Centrality",50,0,500000);

    Int_t bNumberEvents = bzdcchain->GetEntries();
    cout << "Total Number of Events in Run 375259 is " << bNumberEvents << endl;
    //bNumberEvents = 5000000;
    const Int_t maxSelectedEventsb = 1000000;
    Int_t selectedCountb = 0;
   
    for (int i = 0; i < bNumberEvents; i++)
    {
        if (selectedCountb >= maxSelectedEventsb) break;

        bzdcchain->GetEntry(i);
        bhichain->GetEntry(i);

        if ( i % 100000 == 0)
        {
            cout << "Event " << i << " has been processed" << endl;
        }
        if (bhibin >= 60 && bhibin <= 140)
        {
        selectedCountb++;
        
        for (int n = 0; n < 56; n++)
        {
            
            if (bzside[n] == 1 && bsection[n] == 4)
            {
                if (bchannel[n] == 1)
                {
                    bpRPD_ratio[10][1] = bTS2[n] / bTS3[n];

                    if (bpRPD_ratio[10][1] > 1.21 && bpRPD_ratio[10][1] < 2.15)
                    {
                        bpRPD_sig[10][1] = bTS2[n] + bTS3[n];
                    }

                    fCDist[10][1]->Fill(bpRPD_sig[10][1]);

                    //cout << "TS2 value is " << TS2[n] << endl;
                }

                if (bchannel[n] == 2)
                {
                    bpRPD_ratio[6][1] = bTS2[n] / bTS3[n];

                    if (bpRPD_ratio[6][1] > 1.25 && bpRPD_ratio[6][1] < 2.25)
                    {
                        bpRPD_sig[6][1] = bTS2[n] + bTS3[n];
                    }

                    fCDist[6][1]->Fill(bpRPD_sig[6][1]);
                }

                if (bchannel[n] == 3)
                {
                    bpRPD_ratio[2][1] = bTS2[n] / bTS3[n];

                    if (bpRPD_ratio[2][1] > 1.80 && bpRPD_ratio[2][1] < 2.20)
                    {
                        bpRPD_sig[2][1] = bTS2[n] + bTS3[n];
                    }

                    fCDist[2][1]->Fill(bpRPD_sig[2][1]);
                }

                if (bchannel[n] == 4)
                {
                    bpRPD_ratio[14][1] = bTS2[n] / bTS3[n];

                    if (bpRPD_ratio[14][1] > 1.20 && bpRPD_ratio[14][1] < 2.12)
                    {
                        bpRPD_sig[14][1] = bTS2[n] + bTS3[n];
                    }

                    fCDist[14][1]->Fill(bpRPD_sig[14][1]);
                }

                if (bchannel[n] == 5)
                {
                    bpRPD_ratio[11][1] = bTS2[n] / bTS3[n];

                    if (bpRPD_ratio[11][1] > 1.31 && bpRPD_ratio[11][1] < 2.31)
                    {
                        bpRPD_sig[11][1] = bTS2[n] + bTS3[n];
                    }

                    fCDist[11][1]->Fill(bpRPD_sig[11][1]);
                }

                if (bchannel[n] == 6)
                {
                    bpRPD_ratio[7][1] = bTS2[n] / bTS3[n];

                    if (bpRPD_ratio[7][1] > 1.39 && bpRPD_ratio[7][1] < 2.55)
                    {
                        bpRPD_sig[7][1] = bTS2[n] + bTS3[n];
                    }

                    fCDist[7][1]->Fill(bpRPD_sig[7][1]);
                }

                if (bchannel[n] == 7)
                {
                    bpRPD_ratio[3][1] = bTS2[n] / bTS3[n];

                    if (bpRPD_ratio[3][1] > 1.33 && bpRPD_ratio[3][1] < 2.50)
                    {
                        bpRPD_sig[3][1] = bTS2[n] + bTS3[n];
                    }

                    fCDist[3][1]->Fill(bpRPD_sig[3][1]);
                }

                if (bchannel[n] == 8)
                {
                    bpRPD_ratio[15][1] = bTS2[n] / bTS3[n];

                    if (bpRPD_ratio[15][1] > 1.32 && bpRPD_ratio[15][1] < 2.33)
                    {
                        bpRPD_sig[15][1] = bTS2[n] + bTS3[n];
                    }

                    fCDist[15][1]->Fill(bpRPD_sig[15][1]);
                }

                if (bchannel[n] == 9)
                {
                    bpRPD_ratio[4][1] = bTS2[n] / bTS3[n];

                    if (bpRPD_ratio[4][1] > 0.98 && bpRPD_ratio[4][1] < 2.53)
                    {
                        bpRPD_sig[4][1] = bTS2[n] + bTS3[n];
                    }

                    fCDist[4][1]->Fill(bpRPD_sig[4][1]);
                }

                if (bchannel[n] == 10)
                {
                    bpRPD_ratio[8][1] = bTS2[n] / bTS3[n];

                    if (bpRPD_ratio[8][1] > 1.10 && bpRPD_ratio[8][1] < 2.40)
                    {
                        bpRPD_sig[8][1] = bTS2[n] + bTS3[n];
                    }

                    fCDist[8][1]->Fill(bpRPD_sig[8][1]);
                }

                if (bchannel[n] == 11)
                {
                    bpRPD_ratio[12][1] = bTS2[n] / bTS3[n];

                    if (bpRPD_ratio[12][1] > 1.12 && bpRPD_ratio[12][1] < 2.32)
                    {
                        bpRPD_sig[12][1] = bTS2[n] + bTS3[n];
                    }

                    fCDist[12][1]->Fill(bpRPD_sig[12][1]);
                }

                if (bchannel[n] == 12)
                {
                    bpRPD_ratio[0][1] = bTS2[n] / bTS3[n];

                    if (bpRPD_ratio[0][1] > 0.89 && bpRPD_ratio[0][1] < 2.60)
                    {
                        bpRPD_sig[0][1] = bTS2[n] + bTS3[n];
                    }

                    fCDist[0][1]->Fill(bpRPD_sig[0][1]);
                }

                if (bchannel[n] == 13)
                {
                    bpRPD_ratio[5][1] = bTS2[n] / bTS3[n];

                    if (bpRPD_ratio[5][1] > 1.41 && bpRPD_ratio[5][1] < 2.76)
                    {
                        bpRPD_sig[5][1] = bTS2[n] + bTS3[n];
                    }

                    fCDist[5][1]->Fill(bpRPD_sig[5][1]);
                }

                if (bchannel[n] == 14)
                {
                    bpRPD_ratio[9][1] = bTS2[n] / bTS3[n];

                    if (bpRPD_ratio[9][1] > 1.34 && bpRPD_ratio[9][1] < 2.72)
                    {
                        bpRPD_sig[9][1] = bTS2[n] + bTS3[n];
                    }

                    fCDist[9][1]->Fill(bpRPD_sig[9][1]);
                }

                if (bchannel[n] == 15)
                {
                    bpRPD_ratio[13][1] = bTS2[n] / bTS3[n];

                    if (bpRPD_ratio[13][1] > 1.36 && bpRPD_ratio[13][1] < 2.54)
                    {
                        bpRPD_sig[13][1] = bTS2[n] + bTS3[n];
                    }

                    fCDist[13][1]->Fill(bpRPD_sig[13][1]);
                }

                if (bchannel[n] == 16)
                {
                    bpRPD_ratio[1][1] = bTS2[n] / bTS3[n];

                    if (bpRPD_ratio[1][1] > 1.25 && bpRPD_ratio[1][1] < 2.80)
                    {
                        bpRPD_sig[1][1] = bTS2[n] + bTS3[n];
                    }

                    fCDist[1][1]->Fill(bpRPD_sig[1][1]);
                }
                
            } // end pos zdc
        } // end channel loop 
        } // end bhibin
    } // end event loop 375259
   

   
    Int_t aNumberEvents = azdcchain->GetEntries();
    cout << "Total Number of Events in Run 374810 is " << aNumberEvents << endl;
    //aNumberEvents = 600000;
    const Int_t maxSelectedEventsa = 1000000;
    Int_t selectedCounta = 0;
    
    for (int i = 0; i < aNumberEvents; i++)
    {

        if (selectedCounta >= maxSelectedEventsa) break;
        
        azdcchain->GetEntry(i);
        ahichain->GetEntry(i);

        

        if ( i % 100000 == 0)
        {
            cout << "Event " << i << " has been processed" << endl;
        }
        if (ahibin >= 60 && ahibin <= 140)
        {
        selectedCounta++;

        for (int n = 0; n < 56; n++)
        {
            
            if (azside[n] == 1 && asection[n] == 4)
            {
                if (achannel[n] == 1)
                {
                    apRPD_ratio[10][0] = aTS2[n] / aTS3[n];

                    if (apRPD_ratio[10][0] > 0.881 && apRPD_ratio[10][0] < 2.12)
                    {
                        apRPD_sig[10][0] = aTS2[n] + aTS3[n];
                    }

                    fCDist[10][0]->Fill(apRPD_sig[10][0]);
                }

                if (achannel[n] == 2)
                {
                    apRPD_ratio[6][0] = aTS2[n] / aTS3[n];

                    if (apRPD_ratio[6][0] > 0.99 && apRPD_ratio[6][0] < 2.16)
                    {
                        apRPD_sig[6][0] = aTS2[n] + aTS3[n];
                    }

                    fCDist[6][0]->Fill(apRPD_sig[6][0]);
                }

                if (achannel[n] == 3)
                {
                    apRPD_ratio[2][0] = aTS2[n] / aTS3[n];

                    if (apRPD_ratio[2][0] > 1.80 && apRPD_ratio[2][0] < 2.20)
                    {
                        apRPD_sig[2][0] = aTS2[n] + aTS3[n];
                    }

                    fCDist[2][0]->Fill(apRPD_sig[2][0]);
                }

                if (achannel[n] == 4)
                {
                    apRPD_ratio[14][0] = aTS2[n] / aTS3[n];

                    if (apRPD_ratio[14][0] > 0.82 && apRPD_ratio[14][0] < 2.20)
                    {
                        apRPD_sig[14][0] = aTS2[n] + aTS3[n];
                    }

                    fCDist[14][0]->Fill(apRPD_sig[14][0]);
                }

                if (achannel[n] == 5)
                {
                    apRPD_ratio[11][0] = aTS2[n] / aTS3[n];

                    if (apRPD_ratio[11][0] > 0.89 && apRPD_ratio[11][0] < 2.16)
                    {
                        apRPD_sig[11][0] = aTS2[n] + aTS3[n];
                    }

                    fCDist[11][0]->Fill(apRPD_sig[11][0]);
                }

                if (achannel[n] == 6)
                {
                    apRPD_ratio[7][0] = aTS2[n] / aTS3[n];

                    if (apRPD_ratio[7][0] > 1.07 && apRPD_ratio[7][0] < 2.39)
                    {
                        apRPD_sig[7][0] = aTS2[n] + aTS3[n];
                    }

                    fCDist[7][0]->Fill(apRPD_sig[7][0]);
                }

                if (achannel[n] == 7)
                {
                    apRPD_ratio[3][0] = aTS2[n] / aTS3[n];

                    if (apRPD_ratio[3][0] > 1.06 && apRPD_ratio[3][0] < 2.43)
                    {
                        apRPD_sig[3][0] = aTS2[n] + aTS3[n];
                    }

                    fCDist[3][0]->Fill(apRPD_sig[3][0]);
                }

                if (achannel[n] == 8)
                {
                    apRPD_ratio[15][0] = aTS2[n] / aTS3[n];

                    if (apRPD_ratio[15][0] > 0.84 && apRPD_ratio[15][0] < 2.26)
                    {
                        apRPD_sig[15][0] = aTS2[n] + aTS3[n];
                    }

                    fCDist[15][0]->Fill(apRPD_sig[15][0]);
                }

                if (achannel[n] == 9)
                {
                    apRPD_ratio[4][0] = aTS2[n] / aTS3[n];

                    if (apRPD_ratio[4][0] > 0.74 && apRPD_ratio[4][0] < 2.78)
                    {
                        apRPD_sig[4][0] = aTS2[n] + aTS3[n];
                    }

                    fCDist[4][0]->Fill(apRPD_sig[4][0]);
                }

                if (achannel[n] == 10)
                {
                    apRPD_ratio[8][0] = aTS2[n] / aTS3[n];

                    if (apRPD_ratio[8][0] > 0.85 && apRPD_ratio[8][0] < 2.64)
                    {
                        apRPD_sig[8][0] = aTS2[n] + aTS3[n];
                    }

                    fCDist[8][0]->Fill(apRPD_sig[8][0]);
                }

                if (achannel[n] == 11)
                {
                    apRPD_ratio[12][0] = aTS2[n] / aTS3[n];

                    if (apRPD_ratio[12][0] > 0.83 && apRPD_ratio[12][0] < 2.57)
                    {
                        apRPD_sig[12][0] = aTS2[n] + aTS3[n];
                    }

                    fCDist[12][0]->Fill(apRPD_sig[12][0]);
                }

                if (achannel[n] == 12)
                {
                    apRPD_ratio[0][0] = aTS2[n] / aTS3[n];

                    if (apRPD_ratio[0][0] > 0.67 && apRPD_ratio[0][0] < 2.83)
                    {
                        apRPD_sig[0][0] = aTS2[n] + aTS3[n];
                    }

                    fCDist[0][0]->Fill(apRPD_sig[0][0]);
                }

                if (achannel[n] == 13)
                {
                    apRPD_ratio[5][0] = aTS2[n] / aTS3[n];

                    if (apRPD_ratio[5][0] > 1.16 && apRPD_ratio[5][0] < 2.96)
                    {
                        apRPD_sig[5][0] = aTS2[n] + aTS3[n];
                    }

                    fCDist[5][0]->Fill(apRPD_sig[5][0]);
                }

                if (achannel[n] == 14)
                {
                    apRPD_ratio[9][0] = aTS2[n] / aTS3[n];

                    if (apRPD_ratio[9][0] > 1.07 && apRPD_ratio[9][0] < 2.91)
                    {
                        apRPD_sig[9][0] = aTS2[n] + aTS3[n];
                    }

                    fCDist[9][0]->Fill(apRPD_sig[9][0]);
                }

                if (achannel[n] == 15)
                {
                    apRPD_ratio[13][0] = aTS2[n] / aTS3[n];

                    if (apRPD_ratio[13][0] > 1.09 && apRPD_ratio[13][0] < 2.70)
                    {
                        apRPD_sig[13][0] = aTS2[n] + aTS3[n];
                    }

                    fCDist[13][0]->Fill(apRPD_sig[13][0]);
                }

                if (achannel[n] == 16)
                {
                    apRPD_ratio[1][0] = aTS2[n] / aTS3[n];

                    if (apRPD_ratio[1][0] > 1.02 && apRPD_ratio[1][0] < 3.02)
                    {
                        apRPD_sig[1][0] = aTS2[n] + aTS3[n];
                    }

                    fCDist[1][0]->Fill(apRPD_sig[1][0]);
                }
                
            } // end pos zdc
        } // end channel loop
        } // end ahibin 
    } // end event loop 374810
    
    
    for (int n = 0; n < 16; n++)
    {   for (int x  = 0; x < 2; x++)
        {
            fCDist[n][x]->SetXTitle("fC, Signal is TS2 - TS1");
            fCDist[n][x]->SetYTitle("Counts");
        }
    }

    TCanvas *c1 = new TCanvas();
    c1->Divide(4,4);
    for (int n = 0; n < 16; n++)
    {
        fCDist[n][0]->SetMarkerSize(0.5);
        fCDist[n][0]->SetMarkerStyle(20);
        fCDist[n][0]->SetMarkerColor(kBlue);
        c1->cd(n+1);
        gPad->SetLogy();
        fCDist[n][0]->Draw("P");
    }

    TCanvas *c2 = new TCanvas();
    c2->Divide(4,4);
    for (int n = 0; n < 16; n++)
    {
        fCDist[n][1]->SetMarkerSize(0.5);
        fCDist[n][1]->SetMarkerStyle(21);
        fCDist[n][1]->SetMarkerColor(kRed);
        c2->cd(n+1);
        gPad->SetLogy();
        fCDist[n][1]->Draw("P");
    }
    
    TCanvas *c3 = new TCanvas();
    c3->Divide(4,4);

   for (int n = 0; n < 16; n++)
   {
        fCDist[n][0]->SetMarkerSize(0.5);
        fCDist[n][0]->SetMarkerStyle(20);
        fCDist[n][0]->SetMarkerColor(kBlue);

        fCDist[n][1]->SetMarkerSize(0.5);
        fCDist[n][1]->SetMarkerStyle(21);
        fCDist[n][1]->SetMarkerColor(kRed);

        c3->cd(n+1);
        gPad->SetLogy();

        //fCDist[n][0]->SetMaximum(1000000);
        //fCDist[n][1]->SetMaximum(1000000);
        fCDist[n][0]->Draw("P");
        fCDist[n][1]->Draw("SAME P");
   }

    
}