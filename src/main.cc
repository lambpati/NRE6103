#include <string>
#include <iostream>
#include <chrono>

#include "../include/readprogram.h"
#include "../include/usercontrol.h"
#include "../include/writeoutput.h"
#include "../include/tally.h"
#include "../include/transporter.h"
#include "../include/geometry.h"

int main(int argc, char const *argv[]){

    // TO DO add these parameters to a readable input form
    const int dx = 1000;
    const double particles = 100000;


    // Print intro to 1D solver
    UserControl::printIntro();

    // Get File name as a string
    std::string name;
    std::cin >> name;
    UserControl::setFileName(name);
    auto start = std::chrono::high_resolution_clock::now();
    ReadProgram readprogram;
    readprogram.read();
    WriteProgram::prettyPrintGeometry();
    WriteProgram::prettyPrintBoundaries();
    WriteProgram::prettyPrintTally();

    Transporter transporter;

    Tally::makeMesh(dx);

    // Make particles
    for(int i = 0; i < particles; i++){
       transporter.initParticles(dx);
    }
    std::cout << "Bank size: " << Bank::getMeshBank().size() << std::endl;
    while(!Bank::getMeshBank().empty()){
        for(auto e : Bank::getMeshBank()){
        //std::cout << cnt++ << std::endl;
            transporter.moveParticle(e, dx);
        }
        std::cout << "Bank size after: " << Bank::getMeshBank().size() << std::endl;
    }

    //Tally::calculateFlux(particles, dx);
    auto end = std::chrono::high_resolution_clock::now();
    //WriteProgram::writeToOutput(Tally::getPathlengths());
    WriteProgram::writeToOutput(Tally::getCollisions());
    //WriteProgram::writeToOutput(Tally::getCollTally(),Tally::getMesh());
    double elapsed_time = std::chrono::duration<double>(end-start).count();
    std::cout << "Finished Computation in " << elapsed_time << " seconds. Please look at the output.csv file." << std::endl;

}
