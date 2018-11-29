#include "CombineLogs.h"

#include "OneVarStats.h"
#include <map>
#include "MyInput.h"
#include "TrigCount.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
int main(int argc, const char** argv){
    MyInput inp{argc, argv};
    int null_int;

    // output to collect
    AllVarStats    vars{null_int};
    ostringstream  chain_files {};
    TrigCount*     trigs{nullptr};

    bool           found_names;
    vector<string> names;
    vector<int> ids;

    string find_chain_add { " # chain->Add" };
    string find_trigName  { " #  trigName" };
    string find_trigNum   { " #  trigNum" };
    string find_starting_log { " # Starting log on (local time):" };
    vector<string> trigNames;
    vector<int>    trigIds;
    
    string trash;
    string file_name;
    /* cout << "a1" << endl; */
    while (inp.ss_args >> file_name) {
        /* cout << "a2" << endl; */
        inp.f_log << " # reading file: " << file_name << endl;
        
        ifstream infile {file_name, ios::in};
        if (!infile) {
            /* cout << "a3" << endl; */
            inp.f_log << " # failed to read file: " << file_name << endl;
            cout << "warning! failed to read file: " << file_name << endl;
            cout << "skipping file." << endl;
            continue;
        }

            /* cout << "a4" << endl; */
        // read the files for each kind of input
        string line;
            /* cout << "a5" << endl; */
        while (getline(infile, line)) {
            /* cout << "a6" << endl; */
            if (!line.compare(0,find_chain_add.size(), find_chain_add)) {
                chain_files << line << endl;
            } else if ( !line.compare(0, find_trigName.size(), find_trigName)) {
                istringstream is{line};
                string name;
                vector<string> names_;
                is >> trash >> trash;
                while (is >> name) names_.push_back(name);

                if (names.size() == 0) names = names_;
                else if (names != names_) {
                    ostringstream err;
                    err << "fatal error, Trig Names are not same in a given file." << endl;
                    err << " old names: ";
                    for (auto n : names) err << " " << n;
                    err << endl;
                    err << " new names: ";
                    for (auto n : names_) err << " " << n;
                    err << endl;
                    inp.f_log << err.str();
                    cout << err.str();
                    exit(2);
                }
            } else if ( !line.compare(0, find_trigNum.size(), find_trigNum) ) {
            /* cout << "a7" << endl; */
                istringstream is{line};
                string name;
                vector<int> ids_;
                int id;
                is >> trash >> trash;
                while (is >> id) ids_.push_back(id);

                if (ids.size() == 0) ids = ids_;
                else if (ids != ids_) {
                    ostringstream err;
                    err << "fatal error, trigger ids are not same two different lines." << endl;
                    err << " old ids: ";
                    for (auto n : ids) err << " " << n;
                    err << endl;
                    err << " new ids: ";
                    for (auto n : ids_) err << " " << n;
                    err << endl;
                    inp.f_log << err.str();
                    cout << err.str();
                    exit(2);
                }
            /* cout << "a8" << endl; */
                if (!trigs && names.size() > 0 && ids.size() > 0) {
                    vector<bool*> bools;
                    for (auto i : names) bools.push_back(nullptr);
                    trigs = new TrigCount { null_int, names, ids, bools };
                }
            } else if ( !line.compare(0,3," | ") ) {
            /* cout << "a9" << endl; */
                if (trigs == nullptr) {
                    ostringstream err;
                    err << " fatal error, trying to read trigger numbers without having first trigger names and ids" << endl;
                    cout << err.str();
                    inp.f_log << err.str();
                    exit(2);
                }
            /* cout << "b0" << endl; */
                trigs->add(line);
            } else if ( !line.compare(0, 3, " : ") ) {
            /* cout << "a10" << endl; */
                /* cout << *trigs; */
                vars << line;
            }
            /* cout << "a11" << endl; */
        }
    }
    inp.f_log << " # Summarized stats:\n" << endl;
    inp.f_log << *trigs;
    inp.f_log << vars << endl;
    inp.f_log << " # files used to get these statistics" << endl;
    inp.f_log << chain_files.str() << endl;

};
