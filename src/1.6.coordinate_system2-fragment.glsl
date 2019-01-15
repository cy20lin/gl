#version 330 core

in float textureid_;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;

void main()
{
    vec4 t1 = texture(texture1, TexCoord);
    vec4 t2 = texture(texture2, TexCoord);
    /* FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.02); */
    if (textureid_ <= 0.5) {
         /* FragColor = vec4(1,0,0,1); */
         FragColor = texture(texture1, TexCoord);
    } else if (textureid_ <= 1.5) {
         /* FragColor = vec4(0,1,0,1); */
         FragColor = texture(texture2, TexCoord);
    } else if (textureid_ <= 2.5){
         /* FragColor = vec4(0,0,1,1); */
         FragColor = texture(texture3, TexCoord);
    } 
}
