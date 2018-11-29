#define tree_cxx
#include "tree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void tree::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L tree.C
//      Root > tree t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
}

tree::tree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("a.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("a.root");
      }
      f->GetObject("tree",tree);

   }
   Init(tree);
}

tree::~tree()
{
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
   fChain->SetBranchAddress("trig_9300", &trig_9300, &b_event_trig_9300);
   fChain->SetBranchAddress("refmult", &refmult, &b_event_refmult);
   fChain->SetBranchAddress("nGlobalTracks", &nGlobalTracks, &b_event_nGlobalTracks);
   fChain->SetBranchAddress("nTracks", &nTracks, &b_event_nTracks);
   fChain->SetBranchAddress("nPrimaryTracks", &nPrimaryTracks, &b_event_nPrimaryTracks);
   fChain->SetBranchAddress("nGoodPrimaryTracks", &nGoodPrimaryTracks, &b_event_nGoodPrimaryTracks);
   fChain->SetBranchAddress("nTofMatch", &nTofMatch, &b_event_nTofMatch);
   fChain->SetBranchAddress("nIstHit", &nIstHit, &b_event_nIstHit);
   fChain->SetBranchAddress("nSstHit", &nSstHit, &b_event_nSstHit);
   fChain->SetBranchAddress("nPxl1Hit", &nPxl1Hit, &b_event_nPxl1Hit);
   fChain->SetBranchAddress("nPxl2Hit", &nPxl2Hit, &b_event_nPxl2Hit);
   fChain->SetBranchAddress("nHftHit", &nHftHit, &b_event_nHftHit);
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
