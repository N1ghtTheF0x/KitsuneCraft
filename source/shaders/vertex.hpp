#ifndef VERTEX_FILE_HPP
#define VERTEX_FILE_HPP

const unsigned long long vertex_file_size = 237;

const char* vertex_file_data = "#version 460 core\n"
"\n"
"layout (location = 0) in vec3 a_position;\n"
"\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 proj;\n"
"\n"
"void main()\n"
"{\n"
"    gl_Position = proj * view * model * vec4(a_position.x,a_position.y,a_position.z,1.0);\n"
"}\0";

#endif