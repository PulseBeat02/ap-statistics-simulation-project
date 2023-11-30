#include <iostream>
#include <fstream>
#include <string>
#include "parser.hpp"

//  /usr/local/Cellar/llvm/17.0.5/bin/clang++ -o program regression.cpp
// ./program

// f(N) = g(N) * sqrt(N)
// Calculates g(N) based off values of N
int main() {
    std::ifstream input("data.csv");
    aria::csv::CsvParser parser = aria::csv::CsvParser(input);
    std::ofstream csv;
    csv.open("gConst.csv");
    csv << "N,g(N)\n";
    bool header = true;
    for (auto &row: parser) {
        if (header) {
            header = false;
            continue;
        }
        double N = std::stod(row.front());
        double count = std::stod(row.back());
        const double gConst = count / std::sqrt(N);
        std::string line = std::to_string(N) + "," + std::to_string(gConst) + "\n";
        csv << line;
    }
    input.close();
    csv.close();
    return 0;
}