//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Dec  6 13:52:39 2018 by ROOT version 6.14/06
// from TTree tree/Jet Tree Recoiling from Highest Et Tower
// found on file: p17.root
//////////////////////////////////////////////////////////

#ifndef EventTree_h
#define EventTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "TObject.h"
#include "TClonesArray.h"

class EventTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.
   static constexpr Int_t kMaxjets = 31;
   static constexpr Int_t kMaxch_tracks = 74;

   // Declaration of leaf types
 //Event           *event;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   Int_t           njets;
   Int_t           nch;
   Double_t        bbcAdcES;
   Double_t        zdcX;
   Int_t           runId;
   Double_t        refMult;
   Double_t        vz;
   Bool_t          trig_500001;
   Bool_t          trig_500006;
   Bool_t          trig_500018;
   Bool_t          trig_500202;
   Bool_t          trig_500206;
   Bool_t          trig_500215;
   Bool_t          trig_500904;
   Double_t        rho;
   Double_t        phi_Et;
   Double_t        eta_Et;
   Double_t        Et;
   Int_t           towId_Et;
   Int_t           jets_;
   UInt_t          jets_fUniqueID[kMaxjets];   //[jets_]
   UInt_t          jets_fBits[kMaxjets];   //[jets_]
   Double_t        jets_phi[kMaxjets];   //[jets_]
   Double_t        jets_eta[kMaxjets];   //[jets_]
   Double_t        jets_pt[kMaxjets];   //[jets_]
   Double_t        jets_area[kMaxjets];   //[jets_]
   Int_t           jets_nch[kMaxjets];   //[jets_]
   Int_t           ch_tracks_;
   UInt_t          ch_tracks_fUniqueID[kMaxch_tracks];   //[ch_tracks_]
   UInt_t          ch_tracks_fBits[kMaxch_tracks];   //[ch_tracks_]
   Double_t        ch_tracks_phi[kMaxch_tracks];   //[ch_tracks_]
   Double_t        ch_tracks_eta[kMaxch_tracks];   //[ch_tracks_]
   Double_t        ch_tracks_pt[kMaxch_tracks];   //[ch_tracks_]

   // List of branches
   TBranch        *b_event_fUniqueID;   //!
   TBranch        *b_event_fBits;   //!
   TBranch        *b_event_njets;   //!
   TBranch        *b_event_nch;   //!
   TBranch        *b_event_bbcAdcES;   //!
   TBranch        *b_event_zdcX;   //!
   TBranch        *b_event_runId;   //!
   TBranch        *b_event_refMult;   //!
   TBranch        *b_event_vz;   //!
   TBranch        *b_event_trig_500001;   //!
   TBranch        *b_event_trig_500006;   //!
   TBranch        *b_event_trig_500018;   //!
   TBranch        *b_event_trig_500202;   //!
   TBranch        *b_event_trig_500206;   //!
   TBranch        *b_event_trig_500215;   //!
   TBranch        *b_event_trig_500904;   //!
   TBranch        *b_event_rho;   //!
   TBranch        *b_event_phi_Et;   //!
   TBranch        *b_event_eta_Et;   //!
   TBranch        *b_event_Et;   //!
   TBranch        *b_event_towId_Et;   //!
   TBranch        *b_jets_;   //!
   TBranch        *b_jets_fUniqueID;   //!
   TBranch        *b_jets_fBits;   //!
   TBranch        *b_jets_phi;   //!
   TBranch        *b_jets_eta;   //!
   TBranch        *b_jets_pt;   //!
   TBranch        *b_jets_area;   //!
   TBranch        *b_jets_nch;   //!
   TBranch        *b_ch_tracks_;   //!
   TBranch        *b_ch_tracks_fUniqueID;   //!
   TBranch        *b_ch_tracks_fBits;   //!
   TBranch        *b_ch_tracks_phi;   //!
   TBranch        *b_ch_tracks_eta;   //!
   TBranch        *b_ch_tracks_pt;   //!

   EventTree(TTree *tree=0);
   virtual ~EventTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

