//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Nov 30 13:32:38 2018 by ROOT version 6.14/06
// from TTree VarStats/Statistics on observables per run
// found on file: ../logs/c_P16_1_20.root
//////////////////////////////////////////////////////////

#ifndef varclass_h
#define varclass_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class varclass {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           runId;
   Int_t           BBCMB;
   Int_t           BHT1_VPDMB_30;
   Int_t           BHT1_VPDMB_30_nobsmd;
   Int_t           BHT2_BBCMB;
   Int_t           FMS_JP2;
   Int_t           FMS_JP1;
   Int_t           VPDMB_30;
   Int_t           ZEROBIAS;
   Double_t        refmult_min;
   Double_t        refmult_max;
   Double_t        refmult_sum;
   Double_t        refmult_sum2;
   Long64_t        refmult_nEntries;
   Double_t        nGlobalTracks_min;
   Double_t        nGlobalTracks_max;
   Double_t        nGlobalTracks_sum;
   Double_t        nGlobalTracks_sum2;
   Long64_t        nGlobalTracks_nEntries;
   Double_t        nTracks_min;
   Double_t        nTracks_max;
   Double_t        nTracks_sum;
   Double_t        nTracks_sum2;
   Long64_t        nTracks_nEntries;
   Double_t        nPrimaryTracks_min;
   Double_t        nPrimaryTracks_max;
   Double_t        nPrimaryTracks_sum;
   Double_t        nPrimaryTracks_sum2;
   Long64_t        nPrimaryTracks_nEntries;
   Double_t        nGoodPrimaryTracks_min;
   Double_t        nGoodPrimaryTracks_max;
   Double_t        nGoodPrimaryTracks_sum;
   Double_t        nGoodPrimaryTracks_sum2;
   Long64_t        nGoodPrimaryTracks_nEntries;
   Double_t        nTofMatch_min;
   Double_t        nTofMatch_max;
   Double_t        nTofMatch_sum;
   Double_t        nTofMatch_sum2;
   Long64_t        nTofMatch_nEntries;
   Double_t        nIstHit_min;
   Double_t        nIstHit_max;
   Double_t        nIstHit_sum;
   Double_t        nIstHit_sum2;
   Long64_t        nIstHit_nEntries;
   Double_t        nSstHit_min;
   Double_t        nSstHit_max;
   Double_t        nSstHit_sum;
   Double_t        nSstHit_sum2;
   Long64_t        nSstHit_nEntries;
   Double_t        nPxl1Hit_min;
   Double_t        nPxl1Hit_max;
   Double_t        nPxl1Hit_sum;
   Double_t        nPxl1Hit_sum2;
   Long64_t        nPxl1Hit_nEntries;
   Double_t        nPxl2Hit_min;
   Double_t        nPxl2Hit_max;
   Double_t        nPxl2Hit_sum;
   Double_t        nPxl2Hit_sum2;
   Long64_t        nPxl2Hit_nEntries;
   Double_t        nHftHit_min;
   Double_t        nHftHit_max;
   Double_t        nHftHit_sum;
   Double_t        nHftHit_sum2;
   Long64_t        nHftHit_nEntries;
   Double_t        ranking_min;
   Double_t        ranking_max;
   Double_t        ranking_sum;
   Double_t        ranking_sum2;
   Long64_t        ranking_nEntries;
   Double_t        xPV_min;
   Double_t        xPV_max;
   Double_t        xPV_sum;
   Double_t        xPV_sum2;
   Long64_t        xPV_nEntries;
   Double_t        yPV_min;
   Double_t        yPV_max;
   Double_t        yPV_sum;
   Double_t        yPV_sum2;
   Long64_t        yPV_nEntries;
   Double_t        zPV_min;
   Double_t        zPV_max;
   Double_t        zPV_sum;
   Double_t        zPV_sum2;
   Long64_t        zPV_nEntries;
   Double_t        zdcX_min;
   Double_t        zdcX_max;
   Double_t        zdcX_sum;
   Double_t        zdcX_sum2;
   Long64_t        zdcX_nEntries;
   Double_t        bbcAdcES_min;
   Double_t        bbcAdcES_max;
   Double_t        bbcAdcES_sum;
   Double_t        bbcAdcES_sum2;
   Long64_t        bbcAdcES_nEntries;
   Double_t        bbcAdcEL_min;
   Double_t        bbcAdcEL_max;
   Double_t        bbcAdcEL_sum;
   Double_t        bbcAdcEL_sum2;
   Long64_t        bbcAdcEL_nEntries;
   Double_t        bbcAdcWS_min;
   Double_t        bbcAdcWS_max;
   Double_t        bbcAdcWS_sum;
   Double_t        bbcAdcWS_sum2;
   Long64_t        bbcAdcWS_nEntries;
   Double_t        bbcAdcWL_min;
   Double_t        bbcAdcWL_max;
   Double_t        bbcAdcWL_sum;
   Double_t        bbcAdcWL_sum2;
   Long64_t        bbcAdcWL_nEntries;
   Double_t        zdcSumAdcEast_min;
   Double_t        zdcSumAdcEast_max;
   Double_t        zdcSumAdcEast_sum;
   Double_t        zdcSumAdcEast_sum2;
   Long64_t        zdcSumAdcEast_nEntries;
   Double_t        zdcSumAdcWest_min;
   Double_t        zdcSumAdcWest_max;
   Double_t        zdcSumAdcWest_sum;
   Double_t        zdcSumAdcWest_sum2;
   Long64_t        zdcSumAdcWest_nEntries;
   Double_t        goodTrkRatio_min;
   Double_t        goodTrkRatio_max;
   Double_t        goodTrkRatio_sum;
   Double_t        goodTrkRatio_sum2;
   Long64_t        goodTrkRatio_nEntries;
   Double_t        phiTrkMean_min;
   Double_t        phiTrkMean_max;
   Double_t        phiTrkMean_sum;
   Double_t        phiTrkMean_sum2;
   Long64_t        phiTrkMean_nEntries;
   Double_t        etaTrkMean_min;
   Double_t        etaTrkMean_max;
   Double_t        etaTrkMean_sum;
   Double_t        etaTrkMean_sum2;
   Long64_t        etaTrkMean_nEntries;
   Double_t        phiTrkLead_min;
   Double_t        phiTrkLead_max;
   Double_t        phiTrkLead_sum;
   Double_t        phiTrkLead_sum2;
   Long64_t        phiTrkLead_nEntries;
   Double_t        etaTrkLead_min;
   Double_t        etaTrkLead_max;
   Double_t        etaTrkLead_sum;
   Double_t        etaTrkLead_sum2;
   Long64_t        etaTrkLead_nEntries;
   Double_t        maxpt_min;
   Double_t        maxpt_max;
   Double_t        maxpt_sum;
   Double_t        maxpt_sum2;
   Long64_t        maxpt_nEntries;
   Double_t        sumpt_min;
   Double_t        sumpt_max;
   Double_t        sumpt_sum;
   Double_t        sumpt_sum2;
   Long64_t        sumpt_nEntries;
   Double_t        ntowTriggers_min;
   Double_t        ntowTriggers_max;
   Double_t        ntowTriggers_sum;
   Double_t        ntowTriggers_sum2;
   Long64_t        ntowTriggers_nEntries;
   Double_t        nHT1trigs_min;
   Double_t        nHT1trigs_max;
   Double_t        nHT1trigs_sum;
   Double_t        nHT1trigs_sum2;
   Long64_t        nHT1trigs_nEntries;
   Double_t        nHT2trigs_min;
   Double_t        nHT2trigs_max;
   Double_t        nHT2trigs_sum;
   Double_t        nHT2trigs_sum2;
   Long64_t        nHT2trigs_nEntries;
   Double_t        maxEt_min;
   Double_t        maxEt_max;
   Double_t        maxEt_sum;
   Double_t        maxEt_sum2;
   Long64_t        maxEt_nEntries;
   Double_t        sumEt_min;
   Double_t        sumEt_max;
   Double_t        sumEt_sum;
   Double_t        sumEt_sum2;
   Long64_t        sumEt_nEntries;
   Double_t        maxTowAdc_min;
   Double_t        maxTowAdc_max;
   Double_t        maxTowAdc_sum;
   Double_t        maxTowAdc_sum2;
   Long64_t        maxTowAdc_nEntries;
   Double_t        sumTowAdc_min;
   Double_t        sumTowAdc_max;
   Double_t        sumTowAdc_sum;
   Double_t        sumTowAdc_sum2;
   Long64_t        sumTowAdc_nEntries;
   Double_t        phiEt_min;
   Double_t        phiEt_max;
   Double_t        phiEt_sum;
   Double_t        phiEt_sum2;
   Long64_t        phiEt_nEntries;
   Double_t        etaEt_min;
   Double_t        etaEt_max;
   Double_t        etaEt_sum;
   Double_t        etaEt_sum2;
   Long64_t        etaEt_nEntries;
   Double_t        phiEtMean_min;
   Double_t        phiEtMean_max;
   Double_t        phiEtMean_sum;
   Double_t        phiEtMean_sum2;
   Long64_t        phiEtMean_nEntries;
   Double_t        etaEtMean_min;
   Double_t        etaEtMean_max;
   Double_t        etaEtMean_sum;
   Double_t        etaEtMean_sum2;
   Long64_t        etaEtMean_nEntries;

   // List of branches
   TBranch        *b_runId;   //!
   TBranch        *b_BBCMB;   //!
   TBranch        *b_BHT1_VPDMB_30;   //!
   TBranch        *b_BHT1_VPDMB_30_nobsmd;   //!
   TBranch        *b_BHT2_BBCMB;   //!
   TBranch        *b_FMS_JP2;   //!
   TBranch        *b_FMS_JP1;   //!
   TBranch        *b_VPDMB_30;   //!
   TBranch        *b_ZEROBIAS;   //!
   TBranch        *b_refmult_min;   //!
   TBranch        *b_refmult_max;   //!
   TBranch        *b_refmult_sum;   //!
   TBranch        *b_refmult_sum2;   //!
   TBranch        *b_refmult_nEntries;   //!
   TBranch        *b_nGlobalTracks_min;   //!
   TBranch        *b_nGlobalTracks_max;   //!
   TBranch        *b_nGlobalTracks_sum;   //!
   TBranch        *b_nGlobalTracks_sum2;   //!
   TBranch        *b_nGlobalTracks_nEntries;   //!
   TBranch        *b_nTracks_min;   //!
   TBranch        *b_nTracks_max;   //!
   TBranch        *b_nTracks_sum;   //!
   TBranch        *b_nTracks_sum2;   //!
   TBranch        *b_nTracks_nEntries;   //!
   TBranch        *b_nPrimaryTracks_min;   //!
   TBranch        *b_nPrimaryTracks_max;   //!
   TBranch        *b_nPrimaryTracks_sum;   //!
   TBranch        *b_nPrimaryTracks_sum2;   //!
   TBranch        *b_nPrimaryTracks_nEntries;   //!
   TBranch        *b_nGoodPrimaryTracks_min;   //!
   TBranch        *b_nGoodPrimaryTracks_max;   //!
   TBranch        *b_nGoodPrimaryTracks_sum;   //!
   TBranch        *b_nGoodPrimaryTracks_sum2;   //!
   TBranch        *b_nGoodPrimaryTracks_nEntries;   //!
   TBranch        *b_nTofMatch_min;   //!
   TBranch        *b_nTofMatch_max;   //!
   TBranch        *b_nTofMatch_sum;   //!
   TBranch        *b_nTofMatch_sum2;   //!
   TBranch        *b_nTofMatch_nEntries;   //!
   TBranch        *b_nIstHit_min;   //!
   TBranch        *b_nIstHit_max;   //!
   TBranch        *b_nIstHit_sum;   //!
   TBranch        *b_nIstHit_sum2;   //!
   TBranch        *b_nIstHit_nEntries;   //!
   TBranch        *b_nSstHit_min;   //!
   TBranch        *b_nSstHit_max;   //!
   TBranch        *b_nSstHit_sum;   //!
   TBranch        *b_nSstHit_sum2;   //!
   TBranch        *b_nSstHit_nEntries;   //!
   TBranch        *b_nPxl1Hit_min;   //!
   TBranch        *b_nPxl1Hit_max;   //!
   TBranch        *b_nPxl1Hit_sum;   //!
   TBranch        *b_nPxl1Hit_sum2;   //!
   TBranch        *b_nPxl1Hit_nEntries;   //!
   TBranch        *b_nPxl2Hit_min;   //!
   TBranch        *b_nPxl2Hit_max;   //!
   TBranch        *b_nPxl2Hit_sum;   //!
   TBranch        *b_nPxl2Hit_sum2;   //!
   TBranch        *b_nPxl2Hit_nEntries;   //!
   TBranch        *b_nHftHit_min;   //!
   TBranch        *b_nHftHit_max;   //!
   TBranch        *b_nHftHit_sum;   //!
   TBranch        *b_nHftHit_sum2;   //!
   TBranch        *b_nHftHit_nEntries;   //!
   TBranch        *b_ranking_min;   //!
   TBranch        *b_ranking_max;   //!
   TBranch        *b_ranking_sum;   //!
   TBranch        *b_ranking_sum2;   //!
   TBranch        *b_ranking_nEntries;   //!
   TBranch        *b_xPV_min;   //!
   TBranch        *b_xPV_max;   //!
   TBranch        *b_xPV_sum;   //!
   TBranch        *b_xPV_sum2;   //!
   TBranch        *b_xPV_nEntries;   //!
   TBranch        *b_yPV_min;   //!
   TBranch        *b_yPV_max;   //!
   TBranch        *b_yPV_sum;   //!
   TBranch        *b_yPV_sum2;   //!
   TBranch        *b_yPV_nEntries;   //!
   TBranch        *b_zPV_min;   //!
   TBranch        *b_zPV_max;   //!
   TBranch        *b_zPV_sum;   //!
   TBranch        *b_zPV_sum2;   //!
   TBranch        *b_zPV_nEntries;   //!
   TBranch        *b_zdcX_min;   //!
   TBranch        *b_zdcX_max;   //!
   TBranch        *b_zdcX_sum;   //!
   TBranch        *b_zdcX_sum2;   //!
   TBranch        *b_zdcX_nEntries;   //!
   TBranch        *b_bbcAdcES_min;   //!
   TBranch        *b_bbcAdcES_max;   //!
   TBranch        *b_bbcAdcES_sum;   //!
   TBranch        *b_bbcAdcES_sum2;   //!
   TBranch        *b_bbcAdcES_nEntries;   //!
   TBranch        *b_bbcAdcEL_min;   //!
   TBranch        *b_bbcAdcEL_max;   //!
   TBranch        *b_bbcAdcEL_sum;   //!
   TBranch        *b_bbcAdcEL_sum2;   //!
   TBranch        *b_bbcAdcEL_nEntries;   //!
   TBranch        *b_bbcAdcWS_min;   //!
   TBranch        *b_bbcAdcWS_max;   //!
   TBranch        *b_bbcAdcWS_sum;   //!
   TBranch        *b_bbcAdcWS_sum2;   //!
   TBranch        *b_bbcAdcWS_nEntries;   //!
   TBranch        *b_bbcAdcWL_min;   //!
   TBranch        *b_bbcAdcWL_max;   //!
   TBranch        *b_bbcAdcWL_sum;   //!
   TBranch        *b_bbcAdcWL_sum2;   //!
   TBranch        *b_bbcAdcWL_nEntries;   //!
   TBranch        *b_zdcSumAdcEast_min;   //!
   TBranch        *b_zdcSumAdcEast_max;   //!
   TBranch        *b_zdcSumAdcEast_sum;   //!
   TBranch        *b_zdcSumAdcEast_sum2;   //!
   TBranch        *b_zdcSumAdcEast_nEntries;   //!
   TBranch        *b_zdcSumAdcWest_min;   //!
   TBranch        *b_zdcSumAdcWest_max;   //!
   TBranch        *b_zdcSumAdcWest_sum;   //!
   TBranch        *b_zdcSumAdcWest_sum2;   //!
   TBranch        *b_zdcSumAdcWest_nEntries;   //!
   TBranch        *b_goodTrkRatio_min;   //!
   TBranch        *b_goodTrkRatio_max;   //!
   TBranch        *b_goodTrkRatio_sum;   //!
   TBranch        *b_goodTrkRatio_sum2;   //!
   TBranch        *b_goodTrkRatio_nEntries;   //!
   TBranch        *b_phiTrkMean_min;   //!
   TBranch        *b_phiTrkMean_max;   //!
   TBranch        *b_phiTrkMean_sum;   //!
   TBranch        *b_phiTrkMean_sum2;   //!
   TBranch        *b_phiTrkMean_nEntries;   //!
   TBranch        *b_etaTrkMean_min;   //!
   TBranch        *b_etaTrkMean_max;   //!
   TBranch        *b_etaTrkMean_sum;   //!
   TBranch        *b_etaTrkMean_sum2;   //!
   TBranch        *b_etaTrkMean_nEntries;   //!
   TBranch        *b_phiTrkLead_min;   //!
   TBranch        *b_phiTrkLead_max;   //!
   TBranch        *b_phiTrkLead_sum;   //!
   TBranch        *b_phiTrkLead_sum2;   //!
   TBranch        *b_phiTrkLead_nEntries;   //!
   TBranch        *b_etaTrkLead_min;   //!
   TBranch        *b_etaTrkLead_max;   //!
   TBranch        *b_etaTrkLead_sum;   //!
   TBranch        *b_etaTrkLead_sum2;   //!
   TBranch        *b_etaTrkLead_nEntries;   //!
   TBranch        *b_maxpt_min;   //!
   TBranch        *b_maxpt_max;   //!
   TBranch        *b_maxpt_sum;   //!
   TBranch        *b_maxpt_sum2;   //!
   TBranch        *b_maxpt_nEntries;   //!
   TBranch        *b_sumpt_min;   //!
   TBranch        *b_sumpt_max;   //!
   TBranch        *b_sumpt_sum;   //!
   TBranch        *b_sumpt_sum2;   //!
   TBranch        *b_sumpt_nEntries;   //!
   TBranch        *b_ntowTriggers_min;   //!
   TBranch        *b_ntowTriggers_max;   //!
   TBranch        *b_ntowTriggers_sum;   //!
   TBranch        *b_ntowTriggers_sum2;   //!
   TBranch        *b_ntowTriggers_nEntries;   //!
   TBranch        *b_nHT1trigs_min;   //!
   TBranch        *b_nHT1trigs_max;   //!
   TBranch        *b_nHT1trigs_sum;   //!
   TBranch        *b_nHT1trigs_sum2;   //!
   TBranch        *b_nHT1trigs_nEntries;   //!
   TBranch        *b_nHT2trigs_min;   //!
   TBranch        *b_nHT2trigs_max;   //!
   TBranch        *b_nHT2trigs_sum;   //!
   TBranch        *b_nHT2trigs_sum2;   //!
   TBranch        *b_nHT2trigs_nEntries;   //!
   TBranch        *b_maxEt_min;   //!
   TBranch        *b_maxEt_max;   //!
   TBranch        *b_maxEt_sum;   //!
   TBranch        *b_maxEt_sum2;   //!
   TBranch        *b_maxEt_nEntries;   //!
   TBranch        *b_sumEt_min;   //!
   TBranch        *b_sumEt_max;   //!
   TBranch        *b_sumEt_sum;   //!
   TBranch        *b_sumEt_sum2;   //!
   TBranch        *b_sumEt_nEntries;   //!
   TBranch        *b_maxTowAdc_min;   //!
   TBranch        *b_maxTowAdc_max;   //!
   TBranch        *b_maxTowAdc_sum;   //!
   TBranch        *b_maxTowAdc_sum2;   //!
   TBranch        *b_maxTowAdc_nEntries;   //!
   TBranch        *b_sumTowAdc_min;   //!
   TBranch        *b_sumTowAdc_max;   //!
   TBranch        *b_sumTowAdc_sum;   //!
   TBranch        *b_sumTowAdc_sum2;   //!
   TBranch        *b_sumTowAdc_nEntries;   //!
   TBranch        *b_phiEt_min;   //!
   TBranch        *b_phiEt_max;   //!
   TBranch        *b_phiEt_sum;   //!
   TBranch        *b_phiEt_sum2;   //!
   TBranch        *b_phiEt_nEntries;   //!
   TBranch        *b_etaEt_min;   //!
   TBranch        *b_etaEt_max;   //!
   TBranch        *b_etaEt_sum;   //!
   TBranch        *b_etaEt_sum2;   //!
   TBranch        *b_etaEt_nEntries;   //!
   TBranch        *b_phiEtMean_min;   //!
   TBranch        *b_phiEtMean_max;   //!
   TBranch        *b_phiEtMean_sum;   //!
   TBranch        *b_phiEtMean_sum2;   //!
   TBranch        *b_phiEtMean_nEntries;   //!
   TBranch        *b_etaEtMean_min;   //!
   TBranch        *b_etaEtMean_max;   //!
   TBranch        *b_etaEtMean_sum;   //!
   TBranch        *b_etaEtMean_sum2;   //!
   TBranch        *b_etaEtMean_nEntries;   //!

   varclass(TTree *tree=0);
   virtual ~varclass();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef varclass_cxx
varclass::varclass(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../logs/c_P16_1_20.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("../logs/c_P16_1_20.root");
      }
      f->GetObject("VarStats",tree);

   }
   Init(tree);
}

varclass::~varclass()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t varclass::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t varclass::LoadTree(Long64_t entry)
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

void varclass::Init(TTree *tree)
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

   fChain->SetBranchAddress("runId", &runId, &b_runId);
   fChain->SetBranchAddress("BBCMB", &BBCMB, &b_BBCMB);
   fChain->SetBranchAddress("BHT1_VPDMB_30", &BHT1_VPDMB_30, &b_BHT1_VPDMB_30);
   fChain->SetBranchAddress("BHT1_VPDMB_30_nobsmd", &BHT1_VPDMB_30_nobsmd, &b_BHT1_VPDMB_30_nobsmd);
   fChain->SetBranchAddress("BHT2_BBCMB", &BHT2_BBCMB, &b_BHT2_BBCMB);
   fChain->SetBranchAddress("FMS_JP2", &FMS_JP2, &b_FMS_JP2);
   fChain->SetBranchAddress("FMS_JP1", &FMS_JP1, &b_FMS_JP1);
   fChain->SetBranchAddress("VPDMB_30", &VPDMB_30, &b_VPDMB_30);
   fChain->SetBranchAddress("ZEROBIAS", &ZEROBIAS, &b_ZEROBIAS);
   fChain->SetBranchAddress("refmult_min", &refmult_min, &b_refmult_min);
   fChain->SetBranchAddress("refmult_max", &refmult_max, &b_refmult_max);
   fChain->SetBranchAddress("refmult_sum", &refmult_sum, &b_refmult_sum);
   fChain->SetBranchAddress("refmult_sum2", &refmult_sum2, &b_refmult_sum2);
   fChain->SetBranchAddress("refmult_nEntries", &refmult_nEntries, &b_refmult_nEntries);
   fChain->SetBranchAddress("nGlobalTracks_min", &nGlobalTracks_min, &b_nGlobalTracks_min);
   fChain->SetBranchAddress("nGlobalTracks_max", &nGlobalTracks_max, &b_nGlobalTracks_max);
   fChain->SetBranchAddress("nGlobalTracks_sum", &nGlobalTracks_sum, &b_nGlobalTracks_sum);
   fChain->SetBranchAddress("nGlobalTracks_sum2", &nGlobalTracks_sum2, &b_nGlobalTracks_sum2);
   fChain->SetBranchAddress("nGlobalTracks_nEntries", &nGlobalTracks_nEntries, &b_nGlobalTracks_nEntries);
   fChain->SetBranchAddress("nTracks_min", &nTracks_min, &b_nTracks_min);
   fChain->SetBranchAddress("nTracks_max", &nTracks_max, &b_nTracks_max);
   fChain->SetBranchAddress("nTracks_sum", &nTracks_sum, &b_nTracks_sum);
   fChain->SetBranchAddress("nTracks_sum2", &nTracks_sum2, &b_nTracks_sum2);
   fChain->SetBranchAddress("nTracks_nEntries", &nTracks_nEntries, &b_nTracks_nEntries);
   fChain->SetBranchAddress("nPrimaryTracks_min", &nPrimaryTracks_min, &b_nPrimaryTracks_min);
   fChain->SetBranchAddress("nPrimaryTracks_max", &nPrimaryTracks_max, &b_nPrimaryTracks_max);
   fChain->SetBranchAddress("nPrimaryTracks_sum", &nPrimaryTracks_sum, &b_nPrimaryTracks_sum);
   fChain->SetBranchAddress("nPrimaryTracks_sum2", &nPrimaryTracks_sum2, &b_nPrimaryTracks_sum2);
   fChain->SetBranchAddress("nPrimaryTracks_nEntries", &nPrimaryTracks_nEntries, &b_nPrimaryTracks_nEntries);
   fChain->SetBranchAddress("nGoodPrimaryTracks_min", &nGoodPrimaryTracks_min, &b_nGoodPrimaryTracks_min);
   fChain->SetBranchAddress("nGoodPrimaryTracks_max", &nGoodPrimaryTracks_max, &b_nGoodPrimaryTracks_max);
   fChain->SetBranchAddress("nGoodPrimaryTracks_sum", &nGoodPrimaryTracks_sum, &b_nGoodPrimaryTracks_sum);
   fChain->SetBranchAddress("nGoodPrimaryTracks_sum2", &nGoodPrimaryTracks_sum2, &b_nGoodPrimaryTracks_sum2);
   fChain->SetBranchAddress("nGoodPrimaryTracks_nEntries", &nGoodPrimaryTracks_nEntries, &b_nGoodPrimaryTracks_nEntries);
   fChain->SetBranchAddress("nTofMatch_min", &nTofMatch_min, &b_nTofMatch_min);
   fChain->SetBranchAddress("nTofMatch_max", &nTofMatch_max, &b_nTofMatch_max);
   fChain->SetBranchAddress("nTofMatch_sum", &nTofMatch_sum, &b_nTofMatch_sum);
   fChain->SetBranchAddress("nTofMatch_sum2", &nTofMatch_sum2, &b_nTofMatch_sum2);
   fChain->SetBranchAddress("nTofMatch_nEntries", &nTofMatch_nEntries, &b_nTofMatch_nEntries);
   fChain->SetBranchAddress("nIstHit_min", &nIstHit_min, &b_nIstHit_min);
   fChain->SetBranchAddress("nIstHit_max", &nIstHit_max, &b_nIstHit_max);
   fChain->SetBranchAddress("nIstHit_sum", &nIstHit_sum, &b_nIstHit_sum);
   fChain->SetBranchAddress("nIstHit_sum2", &nIstHit_sum2, &b_nIstHit_sum2);
   fChain->SetBranchAddress("nIstHit_nEntries", &nIstHit_nEntries, &b_nIstHit_nEntries);
   fChain->SetBranchAddress("nSstHit_min", &nSstHit_min, &b_nSstHit_min);
   fChain->SetBranchAddress("nSstHit_max", &nSstHit_max, &b_nSstHit_max);
   fChain->SetBranchAddress("nSstHit_sum", &nSstHit_sum, &b_nSstHit_sum);
   fChain->SetBranchAddress("nSstHit_sum2", &nSstHit_sum2, &b_nSstHit_sum2);
   fChain->SetBranchAddress("nSstHit_nEntries", &nSstHit_nEntries, &b_nSstHit_nEntries);
   fChain->SetBranchAddress("nPxl1Hit_min", &nPxl1Hit_min, &b_nPxl1Hit_min);
   fChain->SetBranchAddress("nPxl1Hit_max", &nPxl1Hit_max, &b_nPxl1Hit_max);
   fChain->SetBranchAddress("nPxl1Hit_sum", &nPxl1Hit_sum, &b_nPxl1Hit_sum);
   fChain->SetBranchAddress("nPxl1Hit_sum2", &nPxl1Hit_sum2, &b_nPxl1Hit_sum2);
   fChain->SetBranchAddress("nPxl1Hit_nEntries", &nPxl1Hit_nEntries, &b_nPxl1Hit_nEntries);
   fChain->SetBranchAddress("nPxl2Hit_min", &nPxl2Hit_min, &b_nPxl2Hit_min);
   fChain->SetBranchAddress("nPxl2Hit_max", &nPxl2Hit_max, &b_nPxl2Hit_max);
   fChain->SetBranchAddress("nPxl2Hit_sum", &nPxl2Hit_sum, &b_nPxl2Hit_sum);
   fChain->SetBranchAddress("nPxl2Hit_sum2", &nPxl2Hit_sum2, &b_nPxl2Hit_sum2);
   fChain->SetBranchAddress("nPxl2Hit_nEntries", &nPxl2Hit_nEntries, &b_nPxl2Hit_nEntries);
   fChain->SetBranchAddress("nHftHit_min", &nHftHit_min, &b_nHftHit_min);
   fChain->SetBranchAddress("nHftHit_max", &nHftHit_max, &b_nHftHit_max);
   fChain->SetBranchAddress("nHftHit_sum", &nHftHit_sum, &b_nHftHit_sum);
   fChain->SetBranchAddress("nHftHit_sum2", &nHftHit_sum2, &b_nHftHit_sum2);
   fChain->SetBranchAddress("nHftHit_nEntries", &nHftHit_nEntries, &b_nHftHit_nEntries);
   fChain->SetBranchAddress("ranking_min", &ranking_min, &b_ranking_min);
   fChain->SetBranchAddress("ranking_max", &ranking_max, &b_ranking_max);
   fChain->SetBranchAddress("ranking_sum", &ranking_sum, &b_ranking_sum);
   fChain->SetBranchAddress("ranking_sum2", &ranking_sum2, &b_ranking_sum2);
   fChain->SetBranchAddress("ranking_nEntries", &ranking_nEntries, &b_ranking_nEntries);
   fChain->SetBranchAddress("xPV_min", &xPV_min, &b_xPV_min);
   fChain->SetBranchAddress("xPV_max", &xPV_max, &b_xPV_max);
   fChain->SetBranchAddress("xPV_sum", &xPV_sum, &b_xPV_sum);
   fChain->SetBranchAddress("xPV_sum2", &xPV_sum2, &b_xPV_sum2);
   fChain->SetBranchAddress("xPV_nEntries", &xPV_nEntries, &b_xPV_nEntries);
   fChain->SetBranchAddress("yPV_min", &yPV_min, &b_yPV_min);
   fChain->SetBranchAddress("yPV_max", &yPV_max, &b_yPV_max);
   fChain->SetBranchAddress("yPV_sum", &yPV_sum, &b_yPV_sum);
   fChain->SetBranchAddress("yPV_sum2", &yPV_sum2, &b_yPV_sum2);
   fChain->SetBranchAddress("yPV_nEntries", &yPV_nEntries, &b_yPV_nEntries);
   fChain->SetBranchAddress("zPV_min", &zPV_min, &b_zPV_min);
   fChain->SetBranchAddress("zPV_max", &zPV_max, &b_zPV_max);
   fChain->SetBranchAddress("zPV_sum", &zPV_sum, &b_zPV_sum);
   fChain->SetBranchAddress("zPV_sum2", &zPV_sum2, &b_zPV_sum2);
   fChain->SetBranchAddress("zPV_nEntries", &zPV_nEntries, &b_zPV_nEntries);
   fChain->SetBranchAddress("zdcX_min", &zdcX_min, &b_zdcX_min);
   fChain->SetBranchAddress("zdcX_max", &zdcX_max, &b_zdcX_max);
   fChain->SetBranchAddress("zdcX_sum", &zdcX_sum, &b_zdcX_sum);
   fChain->SetBranchAddress("zdcX_sum2", &zdcX_sum2, &b_zdcX_sum2);
   fChain->SetBranchAddress("zdcX_nEntries", &zdcX_nEntries, &b_zdcX_nEntries);
   fChain->SetBranchAddress("bbcAdcES_min", &bbcAdcES_min, &b_bbcAdcES_min);
   fChain->SetBranchAddress("bbcAdcES_max", &bbcAdcES_max, &b_bbcAdcES_max);
   fChain->SetBranchAddress("bbcAdcES_sum", &bbcAdcES_sum, &b_bbcAdcES_sum);
   fChain->SetBranchAddress("bbcAdcES_sum2", &bbcAdcES_sum2, &b_bbcAdcES_sum2);
   fChain->SetBranchAddress("bbcAdcES_nEntries", &bbcAdcES_nEntries, &b_bbcAdcES_nEntries);
   fChain->SetBranchAddress("bbcAdcEL_min", &bbcAdcEL_min, &b_bbcAdcEL_min);
   fChain->SetBranchAddress("bbcAdcEL_max", &bbcAdcEL_max, &b_bbcAdcEL_max);
   fChain->SetBranchAddress("bbcAdcEL_sum", &bbcAdcEL_sum, &b_bbcAdcEL_sum);
   fChain->SetBranchAddress("bbcAdcEL_sum2", &bbcAdcEL_sum2, &b_bbcAdcEL_sum2);
   fChain->SetBranchAddress("bbcAdcEL_nEntries", &bbcAdcEL_nEntries, &b_bbcAdcEL_nEntries);
   fChain->SetBranchAddress("bbcAdcWS_min", &bbcAdcWS_min, &b_bbcAdcWS_min);
   fChain->SetBranchAddress("bbcAdcWS_max", &bbcAdcWS_max, &b_bbcAdcWS_max);
   fChain->SetBranchAddress("bbcAdcWS_sum", &bbcAdcWS_sum, &b_bbcAdcWS_sum);
   fChain->SetBranchAddress("bbcAdcWS_sum2", &bbcAdcWS_sum2, &b_bbcAdcWS_sum2);
   fChain->SetBranchAddress("bbcAdcWS_nEntries", &bbcAdcWS_nEntries, &b_bbcAdcWS_nEntries);
   fChain->SetBranchAddress("bbcAdcWL_min", &bbcAdcWL_min, &b_bbcAdcWL_min);
   fChain->SetBranchAddress("bbcAdcWL_max", &bbcAdcWL_max, &b_bbcAdcWL_max);
   fChain->SetBranchAddress("bbcAdcWL_sum", &bbcAdcWL_sum, &b_bbcAdcWL_sum);
   fChain->SetBranchAddress("bbcAdcWL_sum2", &bbcAdcWL_sum2, &b_bbcAdcWL_sum2);
   fChain->SetBranchAddress("bbcAdcWL_nEntries", &bbcAdcWL_nEntries, &b_bbcAdcWL_nEntries);
   fChain->SetBranchAddress("zdcSumAdcEast_min", &zdcSumAdcEast_min, &b_zdcSumAdcEast_min);
   fChain->SetBranchAddress("zdcSumAdcEast_max", &zdcSumAdcEast_max, &b_zdcSumAdcEast_max);
   fChain->SetBranchAddress("zdcSumAdcEast_sum", &zdcSumAdcEast_sum, &b_zdcSumAdcEast_sum);
   fChain->SetBranchAddress("zdcSumAdcEast_sum2", &zdcSumAdcEast_sum2, &b_zdcSumAdcEast_sum2);
   fChain->SetBranchAddress("zdcSumAdcEast_nEntries", &zdcSumAdcEast_nEntries, &b_zdcSumAdcEast_nEntries);
   fChain->SetBranchAddress("zdcSumAdcWest_min", &zdcSumAdcWest_min, &b_zdcSumAdcWest_min);
   fChain->SetBranchAddress("zdcSumAdcWest_max", &zdcSumAdcWest_max, &b_zdcSumAdcWest_max);
   fChain->SetBranchAddress("zdcSumAdcWest_sum", &zdcSumAdcWest_sum, &b_zdcSumAdcWest_sum);
   fChain->SetBranchAddress("zdcSumAdcWest_sum2", &zdcSumAdcWest_sum2, &b_zdcSumAdcWest_sum2);
   fChain->SetBranchAddress("zdcSumAdcWest_nEntries", &zdcSumAdcWest_nEntries, &b_zdcSumAdcWest_nEntries);
   fChain->SetBranchAddress("goodTrkRatio_min", &goodTrkRatio_min, &b_goodTrkRatio_min);
   fChain->SetBranchAddress("goodTrkRatio_max", &goodTrkRatio_max, &b_goodTrkRatio_max);
   fChain->SetBranchAddress("goodTrkRatio_sum", &goodTrkRatio_sum, &b_goodTrkRatio_sum);
   fChain->SetBranchAddress("goodTrkRatio_sum2", &goodTrkRatio_sum2, &b_goodTrkRatio_sum2);
   fChain->SetBranchAddress("goodTrkRatio_nEntries", &goodTrkRatio_nEntries, &b_goodTrkRatio_nEntries);
   fChain->SetBranchAddress("phiTrkMean_min", &phiTrkMean_min, &b_phiTrkMean_min);
   fChain->SetBranchAddress("phiTrkMean_max", &phiTrkMean_max, &b_phiTrkMean_max);
   fChain->SetBranchAddress("phiTrkMean_sum", &phiTrkMean_sum, &b_phiTrkMean_sum);
   fChain->SetBranchAddress("phiTrkMean_sum2", &phiTrkMean_sum2, &b_phiTrkMean_sum2);
   fChain->SetBranchAddress("phiTrkMean_nEntries", &phiTrkMean_nEntries, &b_phiTrkMean_nEntries);
   fChain->SetBranchAddress("etaTrkMean_min", &etaTrkMean_min, &b_etaTrkMean_min);
   fChain->SetBranchAddress("etaTrkMean_max", &etaTrkMean_max, &b_etaTrkMean_max);
   fChain->SetBranchAddress("etaTrkMean_sum", &etaTrkMean_sum, &b_etaTrkMean_sum);
   fChain->SetBranchAddress("etaTrkMean_sum2", &etaTrkMean_sum2, &b_etaTrkMean_sum2);
   fChain->SetBranchAddress("etaTrkMean_nEntries", &etaTrkMean_nEntries, &b_etaTrkMean_nEntries);
   fChain->SetBranchAddress("phiTrkLead_min", &phiTrkLead_min, &b_phiTrkLead_min);
   fChain->SetBranchAddress("phiTrkLead_max", &phiTrkLead_max, &b_phiTrkLead_max);
   fChain->SetBranchAddress("phiTrkLead_sum", &phiTrkLead_sum, &b_phiTrkLead_sum);
   fChain->SetBranchAddress("phiTrkLead_sum2", &phiTrkLead_sum2, &b_phiTrkLead_sum2);
   fChain->SetBranchAddress("phiTrkLead_nEntries", &phiTrkLead_nEntries, &b_phiTrkLead_nEntries);
   fChain->SetBranchAddress("etaTrkLead_min", &etaTrkLead_min, &b_etaTrkLead_min);
   fChain->SetBranchAddress("etaTrkLead_max", &etaTrkLead_max, &b_etaTrkLead_max);
   fChain->SetBranchAddress("etaTrkLead_sum", &etaTrkLead_sum, &b_etaTrkLead_sum);
   fChain->SetBranchAddress("etaTrkLead_sum2", &etaTrkLead_sum2, &b_etaTrkLead_sum2);
   fChain->SetBranchAddress("etaTrkLead_nEntries", &etaTrkLead_nEntries, &b_etaTrkLead_nEntries);
   fChain->SetBranchAddress("maxpt_min", &maxpt_min, &b_maxpt_min);
   fChain->SetBranchAddress("maxpt_max", &maxpt_max, &b_maxpt_max);
   fChain->SetBranchAddress("maxpt_sum", &maxpt_sum, &b_maxpt_sum);
   fChain->SetBranchAddress("maxpt_sum2", &maxpt_sum2, &b_maxpt_sum2);
   fChain->SetBranchAddress("maxpt_nEntries", &maxpt_nEntries, &b_maxpt_nEntries);
   fChain->SetBranchAddress("sumpt_min", &sumpt_min, &b_sumpt_min);
   fChain->SetBranchAddress("sumpt_max", &sumpt_max, &b_sumpt_max);
   fChain->SetBranchAddress("sumpt_sum", &sumpt_sum, &b_sumpt_sum);
   fChain->SetBranchAddress("sumpt_sum2", &sumpt_sum2, &b_sumpt_sum2);
   fChain->SetBranchAddress("sumpt_nEntries", &sumpt_nEntries, &b_sumpt_nEntries);
   fChain->SetBranchAddress("ntowTriggers_min", &ntowTriggers_min, &b_ntowTriggers_min);
   fChain->SetBranchAddress("ntowTriggers_max", &ntowTriggers_max, &b_ntowTriggers_max);
   fChain->SetBranchAddress("ntowTriggers_sum", &ntowTriggers_sum, &b_ntowTriggers_sum);
   fChain->SetBranchAddress("ntowTriggers_sum2", &ntowTriggers_sum2, &b_ntowTriggers_sum2);
   fChain->SetBranchAddress("ntowTriggers_nEntries", &ntowTriggers_nEntries, &b_ntowTriggers_nEntries);
   fChain->SetBranchAddress("nHT1trigs_min", &nHT1trigs_min, &b_nHT1trigs_min);
   fChain->SetBranchAddress("nHT1trigs_max", &nHT1trigs_max, &b_nHT1trigs_max);
   fChain->SetBranchAddress("nHT1trigs_sum", &nHT1trigs_sum, &b_nHT1trigs_sum);
   fChain->SetBranchAddress("nHT1trigs_sum2", &nHT1trigs_sum2, &b_nHT1trigs_sum2);
   fChain->SetBranchAddress("nHT1trigs_nEntries", &nHT1trigs_nEntries, &b_nHT1trigs_nEntries);
   fChain->SetBranchAddress("nHT2trigs_min", &nHT2trigs_min, &b_nHT2trigs_min);
   fChain->SetBranchAddress("nHT2trigs_max", &nHT2trigs_max, &b_nHT2trigs_max);
   fChain->SetBranchAddress("nHT2trigs_sum", &nHT2trigs_sum, &b_nHT2trigs_sum);
   fChain->SetBranchAddress("nHT2trigs_sum2", &nHT2trigs_sum2, &b_nHT2trigs_sum2);
   fChain->SetBranchAddress("nHT2trigs_nEntries", &nHT2trigs_nEntries, &b_nHT2trigs_nEntries);
   fChain->SetBranchAddress("maxEt_min", &maxEt_min, &b_maxEt_min);
   fChain->SetBranchAddress("maxEt_max", &maxEt_max, &b_maxEt_max);
   fChain->SetBranchAddress("maxEt_sum", &maxEt_sum, &b_maxEt_sum);
   fChain->SetBranchAddress("maxEt_sum2", &maxEt_sum2, &b_maxEt_sum2);
   fChain->SetBranchAddress("maxEt_nEntries", &maxEt_nEntries, &b_maxEt_nEntries);
   fChain->SetBranchAddress("sumEt_min", &sumEt_min, &b_sumEt_min);
   fChain->SetBranchAddress("sumEt_max", &sumEt_max, &b_sumEt_max);
   fChain->SetBranchAddress("sumEt_sum", &sumEt_sum, &b_sumEt_sum);
   fChain->SetBranchAddress("sumEt_sum2", &sumEt_sum2, &b_sumEt_sum2);
   fChain->SetBranchAddress("sumEt_nEntries", &sumEt_nEntries, &b_sumEt_nEntries);
   fChain->SetBranchAddress("maxTowAdc_min", &maxTowAdc_min, &b_maxTowAdc_min);
   fChain->SetBranchAddress("maxTowAdc_max", &maxTowAdc_max, &b_maxTowAdc_max);
   fChain->SetBranchAddress("maxTowAdc_sum", &maxTowAdc_sum, &b_maxTowAdc_sum);
   fChain->SetBranchAddress("maxTowAdc_sum2", &maxTowAdc_sum2, &b_maxTowAdc_sum2);
   fChain->SetBranchAddress("maxTowAdc_nEntries", &maxTowAdc_nEntries, &b_maxTowAdc_nEntries);
   fChain->SetBranchAddress("sumTowAdc_min", &sumTowAdc_min, &b_sumTowAdc_min);
   fChain->SetBranchAddress("sumTowAdc_max", &sumTowAdc_max, &b_sumTowAdc_max);
   fChain->SetBranchAddress("sumTowAdc_sum", &sumTowAdc_sum, &b_sumTowAdc_sum);
   fChain->SetBranchAddress("sumTowAdc_sum2", &sumTowAdc_sum2, &b_sumTowAdc_sum2);
   fChain->SetBranchAddress("sumTowAdc_nEntries", &sumTowAdc_nEntries, &b_sumTowAdc_nEntries);
   fChain->SetBranchAddress("phiEt_min", &phiEt_min, &b_phiEt_min);
   fChain->SetBranchAddress("phiEt_max", &phiEt_max, &b_phiEt_max);
   fChain->SetBranchAddress("phiEt_sum", &phiEt_sum, &b_phiEt_sum);
   fChain->SetBranchAddress("phiEt_sum2", &phiEt_sum2, &b_phiEt_sum2);
   fChain->SetBranchAddress("phiEt_nEntries", &phiEt_nEntries, &b_phiEt_nEntries);
   fChain->SetBranchAddress("etaEt_min", &etaEt_min, &b_etaEt_min);
   fChain->SetBranchAddress("etaEt_max", &etaEt_max, &b_etaEt_max);
   fChain->SetBranchAddress("etaEt_sum", &etaEt_sum, &b_etaEt_sum);
   fChain->SetBranchAddress("etaEt_sum2", &etaEt_sum2, &b_etaEt_sum2);
   fChain->SetBranchAddress("etaEt_nEntries", &etaEt_nEntries, &b_etaEt_nEntries);
   fChain->SetBranchAddress("phiEtMean_min", &phiEtMean_min, &b_phiEtMean_min);
   fChain->SetBranchAddress("phiEtMean_max", &phiEtMean_max, &b_phiEtMean_max);
   fChain->SetBranchAddress("phiEtMean_sum", &phiEtMean_sum, &b_phiEtMean_sum);
   fChain->SetBranchAddress("phiEtMean_sum2", &phiEtMean_sum2, &b_phiEtMean_sum2);
   fChain->SetBranchAddress("phiEtMean_nEntries", &phiEtMean_nEntries, &b_phiEtMean_nEntries);
   fChain->SetBranchAddress("etaEtMean_min", &etaEtMean_min, &b_etaEtMean_min);
   fChain->SetBranchAddress("etaEtMean_max", &etaEtMean_max, &b_etaEtMean_max);
   fChain->SetBranchAddress("etaEtMean_sum", &etaEtMean_sum, &b_etaEtMean_sum);
   fChain->SetBranchAddress("etaEtMean_sum2", &etaEtMean_sum2, &b_etaEtMean_sum2);
   fChain->SetBranchAddress("etaEtMean_nEntries", &etaEtMean_nEntries, &b_etaEtMean_nEntries);
   Notify();
}

Bool_t varclass::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void varclass::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t varclass::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef varclass_cxx
