#include "../include/tally.h"

void Tally::makeMesh(int res){
    // Get width of each bin
    w = (Geometry::getMax()-Geometry::getMin())/res;
    for(int i=0; i <= res; i++){
        mesh.push_back(w*i);
        collisions.push_back(std::make_pair((w*i),0.));
        pathlengths.push_back(std::make_pair((w*i),0.));
    }
}

void Tally::addColl(double pos, double weight){
   double val;
    if(flux){
        for(int i = 0; i < mesh.size(); i++){
            // Tally simulat to MGMC collision_mesh_tally.cpp line 58-64 tallying weight instead and evaluating on position
           if(mesh.at(i) <= pos && pos <= mesh.at(i+1)){
                coll_tally.at(i) += weight;
                break;
           }
        }
    }
    else{

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

void Tally::calculateFlux(double pos, int i){
}

void Tally::accumulateColl(double pos, double weight){
    for(int i = 0; i < collisions.size(); i++){
        if(collisions.at(i).first <= pos && pos <= collisions.at(i+1).first){
            collisions.at(i).second += weight;
        }
    }

}

void Tally::pathLengthTally(double pos, double prev_pos, double dir, double weight) {
    for(int i = 0; i < pathlengths.size(); i++){
        if(pathlengths.at(i).first <= pos && pos <= pathlengths.at(i+1).first){
            pathlengths.at(i).second += weight*(pos-prev_pos);
        }
    }

}