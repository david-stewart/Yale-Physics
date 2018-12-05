#include "InputBase.h"
#include "InputCombine.h"
#include "TFile.h"
#include "TH1F.h"
#include "RunStats.h"
#include "iostream"
#include "sstream"

using namespace std;

InputCombine::InputCombine(int argc, const char** argv) :
    InputBase{argc, argv, true}
{
    /* cout << "c0" << endl; */
    /* cout << "n_inputs " << n_inputs << endl; */
    if (give_help_msg) {
        std::cout 
            << " required arguments:"<< endl
            << " 1: output log name" << endl
            << " 2-...: input root files to combine" << endl;
        exit(0);
    }

    chain = new TChain("VarStats"); 
    chain_file_names = new TChain("file_names");

    string add_name;
    while (ss_args >> add_name) {
        if (add_name.find(".root") == string::npos){
            ostringstream msg;
            msg << " # Warning, skipping file " << add_name 
                << " because it's not a \".root\" file." << endl;
            f_log << msg.str();
            cout  << msg.str();
        } else {
            ostringstream msg;
            msg << " # TChain->AddFile("<<add_name<<")"<<endl;
            f_log << msg.str();
            cout << msg.str();
            chain->AddFile(add_name.c_str());
            chain_file_names->AddFile(add_name.c_str());
        }
    }
}

InputCombine::~InputCombine() {
    /* file->Write(); */
    /* file->Close(); */
};
