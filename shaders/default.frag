#version 460 core
out vec4 _output;

uniform vec4 diffuse_rgba;

uniform bool has_diffuse_map;
uniform sampler2D diffuse_map;

uniform vec2 tex_uv;

void main()
{
    if(has_diffuse_map)
        _output = texture(diffuse_map,tex_uv) * diffuse_rgba;
    else
        _output = diffuse_rgba;
}