#include "map_vals_per_line.h"
#include <iostream>
#include <map>

using namespace std;
int main(int argc, const char** argv) {

    auto myMap = map_vals_per_line("logs/test.log");
    for (auto i : myMap) {
        cout << i.first << " : ";
        char num[100];
        for (auto e : i.second) printf(" %10i",e);
        cout << endl;
    }
}
