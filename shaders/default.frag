#version 460 core
out vec4 _output;

in vec4 diffuse_rgba;
in vec2 tex_uv;

uniform sampler2D diffuse_map;

void main()
{
    _output = diffuse_rgba;
    //_output = texture(diffuse_map,tex_uv) * diffuse_rgba;
}