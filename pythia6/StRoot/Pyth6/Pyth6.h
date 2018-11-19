#ifndef Pyth6__h
#define Pyth6__h
#include "TClass.h"

#include <iostream>
#include "StMaker.h"
#include "Jet_Tree.h"
#include "JetMaker.h"

void print_hello_world();


class PythJets {
    public:
    JtEvent mEvent;
    TClonesArray  b_jets;
    PythJets();
    virtual ~PythJets();

    int run(int nEvents, 
            double hatMin=5.0,
            double hatMax=7.0,
            string outFile = "pythia6.root",
            int seed = -1,
            string = "tree", 
            string = "particles", 
            string = "ptSpectra", 
            int = 211);
        /* void sayhello(); */
    /* private: */
        /* ClassDef(PythLib, 1) */
    private:
        ClassDef(PythJets, 1);
};


#endif
