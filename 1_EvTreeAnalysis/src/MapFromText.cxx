#include "MapFromText.h"

#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "TString.h"
using namespace std;

// input: file location
// output: map which uses the first word as keys, the second as a vector of the remaining values.

// read through the text file and fill a map with all the lines that start with an integer and fill 
// a vector with more ints
map <int, vector<int>> map_int_v_int (const char* file_name, FILE* flog, bool debug){
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
                if (word.BeginsWith("//") || word.BeginsWith("#" || !word.IsDigit())) break;
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
		if (flog != NULL) fprintf(flog, "# Read in following values:\n");
        for (auto i : rmap) {
            cout << " || " << i.first << " ";
            for (auto j : i.second) cout << " " << j;
            cout << endl;

			if (flog != NULL) {
				fprintf(flog, "%i ", i.first);
				for (auto j : i.second) fprintf(flog, "%i ", j);
				fprintf(flog, "\n");
			}
        }
    }
    return rmap;
};

