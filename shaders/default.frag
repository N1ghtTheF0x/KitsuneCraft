#version 460 core
out vec4 _output;

uniform vec4 diffuse_rgba;

void main()
{
    _output = diffuse_rgba;
}