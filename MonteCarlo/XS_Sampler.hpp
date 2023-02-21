#pragma once
class XS {
	public:
		// Variables
		double Emax; // Maximum energy 
		double Esample; // Sampling xs
		double E_bin_max; // Maximum xs in each bin 
		double E_bin_sample; // Sampling XS in each bin
		bool adjusted;
		double xs_val;

		XS(double xs);
		~XS() = default;

		void reset_XS();
		double E(double x);
		double T(double x_0, double x);
};