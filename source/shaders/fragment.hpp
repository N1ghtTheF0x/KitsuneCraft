#ifndef FRAGMENT_FILE_HPP
#define FRAGMENT_FILE_HPP

const unsigned long long fragment_file_size = 138;

const char* fragment_file_data = "#version 460 core\n"
"out vec4 _output;\n"
"\n"
"uniform vec4 diffuse_rgba;\n"
"uniform vec2 tex_uv;\n"
"\n"
"void main()\n"
"{\n"
"    _output = diffuse_rgba;\n"
"}\0";

#endif