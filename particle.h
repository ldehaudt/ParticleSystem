#ifndef PARTICLE_H
# define PARTICLE_H

# include <GLFW/glfw3.h>
# include <math.h>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <OpenCL/opencl.h>
#include <OpenGL/CGLCurrent.h>
#include <OpenGL/gl3.h>

# define SCR_WIDTH 1400
# define SCR_HEIGHT 1400

typedef struct s_particle{
    float x;
    float y;
    float z;
    float vx;
    float vy;
    float vz;
}               particle;

#endif