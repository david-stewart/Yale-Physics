#include <TSystem>
#include <TString>

void run(string argv) {
#ifdef __CINT__
  gSystem->Load("libEG");
  gSystem -> Load("$FASTJET/lib/libfastjet");
  gSystem -> Load("$FASTJET/lib/libfastjettools");
  gSystem->Load("libEGPythia6");
#endif
    gSystem->Load("/gpfs/mnt/gpfs01/star/pwg/dstewart/scratch/Yale-Physics/pythia6/.sl73_gcc485/lib/Pyth6");
    cout << " This was input \"" << argv << "\"" << endl;
    Pyth6* py = new Pyth6(argv);
    cout <<  "Ran Pyth6" << endl;
    delete py;
};
