void rateVsRun(){
    // create a graph of the rate vs run number
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    // run 374354, 374288
    double rate_ZB[4]     = { 652239.13,1885860.65,4381659.78}; 
    double rate_ZDCAND[4] = { 3827.41, 32773.62, 72351.36};
    double rate_ZDCOR[4]  = {70748.47,157893.81, 716809.18};
    double numBunches[4] = { 58, 170,394}; 

    // loop over rates and calculated zdc/zb
    double rate_ZDCAND_ZB[4];
    double rate_ZDCOR_ZB[4];
    for(int i = 0; i < 3; i++){
        rate_ZDCAND_ZB[i] = rate_ZDCAND[i]/rate_ZB[i];
        rate_ZDCOR_ZB[i] = rate_ZDCOR[i]/rate_ZB[i];
    }
    

    TCanvas *c = new TCanvas("c","c",800,600);
    c->cd(); 
    auto g = new TGraph(3,numBunches,rate_ZDCAND_ZB);
    g->SetTitle(";Number of Bunches; ZDC Rate / ZB Rate");
    g->GetYaxis()->SetTitleOffset(1.4);
    g->SetLineColor(kRed);
    g->SetMarkerColor(kRed);
    g->SetLineWidth(2);
    g->Draw("AC*");

    auto g2 = new TGraph(3,numBunches,rate_ZDCOR_ZB);
    //g2->SetTitle(";Number of Bunches; ZDC Rate / ZB Rate");
    // g2->GetYaxis()->SetTitleOffset(1.4);
    g2->SetLineColor(kBlack);
    g2->SetMarkerColor(kBlack);
    g2->SetLineWidth(2);
    g2->Draw("C* same");

    // create a legend
    TLegend* leg = new TLegend(0.1, 0.7, 0.9, 0.9);
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetTextSize(0.04);
    leg->AddEntry(g, "ZDCAND", "p");
    leg->AddEntry(g2, "ZDCOR", "p");
    leg->Draw("same");





}