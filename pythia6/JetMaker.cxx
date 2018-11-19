using namespace fastjet;

void JetMaker::clear_particles() { particles.clear(); };

JetMaker::JetMaker(double R_) : R{R_}, rho{0} {
    /* JetMedianBackgroundEstimator* bge_rm2; */
    double ghost_maxrap {4.0};
    double jet_R_background{R};
    JetDefinition jet_def_bkgd(kt_algorithm, jet_R_background); 
    AreaDefinition area_def_bkgd(active_area_explicit_ghosts,
                                 GhostedAreaSpec (ghost_maxrap,1,0.01));
    Selector selector_rm2 = SelectorAbsEtaMax(1.0) * (!SelectorNHardest(2)); 
    bge_rm2 = new JetMedianBackgroundEstimator (selector_rm2, jet_def_bkgd, area_def_bkgd); 
    subtractor = new Subtractor( bge_rm2 ) ;
};

void JetMaker::operator()(double px, double py, double pz, double E){
    particles.push_back( PseudoJet{px, py, pz, E} );
};

void JetMaker::make_jets() {
    /* double ghost_maxrap{4}; */
    JetDefinition jet_def(antikt_algorithm, R);
    AreaDefinition area_def(active_area_explicit_ghosts,GhostedAreaSpec(4.0,1,0.01));
    ClusterSequenceArea cs(particles, jet_def, area_def);
    /* Selector pghost = SelectorIsPureGhost(); */
    jets = sorted_by_pt ( (!SelectorIsPureGhost())(cs.inclusive_jets()) );
    bge_rm2->set_particles(particles);
    rho = bge_rm2->rho();
}
