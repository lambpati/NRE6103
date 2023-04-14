#pragma once

#include <algorithm>
#include <iterator>
#include <vector>

#include "../include/particle.h"
#include "../include/rng_gen.h"
#include "../include/geometry.h"
#include "../include/boundaries.h"
#include "../include/bank.h"
#include "../include/tally.h"

class Transporter {
    private:

       const double survive_weight = 0.8; // Between 0 and 1 values
       const double weight_cutoff = 0.1;

       int current_region = 0;

       double left_bound = 0;
       double right_bound = 0;



    public:
        //Methods
        Transporter() = default;

        void initParticles(double dx);

        void russianRoulette(Particle& p);
        void collision(Particle& p);
        void moveParticle(Particle& p, double dx, double particles);
        void determineMaterial(Particle& p);
        void fissionNeutrons(Particle& p);

        //Getters


        //Setters
};