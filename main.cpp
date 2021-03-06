#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <numeric>
#include <random>
#include <algorithm>
#include "PerlinNoise.h"

constexpr int MAP_SCALE = 50; // arbitrarily set, can be changed by the user whenever
PerlinNoise generator(24);

// Initialize the heightmap using the insertion values as values for z, which are passed into the noise function

void initializeTerrain() {
    for (int x = 0; x < 1024; x++){
        for (int y = 0; y < 1024; y++) {
            generator.heightMap[x][y] = generator.noise(x, y, generator.zValuesInsertion.at(x)) *
                                        MAP_SCALE; // multiplies by the preset amplitude
        }
    }
}

// This function renders the heightmap into a terrain using openGL

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity(); // Replaces the current matrix, which represents how we view a screen, with the 4X4 identity matrix
    GLuint tex;
    glGenTextures(1, &tex);

    glBindTexture(GL_TEXTURE_2D, tex);

    for (int x = 0; x < 1024-1; x++) {
        // By initializing as GL_TRIANGLE_STRIP, each vertex after the first two will be dealt with as a triangle
        // This needs to be done for every row in the heightmap
        glBegin(GL_TRIANGLE_STRIP);

        for (int y = 0; y < 1024-1; y++) {

            // Finding all the neighboring points for each point in the array, and creating triangles out of all of them

            // Draw vertex 1
            glColor3f(y, y, y);
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(x, y, generator.heightMap[x][y]);

            // Draw vertex 2
            glColor3f(y, y, y);
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(x+1, y, generator.heightMap[x+1][y]);


            // Draw vertex 3
            glColor3f(y+1, y+1, y+1);
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(x, y+1, generator.heightMap[x][y+1]);

            // Draw vertex 4
            glColor3f(y+1, y+1, y+1);
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(x+1, y+1, generator.heightMap[x+1][y+1]);

        }
    }

    // Enables the blending between created triangles
    glEnable(GL_BLEND);


    glDepthMask(GL_FALSE);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);

    glFlush();
    glEnd();
    glFlush();
}



int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hello world!");
    render();
    return 0;
}
