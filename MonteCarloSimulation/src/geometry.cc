#include "../include/geometry.h"

void Geometry::setXS(double arr[6]){
    DummyXS.sig_a = arr[0];
    DummyXS.sig_f = arr[1];
    DummyXS.v_sig_f = arr[2];
    DummyXS.s = arr[3];
    DummyXS.X_min = arr[4];
    DummyXS.X_max = arr[5];
}

void Geometry::setGeometry(int loc){
    std::pair<int,CrossSections> s = std::make_pair(loc, DummyXS);
    // If vector is smaller than location, push_back (push_back faster than insert)
    if(loc > data.size()){
        data.push_back(s);
    }
    // Else put in at location
    else{
        data.insert(data.begin() + loc, s);
    }
}