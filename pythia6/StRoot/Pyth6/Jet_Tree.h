#ifndef Jet_Tree__H
#define Jet_Tree__H

struct JtJet : public TObject {
	public:
    JtJet() {} ;
	virtual ~JtJet() {};
    double phi; 
    double eta; //
    double pt;  //
    double pt_corr; // jet pt - rho A
    double area; //
    int    nch;
	ClassDef(JtJet,1);
};

struct JtEvent : public TObject {
	virtual ~JtEvent() {} ;
    int     njets;   // will match the number of jets measured
    double  rho;   // rho of background

    int     n_c;     // charged particles
    int     n_n;     // nuetral neutral particles
    double  ptsum_c;
    double  ptsum_n;
    double  ptmax_c;
    double  ptmax_n;
    double  eta_c; // eta of leading charged particle
    double  eta_n; // eta of leading neutral particle
    double  phi_c; // phi of leading charged particle
    double  phi_n; // phi of leading charged particle

    ClassDef(JtEvent,1);
};
#endif
