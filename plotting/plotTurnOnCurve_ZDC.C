void plotTurnOnCurve_ZDC(int nNeutron = 1){
    TFile* infile = new TFile("Run374521_ZDCTriggerCheck.root","READ");
    TH1D* hZDCP = (TH1D*)infile->Get("hZDCP");
    TH1D* hZDCM = (TH1D*)infile->Get("hZDCM");
    TH1D* hZDCP_GeV = (TH1D*)infile->Get("hZDCP_GeV");
    TH1D* hZDCM_GeV = (TH1D*)infile->Get("hZDCM_GeV");
    TH1D* hZDCP22 = (TH1D*)infile->Get("hZDCP22");
    TH1D* hZDCM22 = (TH1D*)infile->Get("hZDCM22");
    TH1D* hZDCP80 = (TH1D*)infile->Get("hZDCP80");
    TH1D* hZDCM80 = (TH1D*)infile->Get("hZDCM80");
    TH1D* hZDCP133 = (TH1D*)infile->Get("hZDCP133");
    TH1D* hZDCM133 = (TH1D*)infile->Get("hZDCM133");

    // zdc plus
    hZDCP22->SetLineColor(kRed);
    hZDCP22->SetLineWidth(2);
    hZDCP22->SetMarkerStyle(20);
    hZDCP22->Divide(hZDCP);
    hZDCP22->GetXaxis()->SetTitle("ZDC Sum");


    hZDCP80->SetLineColor(kRed);
    hZDCP80->SetLineWidth(2);
    hZDCP80->Divide(hZDCP);
    hZDCP80->GetXaxis()->SetTitle("ZDC Sum");

    // zdc minus
    hZDCM22->SetLineColor(kBlue);
    hZDCM22->SetLineWidth(2);
    hZDCM22->SetMarkerStyle(20);
    hZDCM22->Divide(hZDCM);


    TLegend* leg = new TLegend(0.7,0.7,0.85,0.85);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->SetTextSize(0.03);


    
    TCanvas* c1 = new TCanvas("c1","c1",800,600);
    c1->cd();
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    c1->SetTopMargin(0.05);
    c1->SetBottomMargin(0.09);
    c1->SetLeftMargin(0.09);
    c1->SetRightMargin(0.05);
    if(nNeutron == 1){
      hZDCP22->Draw();
      hZDCM22->Draw("same");
      leg->AddEntry(hZDCP22,"ZDCP22","l");
      leg->AddEntry(hZDCM22,"ZDCM22","l");
    }
    else if(nNeutron == 2){
      hZDCP80->Draw();
      hZDCM80->Draw("same");
      leg->AddEntry(hZDCP80,"ZDCP80","l");
      leg->AddEntry(hZDCM80,"ZDCM80","l");
    }
    else if(nNeutron == 3){
      hZDCP133->Draw();
      hZDCM133->Draw("same");
      leg->AddEntry(hZDCP133,"ZDCP133","l");
      leg->AddEntry(hZDCM133,"ZDCM133","l");
    }
  
    leg->Draw("same");
    c1->SaveAs(Form("ZDC%dnThreshold_TurnOn.pdf", nNeutron));


}