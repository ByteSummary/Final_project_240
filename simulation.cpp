#include <iostream>
#include <fstream>

simulation(std::string fileName) {
    randnum = 1234567;

    std::ifstream infile(fileName);

    if(!infile) {
        std::cerr << "Error: could not open file: " << fileName << std::endl;
        exit(1);
    }
}