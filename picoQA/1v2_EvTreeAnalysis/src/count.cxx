#include "count.h"

/* #include "MyLoop.h" */
/* #include "tree.h" */
#include "CountInput.h"
#include "RunStats.h"

/* #include <iostream> */
/* #include <iomanip> */
/* #include <unistd.h> */

using namespace std;

void CountInput::Loop() {
};

int main(int argc, const char** argv) {
    CountInput input{argc, argv};
    input.Loop();
    //make a map of the inputs, as well as a tree of the desired histograms (it any)
    map<int, vector<pair<string, OneVarFiller_Base>> > events;
    map<int, RunStats> run_stats;
    events[0] = vector<EventsTatsFiller_Base>{};
    events[0].push_back( {"refmult", {refmult}} );

    // Fill the stats with the branches
    
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
