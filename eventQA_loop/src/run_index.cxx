#include "map_vals_per_line.h"
#include <iostream>
#include <map>

using namespace std;
int main(int argc, const char** argv) {
   // arguments:
   // 1 : log file from which to build the index
   // 2 : the output file where to put the index
    if (argc < 3) {
        cout << "required arguments: [1] log input file [2] output file name" << endl;
        return 1;
    }
    /* map<int, vector<int>> myMap { map_vals_per_line(argv[1], NULL, true) }; */
    auto myMap =  map_vals_per_line(argv[1], NULL, true) ;

    FILE* fout = fopen(argv[2],"w");
    fprintf(fout, "Something in here!\n");
    int index{0};
    for (auto i : myMap) fprintf(fout,"%i %i\n", i.first, index++);
    fclose(fout);
    cout << "finished running" << endl;
}
