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
    inline static double w;
    inline static std::vector<std::pair<double, double>> pathlengths;

    inline static std::vector<double> std_dev;
    inline static std::vector<double> mean_flux;

public:
    //Methods
    Tally() = default;

    static void makeMesh(int res);
    static void pathLengthTally(double pos, double prev_pos, double dir, double weight, double particles);
    //Getters
    static const bool getTallyType() { return flux; };
    static const std::vector<std::pair<double,double>> getPathlengths(){ return pathlengths; };
    static std::pair<double, double> getMeanVariance(const std::vector<std::pair<double, double>>& vect);

    //Setters
    static void setTallyType(bool f) { flux = f; };
};