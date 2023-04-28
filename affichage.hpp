#ifndef AFFICHAGE_HPP
#define AFFICHAGE_HPP
/*
#include <stdio.h>
#include <stdint.h>
*/
#include <vector>
#include <map>


#include "Sprite.hpp"
#include "Enemies.hpp"

#define PATH_TO_TEXTURE_FOLDER "Textures/" // Chemin relatif vers le dossier où se trouvent les textures.
#define NO_TEXTURE_FOUND "Textures/noTexture.png"

class Affichage {
protected :
    std::vector<Sprite*> sprites;   // Liste des Sprite connus
                                // Il serait bien qu'un Sprite* n'apparaîsse qu'une seule fois dans sprites
                                // Il faudrait remplacer les Sprite* par des smart pointers ou faire gaffe lors de la suppression d'un Sprite
    std::map<std::string, TexturePack*> imageChargees; // Dictionnaire stockant les texture chargées avec comme clée le nom de sprite associé
    std::map<std::string, TexturePack*>::iterator imIterator; // Permet simplement de ne pas avoir à allouer de la mémoire à chaque fois que l'on veut itérer sur imageChargees

    SDL_Renderer* renderer;

    std::string imageFormat = ".png";
    static const std::map<std::string, std::string> nomFichiers; // J'aimerai que ce soit initialisé lors du make. Exemple de ce que je veux dire par là :

    float camPos[2]; // Position de la caméra
    float zoom; // Zoom de la caméra

    SDL_Texture* noTexture;

public :
    /* CONSTRUCTEURS ET DESTRUCTEURS */
    Affichage(SDL_Renderer *rend);
    Affichage();
    /* FIN CONSTRUCTEURS ET DESTRUCTEURS */

    void setZoom(float z);
    void setCamPos(float x, float y);

    void enleveSprite(const Sprite& s);

    void visit(Sprite* s, std::string& spriteName, uint8_t nbEtats, std::vector<uint8_t>& nbFrameParEtat); // Un Sprite n'a pas à savoir le nom ou le chemin du fichier de l'image qu'il possède. Il doit juste connaître son nom et son état.

    void update();

    // void enemiesUpdate();

    void affiche_all() const;

};

#endif