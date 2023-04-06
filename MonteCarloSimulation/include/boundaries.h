#pragma once

#include <utility>

class Boundaries{
    private:
        // Left pair = left boundary condition
       inline static std::pair<char, char> bounds;

    public:
        //Methods
        Boundaries() = default;

        //Getters
        static const std::pair<char, char> getBoundaries() { return bounds; };

        //Setters
        void setBounds(char l, char r);
        static void setLeft(char l);
        static void setRight(char r);
};
