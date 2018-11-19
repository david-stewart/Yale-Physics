#ifndef StdInp__H
#define StdInp__H

#include <iostream>
#include <fstream>
#include <vector>
#include "TString.h"
#include <time.h>
#include "TChain.h"
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
    string fname;
    string r_fname;
    ofstream flog;
    void    update_log();
    vector<string> argv;
    vector<string> options;
    StdInp ( string inputs,
             int nEvents = 100,
             string fname = "test.log",
             string r_fname = "test.root");
            /* int argc, */
            /* const char** argv, */
            /* bool is_test = false, */
            /* long long int nEvents = 10,  // overriden by options in argc */
            /* TString log_name="test.log",       // "      ditto               " */

            /* TString rt_file_name="/gpfs/mnt/gpfs01/star/pwg/dstewart/scratch/QA/0_picoToEvTree/root/P16id/52BEE570E234E6E1DE80C69928D0A187_1593.root" */
        /* );  // "      ditto               " */

    time_t start_time;
    const char* time_ellapsed();
    ~StdInp();
};

#endif
