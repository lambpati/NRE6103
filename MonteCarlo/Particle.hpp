#pragma once

#include <cmath>

// Stores particle state within public functions and methods
class Particle{
  public:
    // Variables
    double x;
    double x_prev;
    double u;
    double w;
    int bin;
    double Esmp;
    bool alive;
    int xs_evals;

    Particle(double x, double u, double w);

    // Methods
    bool is_alive(){ return alive; }
    void kill(){ alive = false; }
    void move(double dist);
    void turn(){ u *= -1.0; }
    void xs_eval(){ xs_evals++; }
    int eval_bin();

}
