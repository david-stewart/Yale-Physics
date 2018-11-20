#include "MyInput.h"
#include "TFile.h"
#include "TH1F.h"

MyInput::MyInput(int argc, const char** argv) :
    InputBase{argc, argv, true} 
{
    cout << "n_inputs " << n_inputs << endl;
    if (give_help_msg) {
        cout << "required inputs are: [log_name.log] [string file_name] [string hgram name] [int nEvents]" << endl;
        exit (2);
    }
    if (n_inputs < 3) {
        cout << "required inputs are: [log_name.log] [string file_name] [string hgram name] [int nEvents]" << endl;
        exit(2);
    }

    f_log << "  Hi, this is from the derived input base!" << endl;
    string str;
    ss_args >> str;
    if (str.find(".root") == string::npos) {
        cout << "fatal, root file name must end in \".root\". Name given was\""<<str<<"\""<<endl;
        exit(1);
    }
    file = new TFile(str.c_str(),"RECREATE");

    ss_args >> str;
    hg = new TH1F (str.c_str(), "a;a;a", 10,-0.5, 1.5);
    ss_args >> nEvents;
    f_log << " # running " << nEvents << " events" << endl;
}
MyInput::~MyInput() {
    file->Write();
    file->Close();
};

