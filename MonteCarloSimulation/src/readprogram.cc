#include "../include/readprogram.h"

#include "../include/usercontrol.h"
#include "../include/tally.h"
#include "../include/boundaries.h"
#include "../include/geometry.h"

std::ifstream ReadProgram::file;
int ReadProgram::lineNum;
std::string ReadProgram::contents;

std::string c;
std::istringstream iss(c);
std::string keyword;
std::string value;

void ReadProgram::populateBoundaries(){
    // Ideally iterate twice to determine the boundary conditions of the file
    do{
        iss >> keyword;
        iss >> value;
        char g = value[0];

        if(keyword == "LEFT"){
            Boundaries::setLeft(g);
        }

        else if(keyword == "RIGHT"){
            Boundaries::setRight(g);
        }
    } while(keyword == "LEFT" || "RIGHT");

}

void ReadProgram::populateGeometry(){
    while (true) {
        double XS_Data[6];
        // Keyword is the region #
        iss >> keyword;
        int key = std::stoi(keyword);

        //Determine if there are no more digits (meaning it is a new section)
        char* p;
        std::strtod(keyword.c_str(), &p);
        if (*p == 0) {
            return;
        }

        // Populate the XS Data relevantly
        for (int i = 0; i < 6; i++) {
            iss >> c;
            XS_Data[i] = std::stod(c);
        }
        // Put into structure for easy access
        Geometry::setXS(XS_Data);
        Geometry::setGeometry(key);
    }
}
void ReadProgram::parseFile(){
    //Iterate through words
    iss >> keyword;
    if (keyword == "FLUX") {
        // Sets flux tally type to true
        Tally::setTallyType(true);
    }
    else if (keyword == "EIGEN") {
        //Sets flux tally type to false (eigen solution)
        Tally::setTallyType(false);
    }

    else if (keyword == "BOUNDARIES") {
        // Sets boundaries to vacuum or specular for left and right
        ReadProgram::populateBoundaries();
    }
    else if (keyword == "DATA") {
        // Determine geometry type + XS
        ReadProgram::populateGeometry();
    }
}

// Reads contents of a file specified by user
void ReadProgram::read(){
   file.exceptions(std::ifstream::badbit); //I dont see why to check for badbits
   try {
       // File read and write
       file.open(UserControl::getFileName());
       if (!file.is_open()) {
           throw std::ifstream::failure("Cannot find file");
       }
       while (!file.eof()) {
           file >> c;
           std::istringstream iss(c);
           ReadProgram::parseFile();
       }
       file.close();
   }
   catch(const std::ifstream::failure& e){
       std::cerr << e.what() << std::endl;
   }
}

