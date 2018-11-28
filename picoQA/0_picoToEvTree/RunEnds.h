//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Nov 27 12:05:18 2018 by ROOT version 5.34/30
// from TTree RunEnds/Tree of first and last events per run
// found on file: test.root
//////////////////////////////////////////////////////////

#ifndef RunEnds_h
#define RunEnds_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <TObject.h>

// Fixed size dimensions of array or collections stored in the TTree if any.

class RunEnds {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
 //RunEnds         *RunEnds;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   Int_t           runId;
   Int_t           time_0;
   Int_t           time_1;
   Int_t           eventId_0;
   Int_t           eventId_1;
   Long64_t        nEvents;

   // List of branches
   TBranch        *b_RunEnds_fUniqueID;   //!
   TBranch        *b_RunEnds_fBits;   //!
   TBranch        *b_RunEnds_runId;   //!
   TBranch        *b_RunEnds_time_0;   //!
   TBranch        *b_RunEnds_time_1;   //!
   TBranch        *b_RunEnds_eventId_0;   //!
   TBranch        *b_RunEnds_eventId_1;   //!
   TBranch        *b_RunEnds_nEvents;   //!

   RunEnds(TTree *tree=0);
   virtual ~RunEnds();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef RunEnds_cxx
RunEnds::RunEnds(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("test.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("test.root");
      }
      f->GetObject("RunEnds",tree);

   }
   Init(tree);
}

RunEnds::~RunEnds()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t RunEnds::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t RunEnds::LoadTree(Long64_t entry)
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

void RunEnds::Init(TTree *tree)
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

   fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_RunEnds_fUniqueID);
   fChain->SetBranchAddress("fBits", &fBits, &b_RunEnds_fBits);
   fChain->SetBranchAddress("runId", &runId, &b_RunEnds_runId);
   fChain->SetBranchAddress("time_0", &time_0, &b_RunEnds_time_0);
   fChain->SetBranchAddress("time_1", &time_1, &b_RunEnds_time_1);
   fChain->SetBranchAddress("eventId_0", &eventId_0, &b_RunEnds_eventId_0);
   fChain->SetBranchAddress("eventId_1", &eventId_1, &b_RunEnds_eventId_1);
   fChain->SetBranchAddress("nEvents", &nEvents, &b_RunEnds_nEvents);
   Notify();
}

Bool_t RunEnds::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void RunEnds::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t RunEnds::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef RunEnds_cxx
