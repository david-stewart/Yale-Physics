#include "InputBase.h"
#include "InputSapling.h"
#include "TFile.h"
#include "TH1F.h"

#include "TProfile.h"
#include "TMath.h"
#include "TH1.h"
#include "TH2.h"
#include <algorithm>

using namespace std;

//------------------------------------------------------------------
// get basic zdcX and bbc hisgorams
//------------------------------------------------------------------

# define TWO_PI 6.2831853072
# define ONE_PI 3.1415926536
# define HALF_PI  1.5707963268
# define LEFT_PI -0.7853981634
# define RIGHT_PI 5.4977871438

bool is_same_side (double first, double second) {
    double diff { abs(first - second)/TMath::Pi() };
    while (diff > 1) diff = abs(diff - 2);
    if (diff < 0.5) return true;
    else return false;
};

double delta_phi(double Et, double jet) {
    double diff { (jet - Et)/TMath::Pi() };
    while (diff < -0.25) diff += 2;
    while (diff > 1.75) diff -= 2;
    return diff;
};
// TODO total jet spectra
// TODO TH2D jet spectra w.r.t. trigger
void InputSapling::TriggerCombinations() {
    
    // read in the "good run list" and run only over those
    if (chain == 0) return;
    bool runAll{nEvents == -1};
    Long64_t jentry{0};

	//only read in godo runs
	bool check_good{good_runs.size()!=0};

    TH1D* which_triggers = new TH1D("which_triggers",
            "binary;500: 001-1, 006-2, 018-4, 202-8, 206-16, 215-32, 904-64;N_{trigs}",
            128,-0.5,127.5);
    TH1D* yesno_500001 = new TH1D("yesno_500001", "if 500001;0:no,1:yes",2,-0.5,1.5);

    if (runAll) {
        f_log << " # starting to read all events" << endl;
    } else {
        f_log << " # starting to read " << nEvents << " all events" << endl;
    }
	map<int, int> m_500206;

    Long64_t nbytes = 0, nb = 0;
    while (runAll || jentry < nEvents){
        nb = chain->GetEntry(jentry);   nbytes += nb;
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        if (jentry % 500000 == 0) {
            f_log << " # finished " << jentry << " events" << endl;
        }

        if (check_good && !binary_search(good_runs.begin(), good_runs.end(), runId)) continue;

		if (trig_500206) {
			if (m_500206.count(runId)) ++m_500206[runId];
			else m_500206[runId] = 1;
		}

        /* cout << " this is the name: " << chain->GetFile()->GetName() << endl; */
        int nfill{0};
        if (trig_500001) nfill += 1;
        if (trig_500006) nfill += 2;
        if (trig_500018) nfill += 4;
        if (trig_500202) nfill += 8;
        if (trig_500206) nfill += 16;
        if (trig_500215) nfill += 32;
        if (trig_500904) nfill += 64;
        which_triggers->Fill(nfill);

        if (trig_500001) {
            yesno_500001->Fill(1);
        } else {
            yesno_500001->Fill(0);
        }
        ++jentry;
    }
	f_log  << "500206 entries per run: " << endl;
	f_log  << "  --run---  num"<<endl;
	for (auto e : m_500206) f_log << "  " << e.first << "  " << e.second << endl;
	

};

void InputSapling::ExploratoryLoop() {
    if (chain == 0) return;
    bool runAll{nEvents == -1};
    Long64_t jentry{0};

    if (runAll) {
        f_log << " # starting to read all events" << endl;
    } else {
        f_log << " # starting to read " << nEvents << " all events" << endl;
    }

    vector<pair<bool*, pair<string,string>>> sets { 
        {&trig_500001, {"500001", "VPDMB-5-ssd"}},
        {&trig_500006, {"500006", "VPDMB-5-nossd"}},
        {&trig_500018, {"500018", "BBCMB"}},
        {&trig_500202, {"500202", "BHT1*VPDMB-30"}},
        {&trig_500206, {"500206", "BHT1*VPDMB-30_nobsmd"}},
        {&trig_500215, {"500215", "BHT2*BBCMB"}},
        {&trig_500904, {"500904", "VPDMB-30"}},
    };

    vector<TH1D*> vh_zdcX;
    vector<TH1D*> vh_bbcES;
    vector<TH1D*> vh_vz;

    vector<TProfile*> vp_bbc_zdcX;
    vector<TProfile*> vp_bbc_vz;
    vector<TProfile*> vp_zdcX_vz;

    vector<pair<TProfile*, TProfile*>> vp_maxTr_bbc; //first for same side, second for opposite side
    vector<TProfile*> vp_maxEt_bbc;
    vector<pair<TProfile*, TProfile*>> vp_maxJet_bbc;

    vector<pair<TH1D*, TH1D*>> vh_maxTr; // first for same side, second for opposite side
    vector<TH1D*> vh_maxEt;
    vector<pair<TH1D*, TH1D*>> vh_maxJet;

    vector<TH1D*> vh_jet_pt;
    vector<TH2D*> vh_jet_pt_dphi;

    const auto& fmt = TString::Format;

    int    nb_zdcX {200};
    double lo_zdcX {0};
    double hi_zdcX {50E3};

    int    nb_bbcES {200};
    double lo_bbcES {0};
    double hi_bbcES {70E3};

    int    nb_Vz {124};
    double lo_Vz {-31};
    double hi_Vz { 31};

    int    nb_Trpt {64};
    double lo_Trpt {-1};
    double hi_Trpt { 31};

    int    nb_Et {64};
    double lo_Et {-1};
    double hi_Et { 31};

    int    nb_jetPt {120};
    double lo_jetPt {0};
    double hi_jetPt {60};

    for (auto x : sets) {
        const char* num {x.second.first.c_str()};
        const char* name {x.second.second.c_str()};
        vh_zdcX.push_back(new TH1D( fmt("h_zdcX_%s",num).Data(), fmt("%s;zdcX;N_events",name).Data(), nb_zdcX, lo_zdcX, hi_zdcX));
        vh_bbcES.push_back(new TH1D( fmt("h_bbcES_%s",num).Data(), fmt("%s;bbcES;N_events",name).Data(), nb_bbcES, lo_bbcES, hi_bbcES));
        vh_vz.push_back(new TH1D( fmt("h_vz_%s",num).Data(), fmt("%s;vz;N_events",name).Data(), nb_Vz, lo_Vz, hi_Vz));

        vp_bbc_zdcX.push_back(new TProfile(fmt("p_bbc_zdcX_%s",num).Data(), fmt("%s;zdcX;BBC Adc ES",name).Data(), nb_zdcX, lo_zdcX, hi_zdcX));
        vp_bbc_vz.push_back(new TProfile(fmt("p_bbc_vz_%s",num).Data(), fmt("%s;V_{z};BBC Adc ES",name).Data(), nb_Vz, lo_Vz, hi_Vz));
        vp_zdcX_vz.push_back(new TProfile(fmt("p_zdcX_vz_%s",num).Data(), fmt("%s;V_{z};zdcX",name).Data(),     nb_Vz, lo_Vz, hi_Vz));

        vp_maxTr_bbc.push_back( {
                new TProfile(fmt("p_maxTr_bbc_%s_S",num).Data(), 
                             fmt("%s S:Same Side;BBC Adc ES;max Track p_{T}",name).Data(),   nb_bbcES, lo_bbcES, hi_bbcES),
                new TProfile(fmt("p_maxTr_bbc_%s_R",num).Data(), 
                             fmt("%s R:Recoil Side;BBC Adc ES;max Track p_{T}",name).Data(), nb_bbcES, lo_bbcES, hi_bbcES)
                });

        vp_maxEt_bbc.push_back( 
                new TProfile(fmt("p_maxEt_bbc_%s",num).Data(), 
                             fmt("%s;BBC Adc ES;max Et hit",name).Data(), nb_bbcES, lo_bbcES, hi_bbcES));

        vp_maxJet_bbc.push_back( {
                new TProfile(fmt("p_maxJet_bbc_%s_S",num).Data(), 
                             fmt("%s S:Same Side;BBC Adc ES;max Jet p_{T}",name).Data(), nb_bbcES, lo_bbcES, hi_bbcES),
                new TProfile(fmt("p_maxJet_bbc_%s_R",num).Data(), 
                             fmt("%s R:Recoil Side;BBC Adc ES;max Jet p_{T}",name).Data(), nb_bbcES, lo_bbcES, hi_bbcES)
        });

        vh_maxTr.push_back( {
                new TH1D(fmt("h_maxTr_%s_S",num).Data(), 
                        fmt("%s S:Same Side;max Track p_{T};N_{events}",name).Data(), nb_Trpt, lo_Trpt, hi_Trpt),
                new TH1D(fmt("h_maxTr_%s_R",num).Data(), 
                         fmt("%s R:Recoil Side;max Track p_{T};N_{events}",name).Data(), nb_Trpt, lo_Trpt, hi_Trpt)
        });

        vh_maxEt.push_back( 
                new TH1D(fmt("h_maxEt_%s",num).Data(), 
                         fmt("%s;max Et hit;N_{events}",name).Data(), nb_Et, lo_Et, hi_Et)
        );

        vh_maxJet.push_back( {
                new TH1D(fmt("h_maxJet_%s_S",num).Data(), 
                         fmt("%s S:Same Side;max Jet p_{T};N_{events}",name).Data(), nb_jetPt, lo_jetPt, hi_jetPt), 
                new TH1D(fmt("h_maxJet_%s_R",num).Data(), 
                         fmt("%s R:Recoil Side;max Jet p_{T};N_{events}",name).Data(), nb_jetPt, lo_jetPt, hi_jetPt)
        });

        vh_jet_pt.push_back( 
            new TH1D(fmt("h_jet_pt_%s",num).Data(), 
                 fmt("%s;Jet p_{T};N_{Jets}",name).Data(), nb_jetPt, lo_jetPt, hi_jetPt)
        );

        vh_jet_pt_dphi.push_back( 
            new TH2D(fmt("h_jet_pt_dphi_%s",num).Data(), 
                 fmt("%s;#Delta#phi;p_{T,jet}",name).Data(), 44, -0.25, 1.75, nb_jetPt, lo_jetPt, hi_jetPt)
        );
   
    }
    
    Long64_t nbytes = 0, nb = 0;
    /* jentry = 11910; // TODO */
	bool check_good{good_runs.size()!=0};
	map<int, int> m_500206;

    while (runAll || jentry < nEvents){
        nb = chain->GetEntry(jentry);  
        nbytes += nb;
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        if (jentry % 1000000 == 0) {
            f_log << " # finished " << jentry << " events" << endl;
            cout << " # finished " << jentry << " events" << endl;
            update_log();
		}

        if (check_good && !binary_search(good_runs.begin(), good_runs.end(), runId)) continue;

		if (trig_500206) {
			if (m_500206.count(runId)) ++m_500206[runId];
			else m_500206[runId] = 1;
		}

        for (int i{0};i<sets.size();++i){
            if (*sets[i].first) {
                /* cout << " a2: " << endl; // TODO */
                vh_zdcX[i]->Fill(zdcX);
                vh_bbcES[i]->Fill(bbcAdcES);
                vh_vz[i]->Fill(vz);

                vp_bbc_zdcX[i]->Fill(zdcX, bbcAdcES);
                vp_bbc_vz[i]->Fill(vz, bbcAdcES);
                vp_zdcX_vz[i]->Fill(vz, zdcX);

                if (Et != -1) {
                    /* cout << " a3: " << endl; // TODO */
                    vh_maxEt[i]->Fill(Et);
                    vp_maxEt_bbc[i]->Fill(bbcAdcES, Et);
                    if (njets > 0) {
                        if (is_same_side(phi_Et, jets_phi[0])) {
                            vp_maxJet_bbc[i].first->Fill(bbcAdcES, jets_pt[0]);
                            vh_maxJet[i]    .first->Fill(jets_pt[0]);
                        } else {
                            vp_maxJet_bbc[i].second->Fill(bbcAdcES, jets_pt[0]);
                            vh_maxJet[i]    .second->Fill(jets_pt[0]);
                        }
                    }
                    /* cout << " a4: " << endl; // TODO */

                    for (int j{0}; j<njets;++j){
                    /* cout << " a5: " << endl; // TODO */
                        vh_jet_pt[i]->Fill(jets_pt[j]);
                        vh_jet_pt_dphi[i]->Fill(delta_phi(phi_Et, jets_phi[j]), jets_pt[j]);
                    }

                    /* cout << " a6: " << endl; // TODO */
                    if (nch > 0) {
                    /* cout << " a7: " << endl; // TODO */
                        if (is_same_side(phi_Et, ch_tracks_phi[0])) {
                            vp_maxTr_bbc[i].first->Fill(bbcAdcES, ch_tracks_pt[0]);
                            vh_maxTr[i]    .first->Fill(ch_tracks_pt[0]);
                        } else {
                            vp_maxTr_bbc[i].second->Fill(bbcAdcES, ch_tracks_pt[0]);
                            vh_maxTr[i]    .second->Fill(ch_tracks_pt[0]);
                        }
                    }
                    /* cout << " a8: " << endl; // TODO */
                }
            }
        };
        /* update_log(); // TODO */
        ++jentry;
    }
	f_log  << "500206 entries per run: " << endl;
	f_log  << "  --run---  num"<<endl;
	for (auto e : m_500206) f_log << "  " << e.first << "  " << e.second << endl;
};

//------------------------------------------------------------------
// get basic zdcX and bbc hisgorams
//------------------------------------------------------------------
void InputSapling::LoopPrototype() {
    if (chain == 0) return;
    bool runAll{nEvents == -1};
    Long64_t jentry{0};

    if (runAll) {
        f_log << " # starting to read all events" << endl;
    } else {
        f_log << " # starting to read " << nEvents << " all events" << endl;
    }

    Long64_t nbytes = 0, nb = 0;
    while (runAll || jentry < nEvents){
        nb = chain->GetEntry(jentry);   nbytes += nb;
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        if (jentry % 500000 == 0) {
            f_log << " # finished " << jentry << " events" << endl;
        }

        if (njets < 2) { ++jentry; continue;}
        double last_pt = jets_pt[0];
        for (int i{1}; i<njets;++i) {
            if (jets_pt[i] > last_pt) cout << "  HERE! : " << i << " " << jets_pt[i] << " > " << last_pt;
            last_pt = jets_pt[i];
        }
        
        ++jentry;
    }
};

InputSapling::InputSapling(int argc, const char** argv) :
    InputBase{argc, argv, true},
    nEvents{100}
{
    chain = new TChain("tree");
    /* cout << "c0" << endl; */
    /* cout << "n_inputs " << n_inputs << endl; */
    if (give_help_msg) {
        std::cout 
            << " req. 3 ars:" << endl
            << " 1: output log name" << endl
            << " 2: #events" << endl
            << " 3:  has two options:" << endl
            << "    first:  root file name" << endl
            << "    second: [input.list of root files] [n] [N]"<<endl
            << "            where n, N, are n of N files" <<  endl
            << "           (i.e. 3 7 means get the third group of seven>" << endl;
        exit(0);
    }
    TString name { log_name };

    name.ReplaceAll(".log",".root");
    file = new TFile(name.Data(),"recreate");
    string in_name;

    int which_group{0};
    int n_groups{0};

    string in_file_name;

    nEvents = 0;
    if (n_inputs > 0) ss_args >> nEvents;
    if (nEvents == 0) {
        cout << "Warning, 0 events selected. Must select some events." << endl;
        exit(1);
    };
    if (n_inputs > 1){
        ss_args >> in_file_name;
    } else {
        in_file_name = "test.root";
        cout << " Using \"test.root\" for input file" << endl;
    }
    if (n_inputs > 2) ss_args >> which_group;
    if (n_inputs > 3) ss_args >> n_groups;

    if (in_file_name.find(".list") != string::npos){
        f_log <<       " # reading list of input files from " << in_file_name << endl;
        vector<TString> root_files;
        TString word;
        ifstream file;
        file.open(in_file_name.c_str());
        while (file >> word){
            /* cout << "word: " << word << endl; */
            if (word.EndsWith(".root")){
                root_files.push_back(word);
            } else {
                f_log <<       " # Notice: skipping file " << word << " is not a \"\\*.root\" file" << endl;
                /* fprintf(flog, " # Notice: skipping file %s is not a \"\\*.root\" file.\n", word.Data()); */
            }
        }
        if (which_group!=0) {
            f_log <<       " # dividing the " << root_files.size() << " input files into " << n_groups << " groups" << endl
                  << " # reading group " << which_group << " for this run." << endl;
            /* fprintf(flog, " # dividing the %i input files into %i groups; reading group %i for this run\n", */
                    /* root_files.size(), n_groups, which_group); */
            int n_files = root_files.size() / n_groups;
            int remainder = root_files.size() % n_groups;
            /* cout << " " << which_group << "  of  " << n_groups << " groups of " << root_files.size() << " files" << endl; */
            for (int i{n_files * (which_group - 1)};
                    i < (which_group == n_groups ? root_files.size() : n_files * which_group); ++i)
            {
                chain->AddFile(root_files[i]);
                f_log << " # chain->Add("<<root_files[i]<<")"<<endl;
                in_name = root_files[i];
                /* fprintf(flog, " # chain->Add(%s)\n", root_files[i].Data()); */
                /* cout << " # chain->Add(" << root_files[i] << ")" << endl; */
            }
        } else {
            for (auto file : root_files) {
                chain->AddFile(file.Data());
                f_log << " # chain->Add("<<file<<")"<<endl;
            };
        };
    } else {
        f_log <<       " # adding file " << in_file_name << endl;
        cout << "chain add " << in_file_name << endl;
        chain->Add(in_file_name.c_str());
    }
    Init(chain);

    // read the list of good and bad runs
    if (map_args.count("good_run.list")){
        // then read in the good runs
        string read_list = map_args["good_run.list"];
        ifstream if_file;
        if_file.open(read_list.c_str());
        if (!if_file.is_open()) {
            f_log << "Warning, the good run file " << read_list << " could not be found." << endl;
            cout  << "   no good run list obtained" << endl;
        } else {
            string line;
            while (getline(if_file,line)) {
                line.append(" ");
                stringstream words(line);
                TString word;
                while (words >> word) {
                    if (word.BeginsWith("//") || word.BeginsWith("#")) break;
                    good_runs.push_back(word.Atoi());
                }
            }
            std::sort(good_runs.begin(), good_runs.end());
            f_log << " Read in good run list from " << read_list;
            f_log << " Good runs (number = " << good_runs.size() << "):" <<endl;
            for (auto i : good_runs) f_log << "  " << i << endl;
        }
        if_file.close();
    }
    // read the list of good and bad runs
    if (map_args.count("bad_run.list")){
        // then read in the good runs
        string read_list = map_args["bad_run.list"];
        ifstream if_file;
        if_file.open(read_list.c_str());
        if (!if_file.is_open()) {
            f_log << "Warning, the bad run file " << read_list << " could not be found." << endl;
            cout  << "   no bad run list obtained" << endl;
        } else {
            string line;
            while (getline(if_file,line)) {
                line.append(" ");
                stringstream words(line);
                TString word;
                while (words >> word) {
                    if (word.BeginsWith("//") || word.BeginsWith("#")) break;
                    bad_runs.push_back(word.Atoi());
                }
            }
            std::sort(bad_runs.begin(), bad_runs.end());
            f_log << " Read in bad run list from " << read_list;
            f_log << " Bad runs (number = " << bad_runs.size() << "):" <<endl;
            for (auto i : bad_runs) f_log << "  " << i << endl;
        }
        if_file.close();
    }
}

InputSapling::~InputSapling() {
    file->Write();
    file->Close();
};
