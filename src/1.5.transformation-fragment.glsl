#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    vec4 t1 = texture(texture1, TexCoord);
    vec4 t2 = texture(texture2, TexCoord);
    /* FragColor = vec4( */
    /*       t1.x*0.8+t2.x*0.2, */
    /*       t1.y*0.8+t2.y*0.2, */
    /*       t1.z*0.8+t2.z*0.2, */
    /*       t1.w*0.8+t2.w*0.2); */
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.02);
}
