#include "RunStats.h"
#include <iostream>
using namespace std;

//---------------------------------------------------------------
ClassImp(OneVar)

OneVar::OneVar() :
    is_int{false}, min{0}, max{0}, nEntries{0}, sum{0}, sum2{0}
{};
OneVar::~OneVar () {};
/* OneVar::OneVar(const OneVar&) {}; */
//---------------------------------------------------------------

OneVarFiller::~OneVarFiller(){};


OneVarFiller::OneVarFiller(int* p) :
    p_int{p}, p_double{nullptr}, is_int{true}
{
    data.is_int = true;
};

OneVarFiller::OneVarFiller(double* p) :
    p_int{nullptr}, p_double{p}, is_int{false}
{
    data.is_int = false;
};

void OneVarFiller::operator()() {
    double v { is_int ? *p_int : *p_double } ;
    if (v != v) return;
    /* std::cout << "This is v: " << v << std::endl; */
    ++data.nEntries;
    if (data.nEntries == 1) {
        data.min = v;
        data.max = v;
        data.sum = v;
        data.sum2 = v*v;
    } else {
        if (data.min > v) data.min = v;
        if (data.max < v) data.max = v;
        data.sum += v;
        data.sum2 += v*v;
    }
    /* std::cout << " " << data.is_int << " " << data.nEntries << " min:" << data.min */ 
                /* << " max:"<<data.max<<" sum:"<<data.sum<<" sum2:"<<data.sum2<<std::endl; */
};

OneVarFiller::OneVarFiller(const OneVarFiller& rhs) {
    is_int = rhs.is_int;
    p_int =  rhs.p_int;
    p_double = rhs.p_double;
    data = OneVar{};
    data.is_int = rhs.is_int;
};

RunStats::~RunStats(){};
OneVar& OneVar::operator+(const OneVar& rhs){
    if (min > rhs.min) min = rhs.min;
    if (max < rhs.max) max = rhs.max;
    sum += rhs.sum;
    sum2 += rhs.sum2;
    nEntries += rhs.nEntries;
    return *this;
};

