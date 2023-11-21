#ifndef __N1GHTTHEF0X_KITSUNECRAFT_MATH_HPP
#define __N1GHTTHEF0X_KITSUNECRAFT_MATH_HPP

#include <cmath>

namespace N1ghtTheF0x::KitsuneCraft
{
    struct IVector2
    {
        float x;
        float y;
    };
    struct IVector3 : public IVector2
    {
        float z;
    };
    class Vector3
    {
    private:
        union 
        {
            float _x;
            float _y;
            float _z;
            float _field[3];
        };
    public:
        Vector3(): Vector3(0,0,0) {}
        Vector3(float x,float y,float z): _x(x), _y(y), _z(z) {}
        Vector3(const Vector3 &vector): _x(vector._x), _y(vector._y), _z(vector._z) {}
        Vector3(const IVector2 &vector): Vector3(vector.x,vector.y,0) {}
        Vector3(const IVector3 &vector): Vector3(vector.x,vector.y,vector.z) {}

        operator float*(){return _field;}

        float x() const {return _x;}
        float y() const {return _y;}
        float z() const {return _z;}
        Vector3 &setX(float x) {_x = x;return *this;}
        Vector3 &setY(float y) {_y = y;return *this;}
        Vector3 &setZ(float z) {_z = z;return *this;}
        Vector3 &set(float x,float y,float z) {return setX(x).setY(y).setZ(z);}

        float length() const {return sqrtf(_x*_x+_y*_y);}

        Vector3 normalize() {float n = length();if(n != 0) set(_x/n,_y/n,_z/n);}

        Vector3 add(float x,float y,float z) const {return {_x + x,_y + y,_z + z};}
        Vector3 add(const Vector3 &other) const {return add(other._x,other._y,other._z);}
        Vector3 operator+(const Vector3 &other) const {return add(other);}

        Vector3 subtract(float x,float y,float z) const {return {_x - x,_y - y,_z - 1};}
        Vector3 subtract(const Vector3 &other) const {return subtract(other._x,other._y,other._z);}
        Vector3 operator-(const Vector3 &other) const {return subtract(other);}

        Vector3 multiply(float x) const {return {_x * x,_y * x,_z * x};}
        float multiply(float x,float y,float z) const {return _x*x + _y*y + _z*z;}
        float multiply(const Vector3 &other) const {return multiply(other._x,other._y,other._z);}
        float operator*(const Vector3 &other) const {return multiply(other);}

        Vector3 cross(float x,float y,float z) const {return {_y*z - _z*y,_z*x - _x*z,_x*y - _y*x};}
        Vector3 cross(const Vector3 &other) const {return cross(other._x,other._y,other._z);}
    };
    class Matrix
    {
    private:
        float _raw[4][4];
    public:
        Matrix() {for(int y = 0;y < 4;y++) for(int x = 0;x < 4;x++) _raw[y][x] = 0;}
        Matrix(float fov,float aspect,float near,float far): Matrix()
        {
            _raw[0][0] = aspect * fov;
            _raw[1][1] = fov;
            _raw[2][2] = far / (far - near);
            _raw[3][2] = (-far * near) / (far - near);
            _raw[2][3] = 1;
            _raw[3][3] = 0;
        }
        Matrix add(const Matrix &other) const
        {
            Matrix m;
            for(int y = 0;y < 4;y++)
            for(int x = 0;y < 4;y++)
                m._raw[y][x] = _raw[y][x] + other._raw[y][x];
            return m;
        }
        Matrix operator+(const Matrix &o) const {return add(o);}
        Matrix multiply(float x) const
        {
            Matrix m;
            for(int y = 0;y < 4;y++)
            for(int x = 0;y < 4;y++)
                m._raw[y][x] = _raw[y][x] * x;
            return m;
        }
        Matrix operator*(float x) const {return multiply(x);}
        Matrix subtract(const Matrix &other) const
        {
            Matrix m;
            Matrix b = other.multiply(-1);
            return add(b);
        }
        Matrix operator-(const Matrix &other) const {return subtract(other);}
        Matrix multiply(const Matrix &other) const
        {
            Matrix m;
            for(int c = 0;c < 4;c++)
            for(int r = 0;r < 4;r++)
                m._raw[r][c] = _raw[r][0] * other._raw[0][c] +
                               _raw[r][1] * other._raw[1][c] +
                               _raw[r][2] * other._raw[2][c] +
                               _raw[r][3] * other._raw[3][c];
            return m;
        }
        Vector3 multiply(const Vector3 &vec) const
        {
            Vector3 o;
            o.setX(vec.x() * _raw[0][0] + vec.y() * _raw[1][0] + vec.z() * _raw[2][0] + _raw[3][0]);
            o.setY(vec.x() * _raw[0][1] + vec.y() * _raw[1][1] + vec.z() * _raw[2][1] + _raw[3][1]);
            o.setZ(vec.x() * _raw[0][2] + vec.y() * _raw[1][2] + vec.z() * _raw[2][2] + _raw[3][2]);
            float w = vec.x() * _raw[0][3] + vec.y() * _raw[1][3] + vec.z() * _raw[2][3] + _raw[3][3];

            if (w != 0.0f)
                o.set(o.x() / w,o.y() / w,o.z() / w);
            return o;
        }
    };
}

#endif