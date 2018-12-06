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

    long long int nEvents;
    void LoopPrototype(); // does nothing; just serves as a template for other loops
    void LoopZdcBbcHgram();
    void LoopSapling();
};

#endif
