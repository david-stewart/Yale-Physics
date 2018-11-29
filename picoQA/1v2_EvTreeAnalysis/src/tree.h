//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Nov  8 10:17:32 2018 by ROOT version 5.34/30
// from TTree tree/Tree of General Event Characteristics
// found on file: ../a.root
//////////////////////////////////////////////////////////

#ifndef tree_h
#define tree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <TObject.h>

// Fixed size dimensions of array or collections stored in the TTree if any.

class tree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
 //QA_event        *event;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   Int_t           runId;
   Int_t           eventId;
   Bool_t          trig_500001;
   Bool_t          trig_500006;
   Bool_t          trig_500018;
   Bool_t          trig_500202;
   Bool_t          trig_500206;
   Bool_t          trig_500215;
   Bool_t          trig_500808;
   Bool_t          trig_500809;
   Bool_t          trig_500904;
   Bool_t          trig_9300;
   Int_t           refmult;
   Int_t           nGlobalTracks;
   Int_t           nTracks;
   Int_t           nPrimaryTracks;
   Int_t           nGoodPrimaryTracks;
   Int_t           nTofMatch;
   Int_t           nIstHit;
   Int_t           nSstHit;
   Int_t           nPxl1Hit;
   Int_t           nPxl2Hit;
   Int_t           nHftHit;
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
   TBranch        *b_event_trig_500001;   //!
   TBranch        *b_event_trig_500006;   //!
   TBranch        *b_event_trig_500018;   //!
   TBranch        *b_event_trig_500202;   //!
   TBranch        *b_event_trig_500206;   //!
   TBranch        *b_event_trig_500215;   //!
   TBranch        *b_event_trig_500808;   //!
   TBranch        *b_event_trig_500809;   //!
   TBranch        *b_event_trig_500904;   //!
   TBranch        *b_event_trig_9300;   //!
   TBranch        *b_event_refmult;   //!
   TBranch        *b_event_nGlobalTracks;   //!
   TBranch        *b_event_nTracks;   //!
   TBranch        *b_event_nPrimaryTracks;   //!
   TBranch        *b_event_nGoodPrimaryTracks;   //!
   TBranch        *b_event_nTofMatch;   //!
   TBranch        *b_event_nIstHit;   //!
   TBranch        *b_event_nSstHit;   //!
   TBranch        *b_event_nPxl1Hit;   //!
   TBranch        *b_event_nPxl2Hit;   //!
   TBranch        *b_event_nHftHit;   //!
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

   tree(TTree *tree=0);
   virtual ~tree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif // #ifdef tree_cxx
