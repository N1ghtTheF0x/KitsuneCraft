#ifndef VERTEX_FILE_HPP
#define VERTEX_FILE_HPP

const unsigned long long vertex_file_size = 444;

const char* vertex_file_data = "#version 460 core\n"
"\n"
"layout (location = 0) in vec3 a_position;\n"
"layout (location = 1) in vec4 a_diffuse_rgba;\n"
"layout (location = 2) in vec2 a_tex_uv;\n"
"\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 proj;\n"
"\n"
"out vec4 diffuse_rgba;\n"
"out vec2 tex_uv;\n"
"\n"
"void main()\n"
"{\n"
"    //gl_Position = proj * view * model * vec4(a_position,1.0);\n"
"    gl_Position = vec4(a_position,1.0);\n"
"    diffuse_rgba = a_diffuse_rgba;\n"
"    tex_uv = a_tex_uv;\n"
"}\0";

#endif