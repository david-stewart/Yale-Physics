//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Oct 31 16:22:57 2018 by ROOT version 5.34/30
// from TTree tree/Tree of General Event Characteristics
// found on file: temp.root
//////////////////////////////////////////////////////////

#ifndef tree_h
#define tree_h

#include "map_vals_per_line.h"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <map>
#include "TriggerCount.h"

// Header file for the classes stored in the TTree if any.
#include <TObject.h>

// Fixed size dimensions of array or collections stored in the TTree if any.

class tree {
    public :
    tree(  vector<TString> options, 
           TTree *tree=0, 
           long long int=-1, 
           const TString& log_name="log"
    );
    vector<TString> options;
    long long int event_limit;
    FILE* flog;

    int n_count; 
    TTree          *fChain;   //!pointer to the analyzed TTree or TChain
    Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   //QA_event        *event;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   Int_t           runId;
   Int_t           eventId;
   Bool_t          trig_500206;
   Bool_t          trig_470202;
   Bool_t          trig_480202;
   Bool_t          trig_490202;
   Bool_t          trig_500202;
   Bool_t          trig_510202;
   Bool_t          trig_470205;
   Bool_t          trig_480205;
   Bool_t          trig_490205;
   Bool_t          trig_500215;
   Bool_t          trig_500001;
   Bool_t          trig_500904;
   Bool_t          trig_510009;
   Int_t           nGlobalTracks;
   Int_t           nTracks;
   Int_t           nPrimaryTracks;
   Int_t           nGoodPrimaryTracks;
   Int_t           nTofMatch;
   Double_t        ranking;
   Double_t        xPV;
   Double_t        yPV;
   Double_t        zPV;
   Double_t        zdcX;
   Double_t        bbcAdcES;
   Double_t        bbcAdcEL;
   Double_t        bbcAdcWS;
   Double_t        bbcAdcWL;
   Double_t        zdcSumAdcEast;
   Double_t        zdcSumAdcWest;
   Double_t        goodTrkRatio;
   Double_t        phiTrkMean;
   Double_t        etaTrkMean;
   Double_t        phiTrkLead;
   Double_t        etaTrkLead;
   Double_t        maxpt;
   Double_t        sumpt;
   Int_t           trigId;
   Int_t           ntowTriggers;
   Int_t           nHT1trigs;
   Int_t           nHT2trigs;
   Double_t        maxEt;
   Double_t        sumEt;
   Double_t        maxTowAdc;
   Double_t        sumTowAdc;
   Double_t        phiEt;
   Double_t        etaEt;
   Double_t        phiEtMean;
   Double_t        etaEtMean;
   Bool_t          maxEt_is_maxAdc;

   // List of branches
   TBranch        *b_event_fUniqueID;   //!
   TBranch        *b_event_fBits;   //!
   TBranch        *b_event_runId;   //!
   TBranch        *b_event_eventId;   //!
   TBranch        *b_event_trig_500206;   //!
   TBranch        *b_event_trig_470202;   //!
   TBranch        *b_event_trig_480202;   //!
   TBranch        *b_event_trig_490202;   //!
   TBranch        *b_event_trig_500202;   //!
   TBranch        *b_event_trig_510202;   //!
   TBranch        *b_event_trig_470205;   //!
   TBranch        *b_event_trig_480205;   //!
   TBranch        *b_event_trig_490205;   //!
   TBranch        *b_event_trig_500215;   //!
   TBranch        *b_event_trig_500001;   //!
   TBranch        *b_event_trig_500904;   //!
   TBranch        *b_event_trig_510009;   //!
   TBranch        *b_event_nGlobalTracks;   //!
   TBranch        *b_event_nTracks;   //!
   TBranch        *b_event_nPrimaryTracks;   //!
   TBranch        *b_event_nGoodPrimaryTracks;   //!
   TBranch        *b_event_nTofMatch;   //!
   TBranch        *b_event_ranking;   //!
   TBranch        *b_event_xPV;   //!
   TBranch        *b_event_yPV;   //!
   TBranch        *b_event_zPV;   //!
   TBranch        *b_event_zdcX;   //!
   TBranch        *b_event_bbcAdcES;   //!
   TBranch        *b_event_bbcAdcEL;   //!
   TBranch        *b_event_bbcAdcWS;   //!
   TBranch        *b_event_bbcAdcWL;   //!
   TBranch        *b_event_zdcSumAdcEast;   //!
   TBranch        *b_event_zdcSumAdcWest;   //!
   TBranch        *b_event_goodTrkRatio;   //!
   TBranch        *b_event_phiTrkMean;   //!
   TBranch        *b_event_etaTrkMean;   //!
   TBranch        *b_event_phiTrkLead;   //!
   TBranch        *b_event_etaTrkLead;   //!
   TBranch        *b_event_maxpt;   //!
   TBranch        *b_event_sumpt;   //!
   TBranch        *b_event_trigId;   //!
   TBranch        *b_event_ntowTriggers;   //!
   TBranch        *b_event_nHT1trigs;   //!
   TBranch        *b_event_nHT2trigs;   //!
   TBranch        *b_event_maxEt;   //!
   TBranch        *b_event_sumEt;   //!
   TBranch        *b_event_maxTowAdc;   //!
   TBranch        *b_event_sumTowAdc;   //!
   TBranch        *b_event_phiEt;   //!
   TBranch        *b_event_etaEt;   //!
   TBranch        *b_event_phiEtMean;   //!
   TBranch        *b_event_etaEtMean;   //!
   TBranch        *b_event_maxEt_is_maxAdc;   //!

   virtual ~tree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   void     Loop_0(); // test loop
   void     Loop_1();
   void     Loop_2();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

};
#endif

#ifdef tree_cxx
tree::tree(vector<TString> in_options,
           TTree *tree, 
           long long int in_event_limit, 
           const TString& log_name) :
    options( in_options ),
    fChain(0), 
    event_limit{in_event_limit}
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
    /* cout << "d0" << endl; */
    /* for (auto i : options) cout << " > " << i << "<|" << endl; */

    flog = fopen(log_name.Data(),"w");
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("temp.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("temp.root");
      }
      f->GetObject("tree",tree);

   }
   Init(tree);
}

tree::~tree()
{
    fprintf(flog, "# Ending Program\n");
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
   fChain->SetBranchAddress("trig_500206", &trig_500206, &b_event_trig_500206);
   fChain->SetBranchAddress("trig_470202", &trig_470202, &b_event_trig_470202);
   fChain->SetBranchAddress("trig_480202", &trig_480202, &b_event_trig_480202);
   fChain->SetBranchAddress("trig_490202", &trig_490202, &b_event_trig_490202);
   fChain->SetBranchAddress("trig_500202", &trig_500202, &b_event_trig_500202);
   fChain->SetBranchAddress("trig_510202", &trig_510202, &b_event_trig_510202);
   fChain->SetBranchAddress("trig_470205", &trig_470205, &b_event_trig_470205);
   fChain->SetBranchAddress("trig_480205", &trig_480205, &b_event_trig_480205);
   fChain->SetBranchAddress("trig_490205", &trig_490205, &b_event_trig_490205);
   fChain->SetBranchAddress("trig_500215", &trig_500215, &b_event_trig_500215);
   fChain->SetBranchAddress("trig_500001", &trig_500001, &b_event_trig_500001);
   fChain->SetBranchAddress("trig_500904", &trig_500904, &b_event_trig_500904);
   fChain->SetBranchAddress("trig_510009", &trig_510009, &b_event_trig_510009);
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
#endif // #ifdef tree_cxx
