#version 330 core
layout (location = 0) in vec3 pos;

out vec3 Texcoords;

uniform mat4 camera_from_world;
uniform mat4 view_from_camera;

void main()
{
	Texcoords = pos;
	gl_Position = view_from_camera * camera_from_world * vec4(pos,1.0);
};