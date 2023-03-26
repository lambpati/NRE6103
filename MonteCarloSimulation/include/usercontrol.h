#pragma once

#include <string>
#include <iostream>
#include <chrono>

using clock = std::chrono::system_clock;
using sec = std::chrono::duration<double>;

class UserControl{
    // Variables
    private:
        static std::string fileName;
        const std::chrono::time_point start;
        const sec duration;

    public:
        // Methods
        UserControl() = default;
        static void printIntro();
        static void printOutro();
        // Getters
        static std::string getFileName() { return fileName; }

        // Setters
        static void setFileName(std::string f){ fileName = f; } 
};