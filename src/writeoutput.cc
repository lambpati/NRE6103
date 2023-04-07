#include "../include/writeoutput.h"


// If C++ 20 or above, use conditional formatting
#if (__cplusplus >= 202002L)
#include <format>
void WriteProgram::prettyPrintGeometry() {
    auto dat = Geometry::getGeometry();
    std::cout << "Constructed geometry according to below NOTE MAKE SURE SCREEN IS BIG ENOUGH TO SHOW TABLE CORRECTLY" << std::endl;
    std::cout << std::format("|{:^9}|{:^9}|{:^9}|{:^9}|{:^9}|{:^9}|{:^9}|{:^9}|\n", "Region", "Sigma A","Sigma S", "Sigma F", "V Sig F", "S", "X min", "X max");
    for (auto &d : dat) {
       int reg = d.first;
       CrossSections xs = d.second;
       std::cout << std::format("|{:^9}|{:^9}|{:^9}|{:^9}|{:^9}|{:^9}|{:^9}|{:^9}|\n", reg, xs.sig_a, xs.sig_s, xs.sig_f, xs.v_sig_f, xs.s, xs.X_min, xs.X_max);

     }
}
// Else use regular formatting
#else
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
#endif


std::string WriteProgram::output = "output.txt";
std::ofstream WriteProgram::out;

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