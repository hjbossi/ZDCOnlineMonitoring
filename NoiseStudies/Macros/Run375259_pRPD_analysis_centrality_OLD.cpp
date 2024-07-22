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

void Run375259_pRPD_analysis_centrality()
{
      //Make TChain
      TChain *zdcchain = new TChain();
      TChain *hichain = new TChain();
      for (int i = 1 ; i < 135 ; i++){
      if(i == 116) continue;
      zdcchain->Add(Form("/store/data/Runs_2023/375259/240112_203159/0000/HiForestMiniAOD_%i.root/zdcanalyzer/zdcdigi", i));
      hichain->Add(Form("/store/data/Runs_2023/375259/240112_203159/0000/HiForestMiniAOD_%i.root/hiEvtAnalyzer/HiTree", i));
      }

      zdcchain->AddFriend(hichain);
    // Mapping for channels to blocks is same for both pos and neg RPD
    /*Channel to block mapping 
    RPD Blocks: 
    0, 1, 2, 3,
    4, 5, 6, 7,
    8, 9, 10, 11,
    12, 13, 14, 15 ...or is it 1 to 16...

    Channel:
    11, 15, 2, 6,
    8, 12, 1, 5,
    9, 13, 0, 4
    10, 14, 3, 7 ... or do i subtract by 1...
    */
  /* access centrality 
    use hievtanalyzer in addition to zdc analyzer
    HiTree->Print()
    hiBin of 100 is 50, divide bin by 2 to get centrality
    make a chain, add 
  */
    
    // Defining blocks to be used for later. 
    // Start at 0 to keep things consistent in cpp
    double pos_RPD_ratio_block0 = 0;
    double pos_RPD_ratio_block1 = 0;
    double pos_RPD_ratio_block2 = 0;
    double pos_RPD_ratio_block3 = 0;
    double pos_RPD_ratio_block4 = 0;
    double pos_RPD_ratio_block5 = 0;
    double pos_RPD_ratio_block6 = 0;
    double pos_RPD_ratio_block7 = 0;
    double pos_RPD_ratio_block8 = 0;
    double pos_RPD_ratio_block9 = 0;
    double pos_RPD_ratio_block10 = 0;
    double pos_RPD_ratio_block11 = 0;
    double pos_RPD_ratio_block12 = 0;
    double pos_RPD_ratio_block13 = 0;
    double pos_RPD_ratio_block14 = 0;
    double pos_RPD_ratio_block15 = 0;

    double pRPD_block0_signal = 0;
    double pRPD_block1_signal = 0;
    double pRPD_block2_signal = 0;
    double pRPD_block3_signal = 0;
    double pRPD_block4_signal = 0;
    double pRPD_block5_signal = 0;
    double pRPD_block6_signal = 0;
    double pRPD_block7_signal = 0;
    double pRPD_block8_signal = 0;
    double pRPD_block9_signal = 0;
    double pRPD_block10_signal = 0;
    double pRPD_block11_signal = 0;
    double pRPD_block12_signal = 0;
    double pRPD_block13_signal = 0;
    double pRPD_block14_signal = 0;
    double pRPD_block15_signal = 0;

    double pEM1_ratio = 0;
    double pEM2_ratio = 0;
    double pEM3_ratio = 0;
    double pEM4_ratio = 0;
    double pEM5_ratio = 0;

    double pEM1_signal = 0;
    double pEM2_signal = 0;
    double pEM3_signal = 0;
    double pEM4_signal = 0;
    double pEM5_signal = 0;

    double pHAD1_signal = 0;
    double pHAD2_signal = 0;
    double pHAD3_signal = 0;
    double pHAD4_signal = 0;

    double pHAD1_ratio = 0;
    double pHAD2_ratio = 0;
    double pHAD3_ratio = 0;
    double pHAD4_ratio = 0;

    double pRPDX1 = 0;
    double pRPDX2 = 0;
    double pRPDX3 = 0;
    double pRPDX4 = 0;

    double pRPDY1 = 0;
    double pRPDY2 = 0;
    double pRPDY3 = 0;
    double pRPDY4 = 0;

    double pRPD_Total_Signal = 0;  

    double pRPD_signal_row = 0;
    double pRPD_signal_col = 0;

    int hibin = 0;

    // Histograms for time slices for each rpd block
    TH1F *pos_rpd_ts_block0 = new TH1F("","Block 0 Pos RPD",6,0,6); // channel 11 is for this block
    TH1F *pos_rpd_ts_block1 = new TH1F("","Block 1 Pos RPD",6,0,6); // channel 15 is for this block
    TH1F *pos_rpd_ts_block2 = new TH1F("","Block 2 Pos RPD",6,0,6); // channel 2 is for this block
    TH1F *pos_rpd_ts_block3 = new TH1F("","Block 3 Pos RPD",6,0,6); // channel 6 is for this block
    TH1F *pos_rpd_ts_block4 = new TH1F("","Block 4 Pos RPD",6,0,6); // channel 8 is for this block
    TH1F *pos_rpd_ts_block5 = new TH1F("","Block 5 Pos RPD",6,0,6); // channel 12 is for this block
    TH1F *pos_rpd_ts_block6 = new TH1F("","Block 6 Pos RPD",6,0,6); // channel 1 is for this block
    TH1F *pos_rpd_ts_block7 = new TH1F("","Block 7 Pos RPD",6,0,6); // channel 5 is for this block
    TH1F *pos_rpd_ts_block8 = new TH1F("","Block 8 Pos RPD",6,0,6); // channel 9 is for this block
    TH1F *pos_rpd_ts_block9 = new TH1F("","Block 9 Pos RPD",6,0,6); // channel 13 is for this block
    TH1F *pos_rpd_ts_block10 = new TH1F("","Block 10 Pos RPD",6,0,6);// channel 0 is for this block
    TH1F *pos_rpd_ts_block11 = new TH1F("","Block 11 Pos RPD",6,0,6);// channel 4 is for this block
    TH1F *pos_rpd_ts_block12 = new TH1F("","Block 12 Pos RPD",6,0,6);// channel 10 is for this block
    TH1F *pos_rpd_ts_block13 = new TH1F("","Block 13 Pos RPD",6,0,6);// channel 14 is for this block
    TH1F *pos_rpd_ts_block14 = new TH1F("","Block 14 Pos RPD",6,0,6);// channel 3 is for this block
    TH1F *pos_rpd_ts_block15 = new TH1F("","Block 15 Pos RPD",6,0,6);// channel 7 is for this block 

    // Histograms for ratios of time slices for each block.
    // We want ratio of time slice 2 to time slice 
    TH1F *pRPD_ratio_TS_2to3_block0 = new TH1F("","Pos RPD Block 0 Ratio TS 2 to 3",75,0,5);
    TH1F *pRPD_ratio_TS_2to3_block1 = new TH1F("","Pos RPD Block 1 Ratio TS 2 to 3",75,0,5);
    TH1F *pRPD_ratio_TS_2to3_block2 = new TH1F("","Pos RPD Block 2 Ratio TS 2 to 3",75,0,5);
    TH1F *pRPD_ratio_TS_2to3_block3 = new TH1F("","Pos RPD Block 3 Ratio TS 2 to 3",75,0,5);
    TH1F *pRPD_ratio_TS_2to3_block4 = new TH1F("","Pos RPD Block 4 Ratio TS 2 to 3",75,0,5);
    TH1F *pRPD_ratio_TS_2to3_block5 = new TH1F("","Pos RPD Block 5 Ratio TS 2 to 3",75,0,5);
    TH1F *pRPD_ratio_TS_2to3_block6 = new TH1F("","Pos RPD Block 6 Ratio TS 2 to 3",75,0,5);
    TH1F *pRPD_ratio_TS_2to3_block7 = new TH1F("","Pos RPD Block 7 Ratio TS 2 to 3",75,0,5);
    TH1F *pRPD_ratio_TS_2to3_block8 = new TH1F("","Pos RPD Block 8 Ratio TS 2 to 3",75,0,5);
    TH1F *pRPD_ratio_TS_2to3_block9 = new TH1F("","Pos RPD Block 9 Ratio TS 2 to 3",75,0,5);
    TH1F *pRPD_ratio_TS_2to3_block10 = new TH1F("","Pos RPD Block 10 Ratio TS 2 to 3",75,0,5);
    TH1F *pRPD_ratio_TS_2to3_block11 = new TH1F("","Pos RPD Block 11 Ratio TS 2 to 3",75,0,5);
    TH1F *pRPD_ratio_TS_2to3_block12 = new TH1F("","Pos RPD Block 12 Ratio TS 2 to 3",75,0,5);
    TH1F *pRPD_ratio_TS_2to3_block13 = new TH1F("","Pos RPD Block 13 Ratio TS 2 to 3",75,0,5);
    TH1F *pRPD_ratio_TS_2to3_block14 = new TH1F("","Pos RPD Block 14 Ratio TS 2 to 3",75,0,5);
    TH1F *pRPD_ratio_TS_2to3_block15 = new TH1F("","Pos RPD Block 15 Ratio TS 2 to 3",75,0,5);

    // Plot fC distributions for TS 2to3 ratio of 1 to 2.5, BUT IT DEPENDS ON THE BLOCK
    // I just need to remove the low tail. 
    TH1F *pRPD_block0_fC = new TH1F("","Pos RPD Block 0 fC",100,1000,400000);
    TH1F *pRPD_block1_fC = new TH1F("","Pos RPD Block 1 fC",100,1000,400000);
    TH1F *pRPD_block2_fC = new TH1F("","Pos RPD Block 2 fC",100,1000,400000);
    TH1F *pRPD_block3_fC = new TH1F("","Pos RPD Block 3 fC",100,1000,400000);
    TH1F *pRPD_block4_fC = new TH1F("","Pos RPD Block 4 fC",100,1000,400000);
    TH1F *pRPD_block5_fC = new TH1F("","Pos RPD Block 5 fC",100,1000,400000);
    TH1F *pRPD_block6_fC = new TH1F("","Pos RPD Block 6 fC",100,1000,400000);
    TH1F *pRPD_block7_fC = new TH1F("","Pos RPD Block 7 fC",100,1000,400000);
    TH1F *pRPD_block8_fC = new TH1F("","Pos RPD Block 8 fC",100,1000,400000);
    TH1F *pRPD_block9_fC = new TH1F("","Pos RPD Block 9 fC",100,1000,400000);
    TH1F *pRPD_block10_fC = new TH1F("","Pos RPD Block 10 fC",100,1000,400000);
    TH1F *pRPD_block11_fC = new TH1F("","Pos RPD Block 11 fC",100,1000,400000);
    TH1F *pRPD_block12_fC = new TH1F("","Pos RPD Block 12 fC",100,1000,400000);
    TH1F *pRPD_block13_fC = new TH1F("","Pos RPD Block 13 fC",100,1000,400000);
    TH1F *pRPD_block14_fC = new TH1F("","Pos RPD Block 14 fC",100,1000,400000);
    TH1F *pRPD_block15_fC = new TH1F("","Pos RPD Block 15 fC",100,1000,400000);

    //2D Histogram for center of mass plot
    TH2F  *pRPD_COM1 = new TH2F("","Run 375259, pRPD COM, 0 - 10% Centrality",200,-4,4,200,-4,4);
    TH2F  *pRPD_COM2 = new TH2F("","Run 375259, pRPD COM, 10 - 20% Centrality",200,-4,4,200,-4,4);
    TH2F  *pRPD_COM3 = new TH2F("","Run 375259, pRPD COM, 20 - 30% Centrality",200,-4,4,200,-4,4);
    TH2F  *pRPD_COM4 = new TH2F("","Run 375259, pRPD COM, 30 - 40% Centrality",200,-4,4,200,-4,4);
    TH2F  *pRPD_COM5 = new TH2F("","Run 375259, pRPD COM, 40 - 50% Centrality",200,-4,4,200,-4,4);
    TH2F  *pRPD_COM6 = new TH2F("","Run 375259, pRPD COM, 50 - 60% Centrality",200,-4,4,200,-4,4);
    TH2F  *pRPD_COM7 = new TH2F("","Run 375259, pRPD COM, 60 - 70% Centrality",200,-4,4,200,-4,4);
    TH2F  *pRPD_COM8 = new TH2F("","Run 375259, pRPD COM, 70 - 80% Centrality",200,-4,4,200,-4,4);
    TH2F  *pRPD_COM9 = new TH2F("","Run 375259, pRPD COM, 80 - 90% Centrality",200,-4,4,200,-4,4);
    TH2F  *pRPD_COM10 = new TH2F("","Run 375259, pRPD COM, 90 - 100% Centrality",200,-4,4,200,-4,4);                  

    //2D Histogram for block diagram (heat map)
    TH2 *pRPD_blockdiagram = new TH2D("", "Run 375259, All Cent, Pos RPD Block Diagram",4,0,4,4,0,4);  

    int hibin = 0;
    int zside[56];
    int section[56];
    int channel[56];

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
    for (int i = 0; i < NumofEvents; i++) {                    //Number of events we will run through.
		  zdcchain->GetEntry(i);  
      hichain->GetEntry(i);                                    
                      
      //Number timeslices
      const int NTS = 6; 

	    //Leaves in ZDC
	    TLeaf* zsideLeaf = (TLeaf*)zdcchain->GetLeaf("zside");
	    TLeaf* sectionLeaf = (TLeaf*)zdcchain->GetLeaf("section");
      TLeaf* channelLeaf = (TLeaf*)zdcchain->GetLeaf("channel");
      TLeaf* fCleaf[NTS];
      // Get data from leaves
      for (int iTS = 0; iTS < NTS; iTS++) {
		    fCleaf[iTS] = (TLeaf*)zdcchain->GetLeaf(Form("chargefCTs%d", iTS));
	    }                

        if (hibin >= 180 && hibin <= 200) {
          for (int n = 0; n < 56; n++) {
                        
		        int side = (int)((zsideLeaf->GetValue(n) + 1) / 2.0);  //side == 0 is the neg side and side == 1 is the pos side
		        int type = (int)(sectionLeaf->GetValue(n)) - 1;        //type == 0 is EM, type == 1 is HAD, type == 2 is BRAN (does not exist), and type == 3 is RPD
		        int channel = (int)(channelLeaf->GetValue(n)) - 1;     //EM has 5 channels, HAD has 4 channels, and RPD has 16 channels

		        if (side == 1 && type == 3) 
              {
                double TS_fC[NTS];

                for (int iTS = 0; iTS < NTS; iTS++) {
                  if (fCleaf[iTS]->GetValue(n) > 100) {
                    TS_fC[iTS] = fCleaf[iTS]->GetValue(n);
                  }
                }

                  if(channel == 0){
                    for (int iTS = 0; iTS < 6; iTS++) {
                      pos_rpd_ts_block10->Fill(iTS,TS_fC[iTS]) ; // channel 0 corresponds to block 10
                    }
                    pos_RPD_ratio_block10 = TS_fC[2] / TS_fC[3];      
						        pRPD_ratio_TS_2to3_block10->Fill(pos_RPD_ratio_block10);
                    if (pos_RPD_ratio_block10 > 1.7 && pos_RPD_ratio_block10 < 2.2) {

                     pRPD_block10_signal = TS_fC[2] + TS_fC[3];

                     pRPD_block10_fC->Fill(pRPD_block10_signal);
                    }
                  }

                  if(channel == 1){
                    for (int iTS = 0; iTS < 6; iTS++) {
                      pos_rpd_ts_block6->Fill(iTS,TS_fC[iTS]) ; // channel 1 corresponds to block 6
                    }
                    pos_RPD_ratio_block6 = TS_fC[2] / TS_fC[3];      
						        pRPD_ratio_TS_2to3_block6->Fill(pos_RPD_ratio_block6);
                    if (pos_RPD_ratio_block6 > 1.7 && pos_RPD_ratio_block6 < 2.2) {

                      pRPD_block6_signal = TS_fC[2] + TS_fC[3];

                      pRPD_block6_fC->Fill(pRPD_block6_signal);
                    }
                  }

                     if(channel == 2){
                        for (int iTS = 0; iTS < 6; iTS++) {
                         pos_rpd_ts_block2->Fill(iTS,TS_fC[iTS]) ; // channel 2 corresponds to block 2
                        }
                        pos_RPD_ratio_block2 = TS_fC[2] / TS_fC[3];      
						            pRPD_ratio_TS_2to3_block2->Fill(pos_RPD_ratio_block2);
                        if (pos_RPD_ratio_block2 > 1.7 && pos_RPD_ratio_block2 < 2.3) {

                            pRPD_block2_signal = TS_fC[2] + TS_fC[3];

                            pRPD_block2_fC->Fill(pRPD_block2_signal);
                          }
                    }

                     if(channel == 3){
                        for (int iTS = 0; iTS < 6; iTS++) {
                         pos_rpd_ts_block14->Fill(iTS,TS_fC[iTS]) ; // channel 3 corresponds to block 14
                        }
                        pos_RPD_ratio_block14 = TS_fC[2] / TS_fC[3];      
						            pRPD_ratio_TS_2to3_block14->Fill(pos_RPD_ratio_block14);
                        if (pos_RPD_ratio_block14 > 1.7 && pos_RPD_ratio_block14 < 2.2) {

                            pRPD_block14_signal = TS_fC[2] + TS_fC[3];

                            pRPD_block14_fC->Fill(pRPD_block14_signal);
                          }
                    } 
                    if(channel == 4){
                        for (int iTS = 0; iTS < 6; iTS++) {
                         pos_rpd_ts_block11->Fill(iTS,TS_fC[iTS]) ; // channel 4 corresponds to block 11
                        }
                        pos_RPD_ratio_block11 = TS_fC[2] / TS_fC[3];      
						            pRPD_ratio_TS_2to3_block11->Fill(pos_RPD_ratio_block11);
                        if (pos_RPD_ratio_block11 > 1.7 && pos_RPD_ratio_block11 < 2.2) {

                            pRPD_block11_signal = TS_fC[2] + TS_fC[3];

                            pRPD_block11_fC->Fill(pRPD_block11_signal);
                          }
                    }
                     if(channel == 5){
                        for (int iTS = 0; iTS < 6; iTS++) {
                         pos_rpd_ts_block7->Fill(iTS,TS_fC[iTS]) ; // channel 5 corresponds to block 7
                        }
                        pos_RPD_ratio_block7 = TS_fC[2] / TS_fC[3];      
						            pRPD_ratio_TS_2to3_block7->Fill(pos_RPD_ratio_block7);
                        if (pos_RPD_ratio_block7 > 1.7 && pos_RPD_ratio_block7 < 2.2) {

                            pRPD_block7_signal = TS_fC[2] + TS_fC[3];

                            pRPD_block7_fC->Fill(pRPD_block7_signal);
                          }
                    }
                      if(channel == 6){
                        for (int iTS = 0; iTS < 6; iTS++) {
                         pos_rpd_ts_block3->Fill(iTS,TS_fC[iTS]) ; // channel 6 corresponds to block 3
                        }
                        pos_RPD_ratio_block3 = TS_fC[2] / TS_fC[3];      
						            pRPD_ratio_TS_2to3_block3->Fill(pos_RPD_ratio_block3);
                        if (pos_RPD_ratio_block3 > 1.7 && pos_RPD_ratio_block3 < 2.4) {

                            pRPD_block3_signal = TS_fC[2] + TS_fC[3];

                            pRPD_block3_fC->Fill(pRPD_block3_signal);
                          }
                    }
                      if(channel == 7){
                        for (int iTS = 0; iTS < 6; iTS++) {
                         pos_rpd_ts_block15->Fill(iTS,TS_fC[iTS]) ; // channel 7 corresponds to block 15
                        }
                        pos_RPD_ratio_block15 = TS_fC[2] / TS_fC[3];      
						            pRPD_ratio_TS_2to3_block15->Fill(pos_RPD_ratio_block15);
                        if (pos_RPD_ratio_block15 > 1.7 && pos_RPD_ratio_block15 < 2.3) {

                            pRPD_block15_signal = TS_fC[2] + TS_fC[3];

                            pRPD_block15_fC->Fill(pRPD_block15_signal);
                          }
                    }
                      if(channel == 8){
                        for (int iTS = 0; iTS < 6; iTS++) {
                         pos_rpd_ts_block4->Fill(iTS,TS_fC[iTS]) ; // channel 8 corresponds to block 4
                        }
                        pos_RPD_ratio_block4 = TS_fC[2] / TS_fC[3];      
						            pRPD_ratio_TS_2to3_block4->Fill(pos_RPD_ratio_block4);
                        if (pos_RPD_ratio_block4 > 1.7 && pos_RPD_ratio_block4 < 2.4) {

                            pRPD_block4_signal = TS_fC[2] + TS_fC[3];

                            pRPD_block4_fC->Fill(pRPD_block4_signal);
                          }
                    }
                      if(channel == 9){
                        for (int iTS = 0; iTS < 6; iTS++) {
                         pos_rpd_ts_block8->Fill(iTS,TS_fC[iTS]) ; // channel 9 corresponds to block 8
                        }
                        pos_RPD_ratio_block8 = TS_fC[2] / TS_fC[3];      
						            pRPD_ratio_TS_2to3_block8->Fill(pos_RPD_ratio_block8);
                        if (pos_RPD_ratio_block8 > 1.3 && pos_RPD_ratio_block8 < 2.4) {

                            pRPD_block8_signal = TS_fC[2] + TS_fC[3];

                            pRPD_block8_fC->Fill(pRPD_block8_signal);
                          }
                    }
                      if(channel == 10){
                        for (int iTS = 0; iTS < 6; iTS++) {
                         pos_rpd_ts_block12->Fill(iTS,TS_fC[iTS]) ; // channel 10 corresponds to block 12
                        }
                        pos_RPD_ratio_block12 = TS_fC[2] / TS_fC[3];      
						            pRPD_ratio_TS_2to3_block12->Fill(pos_RPD_ratio_block12);
                        if (pos_RPD_ratio_block12 > 1.3 && pos_RPD_ratio_block12 < 2.4) {

                            pRPD_block12_signal = TS_fC[2] + TS_fC[3];

                            pRPD_block12_fC->Fill(pRPD_block12_signal);
                          }
                    }
                      if(channel == 11){
                        for (int iTS = 0; iTS < 6; iTS++) {
                         pos_rpd_ts_block0->Fill(iTS,TS_fC[iTS]) ; // channel 11 corresponds to block 0
                        }
                        pos_RPD_ratio_block0 = TS_fC[2] / TS_fC[3];      
						            pRPD_ratio_TS_2to3_block0->Fill(pos_RPD_ratio_block0);
                        if (pos_RPD_ratio_block0 > 1.2 && pos_RPD_ratio_block0 < 2.5) {

                            pRPD_block0_signal = TS_fC[2] + TS_fC[3];

                            pRPD_block0_fC->Fill(pRPD_block0_signal);
                          }
                    }
                      if(channel == 12){
                        for (int iTS = 0; iTS < 6; iTS++) {
                         pos_rpd_ts_block5->Fill(iTS,TS_fC[iTS]) ; // channel 12 corresponds to block 5
                        }
                        pos_RPD_ratio_block5 = TS_fC[2] / TS_fC[3];      
						            pRPD_ratio_TS_2to3_block5->Fill(pos_RPD_ratio_block5);
                        if (pos_RPD_ratio_block5 > 1.8 && pos_RPD_ratio_block5 < 2.6) {

                            pRPD_block5_signal = TS_fC[2] + TS_fC[3];

                            pRPD_block5_fC->Fill(pRPD_block5_signal);
                          }
                    }
                      if(channel == 13){
                        for (int iTS = 0; iTS < 6; iTS++) {
                         pos_rpd_ts_block9->Fill(iTS,TS_fC[iTS]) ; // channel 13 corresponds to block 9
                        }
                        pos_RPD_ratio_block9 = TS_fC[2] / TS_fC[3];      
						            pRPD_ratio_TS_2to3_block9->Fill(pos_RPD_ratio_block9);
                        if (pos_RPD_ratio_block9 > 1.8 && pos_RPD_ratio_block9 < 2.6) {

                            pRPD_block9_signal = TS_fC[2] + TS_fC[3];

                            pRPD_block9_fC->Fill(pRPD_block9_signal);
                          }
                    }
                      if(channel == 14){
                        for (int iTS = 0; iTS < 6; iTS++) {
                         pos_rpd_ts_block13->Fill(iTS,TS_fC[iTS]) ; // channel 14 corresponds to block 13
                        }
                        pos_RPD_ratio_block13 = TS_fC[2] / TS_fC[3];      
						            pRPD_ratio_TS_2to3_block13->Fill(pos_RPD_ratio_block13);
                        if (pos_RPD_ratio_block13 > 1.8 && pos_RPD_ratio_block13 < 2.4) {

                            pRPD_block13_signal = TS_fC[2] + TS_fC[3];

                            pRPD_block13_fC->Fill(pRPD_block13_signal);
                          }
                    }
                      if(channel == 15){
                        for (int iTS = 0; iTS < 6; iTS++) {
                         pos_rpd_ts_block1->Fill(iTS,TS_fC[iTS]) ; // channel 15 corresponds to block 1
                        }
                        pos_RPD_ratio_block1 = TS_fC[2] / TS_fC[3];      
						            pRPD_ratio_TS_2to3_block1->Fill(pos_RPD_ratio_block1);
                        if (pos_RPD_ratio_block1 > 1.8 && pos_RPD_ratio_block1 < 2.7) {

                            pRPD_block1_signal = TS_fC[2] + TS_fC[3];

                            pRPD_block1_fC->Fill(pRPD_block1_signal);
                          }
                    }                                
                          pRPDX1 = pRPD_block0_signal + pRPD_block4_signal + pRPD_block8_signal + pRPD_block12_signal;
                          pRPDX2 = pRPD_block1_signal + pRPD_block5_signal + pRPD_block9_signal + pRPD_block13_signal;
                          pRPDX3 = pRPD_block2_signal + pRPD_block6_signal + pRPD_block10_signal + pRPD_block14_signal;
                          pRPDX4 = pRPD_block3_signal + pRPD_block7_signal + pRPD_block11_signal + pRPD_block15_signal;

                          pRPDY1 = pRPD_block0_signal + pRPD_block1_signal + pRPD_block2_signal + pRPD_block3_signal;
                          pRPDY2 = pRPD_block4_signal + pRPD_block5_signal + pRPD_block6_signal + pRPD_block7_signal;
                          pRPDY3 = pRPD_block8_signal + pRPD_block9_signal + pRPD_block10_signal + pRPD_block11_signal;
                          pRPDY4 = pRPD_block12_signal + pRPD_block13_signal + pRPD_block14_signal + pRPD_block15_signal;

                          pRPD_Total_Signal = pRPDY1 + pRPDY2 + pRPDY3 + pRPDY4;
                          pRPD_signal_row = (((-3) * (pRPDY4)) + ((-1) * (pRPDY3)) + ((1) * (pRPDY2)) + ((3) * (pRPDY1))) / pRPD_Total_Signal;
                          pRPD_signal_col = (((3) * (pRPDX4)) + ((1) * (pRPDX3)) + ((-1) * (pRPDX2)) + ((-3) * (pRPDX1))) / pRPD_Total_Signal;
                          if (pRPD_signal_row == 0 && pRPD_signal_col == 0) {continue;}
                        
                        pRPD_blockdiagram->Fill(0.5,3.5,pRPD_block0_signal);
                        pRPD_blockdiagram->Fill(1.5,3.5,pRPD_block1_signal);
                        pRPD_blockdiagram->Fill(2.5,3.5,pRPD_block2_signal);
                        pRPD_blockdiagram->Fill(3.5,3.5,pRPD_block3_signal);

                        pRPD_blockdiagram->Fill(0.5,2.5,pRPD_block4_signal);
                        pRPD_blockdiagram->Fill(1.5,2.5,pRPD_block5_signal);
                        pRPD_blockdiagram->Fill(2.5,2.5,pRPD_block6_signal);
                        pRPD_blockdiagram->Fill(3.5,2.5,pRPD_block7_signal);

                        pRPD_blockdiagram->Fill(0.5,1.5,pRPD_block8_signal);
                        pRPD_blockdiagram->Fill(1.5,1.5,pRPD_block9_signal);
                        pRPD_blockdiagram->Fill(2.5,1.5,pRPD_block10_signal);
                        pRPD_blockdiagram->Fill(3.5,1.5,pRPD_block11_signal);

                        pRPD_blockdiagram->Fill(0.5,0.5,pRPD_block12_signal);
                        pRPD_blockdiagram->Fill(1.5,0.5,pRPD_block13_signal);
                        pRPD_blockdiagram->Fill(2.5,0.5,pRPD_block14_signal);
                        pRPD_blockdiagram->Fill(3.5,0.5,pRPD_block15_signal);
                      }
                        } // end of channel loop
                      pRPD_COM10->Fill(pRPD_signal_col, pRPD_signal_row);

      } // end of centrality     
      
    } // end of event loop (for)
    //Fit the ratios with a gaussian function
    pRPD_ratio_TS_2to3_block0->Fit("gaus","","",1,3);
    pRPD_ratio_TS_2to3_block1->Fit("gaus","","",1.5,3);
    pRPD_ratio_TS_2to3_block2->Fit("gaus","","",1.5,3);
    pRPD_ratio_TS_2to3_block3->Fit("gaus","","",1.6,3);
    pRPD_ratio_TS_2to3_block4->Fit("gaus","","",1,3);
    pRPD_ratio_TS_2to3_block5->Fit("gaus","","",1.7,3);
    pRPD_ratio_TS_2to3_block6->Fit("gaus","","",1.5,3);
    pRPD_ratio_TS_2to3_block7->Fit("gaus","","",1.7,3);
    pRPD_ratio_TS_2to3_block8->Fit("gaus","","",1,3);
    pRPD_ratio_TS_2to3_block9->Fit("gaus","","",1.7,3);
    pRPD_ratio_TS_2to3_block10->Fit("gaus","","",1.5,3);
    pRPD_ratio_TS_2to3_block11->Fit("gaus","","",1.5,3);
    pRPD_ratio_TS_2to3_block12->Fit("gaus","","",1,3);
    pRPD_ratio_TS_2to3_block13->Fit("gaus","","",1.7,3);
    pRPD_ratio_TS_2to3_block14->Fit("gaus","","",1.4,3);
    pRPD_ratio_TS_2to3_block15->Fit("gaus","","",1.6,3);


    //Display Fit Parameters in Statistics Box in histogram
    gStyle->SetOptFit();
    
    //Make Canvas
    TCanvas *c1 = new TCanvas();

    // Give canvas a title
    c1->SetTitle("Run 375259 Time Slice Distribution for Positive RPD");

    //Divide canvas into a 4x4 grid
    c1->Divide(4,4);

    //Title axes on histograms
    pos_rpd_ts_block0->SetXTitle("Time Slices");
    pos_rpd_ts_block1->SetXTitle("Time Slices");
    pos_rpd_ts_block2->SetXTitle("Time Slices");
    pos_rpd_ts_block3->SetXTitle("Time Slices");
    pos_rpd_ts_block4->SetXTitle("Time Slices");
    pos_rpd_ts_block5->SetXTitle("Time Slices");
    pos_rpd_ts_block6->SetXTitle("Time Slices");
    pos_rpd_ts_block7->SetXTitle("Time Slices");
    pos_rpd_ts_block8->SetXTitle("Time Slices");
    pos_rpd_ts_block9->SetXTitle("Time Slices");
    pos_rpd_ts_block10->SetXTitle("Time Slices");
    pos_rpd_ts_block11->SetXTitle("Time Slices");
    pos_rpd_ts_block12->SetXTitle("Time Slices");
    pos_rpd_ts_block13->SetXTitle("Time Slices");
    pos_rpd_ts_block14->SetXTitle("Time Slices");
    pos_rpd_ts_block15->SetXTitle("Time Slices");

    pos_rpd_ts_block0->SetYTitle("Charge (fC)");
    pos_rpd_ts_block1->SetYTitle("Charge (fC)");
    pos_rpd_ts_block2->SetYTitle("Charge (fC)");
    pos_rpd_ts_block3->SetYTitle("Charge (fC)");
    pos_rpd_ts_block4->SetYTitle("Charge (fC)");
    pos_rpd_ts_block5->SetYTitle("Charge (fC)");
    pos_rpd_ts_block6->SetYTitle("Charge (fC)");
    pos_rpd_ts_block7->SetYTitle("Charge (fC)");
    pos_rpd_ts_block8->SetYTitle("Charge (fC)");
    pos_rpd_ts_block9->SetYTitle("Charge (fC)");
    pos_rpd_ts_block10->SetYTitle("Charge (fC)");
    pos_rpd_ts_block11->SetYTitle("Charge (fC)");
    pos_rpd_ts_block12->SetYTitle("Charge (fC)");
    pos_rpd_ts_block13->SetYTitle("Charge (fC)");
    pos_rpd_ts_block14->SetYTitle("Charge (fC)");
    pos_rpd_ts_block15->SetYTitle("Charge (fC)");


    
    // Draw Histogram and place on specific section of canvas
    
    c1->cd(1);
    pos_rpd_ts_block0->Draw("hist e");

    c1->cd(2);
    pos_rpd_ts_block1->Draw("hist e");

    c1->cd(3);
    pos_rpd_ts_block2->Draw("hist e");

    c1->cd(4);
    pos_rpd_ts_block3->Draw("hist e");

    c1->cd(5);
    pos_rpd_ts_block4->Draw("hist e");

    c1->cd(6);
    pos_rpd_ts_block5->Draw("hist e");
    
    c1->cd(7);
    pos_rpd_ts_block6->Draw("hist e");
  
    c1->cd(8);
    pos_rpd_ts_block7->Draw("hist e");

    c1->cd(9);    
    pos_rpd_ts_block8->Draw("hist e");

    c1->cd(10);
    pos_rpd_ts_block9->Draw("hist e");

    c1->cd(11);
    pos_rpd_ts_block10->Draw("hist e");

    c1->cd(12);
    pos_rpd_ts_block11->Draw("hist e");

    c1->cd(13);
    pos_rpd_ts_block12->Draw("hist e");

    c1->cd(14);
    pos_rpd_ts_block13->Draw("hist e");

    c1->cd(15);
    pos_rpd_ts_block14->Draw("hist e");

    c1->cd(16);
    pos_rpd_ts_block15->Draw("hist e");
    
    //c1->SaveAs("/home/mwrotny/Run375259_TSDist_pRPD.pdf");

    // Definition of new canvas for time slice ratios
    TCanvas *c2 = new TCanvas("title","title",600,800);

    c2->SetTitle("Run 375259 Pos RPD TS Ratios");

    c2->Divide(4,4);

    pRPD_ratio_TS_2to3_block0->SetXTitle("TS2 / TS3");
    pRPD_ratio_TS_2to3_block1->SetXTitle("TS2 / TS3");
    pRPD_ratio_TS_2to3_block2->SetXTitle("TS2 / TS3");
    pRPD_ratio_TS_2to3_block3->SetXTitle("TS2 / TS3");
    pRPD_ratio_TS_2to3_block4->SetXTitle("TS2 / TS3");
    pRPD_ratio_TS_2to3_block5->SetXTitle("TS2 / TS3");
    pRPD_ratio_TS_2to3_block6->SetXTitle("TS2 / TS3");
    pRPD_ratio_TS_2to3_block7->SetXTitle("TS2 / TS3");
    pRPD_ratio_TS_2to3_block8->SetXTitle("TS2 / TS3");
    pRPD_ratio_TS_2to3_block9->SetXTitle("TS2 / TS3");
    pRPD_ratio_TS_2to3_block10->SetXTitle("TS2 / TS3");
    pRPD_ratio_TS_2to3_block11->SetXTitle("TS2 / TS3");
    pRPD_ratio_TS_2to3_block12->SetXTitle("TS2 / TS3");
    pRPD_ratio_TS_2to3_block13->SetXTitle("TS2 / TS3");
    pRPD_ratio_TS_2to3_block14->SetXTitle("TS2 / TS3");
    pRPD_ratio_TS_2to3_block15->SetXTitle("TS2 / TS3");

    pRPD_ratio_TS_2to3_block0->SetYTitle("Counts");
    pRPD_ratio_TS_2to3_block1->SetYTitle("Counts");
    pRPD_ratio_TS_2to3_block2->SetYTitle("Counts");
    pRPD_ratio_TS_2to3_block3->SetYTitle("Counts");
    pRPD_ratio_TS_2to3_block4->SetYTitle("Counts");
    pRPD_ratio_TS_2to3_block5->SetYTitle("Counts");
    pRPD_ratio_TS_2to3_block6->SetYTitle("Counts");
    pRPD_ratio_TS_2to3_block7->SetYTitle("Counts");
    pRPD_ratio_TS_2to3_block8->SetYTitle("Counts");
    pRPD_ratio_TS_2to3_block9->SetYTitle("Counts");
    pRPD_ratio_TS_2to3_block10->SetYTitle("Counts");
    pRPD_ratio_TS_2to3_block11->SetYTitle("Counts");
    pRPD_ratio_TS_2to3_block12->SetYTitle("Counts");
    pRPD_ratio_TS_2to3_block13->SetYTitle("Counts");
    pRPD_ratio_TS_2to3_block14->SetYTitle("Counts");
    pRPD_ratio_TS_2to3_block15->SetYTitle("Counts");
    
    c2->cd(1);
    pRPD_ratio_TS_2to3_block0->Draw();

    c2->cd(2);
    pRPD_ratio_TS_2to3_block1->Draw();

    c2->cd(3);
    pRPD_ratio_TS_2to3_block2->Draw();

    c2->cd(4);
    pRPD_ratio_TS_2to3_block3->Draw();

    c2->cd(5);
    pRPD_ratio_TS_2to3_block4->Draw();

    c2->cd(6);
    pRPD_ratio_TS_2to3_block5->Draw();

    c2->cd(7);
    pRPD_ratio_TS_2to3_block6->Draw();

    c2->cd(8);
    pRPD_ratio_TS_2to3_block7->Draw();

    c2->cd(9);
    pRPD_ratio_TS_2to3_block8->Draw();

    c2->cd(10);
    pRPD_ratio_TS_2to3_block9->Draw();

    c2->cd(11);
    pRPD_ratio_TS_2to3_block10->Draw();

    c2->cd(12);
    pRPD_ratio_TS_2to3_block11->Draw();

    c2->cd(13);
    pRPD_ratio_TS_2to3_block12->Draw();

    c2->cd(14);
    pRPD_ratio_TS_2to3_block13->Draw();

    c2->cd(15);
    pRPD_ratio_TS_2to3_block14->Draw();

    c2->cd(16);
    pRPD_ratio_TS_2to3_block15->Draw();
    
    //c2->SaveAs("/home/mwrotny/Run375259_TimeSliceRatio_2_to_3_pRPD_gausfits.pdf");

    TCanvas *c3 = new TCanvas();

    c3->SetTitle("Run 375259 fC Distributions Pos RPD Including Ratio-Cuts");

    c3->Divide(4,4);

    pRPD_block0_fC->SetXTitle("fC");
    pRPD_block1_fC->SetXTitle("fC");
    pRPD_block2_fC->SetXTitle("fC");
    pRPD_block3_fC->SetXTitle("fC");
    pRPD_block4_fC->SetXTitle("fC");
    pRPD_block5_fC->SetXTitle("fC");
    pRPD_block6_fC->SetXTitle("fC");
    pRPD_block7_fC->SetXTitle("fC");
    pRPD_block8_fC->SetXTitle("fC");
    pRPD_block9_fC->SetXTitle("fC");
    pRPD_block10_fC->SetXTitle("fC");
    pRPD_block11_fC->SetXTitle("fC");
    pRPD_block12_fC->SetXTitle("fC");
    pRPD_block13_fC->SetXTitle("fC");
    pRPD_block14_fC->SetXTitle("fC");
    pRPD_block15_fC->SetXTitle("fC");

    pRPD_block0_fC->SetYTitle("Counts");
    pRPD_block1_fC->SetYTitle("Counts");
    pRPD_block2_fC->SetYTitle("Counts");
    pRPD_block3_fC->SetYTitle("Counts");
    pRPD_block4_fC->SetYTitle("Counts");
    pRPD_block5_fC->SetYTitle("Counts");
    pRPD_block6_fC->SetYTitle("Counts");
    pRPD_block7_fC->SetYTitle("Counts");
    pRPD_block8_fC->SetYTitle("Counts");
    pRPD_block9_fC->SetYTitle("Counts");
    pRPD_block10_fC->SetYTitle("Counts");
    pRPD_block11_fC->SetYTitle("Counts");
    pRPD_block12_fC->SetYTitle("Counts");
    pRPD_block13_fC->SetYTitle("Counts");
    pRPD_block14_fC->SetYTitle("Counts");
    pRPD_block15_fC->SetYTitle("Counts");

    c3->cd(1);
    pRPD_block0_fC->Draw();

    c3->cd(2);
    pRPD_block1_fC->Draw();

    c3->cd(3);
    pRPD_block2_fC->Draw();

    c3->cd(4);
    pRPD_block3_fC->Draw();

    c3->cd(5);
    pRPD_block4_fC->Draw();

    c3->cd(6);
    pRPD_block5_fC->Draw();

    c3->cd(7);
    pRPD_block6_fC->Draw();

    c3->cd(8);
    pRPD_block7_fC->Draw();

    c3->cd(9);
    pRPD_block8_fC->Draw();

    c3->cd(10);
    pRPD_block9_fC->Draw();

    c3->cd(11);
    pRPD_block10_fC->Draw();

    c3->cd(12);
    pRPD_block11_fC->Draw();

    c3->cd(13);
    pRPD_block12_fC->Draw();

    c3->cd(14);
    pRPD_block13_fC->Draw();

    c3->cd(15);
    pRPD_block14_fC->Draw();

    c3->cd(16);
    pRPD_block15_fC->Draw();
    
    //c3->SaveAs("/home/mwrotny/Run375259_pRPD_fC_Distributions.pdf");

    pRPD_COM1->SetXTitle("X Position (cm)");
    pRPD_COM1->SetYTitle("Y Position (cm)");

    pRPD_COM2->SetXTitle("X Position (cm)");
    pRPD_COM2->SetYTitle("Y Position (cm)");

    pRPD_COM3->SetXTitle("X Position (cm)");
    pRPD_COM4->SetYTitle("Y Position (cm)");

    pRPD_COM4->SetXTitle("X Position (cm)");
    pRPD_COM4->SetYTitle("Y Position (cm)");

    pRPD_COM5->SetXTitle("X Position (cm)");
    pRPD_COM5->SetYTitle("Y Position (cm)");

    pRPD_COM6->SetXTitle("X Position (cm)");
    pRPD_COM6->SetYTitle("Y Position (cm)");

    pRPD_COM7->SetXTitle("X Position (cm)");
    pRPD_COM7->SetYTitle("Y Position (cm)");

    pRPD_COM8->SetXTitle("X Position (cm)");
    pRPD_COM8->SetYTitle("Y Position (cm)");

    pRPD_COM9->SetXTitle("X Position (cm)");
    pRPD_COM9->SetYTitle("Y Position (cm)");

    pRPD_COM10->SetXTitle("X Position (cm)");
    pRPD_COM10->SetYTitle("Y Position (cm)");

    TCanvas *c4 = new TCanvas();
    //Divide into 5 columns, 2 rows
   
    pRPD_COM10->Draw("colz");

    pRPD_blockdiagram->SetXTitle("Column");
    pRPD_blockdiagram->SetYTitle("Row");

    TCanvas *c5 = new TCanvas();

    pRPD_blockdiagram->Draw("textcolz");   
    
   //c4->SaveAs("/home/mwrotny/Run375259_pRPD_realCOMvsCent.pdf");
}
