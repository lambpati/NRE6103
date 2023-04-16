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

int main(int argc, char const *argv[]){

    // TO DO add these parameters to a readable input form
    const int dx = 1000;
    const double particles = 1000000;//10000;
    const int batches = 100;
    const int inactive = 5;

    RNG_GEN::setSeed(896654);

    std::vector<double> k_eff;
    
    double Avg_K = NAN;
    
    unsigned long long timed=0;





    // Print intro to 1D solver
    UserControl::printIntro();

    // Get File name as a string
    std::string name;
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

    // Make particles
    for(int i = 0; i < particles; i++){
        //std::cout << "Adding particle " << i << std::endl;
       transporter.initParticles(dx,particles, i);
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

    for (int i = 0; i < batches; i++) {
       // std::cout << "On generation " << i << std::endl;
        k_eff.push_back((double)Bank::getNextBank().size() / (double)Bank::getMeshBank().size());
       // std::cout << "K is " << k_eff.back() << std::endl;
        Bank::initBanks();
        for (int j = 0; j < particles; j++) {
            // Choose  randomly from uniform distribution of fission particle bank to allow to propogate
            int index = std::floor(RNG_GEN::rand()*Bank::getMeshBank().size());
            Particle e = Bank::getMeshBank().at(index);
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
    WriteProgram::writeToStatistics(Tally::getMean(), Tally::getVariance());
    WriteProgram::writeToOutput(Tally::getFlux(), Avg_K);
    timed += t.seconds_elapsed();
    std::cout << "Finished Computation in " << timed << " seconds. Please look at the output.csv and statistics.csv files." << std::endl;

}
