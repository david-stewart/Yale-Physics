#include "StdInp.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;
// implrement class StdInp
void StdInp::update_log() {
    flog.close();
    flog.open(fname.c_str(), ios::app);
    /* fclose(flog); */
    /* flog = fopen(fname.c_str(), "a"); */
};

StdInp::StdInp ( string inputs, int nEvents_, string fname_, string r_fname_  )
 :
     nEvents{nEvents},
     fname{fname_},
     r_fname{r_fname_}
{
    // fill in the arc and argv
    argv.push_back("prog_name");
    istringstream i_string{inputs};
    string word;
    while(i_string >> word) argv.push_back(word);
    int argc = argv.size();

    if (argc > 1 && (argv[1] == "--help" || argv[1] == "-h")) {
        std::cout 
            << " Enter three arguments: [1] # events [2] output log name" << endl
            << " [3] enter output root files name"<<endl;
        exit(0);
    }

    // override the default values
    if (argc > 1) nEvents = stoi(argv[1]);
    if (argc > 2) fname   = argv[2];
    if (argc > 3) r_fname = argv[3];
    if (argc > 4) for (int i{4}; i < argc; ++i) options.push_back(argv[i]);


    TString temp_string(fname);
    if (temp_string.EndsWith(".root")) {
        cout << "fatal: log file name ends with '.root'. Terminating program." << endl;
        exit(2);
    }
    flog.open(fname.c_str(), ios::trunc);
    if (!flog) cout << "fatal: couldn't open output log file \""<< fname <<"\""<<endl;

    time(&start_time);
    flog <<       " # Starting log on (local time):  " << ctime(&start_time) << endl;
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
