#pragma once

#include "../include/particle.h"
#include "../include/rng.h"

class Transporter {
    private:
        // TO DO add these parameters to a readable input form
       const int dx = 1000;
       const double particles = 100000;
       const double survive_weight = 0.8; // Between 0 and 1 values
       const double weight_cutoff = 0.2;



    public:
        //Methods
        Transporter() = default;

        void russianRoulette(Particle& p);

        //Getters


        //Setters
};