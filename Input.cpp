#include "Input.hpp"

float Input::mouseX;
float Input::mouseY;
float Input::offsetX;
float Input::offsetY;
float Input::scroll;
bool Input::following;
bool Input::noGrav;

void Input::initInput(){
    mouseX = 0;
    mouseY = 0;
    scroll = 0;
    following = true;
    noGrav = false;
}

void Input::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    scroll -= yoffset / 100.0;
}

void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        mouseY += 0.1f;
        offsetY += 0.1f;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        mouseX -= 0.1f;
        offsetX -= 0.1f;        
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        mouseY -= 0.1f;        
        offsetY -= 0.1f;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        mouseX += 0.1f;
        offsetX += 0.1f;
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        following = !following;
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        noGrav = !noGrav;
}

void Input::mouseMoved(GLFWwindow* window, double xpos, double ypos)
{
    if (following){
        mouseX = (xpos * 2 - SCR_WIDTH) / SCR_WIDTH;
        mouseY = (SCR_HEIGHT - ypos * 2) / SCR_HEIGHT;
    }
}