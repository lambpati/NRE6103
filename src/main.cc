#include <string>
#include <iostream>
#include <chrono>

#include "../include/readprogram.h"
#include "../include/usercontrol.h"
#include "../include/writeoutput.h"
#include "../include/tally.h"
#include "../include/transporter.h"

int main(int argc, char const *argv[]){

    // TO DO add these parameters to a readable input form
    const int dx = 100;
    const double particles = 1000000;


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

    Tally::makeMesh(dx, particles);

    // Make particles
    for(int i = 0; i < particles; i++){
        transporter.initParticles();
    }

    int cnt = 0;

    for(auto i : Bank::getMeshBank()){
        //std::cout << cnt++ << std::endl;
        transporter.moveParticle(i);
    }
    //Tally::calculateFlux(particles, dx);
    //Tally::pathLengthTally(particles, dx);
    auto end = std::chrono::high_resolution_clock::now();
    WriteProgram::writeToOutput(Tally::getRx(),Tally::getMesh());
    double elapsed_time = std::chrono::duration<double>(end-start).count();
    std::cout << "Finished Computation in " << elapsed_time << " seconds. Please look at the output.csv file." << std::endl;

}
