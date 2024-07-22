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

void Run375259_NeutronPlot()
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

    TH1F *pEM_TSratio[5] = {0};

        pEM_TSratio[0] = new TH1F("","",100,0,10); 
        pEM_TSratio[1] = new TH1F("","",100,0,10); 
        pEM_TSratio[2] = new TH1F("","",100,0,10); 
        pEM_TSratio[3] = new TH1F("","",100,0,10); 
        pEM_TSratio[4] = new TH1F("","",100,0,10); 

    TH1F* pHAD_TSratio[4] = {0};

        pHAD_TSratio[0] = new TH1F("","",100,0,10);
        pHAD_TSratio[1] = new TH1F("","",100,0,10);
        pHAD_TSratio[2] = new TH1F("","",100,0,10);
        pHAD_TSratio[3] = new TH1F("","",100,0,10);

    TH2F* NeutronPlot = new TH2F("","Run375259 Neutron Plot",200,0,40000,200,0,70000);
    TH1F* NeutronPlotProj = new TH1F("","Run 375259 Neutron Plot Projection",200,1000,40000);
    TH2F* EMpositionVSTotalSig = new TH2F("","Run 375259 pos EM position vs total signal",200,0,200000,100,-5,5);

    int hibin;
    float ZDC;
    float sumPlus;
    float sumMinus;
    float pEM_ratio[5];
    float pEM_signal[5];
    float pHAD_ratio[4];
    float pHAD_signal[4];

    int zside[56];
    int section[56];
    int channel[56];
    float TS0[56];
    float TS1[56];
    float TS2[56];
    float TS3[56];
    float TS4[56];
    float TS5[56];

    float pEM_signal_total;
    float pHAD_signal_total;
    float pEM_signal_position;

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
    zdcchain->SetBranchAddress("sumPlus",&sumPlus);
    zdcchain->SetBranchAddress("sumMinus",&sumMinus);

    Int_t NumofEvents = zdcchain->GetEntries();
	    cout << "Total # of events = " << NumofEvents << endl;
        NumofEvents = 100000;
            for (int i = 0; i < NumofEvents; i++) {           
		        zdcchain->GetEntry(i);  
                hichain->GetEntry(i);
                if (hibin >= 180 && hibin <= 200){
                for (int n = 0; n < 56; n++){
                    if (zside[n] == 1 && section[n] == 1){
                        if (channel[n] == 1) {
                                    pEM_ratio[0] = (TS2[n]/TS3[n]);
                                    pEM_TSratio[0]->Fill(pEM_ratio[0]);

                                    if (pEM_ratio[0] > 3.6967 && pEM_ratio[0] < 4.8773){
                                        pEM_signal[0] = TS2[n] + TS3[n];
                                    }
                                }
                                if (channel[n] == 2) {

                                    pEM_ratio[1] = (TS2[n] / TS3[n]);
                                    pEM_TSratio[1]->Fill(pEM_ratio[1]);

                                    if (pEM_ratio[1] > 3.9674 && pEM_ratio[1] < 4.5806){
                                        pEM_signal[1] = TS2[n] + TS3[n];
                                    }
                                }
                                if (channel[n] == 3){

                                    pEM_ratio[2] = (TS2[n] / TS3[n]);
                                    pEM_TSratio[2]->Fill(pEM_ratio[2]);

                                    if (pEM_ratio[2] > 3.6616 && pEM_ratio[2] < 4.1064){
                                        pEM_signal[2] = TS2[n] + TS3[n];
                                    }
                                }
                                if (channel[n] == 4){

                                    pEM_ratio[3] = (TS2[n] / TS3[n]);
                                    pEM_TSratio[3]->Fill(pEM_ratio[3]);

                                    if (pEM_ratio[3] > 3.5942 && pEM_ratio[3] < 3.8438){
                                        pEM_signal[3] = TS2[n] + TS3[n];
                                    }
                                }
                                if (channel[n] == 5){

                                    pEM_ratio[4] = (TS2[n] / TS3[n]);
                                    pEM_TSratio[4]->Fill(pEM_ratio[4]);

                                    if (pEM_ratio[4] > 3.4296 && pEM_ratio[4] < 3.6964){
                                        pEM_signal[4] = TS2[n] + TS3[n];
                                    }
                                }
                                pEM_signal_total = ( 0.6 * pEM_signal[0] + 0.89 * pEM_signal[1] + 1 * pEM_signal[2] + 1.29 * pEM_signal[3] + 0.57 * pEM_signal[4]);
                                pEM_signal_position = ( (0.6 * -3.6 * pEM_signal[0]) + (0.89 * -1.8 * pEM_signal[1]) + (1 * 0 * pEM_signal[2]) + (1.29 * 1.8 * pEM_signal[3]) + (0.57 * 3.6 * pEM_signal[4])) / pEM_signal_total;
                    } // end side section for EM
                    if (zside[n] == 1 && section[n] == 2){
                        if (channel[n] == 1){
                            pHAD_ratio[0] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[0]->Fill(pHAD_ratio[0]);
                            if (pHAD_ratio[0] > 3.5 && pHAD_ratio[0] < 4){
                                pHAD_signal[0] = TS2[n] + TS3[n];
                            }
                        }
                        if (channel[n] == 2){
                            pHAD_ratio[1] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[1]->Fill(pHAD_ratio[1]);
                            if (pHAD_ratio[1] > 3.5 && pHAD_ratio[1] < 4.5){
                                pHAD_signal[1] = TS2[n] + TS3[n];
                            }
                        }
                        if (channel[n] == 3){
                            pHAD_ratio[2] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[2]->Fill(pHAD_ratio[2]);
                            if (pHAD_ratio[2] > 3.5 && pHAD_ratio[2] < 5){
                                pHAD_signal[2] = TS2[n] + TS3[n];
                            }
                        }
                        if (channel[n] == 4){
                            pHAD_ratio[3] = (TS2[n] / TS3[n]);
                            pHAD_TSratio[3]->Fill(pHAD_ratio[3]);
                            if (pHAD_ratio[3] > 4 && pHAD_ratio[3] < 5){
                                pHAD_signal[3] = TS2[n] + TS3[n];
                            }
                        }
                        pHAD_signal_total = pHAD_signal[0] + pHAD_signal[1] + pHAD_signal[2] + pHAD_signal[3]; 
                        ZDC = ((0.1 * pEM_signal_total) + pHAD_signal_total); // in GeV
                    } // end side and section for had
                    //cout << "ZDC value = " << ZDC << endl;
                } // end channel loop
                // 0.9397 GeV / fC
                NeutronPlot->Fill(ZDC, pEM_signal_total);
                NeutronPlotProj->Fill(ZDC);
                EMpositionVSTotalSig->Fill(ZDC,pEM_signal_position);
                } // end centrality
            } // end event loop

            pEM_TSratio[0]->Fit("gaus","","",3,6);
            pEM_TSratio[1]->Fit("gaus","","",3,5.5);
            pEM_TSratio[2]->Fit("gaus","","",3,5);
            pEM_TSratio[3]->Fit("gaus","","",3,4.2);
            pEM_TSratio[4]->Fit("gaus","","",3,4.2);

            pHAD_TSratio[0]->Fit("gaus","","",3,4);
            pHAD_TSratio[1]->Fit("gaus","","",3,4.5);
            pHAD_TSratio[2]->Fit("gaus","","",3,5.5);
            pHAD_TSratio[3]->Fit("gaus","","",3,5.5);

            NeutronPlotProj->Fit("gaus","","",1500,3500);

            gStyle->SetOptFit();

            TCanvas *c1 = new TCanvas();
            c1->Divide(3,2);
            c1->cd(1);
            pEM_TSratio[0]->Draw("");
            c1->cd(2);
            pEM_TSratio[1]->Draw("");
            c1->cd(3);
            pEM_TSratio[2]->Draw("");
            c1->cd(4);
            pEM_TSratio[3]->Draw("");
            c1->cd(5);
            pEM_TSratio[4]->Draw("");
            TCanvas *c2 = new TCanvas();
            c2->Divide(2,2);
            c2->cd(1);
            pHAD_TSratio[0]->Draw("");
            c2->cd(2);
            pHAD_TSratio[1]->Draw("");
            c2->cd(3);
            pHAD_TSratio[2]->Draw("");
            c2->cd(4);
            pHAD_TSratio[3]->Draw("");

            TCanvas *c3 = new TCanvas();
            NeutronPlot->SetXTitle("0.1EM + HAD");
            NeutronPlot->SetYTitle("EM");
            NeutronPlot->Draw("colz");

            TCanvas *c4 = new TCanvas();
            NeutronPlotProj->SetXTitle("0.1EM + HAD");
            NeutronPlotProj->SetYTitle("counts");
            NeutronPlotProj->Draw();
            
            TCanvas *c5 = new TCanvas();
            EMpositionVSTotalSig->SetXTitle("0.1EM + HAD");
            EMpositionVSTotalSig->SetYTitle("EM Position");
            EMpositionVSTotalSig->Draw("colz");

             /* 
    // title and draw pEM distributions, ratios, and fc

    for (int n = 0; n < 5; n++){
        Run375259_pEM_TS[n][0]->SetXTitle("Time Slice");
        Run375259_pEM_TS[n][0]->SetYTitle("Charge (fC)");
        Run375259_pEM_TS[n][1]->SetXTitle("Time Slice");
        Run375259_pEM_TS[n][1]->SetYTitle("Charge (fC)");
        Run375259_pEM_TS[n][2]->SetXTitle("Time Slice");
        Run375259_pEM_TS[n][2]->SetYTitle("Charge (fC)");
        Run375259_pEM_TS[n][3]->SetXTitle("Time Slice");
        Run375259_pEM_TS[n][3]->SetYTitle("Charge (fC)");
        Run375259_pEM_TS[n][4]->SetXTitle("Time Slice");
        Run375259_pEM_TS[n][4]->SetYTitle("Charge (fC)");
        Run375259_pEM_TS[n][5]->SetXTitle("Time Slice");
        Run375259_pEM_TS[n][5]->SetYTitle("Charge (fC)");
        Run375259_pEM_TS[n][6]->SetXTitle("Time Slice");
        Run375259_pEM_TS[n][6]->SetYTitle("Charge (fC)");
        Run375259_pEM_TS[n][7]->SetXTitle("Time Slice");
        Run375259_pEM_TS[n][7]->SetYTitle("Charge (fC)");
        Run375259_pEM_TS[n][8]->SetXTitle("Time Slice");
        Run375259_pEM_TS[n][8]->SetYTitle("Charge (fC)");
        Run375259_pEM_TS[n][9]->SetXTitle("Time Slice");
        Run375259_pEM_TS[n][9]->SetYTitle("Charge (fC)");
        Run375259_pEM_TS[n][10]->SetXTitle("Time Slice");
        Run375259_pEM_TS[n][10]->SetYTitle("Charge (fC)");
    }
    
    TCanvas *a1 = new TCanvas();
    a1->Divide(5,5);
    Run375259_pEM_TS[0][0]->Draw("hist e");
    Run375259_pEM_TS[1][0]->Draw("hist e");
    Run375259_pEM_TS[2][0]->Draw("hist e");
    Run375259_pEM_TS[3][0]->Draw("hist e");
    Run375259_pEM_TS[4][0]->Draw("hist e");
    Run375259_pEM_TS[0][1]->Draw("hist e");
    Run375259_pEM_TS[1][1]->Draw("hist e");
    Run375259_pEM_TS[2][1]->Draw("hist e");
    Run375259_pEM_TS[3][1]->Draw("hist e");
    Run375259_pEM_TS[4][1]->Draw("hist e");
    Run375259_pEM_TS[0][2]->Draw("hist e");
    Run375259_pEM_TS[1][2]->Draw("hist e");
    Run375259_pEM_TS[2][2]->Draw("hist e");
    Run375259_pEM_TS[3][2]->Draw("hist e");
    Run375259_pEM_TS[4][2]->Draw("hist e");
    Run375259_pEM_TS[0][3]->Draw("hist e");
    Run375259_pEM_TS[1][3]->Draw("hist e");
    Run375259_pEM_TS[2][3]->Draw("hist e");
    Run375259_pEM_TS[3][3]->Draw("hist e");
    Run375259_pEM_TS[4][3]->Draw("hist e");
    Run375259_pEM_TS[0][4]->Draw("hist e");
    Run375259_pEM_TS[1][4]->Draw("hist e");
    Run375259_pEM_TS[2][4]->Draw("hist e");
    Run375259_pEM_TS[3][4]->Draw("hist e");
    Run375259_pEM_TS[4][4]->Draw("hist e");

    TCanvas *a2 = new TCanvas();
    a2->Divide(5,5);
    Run375259_pEM_TS[0][5]->Draw("hist e");
    Run375259_pEM_TS[1][5]->Draw("hist e");
    Run375259_pEM_TS[2][5]->Draw("hist e");
    Run375259_pEM_TS[3][5]->Draw("hist e");
    Run375259_pEM_TS[4][5]->Draw("hist e");
    Run375259_pEM_TS[0][6]->Draw("hist e");
    Run375259_pEM_TS[1][6]->Draw("hist e");
    Run375259_pEM_TS[2][6]->Draw("hist e");
    Run375259_pEM_TS[3][6]->Draw("hist e");
    Run375259_pEM_TS[4][6]->Draw("hist e");
    Run375259_pEM_TS[0][7]->Draw("hist e");
    Run375259_pEM_TS[1][7]->Draw("hist e");
    Run375259_pEM_TS[2][7]->Draw("hist e");
    Run375259_pEM_TS[3][7]->Draw("hist e");
    Run375259_pEM_TS[4][7]->Draw("hist e");
    Run375259_pEM_TS[0][8]->Draw("hist e");
    Run375259_pEM_TS[1][8]->Draw("hist e");
    Run375259_pEM_TS[2][8]->Draw("hist e");
    Run375259_pEM_TS[3][8]->Draw("hist e");
    Run375259_pEM_TS[4][8]->Draw("hist e");
    Run375259_pEM_TS[0][9]->Draw("hist e");
    Run375259_pEM_TS[1][9]->Draw("hist e");
    Run375259_pEM_TS[2][9]->Draw("hist e");
    Run375259_pEM_TS[3][9]->Draw("hist e");
    Run375259_pEM_TS[4][9]->Draw("hist e");

    TCanvas *a3 = new TCanvas();
    a3->Divide(2,2);
    a3->cd(1);
    Run375259_pEM_TS[0][10]->Draw("hist e");
    a3->cd(2);
    Run375259_pEM_TS[1][10]->Draw("hist e");
    a3->cd(3);
    Run375259_pEM_TS[2][10]->Draw("hist e");
    a3->cd(4);
    Run375259_pEM_TS[3][10]->Draw("hist e");
    a3->cd(5);
    Run375259_pEM_TS[4][10]->Draw("hist e");


    for (int n = 0; n < 5; n++){
        Run375259_pEM_TSratio[n][0]->SetXTitle("Ratio TS2 : TS3");
        Run375259_pEM_TSratio[n][0]->SetYTitle("Counts");
        Run375259_pEM_TSratio[n][1]->SetXTitle("Ratio TS2 : TS3");
        Run375259_pEM_TSratio[n][1]->SetYTitle("Counts");
        Run375259_pEM_TSratio[n][2]->SetXTitle("Ratio TS2 : TS3");
        Run375259_pEM_TSratio[n][2]->SetYTitle("Counts");
        Run375259_pEM_TSratio[n][3]->SetXTitle("Ratio TS2 : TS3");
        Run375259_pEM_TSratio[n][3]->SetYTitle("Counts");
        Run375259_pEM_TSratio[n][4]->SetXTitle("Ratio TS2 : TS3");
        Run375259_pEM_TSratio[n][4]->SetYTitle("Counts");
        Run375259_pEM_TSratio[n][5]->SetXTitle("Ratio TS2 : TS3");
        Run375259_pEM_TSratio[n][5]->SetYTitle("Counts");
        Run375259_pEM_TSratio[n][6]->SetXTitle("Ratio TS2 : TS3");
        Run375259_pEM_TSratio[n][6]->SetYTitle("Counts");
        Run375259_pEM_TSratio[n][7]->SetXTitle("Ratio TS2 : TS3");
        Run375259_pEM_TSratio[n][7]->SetYTitle("Counts");
        Run375259_pEM_TSratio[n][8]->SetXTitle("Ratio TS2 : TS3");
        Run375259_pEM_TSratio[n][8]->SetYTitle("Counts");
        Run375259_pEM_TSratio[n][9]->SetXTitle("Ratio TS2 : TS3");
        Run375259_pEM_TSratio[n][9]->SetYTitle("Counts");
        Run375259_pEM_TSratio[n][10]->SetXTitle("Ratio TS2 : TS3");
        Run375259_pEM_TSratio[n][10]->SetYTitle("Counts");
    }

    TCanvas *a4 = new TCanvas();
    a4->Divide(5,5);
    a4->cd(1);
    Run375259_pEM_TSratio[0][0]->Draw();
    Run375259_pEM_TSratio[1][0]->Draw();
    Run375259_pEM_TSratio[2][0]->Draw();
    Run375259_pEM_TSratio[3][0]->Draw();
    Run375259_pEM_TSratio[4][0]->Draw();
    Run375259_pEM_TSratio[0][1]->Draw();
    Run375259_pEM_TSratio[1][1]->Draw();
    Run375259_pEM_TSratio[2][1]->Draw();
    Run375259_pEM_TSratio[3][1]->Draw();
    Run375259_pEM_TSratio[4][1]->Draw();
    Run375259_pEM_TSratio[0][2]->Draw();
    Run375259_pEM_TSratio[1][2]->Draw();
    Run375259_pEM_TSratio[2][2]->Draw();
    Run375259_pEM_TSratio[3][2]->Draw();
    Run375259_pEM_TSratio[4][2]->Draw();
    Run375259_pEM_TSratio[0][3]->Draw();
    Run375259_pEM_TSratio[1][3]->Draw();
    Run375259_pEM_TSratio[2][3]->Draw();
    Run375259_pEM_TSratio[3][3]->Draw();
    Run375259_pEM_TSratio[4][3]->Draw();
    Run375259_pEM_TSratio[0][4]->Draw();
    Run375259_pEM_TSratio[1][4]->Draw();
    Run375259_pEM_TSratio[2][4]->Draw();
    Run375259_pEM_TSratio[3][4]->Draw();
    Run375259_pEM_TSratio[4][4]->Draw();

    TCanvas *a4 = new TCanvas();
    a4->Divide(5,5);
    Run375259_pEM_TSratio[0][0]->Draw();
    Run375259_pEM_TSratio[1][0]->Draw();
    Run375259_pEM_TSratio[2][0]->Draw();
    Run375259_pEM_TSratio[3][0]->Draw();
    Run375259_pEM_TSratio[4][0]->Draw();
    Run375259_pEM_TSratio[0][1]->Draw();
    Run375259_pEM_TSratio[1][1]->Draw();
    Run375259_pEM_TSratio[2][1]->Draw();
    Run375259_pEM_TSratio[3][1]->Draw();
    Run375259_pEM_TSratio[4][1]->Draw();
    Run375259_pEM_TSratio[0][2]->Draw();
    Run375259_pEM_TSratio[1][2]->Draw();
    Run375259_pEM_TSratio[2][2]->Draw();
    Run375259_pEM_TSratio[3][2]->Draw();
    Run375259_pEM_TSratio[4][2]->Draw();
    Run375259_pEM_TSratio[0][3]->Draw();
    Run375259_pEM_TSratio[1][3]->Draw();
    Run375259_pEM_TSratio[2][3]->Draw();
    Run375259_pEM_TSratio[3][3]->Draw();
    Run375259_pEM_TSratio[4][3]->Draw();
    Run375259_pEM_TSratio[0][4]->Draw();
    Run375259_pEM_TSratio[1][4]->Draw();
    Run375259_pEM_TSratio[2][4]->Draw();
    Run375259_pEM_TSratio[3][4]->Draw();
    Run375259_pEM_TSratio[4][4]->Draw();

    for (int n = 0; n < 5; n++){
        Run375259_pEM_fC[n][0]->SetXTitle("Charge (fC)");
        Run375259_pEM_fC[n][0]->SetYTitle("Counts");
        Run375259_pEM_fC[n][1]->SetXTitle("Charge (fC)");
        Run375259_pEM_fC[n][1]->SetYTitle("Counts");
        Run375259_pEM_fC[n][2]->SetXTitle("Charge (fC)");
        Run375259_pEM_fC[n][2]->SetYTitle("Counts");
        Run375259_pEM_fC[n][3]->SetXTitle("Charge (fC)");
        Run375259_pEM_fC[n][3]->SetYTitle("Counts");
        Run375259_pEM_fC[n][4]->SetXTitle("Charge (fC)");
        Run375259_pEM_fC[n][4]->SetYTitle("Counts");
        Run375259_pEM_fC[n][5]->SetXTitle("Charge (fC)");
        Run375259_pEM_fC[n][5]->SetYTitle("Counts");
        Run375259_pEM_fC[n][6]->SetXTitle("Charge (fC)");
        Run375259_pEM_fC[n][6]->SetYTitle("Counts");
        Run375259_pEM_fC[n][7]->SetXTitle("Charge (fC)");
        Run375259_pEM_fC[n][7]->SetYTitle("Counts");
        Run375259_pEM_fC[n][8]->SetXTitle("Charge (fC)");
        Run375259_pEM_fC[n][8]->SetYTitle("Counts");
        Run375259_pEM_fC[n][9]->SetXTitle("Charge (fC)");
        Run375259_pEM_fC[n][9]->SetYTitle("Counts");
        Run375259_pEM_fC[n][10]->SetXTitle("Charge (fC)");
        Run375259_pEM_fC[n][10]->SetYTitle("Counts");
    }

    TCanvas *c26 = new TCanvas();
    c26->Divide(3,2);
    for (int n = 0; n < 5; n++){
        c26->cd(n+1);
        Run375259_pEM_fC[n][0]->Draw();
    }
    
    // Plot avg signal for em section for each centrality
    for (int n = 0; n < 11; n++){
        Run375259_pEM_Profile[n]->SetXTitle("X Position");
        Run375259_pEM_Profile[n]->SetYTitle("Avg Signal (fC)");
    }
    
    TCanvas *c27 = new TCanvas();
    c27->Divide(5,2);
    for (int n = 0; n < 10; n++){
        c27->cd(n+1);
        Run375259_pEM_Profile[n]->Draw("hist e");
    }

    // rpd com plot
    for (int n = 0; n < 10; n++){
        Run375259_pRPD_COM[n]->SetXTitle("X Position (cm)");
        Run375259_pRPD_COM[n]->SetYTitle("Y Position (cm)");
    }  

    TCanvas *c28 = new TCanvas();
    c28->Divide(5,2);
    for (int n = 0; n < 10; n++){
        c28->cd(n+1);
        Run375259_pRPD_COM[n]->Draw("colz");
    }

    for (int n = 0; n < 10; n++){
        pos_rpd_xprojection[n]->SetXTitle("X Position (cm)");
        pos_rpd_xprojection[n]->SetYTitle("Counts");
    }
    
    pos_rpd_xprojection[0]->SetLineColor(kRed);
    pos_rpd_xprojection[1]->SetLineColor(kBlack);
    pos_rpd_xprojection[2]->SetLineColor(kBlue);
    pos_rpd_xprojection[3]->SetLineColor(kGreen);
    pos_rpd_xprojection[4]->SetLineColor(kCyan);
    pos_rpd_xprojection[5]->SetLineColor(kYellow);
    pos_rpd_xprojection[6]->SetLineColor(kOrange);
    pos_rpd_xprojection[7]->SetLineColor(kViolet);
    pos_rpd_xprojection[8]->SetLineColor(kRainBow);
    pos_rpd_xprojection[9]->SetLineColor(kGray);
    
    TCanvas *c29 = new TCanvas();
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

    TCanvas *c30 = new TCanvas();
    c30->Divide(5,2);
    for (int n = 0; n < 10; n++){
        Run375259_pRPD_prof[n]->SetXTitle("X Position");
        Run375259_pRPD_prof[n]->SetYTitle("Avg Signal");
    }
    
    for (int n = 0; n < 10 ; n++){
        c30->cd(n+1);
        Run375259_pRPD_prof[n]->Draw("hist e");
    }

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

    TCanvas *c31 = new TCanvas();
    auto EMlegend = new TLegend(0.7,0.7,0.9,0.9);
    EMlegend->AddEntry(Run375259_pEM_COMvsCent[0], "0 - <10% Centrality", "l");
    EMlegend->AddEntry(Run375259_pEM_COMvsCent[1], "10 - <20% Centrality", "l");
    EMlegend->AddEntry(Run375259_pEM_COMvsCent[2], "20 - <30% Centrality", "l");
    EMlegend->AddEntry(Run375259_pEM_COMvsCent[3], "30 - <40% Centrality", "l");
    EMlegend->AddEntry(Run375259_pEM_COMvsCent[4], "40 - <50% Centrality", "l");
    EMlegend->AddEntry(Run375259_pEM_COMvsCent[5], "50 - <60% Centrality", "l");
    EMlegend->AddEntry(Run375259_pEM_COMvsCent[6], "60 - <70% Centrality", "l");
    EMlegend->AddEntry(Run375259_pEM_COMvsCent[7], "70 - <80% Centrality", "l");
    EMlegend->AddEntry(Run375259_pEM_COMvsCent[8], "80 - <90% Centrality", "l");
    EMlegend->AddEntry(Run375259_pEM_COMvsCent[9], "90 - <100% Centrality", "l");

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
    EMlegend->Draw();

    pEM_stack->GetXaxis()->SetTitle("X Position (cm)");
    pEM_stack->GetYaxis()->SetTitle("counts");

    TCanvas *c32 = new TCanvas();
    c32->Divide(5,2);
    for (int n = 0; n < 10; n++){
        Run375259_pEM_COMvsCent[n]->SetXTitle("X Position (cm)");
        Run375259_pEM_COMvsCent[n]->SetYTitle("Counts");
    }

    for (int n = 0; n < 10; n++){
        c32->cd(n+1);
        Run375259_pEM_COMvsCent[n]->Draw();
    }

    for (int n = 0; n < 10; n++){
        Run375259_pRPDx_vs_pEMx[n]->SetYTitle("pEM X Position (cm)");
        Run375259_pRPDx_vs_pEMx[n]->SetXTitle("pRPD X Position (cm)");
    }

    TCanvas *c33 = new TCanvas();
    c33->Divide(5,2);
    for (int n = 0; n < 10; n++){
        c33->cd(n+1);
        Run375259_pRPDx_vs_pEMx[n]->Draw("colz");
    }

    for (int n = 0; n < 10; n++){
        Run375259_pRPD_Avg_Y_Sig[n]->SetXTitle("Y Position");
        Run375259_pRPD_Avg_Y_Sig[n]->SetYTitle("Average Signal (fC)");
    }
   
    TCanvas *c34 = new TCanvas();
    c34->Divide(5,2);
    for (int n = 0; n < 10; n++){
        c34->cd(n+1);
        Run375259_pRPD_Avg_Y_Sig[n]->Draw("hist e");
    }

    for (int n = 0; n < 10; n++){
        Run375259_pRPD_HeatMap[n]->SetXTitle("X Position");
        Run375259_pRPD_HeatMap[n]->SetYTitle("Y Position");
    }

    TCanvas *c35 = new TCanvas();
    c35->Divide(5,2);
    for (int n = 0; n < 10; n++){
        c35->cd(n+1);
        Run375259_pRPD_HeatMap[n]->Draw("textcolz");
    }

    for (int n = 0; n < 10; n++){
        Run375259_pRPD_position_vstotalsignal[n]->SetXTitle("0.1 EM + HAD");
        Run375259_pRPD_position_vstotalsignal[n]->SetYTitle("pRPD Position");
    }

    TCanvas *c36 = new TCanvas();
    c36->Divide(5,2);
    for (int n = 0; n < 10; n++){
        c36->cd(n+1);
        Run375259_pRPD_position_vstotalsignal[n]->Draw("colz");
    }
    
    for (int n = 0; n < 10; n++){
       Run375259_pEM_position_vstotalsignal[n]->SetXTitle("0.1EM + HAD");
       Run375259_pEM_position_vstotalsignal[n]->SetYTitle("pos EM Position"); 
    }

    TCanvas *c37 = new TCanvas();
    c37->Divide(5,2);
    for (int n = 0; n < 10; n++){
        c37->cd(n+1);
        Run375259_pEM_position_vstotalsignal[n]->Draw("colz");
    }
    */

   /*
    // Title and Plot time slice distributions for RPD
    for (int n = 0; n < 16; n++){
        Run375259_pRPD_TS[n][0]->SetXTitle("Time Slice"); 
        Run375259_pRPD_TS[n][0]->SetYTitle("Charge (fC)"); 

        Run375259_pRPD_TS[n][1]->SetXTitle("Time Slice"); 
        Run375259_pRPD_TS[n][1]->SetYTitle("Charge (fC)");

        Run375259_pRPD_TS[n][2]->SetXTitle("Time Slice"); 
        Run375259_pRPD_TS[n][2]->SetYTitle("Charge (fC)");

        Run375259_pRPD_TS[n][3]->SetXTitle("Time Slice"); 
        Run375259_pRPD_TS[n][3]->SetYTitle("Charge (fC)");

        Run375259_pRPD_TS[n][4]->SetXTitle("Time Slice"); 
        Run375259_pRPD_TS[n][4]->SetYTitle("Charge (fC)");

        Run375259_pRPD_TS[n][5]->SetXTitle("Time Slice"); 
        Run375259_pRPD_TS[n][5]->SetYTitle("Charge (fC)");

        Run375259_pRPD_TS[n][6]->SetXTitle("Time Slice"); 
        Run375259_pRPD_TS[n][6]->SetYTitle("Charge (fC)");

        Run375259_pRPD_TS[n][7]->SetXTitle("Time Slice"); 
        Run375259_pRPD_TS[n][7]->SetYTitle("Charge (fC)");

        Run375259_pRPD_TS[n][8]->SetXTitle("Time Slice"); 
        Run375259_pRPD_TS[n][8]->SetYTitle("Charge (fC)");

        Run375259_pRPD_TS[n][9]->SetXTitle("Time Slice"); 
        Run375259_pRPD_TS[n][9]->SetYTitle("Charge (fC)");

        Run375259_pRPD_TS[n][10]->SetXTitle("Time Slice"); 
        Run375259_pRPD_TS[n][10]->SetYTitle("Charge (fC)");
    }

    TCanvas *c1 = new TCanvas();
    c1->Divide(4,4);
        for (int n = 0; n < 16; n++){
            c1->cd(n+1);
            Run375259_pRPD_TS[n][0]->Draw("hist e");
        }
    TCanvas *c2 = new TCanvas();
    c2->Divide(4,4);
        for (int n = 0; n < 16; n++){
            c2->cd(n+1);
            Run375259_pRPD_TS[n][1]->Draw("hist e");
        }
    TCanvas *c3 = new TCanvas();
    c3->Divide(4,4);
        for (int n = 0; n < 16; n++){
            c3->cd(n+1);
            Run375259_pRPD_TS[n][2]->Draw("hist e");
        }
    TCanvas *c4 = new TCanvas();
    c4->Divide(4,4);
        for (int n = 0; n < 16; n++){
            c4->cd(n+1);
            Run375259_pRPD_TS[n][3]->Draw("hist e");
        }
    TCanvas *c5 = new TCanvas();
    c5->Divide(4,4);
        for (int n = 0; n < 16; n++){
            c5->cd(n+1);
            Run375259_pRPD_TS[n][4]->Draw("hist e");
        }
    TCanvas *c6 = new TCanvas();
    c6->Divide(4,4);
        for (int n = 0; n < 16; n++){
            c6->cd(n+1);
            Run375259_pRPD_TS[n][5]->Draw("hist e");
        }
    TCanvas *c7 = new TCanvas();
    c7->Divide(4,4);
        for (int n = 0; n < 16; n++){
            c7->cd(n+1);
            Run375259_pRPD_TS[n][6]->Draw("hist e");
        }
    TCanvas *c8 = new TCanvas();
    c8->Divide(4,4);
        for (int n = 0; n < 16; n++){
            c8->cd(n+1);
            Run375259_pRPD_TS[n][7]->Draw("hist e");
        }
    TCanvas *c9 = new TCanvas();
    c9->Divide(4,4);
        for (int n = 0; n < 16; n++){
            c9->cd(n+1);
            Run375259_pRPD_TS[n][8]->Draw("hist e");
        }
    TCanvas *c10 = new TCanvas();
    c10->Divide(4,4);
        for (int n = 0; n < 16; n++){
            c10->cd(n+1);
            Run375259_pRPD_TS[n][9]->Draw("hist e");
        }
    TCanvas *c11 = new TCanvas();
    c11->Divide(4,4);
        for (int n = 0; n < 16; n++){
            c11->cd(n+1);
            Run375259_pRPD_TS[n][10]->Draw("hist e");
        }
    
    // title and draw all rpd ts ratios
    for (int n = 0; n < 16; n++){
        Run375259_pRPD_TSratio[n][0]->SetXTitle("Ratio of TS2 to TS3"); 
        Run375259_pRPD_TSratio[n][0]->SetYTitle("Counts"); 

        Run375259_pRPD_TSratio[n][1]->SetXTitle("Ratio of TS2 to TS3"); 
        Run375259_pRPD_TSratio[n][1]->SetYTitle("Counts"); 

        Run375259_pRPD_TSratio[n][2]->SetXTitle("Ratio of TS2 to TS3"); 
        Run375259_pRPD_TSratio[n][2]->SetYTitle("Counts"); 

        Run375259_pRPD_TSratio[n][3]->SetXTitle("Ratio of TS2 to TS3"); 
        Run375259_pRPD_TSratio[n][3]->SetYTitle("Counts"); 

        Run375259_pRPD_TSratio[n][4]->SetXTitle("Ratio of TS2 to TS3"); 
        Run375259_pRPD_TSratio[n][4]->SetYTitle("Counts"); 

        Run375259_pRPD_TSratio[n][5]->SetXTitle("Ratio of TS2 to TS3"); 
        Run375259_pRPD_TSratio[n][5]->SetYTitle("Counts"); 

        Run375259_pRPD_TSratio[n][6]->SetXTitle("Ratio of TS2 to TS3"); 
        Run375259_pRPD_TSratio[n][6]->SetYTitle("Counts"); 

        Run375259_pRPD_TSratio[n][7]->SetXTitle("Ratio of TS2 to TS3"); 
        Run375259_pRPD_TSratio[n][7]->SetYTitle("Counts"); 

        Run375259_pRPD_TSratio[n][8]->SetXTitle("Ratio of TS2 to TS3"); 
        Run375259_pRPD_TSratio[n][8]->SetYTitle("Counts"); 

        Run375259_pRPD_TSratio[n][9]->SetXTitle("Ratio of TS2 to TS3"); 
        Run375259_pRPD_TSratio[n][9]->SetYTitle("Counts"); 

        Run375259_pRPD_TSratio[n][10]->SetXTitle("Ratio of TS2 to TS3"); 
        Run375259_pRPD_TSratio[n][10]->SetYTitle("Counts"); 
    }

    TCanvas *c12 = new TCanvas();
    c12->Divide(4,4);
        for (int n = 0; n < 16; n++){
            c12->cd(n+1);
            Run375259_pRPD_TSratio[n][0]->Draw();
        }
    TCanvas *c13 = new TCanvas();
    c13->Divide(4,4);
        for (int n = 0; n < 16; n++){
            c13->cd(n+1);
            Run375259_pRPD_TSratio[n][1]->Draw();
        }
    TCanvas *c14 = new TCanvas();
    c14->Divide(4,4);
        for (int n = 0; n < 16; n++){
            c14->cd(n+1);
            Run375259_pRPD_TSratio[n][2]->Draw();
        }
    TCanvas *c15 = new TCanvas();
    c15->Divide(4,4);
        for (int n = 0; n < 16; n++){
            c15->cd(n+1);
            Run375259_pRPD_TSratio[n][3]->Draw();
        }
    TCanvas *c16 = new TCanvas();
    c16->Divide(4,4);
        for (int n = 0; n < 16; n++){
            c16->cd(n+1);
            Run375259_pRPD_TSratio[n][4]->Draw();
        }
    TCanvas *c17 = new TCanvas();
    c17->Divide(4,4);
        for (int n = 0; n < 16; n++){
            c17->cd(n+1);
            Run375259_pRPD_TSratio[n][5]->Draw();
        }
    TCanvas *c18 = new TCanvas();
    c18->Divide(4,4);
        for (int n = 0; n < 16; n++){
            c18->cd(n+1);
            Run375259_pRPD_TSratio[n][6]->Draw();
        }
    TCanvas *c19 = new TCanvas();
    c19->Divide(4,4);
        for (int n = 0; n < 16; n++){
            c19->cd(n+1);
            Run375259_pRPD_TSratio[n][7]->Draw();
        }
    TCanvas *c20 = new TCanvas();
    c20->Divide(4,4);
        for (int n = 0; n < 16; n++){
            c20->cd(n+1);
            Run375259_pRPD_TSratio[n][8]->Draw();
        }
    TCanvas *c21 = new TCanvas();
    c21->Divide(4,4);
        for (int n = 0; n < 16; n++){
            c21->cd(n+1);
            Run375259_pRPD_TSratio[n][9]->Draw();
        }
    TCanvas *c22 = new TCanvas();
    c22->Divide(4,4);
        for (int n = 0; n < 16; n++){
            c22->cd(n+1);
            Run375259_pRPD_TSratio[n][10]->Draw();
        }

    for (int n = 0; n < 16; n++){
        Run375259_pRPD_fC[n][0]->SetXTitle("fC"); 
        Run375259_pRPD_fC[n][0]->SetYTitle("Counts"); 

        Run375259_pRPD_fC[n][1]->SetXTitle("fC"); 
        Run375259_pRPD_fC[n][1]->SetYTitle("Counts"); 

        Run375259_pRPD_fC[n][2]->SetXTitle("fC"); 
        Run375259_pRPD_fC[n][2]->SetYTitle("Counts"); 

        Run375259_pRPD_fC[n][3]->SetXTitle("fC"); 
        Run375259_pRPD_fC[n][3]->SetYTitle("Counts"); 

        Run375259_pRPD_fC[n][4]->SetXTitle("fC"); 
        Run375259_pRPD_fC[n][4]->SetYTitle("Counts"); 

        Run375259_pRPD_fC[n][5]->SetXTitle("fC"); 
        Run375259_pRPD_fC[n][5]->SetYTitle("Counts"); 

        Run375259_pRPD_fC[n][6]->SetXTitle("fC"); 
        Run375259_pRPD_fC[n][6]->SetYTitle("Counts"); 

        Run375259_pRPD_fC[n][7]->SetXTitle("fC"); 
        Run375259_pRPD_fC[n][7]->SetYTitle("Counts"); 

        Run375259_pRPD_fC[n][8]->SetXTitle("fC"); 
        Run375259_pRPD_fC[n][8]->SetYTitle("Counts"); 

        Run375259_pRPD_fC[n][9]->SetXTitle("fC"); 
        Run375259_pRPD_fC[n][9]->SetYTitle("Counts"); 

        Run375259_pRPD_fC[n][10]->SetXTitle("fC"); 
        Run375259_pRPD_fC[n][10]->SetYTitle("Counts"); 
    }

    TCanvas *c23 = new TCanvas();
    c23->Divide(4,4);
    for (int n = 0; n < 16; n++)
    {
    c23->cd(n+1);  
    Run375259_pRPD_fC[n][0]->Draw();
    }

    TCanvas *c24 = new TCanvas();
    c24->Divide(4,4);
    for (int n = 0; n < 16; n++)
    {
    c24->cd(n+1);  
    Run375259_pRPD_fC[n][1]->Draw();
    }

    TCanvas *c25 = new TCanvas();
    c25->Divide(4,4);
    for (int n = 0; n < 16; n++)
    {
    c25->cd(n+1);  
    Run375259_pRPD_fC[n][2]->Draw();
    }

    TCanvas *c26 = new TCanvas();
    c26->Divide(4,4);
    for (int n = 0; n < 16; n++)
    {
    c26->cd(n+1);  
    Run375259_pRPD_fC[n][3]->Draw();
    }

    TCanvas *c27 = new TCanvas();
    c27->Divide(4,4);
    for (int n = 0; n < 16; n++)
    {
    c27->cd(n+1);  
    Run375259_pRPD_fC[n][4]->Draw();
    }

    TCanvas *c28 = new TCanvas();
    c28->Divide(4,4);
    for (int n = 0; n < 16; n++)
    {
    c28->cd(n+1);  
    Run375259_pRPD_fC[n][5]->Draw();
    }

    TCanvas *c29 = new TCanvas();
    c29->Divide(4,4);
    for (int n = 0; n < 16; n++)
    {
    c29->cd(n+1);  
    Run375259_pRPD_fC[n][6]->Draw();
    }

    TCanvas *c30 = new TCanvas();
    c30->Divide(4,4);
    for (int n = 0; n < 16; n++)
    {
    c30->cd(n+1);  
    Run375259_pRPD_fC[n][7]->Draw();
    }

    TCanvas *c31 = new TCanvas();
    c31->Divide(4,4);
    for (int n = 0; n < 16; n++)
    {
    c31->cd(n+1);  
    Run375259_pRPD_fC[n][8]->Draw();
    }

    TCanvas *c32 = new TCanvas();
    c32->Divide(4,4);
    for (int n = 0; n < 16; n++)
    {
    c32->cd(n+1);  
    Run375259_pRPD_fC[n][9]->Draw();
    }

    TCanvas *c33 = new TCanvas();
    c33->Divide(4,4);
    for (int n = 0; n < 16; n++)
    {
    c33->cd(n+1);  
    Run375259_pRPD_fC[n][10]->Draw();
    }
    
    // title and draw pEM distributions, ratios, and fc

    for (int n = 0; n < 5; n++){
        Run375259_pEM_TS[n][0]->SetXTitle("Time Slice");
        Run375259_pEM_TS[n][0]->SetYTitle("Charge (fC)");
        Run375259_pEM_TS[n][1]->SetXTitle("Time Slice");
        Run375259_pEM_TS[n][1]->SetYTitle("Charge (fC)");
        Run375259_pEM_TS[n][2]->SetXTitle("Time Slice");
        Run375259_pEM_TS[n][2]->SetYTitle("Charge (fC)");
        Run375259_pEM_TS[n][3]->SetXTitle("Time Slice");
        Run375259_pEM_TS[n][3]->SetYTitle("Charge (fC)");
        Run375259_pEM_TS[n][4]->SetXTitle("Time Slice");
        Run375259_pEM_TS[n][4]->SetYTitle("Charge (fC)");
        Run375259_pEM_TS[n][5]->SetXTitle("Time Slice");
        Run375259_pEM_TS[n][5]->SetYTitle("Charge (fC)");
        Run375259_pEM_TS[n][6]->SetXTitle("Time Slice");
        Run375259_pEM_TS[n][6]->SetYTitle("Charge (fC)");
        Run375259_pEM_TS[n][7]->SetXTitle("Time Slice");
        Run375259_pEM_TS[n][7]->SetYTitle("Charge (fC)");
        Run375259_pEM_TS[n][8]->SetXTitle("Time Slice");
        Run375259_pEM_TS[n][8]->SetYTitle("Charge (fC)");
        Run375259_pEM_TS[n][9]->SetXTitle("Time Slice");
        Run375259_pEM_TS[n][9]->SetYTitle("Charge (fC)");
        Run375259_pEM_TS[n][10]->SetXTitle("Time Slice");
        Run375259_pEM_TS[n][10]->SetYTitle("Charge (fC)");
    }
    
    TCanvas *a1 = new TCanvas();
    a1->Divide(5,5);
    a1->cd(1);
    Run375259_pEM_TS[0][0]->Draw("hist e");
    a1->cd(2);
    Run375259_pEM_TS[1][0]->Draw("hist e");
    a1->cd(3);
    Run375259_pEM_TS[2][0]->Draw("hist e");
    a1->cd(4);
    Run375259_pEM_TS[3][0]->Draw("hist e");
    a1->cd(5);
    Run375259_pEM_TS[4][0]->Draw("hist e");
    a1->cd(6);
    Run375259_pEM_TS[0][1]->Draw("hist e");
    a1->cd(7);
    Run375259_pEM_TS[1][1]->Draw("hist e");
    a1->cd(8);
    Run375259_pEM_TS[2][1]->Draw("hist e");
    a1->cd(9);
    Run375259_pEM_TS[3][1]->Draw("hist e");
    a1->cd(10);
    Run375259_pEM_TS[4][1]->Draw("hist e");
    a1->cd(11);
    Run375259_pEM_TS[0][2]->Draw("hist e");
    a1->cd(12);
    Run375259_pEM_TS[1][2]->Draw("hist e");
    a1->cd(13);
    Run375259_pEM_TS[2][2]->Draw("hist e");
    a1->cd(14);
    Run375259_pEM_TS[3][2]->Draw("hist e");
    a1->cd(15);
    Run375259_pEM_TS[4][2]->Draw("hist e");
    a1->cd(16);
    Run375259_pEM_TS[0][3]->Draw("hist e");
    a1->cd(17);
    Run375259_pEM_TS[1][3]->Draw("hist e");
    a1->cd(18);
    Run375259_pEM_TS[2][3]->Draw("hist e");
    a1->cd(19);
    Run375259_pEM_TS[3][3]->Draw("hist e");
    a1->cd(20);
    Run375259_pEM_TS[4][3]->Draw("hist e");
    a1->cd(21);
    Run375259_pEM_TS[0][4]->Draw("hist e");
    a1->cd(22);
    Run375259_pEM_TS[1][4]->Draw("hist e");
    a1->cd(23);
    Run375259_pEM_TS[2][4]->Draw("hist e");
    a1->cd(24);
    Run375259_pEM_TS[3][4]->Draw("hist e");
    a1->cd(25);
    Run375259_pEM_TS[4][4]->Draw("hist e");

    TCanvas *a2 = new TCanvas();
    a2->Divide(5,5);
    a2->cd(1);
    Run375259_pEM_TS[0][5]->Draw("hist e");
    a2->cd(2);
    Run375259_pEM_TS[1][5]->Draw("hist e");
    a2->cd(3);
    Run375259_pEM_TS[2][5]->Draw("hist e");
    a2->cd(4);
    Run375259_pEM_TS[3][5]->Draw("hist e");
    a2->cd(5);
    Run375259_pEM_TS[4][5]->Draw("hist e");
    a2->cd(6);
    Run375259_pEM_TS[0][6]->Draw("hist e");
    a2->cd(7);
    Run375259_pEM_TS[1][6]->Draw("hist e");
    a2->cd(8);
    Run375259_pEM_TS[2][6]->Draw("hist e");
    a2->cd(9);
    Run375259_pEM_TS[3][6]->Draw("hist e");
    a2->cd(10);
    Run375259_pEM_TS[4][6]->Draw("hist e");
    a2->cd(11);
    Run375259_pEM_TS[0][7]->Draw("hist e");
    a2->cd(12);
    Run375259_pEM_TS[1][7]->Draw("hist e");
    a2->cd(13);
    Run375259_pEM_TS[2][7]->Draw("hist e");
    a2->cd(14);
    Run375259_pEM_TS[3][7]->Draw("hist e");
    a2->cd(15);
    Run375259_pEM_TS[4][7]->Draw("hist e");
    a2->cd(16);
    Run375259_pEM_TS[0][8]->Draw("hist e");
    a2->cd(17);
    Run375259_pEM_TS[1][8]->Draw("hist e");
    a2->cd(18);
    Run375259_pEM_TS[2][8]->Draw("hist e");
    a2->cd(19);
    Run375259_pEM_TS[3][8]->Draw("hist e");
    a2->cd(20);
    Run375259_pEM_TS[4][8]->Draw("hist e");
    a2->cd(21);
    Run375259_pEM_TS[0][9]->Draw("hist e");
    a2->cd(22);
    Run375259_pEM_TS[1][9]->Draw("hist e");
    a2->cd(23);
    Run375259_pEM_TS[2][9]->Draw("hist e");
    a2->cd(24);
    Run375259_pEM_TS[3][9]->Draw("hist e");
    a2->cd(25);
    Run375259_pEM_TS[4][9]->Draw("hist e");

    TCanvas *a3 = new TCanvas();
    a3->Divide(3,2);
    a3->cd(1);
    Run375259_pEM_TS[0][10]->Draw("hist e");
    a3->cd(2);
    Run375259_pEM_TS[1][10]->Draw("hist e");
    a3->cd(3);
    Run375259_pEM_TS[2][10]->Draw("hist e");
    a3->cd(4);
    Run375259_pEM_TS[3][10]->Draw("hist e");
    a3->cd(5);
    Run375259_pEM_TS[4][10]->Draw("hist e");


    for (int n = 0; n < 5; n++){
        Run375259_pEM_TSratio[n][0]->SetXTitle("Ratio TS2 : TS3");
        Run375259_pEM_TSratio[n][0]->SetYTitle("Counts");
        Run375259_pEM_TSratio[n][1]->SetXTitle("Ratio TS2 : TS3");
        Run375259_pEM_TSratio[n][1]->SetYTitle("Counts");
        Run375259_pEM_TSratio[n][2]->SetXTitle("Ratio TS2 : TS3");
        Run375259_pEM_TSratio[n][2]->SetYTitle("Counts");
        Run375259_pEM_TSratio[n][3]->SetXTitle("Ratio TS2 : TS3");
        Run375259_pEM_TSratio[n][3]->SetYTitle("Counts");
        Run375259_pEM_TSratio[n][4]->SetXTitle("Ratio TS2 : TS3");
        Run375259_pEM_TSratio[n][4]->SetYTitle("Counts");
        Run375259_pEM_TSratio[n][5]->SetXTitle("Ratio TS2 : TS3");
        Run375259_pEM_TSratio[n][5]->SetYTitle("Counts");
        Run375259_pEM_TSratio[n][6]->SetXTitle("Ratio TS2 : TS3");
        Run375259_pEM_TSratio[n][6]->SetYTitle("Counts");
        Run375259_pEM_TSratio[n][7]->SetXTitle("Ratio TS2 : TS3");
        Run375259_pEM_TSratio[n][7]->SetYTitle("Counts");
        Run375259_pEM_TSratio[n][8]->SetXTitle("Ratio TS2 : TS3");
        Run375259_pEM_TSratio[n][8]->SetYTitle("Counts");
        Run375259_pEM_TSratio[n][9]->SetXTitle("Ratio TS2 : TS3");
        Run375259_pEM_TSratio[n][9]->SetYTitle("Counts");
        Run375259_pEM_TSratio[n][10]->SetXTitle("Ratio TS2 : TS3");
        Run375259_pEM_TSratio[n][10]->SetYTitle("Counts");
    }

    TCanvas *a4 = new TCanvas();
    a4->Divide(5,5);
    a4->cd(1);
    Run375259_pEM_TSratio[0][0]->Draw();
    a4->cd(2);
    Run375259_pEM_TSratio[1][0]->Draw();
    a4->cd(3);
    Run375259_pEM_TSratio[2][0]->Draw();
    a4->cd(4);
    Run375259_pEM_TSratio[3][0]->Draw();
    a4->cd(5);
    Run375259_pEM_TSratio[4][0]->Draw();
    a4->cd(6);
    Run375259_pEM_TSratio[0][1]->Draw();
    a4->cd(7);
    Run375259_pEM_TSratio[1][1]->Draw();
    a4->cd(8);
    Run375259_pEM_TSratio[2][1]->Draw();
    a4->cd(9);
    Run375259_pEM_TSratio[3][1]->Draw();
    a4->cd(10);
    Run375259_pEM_TSratio[4][1]->Draw();
    a4->cd(11);
    Run375259_pEM_TSratio[0][2]->Draw();
    a4->cd(12);
    Run375259_pEM_TSratio[1][2]->Draw();
    a4->cd(13);
    Run375259_pEM_TSratio[2][2]->Draw();
    a4->cd(14);
    Run375259_pEM_TSratio[3][2]->Draw();
    a4->cd(15);
    Run375259_pEM_TSratio[4][2]->Draw();
    a4->cd(16);
    Run375259_pEM_TSratio[0][3]->Draw();
    a4->cd(17);
    Run375259_pEM_TSratio[1][3]->Draw();
    a4->cd(18);
    Run375259_pEM_TSratio[2][3]->Draw();
    a4->cd(19);
    Run375259_pEM_TSratio[3][3]->Draw();
    a4->cd(20);
    Run375259_pEM_TSratio[4][3]->Draw();
    a4->cd(21);
    Run375259_pEM_TSratio[0][4]->Draw();
    a4->cd(22);
    Run375259_pEM_TSratio[1][4]->Draw();
    a4->cd(23);
    Run375259_pEM_TSratio[2][4]->Draw();
    a4->cd(24);
    Run375259_pEM_TSratio[3][4]->Draw();
    a4->cd(25);
    Run375259_pEM_TSratio[4][4]->Draw();

    TCanvas *a5 = new TCanvas();
    a5->Divide(5,5);
    a5->cd(1);
    Run375259_pEM_TSratio[0][5]->Draw();
    a5->cd(2);
    Run375259_pEM_TSratio[1][5]->Draw();
    a5->cd(3);
    Run375259_pEM_TSratio[2][5]->Draw();
    a5->cd(4);
    Run375259_pEM_TSratio[3][5]->Draw();
    a5->cd(5);
    Run375259_pEM_TSratio[4][5]->Draw();
    a5->cd(6);
    Run375259_pEM_TSratio[0][6]->Draw();
    a5->cd(7);
    Run375259_pEM_TSratio[1][6]->Draw();
    a5->cd(8);
    Run375259_pEM_TSratio[2][6]->Draw();
    a5->cd(9);
    Run375259_pEM_TSratio[3][6]->Draw();
    a5->cd(10);
    Run375259_pEM_TSratio[4][6]->Draw();
    a5->cd(11);
    Run375259_pEM_TSratio[0][7]->Draw();
    a5->cd(12);
    Run375259_pEM_TSratio[1][7]->Draw();
    a5->cd(13);
    Run375259_pEM_TSratio[2][7]->Draw();
    a5->cd(14);
    Run375259_pEM_TSratio[3][7]->Draw();
    a5->cd(15);
    Run375259_pEM_TSratio[4][7]->Draw();
    a5->cd(16);
    Run375259_pEM_TSratio[0][8]->Draw();
    a5->cd(17);
    Run375259_pEM_TSratio[1][8]->Draw();
    a5->cd(18);
    Run375259_pEM_TSratio[2][8]->Draw();
    a5->cd(19);
    Run375259_pEM_TSratio[3][8]->Draw();
    a5->cd(20);
    Run375259_pEM_TSratio[4][8]->Draw();
    a5->cd(21);
    Run375259_pEM_TSratio[0][9]->Draw();
    a5->cd(22);
    Run375259_pEM_TSratio[1][9]->Draw();
    a5->cd(23);
    Run375259_pEM_TSratio[2][9]->Draw();
    a5->cd(24);
    Run375259_pEM_TSratio[3][9]->Draw();
    a5->cd(25);
    Run375259_pEM_TSratio[4][9]->Draw();

    TCanvas *a6 = new TCanvas();
    a6->Divide(3,2);
    a6->cd(1);
    Run375259_pEM_TSratio[0][10]->Draw();
    a6->cd(2);
    Run375259_pEM_TSratio[1][10]->Draw();
    a6->cd(3);
    Run375259_pEM_TSratio[2][10]->Draw();
    a6->cd(4);
    Run375259_pEM_TSratio[3][10]->Draw();
    a6->cd(5);
    Run375259_pEM_TSratio[4][10]->Draw();

    for (int n = 0; n < 5; n++){
        Run375259_pEM_fC[n][0]->SetXTitle("Charge (fC)");
        Run375259_pEM_fC[n][0]->SetYTitle("Counts");
        Run375259_pEM_fC[n][1]->SetXTitle("Charge (fC)");
        Run375259_pEM_fC[n][1]->SetYTitle("Counts");
        Run375259_pEM_fC[n][2]->SetXTitle("Charge (fC)");
        Run375259_pEM_fC[n][2]->SetYTitle("Counts");
        Run375259_pEM_fC[n][3]->SetXTitle("Charge (fC)");
        Run375259_pEM_fC[n][3]->SetYTitle("Counts");
        Run375259_pEM_fC[n][4]->SetXTitle("Charge (fC)");
        Run375259_pEM_fC[n][4]->SetYTitle("Counts");
        Run375259_pEM_fC[n][5]->SetXTitle("Charge (fC)");
        Run375259_pEM_fC[n][5]->SetYTitle("Counts");
        Run375259_pEM_fC[n][6]->SetXTitle("Charge (fC)");
        Run375259_pEM_fC[n][6]->SetYTitle("Counts");
        Run375259_pEM_fC[n][7]->SetXTitle("Charge (fC)");
        Run375259_pEM_fC[n][7]->SetYTitle("Counts");
        Run375259_pEM_fC[n][8]->SetXTitle("Charge (fC)");
        Run375259_pEM_fC[n][8]->SetYTitle("Counts");
        Run375259_pEM_fC[n][9]->SetXTitle("Charge (fC)");
        Run375259_pEM_fC[n][9]->SetYTitle("Counts");
        Run375259_pEM_fC[n][10]->SetXTitle("Charge (fC)");
        Run375259_pEM_fC[n][10]->SetYTitle("Counts");
    }

    TCanvas *a7 = new TCanvas();
    a7->Divide(5,5);
    a7->cd(1);
    Run375259_pEM_fC[0][0]->Draw();
    a7->cd(2);
    Run375259_pEM_fC[1][0]->Draw();
    a7->cd(3);
    Run375259_pEM_fC[2][0]->Draw();
    a7->cd(4);
    Run375259_pEM_fC[3][0]->Draw();
    a7->cd(5);
    Run375259_pEM_fC[4][0]->Draw();
    a7->cd(6);
    Run375259_pEM_fC[0][1]->Draw();
    a7->cd(7);
    Run375259_pEM_fC[1][1]->Draw();
    a7->cd(8);
    Run375259_pEM_fC[2][1]->Draw();
    a7->cd(9);
    Run375259_pEM_fC[3][1]->Draw();
    a7->cd(10);
    Run375259_pEM_fC[4][1]->Draw();
    a7->cd(11);
    Run375259_pEM_fC[0][2]->Draw();
    a7->cd(12);
    Run375259_pEM_fC[1][2]->Draw();
    a7->cd(13);
    Run375259_pEM_fC[2][2]->Draw();
    a7->cd(14);
    Run375259_pEM_fC[3][2]->Draw();
    a7->cd(15);
    Run375259_pEM_fC[4][2]->Draw();
    a7->cd(16);
    Run375259_pEM_fC[0][3]->Draw();
    a7->cd(17);
    Run375259_pEM_fC[1][3]->Draw();
    a7->cd(18);
    Run375259_pEM_fC[2][3]->Draw();
    a7->cd(19);
    Run375259_pEM_fC[3][3]->Draw();
    a7->cd(20);
    Run375259_pEM_fC[4][3]->Draw();
    a7->cd(21);
    Run375259_pEM_fC[0][4]->Draw();
    a7->cd(22);
    Run375259_pEM_fC[1][4]->Draw();
    a7->cd(23);
    Run375259_pEM_fC[2][4]->Draw();
    a7->cd(24);
    Run375259_pEM_fC[3][4]->Draw();
    a7->cd(25);
    Run375259_pEM_fC[4][4]->Draw();

    TCanvas *a8 = new TCanvas();
    a8->Divide(5,5);
    a8->cd(1);
    Run375259_pEM_fC[0][5]->Draw();
    a8->cd(2);
    Run375259_pEM_fC[1][5]->Draw();
    a8->cd(3);
    Run375259_pEM_fC[2][5]->Draw();
    a8->cd(4);
    Run375259_pEM_fC[3][5]->Draw();
    a8->cd(5);
    Run375259_pEM_fC[4][5]->Draw();
    a8->cd(6);
    Run375259_pEM_fC[0][6]->Draw();
    a8->cd(7);
    Run375259_pEM_fC[1][6]->Draw();
    a8->cd(8);
    Run375259_pEM_fC[2][6]->Draw();
    a8->cd(9);
    Run375259_pEM_fC[3][6]->Draw();
    a8->cd(10);
    Run375259_pEM_fC[4][6]->Draw();
    a8->cd(11);
    Run375259_pEM_fC[0][7]->Draw();
    a8->cd(12);
    Run375259_pEM_fC[1][7]->Draw();
    a8->cd(13);
    Run375259_pEM_fC[2][7]->Draw();
    a8->cd(14);
    Run375259_pEM_fC[3][7]->Draw();
    a8->cd(15);
    Run375259_pEM_fC[4][7]->Draw();
    a8->cd(16);
    Run375259_pEM_fC[0][8]->Draw();
    a8->cd(17);
    Run375259_pEM_fC[1][8]->Draw();
    a8->cd(18);
    Run375259_pEM_fC[2][8]->Draw();
    a8->cd(19);
    Run375259_pEM_fC[3][8]->Draw();
    a8->cd(20);
    Run375259_pEM_fC[4][8]->Draw();
    a8->cd(21);
    Run375259_pEM_fC[0][9]->Draw();
    a8->cd(22);
    Run375259_pEM_fC[1][9]->Draw();
    a8->cd(23);
    Run375259_pEM_fC[2][9]->Draw();
    a8->cd(24);
    Run375259_pEM_fC[3][9]->Draw();
    a8->cd(25);
    Run375259_pEM_fC[4][9]->Draw();

    TCanvas *a9 = new TCanvas();
    a9->Divide(3,2);
    a9->cd(1);
    Run375259_pEM_fC[0][10]->Draw();
    a9->cd(2);
    Run375259_pEM_fC[1][10]->Draw();
    a9->cd(3);
    Run375259_pEM_fC[2][10]->Draw();
    a9->cd(4);
    Run375259_pEM_fC[3][10]->Draw();
    a9->cd(5);
    Run375259_pEM_fC[4][10]->Draw();

    // Plot avg signal for em section for each centrality
    for (int n = 0; n < 11; n++){
        Run375259_pEM_Profile[n]->SetXTitle("X Position");
        Run375259_pEM_Profile[n]->SetYTitle("Avg Signal (fC)");
    }
    
    TCanvas *c27 = new TCanvas();
    c27->Divide(5,2);
    for (int n = 0; n < 10; n++){
        c27->cd(n+1);
        Run375259_pEM_Profile[n]->Draw("hist e");
    }

    // rpd com plot
    for (int n = 0; n < 10; n++){
        Run375259_pRPD_COM[n]->SetXTitle("X Position (cm)");
        Run375259_pRPD_COM[n]->SetYTitle("Y Position (cm)");
    }  

    TCanvas *c28 = new TCanvas();
    c28->Divide(5,2);
    for (int n = 0; n < 10; n++){
        c28->cd(n+1);
        Run375259_pRPD_COM[n]->Draw("colz");
    }

    for (int n = 0; n < 10; n++){
        pos_rpd_xprojection[n]->SetXTitle("X Position (cm)");
        pos_rpd_xprojection[n]->SetYTitle("Counts");
    }
    
    pos_rpd_xprojection[0]->SetLineColor(kRed);
    pos_rpd_xprojection[1]->SetLineColor(kBlack);
    pos_rpd_xprojection[2]->SetLineColor(kBlue);
    pos_rpd_xprojection[3]->SetLineColor(kGreen);
    pos_rpd_xprojection[4]->SetLineColor(kCyan);
    pos_rpd_xprojection[5]->SetLineColor(kYellow);
    pos_rpd_xprojection[6]->SetLineColor(kOrange);
    pos_rpd_xprojection[7]->SetLineColor(kViolet);
    pos_rpd_xprojection[8]->SetLineColor(kRainBow);
    pos_rpd_xprojection[9]->SetLineColor(kGray);
    
    TCanvas *c29 = new TCanvas();
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

    TCanvas *c30 = new TCanvas();
    c30->Divide(5,2);
    for (int n = 0; n < 10; n++){
        Run375259_pRPD_prof[n]->SetXTitle("X Position");
        Run375259_pRPD_prof[n]->SetYTitle("Avg Signal");
    }
    
    for (int n = 0; n < 10 ; n++){
        c30->cd(n+1);
        Run375259_pRPD_prof[n]->Draw("hist e");
    }

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

    TCanvas *c31 = new TCanvas();
    auto EMlegend = new TLegend(0.7,0.7,0.9,0.9);
    EMlegend->AddEntry(Run375259_pEM_COMvsCent[0], "0 - <10% Centrality", "l");
    EMlegend->AddEntry(Run375259_pEM_COMvsCent[1], "10 - <20% Centrality", "l");
    EMlegend->AddEntry(Run375259_pEM_COMvsCent[2], "20 - <30% Centrality", "l");
    EMlegend->AddEntry(Run375259_pEM_COMvsCent[3], "30 - <40% Centrality", "l");
    EMlegend->AddEntry(Run375259_pEM_COMvsCent[4], "40 - <50% Centrality", "l");
    EMlegend->AddEntry(Run375259_pEM_COMvsCent[5], "50 - <60% Centrality", "l");
    EMlegend->AddEntry(Run375259_pEM_COMvsCent[6], "60 - <70% Centrality", "l");
    EMlegend->AddEntry(Run375259_pEM_COMvsCent[7], "70 - <80% Centrality", "l");
    EMlegend->AddEntry(Run375259_pEM_COMvsCent[8], "80 - <90% Centrality", "l");
    EMlegend->AddEntry(Run375259_pEM_COMvsCent[9], "90 - <100% Centrality", "l");

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
    EMlegend->Draw();

    pEM_stack->GetXaxis()->SetTitle("X Position (cm)");
    pEM_stack->GetYaxis()->SetTitle("counts");

    TCanvas *c32 = new TCanvas();
    c32->Divide(5,2);
    for (int n = 0; n < 10; n++){
        Run375259_pEM_COMvsCent[n]->SetXTitle("X Position (cm)");
        Run375259_pEM_COMvsCent[n]->SetYTitle("Counts");
    }

    for (int n = 0; n < 10; n++){
        c32->cd(n+1);
        Run375259_pEM_COMvsCent[n]->Draw();
    }

    for (int n = 0; n < 10; n++){
        Run375259_pRPDx_vs_pEMx[n]->SetYTitle("pEM X Position (cm)");
        Run375259_pRPDx_vs_pEMx[n]->SetXTitle("pRPD X Position (cm)");
    }

    TCanvas *c33 = new TCanvas();
    c33->Divide(5,2);
    for (int n = 0; n < 10; n++){
        c33->cd(n+1);
        Run375259_pRPDx_vs_pEMx[n]->Draw("colz");
    }

    for (int n = 0; n < 10; n++){
        Run375259_pRPD_Avg_Y_Sig[n]->SetXTitle("Y Position");
        Run375259_pRPD_Avg_Y_Sig[n]->SetYTitle("Average Signal (fC)");
    }
   
    TCanvas *c34 = new TCanvas();
    c34->Divide(5,2);
    for (int n = 0; n < 10; n++){
        c34->cd(n+1);
        Run375259_pRPD_Avg_Y_Sig[n]->Draw("hist e");
    }

    for (int n = 0; n < 10; n++){
        Run375259_pRPD_HeatMap[n]->SetXTitle("X Position");
        Run375259_pRPD_HeatMap[n]->SetYTitle("Y Position");
    }

    TCanvas *c35 = new TCanvas();
    c35->Divide(5,2);
    for (int n = 0; n < 10; n++){
        c35->cd(n+1);
        Run375259_pRPD_HeatMap[n]->Draw("textcolz");
    }

    for (int n = 0; n < 10; n++){
        Run375259_pRPD_position_vstotalsignal[n]->SetXTitle("0.1 EM + HAD");
        Run375259_pRPD_position_vstotalsignal[n]->SetYTitle("pRPD Position");
    }

    TCanvas *c36 = new TCanvas();
    c36->Divide(5,2);
    for (int n = 0; n < 10; n++){
        c36->cd(n+1);
        Run375259_pRPD_position_vstotalsignal[n]->Draw("colz");
    }
    
    for (int n = 0; n < 10; n++){
       Run375259_pEM_position_vstotalsignal[n]->SetXTitle("0.1EM + HAD");
       Run375259_pEM_position_vstotalsignal[n]->SetYTitle("pos EM Position"); 
    }

    TCanvas *c37 = new TCanvas();
    c37->Divide(5,2);
    for (int n = 0; n < 10; n++){
        c37->cd(n+1);
        Run375259_pEM_position_vstotalsignal[n]->Draw("colz");
    }
    */


















   /*
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
                                        pEM_signal[0][0] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[1][0] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[2][0] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[3][0] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[4][0] = TS2[n]; //- TS1[n];
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
                                pHAD_signal[0][0] = TS2[n]; //- TS1[n];
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
                                pHAD_signal[1][0] = TS2[n]; //- TS1[n];
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
                                pHAD_signal[2][0] = TS2[n]; //- TS1[n];
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
                                pHAD_signal[3][0] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[0][1] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[1][1] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[2][1] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[3][1] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[4][1] = TS2[n]; //- TS1[n];
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
                                pHAD_signal[0][1] = TS2[n]; //- TS1[n];
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
                                pHAD_signal[1][1] = TS2[n]; //- TS1[n];
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
                                pHAD_signal[2][1] = TS2[n]; //- TS1[n];
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
                                pHAD_signal[3][1] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[0][2] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[1][2] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[2][2] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[3][2] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[4][2] = TS2[n]; //- TS1[n];
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
                                pHAD_signal[0][2] = TS2[n]; //- TS1[n];
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
                                pHAD_signal[1][2] = TS2[n]; //- TS1[n];
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
                                pHAD_signal[2][2] = TS2[n]; //- TS1[n];
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
                                pHAD_signal[3][2] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[0][3] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[1][3] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[2][3] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[3][3] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[4][3] = TS2[n]; //- TS1[n];
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
                                pHAD_signal[0][3] = TS2[n]; //- TS1[n];
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
                                pHAD_signal[1][3] = TS2[n]; //- TS1[n];
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
                                pHAD_signal[2][3] = TS2[n]; //- TS1[n];
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
                                pHAD_signal[3][3] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[0][4] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[1][4] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[2][4] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[3][4] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[4][4] = TS2[n]; //- TS1[n];
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
                                pHAD_signal[0][4] = TS2[n]; //- TS1[n];
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
                                pHAD_signal[1][4] = TS2[n]; //- TS1[n];
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
                                pHAD_signal[2][4] = TS2[n]; //- TS1[n];
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
                                pHAD_signal[3][4] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[0][5] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[1][5] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[2][5] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[3][5] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[4][5] = TS2[n]; //- TS1[n];
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
                                pHAD_signal[0][5] = TS2[n]; //- TS1[n];
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
                                pHAD_signal[1][5] = TS2[n]; //- TS1[n];
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
                                pHAD_signal[2][5] = TS2[n]; //- TS1[n];
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
                                pHAD_signal[3][5] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[0][6] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[1][6] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[2][6] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[3][6] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[4][6] = TS2[n]; //- TS1[n];
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
                                pHAD_signal[0][6] = TS2[n]; //- TS1[n];
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
                                pHAD_signal[1][6] = TS2[n]; //- TS1[n];
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
                                pHAD_signal[2][6] = TS2[n]; //- TS1[n];
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
                                pHAD_signal[3][6] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[0][7] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[1][7] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[2][7] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[3][7] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[4][7] = TS2[n]; //- TS1[n];
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
                                pHAD_signal[0][7] = TS2[n]; //- TS1[n];
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
                                pHAD_signal[1][7] = TS2[n]; //- TS1[n];
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
                                pHAD_signal[2][7] = TS2[n]; //- TS1[n];
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
                                pHAD_signal[3][7] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[0][8] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[1][8] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[2][8] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[3][8] = TS2[n]; //- TS1[n];
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
                                        pEM_signal[4][8] = TS2[n]; //- TS1[n];
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
                                pHAD_signal[0][8] = TS2[n]; //- TS1[n];
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
                                pHAD_signal[1][8] = TS2[n]; //- TS1[n];
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
                                pHAD_signal[2][8] = TS2[n]; //- TS1[n];
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
                                pHAD_signal[3][8] = TS2[n]; //- TS1[n];
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
                } // end of hibin 160 to 180*/














                /* if (zside[n] == 1 && section[n] == 4) {
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

                                    if (pRPD_ratio[10][9] < 1.7){
                                        pRPD_JunkTS[10]->Fill(0.0,TS0[n]);
                                        pRPD_JunkTS[10]->Fill(1.0,TS1[n]);
                                        pRPD_JunkTS[10]->Fill(2.0,TS2[n]);
                                        pRPD_JunkTS[10]->Fill(3.0,TS3[n]);
                                        pRPD_JunkTS[10]->Fill(4.0,TS4[n]);
                                        pRPD_JunkTS[10]->Fill(5.0,TS5[n]);
                                    }
                                    if (pRPD_ratio[10][9] > 1.7){
                                        pRPD_GoodTS[10]->Fill(0.0,TS0[n]);
                                        pRPD_GoodTS[10]->Fill(1.0,TS1[n]);
                                        pRPD_GoodTS[10]->Fill(2.0,TS2[n]);
                                        pRPD_GoodTS[10]->Fill(3.0,TS3[n]);
                                        pRPD_GoodTS[10]->Fill(4.0,TS4[n]);
                                        pRPD_GoodTS[10]->Fill(5.0,TS5[n]);
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
                                    if (pRPD_ratio[6][9] < 1.7){
                                        pRPD_JunkTS[6]->Fill(0.0,TS0[n]);
                                        pRPD_JunkTS[6]->Fill(1.0,TS1[n]);
                                        pRPD_JunkTS[6]->Fill(2.0,TS2[n]);
                                        pRPD_JunkTS[6]->Fill(3.0,TS3[n]);
                                        pRPD_JunkTS[6]->Fill(4.0,TS4[n]);
                                        pRPD_JunkTS[6]->Fill(5.0,TS5[n]);
                                    }
                                    if (pRPD_ratio[6][9] > 1.7){
                                        pRPD_GoodTS[6]->Fill(0.0,TS0[n]);
                                        pRPD_GoodTS[6]->Fill(1.0,TS1[n]);
                                        pRPD_GoodTS[6]->Fill(2.0,TS2[n]);
                                        pRPD_GoodTS[6]->Fill(3.0,TS3[n]);
                                        pRPD_GoodTS[6]->Fill(4.0,TS4[n]);
                                        pRPD_GoodTS[6]->Fill(5.0,TS5[n]);
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
                                    if (pRPD_ratio[2][9] < 1.7){
                                        pRPD_JunkTS[2]->Fill(0.0,TS0[n]);
                                        pRPD_JunkTS[2]->Fill(1.0,TS1[n]);
                                        pRPD_JunkTS[2]->Fill(2.0,TS2[n]);
                                        pRPD_JunkTS[2]->Fill(3.0,TS3[n]);
                                        pRPD_JunkTS[2]->Fill(4.0,TS4[n]);
                                        pRPD_JunkTS[2]->Fill(5.0,TS5[n]);
                                    }
                                    if (pRPD_ratio[2][9] > 1.7){
                                        pRPD_GoodTS[2]->Fill(0.0,TS0[n]);
                                        pRPD_GoodTS[2]->Fill(1.0,TS1[n]);
                                        pRPD_GoodTS[2]->Fill(2.0,TS2[n]);
                                        pRPD_GoodTS[2]->Fill(3.0,TS3[n]);
                                        pRPD_GoodTS[2]->Fill(4.0,TS4[n]);
                                        pRPD_GoodTS[2]->Fill(5.0,TS5[n]);
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
                                    if (pRPD_ratio[14][9] < 1.7){
                                        pRPD_JunkTS[14]->Fill(0.0,TS0[n]);
                                        pRPD_JunkTS[14]->Fill(1.0,TS1[n]);
                                        pRPD_JunkTS[14]->Fill(2.0,TS2[n]);
                                        pRPD_JunkTS[14]->Fill(3.0,TS3[n]);
                                        pRPD_JunkTS[14]->Fill(4.0,TS4[n]);
                                        pRPD_JunkTS[14]->Fill(5.0,TS5[n]);
                                    }
                                    if (pRPD_ratio[14][9] > 1.7){
                                        pRPD_GoodTS[14]->Fill(0.0,TS0[n]);
                                        pRPD_GoodTS[14]->Fill(1.0,TS1[n]);
                                        pRPD_GoodTS[14]->Fill(2.0,TS2[n]);
                                        pRPD_GoodTS[14]->Fill(3.0,TS3[n]);
                                        pRPD_GoodTS[14]->Fill(4.0,TS4[n]);
                                        pRPD_GoodTS[14]->Fill(5.0,TS5[n]);
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
                                    if (pRPD_ratio[11][9] < 1.7){
                                        pRPD_JunkTS[11]->Fill(0.0,TS0[n]);
                                        pRPD_JunkTS[11]->Fill(1.0,TS1[n]);
                                        pRPD_JunkTS[11]->Fill(2.0,TS2[n]);
                                        pRPD_JunkTS[11]->Fill(3.0,TS3[n]);
                                        pRPD_JunkTS[11]->Fill(4.0,TS4[n]);
                                        pRPD_JunkTS[11]->Fill(5.0,TS5[n]);
                                    }
                                    if (pRPD_ratio[11][9] > 1.7){
                                        pRPD_GoodTS[11]->Fill(0.0,TS0[n]);
                                        pRPD_GoodTS[11]->Fill(1.0,TS1[n]);
                                        pRPD_GoodTS[11]->Fill(2.0,TS2[n]);
                                        pRPD_GoodTS[11]->Fill(3.0,TS3[n]);
                                        pRPD_GoodTS[11]->Fill(4.0,TS4[n]);
                                        pRPD_GoodTS[11]->Fill(5.0,TS5[n]);
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
                                    if (pRPD_ratio[7][9] < 1.7){
                                        pRPD_JunkTS[7]->Fill(0.0,TS0[n]);
                                        pRPD_JunkTS[7]->Fill(1.0,TS1[n]);
                                        pRPD_JunkTS[7]->Fill(2.0,TS2[n]);
                                        pRPD_JunkTS[7]->Fill(3.0,TS3[n]);
                                        pRPD_JunkTS[7]->Fill(4.0,TS4[n]);
                                        pRPD_JunkTS[7]->Fill(5.0,TS5[n]);
                                    }
                                    if (pRPD_ratio[7][9] > 1.7){
                                        pRPD_GoodTS[7]->Fill(0.0,TS0[n]);
                                        pRPD_GoodTS[7]->Fill(1.0,TS1[n]);
                                        pRPD_GoodTS[7]->Fill(2.0,TS2[n]);
                                        pRPD_GoodTS[7]->Fill(3.0,TS3[n]);
                                        pRPD_GoodTS[7]->Fill(4.0,TS4[n]);
                                        pRPD_GoodTS[7]->Fill(5.0,TS5[n]);
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
                                    if (pRPD_ratio[3][9] < 1.7){
                                        pRPD_JunkTS[3]->Fill(0.0,TS0[n]);
                                        pRPD_JunkTS[3]->Fill(1.0,TS1[n]);
                                        pRPD_JunkTS[3]->Fill(2.0,TS2[n]);
                                        pRPD_JunkTS[3]->Fill(3.0,TS3[n]);
                                        pRPD_JunkTS[3]->Fill(4.0,TS4[n]);
                                        pRPD_JunkTS[3]->Fill(5.0,TS5[n]);
                                    }
                                    if (pRPD_ratio[3][9] > 1.7){
                                        pRPD_GoodTS[3]->Fill(0.0,TS0[n]);
                                        pRPD_GoodTS[3]->Fill(1.0,TS1[n]);
                                        pRPD_GoodTS[3]->Fill(2.0,TS2[n]);
                                        pRPD_GoodTS[3]->Fill(3.0,TS3[n]);
                                        pRPD_GoodTS[3]->Fill(4.0,TS4[n]);
                                        pRPD_GoodTS[3]->Fill(5.0,TS5[n]);
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
                                    if (pRPD_ratio[15][9] < 1.7){
                                        pRPD_JunkTS[15]->Fill(0.0,TS0[n]);
                                        pRPD_JunkTS[15]->Fill(1.0,TS1[n]);
                                        pRPD_JunkTS[15]->Fill(2.0,TS2[n]);
                                        pRPD_JunkTS[15]->Fill(3.0,TS3[n]);
                                        pRPD_JunkTS[15]->Fill(4.0,TS4[n]);
                                        pRPD_JunkTS[15]->Fill(5.0,TS5[n]);
                                    }
                                    if (pRPD_ratio[15][9] > 1.7){
                                        pRPD_GoodTS[15]->Fill(0.0,TS0[n]);
                                        pRPD_GoodTS[15]->Fill(1.0,TS1[n]);
                                        pRPD_GoodTS[15]->Fill(2.0,TS2[n]);
                                        pRPD_GoodTS[15]->Fill(3.0,TS3[n]);
                                        pRPD_GoodTS[15]->Fill(4.0,TS4[n]);
                                        pRPD_GoodTS[15]->Fill(5.0,TS5[n]);
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
                                    if (pRPD_ratio[4][9] < 1.7){
                                        pRPD_JunkTS[4]->Fill(0.0,TS0[n]);
                                        pRPD_JunkTS[4]->Fill(1.0,TS1[n]);
                                        pRPD_JunkTS[4]->Fill(2.0,TS2[n]);
                                        pRPD_JunkTS[4]->Fill(3.0,TS3[n]);
                                        pRPD_JunkTS[4]->Fill(4.0,TS4[n]);
                                        pRPD_JunkTS[4]->Fill(5.0,TS5[n]);
                                    }
                                    if (pRPD_ratio[4][9] > 1.7){
                                        pRPD_GoodTS[4]->Fill(0.0,TS0[n]);
                                        pRPD_GoodTS[4]->Fill(1.0,TS1[n]);
                                        pRPD_GoodTS[4]->Fill(2.0,TS2[n]);
                                        pRPD_GoodTS[4]->Fill(3.0,TS3[n]);
                                        pRPD_GoodTS[4]->Fill(4.0,TS4[n]);
                                        pRPD_GoodTS[4]->Fill(5.0,TS5[n]);
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
                                    if (pRPD_ratio[8][9] < 1.7){
                                        pRPD_JunkTS[8]->Fill(0.0,TS0[n]);
                                        pRPD_JunkTS[8]->Fill(1.0,TS1[n]);
                                        pRPD_JunkTS[8]->Fill(2.0,TS2[n]);
                                        pRPD_JunkTS[8]->Fill(3.0,TS3[n]);
                                        pRPD_JunkTS[8]->Fill(4.0,TS4[n]);
                                        pRPD_JunkTS[8]->Fill(5.0,TS5[n]);
                                    }
                                    if (pRPD_ratio[8][9] > 1.7){
                                        pRPD_GoodTS[8]->Fill(0.0,TS0[n]);
                                        pRPD_GoodTS[8]->Fill(1.0,TS1[n]);
                                        pRPD_GoodTS[8]->Fill(2.0,TS2[n]);
                                        pRPD_GoodTS[8]->Fill(3.0,TS3[n]);
                                        pRPD_GoodTS[8]->Fill(4.0,TS4[n]);
                                        pRPD_GoodTS[8]->Fill(5.0,TS5[n]);
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
                                    if (pRPD_ratio[12][9] < 1.7){
                                        pRPD_JunkTS[12]->Fill(0.0,TS0[n]);
                                        pRPD_JunkTS[12]->Fill(1.0,TS1[n]);
                                        pRPD_JunkTS[12]->Fill(2.0,TS2[n]);
                                        pRPD_JunkTS[12]->Fill(3.0,TS3[n]);
                                        pRPD_JunkTS[12]->Fill(4.0,TS4[n]);
                                        pRPD_JunkTS[12]->Fill(5.0,TS5[n]);
                                    }
                                    if (pRPD_ratio[12][9] > 1.7){
                                        pRPD_GoodTS[12]->Fill(0.0,TS0[n]);
                                        pRPD_GoodTS[12]->Fill(1.0,TS1[n]);
                                        pRPD_GoodTS[12]->Fill(2.0,TS2[n]);
                                        pRPD_GoodTS[12]->Fill(3.0,TS3[n]);
                                        pRPD_GoodTS[12]->Fill(4.0,TS4[n]);
                                        pRPD_GoodTS[12]->Fill(5.0,TS5[n]);
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
                                    if (pRPD_ratio[0][9] < 1.7){
                                        pRPD_JunkTS[0]->Fill(0.0,TS0[n]);
                                        pRPD_JunkTS[0]->Fill(1.0,TS1[n]);
                                        pRPD_JunkTS[0]->Fill(2.0,TS2[n]);
                                        pRPD_JunkTS[0]->Fill(3.0,TS3[n]);
                                        pRPD_JunkTS[0]->Fill(4.0,TS4[n]);
                                        pRPD_JunkTS[0]->Fill(5.0,TS5[n]);
                                    }
                                    if (pRPD_ratio[0][9] > 1.7){
                                        pRPD_GoodTS[0]->Fill(0.0,TS0[n]);
                                        pRPD_GoodTS[0]->Fill(1.0,TS1[n]);
                                        pRPD_GoodTS[0]->Fill(2.0,TS2[n]);
                                        pRPD_GoodTS[0]->Fill(3.0,TS3[n]);
                                        pRPD_GoodTS[0]->Fill(4.0,TS4[n]);
                                        pRPD_GoodTS[0]->Fill(5.0,TS5[n]);
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
                                    if (pRPD_ratio[5][9] < 1.7){
                                        pRPD_JunkTS[5]->Fill(0.0,TS0[n]);
                                        pRPD_JunkTS[5]->Fill(1.0,TS1[n]);
                                        pRPD_JunkTS[5]->Fill(2.0,TS2[n]);
                                        pRPD_JunkTS[5]->Fill(3.0,TS3[n]);
                                        pRPD_JunkTS[5]->Fill(4.0,TS4[n]);
                                        pRPD_JunkTS[5]->Fill(5.0,TS5[n]);
                                    }
                                    if (pRPD_ratio[5][9] > 1.7){
                                        pRPD_GoodTS[5]->Fill(0.0,TS0[n]);
                                        pRPD_GoodTS[5]->Fill(1.0,TS1[n]);
                                        pRPD_GoodTS[5]->Fill(2.0,TS2[n]);
                                        pRPD_GoodTS[5]->Fill(3.0,TS3[n]);
                                        pRPD_GoodTS[5]->Fill(4.0,TS4[n]);
                                        pRPD_GoodTS[5]->Fill(5.0,TS5[n]);
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
                                    if (pRPD_ratio[9][9] < 1.7){
                                        pRPD_JunkTS[9]->Fill(0.0,TS0[n]);
                                        pRPD_JunkTS[9]->Fill(1.0,TS1[n]);
                                        pRPD_JunkTS[9]->Fill(2.0,TS2[n]);
                                        pRPD_JunkTS[9]->Fill(3.0,TS3[n]);
                                        pRPD_JunkTS[9]->Fill(4.0,TS4[n]);
                                        pRPD_JunkTS[9]->Fill(5.0,TS5[n]);
                                    }
                                    if (pRPD_ratio[9][9] > 1.7){
                                        pRPD_GoodTS[9]->Fill(0.0,TS0[n]);
                                        pRPD_GoodTS[9]->Fill(1.0,TS1[n]);
                                        pRPD_GoodTS[9]->Fill(2.0,TS2[n]);
                                        pRPD_GoodTS[9]->Fill(3.0,TS3[n]);
                                        pRPD_GoodTS[9]->Fill(4.0,TS4[n]);
                                        pRPD_GoodTS[9]->Fill(5.0,TS5[n]);
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
                                    if (pRPD_ratio[13][9] < 1.7){
                                        pRPD_JunkTS[13]->Fill(0.0,TS0[n]);
                                        pRPD_JunkTS[13]->Fill(1.0,TS1[n]);
                                        pRPD_JunkTS[13]->Fill(2.0,TS2[n]);
                                        pRPD_JunkTS[13]->Fill(3.0,TS3[n]);
                                        pRPD_JunkTS[13]->Fill(4.0,TS4[n]);
                                        pRPD_JunkTS[13]->Fill(5.0,TS5[n]);
                                    }
                                    if (pRPD_ratio[13][9] > 1.7){
                                        pRPD_GoodTS[13]->Fill(0.0,TS0[n]);
                                        pRPD_GoodTS[13]->Fill(1.0,TS1[n]);
                                        pRPD_GoodTS[13]->Fill(2.0,TS2[n]);
                                        pRPD_GoodTS[13]->Fill(3.0,TS3[n]);
                                        pRPD_GoodTS[13]->Fill(4.0,TS4[n]);
                                        pRPD_GoodTS[13]->Fill(5.0,TS5[n]);
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
                                    if (pRPD_ratio[1][9] < 1.7){
                                        pRPD_JunkTS[1]->Fill(0.0,TS0[n]);
                                        pRPD_JunkTS[1]->Fill(1.0,TS1[n]);
                                        pRPD_JunkTS[1]->Fill(2.0,TS2[n]);
                                        pRPD_JunkTS[1]->Fill(3.0,TS3[n]);
                                        pRPD_JunkTS[1]->Fill(4.0,TS4[n]);
                                        pRPD_JunkTS[1]->Fill(5.0,TS5[n]);
                                    }
                                    if (pRPD_ratio[1][9] > 1.7){
                                        pRPD_GoodTS[1]->Fill(0.0,TS0[n]);
                                        pRPD_GoodTS[1]->Fill(1.0,TS1[n]);
                                        pRPD_GoodTS[1]->Fill(2.0,TS2[n]);
                                        pRPD_GoodTS[1]->Fill(3.0,TS3[n]);
                                        pRPD_GoodTS[1]->Fill(4.0,TS4[n]);
                                        pRPD_GoodTS[1]->Fill(5.0,TS5[n]);
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

                                } // end of side and section*/
}