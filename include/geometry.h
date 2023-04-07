#pragma once

#include <vector>
#include <utility>
#include <unordered_map>

typedef struct{
    double sig_a;
    double sig_s;
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
    inline static std::vector<std::pair<int, CrossSections>> data;
    //Global maxes and mins
    inline static double max;
    inline static double min;
    inline static CrossSections DummyXS;

    // TO DO add these parameters to a readable input form
    const int dx = 1000;

    
    public:
        //Methods
        Geometry() = default;
        static void divideGeometry();
        static void determineGlobalRange();

        //Getters
        static const std::vector<std::pair<int, CrossSections>> getGeometry() { return data; };
        static const int getRegion(int loc) { return data.at(loc).first; };
        static const CrossSections getXS(int loc) { return data.at(loc).second; };
        // Region indexes at 1, loc indexes at 0 so subtract 1 from r to get loc
        static const CrossSections getXSvRegion(int r){ return data.at(r-1).second; };
        static const double getMax(){ return max; };
        static const double getMin(){return min; };
        
        //Setters
        void setRange(double X_min, double X_max);
        static void setGeometry(int loc);
        static void setXS(double arr[6]);


};