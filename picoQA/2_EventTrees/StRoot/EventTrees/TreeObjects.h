#ifndef TreeObjects__h
#define TreeObjects__h
#include <iostream>

#include <vector>

using namespace std;

class AntiktJet : public TObject {
	public:
    AntiktJet() {} ;
	virtual ~AntiktJet() {};
    double phi; 
    /* double dphi; // phi relative to the trigger tower (redundent with phi) */
    /* int    dphi_bin; // 0, 1, or 2 */
    double eta; //
    double pt;  //
    /* double rho; */
    /* double pt_corr; // jet pt - rho A */
    double area; //
    int    nch;
	ClassDef(JtJet,1);
};

class ChargedTrack : public TObject {
	public:
    ChargedTrack() {} ;
	virtual ~ChargedTrack() {};
    double phi; 
    double eta; //
    double pt;  //
	ClassDef(JtJet,1);
};

struct Event : public TObject {
	virtual ~Event() {} ;
    int          njets;       // will match the number of jets measured
    int          nch; // doesn't *have* to match sum of jet tracks;
    double       bbcAdcES;  // bbc East adc
    double       zdcX;
    int          runId;      
    /* int          eventId; */
    double       refMult;
    double       vz;
    /* double       rand; // random (0,1) */
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
    int          towIdEt;

    ClassDef(JtEvent,1);
};
#endif
