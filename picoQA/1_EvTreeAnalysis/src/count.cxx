#include "count.h"

/* #include "MyLoop.h" */
/* #include "tree.h" */
#include "InputCount.h"
#include "RunStats.h"
#include <assert.h>

#include <vector>
#include <array>
#include <map>

/* #include <iostream> */
/* #include <iomanip> */
/* #include <unistd.h> */

/* CountLoop::CountLoop(InputCount& inp_) : input(inp_), tree{inp_.chain} {}; */
class Filler{
    public:
    vector<string>* names;
    map<int,vector<OneVarFiller>>* mapV;
    Filler(vector<string>* names_, map<int,vector<OneVarFiller>>* map_) 
    {
        names=names_; 
        mapV = map_;
    };

    void operator()(string name, int& v) {
        names->push_back(name);
        (*mapV)[0].push_back(OneVarFiller{&v});
    };
    void operator()(string name, double& v) {
        names->push_back(name);
        (*mapV)[0].push_back(OneVarFiller{&v});
    };
};

void InputCount::CountLoop() {
    if (fChain == 0) return;
    bool runAll{nEvents == -1};
    Long64_t jentry{0};

    // make map to record number of triggers
    vector<string> trig_names;
    map<int, vector<Ticker>> mapT;
    mapT[0] = vector<Ticker>{};
    auto t_fill = [&trig_names, &mapT](string t_name, bool& b) {
        trig_names.push_back(t_name), mapT[0].push_back({b});
    };
    /* t_fill( "VPDMB_5_ssd",   trig_500001 ); */
    /* t_fill( "VPDMB_5_nossd", trig_500006 ); */
    t_fill( "BBCMB",          trig_500018 );
    t_fill( "BHT1_VPDMB_30"       ,  trig_500202 );
    t_fill( "BHT1_VPDMB_30_nobsmd",  trig_500206 );
    t_fill( "BHT2_BBCMB",            trig_500215 ); 
    t_fill( "FMS_JP2",               trig_500808 );
    t_fill( "FMS_JP1",               trig_500809 );
    t_fill( "VPDMB_30",              trig_500904 );
    t_fill( "ZEROBIAS",              trig_9300   );

    // make maps to keep the data
    vector<string> par_names;
    map<int, vector<OneVarFiller>> mapV;
    mapV[0] = vector<OneVarFiller>{};
    Filler fill(&par_names, &mapV);


    fill("refmult", refmult);
    fill("nGlobalTracks", nGlobalTracks );
    fill("nTracks", nTracks );
    fill("nPrimaryTracks", nPrimaryTracks );
    fill("nGoodPrimaryTracks", nGoodPrimaryTracks );
    fill("nTofMatch", nTofMatch );
    fill("nIstHit", nIstHit );
    fill("nSstHit", nSstHit );
    fill("nPxl1Hit", nPxl1Hit );
    fill("nPxl2Hit", nPxl2Hit );
    fill("nHftHit",  nHftHit );
    fill("ranking", ranking );
    fill("xPV", xPV );
    fill("yPV", yPV );
    fill("zPV", zPV );
    fill("zdcX", zdcX );
    fill("bbcAdcES", bbcAdcES );
    fill("bbcAdcEL", bbcAdcEL );
    fill("bbcAdcWS", bbcAdcWS );
    fill("bbcAdcWL", bbcAdcWL );
    fill("zdcSumAdcEast", zdcSumAdcEast );
    fill("zdcSumAdcWest", zdcSumAdcWest );
    fill("goodTrkRatio", goodTrkRatio );
    fill("phiTrkMean", phiTrkMean );
    fill("etaTrkMean", etaTrkMean );
    fill("phiTrkLead", phiTrkLead );
    fill("etaTrkLead", etaTrkLead );
    fill("maxpt", maxpt );
    fill("sumpt", sumpt );
    fill("ntowTriggers", ntowTriggers );
    fill("nHT1trigs", nHT1trigs );
    fill("nHT2trigs", nHT2trigs );
    fill("maxEt", maxEt );
    fill("sumEt", sumEt );
    fill("maxTowAdc", maxTowAdc );
    fill("sumTowAdc", sumTowAdc );
    fill("phiEt", phiEt );
    fill("etaEt", etaEt );
    fill("phiEtMean", phiEtMean );
    fill("etaEtMean", etaEtMean );

    /* map<int, RunStats> mapR; */
    /* mapV[0].push_back(make_pair("refmult", OneVarFiller<int>{refmult})); */
    /* cout << mapV.size() << endl; */

    /* cout << fChain->GetEntries() << "  |  " << endl; */
    if (nEvents == -1) {
        f_log << " # starting to read all events" << endl;
    } else {
        f_log << " # starting to read " << nEvents << " all events" << endl;
    }

    Long64_t nbytes = 0, nb = 0;
    while (runAll || jentry < nEvents){
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        if (jentry % 500000 == 0) {
            f_log << " # finished " << jentry << " events" << endl;
            update_log();
        }
        if (!mapV.count(runId)) {
            /* for (auto& v : mapV[runId]) v(); */
            /* } else { */
            mapV[runId] = vector<OneVarFiller>{};
            for (const auto& v : mapV[0]) mapV[runId].push_back(OneVarFiller{v});

            mapT[runId] = vector<Ticker>{};
            for (const auto& v : mapT[0]) mapT[runId].push_back(Ticker{v});
        }
        for (auto& v : mapV[0])     v();
        for (auto& v : mapV[runId]) v();
        for (auto& v : mapT[0])     v();
        for (auto& v : mapT[runId]) v();
        ++jentry;
    }

    int br_runId;
    tr_data->Branch("runId", &br_runId);

    vector<int>    val_ntrigs(mapT[0].size());
    vector<OneVar> val_onevar(mapV[0].size());

    for (int i{0}; i<val_ntrigs.size();++i)//{
        tr_data->Branch(trig_names[i].c_str(), &val_ntrigs[i]);

    for (int i{0}; i<val_onevar.size(); ++i){
        string min_name{par_names[i]};
    
        tr_data->Branch(min_name.append("_min").c_str(),&(val_onevar[i].min));

        string max_name{par_names[i]};
        tr_data->Branch(max_name.append("_max").c_str(),&(val_onevar[i].max));

        string sum_name{par_names[i]};
        tr_data->Branch(sum_name.append("_sum").c_str(),&(val_onevar[i].sum));

        string sum2_name{par_names[i]};
        tr_data->Branch(sum2_name.append("_sum2").c_str(),&(val_onevar[i].sum2));

        string nEntries_name{par_names[i]};
        tr_data->Branch(nEntries_name.append("_nEntries").c_str(),&(val_onevar[i].nEntries));
    }


    cout << mapT.size() << "    ----" << endl;
    for (auto& v_ : mapT){
        br_runId = v_.first;
        cout << "Writing for run " << v_.first << endl;

        assert (mapV.count(v_.first) != 0);

        auto& trigs = v_.second;
        for (int i{0}; i < val_ntrigs.size(); ++i) 
            val_ntrigs[i] = trigs[i].n;

        // set data points
        int run_id = v_.first;
        auto& vals = mapV[run_id];
        for (int i{0}; i < val_onevar.size(); ++i)
            val_onevar[i] = vals[i].data;

        tr_data->Fill();
    }
};

using namespace std;

int main(int argc, const char** argv) {
    InputCount input{argc, argv};
    input.CountLoop();
}

