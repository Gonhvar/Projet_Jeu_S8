#include "Vector2D.hpp"

Vector2D::Vector2D(float X, float Y) : x(X), y(Y) {
    norme = sqrt(X*X + Y*Y);
}

void Vector2D::redef(float X, float Y) {
    // Redéfinie le vecteur et calcul sa nouvelle norme
    x = X;
    y = Y;
    norme = sqrt(X*X + Y*Y);
}

void Vector2D::plus(float X, float Y) {
    x += X;
    y += Y;
    norme = sqrt(x*x + y*y);
}

Vector2D& Vector2D::operator+=(const Vector2D& o) {
    // Ajoute le vecteur de droite au vecteur de gauche
    x += o.x;
    y += o.y;
    norme = sqrt(x*x + y*y);
    return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& o) {
    // Ajoute le vecteur de droite au vecteur de gauche
    x -= o.x;
    y -= o.y;
    norme = sqrt(x*x + y*y);
    return *this;
}

Vector2D& Vector2D::operator*=(const float a) {
    // Multiplie le vecteur par le scalaire à gauche
    x *= a;
    y *= a;
    norme *= a;
    return *this;
}

void Vector2D::normeToV(float newNorme) {
    // Redéfinie la longueur du vecteur à newNorme sans changer sa direction
    if (norme) {
        *this *= newNorme/norme;
    }
}

void Vector2D::printSelf() {
    std::cout << "x=" << x << ", y=" << y << ", norme=" << norme << std::endl;
}

// std::string Vector2D::serialize(std::string& toWrite) {
//     std::ostringstream oss;
//     oss << x << "|" << y << "|" << norme << std::endl;
//     toWrite += oss.str();
//     return "Vector2D";
// }

// void Vector2D::deSerialize(std::string& toRead) {
//     std::vector<std::string> tokens;
    
//     std::istringstream iss(toRead);
//     std::string token;
//     int i=0;
//     if (std::getline(iss, token, '|')) {
//         tokens.push_back(token);
//         x = std::stof(tokens[i]);
//         i++;
//     }
//     if (std::getline(iss, token, '|')) {
//         tokens.push_back(token);
//         y = std::stof(tokens[i]);
//         i++;
//     }
//     if (std::getline(iss, token, '|')) {
//         tokens.push_back(token);
//         norme = std::stof(tokens[i]);
//         i++;
//     }
    
//     std::cout << "fin deSerialize : ";
//     printSelf();
// }