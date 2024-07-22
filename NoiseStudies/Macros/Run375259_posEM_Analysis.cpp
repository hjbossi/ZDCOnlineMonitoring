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
#include "TF1.h"
#include "TGraphErrors.h"

void Run375259_posEM_Analysis() 
{

    // run code again for RPD
    // run code with calibration factors
    TChain *zdcchain = new TChain();
    TChain *hichain = new TChain();
    for (int x = 1 ; x < 135 ; x++){
        if(x == 116) continue;
        zdcchain->Add(Form("/store/data/Runs_2023/375259/240112_203159/0000/HiForestMiniAOD_%i.root/zdcanalyzer/zdcdigi", x));
        hichain->Add(Form("/store/data/Runs_2023/375259/240112_203159/0000/HiForestMiniAOD_%i.root/hiEvtAnalyzer/HiTree", x));
    }

    zdcchain->AddFriend(hichain);

    TH1F *Run375259_pEM_TS[5] = {0};

        Run375259_pEM_TS[0] = new TH1F("","Run 375259 pEM section 1",6,0,6);
        Run375259_pEM_TS[1] = new TH1F("","Run 375259 pEM section 2",6,0,6);
        Run375259_pEM_TS[2] = new TH1F("","Run 375259 pEM section 3",6,0,6);
        Run375259_pEM_TS[3] = new TH1F("","Run 375259 pEM section 4",6,0,6);
        Run375259_pEM_TS[4] = new TH1F("","Run 375259 pEM section 5",6,0,6);
    
    TH1F *Run375259_pEM_TSratio[5] = {0};

        Run375259_pEM_TSratio[0] = new TH1F("","Run 375259 pEM TS Ratio Section 1",60,0,6);
        Run375259_pEM_TSratio[1] = new TH1F("","Run 375259 pEM TS Ratio Section 2",60,0,6);
        Run375259_pEM_TSratio[2] = new TH1F("","Run 375259 pEM TS Ratio Section 3",60,0,6);
        Run375259_pEM_TSratio[3] = new TH1F("","Run 375259 pEM TS Ratio Section 4",60,0,6);
        Run375259_pEM_TSratio[4] = new TH1F("","Run 375259 pEM TS Ratio Section 5",60,0,6);

    TH1F *Run375259_pEM_fC[5] = {0};

        Run375259_pEM_fC[0] = new TH1F("","Run 375259 pEM Section 0 fC Distribution",100,0,100000);
        Run375259_pEM_fC[1] = new TH1F("","Run 375259 pEM Section 1 fC Distribution",100,0,100000);    
        Run375259_pEM_fC[2] = new TH1F("","Run 375259 pEM Section 2 fC Distribution",100,0,100000);
        Run375259_pEM_fC[3] = new TH1F("","Run 375259 pEM Section 3 fC Distribution",100,0,100000);
        Run375259_pEM_fC[4] = new TH1F("","Run 375259 pEM Section 4 fC Distribution",100,0,100000);

    TH1F *Run375259_pEM_COMvsCent[10] = {0};

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

    TProfile *Run375259_pEM_Profile[10] = {0};

        Run375259_pEM_Profile[0] = new TProfile("","Run 375259 pEM Avg Signal vs X Position 0 to 10 Centrality",5,0,5);
        Run375259_pEM_Profile[1] = new TProfile("","Run 375259 pEM Avg Signal vs X Position 10 to 20 Centrality",5,0,5);
        Run375259_pEM_Profile[2] = new TProfile("","Run 375259 pEM Avg Signal vs X Position 20 to 30 Centrality",5,0,5);
        Run375259_pEM_Profile[3] = new TProfile("","Run 375259 pEM Avg Signal vs X Position 30 to 40 Centrality",5,0,5);
        Run375259_pEM_Profile[4] = new TProfile("","Run 375259 pEM Avg Signal vs X Position 40 to 50 Centrality",5,0,5);
        Run375259_pEM_Profile[5] = new TProfile("","Run 375259 pEM Avg Signal vs X Position 50 to 60 Centrality",5,0,5);
        Run375259_pEM_Profile[6] = new TProfile("","Run 375259 pEM Avg Signal vs X Position 60 to 70 Centrality",5,0,5);
        Run375259_pEM_Profile[7] = new TProfile("","Run 375259 pEM Avg Signal vs X Position 70 to 80 Centrality",5,0,5);
        Run375259_pEM_Profile[8] = new TProfile("","Run 375259 pEM Avg Signal vs X Position 80 to 90 Centrality",5,0,5);
        Run375259_pEM_Profile[9] = new TProfile("","Run 375259 pEM Avg Signal vs X Position 90 to 100 Centrality",5,0,5);

    THStack *pEM_stack = new THStack("","Run 375259 pEM X Distribution with Centrality");

    int hibin = 0;
    int zside[56];
    int section[56];
    int channel[56];

    double pEM_ratio[5];
    double pEM_signal[5][10];

    float pEM_sum;
    double pEM_signal_col[10];
    double pEM_signal_total[10];

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

     Int_t NumofEvents = zdcchain->GetEntries();
	    cout << "Total # of events = " << NumofEvents << endl;
            for (int i = 0; i < NumofEvents; i++) {           
		        zdcchain->GetEntry(i);  
                hichain->GetEntry(i);
                for (int n = 0; n < 56; n++) {
                        if (zside[n] == 1 && section[n] == 1) {
                            //cout << (TS2[n] + TS3[n]) << endl;
                        pEM_sum += TS2[n] + TS3[n];
                        }
                }
                //cout << pEM_sum << endl;
                if (pEM_sum > 1000) {
                if (hibin >=0 && hibin < 20 ){ 
                    
                            for (int n = 0; n < 56; n++) {
                                if (zside[n] == 1 && section[n] == 1) {
                                if (channel[n] == 1) {
                                    Run375259_pEM_TS[0]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[0]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[0]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[0]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[0]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[0]->Fill(5.0, TS5[n]);

                                    pEM_ratio[0] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[0]->Fill(pEM_ratio[0]);

                                    if (pEM_ratio[0] > 3.6967 && pEM_ratio[0] < 4.8773){
                                        pEM_signal[0][0] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[0]->Fill(pEM_signal[0][0]);

                                }
                                if (channel[n] == 2) {
                                    Run375259_pEM_TS[1]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[1]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[1]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[1]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[1]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[1]->Fill(5.0, TS5[n]);

                                    pEM_ratio[1] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[1]->Fill(pEM_ratio[1]);

                                    if (pEM_ratio[1] > 3.9674 && pEM_ratio[1] < 4.5806){
                                        pEM_signal[1][0] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[1]->Fill(pEM_signal[1][0]);
                                }
                                if (channel[n] == 3){
                                    Run375259_pEM_TS[2]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[2]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[2]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[2]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[2]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[2]->Fill(5.0, TS5[n]);

                                    pEM_ratio[2] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[2]->Fill(pEM_ratio[2]);

                                    if (pEM_ratio[2] > 3.6616 && pEM_ratio[2] < 4.1064){
                                        pEM_signal[2][0] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[2]->Fill(pEM_signal[2][0]);
                                }
                                if (channel[n] == 4){
                                    Run375259_pEM_TS[3]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[3]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[3]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[3]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[3]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[3]->Fill(5.0, TS5[n]);

                                    pEM_ratio[3] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[3]->Fill(pEM_ratio[3]);

                                    if (pEM_ratio[3] > 3.5942 && pEM_ratio[3] < 3.8438){
                                        pEM_signal[3][0] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[3]->Fill(pEM_signal[3][0]);
                                }
                                if (channel[n] == 5){
                                    Run375259_pEM_TS[4]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[4]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[4]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[4]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[4]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[4]->Fill(5.0, TS5[n]);

                                    pEM_ratio[4] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[4]->Fill(pEM_ratio[4]);

                                    if (pEM_ratio[4] > 3.4296 && pEM_ratio[4] < 3.6964){
                                        pEM_signal[4][0] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[4]->Fill(pEM_signal[4][0]);
                                }
                                pEM_signal_total[0] = (0.6 * pEM_signal[0][0]) + (0.89 * pEM_signal[1][0]) + (1 * pEM_signal[2][0]) + (1.29 * pEM_signal[3][0]) + (0.57 * pEM_signal[4][0]);
                                pEM_signal_col[0] = ((-3.6 * 0.6 * pEM_signal[0][0]) + (-1.8 * 0.89 * pEM_signal[1][0]) + (0 * 1 * pEM_signal[2][0]) + (1.8 * 1.29 * pEM_signal[3][0]) + (3.6 * 0.57 * pEM_signal[4][0])) / pEM_signal_total[0];

                            } // end of side & section
                        } // end channel loop
                        Run375259_pEM_COMvsCent[0]->Fill(pEM_signal_col[0]);

                        Run375259_pEM_Profile[0]->Fill(0.0 , pEM_signal[0][0]);
                        Run375259_pEM_Profile[0]->Fill(1.0 , pEM_signal[1][0]);
                        Run375259_pEM_Profile[0]->Fill(2.0 , pEM_signal[2][0]);
                        Run375259_pEM_Profile[0]->Fill(3.0 , pEM_signal[3][0]);
                        Run375259_pEM_Profile[0]->Fill(4.0 , pEM_signal[4][0]);
                } // end centrality
                if (hibin >=20 && hibin < 40 ){ 
                            for (int n = 0; n < 56; n++) {
                                if (zside[n] == 1 && section[n] == 1) {
                                if (channel[n] == 1) {
                                    Run375259_pEM_TS[0]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[0]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[0]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[0]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[0]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[0]->Fill(5.0, TS5[n]);

                                    pEM_ratio[0] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[0]->Fill(pEM_ratio[0]);

                                    if (pEM_ratio[0] > 3.6967 && pEM_ratio[0] < 4.8773){
                                        pEM_signal[0][1] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[0]->Fill(pEM_signal[0][1]);

                                }
                                if (channel[n] == 2) {
                                    Run375259_pEM_TS[1]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[1]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[1]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[1]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[1]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[1]->Fill(5.0, TS5[n]);

                                    pEM_ratio[1] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[1]->Fill(pEM_ratio[1]);

                                    if (pEM_ratio[1] > 3.9674 && pEM_ratio[1] < 4.5806){
                                        pEM_signal[1][1] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[1]->Fill(pEM_signal[1][1]);
                                }
                                if (channel[n] == 3){
                                    Run375259_pEM_TS[2]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[2]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[2]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[2]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[2]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[2]->Fill(5.0, TS5[n]);

                                    pEM_ratio[2] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[2]->Fill(pEM_ratio[2]);

                                    if (pEM_ratio[2] > 3.6616 && pEM_ratio[2] < 4.1064){
                                        pEM_signal[2][1] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[2]->Fill(pEM_signal[2][1]);
                                }
                                if (channel[n] == 4){
                                    Run375259_pEM_TS[3]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[3]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[3]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[3]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[3]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[3]->Fill(5.0, TS5[n]);

                                    pEM_ratio[3] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[3]->Fill(pEM_ratio[3]);

                                    if (pEM_ratio[3] > 3.5942 && pEM_ratio[3] < 3.8438){
                                        pEM_signal[3][1] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[3]->Fill(pEM_signal[3][1]);
                                }
                                if (channel[n] == 5){
                                    Run375259_pEM_TS[4]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[4]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[4]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[4]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[4]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[4]->Fill(5.0, TS5[n]);

                                    pEM_ratio[4] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[4]->Fill(pEM_ratio[4]);

                                    if (pEM_ratio[4] > 3.4296 && pEM_ratio[4] < 3.6964){
                                        pEM_signal[4][1] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[4]->Fill(pEM_signal[4][1]);
                                }
                                 pEM_signal_total[1] = (0.6 * pEM_signal[0][1]) + (0.89 * pEM_signal[1][1]) + (1 * pEM_signal[2][1]) + (1.29 * pEM_signal[3][1]) + (0.57 * pEM_signal[4][1]);
                                 pEM_signal_col[1] = ((-3.6 * 0.6 * pEM_signal[0][1]) + (-1.8 * 0.89 * pEM_signal[1][1]) + (0 * 1 * pEM_signal[2][1]) + (1.8 * 1.29 * pEM_signal[3][1]) + (3.6 * 0.57 * pEM_signal[4][1])) / pEM_signal_total[1];
                            } // end of side & section
                        } // end channel loop
                        Run375259_pEM_COMvsCent[1]->Fill(pEM_signal_col[1]);
                        Run375259_pEM_Profile[1]->Fill(0.0 , pEM_signal[0][1]);
                        Run375259_pEM_Profile[1]->Fill(1.0 , pEM_signal[1][1]);
                        Run375259_pEM_Profile[1]->Fill(2.0 , pEM_signal[2][1]);
                        Run375259_pEM_Profile[1]->Fill(3.0 , pEM_signal[3][1]);
                        Run375259_pEM_Profile[1]->Fill(4.0 , pEM_signal[4][1]);
                } // end centrality
                if (hibin >=40 && hibin < 60 ){ 
                            for (int n = 0; n < 56; n++) {
                                if (zside[n] == 1 && section[n] == 1) {
                                if (channel[n] == 1) {
                                    Run375259_pEM_TS[0]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[0]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[0]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[0]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[0]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[0]->Fill(5.0, TS5[n]);

                                    pEM_ratio[0] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[0]->Fill(pEM_ratio[0]);

                                    if (pEM_ratio[0] > 3.6967 && pEM_ratio[0] < 4.8773){
                                        pEM_signal[0][2] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[0]->Fill(pEM_signal[0][2]);
                                }
                                if (channel[n] == 2) {
                                    Run375259_pEM_TS[1]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[1]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[1]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[1]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[1]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[1]->Fill(5.0, TS5[n]);

                                    pEM_ratio[1] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[1]->Fill(pEM_ratio[1]);

                                    if (pEM_ratio[1] > 3.9674 && pEM_ratio[1] < 4.5806){
                                        pEM_signal[1][2] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[1]->Fill(pEM_signal[1][2]);
                                }
                                if (channel[n] == 3){
                                    Run375259_pEM_TS[2]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[2]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[2]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[2]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[2]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[2]->Fill(5.0, TS5[n]);

                                    pEM_ratio[2] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[2]->Fill(pEM_ratio[2]);

                                    if (pEM_ratio[2] > 3.6616 && pEM_ratio[2] < 4.1064){
                                        pEM_signal[2][2] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[2]->Fill(pEM_signal[2][2]);
                                }
                                if (channel[n] == 4){
                                    Run375259_pEM_TS[3]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[3]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[3]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[3]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[3]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[3]->Fill(5.0, TS5[n]);

                                    pEM_ratio[3] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[3]->Fill(pEM_ratio[3]);

                                    if (pEM_ratio[3] > 3.5942 && pEM_ratio[3] < 3.8438){
                                        pEM_signal[3][2] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[3]->Fill(pEM_signal[3][2]);
                                }
                                if (channel[n] == 5){
                                    Run375259_pEM_TS[4]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[4]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[4]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[4]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[4]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[4]->Fill(5.0, TS5[n]);

                                    pEM_ratio[4] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[4]->Fill(pEM_ratio[4]);

                                    if (pEM_ratio[4] > 3.4296 && pEM_ratio[4] < 3.6964){
                                        pEM_signal[4][2] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[4]->Fill(pEM_signal[4][2]);
                                }
                                 pEM_signal_total[2] = (0.6 * pEM_signal[0][2]) + (0.89 * pEM_signal[1][2]) + (1 * pEM_signal[2][2]) + (1.29 * pEM_signal[3][2]) + (0.57 * pEM_signal[4][2]);
                                 pEM_signal_col[2] = ((-3.6 * 0.6 * pEM_signal[0][2]) + (-1.8 * 0.89 * pEM_signal[1][2]) + (0 * 1 * pEM_signal[2][2]) + (1.8 * 1.29 * pEM_signal[3][2]) + (3.6 * 0.57 * pEM_signal[4][2])) / pEM_signal_total[2];
                            } // end of side & section
                        } // end channel loop
                        Run375259_pEM_COMvsCent[2]->Fill(pEM_signal_col[2]);
                        Run375259_pEM_Profile[2]->Fill(0.0 , pEM_signal[0][2]);
                        Run375259_pEM_Profile[2]->Fill(1.0 , pEM_signal[1][2]);
                        Run375259_pEM_Profile[2]->Fill(2.0 , pEM_signal[2][2]);
                        Run375259_pEM_Profile[2]->Fill(3.0 , pEM_signal[3][2]);
                        Run375259_pEM_Profile[2]->Fill(4.0 , pEM_signal[4][2]);
                } // end centrality
                if (hibin >=60 && hibin < 80 ){ 
                            for (int n = 0; n < 56; n++) {
                                if (zside[n] == 1 && section[n] == 1) {
                                if (channel[n] == 1) {
                                    Run375259_pEM_TS[0]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[0]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[0]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[0]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[0]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[0]->Fill(5.0, TS5[n]);

                                    pEM_ratio[0] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[0]->Fill(pEM_ratio[0]);

                                    if (pEM_ratio[0] > 3.6967 && pEM_ratio[0] < 4.8773){
                                        pEM_signal[0][3] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[0]->Fill(pEM_signal[0][3]);

                                }
                                if (channel[n] == 2) {
                                    Run375259_pEM_TS[1]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[1]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[1]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[1]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[1]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[1]->Fill(5.0, TS5[n]);

                                    pEM_ratio[1] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[1]->Fill(pEM_ratio[1]);

                                    if (pEM_ratio[1] > 3.9674 && pEM_ratio[1] < 4.5806){
                                        pEM_signal[1][3] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[1]->Fill(pEM_signal[1][3]);
                                }
                                if (channel[n] == 3){
                                    Run375259_pEM_TS[2]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[2]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[2]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[2]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[2]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[2]->Fill(5.0, TS5[n]);

                                    pEM_ratio[2] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[2]->Fill(pEM_ratio[2]);

                                    if (pEM_ratio[2] > 3.6616 && pEM_ratio[2] < 4.1064){
                                        pEM_signal[2][3] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[2]->Fill(pEM_signal[2][3]);
                                }
                                if (channel[n] == 4){
                                    Run375259_pEM_TS[3]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[3]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[3]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[3]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[3]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[3]->Fill(5.0, TS5[n]);

                                    pEM_ratio[3] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[3]->Fill(pEM_ratio[3]);

                                    if (pEM_ratio[3] > 3.5942 && pEM_ratio[3] < 3.8438){
                                        pEM_signal[3][3] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[3]->Fill(pEM_signal[3][3]);
                                }
                                if (channel[n] == 5){
                                    Run375259_pEM_TS[4]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[4]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[4]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[4]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[4]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[4]->Fill(5.0, TS5[n]);

                                    pEM_ratio[4] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[4]->Fill(pEM_ratio[4]);

                                    if (pEM_ratio[4] > 3.4296 && pEM_ratio[4] < 3.6964){
                                        pEM_signal[4][3] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[4]->Fill(pEM_signal[4][3]);
                                }
                                 pEM_signal_total[3] = (0.6 * pEM_signal[0][3]) + (0.89 * pEM_signal[1][3]) + (1 * pEM_signal[2][3]) + (1.29 * pEM_signal[3][3]) + (0.57 * pEM_signal[4][3]);
                                pEM_signal_col[3] = ((-3.6 * 0.6 * pEM_signal[0][3]) + (-1.8 * 0.89 * pEM_signal[1][3]) + (0 * 1 * pEM_signal[2][3]) + (1.8 * 1.29 * pEM_signal[3][3]) + (3.6 * 0.57 * pEM_signal[4][3])) / pEM_signal_total[3];
                            } // end of side & section
                        } // end channel loop
                        Run375259_pEM_COMvsCent[3]->Fill(pEM_signal_col[3]);
                        Run375259_pEM_Profile[3]->Fill(0.0 , pEM_signal[0][3]);
                        Run375259_pEM_Profile[3]->Fill(1.0 , pEM_signal[1][3]);
                        Run375259_pEM_Profile[3]->Fill(2.0 , pEM_signal[2][3]);
                        Run375259_pEM_Profile[3]->Fill(3.0 , pEM_signal[3][3]);
                        Run375259_pEM_Profile[3]->Fill(4.0 , pEM_signal[4][3]);
                } // end centrality
                if (hibin >=80 && hibin < 100 ){ 
                            for (int n = 0; n < 56; n++) {
                                if (zside[n] == 1 && section[n] == 1) {
                                if (channel[n] == 1) {
                                    Run375259_pEM_TS[0]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[0]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[0]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[0]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[0]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[0]->Fill(5.0, TS5[n]);

                                    pEM_ratio[0] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[0]->Fill(pEM_ratio[0]);

                                    if (pEM_ratio[0] > 3.6967 && pEM_ratio[0] < 4.8773){
                                        pEM_signal[0][4] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[0]->Fill(pEM_signal[0][4]);

                                }
                                if (channel[n] == 2) {
                                    Run375259_pEM_TS[1]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[1]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[1]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[1]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[1]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[1]->Fill(5.0, TS5[n]);

                                    pEM_ratio[1] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[1]->Fill(pEM_ratio[1]);

                                    if (pEM_ratio[1] > 3.9674 && pEM_ratio[1] < 4.5806){
                                        pEM_signal[1][4] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[1]->Fill(pEM_signal[1][4]);
                                }
                                if (channel[n] == 3){
                                    Run375259_pEM_TS[2]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[2]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[2]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[2]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[2]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[2]->Fill(5.0, TS5[n]);

                                    pEM_ratio[2] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[2]->Fill(pEM_ratio[2]);

                                    if (pEM_ratio[2] > 3.6616 && pEM_ratio[2] < 4.1064){
                                        pEM_signal[2][4] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[2]->Fill(pEM_signal[2][4]);
                                }
                                if (channel[n] == 4){
                                    Run375259_pEM_TS[3]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[3]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[3]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[3]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[3]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[3]->Fill(5.0, TS5[n]);

                                    pEM_ratio[3] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[3]->Fill(pEM_ratio[3]);

                                    if (pEM_ratio[3] > 3.5942 && pEM_ratio[3] < 3.8438){
                                        pEM_signal[3][4] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[3]->Fill(pEM_signal[3][4]);
                                }
                                if (channel[n] == 5){
                                    Run375259_pEM_TS[4]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[4]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[4]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[4]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[4]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[4]->Fill(5.0, TS5[n]);

                                    pEM_ratio[4] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[4]->Fill(pEM_ratio[4]);

                                    if (pEM_ratio[4] > 3.4296 && pEM_ratio[4] < 3.6964){
                                        pEM_signal[4][4] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[4]->Fill(pEM_signal[4][4]);
                                }
                                 pEM_signal_total[4] = (0.6 * pEM_signal[0][4]) + (0.89 * pEM_signal[1][4]) + (1 * pEM_signal[2][4]) + (1.29 * pEM_signal[3][4]) + (0.57 * pEM_signal[4][4]);
                                pEM_signal_col[4] = ((-3.6 * 0.6 * pEM_signal[0][4]) + (-1.8 * 0.89 * pEM_signal[1][4]) + (0 * 1 * pEM_signal[2][4]) + (1.8 * 1.29 * pEM_signal[3][4]) + (3.6 * 0.57 * pEM_signal[4][4])) / pEM_signal_total[4];
                            } // end of side & section
                        } // end channel loop
                        Run375259_pEM_COMvsCent[4]->Fill(pEM_signal_col[4]);
                        Run375259_pEM_Profile[4]->Fill(0.0 , pEM_signal[0][4]);
                        Run375259_pEM_Profile[4]->Fill(1.0 , pEM_signal[1][4]);
                        Run375259_pEM_Profile[4]->Fill(2.0 , pEM_signal[2][4]);
                        Run375259_pEM_Profile[4]->Fill(3.0 , pEM_signal[3][4]);
                        Run375259_pEM_Profile[4]->Fill(4.0 , pEM_signal[4][4]);
                } // end centrality
                if (hibin >=100 && hibin < 120 ){ 
                            for (int n = 0; n < 56; n++) {
                                if (zside[n] == 1 && section[n] == 1) {
                                if (channel[n] == 1) {
                                    Run375259_pEM_TS[0]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[0]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[0]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[0]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[0]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[0]->Fill(5.0, TS5[n]);

                                    pEM_ratio[0] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[0]->Fill(pEM_ratio[0]);

                                    if (pEM_ratio[0] > 3.6967 && pEM_ratio[0] < 4.8773){
                                        pEM_signal[0][5] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[0]->Fill(pEM_signal[0][5]);
                                }
                                if (channel[n] == 2) {
                                    Run375259_pEM_TS[1]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[1]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[1]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[1]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[1]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[1]->Fill(5.0, TS5[n]);

                                    pEM_ratio[1] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[1]->Fill(pEM_ratio[1]);

                                    if (pEM_ratio[1] > 3.9674 && pEM_ratio[1] < 4.5806){
                                        pEM_signal[1][5] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[1]->Fill(pEM_signal[1][5]);
                                }
                                if (channel[n] == 3){
                                    Run375259_pEM_TS[2]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[2]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[2]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[2]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[2]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[2]->Fill(5.0, TS5[n]);

                                    pEM_ratio[2] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[2]->Fill(pEM_ratio[2]);

                                    if (pEM_ratio[2] > 3.6616 && pEM_ratio[2] < 4.1064){
                                        pEM_signal[2][5] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[2]->Fill(pEM_signal[2][5]);
                                }
                                if (channel[n] == 4){
                                    Run375259_pEM_TS[3]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[3]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[3]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[3]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[3]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[3]->Fill(5.0, TS5[n]);

                                    pEM_ratio[3] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[3]->Fill(pEM_ratio[3]);

                                    if (pEM_ratio[3] > 3.5942 && pEM_ratio[3] < 3.8438){
                                        pEM_signal[3][5] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[3]->Fill(pEM_signal[3][5]);
                                }
                                if (channel[n] == 5){
                                    Run375259_pEM_TS[4]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[4]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[4]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[4]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[4]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[4]->Fill(5.0, TS5[n]);

                                    pEM_ratio[4] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[4]->Fill(pEM_ratio[4]);

                                    if (pEM_ratio[4] > 3.4296 && pEM_ratio[4] < 3.6964){
                                        pEM_signal[4][5] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[4]->Fill(pEM_signal[4][5]);
                                }
                                 pEM_signal_total[5] = (0.6 * pEM_signal[0][5]) + (0.89 * pEM_signal[1][5]) + (1 * pEM_signal[2][5]) + (1.29 * pEM_signal[3][5]) + (0.57 * pEM_signal[4][5]);
                                pEM_signal_col[5] = ((-3.6 * 0.6 * pEM_signal[0][5]) + (-1.8 * 0.89 * pEM_signal[1][5]) + (0 * 1 * pEM_signal[2][5]) + (1.8 * 1.29 * pEM_signal[3][5]) + (3.6 * 0.57 * pEM_signal[4][5])) / pEM_signal_total[5];
                            } // end of side & section
                        } // end channel loop
                        Run375259_pEM_COMvsCent[5]->Fill(pEM_signal_col[5]);
                        Run375259_pEM_Profile[5]->Fill(0.0 , pEM_signal[0][5]);
                        Run375259_pEM_Profile[5]->Fill(1.0 , pEM_signal[1][5]);
                        Run375259_pEM_Profile[5]->Fill(2.0 , pEM_signal[2][5]);
                        Run375259_pEM_Profile[5]->Fill(3.0 , pEM_signal[3][5]);
                        Run375259_pEM_Profile[5]->Fill(4.0 , pEM_signal[4][5]);
                } // end centrality
                if (hibin >=120 && hibin < 140 ){ 
                            for (int n = 0; n < 56; n++) {
                                if (zside[n] == 1 && section[n] == 1) {
                                if (channel[n] == 1) {
                                    Run375259_pEM_TS[0]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[0]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[0]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[0]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[0]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[0]->Fill(5.0, TS5[n]);

                                    pEM_ratio[0] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[0]->Fill(pEM_ratio[0]);

                                    if (pEM_ratio[0] > 3.6967 && pEM_ratio[0] < 4.8773){
                                        pEM_signal[0][6] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[0]->Fill(pEM_signal[0][6]);

                                }
                                if (channel[n] == 2) {
                                    Run375259_pEM_TS[1]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[1]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[1]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[1]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[1]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[1]->Fill(5.0, TS5[n]);

                                    pEM_ratio[1] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[1]->Fill(pEM_ratio[1]);

                                    if (pEM_ratio[1] > 3.9674 && pEM_ratio[1] < 4.5806){
                                        pEM_signal[1][6] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[1]->Fill(pEM_signal[1][6]);
                                }
                                if (channel[n] == 3){
                                    Run375259_pEM_TS[2]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[2]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[2]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[2]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[2]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[2]->Fill(5.0, TS5[n]);

                                    pEM_ratio[2] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[2]->Fill(pEM_ratio[2]);

                                    if (pEM_ratio[2] > 3.6616 && pEM_ratio[2] < 4.1064){
                                        pEM_signal[2][6] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[2]->Fill(pEM_signal[2][6]);
                                }
                                if (channel[n] == 4){
                                    Run375259_pEM_TS[3]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[3]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[3]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[3]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[3]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[3]->Fill(5.0, TS5[n]);

                                    pEM_ratio[3] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[3]->Fill(pEM_ratio[3]);

                                    if (pEM_ratio[3] > 3.5942 && pEM_ratio[3] < 3.8438){
                                        pEM_signal[3][6] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[3]->Fill(pEM_signal[3][6]);
                                }
                                if (channel[n] == 5){
                                    Run375259_pEM_TS[4]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[4]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[4]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[4]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[4]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[4]->Fill(5.0, TS5[n]);

                                    pEM_ratio[4] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[4]->Fill(pEM_ratio[4]);

                                    if (pEM_ratio[4] > 3.4296 && pEM_ratio[4] < 3.6964){
                                        pEM_signal[4][6] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[4]->Fill(pEM_signal[4][6]);
                                }
                                 pEM_signal_total[6] = (0.6 * pEM_signal[0][6]) + (0.89 * pEM_signal[1][6]) + (1 * pEM_signal[2][6]) + (1.29 * pEM_signal[3][6]) + (0.57 * pEM_signal[4][6]);
                                pEM_signal_col[6] = ((-3.6 * 0.6 * pEM_signal[0][6]) + (-1.8 * 0.89 * pEM_signal[1][6]) + (0 * 1 * pEM_signal[2][6]) + (1.8 * 1.29 * pEM_signal[3][6]) + (3.6 * 0.57 * pEM_signal[4][6])) / pEM_signal_total[6];
                            } // end of side & section
                        } // end channel loop
                        Run375259_pEM_COMvsCent[6]->Fill(pEM_signal_col[6]);
                        Run375259_pEM_Profile[6]->Fill(0.0 , pEM_signal[0][6]);
                        Run375259_pEM_Profile[6]->Fill(1.0 , pEM_signal[1][6]);
                        Run375259_pEM_Profile[6]->Fill(2.0 , pEM_signal[2][6]);
                        Run375259_pEM_Profile[6]->Fill(3.0 , pEM_signal[3][6]);
                        Run375259_pEM_Profile[6]->Fill(4.0 , pEM_signal[4][6]);
                } // end centrality
                if (hibin >=140 && hibin < 160 ){ 
                            for (int n = 0; n < 56; n++) {
                                if (zside[n] == 1 && section[n] == 1) {
                                if (channel[n] == 1) {
                                    Run375259_pEM_TS[0]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[0]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[0]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[0]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[0]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[0]->Fill(5.0, TS5[n]);

                                    pEM_ratio[0] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[0]->Fill(pEM_ratio[0]);

                                    if (pEM_ratio[0] > 3.6967 && pEM_ratio[0] < 4.8773){
                                        pEM_signal[0][7] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[0]->Fill(pEM_signal[0][7]);

                                }
                                if (channel[n] == 2) {
                                    Run375259_pEM_TS[1]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[1]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[1]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[1]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[1]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[1]->Fill(5.0, TS5[n]);

                                    pEM_ratio[1] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[1]->Fill(pEM_ratio[1]);

                                    if (pEM_ratio[1] > 3.9674 && pEM_ratio[1] < 4.5806){
                                        pEM_signal[1][7] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[1]->Fill(pEM_signal[1][7]);
                                }
                                if (channel[n] == 3){
                                    Run375259_pEM_TS[2]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[2]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[2]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[2]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[2]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[2]->Fill(5.0, TS5[n]);

                                    pEM_ratio[2] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[2]->Fill(pEM_ratio[2]);

                                    if (pEM_ratio[2] > 3.6616 && pEM_ratio[2] < 4.1064){
                                        pEM_signal[2][7] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[2]->Fill(pEM_signal[2][7]);
                                }
                                if (channel[n] == 4){
                                    Run375259_pEM_TS[3]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[3]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[3]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[3]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[3]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[3]->Fill(5.0, TS5[n]);

                                    pEM_ratio[3] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[3]->Fill(pEM_ratio[3]);

                                    if (pEM_ratio[3] > 3.5942 && pEM_ratio[3] < 3.8438){
                                        pEM_signal[3][7] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[3]->Fill(pEM_signal[3][7]);
                                }
                                if (channel[n] == 5){
                                    Run375259_pEM_TS[4]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[4]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[4]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[4]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[4]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[4]->Fill(5.0, TS5[n]);

                                    pEM_ratio[4] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[4]->Fill(pEM_ratio[4]);

                                    if (pEM_ratio[4] > 3.4296 && pEM_ratio[4] < 3.6964){
                                        pEM_signal[4][7] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[4]->Fill(pEM_signal[4][7]);
                                }
                                 pEM_signal_total[7] = (0.6 * pEM_signal[0][7]) + (0.89 * pEM_signal[1][7]) + (1 * pEM_signal[2][7]) + (1.29 * pEM_signal[3][7]) + (0.57 * pEM_signal[4][7]);
                                pEM_signal_col[7] = ((-3.6 * 0.6 * pEM_signal[0][7]) + (-1.8 * 0.89 * pEM_signal[1][7]) + (0 * 1 * pEM_signal[2][7]) + (1.8 * 1.29 * pEM_signal[3][7]) + (3.6 * 0.57 * pEM_signal[4][7])) / pEM_signal_total[7];
                            } // end of side & section
                        } // end channel loop
                        Run375259_pEM_COMvsCent[7]->Fill(pEM_signal_col[7]);
                        Run375259_pEM_Profile[7]->Fill(0.0 , pEM_signal[0][7]);
                        Run375259_pEM_Profile[7]->Fill(1.0 , pEM_signal[1][7]);
                        Run375259_pEM_Profile[7]->Fill(2.0 , pEM_signal[2][7]);
                        Run375259_pEM_Profile[7]->Fill(3.0 , pEM_signal[3][7]);
                        Run375259_pEM_Profile[7]->Fill(4.0 , pEM_signal[4][7]);
                } // end centrality
                if (hibin >=160 && hibin < 180 ){ 
                            for (int n = 0; n < 56; n++) {
                                if (zside[n] == 1 && section[n] == 1) {
                                if (channel[n] == 1) {
                                    Run375259_pEM_TS[0]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[0]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[0]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[0]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[0]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[0]->Fill(5.0, TS5[n]);

                                    pEM_ratio[0] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[0]->Fill(pEM_ratio[0]);

                                    if (pEM_ratio[0] > 3.6967 && pEM_ratio[0] < 4.8773){
                                        pEM_signal[0][8] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[0]->Fill(pEM_signal[0][8]);

                                }
                                if (channel[n] == 2) {
                                    Run375259_pEM_TS[1]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[1]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[1]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[1]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[1]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[1]->Fill(5.0, TS5[n]);

                                    pEM_ratio[1] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[1]->Fill(pEM_ratio[1]);

                                    if (pEM_ratio[1] > 3.9674 && pEM_ratio[1] < 4.5806){
                                        pEM_signal[1][8] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[1]->Fill(pEM_signal[1][8]);
                                }
                                if (channel[n] == 3){
                                    Run375259_pEM_TS[2]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[2]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[2]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[2]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[2]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[2]->Fill(5.0, TS5[n]);

                                    pEM_ratio[2] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[2]->Fill(pEM_ratio[2]);

                                    if (pEM_ratio[2] > 3.6616 && pEM_ratio[2] < 4.1064){
                                        pEM_signal[2][8] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[2]->Fill(pEM_signal[2][8]);
                                }
                                if (channel[n] == 4){
                                    Run375259_pEM_TS[3]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[3]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[3]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[3]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[3]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[3]->Fill(5.0, TS5[n]);

                                    pEM_ratio[3] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[3]->Fill(pEM_ratio[3]);

                                    if (pEM_ratio[3] > 3.5942 && pEM_ratio[3] < 3.8438){
                                        pEM_signal[3][8] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[3]->Fill(pEM_signal[3][8]);
                                }
                                if (channel[n] == 5){
                                    Run375259_pEM_TS[4]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[4]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[4]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[4]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[4]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[4]->Fill(5.0, TS5[n]);

                                    pEM_ratio[4] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[4]->Fill(pEM_ratio[4]);

                                    if (pEM_ratio[4] > 3.4296 && pEM_ratio[4] < 3.6964){
                                        pEM_signal[4][8] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[4]->Fill(pEM_signal[4][8]);
                                }
                                 pEM_signal_total[8] = (0.6 * pEM_signal[0][8]) + (0.89 * pEM_signal[1][8]) + (1 * pEM_signal[2][8]) + (1.29 * pEM_signal[3][8]) + (0.57 * pEM_signal[4][8]);
                                pEM_signal_col[8] = ((-3.6 * 0.6 * pEM_signal[0][8]) + (-1.8 * 0.89 * pEM_signal[1][8]) + (0 * 1 * pEM_signal[2][8]) + (1.8 * 1.29 * pEM_signal[3][8]) + (3.6 * 0.57 * pEM_signal[4][8])) / pEM_signal_total[8];
                            } // end of side & section
                        } // end channel loop
                        Run375259_pEM_COMvsCent[8]->Fill(pEM_signal_col[8]);
                        Run375259_pEM_Profile[8]->Fill(0.0 , pEM_signal[0][8]);
                        Run375259_pEM_Profile[8]->Fill(1.0 , pEM_signal[1][8]);
                        Run375259_pEM_Profile[8]->Fill(2.0 , pEM_signal[2][8]);
                        Run375259_pEM_Profile[8]->Fill(3.0 , pEM_signal[3][8]);
                        Run375259_pEM_Profile[8]->Fill(4.0 , pEM_signal[4][8]);
                } // end centrality
                if (hibin >=180 && hibin < 200 ){ 
                            for (int n = 0; n < 56; n++) {
                                if (zside[n] == 1 && section[n] == 1) {
                                if (channel[n] == 1) {
                                    Run375259_pEM_TS[0]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[0]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[0]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[0]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[0]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[0]->Fill(5.0, TS5[n]);

                                    pEM_ratio[0] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[0]->Fill(pEM_ratio[0]);

                                    if (pEM_ratio[0] > 3.6967 && pEM_ratio[0] < 4.8773){
                                        pEM_signal[0][9] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[0]->Fill(pEM_signal[0][9]);

                                }
                                if (channel[n] == 2) {
                                    Run375259_pEM_TS[1]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[1]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[1]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[1]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[1]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[1]->Fill(5.0, TS5[n]);

                                    pEM_ratio[1] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[1]->Fill(pEM_ratio[1]);

                                    if (pEM_ratio[1] > 3.9674 && pEM_ratio[1] < 4.5806){
                                        pEM_signal[1][9] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[1]->Fill(pEM_signal[1][9]);
                                }
                                if (channel[n] == 3){
                                    Run375259_pEM_TS[2]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[2]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[2]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[2]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[2]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[2]->Fill(5.0, TS5[n]);

                                    pEM_ratio[2] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[2]->Fill(pEM_ratio[2]);

                                    if (pEM_ratio[2] > 3.6616 && pEM_ratio[2] < 4.1064){
                                        pEM_signal[2][9] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[2]->Fill(pEM_signal[2][9]);
                                }
                                if (channel[n] == 4){
                                    Run375259_pEM_TS[3]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[3]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[3]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[3]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[3]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[3]->Fill(5.0, TS5[n]);

                                    pEM_ratio[3] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[3]->Fill(pEM_ratio[3]);

                                    if (pEM_ratio[3] > 3.5942 && pEM_ratio[3] < 3.8438){
                                        pEM_signal[3][9] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[3]->Fill(pEM_signal[3][9]);
                                }
                                if (channel[n] == 5){
                                    Run375259_pEM_TS[4]->Fill(0.0, TS0[n]);
                                    Run375259_pEM_TS[4]->Fill(1.0, TS1[n]);
                                    Run375259_pEM_TS[4]->Fill(2.0, TS2[n]);
                                    Run375259_pEM_TS[4]->Fill(3.0, TS3[n]);
                                    Run375259_pEM_TS[4]->Fill(4.0, TS4[n]);
                                    Run375259_pEM_TS[4]->Fill(5.0, TS5[n]);

                                    pEM_ratio[4] = TS2[n] / TS3[n];
                                    Run375259_pEM_TSratio[4]->Fill(pEM_ratio[4]);

                                    if (pEM_ratio[4] > 3.4296 && pEM_ratio[4] < 3.6964){
                                        pEM_signal[4][9] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pEM_fC[4]->Fill(pEM_signal[4][9]);
                                }
                                 pEM_signal_total[9] = (0.6 * pEM_signal[0][9]) + (0.89 * pEM_signal[1][9]) + (1 * pEM_signal[2][9]) + (1.29 * pEM_signal[3][9]) + (0.57 * pEM_signal[4][9]);
                                pEM_signal_col[9] = ((-3.6 * 0.6 * pEM_signal[0][9]) + (-1.8 * 0.89 * pEM_signal[1][9]) + (0 * 1 * pEM_signal[2][9]) + (1.8 * 1.29 * pEM_signal[3][9]) + (3.6 * 0.59 * pEM_signal[4][9])) / pEM_signal_total[9];
                            } // end of side & section
                        } // end channel loop
                        Run375259_pEM_COMvsCent[9]->Fill(pEM_signal_col[9]);
                        Run375259_pEM_Profile[9]->Fill(0.0 , pEM_signal[0][9]);
                        Run375259_pEM_Profile[9]->Fill(1.0 , pEM_signal[1][9]);
                        Run375259_pEM_Profile[9]->Fill(2.0 , pEM_signal[2][9]);
                        Run375259_pEM_Profile[9]->Fill(3.0 , pEM_signal[3][9]);
                        Run375259_pEM_Profile[9]->Fill(4.0 , pEM_signal[4][9]);
                } // end centrality
                } // end sum signal
            } // end event loop

    gStyle->SetOptFit();        

    Run375259_pEM_TSratio[0]->Fit("gaus","","",3.5,5);
    Run375259_pEM_TSratio[1]->Fit("gaus","","",3.5,5);
    Run375259_pEM_TSratio[2]->Fit("gaus","","",3.5,5);
    Run375259_pEM_TSratio[3]->Fit("gaus","","",3,4.2);
    Run375259_pEM_TSratio[4]->Fit("gaus","","",3,4.1);

    Run375259_pEM_TS[0]->SetXTitle("Time Slice");
    Run375259_pEM_TS[0]->SetYTitle("Charge (fC)");

    Run375259_pEM_TS[1]->SetXTitle("Time Slice");
    Run375259_pEM_TS[1]->SetYTitle("Charge (fC)");

    Run375259_pEM_TS[2]->SetXTitle("Time Slice");
    Run375259_pEM_TS[2]->SetYTitle("Charge (fC)");

    Run375259_pEM_TS[3]->SetXTitle("Time Slice");
    Run375259_pEM_TS[3]->SetYTitle("Charge (fC)");

    Run375259_pEM_TS[4]->SetXTitle("Time Slice");
    Run375259_pEM_TS[4]->SetYTitle("Charge (fC)");
       
    TCanvas *c1 = new TCanvas();
    c1->Divide(3,2);
    c1->cd(1);
    Run375259_pEM_TS[0]->Draw("hist e");
    c1->cd(2);
    Run375259_pEM_TS[1]->Draw("hist e");
    c1->cd(3);
    Run375259_pEM_TS[2]->Draw("hist e");
    c1->cd(4);
    Run375259_pEM_TS[3]->Draw("hist e");
    c1->cd(5);
    Run375259_pEM_TS[4]->Draw("hist e");

    Run375259_pEM_TSratio[0]->SetXTitle("Ratio TS2 : TS3");
    Run375259_pEM_TSratio[0]->SetYTitle("Counts");

    Run375259_pEM_TSratio[1]->SetXTitle("Ratio TS2 : TS3");
    Run375259_pEM_TSratio[1]->SetYTitle("Counts");

    Run375259_pEM_TSratio[2]->SetXTitle("Ratio TS2 : TS3");
    Run375259_pEM_TSratio[2]->SetYTitle("Counts");

    Run375259_pEM_TSratio[3]->SetXTitle("Ratio TS2 : TS3");
    Run375259_pEM_TSratio[3]->SetYTitle("Counts");

    Run375259_pEM_TSratio[4]->SetXTitle("Ratio TS2 : TS3");
    Run375259_pEM_TSratio[4]->SetYTitle("Counts");

    TCanvas *c2 = new TCanvas();
    c2->Divide(3,2);
    c2->cd(1);
    Run375259_pEM_TSratio[0]->Draw();
    c2->cd(2);
    Run375259_pEM_TSratio[1]->Draw();
    c2->cd(3);
    Run375259_pEM_TSratio[2]->Draw();
    c2->cd(4);
    Run375259_pEM_TSratio[3]->Draw();
    c2->cd(5);
    Run375259_pEM_TSratio[4]->Draw();

    Run375259_pEM_fC[0]->SetXTitle("Charge (fC)");
    Run375259_pEM_fC[0]->SetYTitle("Counts");

    Run375259_pEM_fC[1]->SetXTitle("Charge (fC)");
    Run375259_pEM_fC[1]->SetYTitle("Counts");

    Run375259_pEM_fC[2]->SetXTitle("Charge (fC)");
    Run375259_pEM_fC[2]->SetYTitle("Counts");

    Run375259_pEM_fC[3]->SetXTitle("Charge (fC)");
    Run375259_pEM_fC[3]->SetYTitle("Counts");

    Run375259_pEM_fC[4]->SetXTitle("Charge (fC)");
    Run375259_pEM_fC[4]->SetYTitle("Counts");

    TCanvas *c3 = new TCanvas();
    c3->Divide(3,2);
    c3->cd(1);
    Run375259_pEM_fC[0]->Draw();
    c3->cd(2);
    Run375259_pEM_fC[1]->Draw();
    c3->cd(3);
    Run375259_pEM_fC[2]->Draw();
    c3->cd(4);
    Run375259_pEM_fC[3]->Draw();
    c3->cd(5);
    Run375259_pEM_fC[4]->Draw();

    Run375259_pEM_Profile[0]->SetXTitle("X Position");
    Run375259_pEM_Profile[0]->SetYTitle("Avg Signal");

    Run375259_pEM_Profile[1]->SetXTitle("X Position");
    Run375259_pEM_Profile[1]->SetYTitle("Avg Signal");

    Run375259_pEM_Profile[2]->SetXTitle("X Position");
    Run375259_pEM_Profile[2]->SetYTitle("Avg Signal");

    Run375259_pEM_Profile[3]->SetXTitle("X Position");
    Run375259_pEM_Profile[3]->SetYTitle("Avg Signal");

    Run375259_pEM_Profile[4]->SetXTitle("X Position");
    Run375259_pEM_Profile[4]->SetYTitle("Avg Signal");

    Run375259_pEM_Profile[5]->SetXTitle("X Position");
    Run375259_pEM_Profile[5]->SetYTitle("Avg Signal");

    Run375259_pEM_Profile[6]->SetXTitle("X Position");
    Run375259_pEM_Profile[6]->SetYTitle("Avg Signal");

    Run375259_pEM_Profile[7]->SetXTitle("X Position");
    Run375259_pEM_Profile[7]->SetYTitle("Avg Signal");

    Run375259_pEM_Profile[8]->SetXTitle("X Position");
    Run375259_pEM_Profile[8]->SetYTitle("Avg Signal");

    Run375259_pEM_Profile[9]->SetXTitle("X Position");
    Run375259_pEM_Profile[9]->SetYTitle("Avg Signal");

    TCanvas *c4 = new TCanvas();
    c4->Divide(5,2);
    c4->cd(1);
    Run375259_pEM_Profile[0]->Draw("hist e");
    c4->cd(2);
    Run375259_pEM_Profile[1]->Draw("hist e");
    c4->cd(3);
    Run375259_pEM_Profile[2]->Draw("hist e");
    c4->cd(4);
    Run375259_pEM_Profile[3]->Draw("hist e");
    c4->cd(5);
    Run375259_pEM_Profile[4]->Draw("hist e");
    c4->cd(6);
    Run375259_pEM_Profile[5]->Draw("hist e");
    c4->cd(7);
    Run375259_pEM_Profile[6]->Draw("hist e");
    c4->cd(8);
    Run375259_pEM_Profile[7]->Draw("hist e");
    c4->cd(9);
    Run375259_pEM_Profile[8]->Draw("hist e");
    c4->cd(10);
    Run375259_pEM_Profile[9]->Draw("hist e");

    Run375259_pEM_COMvsCent[0]->SetLineColor(kRed);
    Run375259_pEM_COMvsCent[1]->SetLineColor(kCyan);
    Run375259_pEM_COMvsCent[2]->SetLineColor(kBlue);
    Run375259_pEM_COMvsCent[3]->SetLineColor(kYellow);
    Run375259_pEM_COMvsCent[4]->SetLineColor(kGreen);
    Run375259_pEM_COMvsCent[5]->SetLineColor(kViolet);
    Run375259_pEM_COMvsCent[6]->SetLineColor(kBlack);
    Run375259_pEM_COMvsCent[7]->SetLineColor(kOrange);
    Run375259_pEM_COMvsCent[8]->SetLineColor(kGray);
    Run375259_pEM_COMvsCent[9]->SetLineColor(kRainBow);

    TCanvas *c5 = new TCanvas();
    auto legend = new TLegend(0.7,0.7,0.9,0.9);
    legend->AddEntry(Run375259_pEM_COMvsCent[0], "0 - <10% Centrality", "l");
    legend->AddEntry(Run375259_pEM_COMvsCent[1], "10 - <20% Centrality", "l");
    legend->AddEntry(Run375259_pEM_COMvsCent[2], "20 - <30% Centrality", "l");
    legend->AddEntry(Run375259_pEM_COMvsCent[3], "30 - <40% Centrality", "l");
    legend->AddEntry(Run375259_pEM_COMvsCent[4], "40 - <50% Centrality", "l");
    legend->AddEntry(Run375259_pEM_COMvsCent[5], "50 - <60% Centrality", "l");
    legend->AddEntry(Run375259_pEM_COMvsCent[6], "60 - <70% Centrality", "l");
    legend->AddEntry(Run375259_pEM_COMvsCent[7], "70 - <80% Centrality", "l");
    legend->AddEntry(Run375259_pEM_COMvsCent[8], "80 - <90% Centrality", "l");
    legend->AddEntry(Run375259_pEM_COMvsCent[9], "90 - <100% Centrality", "l");

    pEM_stack->Add(Run375259_pEM_COMvsCent[0]);
    pEM_stack->Add(Run375259_pEM_COMvsCent[1]);
    pEM_stack->Add(Run375259_pEM_COMvsCent[2]);
    pEM_stack->Add(Run375259_pEM_COMvsCent[3]);
    pEM_stack->Add(Run375259_pEM_COMvsCent[4]);
    pEM_stack->Add(Run375259_pEM_COMvsCent[5]);
    pEM_stack->Add(Run375259_pEM_COMvsCent[6]);
    pEM_stack->Add(Run375259_pEM_COMvsCent[7]);
    pEM_stack->Add(Run375259_pEM_COMvsCent[8]);
    pEM_stack->Add(Run375259_pEM_COMvsCent[9]);

    pEM_stack->Draw("nostack");
    legend->Draw();

    pEM_stack->GetXaxis()->SetTitle("X Position (cm)");
    pEM_stack->GetYaxis()->SetTitle("counts");

    TCanvas *c6 = new TCanvas();
    c6->Divide(5,2);
    Run375259_pEM_COMvsCent[0]->SetXTitle("X Position (cm)");
    Run375259_pEM_COMvsCent[0]->SetYTitle("Counts");
    Run375259_pEM_COMvsCent[1]->SetXTitle("X Position (cm)");
    Run375259_pEM_COMvsCent[1]->SetYTitle("Counts");
    Run375259_pEM_COMvsCent[2]->SetXTitle("X Position (cm)");
    Run375259_pEM_COMvsCent[2]->SetYTitle("Counts");
    Run375259_pEM_COMvsCent[3]->SetXTitle("X Position (cm)");
    Run375259_pEM_COMvsCent[3]->SetYTitle("Counts");
    Run375259_pEM_COMvsCent[4]->SetXTitle("X Position (cm)");
    Run375259_pEM_COMvsCent[4]->SetYTitle("Counts");
    Run375259_pEM_COMvsCent[5]->SetXTitle("X Position (cm)");
    Run375259_pEM_COMvsCent[5]->SetYTitle("Counts");
    Run375259_pEM_COMvsCent[6]->SetXTitle("X Position (cm)");
    Run375259_pEM_COMvsCent[6]->SetYTitle("Counts");
    Run375259_pEM_COMvsCent[7]->SetXTitle("X Position (cm)");
    Run375259_pEM_COMvsCent[7]->SetYTitle("Counts");
    Run375259_pEM_COMvsCent[8]->SetXTitle("X Position (cm)");
    Run375259_pEM_COMvsCent[8]->SetYTitle("Counts");
    Run375259_pEM_COMvsCent[9]->SetXTitle("X Position (cm)");
    Run375259_pEM_COMvsCent[9]->SetYTitle("Counts");

    c6->cd(1);
    Run375259_pEM_COMvsCent[0]->Draw();
    c6->cd(2);
    Run375259_pEM_COMvsCent[1]->Draw();
    c6->cd(3);
    Run375259_pEM_COMvsCent[2]->Draw();
    c6->cd(4);
    Run375259_pEM_COMvsCent[3]->Draw();
    c6->cd(5);
    Run375259_pEM_COMvsCent[4]->Draw();
    c6->cd(6);
    Run375259_pEM_COMvsCent[5]->Draw();
    c6->cd(7);
    Run375259_pEM_COMvsCent[6]->Draw();
    c6->cd(8);
    Run375259_pEM_COMvsCent[7]->Draw();
    c6->cd(9);
    Run375259_pEM_COMvsCent[8]->Draw();
    c6->cd(10);
    Run375259_pEM_COMvsCent[9]->Draw();
}