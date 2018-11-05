#ifndef TRIGGERCOUNT__H
#define TRIGGERCOUNT__H

struct TriggerCount {

    long int n500001;
    long int n500006;
    long int n500018;
    long int n500202;
    long int n500206;
    long int n500215;
    long int n500808;
    long int n500809;
    long int n500904;

    // VPDMB-5
    long int n510009;

    TriggerCount () :
    n500001{0}, n500006{0}, n500018{0}, n500202{0},
    n500206{0}, n500215{0}, n500808{0}, n500809{0},
    n500904{0}
    {};
};

#endif
