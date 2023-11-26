#ifndef __N1GHTTHEF0X_KITSUNECRAFT_MESH_HPP
#define __N1GHTTHEF0X_KITSUNECRAFT_MESH_HPP

#include "Vertex.hpp"
#include <vector>

namespace N1ghtTheF0x::KitsuneCraft
{
    struct Mesh
    {
        Vertices verts;
        std::vector<unsigned int> indices;
    };
}

#endif