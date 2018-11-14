#include "OneVarStats.h"
#include <math.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <cfloat>


using namespace std;

OneVarStats::OneVarStats(int runId_, string name_) :
    runId{runId_},
    name{name_},
    nEntries{0},
    sum{0},
    sum2{0},
    min{0},
    max{0}
{};

OneVarStats::OneVarStats(int runId_, string name_, int* val_) :
    OneVarStats(runId_, name_)
{
  v_int = val_;
  v_double = nullptr;
};
OneVarStats::OneVarStats(int runId_, string name_, double* val_) :
    OneVarStats(runId_, name_)
{
  v_int = nullptr;
  v_double = val_;
};

// copy constructor for a new run
OneVarStats::OneVarStats(int runId_, const OneVarStats& cp) :
    OneVarStats(runId_, cp.name)
{
    v_int = cp.v_int;
    v_double = cp.v_double;
};

void OneVarStats::fill() {
    if (v_int) this->operator()(static_cast<double>(*v_int));
    else       this->operator()(*v_double);
};

void OneVarStats::operator()(double val){
    if (val != val) return; // this is the condition that the input is NAN
    if (nEntries == 0) {
        min = val;
        max = val;
    } else {
        if (val < min) min = val;
        if (val > max) max = val;
    }
    ++nEntries;
    sum += val;
    sum2 += val*val;
};

ostream& OneVarStats::print_header(ostream& os){
    os 
       << setfill(' ')
       << " #  "  
       << setfill('-')
       << setw(8) << "-" << " "
       << left << setw(19) << "-" << " "
       << setw(11) << "-" << " "
       << setw(11) << "-" << " "
       << setw(13) << "-" << " "
       << setw(13) << "-" << " "
       << setw(13) << "-" << " "
       << setw(11) << "-" << " "
       /* << general */
       << setw(13) << "-" << " "
       << setw(13) << "-" << " "
       << endl
       << setfill(' ')
       << " #  " << setw(8) << "runId" << " "
       << left << setw(19) << "variable" << " " 
       /* << setw(8)  << "runId" << " " */
       << setw(11) << "min" << " " 
       << setw(11) << "max" << " " 
       << setw(13) << "mean" << " "
       << setw(13) << "stdev" << " " 
       << setw(13) << "stdev_mean" << " " 
       << setw(11) << "nEntries" << " "
       << setfill(' ')
       /* << general */
       << setw(13) << "sum" << " "
       << setw(13) << "sum2"
       << endl
       << setfill('-')
       << " #  " 
       << setw(8) << "-" << " "
       << setfill('-')
       << left << setw(19) << "-" << " "
       << setw(11) << "-" << " "
       << setw(11) << "-" << " "
       << setw(13) << "-" << " "
       << setw(13) << "-" << " "
       << setw(13) << "-" << " "
       << setw(11) << "-" << " "
       /* << general */
       << setw(13) << "-" << " "
       << setw(13) << "-" << " "
       << setfill(' ')
       << endl;
    return os;
};

ostream& operator<<(ostream& os, OneVarStats const& stats) {
    // get mean
    double mean  { static_cast<double>(stats.sum / stats.nEntries) };
    double stdev { static_cast<double>(sqrt(stats.sum2/stats.nEntries - mean*mean)) };
    double stdev_mean { stdev / sqrt(stats.nEntries) };
    os << " :  " << setfill('0') << setw(8) << stats.runId << setfill(' ')  << " "
       << left << setw(19) << stats.name << " " << right;
    /* os << " #!v 1615819 " << left << setw(19) << stats.name << " " << right; */
    if (stats.v_int) {
        os << setw(11) << static_cast<int>(stats.min) << " " 
           << setw(11) << static_cast<int>(stats.max) << " " 
           << scientific << setprecision(6) << setw(13) << mean << " "
           << setw(13) << stdev << " " 
           << setw(13) << stdev_mean << " " 
           << setw(11) << stats.nEntries << " "
           /* << general */
           << setw(13) << static_cast<long long int>(stats.sum) << " "
           << setw(13) << static_cast<long long int>(stats.sum2);
    } else {
        os.unsetf(ios::fixed | ios::scientific);
        /* os << general; */
        os << setw(11) << stats.min << " " 
           << setw(11) << stats.max << " " 
           << scientific << setprecision(6) << setw(13) << mean << " "
           << setw(13) << stdev << " " 
           << setw(13) << stdev_mean << " " 
           << setw(11) << stats.nEntries << " "
           /* << general */
           << setw(13) << stats.sum  << " "
           << setw(13) << stats.sum2;
    }
    return os;
};

