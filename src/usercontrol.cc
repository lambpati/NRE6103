#include "../include/usercontrol.h"



std::string UserControl::fileName = "";

void UserControl::printIntro(){
    std::cout << "Welcome to 1D Monte Carlo Solver by Patience Yockey." << std::endl;

    std::filesystem::path cpath = std::filesystem::current_path();
 
    std::filesystem::current_path(correct_path);
    cpath = std::filesystem::current_path();
    std::string stringpath = cpath.generic_string();
    std::cout << "Current directory: " << cpath << std::endl;
    std::cout << "Please enter file name: " << std::endl; 
}

void UserControl::setFileName(std::string f){
    fileName = f;
    std::filesystem::path cpath = std::filesystem::current_path();
    std::string stringpath = cpath.generic_string();
    std::cout << "Processing file " << fileName << " in " << cpath << std::endl;

}