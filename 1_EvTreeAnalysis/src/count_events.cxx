#include "MyLoop.h"
#include "tree.h"
#include "StdInp.h"
#include "OneVarStats.h"

#include <iostream>
#include <iomanip>
#include <TProfile.h>
#include "TrigCount.h"

/* #include <unistd.h> */

using namespace std;

// how to use MyLoop : derive tree to MyTree to use this new class with StdInp
MyTree::MyTree( StdInp& inp ) : input(inp), tree{inp.chain} {};

// main loop definition here
void MyTree::MyLoop(){
    if (fChain == 0) return;

    long long int nentries = fChain->GetEntriesFast();
    input.flog  << " # total available events: " << nentries << endl;
    if (input.nEvents != -1) nentries = input.nEvents;
    input.flog << " # starting to read " << input.nEvents << endl;

    Long64_t nbytes = 0, nb = 0;

    vector<OneVarStats>  vals;
    vals.push_back( OneVarStats {0, "refmult", &refmult} ); 
    vals.push_back( OneVarStats {0, "nGlobalTracks", &nGlobalTracks} );
    vals.push_back( OneVarStats {0, "nTracks", &nTracks} );
    vals.push_back( OneVarStats {0, "nPrimaryTracks", &nPrimaryTracks} );
    vals.push_back( OneVarStats {0, "nGoodPrimaryTracks", &nGoodPrimaryTracks} );
    vals.push_back( OneVarStats {0, "nTofMatch", &nTofMatch} );
    vals.push_back( OneVarStats {0, "ranking", &ranking} );
    vals.push_back( OneVarStats {0, "xPV", &xPV} );
    vals.push_back( OneVarStats {0, "yPV", &yPV} );
    vals.push_back( OneVarStats {0, "zPV", &zPV} );
    vals.push_back( OneVarStats {0, "zdcX", &zdcX} );
    vals.push_back( OneVarStats {0, "bbcAdcES", &bbcAdcES} );
    vals.push_back( OneVarStats {0, "bbcAdcEL", &bbcAdcEL} );
    vals.push_back( OneVarStats {0, "bbcAdcWS", &bbcAdcWS} );
    vals.push_back( OneVarStats {0, "bbcAdcWL", &bbcAdcWL} );
    vals.push_back( OneVarStats {0, "zdcSumAdcEast", &zdcSumAdcEast} );
    vals.push_back( OneVarStats {0, "zdcSumAdcWest", &zdcSumAdcWest} );
    vals.push_back( OneVarStats {0, "goodTrkRatio", &goodTrkRatio} );
    vals.push_back( OneVarStats {0, "phiTrkMean", &phiTrkMean} );
    vals.push_back( OneVarStats {0, "etaTrkMean", &etaTrkMean} );
    vals.push_back( OneVarStats {0, "phiTrkLead", &phiTrkLead} );
    vals.push_back( OneVarStats {0, "etaTrkLead", &etaTrkLead} );
    vals.push_back( OneVarStats {0, "maxpt", &maxpt} );
    vals.push_back( OneVarStats {0, "sumpt", &sumpt} );
    vals.push_back( OneVarStats {0, "ntowTriggers", &ntowTriggers} );
    vals.push_back( OneVarStats {0, "nHT1trigs", &nHT1trigs} );
    vals.push_back( OneVarStats {0, "nHT2trigs", &nHT2trigs} );
    vals.push_back( OneVarStats {0, "maxEt", &maxEt} );
    vals.push_back( OneVarStats {0, "sumEt", &sumEt} );
    vals.push_back( OneVarStats {0, "maxTowAdc", &maxTowAdc} );
    vals.push_back( OneVarStats {0, "sumTowAdc", &sumTowAdc} );
    vals.push_back( OneVarStats {0, "phiEt", &phiEt} );
    vals.push_back( OneVarStats {0, "etaEt", &etaEt} );
    vals.push_back( OneVarStats {0, "phiEtMean", &phiEtMean} );
    vals.push_back( OneVarStats {0, "etaEtMean", &etaEtMean} );

    TrigCount tcount{runId, 
          { "VPDMB-5-ssd", "VPDMB-5-nossd",  "BBCMB",  "BHT1*VPDMB-30",  
            "BHT1*VPDMB-30_nobsmd",  "BHT2*BBCMB",  "FMS-JP2",  "FMS-JP1",  "VPDMB-30"
          },
          { 500001,  500006, 500018, 500202, 500206, 500215, 500808, 500809, 500904},
          {
            &trig_500001, &trig_500006, &trig_500018, &trig_500202, &trig_500206,
            &trig_500215, &trig_500808, &trig_500809, &trig_500904
          }
    };

    bool runAll{input.nEvents == -1};
    Long64_t jentry{0};

    while (runAll || jentry < input.nEvents){
        Long64_t ientry = LoadTree(jentry);
        if (jentry % 500000 == 0) {
            input.flog << " # finished " << jentry << " events" << endl;
            input.update_log();
        }
        if (ientry < 0) break;

        nb = fChain->GetEntry(jentry);   nbytes += nb;

        for (auto& x : vals) x.fill();
        tcount.fill();
        ++jentry;
    }
    cout << tcount << endl;
    input.flog << tcount << endl;

    vals[0].print_header(cout);
    vals[0].print_header(input.flog);
    for (auto& x : vals) input.flog << x << endl;
    for (auto& x : vals) cout       << x << endl;
};

int main(int argc, const char** argv) {
    StdInp inp{argc, argv, true, 10, "test.log"};
    MyTree mytree{inp};
    mytree.MyLoop();
    cout << "done" << endl;
}
