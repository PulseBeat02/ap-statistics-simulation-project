#include <iostream>
#include <random>
#include <fstream>

inline int generateRandom(int min, int max);

inline bool isMultiple(const int set[], int size, int num);

inline std::mt19937 &generator();

#define TRIALS 1000000
#define SAMPLES 1000
#define JUMPS_SIZE 1000

// /usr/local/Cellar/llvm/17.0.5/bin/clang++ -fopenmp -o program main.cpp
// ./program
int main() {
    std::ofstream csv;
    csv.open("data.csv");
    csv << "Random Max Range,Average Numbers Generated\n";
    for (int trial = 1; trial <= TRIALS; trial++) {
        const int min = 1;
        const int max = trial * JUMPS_SIZE;
        int sum = 0;
        #pragma omp parallel for
        for (int sample = 0; sample < SAMPLES; sample++) {
            int set[1000000];
            int index = 0;
            int tempNum = generateRandom(min, max);
            while (!isMultiple(set, index, tempNum)) {
                set[index++] = tempNum;
                tempNum = generateRandom(min, max);
            }
            sum += index;
        }
        const double avg = (double) sum / SAMPLES;
        std::string line = std::to_string(max) + "," + std::to_string(avg) + "\n";
        csv << line;
        csv.flush();
    }
    csv.close();
    return 0;
}

inline int generateRandom(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(generator());
}

inline std::mt19937 &generator() {
    static thread_local std::mt19937 gen(std::random_device{}());
    return gen;
}

inline bool isMultiple(const int set[], const int size, const int num) {
    for (int i = 0; i < size; i++) {
        if (num % set[i] == 0) {
            return true;
        }
    }
    return false;
}