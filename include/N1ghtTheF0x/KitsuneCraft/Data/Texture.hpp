#ifndef __N1GHTTHEF0X_KITSUNECRAFT_TEXTURE_HPP
#define __N1GHTTHEF0X_KITSUNECRAFT_TEXTURE_HPP

#include "../SDL.hpp"

namespace N1ghtTheF0x::KitsuneCraft
{
    class Texture
    {
    private:
        GLuint _texture;
        const char* _path;
        unsigned char* _data = NULL;
        int _width;
        int _height;
        int _channels;
    public:
        Texture(const char* path);
        ~Texture();

        operator GLuint();
        bool load();
        void bind();
        void activate();
        void activate(GLenum target);
    };
}

#endif