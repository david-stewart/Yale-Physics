#include "RegionActivities.h"
#include "pi_const.h"
/* #include "fastjet/PseudoJet.hh" */
/* #include "fastjet/ClusterSequence.hh" */
/* #include "fastjet/ClusterSequenceArea.hh" */
/* #include "fastjet/Selector.hh" */
/* #include "fastjet/tools/Subtractor.hh" */
/* #include "fastjet/tools/JetMedianBackgroundEstimator.hh" */
/* using namespace fastjet; */


RegionActivities::RegionActivities ( std::vector<PseudoJet>& input, double in_phi ) :
    particles(input),
    phi_trigger{in_phi},
    n_regions{0},
    n_kept{0},
    has_calc{false}
{};

void RegionActivities::set_phi_trigger( double phi ) { 
    double old_phi{ phi_trigger };
    phi_trigger = phi;
    /* // if needed to, rotate the phi_bounds of the regions */
    if (phi_bounds.size() != 0) {
        double phi_rotate { phi_trigger - old_phi };
        for (auto& bounds : phi_bounds) {
            bounds.first  = phi_std(bounds.first + phi_rotate);
            bounds.second = phi_std(bounds.second + phi_rotate);
        };
    }
};

unsigned int RegionActivities::set_regions ( 
        std::vector< std::pair<double, double> > in_phi_bounds,
        std::vector< std::pair<double, double> > in_eta_bounds)
{
    phi_bounds = in_phi_bounds;
    eta_bounds = in_eta_bounds; 
    
    // rotate bounds according to phi_trigger
    if (phi_trigger != 0) set_phi_trigger( phi_trigger );

    if (particles.size() != 0) return calc();
    else return 0;
};

unsigned int RegionActivities::calc() {
    has_calc = true;
    // calculate the number of tracks in each region
    if (n_regions != 0) regions.clear();
    n_kept = 0;
    n_regions = phi_bounds.size() > eta_bounds.size() ? phi_bounds.size() : eta_bounds.size();

    for (unsigned int i{0}; i<n_regions; ++i) regions.push_back( { 0, 0, 0, 0 } );
    if  (n_regions == 0)                      regions.push_back( { 0, 0, 0, 0 } );
    // regions are full of the struct : has_track, nch, sumpt, maxpt, index (of particle with the last pt
    
    if (particles.size() == 0) return 0;

    bool use_eta{ eta_bounds.size() != 0 };
    bool use_phi{ phi_bounds.size() != 0 };
    
    if (!use_eta && !use_phi) { // there is a single regions for all tracks
        for (unsigned int i{0}; i<particles.size(); ++i) add_particle(regions[0], i);
    } else if (use_eta && use_phi) {
        for (unsigned int ip{0}; ip<particles.size(); ++ip) 
        {
            double phi { abs_delta_phi(particles[ip].phi_std(), phi_trigger) };
            double eta { particles[ip].pseudorapidity() };
            for (unsigned int ibin{0}; ibin<phi_bounds.size(); ++ibin)
            if (    phi >= phi_bounds[ibin].first
                 && phi <  phi_bounds[ibin].second
                 && eta >= eta_bounds[ibin].first 
                 && eta <  eta_bounds[ibin].second)
            { add_particle(regions[ibin], ip); }
        }
    } else if (use_eta) {
        for (unsigned int ip{0}; ip<particles.size(); ++ip) 
        {
            double eta { particles[ip].pseudorapidity() };
            for (unsigned int ibin{0}; ibin<phi_bounds.size(); ++ibin)
            if (    eta >= eta_bounds[ibin].first 
                 && eta <  eta_bounds[ibin].second )
            { add_particle(regions[ibin], ip); }
        }
    } else if (use_phi) {
        for (unsigned int ip{0}; ip<particles.size(); ++ip) 
        {
            double phi { abs_delta_phi(particles[ip].phi_std(), phi_trigger) };
            for (unsigned int ibin{0}; ibin<phi_bounds.size(); ++ibin)
            if (    phi >= phi_bounds[ibin].first 
                 && phi <  phi_bounds[ibin].second )
            { add_particle(regions[ibin], ip); }
        }
    }
    return n_kept;
};

void RegionActivities::add_particle( T_region& r, unsigned int i_particle) {
    ++n_kept;
    PseudoJet& p = particles[i_particle];
    double pt{ p.pt() };
    r.nch += 1;
    r.sumpt += pt;
    if (pt > r.maxpt) {
        r.maxpt = pt;
        r.index = i_particle;
    }
};
