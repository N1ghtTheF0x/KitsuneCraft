#ifndef __N1GHTTHEF0X_KITSUNECRAFT_OPENGL_HPP
#define __N1GHTTHEF0X_KITSUNECRAFT_OPENGL_HPP

#include <glm.hpp>

namespace N1ghtTheF0x::KitsuneCraft
{
    class OpenGL
    {
    private:
        unsigned int _program;
        unsigned int _vbo;
        unsigned int _vao;
        int _diffuse_rgba_loc;
        int _model_loc;
        int _view_loc;
        int _proj_loc;
    public:
        OpenGL();
        ~OpenGL();
        void init();
        void init(const char* *vShader,const char* *fShader);
        void use();
        void drawTri(float* verts,size_t size,int count);
        void drawQuad(float* verts,size_t size,int count);
        void clear();
        void resize(int w,int h);
        void setDiffuseColor(float r,float g,float b,float a = 1.0f);
        void setModel(glm::mat4 transform);
        void setView(glm::mat4 transform);
        void setProjection(glm::mat4 transform);
    };
}

#endif