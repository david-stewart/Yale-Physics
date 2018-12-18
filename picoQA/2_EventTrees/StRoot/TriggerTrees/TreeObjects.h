#ifndef TreeObjects__h
#define TreeObjects__h
#include <iostream>

struct Event : public TObject {
	virtual ~Event() {} ;
    int          runId;      
    int          eventId;
    int          index_file;
    int          nch; // doesn't *have* to match sum of jet tracks;
    double       bbcAdcES;  // bbc East adc
    double       zdcX;
    double       ranking;
    int          i_file_name;
   
    double       refMult;
    double       vz;
    
    bool trig_500001;//
    bool trig_500006;//
    bool trig_500018;//
    bool trig_500202;//
    bool trig_500206;//
    bool trig_500215;//
    bool trig_500904;//

    ClassDef(Event,1);
};
#endif
