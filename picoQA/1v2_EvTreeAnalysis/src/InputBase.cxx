#include "InputBase.h"

#include <TString.h>

/* ClassImp(InputBase) */
InputBase::InputBase(int argc, const char** argv, bool has_help_msg_) : 
    has_help_msg{has_help_msg_},
    give_help_msg{false},
    n_inputs{argc-2}
{
    for (int i{1}; i<argc; ++i) ss_args << " " << argv[i];
    open_log();
};

InputBase::InputBase(string line, bool has_help_msg_) : 
    has_help_msg{has_help_msg_},
    give_help_msg{false},
    n_inputs{0}
{
    TString tmp{line};
    tmp.ReplaceAll(":"," ");
    istringstream istring(tmp.Data());
    string word;
    while (istring >> word) {
        ss_args << " " << word;
        ++n_inputs;
    }
    open_log();
};

void InputBase::open_log() {
    ss_args >> log_name;

    if (has_help_msg && (log_name == "-h" || log_name == "--help")){
        give_help_msg = true; 
        return;
    }

    if (log_name.find(".log",0) == string::npos) {
        cout << "fatal: log file must end with \".log\". The name given was \"" << log_name << "\"." << endl;
        exit(2);
    }
    f_log.open(log_name.c_str(), ios::trunc);
    time(&start_time);
    f_log <<       " # Starting log on (local time):  " << ctime(&start_time);
};

InputBase::~InputBase() {
    time_t end_time;
    time(&end_time);
    double f_seconds { difftime(end_time, start_time) };

    f_log <<      " # Ending log on (local time):   " << ctime(&end_time);// << endl;
    f_log <<      " # Time ellapsed: " << (int) f_seconds << " seconds or (in hr:min:sec) "
          << time_ellapsed() << endl;
    f_log.unsetf(ios::fixed | ios::scientific);
    f_log.close();
};

string InputBase::time_ellapsed(){
    time_t end_time;
    time(&end_time);
    double f_seconds { difftime(end_time, start_time) };
    int seconds { (int) f_seconds };
    int hr { seconds/3600 };
    int min { (seconds - 3600*hr)/60 };
    int sec { seconds - 3600*hr - 60*min };

    ostringstream os;
    os << setprecision(0) << setw(2) << setfill('0')<< hr <<":"<<setw(2)<<min <<":"<< setw(2) << sec;
    return os.str();
};

void InputBase::update_log() {
    f_log.close();
    f_log.open(log_name.c_str(), ios::app);
};
