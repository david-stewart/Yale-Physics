#ifndef MyInput__h
#define MyInput__h

#include "InputBase.h"
#include "RunStats.h"
#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"


class InputCombine : public InputBase {
    public:
    TChain* chain; // input chain
    ~InputCombine();
    InputCombine(int argc, const char** argv);
    void Combine();
};

#endif
