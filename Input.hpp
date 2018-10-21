#ifndef INPUT_HPP
#define INPUT_HPP
#include "particle.h"

class Input
{
    public:
        static float mouseX;
        static float mouseY;
        static float offsetX;
        static float offsetY;
        static float scroll;
        static bool following;
        static bool noGrav;
        static void initInput();
        static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void mouseMoved(GLFWwindow* window, double xpos, double ypos);
    private:
        
};

#endif