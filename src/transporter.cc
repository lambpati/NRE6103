#include "../include/transporter.h"

void Transporter::russianRoulette(Particle& p){
    //Roulettes weight of the particle 
    if (std::abs(p.wgt) < weight_cutoff) {
        double P_kill = 1.0 - (std::abs(p.wgt) / survive_weight);
        if (RNG::rand() < P_kill) {
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

void Transporter::determineMaterial(Particle& p, int i){
    // Check to make sure particle position is within i'th region bounds (Region = index + 1)
    if(p.pos < Geometry::getXSvRegion(i).X_max && p.pos >= Geometry::getXSvRegion(i).X_min){
        current_region = Geometry::getRegion(i-1);
        return;
    }
    // If out of i'th region, iterate + 1 to find correct region
    else if(p.pos >= Geometry::getXSvRegion(i).X_max && p.pos <= Geometry::getMax()){
        Transporter::determineMaterial(p, i+1);
    }
    // If before i'th region, iterate - 1 to find correct region
    else if(p.pos < Geometry::getXSvRegion(i).X_min && p.pos >= Geometry::getMin()){
        Transporter::determineMaterial(p, i+1);
    }
    // Fall through case. particle outside of material. Particle is determined by BCs
    else{
        // LHS BC
        if(p.pos < Geometry::getMin()){
            Boundaries::determineBehavior(p, false);
        }
        // RHS BC
        else{
            Boundaries::determineBehavior(p, true);
        }

    }
}