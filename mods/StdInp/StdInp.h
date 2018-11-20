#ifndef StdInp__h
#define StdInp__h

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>


using namespace std;
class StdInp {
    public:
    StdInp(int argc, const char** argv);
    StdInp(string line);
    ofstream log;
    void update_log();
    stringstream options;
    private:
    void setup();
    string log_name;
};

#endif
