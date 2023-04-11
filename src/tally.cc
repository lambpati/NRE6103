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

// Copied from transporter to be used here for convience in flux caluclations
void Tally::determineMaterial(double pos, int i){
    // REMEMBER i starts at 1
    // Check to make sure particle position is within i'th region bounds (Region = index + 1)
    if(pos < Geometry::getXSvRegion(i).X_max && pos >= Geometry::getXSvRegion(i).X_min){
        reg = Geometry::getRegion(i-1);
        return;
    }
    // If out of i'th region, iterate + 1 to find correct region
    else if(pos >= Geometry::getXSvRegion(i).X_max && pos < Geometry::getMax()){
        Tally::determineMaterial(pos, i+1);
    }
    // If before i'th region, iterate - 1 to find correct region
    else if(pos < Geometry::getXSvRegion(i).X_min && pos > Geometry::getMin()){
        Tally::determineMaterial(pos, i-1);
    }
    else{
        if(pos == Geometry::getMin()){
            reg = 1;
            return;
        }
        else{
            reg = Geometry::getRegion(Geometry::getGeometry().size()-1);
            return;
        }
    }
}

void Tally::calculateFlux(double particles, int bins){
    if(flux){
        for(int i = 0; i < mesh.size(); i++){
            double pos = w*i;
            double collisions = coll_tally.at(i)/particles;
            rx_rate.push_back(collisions);
            Tally::determineMaterial(pos,1);
            double sig_tot = Geometry::getXSvRegion(reg).sig_s + Geometry::getXSvRegion(reg).sig_a;
            // Hardcoded region 3
            double source = Geometry::getXSvRegion(3).s;
            flux_rate.push_back(collisions*sig_tot*bins);
        }
    }
    else{

    }
} 