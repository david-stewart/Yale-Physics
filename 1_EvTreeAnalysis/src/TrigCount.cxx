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
    n_trigs{ (int) b_bools.size() }
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
    os << " #  run 00000000 stands for the sum of all runs " << endl;

    os << " #  " << setfill('-') << setw(8) << "-" << " ";
    for (auto i : T.len_names) os << setw(i) << "-" << " ";
    os << endl;

    os << left << setfill(' ');
    os << " #  " << setw(8) << "trigName" << " ";
    for (int i=0;i<T.n_trigs;++i) os << setw(T.len_names[i]) << T.names[i] << " ";
    os << endl;

    os << left << setfill(' ');
    os << " #  " << setw(8) << "trigNum" << " ";
    for (int i=0;i<T.n_trigs;++i) os << setw(T.len_names[i]) << T.trig_ids[i] << " ";
    os << endl;

    os << " #  " << setfill('-') << setw(8) << "-" << " ";
    for (auto i : T.len_names) os << setw(i) << "-" << " ";
    os << endl;

    // output the data itself
    os << setfill(' ');
    os << " #  00000000 "; 
    os << right;
    for (int i{0}; i<T.n_trigs; ++i) {
        char cc[20];
        /* os << setw( T.len_names[i] - 2 ) << (double)T.data[0][i]/1.0e6 << " M "; */
        sprintf(cc, "%i.%03i M", (int)T.data[0][i]/1000000, ((int)T.data[0][i] % 1000000)/1000);
        os << setw(T.len_names[i]) << cc << " ";
    }
    os << endl;

    for (auto e : T.data) {
        os << " |  " << setfill('0') << setw(8) << e.first 
           << " " << setfill(' ') << right;
        for (int i=0; i<T.n_trigs; ++i) os << setw(T.len_names[i]) << e.second[i] << " ";
        os << endl;
    }
    return os;
};
