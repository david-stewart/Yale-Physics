#include "MapFromText.h"
#include <iostream>
#include "TString.h"

using namespace std;

map<int, vector<int>>& operator+=(map<int, vector<int>>& lhs, const map<int, vector<int>>& rhs) {
    /* for (auto v : lhs) cout << v.first << endl; */
    for (const auto& v : rhs) {
        if (lhs.count(v.first)) {
            // check that the vectors are the same size
            if (lhs[v.first].size() != v.second.size())
                cout << "Error! vectors for " << v.first << " in each map are different sizes! "<<endl;
            else {
                for (unsigned int i{0}; i<v.second.size(); ++i) lhs[v.first][i] += v.second[i];
            }
        } else {
            lhs[v.first] = v.second;
        }
    }
    return lhs;
};

map<TString, vector<double>>& operator*= (map<TString, vector<double>>& lhs, const map<TString, vector<double>> rhs) {
    // will update the min and max values of the lhs, while zero-ing out it's std-dev's
    for (auto & v : lhs) { v.second[3] = 0; v.second[4] = 0; }
    for (const auto& v : rhs) {
        if (lhs.count(v.first)) {
            auto& lv = lhs[v.first];
            lv[0] = min(lv[0], v.second[0]);
            lv[1] = max(lv[1], v.second[1]);
        }
    }
    return lhs;
};


void operator+(map<int,int> a, map<int,int> b) { for (auto v : b) cout << v.second << endl; };

int main() {
    cout << "lion" << endl;
    FILE* fout = fopen("test.log","w");
    /* auto map_i = map_int_v_int("test_files/count_events_P16id_15_20.log", fout, true); */
    /* cout << " ---------- map to double ---------- " << endl; */
    /* auto map_d = map_int_v_double("test_files/count_events_P16id_15_20.log", fout, true); */
    /* cout << " ---------- map string to double ---------- " << endl; */
    /* auto map_s = map_string_v_double("test_files/count_events_P16id_15_20.log", fout, true); */

    fprintf(fout, " Set one:\n");
    auto map_a = map_int_v_int("test_files/test_map_0.log", fout);

    fprintf(fout, " Set two:\n");
    auto map_b = map_int_v_int("test_files/test_map_1.log", fout) ;

    cout << "map a:" << endl;
    for (auto v : map_a) {
        cout << " * " << v.first << " : ";
        for (auto v2 : v.second) cout << v2 << " ";
        cout << endl;
    }

    cout << "map b:" << endl;
    for (auto v : map_b) {
        cout << " * " << v.first << " : ";
        for (auto v2 : v.second) cout << v2 << " ";
        cout << endl;
    }

    map_a += map_b;

    cout << "map a: again" << endl;
    for (auto v : map_a) {
        cout << " * " << v.first << " : ";
        for (auto v2 : v.second) cout << v2 << " ";
        cout << endl;
    }

    auto copy_a = map_a;
    cout << "copy:"<<endl;
    for (auto v : copy_a) {
        cout << " * " << v.first << " : ";
        for (auto v2 : v.second) cout << v2 << " ";
        cout << endl;
    }

    map_a += map_int_v_int("test_files/test_map_1.log", fout) ;
    map_a += map_int_v_int("test_files/test_map_1.log", fout) ;

    cout << "map a: last" << endl;
    for (auto v : map_a) {
        cout << " * " << v.first << " : ";
        for (auto v2 : v.second) cout << v2 << " ";
        cout << endl;
    }


    cout << "copy:"<<endl;
    for (auto v : copy_a) {
        cout << " * " << v.first << " : ";
        for (auto v2 : v.second) cout << v2 << " ";
        cout << endl;
    }


};

    

