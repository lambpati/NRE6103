#pragma once

#include <algorithm>
#include <iterator>
#include <vector>

#include "../include/particle.h"
#include "../include/rng.h"
#include "../include/geometry.h"
#include "../include/boundaries.h"
#include "../include/bank.h"
#include "../include/tally.h"

class Transporter {
    private:

       const double survive_weight = 0.8; // Between 0 and 1 values
       const double weight_cutoff = 0.1;

        // normally would be transport correction factor but idk
       double sigma_ts;

       int current_region;



    public:
        //Methods
        Transporter() = default;

        void initParticles(double dx);

        void russianRoulette(Particle& p);
        void collision(Particle& p);
        void moveParticle(Particle& p, double dx);
        void determineMaterial(Particle& p);
        void fissionNeutrons(Particle& p);
        void scatterNeutrons(Particle& p);
        void captureNeutrons(Particle& p);

        //Getters


        //Setters
};