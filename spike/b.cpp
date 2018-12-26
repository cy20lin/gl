
#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>
using namespace gl;
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

int main()
{
    // create context, e.g. using GLFW, Qt, SDL, GLUT, ...

    // Assume context creation using GLFW
    glbinding::initialize(glfwGetProcAddress);

    glBegin(GL_TRIANGLES);
    // ...
    glEnd();
}
