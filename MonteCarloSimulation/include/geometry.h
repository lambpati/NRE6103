#pragma once

#include <vector>
#include <utility>
#include <unordered_map>

struct CrossSections{
            double sig_a;
            double sig_f;
            double v_sig_f;
            double s;
            int X_min;
            int X_max;

} DummyXS;

class Geometry{
    private:
    // Storing in a vector of pairs for memory allocation and speed.
    // First value is key second value is values
    std::vector<std::pair<int, CrossSections>> geometry;
    std::pair<int,int> range;

    
    public:
        //Methods
        Geometry() = default;

        //Getters

        //Setters
        void setRange(int X_min, int X_max);
        void setGeometry(int loc);
        void Geometry::setXS(double sig_a, double sig_f, double v_sig_f, double s, int X_min, int X_max);


};