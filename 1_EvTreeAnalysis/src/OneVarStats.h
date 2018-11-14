#ifndef OneVarStats__h
#define OneVarStats__h

#include <TString.h>
#include <TProfile.h>
#include <string>

using namespace std;
class OneVarStats {
    private:
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
        OneVarStats(string name);
        OneVarStats(string name, int*    val);
        OneVarStats(string name, double* val);
        void fill();
        friend ostream& operator<<(ostream&, OneVarStats const&);
        ostream& print_header(ostream& os);
};


#endif
