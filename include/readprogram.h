#pragma once

#include <fstream>
#include <string>
#include <utility>
#include <sstream>

#include "../include/usercontrol.h"
#include "../include/tally.h"
#include "../include/boundaries.h"
#include "../include/geometry.h"

class ReadProgram{
  private:
    static std::ifstream file;
    static int lineNum;
    static std::string contents;
    std::string c;
    std::string keyword;

    

  public:
    ReadProgram() = default;

    // Getters
    static int getLineNum() { return lineNum; }

    //Methods
    void read();
    void parseFile();
    void populateGeometry();
    void populateBoundaries();
};