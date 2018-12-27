//   New objective: kj
//
// Includes code from (1) Joel Mazer from https://github.com/joelmazer/star-jetframework in July 2018
//                    (2) Tong Liu from ARCAS, also July 2018
//
#include "Run16128015.h"
#include <iostream>
#include "TowerList.h"

#include "fastjet/config.h"
#include "fastjet/PseudoJet.hh"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/Selector.hh"
#include "fastjet/tools/Subtractor.hh"
#include "fastjet/tools/JetMedianBackgroundEstimator.hh"
#include "TChain.h"

#define kNMaxJets   40
#define kNMaxTracks 100
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
    Selector ptmin;

    MyJetDefinitionTerms(float jet_R_background){ 
        float ghost_maxrap = 4.0;
        JetDefinition jet_def_bkgd(kt_algorithm, jet_R_background); // <--
        AreaDefinition area_def_bkgd(active_area_explicit_ghosts,GhostedAreaSpec (ghost_maxrap,1,0.01));

        Selector selector_rm2 = SelectorAbsEtaMax(1.0) * (!SelectorNHardest(2)); // <--
        bge_rm2 = new JetMedianBackgroundEstimator (selector_rm2, jet_def_bkgd, area_def_bkgd); // <--

        subtractor = new Subtractor( bge_rm2 ) ;
        ptmin = SelectorPtMin(0.2);
    };
};

struct MyInfo : public PseudoJet::UserInfoBase {
    MyInfo(float hratio_in) : _hratio{hratio_in} {};
    float hratio() const { return _hratio; };
    float _hratio;
};

ClassImp(Run16128015)
//-----------------------------------------------------------------------------
Run16128015::Run16128015(
        const char*     i_name,
        StPicoDstMaker* i_picoMaker,
        const char*     i_outName,
        const char*     i_bad_run_file,
        bool            i_debug
    )
  : StMaker(i_name), 
    /* max_ntracks_noTOF(0), */
    /* mTestConditions(false), */
    /* mAllTOF(false), */
    fPicoDstMaker   {i_picoMaker},
    fOutName        {i_outName},
    fbad_run_file   {i_bad_run_file},
    fdebug          {i_debug},
    /* fmakePreCuts    {i_makePreCuts}, */
    /* b_activity      {"Activity", kMaxRegions}, */
    fEventsProcessed{0},
    f_hastriggers   {true},
    fvz_cut {30.}
{ 
    ftriggerid = std::vector<int> { 500001, 500006, 500018, 50020, 500206, 500216, 500904 };
};

//----------------------------------------------------------------------------- 
Run16128015::~Run16128015()
{ };

//----------------------------------------------------------------------------- 
Int_t Run16128015::Init() {
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

    fprintf(flog,"Using vertex cut: %f\n", fvz_cut);
    fprintf(flog,"Using trigger ids:\n");

    if (!f_hastriggers) fprintf(flog, " * ! * ! *  fatal error: no trigger id's set \n");

    for (auto x : ftriggerid) fprintf(flog, "   %i\n", x);
    /* fprintf(flog, fisAu ? " Using Au + Au settings\n" : " Using p + Au settings\n"); */

    // d. Set the TTree
    ftree = new TTree("trigger_tree","trigger events");
    ftree->Branch("event",        &fevent);
    /* ftree->Branch("activity",     &b_activity); */

    /* if (fmakePreCuts) { */
    /*     fpc_tree = new TTree("pc_tree","Some conditions after event cuts but priot to Et Tower > Et Min cut"); */
    /*     fpc_tree->Branch("pre_cut_data",  &fpc); */
    /* } */

    // e. Initialize fbge, frand, and histograms
    f_bge = new MyJetDefinitionTerms(0.4);
    /* frand = new TRandom3(0); */
    /* ftree->Branch("jets", &b_triggers); */
    return kStOK;
}

//----------------------------------------------------------------------------- 
Int_t Run16128015::Finish() {
    //write the file name tree
    fout->cd();
    TTree* file_names = new TTree("file_names", "names of the files to which the events are correlated");
    string f_name;
    int    i_name;
    file_names->Branch("name", &f_name);
    file_names->Branch("index", &i_name);

    for (auto entry : m_file_names){
        f_name = entry.first;
        i_name = entry.second;
        file_names->Fill();
        cout << " entry: " << f_name << "    index: " << i_name << endl;
    }

    fout->Write();
    fout->Close();

    // write the tree of input file names
    fprintf(flog," Finished running.\n Read %lli jet events.\n\n", fEventsProcessed);
    fclose(flog);
    if (fdebug) fclose(dlog);
    return kStOK;
}
    
//----------------------------------------------------------------------------- 
void Run16128015::Clear(Option_t *opt) { }

//----------------------------------------------------------------------------- 
Int_t Run16128015::Make() {
    if (!f_hastriggers) {std::cout << "fatal: Skipping run, no triggers have been selected" 
                        << std::endl;
                        return kStErr;
    }
    if (fdebug) fprintf(dlog,"--- new event\n");
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
    if ((fevent.runId != 16128015) || !(mevent->isTrigger(500206))) return kStOk;
    /* if (std::binary_search(fbad_run_list.begin(), fbad_run_list.end(), fevent.runId)) */ 
        /* return kStOk; */ 
    /* fHgram_ev_cuts->Fill(1); */
    /* if (fdebug) fprintf(dlog," %-20s\n", "*passed runID"); */

    fevent.ranking = mevent->ranking();
    /* int sig = fevent.ranking > 0 ? +1 : -1; */
    /* double ln = TMath::Log(TMath::Abs(rank)); */
    /* fHgram_ln_ranking->Fill(sig*ln); */
    /* if (fdebug) fprintf(dlog," %-20s %-10.2f\n", "ranking", fevent.ranking); */
    /* if (sig < 0) return kStOK; */
    /* fHgram_ev_cuts->Fill(3); */
    fevent.vx = mevent->primaryVertex().x();
    fevent.vy = mevent->primaryVertex().y();
    fevent.vz = mevent->primaryVertex().z();
    fevent.vzVpd = mevent->vzVpd();
    /* cout << " vpdvz " << mevent->vzVpd() << endl; */

    std::vector<unsigned int> triggers = mevent->triggerIds();
    fevent.n_triggers = triggers.size();
    fevent.triggers.Set(fevent.n_triggers);
    for (int i{0}; i<fevent.n_triggers; ++i) fevent.triggers.AddAt(triggers[i], i);

    /* if (triggers.size() > 1) { */
    /*     int i = 0; */
    /*     cout << "----------------"<<endl; */
    /*     cout << "n_triggers " << triggers.size() << endl; */
    /*     for (auto j : triggers) cout << "  " << i++ << ":  " << j << endl; */
    /* } */

    fevent.zdcX    = mevent->ZDCx();
    fevent.refMult = mevent->refMult();
    fevent.nch = 0;

    vector<PseudoJet> particles;

    /* int count_nch{0}; */
    bool track_over_30GeV = false;
    for (unsigned int i = 0; i < fPicoDst->numberOfTracks(); ++i){
        StPicoTrack* track = static_cast<StPicoTrack*>(fPicoDst->track(i));
        if (!track->isPrimary()) continue;

        // thanks to joel mazer
        StThreeVectorF Ptrack = track->pMom();
        float pt  = Ptrack.perp();
        fevent.track_over_30GeV = ( (pt > 30) ? true : false );
        if (pt > 30)   track_over_30GeV = true;
        if (pt < 0.2)  continue;

        float eta = Ptrack.pseudoRapidity();
        float phi = Ptrack.phi();
        if (abs(phi) > 10) continue;

        // thanks to joel mazer
        float dca = (track->dcaPoint() - mevent->primaryVertex()).mag();
        if (dca > 3.0)  continue;

        if (TMath::Abs(Ptrack.pseudoRapidity())  >= 1.0) continue;

        float nhit_ratio = ((float)track->nHitsFit()) / (float)track->nHitsMax();
        if (nhit_ratio <= 0.52) continue;

        particles.push_back (PseudoJet());
        unsigned int j = particles.size() - 1;
        particles[j].reset_PtYPhiM(pt, eta, phi);
        particles[j].set_user_index(i);
        particles[j].set_user_info(new MyInfo(nhit_ratio));

        /* ++count_nch; */
    }

    particles = sorted_by_pt(particles);
    fevent.ch_pt.Set(particles.size());
    fevent.ch_eta.Set(particles.size());
    fevent.ch_phi.Set(particles.size());
    fevent.hit_ratio.Set(particles.size());

    for (unsigned int i{0}; i<particles.size(); ++i){
        fevent.ch_pt.AddAt(particles[i].pt(),i);
        fevent.ch_phi.AddAt(particles[i].phi(),i);
        fevent.ch_eta.AddAt(particles[i].eta(),i);
        fevent.hit_ratio.AddAt(particles[i].user_info<MyInfo>().hratio(),i);

        printf("i:%i pt:%f phi:%f eta:%f hratio:%f\n",
                i, particles[i].pt(), particles[i].phi(), particles[i].eta(),
                particles[i].user_info<MyInfo>().hratio()
        );
    }
    //Check for there not being any +30 jets
    fevent.track_over_30GeV = track_over_30GeV;
    fevent.nch = particles.size();
    fevent.bbcAdcES = mevent->bbcAdcEast(0);
    for (int i = 1; i < 16; ++i) fevent.bbcAdcES += mevent->bbcAdcEast(i);
    //
    // get the filename into the map
    string if_name {((TChain*)fPicoDstMaker->chain())->GetFile()->GetName()};
    /* cout << "name: " << if_name << endl; */
    if (m_file_names.count(if_name)==0) m_file_names[if_name] = m_file_names.size();
    fevent.i_file_name = m_file_names[if_name];
    /* cout << "m_file_names[if_name]: " << m_file_names[if_name] << endl; */

    //fill the jet branches
    ftree->Fill();
    fEventsProcessed++ ;
	return kStOK;
}

