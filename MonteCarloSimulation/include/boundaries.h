#pragma once

#include <utility>

class Boundaries{
    private:
        // Left pair = left boundary condition
       pair<char, char> boundaries; 

    public:
        //Methods
        Boundaries() = default;

        //Getters

        //Setters
        setBounds(char l, char r);
        setLeft(char l);
        setRight(char r;)
};
