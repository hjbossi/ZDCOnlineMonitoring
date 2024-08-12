void analyzePedestalsOverTime(){
    TFile* inFileA = TFile::Open("/Users/hannahbossi/Desktop/ZDCAnalyzer_USC_383998.root"); 
    TFile* inFileB = TFile::Open("/Users/hannahbossi/Desktop/ZDCAnalyzer_USC_384153.root"); 

    std::vector<TFile*> files = {inFileA, inFileB}; 
    int nFiles = files.size(); 
    std::string namesNoSpace[20] = {"hZDCM_RPD4", "hZDCM_RPD5", "hZDCM_RPD6", "hZDCM_RPD7"};
    std::string ColorStrings[10] = {"#3f90da", "#ffa90e", "#bd1f01", "#94a4a2", "#832db6", "#a96b59", "#e76300", "#b9ac70", "#717581", "#92dadd"};//{"#5790fc", "#f89c20", "#e42536", "#964a8b", "#9c9ca1", "#7a21dd"};
    int nHists = 4; 

    gStyle->SetOptTitle(0); 
    gStyle->SetOptStat(0); 
    TCanvas* cADC = new TCanvas("cADC", "cADC", 800, 600);
    cADC->SetLogy();
    cADC->SetRightMargin(0.05);

    std::vector<TH1D*> adcHists; 
    for(int i = 0; i < nFiles; i++){
        TDirectoryFile* inDirect = (TDirectoryFile*)files.at(i)->Get("zdcana"); 
        TDirectoryFile* adcDirect = (TDirectoryFile*)inDirect->Get("ADC");
        for(int h = 0; h < nHists; h++){
            std::cout << "here h is " << h << std::endl;
            adcDirect->ls();
            int index; 
            if(h < nHists) index = h; 
            else index = h - nHists; 
            TH2D* twodHist = (TH2D*)adcDirect->Get(namesNoSpace[h].c_str());
            int tsBin = twodHist->GetXaxis()->FindBin(2.);  
            TH1D* proj = (TH1D*)twodHist->ProjectionY(Form("%s_proj_%d_%d", twodHist->GetName(), h, i), tsBin, tsBin); 
            adcHists.push_back(proj);
        }
    }


  



    adcHists[0]->SetLineColor(TColor::GetColor(ColorStrings[0].c_str()));
    adcHists[0]->SetLineWidth(3);
    adcHists[0]->SetMarkerStyle(20);
    adcHists[0]->SetMarkerColor(TColor::GetColor(ColorStrings[0].c_str()));
    //adcHists[0]->SetFillColor(TColor::GetColor(ColorStrings[0].c_str()));
    //adcHists[0]->SetFillStyle(3004);
    adcHists[0]->GetXaxis()->SetTitle("ADC Per Channel");
    adcHists[0]->GetYaxis()->SetRangeUser(1, 1e10);
    adcHists[0]->GetXaxis()->SetRangeUser(0, 60);
    adcHists[0]->Draw();

    TLatex* cms = new TLatex(0.10,0.92,"#bf{ZDC} #it{Work in progress}");
    cms->SetNDC();
    cms->SetTextSize(0.05);
    cms->SetTextFont(42);



    for(int i = 1; i < nHists*nFiles; i++){
        if (i < nHists){
            adcHists[i]->SetLineColor(TColor::GetColor(ColorStrings[i].c_str()));
            adcHists[i]->SetMarkerColor(TColor::GetColor(ColorStrings[i].c_str()));
        }
        else{
            adcHists[i]->SetLineColor(TColor::GetColor(ColorStrings[i-nHists].c_str()));
            adcHists[i]->SetMarkerColor(TColor::GetColor(ColorStrings[i-nHists].c_str()));
            adcHists[i]->SetLineStyle(7);

        }
      
        adcHists[i]->SetLineWidth(3);
        adcHists[i]->SetMarkerStyle(20);
       
        // adcHists[i]->SetFillColor(TColor::GetColor(ColorStrings[i].c_str()));
        adcHists[i]->Draw("same");
    }

    TLegend* legADC = new TLegend(0.16, 0.57, 0.7, 0.88);
    legADC->SetBorderSize(0);
    //legADC->SetNColumns(2);
    for (int i = 0; i < nHists*nFiles; i++) {
        else legADC->AddEntry(adcHists[i], Form("Run 384153, %s, #mu = %0.2f", namesNoSpace[i-nHists].c_str(),  adcHists[i]->GetMean()), "l");
        if(i < nHists)legADC->AddEntry(adcHists[i], Form("Run 383998, %s, #mu = %0.2f", namesNoSpace[i].c_str(),  adcHists[i]->GetMean()), "l");
    }
    legADC->SetTextSize(0.04);
    legADC->Draw();
    cms->Draw();

    cADC->SaveAs(Form("/Users/hannahbossi/Desktop/ZDCADCPerChannel_OverTime_ZDCM.pdf"));



}