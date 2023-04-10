#pragma once

#include <vector>

#include "../include/particle.h"

class Bank{
    private:
        // Particles alive
        inline static std::vector<Particle> mesh_bank;

    public:
        //Methods
        Bank() = default;

        static void addParticle(Particle& p);
        static void killParticle(Particle& p);
        //Getters

        //Setters
        


};