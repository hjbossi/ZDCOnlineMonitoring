using namespace std;

float thiscEMHAD;

void DrawOneTH1(const char* name, const char* plotopt, int logy, int logx, double xmin, double xmax, TCanvas *c, TFile *f, const char* figdir, bool fit=false, double fitmin=0, double fitmax=0)
{
  c->SetLogx(logx);
  c->SetLogy(logy);
  TH1* thishist = (TH1F*)f->Get(name);
  thishist->SetLineColor(kBlack);
  if(logx && xmin<0) xmin = thishist->GetBinLowEdge(2);
  if(xmax<0) xmax = thishist->GetXaxis()->GetXmax();
  if(xmin<0) xmin = thishist->GetXaxis()->GetXmin();
  thishist->GetXaxis()->SetRangeUser(xmin,xmax);
  if(!thishist) { cerr << name << " missing." << endl; return ; }

  TFitResultPtr frp;
  if(fit)
  {
    TF1* fit = new TF1("fit","[0]*exp(-(x-[5]*1)*(x-[5]*1)/(2*[6]*1)) + [1]*exp(-(x-[5]*2)*(x-[5]*2)/(2*[6]*2)) +[2]*exp(-(x-[5]*3)*(x-[5]*3)/(2*[6]*3)) +[3]*exp(-(x-[5]*4)*(x-[5]*4)/(2*[6]*4))+[4]*exp(-(x-[5]*5)*(x-[5]*5)/(2*[6]*5))",4e3,40e3);
    fit->SetRange(fitmin,fitmax);
    fit->SetParLimits(0,0,10000);
    fit->SetParLimits(1,0,10000);
    fit->SetParLimits(2,0,10000);
    fit->SetParLimits(3,0,10000);
    fit->SetParLimits(4,0,10000);
    fit->SetParameter(0,400);
    fit->SetParameter(1,200);
    fit->SetParameter(2,10);
    fit->SetParameter(3,10);
    fit->SetParameter(4,10);
    fit->SetParameter(5,2500);
    fit->SetParameter(6,750*750);
    //fit->FixParameter(3,0);
    fit->FixParameter(4,0);
    frp = thishist->Fit("fit","RS");
  }
  thishist->Draw(plotopt);
  if(fit)
  {
    TLatex ltx;
    ltx.SetTextSize(0.05);
    ltx.DrawLatexNDC(0.5,0.80,Form("E_{0} = %.0f #pm %.0f",frp->Parameter(5),frp->ParError(5)));
    ltx.DrawLatexNDC(0.5,0.74,Form("#sigma = %.0f #pm %.0f",sqrt(frp->Parameter(6)),frp->ParError(6)/sqrt(frp->Parameter(6))/2));
    ltx.DrawLatexNDC(0.5,0.68,Form("resolution: %.4f",sqrt(frp->Parameter(6))/frp->Parameter(5)));
    cerr << "cEMHAD:\t" << thiscEMHAD << "\t" << sqrt(frp->Parameter(6))/frp->Parameter(5) << endl;
  }
  c->Print(Form("%s/fit_small_%s.TSfact40.png",figdir,name));
}

void DrawOneTH2(const char* name, const char* plotopt, int logz, float xmin, float xmax, TCanvas *c, TFile *f, const char* figdir)
{
  c->SetLogx(0);
  c->SetLogy(0);
  c->SetLogz(logz);
  TH2* thishist = (TH2F*)f->Get(name); 
  if(xmax<0) xmax = thishist->GetXaxis()->GetXmax();
  if(xmin<0) xmin = thishist->GetXaxis()->GetXmin();
  thishist->GetXaxis()->SetRangeUser(xmin,xmax);
  if(!thishist) { cerr << name << " missing." << endl; return ; }
  thishist->Draw(plotopt);
  c->Print(Form("%s/%s.png",figdir,name));
}


int Plot_analyze(char const *filename="histograms_L1Ntuple.374828_0-100000.root")
{
  TStyle* gStyle = new TStyle();
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  string tag(filename);
  tag.erase(tag.size()-5);
  size_t pos = tag.find_last_of('/');
  tag = (pos != std::string::npos) ? tag.substr(pos+1) : tag;

  TFile *f = new TFile(filename);

  TH1D* hZDCP = (TH1D*)f->Get("hZDCP");
  TH1D* hZDCM = (TH1D*)f->Get("hZDCM");
  TH1D* hZDCP_1n = (TH1D*)f->Get("hZDCP_1n");
  TH1D* hZDCM_1n = (TH1D*)f->Get("hZDCM_1n");

  TCanvas* c = new TCanvas("c","c",800,600);
  c->SetLogy(1);

  c->SetLogx(1);
  hZDCP->SetLineColor(kRed);
  hZDCM->SetLineColor(kBlue);
  hZDCP->SetLineWidth(2);
  hZDCM->SetLineWidth(2);
  hZDCM->GetXaxis()->SetRangeUser(1000,200000);;
  hZDCM->GetXaxis()->SetTitle("ZDC Sum");
  hZDCM->SetTitle("ZDC Energy, calibrated sum");
  hZDCM->Draw();
  hZDCP->Draw("same");
  c->SaveAs(Form("../figs/ZDCEnCalibPM_%s.png", tag.c_str()));

  c->SetLogx(0);
  hZDCP_1n->SetLineColor(kRed);
  hZDCM_1n->SetLineColor(kBlue);
  hZDCP_1n->SetLineWidth(2);
  hZDCM_1n->SetLineWidth(2);
  hZDCM_1n->GetXaxis()->SetRangeUser(1000,15000);
  hZDCM_1n->GetXaxis()->SetTitle("ZDC Sum");
  hZDCM_1n->SetTitle("ZDC Energy, calibrated sum");
  hZDCM_1n->Draw();
  hZDCP_1n->Draw("same");
  c->SaveAs(Form("../figs/ZDCEnCalibPM_1n_%s.png", tag.c_str()));

  DrawOneTH1("hZDCP_1n","e",1,0,1000,15000,c,f,"../figs",true, 1500,14000);
  DrawOneTH1("hZDCM_1n","e",1,0,1000,15000,c,f,"../figs",true, 1700,14000);
  const int NSide = 2; //0: plus, 1: minus
  const char* sSide[NSide] = {"P","M"};
  const int NEMHAD = 10;
  const float cEMHAD[NEMHAD][NSide] = {{0.08,0.08},{0.10,0.10},{0.12,0.12},{0.14,0.14},{0.16,0.16},{0.18,0.18},{0.20,0.20},{0.22,0.22},{0.24,0.24},{0.26,0.26}}; 
  const double fitmin[NSide] = {2500,2500}; //for the TSfactor=40% case
  //const double fitmin[NSide] = {1580,1580};
  for(int iSide=0;iSide<NSide;iSide++)
    for(int iEMHAD=0;iEMHAD<NEMHAD;iEMHAD++)
    {
      thiscEMHAD = cEMHAD[iEMHAD][iSide];
      DrawOneTH2(Form("ZDC%s_EMHAD_%i",sSide[iSide],iEMHAD),"COLZ",1,0,10000,c,f,"../figs");
      DrawOneTH1(Form("ZDC%s_1n_EMHAD_%i",sSide[iSide],iEMHAD),"e",1,0,1000,15000,c,f,"../figs",true, fitmin[iSide]-(9-iEMHAD)*10,11120-(9-iEMHAD)*15);
    }

  return 1;
}
