#pragma once

#include <vector>
#include <algorithm>
#include <cmath>

#include "../include/geometry.h"

class Tally {
private:
    inline static bool flux;
    inline static std::vector<int> coll_tally;
    inline static std::vector<int> fiss_tally;
    inline static double w;
    inline static std::vector<double> mesh;

public:
    //Methods
    Tally() = default;

    static void makeMesh(int res);
    static void addFiss(double pos);
    static void addColl(double pos, double weight=1., int i=0);
    static void determineBin(int bins);
    //Getters
    static const bool getTallyType() { return flux; };
    static const std::vector<int> getCollTally(){ return coll_tally; };
    static const std::vector<double> getMesh(){ return mesh; };

    //Setters
    static void setTallyType(bool f) { flux = f; };
};