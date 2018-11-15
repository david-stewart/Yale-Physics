#ifndef TrigCount__h
#define TrigCount__h

#include <TString.h>
#include <TProfile.h>
#include <string>
#include <vector>
#include <map>

using namespace std;
class TrigCount {
    private:
        int&           runId;
        vector<string> names;
        vector<int>    trig_ids;
        vector<bool*>  b_bools;
        int            n_trigs;
        map<int, vector<long int>> data;
        vector<int>    len_names; // for formated printing; at least 10 digits
    public:
        TrigCount(int& runId_, vector<string> names, vector<int> trigIds, vector<bool*> trig_bools);
        void fill();
        // this next value prints the entire required data, header and all
        friend ostream& operator<<(ostream&, TrigCount&);
};

#endif
