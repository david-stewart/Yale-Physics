#include "OneVarStats.h"
#include <math.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <cfloat>
#include <iostream>
#include <sstream>


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
  isInt = true ;
  v_int = val_;
  v_double = nullptr;
};
OneVarStats::OneVarStats(int runId_, string name_, double* val_) :
    OneVarStats(runId_, name_)
{
  isInt = false;
  v_int = nullptr;
  v_double = val_;
};

// copy constructor for a new run
OneVarStats::OneVarStats(int runId_, const OneVarStats& cp) :
    OneVarStats(runId_, cp.name)
{
    v_int = cp.v_int;
    v_double = cp.v_double;
    isInt = cp.isInt;
};

void OneVarStats::fill() {
    if (isInt) this->operator()(static_cast<double>(*v_int));
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

ostream& operator<<(ostream& os, OneVarStats& stats) {
    // get mean
    double mean  { static_cast<double>(stats.sum / stats.nEntries) };
    double stdev { static_cast<double>(sqrt(stats.sum2/stats.nEntries - mean*mean)) };
    double stdev_mean { stdev / sqrt(stats.nEntries) };
    os << " :  " << setfill('0') << setw(8) << stats.runId << setfill(' ')  << " "
       << left << setw(19) << stats.name << " " << right;
    /* os << " #!v 1615819 " << left << setw(19) << stats.name << " " << right; */
    if (stats.isInt) {
        os << setw(11) << static_cast<int>(stats.min) << " " 
           << setw(11) << static_cast<int>(stats.max) << " " 
           << /*scientific << setprecision(6) <<*/ setw(13) << mean << " "
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
           << /*scientific << setprecision(6) << */ setw(13) << mean << " "
           << setw(13) << stdev << " " 
           << setw(13) << stdev_mean << " " 
           << setw(11) << stats.nEntries << " "
           /* << general */
           << setw(13) << stats.sum  << " "
           << setw(13) << stats.sum2;
    }
    return os;
};

AllVarStats::AllVarStats(int& runId_) : 
    runId{runId_} 
{};

void AllVarStats::fill() {
    if (!data.count(runId)){
        data[runId] = vector<OneVarStats>{};
        for (auto& x : data[0]) data[runId].push_back({runId, x});
    }
    for (auto& x : data[0])     x.fill();
    for (auto& x : data[runId]) x.fill();
};

void AllVarStats::addVar (string name, int*    val){
    /* cout << " len data " << data.size() << endl; */
    cout << "_"<<name<<"_ "<<endl;
    if (!data.count(0)) data[0] = vector<OneVarStats>{};
    /* cout << " len data " << data.size() << endl; */
    if (name_map.count(name)) {
        cout << "fatal: Error in adding variable \"" << name << "\"" << endl;
        cout << "       This variable has already been added!" << endl;
    } else {
        name_map[name] = data[0].size();
        cout << " : names ";
        for (auto i : name_map) cout << " " << i.second << " " << i.first;
        cout << endl;
    }
    for (auto& p : data) { 
        /* cout << " PUSHING " << name << " into " << p.first << endl; */
        cout << " name " << name << "  presize " << p.second.size();
        p.second.push_back(OneVarStats{p.first,name,val}); 
        cout << " post size " << p.second.size() << endl;
    }
};

void AllVarStats::addVar (string name, double* val){
    if (!data.count(0)) data[0] = vector<OneVarStats>{};
    if (name_map.count(name)) {
        cout << "fatal: Error in adding variable \"" << name << "\"" << endl;
        cout << "       This variable has already been added!" << endl;
    } else {
        name_map[name] = data[0].size();
    }
    for (auto& p : data) p.second.push_back(OneVarStats{p.first,name,val});
};

ostream& operator<< (ostream& os, AllVarStats& obj){
    for (auto& x : obj.data) {
        /* cout << " LION " << x.first << endl; */
        OneVarStats::print_header(os);
        for (auto& y : x.second) os << y << endl;
        /* { cout << " LIONESS " << y.getrunid() << endl; os << y << endl;} */
        os << endl;
    }
    return os;
};

void operator<< (AllVarStats& lhs, string line) {
    /* cout << "z0" << endl; */
    istringstream inp{line};
    /* cout << "z1" << endl; */
    int runId;
    /* cout << "z2" << endl; */
    string trash, name, min, max;// use mean to see if it is an integer or a float
    /* cout << "z3" << endl; */

    inp >> trash >> runId >> name >> min >> max;
    /* cout << "z4" << endl; */

    bool isInt = ( (min.find('.',0) == string::npos) || (max.find('.',0) == string::npos) );
    
    // if a new variable, then add it to all runIds
    /* cout << "z5" << endl; */
    if (!lhs.name_map.count(name)) {
    /* cout << "z6" << endl; */
        if (isInt) { lhs.addVar(name, (int*)    nullptr); } //cout << "int" << endl; }
        else       { lhs.addVar(name, (double*) nullptr); } //cout << "double" << endl; }
        /* cout << "wolf2: " << lhs.data.size() << endl; */
        /* cout << "wolf2: " << lhs.data[0].size() << endl; */
        /* for (auto i : lhs.data) { */
            /* cout << i.first << endl; */
            /* cout << i.second.size() << endl; */
        /* } */
    /* cout << "z7" << endl; */
    }
    /* cout << "z8" << endl; */

    // if new runId, then add a new runId
    /* cout << " name " << name << " runId " << runId << endl; */
    if (!lhs.data.count(runId)) {
        /* cout << " c-0" << endl; */
        lhs.data[runId] = vector<OneVarStats>{};
        for (auto& x : lhs.data[0]) lhs.data[runId].push_back({runId, x});
    }
    /* for (auto x : lhs.data) { */ 
        /* cout << " run id " << x.first; */
        /* for (auto y : x.second) cout << "att " << y << endl; */
        /* cout << endl; */
    /* } */
    /* cout << "z9" << endl; */

    // now add the value
    /* lhs.data[0]    [lhs.name_map[name]].add(line); */ // the 0 is already summed up and will be tallie dlike any other run

    /* cout << " name map " << (lhs.name_map[name]) << endl; */
    /* cout << lhs.data[runId].size() << endl; */
    /* cout << " shocker " << endl; */
    /* for (auto i : lhs.data) { */ 
        /* cout << " i.first " << i.first << "  " << (i.first == runId) << endl; */ 
        /* cout << " name_map " << lhs.name_map[name] << endl; */
        /* cout << lhs.data[runId][lhs.name_map[name]].min << endl; */
    /* } */
    lhs.data[runId][lhs.name_map[name]].add(line);
    /* cout << "z10" << endl; */
    return;
};

void OneVarStats::add(string inp){
    int runId_;
    string name_;
    long long int nEntries_;
    long double sum_;
    long double sum2_;
    double min_;
    double max_;
    /* cout << "z - " << inp << "||" << endl; */
    /* cout << "z - 0" << endl; */

    string trash0, trash1, trash2, trash3;
    /* cout << "z - 1" << endl; */
    istringstream ss{inp};
    /* cout << "z - 2" << endl; */
    /* cout << " reading " << ss.str() << endl; */
    ss >> trash0 >> runId_ >> name_ >> min_ >> max_ >> trash1 >> trash2>> trash3>> nEntries_ >> sum_ >> sum2_;
    /* cout << " runId_ " << runId_ << " name_ " << name_ << " min_ " << min_ << " max_ " << max_ << " nEntries_ " << nEntries_ << " sum_ " << sum_ << " sum2_ " << sum2_ << endl; */

    istringstream s0{inp};
    /* cout << "test: " << endl; */
    /* while (s0 >> trash0) cout << " " << trash0; */
    /* cout << endl; */
    /* cout << "z - 3" << endl; */
    
    /* if (runId != runId_ || name_ != name) { */
    /*     cout << "fatal error, trying to entry of runId::variable " << runId_<<"::"<<name_ */
    /*          << "to existing record " << runId<<"::"<<name<<endl; */
    /*     exit(2); */
    /* } */
    /* cout << "z - 4" << " " << min_ << endl; */
    /* cout << " this stuff " << runId << endl; */
    /* cout << " min " << min << endl; */
    if (nEntries == 0){
        min = min_;
        max = max_;
    } else {
        if (min_ < min) min = min_;
        if (max_ > max) max = max_;
    }
    nEntries += nEntries_;
    sum += sum_;
    sum2 += sum2_;
};

    

