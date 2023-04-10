#pragma once

#include "../include/particle.h"
#include "../include/rng.h"
#include "../include/geometry.h"
#include "../include/boundaries.h"
#include "../include/bank.h"

class Transporter {
    private:
        // TO DO add these parameters to a readable input form
       const int dx = 1000;
       const double particles = 100000;
       const double survive_weight = 0.8; // Between 0 and 1 values
       const double weight_cutoff = 0.1;

        // normally would be transport correction factor but idk
       const double sigma_t = 1/particles;

       int current_region;



    public:
        //Methods
        Transporter() = default;

        void russianRoulette(Particle& p);
        void collision(Particle& p);
        void determineMaterial(Particle& p, int i);
        void fissionNeutrons(Particel& p, );
        void scatterNeutrons(Particle& p, );
        void captureNeutrons(Particle& p, )

        //Getters


        //Setters
};