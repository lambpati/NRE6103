#include "../include/transporter.h"

void Transporter::russianRoulette(Particle& p){
    //Roulettes weight of the particle 
    if (std::abs(p.wgt) < weight_cutoff) {
        double P_kill = 1.0 - (std::abs(p.wgt) / survive_weight);
        if (RNG::rand() < P_kill)
            //Lost the game of Russian Roulette
            p.wgt = 0.;
            p.is_alive = false;
        }
        else {
            //Survived another day
            p.wgt = std::copysign(survive_weight, p.wgt);
        }
    }
}