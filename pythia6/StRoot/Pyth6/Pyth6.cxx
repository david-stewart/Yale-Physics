#include "Pyth6.h"
#include <iostream>
#include <fstream>
#include "TApplication.h"
#include "TPythia6.h"
#include "TFile.h"
#include "TError.h"
#include "TTree.h"
#include "TClonesArray.h"
#include "TH1.h"
#include "TF1.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "Riostream.h"
#include <cstdlib>

// see https://root.cern.ch/root/html/tutorials/pythia/pythiaExample.C.html


ClassImp(PythJets)
PythJets::PythJets() { };
PythJets::~PythJets() { };

/* void PythJets::sayhello() { */ 
/*     std::cout << "hello!" << std::endl; */
/*     std::ofstream of; */
/*     of.open("hello_file"); */
/*     of << "Hello World!" << endl; */
/* }; */

using namespace std;
int PythJets::run(int nEvents, 
        string FILENAME,
        string TREENAME,
        string BRANCHNAME,
        string HISTNAME,
        int    PDGNUMBER
) {
  // Load needed libraries
  /* loadLibraries(); */

  // Create an instance of the Pythia event generator ...
  TPythia6* pythia = new TPythia6;

  // ... and initialise it to run p+p at sqrt(200) GeV in CMS
  pythia->Initialize("cms", "p", "p", 200);

  // Open an output file
  TFile* file = TFile::Open(FILENAME.c_str(), "RECREATE");
  if (!file || !file->IsOpen()) {
    Error("makeEventSample", "Couldn;t open file %s", FILENAME.c_str());
    return 1;
  }

  // Make a tree in that file ...
  TTree* tree = new TTree(TREENAME.c_str(), "Pythia 6 tree");

  // ... and register a the cache of pythia on a branch (It's a
  // TClonesArray of TMCParticle objects. )
  TClonesArray* particles = (TClonesArray*)pythia->GetListOfParticles();
  tree->Branch(BRANCHNAME.c_str(), &particles);

  // Now we make some events
  for (Int_t i = 0; i < nEvents; i++) {
    // Show how far we got every 100'th event.
    if (i % 100 == 0)
      cout << "Event # " << i << endl;

    // Make one event.
    pythia->GenerateEvent();

    // Maybe you want to have another branch with global event
    // information.  In that case, you should process that here.
    // You can also filter out particles here if you want.

    // Now we're ready to fill the tree, and the event is over.
    tree->Fill();
  }

  // Show tree structure
  tree->Print();

  // After the run is over, we may want to do some summary plots:
  TH1D* hist = new TH1D(HISTNAME.c_str(), "p_{#perp}  spectrum for  #pi^{+}",
                        100, 0, 3);
  hist->SetXTitle("p_{#perp}");
  hist->SetYTitle("dN/dp_{#perp}");
  char expression[64];
  sprintf(expression,"sqrt(pow(%s.fPx,2)+pow(%s.fPy,2))>>%s",
          BRANCHNAME.c_str(), BRANCHNAME.c_str(), HISTNAME.c_str());
  char selection[64];
  sprintf(selection,"%s.fKF==%d", BRANCHNAME.c_str(), PDGNUMBER);
  tree->Draw(expression,selection);

  // Normalise to the number of events, and the bin sizes.
  hist->Sumw2();
  hist->Scale(3 / 100. / hist->Integral());
  hist->Fit("expo", "QO+", "", .25, 1.75);
  TF1* func = hist->GetFunction("expo");
  func->SetParNames("A", "- 1 / T");
  // and now we flush and close the file
  file->Write();
  file->Close();

  return 0;
    
};
