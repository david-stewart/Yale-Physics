#include "OneVarStats.h"
#include <math.h>
#include <iostream>
#include <iomanip>
#include <string>


using namespace std;

OneVarStats::OneVarStats(string name_) :
    name{name_},
    nEntries{0},
    sum{0},
    sum2{0},
    min{0},
    max{0}
{};

OneVarStats::OneVarStats(string name_, int* val_) :
    OneVarStats(name_)
{
  v_int = val_;
  v_double = nullptr;
};
OneVarStats::OneVarStats(string name_, double* val_) :
    OneVarStats(name_)
{
  v_int = nullptr;
  v_double = val_;
};

void OneVarStats::fill() {
    if (v_int) this->operator()(static_cast<double>(*v_int));
    else       this->operator()(*v_double);
};

void OneVarStats::operator()(double val){
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
       << " #      " 
       << setfill('-')
       << left << setw(19) << "-" << " "
       << setw(10) << "-" << " "
       << setw(10) << "-" << " "
       << setw(12) << "-" << " "
       << setw(12) << "-" << " "
       << setw(12) << "-" << " "
       << setw(10) << "-" << " "
       /* << general */
       << setw(12) << "-" << " "
       << setw(12) << "-" << " "
       << endl
       << setfill(' ')
       << " #      " << left << setw(19) << "variable name" << " " 
       << setw(10) << "min" << " " 
       << setw(10) << "max" << " " 
       << setw(12) << "mean" << " "
       << setw(12) << "stdev" << " " 
       << setw(12) << "stdev_mean" << " " 
       << setw(10) << "nEntries" << " "
       << setfill(' ')
       /* << general */
       << setw(12) << "sum" << " "
       << setw(12) << "sum2"
       << endl
       << setfill('-')
       << " #      " 
       << setfill('-')
       << left << setw(19) << "-" << " "
       << setw(10) << "-" << " "
       << setw(10) << "-" << " "
       << setw(12) << "-" << " "
       << setw(12) << "-" << " "
       << setw(12) << "-" << " "
       << setw(10) << "-" << " "
       /* << general */
       << setw(12) << "-" << " "
       << setw(12) << "-" << " "
       << setfill(' ')
       << endl;
    return os;
};

ostream& operator<<(ostream& os, OneVarStats const& stats) {
    // get mean
    double mean  { static_cast<double>(stats.sum / stats.nEntries) };
    double stdev { static_cast<double>(sqrt(stats.sum2/stats.nEntries - mean*mean)) };
    double stdev_mean { stdev / sqrt(stats.nEntries) };
    os << " #!val: " << left << setw(19) << stats.name << " " << right;
    if (stats.v_int) {
        os << setw(10) << static_cast<int>(stats.min) << " " 
           << setw(10) << static_cast<int>(stats.max) << " " 
           << scientific << setprecision(6) << setw(12) << mean << " "
           << setw(12) << stdev << " " 
           << setw(12) << stdev_mean << " " 
           << setw(10) << stats.nEntries << " "
           /* << general */
           << setw(12) << static_cast<long long int>(stats.sum) << " "
           << setw(12) << static_cast<long long int>(stats.sum2);
    } else {
        os.unsetf(ios::fixed | ios::scientific);
        /* os << general; */
        os << setw(10) << stats.min << " " 
           << setw(10) << stats.max << " " 
           << scientific << setprecision(6) << setw(12) << mean << " "
           << setw(12) << stdev << " " 
           << setw(12) << stdev_mean << " " 
           << setw(10) << stats.nEntries << " "
           /* << general */
           << setw(12) << stats.sum  << " "
           << setw(12) << stats.sum2;
    }
    return os;
};

