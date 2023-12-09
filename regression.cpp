#include <iostream>
#include <fstream>
#include <string>
#include "parser.hpp"

const double E = 2.71828182845904523536;

inline long double calculateSquareRootGConst(double N, double count);

inline long double calculateExponentGConst(double N, double count);

inline long double calculateProbabilityFromAverage(double N, double count);

//  /usr/local/Cellar/llvm/17.0.5/bin/clang++ -o program regression.cpp
// ./program

// f(N) = g(N) * sqrt(N)
// Calculates g(N) based off values of N
int main() {
    std::ifstream input("data.csv");
    aria::csv::CsvParser parser = aria::csv::CsvParser(input);
    std::ofstream csv;
    csv.open("const.csv");
    csv << "N,g(N)\n";
    bool header = true;
    for (auto &row: parser) {
        if (header) {
            header = false;
            continue;
        }
        double N = std::stod(row.front());
        double count = std::stod(row.back());
        const long double constant = calculateProbabilityFromAverage(N, count);
        std::string line = std::to_string(N) + "," + std::to_string(constant) + "\n";
        csv << line;
    }
    input.close();
    csv.close();
    return 0;
}

inline long double calculateExponentGConst(double N, double count) {
    double first = count / std::sqrt(N);
    return first / std::pow(count, -0.01 * E);
}

inline long double calculateSquareRootGConst(double N, double count) {
    return count / std::sqrt(N);
}

inline long double calculateProbabilityFromAverage(double N, double count) {
    return 1 / count;
}