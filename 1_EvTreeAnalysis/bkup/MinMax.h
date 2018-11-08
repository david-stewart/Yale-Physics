#ifndef MINMAX__H
#define MINMAX__H

#include <vector>
#include "TProfile.h"
#include <iostream>

using namespace std;

class BranchMinMax {
    public:
    TProfile* prof;
    int i_bin;
    float f_bin;
    const char* name;
    double minval;
    double maxval;
    virtual void update() = 0;
    bool is_first;
    BranchMinMax(TProfile* prof_, int i_bin_, const char* name_) :
        prof{prof_}, i_bin{i_bin_}, f_bin{(float) i_bin_}, name{name_},
        minval{0}, maxval{0}, is_first{true}
    {};
    double mean() { return prof->GetBinContent(i_bin); }
    double std()  { return prof->GetBinError(i_bin); }
    void print() { cout << " name:"<<name<<"   min:"<<minval<<"  max:"<<maxval<<"  mean:"<<mean()<<"  std:"<<std()<<endl; };
};

class BranchMinMax_Int : public BranchMinMax {
    public:
        int& val;
    BranchMinMax_Int(TProfile* prof_, int i_bin_, const char* name_, int& val_) :
        BranchMinMax{prof_, i_bin_, name_}, val{val_}
    {};
    void update() {
        if (is_first) {
            is_first = false;
            minval = val;
            maxval = val;
        } else {
            if (val < minval) minval = val;
            if (val > maxval) maxval = val;
        }
        prof->Fill(f_bin, val);
    };
};

class BranchMinMax_Double : public BranchMinMax {
    public:
        double& val;
    BranchMinMax_Double(TProfile* prof_, int i_bin_, const char* name_, double& val_) :
        BranchMinMax{prof_, i_bin_, name_}, val{val_}
    {};
    void update() {
        if (is_first) {
            is_first = false;
            minval = val;
            maxval = val;
        } else {
            if (val < minval) minval = val;
            if (val > maxval) maxval = val;
        }
        prof->Fill(f_bin, val);
    };
};

/* class BranchMinMax_Double : public BranchMinMax { */
/*     public: */
/*         double& val; */
/*     BranchMinMax_Int(TProfile* prof_, int i_bin_, const char* name_, int& val_) : */
/*         prof{prof}, */ 
/*         i_bin{i_bin_}, */
/*         f_bin{(float)i_bin_}, */
/*         name{name_}, */ 
/*         val{val_}, */
/*         is_first{true}, */
/*         minval{0}, */
/*         maxval{0} */
/*     {}; */
/*     void update() { */
/*         if (is_first) { */
/*             is_first = false; */
/*             minval = val; */
/*             maxval = val; */
/*         } else { */
/*             if (val < minval) minval = val; */
/*             if (val > maxval) maxval = val; */
/*         } */
/*         prof->Fill(f_bin, val); */
/*     }; */
/* }; */

#endif
