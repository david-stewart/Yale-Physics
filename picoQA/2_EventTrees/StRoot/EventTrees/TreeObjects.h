#ifndef TreeObjects__h
#define TreeObjects__h
#include <iostream>

class AntiktJet : public TObject {
	public:
    AntiktJet() {} ;
	virtual ~AntiktJet() {};
    double phi; 
    double eta; 
    double pt;  
    double area; 
    int    nch;
	ClassDef(AntiktJet,1);
};

class ChargedTrack : public TObject {
	public:
    ChargedTrack() {} ;
    /* void SetPhiEtaPt(double phi_, double eta_, double pt_) */ 

    /* { phi = phi_; eta = eta_; pt = pt_; } ; */
	virtual ~ChargedTrack() {};
    double phi; 
    double eta; 
    double pt; 
	ClassDef(ChargedTrack,1);
};

struct Event : public TObject {
	virtual ~Event() {} ;
    int          njets;       // will match the number of jets measured
    int          nch; // doesn't *have* to match sum of jet tracks;
    double       bbcAdcES;  // bbc East adc
    double       zdcX;
    int          runId;      
   
    double       refMult;
    double       vz;
    
    bool trig_500001;//
    bool trig_500006;//
    bool trig_500202;//
    bool trig_500206;//
    bool trig_500215;//
    bool trig_500904;//

    double       rho;   // background pT to area density
    double       phi_Et; // Trigger Tower (max Et tower)
    double       eta_Et; //
    double       Et; //
    int          towId_Et;

    ClassDef(Event,1);
};
#endif
