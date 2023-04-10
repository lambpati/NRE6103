#include "../include/bank.h"

void Bank::addParticle(Particle& p){
    mesh_bank.push_back(p);
}

void Bank::killParticle(Particle& p){
    mesh_bank.erase(std::remove(mesh_bank.begin(),mesh_bank.end()))
}