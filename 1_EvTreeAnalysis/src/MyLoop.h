#ifndef MyLoop__h
#define MyLoop__h
#include "tree.h"
#include "StdInp.h"
class MyTree : public tree { 
    public:
    StdInp& input;
    MyTree (StdInp& inp);
    void MyLoop();
};
#endif
