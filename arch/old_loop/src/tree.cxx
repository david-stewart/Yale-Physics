#include "tree.h"

tree::tree(std::vector<TString> options_,
           TTree *tree, 
           long long int nEvents_, 
           FILE* flog_,
           bool is_test_) :
    n_calc_events{0},
    options( options_ ),
    fChain(0), 
    nEvents{nEvents_},
    flog { flog_ },
    is_test { is_test_ }
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
    /* cout << "d0" << endl; */
    /* for (auto i : options) cout << " > " << i << "<|" << endl; */

    /* flog = fopen(log_name.Data(),"w"); */
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("temp.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("temp.root");
      }
      f->GetObject("tree",tree);

   }

   time(&start_time);
   fprintf(flog, " # running Init(tree), starting clock\n");
   Init(tree);
}

tree::~tree()
{
    fprintf(flog, "# Ending program\n");
    time(&end_time);
    double f_seconds { difftime(end_time, start_time) };
    int seconds { (int) f_seconds };
    int hr { seconds/3600 };
    int min { (seconds - 3600*hr)/60 };
    int sec { seconds - 3600*hr - 60*min };
    fprintf(flog," # Time ellapsed: %9i seconds or (in hr:min:sec) %02i:%02i:%02i\n",
            seconds, hr, min, sec);
    fprintf(flog, " # finished %lli events, for %8.4f sec/(1M events) \n", n_calc_events,
            1.E6 * f_seconds / n_calc_events);

    /* fprintf(flog, " # %8.4f sec/(1M events) \n", 1E6* f_seconds / (float) n_calc_events); */
    /* std::cout << "n_calc_events " << n_calc_events << " " << difftime(end_time, start_time) << std::endl; */

   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t tree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t tree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void tree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_event_fUniqueID);
   fChain->SetBranchAddress("fBits", &fBits, &b_event_fBits);
   fChain->SetBranchAddress("runId", &runId, &b_event_runId);
   fChain->SetBranchAddress("eventId", &eventId, &b_event_eventId);

   fChain->SetBranchAddress("trig_500001", &trig_500001, &b_event_trig_500001);
   fChain->SetBranchAddress("trig_500006", &trig_500006, &b_event_trig_500006);
   fChain->SetBranchAddress("trig_500018", &trig_500018, &b_event_trig_500018);
   fChain->SetBranchAddress("trig_500202", &trig_500202, &b_event_trig_500202);
   fChain->SetBranchAddress("trig_500206", &trig_500206, &b_event_trig_500206);
   fChain->SetBranchAddress("trig_500215", &trig_500215, &b_event_trig_500215);
   fChain->SetBranchAddress("trig_500808", &trig_500808, &b_event_trig_500808);
   fChain->SetBranchAddress("trig_500809", &trig_500809, &b_event_trig_500809);
   fChain->SetBranchAddress("trig_500904", &trig_500904, &b_event_trig_500904);

   fChain->SetBranchAddress("nGlobalTracks", &nGlobalTracks, &b_event_nGlobalTracks);
   fChain->SetBranchAddress("nTracks", &nTracks, &b_event_nTracks);
   fChain->SetBranchAddress("nPrimaryTracks", &nPrimaryTracks, &b_event_nPrimaryTracks);
   fChain->SetBranchAddress("nGoodPrimaryTracks", &nGoodPrimaryTracks, &b_event_nGoodPrimaryTracks);
   fChain->SetBranchAddress("nTofMatch", &nTofMatch, &b_event_nTofMatch);
   fChain->SetBranchAddress("ranking", &ranking, &b_event_ranking);
   fChain->SetBranchAddress("xPV", &xPV, &b_event_xPV);
   fChain->SetBranchAddress("yPV", &yPV, &b_event_yPV);
   fChain->SetBranchAddress("zPV", &zPV, &b_event_zPV);
   fChain->SetBranchAddress("zdcX", &zdcX, &b_event_zdcX);
   fChain->SetBranchAddress("bbcAdcES", &bbcAdcES, &b_event_bbcAdcES);
   fChain->SetBranchAddress("bbcAdcEL", &bbcAdcEL, &b_event_bbcAdcEL);
   fChain->SetBranchAddress("bbcAdcWS", &bbcAdcWS, &b_event_bbcAdcWS);
   fChain->SetBranchAddress("bbcAdcWL", &bbcAdcWL, &b_event_bbcAdcWL);
   fChain->SetBranchAddress("zdcSumAdcEast", &zdcSumAdcEast, &b_event_zdcSumAdcEast);
   fChain->SetBranchAddress("zdcSumAdcWest", &zdcSumAdcWest, &b_event_zdcSumAdcWest);
   fChain->SetBranchAddress("goodTrkRatio", &goodTrkRatio, &b_event_goodTrkRatio);
   fChain->SetBranchAddress("phiTrkMean", &phiTrkMean, &b_event_phiTrkMean);
   fChain->SetBranchAddress("etaTrkMean", &etaTrkMean, &b_event_etaTrkMean);
   fChain->SetBranchAddress("phiTrkLead", &phiTrkLead, &b_event_phiTrkLead);
   fChain->SetBranchAddress("etaTrkLead", &etaTrkLead, &b_event_etaTrkLead);
   fChain->SetBranchAddress("maxpt", &maxpt, &b_event_maxpt);
   fChain->SetBranchAddress("sumpt", &sumpt, &b_event_sumpt);
   fChain->SetBranchAddress("trigId", &trigId, &b_event_trigId);
   fChain->SetBranchAddress("ntowTriggers", &ntowTriggers, &b_event_ntowTriggers);
   fChain->SetBranchAddress("nHT1trigs", &nHT1trigs, &b_event_nHT1trigs);
   fChain->SetBranchAddress("nHT2trigs", &nHT2trigs, &b_event_nHT2trigs);
   fChain->SetBranchAddress("maxEt", &maxEt, &b_event_maxEt);
   fChain->SetBranchAddress("sumEt", &sumEt, &b_event_sumEt);
   fChain->SetBranchAddress("maxTowAdc", &maxTowAdc, &b_event_maxTowAdc);
   fChain->SetBranchAddress("sumTowAdc", &sumTowAdc, &b_event_sumTowAdc);
   fChain->SetBranchAddress("phiEt", &phiEt, &b_event_phiEt);
   fChain->SetBranchAddress("etaEt", &etaEt, &b_event_etaEt);
   fChain->SetBranchAddress("phiEtMean", &phiEtMean, &b_event_phiEtMean);
   fChain->SetBranchAddress("etaEtMean", &etaEtMean, &b_event_etaEtMean);
   fChain->SetBranchAddress("maxEt_is_maxAdc", &maxEt_is_maxAdc, &b_event_maxEt_is_maxAdc);
   Notify();
}

Bool_t tree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void tree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t tree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
