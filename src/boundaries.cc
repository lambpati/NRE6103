#include "../include/boundaries.h"

#include <iostream>

void Boundaries::setLeft(char l){
      if(l == 'V'){
        bounds.first = true;
    }
    else{
        bounds.first = false;
    }
}

void Boundaries::setRight(char r){
      if(r == 'V'){
        bounds.second = true;
    }
    else{
        bounds.second = false;
    }
}

void Boundaries::reflect(Particle& p){
    //If specular boundary conditions are impinged, change direction to the negative direction
     p.dir = -1*p.dir;
}

void Boundaries::vaccuum(Particle& p){
    if (Tally::getTallyType()) {
        p.wgt = 0.;
        Bank::killParticles(p);

    }
    //If vaccuum boundary conditions are impinged, particle gets lost and thus dies
    p.is_alive = false;
}

void Boundaries::determineBehavior(Particle& p, bool side){
    if(side && bounds.second){
      //  std::cout << "Vaccuum RHS" << std::endl;
        Boundaries::vaccuum(p);
    }
    else if(side && !bounds.second){
     //   std::cout << "Reflecting RHS" << std::endl;
        Boundaries::reflect(p);
    }
    else if(!side && bounds.first) {
       // std::cout << "Vaccuum LHS" << std::endl;
        Boundaries::vaccuum(p);
    }
    else{
      //  std::cout << "Reflect LHS" << std::endl;
        Boundaries::reflect(p);
    }
}