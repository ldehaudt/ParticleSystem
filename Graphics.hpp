#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP
#include "particle.h"
#include "Input.hpp"
#include "GPU.hpp";

class Graphics
{
    public:
        int numParticles;
        Graphics(bool square, int particles);
        ~Graphics();
        
        // glClearColor(0.25f,0.305f,0.36f, 1.0f);

    private:
        void loop(unsigned int VAO);
        GPU *gpuObj;
        GLFWwindow      *window;
        int shaderProgram;
        int uniMX;
        int uniMY;
        int uniMZ;
        int frames;
        float fps;
        float startTime;
        float curTime;
        const char *vertexShaderSource = 
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "out float dist;"
        "uniform float mouseX;"
        "uniform float mouseY;"
        "uniform float mouseZ;"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "   dist = sqrt((mouseX - aPos.x) * (mouseX - aPos.x) + (mouseY - aPos.y) * (mouseY - aPos.y) + (mouseZ - aPos.z) * (mouseZ - aPos.z));"
        "}\0";
        const char *fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in float dist;"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(0.25 + 0.75f * (1 - (dist * 1.5)),0.305f + 0.695f * (1 - (dist * 1.5)),0.36f + 0.64f * (1 - (dist * 1.5)), 1.0f);\n"
        "}\n\0";
};

#endif