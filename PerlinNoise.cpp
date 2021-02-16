//
// Created by goodmanmcgee on 2021-02-13.
//

#include <numeric>
#include <random>
#include <algorithm>
#include <iostream>
#include "PerlinNoise.h"

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

    // The code below uses the hashvector and does operations upon that
    // By having nested indexing, it ensures that the printed values are truly (pseudo)random, with incrementing the overflows doing the same

    int vec1, vec2, vec3, vec4, vec5, vec6, vec7, vec8;

    vec1 = hashVector.at(hashVector.at(hashVector.at(xOverflow) + yOverflow) + zOverflow);
    vec2 = hashVector.at(hashVector.at(hashVector.at(xOverflow) + yOverflow + 1) + zOverflow);
    vec3 = hashVector.at(hashVector.at(hashVector.at(xOverflow) + yOverflow) + zOverflow + 1);
    vec4 = hashVector.at(hashVector.at(hashVector.at(xOverflow) + yOverflow + 1) + zOverflow + 1);
    vec5 = hashVector.at(hashVector.at(hashVector.at(xOverflow + 1) + yOverflow) + zOverflow);
    vec6 = hashVector.at(hashVector.at(hashVector.at(xOverflow + 1) + yOverflow + 1) + zOverflow);
    vec7 = hashVector.at(hashVector.at(hashVector.at(xOverflow + 1) + yOverflow) + zOverflow + 1);
    vec8 = hashVector.at(hashVector.at(hashVector.at(xOverflow + 1) + yOverflow + 1) + zOverflow + 1);

    double x1, x2, y1, y2;

    x1 = lerp(grad(vec1, xFinal, yFinal, zFinal), grad(vec5, xFinal - 1, yFinal - 1, zFinal), fadedX);
    x2 = lerp(grad(vec2, xFinal, yFinal - 1, zFinal), grad(vec6, xFinal - 1, yFinal - 1, zFinal), fadedX);
    y1 = lerp (x1, x2, fadedY);
    x1 = lerp (grad(vec3, xFinal, yFinal, zFinal - 1), grad(vec7, xFinal - 1, yFinal - 1, zFinal - 1), fadedX);
    x2 = lerp (grad(vec4, xFinal, yFinal, zFinal - 1), grad(vec8, xFinal - 1, yFinal - 1, zFinal - 1), fadedX);

    y2 = lerp (x1, x2, fadedY);

    return (lerp (y1, y2, fadedZ) + 1)/2;


}

double grad(int hash, double x, double y, double z) {
    // This function uses bit manipulation to pick a random vector from the following using the last four bits of the hash function
    /*
     (1,1,0),(-1,1,0),(1,-1,0),(-1,-1,0)
     (1,0,1),(-1,0,1),(1,0,-1),(-1,0,-1),
     (0,1,1),(0,-1,1),(0,1,-1),(0,-1,-1)
     */

    int h = hash & 15; // Takes last 4 bits of the hashed value
    double u = h < 8 ? x : y; // If the first digit (MSB) is 0, let u equal x, otherwise let u equal y
    if (h < 4)
        v = y;
    else if (h == 12 || h == 14)
        v = x;
    else
        v = z;

    return (h&1 == 0 ? u : -u + h&2 == 0 ? v : -v); // Uses the last two digits to determine if u and v are positive or negative, and returns the sum of those
}

double linExtrapolate(double a, double b, double x) {
    return a + x * (b - a); // creates a function to extrapolate between two points
}