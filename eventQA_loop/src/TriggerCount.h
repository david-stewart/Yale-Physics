#ifndef TRIGGERCOUNT__H
#define TRIGGERCOUNT__H

struct TriggerCount {
    // BHT1*VPDMB-30_nobsmd
    long int n500206;
    
    // BHT1*VPDMB-30
    long int n470202; long int n480202; long int n490202; long int n500202; long int n510202;

    // BHT2*BBCMB
    long int n470205; long int n480205; long int n490205; long int n500215;

    // VPDMB-5-ssd
    long int n500001;

    // VPDMB-30
    long int n500904;

    // VPDMB-5
    long int n510009;

    TriggerCount () :
        n500206{0}, n470202{0}, n480202{0}, n490202{0}, n500202{0}, n510202{0},
        n470205{0}, n480205{0}, n490205{0}, n500215{0}, n500001{0}, n500904{0},
        n510009{0}
    {};
};

#endif
