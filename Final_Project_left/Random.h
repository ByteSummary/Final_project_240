#ifndef __RANDOM_H__
#define __RANDOM_H__

#include <iostream>
#include <random>

class Random {
    private:
        std::mt19937 rng; // Mersenne twister
        std::uniform_real_distribution<double> rand_double;
        int initial_seed;
    
    public:
        Random(int seed);
        double getRandomDouble();

    
};

#endif