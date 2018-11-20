#include "StdInp.h"

StdInp::StdInp(int argc, const char** argv) {
    for (int i{1}; i<argc; ++i) options << " " << argv[i];
    setup();

    /* for (int i{0}; i<argc; ++i) cout << "  " << argv[i]; */
    /* cout << endl; */
    /* cout << "options: " << options.str() << endl; */
};

StdInp::StdInp(string str) { options.str(str); setup();}

void StdInp::setup() {
    options >> log_name;
    TString suffix(log_name);
    if (!suffix.EndsWith(".log")) {
        cout << "fatal: must enter a log name that ends with .log" << endl;
        exit(1);
    };
