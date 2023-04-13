#include "../include/bank.h"

//TESTING
#include <iostream>

void Bank::addParticle(Particle& p){
    mesh_bank.push_back(p);
}

void Bank::addPrev(Particle& p){
    prev_mesh.push_back(p);
}

void Bank::moveParticles(){
    //prev_mesh = mesh_bank;
    mesh_bank.clear();
}

void Bank::killParticles(Particle& p){
    // pop front
    assert(!mesh_bank.empty());
    mesh_bank.erase(mesh_bank.begin());
}