#include "ReadProgram.hpp"
#include "UserControl.hpp"

#include <string>
#include <iostream>

int main(int argc, char const *argv[]){
    // Print intro to 1D solver
    UserControl::printIntro();

    // Get File name as a string
    std::string name;
    std::cin >> name;
    UserControl::processFile(name);
    ReadProgram::read();

}
