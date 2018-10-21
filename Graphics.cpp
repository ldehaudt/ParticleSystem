#include "Graphics.hpp"

void Graphics::loop(unsigned int VAO){
    while (!glfwWindowShouldClose(window))
    {
        frames++;
        curTime = glfwGetTime();
        if (curTime - startTime > 1)
        {
            fps = (double) frames / (curTime - startTime);
            startTime = curTime;
            frames = 0;
            char *str = (char *)malloc(100);
            sprintf(str, "FPS : %d", (int)round(fps));
            glfwSetWindowTitle(window, str);
            free(str);
        }
        gpuObj->clLoop();
        glClearColor(0.25f,0.305f,0.36f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUniform1f(uniMX, Input::mouseX);
        glUniform1f(uniMY, Input::mouseY);
        glUniform1f(uniMZ, 0);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, numParticles);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

Graphics::Graphics(bool square, int np){
    frames = 0;
    fps = 0;

    startTime = glfwGetTime();
    numParticles = np;
    Input::initInput();
    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "FPS : ...", NULL, NULL);
    glfwMakeContextCurrent(window);
    gpuObj = new GPU(numParticles);

    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);


    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, numParticles * sizeof(particle), NULL, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(particle), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glBindVertexArray(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    glFinish();

    gpuObj->initKernel(&VAO, square);
 
    uniMX = glGetUniformLocation(shaderProgram, "mouseX");
    uniMY = glGetUniformLocation(shaderProgram, "mouseY");
    uniMZ = glGetUniformLocation(shaderProgram, "mouseZ");

    glfwSetCursorPosCallback(window, Input::mouseMoved);
    glfwSetKeyCallback(window, Input::key_callback);
    glfwSetScrollCallback(window, Input::scroll_callback);
    loop(VAO);
    delete(gpuObj);
    glfwTerminate();
}