#ifndef REGIONACTIVITIES__H
#define REGIONACTIVITIES__H

#include "fastjet/config.h"
#include "fastjet/PseudoJet.hh"
#include "pi_const.h"

using namespace fastjet;

class RegionActivities {
    public:
    struct T_region {
        /* bool has_track; // if there is a track in each region */
        unsigned int nch;    // number of charged tracks in each phi_eta region
        double sumpt; // sum of pt in each region in each region
        double maxpt; // max pt of a single track in each region
        unsigned int index;  // the location of the Psuuedojet with maximum pt in each region
    };
    RegionActivities ( std::vector<PseudoJet>& particles, double in_phi = 0);
    private:
    std::vector<PseudoJet>& particles;

    std::vector< std::pair<double, double> > phi_bounds;
    std::vector< std::pair<double, double> > eta_bounds;

    void add_particle(T_region&, unsigned int);


    public:
    // iniitialize with reference to the particles

    // set the trigger phi (defaults to zero)
    void set_phi_trigger (double phi_trigger);

    // set the regions (defaults to two empy lists); returns number of tracks
    // in the regions
    unsigned int set_regions ( std::vector< std::pair<double, double> > phi_bounds = std::vector<std::pair<double,double>> {},
                               std::vector< std::pair<double, double> > eta_bounds = std::vector<std::pair<double,double>> {});

    unsigned int calc (); // calculated values in each region returns number of tracks in each region

    // how many regions are present
    /* int size(); */

    std::vector< T_region > regions;

    /* PseuedoJet&   get_lead_track(int i);    // return the lead track from a region */
    /* PseuedoJet&   get_oa_lead_track(int i); // return overall lead track from a region */

    public: 
    double phi_trigger;
    unsigned int n_regions;
    unsigned int n_kept;
    bool has_calc;
};

#endif
