#include "MyInput.h"
#include "TFile.h"
#include "TH1F.h"
#include "RunStats.h"

MyInput::MyInput(string argv) :
    InputBase{argv, true},
    nEvents{100}
{
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
    // open the output file
    TString name { log_name };
    name.Replace(".log",".root");
    tr_in_files = new TFile(name.Data(),"recreate");
    string in_name;
    tr_in_files->Branch("file_names",&in_name);

    int which_group{0};
    int n_groups{0};

    if (n_inputs > 0) nEvents << ss_args;
    if (n_inputs > 1){
        file_name << ss_args;
    } else {
        in_file_name = "test.root";
        cout << " Using \"test.root\" for input file" << endl;
    }
    if (n_inputs > 2) which_group << ss_args;
    if (n_inputs > 3) n_groups << ss_args;

    // initalize the tchain
    if (in_file_name.find(".list") != string::npos){
        f_log <<       " # reading list of input files from " << in_file_name << endl;
        /* fprintf(flog, " # reading list of input files from %s\n", in_file_name.Data()); */
        vector<TString> root_files;
        TString word;
        ifstream file;
        file.open(in_file_name.Data());
        while (file >> word){
            if (word.EndsWith(".root")){
                root_files.push_back(word);
            } else {
                f_log <<       " # Notice: skipping file " << word << " is not a \"\\*.root\" file" << endl;
                /* fprintf(flog, " # Notice: skipping file %s is not a \"\\*.root\" file.\n", word.Data()); */
            }
        }
        for (auto i : root_files) {
            cout << " root file: " << i << endl;
            /* in_name = i; */
            /* tr_in_files->Write(); */
        }
        if (which_group!=0) {
            f_log <<       " # dividing the " << root_files.size() << " input files into " << n_groups << " groups"
                  << "reading group " << which_group << " for this run." << endl;
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
                cout << " # chain->Add(" << root_files[i] << ")" << endl;
            }
        } else {
            for (auto file : root_files) {
                chain->AddFile(file.Data());
                in_name = file;
                tr_in_files->Fill();
            };
        };
    } else {
        f_log <<       " # adding file " << in_file_name << endl;
        /* fprintf(flog, " # adding file(s) from %s\n", in_file_name.Data()); */
        chain->Add(in_file_name.Data());
        in_name = in_file_name;
        tr_in_files->Fill();
    }
        
    // write the input names
    tr_data = new TTree("run_data","data for each run");
    tr_data->Branch("data",&fdata);

    myTree = tree{chain};
}

MyInput::~MyInput() {
    file->Write();
    file->Close();
};

