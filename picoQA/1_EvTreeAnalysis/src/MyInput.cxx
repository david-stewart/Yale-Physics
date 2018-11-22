#include "MyInput.h"
#include "TFile.h"
#include "TH1F.h"

MyInput::MyInput(int argc, const char** argv) :
    InputBase{argc, argv, true}
{
    /* cout << "n_inputs " << n_inputs << endl; */
    if (give_help_msg) {
        cout << " This script compiles individual output log scripts."
             << " required input : out-file-name.log input1.log input2.log [input3.log ...]." << endl;
        exit (2);
    }

    if (n_inputs < 2) {
        cout << " fatal: ";
        cout << " At least two files are required" << endl << endl;
        cout << " This script compiles individual output log scripts." << endl;
        cout << " required input : out-file-name.log input1.log input2.log [input3.log ...]." << endl;
        exit(2);
    }
}

MyInput::~MyInput() {
};

