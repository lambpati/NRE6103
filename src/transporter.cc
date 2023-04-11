#include "../include/transporter.h"


#include <iostream>

void Transporter::initParticles(){
    //Make new particle
    Particle p;
    // If flux fixed source problem
    if(Tally::getTallyType()){
        // Assumably we will only have one source, which for now is hardcoded in region 3, index 2
        current_region = Geometry::getRegion(2);
        // Derive p.pos from current region max and min and normalized random number
        p.pos = RNG::rand()*(Geometry::getXSvRegion(current_region).X_max-Geometry::getXSvRegion(current_region).X_min)+Geometry::getXSvRegion(current_region).X_min;
        // Derive p.dir from random number
        p.dir = 1 - 2 * RNG::rand();
        // Set p.wgt to 1
        p.wgt = 1;
        // Set to is_alive = true
        p.is_alive = true;
    }
    // Else is eigenvalue problem
    else{
        //current_region = Geometry::getRegion(2);
        throw;
    }
    Bank::addParticle(p);
}
void Transporter::russianRoulette(Particle& p){
    //Roulettes weight of the particle 
    if (p.wgt < weight_cutoff) {
        // double P_kill = 1.0 - (p.wgt / survive_weight);
        if (RNG::rand() > weight_cutoff) {
            //Lost the game of Russian Roulette
            p.wgt = 0.;
            p.is_alive = false;
            Bank::killParticles(p);
        }
        else {
            //Survived another day
            //Multiply existing survive_weight (10) p.wgt = p.wgt(10)
           // p.wgt = std::copysign(survive_weight, p.wgt);
            p.wgt *= 1/weight_cutoff;
        }
    }
}

void Transporter::determineMaterial(Particle& p, int i){
    // REMEMBER i starts at 1
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
        Transporter::determineMaterial(p, i-1);
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

void Transporter::moveParticle(Particle& p){
    int cnt = 0;
    while(p.is_alive){
        if (cnt++ > 10000) {
            std::cout << p.pos << " is stuck" << std::endl;
            throw;
        }

        double prev_pos = p.pos;
        //p.dir = 1 - 2 * (RNG::rand());
        Transporter::determineMaterial(p, current_region);
        double sig_tot = Geometry::getXSvRegion(current_region).sig_s + Geometry::getXSvRegion(current_region).sig_a;
        if (sig_tot == 0) {
            p.pos = p.dir > 0 ? Geometry::getXSvRegion(current_region).X_max +0.01: Geometry::getXSvRegion(current_region).X_min-0.01;
        }
        else {
            p.pos += 1/sig_tot * std::log(RNG::rand() + sigma_t) * p.dir;
        }
        //Tally::addTrac(p.pos, p.dir, p.wgt);
        Tally::pathLengthTally(p.pos, prev_pos, p.dir, p.wgt);
        int new_region = current_region;
        Transporter::determineMaterial(p, new_region);
        if (current_region != new_region) continue;
        // At this new location, does it experience a collision?
        Transporter::collision(p);
       // p.is_alive = false;
    }

}

void Transporter::collision(Particle& p){
    Transporter::determineMaterial(p, current_region);
    if(!p.is_alive){
        return;
    }
    //Tally::addColl(p.pos, p.wgt);
    double sig_tot = Geometry::getXSvRegion(current_region).sig_s + Geometry::getXSvRegion(current_region).sig_a;
    // Scattering probability = sig_s / sig_total
    double Pscatter = Geometry::getXSvRegion(current_region).sig_s / sig_tot;
    // Fission probability = sig_f/ sig_total
    double Pfission = Pscatter + Geometry::getXSvRegion(current_region).sig_f/sig_tot;
    // Capture probability = sig_a/ sig_total - Pfission
    double Pcapt = Geometry::getXSvRegion(current_region).sig_a/sig_tot - Pfission;
   
    double rand_val = RNG::rand();

    // Will it scatter?
    if(rand_val < Pscatter){
        //Tally::addColl(p.pos, p.wgt);
        //If scatter, just change direction
        double new_dir = 1 - 2 * (RNG::rand());
        p.dir = new_dir;
    }
    else if(rand_val < Pfission){
        //Tally::addColl(p.pos, p.wgt);
        //Do fission
        //Transporter::fissionNeutrons(p);
        p.wgt *= 1-(Pfission - Pscatter);
    }
    else {
        //Tally::addColl(p.pos, p.wgt);
        // Captured
        p.wgt *= 1-Pcapt;

        // Sample RNG once to determine if scattering vs absorption and then distinguish between capture and fission
    }

    Transporter::russianRoulette(p);
}

void Transporter::fissionNeutrons(Particle& p){
    double sig_tot = Geometry::getXSvRegion(current_region).sig_s + Geometry::getXSvRegion(current_region).sig_a;
    //Determine weighted k_score according to particle to determine if particle produces something
    // double k_score = p.wgt * Geometry::getXSvRegion(current_region).v_sig_f / sig_tot;
    double k_score = p.wgt * Geometry::getXSvRegion(current_region).v_sig_f / Geometry::getXSvRegion(current_region).sig_f;

    //How many neutrons do we produce?
    int n_new = 0;
    // Is a flux based fixed source problem
    if(Tally::getTallyType()){
        n_new = int(std::abs(k_score) + RNG::rand());
    }
    // Else is a eigenvalue problem
    else{

    }

    // Make all new particles
    for(int i = 0; i < n_new; i++){
        // Randomize direction
        double new_dir = 1 - 2 * (RNG::rand());
        // Daughter particle has same weight as parent particle, same position, and is_alive=true, but different direction generated randomly
        Particle p_d{new_dir,
                    p.pos,
                    p.wgt,
                    true};
        // Save particle as fission particle. Using banks to allow for threading in future
        Bank::addParticle(p_d);
        //Add to fission tally 
        Tally::addFiss(p.pos);

        Transporter::moveParticle(p_d);
    }
}