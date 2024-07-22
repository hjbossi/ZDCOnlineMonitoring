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

void Run375259_posRPD_Analysis_REAL()
{

      TChain *zdcchain = new TChain();
      TChain *hichain = new TChain();
      for (int x = 1 ; x < 135 ; x++){
      if(x == 116) continue;
      zdcchain->Add(Form("/store/data/Runs_2023/375259/240112_203159/0000/HiForestMiniAOD_%i.root/zdcanalyzer/zdcdigi", x));
      hichain->Add(Form("/store/data/Runs_2023/375259/240112_203159/0000/HiForestMiniAOD_%i.root/hiEvtAnalyzer/HiTree", x));
      }

      zdcchain->AddFriend(hichain);
      
      double pRPD_ratio[16][10] = {0};
      double pRPD_signal[16][10] = {0};

      double pEM_ratio[16][10] = {0};
      double pEM_signal[16][10] = {0};
      
     //Time slice distributions for EM, HAD, and RPD on Pos side
    TH1F *Run375259_pRPD_TS[16] = {0};

        Run375259_pRPD_TS[0] = new TH1F("","Run 375259 pRPD Block 0",6,0,6);
        Run375259_pRPD_TS[1] = new TH1F("","Run 375259 pRPD Block 1",6,0,6);
        Run375259_pRPD_TS[2] = new TH1F("","Run 375259 pRPD Block 2",6,0,6);
        Run375259_pRPD_TS[3] = new TH1F("","Run 375259 pRPD Block 3",6,0,6);
        Run375259_pRPD_TS[4] = new TH1F("","Run 375259 pRPD Block 4",6,0,6);
        Run375259_pRPD_TS[5] = new TH1F("","Run 375259 pRPD Block 5",6,0,6);
        Run375259_pRPD_TS[6] = new TH1F("","Run 375259 pRPD Block 6",6,0,6);
        Run375259_pRPD_TS[7] = new TH1F("","Run 375259 pRPD Block 7",6,0,6);
        Run375259_pRPD_TS[8] = new TH1F("","Run 375259 pRPD Block 8",6,0,6);
        Run375259_pRPD_TS[9] = new TH1F("","Run 375259 pRPD Block 9",6,0,6);
        Run375259_pRPD_TS[10] = new TH1F("","Run 375259 pRPD Block 10",6,0,6);
        Run375259_pRPD_TS[11] = new TH1F("","Run 375259 pRPD Block 11",6,0,6);
        Run375259_pRPD_TS[12] = new TH1F("","Run 375259 pRPD Block 12",6,0,6);
        Run375259_pRPD_TS[13] = new TH1F("","Run 375259 pRPD Block 13",6,0,6);
        Run375259_pRPD_TS[14] = new TH1F("","Run 375259 pRPD Block 14",6,0,6);
        Run375259_pRPD_TS[15] = new TH1F("","Run 375259 pRPD Block 15",6,0,6);
    
    TH1F *Run375259_pEM_TS[5] = {0};

        Run375259_pEM_TS[0] = new TH1F("","Run 375259 pEM section 1",6,0,6);
        Run375259_pEM_TS[1] = new TH1F("","Run 375259 pEM section 2",6,0,6);
        Run375259_pEM_TS[2] = new TH1F("","Run 375259 pEM section 3",6,0,6);
        Run375259_pEM_TS[3] = new TH1F("","Run 375259 pEM section 4",6,0,6);
        Run375259_pEM_TS[4] = new TH1F("","Run 375259 pEM section 5",6,0,6);

    TH1F *Run375259_pHAD_TS[4] = {0};

        Run375259_pHAD_TS[0] = new TH1F("","Run 375259 pHAD section 1 TS",6,0,6);
        Run375259_pHAD_TS[1] = new TH1F("","Run 375259 pHAD section 2 TS",6,0,6);
        Run375259_pHAD_TS[2] = new TH1F("","Run 375259 pHAD section 3 TS",6,0,6);
        Run375259_pHAD_TS[3] = new TH1F("","Run 375259 pHAD section 4 TS",6,0,6);

    //Ratios of time slice 2 to time slice 3 for EM, HAD, and RPD on pos side
    TH1F *Run375259_pRPD_TSratio[16] = {0};

        Run375259_pRPD_TSratio[0] = new TH1F("","Run 375259 pRPD Ratio Block 0",50,0,5);
        Run375259_pRPD_TSratio[1] = new TH1F("","Run 375259 pRPD Ratio Block 1",50,0,5);
        Run375259_pRPD_TSratio[2] = new TH1F("","Run 375259 pRPD Ratio Block 2",50,0,5);
        Run375259_pRPD_TSratio[3] = new TH1F("","Run 375259 pRPD Ratio Block 3",50,0,5);
        Run375259_pRPD_TSratio[4] = new TH1F("","Run 375259 pRPD Ratio Block 4",50,0,5);
        Run375259_pRPD_TSratio[5] = new TH1F("","Run 375259 pRPD Ratio Block 5",50,0,5);
        Run375259_pRPD_TSratio[6] = new TH1F("","Run 375259 pRPD Ratio Block 6",50,0,5);
        Run375259_pRPD_TSratio[7] = new TH1F("","Run 375259 pRPD Ratio Block 7",50,0,5);
        Run375259_pRPD_TSratio[8] = new TH1F("","Run 375259 pRPD Ratio Block 8",50,0,5);
        Run375259_pRPD_TSratio[9] = new TH1F("","Run 375259 pRPD Ratio Block 9",50,0,5);
        Run375259_pRPD_TSratio[10] = new TH1F("","Run 375259 pRPD Ratio Block 10",50,0,5);
        Run375259_pRPD_TSratio[11] = new TH1F("","Run 375259 pRPD Ratio Block 11",50,0,5);
        Run375259_pRPD_TSratio[12] = new TH1F("","Run 375259 pRPD Ratio Block 12",50,0,5);
        Run375259_pRPD_TSratio[13] = new TH1F("","Run 375259 pRPD Ratio Block 13",50,0,5);
        Run375259_pRPD_TSratio[14] = new TH1F("","Run 375259 pRPD Ratio Block 14",50,0,5);
        Run375259_pRPD_TSratio[15] = new TH1F("","Run 375259 pRPD Ratio Block 15",50,0,5);

    TH1F *Run375259_pEM_TSratio[5] = {0};

        Run375259_pEM_TSratio[0] = new TH1F("","Run 375259 pEM TS Ratio Section 1",50,0,5);
        Run375259_pEM_TSratio[1] = new TH1F("","Run 375259 pEM TS Ratio Section 2",50,0,5);
        Run375259_pEM_TSratio[2] = new TH1F("","Run 375259 pEM TS Ratio Section 3",50,0,5);
        Run375259_pEM_TSratio[3] = new TH1F("","Run 375259 pEM TS Ratio Section 4",50,0,5);
        Run375259_pEM_TSratio[4] = new TH1F("","Run 375259 pEM TS Ratio Section 5",50,0,5);

    TH1F *Run375259_pHAD_TSratio[4] = {0};

        Run375259_pHAD_TSratio[0] = new TH1F("","Run 375259 pHAD TS Ratio Section 1",50,0,5);
        Run375259_pHAD_TSratio[1] = new TH1F("","Run 375259 pHAD TS Ratio Section 2",50,0,5);
        Run375259_pHAD_TSratio[2] = new TH1F("","Run 375259 pHAD TS Ratio Section 3",50,0,5);
        Run375259_pHAD_TSratio[3] = new TH1F("","Run 375259 pHAD TS Ratio Section 4",50,0,5);

    //fC distributions for all centralities for EM, HAD, and RPD on pos side

    TH1F *Run375259_pRPD_fC[16] = {0};

        Run375259_pRPD_fC[0] = new TH1F("","Run 375259 pRPD Block 0 fC Distribution ",100,0,400000);
        Run375259_pRPD_fC[1] = new TH1F("","Run 375259 pRPD Block 1 fC Distribution ",100,0,400000);
        Run375259_pRPD_fC[2] = new TH1F("","Run 375259 pRPD Block 2 fC Distribution ",100,0,400000);
        Run375259_pRPD_fC[3] = new TH1F("","Run 375259 pRPD Block 3 fC Distribution ",100,0,400000);
        Run375259_pRPD_fC[4] = new TH1F("","Run 375259 pRPD Block 4 fC Distribution ",100,0,400000);
        Run375259_pRPD_fC[5] = new TH1F("","Run 375259 pRPD Block 5 fC Distribution ",100,0,400000);
        Run375259_pRPD_fC[6] = new TH1F("","Run 375259 pRPD Block 6 fC Distribution ",100,0,400000);
        Run375259_pRPD_fC[7] = new TH1F("","Run 375259 pRPD Block 7 fC Distribution ",100,0,400000);
        Run375259_pRPD_fC[8] = new TH1F("","Run 375259 pRPD Block 8 fC Distribution ",100,0,400000);
        Run375259_pRPD_fC[9] = new TH1F("","Run 375259 pRPD Block 9 fC Distribution ",100,0,400000);
        Run375259_pRPD_fC[10] = new TH1F("","Run 375259 pRPD Block 10 fC Distribution ",100,0,400000);
        Run375259_pRPD_fC[11] = new TH1F("","Run 375259 pRPD Block 11 fC Distribution ",100,0,400000);
        Run375259_pRPD_fC[12] = new TH1F("","Run 375259 pRPD Block 12 fC Distribution ",100,0,400000);
        Run375259_pRPD_fC[13] = new TH1F("","Run 375259 pRPD Block 13 fC Distribution ",100,0,400000);
        Run375259_pRPD_fC[14] = new TH1F("","Run 375259 pRPD Block 14 fC Distribution ",100,0,400000);
        Run375259_pRPD_fC[15] = new TH1F("","Run 375259 pRPD Block 15 fC Distribution ",100,0,400000);

    TH1F *Run375259_pEM_fC[5] = {0};

        Run375259_pEM_fC[0] = new TH1F("","Run 375259 pEM Section 0 fC Distribution",100,0,-100);
        Run375259_pEM_fC[1] = new TH1F("","Run 375259 pEM Section 1 fC Distribution",100,0,-100);    
        Run375259_pEM_fC[2] = new TH1F("","Run 375259 pEM Section 2 fC Distribution",100,0,-100);
        Run375259_pEM_fC[3] = new TH1F("","Run 375259 pEM Section 3 fC Distribution",100,0,-100);
        Run375259_pEM_fC[4] = new TH1F("","Run 375259 pEM Section 4 fC Distribution",100,0,-100);

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

    //Block diagram for pos RPD

    // TProfiles for pos RPD
    TProfile *Run375259_pRPD_prof[10] = {0};

        Run375259_pRPD_prof[0] = new TProfile("","Run 375259 pRPD Avg Signal vs X Position 0 to 10 cent",4,0,4);
        Run375259_pRPD_prof[1] = new TProfile("","Run 375259 pRPD Avg Signal vs X Position 10 to 20 cent",4,0,4);
        Run375259_pRPD_prof[2] = new TProfile("","Run 375259 pRPD Avg Signal vs X Position 20 to 30 cent",4,0,4);
        Run375259_pRPD_prof[3] = new TProfile("","Run 375259 pRPD Avg Signal vs X Position 30 to 40 cent",4,0,4);
        Run375259_pRPD_prof[4] = new TProfile("","Run 375259 pRPD Avg Signal vs X Position 40 to 50 cent",4,0,4);
        Run375259_pRPD_prof[5] = new TProfile("","Run 375259 pRPD Avg Signal vs X Position 50 to 60 cent",4,0,4);
        Run375259_pRPD_prof[6] = new TProfile("","Run 375259 pRPD Avg Signal vs X Position 60 to 70 cent",4,0,4);
        Run375259_pRPD_prof[7] = new TProfile("","Run 375259 pRPD Avg Signal vs X Position 70 to 80 cent",4,0,4);
        Run375259_pRPD_prof[8] = new TProfile("","Run 375259 pRPD Avg Signal vs X Position 80 to 90 cent",4,0,4);
        Run375259_pRPD_prof[9] = new TProfile("","Run 375259 pRPD Avg Signal vs X Position 90 to 100 cent",4,0,4);

    //Stack for all COM Projection Histograms

    TH1F *pos_rpd_xprojection[10] = {0};

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

    THStack *pRPD_stack = new THStack("", "Run375259 pRPD X Distribution with Centrality");

    int hibin = 0;
    int zside[56];
    int section[56];
    int channel[56];

    double pRPDX1[10];
    double pRPDX2[10];
    double pRPDX3[10];
    double pRPDX4[10];

    double pRPDY1[10];
    double pRPDY2[10];
    double pRPDY3[10];
    double pRPDY4[10];

    double pRPD_signal_col[10];
    double pRPD_signal_row[10];
    double pRPD_total_signal_col[10][4];

    float pRPD_sum;
    double pRPD_signal_total[10];

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
            for (int i = 0; i < NumofEvents; i++) {           
		        zdcchain->GetEntry(i);  
                hichain->GetEntry(i);
                for (int n = 0; n < 56; n++) {
                        if (zside[n] == 1 && section[n] == 4) {
                        pRPD_sum += TS2[n] + TS3[n];
                        }
                }
                if (hibin >=0 && hibin < 20 ){ 
                    if (pRPD_sum > 3200) {
                            for (int n = 0; n < 56; n++) {
                                if (zside[n] == 1 && section[n] == 4) {
                                    if (channel[n] == 1) {
                                    Run375259_pRPD_TS[10]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[10]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[10]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[10]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[10]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[10]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[10][0] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[10]->Fill(pRPD_ratio[10][0]);

                                    if (pRPD_ratio[10][0] > 1.5 && pRPD_ratio[10][0] < 2.0) {
                                    pRPD_signal[10][0] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[10]->Fill(pRPD_signal[10][0]);
                                    
                                    }
                                    if (channel[n] == 2) {
                                    Run375259_pRPD_TS[6]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[6]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[6]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[6]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[6]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[6]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[6][0] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[6]->Fill(pRPD_ratio[6][0]);
                                    
                                    if (pRPD_ratio[6][0] > 1.5 && pRPD_ratio[6][0] < 2.1) {
                                    pRPD_signal[6][0] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[6]->Fill(pRPD_signal[6][0]);
                                    
                                    } 
                                    if (channel[n] == 3) {
                                    Run375259_pRPD_TS[2]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[2]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[2]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[2]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[2]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[2]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[2][0] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[2]->Fill(pRPD_ratio[2][0]);
                                    
                                    if (pRPD_ratio[2][0] > 1.5 && pRPD_ratio[2][0] < 2.0) {
                                    pRPD_signal[2][0] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[2]->Fill(pRPD_signal[2][0]);
                                    
                                    }      
                                    if (channel[n] == 4) {
                                    Run375259_pRPD_TS[14]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[14]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[14]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[14]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[14]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[14]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[14][0] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[14]->Fill(pRPD_ratio[14][0]);

                                    if (pRPD_ratio[14][0] > 1.5 && pRPD_ratio[14][0] < 2.0) {
                                    pRPD_signal[14][0] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[14]->Fill(pRPD_signal[14][0]);
                                    
                                    }   
                                    if (channel[n] == 5) {
                                    Run375259_pRPD_TS[11]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[11]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[11]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[11]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[11]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[11]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[11][0] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[11]->Fill(pRPD_ratio[11][0]);
                                    
                                    if (pRPD_ratio[11][0] > 1.5 && pRPD_ratio[11][0] < 2.1) {
                                    pRPD_signal[11][0] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[11]->Fill(pRPD_signal[11][0]);
                                    
                                    }   
                                    if (channel[n] == 6) {
                                    Run375259_pRPD_TS[7]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[7]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[7]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[7]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[7]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[7]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[7][0] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[7]->Fill(pRPD_ratio[7][0]);
                                    
                                    if (pRPD_ratio[7][0] > 1.6 && pRPD_ratio[7][0] < 2.4) {
                                    pRPD_signal[7][0] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[7]->Fill(pRPD_signal[7][0]);
                                    
                                    }   
                                    if (channel[n] == 7) {
                                    Run375259_pRPD_TS[3]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[3]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[3]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[3]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[3]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[3]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[3][0] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[3]->Fill(pRPD_ratio[3][0]);
                                    
                                    if (pRPD_ratio[3][0] > 1.5 && pRPD_ratio[3][0] < 2.4) {
                                    pRPD_signal[3][0] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[3]->Fill(pRPD_signal[3][0]);
                                    
                                    }   
                                    if (channel[n] == 8) {
                                    Run375259_pRPD_TS[15]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[15]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[15]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[15]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[15]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[15]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[15][0] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[15]->Fill(pRPD_ratio[15][0]);

                                    if (pRPD_ratio[15][0] > 1.6 && pRPD_ratio[15][0] < 2.2) {
                                    pRPD_signal[15][0] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[15]->Fill(pRPD_signal[15][0]);
                                    }   
                                    if (channel[n] == 9) {
                                    Run375259_pRPD_TS[4]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[4]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[4]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[4]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[4]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[4]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[4][0] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[4]->Fill(pRPD_ratio[4][0]);

                                    if (pRPD_ratio[4][0] > 1.5 && pRPD_ratio[4][0] < 2.4 ) {
                                    pRPD_signal[4][0] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[4]->Fill(pRPD_signal[4][0]);
                                    }   
                                    if (channel[n] == 10) {
                                    Run375259_pRPD_TS[8]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[8]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[8]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[8]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[8]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[8]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[8][0] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[8]->Fill(pRPD_ratio[8][0]);

                                    if (pRPD_ratio[8][0] > 1.5 && pRPD_ratio[8][0] < 2.3) {
                                    pRPD_signal[8][0] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[8]->Fill(pRPD_signal[8][0]);
                                    }   
                                    if (channel[n] == 11) {
                                    Run375259_pRPD_TS[12]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[12]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[12]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[12]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[12]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[12]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[12][0] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[12]->Fill(pRPD_ratio[12][0]);

                                    if (pRPD_ratio[12][0] > 1.5 && pRPD_ratio[12][0] < 2.2){
                                    pRPD_signal[12][0] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[12]->Fill(pRPD_signal[12][0]);
                                    }   
                                    if (channel[n] == 12) {
                                    Run375259_pRPD_TS[0]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[0]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[0]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[0]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[0]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[0]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[0][0] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[0]->Fill(pRPD_ratio[0][0]);

                                    if (pRPD_ratio[0][0] > 1.5 && pRPD_ratio[0][0] < 2.3){
                                    pRPD_signal[0][0] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[0]->Fill(pRPD_signal[0][0]);
                                    }   
                                    if (channel[n] == 13) {
                                    Run375259_pRPD_TS[5]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[5]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[5]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[5]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[5]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[5]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[5][0] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[5]->Fill(pRPD_ratio[5][0]);

                                    if (pRPD_ratio[5][0] > 1.7 && pRPD_ratio[5][0] < 2.5){
                                    pRPD_signal[5][0] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[5]->Fill(pRPD_signal[5][0]);
                                    }   
                                    if (channel[n] == 14) {
                                    Run375259_pRPD_TS[9]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[9]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[9]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[9]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[9]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[9]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[9][0] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[9]->Fill(pRPD_ratio[9][0]);
                                    
                                    if (pRPD_ratio[9][0] > 1.6 && pRPD_ratio[9][0] < 2.4) {
                                    pRPD_signal[9][0] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[9]->Fill(pRPD_signal[9][0]);
                                    }   
                                    if (channel[n] == 15) {
                                    Run375259_pRPD_TS[13]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[13]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[13]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[13]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[13]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[13]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[13][0] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[13]->Fill(pRPD_ratio[13][0]);

                                    if (pRPD_ratio[13][0] > 1.6 && pRPD_ratio[13][0] < 2.4) {
                                    pRPD_signal[13][0] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[13]->Fill(pRPD_signal[13][0]);
                                    }   
                                    if (channel[n] == 16) {
                                    Run375259_pRPD_TS[1]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[1]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[1]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[1]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[1]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[1]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[1][0] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[1]->Fill(pRPD_ratio[1][0]);

                                    if (pRPD_ratio[1][0] > 1.5 && pRPD_ratio[1][0] < 2.5) {
                                    pRPD_signal[1][0] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[1]->Fill(pRPD_signal[1][0]);
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

                                } // end of side and section
                            }  // end of channel loop
                            Run375259_pRPD_COM[0]->Fill(pRPD_signal_col[0], pRPD_signal_row[0]);
                            // fill projection
                            pos_rpd_xprojection[0]->Fill(pRPD_signal_col[0]);
                            // fill profile
                            Run375259_pRPD_prof[0]->Fill(0.0,pRPDX1[0]);
                            Run375259_pRPD_prof[0]->Fill(1.0,pRPDX2[0]);
                            Run375259_pRPD_prof[0]->Fill(2.0,pRPDX3[0]);
                            Run375259_pRPD_prof[0]->Fill(3.0,pRPDX4[0]);
                    } // end of sum cut
                } // end of hibin    
                if (hibin >20 && hibin < 40 ){ 
                    if (pRPD_sum > 3200) {
                            for (int n = 0; n < 56; n++) {
                                if (zside[n] == 1 && section[n] == 4) {
                                    if (channel[n] == 1) {
                                    Run375259_pRPD_TS[10]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[10]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[10]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[10]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[10]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[10]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[10][1] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[10]->Fill(pRPD_ratio[10][1]);

                                    if (pRPD_ratio[10][1] > 1.5 && pRPD_ratio[10][1] < 2.0) {
                                    pRPD_signal[10][1] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[10]->Fill(pRPD_signal[10][1]);
                                    
                                    }
                                    if (channel[n] == 2) {
                                    Run375259_pRPD_TS[6]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[6]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[6]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[6]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[6]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[6]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[6][1] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[6]->Fill(pRPD_ratio[6][1]);
                                    
                                    if (pRPD_ratio[6][1] > 1.5 && pRPD_ratio[6][1] < 2.1) {
                                    pRPD_signal[6][1] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[6]->Fill(pRPD_signal[6][1]);
                                    
                                    } 
                                    if (channel[n] == 3) {
                                    Run375259_pRPD_TS[2]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[2]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[2]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[2]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[2]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[2]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[2][1] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[2]->Fill(pRPD_ratio[2][1]);
                                    
                                    if (pRPD_ratio[2][1] > 1.5 && pRPD_ratio[2][1] < 2.0) {
                                    pRPD_signal[2][1] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[2]->Fill(pRPD_signal[2][1]);
                                    
                                    }      
                                    if (channel[n] == 4) {
                                    Run375259_pRPD_TS[14]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[14]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[14]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[14]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[14]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[14]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[14][1] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[14]->Fill(pRPD_ratio[14][1]);

                                    if (pRPD_ratio[14][1] > 1.5 && pRPD_ratio[14][1] < 2.0) {
                                    pRPD_signal[14][1] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[14]->Fill(pRPD_signal[14][1]);
                                    
                                    }   
                                    if (channel[n] == 5) {
                                    Run375259_pRPD_TS[11]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[11]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[11]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[11]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[11]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[11]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[11][1] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[11]->Fill(pRPD_ratio[11][1]);
                                    
                                    if (pRPD_ratio[11][1] > 1.5 && pRPD_ratio[11][1] < 2.1) {
                                    pRPD_signal[11][1] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[11]->Fill(pRPD_signal[11][1]);
                                    
                                    }   
                                    if (channel[n] == 6) {
                                    Run375259_pRPD_TS[7]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[7]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[7]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[7]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[7]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[7]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[7][1] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[7]->Fill(pRPD_ratio[7][1]);
                                    
                                    if (pRPD_ratio[7][1] > 1.6 && pRPD_ratio[7][1] < 2.4) {
                                    pRPD_signal[7][1] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[7]->Fill(pRPD_signal[7][1]);
                                    
                                    }   
                                    if (channel[n] == 7) {
                                    Run375259_pRPD_TS[3]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[3]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[3]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[3]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[3]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[3]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[3][1] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[3]->Fill(pRPD_ratio[3][1]);
                                    
                                    if (pRPD_ratio[3][1] > 1.5 && pRPD_ratio[3][1] < 2.4) {
                                    pRPD_signal[3][1] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[3]->Fill(pRPD_signal[3][1]);
                                    
                                    }   
                                    if (channel[n] == 8) {
                                    Run375259_pRPD_TS[15]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[15]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[15]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[15]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[15]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[15]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[15][1] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[15]->Fill(pRPD_ratio[15][1]);

                                    if (pRPD_ratio[15][1] > 1.6 && pRPD_ratio[15][1] < 2.2) {
                                    pRPD_signal[15][1] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[15]->Fill(pRPD_signal[15][1]);
                                    }   
                                    if (channel[n] == 9) {
                                    Run375259_pRPD_TS[4]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[4]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[4]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[4]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[4]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[4]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[4][1] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[4]->Fill(pRPD_ratio[4][1]);

                                    if (pRPD_ratio[4][1] > 1.5 && pRPD_ratio[4][1] < 2.4 ) {
                                    pRPD_signal[4][1] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[4]->Fill(pRPD_signal[4][1]);
                                    }   
                                    if (channel[n] == 10) {
                                    Run375259_pRPD_TS[8]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[8]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[8]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[8]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[8]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[8]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[8][1] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[8]->Fill(pRPD_ratio[8][1]);

                                    if (pRPD_ratio[8][1] > 1.5 && pRPD_ratio[8][1] < 2.3) {
                                    pRPD_signal[8][1] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[8]->Fill(pRPD_signal[8][1]);
                                    }   
                                    if (channel[n] == 11) {
                                    Run375259_pRPD_TS[12]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[12]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[12]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[12]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[12]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[12]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[12][1] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[12]->Fill(pRPD_ratio[12][1]);

                                    if (pRPD_ratio[12][1] > 1.5 && pRPD_ratio[12][1] < 2.2){
                                    pRPD_signal[12][1] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[12]->Fill(pRPD_signal[12][1]);
                                    }   
                                    if (channel[n] == 12) {
                                    Run375259_pRPD_TS[0]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[0]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[0]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[0]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[0]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[0]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[0][1] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[0]->Fill(pRPD_ratio[0][1]);

                                    if (pRPD_ratio[0][1] > 1.5 && pRPD_ratio[0][1] < 2.3){
                                    pRPD_signal[0][1] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[0]->Fill(pRPD_signal[0][1]);
                                    }   
                                    if (channel[n] == 13) {
                                    Run375259_pRPD_TS[5]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[5]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[5]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[5]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[5]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[5]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[5][1] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[5]->Fill(pRPD_ratio[5][1]);

                                    if (pRPD_ratio[5][1] > 1.7 && pRPD_ratio[5][1] < 2.5){
                                    pRPD_signal[5][1] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[5]->Fill(pRPD_signal[5][1]);
                                    }   
                                    if (channel[n] == 14) {
                                    Run375259_pRPD_TS[9]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[9]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[9]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[9]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[9]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[9]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[9][1] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[9]->Fill(pRPD_ratio[9][1]);
                                    
                                    if (pRPD_ratio[9][1] > 1.6 && pRPD_ratio[9][1] < 2.4) {
                                    pRPD_signal[9][1] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[9]->Fill(pRPD_signal[9][1]);
                                    }   
                                    if (channel[n] == 15) {
                                    Run375259_pRPD_TS[13]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[13]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[13]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[13]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[13]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[13]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[13][1] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[13]->Fill(pRPD_ratio[13][1]);

                                    if (pRPD_ratio[13][1] > 1.6 && pRPD_ratio[13][1] < 2.4) {
                                    pRPD_signal[13][1] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[13]->Fill(pRPD_signal[13][1]);
                                    }   
                                    if (channel[n] == 16) {
                                    Run375259_pRPD_TS[1]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[1]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[1]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[1]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[1]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[1]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[1][1] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[1]->Fill(pRPD_ratio[1][1]);

                                    if (pRPD_ratio[1][1] > 1.5 && pRPD_ratio[1][1] < 2.5) {
                                    pRPD_signal[1][1] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[1]->Fill(pRPD_signal[1][1]);
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
                            }  // end of channel loop
                            Run375259_pRPD_COM[1]->Fill(pRPD_signal_col[1], pRPD_signal_row[1]);
                            // fill projection
                            pos_rpd_xprojection[1]->Fill(pRPD_signal_col[1]);
                            // fill profile
                            Run375259_pRPD_prof[1]->Fill(0.0,pRPDX1[1]);
                            Run375259_pRPD_prof[1]->Fill(1.0,pRPDX2[1]);
                            Run375259_pRPD_prof[1]->Fill(2.0,pRPDX3[1]);
                            Run375259_pRPD_prof[1]->Fill(3.0,pRPDX4[1]);
                    } // end of sum cut
                } // end of hibin 

                if (hibin >=40 && hibin < 60 ){ 
                    if (pRPD_sum > 3200) {
                            for (int n = 0; n < 56; n++) {
                                if (zside[n] == 1 && section[n] == 4) {
                                    if (channel[n] == 1) {
                                    Run375259_pRPD_TS[10]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[10]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[10]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[10]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[10]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[10]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[10][2] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[10]->Fill(pRPD_ratio[10][2]);

                                    if (pRPD_ratio[10][2] > 1.5 && pRPD_ratio[10][2] < 2.0) {
                                    pRPD_signal[10][2] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[10]->Fill(pRPD_signal[10][2]);
                                    
                                    }
                                    if (channel[n] == 2) {
                                    Run375259_pRPD_TS[6]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[6]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[6]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[6]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[6]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[6]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[6][2] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[6]->Fill(pRPD_ratio[6][2]);
                                    
                                    if (pRPD_ratio[6][2] > 1.5 && pRPD_ratio[6][2] < 2.1) {
                                    pRPD_signal[6][2] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[6]->Fill(pRPD_signal[6][2]);
                                    
                                    } 
                                    if (channel[n] == 3) {
                                    Run375259_pRPD_TS[2]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[2]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[2]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[2]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[2]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[2]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[2][2] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[2]->Fill(pRPD_ratio[2][2]);
                                    
                                    if (pRPD_ratio[2][2] > 1.5 && pRPD_ratio[2][2] < 2.0) {
                                    pRPD_signal[2][2] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[2]->Fill(pRPD_signal[2][2]);
                                    
                                    }      
                                    if (channel[n] == 4) {
                                    Run375259_pRPD_TS[14]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[14]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[14]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[14]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[14]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[14]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[14][2] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[14]->Fill(pRPD_ratio[14][2]);

                                    if (pRPD_ratio[14][2] > 1.5 && pRPD_ratio[14][2] < 2.0) {
                                    pRPD_signal[14][2] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[14]->Fill(pRPD_signal[14][2]);
                                    
                                    }   
                                    if (channel[n] == 5) {
                                    Run375259_pRPD_TS[11]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[11]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[11]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[11]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[11]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[11]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[11][2] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[11]->Fill(pRPD_ratio[11][2]);
                                    
                                    if (pRPD_ratio[11][2] > 1.5 && pRPD_ratio[11][2] < 2.1) {
                                    pRPD_signal[11][2] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[11]->Fill(pRPD_signal[11][2]);
                                    
                                    }   
                                    if (channel[n] == 6) {
                                    Run375259_pRPD_TS[7]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[7]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[7]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[7]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[7]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[7]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[7][2] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[7]->Fill(pRPD_ratio[7][2]);
                                    
                                    if (pRPD_ratio[7][2] > 1.6 && pRPD_ratio[7][2] < 2.4) {
                                    pRPD_signal[7][2] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[7]->Fill(pRPD_signal[7][2]);
                                    
                                    }   
                                    if (channel[n] == 7) {
                                    Run375259_pRPD_TS[3]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[3]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[3]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[3]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[3]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[3]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[3][2] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[3]->Fill(pRPD_ratio[3][2]);
                                    
                                    if (pRPD_ratio[3][2] > 1.5 && pRPD_ratio[3][2] < 2.4) {
                                    pRPD_signal[3][2] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[3]->Fill(pRPD_signal[3][2]);
                                    
                                    }   
                                    if (channel[n] == 8) {
                                    Run375259_pRPD_TS[15]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[15]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[15]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[15]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[15]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[15]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[15][2] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[15]->Fill(pRPD_ratio[15][2]);

                                    if (pRPD_ratio[15][2] > 1.6 && pRPD_ratio[15][2] < 2.2) {
                                    pRPD_signal[15][2] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[15]->Fill(pRPD_signal[15][2]);
                                    }   
                                    if (channel[n] == 9) {
                                    Run375259_pRPD_TS[4]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[4]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[4]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[4]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[4]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[4]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[4][2] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[4]->Fill(pRPD_ratio[4][2]);

                                    if (pRPD_ratio[4][2] > 1.5 && pRPD_ratio[4][2] < 2.4 ) {
                                    pRPD_signal[4][2] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[4]->Fill(pRPD_signal[4][2]);
                                    }   
                                    if (channel[n] == 10) {
                                    Run375259_pRPD_TS[8]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[8]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[8]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[8]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[8]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[8]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[8][2] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[8]->Fill(pRPD_ratio[8][2]);

                                    if (pRPD_ratio[8][2] > 1.5 && pRPD_ratio[8][2] < 2.3) {
                                    pRPD_signal[8][2] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[8]->Fill(pRPD_signal[8][2]);
                                    }   
                                    if (channel[n] == 11) {
                                    Run375259_pRPD_TS[12]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[12]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[12]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[12]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[12]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[12]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[12][2] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[12]->Fill(pRPD_ratio[12][2]);

                                    if (pRPD_ratio[12][2] > 1.5 && pRPD_ratio[12][2] < 2.2){
                                    pRPD_signal[12][2] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[12]->Fill(pRPD_signal[12][2]);
                                    }   
                                    if (channel[n] == 12) {
                                    Run375259_pRPD_TS[0]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[0]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[0]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[0]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[0]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[0]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[0][2] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[0]->Fill(pRPD_ratio[0][2]);

                                    if (pRPD_ratio[0][2] > 1.5 && pRPD_ratio[0][2] < 2.3){
                                    pRPD_signal[0][2] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[0]->Fill(pRPD_signal[0][2]);
                                    }   
                                    if (channel[n] == 13) {
                                    Run375259_pRPD_TS[5]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[5]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[5]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[5]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[5]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[5]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[5][2] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[5]->Fill(pRPD_ratio[5][2]);

                                    if (pRPD_ratio[5][2] > 1.7 && pRPD_ratio[5][2] < 2.5){
                                    pRPD_signal[5][2] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[5]->Fill(pRPD_signal[5][2]);
                                    }   
                                    if (channel[n] == 14) {
                                    Run375259_pRPD_TS[9]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[9]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[9]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[9]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[9]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[9]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[9][2] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[9]->Fill(pRPD_ratio[9][2]);
                                    
                                    if (pRPD_ratio[9][2] > 1.6 && pRPD_ratio[9][2] < 2.4) {
                                    pRPD_signal[9][2] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[9]->Fill(pRPD_signal[9][2]);
                                    }   
                                    if (channel[n] == 15) {
                                    Run375259_pRPD_TS[13]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[13]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[13]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[13]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[13]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[13]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[13][2] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[13]->Fill(pRPD_ratio[13][2]);

                                    if (pRPD_ratio[13][2] > 1.6 && pRPD_ratio[13][2] < 2.4) {
                                    pRPD_signal[13][2] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[13]->Fill(pRPD_signal[13][2]);
                                    }   
                                    if (channel[n] == 16) {
                                    Run375259_pRPD_TS[1]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[1]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[1]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[1]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[1]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[1]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[1][2] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[1]->Fill(pRPD_ratio[1][2]);

                                    if (pRPD_ratio[1][2] > 1.5 && pRPD_ratio[1][2] < 2.5) {
                                    pRPD_signal[1][2] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[1]->Fill(pRPD_signal[1][2]);
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
                            }  // end of channel loop
                            Run375259_pRPD_COM[2]->Fill(pRPD_signal_col[2], pRPD_signal_row[2]);
                            // fill projection
                            pos_rpd_xprojection[2]->Fill(pRPD_signal_col[2]);
                            // fill profile
                            Run375259_pRPD_prof[2]->Fill(0.0,pRPDX1[2]);
                            Run375259_pRPD_prof[2]->Fill(1.0,pRPDX2[2]);
                            Run375259_pRPD_prof[2]->Fill(2.0,pRPDX3[2]);
                            Run375259_pRPD_prof[2]->Fill(3.0,pRPDX4[2]);
                    } // end of sum cut
                } // end of hibin 

                if (hibin >=60 && hibin < 80 ){ 
                    if (pRPD_sum > 3200) {
                            for (int n = 0; n < 56; n++) {
                                if (zside[n] == 1 && section[n] == 4) {
                                    if (channel[n] == 1) {
                                    Run375259_pRPD_TS[10]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[10]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[10]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[10]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[10]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[10]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[10][3] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[10]->Fill(pRPD_ratio[10][3]);

                                    if (pRPD_ratio[10][3] > 1.5 && pRPD_ratio[10][3] < 2.0) {
                                    pRPD_signal[10][3] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[10]->Fill(pRPD_signal[10][3]);
                                    
                                    }
                                    if (channel[n] == 2) {
                                    Run375259_pRPD_TS[6]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[6]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[6]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[6]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[6]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[6]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[6][3] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[6]->Fill(pRPD_ratio[6][3]);
                                    
                                    if (pRPD_ratio[6][3] > 1.5 && pRPD_ratio[6][3] < 2.1) {
                                    pRPD_signal[6][3] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[6]->Fill(pRPD_signal[6][3]);
                                    
                                    } 
                                    if (channel[n] == 3) {
                                    Run375259_pRPD_TS[2]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[2]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[2]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[2]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[2]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[2]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[2][3] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[2]->Fill(pRPD_ratio[2][3]);
                                    
                                    if (pRPD_ratio[2][3] > 1.5 && pRPD_ratio[2][3] < 2.0) {
                                    pRPD_signal[2][3] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[2]->Fill(pRPD_signal[2][3]);
                                    
                                    }      
                                    if (channel[n] == 4) {
                                    Run375259_pRPD_TS[14]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[14]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[14]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[14]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[14]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[14]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[14][3] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[14]->Fill(pRPD_ratio[14][3]);

                                    if (pRPD_ratio[14][3] > 1.5 && pRPD_ratio[14][3] < 2.0) {
                                    pRPD_signal[14][3] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[14]->Fill(pRPD_signal[14][3]);
                                    
                                    }   
                                    if (channel[n] == 5) {
                                    Run375259_pRPD_TS[11]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[11]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[11]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[11]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[11]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[11]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[11][3] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[11]->Fill(pRPD_ratio[11][3]);
                                    
                                    if (pRPD_ratio[11][3] > 1.5 && pRPD_ratio[11][3] < 2.1) {
                                    pRPD_signal[11][3] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[11]->Fill(pRPD_signal[11][3]);
                                    
                                    }   
                                    if (channel[n] == 6) {
                                    Run375259_pRPD_TS[7]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[7]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[7]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[7]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[7]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[7]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[7][3] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[7]->Fill(pRPD_ratio[7][3]);
                                    
                                    if (pRPD_ratio[7][3] > 1.6 && pRPD_ratio[7][3] < 2.4) {
                                    pRPD_signal[7][3] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[7]->Fill(pRPD_signal[7][3]);
                                    
                                    }   
                                    if (channel[n] == 7) {
                                    Run375259_pRPD_TS[3]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[3]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[3]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[3]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[3]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[3]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[3][3] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[3]->Fill(pRPD_ratio[3][3]);
                                    
                                    if (pRPD_ratio[3][3] > 1.5 && pRPD_ratio[3][3] < 2.4) {
                                    pRPD_signal[3][3] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[3]->Fill(pRPD_signal[3][3]);
                                    
                                    }   
                                    if (channel[n] == 8) {
                                    Run375259_pRPD_TS[15]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[15]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[15]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[15]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[15]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[15]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[15][3] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[15]->Fill(pRPD_ratio[15][3]);

                                    if (pRPD_ratio[15][3] > 1.6 && pRPD_ratio[15][3] < 2.2) {
                                    pRPD_signal[15][3] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[15]->Fill(pRPD_signal[15][3]);
                                    }   
                                    if (channel[n] == 9) {
                                    Run375259_pRPD_TS[4]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[4]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[4]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[4]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[4]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[4]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[4][3] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[4]->Fill(pRPD_ratio[4][3]);

                                    if (pRPD_ratio[4][3] > 1.5 && pRPD_ratio[4][3] < 2.4 ) {
                                    pRPD_signal[4][3] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[4]->Fill(pRPD_signal[4][3]);
                                    }   
                                    if (channel[n] == 10) {
                                    Run375259_pRPD_TS[8]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[8]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[8]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[8]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[8]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[8]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[8][3] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[8]->Fill(pRPD_ratio[8][3]);

                                    if (pRPD_ratio[8][3] > 1.5 && pRPD_ratio[8][3] < 2.3) {
                                    pRPD_signal[8][3] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[8]->Fill(pRPD_signal[8][3]);
                                    }   
                                    if (channel[n] == 11) {
                                    Run375259_pRPD_TS[12]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[12]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[12]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[12]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[12]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[12]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[12][3] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[12]->Fill(pRPD_ratio[12][3]);

                                    if (pRPD_ratio[12][3] > 1.5 && pRPD_ratio[12][3] < 2.2){
                                    pRPD_signal[12][3] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[12]->Fill(pRPD_signal[12][3]);
                                    }   
                                    if (channel[n] == 12) {
                                    Run375259_pRPD_TS[0]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[0]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[0]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[0]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[0]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[0]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[0][3] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[0]->Fill(pRPD_ratio[0][3]);

                                    if (pRPD_ratio[0][3] > 1.5 && pRPD_ratio[0][3] < 2.3){
                                    pRPD_signal[0][3] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[0]->Fill(pRPD_signal[0][3]);
                                    }   
                                    if (channel[n] == 13) {
                                    Run375259_pRPD_TS[5]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[5]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[5]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[5]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[5]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[5]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[5][3] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[5]->Fill(pRPD_ratio[5][3]);

                                    if (pRPD_ratio[5][3] > 1.7 && pRPD_ratio[5][3] < 2.5){
                                    pRPD_signal[5][3] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[5]->Fill(pRPD_signal[5][3]);
                                    }   
                                    if (channel[n] == 14) {
                                    Run375259_pRPD_TS[9]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[9]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[9]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[9]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[9]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[9]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[9][3] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[9]->Fill(pRPD_ratio[9][3]);
                                    
                                    if (pRPD_ratio[9][3] > 1.6 && pRPD_ratio[9][3] < 2.4) {
                                    pRPD_signal[9][3] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[9]->Fill(pRPD_signal[9][3]);
                                    }   
                                    if (channel[n] == 15) {
                                    Run375259_pRPD_TS[13]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[13]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[13]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[13]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[13]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[13]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[13][3] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[13]->Fill(pRPD_ratio[13][3]);

                                    if (pRPD_ratio[13][3] > 1.6 && pRPD_ratio[13][3] < 2.4) {
                                    pRPD_signal[13][3] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[13]->Fill(pRPD_signal[13][3]);
                                    }   
                                    if (channel[n] == 16) {
                                    Run375259_pRPD_TS[1]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[1]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[1]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[1]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[1]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[1]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[1][3] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[1]->Fill(pRPD_ratio[1][3]);

                                    if (pRPD_ratio[1][3] > 1.5 && pRPD_ratio[1][3] < 2.5) {
                                    pRPD_signal[1][3] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[1]->Fill(pRPD_signal[1][3]);
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
                            }  // end of channel loop
                            Run375259_pRPD_COM[3]->Fill(pRPD_signal_col[3], pRPD_signal_row[3]);
                            // fill projection
                            pos_rpd_xprojection[3]->Fill(pRPD_signal_col[3]);
                            // fill profile
                            Run375259_pRPD_prof[3]->Fill(0.0,pRPDX1[3]);
                            Run375259_pRPD_prof[3]->Fill(1.0,pRPDX2[3]);
                            Run375259_pRPD_prof[3]->Fill(2.0,pRPDX3[3]);
                            Run375259_pRPD_prof[3]->Fill(3.0,pRPDX4[3]);
                    } // end of sum cut
                } // end of hibin 
                if (hibin >=80 && hibin < 100 ){ 
                    if (pRPD_sum > 3200) {
                            for (int n = 0; n < 56; n++) {
                                if (zside[n] == 1 && section[n] == 4) {
                                    if (channel[n] == 1) {
                                    Run375259_pRPD_TS[10]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[10]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[10]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[10]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[10]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[10]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[10][4] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[10]->Fill(pRPD_ratio[10][4]);

                                    if (pRPD_ratio[10][4] > 1.5 && pRPD_ratio[10][4] < 2.0) {
                                    pRPD_signal[10][4] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[10]->Fill(pRPD_signal[10][4]);
                                    
                                    }
                                    if (channel[n] == 2) {
                                    Run375259_pRPD_TS[6]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[6]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[6]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[6]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[6]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[6]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[6][4] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[6]->Fill(pRPD_ratio[6][4]);
                                    
                                    if (pRPD_ratio[6][4] > 1.5 && pRPD_ratio[6][4] < 2.1) {
                                    pRPD_signal[6][4] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[6]->Fill(pRPD_signal[6][4]);
                                    
                                    } 
                                    if (channel[n] == 3) {
                                    Run375259_pRPD_TS[2]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[2]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[2]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[2]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[2]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[2]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[2][4] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[2]->Fill(pRPD_ratio[2][4]);
                                    
                                    if (pRPD_ratio[2][4] > 1.5 && pRPD_ratio[2][4] < 2.0) {
                                    pRPD_signal[2][4] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[2]->Fill(pRPD_signal[2][4]);
                                    
                                    }      
                                    if (channel[n] == 4) {
                                    Run375259_pRPD_TS[14]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[14]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[14]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[14]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[14]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[14]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[14][4] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[14]->Fill(pRPD_ratio[14][4]);

                                    if (pRPD_ratio[14][4] > 1.5 && pRPD_ratio[14][4] < 2.0) {
                                    pRPD_signal[14][4] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[14]->Fill(pRPD_signal[14][4]);
                                    
                                    }   
                                    if (channel[n] == 5) {
                                    Run375259_pRPD_TS[11]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[11]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[11]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[11]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[11]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[11]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[11][4] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[11]->Fill(pRPD_ratio[11][4]);
                                    
                                    if (pRPD_ratio[11][4] > 1.5 && pRPD_ratio[11][4] < 2.1) {
                                    pRPD_signal[11][4] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[11]->Fill(pRPD_signal[11][4]);
                                    
                                    }   
                                    if (channel[n] == 6) {
                                    Run375259_pRPD_TS[7]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[7]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[7]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[7]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[7]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[7]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[7][4] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[7]->Fill(pRPD_ratio[7][4]);
                                    
                                    if (pRPD_ratio[7][4] > 1.6 && pRPD_ratio[7][4] < 2.4) {
                                    pRPD_signal[7][4] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[7]->Fill(pRPD_signal[7][4]);
                                    
                                    }   
                                    if (channel[n] == 7) {
                                    Run375259_pRPD_TS[3]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[3]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[3]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[3]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[3]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[3]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[3][4] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[3]->Fill(pRPD_ratio[3][4]);
                                    
                                    if (pRPD_ratio[3][4] > 1.5 && pRPD_ratio[3][4] < 2.4) {
                                    pRPD_signal[3][4] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[3]->Fill(pRPD_signal[3][4]);
                                    
                                    }   
                                    if (channel[n] == 8) {
                                    Run375259_pRPD_TS[15]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[15]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[15]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[15]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[15]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[15]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[15][4] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[15]->Fill(pRPD_ratio[15][4]);

                                    if (pRPD_ratio[15][4] > 1.6 && pRPD_ratio[15][4] < 2.2) {
                                    pRPD_signal[15][4] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[15]->Fill(pRPD_signal[15][4]);
                                    }   
                                    if (channel[n] == 9) {
                                    Run375259_pRPD_TS[4]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[4]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[4]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[4]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[4]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[4]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[4][4] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[4]->Fill(pRPD_ratio[4][4]);

                                    if (pRPD_ratio[4][4] > 1.5 && pRPD_ratio[4][4] < 2.4 ) {
                                    pRPD_signal[4][4] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[4]->Fill(pRPD_signal[4][4]);
                                    }   
                                    if (channel[n] == 10) {
                                    Run375259_pRPD_TS[8]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[8]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[8]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[8]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[8]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[8]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[8][4] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[8]->Fill(pRPD_ratio[8][4]);

                                    if (pRPD_ratio[8][4] > 1.5 && pRPD_ratio[8][4] < 2.3) {
                                    pRPD_signal[8][4] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[8]->Fill(pRPD_signal[8][4]);
                                    }   
                                    if (channel[n] == 11) {
                                    Run375259_pRPD_TS[12]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[12]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[12]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[12]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[12]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[12]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[12][4] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[12]->Fill(pRPD_ratio[12][4]);

                                    if (pRPD_ratio[12][4] > 1.5 && pRPD_ratio[12][4] < 2.2){
                                    pRPD_signal[12][4] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[12]->Fill(pRPD_signal[12][4]);
                                    }   
                                    if (channel[n] == 12) {
                                    Run375259_pRPD_TS[0]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[0]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[0]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[0]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[0]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[0]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[0][4] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[0]->Fill(pRPD_ratio[0][4]);

                                    if (pRPD_ratio[0][4] > 1.5 && pRPD_ratio[0][4] < 2.3){
                                    pRPD_signal[0][4] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[0]->Fill(pRPD_signal[0][4]);
                                    }   
                                    if (channel[n] == 13) {
                                    Run375259_pRPD_TS[5]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[5]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[5]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[5]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[5]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[5]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[5][4] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[5]->Fill(pRPD_ratio[5][4]);

                                    if (pRPD_ratio[5][4] > 1.7 && pRPD_ratio[5][4] < 2.5){
                                    pRPD_signal[5][4] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[5]->Fill(pRPD_signal[5][4]);
                                    }   
                                    if (channel[n] == 14) {
                                    Run375259_pRPD_TS[9]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[9]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[9]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[9]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[9]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[9]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[9][4] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[9]->Fill(pRPD_ratio[9][4]);
                                    
                                    if (pRPD_ratio[9][4] > 1.6 && pRPD_ratio[9][4] < 2.4) {
                                    pRPD_signal[9][4] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[9]->Fill(pRPD_signal[9][4]);
                                    }   
                                    if (channel[n] == 15) {
                                    Run375259_pRPD_TS[13]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[13]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[13]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[13]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[13]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[13]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[13][4] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[13]->Fill(pRPD_ratio[13][4]);

                                    if (pRPD_ratio[13][4] > 1.6 && pRPD_ratio[13][4] < 2.4) {
                                    pRPD_signal[13][4] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[13]->Fill(pRPD_signal[13][4]);
                                    }   
                                    if (channel[n] == 16) {
                                    Run375259_pRPD_TS[1]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[1]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[1]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[1]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[1]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[1]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[1][4] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[1]->Fill(pRPD_ratio[1][4]);

                                    if (pRPD_ratio[1][4] > 1.5 && pRPD_ratio[1][4] < 2.5) {
                                    pRPD_signal[1][4] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[1]->Fill(pRPD_signal[1][4]);
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
                            }  // end of channel loop
                            Run375259_pRPD_COM[4]->Fill(pRPD_signal_col[4], pRPD_signal_row[4]);
                            // fill projection
                            pos_rpd_xprojection[4]->Fill(pRPD_signal_col[4]);
                            // fill profile
                            Run375259_pRPD_prof[4]->Fill(0.0,pRPDX1[4]);
                            Run375259_pRPD_prof[4]->Fill(1.0,pRPDX2[4]);
                            Run375259_pRPD_prof[4]->Fill(2.0,pRPDX3[4]);
                            Run375259_pRPD_prof[4]->Fill(3.0,pRPDX4[4]);
                    } // end of sum cut
                } // end of hibin 
                if (hibin >=100 && hibin < 120 ){ 
                    if (pRPD_sum > 3200) {
                            for (int n = 0; n < 56; n++) {
                                if (zside[n] == 1 && section[n] == 4) {
                                    if (channel[n] == 1) {
                                    Run375259_pRPD_TS[10]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[10]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[10]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[10]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[10]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[10]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[10][5] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[10]->Fill(pRPD_ratio[10][5]);

                                    if (pRPD_ratio[10][5] > 1.5 && pRPD_ratio[10][5] < 2.0) {
                                    pRPD_signal[10][5] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[10]->Fill(pRPD_signal[10][5]);
                                    
                                    }
                                    if (channel[n] == 2) {
                                    Run375259_pRPD_TS[6]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[6]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[6]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[6]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[6]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[6]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[6][5] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[6]->Fill(pRPD_ratio[6][5]);
                                    
                                    if (pRPD_ratio[6][5] > 1.5 && pRPD_ratio[6][5] < 2.1) {
                                    pRPD_signal[6][5] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[6]->Fill(pRPD_signal[6][5]);
                                    
                                    } 
                                    if (channel[n] == 3) {
                                    Run375259_pRPD_TS[2]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[2]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[2]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[2]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[2]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[2]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[2][5] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[2]->Fill(pRPD_ratio[2][5]);
                                    
                                    if (pRPD_ratio[2][5] > 1.5 && pRPD_ratio[2][5] < 2.0) {
                                    pRPD_signal[2][5] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[2]->Fill(pRPD_signal[2][5]);
                                    
                                    }      
                                    if (channel[n] == 4) {
                                    Run375259_pRPD_TS[14]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[14]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[14]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[14]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[14]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[14]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[14][5] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[14]->Fill(pRPD_ratio[14][5]);

                                    if (pRPD_ratio[14][5] > 1.5 && pRPD_ratio[14][5] < 2.0) {
                                    pRPD_signal[14][5] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[14]->Fill(pRPD_signal[14][5]);
                                    
                                    }   
                                    if (channel[n] == 5) {
                                    Run375259_pRPD_TS[11]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[11]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[11]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[11]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[11]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[11]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[11][5] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[11]->Fill(pRPD_ratio[11][5]);
                                    
                                    if (pRPD_ratio[11][5] > 1.5 && pRPD_ratio[11][5] < 2.1) {
                                    pRPD_signal[11][5] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[11]->Fill(pRPD_signal[11][5]);
                                    
                                    }   
                                    if (channel[n] == 6) {
                                    Run375259_pRPD_TS[7]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[7]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[7]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[7]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[7]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[7]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[7][5] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[7]->Fill(pRPD_ratio[7][5]);
                                    
                                    if (pRPD_ratio[7][5] > 1.6 && pRPD_ratio[7][5] < 2.4) {
                                    pRPD_signal[7][5] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[7]->Fill(pRPD_signal[7][5]);
                                    
                                    }   
                                    if (channel[n] == 7) {
                                    Run375259_pRPD_TS[3]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[3]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[3]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[3]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[3]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[3]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[3][5] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[3]->Fill(pRPD_ratio[3][5]);
                                    
                                    if (pRPD_ratio[3][5] > 1.5 && pRPD_ratio[3][5] < 2.4) {
                                    pRPD_signal[3][5] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[3]->Fill(pRPD_signal[3][5]);
                                    
                                    }   
                                    if (channel[n] == 8) {
                                    Run375259_pRPD_TS[15]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[15]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[15]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[15]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[15]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[15]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[15][5] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[15]->Fill(pRPD_ratio[15][5]);

                                    if (pRPD_ratio[15][5] > 1.6 && pRPD_ratio[15][5] < 2.2) {
                                    pRPD_signal[15][5] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[15]->Fill(pRPD_signal[15][5]);
                                    }   
                                    if (channel[n] == 9) {
                                    Run375259_pRPD_TS[4]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[4]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[4]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[4]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[4]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[4]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[4][5] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[4]->Fill(pRPD_ratio[4][5]);

                                    if (pRPD_ratio[4][5] > 1.5 && pRPD_ratio[4][5] < 2.4 ) {
                                    pRPD_signal[4][5] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[4]->Fill(pRPD_signal[4][5]);
                                    }   
                                    if (channel[n] == 10) {
                                    Run375259_pRPD_TS[8]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[8]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[8]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[8]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[8]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[8]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[8][5] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[8]->Fill(pRPD_ratio[8][5]);

                                    if (pRPD_ratio[8][5] > 1.5 && pRPD_ratio[8][5] < 2.3) {
                                    pRPD_signal[8][5] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[8]->Fill(pRPD_signal[8][5]);
                                    }   
                                    if (channel[n] == 11) {
                                    Run375259_pRPD_TS[12]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[12]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[12]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[12]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[12]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[12]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[12][5] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[12]->Fill(pRPD_ratio[12][5]);

                                    if (pRPD_ratio[12][5] > 1.5 && pRPD_ratio[12][5] < 2.2){
                                    pRPD_signal[12][5] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[12]->Fill(pRPD_signal[12][5]);
                                    }   
                                    if (channel[n] == 12) {
                                    Run375259_pRPD_TS[0]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[0]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[0]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[0]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[0]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[0]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[0][5] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[0]->Fill(pRPD_ratio[0][5]);

                                    if (pRPD_ratio[0][5] > 1.5 && pRPD_ratio[0][5] < 2.3){
                                    pRPD_signal[0][5] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[0]->Fill(pRPD_signal[0][5]);
                                    }   
                                    if (channel[n] == 13) {
                                    Run375259_pRPD_TS[5]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[5]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[5]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[5]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[5]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[5]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[5][5] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[5]->Fill(pRPD_ratio[5][5]);

                                    if (pRPD_ratio[5][5] > 1.7 && pRPD_ratio[5][5] < 2.5){
                                    pRPD_signal[5][5] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[5]->Fill(pRPD_signal[5][5]);
                                    }   
                                    if (channel[n] == 14) {
                                    Run375259_pRPD_TS[9]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[9]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[9]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[9]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[9]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[9]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[9][5] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[9]->Fill(pRPD_ratio[9][5]);
                                    
                                    if (pRPD_ratio[9][5] > 1.6 && pRPD_ratio[9][5] < 2.4) {
                                    pRPD_signal[9][5] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[9]->Fill(pRPD_signal[9][5]);
                                    }   
                                    if (channel[n] == 15) {
                                    Run375259_pRPD_TS[13]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[13]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[13]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[13]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[13]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[13]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[13][5] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[13]->Fill(pRPD_ratio[13][5]);

                                    if (pRPD_ratio[13][5] > 1.6 && pRPD_ratio[13][5] < 2.4) {
                                    pRPD_signal[13][5] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[13]->Fill(pRPD_signal[13][5]);
                                    }   
                                    if (channel[n] == 16) {
                                    Run375259_pRPD_TS[1]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[1]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[1]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[1]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[1]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[1]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[1][5] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[1]->Fill(pRPD_ratio[1][5]);

                                    if (pRPD_ratio[1][5] > 1.5 && pRPD_ratio[1][5] < 2.5) {
                                    pRPD_signal[1][5] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[1]->Fill(pRPD_signal[1][5]);
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
                            }  // end of channel loop
                            Run375259_pRPD_COM[5]->Fill(pRPD_signal_col[5], pRPD_signal_row[5]);
                            // fill projection
                            pos_rpd_xprojection[5]->Fill(pRPD_signal_col[5]);
                            // fill profile
                            Run375259_pRPD_prof[5]->Fill(0.0,pRPDX1[5]);
                            Run375259_pRPD_prof[5]->Fill(1.0,pRPDX2[5]);
                            Run375259_pRPD_prof[5]->Fill(2.0,pRPDX3[5]);
                            Run375259_pRPD_prof[5]->Fill(3.0,pRPDX4[5]);
                    } // end of sum cut
                } // end of hibin 
                if (hibin >=120 && hibin < 140 ){ 
                    if (pRPD_sum > 3200) {
                            for (int n = 0; n < 56; n++) {
                                if (zside[n] == 1 && section[n] == 4) {
                                    if (channel[n] == 1) {
                                    Run375259_pRPD_TS[10]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[10]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[10]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[10]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[10]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[10]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[10][6] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[10]->Fill(pRPD_ratio[10][6]);

                                    if (pRPD_ratio[10][6] > 1.5 && pRPD_ratio[10][6] < 2.0) {
                                    pRPD_signal[10][6] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[10]->Fill(pRPD_signal[10][6]);
                                    
                                    }
                                    if (channel[n] == 2) {
                                    Run375259_pRPD_TS[6]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[6]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[6]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[6]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[6]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[6]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[6][6] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[6]->Fill(pRPD_ratio[6][6]);
                                    
                                    if (pRPD_ratio[6][6] > 1.5 && pRPD_ratio[6][6] < 2.1) {
                                    pRPD_signal[6][6] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[6]->Fill(pRPD_signal[6][6]);
                                    
                                    } 
                                    if (channel[n] == 3) {
                                    Run375259_pRPD_TS[2]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[2]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[2]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[2]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[2]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[2]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[2][6] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[2]->Fill(pRPD_ratio[2][6]);
                                    
                                    if (pRPD_ratio[2][6] > 1.5 && pRPD_ratio[2][6] < 2.0) {
                                    pRPD_signal[2][6] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[2]->Fill(pRPD_signal[2][6]);
                                    
                                    }      
                                    if (channel[n] == 4) {
                                    Run375259_pRPD_TS[14]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[14]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[14]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[14]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[14]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[14]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[14][6] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[14]->Fill(pRPD_ratio[14][6]);

                                    if (pRPD_ratio[14][6] > 1.5 && pRPD_ratio[14][6] < 2.0) {
                                    pRPD_signal[14][6] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[14]->Fill(pRPD_signal[14][6]);
                                    
                                    }   
                                    if (channel[n] == 5) {
                                    Run375259_pRPD_TS[11]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[11]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[11]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[11]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[11]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[11]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[11][6] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[11]->Fill(pRPD_ratio[11][6]);
                                    
                                    if (pRPD_ratio[11][6] > 1.5 && pRPD_ratio[11][6] < 2.1) {
                                    pRPD_signal[11][6] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[11]->Fill(pRPD_signal[11][6]);
                                    
                                    }   
                                    if (channel[n] == 6) {
                                    Run375259_pRPD_TS[7]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[7]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[7]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[7]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[7]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[7]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[7][6] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[7]->Fill(pRPD_ratio[7][6]);
                                    
                                    if (pRPD_ratio[7][6] > 1.6 && pRPD_ratio[7][6] < 2.4) {
                                    pRPD_signal[7][6] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[7]->Fill(pRPD_signal[7][6]);
                                    
                                    }   
                                    if (channel[n] == 7) {
                                    Run375259_pRPD_TS[3]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[3]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[3]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[3]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[3]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[3]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[3][6] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[3]->Fill(pRPD_ratio[3][6]);
                                    
                                    if (pRPD_ratio[3][6] > 1.5 && pRPD_ratio[3][6] < 2.4) {
                                    pRPD_signal[3][6] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[3]->Fill(pRPD_signal[3][6]);
                                    
                                    }   
                                    if (channel[n] == 8) {
                                    Run375259_pRPD_TS[15]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[15]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[15]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[15]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[15]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[15]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[15][6] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[15]->Fill(pRPD_ratio[15][6]);

                                    if (pRPD_ratio[15][6] > 1.6 && pRPD_ratio[15][6] < 2.2) {
                                    pRPD_signal[15][6] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[15]->Fill(pRPD_signal[15][6]);
                                    }   
                                    if (channel[n] == 9) {
                                    Run375259_pRPD_TS[4]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[4]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[4]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[4]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[4]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[4]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[4][6] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[4]->Fill(pRPD_ratio[4][6]);

                                    if (pRPD_ratio[4][6] > 1.5 && pRPD_ratio[4][6] < 2.4 ) {
                                    pRPD_signal[4][6] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[4]->Fill(pRPD_signal[4][6]);
                                    }   
                                    if (channel[n] == 10) {
                                    Run375259_pRPD_TS[8]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[8]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[8]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[8]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[8]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[8]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[8][6] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[8]->Fill(pRPD_ratio[8][6]);

                                    if (pRPD_ratio[8][6] > 1.5 && pRPD_ratio[8][6] < 2.3) {
                                    pRPD_signal[8][6] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[8]->Fill(pRPD_signal[8][6]);
                                    }   
                                    if (channel[n] == 11) {
                                    Run375259_pRPD_TS[12]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[12]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[12]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[12]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[12]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[12]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[12][6] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[12]->Fill(pRPD_ratio[12][6]);

                                    if (pRPD_ratio[12][6] > 1.5 && pRPD_ratio[12][6] < 2.2){
                                    pRPD_signal[12][6] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[12]->Fill(pRPD_signal[12][6]);
                                    }   
                                    if (channel[n] == 12) {
                                    Run375259_pRPD_TS[0]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[0]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[0]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[0]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[0]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[0]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[0][6] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[0]->Fill(pRPD_ratio[0][6]);

                                    if (pRPD_ratio[0][6] > 1.5 && pRPD_ratio[0][6] < 2.3){
                                    pRPD_signal[0][6] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[0]->Fill(pRPD_signal[0][6]);
                                    }   
                                    if (channel[n] == 13) {
                                    Run375259_pRPD_TS[5]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[5]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[5]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[5]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[5]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[5]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[5][6] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[5]->Fill(pRPD_ratio[5][6]);

                                    if (pRPD_ratio[5][6] > 1.7 && pRPD_ratio[5][6] < 2.5){
                                    pRPD_signal[5][6] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[5]->Fill(pRPD_signal[5][6]);
                                    }   
                                    if (channel[n] == 14) {
                                    Run375259_pRPD_TS[9]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[9]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[9]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[9]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[9]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[9]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[9][6] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[9]->Fill(pRPD_ratio[9][6]);
                                    
                                    if (pRPD_ratio[9][6] > 1.6 && pRPD_ratio[9][6] < 2.4) {
                                    pRPD_signal[9][6] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[9]->Fill(pRPD_signal[9][6]);
                                    }   
                                    if (channel[n] == 15) {
                                    Run375259_pRPD_TS[13]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[13]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[13]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[13]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[13]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[13]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[13][6] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[13]->Fill(pRPD_ratio[13][6]);

                                    if (pRPD_ratio[13][6] > 1.6 && pRPD_ratio[13][6] < 2.4) {
                                    pRPD_signal[13][6] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[13]->Fill(pRPD_signal[13][6]);
                                    }   
                                    if (channel[n] == 16) {
                                    Run375259_pRPD_TS[1]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[1]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[1]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[1]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[1]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[1]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[1][6] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[1]->Fill(pRPD_ratio[1][6]);

                                    if (pRPD_ratio[1][6] > 1.5 && pRPD_ratio[1][6] < 2.5) {
                                    pRPD_signal[1][6] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[1]->Fill(pRPD_signal[1][6]);
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
                            }  // end of channel loop
                            Run375259_pRPD_COM[6]->Fill(pRPD_signal_col[6], pRPD_signal_row[6]);
                            // fill projection
                            pos_rpd_xprojection[6]->Fill(pRPD_signal_col[6]);
                            // fill profile
                            Run375259_pRPD_prof[6]->Fill(0.0,pRPDX1[6]);
                            Run375259_pRPD_prof[6]->Fill(1.0,pRPDX2[6]);
                            Run375259_pRPD_prof[6]->Fill(2.0,pRPDX3[6]);
                            Run375259_pRPD_prof[6]->Fill(3.0,pRPDX4[6]);
                    } // end of sum cut
                } // end of hibin 
                if (hibin >=140 && hibin < 160 ){ 
                    if (pRPD_sum > 3200) {
                            for (int n = 0; n < 56; n++) {
                                if (zside[n] == 1 && section[n] == 4) {
                                    if (channel[n] == 1) {
                                    Run375259_pRPD_TS[10]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[10]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[10]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[10]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[10]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[10]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[10][7] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[10]->Fill(pRPD_ratio[10][7]);

                                    if (pRPD_ratio[10][7] > 1.5 && pRPD_ratio[10][7] < 2.0) {
                                    pRPD_signal[10][7] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[10]->Fill(pRPD_signal[10][7]);
                                    
                                    }
                                    if (channel[n] == 2) {
                                    Run375259_pRPD_TS[6]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[6]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[6]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[6]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[6]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[6]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[6][7] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[6]->Fill(pRPD_ratio[6][7]);
                                    
                                    if (pRPD_ratio[6][7] > 1.5 && pRPD_ratio[6][7] < 2.1) {
                                    pRPD_signal[6][7] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[6]->Fill(pRPD_signal[6][7]);
                                    
                                    } 
                                    if (channel[n] == 3) {
                                    Run375259_pRPD_TS[2]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[2]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[2]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[2]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[2]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[2]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[2][7] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[2]->Fill(pRPD_ratio[2][7]);
                                    
                                    if (pRPD_ratio[2][7] > 1.5 && pRPD_ratio[2][7] < 2.0) {
                                    pRPD_signal[2][7] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[2]->Fill(pRPD_signal[2][7]);
                                    
                                    }      
                                    if (channel[n] == 4) {
                                    Run375259_pRPD_TS[14]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[14]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[14]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[14]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[14]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[14]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[14][7] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[14]->Fill(pRPD_ratio[14][7]);

                                    if (pRPD_ratio[14][7] > 1.5 && pRPD_ratio[14][7] < 2.0) {
                                    pRPD_signal[14][7] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[14]->Fill(pRPD_signal[14][7]);
                                    
                                    }   
                                    if (channel[n] == 5) {
                                    Run375259_pRPD_TS[11]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[11]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[11]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[11]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[11]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[11]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[11][7] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[11]->Fill(pRPD_ratio[11][7]);
                                    
                                    if (pRPD_ratio[11][7] > 1.5 && pRPD_ratio[11][7] < 2.1) {
                                    pRPD_signal[11][7] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[11]->Fill(pRPD_signal[11][7]);
                                    
                                    }   
                                    if (channel[n] == 6) {
                                    Run375259_pRPD_TS[7]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[7]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[7]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[7]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[7]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[7]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[7][7] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[7]->Fill(pRPD_ratio[7][7]);
                                    
                                    if (pRPD_ratio[7][7] > 1.6 && pRPD_ratio[7][7] < 2.4) {
                                    pRPD_signal[7][7] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[7]->Fill(pRPD_signal[7][7]);
                                    
                                    }   
                                    if (channel[n] == 7) {
                                    Run375259_pRPD_TS[3]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[3]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[3]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[3]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[3]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[3]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[3][7] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[3]->Fill(pRPD_ratio[3][7]);
                                    
                                    if (pRPD_ratio[3][7] > 1.5 && pRPD_ratio[3][7] < 2.4) {
                                    pRPD_signal[3][7] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[3]->Fill(pRPD_signal[3][7]);
                                    
                                    }   
                                    if (channel[n] == 8) {
                                    Run375259_pRPD_TS[15]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[15]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[15]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[15]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[15]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[15]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[15][7] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[15]->Fill(pRPD_ratio[15][7]);

                                    if (pRPD_ratio[15][7] > 1.6 && pRPD_ratio[15][7] < 2.2) {
                                    pRPD_signal[15][7] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[15]->Fill(pRPD_signal[15][7]);
                                    }   
                                    if (channel[n] == 9) {
                                    Run375259_pRPD_TS[4]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[4]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[4]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[4]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[4]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[4]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[4][7] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[4]->Fill(pRPD_ratio[4][7]);

                                    if (pRPD_ratio[4][7] > 1.5 && pRPD_ratio[4][7] < 2.4 ) {
                                    pRPD_signal[4][7] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[4]->Fill(pRPD_signal[4][7]);
                                    }   
                                    if (channel[n] == 10) {
                                    Run375259_pRPD_TS[8]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[8]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[8]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[8]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[8]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[8]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[8][7] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[8]->Fill(pRPD_ratio[8][7]);

                                    if (pRPD_ratio[8][7] > 1.5 && pRPD_ratio[8][7] < 2.3) {
                                    pRPD_signal[8][7] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[8]->Fill(pRPD_signal[8][7]);
                                    }   
                                    if (channel[n] == 11) {
                                    Run375259_pRPD_TS[12]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[12]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[12]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[12]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[12]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[12]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[12][7] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[12]->Fill(pRPD_ratio[12][7]);

                                    if (pRPD_ratio[12][7] > 1.5 && pRPD_ratio[12][7] < 2.2){
                                    pRPD_signal[12][7] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[12]->Fill(pRPD_signal[12][7]);
                                    }   
                                    if (channel[n] == 12) {
                                    Run375259_pRPD_TS[0]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[0]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[0]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[0]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[0]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[0]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[0][7] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[0]->Fill(pRPD_ratio[0][7]);

                                    if (pRPD_ratio[0][7] > 1.5 && pRPD_ratio[0][7] < 2.3){
                                    pRPD_signal[0][7] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[0]->Fill(pRPD_signal[0][7]);
                                    }   
                                    if (channel[n] == 13) {
                                    Run375259_pRPD_TS[5]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[5]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[5]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[5]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[5]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[5]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[5][7] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[5]->Fill(pRPD_ratio[5][7]);

                                    if (pRPD_ratio[5][7] > 1.7 && pRPD_ratio[5][7] < 2.5){
                                    pRPD_signal[5][7] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[5]->Fill(pRPD_signal[5][7]);
                                    }   
                                    if (channel[n] == 14) {
                                    Run375259_pRPD_TS[9]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[9]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[9]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[9]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[9]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[9]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[9][7] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[9]->Fill(pRPD_ratio[9][7]);
                                    
                                    if (pRPD_ratio[9][7] > 1.6 && pRPD_ratio[9][7] < 2.4) {
                                    pRPD_signal[9][7] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[9]->Fill(pRPD_signal[9][7]);
                                    }   
                                    if (channel[n] == 15) {
                                    Run375259_pRPD_TS[13]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[13]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[13]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[13]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[13]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[13]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[13][7] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[13]->Fill(pRPD_ratio[13][7]);

                                    if (pRPD_ratio[13][7] > 1.6 && pRPD_ratio[13][7] < 2.4) {
                                    pRPD_signal[13][7] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[13]->Fill(pRPD_signal[13][7]);
                                    }   
                                    if (channel[n] == 16) {
                                    Run375259_pRPD_TS[1]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[1]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[1]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[1]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[1]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[1]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[1][7] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[1]->Fill(pRPD_ratio[1][7]);

                                    if (pRPD_ratio[1][7] > 1.5 && pRPD_ratio[1][7] < 2.5) {
                                    pRPD_signal[1][7] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[1]->Fill(pRPD_signal[1][7]);
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
                            }  // end of channel loop
                            Run375259_pRPD_COM[7]->Fill(pRPD_signal_col[7], pRPD_signal_row[7]);
                            // fill projection
                            pos_rpd_xprojection[7]->Fill(pRPD_signal_col[7]);
                            // fill profile
                            Run375259_pRPD_prof[7]->Fill(0.0,pRPDX1[7]);
                            Run375259_pRPD_prof[7]->Fill(1.0,pRPDX2[7]);
                            Run375259_pRPD_prof[7]->Fill(2.0,pRPDX3[7]);
                            Run375259_pRPD_prof[7]->Fill(3.0,pRPDX4[7]);
                    } // end of sum cut
                } // end of hibin 
                if (hibin >=160 && hibin < 180 ){ 
                    if (pRPD_sum > 3200) {
                            for (int n = 0; n < 56; n++) {
                                if (zside[n] == 1 && section[n] == 4) {
                                    if (channel[n] == 1) {
                                    Run375259_pRPD_TS[10]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[10]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[10]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[10]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[10]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[10]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[10][8] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[10]->Fill(pRPD_ratio[10][8]);

                                    if (pRPD_ratio[10][8] > 1.5 && pRPD_ratio[10][8] < 2.0) {
                                    pRPD_signal[10][8] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[10]->Fill(pRPD_signal[10][8]);
                                    
                                    }
                                    if (channel[n] == 2) {
                                    Run375259_pRPD_TS[6]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[6]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[6]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[6]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[6]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[6]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[6][8] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[6]->Fill(pRPD_ratio[6][8]);
                                    
                                    if (pRPD_ratio[6][8] > 1.5 && pRPD_ratio[6][8] < 2.1) {
                                    pRPD_signal[6][8] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[6]->Fill(pRPD_signal[6][8]);
                                    
                                    } 
                                    if (channel[n] == 3) {
                                    Run375259_pRPD_TS[2]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[2]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[2]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[2]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[2]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[2]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[2][8] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[2]->Fill(pRPD_ratio[2][8]);
                                    
                                    if (pRPD_ratio[2][8] > 1.5 && pRPD_ratio[2][8] < 2.0) {
                                    pRPD_signal[2][8] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[2]->Fill(pRPD_signal[2][8]);
                                    
                                    }      
                                    if (channel[n] == 4) {
                                    Run375259_pRPD_TS[14]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[14]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[14]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[14]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[14]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[14]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[14][8] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[14]->Fill(pRPD_ratio[14][8]);

                                    if (pRPD_ratio[14][8] > 1.5 && pRPD_ratio[14][8] < 2.0) {
                                    pRPD_signal[14][8] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[14]->Fill(pRPD_signal[14][8]);
                                    
                                    }   
                                    if (channel[n] == 5) {
                                    Run375259_pRPD_TS[11]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[11]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[11]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[11]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[11]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[11]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[11][8] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[11]->Fill(pRPD_ratio[11][8]);
                                    
                                    if (pRPD_ratio[11][8] > 1.5 && pRPD_ratio[11][8] < 2.1) {
                                    pRPD_signal[11][8] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[11]->Fill(pRPD_signal[11][8]);
                                    
                                    }   
                                    if (channel[n] == 6) {
                                    Run375259_pRPD_TS[7]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[7]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[7]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[7]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[7]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[7]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[7][8] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[7]->Fill(pRPD_ratio[7][8]);
                                    
                                    if (pRPD_ratio[7][8] > 1.6 && pRPD_ratio[7][8] < 2.4) {
                                    pRPD_signal[7][8] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[7]->Fill(pRPD_signal[7][8]);
                                    
                                    }   
                                    if (channel[n] == 7) {
                                    Run375259_pRPD_TS[3]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[3]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[3]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[3]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[3]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[3]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[3][8] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[3]->Fill(pRPD_ratio[3][8]);
                                    
                                    if (pRPD_ratio[3][8] > 1.5 && pRPD_ratio[3][8] < 2.4) {
                                    pRPD_signal[3][8] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[8]->Fill(pRPD_signal[3][8]);
                                    
                                    }   
                                    if (channel[n] == 8) {
                                    Run375259_pRPD_TS[15]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[15]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[15]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[15]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[15]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[15]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[15][8] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[15]->Fill(pRPD_ratio[15][8]);

                                    if (pRPD_ratio[15][8] > 1.6 && pRPD_ratio[15][8] < 2.2) {
                                    pRPD_signal[15][8] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[15]->Fill(pRPD_signal[15][8]);
                                    }   
                                    if (channel[n] == 9) {
                                    Run375259_pRPD_TS[4]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[4]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[4]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[4]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[4]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[4]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[4][8] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[4]->Fill(pRPD_ratio[4][8]);

                                    if (pRPD_ratio[4][8] > 1.5 && pRPD_ratio[4][8] < 2.4 ) {
                                    pRPD_signal[4][8] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[4]->Fill(pRPD_signal[4][8]);
                                    }   
                                    if (channel[n] == 10) {
                                    Run375259_pRPD_TS[8]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[8]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[8]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[8]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[8]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[8]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[8][8] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[8]->Fill(pRPD_ratio[8][8]);

                                    if (pRPD_ratio[8][8] > 1.5 && pRPD_ratio[8][8] < 2.3) {
                                    pRPD_signal[8][8] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[8]->Fill(pRPD_signal[8][8]);
                                    }   
                                    if (channel[n] == 11) {
                                    Run375259_pRPD_TS[12]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[12]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[12]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[12]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[12]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[12]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[12][8] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[12]->Fill(pRPD_ratio[12][8]);

                                    if (pRPD_ratio[12][8] > 1.5 && pRPD_ratio[12][8] < 2.2){
                                    pRPD_signal[12][8] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[12]->Fill(pRPD_signal[12][8]);
                                    }   
                                    if (channel[n] == 12) {
                                    Run375259_pRPD_TS[0]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[0]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[0]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[0]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[0]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[0]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[0][8] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[0]->Fill(pRPD_ratio[0][8]);

                                    if (pRPD_ratio[0][8] > 1.5 && pRPD_ratio[0][8] < 2.3){
                                    pRPD_signal[0][8] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[0]->Fill(pRPD_signal[0][8]);
                                    }   
                                    if (channel[n] == 13) {
                                    Run375259_pRPD_TS[5]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[5]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[5]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[5]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[5]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[5]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[5][8] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[5]->Fill(pRPD_ratio[5][8]);

                                    if (pRPD_ratio[5][8] > 1.7 && pRPD_ratio[5][8] < 2.5){
                                    pRPD_signal[5][8] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[5]->Fill(pRPD_signal[5][8]);
                                    }   
                                    if (channel[n] == 14) {
                                    Run375259_pRPD_TS[9]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[9]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[9]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[9]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[9]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[9]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[9][8] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[9]->Fill(pRPD_ratio[9][8]);
                                    
                                    if (pRPD_ratio[9][8] > 1.6 && pRPD_ratio[9][8] < 2.4) {
                                    pRPD_signal[9][8] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[9]->Fill(pRPD_signal[9][8]);
                                    }   
                                    if (channel[n] == 15) {
                                    Run375259_pRPD_TS[13]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[13]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[13]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[13]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[13]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[13]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[13][8] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[13]->Fill(pRPD_ratio[13][8]);

                                    if (pRPD_ratio[13][8] > 1.6 && pRPD_ratio[13][8] < 2.4) {
                                    pRPD_signal[13][8] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[13]->Fill(pRPD_signal[13][8]);
                                    }   
                                    if (channel[n] == 16) {
                                    Run375259_pRPD_TS[1]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[1]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[1]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[1]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[1]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[1]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[1][8] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[1]->Fill(pRPD_ratio[1][8]);

                                    if (pRPD_ratio[1][8] > 1.5 && pRPD_ratio[1][8] < 2.5) {
                                    pRPD_signal[1][8] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[1]->Fill(pRPD_signal[1][8]);
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
                            }  // end of channel loop
                            Run375259_pRPD_COM[8]->Fill(pRPD_signal_col[8], pRPD_signal_row[8]);
                            // fill projection
                            pos_rpd_xprojection[8]->Fill(pRPD_signal_col[8]);
                            // fill profile
                            Run375259_pRPD_prof[8]->Fill(0.0,pRPDX1[8]);
                            Run375259_pRPD_prof[8]->Fill(1.0,pRPDX2[8]);
                            Run375259_pRPD_prof[8]->Fill(2.0,pRPDX3[8]);
                            Run375259_pRPD_prof[8]->Fill(3.0,pRPDX4[8]);
                    } // end of sum cut
                } // end of hibin 
                if (hibin >=180 && hibin < 200 ){ 
                    if (pRPD_sum > 3200) {
                            for (int n = 0; n < 56; n++) {
                                if (zside[n] == 1 && section[n] == 4) {
                                    if (channel[n] == 1) {
                                    Run375259_pRPD_TS[10]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[10]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[10]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[10]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[10]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[10]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[10][9] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[10]->Fill(pRPD_ratio[10][9]);

                                    if (pRPD_ratio[10][9] > 1.5 && pRPD_ratio[10][9] < 2.0) {
                                    pRPD_signal[10][9] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[10]->Fill(pRPD_signal[10][9]);
                                    
                                    }
                                    if (channel[n] == 2) {
                                    Run375259_pRPD_TS[6]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[6]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[6]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[6]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[6]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[6]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[6][9] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[6]->Fill(pRPD_ratio[6][9]);
                                    
                                    if (pRPD_ratio[6][9] > 1.5 && pRPD_ratio[6][9] < 2.1) {
                                    pRPD_signal[6][9] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[6]->Fill(pRPD_signal[6][9]);
                                    
                                    } 
                                    if (channel[n] == 3) {
                                    Run375259_pRPD_TS[2]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[2]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[2]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[2]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[2]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[2]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[2][9] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[2]->Fill(pRPD_ratio[2][9]);
                                    
                                    if (pRPD_ratio[2][9] > 1.5 && pRPD_ratio[2][9] < 2.0) {
                                    pRPD_signal[2][9] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[2]->Fill(pRPD_signal[2][9]);
                                    
                                    }      
                                    if (channel[n] == 4) {
                                    Run375259_pRPD_TS[14]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[14]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[14]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[14]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[14]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[14]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[14][9] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[14]->Fill(pRPD_ratio[14][9]);

                                    if (pRPD_ratio[14][9] > 1.5 && pRPD_ratio[14][9] < 2.0) {
                                    pRPD_signal[14][9] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[14]->Fill(pRPD_signal[14][9]);
                                    
                                    }   
                                    if (channel[n] == 5) {
                                    Run375259_pRPD_TS[11]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[11]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[11]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[11]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[11]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[11]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[11][9] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[11]->Fill(pRPD_ratio[11][9]);
                                    
                                    if (pRPD_ratio[11][9] > 1.5 && pRPD_ratio[11][9] < 2.1) {
                                    pRPD_signal[11][9] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[11]->Fill(pRPD_signal[11][9]);
                                    
                                    }   
                                    if (channel[n] == 6) {
                                    Run375259_pRPD_TS[7]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[7]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[7]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[7]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[7]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[7]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[7][9] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[7]->Fill(pRPD_ratio[7][9]);
                                    
                                    if (pRPD_ratio[7][9] > 1.6 && pRPD_ratio[7][9] < 2.4) {
                                    pRPD_signal[7][9] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[7]->Fill(pRPD_signal[7][9]);
                                    
                                    }   
                                    if (channel[n] == 7) {
                                    Run375259_pRPD_TS[3]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[3]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[3]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[3]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[3]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[3]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[3][9] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[3]->Fill(pRPD_ratio[3][9]);
                                    
                                    if (pRPD_ratio[3][9] > 1.5 && pRPD_ratio[3][9] < 2.4) {
                                    pRPD_signal[3][9] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[3]->Fill(pRPD_signal[3][9]);
                                    
                                    }   
                                    if (channel[n] == 8) {
                                    Run375259_pRPD_TS[15]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[15]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[15]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[15]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[15]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[15]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[15][9] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[15]->Fill(pRPD_ratio[15][9]);

                                    if (pRPD_ratio[15][9] > 1.6 && pRPD_ratio[15][9] < 2.2) {
                                    pRPD_signal[15][9] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[15]->Fill(pRPD_signal[15][9]);
                                    }   
                                    if (channel[n] == 9) {
                                    Run375259_pRPD_TS[4]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[4]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[4]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[4]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[4]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[4]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[4][9] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[4]->Fill(pRPD_ratio[4][9]);

                                    if (pRPD_ratio[4][9] > 1.5 && pRPD_ratio[4][9] < 2.4 ) {
                                    pRPD_signal[4][9] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[4]->Fill(pRPD_signal[4][9]);
                                    }   
                                    if (channel[n] == 10) {
                                    Run375259_pRPD_TS[8]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[8]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[8]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[8]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[8]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[8]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[8][9] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[8]->Fill(pRPD_ratio[8][9]);

                                    if (pRPD_ratio[8][9] > 1.5 && pRPD_ratio[8][9] < 2.3) {
                                    pRPD_signal[8][9] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[8]->Fill(pRPD_signal[8][9]);
                                    }   
                                    if (channel[n] == 11) {
                                    Run375259_pRPD_TS[12]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[12]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[12]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[12]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[12]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[12]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[12][9] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[12]->Fill(pRPD_ratio[12][9]);

                                    if (pRPD_ratio[12][9] > 1.5 && pRPD_ratio[12][9] < 2.2){
                                    pRPD_signal[12][9] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[12]->Fill(pRPD_signal[12][9]);
                                    }   
                                    if (channel[n] == 12) {
                                    Run375259_pRPD_TS[0]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[0]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[0]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[0]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[0]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[0]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[0][9] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[0]->Fill(pRPD_ratio[0][9]);

                                    if (pRPD_ratio[0][9] > 1.5 && pRPD_ratio[0][9] < 2.3){
                                    pRPD_signal[0][9] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[0]->Fill(pRPD_signal[0][9]);
                                    }   
                                    if (channel[n] == 13) {
                                    Run375259_pRPD_TS[5]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[5]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[5]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[5]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[5]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[5]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[5][9] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[5]->Fill(pRPD_ratio[5][9]);

                                    if (pRPD_ratio[5][9] > 1.7 && pRPD_ratio[5][9] < 2.5){
                                    pRPD_signal[5][9] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[5]->Fill(pRPD_signal[5][9]);
                                    }   
                                    if (channel[n] == 14) {
                                    Run375259_pRPD_TS[9]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[9]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[9]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[9]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[9]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[9]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[9][9] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[9]->Fill(pRPD_ratio[9][9]);
                                    
                                    if (pRPD_ratio[9][9] > 1.6 && pRPD_ratio[9][9] < 2.4) {
                                    pRPD_signal[9][9] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[9]->Fill(pRPD_signal[9][9]);
                                    }   
                                    if (channel[n] == 15) {
                                    Run375259_pRPD_TS[13]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[13]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[13]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[13]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[13]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[13]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[13][9] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[13]->Fill(pRPD_ratio[13][9]);

                                    if (pRPD_ratio[13][9] > 1.6 && pRPD_ratio[13][9] < 2.4) {
                                    pRPD_signal[13][9] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[13]->Fill(pRPD_signal[13][9]);
                                    }   
                                    if (channel[n] == 16) {
                                    Run375259_pRPD_TS[1]->Fill(0.0,TS0[n]);
                                    Run375259_pRPD_TS[1]->Fill(1.0,TS1[n]);
                                    Run375259_pRPD_TS[1]->Fill(2.0,TS2[n]);
                                    Run375259_pRPD_TS[1]->Fill(3.0,TS3[n]);
                                    Run375259_pRPD_TS[1]->Fill(4.0,TS4[n]);
                                    Run375259_pRPD_TS[1]->Fill(5.0,TS5[n]);

                                    pRPD_ratio[1][9] = TS2[n] / TS3[n];
                                    Run375259_pRPD_TSratio[1]->Fill(pRPD_ratio[1][9]);

                                    if (pRPD_ratio[1][9] > 1.5 && pRPD_ratio[1][9] < 2.5) {
                                    pRPD_signal[1][9] = TS2[n] + TS3[n];
                                    }
                                    Run375259_pRPD_fC[1]->Fill(pRPD_signal[1][9]);
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
                            }  // end of channel loop
                            Run375259_pRPD_COM[9]->Fill(pRPD_signal_col[9], pRPD_signal_row[9]);
                            // fill projection
                            pos_rpd_xprojection[9]->Fill(pRPD_signal_col[9]);
                            // fill profile
                            Run375259_pRPD_prof[9]->Fill(0.0,pRPDX1[9]);
                            Run375259_pRPD_prof[9]->Fill(1.0,pRPDX2[9]);
                            Run375259_pRPD_prof[9]->Fill(2.0,pRPDX3[9]);
                            Run375259_pRPD_prof[9]->Fill(3.0,pRPDX4[9]);
                    } // end of sum cut
                } // end of hibin 
            } // end of event loop
    gStyle->SetOptFit();

    Run375259_pRPD_TSratio[0]->Fit("gaus","","",1,3);
    Run375259_pRPD_TSratio[1]->Fit("gaus","","",1,3);
    Run375259_pRPD_TSratio[2]->Fit("gaus","","",1,3);
    Run375259_pRPD_TSratio[3]->Fit("gaus","","",1,3);
    Run375259_pRPD_TSratio[4]->Fit("gaus","","",1,3);
    Run375259_pRPD_TSratio[5]->Fit("gaus","","",1,3);
    Run375259_pRPD_TSratio[6]->Fit("gaus","","",1,3);
    Run375259_pRPD_TSratio[7]->Fit("gaus","","",1,3);
    Run375259_pRPD_TSratio[8]->Fit("gaus","","",1,3);
    Run375259_pRPD_TSratio[9]->Fit("gaus","","",1,3);
    Run375259_pRPD_TSratio[10]->Fit("gaus","","",1,3);
    Run375259_pRPD_TSratio[11]->Fit("gaus","","",1,3);
    Run375259_pRPD_TSratio[12]->Fit("gaus","","",1,3);
    Run375259_pRPD_TSratio[13]->Fit("gaus","","",1,3);
    Run375259_pRPD_TSratio[14]->Fit("gaus","","",1,3);
    Run375259_pRPD_TSratio[15]->Fit("gaus","","",1,3);

    Run375259_pRPD_TS[0]->SetXTitle("Time Slice"); 
    Run375259_pRPD_TS[0]->SetYTitle("Charge (fC)"); 

    Run375259_pRPD_TS[1]->SetXTitle("Time Slice"); 
    Run375259_pRPD_TS[1]->SetYTitle("Charge (fC)");      

    Run375259_pRPD_TS[2]->SetXTitle("Time Slice"); 
    Run375259_pRPD_TS[2]->SetYTitle("Charge (fC)");

    Run375259_pRPD_TS[3]->SetXTitle("Time Slice"); 
    Run375259_pRPD_TS[3]->SetYTitle("Charge (fC)");

    Run375259_pRPD_TS[4]->SetXTitle("Time Slice"); 
    Run375259_pRPD_TS[4]->SetYTitle("Charge (fC)");

    Run375259_pRPD_TS[5]->SetXTitle("Time Slice"); 
    Run375259_pRPD_TS[5]->SetYTitle("Charge (fC)");

    Run375259_pRPD_TS[6]->SetXTitle("Time Slice"); 
    Run375259_pRPD_TS[6]->SetYTitle("Charge (fC)");

    Run375259_pRPD_TS[7]->SetXTitle("Time Slice"); 
    Run375259_pRPD_TS[7]->SetYTitle("Charge (fC)");

    Run375259_pRPD_TS[8]->SetXTitle("Time Slice"); 
    Run375259_pRPD_TS[8]->SetYTitle("Charge (fC)");

    Run375259_pRPD_TS[9]->SetXTitle("Time Slice"); 
    Run375259_pRPD_TS[9]->SetYTitle("Charge (fC)");

    Run375259_pRPD_TS[10]->SetXTitle("Time Slice"); 
    Run375259_pRPD_TS[10]->SetYTitle("Charge (fC)");

    Run375259_pRPD_TS[11]->SetXTitle("Time Slice"); 
    Run375259_pRPD_TS[11]->SetYTitle("Charge (fC)");

    Run375259_pRPD_TS[12]->SetXTitle("Time Slice"); 
    Run375259_pRPD_TS[12]->SetYTitle("Charge (fC)");

    Run375259_pRPD_TS[13]->SetXTitle("Time Slice"); 
    Run375259_pRPD_TS[13]->SetYTitle("Charge (fC)");

    Run375259_pRPD_TS[14]->SetXTitle("Time Slice"); 
    Run375259_pRPD_TS[14]->SetYTitle("Charge (fC)");

    Run375259_pRPD_TS[15]->SetXTitle("Time Slice"); 
    Run375259_pRPD_TS[15]->SetYTitle("Charge (fC)");

    TCanvas *c1 = new TCanvas();
    c1->Divide(4,4);
    c1->cd(1);
    Run375259_pRPD_TS[0]->Draw("hist e");
    c1->cd(2);
    Run375259_pRPD_TS[1]->Draw("hist e");
    c1->cd(3);
    Run375259_pRPD_TS[2]->Draw("hist e");
    c1->cd(4);
    Run375259_pRPD_TS[3]->Draw("hist e");
    c1->cd(5);
    Run375259_pRPD_TS[4]->Draw("hist e");
    c1->cd(6);
    Run375259_pRPD_TS[5]->Draw("hist e");
    c1->cd(7);
    Run375259_pRPD_TS[6]->Draw("hist e");
    c1->cd(8);
    Run375259_pRPD_TS[7]->Draw("hist e");
    c1->cd(9);
    Run375259_pRPD_TS[8]->Draw("hist e");
    c1->cd(10);
    Run375259_pRPD_TS[9]->Draw("hist e");
    c1->cd(11);
    Run375259_pRPD_TS[10]->Draw("hist e");
    c1->cd(12);
    Run375259_pRPD_TS[11]->Draw("hist e");
    c1->cd(13);
    Run375259_pRPD_TS[12]->Draw("hist e");
    c1->cd(14);
    Run375259_pRPD_TS[13]->Draw("hist e");
    c1->cd(15);
    Run375259_pRPD_TS[14]->Draw("hist e");
    c1->cd(16);
    Run375259_pRPD_TS[15]->Draw("hist e");

    Run375259_pRPD_TSratio[0]->SetXTitle("Ratio of TS2 to TS3"); 
    Run375259_pRPD_TSratio[0]->SetYTitle("Counts"); 

    Run375259_pRPD_TSratio[1]->SetXTitle("Ratio of TS2 to TS3"); 
    Run375259_pRPD_TSratio[1]->SetYTitle("Counts"); 

    Run375259_pRPD_TSratio[2]->SetXTitle("Ratio of TS2 to TS3"); 
    Run375259_pRPD_TSratio[2]->SetYTitle("Counts"); 

    Run375259_pRPD_TSratio[3]->SetXTitle("Ratio of TS2 to TS3"); 
    Run375259_pRPD_TSratio[3]->SetYTitle("Counts"); 

    Run375259_pRPD_TSratio[4]->SetXTitle("Ratio of TS2 to TS3"); 
    Run375259_pRPD_TSratio[4]->SetYTitle("Counts"); 

    Run375259_pRPD_TSratio[5]->SetXTitle("Ratio of TS2 to TS3"); 
    Run375259_pRPD_TSratio[5]->SetYTitle("Counts"); 

    Run375259_pRPD_TSratio[6]->SetXTitle("Ratio of TS2 to TS3"); 
    Run375259_pRPD_TSratio[6]->SetYTitle("Counts"); 

    Run375259_pRPD_TSratio[7]->SetXTitle("Ratio of TS2 to TS3"); 
    Run375259_pRPD_TSratio[7]->SetYTitle("Counts"); 

    Run375259_pRPD_TSratio[8]->SetXTitle("Ratio of TS2 to TS3"); 
    Run375259_pRPD_TSratio[8]->SetYTitle("Counts"); 

    Run375259_pRPD_TSratio[9]->SetXTitle("Ratio of TS2 to TS3"); 
    Run375259_pRPD_TSratio[9]->SetYTitle("Counts"); 

    Run375259_pRPD_TSratio[10]->SetXTitle("Ratio of TS2 to TS3"); 
    Run375259_pRPD_TSratio[10]->SetYTitle("Counts"); 

    Run375259_pRPD_TSratio[11]->SetXTitle("Ratio of TS2 to TS3"); 
    Run375259_pRPD_TSratio[11]->SetYTitle("Counts"); 

    Run375259_pRPD_TSratio[12]->SetXTitle("Ratio of TS2 to TS3"); 
    Run375259_pRPD_TSratio[12]->SetYTitle("Counts"); 

    Run375259_pRPD_TSratio[13]->SetXTitle("Ratio of TS2 to TS3"); 
    Run375259_pRPD_TSratio[13]->SetYTitle("Counts"); 

    Run375259_pRPD_TSratio[14]->SetXTitle("Ratio of TS2 to TS3"); 
    Run375259_pRPD_TSratio[14]->SetYTitle("Counts"); 

    Run375259_pRPD_TSratio[15]->SetXTitle("Ratio of TS2 to TS3"); 
    Run375259_pRPD_TSratio[15]->SetYTitle("Counts"); 

    TCanvas *c2 = new TCanvas();
    c2->Divide(4,4);
    c2->cd(1);
    Run375259_pRPD_TSratio[0]->Draw();

    c2->cd(2);
    Run375259_pRPD_TSratio[1]->Draw();

    c2->cd(3);
    Run375259_pRPD_TSratio[2]->Draw();

    c2->cd(4);
    Run375259_pRPD_TSratio[3]->Draw();

    c2->cd(5);
    Run375259_pRPD_TSratio[4]->Draw();

    c2->cd(6);
    Run375259_pRPD_TSratio[5]->Draw();

    c2->cd(7);
    Run375259_pRPD_TSratio[6]->Draw();

    c2->cd(8);
    Run375259_pRPD_TSratio[7]->Draw();

    c2->cd(9);
    Run375259_pRPD_TSratio[8]->Draw();

    c2->cd(10);
    Run375259_pRPD_TSratio[9]->Draw();

    c2->cd(11);
    Run375259_pRPD_TSratio[10]->Draw();

    c2->cd(12);
    Run375259_pRPD_TSratio[11]->Draw();

    c2->cd(13);
    Run375259_pRPD_TSratio[12]->Draw();

    c2->cd(14);
    Run375259_pRPD_TSratio[13]->Draw();

    c2->cd(15);
    Run375259_pRPD_TSratio[14]->Draw();

    c2->cd(16);
    Run375259_pRPD_TSratio[15]->Draw();

    Run375259_pRPD_fC[0]->SetXTitle("fC"); 
    Run375259_pRPD_fC[0]->SetYTitle("Counts"); 

    Run375259_pRPD_fC[1]->SetXTitle("fC"); 
    Run375259_pRPD_fC[1]->SetYTitle("Counts");

    Run375259_pRPD_fC[2]->SetXTitle("fC"); 
    Run375259_pRPD_fC[2]->SetYTitle("Counts");

    Run375259_pRPD_fC[3]->SetXTitle("fC"); 
    Run375259_pRPD_fC[3]->SetYTitle("Counts");

    Run375259_pRPD_fC[4]->SetXTitle("fC"); 
    Run375259_pRPD_fC[4]->SetYTitle("Counts");

    Run375259_pRPD_fC[5]->SetXTitle("fC"); 
    Run375259_pRPD_fC[5]->SetYTitle("Counts");

    Run375259_pRPD_fC[6]->SetXTitle("fC"); 
    Run375259_pRPD_fC[6]->SetYTitle("Counts");

    Run375259_pRPD_fC[7]->SetXTitle("fC"); 
    Run375259_pRPD_fC[7]->SetYTitle("Counts");

    Run375259_pRPD_fC[8]->SetXTitle("fC"); 
    Run375259_pRPD_fC[8]->SetYTitle("Counts");

    Run375259_pRPD_fC[9]->SetXTitle("fC"); 
    Run375259_pRPD_fC[9]->SetYTitle("Counts");

    Run375259_pRPD_fC[10]->SetXTitle("fC"); 
    Run375259_pRPD_fC[10]->SetYTitle("Counts");

    Run375259_pRPD_fC[11]->SetXTitle("fC"); 
    Run375259_pRPD_fC[11]->SetYTitle("Counts");

    Run375259_pRPD_fC[12]->SetXTitle("fC"); 
    Run375259_pRPD_fC[12]->SetYTitle("Counts");

    Run375259_pRPD_fC[13]->SetXTitle("fC"); 
    Run375259_pRPD_fC[13]->SetYTitle("Counts");

    Run375259_pRPD_fC[14]->SetXTitle("fC"); 
    Run375259_pRPD_fC[14]->SetYTitle("Counts");

    Run375259_pRPD_fC[15]->SetXTitle("fC"); 
    Run375259_pRPD_fC[15]->SetYTitle("Counts");

    TCanvas *c3 = new TCanvas();
    c3->Divide(4,4);
    c3->cd(1);
    Run375259_pRPD_fC[0]->Draw();

    c3->cd(2);
    Run375259_pRPD_fC[1]->Draw();

    c3->cd(3);
    Run375259_pRPD_fC[2]->Draw();

    c3->cd(4);
    Run375259_pRPD_fC[3]->Draw();

    c3->cd(5);
    Run375259_pRPD_fC[4]->Draw();

    c3->cd(6);
    Run375259_pRPD_fC[5]->Draw();

    c3->cd(7);
    Run375259_pRPD_fC[6]->Draw();

    c3->cd(8);
    Run375259_pRPD_fC[7]->Draw();

    c3->cd(9);
    Run375259_pRPD_fC[8]->Draw();

    c3->cd(10);
    Run375259_pRPD_fC[9]->Draw();

    c3->cd(11);
    Run375259_pRPD_fC[10]->Draw();

    c3->cd(12);
    Run375259_pRPD_fC[11]->Draw();

    c3->cd(13);
    Run375259_pRPD_fC[12]->Draw();

    c3->cd(14);
    Run375259_pRPD_fC[13]->Draw();

    c3->cd(15);
    Run375259_pRPD_fC[14]->Draw();

    c3->cd(16);
    Run375259_pRPD_fC[15]->Draw();

    Run375259_pRPD_COM[0]->SetXTitle("X Position (cm)");
    Run375259_pRPD_COM[0]->SetYTitle("Y Position (cm)");

    Run375259_pRPD_COM[1]->SetXTitle("X Position (cm)");
    Run375259_pRPD_COM[1]->SetYTitle("Y Position (cm)");

    Run375259_pRPD_COM[2]->SetXTitle("X Position (cm)");
    Run375259_pRPD_COM[2]->SetYTitle("Y Position (cm)");

    Run375259_pRPD_COM[3]->SetXTitle("X Position (cm)");
    Run375259_pRPD_COM[3]->SetYTitle("Y Position (cm)");

    Run375259_pRPD_COM[4]->SetXTitle("X Position (cm)");
    Run375259_pRPD_COM[4]->SetYTitle("Y Position (cm)");

    Run375259_pRPD_COM[5]->SetXTitle("X Position (cm)");
    Run375259_pRPD_COM[5]->SetYTitle("Y Position (cm)");

    Run375259_pRPD_COM[6]->SetXTitle("X Position (cm)");
    Run375259_pRPD_COM[6]->SetYTitle("Y Position (cm)");

    Run375259_pRPD_COM[7]->SetXTitle("X Position (cm)");
    Run375259_pRPD_COM[7]->SetYTitle("Y Position (cm)");

    Run375259_pRPD_COM[8]->SetXTitle("X Position (cm)");
    Run375259_pRPD_COM[8]->SetYTitle("Y Position (cm)");

    Run375259_pRPD_COM[9]->SetXTitle("X Position (cm)");
    Run375259_pRPD_COM[9]->SetYTitle("Y Position (cm)");

    Run375259_pRPD_COM[10]->SetXTitle("X Position (cm)");
    Run375259_pRPD_COM[10]->SetYTitle("Y Position (cm)");    

    TCanvas *c4 = new TCanvas();
    c4->Divide(5,2);
    c4->cd(1);
    Run375259_pRPD_COM[0]->Draw("colz");

    c4->cd(2);
    Run375259_pRPD_COM[1]->Draw("colz");

    c4->cd(3);
    Run375259_pRPD_COM[2]->Draw("colz");

    c4->cd(4);
    Run375259_pRPD_COM[3]->Draw("colz");

    c4->cd(5);
    Run375259_pRPD_COM[4]->Draw("colz");

    c4->cd(6);
    Run375259_pRPD_COM[5]->Draw("colz");

    c4->cd(7);
    Run375259_pRPD_COM[6]->Draw("colz");

    c4->cd(8);
    Run375259_pRPD_COM[7]->Draw("colz");

    c4->cd(9);
    Run375259_pRPD_COM[8]->Draw("colz");

    c4->cd(10);
    Run375259_pRPD_COM[9]->Draw("colz");

    
    pos_rpd_xprojection[0]->SetXTitle("X Position (cm)");
    pos_rpd_xprojection[0]->SetYTitle("Counts");
    pos_rpd_xprojection[0]->SetLineColor(kRed);

    pos_rpd_xprojection[1]->SetXTitle("X Position (cm)");
    pos_rpd_xprojection[1]->SetYTitle("Counts");
    pos_rpd_xprojection[1]->SetLineColor(kBlack);

    pos_rpd_xprojection[2]->SetXTitle("X Position (cm)");
    pos_rpd_xprojection[2]->SetYTitle("Counts");
    pos_rpd_xprojection[2]->SetLineColor(kBlue);

    pos_rpd_xprojection[3]->SetXTitle("X Position (cm)");
    pos_rpd_xprojection[3]->SetYTitle("Counts");
    pos_rpd_xprojection[3]->SetLineColor(kGreen);

    pos_rpd_xprojection[4]->SetXTitle("X Position (cm)");
    pos_rpd_xprojection[4]->SetYTitle("Counts");
    pos_rpd_xprojection[4]->SetLineColor(kCyan);

    pos_rpd_xprojection[5]->SetXTitle("X Position (cm)");
    pos_rpd_xprojection[5]->SetYTitle("Counts");
    pos_rpd_xprojection[5]->SetLineColor(kYellow);

    pos_rpd_xprojection[6]->SetXTitle("X Position (cm)");
    pos_rpd_xprojection[6]->SetYTitle("Counts");
    pos_rpd_xprojection[6]->SetLineColor(kOrange);

    pos_rpd_xprojection[7]->SetXTitle("X Position (cm)");
    pos_rpd_xprojection[7]->SetYTitle("Counts");
    pos_rpd_xprojection[7]->SetLineColor(kViolet);

    pos_rpd_xprojection[8]->SetXTitle("X Position (cm)");
    pos_rpd_xprojection[8]->SetYTitle("Counts");
    pos_rpd_xprojection[8]->SetLineColor(kRainBow);

    pos_rpd_xprojection[9]->SetXTitle("X Position (cm)");
    pos_rpd_xprojection[9]->SetYTitle("Counts");
    pos_rpd_xprojection[9]->SetLineColor(kGray);
    
    TCanvas *c5 = new TCanvas();
    pRPD_stack->Add(pos_rpd_xprojection[0]);
    pRPD_stack->Add(pos_rpd_xprojection[1]);
    pRPD_stack->Add(pos_rpd_xprojection[2]);
    pRPD_stack->Add(pos_rpd_xprojection[3]);
    pRPD_stack->Add(pos_rpd_xprojection[4]);
    pRPD_stack->Add(pos_rpd_xprojection[5]);
    pRPD_stack->Add(pos_rpd_xprojection[6]);
    pRPD_stack->Add(pos_rpd_xprojection[7]);
    pRPD_stack->Add(pos_rpd_xprojection[8]);
    pRPD_stack->Add(pos_rpd_xprojection[9]);

    auto legend = new TLegend(0.7,0.7,0.9,0.9);
    legend->AddEntry(pos_rpd_xprojection[0], "0-10 Centrality", "l");
    legend->AddEntry(pos_rpd_xprojection[1], "10-20 Centrality", "l");
    legend->AddEntry(pos_rpd_xprojection[2], "20-30 Centrality", "l");
    legend->AddEntry(pos_rpd_xprojection[3], "30-40 Centrality", "l");
    legend->AddEntry(pos_rpd_xprojection[4], "40-50 Centrality", "l");
    legend->AddEntry(pos_rpd_xprojection[5], "50-60 Centrality", "l");
    legend->AddEntry(pos_rpd_xprojection[6], "60-70 Centrality", "l");
    legend->AddEntry(pos_rpd_xprojection[7], "70-80 Centrality", "l");
    legend->AddEntry(pos_rpd_xprojection[8], "80-90 Centrality", "l");
    legend->AddEntry(pos_rpd_xprojection[9], "90-100 Centrality", "l");
    
    pRPD_stack->Draw("nostack");
    legend->Draw();

    pRPD_stack->GetXaxis()->SetTitle("X Position (cm)");
    pRPD_stack->GetYaxis()->SetTitle("counts");

    TCanvas *c6 = new TCanvas();
    c6->Divide(5,2);
    Run375259_pRPD_prof[0]->SetXTitle("X Position");
    Run375259_pRPD_prof[0]->SetYTitle("Avg Signal");

    Run375259_pRPD_prof[1]->SetXTitle("X Position");
    Run375259_pRPD_prof[1]->SetYTitle("Avg Signal");

    Run375259_pRPD_prof[2]->SetXTitle("X Position");
    Run375259_pRPD_prof[2]->SetYTitle("Avg Signal");

    Run375259_pRPD_prof[3]->SetXTitle("X Position");
    Run375259_pRPD_prof[3]->SetYTitle("Avg Signal");

    Run375259_pRPD_prof[4]->SetXTitle("X Position");
    Run375259_pRPD_prof[4]->SetYTitle("Avg Signal");

    Run375259_pRPD_prof[5]->SetXTitle("X Position");
    Run375259_pRPD_prof[5]->SetYTitle("Avg Signal");

    Run375259_pRPD_prof[6]->SetXTitle("X Position");
    Run375259_pRPD_prof[6]->SetYTitle("Avg Signal");

    Run375259_pRPD_prof[7]->SetXTitle("X Position");
    Run375259_pRPD_prof[7]->SetYTitle("Avg Signal");

    Run375259_pRPD_prof[8]->SetXTitle("X Position");
    Run375259_pRPD_prof[8]->SetYTitle("Avg Signal");

    Run375259_pRPD_prof[9]->SetXTitle("X Position");
    Run375259_pRPD_prof[9]->SetYTitle("Avg Signal");

    c6->cd(1);
    Run375259_pRPD_prof[0]->Draw("hist e");

    c6->cd(2);
    Run375259_pRPD_prof[1]->Draw("hist e");

    c6->cd(3);
    Run375259_pRPD_prof[2]->Draw("hist e");

    c6->cd(4);
    Run375259_pRPD_prof[3]->Draw("hist e");

    c6->cd(5);
    Run375259_pRPD_prof[4]->Draw("hist e");

    c6->cd(6);
    Run375259_pRPD_prof[5]->Draw("hist e");

    c6->cd(7);
    Run375259_pRPD_prof[6]->Draw("hist e");

    c6->cd(8);
    Run375259_pRPD_prof[7]->Draw("hist e");

    c6->cd(9);
    Run375259_pRPD_prof[8]->Draw("hist e");

    c6->cd(10);
    Run375259_pRPD_prof[9]->Draw("hist e");

}

