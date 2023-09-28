/*
* plotUnpackerChecks.C: plot the validation checks for the unpacker. 
* Hannah Bossi, <hannah.bossi@cern.ch>, 9/24/2023
*/

void plotUnpackerChecks(int runNumber = 374288){
    gStyle->SetOptStat(0);

    // histogram 1: sum minus vs. global bx
    TFile* inFile = new TFile(Form("/Users/hannahbossi/Documents/LocalCode/RunPrep/outputFiles/unpackerTest_Run%d_ZB.root", runNumber));
    TH1D* sumMinusBx = (TH1D*)inFile->Get("sumMinusBx");
    sumMinusBx->SetLineColor(kRed);
    sumMinusBx->SetMarkerColor(kRed);
    sumMinusBx->SetLineWidth(2);
    sumMinusBx->GetXaxis()->SetTitle("Global Bx");
    sumMinusBx->GetYaxis()->SetTitle("Sum Minus");
    sumMinusBx->SetTitle("Sum Minus vs. Global Bx");
    
    TH1D* sumMinusEmuBx = (TH1D*)inFile->Get("sumMinusEmuBx");
    sumMinusEmuBx->SetLineColor(kBlue);
    sumMinusEmuBx->SetLineWidth(2);

    TLegend* leg = new TLegend(0.7, 0.7, 0.9, 0.9);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->AddEntry(sumMinusBx, "Unpacked Sums", "l");
    leg->AddEntry(sumMinusEmuBx, "Emulated Sums", "l");

    TCanvas* c1 = new TCanvas("c1", "c1", 800, 600);
    c1->cd(); 
    sumMinusBx->Draw();
    sumMinusEmuBx->Draw("same");
    leg->Draw("same"); 
    c1->SaveAs(Form("/Users/hannahbossi/Documents/LocalCode/RunPrep/plots/UnpackerChecks/Run%d/sumMinus_GlobalBx.png", runNumber));


    // histogram 2: sum plus vs. global bx
    TCanvas* c2 = new TCanvas("c2", "c2", 800, 600);
    c2->cd(); 
    TH1D* sumPlusBx = (TH1D*)inFile->Get("sumPlusBx");
    sumPlusBx->SetLineColor(kRed);
    sumPlusBx->SetMarkerColor(kRed);
    sumPlusBx->SetLineWidth(2);
    sumPlusBx->GetXaxis()->SetTitle("Global Bx");
    sumPlusBx->GetYaxis()->SetTitle("SumPlus");
    sumPlusBx->SetTitle("Sum Plus vs. Global Bx");
    
    TH1D* sumPlusEmuBx = (TH1D*)inFile->Get("sumPlusEmuBx");
    sumPlusEmuBx->SetLineColor(kBlue);
    sumPlusEmuBx->SetLineWidth(2);

    TLegend* leg2 = new TLegend(0.7, 0.7, 0.9, 0.9);
    leg2->SetBorderSize(0);
    leg2->SetFillStyle(0);
    leg2->AddEntry(sumPlusBx, "Unpacked Sums", "l");
    leg2->AddEntry(sumPlusEmuBx, "Emulated Sums", "l");

    sumPlusBx->Draw();
    sumPlusEmuBx->Draw("same");
    leg2->Draw("same");
    c2->SaveAs(Form("/Users/hannahbossi/Documents/LocalCode/RunPrep/plots/UnpackerChecks/Run%d/sumPlus_GlobalBx.png", runNumber));

  
    //histogram 3: sum minus correlation plots
    TCanvas* c3 = new TCanvas("c3", "c3", 800, 600);
    c3->cd();
    TH2D* corrMinus = (TH2D*)inFile->Get("sumMinusCorr");
    corrMinus->GetXaxis()->SetTitle("Sum minus from emulator");
    corrMinus->GetYaxis()->SetTitle("Sum minus from unpacker");
    corrMinus->SetMarkerStyle(20);
    corrMinus->SetMarkerSize(2);
    corrMinus->SetTitle(""); 
    corrMinus->SetMarkerColor(kBlack);
    corrMinus->GetXaxis()->SetRangeUser(0, 500);
    corrMinus->GetYaxis()->SetRangeUser(0, 500);
    corrMinus->Draw("colz");
    // create new tlegend with summary statistics (no histograms)
    TLegend* leg3 = new TLegend(0.16, 0.7, 0.3, 0.85);
    leg3->SetBorderSize(0);
    leg3->SetFillStyle(0);
    leg3->SetTextSize(0.03);
    leg3->AddEntry((TObject*)0, Form("Mean Emu: %.4f", corrMinus->GetMean(1)), "");
    leg3->AddEntry((TObject*)0, Form("RMS Emu: %.4f", corrMinus->GetRMS(1)), "");
    leg3->AddEntry((TObject*)0, Form("Mean Unpack: %.4f", corrMinus->GetMean(2)), "");
    leg3->AddEntry((TObject*)0, Form("RMS Unpack: %.4f", corrMinus->GetRMS(2)), "");
    leg3->Draw("same");
   
    c3->SaveAs(Form("/Users/hannahbossi/Documents/LocalCode/RunPrep/plots/UnpackerChecks/Run%d/sumMinusCorr.pdf", runNumber));
 
    //histogram 4: sum plus correlation plots
    TCanvas* c4 = new TCanvas("c4", "c4", 800, 600);
    c4->cd();
    TH2D* corrPlus = (TH2D*)inFile->Get("sumPlusCorr");
    corrPlus->GetXaxis()->SetTitle("Sum plus from emulator");
    corrPlus->GetYaxis()->SetTitle("Sum plus from unpacker");
    corrPlus->GetXaxis()->SetRangeUser(0, 500);
    corrPlus->GetYaxis()->SetRangeUser(0, 500);
    corrPlus->SetMarkerStyle(20);
    corrPlus->SetMarkerSize(2);
    corrPlus->SetMarkerColor(kBlack);
    corrPlus->SetTitle(""); 
    corrPlus->Draw("colz");

    // create new tlegend with summary statistics (no histograms)
    TLegend* leg4 = new TLegend(0.16, 0.7, 0.3, 0.85);
    leg4->SetBorderSize(0);
    leg4->SetFillStyle(0);
    leg4->SetTextSize(0.03);
    leg4->AddEntry((TObject*)0, Form("Mean Emu: %.4f", corrPlus->GetMean(1)), "");
    leg4->AddEntry((TObject*)0, Form("RMS Emu: %.4f", corrPlus->GetRMS(1)), "");
    leg4->AddEntry((TObject*)0, Form("Mean Unpack: %.4f", corrPlus->GetMean(2)), "");
    leg4->AddEntry((TObject*)0, Form("RMS Unpack: %.4f", corrPlus->GetRMS(2)), "");
    leg4->Draw("same");
    c4->SaveAs(Form("/Users/hannahbossi/Documents/LocalCode/RunPrep/plots/UnpackerChecks/Run%d/sumPlusCorr.pdf", runNumber));
 

    // histogram 5: summary
    TH1D* summary = (TH1D*)inFile->Get("unpackerTest");
    //summary->GetXaxis()->SetLabelSize(0.05);
    gStyle->SetOptTitle(0);
    TCanvas* c5 = new TCanvas("c5", "c5", 800, 600);
    c5->SetLogy(); 
    summary->Draw();
    c5->SaveAs(Form("/Users/hannahbossi/Documents/LocalCode/RunPrep/plots/UnpackerChecks/Run%d/summary.pdf", runNumber));

    
}