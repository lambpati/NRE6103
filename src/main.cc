#include <string>
#include <iostream>
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
    const double particles = 1000000;
    const int batches = 100;
    const int inactive = 5;
    RNG_GEN::setSeed(896654);




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
       transporter.initParticles(dx,i);
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
    }
    WriteProgram::writeToOutput(Tally::getPathlengths());
}
else{
    Bank::createCDF(Bank::getMeshBank());
    //TODO Continue
}
    auto end = std::chrono::high_resolution_clock::now();
    double elapsed_time = std::chrono::duration<double>(end-start).count();
    std::cout << "Finished Computation in " << elapsed_time << " seconds. Please look at the output.csv file." << std::endl;

}
