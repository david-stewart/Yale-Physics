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

    Int_t runId;
    string*   names  = new string[n_entries];
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
        chain->SetBranchAddress(name.c_str(), ptr[i]);
        if ( trigger_names.count(name) ) {
            update[i] = Update::sum;
            type[i]   = Type::Int_t;
        } else if ( name.find("_min") != string::npos ) {
            update[i] = Update::min;
            type[i]   = Type::Double_t;
        } else if ( name.find("_max") != string::npos ) {
            update[i] = Update::max;
            type[i]   = Type::Double_t;
        } else if ( name.find("_sum") != string::npos ) {
            update[i] = Update::sum;
            type[i]   = Type::Double_t;
        } else if ( name.find("_sum2") != string::npos ) {
            update[i] = Update::sum;
            type[i]   = Type::Double_t;
        } else if ( name.find("_nEntries") != string::npos ) {
            update[i] = Update::sum;
            type[i]   = Type::Long64_t;
        } else {
            cout << "We found something that we don't know what to do with!" << endl;
            exit (2);
        }
    }

    map<int, double*> data;
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

        if (data.count(runId)) {
            for (int i{0}; i<n_entries; ++i){
                double val;
                switch (type[i]) {
                    case Type::Int_t :
                        val = *static_cast<Int_t*>(ptr[i]); break;
                    case Type::Double_t :
                        val = *static_cast<Double_t*>(ptr[i]); break;
                    case Type::Long64_t :
                        val = *static_cast<Long64_t*>(ptr[i]); break;
                }
                switch (update[i]) {
                case Update::min :
                    if (val < data[runId][i]) data[runId][i] = val; 
                    break;
                case Update::max :
                    if (val > data[runId][i]) data[runId][i] = val; 
                    break;
                case Update::sum :
                    data[runId][i] += val; 
                    break;
                }
            }
        } else {
            data[runId] = new Double_t[n_entries];
            for (int i{0}; i<n_entries; ++i){
                /* cout << names[i] << endl; */
                double val;
                switch (type[i]) {
                    case Type::Int_t :
                        val = *static_cast<Int_t*>(ptr[i]); break;
                    case Type::Double_t :
                        val = *static_cast<Double_t*>(ptr[i]); break;
                    case Type::Long64_t :
                        val = *static_cast<Long64_t*>(ptr[i]); break;
                }
                data[runId][i] = val;
            }
        }
        /* cout << ++jentry << endl; */
        ++jentry;
    }
    // make the trees:
    // 1. open a named TFile
    string fout_name { log_name };
    fout_name.replace(fout_name.find(".log"), 4, ".root");

    TFile *fout = new TFile (fout_name.c_str(), "RECREATE");
    TTree *otree = new TTree("VarStats","Jet Tree Recoiling from Highest Et Tower");
    int br_runId;
    otree->Branch("runId",&br_runId);

    Double_t* ptr_D = new Double_t [n_entries];
    Int_t*    ptr_I = new Int_t    [n_entries];
    Long64_t* ptr_L = new Long64_t [n_entries];
    /* double* br_vals = new double[n_entries]; */
    for (int i{0}; i<n_entries; ++i){
        switch (type[i]) {
            case Type::Int_t :
                otree->Branch(names[i].c_str(), &ptr_I[i]);
                break;
            case Type::Double_t :
                otree->Branch(names[i].c_str(), &ptr_D[i]);
                break;
            case Type::Long64_t :
                otree->Branch(names[i].c_str(), &ptr_L[i]);
                break;
        }
    }
    
    for (auto x : data) {
        br_runId = x.first;
        for (int i{0}; i<n_entries; ++i){
            if (!strcmp(names[i].c_str(), "BBCMB")) cout << names[i] << endl;
            switch (type[i]) {
                case Type::Int_t :
                    ptr_I[i] = x.second[i];
                    /* if (!strcmp(names[i].c_str(), "BBCMB")) cout << "I: " << x.second[i] << " " << ptr_I[i] << endl; */
                    break;
                case Type::Double_t :
                    ptr_D[i] = x.second[i];
                    /* if (!strcmp(names[i].c_str(), "BBCMB")) cout << "D: " << x.second[i] << " " << ptr_I[i] << endl; */
                    break;
                case Type::Long64_t :
                    ptr_L[i] = x.second[i];
                    /* if (!strcmp(names[i].c_str(), "BBCMB")) cout << "L: " << x.second[i] << " " << ptr_I[i] << endl; */
                    break;
            }
            /* if (!strcmp(names[i].c_str(), "BBCMB")){ */
            /*     cout << names[i] << "   " << x.second[i] */ 
            /*         << " - - - " << *static_cast<Double_t*>(ptr[i]) */ 
            /*         << endl; */
            /*     if (type[i] == Type::Int_t) cout << " is double " << endl; */
            /* } */
        }
        otree->Fill();
    }
    fout->Write();
    fout->Close();
    
    /* cout << names[1] << "hi " << x.second[1] << endl; */

    // now write the output tree
    // output some of the values
    /* for (auto x : data) cout << names[1] << " " << end; */

};
    
    
using namespace std;

int main(int argc, const char** argv) {
    InputCombine input{argc, argv};
    input.Combine();
};

