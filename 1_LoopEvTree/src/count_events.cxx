#define tree_cxx
// generally required
#include "std_inputs.h"
#include "tree.h"
#include <iostream>

// locally required for tree::Loop()
#include <vector>
#include <map>
#include "TriggerCount.h"

using namespace std;

int main(int argc, const char** argv) {
    std_inputs input{ 
        argc, 
        argv, 
        true, // default is_test value
        100,  // default number of runs
        "test.log", // default output_log
        "/gpfs/mnt/gpfs01/star/pwg/dstewart/scratch/QA/0_picoToEvTree/root/raw/good_links/*.root" // default input file
    };
    input.event_tree->Loop();
};

void tree::Loop()
{
    if (is_test) cout << "Entering tree::Loop() in count! " << endl;
    if (fChain == 0) return;
    Long64_t nentries = { nEvents == -1 ? fChain->GetEntriesFast() : nEvents };
    printf(       " * running Loop_1, count #events w/ each trigger in %li events\n", nentries);
    fprintf(flog, " # running Loop_1, count #events w/ each trigger in %li events\n", nentries);
    Long64_t nbytes = 0, nb = 0;

    std::map<int, TriggerCount> emap;
    for (Long64_t jentry=0; jentry<nentries; jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        ++n_calc_events;
        nb = fChain->GetEntry(jentry);
        /* cout << "event:  " << jentry << endl; */   
        /* if (jentry > event_limit) break; */

        if (jentry % 2000000 == 0) {
             printf(      " # finished event : %i\n", jentry);
            fprintf(flog, " # finished event : %i\n", jentry);
        };

        // unique loop work
        if (!emap.count(runId)) emap[runId] = {};

        if (trig_500001) ++emap[runId].n500001;
        if (trig_500006) ++emap[runId].n500006;
        if (trig_500018) ++emap[runId].n500018;
        if (trig_500202) ++emap[runId].n500202;
        if (trig_500206) ++emap[runId].n500206;
        if (trig_500215) ++emap[runId].n500215;
        if (trig_500808) ++emap[runId].n500808;
        if (trig_500809) ++emap[runId].n500809;
        if (trig_500904) ++emap[runId].n500904;

    }
    // print results
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

    long long int sums[9]{0,0,0,0,0,0,0,0,0};
    for (auto i : emap) {
        printf("%10i  %10i %10i %10i %10i %10i %10i %10i %10i %10i\n",
            i.first,          i.second.n500001, i.second.n500006, i.second.n500018, i.second.n500202,
            i.second.n500206, i.second.n500215, i.second.n500808, i.second.n500809, i.second.n500904
        );
        fprintf(flog, "%10i  %10i %10i %10i %10i %10i %10i %10i %10i %10i\n",
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
    fprintf(flog, "%s", dash);
    fprintf(flog, "%s", name);
    fprintf(flog, "%s", nstr);
    fprintf(flog, "%-10s  %10i %10i %10i %10i %10i %10i %10i %10i %10i\n",
            "#<sum> ", sums[0], 
            sums[1], sums[2], sums[3], sums[4], sums[5], sums[6], sums[7],
            sums[8], sums[9]);
    fprintf(flog, "%s", dash);

    printf( "%s", dash);
    printf( "%s", name);
    printf( "%s", nstr);
    printf( "%-10s  %10i %10i %10i %10i %10i %10i %10i %10i %10i\n",
           "#<sum> ", sums[0], 
            sums[1], sums[2], sums[3], sums[4], sums[5], sums[6], sums[7],
            sums[8], sums[9]);
    printf( "%s", dash);
};
