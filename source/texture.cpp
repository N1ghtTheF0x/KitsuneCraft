#include <N1ghtTheF0x/KitsuneCraft/Data/Texture.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

namespace N1ghtTheF0x::KitsuneCraft
{
    Texture::Texture(const char *path): _path(path)
    {
        
    }
    Texture::~Texture()
    {
        stbi_image_free(_data);
        glDeleteTextures(1,&_texture);
    }
    Texture::operator GLuint()
    {
        return _texture;
    }
    bool Texture::load()
    {
        _data = stbi_load(_path,&_width,&_height,&_channels,0);
        if(!_data)
        {
            std::cerr << "Couldn't open " << _path << std::endl;
            return false;
        }
        glGenTextures(1,&_texture);
        bind();
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,_width,_height,0,GL_RGB,GL_UNSIGNED_BYTE,_data);
        return true;
    }
    void Texture::bind()
    {
        glBindTexture(GL_TEXTURE_2D,_texture);
    }
    void Texture::activate(GLenum target)
    {
        glActiveTexture(target);
        bind();
    }
    void Texture::activate()
    {
        activate(GL_TEXTURE0);
    }
}