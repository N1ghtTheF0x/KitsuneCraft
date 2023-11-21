#include "opengl.hpp"
#include "sdl.hpp"

#include "shaders/vertex.hpp"
#include "shaders/fragment.hpp"

#include <iostream>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

static unsigned int compileShader(gl::GLenum type,const char* *source)
{
    unsigned int shader = gl::glCreateShader(type);
    gl::glShaderSource(shader,1,source,NULL);
    gl::glCompileShader(shader);
    int success;
    gl::glGetShaderiv(shader,gl::GL_COMPILE_STATUS,&success);
    if(!success)
    {
        char infoLog[512];
        gl::glGetShaderInfoLog(shader,512,NULL,infoLog);
        std::cerr << "Couldn't compile shader: " << infoLog << std::endl;
        gl::glDeleteShader(shader);
        return 0;
    }
    return shader;
}

static unsigned int createProgram(unsigned int fShader,unsigned int vShader)
{
    unsigned int p = gl::glCreateProgram();
    gl::glAttachShader(p,fShader);
    gl::glAttachShader(p,vShader);
    gl::glLinkProgram(p);
    int success;
    gl::glGetProgramiv(p,gl::GL_LINK_STATUS,&success);
    if(!success)
    {
        char infoLog[512];
        gl::glGetProgramInfoLog(p,512,NULL,infoLog);
        std::cerr << "Couldn't link program: " << infoLog << std::endl;
        gl::glDeleteProgram(p);
        return 0;
    }
    return p;
}

namespace N1ghtTheF0x::KitsuneCraft
{
    OpenGL::OpenGL()
    {

    }
    OpenGL::~OpenGL()
    {
        gl::glDeleteProgram(_program);
    }
    void OpenGL::init(const char* *v,const char* *f)
    {
        unsigned int vertexShader = compileShader(gl::GL_VERTEX_SHADER,v);
        unsigned int fragmentShader = compileShader(gl::GL_FRAGMENT_SHADER,f);
        _program = createProgram(fragmentShader,vertexShader);
        _diffuse_rgba_loc = gl::glGetUniformLocation(_program,"diffuse_rgba");
        _model_loc = gl::glGetUniformLocation(_program,"model");
        _view_loc = gl::glGetUniformLocation(_program,"view");
        _proj_loc = gl::glGetUniformLocation(_program,"proj");
        gl::glDeleteShader(vertexShader);
        gl::glDeleteShader(fragmentShader);

        gl::glGenBuffers(1,&_vbo);
        gl::glGenVertexArrays(1,&_vao);
    }
    void OpenGL::init()
    {
        init(&vertex_file_data,&fragment_file_data);
    }
    void OpenGL::use()
    {
        gl::glUseProgram(_program);
    }
    void OpenGL::drawTri(float *verts,size_t size,int count)
    {
        gl::glBindVertexArray(_vao);

        gl::glBindBuffer(gl::GL_ARRAY_BUFFER,_vbo);
        gl::glBufferData(gl::GL_ARRAY_BUFFER,size,verts,gl::GL_STATIC_DRAW);

        gl::glVertexAttribPointer(0,3,gl::GL_FLOAT,gl::GL_FALSE,3 * sizeof(float),(void*)0);
        gl::glEnableVertexAttribArray(0);

        use();
        gl::glBindVertexArray(_vao);
        gl::glDrawArrays(gl::GL_TRIANGLES,0,count);
    }
    void OpenGL::drawQuad(float *verts,size_t size,int count)
    {
        gl::glBindVertexArray(_vao);

        gl::glBindBuffer(gl::GL_ARRAY_BUFFER,_vbo);
        gl::glBufferData(gl::GL_ARRAY_BUFFER,size,verts,gl::GL_STATIC_DRAW);

        gl::glVertexAttribPointer(0,3,gl::GL_FLOAT,gl::GL_FALSE,3 * sizeof(float),(void*)0);
        gl::glEnableVertexAttribArray(0);

        use();
        gl::glBindVertexArray(_vao);
        gl::glDrawArrays(gl::GL_QUADS,0,count);
    }
    void OpenGL::clear()
    {
        gl::glClearColor(0,0,0,1.0f);
        gl::glClear(gl::ClearBufferMask::GL_COLOR_BUFFER_BIT);
    }
    void OpenGL::resize(int w,int h)
    {
        gl::glViewport(0,0,w,h);
    }
    void OpenGL::setDiffuseColor(float r,float g,float b,float a)
    {
        use();
        gl::glUniform4f(_diffuse_rgba_loc,r,g,b,a);
    }
    void OpenGL::setModel(glm::mat4 transform)
    {
        use();
        gl::glUniformMatrix4fv(_model_loc,1,gl::GL_FALSE,glm::value_ptr(transform));
    }
    void OpenGL::setView(glm::mat4 transform)
    {
        use();
        gl::glUniformMatrix4fv(_view_loc,1,gl::GL_FALSE,glm::value_ptr(transform));
    }
    void OpenGL::setProjection(glm::mat4 transform)
    {
        use();
        gl::glUniformMatrix4fv(_proj_loc,1,gl::GL_FALSE,glm::value_ptr(transform));
    }
}