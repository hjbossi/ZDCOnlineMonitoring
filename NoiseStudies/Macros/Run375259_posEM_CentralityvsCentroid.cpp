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

void Run375259_posEM_CentralityvsCentroid() 
{
    double MidPtCent[] = {4.75, 14.75, 24.75, 34.75, 44.75, 54.75, 64.75, 74.75, 84.75, 94.75};
    double MeanX[] = {0.8222, 1.069, 1.248, 1.392, 1.515, 1.615, 1.687, 1.723, 1.728, 1.765}; 
    double ex[] = {4.75, 4.75, 4.75, 4.75, 4.75, 4.75, 4.75, 4.75, 4.75, 4.75};
    double ey[] = {0.4033, 0.3571, 0.3464, 0.344, 0.3472, 0.3582, 0.3792, 0.4151, 0.4598, 0.5437};

    TGraphErrors *pEM_fit = new TGraphErrors(10, MidPtCent, MeanX, ex, ey);

    pEM_fit->SetTitle("Run375259 pos EM Centroid vs Centrality");
    pEM_fit->SetLineColor(kBlue);
    pEM_fit->SetMarkerStyle(20);

    pEM_fit->GetXaxis()->SetTitle("Centrality (%)");
    pEM_fit->GetYaxis()->SetTitle("Mean X Position (cm)");

    pEM_fit->GetYaxis()->SetRangeUser(0,3.0);
    pEM_fit->GetXaxis()->SetRangeUser(0,100);

    TF1 *fitFunc = new TF1("fitFunc", "pol1",0,100);

    fitFunc->SetParameter(0, 0.2); // slope
    fitFunc->SetParameter(1, 0.3); // intercept

    pEM_fit->Fit("fitFunc", "R");

    TCanvas *can = new TCanvas();
    pEM_fit->Draw("AP");
    fitFunc->Draw("same");

}