#pragma once

#include <fstream>
#include <string>
#include <utility>
#include <sstream>

class ReadProgram{
  private:
    static std::ifstream file;
    static int lineNum;
    static std::string contents;
    static std::string keyword;

    

  public:
    ReadProgram() = default;

    // Getters
    static int getLineNum() { return lineNum; }

    //Methods
    static void read();
    static void parseFile();
    static void populateGeometry();
    static void populateBoundaries();
};