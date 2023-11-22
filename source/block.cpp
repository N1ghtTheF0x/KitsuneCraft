#include "block.hpp"

static float block_top[] = {
    // Top
    1.0f,1.0f,-1.0f,
    -1.0f,1.0f,-1.0f,
    -1.0f,1.0f,1.0f,
    1.0f,1.0f,1.0f,
};
static float block_bottom[] = {
    // Bottom
    1.0f,-1.0f,1.0f,
    -1.0f,-1.0f,1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
};
static float block_front[] = {
    // Front
    1.0f,1.0f,1.0f,
    -1.0f,1.0f,1.0f,
    -1.0f,-1.0f,1.0f,
    1.0f,-1.0f,1.0f,
};
static float block_back[] = {
    // Back
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,1.0f,-1.0f,
    1.0f,1.0f,-1.0f,
};
static float block_left[] = {
    // Left
    -1.0f,1.0f,1.0f,
    -1.0f,1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,1.0f,
};
static float block_right[] = {
    // Right
    1.0f,1.0f,-1.0f,
    1.0f,1.0f,1.0f,
    1.0f,-1.0f,1.0f,
    1.0f,-1.0f,-1.0f,
};

namespace N1ghtTheF0x::KitsuneCraft
{
    using Position = Block::Position;
    using Side = Block::Side;
    Block::Block(Position x,Position y,Position z):
        _x(x), _y(y), _z(z)
    {

    }
    Position Block::x() const {return _x;}
    Position Block::y() const {return _y;}
    Position Block::z() const {return _z;}
    void Block::setX(Position x) {_x = x;}
    void Block::setY(Position y) {_y = y;}
    void Block::setZ(Position z) {_z = z;}

    void Block::enableSide(Side side)
    {
        _side |= (int)side;
    }
    void Block::disableSide(Side side)
    {
        _side &= ~(int)side;
    }
    bool Block::enabledSide(Side side)
    {
        return (_side & (int)side) == (int)side;
    }
    void Block::draw(OpenGL &context)
    {
        int count = 4;
        auto size = sizeof(float) *  3 * count;
        if(enabledSide(Side::Top))
        {
            context.setDiffuseColor(1,0,0);
            context.drawQuad(block_top,size,count);
        }
        if(enabledSide(Side::Bottom))
        {
            context.setDiffuseColor(0,1,0);
            context.drawQuad(block_bottom,size,count);
        }
        if(enabledSide(Side::Front))
        {
            context.setDiffuseColor(0,0,1);
            context.drawQuad(block_front,size,count);
        }
        if(enabledSide(Side::Back))
        {
            context.setDiffuseColor(1,1,0);
            context.drawQuad(block_back,size,count);
        }
        if(enabledSide(Side::Left))
        {
            context.setDiffuseColor(0,1,1);
            context.drawQuad(block_left,size,count);
        }
        if(enabledSide(Side::Right))
        {
            context.setDiffuseColor(1,0,1);
            context.drawQuad(block_right,size,count);
        }
    }
}