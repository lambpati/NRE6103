#include "../include/tally.h"

#include <iostream>

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
    double left_pos = std::min(prev_pos, pos);
    double rite_pos = std::max(prev_pos, pos);
    //std::cout << prev_pos << " to " << pos << ". Dir: " << dir << std::endl;

    // Normalize per bin / particle_count * source_strength * source_width
    double dist = rite_pos - left_pos;

    for(int i = 0; i < pathlengths.size() - 1; i++){
        if(left_pos <= pathlengths.at(i).first && rite_pos >= pathlengths.at(i+1).first){
            pathlengths.at(i).second += std::abs(weight / dir); // / 1000000 * 50 * 5;
        }
        if (left_pos >= pathlengths.at(i).first && rite_pos <= pathlengths.at(i + 1).first) {
            pathlengths.at(i).second += std::abs(weight / dir * dist / w);
        }
    }

}