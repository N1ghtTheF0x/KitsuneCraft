#version 460 core

layout (location = 0) in vec3 a_position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    gl_Position = proj * view * model * vec4(a_position.x,a_position.y,a_position.z,1.0);
}