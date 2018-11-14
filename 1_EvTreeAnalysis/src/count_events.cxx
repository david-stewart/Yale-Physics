#include "MyLoop.h"
#include "tree.h"
#include "StdInp.h"
#include "OneVarStats.h"

#include <iostream>
#include <iomanip>
#include <TProfile.h>

/* #include <unistd.h> */

using namespace std;

void print_header(ostream& flog){
    char dash[200];
    char nstr[200];
    char name[200];

    // print the dashes
    flog << setw(10) << setfill('-') << left << " #";
    flog << right;
    for (int i{0}; i<9; ++i) flog << " " << setw(10) << "-";
    flog << endl;
    flog << setfill(' ');

    // print  the names:
    for (auto name : 
          { " #TrigName", "vpdMB5-ssd", "vpdMB5nosd",  "BBCMB",  "HT1vpdMB30",  
            "HT1vpd30_n",  "BHT2*BBCMB",  "FMS-JP2",  "FMS-JP1",  "VPDMB-30"} ) 
    flog << left << setw(10) << name << " ";
    flog << endl;

    flog << left;
    for (auto name :
         { " #TrigNum", "500001",  "500006",  "500018",  "500202",  
           "500206",    "500215",  "500808",  "500809",  "500904"} )
    flog << setw(10) << name << " "; 
    flog << endl;

    /* for (auto name : */ 
    /*       { " #TrigName", "vpdMB5-ssd", "vpdMB5nosd",  "BBCMB",  "HT1vpdMB30", */  
    /*         "HT1vpd30_n",  "BHT2*BBCMB",  "FMS-JP2",  "FMS-JP1",  "VPDMB-30"} ) */ 
    /* flog << setw(10) << name << " "; */
    /* flog << endl; */

    flog << setw(10) << setfill('-') << left << " #";
    flog << right;
    for (int i{0}; i<9; ++i) flog << " " << setw(10) << "-";
    flog << endl;
    flog << setfill(' ');

        /* cout << setw(10) << setfill('-') */ 

    /* sprintf(dash, "%-10s  %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", */
            /* "#---------", "----------","----------","----------","----------", */
            /* "----------","----------","----------","----------","----------"); */
    /* sprintf(name, "%-10s  %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", */
            /* "#TrigName", "vpdMB5-ssd", "vpdMB5nosd",  "BBCMB",  "HT1vpdMB30", */  
            /* "HT1vpd30_n",  "BHT2*BBCMB",  "FMS-JP2",  "FMS-JP1",  "VPDMB-30"); */
    /* sprintf(nstr, "%-10s  %10i %10i %10i %10i %10i %10i %10i %10i %10i\n", */
            /* "#TrigNum", "500001",  "500006",  "500018",  "500202", */  
            /* "500206",    "500215",  "500808",  "500809",  "500904"; */

     /* printf("%s",dash); */
    /* fprintf(flog, "%s",dash); */
     /* printf("%s",name); */
    /* fprintf(flog, "%s",name); */
     /* printf("%s",nstr); */
    /* fprintf(flog, "%s",nstr); */
     /* printf("%s",dash); */
    /* fprintf(flog, "%s",dash); */
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
    input.flog  << " # total available events: " << nentries << endl;
    /* fprintf(input.flog, "# total available events: %lli\n", nentries); */
    if (input.nEvents != -1) nentries = input.nEvents;
    input.flog << " # starting to read " << input.nEvents << endl;
    /* fprintf(input.flog, "# Starting to read %lli events\n", input.nEvents); */
    /* input.update_log(); */
    /* fprintf(input.flog,"TESTING!\n"); */

    Long64_t nbytes = 0, nb = 0;

    map<int, TriggerCount> emap; // i.e. "event map"

    TProfile prof_e("prof_e",";;", 36, 0.5, 36.5, "e");
    TProfile prof_s("prof_s",";;", 36, 0.5, 36.5, "s");
    vector<OneVarStats>  vals;
    /* vector<MinMaxProf_double> vals; */
    vals.push_back( OneVarStats {"refmult", &refmult} ); 
    vals.push_back( OneVarStats {"nGlobalTracks", &nGlobalTracks} );
    vals.push_back( OneVarStats {"nTracks", &nTracks} );
    vals.push_back( OneVarStats {"nPrimaryTracks", &nPrimaryTracks} );
    vals.push_back( OneVarStats {"nGoodPrimaryTracks", &nGoodPrimaryTracks} );
    vals.push_back( OneVarStats {"nTofMatch", &nTofMatch} );
    vals.push_back( OneVarStats {"ranking", &ranking} );
    vals.push_back( OneVarStats {"xPV", &xPV} );
    vals.push_back( OneVarStats {"yPV", &yPV} );
    vals.push_back( OneVarStats {"zPV", &zPV} );
    vals.push_back( OneVarStats {"zdcX", &zdcX} );
    vals.push_back( OneVarStats {"bbcAdcES", &bbcAdcES} );
    vals.push_back( OneVarStats {"bbcAdcEL", &bbcAdcEL} );
    vals.push_back( OneVarStats {"bbcAdcWS", &bbcAdcWS} );
    vals.push_back( OneVarStats {"bbcAdcWL", &bbcAdcWL} );
    vals.push_back( OneVarStats {"zdcSumAdcEast", &zdcSumAdcEast} );
    vals.push_back( OneVarStats {"zdcSumAdcWest", &zdcSumAdcWest} );
    vals.push_back( OneVarStats {"goodTrkRatio", &goodTrkRatio} );
    vals.push_back( OneVarStats {"phiTrkMean", &phiTrkMean} );
    vals.push_back( OneVarStats {"etaTrkMean", &etaTrkMean} );
    vals.push_back( OneVarStats {"phiTrkLead", &phiTrkLead} );
    vals.push_back( OneVarStats {"etaTrkLead", &etaTrkLead} );
    vals.push_back( OneVarStats {"maxpt", &maxpt} );
    vals.push_back( OneVarStats {"sumpt", &sumpt} );
    /* vals.push_back( MinMaxProf_int{trigId, prof_e, prof_s, "trigId", 25} &); */
    vals.push_back( OneVarStats {"ntowTriggers", &ntowTriggers} );
    vals.push_back( OneVarStats {"nHT1trigs", &nHT1trigs} );
    vals.push_back( OneVarStats {"nHT2trigs", &nHT2trigs} );
    vals.push_back( OneVarStats {"maxEt", &maxEt} );
    vals.push_back( OneVarStats {"sumEt", &sumEt} );
    vals.push_back( OneVarStats {"maxTowAdc", &maxTowAdc} );
    vals.push_back( OneVarStats {"sumTowAdc", &sumTowAdc} );
    vals.push_back( OneVarStats {"phiEt", &phiEt} );
    vals.push_back( OneVarStats {"etaEt", &etaEt} );
    vals.push_back( OneVarStats {"phiEtMean", &phiEtMean} );
    vals.push_back( OneVarStats {"etaEtMean", &etaEtMean} );

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
    print_header(cout);

    long int sums[9]{0,0,0,0,0,0,0,0,0};
    for (auto i : emap) {
        cout << right;
        cout << setw(10) << i.first << " ";
        for (auto v : {  i.second.n500001, i.second.n500006, i.second.n500018, i.second.n500202,     
                         i.second.n500206, i.second.n500215, i.second.n500808, i.second.n500809, i.second.n500904 })
            cout << setw(10) << v << " "; 
        cout << endl;
        /* printf("%10li  %10li %10li %10li %10li %10li %10li %10li %10li %10li\n", */
            /* i.first,          i.second.n500001, i.second.n500006, i.second.n500018, i.second.n500202, */
            /* i.second.n500206, i.second.n500215, i.second.n500808, i.second.n500809, i.second.n500904 */
        /* ); */

        input.flog << right;
        input.flog << setw(10) << i.first << " ";
        for (auto v : {  i.second.n500001, i.second.n500006, i.second.n500018, i.second.n500202,     
                         i.second.n500206, i.second.n500215, i.second.n500808, i.second.n500809, i.second.n500904 })
            input.flog << setw(10) << v << " "; 
        input.flog << endl;
        /* fprintf(input.flog,"%10li  %10li %10li %10li %10li %10li %10li %10li %10li %10li\n", */
        /*     i.first,          i.second.n500001, i.second.n500006, i.second.n500018, i.second.n500202, */
        /*     i.second.n500206, i.second.n500215, i.second.n500808, i.second.n500809, i.second.n500904 */
        /* ); */

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
    print_header(cout);

    /* input.flog << "a1" << endl; */
    input.flog << setw(10) << left << " #!sum:" << " " << right;
    for (auto v : sums) input.flog << setw(10) << v << " ";
    input.flog << endl;

    /* input.flog << "a2" << endl; */
    input.flog << setw(10) << left << " #!sum:" << " " << right;
    for (auto v : sums) input.flog << fixed << setw(8) << setprecision(3) << v/1.0E6 << " M ";
    input.flog << endl;
    /* input.flog << "a3" << endl; */


    /* fprintf(input.flog, "%-10s  %10li %10li %10li %10li %10li %10li %10li %10li %10li\n", */
    /*         "#<sum> ", sums[0], */ 
    /*         sums[1], sums[2], sums[3], sums[4], sums[5], sums[6], sums[7], */
    /*         sums[8], sums[9]); */
    /* fprintf(input.flog,"%-10s  %8s M %8s M %8s M %8s M %8s M %8s M %8s M %8s M %8s M\n", */
    /*         "#<sum> ", */ 
    /*         makeM(sums[0]).Data(), makeM(sums[1]).Data(), makeM(sums[2]).Data(), */ 
    /*         makeM(sums[3]).Data(), makeM(sums[4]).Data(), makeM(sums[5]).Data(), */ 
    /*         makeM(sums[6]).Data(), makeM(sums[7]).Data(), makeM(sums[8]).Data(), */ 
    /*         makeM(sums[9]).Data()); */
    /* printf("%-10s  %10li %10li %10li %10li %10li %10li %10li %10li %10li\n", */
    /*         "#<sum> ", sums[0], */ 
    /*         sums[1], sums[2], sums[3], sums[4], sums[5], sums[6], sums[7], */
    /*         sums[8], sums[9]); */
    /* printf("%-10s  %8s M %8s M %8s M %8s M %8s M %8s M %8s M %8s M %8s M\n", */
    /*         "#<sum> ", */ 
    /*         makeM(sums[0]).Data(), makeM(sums[1]).Data(), makeM(sums[2]).Data(), */ 
    /*         makeM(sums[3]).Data(), makeM(sums[4]).Data(), makeM(sums[5]).Data(), */ 
    /*         makeM(sums[6]).Data(), makeM(sums[7]).Data(), makeM(sums[8]).Data(), */ 
    /*         makeM(sums[9]).Data()); */

    /* input.flog <<       " #      " << setw(20) << setfill('-') << "-" << vals[0].stats_dashes() << setfill(' ') << endl; */
    /* fprintf(input.flog, " #      %-19s %s\n", "--------------", vals[0].stats_dashes().Data()); */
    /* input.flog <<       " #      " << left << setw(20) << "name " << vals[0].stats_header() << endl; */
    /* fprintf(input.flog, " #      %-19s %s\n", "name", vals[0].stats_header().Data()); */
    /* input.flog <<       " #      " << setw(20) << setfill('-') << "-" << vals[0].stats_dashes() << setfill(' ') << endl; */
    /* fprintf(input.flog, " #      %-19s %s\n", "--------------", vals[0].stats_dashes().Data()); */
    vals[0].print_header(input.flog);
    for (auto& x : vals) input.flog << x << endl;
};

int main(int argc, const char** argv) {
    StdInp inp{argc, argv, true, 10, "test.log"};
    MyTree mytree{inp};
    /* MyTree mytree{inp.chain}; */
    mytree.MyLoop();
    printf("done\n");
}
