#include "../include/geometry.h"

void Geometry::setXS(double arr[7]){
    DummyXS.sig_a = arr[0];
    DummyXS.sig_s = arr[1];
    DummyXS.sig_f = arr[2];
    DummyXS.v_sig_f = arr[3];
    DummyXS.s = arr[4];
    DummyXS.X_min = arr[5];
    DummyXS.X_max = arr[6];
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