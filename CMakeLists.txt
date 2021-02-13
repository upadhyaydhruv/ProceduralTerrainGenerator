cmake_minimum_required(VERSION 3.17)
project(ProceduralMap)

set(CMAKE_CXX_STANDARD 14)

add_executable(ProceduralMap main.cpp PerlinNoise.cpp PerlinNoise.h)