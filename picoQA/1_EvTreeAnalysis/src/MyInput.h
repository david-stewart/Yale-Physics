#ifndef MyInput__h
#define MyInput__h

#include "InputBase.h"
#include "TFile.h"
#include "TH1.h"
#include <vector>
#include <string>


class MyInput : public InputBase {
    public:
    /* MyInput(string argv); */
    MyInput(int argc, const char** argv);
    ~MyInput();
};

#endif
