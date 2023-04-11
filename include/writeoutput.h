#pragma once

#include <string>
#include <fstream>
#include <iostream>
//#include <format>
#include <vector>
#include <iomanip>

#include "../include/geometry.h"
#include "../include/boundaries.h"
#include "../include/tally.h"


class WriteProgram{
  private:
    static std::string output;
    static std::ofstream out;

  public:
    WriteProgram() = default;

    //Methods
    static void writeToOutput(std::vector<int> val, std::vector<double> pos);
    static void prettyPrintGeometry();
    static void prettyPrintBoundaries();
    static void prettyPrintTally();
};