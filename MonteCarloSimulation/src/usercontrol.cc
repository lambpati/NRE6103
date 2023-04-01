#include "../include/usercontrol.h"

#include<unistd.h>


std::string UserControl::fileName = "";

void UserControl::printIntro(){
    std::cout << "Welcome to 1D Monte Carlo Solver by Patience Yockey." << std::endl;
    std::cout << "Please enter file name: " << std::endl; 
}

void UserControl::setFileName(std::string fileName){
    // For debugging and pwd purposes
    char cwd[1024];
    chdir("/path/to/change/directory/to");
    getcwd(cwd, sizeof(cwd));
    printf("Current working dir: %s\n", cwd);
    std::cout << "Processing file " << fileName;

}

void UserControl::printOutro(std::chrono::duration<double> d){
    //std::cout << "Finished Computation in " << d << " seconds. Please look at the output.txt file." << std::endl;
}
