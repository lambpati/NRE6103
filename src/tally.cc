#include "../include/tally.h"

void Tally::makeMesh(int res){
    fiss_tally.resize(res+1);
    coll_tally.resize(res+1);
    std::fill(fiss_tally.begin(), fiss_tally.end(), 0);
    std::fill(coll_tally.begin(), coll_tally.end(), 0);
    Tally::determineBin(res);
    for(int i=0; i <= res; i++){
        mesh.push_back(w*i);
    }
}

void Tally::determineBin(int bins){
    double bin = (double) bins;
    // Get width of each bin
    w = (Geometry::getMax()-Geometry::getMin())/bin;
}

void Tally::addColl(double pos, double weight, int i){
    //recursively find bin   
    if(pos >= w*i && pos <= w*(i+1)){
        if(flux){
     // If fixed source, collision tally is a sum of weights
            coll_tally.at(i) += weight; 
        }
        else{
        // Else collision tallies are only summed by +1
            coll_tally.at(i) += 1;

        }
    }
    else{
        Tally::addColl(pos, weight, i+1);
    }
    
}

void Tally::addFiss(double pos){
    //Get the X_min and X_max of global, divide by resolution
    // Determine the increments
}