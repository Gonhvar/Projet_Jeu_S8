#include "Vector2D.hpp"

Vector2D::Vector2D(float X, float Y) : x(X), y(Y) {
    norme = sqrt(X*X + Y*Y);
}

void Vector2D::redef(float X, float Y) {
    x = X;
    y = Y;
    norme = sqrt(X*X + Y*Y);
}

Vector2D& Vector2D::operator+=(const Vector2D& o) {
    x += o.x;
    y += o.y;
    norme = sqrt(x*x + y*y);
    return *this;
}

Vector2D& Vector2D::operator*=(const float a) {
    x *= a;
    y *= a;
    norme *= a;
    return *this;
}

void Vector2D::normeToV(float newNorme) {
    if (norme) {
        *this *= newNorme/norme;
    }
}

void Vector2D::printSelf() {
    std::cout << "x=" << x << ", y=" << y << ", norme=" << norme << std::endl;
}