/* #ifndef JetMaker__h */
/* #define JetMaker__h */

/* #include <vector> */

/* #include "fastjet/config.h" */
/* #include "fastjet/PseudoJet.hh" */
/* #include "fastjet/ClusterSequence.hh" */
/* #include "fastjet/ClusterSequenceArea.hh" */
/* #include "fastjet/Selector.hh" */
/* #include "fastjet/tools/Subtractor.hh" */
/* #include "fastjet/tools/JetMedianBackgroundEstimator.hh" */

/* using namespace fastjet; */

/* class JetMaker { */
/*     private: */
/*         double R; // jet radius parameter */
/*         Subtractor* subtractor; */
/*         JetMedianBackgroundEstimator* bge_rm2; */
/*     public: */
/*         /1* enum class CloneType *1/ */
/*         JetMaker (double R_); */
/*         void operator () (double px, double py, double pz, double E); */
/*         void clear_particles(); */
/*         void make_jets(); */
/*         // add a TMCParticles */
/*         std::vector<PseudoJet> jets; */
/*         std::vector<PseudoJet> particles; */
/*         double rho; */
/* }; */

/* #endif */
