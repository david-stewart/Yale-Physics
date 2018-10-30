#include <TSystem>

class StMaker;
class StChain;
class StPicoDstMaker;

StChain *chain;
void basicRunQA(
        const Int_t nEv=-1,
        const Char_t *inputFile="DataFile.list", 
        const Char_t *outputFile="basicRunQA",
        int   debug=0)
{

//Load all the System libraries
int nEvents=nEv;
gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
loadSharedLibraries();

gSystem->Load("StPicoEvent");
gSystem->Load("StPicoDstMaker");
gSystem->Load("basicRunQA");

chain = new StChain();

StPicoDstMaker *picoMaker =0X0; 
StPicoDstMaker::PicoIoMode IoMode = 2;
cout<<"Input file is"<<inputFile<<endl;
picoMaker = new StPicoDstMaker(IoMode,inputFile,"picoDst");

basicRunQA *pfMaker = new basicRunQA(
        "pf",
        picoMaker,
        outputFile,
        debug );

chain->Init();
cout<<"chain->Init();"<<endl;
int total = picoMaker->chain()->GetEntries();
cout << " Total entries = " << total << endl;
if(nEvents>total||nEvents<0) nEvents = total;
cout<<"Number of Events = "<<nEvents<<endl;
for (Int_t i=0; i<nEvents; i++){   
	if(i%5000==0) cout << "Working on eventNumber " << i << endl;
	chain->Clear();
	int iret = chain->Make(i);
	
	if (iret) { cout << "Bad return code!" << iret << endl; break;}
	total++;
	} 
	cout << endl;	
	cout << "****************************************** " << endl;
	cout << "Work done... now its time to close up shop!"<< endl;
	cout << "****************************************** " << endl;
	chain->Finish();
	cout << "****************************************** " << endl;

	delete chain;
}
