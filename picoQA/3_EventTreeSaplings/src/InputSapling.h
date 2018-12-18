#ifndef MyInput__h
#define MyInput__h

#include "InputBase.h"
#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "EventTree.h"


class InputSapling : public InputBase, public EventTree {

    TFile*  file;    // output file

    /* tree myTree; */
    public:
    TChain* chain; // input chain
    ~InputSapling();
    InputSapling(int argc, const char** argv);

    vector<int> good_runs;
    vector<int> bad_runs;

    long long int nEvents;
    void LoopPrototype(); // does nothing; just serves as a template for other loops
    void TriggerCombinations(); // as name indicates
    void ExploratoryLoop();
    void LoopSapling();
};

#endif
