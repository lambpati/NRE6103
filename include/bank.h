#pragma once

#include <vector>
#include <algorithm>
#include <cassert>
#include <iterator>
#include <numeric>
#include <cmath>

#include "../include/particle.h"

class Bank{
    private:
        // Particles alive
        inline static std::vector<Particle> mesh_bank;
        inline static std::vector<Particle> next_gen;
        inline static double sum;
    public:
        //Methods
        Bank() = default;

        static void addParticle(Particle& p);
        static void addNextPart(Particle& p);
        static void initBanks(int res);
        static void killParticles(Particle& p);
        static void createCDF(std::vector<Particle> mesh);
        //Getters
        static std::vector<Particle> getMeshBank(){return mesh_bank; };
        static double getSum(){ return sum; };
        //Setters
        static void setMesh(int i, Particle& p);
        static void setNextGen(int i, Particle& p);
        


};