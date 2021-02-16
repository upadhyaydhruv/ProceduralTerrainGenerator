//
// Created by goodmanmcgee on 2021-02-13.
//

#include <numeric>
#include <random>
#include <algorithm>
#include <iostream>
#include "PerlinNoise.h"
#define lerp(

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

double noise(double x, double y, double z) {
    // This function find the relevant position of the coordinate in a "unit cube"

    // By modulating by 255, it makes sure that the coordinates are within the preset range of 0 to 255 and prevents overflow errors
    int xOverflow = (int)x % 255;
    int yOverflow = (int)y % 255;
    int zOverflow = (int)z % 255;

    //Now finding the position in the unit cube by modulating by 1.0
    double xFinal = x - xOverflow;
    double yFinal = y - yOverflow;
    double zFinal = z - zOverflow;

    // The fade function is applied on each of these unit cell values in order to create a perception of continuity

    double fadedX = fade(xFinal);
    double fadedY = fade(yFinal);
    double fadedZ = fade(zFinal);


}
