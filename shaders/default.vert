#version 460 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec4 a_diffuse_rgba;
layout (location = 2) in vec2 a_tex_uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec4 diffuse_rgba;
out vec2 tex_uv;

void main()
{
    //gl_Position = proj * view * model * vec4(a_position,1.0);
    gl_Position = vec4(a_position,1.0);
    diffuse_rgba = a_diffuse_rgba;
    tex_uv = a_tex_uv;
}