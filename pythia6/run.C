#include <TSystem>

void run() {
    /* gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C"); */
    /* loadSharedLibraries(); */
        
    /* gSystem->Load("StPicoEvent"); */
    /* gSystem->Load("StPicoDstMaker"); */
#ifdef __CINT__
  // Load the Event Generator abstraction library, Pythia 6
  // library, and the Pythia 6 interface library.
  gSystem->Load("libEG");
  gSystem->Load("$ROOTSYS/../pythia6/libPythia6"); //change to your setup
  gSystem->Load("libEGPythia6");
#endif

    gSystem->Load("PythLib");

    PythJets* a = new PythJets();
    a->run(10000);
};

/* class StMaker; */
/* class StChain; */
/* class StPicoDstMaker; */

/* StChain *chain; */
/* void simpleETowQA( */
/*         const Int_t nEv=-1, */
/*         int   triggerId, */
/*         const Char_t *inputFile="DataFile.list", */ 
/*         const Char_t *outputFile="SimpleETowQA", */
/*         const char* bad_tower_list="/direct/star+scratch/djs/bad_towers/BadTowers_pp200_2015.list", */
/*         const char* bad_run_list=  "/direct/star+scratch/djs/bad_towers/bad_run_list.list") */
/* { */

/* //Load all the System libraries */
/* int nEvents=nEv; */
/* gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C"); */
/* loadSharedLibraries(); */

/* gSystem->Load("StPicoEvent"); */
/* gSystem->Load("StPicoDstMaker"); */
/* gSystem->Load("SimpleETowQA"); */

/* chain = new StChain(); */

/* StPicoDstMaker *picoMaker =0X0; */ 
/* StPicoDstMaker::PicoIoMode IoMode = 2; */
/* cout<<"Input file is"<<inputFile<<endl; */
/* picoMaker = new StPicoDstMaker(IoMode,inputFile,"picoDst"); */

/* SimpleETowQA *pfMaker = new SimpleETowQA( */
/*         "pf", */
/*         picoMaker, */
/*         outputFile, */
/*         triggerId, */
/*         bad_tower_list, */
/*         bad_run_list); */

/* chain->Init(); */
/* cout<<"chain->Init();"<<endl; */
/* int total = picoMaker->chain()->GetEntries(); */
/* cout << " Total entries = " << total << endl; */
/* if(nEvents>total||nEvents<0) nEvents = total; */
/* cout<<"Number of Events = "<<nEvents<<endl; */
/* for (Int_t i=0; i<nEvents; i++){ */   
/* 	if(i%5000==0) cout << "Working on eventNumber " << i << endl; */
/* 	chain->Clear(); */
/* 	int iret = chain->Make(i); */
	
/* 	if (iret) { cout << "Bad return code!" << iret << endl; break;} */
/* 	total++; */
/* 	} */ 
/* 	cout << endl; */	
/* 	cout << "****************************************** " << endl; */
/* 	cout << "Work done... now its time to close up shop!"<< endl; */
/* 	cout << "****************************************** " << endl; */
/* 	chain->Finish(); */
/* 	cout << "****************************************** " << endl; */

/* 	delete chain; */
/* } */
