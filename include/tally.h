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
    inline static std::vector<double> positions;
    inline static std::vector<std::pair<double, double>> pathlengths;
    inline static std::vector<std::pair<double, double>> flux_vec;

    inline static std::vector<double> std_dev;
    inline static std::vector<double> mean_flux;

    inline static std::vector<std::pair<double, double>> forward_flux;
    inline static std::vector<std::pair<double, double>>  adjoint_flux;

public:
    //Methods
    Tally() = default;

    static void makeMesh(int res);
    static void pathLengthTally(double pos, double prev_pos, double dir, double weight, double particles, double sig_tot);
    static void calculateMeanVariance(const std::vector<std::pair<double, double>>& vect);
    static void calculateFlux(int res);
    //Getters
    static const bool getTallyType() { return flux; };
    static const std::vector<std::pair<double,double>> getPathlengths(){ return pathlengths; };
    static const std::vector<std::pair<double,double>> getFlux(){ return flux_vec; };
    static const std::vector<double> getMean(){ return mean_flux; };
    static const std::vector <double> getVariance() { return std_dev; };
    static const std::vector<std::pair<double, double>> getForward(){return forward_flux; };
    static const std::vector<std::pair<double, double>> getAdjoint(){ return adjoint_flux; };
    static const std::vector<double> getPositions(){ return positions; };
    static const double getWidth(){ return w; };

    //Setters
    static void setTallyType(bool f) { flux = f; };
};