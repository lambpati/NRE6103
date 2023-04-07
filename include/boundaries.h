#pragma once

#include <utility>

#include "../include/particle.h"

class Boundaries{
    private:
        // Left pair = left boundary condition
        // Determine if vacuum (true = vacuum), (false = specular);
        inline static std::pair<bool, bool> bounds;
        
        static void reflect(Particle& p);
        static void vaccuum(Particle& p);

    public:
        //Methods
        Boundaries() = default;
        // true = RHS, fale = LHS
        static void determineBehavior(Particle& p, bool side);

        //Getters
        static const std::pair<bool, bool> getBoundaries() { return bounds; };
        static const bool getLeft(){ return bounds.first; };
        static const bool getRight(){ return bounds.second; };

        //Setters
        static void setLeft(char l);
        static void setRight(char r);
};
