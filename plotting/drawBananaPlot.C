void drawBananaPlot(){
    TFile* inFile = TFile::Open("BananaPlot_FSCHadronic.root"); 
    TH2D* bananaPlot = (TH2D*)inFile->Get("bananaPlot"); 
    TH2D* bananaPlotFSCADC = (TH2D*)inFile->Get("bananaPlotFSCADC"); 
    TH2D* bananaPlotFSCplus = (TH2D*)inFile->Get("bananaPlotFSCADCplus"); 
    TH2D* bananaPlotFSCminus = (TH2D*)inFile->Get("bananaPlotFSCADCminus"); 


    TLatex* cms = new TLatex(0.18,0.92,"#bf{CMS} #it{Preliminary} PbPb 5.36 TeV");
    cms->SetNDC();
    cms->SetTextSize(0.05);
    cms->SetTextFont(42);

    TLatex* eventSel = new TLatex(0.3,0.16,"Hadronic Event Selection");
    eventSel->SetNDC();
    eventSel->SetTextSize(0.035);
    eventSel->SetTextFont(42);

    // ------------------------------------------
    /* ZDC Plus and Minus */
    // ------------------------------------------


   
    
    TCanvas* c3 = new TCanvas("c3","c3",600,600);
    c3->cd();
    c3->SetTickx(1);
    c3->SetTicky(1);
    c3->SetLogz(); 
    c3->SetTopMargin(0.09);
    c3->SetBottomMargin(0.08);
    c3->SetLeftMargin(0.11);
    c3->SetRightMargin(0.13);

    //gStyle->SetPalette(kRainBow);

    // zdc plus
    bananaPlot->GetXaxis()->SetTitle("HF Transverse Energy Sum (GeV)"); 
    bananaPlot->GetYaxis()->SetTitle("ZDC Energy Sum (GeV)"); 
    bananaPlot->GetZaxis()->SetRangeUser(1.0, 30); 
    bananaPlot->Draw("colz");
    eventSel->Draw("same");  
    cms->Draw("same");
    //c3->SaveAs("BananaPlotLHCC_FSC.pdf");

    TCanvas* c4 = new TCanvas("c4","c4",600,600);
    c4->cd();
    c4->SetTickx(1);
    c4->SetTicky(1);
    c4->SetLogz(); 
    c4->SetTopMargin(0.09);
    c4->SetBottomMargin(0.08);
    c4->SetLeftMargin(0.13);
    c4->SetRightMargin(0.13);

    //gStyle->SetPalette(kRainBow);

    // zdc plus
    bananaPlotFSCADC->Rebin2D(1,5); 
    bananaPlotFSCADC->GetXaxis()->SetTitle("HF Transverse Energy Sum (GeV)"); 
    bananaPlotFSCADC->GetYaxis()->SetTitle("FSC ADC Sum "); 
    bananaPlotFSCADC->GetZaxis()->SetRangeUser(1.0, 100); 
    bananaPlotFSCADC->Draw("colz"); 
    cms->Draw("same");
    eventSel->Draw("same"); 
    c4->SaveAs("BananaPlotFSC_LHCC.pdf");


    TCanvas* c5= new TCanvas("c5","c5",600,600);
    c5->cd();
    c5->SetTickx(1);
    c5->SetTicky(1);
    c5->SetLogz(); 
    c5->SetTopMargin(0.09);
    c5->SetBottomMargin(0.08);
    c5->SetLeftMargin(0.13);
    c5->SetRightMargin(0.13);

    //gStyle->SetPalette(kRainBow);

    // zdc plus
    bananaPlotFSCplus->Rebin2D(1,5); 
    bananaPlotFSCplus->GetXaxis()->SetTitle("HF+ Transverse Energy Sum (GeV)"); 
    bananaPlotFSCplus->GetYaxis()->SetTitle("FSC+ ADC Sum "); 
    bananaPlotFSCplus->GetZaxis()->SetRangeUser(1.0, 100); 
     bananaPlotFSCplus->GetYaxis()->SetRangeUser(0, 100);
    bananaPlotFSCplus->Draw("colz"); 
    cms->Draw("same");
    eventSel->Draw("same"); 
    c5->SaveAs("BananaPlotFSCplus_LHCC.pdf");
    

    TCanvas* c6= new TCanvas("c6","c6",600,600);
    c6->cd();
    c6->SetTickx(1);
    c6->SetTicky(1);
    c6->SetLogz(); 
    c6->SetTopMargin(0.09);
    c6->SetBottomMargin(0.08);
    c6->SetLeftMargin(0.13);
    c6->SetRightMargin(0.13);

    //gStyle->SetPalette(kRainBow);

    // zdc plus
    bananaPlotFSCminus->Rebin2D(1,5); 
    bananaPlotFSCminus->GetXaxis()->SetTitle("HF- Transverse Energy Sum (GeV)"); 
    bananaPlotFSCminus->GetYaxis()->SetTitle("FSC- ADC Sum "); 
    bananaPlotFSCminus->GetZaxis()->SetRangeUser(1.0, 100); 
    bananaPlotFSCminus->Draw("colz"); 
    cms->Draw("same");
    eventSel->Draw("same"); 
    c6->SaveAs("BananaPlotFSCminus_LHCC.pdf");
    
}