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
    inline static std::vector<int> fiss_tally;
    inline static double w;
    inline static std::vector<double> mesh;
    inline static std::vector<double> flux_rate;
    inline static std::vector<double> rx_rate;

    inline static std::vector<std::pair<double, double>> collisions;
    inline static std::vector<std::pair<double, double>> pathlengths;

    inline static int reg;

public:
    //Methods
    Tally() = default;

    static void makeMesh(int res);
    static void addFiss(double pos);
    static void addColl(double pos, double weight=1.);
    static void calculateFlux(double particles, int bins);
    static void accumulateColl(double pos, double weight);
    static void accumulatePath (double pos, double prev_pos, double dir, double weight);
    static void determineMaterial(double pos, int i);
    static void pathLengthTally(double pos, double prev_pos, double dir, double weight, double particles);
    //Getters
    static const bool getTallyType() { return flux; };
    static const std::vector<int> getCollTally(){ return coll_tally; };
    static const std::vector<double> getMesh(){ return mesh; };
    static const std::vector<double> getFlux(){ return flux_rate; };
    static const std::vector<double> getRx(){ return rx_rate; };
    static const std::vector<std::pair<double,double>> getCollisions(){ return collisions; };
    static const std::vector<std::pair<double,double>> getPathlengths(){ return pathlengths; };

    //Setters
    static void setTallyType(bool f) { flux = f; };
};