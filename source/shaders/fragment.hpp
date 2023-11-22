#ifndef FRAGMENT_FILE_HPP
#define FRAGMENT_FILE_HPP

const unsigned long long fragment_file_size = 295;

const char* fragment_file_data = "#version 460 core\n"
"out vec4 _output;\n"
"\n"
"in vec4 diffuse_rgba;\n"
"in vec2 tex_uv;\n"
"\n"
"uniform bool has_diffuse_map;\n"
"uniform sampler2D diffuse_map;\n"
"\n"
"void main()\n"
"{\n"
"    if(has_diffuse_map)\n"
"        _output = texture(diffuse_map,tex_uv) * diffuse_rgba;\n"
"    else\n"
"        _output = diffuse_rgba;\n"
"}\0";

#endif