#pragma once

#include <omp.h>
#include <memory>
#include <vector>

// Class of Transporter, uses direct sampling for transport method
class Transporter {
private:
  // Get collision distance for particle P
  double get_col_dist(Particle& p, double P_nc, const std::unique_ptr<XS>& xs, PCG& rand);
  // Get # of P with no collision
  double get_no_col(Particle& p, const std::unique_ptr<XS>& xs);
  // Bisect
  double bisection(Particle& p, double tau_hat, const std::unique_ptr<XS>& xs);

  public:
    virtual ~Transporter();
    // Used to store particle bank and cross sections
    virtual void Transport(const std::vector<Particle>& bank, const std::unique_ptr<XS>& xs) = 0;
};
