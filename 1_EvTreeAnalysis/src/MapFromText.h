#ifndef MAP_FROM_TEXT__H
#define MAP_FROM_TEXT__H

#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <TString.h>
using namespace std;


map <int,     vector<int>>       map_int_v_int      (const char* file_name, FILE* flog=NULL, bool debug=false);
map <int,     vector<double>>    map_int_v_double   (const char* file_name, FILE* flog=NULL, bool debug=false);
map <TString, vector<double>> map_string_v_double(const char* file_name, FILE* flog=NULL, bool debug=false);

#endif
