#include "../include/tally.h"

void Tally:makeMesh(int res){
    fiss_tally.resize(res);
    coll_tally.resize(res);

    std::fill(fiss_tally.begin(), fiss_tally.end(), 0);
    std::fill(coll_tally.begin(), coll_tally.end(), 0);
}

int Tally::determineBin(double pos){
    
}

void Tally::addColl(double pos, double weight=1){
    if(flux){
     // If fixed source, collision tally is a sum of weights
        coll_tally.at(pos) += weight;   
    }
    else{
     // Else collision tallies are only summed by +1
        coll_tally.at(pos) += 1;
    }
}

void Tally::addFiss(double pos){
    //Get the X_min and X_max of global, divide by resolution
    // Determine the increments 
    if(p.pos <)
}