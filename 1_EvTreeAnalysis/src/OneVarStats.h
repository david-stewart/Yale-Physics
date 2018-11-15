#ifndef OneVarStats__h
#define OneVarStats__h

#include <TString.h>
#include <TProfile.h>
#include <string>
#include <map>

using namespace std;
class OneVarStats {
    private:
        int    runId;
        string name;
        int*    v_int;
        double* v_double;
        long long int nEntries;
        long double sum;
        long double sum2; // sum^2
        double min;
        double max;
        /* bool first_entry; */
        /* bool is_int; */
        void operator()(double);
    public:
        OneVarStats(int runId, string name);
        OneVarStats(int runId, string name, int*    val);
        OneVarStats(int runId, string name, double* val);
        OneVarStats(int runId, const OneVarStats& cp);
        void fill();
        friend ostream& operator<<(ostream&, OneVarStats&);
        ostream& print_header(ostream& os);
};

// a mapped container of all OneVarStats
class AllVarStats {
    private:
        int runId;
        // ?
    public:
        map<int, vector<OneVarStats> > data; // Map of OneVarStats indexed on runId
        AllVarStats(int& runId_);
        friend ostream& operator<< (ostream&, AllVarStats&);
        void addVar (OneVarStats);
        void addVar (string name, int*    val);
        void addVar (string name, double* val);
        void fill();
};

/* } */

#endif
