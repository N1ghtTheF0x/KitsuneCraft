#include <N1ghtTheF0x/KitsuneCraft/Context.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <exception>

#include "shaders/fragment.hpp"
#include "shaders/vertex.hpp"

static void kc_check_opengl()
{
    #define THROW(text) std::cerr << text << std::endl; throw std::exception(text);
    auto code = glGetError();
    switch(code)
    {
        case GL_INVALID_ENUM:
            THROW("an enumeration parameter is not legal.");
        case GL_INVALID_VALUE:
            THROW("a value parameter is not legal.");
        case GL_INVALID_OPERATION:
            THROW("the state for a command is not legal for its given parameters.");
        case GL_STACK_OVERFLOW:
            THROW("a stack pushing operation causes a stack overflow.");
        case GL_STACK_UNDERFLOW:
            THROW("a stack popping operation occurs while the stack is at its lowest point.");
        case GL_OUT_OF_MEMORY:
            THROW("a memory allocation operation cannot allocate (enough) memory.");
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            THROW("reading or writing to a framebuffer that is not complete.");
    }
}

static void glDebugOutput(GLenum source, 
                            GLenum type, 
                            unsigned int id, 
                            GLenum severity, 
                            GLsizei length, 
                            const char *message, 
                            const void *userParam)
{
    // ignore non-significant error/warning codes
    if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return; 

    std::cout << "---------------" << std::endl;
    std::cout << "Debug message (" << id << "): " <<  message << std::endl;

    switch (source)
    {
        case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
    } std::cout << std::endl;

    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break; 
        case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
    } std::cout << std::endl;
    
    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
    } std::cout << std::endl;
    std::cout << std::endl;
}

static GLuint compileShader(GLenum type,const char* *source)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader,1,source,NULL);
    glCompileShader(shader);
    int success;
    glGetShaderiv(shader,GL_COMPILE_STATUS,&success);
    if(!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader,512,NULL,infoLog);
        std::cerr << "Couldn't compile shader: " << infoLog << std::endl;
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

static GLuint createProgram(unsigned int fShader,unsigned int vShader)
{
    GLuint program = glCreateProgram();
    glAttachShader(program,fShader);
    glAttachShader(program,vShader);
    glLinkProgram(program);
    int success;
    glGetProgramiv(program,GL_LINK_STATUS,&success);
    if(!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(program,512,NULL,infoLog);
        std::cerr << "Couldn't link program: " << infoLog << std::endl;
        glDeleteProgram(program);
        return 0;
    }
    return program;
}

namespace N1ghtTheF0x::KitsuneCraft
{
    Context::Context()
    {

    }
    Context::~Context()
    {
        glDeleteVertexArrays(1,&_vao);
        glDeleteBuffers(1,&_vbo);
        glDeleteBuffers(1,&_ebo);
        glDeleteProgram(_program);
    }
    void Context::init()
    {
#ifndef NDEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glDebugOutput,nullptr);
        glDebugMessageControl(GL_DONT_CARE,GL_DONT_CARE,GL_DONT_CARE,0,nullptr,GL_TRUE);
#endif
        GLuint vertex = compileShader(GL_VERTEX_SHADER,&vertex_file_data);
        GLuint fragment = compileShader(GL_FRAGMENT_SHADER,&fragment_file_data);
        _program = createProgram(fragment,vertex);
        glGenVertexArrays(1,&_vao);
        glGenBuffers(1,&_vbo);
        glGenBuffers(1,&_ebo);
    }
    void Context::use()
    {
        glUseProgram(_program);
    }
    void Context::clear()
    {
        glClearColor(0.1,0.1,0.1,1);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    void Context::prepare(Mesh &mesh)
    {
        Vertices &verts = mesh.verts;
        auto &indices = mesh.indices;

        glBindVertexArray(_vao);

        glBindBuffer(GL_ARRAY_BUFFER,_vbo);
        glBufferData(GL_ARRAY_BUFFER,sizeof(Vertex) * verts.size(),verts.data(),GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int) * indices.size(),indices.data(),GL_STATIC_DRAW);

        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)0);
        glEnableVertexAttribArray(0); // position
        glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1); // color (rgba)
        glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)((3 + 4) * sizeof(float)));
        glEnableVertexAttribArray(2); // uv
    }
    void Context::draw(GLsizei count,GLenum mode)
    {
        use();
        glBindVertexArray(_vao);
        glDrawElements(mode,count,GL_UNSIGNED_INT,0);
    }
    void Context::drawTri(GLsizei count)
    {
        draw(count,GL_TRIANGLES);
    }
    void Context::drawQuad(GLsizei count)
    {
        draw(count,GL_QUADS);
    }
    void Context::setModel(glm::mat4x4 model)
    {
        glUniformMatrix4fv(glGetUniformLocation(_program,"model"),1,GL_FALSE,glm::value_ptr(model));
    }
    void Context::setView(glm::mat4x4 view)
    {
        glUniformMatrix4fv(glGetUniformLocation(_program,"view"),1,GL_FALSE,glm::value_ptr(view));
    }
    void Context::setProjection(glm::mat4x4 proj)
    {
        glUniformMatrix4fv(glGetUniformLocation(_program,"proj"),1,GL_FALSE,glm::value_ptr(proj));
    }
    void Context::setDiffuseTexture(GLuint texture)
    {
        glUniform1ui(glGetUniformLocation(_program,"diffuse_map"),texture);
    }
}