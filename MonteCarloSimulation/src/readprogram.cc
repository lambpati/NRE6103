#include "../include/readprogram.h"


std::ifstream ReadProgram::file;
int ReadProgram::lineNum;
std::string ReadProgram::contents;
//std::string keyword;
std::string value;

void ReadProgram::populateBoundaries(){
    // Ideally iterate twice to determine the boundary conditions of the file
    do{
        file >> keyword;
        file >> value;
        char g = value[0];

        if(keyword == "LEFT"){
            Boundaries::setLeft(g);
        }

        else if(keyword == "RIGHT"){
            Boundaries::setRight(g);
        }
        else {
            break;
        }
    } while(keyword == "LEFT" || "RIGHT");

}

void ReadProgram::populateGeometry(){
    while (file >> keyword) {
        double XS_Data[6];
        // Keyword is the region #
        int hkey = std::stoi(keyword);
        // Make sure its only numeric values
        if (keyword.find_first_of("0123456789") != std::string::npos) {
            file >> keyword;
            // Populate the XS Data relevantly
            for (int i = 0; i < 6; i++) {
                file >> keyword;
                XS_Data[i] = std::stod(keyword);
            }
            // Put into structure for easy access
            Geometry::setXS(XS_Data);
            Geometry::setGeometry(hkey);
        }
        else { 
            break;
        }
    }
}
void ReadProgram::parseFile(){
    //Iterate through words
    file >> keyword;
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
           ReadProgram::parseFile();
       }
       file.close();
   }
   catch(const std::ifstream::failure& e){
       std::cerr << e.what() << std::endl;
   }
}

