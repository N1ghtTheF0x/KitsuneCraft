#include "block.hpp"

static N1ghtTheF0x::KitsuneCraft::Vertices block_top = {
    // Top
    N1ghtTheF0x::KitsuneCraft::Vertex(1.0f,1.0f,-1.0f,   1.0f,0.0f,0.0f,1.0f,     1.0f,1.0f),
    N1ghtTheF0x::KitsuneCraft::Vertex(-1.0f,1.0f,-1.0f,   1.0f,0.0f,0.0f,1.0f,     1.0f,0.0f),
    N1ghtTheF0x::KitsuneCraft::Vertex(-1.0f,1.0f,1.0f,   1.0f,0.0f,0.0f,1.0f,     0.0f,0.0f),
    N1ghtTheF0x::KitsuneCraft::Vertex(1.0f,1.0f,1.0f,   1.0f,0.0f,0.0f,1.0f,     0.0f,1.0f),
};
static N1ghtTheF0x::KitsuneCraft::Vertices block_bottom = {
    // Bottom
    N1ghtTheF0x::KitsuneCraft::Vertex(1.0f,-1.0f,1.0f,   0.0f,1.0f,0.0f,1.0f,     1.0f,1.0f),
    N1ghtTheF0x::KitsuneCraft::Vertex(-1.0f,-1.0f,1.0f,   0.0f,1.0f,0.0f,1.0f,     1.0f,0.0f),
    N1ghtTheF0x::KitsuneCraft::Vertex(-1.0f,-1.0f,-1.0f,   0.0f,1.0f,0.0f,1.0f,     0.0f,0.0f),
    N1ghtTheF0x::KitsuneCraft::Vertex(1.0f,-1.0f,-1.0f,   0.0f,1.0f,0.0f,1.0f,     0.0f,1.0f),
};
static N1ghtTheF0x::KitsuneCraft::Vertices block_front = {
    // Front
    N1ghtTheF0x::KitsuneCraft::Vertex(1.0f,1.0f,1.0f,   0.0f,0.0f,1.0f,1.0f,     1.0f,1.0f),
    N1ghtTheF0x::KitsuneCraft::Vertex(-1.0f,1.0f,1.0f,   0.0f,0.0f,1.0f,1.0f,     1.0f,0.0f),
    N1ghtTheF0x::KitsuneCraft::Vertex(-1.0f,-1.0f,1.0f,   0.0f,0.0f,1.0f,1.0f,     0.0f,0.0f),
    N1ghtTheF0x::KitsuneCraft::Vertex(1.0f,-1.0f,1.0f,   0.0f,0.0f,1.0f,1.0f,     0.0f,1.0f),
};
static N1ghtTheF0x::KitsuneCraft::Vertices block_back = {
    // Back
    N1ghtTheF0x::KitsuneCraft::Vertex(1.0f,-1.0f,-1.0f,   1.0f,1.0f,0.0f,1.0f,     1.0f,1.0f),
    N1ghtTheF0x::KitsuneCraft::Vertex(-1.0f,-1.0f,-1.0f,   1.0f,1.0f,0.0f,1.0f,     1.0f,0.0f),
    N1ghtTheF0x::KitsuneCraft::Vertex(-1.0f,1.0f,-1.0f,   1.0f,1.0f,0.0f,1.0f,     0.0f,0.0f),
    N1ghtTheF0x::KitsuneCraft::Vertex(1.0f,1.0f,-1.0f,   1.0f,1.0f,0.0f,1.0f,     0.0f,1.0f),
};
static N1ghtTheF0x::KitsuneCraft::Vertices block_left = {
    // Left
    N1ghtTheF0x::KitsuneCraft::Vertex(-1.0f,1.0f,1.0f,   1.0f,0.0f,1.0f,1.0f,     1.0f,1.0f),
    N1ghtTheF0x::KitsuneCraft::Vertex(-1.0f,1.0f,-1.0f,   1.0f,0.0f,1.0f,1.0f,     1.0f,0.0f),
    N1ghtTheF0x::KitsuneCraft::Vertex(-1.0f,-1.0f,-1.0f,   1.0f,0.0f,1.0f,1.0f,     0.0f,0.0f),
    N1ghtTheF0x::KitsuneCraft::Vertex(-1.0f,-1.0f,1.0f,   1.0f,0.0f,1.0f,1.0f,     0.0f,1.0f),
};
static N1ghtTheF0x::KitsuneCraft::Vertices block_right = {
    // Right
    N1ghtTheF0x::KitsuneCraft::Vertex(1.0f,1.0f,-1.0f,   0.0f,1.0f,1.0f,1.0f,     1.0f,1.0f),
    N1ghtTheF0x::KitsuneCraft::Vertex(1.0f,1.0f,1.0f,   0.0f,1.0f,1.0f,1.0f,     1.0f,0.0f),
    N1ghtTheF0x::KitsuneCraft::Vertex(1.0f,-1.0f,1.0f,   0.0f,1.0f,1.0f,1.0f,     0.0f,0.0f),
    N1ghtTheF0x::KitsuneCraft::Vertex(1.0f,-1.0f,-1.0f,   0.0f,1.0f,1.0f,1.0f,     0.0f,1.0f),
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
        if(enabledSide(Side::Top))
        {
            context.drawQuad(block_top);
        }
        if(enabledSide(Side::Bottom))
        {
            context.drawQuad(block_bottom);
        }
        if(enabledSide(Side::Front))
        {
            context.drawQuad(block_front);
        }
        if(enabledSide(Side::Back))
        {
            context.drawQuad(block_back);
        }
        if(enabledSide(Side::Left))
        {
            context.drawQuad(block_left);
        }
        if(enabledSide(Side::Right))
        {
            context.drawQuad(block_right);
        }
    }
}