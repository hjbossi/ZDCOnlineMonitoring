void analyzePedestalsGlobal(std::string filename, int runNumber); // analyzer for global runs, uses ZDC analyzer
void analyzePedestalsLocal(TFile* inFile, int runNumber, bool doDummy); 
void analyzePedestals(); // main function
void FillChain(TChain &chain, std::string filename); 


/// main function to analyze pedestals 
void analyzePedstals(){
    std::string filename = "ZDCAnalyzer_USC_385962.root"; 
    TFile* inFile = TFile::Open(filename.c_str()); 
    bool isLocal = true; 
    int runNumber = 385962; 

    if(isLocal){
        std::cout << "~~~~~ Analyzing pedestals from a LOCAL run ~~~~~" << std::endl;
        analyzePedestalsLocal(inFile, runNumber, false);
    }
    else{
        std::cout << "~~~~~ Analyzing pedestals from a GLOBAL run ~~~~~" << std::endl;
        analyzePedestalsGlobal(filename, runNumber); 
    }

}


// ---------------------------------------------------------------------
/// ------------ analyze pedestals for global running -------------------
// ---------------------------------------------------------------------
void analyzePedestalsGlobal(std::string filename, int runNumber){
    
    TChain zdcChain("zdcanalyzer/zdcdigi");
    FillChain(zdcChain, filename);
    TTreeReader zdcReader(&zdcChain);
    TTreeReaderValue<float> sumPlus(zdcReader, "sumPlus");
    TTreeReaderValue<float> sumMinus(zdcReader, "sumMinus");
    TTreeReaderArray<int> z_side(zdcReader, "zside");
    TTreeReaderArray<int> sec(zdcReader, "section");
    TTreeReaderArray<int> ch(zdcReader, "channel");
    TTreeReaderArray<int> adc0(zdcReader, "adcTs0"); 
    TTreeReaderArray<int> adc1(zdcReader, "adcTs1"); 
    TTreeReaderArray<int> adc2(zdcReader, "adcTs2"); 
    TTreeReaderArray<int> adc3(zdcReader, "adcTs3"); 
    TTreeReaderArray<int> adc4(zdcReader, "adcTs4");
    TTreeReaderArray<int> adc5(zdcReader, "adcTs5");
    TTreeReaderValue<int> N(zdcReader, "n");

    std::string namesNoSpace[20] = {"hZDCM_EM1", "hZDCM_EM2", "hZDCM_EM3", "hZDCM_EM4",  "hZDCM_EM5",  "hZDCM_HAD1", "hZDCM_HAD2", "hZDCM_HAD3", "hZDCM_HAD4", "hZDCP_EM1", "hZDCP_EM2", "hZDCP_EM3", "hZDCP_EM4",  "hZDCP_EM5",  "hZDCP_HAD1", "hZDCP_HAD2", "hZDCP_HAD3", "hZDCP_HAD4"};
    int colors[20] = {kRed+2, kRed-4, kOrange+7, kOrange, kYellow-4, kSpring+10, kSpring, kGreen-3, kGreen+3, kTeal-7, kTeal, kAzure+10, kAzure-4, kBlue+2, kViolet+8, kViolet-1, kMagenta+1, kMagenta-4, kPink+7, kPink-4};
    std::string ColorStrings[10] = {"#3f90da", "#ffa90e", "#bd1f01", "#94a4a2", "#832db6", "#a96b59", "#e76300", "#b9ac70", "#717581", "#92dadd"};//{"#5790fc", "#f89c20", "#e42536", "#964a8b", "#9c9ca1", "#7a21dd"};
    std::vector<TH1D*> adcHists; 
    for(int h = 0; h < 18; h++){
        TH1D* adcHist = new TH1D(Form("ADC_%d", h), Form("ADC_%d", h), 255, 0, 255); 
        adcHists.push_back(adcHist); 
    }   

    Long64_t totalEvents = zdcReader.GetEntries(true);
    std::cout << "Total number of events " << totalEvents << std::endl;
    for (Long64_t i = 0; i < totalEvents; i++) {
        zdcReader.Next();
        for (int j = 0; j < *N; j++) {
            // require that we be on the plus or minus side
            if (z_side[j] != -1 && z_side[j] != 1)
                continue;
            // requre that it is EM or HAD
            if (sec[j] != 1 && sec[j] != 2)
                continue;
            // require that EM Channels are 1-5 and HAD channels are 1-4
            if (sec[j] == 1 && (ch[j] < 1 || ch[j] > 5))
                continue;
            if (sec[j] == 2 && (ch[j] < 1 || ch[j] > 4))
                continue;
            int idet = (z_side[j] == 1 ? 9 : 0) + (sec[j] == 2 ? 5 : 0) + (ch[j] - 1);
            adcHists.at(idet)->Fill(adc2[j]); 
        }
    }

    // now plot in the same style as before 
    gStyle->SetOptTitle(0); 
    gStyle->SetOptStat(0); 


    for(int i = 0; i < 18; i++){
        int colorIndex; 
        if(i > 9)colorIndex = i-9; 
        else colorIndex = i; 
        adcHists[i]->SetLineColor(TColor::GetColor(ColorStrings[colorIndex].c_str()));
        adcHists[i]->SetLineWidth(3);
        adcHists[i]->SetMarkerStyle(20);
        adcHists[i]->SetMarkerColor(TColor::GetColor(ColorStrings[colorIndex].c_str()));
        adcHists[i]->SetFillColor(TColor::GetColor(ColorStrings[colorIndex].c_str()));
        adcHists[i]->SetFillStyle(3004);
    }

    TCanvas* cADCMinus = new TCanvas("cADCMinus", "cADCMinus", 800, 600);
    cADCMinus->SetLogy();
    cADCMinus->SetRightMargin(0.05);
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
    TF1* fit = new TF1("fit1nM", "gaus",  0, 250);
    fit->SetLineColor(adcHists[0]->GetLineColor());
    fit->SetLineWidth(3);
    fit->SetLineStyle(2);
    fit->Draw("same");
    adcHists[0]->Fit(fit);



    TLegend* legADC = new TLegend(0.16, 0.57, 0.7, 0.88);
    legADC->SetBorderSize(0);
    legADC->SetTextSize(0.04);
    legADC->AddEntry(adcHists[0], Form("%s, #mu = %0.2f, #sigma = %0.2f", namesNoSpace[0].c_str(),fit->GetParameter(1), fit->GetParameter(2)), "f");


    for(int x = 1; x < 9; x++){
        adcHists[x]->Draw("same"); 
        TF1* fitPed = new TF1("fit1nM", "gaus",  0, 250);
        fitPed->SetLineColor(adcHists[x]->GetLineColor());
        fitPed->SetLineWidth(3);
        fitPed->SetLineStyle(2);
        adcHists[x]->Fit(fitPed); 
        fitPed->Draw("same");
        legADC->AddEntry(adcHists[x], Form("%s, #mu = %0.2f, #sigma = %0.2f", namesNoSpace[x].c_str(),fitPed->GetParameter(1), fitPed->GetParameter(2)), "f");

    }

    TLatex* cms = new TLatex(0.10,0.92,Form("#bf{ZDC} Run %d #it{Work in progress}", runNumber));
    cms->SetNDC();
    cms->SetTextSize(0.05);
    cms->SetTextFont(42);

    legADC->Draw();
    cms->Draw();
    cADCMinus->SaveAs(Form("ZDCAnalyzer_%d_Minus.pdf", runNumber));


    TCanvas* cADCPlus = new TCanvas("cADCPlus", "cADCPlus", 800, 600);
    cADCPlus->SetLogy();
    cADCPlus->SetRightMargin(0.05);
    adcHists[9]->SetLineColor(TColor::GetColor(ColorStrings[0].c_str()));
    adcHists[9]->SetLineWidth(3);
    adcHists[9]->SetMarkerStyle(20);
    adcHists[9]->SetMarkerColor(TColor::GetColor(ColorStrings[0].c_str()));
    adcHists[9]->SetFillColor(TColor::GetColor(ColorStrings[0].c_str()));
    adcHists[9]->SetFillStyle(3004);
    adcHists[9]->GetXaxis()->SetTitle("ADC Per Channel");
    adcHists[9]->GetYaxis()->SetRangeUser(1, 1e10);
    adcHists[9]->GetXaxis()->SetRangeUser(0, 60);
    adcHists[9]->Draw();
    cms->Draw(); 
    TLegend* legADCPlus = new TLegend(0.16, 0.57, 0.7, 0.88);
    legADCPlus->SetBorderSize(0);
    //legADC->SetNColumns(2);
     for(int x = 10; x < 18; x++){
        adcHists[x]->Draw("same");
    }
    for (int i = 9; i < 18; i++) {
        legADCPlus->AddEntry(adcHists[i], Form("%s, #mu = %0.2f", namesNoSpace[i].c_str(),  adcHists[i]->GetMean()), "f");
    }
    legADCPlus->SetTextSize(0.04);
    legADCPlus->Draw();
    cADCPlus->SaveAs(Form("ZDCAnalyzer_%d_Plus.pdf", runNumber));
}


// ---------------------------------------------------------------------
/// ------------ analyze pedestals for Local running -------------------
// ---------------------------------------------------------------------

void analyzePedestalsLocal(TFile* inFile , int runNumber, bool doDummy){
    TDirectoryFile* inDirect = (TDirectoryFile*)inFile->Get("zdcana"); 
    TDirectoryFile* adcDirect = (TDirectoryFile*)inDirect->Get("ADC");
    std::string namesNoSpace[20] = {"hZDCM_EM1", "hZDCM_EM2", "hZDCM_EM3", "hZDCM_EM4",  "hZDCM_EM5",  "hZDCM_HAD1", "hZDCM_HAD2", "hZDCM_HAD3", "hZDCM_HAD4", "hZDCP_EM1", "hZDCP_EM2", "hZDCP_EM3", "hZDCP_EM4",  "hZDCP_EM5",  "hZDCP_HAD1", "hZDCP_HAD2", "hZDCP_HAD3", "hZDCP_HAD4"};
    std::string namesNoSpaceDummy[20] = {"hZDCM_EM6", "hZDCM_EM7", "hZDCM_EM8", "hZDCM_RPD12", "hZDCM_RPD13", "hZDCM_RPD14", "hZDCM_RPD15", "hZDCP_EM6", "hZDCP_EM7", "hZDCP_EM8", "hZDCP_RPD12", "hZDCP_RPD13",  "hZDCP_RPD14",  "hZDCP_RPD15"};
    int colors[20] = {kRed+2, kRed-4, kOrange+7, kOrange, kYellow-4, kSpring+10, kSpring, kGreen-3, kGreen+3, kTeal-7, kTeal, kAzure+10, kAzure-4, kBlue+2, kViolet+8, kViolet-1, kMagenta+1, kMagenta-4, kPink+7, kPink-4};
    std::string ColorStrings[10] = {"#3f90da", "#ffa90e", "#bd1f01", "#94a4a2", "#832db6", "#a96b59", "#e76300", "#b9ac70", "#717581", "#92dadd"};//{"#5790fc", "#f89c20", "#e42536", "#964a8b", "#9c9ca1", "#7a21dd"};
    int nHists = 18; 
    if(doDummy){
        nHists = 14; 
    }

    // now get all the histograms
    std::vector<TH1D*> adcHists; 
    for(int h = 0; h < nHists; h++){
        adcDirect->ls(); 
        TH2D* twodHist; 
        if(doDummy) twodHist = (TH2D*)adcDirect->Get(namesNoSpaceDummy[h].c_str());
        else twodHist = (TH2D*)adcDirect->Get(namesNoSpace[h].c_str());
        int tsBin = twodHist->GetXaxis()->FindBin(2.);  
        TH1D* proj = (TH1D*)twodHist->ProjectionY(Form("%s_proj", twodHist->GetName()), tsBin, tsBin); 
        adcHists.push_back(proj);
    }

 // now plot in the same style as before 
    gStyle->SetOptTitle(0); 
    gStyle->SetOptStat(0); 


    for(int i = 0; i < nHists; i++){
        std::cout << "here " << i << std::endl;
        int colorIndex; 
        if(i > nHists/2)colorIndex = i-nHists/2; 
        else colorIndex = i; 
        adcHists[i]->SetLineColor(TColor::GetColor(ColorStrings[colorIndex].c_str()));
        adcHists[i]->SetLineWidth(3);
        adcHists[i]->SetMarkerStyle(20);
        adcHists[i]->SetMarkerColor(TColor::GetColor(ColorStrings[colorIndex].c_str()));
        adcHists[i]->SetFillColor(TColor::GetColor(ColorStrings[colorIndex].c_str()));
        adcHists[i]->SetFillStyle(3004);
    }

    TCanvas* cADCMinus = new TCanvas("cADCMinus", "cADCMinus", 800, 600);
    cADCMinus->SetLogy();
    cADCMinus->SetRightMargin(0.05);
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
    TF1* fit = new TF1("fit1nM", "gaus",  0, 250);
    fit->SetLineColor(adcHists[0]->GetLineColor());
    fit->SetLineWidth(3);
    fit->SetLineStyle(2);
    fit->Draw("same");
    adcHists[0]->Fit(fit);



    TLegend* legADC = new TLegend(0.16, 0.57, 0.7, 0.88);
    legADC->SetBorderSize(0);
    legADC->SetTextSize(0.04);
    if(doDummy)legADC->AddEntry(adcHists[0], Form("%s, #mu = %0.2f, #sigma = %0.2f", namesNoSpaceDummy[0].c_str(),fit->GetParameter(1), fit->GetParameter(2)), "f");
    else legADC->AddEntry(adcHists[0], Form("%s, #mu = %0.2f, #sigma = %0.2f", namesNoSpace[0].c_str(),fit->GetParameter(1), fit->GetParameter(2)), "f");


    for(int x = 1; x < nHists/2; x++){
        adcHists[x]->Draw("same"); 
        TF1* fitPed = new TF1("fit1nM", "gaus",  0, 60);
        fitPed->SetLineColor(adcHists[x]->GetLineColor());
        fitPed->SetLineWidth(3);
        fitPed->SetLineStyle(2);
        adcHists[x]->Fit(fitPed); 
        fitPed->Draw("same");
        if(doDummy) legADC->AddEntry(adcHists[x], Form("%s, #mu = %0.2f, #sigma = %0.2f", namesNoSpaceDummy[x].c_str(),fitPed->GetParameter(1), fitPed->GetParameter(2)), "f");
        else legADC->AddEntry(adcHists[x], Form("%s, #mu = %0.2f, #sigma = %0.2f", namesNoSpace[x].c_str(),fitPed->GetParameter(1), fitPed->GetParameter(2)), "f");

    }

    TLatex* cms = new TLatex(0.10,0.92,Form("#bf{ZDC} Run %d #it{Work in progress}", runNumber));
    cms->SetNDC();
    cms->SetTextSize(0.05);
    cms->SetTextFont(42);


    legADC->Draw();
    cms->Draw();
    if(doDummy)cADCMinus->SaveAs(Form("ZDCAnalyzer_%d_Minus_DUMMY.pdf", runNumber));
    else cADCMinus->SaveAs(Form("ZDCAnalyzer_%d_Minus.pdf", runNumber));


    TCanvas* cADCPlus = new TCanvas("cADCPlus", "cADCPlus", 800, 600);
    cADCPlus->SetLogy();
    cADCPlus->SetRightMargin(0.05);
    cADCPlus->cd(); 

    int index = nHists/2; 
    adcHists[index]->SetLineColor(TColor::GetColor(ColorStrings[0].c_str()));
    adcHists[index]->SetLineWidth(3);
    adcHists[index]->SetMarkerStyle(20);
    adcHists[index]->SetMarkerColor(TColor::GetColor(ColorStrings[0].c_str()));
    adcHists[index]->SetFillColor(TColor::GetColor(ColorStrings[0].c_str()));
    adcHists[index]->SetFillStyle(3004);
    adcHists[index]->GetXaxis()->SetTitle("ADC Per Channel");
    adcHists[index]->GetYaxis()->SetRangeUser(1, 1e10);
    adcHists[index]->GetXaxis()->SetRangeUser(0, 60);
    adcHists[index]->Draw();
    cms->Draw(); 
    TLegend* legADCPlus = new TLegend(0.16, 0.57, 0.7, 0.88);
    legADCPlus->SetBorderSize(0);
     for(int x = nHists/2; x < nHists; x++){
        adcHists[x]->Draw("same"); 
        TF1* fitPed = new TF1("fit1nP", "gaus",  0, 100);
        fitPed->SetLineColor(adcHists[x]->GetLineColor());
        fitPed->SetLineWidth(3);
        fitPed->SetLineStyle(2);
        adcHists[x]->Fit(fitPed); 
        fitPed->Draw("same");
        if(doDummy)legADCPlus->AddEntry(adcHists[x], Form("%s, #mu = %0.2f, #sigma = %0.2f", namesNoSpaceDummy[x].c_str(),fitPed->GetParameter(1), fitPed->GetParameter(2)), "f");
        else legADCPlus->AddEntry(adcHists[x], Form("%s, #mu = %0.2f, #sigma = %0.2f", namesNoSpace[x].c_str(),fitPed->GetParameter(1), fitPed->GetParameter(2)), "f");
     }
    legADCPlus->SetTextSize(0.04);
    legADCPlus->Draw();
    if(doDummy)cADCPlus->SaveAs(Form("ZDCAnalyzer_%d_Plus_DUMMY.pdf", runNumber));
    else cADCPlus->SaveAs(Form("ZDCAnalyzer_%d_Plus.pdf", runNumber));
}



void FillChain(TChain &chain, std::string filename) {
    chain.Add(filename.c_str());  
}