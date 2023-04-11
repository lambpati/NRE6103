#include "../include/tally.h"


//Testing 
#include <iostream>

void Tally::makeMesh(int res, double particles){
    fiss_tally.resize(res+1);
    coll_tally.resize(res+1);
    rx_rate.resize(res + 1);
    trac_length.resize(res+1);
    std::fill(fiss_tally.begin(), fiss_tally.end(), 0);
    std::fill(coll_tally.begin(), coll_tally.end(), 0);
    std::fill(trac_length.begin(), trac_length.end(), 0);
    std::fill(rx_rate.begin(), rx_rate.end(), 0);
    Tally::determineBin(res);
    for(int i=0; i <= res; i++){
        mesh.push_back(w * i);
    }
    saved_res = res;
    saved_particles = particles;
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

void Tally::addTrac(double pos, double dir, double weight, int i) {
    for (int i = 0; i < mesh.size(); i++) {
        if (pos >= w * i && pos <= w * (i + 1)) {
            if (flux) {
                double val = w / dir * weight;
                // If fixed source, collision tally is a sum of weights
                trac_length.at(i) += val;
            }
            else {
                // Else collision tallies are only summed by +1
                trac_length.at(i) += 1;
            }
        }
    }
}

void Tally::addFiss(double pos){
    //Get the X_min and X_max of global, divide by resolution
    // Determine the increments
}

// Copied from transporter to be used here for convience in flux caluclations
void Tally::determineMaterial(double pos, int i){
    // REMEMBER i starts at 1
    // Check to make sure position is within i'th region bounds (Region = index + 1)
    std::cout << reg << " current region" << std::endl;
    if(pos < Geometry::getXSvRegion(i).X_max && pos >= Geometry::getXSvRegion(i).X_min){
        reg = Geometry::getRegion(i-1);
        return;
    }
    // If out of i'th region, iterate + 1 to find correct region
    else if(pos >= Geometry::getXSvRegion(i).X_max && pos < Geometry::getMax()){
        std::cout << reg+1 << " iterating up region" << std::endl;
        Tally::determineMaterial(pos, i+1);
    }
    // If before i'th region, iterate - 1 to find correct region
    else if(pos < Geometry::getXSvRegion(i).X_min && pos > Geometry::getMin()){
        std::cout << reg-1 << " iterating down region" << std::endl;
        Tally::determineMaterial(pos, i-1);
    }
    else{
        if(pos <= Geometry::getMin()){
            reg = 1;
            return;
        }
        else{
            reg = Geometry::getRegion(Geometry::getGeometry().size()-1);
            return;
        }
    }
}

void Tally::pathLengthTally(double pos, double prev_pos, double dir, double weight) {
    if (flux) {
        for (int i = 0; i < mesh.size(); i++) {
            double left_edge = w * i, right_edge = w * (i + 1);
            double val = w / std::abs(dir) * weight;
            //std::cout << pos << " position" << std::endl;
            // rx_rate = 1/(W*particles) *Sum weights_i
           // double collisions = coll_tally.at(i) / particles;
            //double tracks = val / saved_particles;
            if (pos < left_edge || prev_pos >= right_edge) continue;
            rx_rate.at(i) += 1;

            // Change to path length
            //Account for source
        }
    }

}