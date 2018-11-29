#include "RunStats.h"

EventStatsFiller_Base::EventStatsFiller_Base() : data{EventStats{}} 
{};

EventStatsFiller_Base::operator()() {
    double v {value()};
    ++data.nEntries;
    if (data.nEntries == 1) {
        data.min = v;
        data.max = v;
        data.sum = v;
        data.sum2 = v*v;
    } else {
        if (v < min) min = v;
        if (v > max) max = v;
        sum += v;
        sum2 += v*v;
    }
};


EventStats::EventStats(bool is_int_) :
    is_int{is_int}, min{0}, max{0}, mean{0}, nEntries{0}, sum{0}, sum2{0}
{};

EventStats& EventStats::operator+(const EventStats& rhs){
    if (min > rhs.min) min = rhs.min;
    if (max < rhs.max) max = rhs.max;
    lhs.sum += rhs.sum;
    lhs.sum2 += rhs.sum2;
    lhs.nEntries += rhs.nEntries;
    return lhs;
};
