#include "Pyth6.h"
#include <iostream>
#include <fstream>
#include "TApplication.h"
#include "TPythia6.h"
#include "TFile.h"
#include "TError.h"
#include "TTree.h"
#include "TClonesArray.h"
#include "TMCParticle.h"
#include "TH1.h"
#include "TF1.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "Riostream.h"
#include <cstdlib>
#include <time.h>
#include "TParticlePDG.h"
#include "TDatabasePDG.h"
#include "StThreeVectorF.hh"

#define  NMAX_JETS 50


// see https://root.cern.ch/root/html/tutorials/pythia/pythiaExample.C.html
#include "fastjet/config.h"
#include "fastjet/PseudoJet.hh"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/Selector.hh"
/* #include "fastjet/tools/Subtractor.hh" */
#include "fastjet/tools/JetMedianBackgroundEstimator.hh"
using namespace fastjet;

ClassImp(PythJets)
PythJets::PythJets(string argc_v) : b_jets { "JtJet", NMAX_JETS}, input{argc_v}  {};
PythJets::~PythJets() {};

using namespace std;
using namespace fastjet;
int PythJets::run(int nEvents, 
        double hatMin,
        double hatMax,
        string FILENAME,
        int    seed,
        string TREENAME,
        string BRANCHNAME,
        string HISTNAME,
        int    PDGNUMBER
) {

  // Create an instance of the Pythia event generator ...
  TPythia6* pythia = new TPythia6;
  
  // set the hard scattering
  pythia->SetCKIN(3, hatMin);
  pythia->SetCKIN(4, hatMax);


  if (seed == -1) {
      time_t a_time;
      time(&a_time);
      int i{a_time};
      cout << " using time seed: " << i << endl;
      pythia->SetMRPY(1,i);
  } else {
      pythia->SetMRPY(1,seed);
  }

  // ... and initialise it to run p+p at sqrt(200) GeV in CMS
  pythia->Initialize("cms", "p", "p", 200);

  // Open an output file
  TFile* file = TFile::Open(FILENAME.c_str(), "RECREATE");
  if (!file || !file->IsOpen()) {
    cout << "Couldn't open file " << FILENAME << endl;
    /* Error("makeEventSample", "Couldn't open file %s", FILENAME.c_str()); */
    return 1;
  }

  // Make a tree in that file ...
  TTree* tree = new TTree(TREENAME.c_str(), "Pythia 6 tree");
  /* TH1F* z_vert = new TH1F("z_vert","z_vert", 100, -30, 30); */
  TH1F* h_jets = new TH1F("jets","all detector level jets",45, 0, 45);

  // Make the jet pt histogram

  // ... and register a the cache of pythia on a branch (It's a
  // TClonesArray of TMCParticle objects. )
  TClonesArray* particles = (TClonesArray*)pythia->GetListOfParticles();

  /* tree->Branch(BRANCHNAME.c_str(), &particles); */
  tree->Branch("event", &mEvent);
  tree->Branch("jets",  &b_jets);

  // Now we make some events


  //initialize fastjet
  float ghost_maxrap = 4.0;
  double jet_R_background{0.4};
  JetDefinition jet_def_bkgd(kt_algorithm, jet_R_background); // <--
  AreaDefinition area_def_bkgd(active_area_explicit_ghosts,GhostedAreaSpec (ghost_maxrap,1,0.01));
  Selector selector_rm2 = SelectorAbsEtaMax(1.0) * (!SelectorNHardest(2)); // <--
  JetMedianBackgroundEstimator* bge_rm2 = new JetMedianBackgroundEstimator (selector_rm2, jet_def_bkgd, area_def_bkgd); // <--

  JetDefinition jet_def(antikt_algorithm, 0.4);
  AreaDefinition area_def(active_area_explicit_ghosts,GhostedAreaSpec(4.0,1,0.01));

  cout << "starting pythia loop " << endl;
  for (Int_t iEv = 0; iEv < nEvents; iEv++) {
    /* cout << " |<- E" << endl; */
    // Show how far we got every 100'th event.
    if (iEv % 500 == 0)
    cout << "Event # " << iEv << endl;

    // Make one event.
    pythia->GenerateEvent();
    b_jets.Clear();

    mEvent.n_c = 0;
    mEvent.n_n = 0;

    mEvent.ptsum_c = 0;
    mEvent.ptsum_n = 0;

    mEvent.ptmax_c = 0;
    mEvent.ptmax_n = 0;


    vector<PseudoJet> jet_particles;
    /* TMCParticle* p; */
    /* TIter piter(particles); */
    /* int c {0}; */

    TDatabasePDG pdb;
    for (int i{1}; i < particles->GetEntries()+1; ++i) {
        if (pythia->GetK(i,1) == 0 || pythia->GetK(i,1) > 9) continue;
        StThreeVector<double> tr { pythia->GetP(i,1),
                            pythia->GetP(i,2),
                            pythia->GetP(i,3) };
        double eta { tr.pseudoRapidity() };
        double pt  { tr.perp()};
        if (pt < 0.2 || TMath::Abs(eta) > 1 ) continue;

        double phi { tr.phi() };

        // neutral particles
        if ( (pdb.GetParticle(pythia->GetK(i,2)))->Charge() ) {
                /* pdg->Charge() == 0) { */
            ++mEvent.n_n;
            mEvent.ptsum_n += pt;
            if (pt > mEvent.ptmax_n) {
                mEvent.ptmax_n = pt;
                mEvent.eta_n = eta;
                mEvent.phi_n = phi;
            }
            continue;
        }

        // charged particles
        ++mEvent.n_c;
        mEvent.ptsum_c += pt;
        if (pt > mEvent.ptmax_c) {
            mEvent.ptmax_c = pt;
            mEvent.eta_c = eta;
            mEvent.phi_c = phi;
        }
        jet_particles.push_back(PseudoJet{
                pythia->GetP(i,1), pythia->GetP(i,2),pythia->GetP(i,2),pythia->GetP(i,4)});
                /* p->GetPx(), p->GetPy(), p->GetPz(), p->GetEnergy()} ); */
    }

    ClusterSequenceArea cs{jet_particles, jet_def, area_def};
    vector<PseudoJet> jets = sorted_by_pt ( (!SelectorIsPureGhost())(cs.inclusive_jets()) ) ;
    bge_rm2->set_particles(jet_particles);
    mEvent.rho = bge_rm2->rho();


    /* cout << "           <- jets " << endl; */
    int njets{0};
    Selector pt_min { SelectorPtMin(0.2) };
    for (auto jet : jets) {
        h_jets->Fill(jet.pt());

        JtJet* b_jet = (JtJet*) b_jets.ConstructedAt(njets);
        ++njets;
        b_jet->phi = jet.phi_std();
        b_jet->eta = jet.eta();
        b_jet->pt  = jet.pt();
        b_jet->pt_corr  = (jet - jet.area_4vector()*mEvent.rho).pt();
        b_jet->area = jet.area();
        b_jet->nch  = ( (pt_min)(jet.constituents()) ).size();
    }
    mEvent.njets = njets;
    // Now we're ready to fill the tree, and the event is over.
    /* cout << "                 ----fill----  " << endl; */
    tree->Fill();
  }
  cout << "Finished running pythia" << endl;

  /* cout << "             " << pythia->GetMRPY(1) << " " << setw(30) << setprecision(14) << tree->GetMaximum("particles.fPx") << endl; */


  file->Write();
  file->Close();

  return 0;
    
};
