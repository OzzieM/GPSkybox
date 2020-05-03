#version 330 core

out vec4 FragColor;

in vec3 Texcoords;



uniform samplerCube skybox;


void main()
{

    //final output
    FragColor = vec4(texture(skybox, Texcoords).rgb,1.0);
};

