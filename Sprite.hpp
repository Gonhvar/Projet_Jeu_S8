#pragma once
#include <iostream>
#include <string>

#ifndef ENTITE_HPP
#define ENTITE_HPP

class SDL_Texture {};

class Sprite {
protected :
    std::string name;
    float _coord[3] = { 0, 0, 0 }; // x, y, theta
    float _largeur = 0;
    float _hauteur = 0;
    SDL_Texture* texture = nullptr;
    bool onScreen = 0;

public:
    /* CONSTRUCTEURS ET DESTRUCTEURS */
    Sprite();
    Sprite(const Sprite& other);
    Sprite(std::string textureFileName);
    /* FIN CONSTRUCTEURS ET DESTRUCTEURS */

    float* getCoord();
    void setCoord(float& x, float& y, float& theta);
    void setCoord(float* coord);

    float& getLargeur();
    void setLargeur(float L);
    float& getHauteur();
    void setHauteur(float H);

    bool getOnScreen();
    void setOnScreen(bool toBe);

    //virtual void accept(class Affichage& a) = 0;

    //SDL_Texture* loadTexture(char* filename);

    //SDL_Texture* getTexture();

};