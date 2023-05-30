#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

#include "Inc.hpp"



class Vector2D {
public :
    float x;
    float y;
    float norme;

    Vector2D() = default;
    Vector2D(float X, float Y);
    void redef(float X, float Y);
    void plus(float X, float Y);
    Vector2D& operator+=(const Vector2D& o);
    Vector2D& operator-=(const Vector2D& o);
    Vector2D& operator*=(const float a);
    void normeToV(float newNorme);

    void printSelf();
};

#endif