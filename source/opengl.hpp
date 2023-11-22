#ifndef __N1GHTTHEF0X_KITSUNECRAFT_OPENGL_HPP
#define __N1GHTTHEF0X_KITSUNECRAFT_OPENGL_HPP

#include <glm.hpp>
#include <vector>
#include "sdl.hpp"

namespace N1ghtTheF0x::KitsuneCraft
{
    class Texture
    {
    private:
        SDL_Surface *_surface = nullptr;
        const char* _path;
        unsigned int _id;
    public:
        Texture(const char* path);
        ~Texture();

        operator SDL_Surface*() const;
        operator unsigned int() const;

        bool load();
        void bind() const;
        void active() const;
        void active(gl::GLenum tex) const;
    };
    class Vertex
    {
    private:
        union {
            // Position
            float _x;
            float _y;
            float _z;
            // Color
            float _r;
            float _g;
            float _b;
            float _a;
            // UV
            float _u;
            float _v;
            // All in one array
            float _fields[9];
        };
    public:
        Vertex(float x,float y,float z) {_x = x;_y = y;_z = z;_r = _g = _b = _a = 1.0f;}
        Vertex(float x,float y,float z,float red,float green,float blue,float alpha = 1.0f): Vertex(x,y,z) {_r = red;_g = green;_b = blue;_a = alpha;}
        Vertex(float x,float y,float z,float red,float green,float blue,float alpha,float u,float v): Vertex(x,y,z,red,green,blue,alpha) {_u = u;_v = v;}

        float x() const {return _x;}
        float y() const {return _y;}
        float z() const {return _z;}

        float red() const {return _r;}
        float green() const {return _g;}
        float blue() const {return _b;}
        float alpha() const {return _a;}

        float u() const {return _u;}
        float v() const {return _v;}

        operator float*() const {return (float*)_fields;}

        void setPosition(float x,float y,float z) {_x = x;_y = y;_z = z;}
        void setColor(float red,float green,float blue,float alpha = 1.0f) {_r = red;_g = green;_b = blue;_a = alpha;}
        void setTexCoords(float u,float v) {_u = u;_v = v;}
    };
    typedef std::vector<Vertex> Vertices;
    static std::vector<float> prepareVertexArray(const Vertices &verts)
    {
        std::vector<float> arr;
        for(auto &v : verts)
        for(size_t i = 0;i < 9;i++)
            arr.push_back(v[i]);
        return arr;
    }
    class OpenGL
    {
    private:
        unsigned int _program;
        unsigned int _vbo;
        unsigned int _vao;
        // Fragment
        int _diffuse_rgba_loc;
        int _has_diffuse_map_loc;
        int _diffuse_map_loc;
        int _tex_uv_loc;
        // Vertex
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
        void drawTri(const Vertices &verts);
        void drawQuad(float* verts,size_t size,int count);
        void drawQuad(const Vertices &verts);
        void clear();
        void resize(int w,int h);
        void setDiffuseTexture(const Texture &tex);
        void setModel(glm::mat4 transform);
        void setView(glm::mat4 transform);
        void setProjection(glm::mat4 transform);
    };
}

#endif