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

void Run375259_FirstCollision()
{
    gROOT->ProcessLine("gErrorIgnoreLevel = 6001;");
    gROOT->ProcessLine("gPrintViaErrorHandler = kTRUE;");

    TChain *zdcchain = new TChain();
    TChain *hichain = new TChain(); 
    TChain *HLTchain = new TChain();
    for (int x = 0 ; x < 24 ; x++)
    {
        zdcchain->Add(Form("/store/data/Runs_2023/skims/375259/Run375259_HiForest_SkimMinBias%i.root/zdcdigi", x));
        hichain->Add(Form("/store/data/Runs_2023/skims/375259/Run375259_HiForest_SkimMinBias%i.root/HiTree", x));
        HLTchain->Add(Form("/store/data/Runs_2023/skims/375259/Run375259_HiForest_SkimFirstCollisionONLY%i.root/hltanalysis/HltTree", x));
    }

    zdcchain->AddFriend(hichain);
    zdcchain->AddFriend(HLTchain);

    TH1F *pRPD_TS[16] = {0};
    pRPD_TS[0]= new TH1F("","Run 375259 pos RPD Time Slice Distribution All Centrality Block 0",6,0,6);
    pRPD_TS[1]= new TH1F("","Run 375259 pos RPD Time Slice Distribution All Centrality Block 1",6,0,6);
    pRPD_TS[2]= new TH1F("","Run 375259 pos RPD Time Slice Distribution All Centrality Block 2",6,0,6);
    pRPD_TS[3]= new TH1F("","Run 375259 pos RPD Time Slice Distribution All Centrality Block 3",6,0,6);
    pRPD_TS[4]= new TH1F("","Run 375259 pos RPD Time Slice Distribution All Centrality Block 4",6,0,6);
    pRPD_TS[5]= new TH1F("","Run 375259 pos RPD Time Slice Distribution All Centrality Block 5",6,0,6);
    pRPD_TS[6]= new TH1F("","Run 375259 pos RPD Time Slice Distribution All Centrality Block 6",6,0,6);
    pRPD_TS[7]= new TH1F("","Run 375259 pos RPD Time Slice Distribution All Centrality Block 7",6,0,6);
    pRPD_TS[8]= new TH1F("","Run 375259 pos RPD Time Slice Distribution All Centrality Block 8",6,0,6);
    pRPD_TS[9]= new TH1F("","Run 375259 pos RPD Time Slice Distribution All Centrality Block 9",6,0,6);
    pRPD_TS[10]= new TH1F("","Run 375259 pos RPD Time Slice Distribution All Centrality Block 10",6,0,6);
    pRPD_TS[11]= new TH1F("","Run 375259 pos RPD Time Slice Distribution All Centrality Block 11",6,0,6);
    pRPD_TS[12]= new TH1F("","Run 375259 pos RPD Time Slice Distribution All Centrality Block 12",6,0,6);
    pRPD_TS[13]= new TH1F("","Run 375259 pos RPD Time Slice Distribution All Centrality Block 13",6,0,6);
    pRPD_TS[14]= new TH1F("","Run 375259 pos RPD Time Slice Distribution All Centrality Block 14",6,0,6);
    pRPD_TS[15]= new TH1F("","Run 375259 pos RPD Time Slice Distribution All Centrality Block 15",6,0,6);

    TH1F *nRPD_TS[16] = {0};
    nRPD_TS[0] = new TH1F("","Run 375259 neg RPD Time Slice Distribution All Centrality Block 0",6,0,6);
    nRPD_TS[1] = new TH1F("","Run 375259 neg RPD Time Slice Distribution All Centrality Block 1",6,0,6);
    nRPD_TS[2] = new TH1F("","Run 375259 neg RPD Time Slice Distribution All Centrality Block 2",6,0,6);
    nRPD_TS[3] = new TH1F("","Run 375259 neg RPD Time Slice Distribution All Centrality Block 3",6,0,6);
    nRPD_TS[4] = new TH1F("","Run 375259 neg RPD Time Slice Distribution All Centrality Block 4",6,0,6);
    nRPD_TS[5] = new TH1F("","Run 375259 neg RPD Time Slice Distribution All Centrality Block 5",6,0,6);
    nRPD_TS[6] = new TH1F("","Run 375259 neg RPD Time Slice Distribution All Centrality Block 6",6,0,6);
    nRPD_TS[7] = new TH1F("","Run 375259 neg RPD Time Slice Distribution All Centrality Block 7",6,0,6);
    nRPD_TS[8] = new TH1F("","Run 375259 neg RPD Time Slice Distribution All Centrality Block 8",6,0,6);
    nRPD_TS[9] = new TH1F("","Run 375259 neg RPD Time Slice Distribution All Centrality Block 9",6,0,6);
    nRPD_TS[10] = new TH1F("","Run 375259 neg RPD Time Slice Distribution All Centrality Block 10",6,0,6);
    nRPD_TS[11] = new TH1F("","Run 375259 neg RPD Time Slice Distribution All Centrality Block 11",6,0,6);
    nRPD_TS[12] = new TH1F("","Run 375259 neg RPD Time Slice Distribution All Centrality Block 12",6,0,6);
    nRPD_TS[13] = new TH1F("","Run 375259 neg RPD Time Slice Distribution All Centrality Block 13",6,0,6);
    nRPD_TS[14] = new TH1F("","Run 375259 neg RPD Time Slice Distribution All Centrality Block 14",6,0,6);
    nRPD_TS[15] = new TH1F("","Run 375259 neg RPD Time Slice Distribution All Centrality Block 15",6,0,6);

    TH1F *pEM_TS = new TH1F("","Run 375259 pos EM Time Slice Distribution All Centrality",6,0,6);

    TH1F *nEM_TS = new TH1F("","Run 375259 neg EM Time Slice Distribution All Centrality",6,0,6);

    TH1F *pHAD_TS = new TH1F("","Run 375259 pos HAD Time Slice Distribution All Centrality",6,0,6);

    TH1F *nHAD_TS = new TH1F("","Run 375259 neg HAD Time Slice Distribution All Centrality",6,0,6);

    int zside[56];
    int section[56];
    int channel[56];

    float TS0[56];
    float TS1[56];
    float TS2[56];
    float TS3[56];
    float TS4[56];
    float TS5[56];
    
    zdcchain->SetBranchAddress("chargefCTs0",&TS0);
    zdcchain->SetBranchAddress("chargefCTs1",&TS1);
    zdcchain->SetBranchAddress("chargefCTs2",&TS2);
    zdcchain->SetBranchAddress("chargefCTs3",&TS3);
    zdcchain->SetBranchAddress("chargefCTs4",&TS4);
    zdcchain->SetBranchAddress("chargefCTs5",&TS5);

    // section 1 is EM, 2 is HAD, 4 is RPD

    // Event loop for all events in the run
    Int_t NumofEvents = zdcchain->GetEntries();
	cout << "Total # of events = " << NumofEvents << endl;
    //NumofEvents = 100000;
    for (int i = 0; i < NumofEvents; i++) 
    {           
	    zdcchain->GetEntry(i);  
        hichain->GetEntry(i);
        HLTchain->GetEntry(i);
        if (i % 100000 == 0)
        {
            cout << "Event " << i << " has been processed" << endl;
        }
        for (int n = 0; n < 56; n++)
        {
            if(zside[n] == 1 && section[n] == 4)
            {
                if (channel[n] == 1)
                {
                    pRPD_TS[10]->Fill(0.0,TS0[n]);
                    pRPD_TS[10]->Fill(1.0,TS1[n]);
                    pRPD_TS[10]->Fill(2.0,TS2[n]);
                    pRPD_TS[10]->Fill(3.0,TS3[n]);
                    pRPD_TS[10]->Fill(4.0,TS4[n]);
                    pRPD_TS[10]->Fill(5.0,TS5[n]);
                }
                if (channel[n] == 2)
                {
                    pRPD_TS[6]->Fill(0.0,TS0[n]);
                    pRPD_TS[6]->Fill(1.0,TS1[n]);
                    pRPD_TS[6]->Fill(2.0,TS2[n]);
                    pRPD_TS[6]->Fill(3.0,TS3[n]);
                    pRPD_TS[6]->Fill(4.0,TS4[n]);
                    pRPD_TS[6]->Fill(5.0,TS5[n]);
                }
                if (channel[n] == 3)
                {
                    pRPD_TS[2]->Fill(0.0,TS0[n]);
                    pRPD_TS[2]->Fill(1.0,TS1[n]);
                    pRPD_TS[2]->Fill(2.0,TS2[n]);
                    pRPD_TS[2]->Fill(3.0,TS3[n]);
                    pRPD_TS[2]->Fill(4.0,TS4[n]);
                    pRPD_TS[2]->Fill(5.0,TS5[n]);
                }
                if (channel[n] == 4)
                {
                    pRPD_TS[14]->Fill(0.0,TS0[n]);
                    pRPD_TS[14]->Fill(1.0,TS1[n]);
                    pRPD_TS[14]->Fill(2.0,TS2[n]);
                    pRPD_TS[14]->Fill(3.0,TS3[n]);
                    pRPD_TS[14]->Fill(4.0,TS4[n]);
                    pRPD_TS[14]->Fill(5.0,TS5[n]);
                }
                if (channel[n] == 5)
                {
                    pRPD_TS[11]->Fill(0.0,TS0[n]);
                    pRPD_TS[11]->Fill(1.0,TS1[n]);
                    pRPD_TS[11]->Fill(2.0,TS2[n]);
                    pRPD_TS[11]->Fill(3.0,TS3[n]);
                    pRPD_TS[11]->Fill(4.0,TS4[n]);
                    pRPD_TS[11]->Fill(5.0,TS5[n]);
                }
                if (channel[n] == 6)
                {
                    pRPD_TS[7]->Fill(0.0,TS0[n]);
                    pRPD_TS[7]->Fill(1.0,TS1[n]);
                    pRPD_TS[7]->Fill(2.0,TS2[n]);
                    pRPD_TS[7]->Fill(3.0,TS3[n]);
                    pRPD_TS[7]->Fill(4.0,TS4[n]);
                    pRPD_TS[7]->Fill(5.0,TS5[n]);
                }
                if (channel[n] == 7)
                {
                    pRPD_TS[3]->Fill(0.0,TS0[n]);
                    pRPD_TS[3]->Fill(1.0,TS1[n]);
                    pRPD_TS[3]->Fill(2.0,TS2[n]);
                    pRPD_TS[3]->Fill(3.0,TS3[n]);
                    pRPD_TS[3]->Fill(4.0,TS4[n]);
                    pRPD_TS[3]->Fill(5.0,TS5[n]);
                }
                if (channel[n] == 8)
                {
                    pRPD_TS[15]->Fill(0.0,TS0[n]);
                    pRPD_TS[15]->Fill(1.0,TS1[n]);
                    pRPD_TS[15]->Fill(2.0,TS2[n]);
                    pRPD_TS[15]->Fill(3.0,TS3[n]);
                    pRPD_TS[15]->Fill(4.0,TS4[n]);
                    pRPD_TS[15]->Fill(5.0,TS5[n]);
                }
                if (channel[n] == 9)
                {
                    pRPD_TS[4]->Fill(0.0,TS0[n]);
                    pRPD_TS[4]->Fill(1.0,TS1[n]);
                    pRPD_TS[4]->Fill(2.0,TS2[n]);
                    pRPD_TS[4]->Fill(3.0,TS3[n]);
                    pRPD_TS[4]->Fill(4.0,TS4[n]);
                    pRPD_TS[4]->Fill(5.0,TS5[n]);
                }
                if (channel[n] == 10)
                {
                    pRPD_TS[8]->Fill(0.0,TS0[n]);
                    pRPD_TS[8]->Fill(1.0,TS1[n]);
                    pRPD_TS[8]->Fill(2.0,TS2[n]);
                    pRPD_TS[8]->Fill(3.0,TS3[n]);
                    pRPD_TS[8]->Fill(4.0,TS4[n]);
                    pRPD_TS[8]->Fill(5.0,TS5[n]);
                }
                if (channel[n] == 11)
                {
                    pRPD_TS[12]->Fill(0.0,TS0[n]);
                    pRPD_TS[12]->Fill(1.0,TS1[n]);
                    pRPD_TS[12]->Fill(2.0,TS2[n]);
                    pRPD_TS[12]->Fill(3.0,TS3[n]);
                    pRPD_TS[12]->Fill(4.0,TS4[n]);
                    pRPD_TS[12]->Fill(5.0,TS5[n]);
                }
                if (channel[n] == 12)
                {
                    pRPD_TS[0]->Fill(0.0,TS0[n]);
                    pRPD_TS[0]->Fill(1.0,TS1[n]);
                    pRPD_TS[0]->Fill(2.0,TS2[n]);
                    pRPD_TS[0]->Fill(3.0,TS3[n]);
                    pRPD_TS[0]->Fill(4.0,TS4[n]);
                    pRPD_TS[0]->Fill(5.0,TS5[n]);
                }
                if (channel[n] == 13)
                {
                    pRPD_TS[5]->Fill(0.0,TS0[n]);
                    pRPD_TS[5]->Fill(1.0,TS1[n]);
                    pRPD_TS[5]->Fill(2.0,TS2[n]);
                    pRPD_TS[5]->Fill(3.0,TS3[n]);
                    pRPD_TS[5]->Fill(4.0,TS4[n]);
                    pRPD_TS[5]->Fill(5.0,TS5[n]);
                }
                if (channel[n] == 14)
                {
                    pRPD_TS[9]->Fill(0.0,TS0[n]);
                    pRPD_TS[9]->Fill(1.0,TS1[n]);
                    pRPD_TS[9]->Fill(2.0,TS2[n]);
                    pRPD_TS[9]->Fill(3.0,TS3[n]);
                    pRPD_TS[9]->Fill(4.0,TS4[n]);
                    pRPD_TS[9]->Fill(5.0,TS5[n]);
                }
                if (channel[n] == 15)
                {
                    pRPD_TS[13]->Fill(0.0,TS0[n]);
                    pRPD_TS[13]->Fill(1.0,TS1[n]);
                    pRPD_TS[13]->Fill(2.0,TS2[n]);
                    pRPD_TS[13]->Fill(3.0,TS3[n]);
                    pRPD_TS[13]->Fill(4.0,TS4[n]);
                    pRPD_TS[13]->Fill(5.0,TS5[n]);
                }
                if (channel[n] == 16)
                {
                    pRPD_TS[1]->Fill(0.0,TS0[n]);
                    pRPD_TS[1]->Fill(1.0,TS1[n]);
                    pRPD_TS[1]->Fill(2.0,TS2[n]);
                    pRPD_TS[1]->Fill(3.0,TS3[n]);
                    pRPD_TS[1]->Fill(4.0,TS4[n]);
                    pRPD_TS[1]->Fill(5.0,TS5[n]);
                }
            } // end pos rpd
            if(zside[n] == 0 && section[n] == 4)
            {
                if (channel[n] == 1)
                {
                    pRPD_TS[10]->Fill(0.0,TS0[n]);
                    pRPD_TS[10]->Fill(1.0,TS1[n]);
                    pRPD_TS[10]->Fill(2.0,TS2[n]);
                    pRPD_TS[10]->Fill(3.0,TS3[n]);
                    pRPD_TS[10]->Fill(4.0,TS4[n]);
                    pRPD_TS[10]->Fill(5.0,TS5[n]);
                }
                if (channel[n] == 2)
                {
                    pRPD_TS[6]->Fill(0.0,TS0[n]);
                    pRPD_TS[6]->Fill(1.0,TS1[n]);
                    pRPD_TS[6]->Fill(2.0,TS2[n]);
                    pRPD_TS[6]->Fill(3.0,TS3[n]);
                    pRPD_TS[6]->Fill(4.0,TS4[n]);
                    pRPD_TS[6]->Fill(5.0,TS5[n]);
                }
                if (channel[n] == 3)
                {
                    pRPD_TS[2]->Fill(0.0,TS0[n]);
                    pRPD_TS[2]->Fill(1.0,TS1[n]);
                    pRPD_TS[2]->Fill(2.0,TS2[n]);
                    pRPD_TS[2]->Fill(3.0,TS3[n]);
                    pRPD_TS[2]->Fill(4.0,TS4[n]);
                    pRPD_TS[2]->Fill(5.0,TS5[n]);
                }
                if (channel[n] == 4)
                {
                    pRPD_TS[14]->Fill(0.0,TS0[n]);
                    pRPD_TS[14]->Fill(1.0,TS1[n]);
                    pRPD_TS[14]->Fill(2.0,TS2[n]);
                    pRPD_TS[14]->Fill(3.0,TS3[n]);
                    pRPD_TS[14]->Fill(4.0,TS4[n]);
                    pRPD_TS[14]->Fill(5.0,TS5[n]);
                }
                if (channel[n] == 5)
                {
                    pRPD_TS[11]->Fill(0.0,TS0[n]);
                    pRPD_TS[11]->Fill(1.0,TS1[n]);
                    pRPD_TS[11]->Fill(2.0,TS2[n]);
                    pRPD_TS[11]->Fill(3.0,TS3[n]);
                    pRPD_TS[11]->Fill(4.0,TS4[n]);
                    pRPD_TS[11]->Fill(5.0,TS5[n]);
                }
                if (channel[n] == 6)
                {
                    pRPD_TS[7]->Fill(0.0,TS0[n]);
                    pRPD_TS[7]->Fill(1.0,TS1[n]);
                    pRPD_TS[7]->Fill(2.0,TS2[n]);
                    pRPD_TS[7]->Fill(3.0,TS3[n]);
                    pRPD_TS[7]->Fill(4.0,TS4[n]);
                    pRPD_TS[7]->Fill(5.0,TS5[n]);
                }
                if (channel[n] == 7)
                {
                    pRPD_TS[3]->Fill(0.0,TS0[n]);
                    pRPD_TS[3]->Fill(1.0,TS1[n]);
                    pRPD_TS[3]->Fill(2.0,TS2[n]);
                    pRPD_TS[3]->Fill(3.0,TS3[n]);
                    pRPD_TS[3]->Fill(4.0,TS4[n]);
                    pRPD_TS[3]->Fill(5.0,TS5[n]);
                }
                if (channel[n] == 8)
                {
                    pRPD_TS[15]->Fill(0.0,TS0[n]);
                    pRPD_TS[15]->Fill(1.0,TS1[n]);
                    pRPD_TS[15]->Fill(2.0,TS2[n]);
                    pRPD_TS[15]->Fill(3.0,TS3[n]);
                    pRPD_TS[15]->Fill(4.0,TS4[n]);
                    pRPD_TS[15]->Fill(5.0,TS5[n]);
                }
                if (channel[n] == 9)
                {
                    pRPD_TS[4]->Fill(0.0,TS0[n]);
                    pRPD_TS[4]->Fill(1.0,TS1[n]);
                    pRPD_TS[4]->Fill(2.0,TS2[n]);
                    pRPD_TS[4]->Fill(3.0,TS3[n]);
                    pRPD_TS[4]->Fill(4.0,TS4[n]);
                    pRPD_TS[4]->Fill(5.0,TS5[n]);
                }
                if (channel[n] == 10)
                {
                    pRPD_TS[8]->Fill(0.0,TS0[n]);
                    pRPD_TS[8]->Fill(1.0,TS1[n]);
                    pRPD_TS[8]->Fill(2.0,TS2[n]);
                    pRPD_TS[8]->Fill(3.0,TS3[n]);
                    pRPD_TS[8]->Fill(4.0,TS4[n]);
                    pRPD_TS[8]->Fill(5.0,TS5[n]);
                }
                if (channel[n] == 11)
                {
                    pRPD_TS[12]->Fill(0.0,TS0[n]);
                    pRPD_TS[12]->Fill(1.0,TS1[n]);
                    pRPD_TS[12]->Fill(2.0,TS2[n]);
                    pRPD_TS[12]->Fill(3.0,TS3[n]);
                    pRPD_TS[12]->Fill(4.0,TS4[n]);
                    pRPD_TS[12]->Fill(5.0,TS5[n]);
                }
                if (channel[n] == 12)
                {
                    pRPD_TS[0]->Fill(0.0,TS0[n]);
                    pRPD_TS[0]->Fill(1.0,TS1[n]);
                    pRPD_TS[0]->Fill(2.0,TS2[n]);
                    pRPD_TS[0]->Fill(3.0,TS3[n]);
                    pRPD_TS[0]->Fill(4.0,TS4[n]);
                    pRPD_TS[0]->Fill(5.0,TS5[n]);
                }
                if (channel[n] == 13)
                {
                    pRPD_TS[5]->Fill(0.0,TS0[n]);
                    pRPD_TS[5]->Fill(1.0,TS1[n]);
                    pRPD_TS[5]->Fill(2.0,TS2[n]);
                    pRPD_TS[5]->Fill(3.0,TS3[n]);
                    pRPD_TS[5]->Fill(4.0,TS4[n]);
                    pRPD_TS[5]->Fill(5.0,TS5[n]);
                }
                if (channel[n] == 14)
                {
                    pRPD_TS[9]->Fill(0.0,TS0[n]);
                    pRPD_TS[9]->Fill(1.0,TS1[n]);
                    pRPD_TS[9]->Fill(2.0,TS2[n]);
                    pRPD_TS[9]->Fill(3.0,TS3[n]);
                    pRPD_TS[9]->Fill(4.0,TS4[n]);
                    pRPD_TS[9]->Fill(5.0,TS5[n]);
                }
                if (channel[n] == 15)
                {
                    pRPD_TS[13]->Fill(0.0,TS0[n]);
                    pRPD_TS[13]->Fill(1.0,TS1[n]);
                    pRPD_TS[13]->Fill(2.0,TS2[n]);
                    pRPD_TS[13]->Fill(3.0,TS3[n]);
                    pRPD_TS[13]->Fill(4.0,TS4[n]);
                    pRPD_TS[13]->Fill(5.0,TS5[n]);
                }
                if (channel[n] == 16)
                {
                    pRPD_TS[1]->Fill(0.0,TS0[n]);
                    pRPD_TS[1]->Fill(1.0,TS1[n]);
                    pRPD_TS[1]->Fill(2.0,TS2[n]);
                    pRPD_TS[1]->Fill(3.0,TS3[n]);
                    pRPD_TS[1]->Fill(4.0,TS4[n]);
                    pRPD_TS[1]->Fill(5.0,TS5[n]);
                }
            } // end neg rpd
        } // end channel loop
    } // end event loop

    TCanvas *c1 = new TCanvas();
    c1->Divide(4,4);
    for (int n = 0; n < 16; n++)
    {
        c1->cd(n+1);
        pRPD_TS[n]->Draw("hist e");
    }

    TCanvas *c2 = new TCanvas();
    c2->Divide(4,4);
    for (int n = 0; n < 16; n++)
    {
        c2->cd(n+1);
        nRPD_TS[n]->Draw("hist e");
    }
} // end code