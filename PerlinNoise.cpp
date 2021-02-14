//
// Created by goodmanmcgee on 2021-02-13.
//

#include <numeric>
#include <random>
#include <algorithm>
#include <iostream>
#include "PerlinNoise.h"

PerlinNoise::PerlinNoise(unsigned int seed) {
    data.resize(256);
    std::iota(data.begin(), data.end(), 1);

    std::default_random_engine engine(seed);
    std::shuffle (data.begin(), data.end(), engine);
    std::cout << std::endl;
    data.insert(data.end(), data.begin(), data.end());
}

double PerlinNoise::fade(double t) {
    return 6*pow(t, 5) - 15*pow(t, 4) + 10*pow(t, 3); // 6t^5-15t^4+10t^3 is the perlin fade function to
}
