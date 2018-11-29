#include "InputBase.h"
#include "CountInput.h"
#include "TFile.h"
#include "TH1F.h"
#include "RunStats.h"

using namespace std;

CountInput::CountInput(int argc, const char** argv) :
    InputBase{argc, argv, true},
    nEvents{100}
{
    chain = new TChain("tree");
    /* cout << "c0" << endl; */
    /* cout << "n_inputs " << n_inputs << endl; */
    if (give_help_msg) {
        std::cout 
            << " req. 3 ars:" << endl
            << " 1: output log name" << endl
            << " 2: #events" << endl
            << " 3:  has two options:" << endl
            << "    first:  root file name" << endl
            << "    second: [input.list of root files] [n] [N]"<<endl
            << "            where n, N, are n of N files" <<  endl
            << "           (i.e. 3 7 means get the third group of seven>" << endl;
        exit(0);
    }
    /* cout << "c1" << endl; */
    // open the output file
    TString name { log_name };
    /* cout << "c1.1" << endl; */
    name.ReplaceAll(".log",".root");
    /* cout << "c1.2" << endl; */
    file = new TFile(name.Data(),"recreate");
    tr_data = new TTree("VarStats", "Statistics on observables per run");
    string in_name;
    /* cout << "c1.3" << endl; */
    tr_in_files = new TTree("file_names", "The names of the input files");
    tr_in_files->Branch("file_names",&in_name);
    /* cout << "c1.4" << endl; */

    /* cout << "c2" << endl; */
    int which_group{0};
    int n_groups{0};

    string in_file_name;

    /* cout << "c3" << endl; */
    nEvents = 0;
    if (n_inputs > 0) ss_args >> nEvents;
    if (nEvents == 0) {
        cout << "Warning, 0 events selected. Must select some events." << endl;
        exit(1);
    };
    if (n_inputs > 1){
        ss_args >> in_file_name;
    } else {
        in_file_name = "test.root";
        cout << " Using \"test.root\" for input file" << endl;
    }
    if (n_inputs > 2) ss_args >> which_group;
    if (n_inputs > 3) ss_args >> n_groups;
    /* cout << "c4" << endl; */

    // Get the list of input files and fill the TChain
    // initalize the tchain
    if (in_file_name.find(".list") != string::npos){
        f_log <<       " # reading list of input files from " << in_file_name << endl;
        /* fprintf(flog, " # reading list of input files from %s\n", in_file_name.Data()); */
        vector<TString> root_files;
        TString word;
        ifstream file;
        file.open(in_file_name.c_str());
        while (file >> word){
            /* cout << "word: " << word << endl; */
            if (word.EndsWith(".root")){
                root_files.push_back(word);
            } else {
                f_log <<       " # Notice: skipping file " << word << " is not a \"\\*.root\" file" << endl;
                /* fprintf(flog, " # Notice: skipping file %s is not a \"\\*.root\" file.\n", word.Data()); */
            }
        }
        for (auto i : root_files) {
            /* cout << " root file: " << i << endl; */
            /* in_name = i; */
            /* tr_in_files->Write(); */
        }
        if (which_group!=0) {
            f_log <<       " # dividing the " << root_files.size() << " input files into " << n_groups << " groups" << endl
                  << " # reading group " << which_group << " for this run." << endl;
            /* fprintf(flog, " # dividing the %i input files into %i groups; reading group %i for this run\n", */
                    /* root_files.size(), n_groups, which_group); */
            int n_files = root_files.size() / n_groups;
            int remainder = root_files.size() % n_groups;
            /* cout << " " << which_group << "  of  " << n_groups << " groups of " << root_files.size() << " files" << endl; */
            for (int i{n_files * (which_group - 1)};
                    i < (which_group == n_groups ? root_files.size() : n_files * which_group); ++i){
                chain->AddFile(root_files[i]);
                f_log << " # chain->Add("<<root_files[i]<<")"<<endl;
                in_name = root_files[i];
                tr_in_files->Fill();
                /* fprintf(flog, " # chain->Add(%s)\n", root_files[i].Data()); */
                /* cout << " # chain->Add(" << root_files[i] << ")" << endl; */
            }
        } else {
            for (auto file : root_files) {
                /* cout << " # chain->Add(" << file << ")" << endl; */
                chain->AddFile(file.Data());
                f_log << " # chain->Add("<<file<<")"<<endl;
                /* cout << " Added " << chain->GetEntriesFast() << endl; */
                in_name = file;
                tr_in_files->Fill();
            };
        };
    } else {
        /* cout << "c4.1" << endl; */
        f_log <<       " # adding file " << in_file_name << endl;
        /* cout << "c4.2" << endl; */
        /* fprintf(flog, " # adding file(s) from %s\n", in_file_name.Data()); */
        cout << "chain add " << in_file_name << endl;
        chain->Add(in_file_name.c_str());

        /* cout << "c4.3" << endl; */
        in_name = in_file_name;
        /* cout << "c4.4" << endl; */
        tr_in_files->Fill();
    }
    /* cout << "c6" << endl; */
        
    // write the input names
    Init(chain);
    /* tr_data = new TTree("run_data","data for each run"); */
    /* tr_data->Branch("data",&fdata); */

    /* cout << "before mytree " << *myTree << " |" << endl; */

    /* Init(chain); */
    /* myTree = tree{chain}; */
    /* cout << "after  mytree " << *myTree << " |" << endl; */
    /* int b{0}; */
    /* tr_data->Branch("test_branch",&b); */
    /* tr_data->Fill(); */
    /* b = 4; */
    /* tr_data->Fill(); */
    /* b = 5; */
    /* tr_data->Fill(); */
}

CountInput::~CountInput() {
    file->Write();
    file->Close();
};

