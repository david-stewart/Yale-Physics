#ifndef MAP_VALS_PER_LINE__H
#define MAP_VALS_PER_LINE__H

#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <TString.h>
using namespace std;

//------------------------------------------------------------------------
// Provides a function that makes a c++ map of values per line (the first
// value is the key)
//------------------------------------------------------------------------
map <int, vector<int>> map_vals_per_line(const char* file_name, FILE* flog=NULL, bool debug=false){
    // open the input file
    ifstream file;
    file.open(file_name);
    map <int, vector<int>> rmap {};
    if (!file.is_open()) {
        if (flog!=NULL) fprintf(flog,"# Warning: input file %s could not be opened\n", file_name);
         printf(     "# Warning: input file %s could not be opened\n", file_name);
    } else {
        string line;
        while (getline(file,line)) {
            bool first{true};
            int key {0};
            line.append(" ");
            stringstream words(line);
            TString word;
            while (words >> word) {
                if (word.BeginsWith("//") || word.BeginsWith("#")) break;
                int value { word.Atoi() };
                if (first) { 
                    first = false; 
                    key = value; 
                    if (rmap.count(key)) { 
                        if (flog != NULL) fprintf(flog,"# Warning: key %i present twice in file %s\n.", key, file_name);
                        printf (     "# Warning: key %i present twice in file %s\n.", key, file_name);
                    }
                    continue;
                } else {
                    rmap[key].push_back(value);
                }
            }
        }
    }
    if (debug) {
        for (auto i : rmap) {
            cout << " || " << i.first << " ";
            for (auto j : i.second) cout << " " << j;
            cout << endl;
        }
    }

    /* for (auto a : rmap)  cout << "  : " << a.first <<"| "; */
    /* cout << endl; */
    return rmap;
};

#endif
