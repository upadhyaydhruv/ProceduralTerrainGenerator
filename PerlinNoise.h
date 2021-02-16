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

    // Th
    std::vector<int> hashVector;
private:
    double fade(double t);
    double linExtrapolate(double t, double a, double b);
    double grad(int hash, double x, double y, double z);
};


#endif //PROCEDURALMAP_PERLINNOISE_H
