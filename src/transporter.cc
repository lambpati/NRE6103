#include "../include/transporter.h"


//TESTING
#include <iostream>

void Transporter::initParticles(double dx, double part, int i){
    //Make new particle
    Particle p;
    // If flux fixed source problem
    if(Tally::getTallyType()){
        // Assumably we will only have one source, which for now is hardcoded in region 3, index 2
        current_region = Geometry::getRegion(2);
        // Derive p.pos from current region max and min and normalized random number
        p.pos = RNG_GEN::rand()*(Geometry::getXSvRegion(2).X_max-Geometry::getXSvRegion(2).X_min)+Geometry::getXSvRegion(2).X_min;
        p.dir = 1-2*RNG_GEN::rand();
        // Set p.wgt to 1
        p.wgt = 1;
        // Set to is_alive = true
        p.is_alive = true;
    }
    // Else is eigenvalue problem
    else{
        current_region = Geometry::getRegion(2);
        // Populate bank with v_sig_f as initial guess
        p.pos = Transporter::detDist(part, i);
        //std::cout << p.pos << std::endl;
        p.dir = 1-2*RNG_GEN::rand();
        // Set p.wgt to 1
        p.wgt = 1;
        // Set to is_alive = true
        p.is_alive = true;
    }
    
    Bank::addParticle(p);
}

double Transporter::detDist(double part, int i) {
    double position = (Geometry::getMax() - Geometry::getMin()) / part * i;
    return position;
}

void Transporter::russianRoulette(Particle& p){
    //Roulettes weight of the particle 
    if (p.wgt < weight_cutoff) {
        if (RNG_GEN::rand() > weight_cutoff) {
            //Lost the game of Russian Roulette
            p.wgt = 0.;
            p.is_alive = false;
            //std::cout << "Killing particles " << std::endl;
            Bank::killParticles(p);
        }
        else {
            //Survived another day
            p.wgt *= 1/weight_cutoff;
        }
    }
}

void Transporter::determineMaterial(Particle& p){
        // LHS BC
    if(p.pos <= Geometry::getMin()){
        //std::cout << "LHS " << std::endl;
        Boundaries::determineBehavior(p, false);
    }
    // RHS BC
    else if(p.pos >= Geometry::getMax()){
        //std::cout << "RHS " << std::endl;
        Boundaries::determineBehavior(p, true);
    }
    else{
        //std::cout << "in else" << std::endl;
        for(auto& i : Geometry::getGeometry()){
           // std::cout << "i is " << i << std::endl;
            if(p.pos < i.second.X_max){
                current_region = i.first-1;
                left_bound = i.second.X_min;
                right_bound = i.second.X_max;
                break;
            }
        }
    }
}


int Transporter::determineMaterial(double position){
    double reg = 0;
        for(auto& i : Geometry::getGeometry()){
           // std::cout << "i is " << i << std::endl;
            if(position < i.second.X_max){
                reg = i.first-1;
                left_bound = i.second.X_min;
                right_bound = i.second.X_max;
                break;
            }
        }
        return reg;
    }

void Transporter::moveParticle(Particle& p, double dx, double particles){
    while(p.is_alive){
        double prev_pos = p.pos;
        //std::cout << p.pos << " position " << p.dir << " dir " << std::endl;
        Transporter::determineMaterial(p);
        if (!p.is_alive) break;
        double sig_tot = Geometry::getXSvRegion(current_region).sig_s + Geometry::getXSvRegion(current_region).sig_a;
        //std::cout << "sig_tot in region " << current_region+1 << " is " << sig_tot << std::endl;
        if (sig_tot == 0.) {
            if(p.dir < 0.){
                //current_region--;
                p.pos = Geometry::getXSvRegion(current_region).X_min-0.000001;
            }
            else{
                //current_region++;
                p.pos = Geometry::getXSvRegion(current_region).X_max+0.000001;
            }
        }
        else {
                p.pos += -1/sig_tot * std::log(RNG_GEN::rand() + 0.000001) * p.dir;
        }
        // Please leave the region
        p.pos = p.pos < left_bound && p.dir < 0 ? left_bound - 0.000001 : p.pos;
        p.pos = p.pos > right_bound && p.dir > 0 ? right_bound + 0.000001 : p.pos;
            
        //std::cout << prev_pos << " -> " << p.pos << std::endl;
        Tally::pathLengthTally(p.pos, prev_pos, p.dir, p.wgt, particles, sig_tot);
        int old_region = current_region;
        Transporter::determineMaterial(p);
        if(!Tally::getTallyType()){
            if(!p.is_alive) break;
        }
        if (current_region != old_region) continue;
        // At this new location, does it experience a collision?
        Transporter::collision(p);
        if (Tally::getTallyType()) {
            Transporter::russianRoulette(p);
        }
    }

}

void Transporter::collision(Particle& p){
    Transporter::determineMaterial(p);
    if(!p.is_alive){
        return;
    }
    //std::cout << "coll particle dir " << p.dir << " particle pos " << p.pos << std::endl;
    double sig_tot = Geometry::getXSvRegion(current_region).sig_s + Geometry::getXSvRegion(current_region).sig_a;
    // Scattering probability = sig_s / sig_total
    double Pscatter = Geometry::getXSvRegion(current_region).sig_s / sig_tot;
    // Fission probability = sig_f/ sig_total
    double Pfission =  Pscatter + Geometry::getXSvRegion(current_region).sig_f/sig_tot;
    // Capture probability = sig_a/ sig_total - Pfission
    double Pcapt = (Geometry::getXSvRegion(current_region).sig_a - Geometry::getXSvRegion(current_region).sig_f)/sig_tot; //- Pfission;

    double rand_p = RNG_GEN::rand();

    if(rand_p < Pscatter){
        //If scatter, just change direction
        p.dir = 1-2*RNG_GEN::rand();
       // std::cout << "scattering " << p.dir << std::endl;
    }
    else if(rand_p < Pfission){
        //Do fission
        Transporter::fissionNeutrons(p);
        if (Tally::getTallyType()) {
            p.wgt *= 1 - (Pfission - Pscatter);
        }
        else{
           // p.is_alive = false;
        }
      //  std::cout << "fissioning " << std::endl;
    }
    else{
        // Capture
        if (Tally::getTallyType()) {
            p.wgt *= 1 - Pcapt;
        }
        else {
            p.is_alive = false;
        }
      //  std::cout << "captured " << std::endl;
    }
}

void Transporter::fissionNeutrons(Particle& p){
    double sig_tot = Geometry::getXSvRegion(current_region).sig_s + Geometry::getXSvRegion(current_region).sig_a;
    double k_score = p.wgt * Geometry::getXSvRegion(current_region).v_sig_f / Geometry::getXSvRegion(current_region).sig_f;

    //How many neutrons do we produce?
    int n_new = int(std::abs(k_score) + RNG_GEN::rand());


    // Make all new particles
    for(int i = 0; i < n_new; i++){
        // Randomize direction
        double new_dir = 1 - 2 * RNG_GEN::rand();
        // Daughter particle has same weight as parent particle, same position, and is_alive=true, but different direction generated randomly
        Particle p_d{new_dir,
                    p.pos,
                    p.wgt,
                    true};
        // Save particle as fission particle.
        if (Tally::getTallyType()) {
            Bank::addParticle(p_d);
        }
        else {
            //std::cout << "Particle born" << std::endl;
            Bank::addNextPart(p_d);
        }
    }
}