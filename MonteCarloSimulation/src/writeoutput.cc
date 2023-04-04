#include "../include/writeoutput.h"



std::string WriteProgram::output = "output.txt";
std::ofstream WriteProgram::out;

void WriteProgram::prettyPrintGeometry() {
    // auto dat = Geometry::getGeometry();
    std::cout << "Constructed geometry according to below " << std::endl;
    std::cout << std::format("|{:^9}|{:^9}|{:^9}|{:^9}|{:^9}|{:^9}|\n", "Region", "Sigma A", "Sigma F", "V Sig F", "S", "X min", "X max");
    std::cout << dat.size() << " size of dat" << std::endl;
    for (auto &d : dat) {
       int reg = d.first;
       CrossSections xs = d.second;
       std::cout << std::format("|{:^9}|{:^9}|{:^9}|{:^9}|{:^9}|{:^9}|\n", reg, xs.sig_a, xs.sig_f, xs.v_sig_f, xs.s, xs.X_min, xs.X_max);

    }
}

// Writes array values val into a txt file known as "output.txt"
void WriteProgram::writeToOutput(std::vector<int> val){
    //TODO Write output to txt in specified format
//   // Results stored in build folder "output.txt"
//   out.open(output, std::ios_base::trunc);
//     for(auto &e : val){
//       out << e;
//       out << '\n';
//     }
}