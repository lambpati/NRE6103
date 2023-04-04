#pragma once

#include <vector>
#include <utility>
#include <unordered_map>

typedef struct{
    double sig_a;
    double sig_f;
    double v_sig_f;
    double s;
    double X_min;
    double X_max;

} CrossSections;

class Geometry{
    private:
    // Storing in a vector of pairs for memory allocation and speed.
    // First value is key second value is values
    static std::vector<std::pair<int, CrossSections>> data;
    std::pair<double,double> range;
    static CrossSections DummyXS;

    
    public:
        //Methods
        Geometry() = default;

        //Getters
        const std::vector<std::pair<int, CrossSections>> getGeometry() { return data; };
        const int getRegion(int loc) { return data.at(loc).first; };
        const CrossSections getXS(int loc) { return data.at(loc).second; };
        
        //Setters
        void setRange(double X_min, double X_max);
        static void setGeometry(int loc);
        static void setXS(double arr[6]);


};