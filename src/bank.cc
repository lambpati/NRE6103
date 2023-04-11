#include "../include/bank.h"

//TESTING
#include <iostream>

void Bank::addParticle(Particle& p){
    mesh_bank.push_back(p);
}

void Bank::killParticles(Particle& p){
    size_t j = 0;
    mesh_bank.pop_back();
   // mesh_bank.erase(std::remove_if(mesh_bank.begin(), mesh_bank.end(), [](Particle& p){return (p.is_alive == false);}), mesh_bank.end());
    //std::cout << "Bank size is now " << mesh_bank.size() << std::endl;
}