#pragma once
#include <iostream>
#include <string>

class Sprite {
protected :
    std::string name;
    float _coord[3] = { 0, 0, 0 }; // x, y, theta
    float _largeur = 0;
    float _hauteur = 0;
    SDL_Texture* texture = nullptr;
    bool onScreen = 0;

public:
<<<<<<< HEAD
    double coord[3] = { 0, 0, 0 };
    float largeur = 0;
    float hauteur = 0;
=======
    Sprite();
    Sprite(const Sprite& other);
    Sprite(char* textureFileName);
>>>>>>> e8dac6f1e2da5d90376278f0dcd92e51c5b2825d

    float* getCoord();
    void setCoord(float& x, float& y, float& theta);
    void setCoord(float* coord);

    float& getLargeur();
    void setLargeur(float L);
    float& getHauteur();
    void setHauteur(float H);

    virtual void accept(class Affichage& a) = 0;

    SDL_Texture* loadTexture(char* filename);
};