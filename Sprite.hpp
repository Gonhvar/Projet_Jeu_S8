#pragma once
#include <iostream>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


#ifndef SPRITE_HPP
#define SPRITE_HPP

class Affichage;

// typedef struct { 
//     std::vector<std::vector<SDL_Texture*>>;
// } TexturePack; // Ensemble des textures associées à un nom.

typedef std::vector<std::vector<SDL_Texture*>> TexturePack;


class Sprite {
protected :

    std::string name;
    float _coord[3] = { 0, 0, 0 }; // Coordonnées en haut à gauche x, y, theta
    float _largeur = 1; // Largeur voulue de la texture associée au sprite
    float _hauteur = 1; // Hauteur voulue de la texture associée au sprite
    bool onScreen = 0;

    uint8_t nbEtats = 0;
    std::vector<uint8_t> nbFrameParEtat;
    uint8_t delay = 0; // Temps entre chaque texture
    TexturePack* texture = nullptr; // Liste des Texture en fonction de l'état et de la frame.

    uint8_t etat = 0; // état dans lequel est le Sprite;
    uint8_t frame = 0; // 0 est l'état par défaut


public:
    //L'afficheur est le même pour tous les sprites, la seule fois ou on le met est dans le constructeur du MC
    static Affichage* afficheur;
    //Beaucoup de choses existent en relation avec le joueur, mettre un static peut donc être une bonne idée
    static Sprite* joueur;


    /* CONSTRUCTEURS ET DESTRUCTEURS */
    Sprite();
    Sprite(const Sprite& other);
    //Sprite(std::string& spriteName, Affichage& aff);
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
    TexturePack* getTexture();
    void setTexture(TexturePack* t);
    SDL_Texture* getRightTexture(); // Sert à renvoyer la texture que ce Sprite veut afficher

};

#endif