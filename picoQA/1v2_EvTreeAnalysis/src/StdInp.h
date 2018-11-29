#ifndef StdInp__H
#define StdInp__H

#include <iostream>
#include <fstream>
#include <vector>
#include "TString.h"
#include <time.h>
#include "TChain.h"
#include "TH1.h"
/* #include <iostream> */

// Author David Stewart
// Thu Nov  8 09:30:56 EST 2018
// A class that takes the standard input provides:
//    -- an output log
//    -- a chain to the input root file
//    -- number of events to run
using namespace std;

class StdInp {
    public:
    bool is_test;
    long long int nEvents;
    TChain* chain;
    string fname;
    /* const char* fname; */
    ofstream flog;
    /* FILE*   flog; */
    void    update_log();
    TFile*  file;
    std::vector<TString> options; // all options from the command line after 
                                  // [0] is this a test?
                                  // [1] number of events to run; -1 for all.
                                  // [2] name of output log file
                                  // [3] name of input root file
    StdInp (int argc,
            const char** argv,
            bool is_test = false,
            long long int nEvents = 10,  // overriden by options in argc
            TString log_name="test.log",       // "      ditto               "

            TString in_file_name="/gpfs/mnt/gpfs01/star/pwg/dstewart/scratch/QA/0_picoToEvTree/root/P16id/52BEE570E234E6E1DE80C69928D0A187_1593.root"
        );  // "      ditto               "

    time_t start_time;
    const char* time_ellapsed();

    TFile *f_hgrams;

    TH1F* h_vz_9300;
    TH1F* h_IstHits_9300;
    TH1F* h_SstHits_9300;
    TH1F* h_SstIstHits_9300;

    TH1F* h_vz_500206;
    TH1F* h_IstHits_500206;
    TH1F* h_SstHits_500206;
    TH1F* h_SstIstHits_500206;

    TH1F* h_vz_500904;
    TH1F* h_IstHits_500904;
    TH1F* h_SstHits_500904;
    TH1F* h_SstIstHits_500904;

    ~StdInp();
};

#endif
