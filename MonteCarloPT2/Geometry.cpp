#include "Geometry.hpp"

void Geometry::setXS(int arr[6]){
    DummyXS.sig_a = arr[0];
    DummyXS.sig_f = arr[1];
    DummyXS.v_sig_f = arr[2];
    DummyXS.s = arr[3];
    DummyXS.X_min = arr[4];
    DummyXS.X_max = arr[5];
}

void Geometry::setGeometry(int loc){
    auto s = make_pair(loc, DummyXS);
    // If vector is smaller than location, push_back (push_back faster than insert)
    if(loc > geometry.size()){
        geometry.push_back(s);
    }
    // Else put in at location
    if(loc <= geometry.size()){
        geometry.insert(geometry.begin() + loc, s)
    }
}