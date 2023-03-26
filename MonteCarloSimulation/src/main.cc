#include <string>
#include <iostream>

#include "src/readprogram.h"
#include "src/usercontrol.h"

int main(int argc, char const *argv[]){
    // Print intro to 1D solver
    UserControl::printIntro();

    // Get File name as a string
    std::string name;
    std::cin >> name;
    UserControl::processFile(name);
    ReadProgram::read();

}
