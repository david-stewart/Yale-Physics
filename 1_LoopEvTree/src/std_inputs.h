#ifndef STD_INPUTS__H
#define STD_INPUTS__H
#include <vector>
#include <TString.h>
#include "tree.h"
#include <iostream>
// --------------------------------------------------
// A structure that accepts standard input arguments: argc and argv
// Required inputs (in argv):
//  1. number of events : nEvents
//  2. output log name  : log_name
//  3. input file name  : in_file_name
// This std_inp struct can accept default values (which 
// will be overridden by argv)
// It also accepts a varaible "is_test"
// --------------------------------------------------
struct std_inputs{
    int argc;
    std::vector<TString> argv;

    bool          is_test;
    long long int nEvents;  // how many events to loop over
    TString       log_name;
    TString       in_file_name;

    std::vector<TString> options; // same as argv starting at fourth entry

    // derived values:
    TFile* tfile;
    TTree* ttree;
    FILE*  flog; //output log file

    tree*   event_tree;

    std_inputs(int argc_, 
            const char** argv_, 
            bool is_test_         = false,
            int nEvents_          = 10,
            TString log_name_     = "out.log",
            TString in_file_name_ = "short.root") :
        argc     { argc_ },
        is_test  { is_test_ },
        nEvents  { nEvents_ },
        log_name { log_name_ },
        in_file_name { in_file_name_ }
    {
        for (int i{0}; i<argc; ++i) { argv.push_back(argv_[i]); }
        if (argc > 1 && (argv[1] == "--help" || argv[1] == "-h")) {
            std::cout 
                << " Enter three arguments: [1] # events [2] output log name [3] "
                << "input root file name" << std::endl;
            exit(0);
        }
        if (argc > 1) nEvents = argv[1].Atoi();
        if (argc > 2) log_name = argv[2];
        if (argc > 3) in_file_name = argv[3];
        if (argc > 4) for (int i{4}; i < argc; ++i) 
        { 
            options.push_back(argv_[i]);
            if (is_test) std::cout << "  adding option: " << argv_[i] << std::endl;
        }

        // set up the log file
        if(!log_name.EndsWith(".log")) log_name.Append(".log");
        flog = fopen(log_name.Data(), "w");
        if (is_test) std::cout << " -- Sending output to " << log_name << std::endl;

        // set up tfile and ttree
        if (!in_file_name.EndsWith(".root")) in_file_name.Append(".root");
        TFile* tfile = new TFile(in_file_name.Data(),"read");
        tfile->GetObject("tree",ttree);

        event_tree = new tree(options, ttree, nEvents, flog, is_test);
    };
};

#endif
