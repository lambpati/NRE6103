#include "../include/bank.h"

//TESTING
#include <iostream>

void Bank::addParticle(Particle& p){
    mesh_bank.push_back(p);
}

void Bank::addNextPart(Particle& p){
    next_gen.push_back(p);
}

void Bank::initBanks() {
    mesh_bank.swap(next_gen);
    //mesh_bank = next_gen;
    //clear without references
    for (int i = next_gen.size(); i > 0; i--) {
        next_gen.pop_back();
    }
}

void Bank::killParticles(Particle& p){
    // pop front
    if (!mesh_bank.empty())
        mesh_bank.erase(mesh_bank.begin());
}

void Bank::createCDF(std::vector<Particle> mesh, double k_eff){
    sum = 0;
    double left = 0;
    for(auto& e: mesh){
        sum += e.pos;
        // Uniform CDF
        e.pos;
        // Normal CDF using error function
        // e.pos = 0.5 * std::erfc(-e.pos/std::sqrt(2));
    }
}

void Bank::setMesh(int i, Particle& p){
    mesh_bank.at(i) = p;
}

void Bank::setNextGen(int i, Particle& p){
    next_gen.at(i) = p;
}