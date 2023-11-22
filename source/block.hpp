#ifndef __N1GHTTHEF0X_KITSUNECRAFT_BLOCK_HPP
#define __N1GHTTHEF0X_KITSUNECRAFT_BLOCK_HPP

#include "opengl.hpp"

namespace N1ghtTheF0x::KitsuneCraft
{
    class Block
    {
    public:
        typedef signed long long Position;
        enum struct Side
        {
            // 0bTBFBLR
            Top =  1,
            Bottom = Top << 1,
            Front = Bottom << 1,
            Back = Front << 1,
            Left = Back << 1,
            Right = Left << 1
        };
    private:
        int _side = 0b111111;
        Position _x;
        Position _y;
        Position _z;
    public:
        Block(Position x,Position y,Position z);

        Position x() const;
        Position y() const;
        Position z() const;
        void setX(Position x);
        void setY(Position y);
        void setZ(Position z);

        void enableSide(Side side);
        void disableSide(Side side);
        bool enabledSide(Side side);

        void draw(OpenGL &context);
    };
}

#endif