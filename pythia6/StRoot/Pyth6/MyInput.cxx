#include "MyInput.h"
#include "TFile.h"
#include "TH1F.h"

MyInput::MyInput(int argc, const char** argv) :
    InputBase{argc, argv, true},
    nEvents{100},
    pthat_min{1.},
    pthat_max{2.},
    seed{-1}
{
    /* cout << "n_inputs " << n_inputs << endl; */
    if (give_help_msg) {
        cout << "inputs are: log-f-name root-f-name [nEvents=100] [pthatMin=1.] [pthatMax=2.] [int seed=-1]" << endl;
        cout << "note: if seed == -1, then seed with be randomly set by the system time." << endl;
        exit (2);
    }

    if (n_inputs < 1) {
        cout << "fatal: ";
        cout << "inputs are: log-f-name root-f-name [nEvents=100] [pthatMin=1.] [pthatMax=2.] [int seed=-1]" << endl;
        cout << "note: if seed == -1, then seed with be randomly set by the system time." << endl;
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
      f_log << " # setting the seed from time to " << seed << endl;
      seed = (int)a_time;
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

