#include "../include/boundaries.h"

void Boundaries::setBounds(char l, char r){
    bounds.first = l;
    bounds.second = r;
}

void Boundaries::setLeft(char l){
    bounds.first = l;
}

void Boundaries::setRight(char r){
    bounds.second = r;
}