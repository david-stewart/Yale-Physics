#ifndef TOWERLIST__H
#define TOWERLIST__H
struct TT_list {
    // keep track of the Trigger Tower (TT) list (with Et, phi, eta, and towId)
    // index keeps track of which is the highest Et tower
    //
    double Et_threshold;
    std::vector<double> Et;
    std::vector<double> phi;
    std::vector<double> eta;
    std::vector<int>    towId;
    double maxEt;
    unsigned int index; // location of maxEt in vector Et
    unsigned int size; // size of vectors
    bool hasTT () { return (maxEt >= Et_threshold); };

    TT_list(double i_Et_threshold) :
        Et_threshold{ i_Et_threshold },
        maxEt{-1},
        index{0}, // the index of the TT
        size{0}
    {};
    void add(double i_Et, double i_phi, double i_eta, int i_towId) {
        /* cout << " adding " << i_Et << endl; */
        ++size;
        Et.push_back(i_Et);
        phi.push_back(i_phi);
        eta.push_back(i_eta);
        towId.push_back(i_towId);
        if (i_Et > maxEt) {
            maxEt = i_Et;
            index = size - 1;
        }
    };
    double phiEt()    { return size == 0 ? 100 : phi[index]; } 
    double etaEt()    { return size == 0 ? 100 : eta[index]; }
    int    TT_towID() { return size == 0 ? -1  : towId[index]; }
};

#endif
