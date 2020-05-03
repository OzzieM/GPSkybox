#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include<iostream>
#include<vector>
#include<ostream>
#include<fstream>
#include<sstream>
#include<string>
#include"glm.hpp"
#include"gtc/type_ptr.hpp" 
#include<algorithm>
#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"

using namespace std;

struct Model
{
    GLuint vao;
    GLuint vbo;
    GLsizei vertex_count;

    static Model load(string test)
    {
        Model model;

        vector<GLfloat> vertices;
        {
            //load geometry from file
            {
                fstream file(test);
                if (!file)
                {
                    cout << "could not find model file\n";
                    abort();
                }
                vector<glm::vec3> positions;
                vector<glm::vec3> normals;
                vector<glm::vec2> texcoords;
                string line;
                while (getline(file, line))
                {
                    //cout << line << "\n";
                    istringstream line_stream(line);
                    
                    string type;
                    line_stream >> type;

                    if (type == "v")
                    {
                        GLfloat x, y, z;
                        line_stream >> x;
                        line_stream >> y;
                        line_stream >> z;
                        positions.push_back(glm::vec3(x, y, z));
                    }
                    else if (type == "vt")
                    {
                        GLfloat u,v;
                        line_stream >> u;
                        line_stream >> v;
                        texcoords.push_back(glm::vec2(u,v));
                    }
                    else if (type == "vn")
                    {
                        GLfloat x, y, z;
                        line_stream >> x;
                        line_stream >> y;
                        line_stream >> z;
                        normals.push_back(glm::vec3(x, y, z));
                    }
                    else if (type == "f")
                    {
                        string face;
                            
                        //vertex 0 
                            line_stream >> face;
                            replace(face.begin(), face.end(), '/', ' ');
                            
                            size_t position_index0;
                            size_t texcoord_index0;
                            size_t normal_index0;

                            istringstream face_stream0(face);
                            face_stream0 >> position_index0;
                            face_stream0 >> texcoord_index0;
                            face_stream0 >> normal_index0;
                            
                            glm::vec3 position0 = positions.at(position_index0-1);
                            glm::vec2 texcoord0 = texcoords.at(texcoord_index0 - 1);
                            glm::vec3 normal0 = normals.at(normal_index0 - 1);

                         
                        
                        //vertex 1
                            line_stream >> face;
                            replace(face.begin(), face.end(), '/', ' ');

                            size_t position_index1;
                            size_t texcoord_index1;
                            size_t normal_index1;

                            istringstream face_stream1(face);
                            face_stream1 >> position_index1;
                            face_stream1 >> texcoord_index1;
                            face_stream1 >> normal_index1;

                            glm::vec3 position1 = positions.at(position_index1 - 1);
                            glm::vec2 texcoord1 = texcoords.at(texcoord_index1 - 1);
                            glm::vec3 normal1 = normals.at(normal_index1 - 1);

                           
                        //vertex 2
                            line_stream >> face;
                            replace(face.begin(), face.end(), '/', ' ');

                            size_t position_index2;
                            size_t texcoord_index2;
                            size_t normal_index2;

                            istringstream face_stream2(face);
                            face_stream2 >> position_index2;
                            face_stream2 >> texcoord_index2;
                            face_stream2 >> normal_index2;

                            glm::vec3 position2 = positions.at(position_index2 - 1);
                            glm::vec2 texcoord2 = texcoords.at(texcoord_index2 - 1);
                            glm::vec3 normal2 = normals.at(normal_index2 - 1);


                            //tangent and bitangent 
                            glm::vec3 edge0 = position1 - position0;
                            glm::vec3 edge1 = position2 - position0;
                            glm::vec2 delta_texcoords0 = texcoord1 - texcoord0;
                            glm::vec2 delta_texcoords1 = texcoord2 - texcoord0;

                            float f = 1.0f / (delta_texcoords0.x * delta_texcoords1.y - delta_texcoords1.x * delta_texcoords0.y);

                            glm::vec3 tangent;
                            tangent.x = f * (delta_texcoords1.y * edge0.x - delta_texcoords0.y * edge1.x);
                            tangent.y = f * (delta_texcoords1.y * edge0.y - delta_texcoords0.y * edge1.y);
                            tangent.z = f * (delta_texcoords1.y * edge0.z - delta_texcoords0.y * edge1.z);
                            tangent = glm::normalize(tangent);


                            glm::vec3 bitangent;
                            bitangent.x = f * (-delta_texcoords1.x * edge0.x - delta_texcoords0.x * edge1.x);
                            bitangent.y = f * (-delta_texcoords1.x * edge0.y - delta_texcoords0.x * edge1.y);
                            bitangent.z = f * (-delta_texcoords1.x * edge0.z - delta_texcoords0.x * edge1.z);
                            bitangent = glm::normalize(bitangent);


                            //push everything
                            vertices.push_back(position0.x);
                            vertices.push_back(position0.y);
                            vertices.push_back(position0.z);
                            vertices.push_back(texcoord0.x);
                            vertices.push_back(texcoord0.y);
                            vertices.push_back(normal0.x);
                            vertices.push_back(normal0.y);
                            vertices.push_back(normal0.z);
                            vertices.push_back(tangent.x);
                            vertices.push_back(tangent.y);
                            vertices.push_back(tangent.z);
                            vertices.push_back(bitangent.x);
                            vertices.push_back(bitangent.y);
                            vertices.push_back(bitangent.z);



                            vertices.push_back(position1.x);
                            vertices.push_back(position1.y);
                            vertices.push_back(position1.z);
                            vertices.push_back(texcoord1.x);
                            vertices.push_back(texcoord1.y);
                            vertices.push_back(normal1.x);
                            vertices.push_back(normal1.y);
                            vertices.push_back(normal1.z);
                            vertices.push_back(tangent.x);
                            vertices.push_back(tangent.y);
                            vertices.push_back(tangent.z);
                            vertices.push_back(bitangent.x);
                            vertices.push_back(bitangent.y);
                            vertices.push_back(bitangent.z);
                            
                            vertices.push_back(position2.x);
                            vertices.push_back(position2.y);
                            vertices.push_back(position2.z);
                            vertices.push_back(texcoord2.x);
                            vertices.push_back(texcoord2.y);
                            vertices.push_back(normal2.x);
                            vertices.push_back(normal2.y);
                            vertices.push_back(normal2.z);
                            vertices.push_back(tangent.x);
                            vertices.push_back(tangent.y);
                            vertices.push_back(tangent.z);
                            vertices.push_back(bitangent.x);
                            vertices.push_back(bitangent.y);
                            vertices.push_back(bitangent.z);
                    }
               

                }
            }
           
            model.vertex_count = vertices.size();

            {
                //create vertex buffer object on GPU
                glGenBuffers(1, &model.vbo);
                //set to current buffer 
                glBindBuffer(GL_ARRAY_BUFFER, model.vbo);
                //copy data to current buffer
                glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
            }
        }
        {
            //create VAO
            glGenVertexArrays(1, &model.vao);
            //set as current vertex array
            glBindVertexArray(model.vao);

            GLsizei stride = 14 * sizeof(GLfloat);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(GLfloat)));
            glEnableVertexAttribArray(1);

            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(5 * sizeof(GLfloat)));
            glEnableVertexAttribArray(2);


            glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (void*)(8 * sizeof(GLfloat)));
            glEnableVertexAttribArray(3);
            glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, stride, (void*)(11 * sizeof(GLfloat)));
            glEnableVertexAttribArray(4);
        }
        return model;
    }

    void cleanup()
    {
        glDeleteVertexArrays(1, &this->vao);
        glDeleteBuffers(1, &this->vbo);
    }

    void draw()
    {
        glBindVertexArray(this->vao);
        glDrawArrays(GL_TRIANGLES, 0, this->vertex_count);
    }
};

struct Camera
{
    glm::mat4 camera_from_world = glm::mat4(1);
    float fov = 60.0f;
    float near = 0.01f;
    float far = 1000.0f;
    glm::mat4 view_from_camera(GLFWwindow* window)
    {
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        glViewport(0.0f, 0.0f, width, height);
        return glm::perspective(glm::radians(this->fov), float(width) / float(height), this->near, this->far);

        //GLint view_from_camera_location = glGetUniformLocation(shader_program, "view_from_camera");
        //glUniformMatrix4fv(view_from_camera_location, 1, GL_FALSE, glm::value_ptr(view_from_camera));
    }

};
class Particle
{
public:

    glm::mat4 world_from_model;
    glm::vec3 velocity;
    Model model;
    string name;


    Particle(glm::mat4 world_from_model, glm::vec3 velocity, Model model, string name)
    {  
        this->model = model;
        this->world_from_model = world_from_model;
        this->velocity = velocity;
        this->name = name;
    }
};

GLuint load_textures(GLenum active_texture, const char *filename)
{
    GLuint tex;
    glActiveTexture(active_texture);

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    GLsizei width = 0;
    GLsizei height = 0;

    GLubyte* pixels = stbi_load(filename, &width, &height, NULL, 3);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, pixels);
    return tex;
}

GLuint load_cubemap(
    GLenum active_texture, 
    const char* left,
    const char* right,
    const char* front,
    const char* back,
    const char* top,
    const char* bottom)
{
    GLuint tex;
    glActiveTexture(active_texture);

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_CUBE_MAP, tex);


    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    {
        GLsizei width = 0;
        GLsizei height = 0;

        GLubyte* pixels = stbi_load(right, &width, &height, NULL, 3);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, pixels);
    }
    {
        GLsizei width = 0;
        GLsizei height = 0;

        GLubyte* pixels = stbi_load(left, &width, &height, NULL, 3);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, pixels);
    }
    {
        GLsizei width = 0;
        GLsizei height = 0;

        GLubyte* pixels = stbi_load(top, &width, &height, NULL, 3);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, pixels);
    }
    {
        GLsizei width = 0;
        GLsizei height = 0;

        GLubyte* pixels = stbi_load(bottom, &width, &height, NULL, 3);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, pixels);
    }
    {
        GLsizei width = 0;
        GLsizei height = 0;

        GLubyte* pixels = stbi_load(front, &width, &height, NULL, 3);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, pixels);
    }
    {
        GLsizei width = 0;
        GLsizei height = 0;

        GLubyte* pixels = stbi_load(back, &width, &height, NULL, 3);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, pixels);
    }
    return tex;
}

GLFWwindow *initialize_glfw()
{

    if(!glfwInit())
    {
        cout << "glfwINIT( ) failed \n";
        abort();
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        cout << "glfwCreateWindow failed \n";
        glfwTerminate();
        abort();
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();
    glEnable(GL_DEPTH_TEST);
    return window;
}

GLuint compile_shader(const char* vertex_filename, const char* fragment_filename)
{
    ifstream vertex_shader_file(vertex_filename);
    stringstream vertex_shader_stream;
    vertex_shader_stream << vertex_shader_file.rdbuf();
    string vertex_shader_string = vertex_shader_stream.str();
    const char* vertex_shader_source = vertex_shader_string.c_str();

    ifstream fragment_shader_file(fragment_filename);
    stringstream fragment_shader_stream;
    fragment_shader_stream << fragment_shader_file.rdbuf();
    string fragment_shader_string = fragment_shader_stream.str();
    const char* fragment_shader_source = fragment_shader_string.c_str();
   

    if (!vertex_shader_file)
        cout << vertex_filename <<" vertex file not found\n";

    if (!fragment_shader_file)
        cout<<fragment_filename << "fragment file not found\n";
    //compile vertex
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    //compile fragment
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    //link shaders
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    //delete shaders when done attaching
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    return program;
}

void render_scene(GLFWwindow* window, Model model, GLuint shader_program, GLuint sky_shader_program, vector<Particle> &particles,Camera camera)
{

    //set clear color
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    //glClearColor(0.7f, 0.0f, 0.5f, 1.0f);

    ////clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDepthMask(GL_FALSE);
    {
        glUseProgram(sky_shader_program);

        //camera from world
        GLint camera_from_world_location = glGetUniformLocation(shader_program, "camera_from_world");
        glm::mat4 camera_from_world_no_translation = glm::mat4(glm::mat3(camera.camera_from_world));

        glUniformMatrix4fv(camera_from_world_location, 1, GL_FALSE, glm::value_ptr(camera_from_world_no_translation));

        ////view from camera
        GLint view_from_camera_location = glGetUniformLocation(sky_shader_program, "view_from_camera");
        glUniformMatrix4fv(view_from_camera_location, 1, GL_FALSE, glm::value_ptr(camera.view_from_camera(window)));

        ////color location
        GLint color_location = glGetUniformLocation(sky_shader_program, "color");
        glUniform4f(color_location, 0.0f, 0.9f, 1.0f, 1.0f);

        GLint skymap_location = glGetUniformLocation(sky_shader_program, "skybox");
        glUniform1i(skymap_location, 3);

        //particles[0].world_from_model = glm::translate(particles[0].world_from_model, particles[0].velocity);
        //particles[0].world_from_model = glm::rotate(particles[0].world_from_model, 0.01f, glm::vec3(1.0f, 1.0f, 1.0f));

        GLint world_from_model_location = glGetUniformLocation(sky_shader_program, "world_from_model");
        glUniformMatrix4fv(world_from_model_location, 1, GL_FALSE, glm::value_ptr(particles[0].world_from_model));

        glm::vec4 position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        position = particles[0].world_from_model * position;

        particles[0].model.draw();
    }
    glDepthMask(GL_TRUE);

    {
        glUseProgram(shader_program);

        //camera from world
        GLint camera_from_world_location = glGetUniformLocation(shader_program, "camera_from_world");
        glUniformMatrix4fv(camera_from_world_location, 1, GL_FALSE, glm::value_ptr(camera.camera_from_world));

        ////view from camera
        GLint view_from_camera_location = glGetUniformLocation(shader_program, "view_from_camera");
        glUniformMatrix4fv(view_from_camera_location, 1, GL_FALSE, glm::value_ptr(camera.view_from_camera(window)));

        ////color location
    /*    GLint color_location = glGetUniformLocation(shader_program, "color");
        glUniform4f(color_location, 0.0f, 0.9f, 1.0f, 1.0f);*/

        ////texture location
    /*    GLuint diffuse_map_location = glGetUniformLocation(shader_program, "diffuse_map");
        glUniform1i(diffuse_map_location, 0);

        GLuint specular_map_location = glGetUniformLocation(shader_program, "specular_map");
        glUniform1i(specular_map_location, 1);

        GLuint normal_map_location = glGetUniformLocation(shader_program, "normal_map");
        glUniform1i(normal_map_location, 2);

        GLuint sky_box_location = glGetUniformLocation(shader_program, "skybox");
        glUniform1i(sky_box_location, 3);*/


        for (int i = 0; i < particles.size();i++)
        {
            Particle* particle = &(particles)[i];
            if (particle->name == "monkey-normals.obj")
            {
                GLuint diffuse_map_location = glGetUniformLocation(shader_program, "diffuse_map");
                glUniform1i(diffuse_map_location, 7);

                GLuint specular_map_location = glGetUniformLocation(shader_program, "specular_map");
                glUniform1i(specular_map_location, 8);

                GLuint normal_map_location = glGetUniformLocation(shader_program, "normal_map");
                glUniform1i(normal_map_location, 9);
            }
            if (particle->name == "sphere-normals.obj")
            {
                GLuint diffuse_map_location = glGetUniformLocation(shader_program, "diffuse_map");
                glUniform1i(diffuse_map_location, 4);

                GLuint specular_map_location = glGetUniformLocation(shader_program, "specular_map");
                glUniform1i(specular_map_location, 5);

                GLuint normal_map_location = glGetUniformLocation(shader_program, "normal_map");
                glUniform1i(normal_map_location, 6);
            }
    
            if (particle->name == "teapot-normals.obj")
            {
                GLuint diffuse_map_location = glGetUniformLocation(shader_program, "diffuse_map");
                glUniform1i(diffuse_map_location, 0);

                GLuint specular_map_location = glGetUniformLocation(shader_program, "specular_map");
                glUniform1i(specular_map_location, 1);

                GLuint normal_map_location = glGetUniformLocation(shader_program, "normal_map");
                glUniform1i(normal_map_location, 2);

            }
            if (particle->name == "cube-normals.obj")
            {
                GLuint diffuse_map_location = glGetUniformLocation(shader_program, "diffuse_map");
                glUniform1i(diffuse_map_location, 10);

                GLuint specular_map_location = glGetUniformLocation(shader_program, "specular_map");
                glUniform1i(specular_map_location, 11);

                GLuint normal_map_location = glGetUniformLocation(shader_program, "normal_map");
                glUniform1i(normal_map_location, 12);
            }

            GLuint sky_box_location = glGetUniformLocation(shader_program, "skybox");
            glUniform1i(sky_box_location, 3);

            GLint light_location = glGetUniformLocation(shader_program, "lightPos");
            glUniform3f(light_location, 1.0, 1.0, 1.0);

            //base settings
            GLint ambient_location = glGetUniformLocation(shader_program, "ambientColor");
            glUniform3f(ambient_location, 0.2, 0.0, 0.2);

            GLint specularColor_location = glGetUniformLocation(shader_program, "specularColor");
            glUniform3f(specularColor_location, 1.0, 1.0, 1.0);

            GLint specularStrength_location = glGetUniformLocation(shader_program, "specularStrength");
            glUniform1f(specularStrength_location, 0.2);

            GLint specularHardness_location = glGetUniformLocation(shader_program, "specularHardness");
            glUniform1f(specularHardness_location, 4);


            //particle->world_from_model = glm::translate(particle->world_from_model, particle->velocity);
            //particle->world_from_model = glm::rotate(particle->world_from_model, 0.01f, glm::vec3(1.0f, 1.0f, 1.0f));

            GLint world_from_model_location = glGetUniformLocation(shader_program, "world_from_model");
            glUniformMatrix4fv(world_from_model_location, 1, GL_FALSE, glm::value_ptr(particle->world_from_model));

            glm::vec4 position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
            position = particle->world_from_model * position;

            particle->model.draw();
        }
    }
    //display the results on the screen
    glfwSwapBuffers(window);
}

void cleanup(GLuint shader_program, GLuint sky_shader_program, Model model, vector<GLuint> *textures, vector<Particle> particles)
{
    glDeleteTextures(textures->size(), &(*textures)[0]);
    glDeleteProgram(shader_program);
    glDeleteProgram(sky_shader_program);

    model.cleanup();
    for (auto i = 0;i < particles.size();i++)
        particles[i].model.cleanup();
    //glDeleteTextures(1, &tex);
    glfwTerminate();
}

int main(void)
{
    GLFWwindow* window = initialize_glfw();
    vector<Model> models;
    GLuint shader_program = compile_shader("VertexShader.vert", "FragmentShader.frag");
    GLuint sky_shader_program = compile_shader("sky.vert", "sky.frag");
    Model model = Model::load("monkey-normals.obj");
    Model model1 = Model::load("sphere-normals.obj");
    Model model2 = Model::load("teapot-normals.obj");
    Model model3 = Model::load("cube-normals.obj");

    vector<GLuint> textures;

   /* models.push_back(model);
    models.push_back(model1);*/
    //diffuse
    textures.push_back(load_textures(GL_TEXTURE0, "PavingStones036_2K_Color.jpg"));
    //specular map
    textures.push_back(load_textures(GL_TEXTURE1, "PavingStones036_2K_Roughness.jpg"));
    //normal map
    textures.push_back(load_textures(GL_TEXTURE2, "PavingStones036_2K_Normal.jpg"));
    //skybox
    textures.push_back(
        load_cubemap(
            GL_TEXTURE3, 
            "cyberpunk/left.png",
            "cyberpunk/right.png",
            "cyberpunk/front.png",
            "cyberpunk/back.png",
            "cyberpunk/top.png",
            "cyberpunk/bottom.png"
        ));

    textures.push_back(load_textures(GL_TEXTURE4, "metal/Metal012_2K_Color.jpg"));
    //specular map
    textures.push_back(load_textures(GL_TEXTURE5, "metal/Metal012_2K_Roughness.jpg"));
    //normal map
    textures.push_back(load_textures(GL_TEXTURE6, "metal/Metal012_2K_Normal.jpg"));

    textures.push_back(load_textures(GL_TEXTURE7, "rock2/Rock035_2K_Color.jpg"));
    //specular map
    textures.push_back(load_textures(GL_TEXTURE8, "rock2/Rock035_2K_Roughness.jpg"));
    //normal map
    textures.push_back(load_textures(GL_TEXTURE9, "rock2/Rock035_2K_Normal.jpg"));

    textures.push_back(load_textures(GL_TEXTURE10, "brick/castle_brick_02_red_diff_2k.jpg"));
    //specular map
    textures.push_back(load_textures(GL_TEXTURE11, "brick/castle_brick_02_red_rough_2k.jpg"));
    //normal map
    textures.push_back(load_textures(GL_TEXTURE12, "brick/castle_brick_02_red_nor_2k.jpg"));

    
    vector<Particle> particles;
 
    particles.push_back(Particle(
        glm::translate(glm::mat4(1), glm::vec3(0.0f, 0.0f, 0.0f)),
        glm::vec3(0.0f, 0.0f, 0.0f), model3, "cube-normals.obj"
    ));
    particles.push_back(Particle(
        glm::translate(glm::mat4(1), glm::vec3(-3.5f, 0.0f, 0.0f)), 
        glm::vec3(0.0f, 0.0f, 0.0f), model, "monkey-normals.obj"
    ));

    particles.push_back(Particle(
        glm::translate(glm::mat4(1), glm::vec3(3.5f, 0.0f, 0.0f)),
        glm::vec3(0.0f, 0.0f, 0.0f), model1,"sphere-normals.obj"
    ));

    particles.push_back(Particle(
        glm::translate(glm::mat4(1), glm::vec3(0.0f, 3.0f, 0.0f)),
        glm::vec3(0.0f, 0.0f, 0.0f), model1,"teapot-normals.obj"
    ));



    Camera camera;
    glm::mat4 camera_from_world = glm::mat4(1);
    camera.camera_from_world = glm::translate(camera.camera_from_world, glm::vec3(0.0f,-2.0f, -13.0f));

    GLint world_to_camera_location = glGetUniformLocation(shader_program, "camera_from_world");
    //camera.camera_from_world = glm::rotate(camera.camera_from_world, 0.012f, glm::vec3(3.0f, 0.0f, 0.0f));

    bool was_focused = false;
    while (!glfwWindowShouldClose(window))
    {
       camera.camera_from_world = glm::rotate(camera.camera_from_world, 0.005f, glm::vec3(0.0f, 1.0f, 0.0f));
        bool is_focused = glfwGetWindowAttrib(window, GLFW_FOCUSED) == 1;
        //if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)//if (!was_focused && is_focused)

        if (!was_focused && is_focused)
        {

           cout << "Gained focus\n";
           glDeleteProgram(shader_program);
           shader_program = compile_shader("VertexShader.vert", "FragmentShader.frag");
        }
        was_focused = is_focused;
 

        //camera_from_world = glm::translate(camera_from_world, glm::vec3(.01f, 0.0f, 0.0f));
        //camera_from_world = glm::rotate(camera_from_world, 0.001f, glm::vec3(0.0f, 0.0f, 1.0f));

        //render scene
        render_scene(window, model, shader_program, sky_shader_program,  particles, camera);
        glfwPollEvents();
    }

    cleanup(shader_program, sky_shader_program, model, &textures, particles);
    return 0;
}