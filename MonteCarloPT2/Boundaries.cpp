#include "Boundaries.cpp"

void Boundaries::setBounds(char l, char r){
    boundaries.first = l;
    boundaries.second = r;
}

void Boundaries::setLeft(char l){
    boundaries.first = l;
}

void Boundaries::setRight(char r){
    boundaries.second = r;
}