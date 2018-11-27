#ifndef basicRunQA_h
#define basicRunQA_h

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
#include "TTree.h"
#include <map>
/* #include "StPicoEvent/StPicoBTowHit.h" */

#include "QA_tree.h"

class StPicoDst;
class StPicoDstMaker;
class StPicoEvent;
class TString;
class TH1F;
class TH2F;
class TH3F;
class TH1I;
class TProfile;
class basicRunQA : public StMaker {

    // histograms
    // 1. histograms of results for all towers
    // 2. histograms & profiles of results 
    private:
    FILE* flog;
    StPicoDstMaker  *mPicoDstMaker;
    /* int              mtriggerid; */
    StPicoDst       *mPicoDst;
    TString    	     mOutName;
    /* TString          fbad_tower_file; */
    /* TString          fbad_run_file; */
    /* std::vector<int> fbad_run_list; */
    /* std::vector<int> fbad_tower_list; */
    TFile*           fout;

    public:
    basicRunQA(
        const char     *name,
        StPicoDstMaker *picoMaker,
        const char     *outName,
        bool           debug
    );
    virtual ~basicRunQA();

    virtual Int_t Init();
    virtual Int_t Make();
    virtual void  Clear(Option_t *opt="");
    virtual Int_t Finish();

    bool fdebug;

    TTree          *ftree;
    QA_event       fevent;

    TTree          *ftree_RunEnds;
    RunEnds        fRunEnds;

    map<int, RunEnds> fmap_RunEnds; 
    int fEventsProcessed;


    private:
    ClassDef(basicRunQA, 1)
};
#endif
