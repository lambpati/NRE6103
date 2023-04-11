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
    const int dx = 1000;
    const double particles = 10000000;


    // Print intro to 1D solver
    UserControl::printIntro();

    // Get File name as a string
    std::string name;
    std::cin >> name;
    UserControl::setFileName(name);
    const std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
    ReadProgram readprogram;
    readprogram.read();
    WriteProgram::prettyPrintGeometry();
    WriteProgram::prettyPrintBoundaries();
    WriteProgram::prettyPrintTally();

    Transporter transporter;

    Tally::makeMesh(dx);

    // Make particles
    for(int i = 0; i < particles; i++){
        transporter.initParticles();
    }

    //TESTING
    for(auto i : Bank::getMeshBank()){
        transporter.moveParticle(i);
    }
    const std::chrono::duration<double> duration = std::chrono::system_clock::now() - start;

    WriteProgram::writeToOutput(Tally::getCollTally(),Tally::getMesh());


}
