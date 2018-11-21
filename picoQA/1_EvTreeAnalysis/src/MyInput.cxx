#include "MyInput.h"
#include "TFile.h"
#include "TH1F.h"

ClassImp(MyInput)
MyInput::MyInput(int argc, const char** argv) :
    InputBase{argc, argv, true}
{
    /* cout << "n_inputs " << n_inputs << endl; */
    if (give_help_msg) {
        cout << " This script compiles individual output log scripts."
        cout << " required input : out-file-name.log input1.log input2.log [input3.log ...]." << endl;
        exit (2);
    }

    if (n_inputs < 2) {
        cout << " fatal: ";
        cout << " At least two files are required" << endl << endl;
        cout << " This script compiles individual output log scripts." << endl;
        cout << " required input : out-file-name.log input1.log input2.log [input3.log ...]." << endl;
        exit(2);
    }



    string str;
    ss_args >> str;
    if (str.find(".root") == string::npos) {
        cout << "fatal, root file name must end in \".root\". Name given was\""<<str<<"\""<<endl;
        exit(1);
    }
    file = new TFile(str.c_str(),"RECREATE");

    if (n_inputs>1) ss_args >> nEvents;
    if (n_inputs>2) ss_args >> pthat_min;
    if (n_inputs>3) ss_args >> pthat_max;
    if (n_inputs>4) ss_args >> seed;

    if (seed == -1) {
      time_t a_time;
      time(&a_time);
      seed = (int)a_time;
      f_log << " # setting the seed from -1 to " << seed << " (from the clock)." << endl;
    }
        
    f_log << " # running with inputs: " << endl
          << " #    root file: " << str << endl
          << " #    nEvents:   " << nEvents << endl
          << " #    ptHatMin:  " << pthat_min << endl
          << " #    ptHatMax:  " << pthat_max << endl
          << " #    seed:      " << seed << endl;
}

MyInput::~MyInput() {
    file->Write();
    file->Close();
};

