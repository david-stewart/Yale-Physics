#ifndef EventTress__h
#define EventTress__h

#include "TTree.h"
#include "StRoot/StPicoDstMaker/StPicoDst.h"
#include "StRoot/StPicoEvent/StPicoTrack.h"
#include "StRoot/StPicoEvent/StPicoEvent.h"
#include "StRoot/StPicoDstMaker/StPicoDstMaker.h"
#include "StRoot/StPicoEvent/StPicoEmcTrigger.h"
#include "StRoot/StPicoEvent/StPicoBTowHit.h"
#include "StPicoEvent/StPicoBEmcPidTraits.h"
#include "StMaker.h"
/* #include "bad_runs.h" */
/* #include "bad_towers.h" */
#include "StThreeVectorF.hh"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TH1I.h"
#include "TProfile.h"
#include "TFile.h"
#include <iostream>
#include "StThreeVectorF.hh"
#include "StEmcUtil/geometry/StEmcGeom.h"
#include "StEmcUtil/projection/StEmcPosition.h"
#include "TreeObjects.h"
#include <map>

class StPicoDst;
class StPicoDstMaker;
class StPicoEvent;
class TString;
class TH1F;
class TH2F;
class TH3F;
class TH1I;
class TProfile;
class MyJetDefinitionTerms ;

class Run16128015 : public StMaker {
    private:
    /* map<string, int> m_file_names; */

    StPicoDstMaker* fPicoDstMaker;
    TString         fOutName;
    const char*     fbad_run_file;
    bool            fdebug;
    bool            fmakePreCuts;
    bool            fisAu;

    map<string, int> m_file_names;


    std::vector<int> ftriggerid;

    long long int fEventsProcessed;
    bool f_hastriggers;

    double fvz_cut;
    StPicoDst*       fPicoDst;
    std::vector<int> fbad_run_list;
    TFile* fout;
    FILE*  flog;
    FILE*  dlog;

    TTree*       ftree;
    TTree*       fpc_tree; // a tree which will hold the pre-cut BBCsig, ZDCsig, Zvert, max_TT_Et, 
                           // and NTracks prior to requiring a minimum TT_Et
    Event        fevent;

    MyJetDefinitionTerms* f_bge;

  public:
    Run16128015(
        const char*     name,
        StPicoDstMaker* picoMaker,
        const char*     outName,
        const char*     i_bad_run_file,
        bool            i_debug//,
    );
    virtual ~Run16128015();
    
    virtual Int_t Init();
    virtual Int_t Make();
    virtual void  Clear(Option_t *opt="");
    virtual Int_t Finish();

    ClassDef(Run16128015, 1)
};

#endif
