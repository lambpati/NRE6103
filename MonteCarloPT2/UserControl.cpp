#include "UserControl.hpp"


std::string UserControl::fileName = "";

static void UserControl:printIntro(){
    std::cout << "Welcome to 1D Monte Carlo Solver by Patience Yockey." << std::endl;
    std::cout << "Please enter file name: " << std::endl; 
}

static void UserControl:setFileName(std::string fileName){
    // For debugging and pwd purposes
    char cwd[1024];
    chdir("/path/to/change/directory/to");
    getcwd(cwd, sizeof(cwd));
    printf("Current working dir: %s\n", cwd);

    std::cout << "Processing file " << fileName;
    start = clock::now();

}

static void UserControl::printOutro(){
    duration = clock::now() - start;
    std::cout << "Finished Computation in " << duration << " seconds. Please look at the output.txt file." << std::endl;
}