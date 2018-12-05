#include "count.h"

/* #include "MyLoop.h" */
/* #include "tree.h" */
#include "InputCombine.h"
#include "RunStats.h"
#include <assert.h>

#include <vector>
#include <array>
#include <map>
#include <set>
#include <typeinfo>
#include <algorithm>
#include "TTree.h"

enum class Type  { Int_t, Double_t, Long64_t };
enum class Update { min, max, sum };

void InputCombine::Combine() {
    set<string> trigger_names;
    for (auto name : {"BBCMB", "BHT1_VPDMB_30", "BHT1_VPDMB_30_nobsmd",
        "BHT2_BBCMB", "FMS_JP2", "FMS_JP1", "VPDMB_30", "ZEROBIAS"}
    ) trigger_names.insert(name);

    TObjArray* branches = chain->GetListOfBranches();
    int n_entries { branches->GetEntries()-1 };

    union IDL { Int_t I; Double_t D; Long64_t L; };

    Int_t runId;
    string*   names  = new string[n_entries];
    IDL*      in_val = new IDL   [n_entries];
    void**    ptr    = new void* [n_entries];
    Update*   update = new Update[n_entries];
    Type*     type   = new Type  [n_entries]; 

    TBranch *br =dynamic_cast<TBranch*>(branches->At(0));
    if ( !strcmp(br->GetName(), "runId")) {
        chain->SetBranchAddress("runId", &runId);
    } else {
        cout << "fatal error: first branch not runId" << endl;
        exit(2);
    }

    for (int i{0}; i<n_entries;++i){
        ptr[i] = new void*;
        /* ptr[i] = new PtrVals; */
        TBranch *br =dynamic_cast<TBranch*>(branches->At(i+1));
        string name{br->GetName()};
        names[i] = name;
        /* chain->SetBranchAddress(name.c_str(), ptr[i]); */
        if ( trigger_names.count(name) ) {
            update[i] = Update::sum;
            type[i]   = Type::Int_t;
            chain->SetBranchAddress(name.c_str(), &in_val[i].I);
        } else if ( name.find("_min") != string::npos ) {
            update[i] = Update::min;
            type[i]   = Type::Double_t;
            chain->SetBranchAddress(name.c_str(), &in_val[i].D);
        } else if ( name.find("_max") != string::npos ) {
            update[i] = Update::max;
            type[i]   = Type::Double_t;
            chain->SetBranchAddress(name.c_str(), &in_val[i].D);
        } else if ( name.find("_sum") != string::npos ) {
            update[i] = Update::sum;
            type[i]   = Type::Double_t;
            chain->SetBranchAddress(name.c_str(), &in_val[i].D);
        } else if ( name.find("_sum2") != string::npos ) {
            update[i] = Update::sum;
            type[i]   = Type::Double_t;
            chain->SetBranchAddress(name.c_str(), &in_val[i].D);
        } else if ( name.find("_nEntries") != string::npos ) {
            update[i] = Update::sum;
            type[i]   = Type::Long64_t;
            chain->SetBranchAddress(name.c_str(), &in_val[i].L);
        } else {
            cout << "We found something that we don't know what to do with!" << endl;
            exit (2);
        }
    }

    map<int, IDL*> data;
    Long64_t jentry{0};
    Long64_t nbytes = 0, nb = 0;
    /* cout << chain->GetEntry() << endl; */
    while (true){
        nb = chain->GetEntry(jentry); 
        Long64_t ientry { chain->LoadTree(jentry) };
        nbytes += nb;
        if (ientry < 0) break;
        if (jentry % 500000 == 0) {
            f_log << " # finished " << jentry << " events" << endl;
            update_log();
        }

        // get the values
        if (data.count(runId)) {
            for (int i{0}; i<n_entries; ++i){
                /* double val; */
                switch (type[i]) {
                case Type::Int_t :
                    data[runId][i].I += in_val[i].I;
                    break;
                case Type::Long64_t :
                    data[runId][i].L += in_val[i].L;
                    break;
                case Type::Double_t :
                    switch (update[i]) {
                    case Update::min :
                        if (in_val[i].D < data[runId][i].D) data[runId][i].D = in_val[i].D; 
                        break;
                    case Update::max :
                        if (in_val[i].D > data[runId][i].D) data[runId][i].D = in_val[i].D; 
                        break;
                    case Update::sum :
                        data[runId][i].D += in_val[i].D; 
                        break;
                    }
                }
            }
        } else {
            data[runId] = new IDL[n_entries];
            for (int i{0}; i<n_entries; ++i){
                switch (type[i]) {
                case Type::Int_t :
                    data[runId][i].I = in_val[i].I;
                    break;
                case Type::Long64_t :
                    data[runId][i].L   = in_val[i].L;
                    break;
                case Type::Double_t :
                    data[runId][i].D   = in_val[i].D;
                    break;
                }
            }
        }
        // end the loop
        ++jentry;
    }
    
    // 1. open a named TFile
    string fout_name { log_name };
    fout_name.replace(fout_name.find(".log"), 4, ".root");

    TFile *fout = new TFile (fout_name.c_str(), "RECREATE");
    TTree *otree = new TTree("VarStats","Jet Tree Recoiling from Highest Et Tower");
    int br_runId;
    otree->Branch("runId",&br_runId);

    // make the branches
    IDL*  out_val = new IDL[n_entries];
    for (int i{0}; i<n_entries; ++i){
        switch (type[i]) {
        case Type::Int_t :
            otree->Branch(names[i].c_str(), &out_val[i].I);
            break;
        case Type::Double_t :
            otree->Branch(names[i].c_str(), &out_val[i].D);
            break;
        case Type::Long64_t :
            otree->Branch(names[i].c_str(), &out_val[i].L);
            break;
        }
    }
    
    for (auto x : data) {
        br_runId = x.first;
        for (int i{0}; i<n_entries; ++i){
            switch (type[i]) {
                case Type::Int_t :
                    out_val[i].I = x.second[i].I;
                    break;
                case Type::Double_t :
                    out_val[i].D = x.second[i].D;
                    break;
                case Type::Long64_t :
                    out_val[i].L = x.second[i].L;
                    break;
            }
        }
        otree->Fill();
    }
    
    // copy and sort the file names
    f_log << " # Reading in list of file names into tree \"file_names\"" << endl;
    update_log();
    string* file_names = nullptr;
    chain_file_names->SetBranchAddress("file_names", &file_names);
    jentry = 0;
    nbytes = 0;
    nb = 0;
    vector<string> v_names;
    while (true){
        nb = chain_file_names->GetEntry(jentry); 
        Long64_t ientry { chain_file_names->LoadTree(jentry) };
        nbytes += nb;
        if (ientry < 0) break;
        if (jentry % 500000 == 0) {
            f_log << " # finished " << jentry << " events" << endl;
            update_log();
        }
        v_names.push_back(*file_names);
        ++jentry;
    }
    sort(v_names.begin(), v_names.end());
    vector<string>::iterator new_end = unique(v_names.begin(), v_names.end());

    f_log << " # Finishes reading in file names. Now writting out file names." << endl;
    TTree* tree_names = new TTree("file_names","names of input files for which events are taken");
    tree_names->Branch("file_names",&file_names);

    for (vector<string>::iterator it = v_names.begin(); it != new_end; ++it) {
        *file_names = *it;
        /* cout << " this name " << *file_names << endl; */
        tree_names->Fill();
    }

    // copy over the file_names tree
    fout->Write();
    fout->Close();
    
    
};
    
using namespace std;

int main(int argc, const char** argv) {
    InputCombine input{argc, argv};
    input.Combine();
};

