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

void Run374810_TemplateSignal()
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

    int adc0[56];
    int adc1[56];
    int adc2[56];
    int adc3[56];
    int adc4[56];
    int adc5[56];

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

    TH1F *RPDProfile[16][2];

    RPDProfile[0][0] = new TH1F("","Run 374810 pos RPD Block 0 when EM Signal < 0 All Centrality (fC)",6,0,6);
    RPDProfile[1][0] = new TH1F("","Run 374810 pos RPD Block 1 when EM Signal < 0 All Centrality (fC)",6,0,6);
    RPDProfile[2][0] = new TH1F("","Run 374810 pos RPD Block 2 when EM Signal < 0 All Centrality (fC)",6,0,6);
    RPDProfile[3][0] = new TH1F("","Run 374810 pos RPD Block 3 when EM Signal < 0 All Centrality (fC)",6,0,6);
    RPDProfile[3][0] = new TH1F("","Run 374810 pos RPD Block 3 when EM Signal < 0 All Centrality (fC)",6,0,6);
    RPDProfile[4][0] = new TH1F("","Run 374810 pos RPD Block 4 when EM Signal < 0 All Centrality (fC)",6,0,6);
    RPDProfile[5][0] = new TH1F("","Run 374810 pos RPD Block 5 when EM Signal < 0 All Centrality (fC)",6,0,6);
    RPDProfile[6][0] = new TH1F("","Run 374810 pos RPD Block 6 when EM Signal < 0 All Centrality (fC)",6,0,6);
    RPDProfile[7][0] = new TH1F("","Run 374810 pos RPD Block 7 when EM Signal < 0 All Centrality (fC)",6,0,6);
    RPDProfile[8][0] = new TH1F("","Run 374810 pos RPD Block 8 when EM Signal < 0 All Centrality (fC)",6,0,6);
    RPDProfile[9][0] = new TH1F("","Run 374810 pos RPD Block 9 when EM Signal < 0 All Centrality (fC)",6,0,6);
    RPDProfile[10][0] = new TH1F("","Run 374810 pos RPD Block 10 when EM Signal < 0 All Centrality (fC)",6,0,6);
    RPDProfile[11][0] = new TH1F("","Run 374810 pos RPD Block 11 when EM Signal < 0 All Centrality (fC)",6,0,6);
    RPDProfile[12][0] = new TH1F("","Run 374810 pos RPD Block 12 when EM Signal < 0 All Centrality (fC)",6,0,6);
    RPDProfile[13][0] = new TH1F("","Run 374810 pos RPD Block 13 when EM Signal < 0 All Centrality (fC)",6,0,6);
    RPDProfile[14][0] = new TH1F("","Run 374810 pos RPD Block 14 when EM Signal < 0 All Centrality (fC)",6,0,6);
    RPDProfile[15][0] = new TH1F("","Run 374810 pos RPD Block 15 when EM Signal < 0 All Centrality (fC)",6,0,6);

    RPDProfile[0][1] = new TH1F("","Run 374810 pos RPD Block 0 when EM Signal < 0 All Centrality ADC",6,0,6);
    RPDProfile[1][1] = new TH1F("","Run 374810 pos RPD Block 1 when EM Signal < 0 All Centrality ADC",6,0,6);
    RPDProfile[2][1] = new TH1F("","Run 374810 pos RPD Block 2 when EM Signal < 0 All Centrality ADC",6,0,6);
    RPDProfile[3][1] = new TH1F("","Run 374810 pos RPD Block 3 when EM Signal < 0 All Centrality ADC",6,0,6);
    RPDProfile[3][1] = new TH1F("","Run 374810 pos RPD Block 3 when EM Signal < 0 All Centrality ADC",6,0,6);
    RPDProfile[4][1] = new TH1F("","Run 374810 pos RPD Block 4 when EM Signal < 0 All Centrality ADC",6,0,6);
    RPDProfile[5][1] = new TH1F("","Run 374810 pos RPD Block 5 when EM Signal < 0 All Centrality ADC",6,0,6);
    RPDProfile[6][1] = new TH1F("","Run 374810 pos RPD Block 6 when EM Signal < 0 All Centrality ADC",6,0,6);
    RPDProfile[7][1] = new TH1F("","Run 374810 pos RPD Block 7 when EM Signal < 0 All Centrality ADC",6,0,6);
    RPDProfile[8][1] = new TH1F("","Run 374810 pos RPD Block 8 when EM Signal < 0 All Centrality ADC",6,0,6);
    RPDProfile[9][1] = new TH1F("","Run 374810 pos RPD Block 9 when EM Signal < 0 All Centrality ADC",6,0,6);
    RPDProfile[10][1] = new TH1F("","Run 374810 pos RPD Block 10 when EM Signal < 0 All Centrality ADC",6,0,6);
    RPDProfile[11][1] = new TH1F("","Run 374810 pos RPD Block 11 when EM Signal < 0 All Centrality ADC",6,0,6);
    RPDProfile[12][1] = new TH1F("","Run 374810 pos RPD Block 12 when EM Signal < 0 All Centrality ADC",6,0,6);
    RPDProfile[13][1] = new TH1F("","Run 374810 pos RPD Block 13 when EM Signal < 0 All Centrality ADC",6,0,6);
    RPDProfile[14][1] = new TH1F("","Run 374810 pos RPD Block 14 when EM Signal < 0 All Centrality ADC",6,0,6);
    RPDProfile[15][1] = new TH1F("","Run 374810 pos RPD Block 15 when EM Signal < 0 All Centrality ADC",6,0,6);

    TH1F *EMProfile[5][2];

    EMProfile[0][0] = new TH1F("","Run 374810 pos EM 1 when EM Signal < 0 All Centrality (fC)",6,0,6);
    EMProfile[1][0] = new TH1F("","Run 374810 pos EM 2 when EM Signal < 0 All Centrality (fC)",6,0,6);
    EMProfile[2][0] = new TH1F("","Run 374810 pos EM 3 when EM Signal < 0 All Centrality (fC)",6,0,6);
    EMProfile[3][0] = new TH1F("","Run 374810 pos EM 4 when EM Signal < 0 All Centrality (fC)",6,0,6);
    EMProfile[4][0] = new TH1F("","Run 374810 pos EM 5 when EM Signal < 0 All Centrality (fC)",6,0,6);

    EMProfile[0][1] = new TH1F("","Run 374810 pos EM 1 when EM Signal < 0 All Centrality ADC",6,0,6);
    EMProfile[1][1] = new TH1F("","Run 374810 pos EM 2 when EM Signal < 0 All Centrality ADC",6,0,6);
    EMProfile[2][1] = new TH1F("","Run 374810 pos EM 3 when EM Signal < 0 All Centrality ADC",6,0,6);
    EMProfile[3][1] = new TH1F("","Run 374810 pos EM 4 when EM Signal < 0 All Centrality ADC",6,0,6);
    EMProfile[4][1] = new TH1F("","Run 374810 pos EM 5 when EM Signal < 0 All Centrality ADC",6,0,6);

    TH1F *HADProfile[0][2];

    HADProfile[0][0] = new TH1F("","Run 374810 pos HAD 1 when EM Signal < 0 All Centrality (fC)",6,0,6);
    HADProfile[1][0] = new TH1F("","Run 374810 pos HAD 2 when EM Signal < 0 All Centrality (fC)",6,0,6);
    HADProfile[2][0] = new TH1F("","Run 374810 pos HAD 3 when EM Signal < 0 All Centrality (fC)",6,0,6);
    HADProfile[3][0] = new TH1F("","Run 374810 pos HAD 4 when EM Signal < 0 All Centrality (fC)",6,0,6);

    HADProfile[0][1] = new TH1F("","Run 374810 pos HAD 1 when EM Signal < 0 All Centrality ADC",6,0,6);
    HADProfile[1][1] = new TH1F("","Run 374810 pos HAD 2 when EM Signal < 0 All Centrality ADC",6,0,6);
    HADProfile[2][1] = new TH1F("","Run 374810 pos HAD 3 when EM Signal < 0 All Centrality ADC",6,0,6);
    HADProfile[3][1] = new TH1F("","Run 374810 pos HAD 4 when EM Signal < 0 All Centrality ADC",6,0,6);

    TH1F *RPDfc[16];

    RPDfc[0] = new TH1F("","Run 374810 pos RPD Block 0 fC All Centrality TS2 (neg values) Ratio Cuts",30,-1000,100);
    RPDfc[1] = new TH1F("","Run 374810 pos RPD Block 1 fC All Centrality TS2 (neg values) Ratio Cuts",30,-1000,100);
    RPDfc[2] = new TH1F("","Run 374810 pos RPD Block 2 fC All Centrality TS2 (neg values) Ratio Cuts",30,-1000,100);
    RPDfc[3] = new TH1F("","Run 374810 pos RPD Block 3 fC All Centrality TS2 (neg values) Ratio Cuts",30,-1000,100);
    RPDfc[4] = new TH1F("","Run 374810 pos RPD Block 4 fC All Centrality TS2 (neg values) Ratio Cuts",30,-1000,100);
    RPDfc[5] = new TH1F("","Run 374810 pos RPD Block 5 fC All Centrality TS2 (neg values) Ratio Cuts",30,-1000,100);
    RPDfc[6] = new TH1F("","Run 374810 pos RPD Block 6 fC All Centrality TS2 (neg values) Ratio Cuts",30,-1000,100);
    RPDfc[7] = new TH1F("","Run 374810 pos RPD Block 7 fC All Centrality TS2 (neg values) Ratio Cuts",30,-1000,100);
    RPDfc[8] = new TH1F("","Run 374810 pos RPD Block 8 fC All Centrality TS2 (neg values) Ratio Cuts",30,-1000,100);
    RPDfc[9] = new TH1F("","Run 374810 pos RPD Block 9 fC All Centrality TS2 (neg values) Ratio Cuts",30,-1000,100);
    RPDfc[10] = new TH1F("","Run 374810 pos RPD Block 10 fC All Centrality TS2 (neg values) Ratio Cuts",30,-1000,100);
    RPDfc[11] = new TH1F("","Run 374810 pos RPD Block 11 fC All Centrality TS2 (neg values) Ratio Cuts",30,-1000,100);
    RPDfc[12] = new TH1F("","Run 374810 pos RPD Block 12 fC All Centrality TS2 (neg values) Ratio Cuts",30,-1000,100);
    RPDfc[13] = new TH1F("","Run 374810 pos RPD Block 13 fC All Centrality TS2 (neg values) Ratio Cuts",30,-1000,100);
    RPDfc[14] = new TH1F("","Run 374810 pos RPD Block 14 fC All Centrality TS2 (neg values) Ratio Cuts",30,-1000,100);
    RPDfc[15] = new TH1F("","Run 374810 pos RPD Block 15 fC All Centrality TS2 (neg values) Ratio Cuts",30,-1000,100);

    TH1F *EMfc[5];

    for (int i = 0; i < 5; ++i) {
        EMfc[i] = new TH1F("", Form("Run 374810 pos EM %d All Centrality TS2 (neg values) NO Ratio Cuts", i + 1), 30, -300, 100);
    }

    TH1F *HADfc[4];

    for (int i = 0; i < 4; ++i) {
        HADfc[i] = new TH1F("", Form("Run 374810 pos HAD %d All Centrality TS2 (neg values) NO Ratio Cuts", i + 1), 30, -300, 100);
    }
    
    TH1F *ZDCDist[4];

    ZDCDist[0] = new TH1F("","Run 374810 pos ZDC Total Energy Distribution, All Centrality, 0.05 EM, TS2 - 0.4 * TS1",200,500,300000);
    ZDCDist[1] = new TH1F("","Run 374810 pos ZDC Total Energy Distribution, All Centrality, 0.07 EM, TS2 - 0.4 * TS1",200,500,300000);
    ZDCDist[2] = new TH1F("","Run 374810 pos ZDC Total Energy Distribution, All Centrality, 0.10 EM, TS2 - 0.4 * TS1",200,500,300000);
    ZDCDist[3] = new TH1F("","Run 374810 pos ZDC Total Energy Distribution, All Centrality, 0.12 EM, TS2 - 0.4 * TS1",200,500,300000);

    TH2F *Neutron[4];

    Neutron[0] = new TH2F("","Run 374810 Neutron plot, All Centrality, 0.05 EM, TS2 - 0.4 * TS1",200,0,300000,200,0,350000);
    Neutron[1] = new TH2F("","Run 374810 Neutron plot, All Centrality, 0.07 EM, TS2 - 0.4 * TS1",200,0,300000,200,0,350000);
    Neutron[2] = new TH2F("","Run 374810 Neutron plot, All Centrality, 0.10 EM, TS2 - 0.4 * TS1",200,0,300000,200,0,350000);
    Neutron[3] = new TH2F("","Run 374810 Neutron plot, All Centrality, 0.12 EM, TS2 - 0.4 * TS1",200,0,300000,200,0,350000);

    TH2F *pEMpositionvsSigTot[4];

    pEMpositionvsSigTot[0] = new TH2F("","Run 374810 EM position vs Total Signal (0.05 EM + HAD), TS2 - 0.4 * TS1",100,0,350000,100,-4,4);
    pEMpositionvsSigTot[1] = new TH2F("","Run 374810 EM position vs Total Signal (0.07 EM + HAD), TS2 - 0.4 * TS1",100,0,350000,100,-4,4);
    pEMpositionvsSigTot[2] = new TH2F("","Run 374810 EM position vs Total Signal (0.10 EM + HAD), TS2 - 0.4 * TS1",100,0,350000,100,-4,4);
    pEMpositionvsSigTot[3] = new TH2F("","Run 374810 EM position vs Total Signal (0.12 EM + HAD), TS2 - 0.4 * TS1",100,0,350000,100,-4,4);

    TProfile *RPDMidCent[16];

    RPDMidCent[0] = new TProfile("","Run 374810 pos RPD Block 0 Average Signal 40 to 50% Centrality",6,0,6);
    RPDMidCent[1] = new TProfile("","Run 374810 pos RPD Block 1 Average Signal 40 to 50% Centrality",6,0,6);
    RPDMidCent[2] = new TProfile("","Run 374810 pos RPD Block 2 Average Signal 40 to 50% Centrality",6,0,6);
    RPDMidCent[3] = new TProfile("","Run 374810 pos RPD Block 3 Average Signal 40 to 50% Centrality",6,0,6);
    RPDMidCent[4] = new TProfile("","Run 374810 pos RPD Block 4 Average Signal 40 to 50% Centrality",6,0,6);
    RPDMidCent[5] = new TProfile("","Run 374810 pos RPD Block 5 Average Signal 40 to 50% Centrality",6,0,6);
    RPDMidCent[6] = new TProfile("","Run 374810 pos RPD Block 6 Average Signal 40 to 50% Centrality",6,0,6);
    RPDMidCent[7] = new TProfile("","Run 374810 pos RPD Block 7 Average Signal 40 to 50% Centrality",6,0,6);
    RPDMidCent[8] = new TProfile("","Run 374810 pos RPD Block 8 Average Signal 40 to 50% Centrality",6,0,6);
    RPDMidCent[9] = new TProfile("","Run 374810 pos RPD Block 9 Average Signal 40 to 50% Centrality",6,0,6);
    RPDMidCent[10] = new TProfile("","Run 374810 pos RPD Block 10 Average Signal 40 to 50% Centrality",6,0,6);
    RPDMidCent[11] = new TProfile("","Run 374810 pos RPD Block 11 Average Signal 40 to 50% Centrality",6,0,6);
    RPDMidCent[12] = new TProfile("","Run 374810 pos RPD Block 12 Average Signal 40 to 50% Centrality",6,0,6);
    RPDMidCent[13] = new TProfile("","Run 374810 pos RPD Block 13 Average Signal 40 to 50% Centrality",6,0,6);
    RPDMidCent[14] = new TProfile("","Run 374810 pos RPD Block 14 Average Signal 40 to 50% Centrality",6,0,6);
    RPDMidCent[15] = new TProfile("","Run 374810 pos RPD Block 15 Average Signal 40 to 50% Centrality",6,0,6);

    float EMposition;
    int prevevt;

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
                if (zside[n] == 1 && section[n] == 1)
                {
                    if (channel[n] == 1)
                    {
                        pEM_Ratio[0] = TS2[n] / TS3[n];
                        pEM_sig[0] = (TS2[n] - (0.4 * TS1[n]));  

                        EMProfile[0][0]->Fill(0.0,TS0[n]);   
                        EMProfile[0][0]->Fill(1.0,TS1[n]);        
                        EMProfile[0][0]->Fill(2.0,TS2[n]);  
                        EMProfile[0][0]->Fill(3.0,TS3[n]);  
                        EMProfile[0][0]->Fill(4.0,TS4[n]);  
                        EMProfile[0][0]->Fill(5.0,TS5[n]); 

                        EMProfile[0][1]->Fill(0.0,adc0[n]);   
                        EMProfile[0][1]->Fill(1.0,adc1[n]);        
                        EMProfile[0][1]->Fill(2.0,adc2[n]);  
                        EMProfile[0][1]->Fill(3.0,adc3[n]);  
                        EMProfile[0][1]->Fill(4.0,adc4[n]);  
                        EMProfile[0][1]->Fill(5.0,adc5[n]);  
                    }

                    if (channel[n] == 2)
                    {
                        pEM_Ratio[1] = TS2[n] / TS3[n];
                        pEM_sig[1] = (TS2[n] - (0.4 * TS1[n]));

                        EMProfile[1][0]->Fill(0.0,TS0[n]);   
                        EMProfile[1][0]->Fill(1.0,TS1[n]);        
                        EMProfile[1][0]->Fill(2.0,TS2[n]);  
                        EMProfile[1][0]->Fill(3.0,TS3[n]);  
                        EMProfile[1][0]->Fill(4.0,TS4[n]);  
                        EMProfile[1][0]->Fill(5.0,TS5[n]); 

                        EMProfile[1][1]->Fill(0.0,adc0[n]);   
                        EMProfile[1][1]->Fill(1.0,adc1[n]);        
                        EMProfile[1][1]->Fill(2.0,adc2[n]);  
                        EMProfile[1][1]->Fill(3.0,adc3[n]);  
                        EMProfile[1][1]->Fill(4.0,adc4[n]);  
                        EMProfile[1][1]->Fill(5.0,adc5[n]); 
                    }

                    if (channel[n] == 3)
                    {
                        pEM_Ratio[2] = TS2[n] / TS3[n];
                        pEM_sig[2] = (TS2[n] - (0.4 * TS1[n]));

                        EMProfile[2][0]->Fill(0.0,TS0[n]);   
                        EMProfile[2][0]->Fill(1.0,TS1[n]);        
                        EMProfile[2][0]->Fill(2.0,TS2[n]);  
                        EMProfile[2][0]->Fill(3.0,TS3[n]);  
                        EMProfile[2][0]->Fill(4.0,TS4[n]);  
                        EMProfile[2][0]->Fill(5.0,TS5[n]); 

                        EMProfile[2][1]->Fill(0.0,adc0[n]);   
                        EMProfile[2][1]->Fill(1.0,adc1[n]);        
                        EMProfile[2][1]->Fill(2.0,adc2[n]);  
                        EMProfile[2][1]->Fill(3.0,adc3[n]);  
                        EMProfile[2][1]->Fill(4.0,adc4[n]);  
                        EMProfile[2][1]->Fill(5.0,adc5[n]); 
                    }

                    if (channel[n] == 4)
                    {
                        pEM_Ratio[3] = TS2[n] / TS3[n];
                        pEM_sig[3] = (TS2[n] - (0.4 * TS1[n]));

                        EMProfile[3][0]->Fill(0.0,TS0[n]);   
                        EMProfile[3][0]->Fill(1.0,TS1[n]);        
                        EMProfile[3][0]->Fill(2.0,TS2[n]);  
                        EMProfile[3][0]->Fill(3.0,TS3[n]);  
                        EMProfile[3][0]->Fill(4.0,TS4[n]);  
                        EMProfile[3][0]->Fill(5.0,TS5[n]); 

                        EMProfile[3][1]->Fill(0.0,adc0[n]);   
                        EMProfile[3][1]->Fill(1.0,adc1[n]);        
                        EMProfile[3][1]->Fill(2.0,adc2[n]);  
                        EMProfile[3][1]->Fill(3.0,adc3[n]);  
                        EMProfile[3][1]->Fill(4.0,adc4[n]);  
                        EMProfile[3][1]->Fill(5.0,adc5[n]); 

                        
                    }

                    if (channel[n] == 5)
                    {
                        pEM_Ratio[4] = TS2[n] / TS3[n];
                        pEM_sig[4] = (TS2[n] - (0.4 * TS1[n]));

                        EMProfile[4][0]->Fill(0.0,TS0[n]);   
                        EMProfile[4][0]->Fill(1.0,TS1[n]);        
                        EMProfile[4][0]->Fill(2.0,TS2[n]);  
                        EMProfile[4][0]->Fill(3.0,TS3[n]);  
                        EMProfile[4][0]->Fill(4.0,TS4[n]);  
                        EMProfile[4][0]->Fill(5.0,TS5[n]); 

                        EMProfile[4][1]->Fill(0.0,adc0[n]);   
                        EMProfile[4][1]->Fill(1.0,adc1[n]);        
                        EMProfile[4][1]->Fill(2.0,adc2[n]);  
                        EMProfile[4][1]->Fill(3.0,adc3[n]);  
                        EMProfile[4][1]->Fill(4.0,adc4[n]);  
                        EMProfile[4][1]->Fill(5.0,adc5[n]); 

                        
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
                        pHAD_Ratio[0] = TS2[n] / TS3[n];
                        pHAD_sig[0] = (TS2[n] - (0.4 * TS1[n]));
                        
                        HADProfile[0][0]->Fill(0.0,TS0[n]);
                        HADProfile[0][0]->Fill(1.0,TS1[n]);
                        HADProfile[0][0]->Fill(2.0,TS2[n]);
                        HADProfile[0][0]->Fill(3.0,TS3[n]);
                        HADProfile[0][0]->Fill(4.0,TS4[n]);
                        HADProfile[0][0]->Fill(5.0,TS5[n]);

                        HADProfile[0][1]->Fill(0.0,adc0[n]);
                        HADProfile[0][1]->Fill(1.0,adc1[n]);
                        HADProfile[0][1]->Fill(2.0,adc2[n]);
                        HADProfile[0][1]->Fill(3.0,adc3[n]);
                        HADProfile[0][1]->Fill(4.0,adc4[n]);
                        HADProfile[0][1]->Fill(5.0,adc5[n]);
                    }
                    if (channel[n] == 2)
                    {
                        pHAD_Ratio[1] = TS2[n] / TS3[n];
                        pHAD_sig[1] = (TS2[n] - (0.4 * TS1[n]));

                        HADProfile[1][0]->Fill(0.0,TS0[n]);
                        HADProfile[1][0]->Fill(1.0,TS1[n]);
                        HADProfile[1][0]->Fill(2.0,TS2[n]);
                        HADProfile[1][0]->Fill(3.0,TS3[n]);
                        HADProfile[1][0]->Fill(4.0,TS4[n]);
                        HADProfile[1][0]->Fill(5.0,TS5[n]);

                        HADProfile[1][1]->Fill(0.0,adc0[n]);
                        HADProfile[1][1]->Fill(1.0,adc1[n]);
                        HADProfile[1][1]->Fill(2.0,adc2[n]);
                        HADProfile[1][1]->Fill(3.0,adc3[n]);
                        HADProfile[1][1]->Fill(4.0,adc4[n]);
                        HADProfile[1][1]->Fill(5.0,adc5[n]);
                    }
                    if (channel[n] == 3)
                    {   
                        pHAD_Ratio[2] = TS2[n] / TS3[n];
                        pHAD_sig[2] = (TS2[n] - (0.4 * TS1[n]));

                        HADProfile[2][0]->Fill(0.0,TS0[n]);
                        HADProfile[2][0]->Fill(1.0,TS1[n]);
                        HADProfile[2][0]->Fill(2.0,TS2[n]);
                        HADProfile[2][0]->Fill(3.0,TS3[n]);
                        HADProfile[2][0]->Fill(4.0,TS4[n]);
                        HADProfile[2][0]->Fill(5.0,TS5[n]);

                        HADProfile[2][1]->Fill(0.0,adc0[n]);
                        HADProfile[2][1]->Fill(1.0,adc1[n]);
                        HADProfile[2][1]->Fill(2.0,adc2[n]);
                        HADProfile[2][1]->Fill(3.0,adc3[n]);
                        HADProfile[2][1]->Fill(4.0,adc4[n]);
                        HADProfile[2][1]->Fill(5.0,adc5[n]);
                    }
                    if (channel[n] == 4)
                    {
                        pHAD_Ratio[3] = TS2[n] / TS3[n];
                        pHAD_sig[3] = (TS2[n] - (0.4 * TS1[n]));

                        HADProfile[3][0]->Fill(0.0,TS0[n]);
                        HADProfile[3][0]->Fill(1.0,TS1[n]);
                        HADProfile[3][0]->Fill(2.0,TS2[n]);
                        HADProfile[3][0]->Fill(3.0,TS3[n]);
                        HADProfile[3][0]->Fill(4.0,TS4[n]);
                        HADProfile[3][0]->Fill(5.0,TS5[n]);

                        HADProfile[3][1]->Fill(0.0,adc0[n]);
                        HADProfile[3][1]->Fill(1.0,adc1[n]);
                        HADProfile[3][1]->Fill(2.0,adc2[n]);
                        HADProfile[3][1]->Fill(3.0,adc3[n]);
                        HADProfile[3][1]->Fill(4.0,adc4[n]);
                        HADProfile[3][1]->Fill(5.0,adc5[n]);
                    }
                    //if (pHAD_sig[0] > 0 && pHAD_sig[1] > 0 && pHAD_sig[2] > 0 && pHAD_sig[3] > 0)
                    //{
                    pHAD_sigtot = pHAD_sig[0] + pHAD_sig[1] + pHAD_sig[2] + pHAD_sig[3];
                    //}
                } // end pos had
                    
                
                if (zside[n] == 1 && section[n] == 4)
                {
                    if (channel[n] == 1)
                    {
                        pRPD_ratio[10] = TS2[n] / TS3[n];
                        //cout << pRPD_ratio[10] << endl;
                        if (pRPD_ratio[10] > 1.1 && pRPD_ratio[10] < 2)
                        {
                        pRPD_sig[10] = TS2[n] - 0.4 * TS1[n];
                        }

                        RPDProfile[10][0]->Fill(0.0,TS0[n]);
                        RPDProfile[10][0]->Fill(1.0,TS1[n]);
                        RPDProfile[10][0]->Fill(2.0,TS2[n]);
                        RPDProfile[10][0]->Fill(3.0,TS3[n]);
                        RPDProfile[10][0]->Fill(4.0,TS4[n]);
                        RPDProfile[10][0]->Fill(5.0,TS5[n]);

                        RPDProfile[10][1]->Fill(0.0,adc0[n]);
                        RPDProfile[10][1]->Fill(1.0,adc1[n]);
                        RPDProfile[10][1]->Fill(2.0,adc2[n]);
                        RPDProfile[10][1]->Fill(3.0,adc3[n]);
                        RPDProfile[10][1]->Fill(4.0,adc4[n]);
                        RPDProfile[10][1]->Fill(5.0,adc5[n]);
                    }

                    if (channel[n] == 2)
                    {
                        pRPD_ratio[6] = TS2[n] / TS3[n];

                        if (pRPD_ratio[6] > 1.1 && pRPD_ratio[6] < 2)
                        {
                        pRPD_sig[6] = TS2[n] - 0.4 * TS1[n];
                        } 

                        RPDProfile[6][0]->Fill(0.0,TS0[n]);
                        RPDProfile[6][0]->Fill(1.0,TS1[n]);
                        RPDProfile[6][0]->Fill(2.0,TS2[n]);
                        RPDProfile[6][0]->Fill(3.0,TS3[n]);
                        RPDProfile[6][0]->Fill(4.0,TS4[n]);
                        RPDProfile[6][0]->Fill(5.0,TS5[n]);

                        RPDProfile[6][1]->Fill(0.0,adc0[n]);
                        RPDProfile[6][1]->Fill(1.0,adc1[n]);
                        RPDProfile[6][1]->Fill(2.0,adc2[n]);
                        RPDProfile[6][1]->Fill(3.0,adc3[n]);
                        RPDProfile[6][1]->Fill(4.0,adc4[n]);
                        RPDProfile[6][1]->Fill(5.0,adc5[n]);
                    }

                    if (channel[n] == 3)
                    {
                        pRPD_ratio[2] = TS2[n] / TS3[n];

                        if (pRPD_ratio[2] > 1.1 && pRPD_ratio[2] < 2)
                        {
                        pRPD_sig[2] = TS2[n] - 0.4 * TS1[n];
                        } 

                        RPDProfile[2][0]->Fill(0.0,TS0[n]);
                        RPDProfile[2][0]->Fill(1.0,TS1[n]);
                        RPDProfile[2][0]->Fill(2.0,TS2[n]);
                        RPDProfile[2][0]->Fill(3.0,TS3[n]);
                        RPDProfile[2][0]->Fill(4.0,TS4[n]);
                        RPDProfile[2][0]->Fill(5.0,TS5[n]);

                        RPDProfile[2][1]->Fill(0.0,adc0[n]);
                        RPDProfile[2][1]->Fill(1.0,adc1[n]);
                        RPDProfile[2][1]->Fill(2.0,adc2[n]);
                        RPDProfile[2][1]->Fill(3.0,adc3[n]);
                        RPDProfile[2][1]->Fill(4.0,adc4[n]);
                        RPDProfile[2][1]->Fill(5.0,adc5[n]);
                    }

                    if (channel[n] == 4)
                    {
                        pRPD_ratio[14] = TS2[n] / TS3[n];

                        if (pRPD_ratio[14] > 1.1 && pRPD_ratio[14] < 2)
                        {
                        pRPD_sig[14] = TS2[n] - 0.4 * TS1[n];
                        } 

                        RPDProfile[14][0]->Fill(0.0,TS0[n]);
                        RPDProfile[14][0]->Fill(1.0,TS1[n]);
                        RPDProfile[14][0]->Fill(2.0,TS2[n]);
                        RPDProfile[14][0]->Fill(3.0,TS3[n]);
                        RPDProfile[14][0]->Fill(4.0,TS4[n]);
                        RPDProfile[14][0]->Fill(5.0,TS5[n]);

                        RPDProfile[14][1]->Fill(0.0,adc0[n]);
                        RPDProfile[14][1]->Fill(1.0,adc1[n]);
                        RPDProfile[14][1]->Fill(2.0,adc2[n]);
                        RPDProfile[14][1]->Fill(3.0,adc3[n]);
                        RPDProfile[14][1]->Fill(4.0,adc4[n]);
                        RPDProfile[14][1]->Fill(5.0,adc5[n]);
                    }

                    if (channel[n] == 5)
                    {
                        pRPD_ratio[11] = TS2[n] / TS3[n];

                        if (pRPD_ratio[11] > 1.1 && pRPD_ratio[11] < 2)
                        {
                        pRPD_sig[11] = TS2[n] - 0.4 * TS1[n];
                        } 

                        RPDProfile[11][0]->Fill(0.0,TS0[n]);
                        RPDProfile[11][0]->Fill(1.0,TS1[n]);
                        RPDProfile[11][0]->Fill(2.0,TS2[n]);
                        RPDProfile[11][0]->Fill(3.0,TS3[n]);
                        RPDProfile[11][0]->Fill(4.0,TS4[n]);
                        RPDProfile[11][0]->Fill(5.0,TS5[n]);

                        RPDProfile[11][1]->Fill(0.0,adc0[n]);
                        RPDProfile[11][1]->Fill(1.0,adc1[n]);
                        RPDProfile[11][1]->Fill(2.0,adc2[n]);
                        RPDProfile[11][1]->Fill(3.0,adc3[n]);
                        RPDProfile[11][1]->Fill(4.0,adc4[n]);
                        RPDProfile[11][1]->Fill(5.0,adc5[n]);
                    }

                    if (channel[n] == 6)
                    {
                        pRPD_ratio[7] = TS2[n] / TS3[n];

                        if (pRPD_ratio[7] > 1.3 && pRPD_ratio[7] < 2.3)
                        {
                        pRPD_sig[7] = TS2[n] - 0.4 * TS1[n];
                        } 

                        RPDProfile[7][0]->Fill(0.0,TS0[n]);
                        RPDProfile[7][0]->Fill(1.0,TS1[n]);
                        RPDProfile[7][0]->Fill(2.0,TS2[n]);
                        RPDProfile[7][0]->Fill(3.0,TS3[n]);
                        RPDProfile[7][0]->Fill(4.0,TS4[n]);
                        RPDProfile[7][0]->Fill(5.0,TS5[n]);

                        RPDProfile[7][1]->Fill(0.0,adc0[n]);
                        RPDProfile[7][1]->Fill(1.0,adc1[n]);
                        RPDProfile[7][1]->Fill(2.0,adc2[n]);
                        RPDProfile[7][1]->Fill(3.0,adc3[n]);
                        RPDProfile[7][1]->Fill(4.0,adc4[n]);
                        RPDProfile[7][1]->Fill(5.0,adc5[n]);
                    }

                    if (channel[n] == 7)
                    {
                        pRPD_ratio[3] = TS2[n] / TS3[n];

                        if (pRPD_ratio[3] > 1.3 && pRPD_ratio[3] < 2.3)
                        {
                        pRPD_sig[3] = TS2[n] - 0.4 * TS1[n];
                        } 

                        RPDProfile[3][0]->Fill(0.0,TS0[n]);
                        RPDProfile[3][0]->Fill(1.0,TS1[n]);
                        RPDProfile[3][0]->Fill(2.0,TS2[n]);
                        RPDProfile[3][0]->Fill(3.0,TS3[n]);
                        RPDProfile[3][0]->Fill(4.0,TS4[n]);
                        RPDProfile[3][0]->Fill(5.0,TS5[n]);

                        RPDProfile[3][1]->Fill(0.0,adc0[n]);
                        RPDProfile[3][1]->Fill(1.0,adc1[n]);
                        RPDProfile[3][1]->Fill(2.0,adc2[n]);
                        RPDProfile[3][1]->Fill(3.0,adc3[n]);
                        RPDProfile[3][1]->Fill(4.0,adc4[n]);
                        RPDProfile[3][1]->Fill(5.0,adc5[n]);
                    }

                    if (channel[n] == 8)
                    {
                        pRPD_ratio[15] = TS2[n] / TS3[n];

                        if (pRPD_ratio[15] > 1.1 && pRPD_ratio[15] < 2.0)
                        {
                        pRPD_sig[15] = TS2[n] - 0.4 * TS1[n];
                        } 

                        RPDProfile[15][0]->Fill(0.0,TS0[n]);
                        RPDProfile[15][0]->Fill(1.0,TS1[n]);
                        RPDProfile[15][0]->Fill(2.0,TS2[n]);
                        RPDProfile[15][0]->Fill(3.0,TS3[n]);
                        RPDProfile[15][0]->Fill(4.0,TS4[n]);
                        RPDProfile[15][0]->Fill(5.0,TS5[n]);

                        RPDProfile[15][1]->Fill(0.0,adc0[n]);
                        RPDProfile[15][1]->Fill(1.0,adc1[n]);
                        RPDProfile[15][1]->Fill(2.0,adc2[n]);
                        RPDProfile[15][1]->Fill(3.0,adc3[n]);
                        RPDProfile[15][1]->Fill(4.0,adc4[n]);
                        RPDProfile[15][1]->Fill(5.0,adc5[n]);
                    }

                    if (channel[n] == 9)
                    {
                        pRPD_ratio[4] = TS2[n] / TS3[n];

                        if (pRPD_ratio[4] > 1.1 && pRPD_ratio[4] < 2.5)
                        {
                        pRPD_sig[4] = TS2[n] - 0.4 * TS1[n];
                        } 

                        RPDProfile[4][0]->Fill(0.0,TS0[n]);
                        RPDProfile[4][0]->Fill(1.0,TS1[n]);
                        RPDProfile[4][0]->Fill(2.0,TS2[n]);
                        RPDProfile[4][0]->Fill(3.0,TS3[n]);
                        RPDProfile[4][0]->Fill(4.0,TS4[n]);
                        RPDProfile[4][0]->Fill(5.0,TS5[n]);

                        RPDProfile[4][1]->Fill(0.0,adc0[n]);
                        RPDProfile[4][1]->Fill(1.0,adc1[n]);
                        RPDProfile[4][1]->Fill(2.0,adc2[n]);
                        RPDProfile[4][1]->Fill(3.0,adc3[n]);
                        RPDProfile[4][1]->Fill(4.0,adc4[n]);
                        RPDProfile[4][1]->Fill(5.0,adc5[n]);
                    }

                    if (channel[n] == 10)
                    {
                        pRPD_ratio[8] = TS2[n] / TS3[n];

                        if (pRPD_ratio[8] > 1.3 && pRPD_ratio[8] < 2.3)
                        {
                        pRPD_sig[8] = TS2[n]  - 0.4 * TS1[n];
                        } 

                        RPDProfile[8][0]->Fill(0.0,TS0[n]);
                        RPDProfile[8][0]->Fill(1.0,TS1[n]);
                        RPDProfile[8][0]->Fill(2.0,TS2[n]);
                        RPDProfile[8][0]->Fill(3.0,TS3[n]);
                        RPDProfile[8][0]->Fill(4.0,TS4[n]);
                        RPDProfile[8][0]->Fill(5.0,TS5[n]);

                        RPDProfile[8][1]->Fill(0.0,adc0[n]);
                        RPDProfile[8][1]->Fill(1.0,adc1[n]);
                        RPDProfile[8][1]->Fill(2.0,adc2[n]);
                        RPDProfile[8][1]->Fill(3.0,adc3[n]);
                        RPDProfile[8][1]->Fill(4.0,adc4[n]);
                        RPDProfile[8][1]->Fill(5.0,adc5[n]);
                    }

                    if (channel[n] == 11)
                    {
                        pRPD_ratio[12] = TS2[n] / TS3[n];

                        if (pRPD_ratio[12] > 1.3 && pRPD_ratio[12] < 2.2)
                        {
                        pRPD_sig[12] = TS2[n] - 0.4 * TS1[n];
                        } 

                        RPDProfile[12][0]->Fill(0.0,TS0[n]);
                        RPDProfile[12][0]->Fill(1.0,TS1[n]);
                        RPDProfile[12][0]->Fill(2.0,TS2[n]);
                        RPDProfile[12][0]->Fill(3.0,TS3[n]);
                        RPDProfile[12][0]->Fill(4.0,TS4[n]);
                        RPDProfile[12][0]->Fill(5.0,TS5[n]);

                        RPDProfile[12][1]->Fill(0.0,adc0[n]);
                        RPDProfile[12][1]->Fill(1.0,adc1[n]);
                        RPDProfile[12][1]->Fill(2.0,adc2[n]);
                        RPDProfile[12][1]->Fill(3.0,adc3[n]);
                        RPDProfile[12][1]->Fill(4.0,adc4[n]);
                        RPDProfile[12][1]->Fill(5.0,adc5[n]);
                    }

                    if (channel[n] == 12)
                    {
                        pRPD_ratio[0] = TS2[n] / TS3[n];

                        if (pRPD_ratio[0] > 1.5 && pRPD_ratio[0] < 2.5)
                        {
                        pRPD_sig[0] = TS2[n] - 0.4 * TS1[n];
                        } 

                        RPDProfile[0][0]->Fill(0.0,TS0[n]);
                        RPDProfile[0][0]->Fill(1.0,TS1[n]);
                        RPDProfile[0][0]->Fill(2.0,TS2[n]);
                        RPDProfile[0][0]->Fill(3.0,TS3[n]);
                        RPDProfile[0][0]->Fill(4.0,TS4[n]);
                        RPDProfile[0][0]->Fill(5.0,TS5[n]);

                        RPDProfile[0][1]->Fill(0.0,adc0[n]);
                        RPDProfile[0][1]->Fill(1.0,adc1[n]);
                        RPDProfile[0][1]->Fill(2.0,adc2[n]);
                        RPDProfile[0][1]->Fill(3.0,adc3[n]);
                        RPDProfile[0][1]->Fill(4.0,adc4[n]);
                        RPDProfile[0][1]->Fill(5.0,adc5[n]);
                    }

                    if (channel[n] == 13)
                    {
                        pRPD_ratio[5] = TS2[n] / TS3[n];

                        if (pRPD_ratio[5] > 1.7 && pRPD_ratio[5] < 2.6)
                        {
                        pRPD_sig[5] = TS2[n] - 0.4 * TS1[n];
                        } 

                        RPDProfile[5][0]->Fill(0.0,TS0[n]);
                        RPDProfile[5][0]->Fill(1.0,TS1[n]);
                        RPDProfile[5][0]->Fill(2.0,TS2[n]);
                        RPDProfile[5][0]->Fill(3.0,TS3[n]);
                        RPDProfile[5][0]->Fill(4.0,TS4[n]);
                        RPDProfile[5][0]->Fill(5.0,TS5[n]);

                        RPDProfile[5][1]->Fill(0.0,adc0[n]);
                        RPDProfile[5][1]->Fill(1.0,adc1[n]);
                        RPDProfile[5][1]->Fill(2.0,adc2[n]);
                        RPDProfile[5][1]->Fill(3.0,adc3[n]);
                        RPDProfile[5][1]->Fill(4.0,adc4[n]);
                        RPDProfile[5][1]->Fill(5.0,adc5[n]);
                    }

                    if (channel[n] == 14)
                    {
                        pRPD_ratio[9] = TS2[n] / TS3[n];

                        if (pRPD_ratio[9] > 1.6 && pRPD_ratio[9] < 2.6)
                        {
                        pRPD_sig[9] = TS2[n] - 0.4 * TS1[n];
                        } 

                        RPDProfile[9][0]->Fill(0.0,TS0[n]);
                        RPDProfile[9][0]->Fill(1.0,TS1[n]);
                        RPDProfile[9][0]->Fill(2.0,TS2[n]);
                        RPDProfile[9][0]->Fill(3.0,TS3[n]);
                        RPDProfile[9][0]->Fill(4.0,TS4[n]);
                        RPDProfile[9][0]->Fill(5.0,TS5[n]);

                        RPDProfile[9][1]->Fill(0.0,adc0[n]);
                        RPDProfile[9][1]->Fill(1.0,adc1[n]);
                        RPDProfile[9][1]->Fill(2.0,adc2[n]);
                        RPDProfile[9][1]->Fill(3.0,adc3[n]);
                        RPDProfile[9][1]->Fill(4.0,adc4[n]);
                        RPDProfile[9][1]->Fill(5.0,adc5[n]);
                    }

                    if (channel[n] == 15)
                    {
                        pRPD_ratio[13] = TS2[n] / TS3[n];

                        if (pRPD_ratio[13] > 1.6 && pRPD_ratio[13] < 2.4)
                        {
                        pRPD_sig[13] = TS2[n] - 0.4 * TS1[n];
                        } 

                        RPDProfile[13][0]->Fill(0.0,TS0[n]);
                        RPDProfile[13][0]->Fill(1.0,TS1[n]);
                        RPDProfile[13][0]->Fill(2.0,TS2[n]);
                        RPDProfile[13][0]->Fill(3.0,TS3[n]);
                        RPDProfile[13][0]->Fill(4.0,TS4[n]);
                        RPDProfile[13][0]->Fill(5.0,TS5[n]);

                        RPDProfile[13][1]->Fill(0.0,adc0[n]);
                        RPDProfile[13][1]->Fill(1.0,adc1[n]);
                        RPDProfile[13][1]->Fill(2.0,adc2[n]);
                        RPDProfile[13][1]->Fill(3.0,adc3[n]);
                        RPDProfile[13][1]->Fill(4.0,adc4[n]);
                        RPDProfile[13][1]->Fill(5.0,adc5[n]);
                    }

                    if (channel[n] == 16)
                    {
                        pRPD_ratio[1] = TS2[n] / TS3[n];

                        if (pRPD_ratio[1] > 1.5 && pRPD_ratio[1] < 2.7)
                        {
                        pRPD_sig[1] = TS2[n] - 0.4 * TS1[n];
                        }

                        RPDProfile[1][0]->Fill(0.0,TS0[n]);
                        RPDProfile[1][0]->Fill(1.0,TS1[n]);
                        RPDProfile[1][0]->Fill(2.0,TS2[n]);
                        RPDProfile[1][0]->Fill(3.0,TS3[n]);
                        RPDProfile[1][0]->Fill(4.0,TS4[n]);
                        RPDProfile[1][0]->Fill(5.0,TS5[n]);

                        RPDProfile[1][1]->Fill(0.0,adc0[n]);
                        RPDProfile[1][1]->Fill(1.0,adc1[n]);
                        RPDProfile[1][1]->Fill(2.0,adc2[n]);
                        RPDProfile[1][1]->Fill(3.0,adc3[n]);
                        RPDProfile[1][1]->Fill(4.0,adc4[n]);
                        RPDProfile[1][1]->Fill(5.0,adc5[n]);
                    }
                } // end rpd
            } // end channel loop
          
            ZDC[0] = 0.05 * pEM_sigtot + pHAD_sigtot;// + 0.01 * rpdtot;
            ZDC[1] = 0.07 * pEM_sigtot + pHAD_sigtot;// + 0.01 * rpdtot;
            ZDC[2] = 0.10 * pEM_sigtot + pHAD_sigtot;// + 0.01 * rpdtot;
            ZDC[3] = 0.12 * pEM_sigtot + pHAD_sigtot;// + 0.01 * rpdtot;

            Neutron[0]->Fill(ZDC[0], pEM_sigtot);
            Neutron[1]->Fill(ZDC[1], pEM_sigtot);
            Neutron[2]->Fill(ZDC[2], pEM_sigtot);
            Neutron[3]->Fill(ZDC[3], pEM_sigtot);

            //if (pEM_sigtot < 5000)
            //{
            ZDCDist[0]->Fill(ZDC[0]);
            ZDCDist[1]->Fill(ZDC[1]);
            ZDCDist[2]->Fill(ZDC[2]);
            ZDCDist[3]->Fill(ZDC[3]);
            //}

            pEMpositionvsSigTot[0]->Fill(ZDC[0],EMposition);
            pEMpositionvsSigTot[1]->Fill(ZDC[1],EMposition);
            pEMpositionvsSigTot[2]->Fill(ZDC[2],EMposition);
            pEMpositionvsSigTot[3]->Fill(ZDC[3],EMposition);

        } // end 0 to 200 cent
    } // end event loop
    

    gStyle->SetOptFit();

    Neutron[0]->SetXTitle("0.05 EM + HAD (fC), TS2 - 0.4 * TS1  RATIO CUT");
    Neutron[0]->SetYTitle("EM (fC)");

    Neutron[1]->SetXTitle("0.07 EM + HAD (fC), TS2 - 0.4 * TS1  RATIO CUT");
    Neutron[1]->SetYTitle("EM (fC)");

    Neutron[2]->SetXTitle("0.10 EM + HAD (fC), TS2 - 0.4 * TS1  RATIO CUT");
    Neutron[2]->SetYTitle("EM (fC)");

    Neutron[3]->SetXTitle("0.12 EM + HAD (fC), TS2 - 0.4 * TS1  RATIO CUT");
    Neutron[3]->SetYTitle("EM (fC)");

    ZDCDist[0]->SetXTitle("0.05 EM + HAD (fC), TS2 - 0.4 * TS1  RATIO CUT");
    ZDCDist[0]->SetYTitle("Counts");

    ZDCDist[1]->SetXTitle("0.07 EM + HAD (fC), TS2 - 0.4 * TS1  RATIO CUT");
    ZDCDist[1]->SetYTitle("Counts");

    ZDCDist[2]->SetXTitle("0.10 EM + HAD (fC), TS2 - 0.4 * TS1  RATIO CUT");
    ZDCDist[2]->SetYTitle("Counts");

    ZDCDist[3]->SetXTitle("0.12 EM + HAD (fC), TS2 - 0.4 * TS1  RATIO CUT");
    ZDCDist[3]->SetYTitle("Counts");
    
    pEMpositionvsSigTot[0]->SetXTitle("0.05 EM + HAD (fC), TS2 - 0.4 * TS1  RATIO CUT");
    pEMpositionvsSigTot[0]->SetYTitle("pos EM Position (cm)");

    pEMpositionvsSigTot[1]->SetXTitle("0.07 EM + HAD (fC), TS2 - 0.4 * TS1  RATIO CUT");
    pEMpositionvsSigTot[1]->SetYTitle("pos EM Position (cm)");

    pEMpositionvsSigTot[2]->SetXTitle("0.10 EM + HAD (fC), TS2 - 0.4 * TS1  RATIO CUT");
    pEMpositionvsSigTot[2]->SetYTitle("pos EM Position (cm)");

    pEMpositionvsSigTot[3]->SetXTitle("0.12 EM + HAD (fC), TS2 - 0.4 * TS1  RATIO CUT");
    pEMpositionvsSigTot[3]->SetYTitle("pos EM Position (cm)");

    TCanvas *c4 = new TCanvas();
    c4->Divide(4,4);
    for (int n = 0; n < 16; n++)
    {
        RPDProfile[n][0]->SetXTitle("Time Slice");
        RPDProfile[n][0]->SetYTitle("Total Charge (fC)");
        c4->cd(n+1);
        RPDProfile[n][0]->Draw("hist e");
    }

    TCanvas *c6 = new TCanvas();
    c4->Divide(4,4);
    for (int n = 0; n < 16; n++)
    {
        RPDProfile[n][1]->SetXTitle("Time Slice");
        RPDProfile[n][1]->SetYTitle("Total Charge (ADC)");
        c4->cd(n+1);
        RPDProfile[n][1]->Draw("hist e");
    }

    TCanvas *c5 = new TCanvas();
    c5->Divide(2,2);
    for (int n = 0; n < 4; n++)
    {
        HADProfile[n][0]->SetXTitle("Time Slice");
        HADProfile[n][0]->SetYTitle("Total Charge (fC)");
        c5->cd(n+1);
        HADProfile[n][0]->Draw("hist e");
    }

    TCanvas *c7 = new TCanvas();
    c7->Divide(2,2);
    for (int n = 0; n < 4; n++)
    {
        HADProfile[n][1]->SetXTitle("Time Slice");
        HADProfile[n][1]->SetYTitle("Total Charge (ADC)");
        c7->cd(n+1);
        HADProfile[n][1]->Draw("hist e");
    }

}