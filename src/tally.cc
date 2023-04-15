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
        // Normalize per bin / particle_count * source_strength * source_width 
        // Offset for center bit
        double dist = rite_pos - left_pos;
        inc = std::abs(weight / dir) / particles * Geometry::getXS(2).s *  (Geometry::getXS(2).X_max-Geometry::getXS(2).X_min);
        inc_2 = std::abs(weight / dir * dist / w) / particles * Geometry::getXS(2).s *  (Geometry::getXS(2).X_max-Geometry::getXS(2).X_min) * 2;
    }
    else{
        // Normalize per bin / particle_count * geometry_range * types of materials
        // Offset for center bit
        double dist = rite_pos - left_pos;
        inc = std::abs(1 / dir) / (particles* Geometry::getMax()-Geometry::getMin() * 3); 
        inc_2 = std::abs(1 / dir * dist) / (particles* Geometry::getMax()-Geometry::getMin() * w * 6);
        // inc = std::abs(1 / dir) / (particles * 6 * 2 *(Geometry::getXS(2).X_max-Geometry::getXS(2).X_min));
        // inc_2 = std::abs(1 / dir * dist / w) / (particles *  6 * 2 * (Geometry::getXS(2).X_max-Geometry::getXS(2).X_min) * 2);
    }
    //std::cout << prev_pos << " to " << pos << ". Dir: " << dir << std::endl;

    for(int i = 0; i < pathlengths.size() - 1; i++){
        if(left_pos <= pathlengths.at(i).first && rite_pos >= pathlengths.at(i+1).first){
            pathlengths.at(i).second += inc; // / 1000000 * 50 * 5;
        }
        if (left_pos >= pathlengths.at(i).first && rite_pos <= pathlengths.at(i + 1).first) {
            pathlengths.at(i).second += inc_2;
        }
    }

}

void Tally::calculateMeanVariance(const std::vector<std::pair<double, double>>& vect) {
    double mean = 0, M2 = 0, variance = 0;
    for (size_t i = 0; i < vect.size(); ++i) {
        double delta = vect.at(i).second - mean;
        mean += delta / (i + 1);
        M2 += delta * (vect.at(i).second - mean);
        variance = M2 / (i + 1);
        if (i >= 2) {
            
        }
    }
    mean_flux.push_back(mean);
    std_dev.push_back(variance);
}