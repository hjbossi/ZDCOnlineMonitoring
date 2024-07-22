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

void Run374810NegSig()
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
    int evt;

    float TS0[56];
    float TS1[56];
    float TS2[56];
    float TS3[56];
    float TS4[56];
    float TS5[56];

    float pRPD_ratio[16];
    float pEM_Ratio[5];
    float pHAD_Ratio[4];

    float pRPD_sig[16];
    float pEM_sig[5];
    float pHAD_sig[4];

    float rpdx[4];
    float rpdy[4];
    float rpdtot;

    float ZDC[4];
    float pHAD_sigtot;
    float pEM_sigtot;
    
    int adc0;
    int adc1;
    int adc2;
    int adc3;
    int adc4;
    int adc5;

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
    zdcchain->SetBranchAddress("evt",&evt);
    zdcchain->SetBranchAddress("adcTs0",&adc0);
    zdcchain->SetBranchAddress("adcTs1",&adc1);
    zdcchain->SetBranchAddress("adcTs2",&adc2);
    zdcchain->SetBranchAddress("adcTs3",&adc3);
    zdcchain->SetBranchAddress("adcTs4",&adc4);
    zdcchain->SetBranchAddress("adcTs5",&adc5);

    float EMposition;

    TH1F *EMTS = new TH1F("","Run 374810 Event 357342242 Time Slice Distribution EM 1 - 5",30,0,30);
    TH1F *HADTS = new TH1F("","Run 374810 Event 357342242 Time Slice Distribution HAD 1 - 4",24,0,24);

    TH1F *RPDratio[16];

    RPDratio[0] = new TH1F("","Run 374810 pRPD Block 0 Ratio TS2 to TS1",100,-5,5);
    RPDratio[1] = new TH1F("","Run 374810 pRPD Block 1 Ratio TS2 to TS1",100,-5,5);
    RPDratio[2] = new TH1F("","Run 374810 pRPD Block 2 Ratio TS2 to TS1",100,-5,5);
    RPDratio[3] = new TH1F("","Run 374810 pRPD Block 3 Ratio TS2 to TS1",100,-5,5);
    RPDratio[4] = new TH1F("","Run 374810 pRPD Block 4 Ratio TS2 to TS1",100,-5,5);
    RPDratio[5] = new TH1F("","Run 374810 pRPD Block 5 Ratio TS2 to TS1",100,-5,5);
    RPDratio[6] = new TH1F("","Run 374810 pRPD Block 6 Ratio TS2 to TS1",100,-5,5);
    RPDratio[7] = new TH1F("","Run 374810 pRPD Block 7 Ratio TS2 to TS1",100,-5,5);
    RPDratio[8] = new TH1F("","Run 374810 pRPD Block 8 Ratio TS2 to TS1",100,-5,5);
    RPDratio[9] = new TH1F("","Run 374810 pRPD Block 9 Ratio TS2 to TS1",100,-5,5);
    RPDratio[10] = new TH1F("","Run 374810 pRPD Block 10 Ratio TS2 to TS1",100,-5,5);
    RPDratio[11] = new TH1F("","Run 374810 pRPD Block 11 Ratio TS2 to TS1",100,-5,5);
    RPDratio[12] = new TH1F("","Run 374810 pRPD Block 12 Ratio TS2 to TS1",100,-5,5);
    RPDratio[13] = new TH1F("","Run 374810 pRPD Block 13 Ratio TS2 to TS1",100,-5,5);
    RPDratio[14] = new TH1F("","Run 374810 pRPD Block 14 Ratio TS2 to TS1",100,-5,5);
    RPDratio[15] = new TH1F("","Run 374810 pRPD Block 15 Ratio TS2 to TS1",100,-5,5);

    TH1F *EMratio[5];

    EMratio[0] = new TH1F("","Run 374810 pEM 1 Ratio TS2 to TS1",100,-1000,1000);
    EMratio[1] = new TH1F("","Run 374810 pEM 2 Ratio TS2 to TS1",100,-1000,1000);
    EMratio[2] = new TH1F("","Run 374810 pEM 3 Ratio TS2 to TS1",100,-1000,1000);
    EMratio[3] = new TH1F("","Run 374810 pEM 4 Ratio TS2 to TS1",100,-1000,1000);
    EMratio[4] = new TH1F("","Run 374810 pEM 5 Ratio TS2 to TS1",100,-1000,1000);

    TH1F *HADratio[4];

    HADratio[0] = new TH1F("","Run 374810 pHAD 1 Ratio TS2 to TS1",100,-1000,1000);
    HADratio[1] = new TH1F("","Run 374810 pHAD 2 Ratio TS2 to TS1",100,-1000,1000);
    HADratio[2] = new TH1F("","Run 374810 pHAD 3 Ratio TS2 to TS1",100,-1000,1000);
    HADratio[3] = new TH1F("","Run 374810 pHAD 4 Ratio TS2 to TS1",100,-1000,1000);

    TProfile *RPDProfile[16];

    RPDProfile[0] = new TProfile("","Run 374810 pos RPD Block 0 Average Signal 90 - 100% Centrality",6,0,6);
    RPDProfile[1] = new TProfile("","Run 374810 pos RPD Block 1 Average Signal 90 - 100% Centrality",6,0,6);
    RPDProfile[2] = new TProfile("","Run 374810 pos RPD Block 2 Average Signal 90 - 100% Centrality",6,0,6);
    RPDProfile[3] = new TProfile("","Run 374810 pos RPD Block 3 Average Signal 90 - 100% Centrality",6,0,6);
    RPDProfile[4] = new TProfile("","Run 374810 pos RPD Block 4 Average Signal 90 - 100% Centrality",6,0,6);
    RPDProfile[5] = new TProfile("","Run 374810 pos RPD Block 5 Average Signal 90 - 100% Centrality",6,0,6);
    RPDProfile[6] = new TProfile("","Run 374810 pos RPD Block 6 Average Signal 90 - 100% Centrality",6,0,6);
    RPDProfile[7] = new TProfile("","Run 374810 pos RPD Block 7 Average Signal 90 - 100% Centrality",6,0,6);
    RPDProfile[8] = new TProfile("","Run 374810 pos RPD Block 8 Average Signal 90 - 100% Centrality",6,0,6);
    RPDProfile[9] = new TProfile("","Run 374810 pos RPD Block 9 Average Signal 90 - 100% Centrality",6,0,6);
    RPDProfile[10] = new TProfile("","Run 374810 pos RPD Block 10 Average Signal 90 - 100% Centrality",6,0,6);
    RPDProfile[11] = new TProfile("","Run 374810 pos RPD Block 11 Average Signal 90 - 100% Centrality",6,0,6);
    RPDProfile[12] = new TProfile("","Run 374810 pos RPD Block 12 Average Signal 90 - 100% Centrality",6,0,6);
    RPDProfile[13] = new TProfile("","Run 374810 pos RPD Block 13 Average Signal 90 - 100% Centrality",6,0,6);
    RPDProfile[14] = new TProfile("","Run 374810 pos RPD Block 14 Average Signal 90 - 100% Centrality",6,0,6);
    RPDProfile[15] = new TProfile("","Run 374810 pos RPD Block 15 Average Signal 90 - 100% Centrality",6,0,6);

    TProfile *EMProfile[5];

    EMProfile[0] = new TProfile("","Run 374810 pos EM 1 Average Signal 90 - 100% Centrality",6,0,6);
    EMProfile[1] = new TProfile("","Run 374810 pos EM 2 Average Signal 90 - 100% Centrality",6,0,6);
    EMProfile[2] = new TProfile("","Run 374810 pos EM 3 Average Signal 90 - 100% Centrality",6,0,6);
    EMProfile[3] = new TProfile("","Run 374810 pos EM 4 Average Signal 90 - 100% Centrality",6,0,6);
    EMProfile[4] = new TProfile("","Run 374810 pos EM 5 Average Signal 90 - 100% Centrality",6,0,6);

    TProfile *HADProfile[0];

    HADProfile[0] = new TProfile("","Run 374810 pos HAD 1 Average Signal 90 - 100% Centrality",6,0,6);
    HADProfile[1] = new TProfile("","Run 374810 pos HAD 2 Average Signal 90 - 100% Centrality",6,0,6);
    HADProfile[2] = new TProfile("","Run 374810 pos HAD 3 Average Signal 90 - 100% Centrality",6,0,6);
    HADProfile[3] = new TProfile("","Run 374810 pos HAD 4 Average Signal 90 - 100% Centrality",6,0,6);

    Int_t NumEvents = zdcchain->GetEntries();
    //NumEvents = 100000;
    cout << "The number of events in Run 374810 is " << NumEvents << endl;
    for (int i = 0; i < NumEvents; i++)
    {
        zdcchain->GetEntry(i);
        hichain->GetEntry(i);
        if (i % 100000 == 0)
        {
            cout << "Event " << i << " has been processed" << endl;
        }
        
        if (hibin >= 0 && hibin <= 200)
        {
            for (int n = 0; n < 56; n++)
            {
                if (zside[n] == 1 && section[n] == 4)
                {
                    if (channel[n] == 1)
                    {
                        pRPD_ratio[10] = TS2[n] / TS3[n];
                        if (pRPD_ratio[10] > 1.1 && pRPD_ratio[10] < 2)
                        {
                        pRPD_sig[10] = TS2[n];// - 0.492 * TS1[n];
                        }
                        RPDratio[10]->Fill(pRPD_ratio[10]);
                    }

                    if (channel[n] == 2)
                    {
                        pRPD_ratio[6] = TS2[n] / TS1[n];
                        if (pRPD_ratio[6] > 1.1 && pRPD_ratio[6] < 2)
                        {
                        pRPD_sig[6] = TS2[n];// - 0.482 * TS1[n];
                        } 
                        RPDratio[6]->Fill(pRPD_ratio[6]);
                    }

                    if (channel[n] == 3)
                    {
                        pRPD_ratio[2] = TS2[n] / TS1[n];
                        if (pRPD_ratio[2] > 1.1 && pRPD_ratio[2] < 2)
                        {
                        pRPD_sig[2] = TS2[n];// - 0.837 * TS1[n];
                        } 
                        RPDratio[2]->Fill(pRPD_ratio[2]);
                    }

                    if (channel[n] == 4)
                    {
                        pRPD_ratio[14] = TS2[n] / TS3[n];
                        if (pRPD_ratio[14] > 1.1 && pRPD_ratio[14] < 2)
                        {
                        pRPD_sig[14] = TS2[n];// - 0.486 * TS1[n];
                        } 
                        RPDratio[14]->Fill(pRPD_ratio[14]);
                       
                    }

                    if (channel[n] == 5)
                    {
                        pRPD_ratio[11] = TS2[n] / TS1[n];
                        if (pRPD_ratio[11] > 1.1 && pRPD_ratio[11] < 2)
                        {
                        pRPD_sig[11] = TS2[n];// - 0.496 * TS1[n];
                        } 
                        RPDratio[11]->Fill(pRPD_ratio[11]);
                        
                    }

                    if (channel[n] == 6)
                    {
                        pRPD_ratio[7] = TS2[n] / TS1[n]; 
                        if (pRPD_ratio[7] > 1.3 && pRPD_ratio[7] < 2.3)
                        {
                        pRPD_sig[7] = TS2[n];// - 0.478 * TS1[n];
                        } 
                        RPDratio[7]->Fill(pRPD_ratio[7]);
                       
                    }

                    if (channel[n] == 7)
                    {
                        pRPD_ratio[3] = TS2[n] / TS1[n]; 
                        if (pRPD_ratio[3] > 1.3 && pRPD_ratio[3] < 2.3)
                        {
                        pRPD_sig[3] = TS2[n];// - 0.474 * TS1[n];
                        } 
                        RPDratio[3]->Fill(pRPD_ratio[3]);
                        
                    }

                    if (channel[n] == 8)
                    {
                        pRPD_ratio[15] = TS2[n] / TS1[n];
                        if (pRPD_ratio[15] > 1.1 && pRPD_ratio[15] < 2.0)
                        {
                        pRPD_sig[15] = TS2[n];// - 0.472 * TS1[n];
                        } 
                        RPDratio[15]->Fill(pRPD_ratio[15]);
                        
                    }

                    if (channel[n] == 9)
                    {
                        pRPD_ratio[4] = TS2[n] / TS1[n];
                        if (pRPD_ratio[4] > 1.1 && pRPD_ratio[4] < 2.5)
                        {
                        pRPD_sig[4] = TS2[n];// - 0.459 * TS1[n];
                        } 
                        RPDratio[4]->Fill(pRPD_ratio[4]);
                       
                    }

                    if (channel[n] == 10)
                    {
                        pRPD_ratio[8] = TS2[n] / TS1[n];
                        if (pRPD_ratio[8] > 1.3 && pRPD_ratio[8] < 2.3)
                        {
                        pRPD_sig[8] = TS2[n];//  - 0.454 * TS1[n];
                        } 
                        RPDratio[8]->Fill(pRPD_ratio[8]);
                        
                    }

                    if (channel[n] == 11)
                    {
                        pRPD_ratio[12] = TS2[n] / TS1[n];
                        if (pRPD_ratio[12] > 1.3 && pRPD_ratio[12] < 2.2)
                        {
                        pRPD_sig[12] = TS2[n];// - 0.457 * TS1[n];
                        } 
                        RPDratio[12]->Fill(pRPD_ratio[12]);
                        
                    }

                    if (channel[n] == 12)
                    {
                        pRPD_ratio[0] = TS2[n] / TS1[n];
                        if (pRPD_ratio[0] > 1.5 && pRPD_ratio[0] < 2.5)
                        {
                        pRPD_sig[0] = TS2[n];// - 0.469 * TS1[n];
                        } 
                        RPDratio[0]->Fill(pRPD_ratio[0]);
                        
                    }

                    if (channel[n] == 13)
                    {
                        pRPD_ratio[5] = TS2[n] / TS1[n];
                        if (pRPD_ratio[5] > 1.7 && pRPD_ratio[5] < 2.6)
                        {
                        pRPD_sig[5] = TS2[n];// - 0.468 * TS1[n];
                        } 
                        RPDratio[5]->Fill(pRPD_ratio[5]);
                        
                    }

                    if (channel[n] == 14)
                    {
                        pRPD_ratio[9] = TS2[n] / TS1[n];
                        if (pRPD_ratio[9] > 1.6 && pRPD_ratio[9] < 2.6)
                        {
                        pRPD_sig[9] = TS2[n];// - 0.459 * TS1[n];
                        } 
                        RPDratio[9]->Fill(pRPD_ratio[9]);
                        
                    }

                    if (channel[n] == 15)
                    {
                        pRPD_ratio[13] = TS2[n] / TS1[n];
                        if (pRPD_ratio[13] > 1.6 && pRPD_ratio[13] < 2.4)
                        {
                        pRPD_sig[13] = TS2[n];// - 0.455 * TS1[n];
                        } 
                        RPDratio[13]->Fill(pRPD_ratio[13]);
                       
                    }

                    if (channel[n] == 16)
                    {
                        pRPD_ratio[1] = TS2[n] / TS1[n];
                        if (pRPD_ratio[1] > 1.5 && pRPD_ratio[1] < 2.7)
                        {
                        pRPD_sig[1] = TS2[n];// - 0.472 * TS1[n];
                        } 
                        RPDratio[1]->Fill(pRPD_ratio[1]);
                    }

                }

                if (zside[n] == 1 && section[n] == 1)
                {
                    if (channel[n] == 1)
                    {
                        pEM_Ratio[0] = TS2[n] / TS1[n];

                        //if (pEM_Ratio[0] > 3 && pEM_Ratio[0] < 5)
                        //{
                        pEM_sig[0] = 0.6 * (TS2[n] - (0.504 * TS1[n]));
                        //} 
                        EMTS->Fill(0.0,TS0[n]);
                        EMTS->Fill(1.0,TS1[n]);   
                        EMTS->Fill(2.0,TS2[n]);               
                        EMTS->Fill(3.0,TS3[n]);   
                        EMTS->Fill(4.0,TS4[n]);   
                        EMTS->Fill(5.0,TS5[n]);  
                        EMratio[0]->Fill(pEM_Ratio[0]); 
                        /*if (pEM_sig[0] < 0)
                        {
                            cout << "Event " << evt << " has a negative value for EM 1" << endl;
                            if (evt - 1)
                            {
                                cout << "The event before " << evt << " is real" << endl;
                            }
                        }*/
                    }

                    if (channel[n] == 2)
                    {
                        pEM_Ratio[1] = TS2[n] / TS1[n];

                        //if (pEM_Ratio[1] > 3.5 && pEM_Ratio[1] < 5)
                        //{
                        pEM_sig[1] = 0.89 * (TS2[n] - (0.469 * TS1[n]));
                        //}
                        EMTS->Fill(6.0,TS0[n]);
                        EMTS->Fill(7.0,TS1[n]);   
                        EMTS->Fill(8.0,TS2[n]);               
                        EMTS->Fill(9.0,TS3[n]);   
                        EMTS->Fill(10.0,TS4[n]);   
                        EMTS->Fill(11.0,TS5[n]); 
                        EMratio[1]->Fill(pEM_Ratio[1]);  
                        /*if (pEM_sig[1] < 0)
                        {
                            cout << "Event " << evt << " has a negative value for EM 2" << endl;
                            if (evt - 1)
                            {
                                cout << "The event before " << evt << " is real" << endl;
                            }
                        }*/
                    }

                    if (channel[n] == 3)
                    {

                        pEM_Ratio[2] = TS2[n] / TS1[n];

                        //if (pEM_Ratio[2] > 3 && pEM_Ratio[2] < 4.5)
                        //{
                        pEM_sig[2] = 1 * (TS2[n] - (0.449 * TS1[n]));
                        //} 
                        EMTS->Fill(12.0,TS0[n]);
                        EMTS->Fill(13.0,TS1[n]);   
                        EMTS->Fill(14.0,TS2[n]);               
                        EMTS->Fill(15.0,TS3[n]);   
                        EMTS->Fill(16.0,TS4[n]);   
                        EMTS->Fill(17.0,TS5[n]); 
                        EMratio[2]->Fill(pEM_Ratio[2]); 
                        /*if (pEM_sig[2] < 0)
                        {
                            cout << "Event " << evt << " has a negative value for EM 3" << endl;
                            if (evt - 1)
                            {
                                cout << "The event before " << evt << " is real" << endl;
                            }
                        }*/
                         
                    }

                    if (channel[n] == 4)
                    {
                        pEM_Ratio[3] = TS2[n] / TS1[n];

                        //if (pEM_Ratio[3] > 3 && pEM_Ratio[3] < 4)
                        //{
                        pEM_sig[3] = 1.29 * (TS2[n] - (0.46 * TS1[n]));
                        //}
                        EMTS->Fill(18.0,TS0[n]);
                        EMTS->Fill(19.0,TS1[n]);   
                        EMTS->Fill(20.0,TS2[n]);               
                        EMTS->Fill(21.0,TS3[n]);   
                        EMTS->Fill(22.0,TS4[n]);   
                        EMTS->Fill(23.0,TS5[n]); 
                        EMratio[3]->Fill(pEM_Ratio[3]); 
                        /*if (pEM_sig[3] < 0)
                        {
                            cout << "Event " << evt << " has a negative value for EM 4" << endl;
                            if (evt - 1)
                            {
                                cout << "The event before " << evt << " is real" << endl;
                            }
                        }*/
                          
                    }

                    if (channel[n] == 5)
                    {

                        pEM_Ratio[4] = TS2[n] / TS1[n];

                        //if (pEM_Ratio[4] > 3 && pEM_Ratio[4] < 4)
                        //{
                        pEM_sig[4] = 0.57 * (TS2[n] - (0.449 * TS1[n]));
                        //}
                        EMTS->Fill(24.0,TS0[n]);
                        EMTS->Fill(25.0,TS1[n]);   
                        EMTS->Fill(26.0,TS2[n]);               
                        EMTS->Fill(27.0,TS3[n]);   
                        EMTS->Fill(28.0,TS4[n]);   
                        EMTS->Fill(29.0,TS5[n]); 
                        EMratio[4]->Fill(pEM_Ratio[4]); 
                        /*if (pEM_sig[4] < 0)
                        {
                            cout << "Event " << evt << " has a negative value for EM 5" << endl;
                            if (evt - 1)
                            {
                                cout << "The event before " << evt << " is real" << endl;
                            }
                        }*/
                        
                    }

                    //if (pEM_sig[0] > 0 && pEM_sig[1] > 0 && pEM_sig[2] > 0 && pEM_sig[3] > 0 && pEM_sig[4] > 0)
                    //{
                    pEM_sigtot = pEM_sig[0] +  pEM_sig[1] + pEM_sig[2] + pEM_sig[3] + pEM_sig[4];
                    EMposition = ((-3.6 * pEM_sig[0]) + (-1.8 * pEM_sig[1]) + (0 * pEM_sig[2]) + (1.8 * pEM_sig[3]) + (3.6 * pEM_sig[4])) / pEM_sigtot;
                    //pEM_sigtot = 1.41 * pEM_sig[0] +  1.87 * pEM_sig[1] + 1 * pEM_sig[2] +  1.28 * pEM_sig[3] +  1.25 * pEM_sig[4]; 

                    //}
                    //top pos bottom neg
                } // end pos em
                if (zside[n] == 1 && section[n] == 2)
                {
                    if (channel[n] == 1)
                    {
                        pHAD_Ratio[0] = TS2[n] / TS1[n];
                        cout << pHAD_Ratio[0] << endl;

                        //if (pHAD_Ratio[0] > 3 && pHAD_Ratio[0] < 4)
                        //{
                        pHAD_sig[0] = (TS2[n] - (0.458 * TS1[n]));
                        //}
                        HADTS->Fill(0.0,TS0[n]);
                        HADTS->Fill(1.0,TS1[n]);   
                        HADTS->Fill(2.0,TS2[n]);               
                        HADTS->Fill(3.0,TS3[n]);   
                        HADTS->Fill(4.0,TS4[n]);   
                        HADTS->Fill(5.0,TS5[n]); 
                        HADratio[0]->Fill(pHAD_Ratio[0]);   
                    }
                    if (channel[n] == 2)
                    {
                        pHAD_Ratio[1] = TS2[n] / TS1[n];

                        //if (pHAD_Ratio[1] > 3.5 && pHAD_Ratio[1] < 4.5)
                        //{
                        pHAD_sig[1] = (TS2[n] - (0.488 * TS1[n]));
                        //}
                        HADTS->Fill(6.0,TS0[n]);
                        HADTS->Fill(7.0,TS1[n]);   
                        HADTS->Fill(8.0,TS2[n]);               
                        HADTS->Fill(9.0,TS3[n]);   
                        HADTS->Fill(10.0,TS4[n]);   
                        HADTS->Fill(11.0,TS5[n]);
                        HADratio[1]->Fill(pHAD_Ratio[1]);   
                    }
                    if (channel[n] == 3)
                    {   
                        pHAD_Ratio[2] = TS2[n] / TS1[n];

                        //if (pHAD_Ratio[2] > 4 && pHAD_Ratio[2] < 5)
                        //{
                        pHAD_sig[2] = (TS2[n] - (0.515 * TS1[n]));
                        //}
                        HADTS->Fill(12.0,TS0[n]);
                        HADTS->Fill(13.0,TS1[n]);   
                        HADTS->Fill(14.0,TS2[n]);               
                        HADTS->Fill(15.0,TS3[n]);   
                        HADTS->Fill(16.0,TS4[n]);   
                        HADTS->Fill(17.0,TS5[n]);
                        HADratio[2]->Fill(pHAD_Ratio[2]); 
                    }
                    if (channel[n] == 4)
                    {
                        pHAD_Ratio[3] = TS2[n] / TS1[n];

                        //if (pHAD_Ratio[3] > 3.5 && pHAD_Ratio[3] < 5)
                        //{
                        pHAD_sig[3] = (TS2[n] - (0.51 * TS1[n]));
                        //}
                        HADTS->Fill(18.0,TS0[n]);
                        HADTS->Fill(19.0,TS1[n]);   
                        HADTS->Fill(20.0,TS2[n]);               
                        HADTS->Fill(21.0,TS3[n]);   
                        HADTS->Fill(22.0,TS4[n]);   
                        HADTS->Fill(23.0,TS5[n]);
                        HADratio[3]->Fill(pHAD_Ratio[3]);    
                    }
                    //if (pHAD_sig[0] > 0 && pHAD_sig[1] > 0 && pHAD_sig[2] > 0 && pHAD_sig[3] > 0)
                    //{
                    pHAD_sigtot = pHAD_sig[0] + pHAD_sig[1] + pHAD_sig[2] + pHAD_sig[3];
                    //}
                } // end pos had
            } // end channel loop
        } // end 0 to 200 cent
    } // end event loop

    gStyle->SetOptFit();

    EMTS->SetXTitle("TS for All EM Sections");
    EMTS->SetYTitle("Total Charge in TS (fC)");

    TCanvas *c1 = new TCanvas();
    c1->cd(1);
    EMTS->Draw("hist e");

    HADTS->SetXTitle("TS for All HAD Sections");
    HADTS->SetYTitle("Total Charge in TS (fC)");

    TCanvas *c2 = new TCanvas();
    c2->cd(1);
    HADTS->Draw("hist e");

    TCanvas *c3 = new TCanvas();
    c3->Divide(4,4);
    for (int n = 0; n < 16; n++)
    {
        RPDratio[n]->SetXTitle("Ratio TS 2 / TS1");
        RPDratio[n]->SetYTitle("Counts");
        c3->cd(n+1);
        RPDratio[n]->Draw();
    }

    TCanvas *c4 = new TCanvas();
    c4->Divide(3,2);
    for (int n = 0; n < 5; n++)
    {
        EMratio[n]->SetXTitle("Ratio TS 2 / TS1");
        EMratio[n]->SetYTitle("Counts");
        c4->cd(n+1);
        EMratio[n]->Draw();
    }

    TCanvas *c5 = new TCanvas();
    c5->Divide(2,2);
    for (int n = 0; n < 4; n++)
    {
        HADratio[n]->SetXTitle("Ratio TS 2 / TS1");
        HADratio[n]->SetYTitle("Counts");
        c5->cd(n+1);
        HADratio[n]->Draw();
    }

}