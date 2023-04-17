#include "../include/pertubation.h"

double Pertubation::calculatePertubation(double delta, double k){
    double v_sig = 0;
    double sig_a = 0;
    double width = Tally::getWidth();
    Transporter transporter;
    for(int i = 0; i < Tally::getAdjoint().size(); i++){
        double mul = Tally::getAdjoint().at(i).second*Tally::getForward().at(i).second;
        int reg = transporter.determineMaterial(Tally::getAdjoint().at(i).first);
        v_sig += Geometry::getXS(reg).v_sig_f*mul*width;
        
        if(reg != 2 && reg != 3){
            sig_a += Geometry::getXS(reg).sig_a*mul*width;
        }
        else{
            sig_a += (Geometry::getXS(reg).sig_a+delta)*mul*width;
        }
    }
    double k_pert = v_sig/sig_a;
    return k_pert;
}