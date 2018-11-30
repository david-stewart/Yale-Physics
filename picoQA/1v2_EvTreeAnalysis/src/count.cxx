#include "count.h"

/* #include "MyLoop.h" */
/* #include "tree.h" */
#include "CountInput.h"
#include "RunStats.h"
#include <assert.h>

#include <vector>
#include <array>
#include <map>

/* #include <iostream> */
/* #include <iomanip> */
/* #include <unistd.h> */

/* CountLoop::CountLoop(CountInput& inp_) : input(inp_), tree{inp_.chain} {}; */
class Filler{
    public:
    vector<string>& names;
    map<int,vector<OneVarFiller>>& mapV;
    Filler(vector<string>& names_, map<int,vector<OneVarFiller>>& map_) :
        names{names_}, mapV{map_} {};

    void operator()(string name, int& v) {
        names.push_back(name);
        mapV[0].push_back(OneVarFiller{&v});
    }
    void operator()(string name, double& v) {
        names.push_back(name);
        mapV[0].push_back(OneVarFiller{&v});
    }
};

void CountInput::CountLoop() {
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
    /* t_fill( "BHT1_VPDMB-30"       ,  trig_500202 ); */
    /* t_fill( "BHT1_VPDMB_30_nobsmd",  trig_500206 ); */
    /* t_fill( "BHT2_BBCMB",            trig_500215 ); */ 
    /* t_fill( "FMS_JP2",               trig_500808 ); */
    /* t_fill( "FMS_JP1",               trig_500809 ); */
    /* t_fill( "VPDMB_30",              trig_500904 ); */
    t_fill( "ZEROBIAS",              trig_9300   );

    // make maps to keep the data
    vector<string> par_names;
    map<int, vector<OneVarFiller>> mapV;
    mapV[0] = vector<OneVarFiller>{};
    Filler fill{par_names, mapV};


    fill("refmult", refmult);
    /* fill("nGlobalTracks", nGlobalTracks ); */
    /* fill("nTracks", nTracks ); */
    /* fill("nPrimaryTracks", nPrimaryTracks ); */
    /* fill("nGoodPrimaryTracks", nGoodPrimaryTracks ); */
    /* fill("nTofMatch", nTofMatch ); */
    /* fill("nIstHit", nIstHit ); */
    /* fill("nSstHit", nSstHit ); */
    /* fill("nPxl1Hit", nPxl1Hit ); */
    /* fill("nPxl2Hit", nPxl2Hit ); */
    /* fill("nHftHit",  nHftHit ); */
    /* fill("ranking", ranking ); */
    /* fill("xPV", xPV ); */
    /* fill("yPV", yPV ); */
    /* fill("zPV", zPV ); */
    /* fill("zdcX", zdcX ); */
    /* fill("bbcAdcES", bbcAdcES ); */
    /* fill("bbcAdcEL", bbcAdcEL ); */
    /* fill("bbcAdcWS", bbcAdcWS ); */
    /* fill("bbcAdcWL", bbcAdcWL ); */
    /* fill("zdcSumAdcEast", zdcSumAdcEast ); */
    /* fill("zdcSumAdcWest", zdcSumAdcWest ); */
    /* fill("goodTrkRatio", goodTrkRatio ); */
    /* fill("phiTrkMean", phiTrkMean ); */
    /* fill("etaTrkMean", etaTrkMean ); */
    /* fill("phiTrkLead", phiTrkLead ); */
    /* fill("etaTrkLead", etaTrkLead ); */
    /* fill("maxpt", maxpt ); */
    /* fill("sumpt", sumpt ); */
    /* fill("ntowTriggers", ntowTriggers ); */
    /* fill("nHT1trigs", nHT1trigs ); */
    /* fill("nHT2trigs", nHT2trigs ); */
    /* fill("maxEt", maxEt ); */
    /* fill("sumEt", sumEt ); */
    /* fill("maxTowAdc", maxTowAdc ); */
    /* fill("sumTowAdc", sumTowAdc ); */
    /* fill("phiEt", phiEt ); */
    /* fill("etaEt", etaEt ); */
    /* fill("phiEtMean", phiEtMean ); */
    /* fill("etaEtMean", etaEtMean ); */

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
    // write the trees of data
    vector<int>    val_ntrigs(mapT[0].size());
    vector<OneVar> val_onevar(mapV[0].size());
    /* vector<int> br_n_trigs; */ 
    /* array<int, */ 
    /* vector<OneVar>   br_onevar; */
    /* int i{0}; */
    /* int j{100}; */
    /* int newbie; */
    /* file->cd(); */
    /* tr_data->Branch("newbie_copy",&newbie); */
    /* for (int i{0}; i<trig_names.size();++i) br_n_trigs.push_back(0); */
    for (int i{0}; i<val_ntrigs.size();++i)//{
        tr_data->Branch(trig_names[i].c_str(), &val_ntrigs[i]);
        /* for (auto name : trig_names){ */
        /* cout << " trig_names " << trig_names[i] <<  endl; */
        /* br_n_trigs.push_back(0); */
        /* tr_data->Branch(TString::Format("dat_%i",i).Data(), &br_n_trigs[i]); */
        /* tr_data->Branch("MMM",&br_n_trigs[0]); */
    //}
    /* tr_data->Branch("NNN", &br_n_trigs[0]); */
    /* i = 0; */
    /* OneVar test_onevar; */
    for (int i{0}; i<val_onevar.size(); ++i) 
        tr_data->Branch(par_names[i].c_str(), &val_onevar[i]);
        /* auto name : par_names){ */
        /* int test_int; */
        /* br_onevar.push_back(OneVar{}); */
        /* tr_data->Branch(name.c_str(), &br_onevar[i]); */
        /* cout << "Branch " << name << endl; */
        /* ++i; */
    /* }; */
    cout << mapT.size() << "    ----" << endl;
    for (auto& v_ : mapT){
        cout << "Writing for run " << v_.first << endl;

        assert (mapV.count(v_.first) != 0);

        // set number of triggers
        auto& trigs = v_.second;
        for (int i{0}; i < val_ntrigs.size(); ++i) 
            val_ntrigs[i] = trigs[i].n;
        // {
            /* br_n_trigs[i] = trigs[i].n; */
            /* cout << " trigs " << setw(10) << trig_names[i] */ 
            /*      << " " << setw(10) << br_n_trigs[i] << endl; */
        /* } */
        /* newbie = br_n_trigs[0]; */

        // set data points
        int run_id = v_.first;
        auto& vals = mapV[run_id];
        for (int i{0}; i < val_onevar.size(); ++i)
            val_onevar[i] = vals[i].data;
        /* for (int i{0}; i < vals.size(); ++i){ */
            /* cout << " val " << par_names[i] << " sum: " << vals[i].data.sum << endl; */
            /* br_onevar[i] = vals[i].data; */
        /* } */
        tr_data->Fill();
    }

    /* for (auto& p : mapT) { */
    /*     cout << " STARTING RUN " << p.first << endl; */

    /*     for (int i{0}; i<p.second.size(); ++i){ */
    /*         cout << " -> " << trig_names[i] << " " << p.second[i].n << endl; */
    /*     } */
    /* } */
    /* for (const auto& m : mapV[0]) { */
        /* cout << m.first << " "; */
        /* for (const auto v : m.second) */
    /* } */
};

using namespace std;

int main(int argc, const char** argv) {
    CountInput input{argc, argv};
    input.CountLoop();
}

// how to use MyLoop : derive tree to MyTree to use this new class with StdInp
/* MyTree::MyTree( StdInp& inp ) : input(inp), tree{inp.chain} {}; */

/* // main loop definition here */
/* void MyTree::MyLoop(){ */
/*     if (fChain == 0) return; */

/*     long long int nentries = fChain->GetEntriesFast(); */
/*     input.flog  << " # total available events: " << nentries << endl; */
/*     if (input.nEvents != -1) nentries = input.nEvents; */
/*     input.flog << " # starting to read " << input.nEvents << endl; */

/*     Long64_t nbytes = 0, nb = 0; */

/*     AllVarStats vars(runId); */
/*     vars.addVar("refmult", &refmult); */
/*     vars.addVar("nGlobalTracks", &nGlobalTracks ); */
/*     vars.addVar("nTracks", &nTracks ); */
/*     vars.addVar("nPrimaryTracks", &nPrimaryTracks ); */
/*     vars.addVar("nGoodPrimaryTracks", &nGoodPrimaryTracks ); */
/*     vars.addVar("nTofMatch", &nTofMatch ); */
/*     vars.addVar("nIstHit", &nIstHit ); */
/*     vars.addVar("nSstHit", &nSstHit ); */
/*     vars.addVar("nPxl1Hit", &nPxl1Hit ); */
/*     vars.addVar("nPxl2Hit", &nPxl2Hit ); */
/*     vars.addVar("nHftHit",  &nHftHit ); */
/*     vars.addVar("ranking", &ranking ); */
/*     vars.addVar("xPV", &xPV ); */
/*     vars.addVar("yPV", &yPV ); */
/*     vars.addVar("zPV", &zPV ); */
/*     vars.addVar("zdcX", &zdcX ); */
/*     vars.addVar("bbcAdcES", &bbcAdcES ); */
/*     vars.addVar("bbcAdcEL", &bbcAdcEL ); */
/*     vars.addVar("bbcAdcWS", &bbcAdcWS ); */
/*     vars.addVar("bbcAdcWL", &bbcAdcWL ); */
/*     vars.addVar("zdcSumAdcEast", &zdcSumAdcEast ); */
/*     vars.addVar("zdcSumAdcWest", &zdcSumAdcWest ); */
/*     vars.addVar("goodTrkRatio", &goodTrkRatio ); */
/*     vars.addVar("phiTrkMean", &phiTrkMean ); */
/*     vars.addVar("etaTrkMean", &etaTrkMean ); */
/*     vars.addVar("phiTrkLead", &phiTrkLead ); */
/*     vars.addVar("etaTrkLead", &etaTrkLead ); */
/*     vars.addVar("maxpt", &maxpt ); */
/*     vars.addVar("sumpt", &sumpt ); */
/*     vars.addVar("ntowTriggers", &ntowTriggers ); */
/*     vars.addVar("nHT1trigs", &nHT1trigs ); */
/*     vars.addVar("nHT2trigs", &nHT2trigs ); */
/*     vars.addVar("maxEt", &maxEt ); */
/*     vars.addVar("sumEt", &sumEt ); */
/*     vars.addVar("maxTowAdc", &maxTowAdc ); */
/*     vars.addVar("sumTowAdc", &sumTowAdc ); */
/*     vars.addVar("phiEt", &phiEt ); */
/*     vars.addVar("etaEt", &etaEt ); */
/*     vars.addVar("phiEtMean", &phiEtMean ); */
/*     vars.addVar("etaEtMean", &etaEtMean ); */

/*     TrigCount tcount{runId, */ 
/*           { "VPDMB-5-ssd", "VPDMB-5-nossd",  "BBCMB",  "BHT1*VPDMB-30", */  
/*             "BHT1*VPDMB-30_nobsmd",  "BHT2*BBCMB",  "FMS-JP2",  "FMS-JP1",  "VPDMB-30", "ZEROBIAS" */
/*           }, */
/*           { 500001,  500006, 500018, 500202, 500206, 500215, 500808, 500809, 500904, 9300}, */
/*           { */
/*             &trig_500001, &trig_500006, &trig_500018, &trig_500202, &trig_500206, */
/*             &trig_500215, &trig_500808, &trig_500809, &trig_500904, &trig_9300 */
/*           } */
/*     }; */

/*     bool runAll{input.nEvents == -1}; */
/*     Long64_t jentry{0}; */

/*     while (runAll || jentry < input.nEvents){ */
/*         Long64_t ientry = LoadTree(jentry); */
/*         if (jentry % 500000 == 0) { */
/*             input.flog << " # finished " << jentry << " events" << endl; */
/*             input.update_log(); */
/*         } */
/*         if (ientry < 0) break; */

/*         nb = fChain->GetEntry(jentry);   nbytes += nb; */

/*         vars.fill(); */

/*         if (trig_500904){ */
/*             input.h_vz_500904->Fill(zPV); */
/*             input.h_IstHits_500904->Fill(nIstHit); */
/*             input.h_SstHits_500904->Fill(nSstHit); */
/*             input.h_SstIstHits_500904->Fill(nSstHit+nIstHit); */
/*         } */
/*         if (trig_9300){ */
/*             input.h_vz_9300->Fill(zPV); */
/*             input.h_IstHits_9300->Fill(nIstHit); */
/*             input.h_SstHits_9300->Fill(nSstHit); */
/*             input.h_SstIstHits_9300->Fill(nSstHit+nIstHit); */
/*         } */
/*         if (trig_500206){ */
/*             input.h_vz_500206->Fill(zPV); */
/*             input.h_IstHits_500206->Fill(nIstHit); */
/*             input.h_SstHits_500206->Fill(nSstHit); */
/*             input.h_SstIstHits_500206->Fill(nSstHit+nIstHit); */
/*         } */

/*         /1* for (auto& x : vals) x.fill(); *1/ */
/*         tcount.fill(); */
/*         ++jentry; */
/*     } */
/*     cout << tcount << endl; */
/*     cout << vars << endl; */

/*     input.flog << tcount << endl; */
/*     input.flog << vars << endl; */

/*     /1* vals[0].print_header(cout); *1/ */
/*     /1* vals[0].print_header(input.flog); *1/ */
/*     /1* for (auto& x : vals) input.flog << x << endl; *1/ */
/*     /1* for (auto& x : vals) cout       << x << endl; *1/ */
/* }; */

/* /1* int main(int argc, const char** argv) { *1/ */
/* /1*     CountInput input(argc, argv); *1/ */
/*     // get all the the input braches sorted out */
/*     /1* StdInp inp{argc, argv, true, 10, "test.log"}; *1/ */
/*     /1* MyTree mytree{inp}; *1/ */
/*     /1* mytree.MyLoop(); *1/ */
/*     /1* cout << "done" << endl; *1/ */
/* /1* } *1/ */
