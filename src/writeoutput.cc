#include "../include/writeoutput.h"


void WriteProgram::prettyPrintGeometry() {
    auto dat = Geometry::getGeometry();
    std::cout << "Constructed geometry according to below NOTE MAKE SURE SCREEN IS BIG ENOUGH TO SHOW TABLE CORRECTLY" << std::endl;
    std::cout << '|' << std::setw(10) << "Region" << '|' << std::setw(10) << "Sigma A" << '|' << std::setw(10) << "Sigma S" << '|' << std::setw(10) << "Sigma F" << '|' << std::setw(10) << "V Sig F" << '|' << std::setw(10) << "S" << '|' << std::setw(10) << "X min" << '|' << std::setw(10) << "X max" << std::endl;
    for (auto &d : dat) {
       int reg = d.first;
       CrossSections xs = d.second;
       std::cout << '|' << std::setw(10) << reg << '|' << std::setw(10) << xs.sig_a << '|' << std::setw(10) << xs.sig_s << '|' << std::setw(10) <<xs.sig_f << '|' << std::setw(10) << xs.v_sig_f << '|' << std::setw(10) << xs.s << '|' << std::setw(10) << xs.X_min << '|' << std::setw(10) << xs.X_max << std::endl;

     }
}


std::string WriteProgram::output = "output.csv";
std::string WriteProgram::mean = "statistics.csv";
std::ofstream WriteProgram::out;

void WriteProgram::prettyPrintBoundaries() {
    auto dat = Boundaries::getBoundaries();
    std::cout << "Boundaries constructed below " << std::endl;
    std::string type_1 = dat.first ? "Vacuum" : "Specular";
    std::string type_2 = dat.second ? "Vacuum" : "Specular";
    std::cout << "Left: " << type_1 << " Right: " << type_2 << std::endl;
}

void WriteProgram::prettyPrintTally() {
    auto dat = Tally::getTallyType();
    std::cout << "Problem type constructed below " << std::endl;
    std::string type = dat ? "Flux" : "Eigenvalue";
    std::cout << "Problem type: " << type << std::endl;
}

// Writes array values val into a csv file known as "output.csv"
void WriteProgram::writeToOutput(std::vector<double> val, std::vector<double> pos){
       out.open(output, std::ios_base::trunc);
       // Header
       out << "Position,Flux \n";
       for(int i=0; i < val.size(); i++){
        out << pos.at(i) << "," << val.at(i) << "\n";
//       out << '\n';
     }
     out.close();
}
// Writes array values val into a csv file known as "statistics.csv"
void WriteProgram::writeToStatistics(std::vector<double> pos, std::vector<double> mea, std::vector<double> var){
       out.open(mean, std::ios_base::trunc);
       // Header
       out << "Position,Mean,Variance \n";
       for(int i=0; i < mea.size(); i++){
        out << pos.at(i) << "," << mea.at(i) << "," << var.at(i) << "\n";
//       out << '\n';
     }
     out.close();
}

// Writes array values val into a csv file known as "output.csv"
void WriteProgram::writeToOutput(std::vector<std::pair<double,double>> val, double K){
    //TODO Write output to txt in specified format
//   // Results stored in examples folder "output.csv"
       out.open(output, std::ios_base::trunc);
       // Header
       if(!std::isnan(K)){
        out << "K_eff is " << K << "\n";
       }
       out << "Position,Flux \n";
       for(auto &e : val){
        out << e.first << "," << e.second << "\n";
//       out << '\n';
     }
     out.close();
}