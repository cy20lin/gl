#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>
using namespace gl;
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>


void processInput(GLFWwindow *window);

int main() {

    glfwInit();
    // glfwWindowHint(GLFW_SAMPLES, 4); // 4x anti-aliasing
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, int(GL_TRUE));
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // open a window and create its OpenGL context
    GLFWwindow * window;
    window = glfwCreateWindow(1024, 768, "Tutorial-01", NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // void return
    glfwSetInputMode(window, GLFW_STICKY_KEYS, int(GL_TRUE));

    glbinding::initialize(glfwGetProcAddress);


    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
