#ifndef __N1GHTTHEF0X_KITSUNECRAFT_CONTEXT_HPP
#define __N1GHTTHEF0X_KITSUNECRAFT_CONTEXT_HPP

#include "SDL.hpp"
#include "Data/Mesh.hpp"
#include "Data/Texture.hpp"

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>

namespace N1ghtTheF0x::KitsuneCraft
{
    class Context
    {
    private:
        GLuint _program;

        GLuint _vbo;
        GLuint _vao;
        GLuint _ebo;
    public:
        Context();
        ~Context();

        void init();
        void use();

        void clear();
        void prepare(Mesh &verts);
        void draw(GLsizei count,GLenum mode);
        void drawTri(GLsizei count);
        void drawQuad(GLsizei count);

        void setModel(glm::mat4x4 model);
        void setView(glm::mat4x4 view);
        void setProjection(glm::mat4x4 proj);
        void setDiffuseTexture(GLuint texture);
    };
}

#endif