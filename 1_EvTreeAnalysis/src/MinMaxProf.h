#ifndef MinMixProf__h
#define MinMixProf__h

#include <TString.h>
#include <TProfile.h>

class MinMaxProf {
    public:
    virtual TString getstats() = 0; // return the line:  # [min] [max] [mean] [std dev]
    virtual void fill() = 0;

    MinMaxProf(TProfile&, TProfile&, const char*, Int_t);
    TProfile& prof_e;
    TProfile& prof_s;
    Int_t i_bin;
    const char* name;
    float f_bin;

};

class MinMaxProf_int : public MinMaxProf { 
    private:
        Int_t& val;
        Int_t  minVal;
        Int_t  maxVal;
        bool is_first;
    public:
    MinMaxProf_int(Int_t&, TProfile&, TProfile&, const char*, Int_t);
    TString getstats();
    void fill();
};

class MinMaxProf_double : public MinMaxProf { 
    private:
        Double_t& val;
        Double_t minVal;
        Double_t maxVal;
        bool is_first;
    public:
    MinMaxProf_double(Double_t&, TProfile&, TProfile&, const char*, Int_t);
    TString getstats();
    void fill();
};

#endif
