#include "../include/transporter.h"


//TESTING
#include <iostream>

void Transporter::initParticles(double dx){
    //Make new particle
    Particle p;
    // If flux fixed source problem
    if(Tally::getTallyType()){
        // Assumably we will only have one source, which for now is hardcoded in region 3, index 2
        current_region = Geometry::getRegion(2);
        // Derive p.pos from current region max and min and normalized random number
        p.pos = RNG::rand()*(Geometry::getXSvRegion(current_region).X_max-Geometry::getXSvRegion(current_region).X_min)+Geometry::getXSvRegion(current_region).X_min;
        //std::cout << p.pos << std::endl;
        // Derive p.dir from random number
        p.dir = RNG::rdir();
        //p.dir = 10-20*RNG::rand();
        // Set p.wgt to 1
        p.wgt = 1;
        // Set to is_alive = true
        p.is_alive = true;
    }
    // Else is eigenvalue problem
    else{

    }
    Bank::addParticle(p);
    //Transporter::moveParticle(p, dx);
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
        //   std::cout << "RHS " << p.is_alive << std::endl;
    }
    else{
        //std::cout << "in else" << std::endl;
        for(int i = 0; i < Geometry::getGeometry().size(); i++){
           // std::cout << "i is " << i << std::endl;
            if(Geometry::getXS(i).X_min < p.pos && p.pos < Geometry::getXS(i).X_max){
                current_region = i+1;
             //   std::cout << "current region is " << current_region << "(" << Geometry::getXS(i).X_min << "," << Geometry::getXS(i).X_max << ")" << std::endl;
                break;
            }
        }
    }
}

void Transporter::moveParticle(Particle& p, double dx){
    sigma_ts = dx;
    while(p.is_alive){
        double prev_pos = p.pos;
        //p.dir = 1 - 2 * RNG::rand();
       // std::cout << p.pos << " position " << p.dir << " dir " << std::endl;
        Transporter::determineMaterial(p);
        double sig_tot = Geometry::getXSvRegion(current_region).sig_s + Geometry::getXSvRegion(current_region).sig_a;
        if(p.is_alive){
            //std::cout << "sig_tot in region " << current_region << " is " << sig_tot << std::endl;
            if (sig_tot == 0.) {
                if(p.dir < 0.){
                    //current_region--;
                    p.pos = Geometry::getXSvRegion(current_region).X_min-1/dx;
                    //std::cout << "moving from  " << prev_pos << " to " << p.pos << std::endl;
                    break;
                }
                else{
                    //current_region++;
                    p.pos = Geometry::getXSvRegion(current_region).X_max+1/dx;
                    break;
                }
            }
            else {
                p.pos += -1/sig_tot * std::log(RNG::rand() + 1/dx)* p.dir;
              //  if((p.pos + 1/dx) >= Geometry::getXSvRegion(current_region).X_max) p.pos = Geometry::getXSvRegion(current_region).X_max + 10/dx;
            }
            // Please leave the region
                (p.pos <= Geometry::getXSvRegion(current_region).X_min && p.pos > Geometry::getMin()) ? (p.pos = Geometry::getXSvRegion(current_region-1).X_max - 1/dx) : 0;
                (p.pos >= Geometry::getXSvRegion(current_region).X_max && p.pos < Geometry::getMax()) ? (p.pos = Geometry::getXSvRegion(current_region+1).X_min + 1/dx) : 0;
            
            Transporter::determineMaterial(p);
            Tally::pathLengthTally(p.pos, prev_pos, p.dir, p.wgt);

            //std::cout << "moving from  " << prev_pos << " to " << p.pos << std::endl;
            // At this new location, does it experience a collision?
            Transporter::collision(p);
            Transporter::russianRoulette(p);
            // p.is_alive = false;
        }
    }

}

void Transporter::collision(Particle& p){
    Transporter::determineMaterial(p);
    if(!p.is_alive){
        return;
    }
    //std::cout << "coll particle dir " << p.dir << " particle pos " << p.pos << std::endl;
    //Tally::addColl(p.pos, p.wgt);
    double sig_tot = Geometry::getXSvRegion(current_region).sig_s + Geometry::getXSvRegion(current_region).sig_a;
    // Scattering probability = sig_s / sig_total
    double Pscatter = Geometry::getXSvRegion(current_region).sig_s / sig_tot;
    // Fission probability = sig_f/ sig_total
    double Pfission =  Pscatter + Geometry::getXSvRegion(current_region).sig_f/sig_tot;
    double Nfission =  Geometry::getXSvRegion(current_region).sig_f/sig_tot;
    // Capture probability = sig_a/ sig_total - Pfission
    double Pcapt = Geometry::getXSvRegion(current_region).sig_a/sig_tot; //- Pfission;

    double rand_p = RNG::rand();

    // Will it scatter?
    if(rand_p < Pscatter){
        Tally::accumulateColl(p.pos, p.wgt);
        //Tally::addColl(p.pos, p.wgt);
        //Bank::addParticle(p);
        //If scatter, just change direction
        p.dir = RNG::rdir();
       // std::cout << "scattering " << p.dir << std::endl;
    }
    else if(rand_p < Pfission){
        Tally::accumulateColl(p.pos, p.wgt);
        //Tally::addColl(p.pos, p.wgt);
        //Bank::addParticle(p);
        //Do fission
        Transporter::fissionNeutrons(p);
        p.wgt *= Nfission;
        //std::cout << "fissioning " << std::endl;
    }
    else if(rand_p < Pcapt){
        Tally::accumulateColl(p.pos, p.wgt);
        //Tally::addColl(p.pos, p.wgt);
        //Bank::addParticle(p);
        // Captured
        // Stuck here (for obvious reasons)
        p.wgt *= Pcapt;
       // std::cout << "captured " << std::endl;
    }
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
        double new_dir = RNG::rdir();
        // Daughter particle has same weight as parent particle, same position, and is_alive=true, but different direction generated randomly
        Particle p_d{new_dir,
                    p.pos,
                    p.wgt,
                    true};
        // Save particle as fission particle. Using banks to allow for threading in future
        Bank::addParticle(p_d);
        //Add to fission tally 
        //Tally::addFiss(p.pos);

        //Transporter::moveParticle(p_d, sigma_ts);
    }
}