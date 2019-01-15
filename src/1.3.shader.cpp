#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
#include "1.3.shader.hpp"
using namespace gl;
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

void Shader::use() {
    glUseProgram(m_id);
}

void Shader::setBool(const char * name, bool value) {
    glUniform1i(glGetUniformLocation(m_id, name), static_cast<int>(value));
}

void Shader::setInt(const char * name, int value) {
    glUniform1i(glGetUniformLocation(m_id, name), static_cast<int>(value));
}

void Shader::setFloat(const char * name, float value) {
    glUniform1f(glGetUniformLocation(m_id, name), static_cast<float>(value));
}

int Shader::id() {
    return m_id;
}

Shader::Shader(const char * vertexPath, const char * fragmentPath) : m_id(-1) {
    // try
    std::string vertexCode;
    std::string fragmentCode;
    {
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream;
        std::stringstream fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    int success;
    char infoLog[512];
    int vId;
    {
        const char * vShaderCode = vertexCode.data();
        vId = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vId, 1, &vShaderCode, nullptr);
        glCompileShader(vId);
        glGetShaderiv(vId, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(vId, 512, NULL, infoLog);
            throw std::runtime_error(std::string() + "VertexShader compilation failed: " + infoLog);
        }
    }
    int fId;
    {
        const char * fShaderCode = fragmentCode.data();
        fId = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fId, 1, &fShaderCode, nullptr);
        glCompileShader(fId);
        glGetShaderiv(fId, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(fId, 512, NULL, infoLog);
            throw std::runtime_error(std::string() + "FragmentShader compilation failed: " + infoLog);
        }
    }
    {
        m_id = glCreateProgram();
        glAttachShader(m_id, vId);
        glAttachShader(m_id, fId);
        glLinkProgram(m_id);
        glGetProgramiv(m_id, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(m_id, 512, nullptr, infoLog);
            throw std::runtime_error(std::string() + "GL Program link failed: " + infoLog);
        }
    }
    glDeleteShader(vId);
    glDeleteShader(fId);
}
