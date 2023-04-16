#include "../include/tally.h"

#include <iostream>

void Tally::makeMesh(int res){
    // Get width of each bin
    w = (Geometry::getMax()-Geometry::getMin())/res;
    for(int i=0; i <= res; i++){
        pathlengths.push_back(std::make_pair((w*i),0.));
    }
}

void Tally::pathLengthTally(double pos, double prev_pos, double dir, double weight, double particles, double sig_tot) {
    double inc = 0;
    double inc_2 = 0;
    double left_pos = std::min(prev_pos, pos);
    double rite_pos = std::max(prev_pos, pos);
    double dist = rite_pos - left_pos;

    for(int i = 0; i < pathlengths.size() - 1; i++){
        // If particle starts in i-1 region and ends in i+1 region, tally where tracklength = w(i+1)-w(i) (canceling with the w)
        if(left_pos <= pathlengths.at(i).first && rite_pos >= pathlengths.at(i+1).first){
            pathlengths.at(i).second += std::abs(weight/dir)/(particles); // / 1000000 * 50 * 5;
        }
        //If particle moves from in region i-1 to within region i, tracklength = rite_pos-w(i)
        else if(left_pos < pathlengths.at(i).first && rite_pos > pathlengths.at(i).first && rite_pos < pathlengths.at(i+1).first){
            pathlengths.at(i).second += std::abs(weight/dir*(rite_pos-w*i))/(w * particles);
        }
        //If particle mobves from within region i to within i+1, tracklength = w(i+1)-left_pos
        else if(left_pos > pathlengths.at(i).first && left_pos < pathlengths.at(i+1).first && rite_pos > pathlengths.at(i+1).first){
            pathlengths.at(i).second += std::abs(weight/dir*(w*(i+1)-left_pos))/(w * particles);
        }
        // If particle moves within bounds of tally, tally by taking the distance into consideration
        else if (left_pos >= pathlengths.at(i).first && rite_pos <= pathlengths.at(i + 1).first) {
            pathlengths.at(i).second += std::abs(weight/dir*dist)/(w * particles);
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


void Tally::calculateFlux(int res){
    double pos = 0;
    double sig_to = 0;
    double reg = 0;
    Transporter transporter;
    for(auto& e: pathlengths){
        reg = transporter.determineMaterial(e.second);
        sig_to = Geometry::getXSvRegion(reg).sig_s + Geometry::getXSvRegion(reg).sig_a;
        if(flux){
            flux_vec.push_back(std::make_pair(e.first, (e.second/sig_to*50*res/(Geometry::getMax()-Geometry::getMin()))));
        }
        else{
            flux_vec.push_back(std::make_pair(e.first, (e.second/sig_to/(Geometry::getMax()-Geometry::getMin()))));
        }
    }

}