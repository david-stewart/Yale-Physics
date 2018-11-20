#include <iostream>
#include <sstream>
#include <vector>

#include "main.h"
#include "MyInput.h"
#include "TH1F.h"

using namespace std;


int main(int argc, const char** argv) {
    MyInput inp{argc, argv};

    /* cout << "a1" << endl; */
    /* cout << " log name " << inp.log_name << endl; */
    inp.f_log << " There were " << inp.n_inputs << " input options " << endl;

    inp.f_log << "These were the input options:" << endl;
    inp.file->cd();
    string w;
    while (inp.ss_args >> w) cout << "   " << w << endl;
    inp.f_log << "And that's a wrap!" << endl;
    for (int i{0}; i<inp.nEvents; ++i) {
        inp.hg->Fill(i%2);
        inp.hg->Fill(i%2);
    }
return 0;
}
