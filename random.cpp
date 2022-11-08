#ifndef __RANDOM_CPP__
#define __RANDOM_CPP__

#include <iostream>
#include <random>
#include "Random.h"

// common use constructor
Random::Random(int seed){
    rand_double = std::uniform_real_distribution<double>(0, 1);
    initial_seed = seed;
    rng.seed(initial_seed);
}

// returns random double number in (0, 1)
double Random::getRandomDouble(){
    return rand_double(rng);
}


#endif