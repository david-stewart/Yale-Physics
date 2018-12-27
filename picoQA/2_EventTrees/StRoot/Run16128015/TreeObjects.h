#ifndef TreeObjects__h
#define TreeObjects__h
#include <iostream>

struct Event : public TObject {
	virtual ~Event() {} ;
    int          runId;      
    int          eventId;

    int          i_file_name;

    int          nch; // doesn't *have* to match sum of jet tracks;
    double       bbcAdcES;  // bbc East adc
    double       zdcX;
    double       ranking;
    double       refMult;
    double       vz;
    double       vzVpd;

    double       vx;
    double       vy;

    bool         track_over_30GeV;

    int          n_triggers; // make an array of triggers
    TArrayI      triggers;
    TArrayF      ch_pt;
    TArrayF      ch_phi;
    TArrayF      ch_eta;
    TArrayF      hit_ratio;

    
    /* bool trig_500001;// */
    /* bool trig_500006;// */
    /* bool trig_500018;// */
    /* bool trig_500202;// */
    /* bool trig_500206;// */
    /* bool trig_500215;// */
    /* bool trig_500904;// */

    ClassDef(Event,1);
};
#endif
