#version 330 core
out vec4 FragColor;
in vec2 Texcoords;
in vec3 Normal;
in vec3 world_space_position;
in vec3 world_space_camera_position;
in mat3 TBN;

uniform sampler2D diffuse_map;
uniform sampler2D specular_map;
uniform sampler2D normal_map;
uniform samplerCube skybox;

//2nd camera
in vec3 world_space_camera_position2;
//uniforms for manipulating lighting
uniform vec3 ambientColor;
uniform float specularStrength;
uniform float specularHardness;
uniform vec3 specularColor;
uniform vec3 lightPos;



void main()
{
//lightPos = vec3(1.0,1.0,1.0)

//light settings 
//vec3 light_dir = lightPos;
      //ambient lighting
    vec3 diffuse_map_color = vec3(texture(diffuse_map, Texcoords));

    vec3 ambient = diffuse_map_color *2.0* vec3(0.18, 0.18, 0.18);
    vec3 light_color = 0.8*vec3(0.6, 0.6, 0.6) - ambient *0.5;
    vec3 specular_color = specularStrength * specularColor;
    vec3 normal = vec3(texture(normal_map, Texcoords));
    normal = normal * 2.0 - 1.0;
    normal = TBN * normal;
    normal = normalize(normal);

    //diffuse lighting
    float diffuse_intensity = max(dot(normal,lightPos),0.0);
    //diffuse_map_color += vec3(texture(specular_map, Texcoords));
    vec3 diffuse = diffuse_map_color * diffuse_intensity * light_color;
    //specular lighting
    vec3 view_direction = normalize(world_space_camera_position - world_space_position);
    vec3 reflect_direction = reflect(-lightPos, normal);
    float specular_intensity = pow(max(dot(view_direction, reflect_direction),0.0), specularHardness);
    specular_intensity *= 1.0 - (texture(specular_map, Texcoords).r);
    vec3 specular = specular_intensity * specular_color;

    //reflection
    vec3 I = normalize(world_space_position - world_space_camera_position);
    vec3 Reflect = reflect(I, normal);
    vec3 Refract = refract(I, normal, 1.0/1.52);
    vec3 reflection = texture(skybox, Reflect).xyz;
    vec3 refraction = texture(skybox, Refract).xyz;
    vec3 mixed = mix(reflection, refraction,0.5f);
    //final output
    FragColor = vec4(ambient+diffuse+specular*mixed, 1.0);
};
