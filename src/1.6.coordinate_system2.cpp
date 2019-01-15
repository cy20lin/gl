#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
using namespace gl;
// using namespace glbinding;
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>

#include "1.3.shader.hpp"
#include <memory>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

const char *vertexShaderSourcePath =
    "./1.6.coordinate_system2-vertex.glsl";
const char *fragmentShaderSourcePath =
    "./1.6.coordinate_system2-fragment.glsl";


class renderer {
public:
    unsigned int m_texture1;
    unsigned int m_texture2;
    unsigned int m_texture3;
    int m_width1;
    int m_height1;
    int m_channel1;
    int m_width2;
    int m_height2;
    int m_channel2;
    int m_width3;
    int m_height3;
    int m_channel3;
    std::shared_ptr<Shader> m_program;
    unsigned int VBO, VAO, EBO;
    void setup() {
        setup_shader();
        setup_vertices();
        setup_texture();
    }
    void setup_shader() {
        // build and compile our shader zprogram
        // ------------------------------------
        m_program = std::make_shared<Shader>(vertexShaderSourcePath, fragmentShaderSourcePath);
    }
    void setup_texture() {
        setup_texture1();
        setup_texture2();
        setup_texture3();
        // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
        // -------------------------------------------------------------------------------------------
        m_program->use();
        m_program->setInt("texture1",0);
        m_program->setInt("texture2",1);
        m_program->setInt("texture3",2);
    }
    void setup_vertices() {
        float vertices[] = {

            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 2.f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 2.f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 2.f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 2.f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 2.f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 2.f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0

        };
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // position attribute
        // texture coord attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(5 * sizeof(float)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnable(GL_DEPTH_TEST);  
        // glDepthFunc(GL_LESS);
    }
    void setup_texture1() {
        glGenTextures(1, &m_texture1);
        glBindTexture(GL_TEXTURE_2D, m_texture1);
        // set the m_texture wrapping/filtering options (on the currently bound texture object)
        // GL_CLAMP_TO_EDGE
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        // load and generate the m_texture
        // unsigned char *data = stbi_load("container.jpg", &m_width, &m_height, &m_channel, 0);
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load("grass_side.png", &m_width1, &m_height1, &m_channel1, 0);
        if (!data) {
            throw std::runtime_error("Failed to load texture");
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width1, m_height1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }
    void setup_texture2() {
        glGenTextures(1, &m_texture2);
        glBindTexture(GL_TEXTURE_2D, m_texture2);
        // set the m_texture wrapping/filtering options (on the currently bound texture object)
        // GL_CLAMP_TO_EDGE
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        // load and generate the m_texture
        // unsigned char *data = stbi_load("container.jpg", &m_width, &m_height, &m_channel, 0);
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load("grass_path_top.png", &m_width2, &m_height2, &m_channel2, 0);
        if (!data) {
            throw std::runtime_error("Failed to load texture");
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width2, m_height2, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }
    void setup_texture3() {
        glGenTextures(1, &m_texture3);
        glBindTexture(GL_TEXTURE_2D, m_texture3);
        // set the m_texture wrapping/filtering options (on the currently bound texture object)
        // GL_CLAMP_TO_EDGE
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        // load and generate the m_texture
        // unsigned char *data = stbi_load("container.jpg", &m_width, &m_height, &m_channel, 0);
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load("dirt.png", &m_width3, &m_height3, &m_channel3, 0);
        if (!data) {
            throw std::runtime_error("Failed to load texture");
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width3, m_height3, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }
    void render() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind Texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_texture2);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, m_texture3);

        // create transformations
        glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 view          = glm::mat4(1.0f);
        glm::mat4 projection    = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
        view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        // retrieve the matrix uniform locations
        unsigned int modelLoc = glGetUniformLocation(m_program->id(), "model");
        unsigned int viewLoc  = glGetUniformLocation(m_program->id(), "view");
        unsigned int projectionLoc  = glGetUniformLocation(m_program->id(), "projection");
        // pass them to the shaders (3 different ways)
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
        // m.setMat4("projection", projection);

        // render box
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

    }
    void teardown() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        // glDeleteBuffers(1, &EBO);
    }
};

class window {};

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glbinding: load all OpenGL function pointers
    // ---------------------------------------
    glbinding::Binding::initialize(glfwGetProcAddress);

    // build and compile our shader program
    // ------------------------------------
    renderer renderer_;
    renderer_.setup();

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        renderer_.render();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);
    renderer_.teardown();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
