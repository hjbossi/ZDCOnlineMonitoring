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

void Run375259_PrepulseVsCent()
{
    // Create Avg Signal (fC) in TS 0 vs Centrality for pos EM (all sections, each array is for section 1 - 5 for one cent range)
    double AvgSigpEM_0to10_ts0[] = {163.024, 133.55, 272.499, 721.906, 1049.13};

    double AvgSigpEM_10to20_ts0[] = {163.089, 133.605, 276.574, 735.314, 1055.5};

    double AvgSigpEM_20to30_ts0[] = {163.26, 134.216, 275.445, 727.783, 1056.92};

    double AvgSigpEM_30to40_ts0[] = {163.368, 133.959, 274.518, 725.259, 1051.36};

    double AvgSigpEM_40to50_ts0[] = {162.727, 133.562, 274.199, 726.82, 1061.83};

    double AvgSigpEM_50to60_ts0[] = {163.098, 133.791, 274.094, 728.527, 1059.19};

    double AvgSigpEM_60to70_ts0[] = {163.291, 134.397, 274.469, 726.885, 1054.37};

    double AvgSigpEM_70to80_ts0[] = {162.813, 134.151, 274.512, 724.966, 1051.57};

    double AvgSigpEM_80to90_ts0[] = {208.372, 208.962, 398.271, 896.757, 1241.08};

    double AvgSigpEM_90to100_ts0[] = {322.106, 407.154, 808.35, 1739.59, 2236.07};

    // Create Avg Signal (fC) in TS 0 vs Centrality for pos EM
    // Each array is the evolution of each section as centrality increases

    double MidPtCentrality[] = {4.75, 14.75, 24.75, 34.75, 44.75, 54.75, 64.75, 74.75, 84.75, 94.75};

    double ex[] = {4.75, 4.75, 4.75, 4.75, 4.75, 4.75, 4.75, 4.75, 4.75, 4.75};

    double AvgSignalEMts0_Section1[] = {163.024, 163.089, 163.26, 163.368, 162.727, 163.098, 163.291, 162.813, 208.372, 322.106};

    double AvgSignalEMts0_Section2[] = {133.55, 133.605, 134.216, 133.959, 133.562, 133.791, 134.397, 134.151, 208.962, 407.154};

    double AvgSignalEMts0_Section3[] = {272.499, 276.574, 275.445, 274.518, 274.199, 274.094, 274.469, 274.512, 398.271, 808.35};

    double AvgSignalEMts0_Section4[] = {721.906, 735.314, 727.783, 725.259, 726.82, 728.527, 726.885, 724.966, 896.757, 1739.59};

    double AvgSignalEMts0_Section5[] = {1049.13, 1055.5, 1056.92, 1051.36, 1061.83, 1059.19, 1054.37, 1051.57, 1241.08, 2236.07};

    TGraphErrors *pEMs1vsCent = new TGraphErrors(10, MidPtCentrality, AvgSignalEMts0_Section1, ex, 0);
    TGraphErrors *pEMs2vsCent = new TGraphErrors(10, MidPtCentrality, AvgSignalEMts0_Section2, ex, 0);
    TGraphErrors *pEMs3vsCent = new TGraphErrors(10, MidPtCentrality, AvgSignalEMts0_Section3, ex, 0);
    TGraphErrors *pEMs4vsCent = new TGraphErrors(10, MidPtCentrality, AvgSignalEMts0_Section4, ex, 0);
    TGraphErrors *pEMs5vsCent = new TGraphErrors(10, MidPtCentrality, AvgSignalEMts0_Section5, ex, 0);

    pEMs1vsCent->SetTitle("Run 375259 pos EM Section 1 Avg Signal in TS 0 vs Centrality");

    pEMs1vsCent->GetXaxis()->SetTitle("Centrality (%)");
    pEMs1vsCent->GetYaxis()->SetTitle("Average Signal in TS 0 (fC)");
    //
    pEMs2vsCent->SetTitle("Run 375259 pos EM Section 2 Avg Signal in TS 0 vs Centrality");

    pEMs2vsCent->GetXaxis()->SetTitle("Centrality (%)");
    pEMs2vsCent->GetYaxis()->SetTitle("Average Signal in TS 0 (fC)");
    //
    pEMs3vsCent->SetTitle("Run 375259 pos EM Section 3 Avg Signal in TS 0 vs Centrality");

    pEMs3vsCent->GetXaxis()->SetTitle("Centrality (%)");
    pEMs3vsCent->GetYaxis()->SetTitle("Average Signal in TS 0 (fC)");
    //
    pEMs4vsCent->SetTitle("Run 375259 pos EM Section 4 Avg Signal in TS 0 vs Centrality");

    pEMs4vsCent->GetXaxis()->SetTitle("Centrality (%)");
    pEMs4vsCent->GetYaxis()->SetTitle("Average Signal in TS 0 (fC)");
    //
    pEMs5vsCent->SetTitle("Run 375259 pos EM Section 5 Avg Signal in TS 0 vs Centrality");

    pEMs5vsCent->GetXaxis()->SetTitle("Centrality (%)");
    pEMs5vsCent->GetYaxis()->SetTitle("Average Signal in TS 0 (fC)");

    pEMs1vsCent->SetMarkerStyle(20);
    pEMs2vsCent->SetMarkerStyle(20);
    pEMs3vsCent->SetMarkerStyle(20);
    pEMs4vsCent->SetMarkerStyle(20);
    pEMs5vsCent->SetMarkerStyle(20);

    TCanvas *c1 = new TCanvas();
    c1->Divide(3,2);
    c1->cd(1);
    pEMs1vsCent->Draw("AP");
    c1->cd(2);
    pEMs2vsCent->Draw("AP");
    c1->cd(3);
    pEMs3vsCent->Draw("AP");
    c1->cd(4);
    pEMs4vsCent->Draw("AP");
    c1->cd(5);
    pEMs5vsCent->Draw("AP");

    double AvgSignalHADts0_Section1[] = {711.063, 712.912, 713.118, 709.316, 712.498, 716.763, 711.97, 709.11, 841.874, 1595.19};

    double AvgSignalHADts0_Section2[] = {264.99, 265.985, 266.28, 264.635, 265.362, 266.947, 265.082, 264.36, 308.991, 563.097};

    double AvgSignalHADts0_Section3[] = {184.322, 184.564, 185.043, 184.435, 184.883, 185.167, 184.373, 183.831, 209.46, 344.641};

    double AvgSignalHADts0_Section4[] = {164.306, 164.573, 164.906, 164.664, 164.631, 165.329, 164.541, 164.029, 184.111, 289.216};

    TGraphErrors *pHADs1vsCent = new TGraphErrors(10, MidPtCentrality, AvgSignalHADts0_Section1, ex, 0);
    TGraphErrors *pHADs2vsCent = new TGraphErrors(10, MidPtCentrality, AvgSignalHADts0_Section2, ex, 0);
    TGraphErrors *pHADs3vsCent = new TGraphErrors(10, MidPtCentrality, AvgSignalHADts0_Section3, ex, 0);
    TGraphErrors *pHADs4vsCent = new TGraphErrors(10, MidPtCentrality, AvgSignalHADts0_Section4, ex, 0);

    pHADs1vsCent->SetTitle("Run 375259 pos HAD Section 1 Avg Signal in TS 0 vs Centrality");
    pHADs2vsCent->SetTitle("Run 375259 pos HAD Section 2 Avg Signal in TS 0 vs Centrality");
    pHADs3vsCent->SetTitle("Run 375259 pos HAD Section 3 Avg Signal in TS 0 vs Centrality");
    pHADs4vsCent->SetTitle("Run 375259 pos HAD Section 4 Avg Signal in TS 0 vs Centrality");

    pHADs1vsCent->GetXaxis()->SetTitle("Centrality (%)");
    pHADs1vsCent->GetYaxis()->SetTitle("Average Signal in TS 0 (fC)");

    pHADs2vsCent->GetXaxis()->SetTitle("Centrality (%)");
    pHADs2vsCent->GetYaxis()->SetTitle("Average Signal in TS 0 (fC)");

    pHADs3vsCent->GetXaxis()->SetTitle("Centrality (%)");
    pHADs3vsCent->GetYaxis()->SetTitle("Average Signal in TS 0 (fC)");

    pHADs4vsCent->GetXaxis()->SetTitle("Centrality (%)");
    pHADs4vsCent->GetYaxis()->SetTitle("Average Signal in TS 0 (fC)");

    pHADs1vsCent->SetMarkerStyle(20);
    pHADs2vsCent->SetMarkerStyle(20);
    pHADs3vsCent->SetMarkerStyle(20);
    pHADs4vsCent->SetMarkerStyle(20);

    TCanvas *c2 = new TCanvas();
    c2->Divide(2,2);
    c2->cd(1);
    pHADs1vsCent->Draw("AP");
    c2->cd(2);
    pHADs2vsCent->Draw("AP");
    c2->cd(3);
    pHADs3vsCent->Draw("AP");
    c2->cd(4);
    pHADs4vsCent->Draw("AP");

    double AvgSignalEMts1_Section1[] = {152.011, 149.995, 149.409, 149.654, 149.401, 150.089, 150.571, 151.253, 163.074, 245.694};

    double AvgSignalEMts1_Section2[] = {112.78, 110.655, 109.774, 109.68, 109.705, 110.196, 110.909, 111.976, 130.999, 284.897};

    double AvgSignalEMts1_Section3[] = {217.029, 218.027, 217.315, 217.172, 217.387, 217.282, 217.307, 217.996, 250.223, 526.051};

    double AvgSignalEMts1_Section4[] = {362.564, 366.02, 363.453, 363.195, 364.093, 364.87, 364.494, 363.77, 412.182, 926.379};

    double AvgSignalEMts1_Section5[] = {544.803, 547.439, 547.114, 546.185, 549.445, 548.23, 546.846, 546.94, 601.942, 1195.84};

    TGraphErrors *pEMs1vsCent2 = new TGraphErrors(10, MidPtCentrality, AvgSignalEMts1_Section1, ex, 0);
    TGraphErrors *pEMs2vsCent2 = new TGraphErrors(10, MidPtCentrality, AvgSignalEMts1_Section2, ex, 0);
    TGraphErrors *pEMs3vsCent2 = new TGraphErrors(10, MidPtCentrality, AvgSignalEMts1_Section3, ex, 0);
    TGraphErrors *pEMs4vsCent2 = new TGraphErrors(10, MidPtCentrality, AvgSignalEMts1_Section4, ex, 0);
    TGraphErrors *pEMs5vsCent2 = new TGraphErrors(10, MidPtCentrality, AvgSignalEMts1_Section5, ex, 0);

    pEMs1vsCent2->SetTitle("Run 375259 pos EM Section 1 Avg Signal in TS 1 vs Centrality");

    pEMs1vsCent2->GetXaxis()->SetTitle("Centrality (%)");
    pEMs1vsCent2->GetYaxis()->SetTitle("Average Signal in TS 1 (fC)");
    //
    pEMs2vsCent2->SetTitle("Run 375259 pos EM Section 2 Avg Signal in TS 1 vs Centrality");

    pEMs2vsCent2->GetXaxis()->SetTitle("Centrality (%)");
    pEMs2vsCent2->GetYaxis()->SetTitle("Average Signal in TS 1 (fC)");
    //
    pEMs3vsCent2->SetTitle("Run 375259 pos EM Section 3 Avg Signal in TS 1 vs Centrality");

    pEMs3vsCent2->GetXaxis()->SetTitle("Centrality (%)");
    pEMs3vsCent2->GetYaxis()->SetTitle("Average Signal in TS 1 (fC)");
    //
    pEMs4vsCent2->SetTitle("Run 375259 pos EM Section 4 Avg Signal in TS 1 vs Centrality");

    pEMs4vsCent2->GetXaxis()->SetTitle("Centrality (%)");
    pEMs4vsCent2->GetYaxis()->SetTitle("Average Signal in TS 1 (fC)");
    //
    pEMs5vsCent2->SetTitle("Run 375259 pos EM Section 5 Avg Signal in TS 1 vs Centrality");

    pEMs5vsCent2->GetXaxis()->SetTitle("Centrality (%)");
    pEMs5vsCent2->GetYaxis()->SetTitle("Average Signal in TS 1 (fC)");

    pEMs1vsCent2->SetMarkerStyle(20);
    pEMs2vsCent2->SetMarkerStyle(20);
    pEMs3vsCent2->SetMarkerStyle(20);
    pEMs4vsCent2->SetMarkerStyle(20);
    pEMs5vsCent2->SetMarkerStyle(20);

    TCanvas *c3 = new TCanvas();
    c3->Divide(3,2);
    c3->cd(1);
    pEMs1vsCent2->Draw("AP");
    c3->cd(2);
    pEMs2vsCent2->Draw("AP");
    c3->cd(3);
    pEMs3vsCent2->Draw("AP");
    c3->cd(4);
    pEMs4vsCent2->Draw("AP");
    c3->cd(5);
    pEMs5vsCent2->Draw("AP");

    double AvgSignalHADts1_Section1[] = {309.479, 309.705, 308.88, 308.399, 309.768, 311.007, 310.301, 310.022, 348.427, 795.741};

    double AvgSignalHADts1_Section2[] = {123.582, 122.378, 122.02, 121.8, 122.222, 123.158, 123.305, 124.07, 136.77, 284.738};

    double AvgSignalHADts1_Section3[] = {95.2859, 91.2062, 90.0975, 89.9104, 90.3941, 91.4754, 92.8192, 94.9079, 103.383, 183.222};

    double AvgSignalHADts1_Section4[] = {94.6603, 91.7165, 91.2258, 91.4192, 91.9736, 93.2697, 94.4568, 95.9664, 102.414, 163.032};

    TGraphErrors *pHADs1vsCent2 = new TGraphErrors(10, MidPtCentrality, AvgSignalHADts1_Section1, ex, 0);
    TGraphErrors *pHADs2vsCent2 = new TGraphErrors(10, MidPtCentrality, AvgSignalHADts1_Section2, ex, 0);
    TGraphErrors *pHADs3vsCent2 = new TGraphErrors(10, MidPtCentrality, AvgSignalHADts1_Section3, ex, 0);
    TGraphErrors *pHADs4vsCent2 = new TGraphErrors(10, MidPtCentrality, AvgSignalHADts1_Section4, ex, 0);

    pHADs1vsCent2->SetTitle("Run 375259 pos HAD Section 1 Avg Signal in TS 1 vs Centrality");
    pHADs2vsCent2->SetTitle("Run 375259 pos HAD Section 2 Avg Signal in TS 1 vs Centrality");
    pHADs3vsCent2->SetTitle("Run 375259 pos HAD Section 3 Avg Signal in TS 1 vs Centrality");
    pHADs4vsCent2->SetTitle("Run 375259 pos HAD Section 4 Avg Signal in TS 1 vs Centrality");

    pHADs1vsCent2->GetXaxis()->SetTitle("Centrality (%)");
    pHADs1vsCent2->GetYaxis()->SetTitle("Average Signal in TS 1 (fC)");

    pHADs2vsCent2->GetXaxis()->SetTitle("Centrality (%)");
    pHADs2vsCent2->GetYaxis()->SetTitle("Average Signal in TS 1 (fC)");

    pHADs3vsCent2->GetXaxis()->SetTitle("Centrality (%)");
    pHADs3vsCent2->GetYaxis()->SetTitle("Average Signal in TS 1 (fC)");

    pHADs4vsCent2->GetXaxis()->SetTitle("Centrality (%)");
    pHADs4vsCent2->GetYaxis()->SetTitle("Average Signal in TS 1 (fC)");

    pHADs1vsCent2->SetMarkerStyle(20);
    pHADs2vsCent2->SetMarkerStyle(20);
    pHADs3vsCent2->SetMarkerStyle(20);
    pHADs4vsCent2->SetMarkerStyle(20);

    TCanvas *c4 = new TCanvas();
    c4->Divide(2,2);
    c4->cd(1);
    pHADs1vsCent2->Draw("AP");
    c4->cd(2);
    pHADs2vsCent2->Draw("AP");
    c4->cd(3);
    pHADs3vsCent2->Draw("AP");
    c4->cd(4);
    pHADs4vsCent2->Draw("AP");

/*
The Average Signal (fC in Time Slice 0) of pEM for All Centrality is 184.444
The Average Signal (fC in Time Slice 0) of pEM for All Centrality is 170.295
The Average Signal (fC in Time Slice 0) of pEM for All Centrality is 343.063
The Average Signal (fC in Time Slice 0) of pEM for All Centrality is 849.746
The Average Signal (fC in Time Slice 0) of pEM for All Centrality is 1196.83

The Average Signal (fC in Time Slice 0) of pEM for 0 - < 10% Centrality is 163.024
The Average Signal (fC in Time Slice 0) of pEM for 0 - < 10% Centrality is 133.55
The Average Signal (fC in Time Slice 0) of pEM for 0 - < 10% Centrality is 272.499
The Average Signal (fC in Time Slice 0) of pEM for 0 - < 10% Centrality is 721.906
The Average Signal (fC in Time Slice 0) of pEM for 0 - < 10% Centrality is 1049.13

The Average Signal (fC in Time Slice 0) of pEM for 10 - < 20% Centrality is 163.089
The Average Signal (fC in Time Slice 0) of pEM for 10 - < 20% Centrality is 133.605
The Average Signal (fC in Time Slice 0) of pEM for 10 - < 20% Centrality is 276.574
The Average Signal (fC in Time Slice 0) of pEM for 10 - < 20% Centrality is 735.314
The Average Signal (fC in Time Slice 0) of pEM for 10 - < 20% Centrality is 1055.5

The Average Signal (fC in Time Slice 0) of pEM for 20 - < 30% Centrality is 163.26
The Average Signal (fC in Time Slice 0) of pEM for 20 - < 30% Centrality is 134.216
The Average Signal (fC in Time Slice 0) of pEM for 20 - < 30% Centrality is 275.445
The Average Signal (fC in Time Slice 0) of pEM for 20 - < 30% Centrality is 727.783
The Average Signal (fC in Time Slice 0) of pEM for 20 - < 30% Centrality is 1056.92

The Average Signal (fC in Time Slice 0) of pEM for 30 - < 40% Centrality is 163.368
The Average Signal (fC in Time Slice 0) of pEM for 30 - < 40% Centrality is 133.959
The Average Signal (fC in Time Slice 0) of pEM for 30 - < 40% Centrality is 274.518
The Average Signal (fC in Time Slice 0) of pEM for 30 - < 40% Centrality is 725.259
The Average Signal (fC in Time Slice 0) of pEM for 30 - < 40% Centrality is 1051.36

The Average Signal (fC in Time Slice 0) of pEM for 40 - < 50% Centrality is 162.727
The Average Signal (fC in Time Slice 0) of pEM for 40 - < 50% Centrality is 133.562
The Average Signal (fC in Time Slice 0) of pEM for 40 - < 50% Centrality is 274.199
The Average Signal (fC in Time Slice 0) of pEM for 40 - < 50% Centrality is 726.82
The Average Signal (fC in Time Slice 0) of pEM for 40 - < 50% Centrality is 1061.83

The Average Signal (fC in Time Slice 0) of pEM for 50 - < 60% Centrality is 163.098
The Average Signal (fC in Time Slice 0) of pEM for 50 - < 60% Centrality is 133.791
The Average Signal (fC in Time Slice 0) of pEM for 50 - < 60% Centrality is 274.094
The Average Signal (fC in Time Slice 0) of pEM for 50 - < 60% Centrality is 728.527
The Average Signal (fC in Time Slice 0) of pEM for 50 - < 60% Centrality is 1059.19

The Average Signal (fC in Time Slice 0) of pEM for 60 - < 70% Centrality is 163.291
The Average Signal (fC in Time Slice 0) of pEM for 60 - < 70% Centrality is 134.397
The Average Signal (fC in Time Slice 0) of pEM for 60 - < 70% Centrality is 274.469
The Average Signal (fC in Time Slice 0) of pEM for 60 - < 70% Centrality is 726.885
The Average Signal (fC in Time Slice 0) of pEM for 60 - < 70% Centrality is 1054.37

The Average Signal (fC in Time Slice 0) of pEM for 70 - < 80% Centrality is 162.813
The Average Signal (fC in Time Slice 0) of pEM for 70 - < 80% Centrality is 134.151
The Average Signal (fC in Time Slice 0) of pEM for 70 - < 80% Centrality is 274.512
The Average Signal (fC in Time Slice 0) of pEM for 70 - < 80% Centrality is 724.966
The Average Signal (fC in Time Slice 0) of pEM for 70 - < 80% Centrality is 1051.57

The Average Signal (fC in Time Slice 0) of pEM for 80 - < 90% Centrality is 208.372
The Average Signal (fC in Time Slice 0) of pEM for 80 - < 90% Centrality is 208.962
The Average Signal (fC in Time Slice 0) of pEM for 80 - < 90% Centrality is 398.271
The Average Signal (fC in Time Slice 0) of pEM for 80 - < 90% Centrality is 896.757
The Average Signal (fC in Time Slice 0) of pEM for 80 - < 90% Centrality is 1241.08

The Average Signal (fC in Time Slice 0) of pEM for 90 - 100% Centrality is 322.106
The Average Signal (fC in Time Slice 0) of pEM for 90 - 100% Centrality is 407.154
The Average Signal (fC in Time Slice 0) of pEM for 90 - 100% Centrality is 808.35
The Average Signal (fC in Time Slice 0) of pEM for 90 - 100% Centrality is 1739.59
The Average Signal (fC in Time Slice 0) of pEM for 90 - 100% Centrality is 2236.07

The Average Signal (fC in Time Slice 0) of pHAD for All Centrality is 817.082
The Average Signal (fC in Time Slice 0) of pHAD for All Centrality is 300.806
The Average Signal (fC in Time Slice 0) of pHAD for All Centrality is 203.755
The Average Signal (fC in Time Slice 0) of pHAD for All Centrality is 179.56

The Average Signal (fC in Time Slice 0) of pHAD for 0 - <10% Centrality is 711.063
The Average Signal (fC in Time Slice 0) of pHAD for 0 - <10% Centrality is 264.99
The Average Signal (fC in Time Slice 0) of pHAD for 0 - <10% Centrality is 184.322
The Average Signal (fC in Time Slice 0) of pHAD for 0 - <10% Centrality is 164.306

The Average Signal (fC in Time Slice 0) of pHAD for 10 - < 20% Centrality is 712.912
The Average Signal (fC in Time Slice 0) of pHAD for 10 - < 20% Centrality is 265.985
The Average Signal (fC in Time Slice 0) of pHAD for 10 - < 20% Centrality is 184.564
The Average Signal (fC in Time Slice 0) of pHAD for 10 - < 20% Centrality is 164.573

The Average Signal (fC in Time Slice 0) of pHAD for 20 - < 30% Centrality is 713.118
The Average Signal (fC in Time Slice 0) of pHAD for 20 - < 30% Centrality is 266.28
The Average Signal (fC in Time Slice 0) of pHAD for 20 - < 30% Centrality is 185.043
The Average Signal (fC in Time Slice 0) of pHAD for 20 - < 30% Centrality is 164.906

The Average Signal (fC in Time Slice 0) of pHAD for 30 - < 40% Centrality is 709.316
The Average Signal (fC in Time Slice 0) of pHAD for 30 - < 40% Centrality is 264.635
The Average Signal (fC in Time Slice 0) of pHAD for 30 - < 40% Centrality is 184.435
The Average Signal (fC in Time Slice 0) of pHAD for 30 - < 40% Centrality is 164.664

The Average Signal (fC in Time Slice 0) of pHAD for 40 - < 50% Centrality is 712.498
The Average Signal (fC in Time Slice 0) of pHAD for 40 - < 50% Centrality is 265.362
The Average Signal (fC in Time Slice 0) of pHAD for 40 - < 50% Centrality is 184.883
The Average Signal (fC in Time Slice 0) of pHAD for 40 - < 50% Centrality is 164.631

The Average Signal (fC in Time Slice 0) of pHAD for 50 - < 60% Centrality is 716.763
The Average Signal (fC in Time Slice 0) of pHAD for 50 - < 60% Centrality is 266.947
The Average Signal (fC in Time Slice 0) of pHAD for 50 - < 60% Centrality is 185.167
The Average Signal (fC in Time Slice 0) of pHAD for 50 - < 60% Centrality is 165.329

The Average Signal (fC in Time Slice 0) of pHAD for 60 - < 70% Centrality is 711.97
The Average Signal (fC in Time Slice 0) of pHAD for 60 - < 70% Centrality is 265.082
The Average Signal (fC in Time Slice 0) of pHAD for 60 - < 70% Centrality is 184.373
The Average Signal (fC in Time Slice 0) of pHAD for 60 - < 70% Centrality is 164.541

The Average Signal (fC in Time Slice 0) of pHAD for 70 - < 80% Centrality is 709.11
The Average Signal (fC in Time Slice 0) of pHAD for 70 - < 80% Centrality is 264.36
The Average Signal (fC in Time Slice 0) of pHAD for 70 - < 80% Centrality is 183.831
The Average Signal (fC in Time Slice 0) of pHAD for 70 - < 80% Centrality is 164.029

The Average Signal (fC in Time Slice 0) of pHAD for 80 - < 90% Centrality is 841.874
The Average Signal (fC in Time Slice 0) of pHAD for 80 - < 90% Centrality is 308.991
The Average Signal (fC in Time Slice 0) of pHAD for 80 - < 90% Centrality is 209.46
The Average Signal (fC in Time Slice 0) of pHAD for 80 - < 90% Centrality is 184.111

The Average Signal (fC in Time Slice 0) of pHAD for 90 - 100% Centrality is 1595.19
The Average Signal (fC in Time Slice 0) of pHAD for 90 - 100% Centrality is 563.097
The Average Signal (fC in Time Slice 0) of pHAD for 90 - 100% Centrality is 344.641
The Average Signal (fC in Time Slice 0) of pHAD for 90 - 100% Centrality is 289.216

The Average Signal (fC in Time Slice 1) of pEM for All Centrality is 161.502
The Average Signal (fC in Time Slice 1) of pEM for All Centrality is 130.829
The Average Signal (fC in Time Slice 1) of pEM for All Centrality is 252.722
The Average Signal (fC in Time Slice 1) of pEM for All Centrality is 427.017
The Average Signal (fC in Time Slice 1) of pEM for All Centrality is 619.721

The Average Signal (fC in Time Slice 1) of pEM for 0 - < 10% Centrality is 152.011
The Average Signal (fC in Time Slice 1) of pEM for 0 - < 10% Centrality is 112.78
The Average Signal (fC in Time Slice 1) of pEM for 0 - < 10% Centrality is 217.029
The Average Signal (fC in Time Slice 1) of pEM for 0 - < 10% Centrality is 362.564
The Average Signal (fC in Time Slice 1) of pEM for 0 - < 10% Centrality is 544.803

The Average Signal (fC in Time Slice 1) of pEM for 10 - < 20% Centrality is 149.995
The Average Signal (fC in Time Slice 1) of pEM for 10 - < 20% Centrality is 110.655
The Average Signal (fC in Time Slice 1) of pEM for 10 - < 20% Centrality is 218.027
The Average Signal (fC in Time Slice 1) of pEM for 10 - < 20% Centrality is 366.02
The Average Signal (fC in Time Slice 1) of pEM for 10 - < 20% Centrality is 547.439

The Average Signal (fC in Time Slice 1) of pEM for 20 - < 30% Centrality is 149.409
The Average Signal (fC in Time Slice 1) of pEM for 20 - < 30% Centrality is 109.774
The Average Signal (fC in Time Slice 1) of pEM for 20 - < 30% Centrality is 217.315
The Average Signal (fC in Time Slice 1) of pEM for 20 - < 30% Centrality is 363.453
The Average Signal (fC in Time Slice 1) of pEM for 20 - < 30% Centrality is 547.114

The Average Signal (fC in Time Slice 1) of pEM for 30 - < 40% Centrality is 149.654
The Average Signal (fC in Time Slice 1) of pEM for 30 - < 40% Centrality is 109.68
The Average Signal (fC in Time Slice 1) of pEM for 30 - < 40% Centrality is 217.172
The Average Signal (fC in Time Slice 1) of pEM for 30 - < 40% Centrality is 363.195
The Average Signal (fC in Time Slice 1) of pEM for 30 - < 40% Centrality is 546.185

The Average Signal (fC in Time Slice 1) of pEM for 40 - < 50% Centrality is 149.401
The Average Signal (fC in Time Slice 1) of pEM for 40 - < 50% Centrality is 109.705
The Average Signal (fC in Time Slice 1) of pEM for 40 - < 50% Centrality is 217.387
The Average Signal (fC in Time Slice 1) of pEM for 40 - < 50% Centrality is 364.093
The Average Signal (fC in Time Slice 1) of pEM for 40 - < 50% Centrality is 549.445

The Average Signal (fC in Time Slice 1) of pEM for 50 - < 60% Centrality is 150.089
The Average Signal (fC in Time Slice 1) of pEM for 50 - < 60% Centrality is 110.196
The Average Signal (fC in Time Slice 1) of pEM for 50 - < 60% Centrality is 217.282
The Average Signal (fC in Time Slice 1) of pEM for 50 - < 60% Centrality is 364.87
The Average Signal (fC in Time Slice 1) of pEM for 50 - < 60% Centrality is 548.23

The Average Signal (fC in Time Slice 1) of pEM for 60 - < 70% Centrality is 150.571
The Average Signal (fC in Time Slice 1) of pEM for 60 - < 70% Centrality is 110.909
The Average Signal (fC in Time Slice 1) of pEM for 60 - < 70% Centrality is 217.307
The Average Signal (fC in Time Slice 1) of pEM for 60 - < 70% Centrality is 364.494
The Average Signal (fC in Time Slice 1) of pEM for 60 - < 70% Centrality is 546.846

The Average Signal (fC in Time Slice 1) of pEM for 70 - < 80% Centrality is 151.253
The Average Signal (fC in Time Slice 1) of pEM for 70 - < 80% Centrality is 111.976
The Average Signal (fC in Time Slice 1) of pEM for 70 - < 80% Centrality is 217.996
The Average Signal (fC in Time Slice 1) of pEM for 70 - < 80% Centrality is 363.77
The Average Signal (fC in Time Slice 1) of pEM for 70 - < 80% Centrality is 546.94

The Average Signal (fC in Time Slice 1) of pEM for 80 - < 90% Centrality is 163.074
The Average Signal (fC in Time Slice 1) of pEM for 80 - < 90% Centrality is 130.999
The Average Signal (fC in Time Slice 1) of pEM for 80 - < 90% Centrality is 250.223
The Average Signal (fC in Time Slice 1) of pEM for 80 - < 90% Centrality is 412.182
The Average Signal (fC in Time Slice 1) of pEM for 80 - < 90% Centrality is 601.942

The Average Signal (fC in Time Slice 1) of pEM for 90 - 100% Centrality is 245.694
The Average Signal (fC in Time Slice 1) of pEM for 90 - 100% Centrality is 284.897
The Average Signal (fC in Time Slice 1) of pEM for 90 - 100% Centrality is 526.051
The Average Signal (fC in Time Slice 1) of pEM for 90 - 100% Centrality is 926.379
The Average Signal (fC in Time Slice 1) of pEM for 90 - 100% Centrality is 1195.84

The Average Signal (fC in Time Slice 1) of pHAD for All Centrality is 363.818
The Average Signal (fC in Time Slice 1) of pHAD for All Centrality is 140.962
The Average Signal (fC in Time Slice 1) of pHAD for All Centrality is 102.632
The Average Signal (fC in Time Slice 1) of pHAD for All Centrality is 101.293

The Average Signal (fC in Time Slice 1) of pHAD for 0 - <10% Centrality is 309.479
The Average Signal (fC in Time Slice 1) of pHAD for 0 - <10% Centrality is 123.582
The Average Signal (fC in Time Slice 1) of pHAD for 0 - <10% Centrality is 95.2859
The Average Signal (fC in Time Slice 1) of pHAD for 0 - <10% Centrality is 94.6603

The Average Signal (fC in Time Slice 1) of pHAD for 10 - < 20% Centrality is 309.705
The Average Signal (fC in Time Slice 1) of pHAD for 10 - < 20% Centrality is 122.378
The Average Signal (fC in Time Slice 1) of pHAD for 10 - < 20% Centrality is 91.2062
The Average Signal (fC in Time Slice 1) of pHAD for 10 - < 20% Centrality is 91.7165

The Average Signal (fC in Time Slice 1) of pHAD for 20 - < 30% Centrality is 308.88
The Average Signal (fC in Time Slice 1) of pHAD for 20 - < 30% Centrality is 122.02
The Average Signal (fC in Time Slice 1) of pHAD for 20 - < 30% Centrality is 90.0975
The Average Signal (fC in Time Slice 1) of pHAD for 20 - < 30% Centrality is 91.2258

The Average Signal (fC in Time Slice 1) of pHAD for 30 - < 40% Centrality is 308.399
The Average Signal (fC in Time Slice 1) of pHAD for 30 - < 40% Centrality is 121.8
The Average Signal (fC in Time Slice 1) of pHAD for 30 - < 40% Centrality is 89.9104
The Average Signal (fC in Time Slice 1) of pHAD for 30 - < 40% Centrality is 91.4192

The Average Signal (fC in Time Slice 1) of pHAD for 40 - < 50% Centrality is 309.768
The Average Signal (fC in Time Slice 1) of pHAD for 40 - < 50% Centrality is 122.222
The Average Signal (fC in Time Slice 1) of pHAD for 40 - < 50% Centrality is 90.3941
The Average Signal (fC in Time Slice 1) of pHAD for 40 - < 50% Centrality is 91.9736

The Average Signal (fC in Time Slice 1) of pHAD for 50 - < 60% Centrality is 311.007
The Average Signal (fC in Time Slice 1) of pHAD for 50 - < 60% Centrality is 123.158
The Average Signal (fC in Time Slice 1) of pHAD for 50 - < 60% Centrality is 91.4754
The Average Signal (fC in Time Slice 1) of pHAD for 50 - < 60% Centrality is 93.2697

The Average Signal (fC in Time Slice 1) of pHAD for 60 - < 70% Centrality is 310.301
The Average Signal (fC in Time Slice 1) of pHAD for 60 - < 70% Centrality is 123.305
The Average Signal (fC in Time Slice 1) of pHAD for 60 - < 70% Centrality is 92.8192
The Average Signal (fC in Time Slice 1) of pHAD for 60 - < 70% Centrality is 94.4568

The Average Signal (fC in Time Slice 1) of pHAD for 70 - < 80% Centrality is 310.022
The Average Signal (fC in Time Slice 1) of pHAD for 70 - < 80% Centrality is 124.07
The Average Signal (fC in Time Slice 1) of pHAD for 70 - < 80% Centrality is 94.9079
The Average Signal (fC in Time Slice 1) of pHAD for 70 - < 80% Centrality is 95.9664

The Average Signal (fC in Time Slice 1) of pHAD for 80 - < 90% Centrality is 348.427
The Average Signal (fC in Time Slice 1) of pHAD for 80 - < 90% Centrality is 136.77
The Average Signal (fC in Time Slice 1) of pHAD for 80 - < 90% Centrality is 103.383
The Average Signal (fC in Time Slice 1) of pHAD for 80 - < 90% Centrality is 102.414

The Average Signal (fC in Time Slice 1) of pHAD for 90 - 100% Centrality is 795.741
The Average Signal (fC in Time Slice 1) of pHAD for 90 - 100% Centrality is 284.738
The Average Signal (fC in Time Slice 1) of pHAD for 90 - 100% Centrality is 183.222
The Average Signal (fC in Time Slice 1) of pHAD for 90 - 100% Centrality is 163.032
*/
}