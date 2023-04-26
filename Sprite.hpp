#pragma once
#include <iostream>
#include <string>


#ifndef SPRITE_HPP
#define SPRITE_HPP

class Affichage;

class Sprite {
protected :
    //L'afficheur est le même pour tous les sprites, la seule fois ou on le met est dans le constructeur du MC
    static Affichage* afficheur;
    //Beaucoup de choses existent en relation avec le joueur, mettre un static peut donc être une bonne idée
    static Sprite* joueur;

    std::string name;
    float _coord[3] = { 0, 0, 0 }; // Coordonnées en haut à gauche x, y, theta
    float _largeur = 1; // Largeur voulue de la texture associée au sprite
    float _hauteur = 1; // Hauteur voulue de la texture associée au sprite
    bool onScreen = 0;

    uint8_t etat = 0; // 0 est l'état par défaut


public:
    /* CONSTRUCTEURS ET DESTRUCTEURS */
    Sprite();
    Sprite(const Sprite& other);
    Sprite(std::string& spriteName, Affichage& aff);
    Sprite(std::string& spriteName);

    virtual ~Sprite() {};
    /* FIN CONSTRUCTEURS ET DESTRUCTEURS */

    float* getCoord();
    float getX();
    float getY();

    void setCoord(float x, float y, float theta);
    void setCoord(float* coord);

    float& getLargeur();
    void setLargeur(float L);
    float& getHauteur();
    void setHauteur(float H);

    bool getOnScreen();
    void setOnScreen(bool toBe);

    void addSprite();

};

#endif