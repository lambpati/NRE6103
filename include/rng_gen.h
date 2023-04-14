#pragma once

#include <random>

class RNG_GEN {
    private:
       inline static uint32_t  seed;
    public:
        RNG_GEN() = default;

        static void setSeed(uint32_t s) { seed = s; };

        static double rand() { 
            static std::random_device rd;  // Will be used to obtain a seed for the random number engine
            static std::mt19937 gen(seed); // Standard mersenne_twister_engine seeded with rd()
            static std::uniform_real_distribution<> dist(0.0, 1.0);
            return dist(gen);
        };

};