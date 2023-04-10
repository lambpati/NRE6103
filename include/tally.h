#pragma once

#include <vector>
#include <algorithm>

#include "../include/geometry.h"

class Tally {
private:
    inline static bool flux;
    inline static std::vector<int> coll_tally;
    inline static std::vector<int> fiss_tally;

public:
    //Methods
    Tally() = default;

    static void makeMesh(int res);
    static void addFiss(double pos);
    static void addColl(double pos, double weight);
    //Getters
    static const bool getTallyType() { return flux; };

    //Setters
    static void setTallyType(bool f) { flux = f; };
};