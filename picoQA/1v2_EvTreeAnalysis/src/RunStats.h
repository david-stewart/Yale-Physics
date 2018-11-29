#ifndef RunStats__h
#define RunStats__h

#include "RunStats.h"


struct OneVar{ // statistics for an observable
    OneVar();
    bool   is_int;
    double min;
    double max;
    long int nEntries;
    long double sum;
    long double sum2;
    friend class OneVarFiller_Base;
    OneVar& operator+(const OneVar&);
    ClassDef("OneVar",1)
};

struct RunStats{
    ~RunStast();
    int  runId;
    int  eventId_0;
    int  eventId_1;
    int  time_0;
    int  time_1;
    int  nEvents;
    ClassDef("RunStats",1)
};

class OneVarFiller_Base{
    OneVarFiller_Base();
    ~OneVarFiller_Base();
    void operator()();
    virtual double value() = 0;
    public:
    OneVar data;
};
template<typename T>
class OneVarFiller : public OneVarFiller_Base {
    T& val;
    OneVarFiller(T& val_) : val{val_} {};
    OneVarFiller(const OneVarFiller<T>& rhs) : val { rhs.val } {};
    double value() { return val; }
};

#endif
