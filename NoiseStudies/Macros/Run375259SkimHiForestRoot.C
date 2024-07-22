#include <ROOT/TThreadExecutor.hxx>

void Run375259SkimHiForestRoot(){
    const unsigned int workers = 24;
    ROOT::TThreadExecutor pool(workers);
    static const int MAXEVT = 6000;

    auto job = [&](int jobIdx){
        TChain* chain1 = new TChain();
        TChain* chain2 = new TChain();
        TChain* chain3 = new TChain();
        TChain* chain4 = new TChain();
        TChain* chain5 = new TChain();
        for (int i = 1 ; i < 135 ; i++){
            if (i == 116) {continue;}
            chain1->Add(Form("/store/data/Runs_2023/375259/240112_203159/0000/HiForestMiniAOD_%i.root/hiEvtAnalyzer/HiTree", i));
            chain2->Add(Form("/store/data/Runs_2023/375259/240112_203159/0000/HiForestMiniAOD_%i.root/hltanalysis/HltTree", i));
            chain3->Add(Form("/store/data/Runs_2023/375259/240112_203159/0000/HiForestMiniAOD_%i.root/zdcanalyzer/zdcdigi", i));
            chain4->Add(Form("/store/data/Runs_2023/375259/240112_203159/0000/HiForestMiniAOD_%i.root/skimanalysis/HltTree", i));
            chain5->Add(Form("/store/data/Runs_2023/375259/240112_203159/0000/HiForestMiniAOD_%i.root/PbPbTracks/trackTree", i));
        }
        chain1->AddFriend(chain2);
        chain1->AddFriend(chain3);
        chain1->AddFriend(chain4);
        chain1->AddFriend(chain5);
        //TFile* fin = TFile::Open("/store/data/Runs_2023/375259/231024_191241/0000/HiForestMiniAOD_20.root");
        /*TTree* tin = (TTree*) chain1->Get("hiEvtAnalyzer/HiTree");
	    TTree* tin3 = (TTree*) chain1->Get("hltanalysis/HltTree");
        TTree* tin2 = (TTree*) chain1->Get("zdcanalyzer/zdcdigi");
	    TTree* tin4 = (TTree*) chain1->Get("skimanalysis/HltTree");
        TTree* tin5 = (TTree*) chain1->Get("PbPbTracks/trackTree");
        tin->SetBranchStatus("hiBin", 1);
        tin2->SetBranchStatus("*", 1);
	    tin3->SetBranchStatus("*", 1);
	    tin4->SetBranchStatus("*", 1);
        tin5->SetBranchStatus("*", 1);*/

        long long totEvt = chain1->GetEntries();
        int hiBin;
	int HIMinimumBias0;
	int HIMinimumBias1;
	int HIMinimumBias2;
	int HIMinimumBias3;
	int vertex_filter;
	int cluster_filter;
    int ZDC_HF_MB;
    int cent_30_50;
    int coinc_filter;
    float vz;

    chain1->SetBranchStatus("*", 1);
    chain1->SetBranchAddress("hiBin", &hiBin);
	chain1->SetBranchAddress("pprimaryVertexFilter", &vertex_filter);
	chain1->SetBranchAddress("pclusterCompatibilityFilter", &cluster_filter);
    chain1->SetBranchAddress("pphfCoincFilter2Th4", &coinc_filter);
    chain1->SetBranchAddress("vz", &vz);
	chain1->SetBranchAddress("Dataset_HIMinimumBias0", &HIMinimumBias0);
	chain1->SetBranchAddress("Dataset_HIMinimumBias1", &HIMinimumBias1);
	chain1->SetBranchAddress("Dataset_HIMinimumBias2", &HIMinimumBias2);
	chain1->SetBranchAddress("Dataset_HIMinimumBias3", &HIMinimumBias3);
    chain1->SetBranchAddress("HLT_HIMinimumBiasHF1ANDZDC1nOR_v1", &ZDC_HF_MB);
    chain1->SetBranchAddress("L1_Centrality_30_50_BptxAND", &cent_30_50);

        TFile* fout = new TFile(Form("/store/User/mwrotny/Run375259_MinBiasEvents%i.root", jobIdx), "recreate");
        TTree* tout = (TTree*) chain1->CloneTree(0);
        TTree* tout2 = (TTree*) chain5->CloneTree(0);
        TTree* tout3 = (TTree*) chain3->CloneTree(0);
        //TTree* tout2 = (TTree*) tin5->CloneTree(0);

        int numFilesPerWorker = totEvt / workers;
        int start = jobIdx*numFilesPerWorker;
        int end = (jobIdx+1)*numFilesPerWorker;
        //int end   = (jobIdx !=5) ? (jobIdx+1)*numFilesPerWorker : totEvt;
        for( auto ievt : ROOT::TSeqU(start, end)){
            //tin->GetEntry(ievt);
            //tin2->GetEntry(ievt);
	    //tin3->GetEntry(ievt);
	    //tin4->GetEntry(ievt);
            chain1->GetEntry(ievt);
            //chain5->GetEntry(ievt);
            //chain3->GetEntry(ievt);
            if( (ievt % 1000000) == 0 ){ std::cout << "Core["<< jobIdx<<"] Processing evt : "<< (ievt - start) << " / " << (end - start) << std::endl;
            }
            if(ZDC_HF_MB == 1){ 
                tout->Fill();
                tout2->Fill();
                tout3->Fill();
                //tout2->Fill();
            }
        }

        fout->Write();
        fout->Close();
        return 1;
    };


    auto res = pool.Map(job, ROOT::TSeqI(workers));
}
