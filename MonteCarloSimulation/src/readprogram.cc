#include "src/readprogram.h"

#include "src/tally.h"
#include "src/boundaries.h"
#include "src/geometry.h"

std::ifstream ReadProgram::file;
int ReadProgram::lineNum;
std::string ReadProgram::contents;

std::string c;
std::istringstream iss(c);
std::string keyword;

void ReadProgram::populateBoundaries(){
    // Ideally iterate twice to determine the boundary conditions of the file
    do{
        iss >> keyword;
        iss >> value;
        char g = value[0];

        if(keyword == "LEFT"){
            Boundaries::setLeft(g)
        }

        if(keyword == "RIGHT"){
            Boundaries::setRight(g);
        }
    } while(keyword == "LEFT" || "RIGHT");

}

void ReadProgram::populateGeometry(){
    do{
        int XS_Data[6];
        // Keyword is the region #
        iss >> keyword;
        int key = std::atoi(keyword);
        // Populate the XS Data relevantly
        for(int i=0; i<6; i++){
            iss >> c;
            XS_Data[i] = std::atoi(c);
        }
        // Put into structure for easy access
        Geometry::setXS(XS_Data);
        Geometry::setGeometry(key);
    } while(key > 47 && key <= 57);
}
void ReadProgram::parseFile(){
    //Iterate through words
    iss >> keyword;
    switch(keyword){
        case "FLUX":
            // Sets flux tally type to true
            Tally::setTallyType(true);
            break;
        case "EIGEN":
            //Sets flux tally type to false (eigen solution)
            Tally::setTallyType(false);
            break;
        case "BOUNDARIES":
            // Sets boundaries to vacuum or specular for left and right

            ReadProgram::populateBoundaries();
            break;
        case "DATA":
            // Determine geometry type + XS
            ReadProgram::populateGeometry();
            break;
        default:
            // Must be comments or fell through ladder

            break;
    }

}

// Reads contents of a file specified by user
void ReadProgram::read(){
   file.exceptions(std::ifstream::badbit); //I dont see why to check for badbits
   try{
       // File read and write
       file.open(UserControl::getFileName());
       if(!file.is_open()){
       throw std::ifstream::failure("Cannot find file");
     }
        while(!file.eof()){
            file >> c;
            std::istringstream iss(c);
            ReadProgram::parseFile();
        }
        file.close()
   }
   catch(const std::ifstream::failure& e){
       std::cerr << e.what() << std::endl;
   }
}

