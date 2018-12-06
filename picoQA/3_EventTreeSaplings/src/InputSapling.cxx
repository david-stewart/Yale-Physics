#include "InputBase.h"
#include "InputSapling.h"
#include "TFile.h"
#include "TH1F.h"

#include "TProfile.h"
#include "TH1.h"

using namespace std;

//------------------------------------------------------------------
// get basic zdcX and bbc hisgorams
//------------------------------------------------------------------
void InputSapling::LoopZdcBbcHgram() {
    if (chain == 0) return;
    bool runAll{nEvents == -1};
    Long64_t jentry{0};

    if (runAll) {
        f_log << " # starting to read all events" << endl;
    } else {
        f_log << " # starting to read " << nEvents << " all events" << endl;
    }

    TH1D* h_zdcX = new TH1D("zdcX","zdcX in Min Bias events", 500, 0, 25000);
    TH1D* h_bbcES = new TH1D("bbcES","BBC Adc East Small in Min Bias events", 500, 0, 70000);
    TH1D* h_vz    = new TH1D("h_vz", "Primary vertex z position", 62, -31, 31);

    TProfile* p_bbc_zdcX = new TProfile("bbc_zdcX", ";zdcX;BBC Adc East Small", 500, 0, 25000);
    TProfile* p_bbc_vz   = new TProfile("bbc_vz",   ";V_{Z};BBC Adc East Small", 62, -31, 31);
    TProfile* p_zdcX_vz  = new TProfile("zdcX_vz",  ";V_{Z};zdcX[Hz]", 62, -31, 31);

    Long64_t nbytes = 0, nb = 0;
    while (runAll || jentry < nEvents){
        nb = chain->GetEntry(jentry);   nbytes += nb;
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        if (jentry % 500000 == 0) {
            f_log << " # finished " << jentry << " events" << endl;
            update_log();
        }
        if (!trig_500001) continue;
        h_zdcX->Fill(zdcX);
        h_bbcES->Fill(bbcAdcES);
        h_vz->Fill(vz);

        p_bbc_zdcX->Fill(zdcX, bbcAdcES);
        p_bbc_vz->Fill(vz, bbcAdcES);
        p_zdcX_vz->Fill(vz, zdcX);

        ++jentry;
    }
};

//------------------------------------------------------------------
// get basic zdcX and bbc hisgorams
//------------------------------------------------------------------
void InputSapling::LoopPrototype() {
    if (chain == 0) return;
    bool runAll{nEvents == -1};
    Long64_t jentry{0};

    if (runAll) {
        f_log << " # starting to read all events" << endl;
    } else {
        f_log << " # starting to read " << nEvents << " all events" << endl;
    }

    Long64_t nbytes = 0, nb = 0;
    while (runAll || jentry < nEvents){
        nb = chain->GetEntry(jentry);   nbytes += nb;
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        if (jentry % 500000 == 0) {
            f_log << " # finished " << jentry << " events" << endl;
            update_log();
        }
        
        ++jentry;
    }
};

InputSapling::InputSapling(int argc, const char** argv) :
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
    TString name { log_name };

    name.ReplaceAll(".log",".root");
    file = new TFile(name.Data(),"recreate");
    string in_name;

    int which_group{0};
    int n_groups{0};

    string in_file_name;

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

    if (in_file_name.find(".list") != string::npos){
        f_log <<       " # reading list of input files from " << in_file_name << endl;
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
        if (which_group!=0) {
            f_log <<       " # dividing the " << root_files.size() << " input files into " << n_groups << " groups" << endl
                  << " # reading group " << which_group << " for this run." << endl;
            /* fprintf(flog, " # dividing the %i input files into %i groups; reading group %i for this run\n", */
                    /* root_files.size(), n_groups, which_group); */
            int n_files = root_files.size() / n_groups;
            int remainder = root_files.size() % n_groups;
            /* cout << " " << which_group << "  of  " << n_groups << " groups of " << root_files.size() << " files" << endl; */
            for (int i{n_files * (which_group - 1)};
                    i < (which_group == n_groups ? root_files.size() : n_files * which_group); ++i)
            {
                chain->AddFile(root_files[i]);
                f_log << " # chain->Add("<<root_files[i]<<")"<<endl;
                in_name = root_files[i];
                /* fprintf(flog, " # chain->Add(%s)\n", root_files[i].Data()); */
                /* cout << " # chain->Add(" << root_files[i] << ")" << endl; */
            }
        } else {
            for (auto file : root_files) {
                chain->AddFile(file.Data());
                f_log << " # chain->Add("<<file<<")"<<endl;
            };
        };
    } else {
        f_log <<       " # adding file " << in_file_name << endl;
        cout << "chain add " << in_file_name << endl;
        chain->Add(in_file_name.c_str());
    }
    Init(chain);
}

InputSapling::~InputSapling() {
    file->Write();
    file->Close();
};
