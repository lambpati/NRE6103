#include "Particle.cpp"

// Determine the number of bins
int Particle:eval_bin(){
  // Compute number of bins
  bin = std::floor(x/ dx_xs_bins);
  // If the bin number computed is greater or equal to number of defined
  // bins, then set the number of bins to the number of defined bins.
  if(bin >= N_XS_BINS) bin = N_XS_BINS;
  return bin;
}

// Set particle's default pos and u to 0, set default weight to 1
void Particle::Particle(double x = 0.0, double u = 0.0, double w = 1.0){
  this->x = x;
  this->u = u;
  this->w = w;

  // Set particle to is_alive
  alive = true;

  Particle::eval_bin();

  // Set the particle to be interacting with the zeroith xs
  xs_evals = 0;
}

// Move particle certain distance
void Particle::move(double dist){
  // Set x_prev to current x
  x_prev = x;
  // Move x to u * dist
  x += u * dist;

  Particle::eval_bin();

}
