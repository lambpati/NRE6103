#include "../include/bank.h"

//TESTING
#include <iostream>

void Bank::addParticle(Particle& p){
    mesh_bank.push_back(p);
}

void Bank::killParticles(Particle& p){
    // pop front
    if (!mesh_bank.empty())
        mesh_bank.erase(mesh_bank.begin());
}