#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <format>
#include <vector>

#include "../include/geometry.h"

class WriteProgram{
  private:
    static std::string output;
    static std::ofstream out;

  public:
    WriteProgram() = default;

    //Methods
    static void writeToOutput(std::vector<int> val);
    static void prettyPrintGeometry();
};