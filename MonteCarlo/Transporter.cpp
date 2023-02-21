#include "Transporter.hpp"

double Transporter::get_col_dist(Particle& p, double P_nc, const std::unique_ptr<XS>& xs, PCG& rng) {
	double x_0 = p.x;
	double x_max;

	// Define maximum x depending on particle angle
	if (p.u == -1) {
		x_max = X_MIN;
	}
	else {
		x_max = X_MAX;

	}

	double G = 1.0 - P_nc;
	double xi = rng.rand();
	double tau_hat = -1 * std::log(1.0 - G * xi);

	// First guess between 1/2 current pos and surface
	double s1 = 0.5 * (x_0 + x_max);
	double s0 = x_max;
	double d = std::abs(s1 - s0);
	double d_prev = d + 1.0;
	double g = 0.0;
	double dg = 0.0;

	while (d > 1e-6) {
		s0 = s1;
		g = tau_hat - xs->T(x_0, s0);
		p.xs_eval();
		dg = -xs->E(s0);
		d_prev = d;
		d = std::abs(s1 - s0);

		// Check and call if bisection is needed
	}
}
