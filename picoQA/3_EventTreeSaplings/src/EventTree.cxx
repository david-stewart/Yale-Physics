#define EventTree_cxx
#include "EventTree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void EventTree::Loop()
{
//   In a ROOT session, you can do:
//      root> .L EventTree.C
//      root> EventTree t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
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

EventTree::EventTree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   /* if (tree == 0) { */
   /*    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("p17.root"); */
   /*    if (!f || !f->IsOpen()) { */
   /*       f = new TFile("p17.root"); */
   /*    } */
   /*    f->GetObject("tree",tree); */

   /* } */
   /* Init(tree); */
}

EventTree::~EventTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t EventTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t EventTree::LoadTree(Long64_t entry)
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

void EventTree::Init(TTree *tree)
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
   fChain->SetBranchAddress("njets", &njets, &b_event_njets);
   fChain->SetBranchAddress("nch", &nch, &b_event_nch);
   fChain->SetBranchAddress("bbcAdcES", &bbcAdcES, &b_event_bbcAdcES);
   fChain->SetBranchAddress("zdcX", &zdcX, &b_event_zdcX);
   fChain->SetBranchAddress("runId", &runId, &b_event_runId);
   fChain->SetBranchAddress("refMult", &refMult, &b_event_refMult);
   fChain->SetBranchAddress("vz", &vz, &b_event_vz);
   fChain->SetBranchAddress("trig_500001", &trig_500001, &b_event_trig_500001);
   fChain->SetBranchAddress("trig_500006", &trig_500006, &b_event_trig_500006);
   fChain->SetBranchAddress("trig_500018", &trig_500018, &b_event_trig_500018);
   fChain->SetBranchAddress("trig_500202", &trig_500202, &b_event_trig_500202);
   fChain->SetBranchAddress("trig_500206", &trig_500206, &b_event_trig_500206);
   fChain->SetBranchAddress("trig_500215", &trig_500215, &b_event_trig_500215);
   fChain->SetBranchAddress("trig_500904", &trig_500904, &b_event_trig_500904);
   fChain->SetBranchAddress("rho", &rho, &b_event_rho);
   fChain->SetBranchAddress("phi_Et", &phi_Et, &b_event_phi_Et);
   fChain->SetBranchAddress("eta_Et", &eta_Et, &b_event_eta_Et);
   fChain->SetBranchAddress("Et", &Et, &b_event_Et);
   fChain->SetBranchAddress("towId_Et", &towId_Et, &b_event_towId_Et);
   fChain->SetBranchAddress("jets", &jets_, &b_jets_);
   fChain->SetBranchAddress("jets.fUniqueID", jets_fUniqueID, &b_jets_fUniqueID);
   fChain->SetBranchAddress("jets.fBits", jets_fBits, &b_jets_fBits);
   fChain->SetBranchAddress("jets.phi", jets_phi, &b_jets_phi);
   fChain->SetBranchAddress("jets.eta", jets_eta, &b_jets_eta);
   fChain->SetBranchAddress("jets.pt", jets_pt, &b_jets_pt);
   fChain->SetBranchAddress("jets.area", jets_area, &b_jets_area);
   fChain->SetBranchAddress("jets.nch", jets_nch, &b_jets_nch);
   fChain->SetBranchAddress("ch_tracks", &ch_tracks_, &b_ch_tracks_);
   fChain->SetBranchAddress("ch_tracks.fUniqueID", ch_tracks_fUniqueID, &b_ch_tracks_fUniqueID);
   fChain->SetBranchAddress("ch_tracks.fBits", ch_tracks_fBits, &b_ch_tracks_fBits);
   fChain->SetBranchAddress("ch_tracks.phi", ch_tracks_phi, &b_ch_tracks_phi);
   fChain->SetBranchAddress("ch_tracks.eta", ch_tracks_eta, &b_ch_tracks_eta);
   fChain->SetBranchAddress("ch_tracks.pt", ch_tracks_pt, &b_ch_tracks_pt);
   Notify();
}

Bool_t EventTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void EventTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t EventTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
