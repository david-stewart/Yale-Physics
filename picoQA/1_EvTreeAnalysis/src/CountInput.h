#ifndef MyInput__h
#define MyInput__h

#include "InputBase.h"
#include "RunStats.h"
#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "tree.h"


class InputCount : public InputBase, public tree {

    TFile*  file;  // output file
    TTree*  tr_data;   // data for each run
    TTree*  tr_in_files; // strings of the input file(s)

    /* tree myTree; */
    public:
    TChain* chain; // input chain
    ~InputCount();
    InputCount(int argc, const char** argv);

    /* string names[N_NAMES]; */
    /* RunStats fdata; */

    void CountLoop();
    long long int nEvents;
};

#endif
