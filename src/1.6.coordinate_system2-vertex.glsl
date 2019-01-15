#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in float textureid;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoord;
out float textureid_;

void main()
{
    /* note that we read the multiplication from right to left */
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    /* gl_Position = vec4(aPos, 1.0); */
    TexCoord = aTexCoord;
    textureid_ = textureid;
}
