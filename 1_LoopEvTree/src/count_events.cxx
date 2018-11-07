#define tree_cxx
// generally required
#include "std_inputs.h"
#include "tree.h"
#include <iostream>

// locally required for tree::Loop()
#include <vector>
#include <map>
#include "TriggerCount.h"
#include "MinMaxMeanVar.h"
#include "MinMax.h"

using namespace std;

int main(int argc, const char** argv) {
    /* MyTree* in_tree; */
    std_inputs input{ 
        argc, 
        argv, 
        true, // default is_test value
        100,  // default number of runs
        "test.log", // default output_log
        "/gpfs/mnt/gpfs01/star/pwg/dstewart/scratch/QA/0_picoToEvTree/root/P16id/good_links/*.root" // default input file
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

    MinMaxMeanVar s_nGlobalTracks{};
    MinMaxMeanVar s_nTracks{};
    MinMaxMeanVar s_nPrimaryTracks{};
    MinMaxMeanVar s_nGoodPrimaryTracks{};
    MinMaxMeanVar s_nTofMatch{};
    MinMaxMeanVar s_ranking{};
    MinMaxMeanVar s_xPV{};
    MinMaxMeanVar s_yPV{};
    MinMaxMeanVar s_zPV{};
    MinMaxMeanVar s_zdcX{};
    MinMaxMeanVar s_bbcAdcES{};
    MinMaxMeanVar s_bbcAdcEL{};
    MinMaxMeanVar s_bbcAdcWS{};
    MinMaxMeanVar s_bbcAdcWL{};
    MinMaxMeanVar s_zdcSumAdcEast{};
    MinMaxMeanVar s_zdcSumAdcWest{};
    MinMaxMeanVar s_goodTrkRatio{};
    MinMaxMeanVar s_phiTrkMean{};
    MinMaxMeanVar s_etaTrkMean{};
    MinMaxMeanVar s_phiTrkLead{};
    MinMaxMeanVar s_etaTrkLead{};
    MinMaxMeanVar s_maxpt{};
    MinMaxMeanVar s_sumpt{};
    MinMaxMeanVar s_trigId{};
    MinMaxMeanVar s_ntowTriggers{};
    MinMaxMeanVar s_nHT1trigs{};
    MinMaxMeanVar s_nHT2trigs{};
    MinMaxMeanVar s_maxEt{};
    MinMaxMeanVar s_sumEt{};
    MinMaxMeanVar s_maxTowAdc{};
    MinMaxMeanVar s_sumTowAdc{};
    MinMaxMeanVar s_phiEt{};
    MinMaxMeanVar s_etaEt{};
    MinMaxMeanVar s_phiEtMean{};
    MinMaxMeanVar s_etaEtMean{};

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

        /* cout << " nGlobalTracks " << nGlobalTracks << */ 
            /* " " << s_nGlobalTracks.min() << "  " << s_nGlobalTracks.max() << endl; */

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

        cout << "ntracks " << nTracks << endl;
        s_nTracks(nTracks);
        s_nPrimaryTracks(nPrimaryTracks);
        s_nGoodPrimaryTracks(nGoodPrimaryTracks);
        s_nTofMatch(nTofMatch);
        s_ranking(ranking);
        s_xPV(xPV);
        s_yPV(yPV);
        s_zPV(zPV);
        s_zdcX(zdcX);
        s_bbcAdcES(bbcAdcES);
        s_bbcAdcEL(bbcAdcEL);
        s_bbcAdcWS(bbcAdcWS);
        s_bbcAdcWL(bbcAdcWL);
        s_zdcSumAdcEast(zdcSumAdcEast);
        s_zdcSumAdcWest(zdcSumAdcWest);
        s_goodTrkRatio(goodTrkRatio);
        s_phiTrkMean(phiTrkMean);
        s_etaTrkMean(etaTrkMean);
        s_phiTrkLead(phiTrkLead);
        s_etaTrkLead(etaTrkLead);
        s_maxpt(maxpt);
        s_sumpt(sumpt);
        s_trigId(trigId);
        s_ntowTriggers(ntowTriggers);
        s_nHT1trigs(nHT1trigs);
        s_nHT2trigs(nHT2trigs);
        s_maxEt(maxEt);
        s_sumEt(sumEt);
        s_maxTowAdc(maxTowAdc);
        s_sumTowAdc(sumTowAdc);
        s_phiEt(phiEt);
        s_etaEt(etaEt);
        s_phiEtMean(phiEtMean);
        s_etaEtMean(etaEtMean);

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

    printf(" Global tracks: n:min:max:mean:std  %i:%f:%f:%f:%f\n",
            s_nGlobalTracks.get_n(),s_nGlobalTracks.min(), s_nGlobalTracks.max(), 
            s_nGlobalTracks.mean(), s_nGlobalTracks.std());

    // print the MinMaxMeanStd
    s_nTracks.print(NULL, "nTracks");
    s_nPrimaryTracks.print(NULL, "nPrimaryTracks");
    s_nGoodPrimaryTracks.print(NULL, "nGoodPrimaryTracks");
    s_nTofMatch.print(NULL, "nTofMatch");
    s_ranking.print(NULL, "ranking");
    s_xPV.print(NULL, "xPV");
    s_yPV.print(NULL, "yPV");
    s_zPV.print(NULL, "zPV");
    s_zdcX.print(NULL, "zdcX");
    s_bbcAdcES.print(NULL, "bbcAdcES");
    s_bbcAdcEL.print(NULL, "bbcAdcEL");
    s_bbcAdcWS.print(NULL, "bbcAdcWS");
    s_bbcAdcWL.print(NULL, "bbcAdcWL");
    s_zdcSumAdcEast.print(NULL, "zdcSumAdcEast");
    s_zdcSumAdcWest.print(NULL, "zdcSumAdcWest");
    s_goodTrkRatio.print(NULL, "goodTrkRatio");
    s_phiTrkMean.print(NULL, "phiTrkMean");
    s_etaTrkMean.print(NULL, "etaTrkMean");
    s_phiTrkLead.print(NULL, "phiTrkLead");
    s_etaTrkLead.print(NULL, "etaTrkLead");
    s_maxpt.print(NULL, "maxpt");
    s_sumpt.print(NULL, "sumpt");
    s_trigId.print(NULL, "trigId");
    s_ntowTriggers.print(NULL, "ntowTriggers");
    s_nHT1trigs.print(NULL, "nHT1trigs");
    s_nHT2trigs.print(NULL, "nHT2trigs");
    s_maxEt.print(NULL, "maxEt");
    s_sumEt.print(NULL, "sumEt");
    s_maxTowAdc.print(NULL, "maxTowAdc");
    s_sumTowAdc.print(NULL, "sumTowAdc");
    s_phiEt.print(NULL, "phiEt");
    s_etaEt.print(NULL, "etaEt");
    s_phiEtMean.print(NULL, "phiEtMean");
    s_etaEtMean.print(NULL, "etaEtMean");

    
};
