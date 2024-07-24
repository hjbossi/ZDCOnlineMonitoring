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
#include <string>


void RunThreeAnalysis()
{
    gROOT->ProcessLine("gErrorIgnoreLevel = 6001;");
    gROOT->ProcessLine("gPrintViaErrorHandler = kTRUE;");

    TChain *zdcchain = new TChain();
    TChain *hichain = new TChain();
    for (int x = 0 ; x < 24 ; x++)
    {
        // The paths for these data files are for the mignerey server, they are skims of the HiForest root files and only include minbias data
        // You will have to read in the root files from your own server 
        zdcchain->Add(Form("/store/data/Runs_2023/skims/374810/Run374810_MinBias%i.root/zdcdigi", x));
        hichain->Add(Form("/store/data/Runs_2023/skims/374810/Run374810_MinBias%i.root/HiTree", x));
    }
    zdcchain->AddFriend(hichain);

    //  Some variables are arrays of 56 because of how the data for these variables are stored in the root files
    int hibin;
    float sumPlus;
    float sumMinus;
    int zside[56];
    int section[56];
    int channel[56];

    float TS0[56];
    float TS1[56];
    float TS2[56];
    float TS3[56];
    float TS4[56];
    float TS5[56];

    int ADC0[56];
    int ADC1[56];
    int ADC2[56];
    int ADC3[56];
    int ADC4[56];
    int ADC5[56];

    // 16 rpd channels, 5 em channels, 4 had channels
    float RPD_ratio[16];
    float EM_ratio[5];
    float HAD_ratio[4];

    float RPD_sig[16];
    float EM_sig[5];
    float HAD_sig[4];

    // x position variables for rpd and EM
    float xrpd[5];
    float yrpd[5];
    float xem;

    float rpd_total;
    float em_total;

    // Declaration of variables in the root files, second argument is the variable we use for them in the code
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
    zdcchain->SetBranchAddress("adcTs0",&ADC0);
    zdcchain->SetBranchAddress("adcTs1",&ADC1);
    zdcchain->SetBranchAddress("adcTs2",&ADC2);
    zdcchain->SetBranchAddress("adcTs3",&ADC3);
    zdcchain->SetBranchAddress("adcTs4",&ADC4);
    zdcchain->SetBranchAddress("adcTs5",&ADC5);

    // Declaration of RPD plots
    // 16 rpd channels
    TH1F *RPD_TSDist[16];
    TH1F *RPD_TSRatio[16];
    TH1F *RPD_fCDist[16];

    for (int n = 0; n < 16; n++)
    {
        RPD_TSDist[n] = new TH1F(Form("h_block%d_rpdtsdist", n), Form("Run 374810 TS Dist All Centrality RPD+ Block %d", n), 6, 0, 6);
        RPD_TSDist[n]->SetXTitle("Time Slice");
        RPD_TSDist[n]->SetYTitle("Total Charge (fC)");
    }

    for (int n = 0; n < 16; n++)
    {
        RPD_TSRatio[n] = new TH1F(Form("h_block%d_rpdtsratio", n), Form("Run 374810 Ratio TS2 : TS3 All Centrality RPD+ Block %d", n), 100, 0, 10);
        RPD_TSRatio[n]->SetXTitle("TS2 : TS3");
        RPD_TSRatio[n]->SetYTitle("Counts");
    }

    for (int n = 0; n < 16; n++)
    {
        RPD_fCDist[n] = new TH1F(Form("h_block%d_rpdfCDist", n), Form("Run 374810 fC Dist All Centrality RPD+ Block %d", n), 100, 0, 100000);
        RPD_fCDist[n]->SetXTitle("TS2 (fC)");
        RPD_fCDist[n]->SetYTitle("Counts");
    }

    // Declaration of EM plots
    // 5 EM channels
    TH1F* EM_TSDist[5];
    TH1F* EM_TSRatio[5];
    TH1F* EM_fCDist[5];

    for (int n = 0; n < 5; n++)
    {
        EM_TSDist[n] = new TH1F(Form("h_block%d_emtsdist", n), Form("Run 374810 TS Dist All Centrality EM+ Channel %d", n), 6, 0, 6);
        EM_TSDist[n]->SetXTitle("Time Slice");
        EM_TSDist[n]->SetYTitle("Total Charge (fC)");
    }

    for (int n = 0; n < 5; n++)
    {
        EM_TSRatio[n] = new TH1F(Form("h_block%d_emtsratio", n), Form("Run 374810 Ratio TS2 : TS3 All Centrality EM+ Block %d", n),100, 0, 10);
        EM_TSRatio[n]->SetXTitle("TS2 : TS3");
        EM_TSRatio[n]->SetYTitle("Counts");
    }

    for (int n = 0; n < 5; n++)
    {
        EM_fCDist[n] = new TH1F(Form("h_block%d_emfCDist", n), Form("Run 374810 fC Dist All Centrality EM+ Block %d", n),100, 0, 200000);
        EM_fCDist[n]->SetXTitle("TS2 (fC)");
        EM_fCDist[n]->SetYTitle("Counts");
    }

    // Declaration of HAD plots
    // 4 HAD channels

    TH1F* HAD_TSDist[4];
    TH1F* HAD_TSRatio[4];
    TH1F* HAD_fCDist[4];

    for (int n = 0; n < 4; n++)
    {
        HAD_TSDist[n] = new TH1F(Form("h_block%d_hadtsdist", n),Form("Run 374810 TS Dist All Centrality HAD+ Channel %d", n),6, 0, 6);
        HAD_TSDist[n]->SetXTitle("Time Slice");
        HAD_TSDist[n]->SetYTitle("Total Charge (fC)");
    }

    for (int n = 0; n < 4; n++)
    {
        HAD_TSRatio[n] = new TH1F(Form("h_block%d_hadtsratio", n), Form("Run 374810 Ratio TS2 : TS3 All Centrality HAD+ Block %d", n), 100, 0, 10);
        HAD_TSRatio[n]->SetXTitle("TS2 : TS3");
        HAD_TSRatio[n]->SetYTitle("Counts");
    }

    for (int n = 0; n < 4; n++)
    {
        HAD_fCDist[n] = new TH1F(Form("h_block%d_hadfCDist", n), Form("Run 374810 fC Dist All Centrality HAD+ Block %d", n), 100, 0, 150000);
        HAD_fCDist[n]->SetXTitle("TS2 (fC)");
        HAD_fCDist[n]->SetYTitle("Counts");
    }
    
    // X Position plot for RPD
    TH1F *RPDx_position = new TH1F("RPD X Position","Run 374810 RPD X Position (cm) All Centrality",200,-4,4);

    // 2D Position plot for RPD 
    TH2F *RPD_COM = new TH2F("RPD Position","Run 374810 RPD Position (cm) All Centrality",200,-4,4,200,-4,4);

    // EM X Position plot
    TH1F *EM_COM = new TH1F("EM Position","Run 374810 EM Position (cm) All Centrality",200,-5,5);

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
    if (hibin >= 0 && hibin <= 200)
    {

        for (int n = 0; n < 56; n++)
        {
            if (zside[n] == 1 & section[n] == 4)
            {
                if (channel[n] == 1)
                {
                    // Fill TS Distributions
                    RPD_TSDist[10]->Fill(0.0,TS0[n]);
                    RPD_TSDist[10]->Fill(1.0,TS1[n]);
                    RPD_TSDist[10]->Fill(2.0,TS2[n]);
                    RPD_TSDist[10]->Fill(3.0,TS3[n]);
                    RPD_TSDist[10]->Fill(4.0,TS4[n]);
                    RPD_TSDist[10]->Fill(5.0,TS5[n]);

                    //Fill TS Ratios 
                    RPD_ratio[10] = TS2[n] / TS3[n];
                    RPD_TSRatio[10]->Fill(RPD_ratio[10]);

                    //Fill fC Distributions (signal distributions)
                    RPD_sig[10] = TS2[n];
                    RPD_fCDist[10]->Fill(RPD_sig[10]);
                }

                if (channel[n] == 2)
                {
                    // Fill TS Distributions
                    RPD_TSDist[6]->Fill(0.0,TS0[n]);
                    RPD_TSDist[6]->Fill(1.0,TS1[n]);
                    RPD_TSDist[6]->Fill(2.0,TS2[n]);
                    RPD_TSDist[6]->Fill(3.0,TS3[n]);
                    RPD_TSDist[6]->Fill(4.0,TS4[n]);
                    RPD_TSDist[6]->Fill(5.0,TS5[n]);

                    //Fill TS Ratios 
                    RPD_ratio[6] = TS2[n] / TS3[n];
                    RPD_TSRatio[6]->Fill(RPD_ratio[6]);

                    //Fill fC Distributions (signal distributions)
                    RPD_sig[6] = TS2[n];
                    RPD_fCDist[6]->Fill(RPD_sig[6]);
                }
                if (channel[n] == 3)
                {
                    // Fill TS Distributions
                    RPD_TSDist[2]->Fill(0.0,TS0[n]);
                    RPD_TSDist[2]->Fill(1.0,TS1[n]);
                    RPD_TSDist[2]->Fill(2.0,TS2[n]);
                    RPD_TSDist[2]->Fill(3.0,TS3[n]);
                    RPD_TSDist[2]->Fill(4.0,TS4[n]);
                    RPD_TSDist[2]->Fill(5.0,TS5[n]);

                    //Fill TS Ratios 
                    RPD_ratio[2] = TS2[n] / TS3[n];
                    RPD_TSRatio[2]->Fill(RPD_ratio[2]);

                    //Fill fC Distributions (signal distributions)
                    RPD_sig[2] = TS2[n];
                    RPD_fCDist[2]->Fill(RPD_sig[2]);
                }

                if (channel[n] == 4)
                {
                    // Fill TS Distributions
                    RPD_TSDist[14]->Fill(0.0,TS0[n]);
                    RPD_TSDist[14]->Fill(1.0,TS1[n]);
                    RPD_TSDist[14]->Fill(2.0,TS2[n]);
                    RPD_TSDist[14]->Fill(3.0,TS3[n]);
                    RPD_TSDist[14]->Fill(4.0,TS4[n]);
                    RPD_TSDist[14]->Fill(5.0,TS5[n]);

                    //Fill TS Ratios 
                    RPD_ratio[14] = TS2[n] / TS3[n];
                    RPD_TSRatio[14]->Fill(RPD_ratio[14]);

                    //Fill fC Distributions (signal distributions)
                    RPD_sig[14] = TS2[n];
                    RPD_fCDist[14]->Fill(RPD_sig[14]);
                }

                if (channel[n] == 5)
                {
                    // Fill TS Distributions
                    RPD_TSDist[11]->Fill(0.0,TS0[n]);
                    RPD_TSDist[11]->Fill(1.0,TS1[n]);
                    RPD_TSDist[11]->Fill(2.0,TS2[n]);
                    RPD_TSDist[11]->Fill(3.0,TS3[n]);
                    RPD_TSDist[11]->Fill(4.0,TS4[n]);
                    RPD_TSDist[11]->Fill(5.0,TS5[n]);

                    //Fill TS Ratios 
                    RPD_ratio[11] = TS2[n] / TS3[n];
                    RPD_TSRatio[11]->Fill(RPD_ratio[11]);

                    //Fill fC Distributions (signal distributions)
                    RPD_sig[11] = TS2[n];
                    RPD_fCDist[11]->Fill(RPD_sig[11]);
                }
                if (channel[n] == 6)
                {
                    // Fill TS Distributions
                    RPD_TSDist[7]->Fill(0.0,TS0[n]);
                    RPD_TSDist[7]->Fill(1.0,TS1[n]);
                    RPD_TSDist[7]->Fill(2.0,TS2[n]);
                    RPD_TSDist[7]->Fill(3.0,TS3[n]);
                    RPD_TSDist[7]->Fill(4.0,TS4[n]);
                    RPD_TSDist[7]->Fill(5.0,TS5[n]);

                    //Fill TS Ratios 
                    RPD_ratio[7] = TS2[n] / TS3[n];
                    RPD_TSRatio[7]->Fill(RPD_ratio[7]);

                    //Fill fC Distributions (signal distributions)
                    RPD_sig[7] = TS2[n];
                    RPD_fCDist[7]->Fill(RPD_sig[7]);
                }

                if (channel[n] == 7)
                {
                    // Fill TS Distributions
                    RPD_TSDist[3]->Fill(0.0,TS0[n]);
                    RPD_TSDist[3]->Fill(1.0,TS1[n]);
                    RPD_TSDist[3]->Fill(2.0,TS2[n]);
                    RPD_TSDist[3]->Fill(3.0,TS3[n]);
                    RPD_TSDist[3]->Fill(4.0,TS4[n]);
                    RPD_TSDist[3]->Fill(5.0,TS5[n]);

                    //Fill TS Ratios 
                    RPD_ratio[3] = TS2[n] / TS3[n];
                    RPD_TSRatio[3]->Fill(RPD_ratio[3]);

                    //Fill fC Distributions (signal distributions)
                    RPD_sig[3] = TS2[n];
                    RPD_fCDist[3]->Fill(RPD_sig[3]);
                }

                if (channel[n] == 8)
                {
                    // Fill TS Distributions
                    RPD_TSDist[15]->Fill(0.0,TS0[n]);
                    RPD_TSDist[15]->Fill(1.0,TS1[n]);
                    RPD_TSDist[15]->Fill(2.0,TS2[n]);
                    RPD_TSDist[15]->Fill(3.0,TS3[n]);
                    RPD_TSDist[15]->Fill(4.0,TS4[n]);
                    RPD_TSDist[15]->Fill(5.0,TS5[n]);

                    //Fill TS Ratios 
                    RPD_ratio[15] = TS2[n] / TS3[n];
                    RPD_TSRatio[15]->Fill(RPD_ratio[15]);

                    //Fill fC Distributions (signal distributions)
                    RPD_sig[15] = TS2[n];
                    RPD_fCDist[15]->Fill(RPD_sig[15]);
                }

                if (channel[n] == 9)
                {
                    // Fill TS Distributions
                    RPD_TSDist[4]->Fill(0.0,TS0[n]);
                    RPD_TSDist[4]->Fill(1.0,TS1[n]);
                    RPD_TSDist[4]->Fill(2.0,TS2[n]);
                    RPD_TSDist[4]->Fill(3.0,TS3[n]);
                    RPD_TSDist[4]->Fill(4.0,TS4[n]);
                    RPD_TSDist[4]->Fill(5.0,TS5[n]);

                    //Fill TS Ratios 
                    RPD_ratio[4] = TS2[n] / TS3[n];
                    RPD_TSRatio[4]->Fill(RPD_ratio[4]);

                    //Fill fC Distributions (signal distributions)
                    RPD_sig[4] = TS2[n];
                    RPD_fCDist[4]->Fill(RPD_sig[4]);
                }

                if (channel[n] == 10)
                {
                    // Fill TS Distributions
                    RPD_TSDist[8]->Fill(0.0,TS0[n]);
                    RPD_TSDist[8]->Fill(1.0,TS1[n]);
                    RPD_TSDist[8]->Fill(2.0,TS2[n]);
                    RPD_TSDist[8]->Fill(3.0,TS3[n]);
                    RPD_TSDist[8]->Fill(4.0,TS4[n]);
                    RPD_TSDist[8]->Fill(5.0,TS5[n]);

                    //Fill TS Ratios 
                    RPD_ratio[8] = TS2[n] / TS3[n];
                    RPD_TSRatio[8]->Fill(RPD_ratio[8]);

                    //Fill fC Distributions (signal distributions)
                    RPD_sig[8] = TS2[n];
                    RPD_fCDist[8]->Fill(RPD_sig[8]);
                }

                if (channel[n] == 11)
                {
                    // Fill TS Distributions
                    RPD_TSDist[12]->Fill(0.0,TS0[n]);
                    RPD_TSDist[12]->Fill(1.0,TS1[n]);
                    RPD_TSDist[12]->Fill(2.0,TS2[n]);
                    RPD_TSDist[12]->Fill(3.0,TS3[n]);
                    RPD_TSDist[12]->Fill(4.0,TS4[n]);
                    RPD_TSDist[12]->Fill(5.0,TS5[n]);

                    //Fill TS Ratios 
                    RPD_ratio[12] = TS2[n] / TS3[n];
                    RPD_TSRatio[12]->Fill(RPD_ratio[12]);

                    //Fill fC Distributions (signal distributions)
                    RPD_sig[12] = TS2[n];
                    RPD_fCDist[12]->Fill(RPD_sig[12]);
                }

                if (channel[n] == 12)
                {
                    // Fill TS Distributions
                    RPD_TSDist[0]->Fill(0.0,TS0[n]);
                    RPD_TSDist[0]->Fill(1.0,TS1[n]);
                    RPD_TSDist[0]->Fill(2.0,TS2[n]);
                    RPD_TSDist[0]->Fill(3.0,TS3[n]);
                    RPD_TSDist[0]->Fill(4.0,TS4[n]);
                    RPD_TSDist[0]->Fill(5.0,TS5[n]);

                    //Fill TS Ratios 
                    RPD_ratio[0] = TS2[n] / TS3[n];
                    RPD_TSRatio[0]->Fill(RPD_ratio[0]);

                    //Fill fC Distributions (signal distributions)
                    RPD_sig[0] = TS2[n];
                    RPD_fCDist[0]->Fill(RPD_sig[0]);
                }

                if (channel[n] == 13)
                {
                    // Fill TS Distributions
                    RPD_TSDist[5]->Fill(0.0,TS0[n]);
                    RPD_TSDist[5]->Fill(1.0,TS1[n]);
                    RPD_TSDist[5]->Fill(2.0,TS2[n]);
                    RPD_TSDist[5]->Fill(3.0,TS3[n]);
                    RPD_TSDist[5]->Fill(4.0,TS4[n]);
                    RPD_TSDist[5]->Fill(5.0,TS5[n]);

                    //Fill TS Ratios 
                    RPD_ratio[5] = TS2[n] / TS3[n];
                    RPD_TSRatio[5]->Fill(RPD_ratio[5]);

                    //Fill fC Distributions (signal distributions)
                    RPD_sig[5] = TS2[n];
                    RPD_fCDist[5]->Fill(RPD_sig[5]);
                }

                if (channel[n] == 14)
                {
                    // Fill TS Distributions
                    RPD_TSDist[9]->Fill(0.0,TS0[n]);
                    RPD_TSDist[9]->Fill(1.0,TS1[n]);
                    RPD_TSDist[9]->Fill(2.0,TS2[n]);
                    RPD_TSDist[9]->Fill(3.0,TS3[n]);
                    RPD_TSDist[9]->Fill(4.0,TS4[n]);
                    RPD_TSDist[9]->Fill(5.0,TS5[n]);

                    //Fill TS Ratios 
                    RPD_ratio[9] = TS2[n] / TS3[n];
                    RPD_TSRatio[9]->Fill(RPD_ratio[9]);

                    //Fill fC Distributions (signal distributions)
                    RPD_sig[9] = TS2[n];
                    RPD_fCDist[9]->Fill(RPD_sig[9]);
                }

                if (channel[n] == 15)
                {
                    // Fill TS Distributions
                    RPD_TSDist[13]->Fill(0.0,TS0[n]);
                    RPD_TSDist[13]->Fill(1.0,TS1[n]);
                    RPD_TSDist[13]->Fill(2.0,TS2[n]);
                    RPD_TSDist[13]->Fill(3.0,TS3[n]);
                    RPD_TSDist[13]->Fill(4.0,TS4[n]);
                    RPD_TSDist[13]->Fill(5.0,TS5[n]);

                    //Fill TS Ratios 
                    RPD_ratio[13] = TS2[n] / TS3[n];
                    RPD_TSRatio[13]->Fill(RPD_ratio[13]);

                    //Fill fC Distributions (signal distributions)
                    RPD_sig[13] = TS2[n];
                    RPD_fCDist[13]->Fill(RPD_sig[13]);
                }

                if (channel[n] == 16)
                {
                    // Fill TS Distributions
                    RPD_TSDist[1]->Fill(0.0,TS0[n]);
                    RPD_TSDist[1]->Fill(1.0,TS1[n]);
                    RPD_TSDist[1]->Fill(2.0,TS2[n]);
                    RPD_TSDist[1]->Fill(3.0,TS3[n]);
                    RPD_TSDist[1]->Fill(4.0,TS4[n]);
                    RPD_TSDist[1]->Fill(5.0,TS5[n]);

                    //Fill TS Ratios 
                    RPD_ratio[1] = TS2[n] / TS3[n];
                    RPD_TSRatio[1]->Fill(RPD_ratio[1]);

                    //Fill fC Distributions (signal distributions)
                    RPD_sig[1] = TS2[n];
                    RPD_fCDist[1]->Fill(RPD_sig[1]);
                }
                xrpd[0] = RPD_sig[0] + RPD_sig[4] + RPD_sig[8] + RPD_sig[12];
                xrpd[1] = RPD_sig[1] + RPD_sig[5] + RPD_sig[9] + RPD_sig[13];
                xrpd[2] = RPD_sig[2] + RPD_sig[6] + RPD_sig[10] + RPD_sig[14];
                xrpd[3] = RPD_sig[3] + RPD_sig[7] + RPD_sig[11] + RPD_sig[15];

                // Total position for rpd, per event, the coefficients are weighting each column by its position in the rpd
                // The coordinate system has the center of the rpd at 0,0
                // The middle of the columns to the left and right are at -1 and 1
                // The middle of the columns to the far left and far right are at -3 and 3
                // We are saying that the signal comes from within the middle of each block / column of blocks
                

                yrpd[0] = RPD_sig[0] + RPD_sig[1] + RPD_sig[2] + RPD_sig[3];
                yrpd[1] = RPD_sig[4] + RPD_sig[5] + RPD_sig[6] + RPD_sig[7];
                yrpd[2] = RPD_sig[8] + RPD_sig[9] + RPD_sig[10] + RPD_sig[11];
                yrpd[3] = RPD_sig[12] + RPD_sig[13] + RPD_sig[14] + RPD_sig[15];

                rpd_total = xrpd[0] + xrpd[1] + xrpd[2] + xrpd[3];

                xrpd[4] = ((-3 * xrpd[0]) + (-1 * xrpd[1]) + (1 * xrpd[2]) + (3 * xrpd[3])) / rpd_total;

                yrpd[4] = ((3 * yrpd[0]) + (1 * yrpd[1]) + (-1 * yrpd[2]) + (-3 * yrpd[3])) / rpd_total;

            } // end rpd
            if (zside[n] == 1 & section[n] == 1)
            {
                if (channel[n] == 1)
                {
                    EM_TSDist[0]->Fill(0.0,TS0[n]);
                    EM_TSDist[0]->Fill(1.0,TS1[n]);
                    EM_TSDist[0]->Fill(2.0,TS2[n]);
                    EM_TSDist[0]->Fill(3.0,TS3[n]);
                    EM_TSDist[0]->Fill(4.0,TS4[n]);
                    EM_TSDist[0]->Fill(5.0,TS5[n]);

                    EM_ratio[0] = TS2[n] / TS3[n];
                    EM_TSRatio[0]->Fill(EM_ratio[0]);

                    EM_sig[0] = TS2[n];
                    EM_fCDist[0]->Fill(EM_sig[0]);
                }

                if (channel[n] == 2)
                {
                    EM_TSDist[1]->Fill(0.0,TS0[n]);
                    EM_TSDist[1]->Fill(1.0,TS1[n]);
                    EM_TSDist[1]->Fill(2.0,TS2[n]);
                    EM_TSDist[1]->Fill(3.0,TS3[n]);
                    EM_TSDist[1]->Fill(4.0,TS4[n]);
                    EM_TSDist[1]->Fill(5.0,TS5[n]);

                    EM_ratio[1] = TS2[n] / TS3[n];
                    EM_TSRatio[1]->Fill(EM_ratio[1]);

                    EM_sig[1] = TS2[n];
                    EM_fCDist[1]->Fill(EM_sig[1]);
                }

                if (channel[n] == 3)
                {
                    EM_TSDist[2]->Fill(0.0,TS0[n]);
                    EM_TSDist[2]->Fill(1.0,TS1[n]);
                    EM_TSDist[2]->Fill(2.0,TS2[n]);
                    EM_TSDist[2]->Fill(3.0,TS3[n]);
                    EM_TSDist[2]->Fill(4.0,TS4[n]);
                    EM_TSDist[2]->Fill(5.0,TS5[n]);

                    EM_ratio[2] = TS2[n] / TS3[n];
                    EM_TSRatio[2]->Fill(EM_ratio[2]);

                    EM_sig[2] = TS2[n];
                    EM_fCDist[2]->Fill(EM_sig[2]);
                }

                if (channel[n] == 4)
                {
                    EM_TSDist[3]->Fill(0.0,TS0[n]);
                    EM_TSDist[3]->Fill(1.0,TS1[n]);
                    EM_TSDist[3]->Fill(2.0,TS2[n]);
                    EM_TSDist[3]->Fill(3.0,TS3[n]);
                    EM_TSDist[3]->Fill(4.0,TS4[n]);
                    EM_TSDist[3]->Fill(5.0,TS5[n]);

                    EM_ratio[3] = TS2[n] / TS3[n];
                    EM_TSRatio[3]->Fill(EM_ratio[3]);

                    EM_sig[3] = TS2[n];
                    EM_fCDist[3]->Fill(EM_sig[3]);
                }

                if (channel[n] == 5)
                {
                    EM_TSDist[4]->Fill(0.0,TS0[n]);
                    EM_TSDist[4]->Fill(1.0,TS1[n]);
                    EM_TSDist[4]->Fill(2.0,TS2[n]);
                    EM_TSDist[4]->Fill(3.0,TS3[n]);
                    EM_TSDist[4]->Fill(4.0,TS4[n]);
                    EM_TSDist[4]->Fill(5.0,TS5[n]);

                    EM_ratio[4] = TS2[n] / TS3[n];
                    EM_TSRatio[4]->Fill(EM_ratio[4]);

                    EM_sig[4] = TS2[n];
                    EM_fCDist[4]->Fill(EM_sig[4]);
                }

                //  The first set of coefficients are relative gains for the EM, since not every PMT for each channel has the same gain 
                //  The gains are relative to channel 3, thats why the relative gain for channel 3 is 1. 
                //  The second set of coefficients are position weights. They are the middle of each section / block in the EM
                //  The middle of channel 3 is x = 0, and the middle of the EM sections on either side increase / decrease by 1.8 cm
                em_total = (0.6 * EM_sig[0]) + (0.89 * EM_sig[1]) + (1 * EM_sig[2]) + (1.29 * EM_sig[3]) + (0.57 * EM_sig[4]);
                xem = ((0.6 * -3.6 * EM_sig[0]) + (0.89 * -1.8 * EM_sig[1]) + (1* 0 * EM_sig[2]) + (1.29 * 1.8 * EM_sig[3]) + (0.57 * 3.6 * EM_sig[4])) / em_total;
            } // end of EM
            if (zside[n] == 1 && section[n] == 2)
            {
                if (channel[n] == 1)
                {
                    HAD_TSDist[0]->Fill(0.0,TS0[n]);
                    HAD_TSDist[0]->Fill(1.0,TS1[n]);
                    HAD_TSDist[0]->Fill(2.0,TS2[n]);
                    HAD_TSDist[0]->Fill(3.0,TS3[n]);
                    HAD_TSDist[0]->Fill(4.0,TS4[n]);
                    HAD_TSDist[0]->Fill(5.0,TS5[n]);

                    HAD_ratio[0] = TS2[n] / TS3[n];
                    HAD_TSRatio[0]->Fill(HAD_ratio[0]);

                    HAD_sig[0] = TS2[n];
                    HAD_fCDist[0]->Fill(HAD_sig[0]);
                }

                if (channel[n] == 2)
                {
                    HAD_TSDist[1]->Fill(0.0,TS0[n]);
                    HAD_TSDist[1]->Fill(1.0,TS1[n]);
                    HAD_TSDist[1]->Fill(2.0,TS2[n]);
                    HAD_TSDist[1]->Fill(3.0,TS3[n]);
                    HAD_TSDist[1]->Fill(4.0,TS4[n]);
                    HAD_TSDist[1]->Fill(5.0,TS5[n]);

                    HAD_ratio[1] = TS2[n] / TS3[n];
                    HAD_TSRatio[1]->Fill(HAD_ratio[1]);

                    HAD_sig[1] = TS2[n];
                    HAD_fCDist[1]->Fill(HAD_sig[1]);
                }

                if (channel[n] == 3)
                {
                    HAD_TSDist[2]->Fill(0.0,TS0[n]);
                    HAD_TSDist[2]->Fill(1.0,TS1[n]);
                    HAD_TSDist[2]->Fill(2.0,TS2[n]);
                    HAD_TSDist[2]->Fill(3.0,TS3[n]);
                    HAD_TSDist[2]->Fill(4.0,TS4[n]);
                    HAD_TSDist[2]->Fill(5.0,TS5[n]);

                    HAD_ratio[2] = TS2[n] / TS3[n];
                    HAD_TSRatio[2]->Fill(HAD_ratio[2]);

                    HAD_sig[2] = TS2[n];
                    HAD_fCDist[2]->Fill(HAD_sig[2]);
                }

                if (channel[n] == 4)
                {
                    HAD_TSDist[3]->Fill(0.0,TS0[n]);
                    HAD_TSDist[3]->Fill(1.0,TS1[n]);
                    HAD_TSDist[3]->Fill(2.0,TS2[n]);
                    HAD_TSDist[3]->Fill(3.0,TS3[n]);
                    HAD_TSDist[3]->Fill(4.0,TS4[n]);
                    HAD_TSDist[3]->Fill(5.0,TS5[n]);

                    HAD_ratio[3] = TS2[n] / TS3[n];
                    HAD_TSRatio[3]->Fill(HAD_ratio[3]);

                    HAD_sig[3] = TS2[n];
                    HAD_fCDist[3]->Fill(HAD_sig[3]);
                }
                
            } // end HAD
        } // end channel loop
        
            RPDx_position->Fill(xrpd[4]);
            RPD_COM->Fill(xrpd[4],yrpd[4]);
            EM_COM->Fill(xem);
        
    } // end hibin (centrality) 0 - 200 is all centrality, 0 - 20 is 0 to 10% centrality
    } // end event loop

    /*
    TCanvas *c1 = new TCanvas();
    c1->Divide(4,4);
    for (int n = 0; n < 16; n++)
    {
        c1->cd(n+1);
        RPD_TSDist[n]->Draw("hist e");
    }

    TCanvas *c2 = new TCanvas();
    c2->Divide(4,4);
    for (int n = 0; n < 16; n++)
    {
        c2->cd(n+1);
        RPD_TSRatio[n]->Draw();
    }

    TCanvas *c3 = new TCanvas();
    c3->Divide(4,4);
    for (int n = 0; n < 16; n++)
    {
        c3->cd(n+1);
        RPD_fCDist[n]->Draw();
    }

    TCanvas *c4 = new TCanvas();
    c4->Divide(3,2);
    for (int n = 0; n < 5; n++)
    {
        c4->cd(n+1);
        EM_TSDist[n]->Draw("hist e");
    }

    TCanvas *c5 = new TCanvas();
    c5->Divide(3,2);
    for (int n = 0; n < 5; n++)
    {
        c5->cd(n+1);
        EM_TSRatio[n]->Draw();
    }

    TCanvas *c6 = new TCanvas();
    c6->Divide(3,2);
    for (int n = 0; n < 5; n++)
    {
        c6->cd(n+1);
        EM_fCDist[n]->Draw();
    }

    TCanvas *c7 = new TCanvas();
    c7->Divide(2,2);
    for (int n = 0; n < 4; n++)
    {
        c7->cd(n+1);
        HAD_TSDist[n]->Draw("hist e");
    }

    TCanvas *c8 = new TCanvas();
    c8->Divide(2,2);
    for (int n = 0; n < 4; n++)
    {
        c8->cd(n+1);
        HAD_TSRatio[n]->Draw();
    }

    TCanvas *c9 = new TCanvas();
    c9->Divide(2,2);
    for (int n = 0; n < 4; n++)
    {
        c9->cd(n+1);
        HAD_fCDist[n]->Draw();
    }
    */

    TCanvas *c10 = new TCanvas();
    c10->cd(1);
    RPDx_position->Draw();

    TCanvas *c11 = new TCanvas();
    c11->cd(1);
    RPD_COM->Draw("colz");

    TCanvas *c12 = new TCanvas();
    c12->cd(1);
    EM_COM->Draw();


}