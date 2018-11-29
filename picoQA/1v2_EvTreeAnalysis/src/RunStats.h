#ifndef RunStats__h
#define RunStats__h

#include "RunStats.h"
#include "TObject.h"

/* struct OneVarList{ */
/*     string name; */
/*     std::vector< std::pair OneVarFiller<int>> v_int; */
/*     std::vector<OneVarFiller<double>> v_double; */

struct Ticker{
    bool& yes_no;
    long int n;
    Ticker(bool& yn_) : yes_no{yn_}, n{0} {};
    Ticker(const Ticker& rhs) : yes_no{rhs.yes_no}, n{0} {};
    void operator()() { if (yes_no) ++n; };
};


struct OneVar : public TObject { // statistics for an observable
    OneVar();
    virtual ~OneVar();
    /* OneVar(const OneVar&); */
    bool   is_int;
    double min;
    double max;
    long int nEntries;
    long double sum;
    long double sum2;
    friend class OneVarFiller_Base;
    OneVar& operator+(const OneVar&);
    ClassDef(OneVar,1)
};

// skip building these for now
struct RunStats{
    ~RunStats();
    RunStats(int);
    int  runId;
    int  eventId_0;
    int  eventId_1;
    int  time_0;
    int  time_1;
    int  nEvents;
    /* ClassDef("RunStats",1) */
};

class OneVarFiller{
    double* p_double;
    int*    p_int;
    bool is_int;
    /* virtual double value() = 0; */
    public:
    void operator()();
    OneVarFiller(int*);
    OneVarFiller(double*);
    OneVarFiller(const OneVarFiller&);
    ~OneVarFiller();
    OneVar data;
};
/* template<typename T> */
/* class OneVarFiller : public OneVarFiller_Base { */
/*     T& val; */
/*     double value() { return val; } */
/*     public: */
/*     OneVarFiller(T& val_, bool is_int_ = true) : OneVarFiller_Base{is_int_}, val{val_} {}; */
/*     OneVarFiller(const OneVarFiller<T>& rhs) : val { rhs.val } {}; */
/* }; */

#endif
