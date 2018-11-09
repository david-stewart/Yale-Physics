#include "MyLoop.h"
#include "tree.h"
#include "StdInp.h"
#include "MinMaxProf.h"

#include <iostream>
#include <TProfile.h>

/* #include <unistd.h> */

using namespace std;

TString makeM(long int i){
    int mval = i/1000000;
    int rval = i%1000000; 
    return TString::Format("%i.%i", mval, rval/1000);
};
void print_header(FILE* flog){
    char dash[200];
    char nstr[200];
    char name[200];

    sprintf(dash, "%-10s  %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n",
            "#---------", "----------","----------","----------","----------",
            "----------","----------","----------","----------","----------");
    sprintf(name, "%-10s  %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n",
            "#TrigName", "vpdMB5-ssd", "vpdMB5nosd",  "BBCMB",  "HT1vpdMB30",  
            "HT1vpd30_n",  "BHT2*BBCMB",  "FMS-JP2",  "FMS-JP1",  "VPDMB-30");
    sprintf(nstr, "%-10s  %10i %10i %10i %10i %10i %10i %10i %10i %10i\n",
            "#TrigNum", 500001,  500006,  500018,  500202,  
            500206,    500215,  500808,  500809,  500904);

     printf("%s",dash);
    fprintf(flog, "%s",dash);
     printf("%s",name);
    fprintf(flog, "%s",name);
     printf("%s",nstr);
    fprintf(flog, "%s",nstr);
     printf("%s",dash);
    fprintf(flog, "%s",dash);
}

// how to use MyLoop : derive tree to MyTree to use this new class with StdInp
MyTree::MyTree( StdInp& inp ) : input(inp), tree{inp.chain} {};

struct TriggerCount {
    long int n500001, n500006, n500018, n500202, n500206, n500215, n500808, n500809, n500904;

    TriggerCount () :
    n500001{0}, n500006{0}, n500018{0}, n500202{0},
    n500206{0}, n500215{0}, n500808{0}, n500809{0},
    n500904{0}
    {};
};

// main loop definition here
void MyTree::MyLoop(){
    if (fChain == 0) return;

    long long int nentries = fChain->GetEntriesFast();
    fprintf(input.flog, "# total available events: %lli\n", nentries);
    if (input.nEvents != -1) nentries = input.nEvents;
    fprintf(input.flog, "# Starting to read %lli events\n", input.nEvents);
    input.update_log();

    Long64_t nbytes = 0, nb = 0;

    map<int, TriggerCount> emap; // i.e. "event map"

    TProfile prof_e("prof_e",";;", 36, 0.5, 36.5, "e");
    TProfile prof_s("prof_s",";;", 36, 0.5, 36.5, "s");
    vector<MinMaxProf_int>    ivals;
    vector<MinMaxProf_double> dvals;
    ivals.push_back( MinMaxProf_int{refmult, prof_e, prof_s, "refmult", 1} );
    ivals.push_back( MinMaxProf_int{nGlobalTracks, prof_e, prof_s, "nGlobalTracks", 2} );
    ivals.push_back( MinMaxProf_int{nTracks, prof_e, prof_s, "nTracks", 3} );
    ivals.push_back( MinMaxProf_int{nPrimaryTracks, prof_e, prof_s, "nPrimaryTracks", 4} );
    ivals.push_back( MinMaxProf_int{nGoodPrimaryTracks, prof_e, prof_s, "nGoodPrimaryTracks", 5} );
    ivals.push_back( MinMaxProf_int{nTofMatch, prof_e, prof_s, "nTofMatch", 6} );
    dvals.push_back( MinMaxProf_double{ranking, prof_e, prof_s, "ranking", 7} );
    dvals.push_back( MinMaxProf_double{xPV, prof_e, prof_s, "xPV", 8} );
    dvals.push_back( MinMaxProf_double{yPV, prof_e, prof_s, "yPV", 9} );
    dvals.push_back( MinMaxProf_double{zPV, prof_e, prof_s, "zPV", 10} );
    dvals.push_back( MinMaxProf_double{zdcX, prof_e, prof_s, "zdcX", 11} );
    dvals.push_back( MinMaxProf_double{bbcAdcES, prof_e, prof_s, "bbcAdcES", 12} );
    dvals.push_back( MinMaxProf_double{bbcAdcEL, prof_e, prof_s, "bbcAdcEL", 13} );
    dvals.push_back( MinMaxProf_double{bbcAdcWS, prof_e, prof_s, "bbcAdcWS", 14} );
    dvals.push_back( MinMaxProf_double{bbcAdcWL, prof_e, prof_s, "bbcAdcWL", 15} );
    dvals.push_back( MinMaxProf_double{zdcSumAdcEast, prof_e, prof_s, "zdcSumAdcEast", 16} );
    dvals.push_back( MinMaxProf_double{zdcSumAdcWest, prof_e, prof_s, "zdcSumAdcWest", 17} );
    dvals.push_back( MinMaxProf_double{goodTrkRatio, prof_e, prof_s, "goodTrkRatio", 18} );
    dvals.push_back( MinMaxProf_double{phiTrkMean, prof_e, prof_s, "phiTrkMean", 19} );
    dvals.push_back( MinMaxProf_double{etaTrkMean, prof_e, prof_s, "etaTrkMean", 20} );
    dvals.push_back( MinMaxProf_double{phiTrkLead, prof_e, prof_s, "phiTrkLead", 21} );
    dvals.push_back( MinMaxProf_double{etaTrkLead, prof_e, prof_s, "etaTrkLead", 22} );
    dvals.push_back( MinMaxProf_double{maxpt, prof_e, prof_s, "maxpt", 23} );
    dvals.push_back( MinMaxProf_double{sumpt, prof_e, prof_s, "sumpt", 24} );
    ivals.push_back( MinMaxProf_int{trigId, prof_e, prof_s, "trigId", 25} );
    ivals.push_back( MinMaxProf_int{ntowTriggers, prof_e, prof_s, "ntowTriggers", 26} );
    ivals.push_back( MinMaxProf_int{nHT1trigs, prof_e, prof_s, "nHT1trigs", 27} );
    ivals.push_back( MinMaxProf_int{nHT2trigs, prof_e, prof_s, "nHT2trigs", 28} );
    dvals.push_back( MinMaxProf_double{maxEt, prof_e, prof_s, "maxEt", 29} );
    dvals.push_back( MinMaxProf_double{sumEt, prof_e, prof_s, "sumEt", 30} );
    dvals.push_back( MinMaxProf_double{maxTowAdc, prof_e, prof_s, "maxTowAdc", 31} );
    dvals.push_back( MinMaxProf_double{sumTowAdc, prof_e, prof_s, "sumTowAdc", 32} );
    dvals.push_back( MinMaxProf_double{phiEt, prof_e, prof_s, "phiEt", 33} );
    dvals.push_back( MinMaxProf_double{etaEt, prof_e, prof_s, "etaEt", 34} );
    dvals.push_back( MinMaxProf_double{phiEtMean, prof_e, prof_s, "phiEtMean", 35} );
    dvals.push_back( MinMaxProf_double{etaEtMean, prof_e, prof_s, "etaEtMean", 36} );

    bool runAll{input.nEvents == -1};
    Long64_t jentry{0};
    while (runAll || jentry < input.nEvents){
    /* for (Long64_t jentry=0; jentry<nentries;jentry++) { */
        Long64_t ientry = LoadTree(jentry);
        if (jentry % 500000 == 0) {
            /* usleep(3000000); */
            fprintf(input.flog, "# ! finished %lli events\n", jentry);
            input.update_log();
        }
        if (ientry < 0) break;

        nb = fChain->GetEntry(jentry);   nbytes += nb;

        for (auto& x : ivals) x.fill();
        for (auto& x : dvals) x.fill();

        if (!emap.count(runId)) emap[runId] = {};

        /* cout << " refmult " << refmult << endl; */

        if (trig_500001) ++emap[runId].n500001;
        if (trig_500006) ++emap[runId].n500006;
        if (trig_500018) ++emap[runId].n500018;
        if (trig_500202) ++emap[runId].n500202;
        if (trig_500206) ++emap[runId].n500206;
        if (trig_500215) ++emap[runId].n500215;
        if (trig_500808) ++emap[runId].n500808;
        if (trig_500809) ++emap[runId].n500809;
        if (trig_500904) ++emap[runId].n500904;
        ++jentry;
    }

    print_header(input.flog);

    long int sums[9]{0,0,0,0,0,0,0,0,0};
    for (auto i : emap) {
        printf("%10li  %10li %10li %10li %10li %10li %10li %10li %10li %10li\n",
            i.first,          i.second.n500001, i.second.n500006, i.second.n500018, i.second.n500202,
            i.second.n500206, i.second.n500215, i.second.n500808, i.second.n500809, i.second.n500904
        );
        fprintf(input.flog,"%10li  %10li %10li %10li %10li %10li %10li %10li %10li %10li\n",
            i.first,          i.second.n500001, i.second.n500006, i.second.n500018, i.second.n500202,
            i.second.n500206, i.second.n500215, i.second.n500808, i.second.n500809, i.second.n500904
        );

        sums[0] += i.second.n500001;
        sums[1] += i.second.n500006;
        sums[2] += i.second.n500018;
        sums[3] += i.second.n500202;
        sums[4] += i.second.n500206;
        sums[5] += i.second.n500215;
        sums[6] += i.second.n500808;
        sums[7] += i.second.n500809;
        sums[8] += i.second.n500904;
    }
    print_header(input.flog);
    fprintf(input.flog, "%-10s  %10li %10li %10li %10li %10li %10li %10li %10li %10li\n",
            "#<sum> ", sums[0], 
            sums[1], sums[2], sums[3], sums[4], sums[5], sums[6], sums[7],
            sums[8], sums[9]);
    fprintf(input.flog,"%-10s  %8s M %8s M %8s M %8s M %8s M %8s M %8s M %8s M %8s M\n",
            "#<sum> ", 
            makeM(sums[0]).Data(), makeM(sums[1]).Data(), makeM(sums[2]).Data(), 
            makeM(sums[3]).Data(), makeM(sums[4]).Data(), makeM(sums[5]).Data(), 
            makeM(sums[6]).Data(), makeM(sums[7]).Data(), makeM(sums[8]).Data(), 
            makeM(sums[9]).Data());
    printf("%-10s  %10li %10li %10li %10li %10li %10li %10li %10li %10li\n",
            "#<sum> ", sums[0], 
            sums[1], sums[2], sums[3], sums[4], sums[5], sums[6], sums[7],
            sums[8], sums[9]);
    printf("%-10s  %8s M %8s M %8s M %8s M %8s M %8s M %8s M %8s M %8s M\n",
            "#<sum> ", 
            makeM(sums[0]).Data(), makeM(sums[1]).Data(), makeM(sums[2]).Data(), 
            makeM(sums[3]).Data(), makeM(sums[4]).Data(), makeM(sums[5]).Data(), 
            makeM(sums[6]).Data(), makeM(sums[7]).Data(), makeM(sums[8]).Data(), 
            makeM(sums[9]).Data());
    fprintf(input.flog, " #      %-19s %s\n", "--------------", ivals[0].stats_dashes().Data());
    fprintf(input.flog, " #      %-19s %s\n", "name", ivals[0].stats_header().Data());
    fprintf(input.flog, " #      %-19s %s\n", "--------------", ivals[0].stats_dashes().Data());
    for (auto& x : ivals) fprintf(input.flog, " #!val: %-19s %s\n", x.name, x.getstats().Data());
    for (auto& x : dvals) fprintf(input.flog, " #!val: %-19s %s\n", x.name, x.getstats().Data());
    // print out the numbers for each runId
};

int main(int argc, const char** argv) {
    StdInp inp{argc, argv, true, 10, "test.log"};
    MyTree mytree{inp};
    /* MyTree mytree{inp.chain}; */
    mytree.MyLoop();
    printf("done\n");
}
