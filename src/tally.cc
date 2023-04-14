#include "../include/tally.h"

#include <iostream>

void Tally::makeMesh(int res){
    // Get width of each bin
    w = (Geometry::getMax()-Geometry::getMin())/res;
    for(int i=0; i <= res; i++){
        pathlengths.push_back(std::make_pair((w*i),0.));
    }
}

void Tally::pathLengthTally(double pos, double prev_pos, double dir, double weight, double particles) {
    double inc;
    double inc_2;
    double left_pos = std::min(prev_pos, pos);
    double rite_pos = std::max(prev_pos, pos);
    if(flux) {
        double dist = rite_pos - left_pos;
        inc = std::abs(weight / dir) / particles * Geometry::getXS(2).s *  (Geometry::getXS(2).X_max-Geometry::getXS(2).X_min);
        inc_2 = std::abs(weight / dir * dist / w) / particles * Geometry::getXS(2).s *  (Geometry::getXS(2).X_max-Geometry::getXS(2).X_min);
    }
    else{
        inc = 1;
        inc_2 = 1;
    }
    //std::cout << prev_pos << " to " << pos << ". Dir: " << dir << std::endl;

    // Normalize per bin / particle_count * source_strength * source_width

    for(int i = 0; i < pathlengths.size() - 1; i++){
        if(left_pos <= pathlengths.at(i).first && rite_pos >= pathlengths.at(i+1).first){
            pathlengths.at(i).second += inc; // / 1000000 * 50 * 5;
        }
        if (left_pos >= pathlengths.at(i).first && rite_pos <= pathlengths.at(i + 1).first) {
            pathlengths.at(i).second += inc_2;
        }
    }

}