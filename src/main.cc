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

int main(int argc, char const *argv[]){

    // TO DO add these parameters to a readable input form
    const int dx = 1000;
    const double particles = 100;
    const int batches = 100;
    const int inactive = 5;

    RNG_GEN::setSeed(896654);

    std::vector<double> k_eff;





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
    auto start = std::chrono::high_resolution_clock::now();

    // Make particles
    for(int i = 0; i < particles; i++){
        //std::cout << "Adding particle " << i << std::endl;
       transporter.initParticles(dx,particles, i);
    }
    std::cout << "Bank size: " << Bank::getMeshBank().size() << std::endl;

if(Tally::getTallyType()){
    int cnt = 0;
    while(!Bank::getMeshBank().empty()){
        for(auto& e : Bank::getMeshBank()){
            if (++cnt % 10000 == 0) {
                auto end = std::chrono::high_resolution_clock::now();
                double elapsed_time = std::chrono::duration<double>(end - start).count();
                std::cout << "Elapsed time: " << elapsed_time << " seconds." << std::endl;
            }
            transporter.moveParticle(e, dx, particles);
        }
        if (Bank::getMeshBank().size() == 1) {
            break;
        }
        std::cout << "Bank size after: " << Bank::getMeshBank().size() << std::endl;
        Tally::getMeanVariance(Tally::getPathlengths());
    }
    WriteProgram::writeToOutput(Tally::getPathlengths());
}
else {
    //Bank::createCDF(Bank::getMeshBank());
    //TODO Continue
    int cnt = 0;
    int v = 0;
    for (auto& e : Bank::getMeshBank()) {
        if (++cnt % 1000 == 0) {
            auto end = std::chrono::high_resolution_clock::now();
            double elapsed_time = std::chrono::duration<double>(end - start).count();
            std::cout << "Elapsed time: " << elapsed_time << " seconds." << std::endl;
        }
        transporter.moveParticle(e, dx, particles);
        //std::cout << "Moving particle " << e.pos << std::endl;
        //std::cout << "Next Bank size: " << Bank::getNextBank().size() << std::endl;
    }

    for (int i = 0; i < batches; i++) {
        std::cout << "Bank size after: " << Bank::getMeshBank().size() << std::endl;
        std::cout << "Next Bank size: " << Bank::getNextBank().size() << std::endl;
        k_eff.push_back(Bank::getNextBank().size() / Bank::getMeshBank().size());
        std::cout << "K_eff: " << k_eff.back() << std::endl;
        Bank::initBanks();
        //std::cout << "Next Bank size: " << Bank::getNextBank().size() << std::endl;
        //std::cout << "Current Bank size: " << Bank::getMeshBank().size() << std::endl;
        for (auto& e : Bank::getMeshBank()) {
            //double sim = std::floor(1. / k_eff.back() * RNG_GEN::rand());
            //std::cout << "sim " << sim << std::endl;
            //for (int j = 0; j < sim; j++) {
                //Particle p = e;
                //p.dir = 1 - 2 * RNG_GEN::rand();
                transporter.moveParticle(e, dx, particles);
            //}
        }
    }
}
    auto end = std::chrono::high_resolution_clock::now();
    double elapsed_time = std::chrono::duration<double>(end-start).count();
    std::cout << "Finished Computation in " << elapsed_time << " seconds. Please look at the output.csv file." << std::endl;

}
