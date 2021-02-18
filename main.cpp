#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <numeric>
#include <random>
#include <algorithm>
#include <PerlinNoise.h>

constexpr int MAP_SCALE = 50; // arbitrarily set, can be changed by the user whenever

// Initialize the heightmap using the insertion values as values for z, which are passed into the noise function

void initializeTerrain() {
    PerlinNoise generator(24); // Creates a perlin noise object with a seed of 24
    int heightMap[1024][1024];
    for (int x = 0; x < 1024; x++){
        for (int y = 0; y < 1024; y++) {
            heightMap[x][y] = generator.noise(x, y, generator.zValuesInsertion.at(x)) * MAP_SCALE; // multiplies by the preset amplitude

    }
}

// This function renders the heightmap into a terrain using openGL

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity(); // Replaces the current matrix, which represents how we view a screen, with the 4X4 identity matrix
    glBindTexture(GL_TEXTURE_2D, land);

    for (int x = 0; x < 1024; x++) {
        // By initializing as GL_TRIANGLE_STRIP, each vertex after the first two will be dealt with as a triangle
        // This needs to be done for every row in the heightmap
        glBegin(GL_TRIANGLE_STRIP);

        for (y = 0; y < 1024; y++) {

            // Draw vertex 1
            glColor3f(y, y, y);
            gltexCoord2f(0.0f, 0.0f);
            glVertex3f(x, y, z);

        }
    }

    // Enables the blending between created triangles
    glEnable(GL_BLEND);


    glDepthMask(GL_FALSE);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);

    glFlush();

    SwapBuffers(g_HDC);

    }
}



void displayMe(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glVertex3f(0.5, 0.0, 0.5);
    glVertex3f(0.5, 0.0, 0.0);
    glVertex3f(0.0, 0.5, 0.0);
    glVertex3f(0.0, 0.0, 0.5);
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {

    initializeTerrain();


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(400, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hello world!");
    glutDisplayFunc(displayMe);
    glutMainLoop();
    return 0;
}
