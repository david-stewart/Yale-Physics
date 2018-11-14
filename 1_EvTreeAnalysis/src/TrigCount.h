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
        int n_trigs;
        vector<*bool>              trig_vals;
        map<int, vector<long int>> map;
        vector<string> trig_names;
        vector<int>    trig_vals;
        vector<int>    len_names; // for formatted printing; at least 10 digits
    public:
        TrigCount(vector<string> names, vector<int> trigIds, vector<*bool> trig_bools);
        void fill();
        // this next value prints the entire required data, header and all
        friend ostream& operator<<(ostream&, TrigCount const&);
};


#endif
