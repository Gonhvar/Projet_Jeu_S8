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
    Sprite();
    Sprite(const Sprite& other);
    Sprite(char* textureFileName);

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