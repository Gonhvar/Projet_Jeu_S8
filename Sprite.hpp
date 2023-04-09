#pragma once
#include <iostream>
#include <string>


#ifndef SPRITE_HPP
#define SPRITE_HPP

class Affichage;

class Sprite {
protected :
    std::string name;
    float _coord[3] = { 0, 0, 0 }; // Coordonnées en haut à gauche x, y, theta
    float _largeur = 0; // Largeur voulue de la texture associée au sprite
    float _hauteur = 0; // Hauteur voulue de la texture associée au sprite
    bool onScreen = 0;

    uint8_t etat = 0; // 0 est l'état par défaut

    Affichage* afficheur;

public:
    /* CONSTRUCTEURS ET DESTRUCTEURS */
    Sprite();
    Sprite(const Sprite& other);
    Sprite(std::string& spriteName, Affichage& aff);
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

#endif