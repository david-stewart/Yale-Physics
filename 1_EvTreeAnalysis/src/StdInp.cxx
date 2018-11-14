#include "StdInp.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
// implrement class StdInp
void StdInp::update_log() {
    flog.close();
    flog.open(fname.c_str(), ios::app);
    /* fclose(flog); */
    /* flog = fopen(fname.c_str(), "a"); */
};

StdInp::StdInp ( 
       int argc, 
       const char** argv_, 
       bool is_test_,
       long long int nEvents_,
       TString log_name,
       TString in_file_name
) :
        is_test  { is_test_ },
        nEvents  { nEvents_ }
{
    std::vector<TString> argv;
    for (int i{0}; i<argc; ++i) { argv.push_back(argv_[i]); }

    if (argc > 1 && (argv[1] == "--help" || argv[1] == "-h")) {
        std::cout 
            << " Enter three arguments: [1] # events [2] output log name" << endl
            << " [3] has two options to list in the input files:"<<endl
            << " [3]:0  root file name (can include standard glob like dir/\\*.root)"<<endl
            << " [3]:1  [input.list (which contains root files)] [n] [N],"<<endl
            << "        where n, N, are n of N files (i.e. 3 7 means divide the files" << endl
            << "        into seven groups and take the third group)" <<endl;
        exit(0);
    }

    if (argc > 1) nEvents = argv[1].Atoi();
    if (argc > 2) log_name = argv[2];
    if (argc > 3) in_file_name = argv[3];
    if (argc > 4) for (int i{4}; i < argc; ++i) options.push_back(argv_[i]);

    // initialize log and file
    chain = new TChain("tree");

    fname = log_name.Data();
    flog.open(fname.c_str(), ios::trunc);
    if (!flog) cout << "fatal: couldn't open output log file \""<< log_name <<"\""<<endl;

    time(&start_time);
    flog <<       " # Starting log on (local time):  " << ctime(&start_time) << endl;
    /* fprintf(flog, " # Starting log on (local time):  %s", ctime(&start_time)); */

    // initalize the tchain
    if (in_file_name.EndsWith(".list")){
        flog <<       " # reading list of input files from " << in_file_name << endl;
        /* fprintf(flog, " # reading list of input files from %s\n", in_file_name.Data()); */
        vector<TString> root_files;
        TString word;
        ifstream file;
        file.open(in_file_name.Data());
        while (file >> word){
            if (word.EndsWith(".root")){
                root_files.push_back(word);
            } else {
                flog <<       " # Notice: skipping file " << word << " is not a \"\\*.root\" file" << endl;
                /* fprintf(flog, " # Notice: skipping file %s is not a \"\\*.root\" file.\n", word.Data()); */
            }
        }
        for (auto i : root_files) cout << " root file: " << i << endl;

        if (options.size() > 1) {
            int which_group = options[0].Atoi();
            int n_groups    = options[1].Atoi();
            flog <<       " # dividing the " << root_files.size() << " input files into " << n_groups << " groups"
                 << "reading group " << which_group << " for this run." << endl;
            /* fprintf(flog, " # dividing the %i input files into %i groups; reading group %i for this run\n", */
                    /* root_files.size(), n_groups, which_group); */
            int n_files = root_files.size() / n_groups;
            int remainder = root_files.size() % n_groups;
            /* cout << " " << which_group << "  of  " << n_groups << " groups of " << root_files.size() << " files" << endl; */
            for (int i{n_files * (which_group - 1)};
                    i < (which_group == n_groups ? root_files.size() : n_files * which_group); ++i){
                chain->AddFile(root_files[i]);
                flog << " # chain->Add("<<root_files[i]<<")"<<endl;
                /* fprintf(flog, " # chain->Add(%s)\n", root_files[i].Data()); */
                printf(" # chain->Add(%s)\n", root_files[i].Data());
            }
        } else {
            for (auto file : root_files) chain->AddFile(file.Data());
        };
    } else {
        flog <<       " # adding file(s) from " << in_file_name << endl;
        /* fprintf(flog, " # adding file(s) from %s\n", in_file_name.Data()); */
        chain->Add(in_file_name.Data());
    }
};

StdInp::~StdInp() {
    time_t end_time;
    time(&end_time);
    double f_seconds { difftime(end_time, start_time) };
    int seconds { (int) f_seconds };
    int hr { seconds/3600 };
    int min { (seconds - 3600*hr)/60 };
    int sec { seconds - 3600*hr - 60*min };
    flog <<      " # Ending log on (local time):   " << ctime(&end_time) << endl;
    /* fprintf(flog," # Ending log on (local time):   %s", ctime(&end_time)); */
    flog <<      " # Time ellapsed: " << seconds << " seconds or (in hr:min:sec) "
         << setprecision(0) << setw(2) << hr << ":" << setw(2) << min << setw(2) << sec << ")" << endl;
    flog.unsetf(ios::fixed | ios::scientific);
    /* fprintf(flog," # Time ellapsed: %i seconds or (in hr:min:sec) %02i:%02i:%02i\n", */
            /* (int) seconds, hr, min, sec); */
    flog.close();
    /* fclose(flog); */
};
