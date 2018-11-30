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

enum BrType { min, max, sum }; //note: sum2 and nEntries also sum their entries

template <typename T>
struct BranchReader {
    string name;
    T&     br_ref;
    BrType type;
    T      value;
    bool   first_entry;
    BranchReader(string name_, T& br_ref_, BrType type_) :
        name{name_}, br_ref{br_ref_}, type{type_}, 
        value{0}, first_entry{true} {};
    void operator()() {
        switch(type){
            case BrType::min :
                if (first_entry) {
                    first_entry = false;
                    value = br_ref;
                } else if (br_ref < value) {
                    value = br_ref;
                }
                break;
            case BrType::max :
                if (first_entry) {
                    first_entry = false;
                    value = br_ref;
                } else if (br_ref > value) {
                    value = br_ref;
                }
                break;
            case BrType::sum :
                value += br_ref;
                break;
        }
    };
};


void InputCombine::Combine() {
    cout << "starting inputcombine" << endl;
    
    // Get the branches from the TChain and 
    set<string> trigger_names;
    for (auto name : {"BBCMB", "BHT1_VPDMB_30", "BHT1_VPDMB_30_nobsmd",
        "BHT2_BBCMB", "FMS_JP2", "FMS_JP1", "VPDMB_30", "ZEROBIAS"}
    ) trigger_names.insert(name);

    TObjArray* branches = chain->GetListOfBranches();
    for (int i{0}; i<branches->GetEntries();++i){
        TBranch *br =dynamic_cast<TBranch*>(branches->At(i));
        string name{br->GetName()};
        cout << "Found branch: " << br->GetName() << endl;
    }
    
    

};

using namespace std;

int main(int argc, const char** argv) {
    InputCombine input{argc, argv};
    input.Combine();
};

