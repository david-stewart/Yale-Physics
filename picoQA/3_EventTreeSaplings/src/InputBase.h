#ifndef InputBase__h
#define InputBase__h

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <time.h>
#include <iomanip>
#include <map>

using namespace std;
class InputBase {
    public:
    //constructors
    InputBase(int argc, const char** argv, bool has_help_msg = false); 
    // if this is true, then don't kill if -h is an option
    InputBase(string line, bool has_help_msg = false);
    virtual ~InputBase();

    //output log
    bool     has_help_msg;
    bool     give_help_msg;

    string   log_name;
    ofstream f_log;

    void update_log();    // write the current log and reopen it for further input
    stringstream ss_args; // all of the options from the input
    map<string,string> map_args;
    int n_inputs;         // number of inputs AFTER the log file name
    string time_ellapsed();

    private:
    void open_log();
    time_t start_time;
};

#endif
