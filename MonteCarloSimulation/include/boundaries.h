#pragma once

#include <utility>

class Boundaries{
    private:
        // Left pair = left boundary condition
       static std::pair<char, char> bounds;

    public:
        //Methods
        Boundaries() = default;

        //Getters

        //Setters
        static void setBounds(char l, char r);
        static void setLeft(char l);
        static void setRight(char r);
};
