//
// Created by goodmanmcgee on 2021-02-13.
//

#include <vector>

#ifndef PROCEDURALMAP_PERLINNOISE_H
#define PROCEDURALMAP_PERLINNOISE_H

class PerlinNoise {

public:
    PerlinNoise(unsigned int seed);
    double noise(double x, double y, double z);
    double gradient(int hash, double x, double y, double z); // Gradient function to return a dot product of the two vectors

    // Th
    std::vector<int> hashVector;
private:
    double fade(double t);
    double linExtrapolate(double t, double a, double b);
    double grad(int hash, double x, double y, double z);
};


#endif //PROCEDURALMAP_PERLINNOISE_H
