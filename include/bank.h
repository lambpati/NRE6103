#pragma once

#include <vector>
#include <algorithm>
#include <cassert>
#include <iterator>

#include "../include/particle.h"

class Bank{
    private:
        // Particles alive
        inline static std::vector<Particle> mesh_bank;
    public:
        //Methods
        Bank() = default;

        static void addParticle(Particle& p);
        static void killParticles(Particle& p);
        //Getters
        static const std::vector<Particle> getMeshBank(){return mesh_bank; };
        //Setters
        


};