void analyzePedstals(){
    TFile* inFile = TFile::Open("/Users/hannahbossi/Desktop/ZDCAnalyzer_USC_384226.root"); 
    TDirectoryFile* inDirect = (TDirectoryFile*)inFile->Get("zdcana"); 
    TDirectoryFile* adcDirect = (TDirectoryFile*)inDirect->Get("ADC");
    std::string namesNoSpace[20] = {"hZDCP_EM1", "hZDCP_EM2", "hZDCP_EM3", "hZDCP_EM4",  "hZDCP_EM5",  "hZDCP_HAD1", "hZDCP_HAD2", "hZDCP_HAD3", "hZDCP_HAD4", "hZDCP_RPD12"};
    int colors[20] = {kRed+2, kRed-4, kOrange+7, kOrange, kYellow-4, kSpring+10, kSpring, kGreen-3, kGreen+3, kTeal-7, kTeal, kAzure+10, kAzure-4, kBlue+2, kViolet+8, kViolet-1, kMagenta+1, kMagenta-4, kPink+7, kPink-4};
    std::string ColorStrings[10] = {"#3f90da", "#ffa90e", "#bd1f01", "#94a4a2", "#832db6", "#a96b59", "#e76300", "#b9ac70", "#717581", "#92dadd"};//{"#5790fc", "#f89c20", "#e42536", "#964a8b", "#9c9ca1", "#7a21dd"};
    int nHists = 10; 

    // now get all the 
    std::vector<TH1D*> adcHists; 
    for(int h = 0; h < nHists; h++){
        adcDirect->ls(); 
        TH2D* twodHist = (TH2D*)adcDirect->Get(namesNoSpace[h].c_str());
        int tsBin = twodHist->GetXaxis()->FindBin(2.);  
        TH1D* proj = (TH1D*)twodHist->ProjectionY(Form("%s_proj", twodHist->GetName()), tsBin, tsBin); 
        adcHists.push_back(proj);
    }

    gStyle->SetOptTitle(0); 
    gStyle->SetOptStat(0); 
    TCanvas* cADC = new TCanvas("cADC", "cADC", 800, 600);
    cADC->SetLogy();
    cADC->SetRightMargin(0.05);
    adcHists[0]->SetLineColor(TColor::GetColor(ColorStrings[0].c_str()));
    adcHists[0]->SetLineWidth(3);
    adcHists[0]->SetMarkerStyle(20);
    adcHists[0]->SetMarkerColor(TColor::GetColor(ColorStrings[0].c_str()));
    adcHists[0]->SetFillColor(TColor::GetColor(ColorStrings[0].c_str()));
    adcHists[0]->SetFillStyle(3004);
    adcHists[0]->GetXaxis()->SetTitle("ADC Per Channel");
    adcHists[0]->GetYaxis()->SetRangeUser(1, 1e10);
    adcHists[0]->GetXaxis()->SetRangeUser(0, 60);

    adcHists[0]->Draw();

    TLatex* cms = new TLatex(0.10,0.92,"#bf{ZDC} #it{Work in progress}");
    cms->SetNDC();
    cms->SetTextSize(0.05);
    cms->SetTextFont(42);



    for(int i = 1; i < nHists; i++){
        adcHists[i]->SetLineColor(TColor::GetColor(ColorStrings[i].c_str()));
        adcHists[i]->SetLineWidth(3);
        adcHists[i]->SetMarkerStyle(20);
        adcHists[i]->SetMarkerColor(TColor::GetColor(ColorStrings[i].c_str()));
        adcHists[i]->SetFillColor(TColor::GetColor(ColorStrings[i].c_str()));
        adcHists[i]->SetFillStyle(3004);
        adcHists[i]->Draw("same");
    }

    TLegend* legADC = new TLegend(0.16, 0.57, 0.7, 0.88);
    legADC->SetBorderSize(0);
    //legADC->SetNColumns(2);
    for (int i = 0; i < nHists; i++) {
        legADC->AddEntry(adcHists[i], Form("%s, #mu = %0.2f", namesNoSpace[i].c_str(),  adcHists[i]->GetMean()), "f");
    }
    legADC->SetTextSize(0.04);
    legADC->Draw();
    cms->Draw();

    cADC->SaveAs(Form("/Users/hannahbossi/Desktop/ZDCAnalyzer_USC_384226_PedestalDebug.pdf"));



}