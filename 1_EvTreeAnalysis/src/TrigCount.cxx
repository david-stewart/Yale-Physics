#include "TrigCount.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <cfloat>

TrigCount::TrigCount(int& runId_, vector<string> names_, vector<int> trig_ids_, 
        vector<bool*> b_bools) :
    runId{runId_},
    names{names_},
    trig_ids{trig_ids_},
    b_bools{b_bools},
    n_trigs{ b_bools.size() }
{
    if (n_trigs != names.size() || n_trigs != trig_ids.size()) {
        cout << "fatal: sizes of vectors initializing TrigCount not of same lengths."
             << endl;
        exit(2);
    }
    data[0] = vector<long int>{};
    for (int i{0}; i<n_trigs; ++i) data[0].push_back(0);
    for (auto n : names) len_names.push_back(n.size() > 10 ? n.size() : 10 );
};

void TrigCount::fill(){
    if (!data.count(runId)){
        data[runId] = vector<long int>{};
        for (int i{0}; i<n_trigs; ++i) data[runId].push_back(0);
    }
    for (int i{0}; i<n_trigs; ++i) {
        if (*b_bools[i]) {
            ++data[runId][i];
            ++data[0][i];
        }
    }
};

ostream& operator<<(ostream& os, TrigCount& T) {
    // write the header
    os << " #  " << setfill('-');
    for (auto i : T.len_names) os << setw(i) << "-" << " ";
    os << endl;

    os << left << setfill(' ');
    os << " #  ";
    for (auto i{0};i<T.n_trigs;++i) os << setw(T.len_names[i]) << T.names[i] << " ";
    os << endl;

    os << left << setfill(' ');
    os << " #  ";
    for (auto i{0};i<T.n_trigs;++i) os << setw(T.len_names[i]) << T.trig_ids[i] << " ";
    os << endl;

    os << " #  " << setfill('-');
    for (auto i : T.len_names) os << setw(i) << "-" << " ";
    os << endl;

    // output the data itself
    os << "  # run 00000000 stands for the sum of all runs " << endl;
    os << setfill(' ');
    os << "  # 00000000 ";
    os << right;
    for (int i{0}; i<T.n_trigs; ++i) {
        char cc[20];
        sprintf(cc, "%li.%li M", T.data[0][i]/1000000, (T.data[0][i] % 1000000 ) / 100);
        os << setw(T.len_names[i]) << cc << " ";
    }
    for (auto e : T.data) {
        os << " |  " << setfill('0') << setw(8) << e.first 
           << " " << setfill(' ') << right;
        for (auto i{0}; i<<T.n_trigs; ++i) os << setw(T.len_names[i]) << e.second[i] << " ";
        os << endl;
    }
    return os;
};
