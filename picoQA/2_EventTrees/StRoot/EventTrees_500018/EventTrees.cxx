//
// Includes code from (1) Joel Mazer from https://github.com/joelmazer/star-jetframework in July 2018
//                    (2) Tong Liu from ARCAS, also July 2018
//
#include "EventTrees.h"
#include <iostream>
#include "TowerList.h"

#include "fastjet/config.h"
#include "fastjet/PseudoJet.hh"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/Selector.hh"
#include "fastjet/tools/Subtractor.hh"
#include "fastjet/tools/JetMedianBackgroundEstimator.hh"

#define kNMaxJets   30
#define kNMaxTracks 75
#define kMaxRegions 20

#define one_pi 3.1415926536
#define two_pi 6.2831853072

using namespace fastjet;

/* struct T_Track { */
/*     double phi; */
/*     double eta; */
/*     double pt; */
/*     T_Track(double a,double b,double c) : phi{a}, eta{b}, pt{c} {}; */
/* }; */


class MyJetDefinitionTerms {
    public:
    /* JetMedianBackgroundEstimator* bge_rm0; */
    /* JetMedianBackgroundEstimator* bge_rm1; */
    Subtractor* subtractor;
    JetMedianBackgroundEstimator* bge_rm2;

    MyJetDefinitionTerms(float jet_R_background){ 
        float ghost_maxrap = 4.0;
        JetDefinition jet_def_bkgd(kt_algorithm, jet_R_background); // <--
        AreaDefinition area_def_bkgd(active_area_explicit_ghosts,GhostedAreaSpec (ghost_maxrap,1,0.01));

        Selector selector_rm2 = SelectorAbsEtaMax(1.0) * (!SelectorNHardest(2)); // <--
        bge_rm2 = new JetMedianBackgroundEstimator (selector_rm2, jet_def_bkgd, area_def_bkgd); // <--

        subtractor = new Subtractor( bge_rm2 ) ;
    };
};

ClassImp(EventTrees)
//-----------------------------------------------------------------------------
EventTrees::EventTrees(
        const char*     i_name,
        StPicoDstMaker* i_picoMaker,
        const char*     i_outName,
        const char*     i_bad_tower_file,
        const char*     i_bad_run_file,
        bool            i_debug
    )
  : StMaker(i_name), 
    /* max_ntracks_noTOF(0), */
    /* mTestConditions(false), */
    /* mAllTOF(false), */
    fPicoDstMaker   {i_picoMaker},
    fOutName        {i_outName},
    fbad_tower_file {i_bad_tower_file},
    fbad_run_file   {i_bad_run_file},
    fdebug          {i_debug},
    /* fmakePreCuts    {i_makePreCuts}, */
    fTT_threshold   {4.0},
    f_jetR          {0.4},
    b_jets          {"AntiktJet",    kNMaxJets},
    b_tracks        {"ChargedTrack", kNMaxTracks},
    /* b_activity      {"Activity", kMaxRegions}, */
    fEventsProcessed{0},
    f_hastriggers   {true},
    fvz_cut {30.}
{ 
    f_jet_etaMax = 1.0;// - f_jetR;
    ftriggerid = std::vector<int> { 500001, 500006, 50020, 500206, 500216, 500904 };
};

//----------------------------------------------------------------------------- 
EventTrees::~EventTrees()
{ };

//----------------------------------------------------------------------------- 
Int_t EventTrees::Init() {
    // a. Open the TFile
    // b. Open the log file
    // c. Set the BadTower and BadRun lists
    // d. Set the TTree

    // a. Open the TFile
    fout = new TFile(TString::Format("%s.root",fOutName.Data()).Data(),"RECREATE") ;

    // b. Open the log file
    if (fdebug) dlog = fopen(TString::Format("%s.debug",fOutName.Data()).Data(),"w");
    flog = fopen(TString::Format("%s.log",fOutName.Data()).Data(),"w");
    fprintf(flog,"Initializing log\n");


    // c. Set the BadTower and BadRun lists
    ifstream file;
    file.open(fbad_tower_file);
    if (!file.is_open()) {
        fprintf(flog,"Warning: the bad tower file %s could not be opened.\n"
                     "  No bad tower list obtained.\n",
                fbad_tower_file);
        fbad_tower_list = vector<int>{};
    } else {
        string line;
        while (getline(file,line)) {
            line.append(" ");
            stringstream words(line);
            TString word;
            while (words >> word) {
                if (word.BeginsWith("//") || word.BeginsWith("#")) break;
                fbad_tower_list.push_back(word.Atoi());
            }
        }
        std::sort(fbad_tower_list.begin(), fbad_tower_list.end());
        fprintf(flog,"Read in bad tower list from %s\n",fbad_tower_file);
        fprintf(flog, " Bad towers (number = %i):\n", fbad_tower_list.size());
        for (auto i : fbad_tower_list) fprintf(flog,"  %i\n",i);
    }
    file.close();

    file.open(fbad_run_file);
    if (!file.is_open()) {
        fprintf(flog,"Warning: the bad run file %s could not be opened.\n"
                     "  No bad run list obtained.\n",
                fbad_run_file);
        fbad_run_list = vector<int>{};
    } else {
        string line;
        while (getline(file,line)) {
            line.append(" ");
            stringstream words(line);
            TString word;
            while (words >> word) {
                if (word.BeginsWith("//") || word.BeginsWith("#")) break;
                fbad_run_list.push_back(word.Atoi());
            }
        }
        std::sort(fbad_run_list.begin(), fbad_run_list.end());
        fprintf(flog,"Read in bad run list from %s\n",fbad_run_file);
        fprintf(flog, " Bad runs (number = %i):\n", fbad_run_list.size());
        for (auto i : fbad_run_list) fprintf(flog,"  %i\n",i);
        /* int bad_run; */
        /* while (file >> bad_run) fbad_run_list.push_back(bad_run); */
        /* std::sort(fbad_run_list.begin(), fbad_run_list.end()); */
        /* fprintf(flog,"Read in bad run list from %s\n",fbad_run_file); */
    }
    file.close();

    // TODO:: efficiency track cut codes will have to be fixed, if this is to be used
    /* if (ftriggerid < 0) { */
    /*     fprintf(flog,"Turning on efficiency track cuts.\n"); */
    /*     f_eff_cut_tracks = true; */
    /*     ftriggerid = -1*ftriggerid; */
    /* } else { */
    /*     f_eff_cut_tracks = false; */
    /* } */
    fprintf(flog,"Using vertex cut: %f\n", fvz_cut);
    fprintf(flog,"Using trigger ids:\n");

    if (!f_hastriggers) fprintf(flog, " * ! * ! *  fatal error: no trigger id's set \n");

    for (auto x : ftriggerid) fprintf(flog, "   %i\n", x);
    /* fprintf(flog, fisAu ? " Using Au + Au settings\n" : " Using p + Au settings\n"); */

    // d. Set the TTree
    ftree = new TTree("tree","Jet Tree Recoiling from Highest Et Tower");
    ftree->Branch("event",        &fevent);
    ftree->Branch("jets",         &b_jets);
    ftree->Branch("ch_tracks",    &b_tracks);
    /* ftree->Branch("activity",     &b_activity); */

    /* if (fmakePreCuts) { */
    /*     fpc_tree = new TTree("pc_tree","Some conditions after event cuts but priot to Et Tower > Et Min cut"); */
    /*     fpc_tree->Branch("pre_cut_data",  &fpc); */
    /* } */

    // e. Initialize fbge, frand, and histograms
    f_bge = new MyJetDefinitionTerms(0.4);
    /* frand = new TRandom3(0); */

    return kStOK;
}

//----------------------------------------------------------------------------- 
Int_t EventTrees::Finish() {
    fout->Write();
    fout->Close();
    fprintf(flog," Finished running.\n Read %lli jet events.\n\n", fEventsProcessed);
    fclose(flog);
    if (fdebug) fclose(dlog);
    return kStOK;
}
    
//----------------------------------------------------------------------------- 
void EventTrees::Clear(Option_t *opt) { }

//----------------------------------------------------------------------------- 
Int_t EventTrees::Make() {
    if (!f_hastriggers) {std::cout << "fatal: Skipping run, no triggers have been selected" 
                        << std::endl;
                        return kStErr;
    }
    if (fdebug) fprintf(dlog,"--- new event\n");
    b_jets.Clear();
    b_tracks.Clear();
    /* b_activity.Clear(); */
    if(!fPicoDstMaker) {
        LOG_WARN << " No PicoDstMaker! Skip! " << endm;

        return kStWarn;
    }

    fPicoDst = fPicoDstMaker->picoDst();
    if(!fPicoDst) {
        LOG_WARN << " No PicoDst! Skip! " << endm;
        return kStWarn;
    }
    /* fHgram_ev_cuts->Fill(0); */
    StPicoEvent* mevent = fPicoDst->event();

    if (fdebug) fprintf(dlog," %-20s %-10i\n", "runID", mevent->runId());
    if (fdebug) fprintf(dlog," %-20s %-10i\n", "eventID", mevent->eventId());
    /* if (fdebug) cout << " runID " << mevent->runId() << endl; */
    fevent.runId = mevent->runId();
    if (std::binary_search(fbad_run_list.begin(), fbad_run_list.end(), fevent.runId)) 
        return kStOk; 
    /* fHgram_ev_cuts->Fill(1); */
    if (fdebug) fprintf(dlog," %-20s\n", "*passed runID");

    if (fdebug) for (auto t : mevent->triggerIds()) 
        fprintf(dlog," trigger: > > %-20i\n",t);
    bool has_trigger{false};
    for (auto x : ftriggerid) {
        if (mevent->isTrigger(x)) {
            has_trigger = true;
            break;
        }
    }
    if (!has_trigger) return kStOK;


    float rank = mevent->ranking();
    int sig = rank > 0 ? +1 : -1;
    /* float ln = TMath::Log(TMath::Abs(rank)); */
    /* fHgram_ln_ranking->Fill(sig*ln); */
    if (fdebug) fprintf(dlog," %-20s %-10.2f\n", "ranking", rank);
    if (sig < 0) return kStOK;
    /* fHgram_ev_cuts->Fill(3); */
    fevent.vz = mevent->primaryVertex().z();

    if (TMath::Abs(fevent.vz) > fvz_cut) return kStOk;
    if (TMath::Abs(fevent.vz - mevent->vzVpd())>3.0) return kStOk;


    fevent.trig_500001 = mevent->isTrigger(500001);//
    fevent.trig_500006 = mevent->isTrigger(500006);//
    fevent.trig_500018 = mevent->isTrigger(500018);//
    fevent.trig_500202 = mevent->isTrigger(500202);//
    fevent.trig_500206 = mevent->isTrigger(500206);//
    fevent.trig_500215 = mevent->isTrigger(500215);//
    fevent.trig_500904 = mevent->isTrigger(500904);//
    fevent.zdcX    = mevent->ZDCx();

    fevent.refMult = mevent->refMult();
    fevent.nch = 0;

    vector<PseudoJet> particles;

    for (unsigned int i = 0; i < fPicoDst->numberOfTracks(); ++i){
        StPicoTrack* track = static_cast<StPicoTrack*>(fPicoDst->track(i));
        if (!track->isPrimary()) continue;

        // thanks to joel mazer
        StThreeVectorF Ptrack = track->pMom();
        float pt  = Ptrack.perp();
        if (pt > 30)   return kStOK; // cut out this event
        if (pt < 0.2)  continue;

        float phi = Ptrack.phi();
        float eta = Ptrack.pseudoRapidity();

        // thanks to joel mazer
        float dca = (track->dcaPoint() - mevent->primaryVertex()).mag();
        if (dca > 3.0)  continue;

        if (TMath::Abs(eta)  >= 1.0) continue;

        float nhit_ratio = ((float)track->nHitsFit()) / (float)track->nHitsMax();
        if (nhit_ratio <= 0.52) continue;


        particles.push_back (PseudoJet());
        unsigned int j = particles.size() - 1;
        particles[j].reset_PtYPhiM(pt, eta, phi);
        particles[j].set_user_index(i);

    }
    if (fdebug) fprintf(dlog," %-20s\n","  -> read tracks\n");

    //Check for there not being any +30 jets
    TT_list towlist(fTT_threshold);
    for (unsigned int i=0 ; i < fPicoDst->numberOfEmcTriggers(); ++i){
        StPicoEmcTrigger* emcTrig = fPicoDst->emcTrigger(i);
        if (! (emcTrig->isHT1() || emcTrig->isHT2()) ) continue;
        int   trigId  = emcTrig->id();
        if (trigId < 1) {
            fprintf(flog,"Warning! in ev(%i) emcTriggerId(%i) (should be > 1)\n",
                    trigId, mevent->eventId());
            continue;
        }
        if (std::binary_search(fbad_tower_list.begin(), 
            fbad_tower_list.end(), trigId)) continue;
        StPicoBTowHit* bTowHit = fPicoDst->btowHit(trigId-1); 
        StEmcPosition *mPosition = new StEmcPosition();
        StThreeVectorF towLoc = mPosition->getPosFromVertex( 
                mevent->primaryVertex(), trigId);
        float towEt    = bTowHit->energy() / ((double)TMath::CosH(towLoc.pseudoRapidity()));
        if (towEt > 30) return kStOk;
        if (towEt < 0.2) {
            // given triggers, this shouldn't happen  
            fprintf(flog,"Warning: in ev(%i) tower with Et(%f) found.\n",
                    mevent->eventId(), towEt);
            continue;
        }
        if (fdebug) cout << " towlist et, phi, eta, id " << towEt<<" "<<towLoc.phi()<<" "<<towLoc.pseudoRapidity()<<" "<<trigId<<endl;
        towlist.add(towEt, towLoc.phi(), towLoc.pseudoRapidity(), trigId);  
    }
    if (fdebug) fprintf(dlog," %-20s\n","  -> end read tower list\n");
    /* fHgram_ev_cuts->Fill(8); */

    // fill the signal histograms (for getting the percentile on the minimum bias data sets)
    fevent.bbcAdcES = mevent->bbcAdcEast(0);
    for (int i = 1; i < 16; ++i) fevent.bbcAdcES += mevent->bbcAdcEast(i);

    /* cout << "new event " << endl; */
    /* for (auto p : particles) cout << " this pt " << p.pt() << endl; */


    particles = sorted_by_pt( particles );
    /* cout << "----now sorted----" << endl; */
    /* for (auto p : particles) cout << " this pt " << p.pt() << endl; */

    fevent.nch = particles.size();
    for (int i{0};i<fevent.nch;++i){
        ChargedTrack* b_track = (ChargedTrack*) b_tracks.ConstructedAt(i);
        b_track->phi = particles[i].phi();
        b_track->eta = particles[i].eta();
        b_track->pt  = particles[i].pt() ;
    }


    /* ++fevent.nch; */

    /* RegionActivities activity{particles}; */
    fevent.Et       = towlist.maxEt;
    fevent.phi_Et   = towlist.etaEt();
    fevent.eta_Et   = towlist.etaEt();
    fevent.towId_Et = towlist.TT_towID();

    //make and fill jets
    AreaDefinition area_def(active_area_explicit_ghosts,GhostedAreaSpec(4.0,1,0.01));
    JetDefinition jet_def(antikt_algorithm, f_jetR);
    ClusterSequenceArea cs(particles, jet_def, area_def);
    vector<PseudoJet> jets_all = cs.inclusive_jets();
    vector<PseudoJet> jets = sorted_by_pt( jets_all );
    f_bge->bge_rm2->set_particles(particles); // set background by the area of interest.
                                              // However, record all jets
                                              //
    fevent.rho = f_bge->bge_rm2->rho();
    fevent.njets = 0;

    /* unsigned int njets = 0; */
    for (unsigned int i_jet = 0; i_jet < jets.size(); ++i_jet){
        PseudoJet& jet = jets[i_jet];
        if ( jet.is_pure_ghost() ) { continue; }
        if ( jet.eta() > f_jet_etaMax || jet.eta() < -f_jet_etaMax) continue;

        AntiktJet* b_jet = (AntiktJet*) b_jets.ConstructedAt(fevent.njets); 
        ++fevent.njets;

        b_jet->phi = jet.phi_std();
        b_jet->eta = jet.eta();
        b_jet->pt  = jet.pt();
        b_jet->area = jet.area();
            
        vector<PseudoJet> constituents = sorted_by_pt(jet.constituents());
        unsigned int nch = 0;
        b_jet->nch = nch;
    }
    
    //fill the jet branches
    ftree->Fill();
    fEventsProcessed++ ;
	return kStOK;
}

