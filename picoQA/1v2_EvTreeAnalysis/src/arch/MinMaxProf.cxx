#include "MinMaxProf.h"
#include <iostream>
using namespace std;


MinMaxProf::MinMaxProf(TProfile& prof_e_, TProfile& prof_s_, const char* name_, Int_t i_bin_) :
    prof_e(prof_e_), prof_s(prof_s_), name{name_}, i_bin{i_bin_} 
{
    f_bin = (float) i_bin;
};

MinMaxProf_int::MinMaxProf_int(Int_t& val_, TProfile& prof_e_, TProfile& prof_s_, const char* name_, Int_t i_bin_) :
    val{val_}, is_first{true}, MinMaxProf{prof_e_, prof_s_, name_, i_bin_}
{};

MinMaxProf_double::MinMaxProf_double(double& val_, TProfile& prof_e_, TProfile& prof_s_, const char* name_, Int_t i_bin_) :
    val{val_}, is_first{true}, MinMaxProf{prof_e_, prof_s_, name_, i_bin_}
{};

TString MinMaxProf::stats_header(){
    return TString::Format(" %12s %12s %12s %12s %12s", "min","max","mean","std_mean","std_distr");
};
TString MinMaxProf::stats_dashes(){
    return TString::Format(" %12s %12s %12s %12s %12s", "------------","------------","------------","------------","------------");
};

TString MinMaxProf_int::getstats() {
    /* cout << "name " << name << " " << minVal << " " << maxVal << " " << prof_e.GetBinContent(i_bin) << " " << prof_e.GetBinError(i_bin) << " " << prof_s.GetBinError(i_bin) << endl; */

    /* cout << TString::Format(" %12i %12i %12.5g %12.5g %12.5g", minVal, maxVal, */
    /*         prof_e.GetBinContent(i_bin), prof_e.GetBinError(i_bin), prof_s.GetBinError(i_bin)) << endl; */
    if (is_first) return TString::Format("# Error! No values entered for %s", name);
    else return TString::Format(" %12i %12i %12.5g %12.5g %12.5g", minVal, maxVal, 
            prof_e.GetBinContent(i_bin), prof_e.GetBinError(i_bin), prof_s.GetBinError(i_bin));
};

TString MinMaxProf_double::getstats() {
    /* cout << "name " << name << " " <<  minVal << " " << maxVal << " " << prof_e.GetBinContent(i_bin) << " " << prof_e.GetBinError(i_bin) << " " << prof_s.GetBinError(i_bin) << endl; */
    /* cout << TString::Format(" %12i %12i %12.5g %12.5g %12.5g", minVal, maxVal, */
            /* prof_e.GetBinContent(i_bin), prof_e.GetBinError(i_bin), prof_s.GetBinError(i_bin)) << endl; */
    if (is_first) return TString::Format("# Error! No values entered for %s", name);
    else return TString::Format(" %12.5g %12.5g %12.5g %12.5g %12.5g", minVal, maxVal, 
            prof_e.GetBinContent(i_bin), prof_e.GetBinError(i_bin), prof_s.GetBinError(i_bin));
};

void MinMaxProf_int::fill() {
    prof_e.Fill(f_bin, val);
    prof_s.Fill(f_bin, val);
    if (is_first){
        is_first = false;
        minVal = val;
        maxVal = val;
    } else {
        if (val < minVal) minVal = val;
        if (val > maxVal) maxVal = val;
    }
    /* cout << " updating " << name << " with " << val << "  min: " <<minVal << "  max: " << maxVal << endl; */
};

void MinMaxProf_double::fill() {
    prof_e.Fill(f_bin, val);
    prof_s.Fill(f_bin, val);
    if (is_first){
        is_first = false;
        minVal = val;
        maxVal = val;
    } else {
        if (val < minVal) minVal = val;
        if (val > maxVal) maxVal = val;
    }
    /* cout << " updating " << name << " with " << val << "  min: " <<minVal << "  max: " << maxVal << endl; */
};
