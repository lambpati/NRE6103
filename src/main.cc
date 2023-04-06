#include <string>
#include <iostream>
#include <chrono>

#include "../include/readprogram.h"
#include "../include/usercontrol.h"
#include "../include/writeoutput.h"

int main(int argc, char const *argv[]){
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
    const std::chrono::duration<double> duration = std::chrono::system_clock::now() - start;


}
