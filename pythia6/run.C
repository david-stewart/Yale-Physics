#include <TSystem>

void run(int nEvents, double minHat, double maxHat, string outfile, int seed=-1) {
    /* gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C"); */
    /* loadSharedLibraries(); */
        
    /* gSystem->Load("StPicoEvent"); */
    /* gSystem->Load("StPicoDstMaker"); */
#ifdef __CINT__
  // Load the Event Generator abstraction library, Pythia 6
  // library, and the Pythia 6 interface library.
  gSystem->Load("libEG");
gSystem -> Load("$FASTJET/lib/libfastjet");
gSystem -> Load("$FASTJET/lib/libfastjettools");
  gSystem->Load("$ROOTSYS/../pythia6/libPythia6"); //change to your setup
  gSystem->Load("libEGPythia6");
#endif

    gSystem->Load("/gpfs/mnt/gpfs01/star/pwg/dstewart/scratch/Yale-Physics/pythia6/.sl73_gcc485/lib/Pyth6");

    PythJets* pythia = new PythJets();
    pythia->run(nEvents, minHat, maxHat, outfile, seed);
};
