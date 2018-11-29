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
map <int, vector<int>> map_int_v_int (const char* file_name, bool debug){
    // open the input file
    ifstream file;
    file.open(file_name);
    map <int, vector<int>> rmap {};
    if (!file.is_open()) {
        /* if (flog!=NULL) fprintf(flog,"# Warning: input file %s could not be opened\n", file_name); */
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
                /* cout << "This word |" << word << "|" << (word.BeginsWith("#") ? "True" : "False") << endl; */
                if (word.BeginsWith("//") || word.BeginsWith("#") || !word.IsDigit()) { break; }
                int value { word.Atoi() };
                if (!key) {
                    key = value; 
                    if (rmap.count(key)) { 
                        /* if (flog != NULL) fprintf(flog,"# Warning: key %i present twice in file %s.\n", key, file_name); */
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
		/* if (flog != NULL) fprintf(flog, "# Read in following values:\n"); */
        for (auto i : rmap) {
            cout << " || " << i.first << " ";
            for (auto j : i.second) cout << " " << j;
            cout << endl;

			/* if (flog != NULL) { */
			/* 	fprintf(flog, "%10i ", i.first); */
			/* 	for (auto j : i.second) fprintf(flog, "%10i ", j); */
			/* 	fprintf(flog, "\n"); */
			/* } */
        }
    }
    file.close();
    return rmap;
};

map <int, vector<double>> map_int_v_double (const char* file_name, bool debug){
    // open the input file
    ifstream file;
    file.open(file_name);
    map <int, vector<double>> rmap {};
    if (!file.is_open()) {
        /* if (flog!=NULL) fprintf(flog,"# Warning: input file %s could not be opened\n", file_name); */
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
                if (word.BeginsWith("//") || word.BeginsWith("#") || !word.IsDigit()) break;
                double value { word.Atof() };
                if (first) { 
                    first = false; 
                    key = value; 
                    if (rmap.count(key)) { 
                        /* if (flog != NULL) fprintf(flog,"# Warning: key %i present twice in file %s\n.", key, file_name); */
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
		/* if (flog != NULL) fprintf(flog, "# Read in following values:\n"); */
        for (auto i : rmap) {
            cout << " || " << i.first << " ";
            for (auto j : i.second) cout << " " << j;
            cout << endl;

			/* if (flog != NULL) { */
			/* 	fprintf(flog, "%10i ", i.first); */
			/* 	for (auto j : i.second) fprintf(flog, "%8.2f ", j); */
			/* 	fprintf(flog, "\n"); */
			/* } */
        }
    }
    file.close();
    return rmap;
};

map <TString, vector<double>> map_string_v_double (const char* file_name, bool debug){
    // open the input file
    ifstream file;
    file.open(file_name);
    map <TString, vector<double>> rmap {};
    if (!file.is_open()) {
        /* if (flog!=NULL) fprintf(flog,"# Warning: input file %s could not be opened\n", file_name); */
        /*  printf(     "# Warning: input file %s could not be opened\n", file_name); */
    } else {
        string line;
        while (getline(file,line)) {
            bool first{true};
            line.append(" ");
            stringstream words(line);
            TString key;
            words >> key;

            cout <<" :note: "<< key << " " << (key.BeginsWith("#!val:") ? "Yep" : "Nope") << endl;
            if (!key.BeginsWith("#!val:")) continue;
            words >> key;

            if (rmap.count(key)) {
                /* if (flog != NULL) fprintf(flog,"# Warning: key %s present twice in file %s\n.", key.Data(), file_name); */
                printf (     "# Warning: key %s present twice in file %s\n.", key.Data(), file_name);
            }

            TString word;
            while (words >> word) {
                rmap[key].push_back(word.Atof());
            }
        }
    }
    if (debug) {
		/* if (flog != NULL) fprintf(flog, "# Read in following values:\n"); */
        for (auto i : rmap) {
            cout << " || " << i.first << " ";
            for (auto j : i.second) cout << " " << j;
            cout << endl;

			/* if (flog != NULL) { */
			/* 	fprintf(flog, "%-14s ", i.first.Data()); */
			/* 	for (auto j : i.second) fprintf(flog, "%8.2f ", j); */
			/* 	fprintf(flog, "\n"); */
			/* } */
        }
    }
    file.close();
    return rmap;
};

