#ifndef LEARNOPENGL_SRC_SHADER_HPP_INCLUDED
#define LEARNOPENGL_SRC_SHADER_HPP_INCLUDED


class Shader {
public:
    unsigned int m_id;
    Shader(const char * vertexPath, const char * fragmentPath);
    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const char * name, bool value);
    void setInt(const char * name, int value);
    void setFloat(const char * name, float value);
};


#endif // LEARNOPENGL_SRC_SHADER_HPP_INCLUDED
