#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <chrono>

#include "../include/readprogram.h"
#include "../include/usercontrol.h"
#include "../include/writeoutput.h"
#include "../include/tally.h"
#include "../include/transporter.h"
#include "../include/geometry.h"
#include "../include/rng_gen.h"
#include "../include/timer.h"
#include "../include/pertubation.h"

int main(int argc, char const *argv[]){

    // TODO Clean up main

    // TODO add these parameters to a readable input form
    const int dx = 1000;
    double particles;
    const int batches = 100;
    const int inactive = 20;

    RNG_GEN::setSeed(896654);

    std::vector<double> k_eff;
    
    double Avg_K = NAN;
    
    unsigned long long timed=0;


    // Print intro to 1D solver
    UserControl::printIntro();

    // Get File name as a string
    std::string name;double delta_in;
    std::cin >> name;
    UserControl::setFileName(name);

    ReadProgram readprogram;
    readprogram.read();
    WriteProgram::prettyPrintGeometry();
    WriteProgram::prettyPrintBoundaries();
    WriteProgram::prettyPrintTally();

    Transporter transporter;

    Tally::makeMesh(dx);

    std::cout << "System timestamp: " << __TIMESTAMP__ << std::endl;
    //std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    timer t;
    
    //Particles hardcoded for convienence
    if(Tally::getTallyType()){
        particles = 1000000;
    }
    else {
        particles = 10000;
    }
    
    // Make particles
    for(int i = 0; i < particles; i++){
        //std::cout << "Adding particle " << i << std::endl;
       transporter.initParticles(dx,particles);
    }
    std::cout << "Bank size: " << Bank::getMeshBank().size() << std::endl;

if(Tally::getTallyType()){
    while(!Bank::getMeshBank().empty()){
        for(auto& e : Bank::getMeshBank()){
            if (t.seconds_elapsed() % 30 == 0 && t.seconds_elapsed() != 0) {
                timed += t.seconds_elapsed();
                t.reset();
                std::cout << "Elapsed time: " << timed << " seconds." << std::endl;
            }
            transporter.moveParticle(e, dx, particles);
        }
        if (Bank::getMeshBank().size() == 1) {
            break;
        }
        //std::cout << "Bank size after: " << Bank::getMeshBank().size() << std::endl;
    }
}
else {
    for (auto& e : Bank::getMeshBank()) {
            if (t.seconds_elapsed() % 30 == 0 && t.seconds_elapsed() != 0) {
                timed += t.seconds_elapsed();
                t.reset();
                std::cout << "Elapsed time: " << timed << " seconds." << std::endl;
            }
        transporter.moveParticle(e, dx, particles);
    }
    //k_eff.push_back((double)Bank::getNextBank().size() / particles);

    for (int i = 0; i < batches; i++) {
       // std::cout << "On generation " << i << std::endl;
        k_eff.push_back((double)Bank::getNextBank().size() / Bank::getMeshBank().size());
        //k_eff.push_back((double)Bank::getNextBank().size() / (double)Bank::getMeshBank().size());
        //std::cout << "K is " << k_eff.back() << std::endl;
        Bank::initBanks();
        for (int j = 0; j < particles; j++) {
            // Choose  randomly from uniform distribution of fission particle bank to allow to propogate
            int index = RNG_GEN::rand()*particles;
            Particle e = Bank::getMeshBank().at(index);
            //std::cout << e.pos << std::endl;
            e.dir = 1 - 2 * RNG_GEN::rand();
            if (t.seconds_elapsed() % 30 == 0 && t.seconds_elapsed() != 0) {
                timed += t.seconds_elapsed();
                t.reset();
                std::cout << "Elapsed time: " << timed << " seconds." << std::endl;
            }
            transporter.moveParticle(e, dx, particles);
        }
    }
    for(int i = 0; i < inactive; i++){
        // Pop front inactive batches
        k_eff.erase(k_eff.begin());
    }
    // Average K_eff
    Avg_K = std::reduce(k_eff.begin(), k_eff.end())/k_eff.size();
    std::cout << "Calculated K_eff: " << Avg_K << std::endl;
}
    Tally::calculateFlux(dx);
    Tally::calculateMeanVariance(Tally::getFlux());
    WriteProgram::writeToStatistics(Tally::getPositions(), Tally::getMean(), Tally::getVariance());
    WriteProgram::writeToOutput(Tally::getFlux(), Avg_K);
    timed += t.seconds_elapsed();
    std::cout << "Finished Computation in " << timed << " seconds. Please look at the output.csv and statistics.csv files." << std::endl;
   
   //TODO Clean up pertubation
    if(!Tally::getTallyType()){
        double delta_in;
        std::cout << "Enter a change in the absorption cross section of material 3 (+/-) in decimal form (not percent): ";
        std::cin >> delta_in;
        t.reset();
        std::cout << "Calculating the pertubation result of " << (Geometry::getXS(2).sig_a+delta_in) << " sigma_a." << std::endl;
        double k_pert = Pertubation::calculatePertubation(delta_in,Avg_K);
        std::cout << "Perturbed K_eff is " << k_pert << std::endl;
        std::cout << "Finished Computation in " << t.seconds_elapsed() << " seconds." << std::endl;
    }

}
