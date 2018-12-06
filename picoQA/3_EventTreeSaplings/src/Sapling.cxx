/* #include "MyLoop.h" */
#include "EventTree.h"
#include "InputSapling.h"
#include <assert.h>

#include <vector>
#include <array>
#include <map>

/* #include <iostream> */
/* #include <iomanip> */
/* #include <unistd.h> */

void InputSapling::SaplingLoop() {
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
        
        // work the code
        cout <<  "rho " << rho << endl;

        ++jentry;
    }
};

using namespace std;

int main(int argc, const char** argv) {
    InputSapling input{argc, argv};
    input.SaplingLoop();
}

