#pragma once

#include <utility>

class Boundaries{
    private:
        // Left pair = left boundary condition
       std::pair<char, char> bounds;

    public:
        //Methods
        Boundaries() = default;

        //Getters

        //Setters
        void setBounds(char l, char r);
        void setLeft(char l);
        void setRight(char r);
};
