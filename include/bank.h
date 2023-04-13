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
        inline static std::vector<Particle> prev_mesh;
    public:
        //Methods
        Bank() = default;

        static void addParticle(Particle& p);
        static void moveParticles();
        static void addPrev(Particle& p);
        static void killParticles(Particle& p);
        static void killPrev(Particle& p);
        //Getters
        static const std::vector<Particle> getMeshBank(){return mesh_bank; };
        //Setters
        


};