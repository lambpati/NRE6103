#include "../include/boundaries.h"

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
    //If vaccuum boundary conditions are impinged, particle gets lost and thus dies
    p.wgt = 0.;
    p.is_alive = false;
    Bank::killParticles(p);
}

void Boundaries::determineBehavior(Particle& p, bool side){
    if(side && bounds.second){
        Boundaries::vaccuum(p);
    }
    else if(side && !bounds.second){
        Boundaries::reflect(p);
    }
    else if(!side && bounds.first) {
        Boundaries::vaccuum(p);
    }
    else{
        Boundaries::reflect(p);
    }
}