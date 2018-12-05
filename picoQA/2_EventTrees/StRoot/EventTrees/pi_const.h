#ifndef PICONST__H
#define PICONST__H

#define one_pi 3.1415926536
#define two_pi 6.2831853072

#include "TMath.h"

inline double abs_delta_phi(double a, double b) {
    double d_phi{ a - b };
    while (d_phi < -one_pi) d_phi += two_pi;
    while (d_phi >  one_pi) d_phi -= two_pi;
    return TMath::Abs(d_phi);
};

inline double delta_phi(double a, double b) {
    double d_phi{ b - a };
    while (d_phi < -one_pi) d_phi += two_pi;
    while (d_phi >  one_pi) d_phi -= two_pi;
    return d_phi;
};


inline double phi_std(double phi) {
    while (phi < -one_pi) phi += two_pi;
    while (phi >  one_pi) phi -= two_pi;
    return phi;
};


#endif
