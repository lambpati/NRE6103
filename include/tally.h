#pragma once

#include <vector>
#include <algorithm>
#include <cmath>
#include <utility>

#include "../include/geometry.h"
#include "../include/transporter.h"
#include "../include/particle.h"

class Tally {
private:
    inline static bool flux;
    inline static std::vector<int> coll_tally;
    inline static std::vector<double> trac_length;
    inline static std::vector<int> fiss_tally;

public:
    //Methods
    Tally() = default;
    
    static void makeMesh(int res);
    static void pathLengthTally(double pos, double prev_pos, double dir, double weight, double particles);
    //Getters
    static const bool getTallyType() { return flux; };
    static const std::vector<std::pair<double,double>> getPathlengths(){ return pathlengths; };

    //Setters
    static void setTallyType(bool f) { flux = f; };
};