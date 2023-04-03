#pragma once
class Sprite {
public:
    double coord[3] = { 0, 0, 0 };
    float largeur = 0;
    float hauteur = 0;

    double* getCoord();
    void setCoord(double& x, double& y, double& theta);
    void setCoord(double* coord);

    float getLargeur();
    void setLargeur(float L);
    float getHauteur();
    void setHauteur(float H);
};