#ifndef Pyth6__h
#define Pyth6__h
#include "TClass.h"

#include <iostream>
#include "StMaker.h"
#include "Jet_Tree.h"
#include "MyInput.h"

class Pyth6 {
    public:
    Pyth6(string args);
    MyInput inp;
    JtEvent mEvent;
    TClonesArray  b_jets;
    virtual ~Pyth6();

    private:
        ClassDef(Pyth6, 1);
};
#endif
