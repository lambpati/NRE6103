#pragma once

#include <string>
#include <iostream>
#include <chrono>


class UserControl{
    // Variables
    private:
        static std::string fileName;
        const std::chrono::duration<double> duration;

    public:
        // Methods
        UserControl() = default;
        static void printIntro();
        static void printOutro(std::chrono::duration<double> d);
        // Getters
        static std::string getFileName() { return fileName; }

        // Setters
        static void setFileName(std::string f);
};