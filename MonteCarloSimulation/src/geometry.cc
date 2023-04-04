#include "../include/geometry.h"

// REMOVE AFTER DEBUGGING
#include<iostream>

void Geometry::setXS(double arr[6]){
    DummyXS.sig_a = arr[0];
    std::cout << "Set sig_a to " << arr[0] << std::endl;
    DummyXS.sig_f = arr[1];
    std::cout << "Set sig_f to " << arr[1] << std::endl;
    DummyXS.v_sig_f = arr[2];
    std::cout << "Set v_sig_f to " << arr[2] << std::endl;
    DummyXS.s = arr[3];
    std::cout << "Set sig_a to " << arr[3] << std::endl;
    DummyXS.X_min = arr[4];
    std::cout << "Set X_min to " << arr[4] << std::endl;
    DummyXS.X_max = arr[5];
    std::cout << "Set X_max to " << arr[5] << std::endl;
}

void Geometry::setGeometry(int loc){
    std::pair<int,CrossSections> s = std::make_pair(loc, DummyXS);
    // If vector is smaller than location, push_back (push_back faster than insert)
    if(loc > data.size()){
        std::cout << "Added region " << loc << std::endl;
        data.push_back(s);
    }
    // Else put in at location
    else{
        std::cout << "Added region " << loc << std::endl;
        data.insert(data.begin() + loc, s);
    }
}