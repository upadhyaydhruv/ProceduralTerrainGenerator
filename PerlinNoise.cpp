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

    // The operations on data below create a vector of size 256 with the numbers from 0 to 255 in random order
    // This is duplicated twice to create a vector of size 512 in order to create a hash function for the generation
    // Of the gradient vectors
    hashVector.resize(256);

    // iota populates the array from 0 to 255 in order
    std::iota(hashVector.begin(), hashVector.end(), 1);

    std::default_random_engine engine(seed);

    // Shuffles the values in the array using the seed
    std::shuffle (hashVector.begin(), hashVector.end(), engine);

    // Duplicates the generated array using an iterator from start to end, creating an array of size 512
    data.insert(hashVector.end(), hashVector.begin(), hashVector.end());
}

double PerlinNoise::fade(double t) {
    return 6*pow(t, 5) - 15*pow(t, 4) + 10*pow(t, 3); // 6t^5-15t^4+10t^3 is the perlin fade function to
}

double noise(double x, double y, double z) {
    // This function find the local relevant position of the coordinate in a "unit cube"

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
