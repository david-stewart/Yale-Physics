#define tree_cxx
#include "tree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, const char** argv) {
    // arguments:
    // 1 : which loop to run
    // 2 : how many events to run
    // 3 : output log file name
    // 4 : which input file to use
    // more than 4 : optional inputs

    // [1] 
    int which_loop            { argc > 1 ? atoi(argv[1]) : 1 };
    long long int event_limit { argc > 2 ? atoi(argv[2]) : 10 };
    TString log_name  { argc > 3 ? argv[3] : TString::Format("out_%i", which_loop).Data() };
    TString file_name { argc > 4 ? argv[4] : TString::Format("raw", which_loop).Data() };
    vector<TString> opts;
    for (int i{5}; i < argc; ++i) { opts.push_back(TString{argv[i]}); cout << " added option: " << argv[i] << endl; }
    /* for (auto i : opts) cout << " -a-d-d- " << i << endl; */
    
    // process the file name
    if (!file_name.EndsWith(".root")) file_name.Append(".root");
    cout << "-- Using loop " << which_loop << " with file " << file_name << endl;

    // process log name
    if(!log_name.EndsWith(".log")) log_name.Append(".log");
    cout << " -- Sending output to " << log_name << endl;

    TFile* file = new TFile(file_name.Data(),"read");
    TTree *ttree;
    file->GetObject("tree",ttree);
    tree theTree(opts, ttree, event_limit, log_name);

    switch (which_loop) {
    case 0 :
        theTree.Loop_0();
        break;
    case 1 :
        theTree.Loop_1();
        break;
    case 2 :
        theTree.Loop_2();
        break;
    default :
        cout << "fatal: invalid loop ("<<which_loop<<") chosen" << endl;
        break;
    }
};

void tree::Loop_0()
    // test loop, used to print out a few values and quit
{
   if (fChain == 0) return;
   Long64_t nentries = { event_limit == -1 ? fChain->GetEntriesFast() : event_limit };
   cout << "running Loop 0, a test loop" << endl;
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries; jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);
      cout << "event:  " << jentry << endl;   
      if (jentry > event_limit) break;
   }
}

void tree::Loop_1()
{
    if (fChain == 0) return;
    Long64_t nentries = { event_limit == -1 ? fChain->GetEntriesFast() : event_limit };
    printf(       " * running Loop_1, count #events w/ each trigger in %li events\n", nentries);
    fprintf(flog, " # running Loop_1, count #events w/ each trigger in %li events\n", nentries);
    Long64_t nbytes = 0, nb = 0;

    std::map<int, TriggerCount> emap;
    for (Long64_t jentry=0; jentry<nentries; jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
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
    for (auto i : emap) {
        printf("%5i: %8i %8i %8i %8i %8i %8i %8i %8i %8i %8i %8i %8i %8i\n",
        i.first,
        i.second.n500206, i.second.n470202, i.second.n480202, i.second.n490202,
        i.second.n500202, i.second.n510202, i.second.n470205, i.second.n480205,
        i.second.n490205, i.second.n500215, i.second.n500001, i.second.n500904,
        i.second.n510009
        );
        fprintf(flog, "%5i: %8i %8i %8i %8i %8i %8i %8i %8i %8i %8i %8i %8i %8i\n",
        i.first,
        i.second.n500206, i.second.n470202, i.second.n480202, i.second.n490202,
        i.second.n500202, i.second.n510202, i.second.n470205, i.second.n480205,
        i.second.n490205, i.second.n500215, i.second.n500001, i.second.n500904,
        i.second.n510009
        );
    }
}

void tree::Loop_2()
{
    if (fChain == 0) return;
    Long64_t nentries = { event_limit == -1 ? fChain->GetEntriesFast() : event_limit };
    printf(       " # running Loop_2, make histograms of each runId for %li events\n", nentries);
    fprintf(flog, " # running Loop_2, make histograms of each runId for %li events\n", nentries);

    Long64_t nbytes = 0, nb = 0;
    auto inmap { map_vals_per_line( options[0].Data(), flog ) } ;

    // initialize hgrams and profile for output


    for (Long64_t jentry=0; jentry<nentries; jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);
        /* cout << "event:  " << jentry << endl; */   
        /* if (jentry > event_limit) break; */

        if (jentry % 2000000 == 0) {
             printf(      " # finished event : %i\n", jentry);
            fprintf(flog, " # finished event : %i\n", jentry);
        };
        
        // unique loop work
    }
};
