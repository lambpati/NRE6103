#pragma once

#include <string>
#include <fstream>
#include <vector>

class WriteProgram{
  private:
    static std::string output;
    static std::ofstream out;

  public:
    WriteProgram() = default;

    //Methods
    static void writeToOutput(std::vector<int> val);
};