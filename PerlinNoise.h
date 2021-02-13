//
// Created by goodmanmcgee on 2021-02-13.
//

#include <vector>

#ifndef PROCEDURALMAP_PERLINNOISE_H
#define PROCEDURALMAP_PERLINNOISE_H

class PerlinNoise {
    std::vector<int> data;

public:
    PerlinNoise(unsigned int seed);
    double noise(double x, double y, double z);

private:
    double fade(double t);
    double lerp(double t, double a, double b);
    double grad(int hash, double x, double y, double z);
};


#endif //PROCEDURALMAP_PERLINNOISE_H
