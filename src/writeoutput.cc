#include "../include/writeoutput.h"



std::string WriteProgram::output = "output.txt";
std::ofstream WriteProgram::out;

void WriteProgram::prettyPrintGeometry() {
    auto dat = Geometry::getGeometry();
    std::cout << "Constructed geometry according to below " << std::endl;
    std::cout << std::format("|{:^9}|{:^9}|{:^9}|{:^9}|{:^9}|{:^9}|{:^9}|{:^9}|\n", "Region", "Sigma A","Sigma S", "Sigma F", "V Sig F", "S", "X min", "X max");
    for (auto &d : dat) {
       int reg = d.first;
       CrossSections xs = d.second;
       std::cout << std::format("|{:^9}|{:^9}|{:^9}|{:^9}|{:^9}|{:^9}|{:^9}|{:^9}|\n", reg, xs.sig_a, xs.sig_s, xs.sig_f, xs.v_sig_f, xs.s, xs.X_min, xs.X_max);

     }
}

void WriteProgram::prettyPrintBoundaries() {
    auto dat = Boundaries::getBoundaries();
    std::cout << "Boundaries constructed below " << std::endl;
    std::cout << "Left: " << dat.first << " Right: " << dat.second << std::endl;
}

void WriteProgram::prettyPrintTally() {
    auto dat = Tally::getTallyType();
    std::cout << "Problem type constructed below " << std::endl;
    std::string type = dat ? "Flux" : "Eigenvalue";
    std::cout << "Problem type: " << type << std::endl;
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