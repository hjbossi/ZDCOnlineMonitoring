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

void Run375259_LinFit_CentvsCOM()
{

    // Linear Fit for Run375259 Centrality vs COM plot
    double MeanX[] = {0.3886, 0.5693, 0.6762, 0.7687, 0.8592, 0.948, 1.032, 1.098, 1.131, 1.076 };
    double MidPtCentrality[] = {4.75, 14.75, 24.75, 34.75, 44.75, 54.75, 64.75, 74.75, 84.75, 94.75};
    double ex[] = {4.75, 4.75, 4.75, 4.75, 4.75, 4.75, 4.75, 4.75, 4.75, 4.75};
    double ey[] = {0.4161, 0.3577, 0.343, 0.3402, 0.3407, 0.3437, 0.349, 0.3671, 0.4046, 0.5588};

    TGraphErrors *LinFit = new TGraphErrors(10, MidPtCentrality, MeanX, ex, ey);

    LinFit->SetTitle("Run375259 pos RPD Centroid vs Centrality");

    LinFit->SetLineColor(kBlue);
    LinFit->SetMarkerStyle(20);

    LinFit->GetYaxis()->SetTitle("Mean X Position (cm)");
    LinFit->GetXaxis()->SetTitle("Centrality (%)");

    LinFit->GetYaxis()->SetRangeUser(0,2.0);
    LinFit->GetXaxis()->SetRangeUser(0,100);

    TF1 *fitFunc = new TF1("fitFunc", "pol1",0,100);

    fitFunc->SetParameter(0, 0.01); // slope
    fitFunc->SetParameter(1, 0.3); // intercept

    LinFit->Fit("fitFunc","R");    

    TCanvas *can = new TCanvas();
    LinFit->Draw("AP");
    fitFunc->Draw("same");
}