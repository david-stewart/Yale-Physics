#ifndef MyInput__h
#define MyInput__h

#include "InputBase.h"
#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "tree.h"


class CountInput : public InputBase, public tree {
    ~CountInput();

    public:
    TChain* chain; // input chain

    TFile*  file;  // output file
    TTree*  tr_data;   // data for each run
    TTree*  tr_in_files; // strings of the input file(s)

    tree myTree;

    /* string names[N_NAMES]; */
    /* RunData fdata; */

    void Loop();

    long long int nEvents;

#endif
