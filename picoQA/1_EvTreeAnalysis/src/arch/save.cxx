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

/* struct Ptr { */
/*     void* ptr; */
/*     BranchType type; */
/*     branch_vals(type_) : type{type_} {}; */
/*     Double_t get_double() { return *static_cast<Double_t*>(ptr); } */
/*     Double_t get_int   () { return *static_cast<Int_t*>   (ptr); } */
/*     Double_t get_long  () { return *static_cast<Long64_t*>(ptr); } */
/* } */

void InputCombine::Combine() {

    // fill a vector of T_ptr to the branch values
    // vector<names> 
    // vector combination scheme
    // Get the branches from the TChain and 
    
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
    Int_t*    i_ptr  = new Int_t [n_entries];
    Double_t* d_ptr  = new Double_t [n_entries];
    Long64_t* l_ptr  = new Long64_t [n_entries];

    TBranch *br =dynamic_cast<TBranch*>(branches->At(0));
    if ( !strcmp(br->GetName(), "runId")) {
        chain->SetBranchAddress("runId", &runId);
    } else {
        cout << "fatal error: first branch not runId" << endl;
        exit(2);
    }

    for (int i{0}; i<n_entries;++i){
        TBranch *br =dynamic_cast<TBranch*>(branches->At(i+1));
        string name{br->GetName()};
        names[i] = name;
        if ( trigger_names.count(name) ) {
            chain->SetBranchAddress(name.c_str(), &i_ptr[i]);
            update[i] = Update::sum;
            type[i]   = Type::Int_t;
        } else if ( name.find("_min") != string::npos ) {
            chain->SetBranchAddress(name.c_str(), &d_ptr[i]);
            update[i] = Update::min;
            type[i]   = Type::Double_t;
        } else if ( name.find("_max") != string::npos ) {
            chain->SetBranchAddress(name.c_str(), &d_ptr[i]);
            update[i] = Update::max;
            type[i]   = Type::Double_t;
        } else if ( name.find("_sum") != string::npos ) {
            chain->SetBranchAddress(name.c_str(), &d_ptr[i]);
            update[i] = Update::sum;
            type[i]   = Type::Double_t;
        } else if ( name.find("_sum2") != string::npos ) {
            chain->SetBranchAddress(name.c_str(), &d_ptr[i]);
            update[i] = Update::sum;
            type[i]   = Type::Double_t;
        } else if ( name.find("_nEntries") != string::npos ) {
            chain->SetBranchAddress(name.c_str(), &l_ptr[i]);
            update[i] = Update::sum;
            type[i]   = Type::Long64_t;
        } else {
            cout << "We found something that we don't know what to do with!" << endl;
            exit (2);
        }
    }
    /* for (int i{0}; i<n_entries; ++i) cout << " -> " << names[i] << endl; */

    // make a new tree with new branches to write out
    /* string file_name {log_name}; */
    /* file_name.replace( file_name.find(".log"), 4, ".root"); */
    /* TFile* file_comb = new TFile(file_name.c_str(), "recreate"); */
    /* file_comb->cd(); */
    /* TTree* tree = new TTree("VarStats","Tree of General Run Characteristics"); */
    /* chain->cd(); */

    /* map <int, vector<BranchReader_Base*>> data; */
    // fill the zero'th data
    cout << "a0" << endl;

    map<int, double*> data;
    cout << "a1" << endl;
    Long64_t jentry{0};
    Long64_t nbytes = 0, nb = 0;
    cout << "a2" << endl;
    /* cout << chain->GetEntry() << endl; */
    while (true){
    cout << "a3" << endl;
        nb = chain->GetEntry(jentry); 
    cout << "a4" << endl;
        Long64_t ientry { chain->LoadTree(jentry) };
        nbytes += nb;
        if (ientry < 0) break;
        if (jentry % 500000 == 0) {
            f_log << " # finished " << jentry << " events" << endl;
            update_log();
        }

        /* if (jentry > 10) break; */
        ++jentry;
        cout << " : " << jentry << endl;
    }

};
    
    
using namespace std;

int main(int argc, const char** argv) {
    InputCombine input{argc, argv};
    input.Combine();
};

