#ifndef PythLib__h
#define PythLib__h
#include "TClass.h"

#include <iostream>
#include "StMaker.h"

void print_hello_world();


class PythJets {
    public:
        PythJets();
        virtual ~PythJets();
        int run(int, 
                string = "pythia.root", 
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
