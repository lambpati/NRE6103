#include <random>

class RNG {
    private:
    public:
        RNG() = default;
        static double rand() { 
            std::random_device rd;  // Will be used to obtain a seed for the random number engine
            std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
            std::uniform_real_distribution<> dist(0.0, 1.0);
            return dist(gen);
        };
        static double rdir(){
             std::random_device rd;  // Will be used to obtain a seed for the random number engine
            std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
            std::uniform_real_distribution<> dist(-1.0, 1.0);
            return dist(gen);
        };

};