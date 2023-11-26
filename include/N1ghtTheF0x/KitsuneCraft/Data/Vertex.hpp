#ifndef __N1GHTTHEF0X_KITSUNECRAFT_VERTEX_HPP
#define __N1GHTTHEF0X_KITSUNECRAFT_VERTEX_HPP

#include <vector>

namespace N1ghtTheF0x::KitsuneCraft
{
    struct Vertex
    {
        float x;
        float y;
        float z;

        float red;
        float green;
        float blue;
        float alpha;

        float u;
        float v;
    };
    typedef std::vector<Vertex> Vertices;
}

#endif