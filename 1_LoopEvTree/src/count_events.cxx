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
        "whole.root" // default input file
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

        if (trig_500206) ++emap[runId].n500206;
        if (trig_470202) ++emap[runId].n470202;
        if (trig_480202) ++emap[runId].n480202;
        if (trig_490202) ++emap[runId].n490202;
        if (trig_500202) ++emap[runId].n500202;
        if (trig_510202) ++emap[runId].n510202;
        if (trig_470205) ++emap[runId].n470205;
        if (trig_480205) ++emap[runId].n480205;
        if (trig_490205) ++emap[runId].n490205;
        if (trig_500215) ++emap[runId].n500215;
        if (trig_500001) ++emap[runId].n500001;
        if (trig_500904) ++emap[runId].n500904;
        if (trig_510009) ++emap[runId].n510009;
    }
    // print results
    fprintf(flog, "%8s  %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s\n",
            "# ------", "--------", "--------", "--------", "--------", "--------", "--------",
            "--------", "--------", "--------", "--------", "--------", "--------", "--------");
    fprintf(flog, "%8s: %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s\n",
            "#TrgName", "1vpd30nb", "HT1vpd30", "HT1vpd30", "HT1vpd30", "HT1vpd30", "HT1vpd30",
            "HT2bbc30", "HT2bbc30", "HT2bbc30", "HT2bbc30", 
            "Mvpd5ssd",
            "MBvpd30",
            "MBvpd5"
    );
    fprintf(flog, "%8s: %8i %8i %8i %8i %8i %8i %8i %8i %8i %8i %8i %8i %8i\n",
            "#TrigId ", 500206, 470202, 480202, 490202, 500202, 510202, 470205, 480205,
            490205, 500215, 500001, 500904, 510009
    );
    fprintf(flog, "%8s  %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s\n",
            "# ------", "--------", "--------", "--------", "--------", "--------", "--------",
            "--------", "--------", "--------", "--------", "--------", "--------", "--------");
    long long int sums[13]{0,0,0,0,0,0,0,0,0,0,0,0,0};
    for (auto i : emap) {
        printf("%8i: %8i %8i %8i %8i %8i %8i %8i %8i %8i %8i %8i %8i %8i\n",
        i.first,
        i.second.n500206, i.second.n470202, i.second.n480202, i.second.n490202,
        i.second.n500202, i.second.n510202, i.second.n470205, i.second.n480205,
        i.second.n490205, i.second.n500215, i.second.n500001, i.second.n500904,
        i.second.n510009
        );
        fprintf(flog, "%8i: %8i %8i %8i %8i %8i %8i %8i %8i %8i %8i %8i %8i %8i\n",
        i.first,
        i.second.n500206, i.second.n470202, i.second.n480202, i.second.n490202,
        i.second.n500202, i.second.n510202, i.second.n470205, i.second.n480205,
        i.second.n490205, i.second.n500215, i.second.n500001, i.second.n500904,
        i.second.n510009
        );
        sums[0] += i.second.n500206;
        sums[1] += i.second.n470202;
        sums[2] += i.second.n480202;
        sums[3] += i.second.n490202;

        sums[4] += i.second.n500202;
        sums[5] += i.second.n510202;
        sums[6] += i.second.n470205;
        sums[7] += i.second.n480205;

        sums[8] += i.second.n490205;
        sums[9] += i.second.n500215;;
        sums[10] += i.second.n500001;
        sums[11] += i.second.n500904;

        sums[12] += i.second.n510009;
    }
    fprintf(flog, "%8s  %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s\n",
            "# ------", "--------", "--------", "--------", "--------", "--------", "--------",
            "--------", "--------", "--------", "--------", "--------", "--------", "--------");
    fprintf(flog, "%8s: %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s\n",
            "#TrgName", "1vpd30nb", "HT1vpd30", "HT1vpd30", "HT1vpd30", "HT1vpd30", "HT1vpd30",
            "HT2bbc30", "HT2bbc30", "HT2bbc30", "HT2bbc30", 
            "Mvpd5ssd",
            "MBvpd30",
            "MBvpd5"
    );
    fprintf(flog, "%8s: %8i %8i %8i %8i %8i %8i %8i %8i %8i %8i %8i %8i %8i\n",
            "#TrigId ", 500206, 470202, 480202, 490202, 500202, 510202, 470205, 480205,
            490205, 500215, 500001, 500904, 510009

    );
    fprintf(flog, "%8s  %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s\n",
            "# ------", "--------", "--------", "--------", "--------", "--------", "--------",
            "--------", "--------", "--------", "--------", "--------", "--------", "--------");
    fprintf(flog, "%8s: %8lli %8lli %8lli %8lli %8lli %8lli %8lli %8lli %8lli %8lli %8lli %8lli %8lli\n",
            "#<sum> ", sums[0], 
            sums[1], sums[2], sums[3], sums[4], sums[5], sums[6], sums[7],
            sums[8], sums[9], sums[10], sums[11], sums[12]);
    fprintf(flog, "%8s  %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s\n",
            "# ------", "--------", "--------", "--------", "--------", "--------", "--------",
            "--------", "--------", "--------", "--------", "--------", "--------", "--------");
}

