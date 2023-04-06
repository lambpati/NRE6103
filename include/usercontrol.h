#pragma once

#include <filesystem>
#include <string>
#include <iostream>
#include <chrono>

#if defined(_MSC_VER)
#include <direct.h>
const std::filesystem::path correct_path = "..\\..\\..\\examples\\";
#elif defined(__GNUC__)
#include <unistd.h>
const std::filesystem::path path = "../../examples/"
#endif


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