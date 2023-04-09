#ifndef VENERA_HPP
#define VENERA_HPP
/*
#include <stdio.h>
#include <stdint.h>
*/
#include <vector>
#include <map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Sprite.hpp"

#define PATH_TO_TEXTURE_FOLDER "/Texture/" // Chemin relatif vers le dossier où se trouvent les textures.

class Affichage {
protected :
    std::vector<Sprite*> sprites; // Liste des Sprite à afficher à tout moment
                                    // Il serait bien qu'un Sprite* n'apparaîsse qu'une seule fois dans sprites
                                    // Il faudrait remplacer les Sprite* par des smart pointers ou faire gaffe lors de la suppression d'un Sprite
    std::map<std::string, SDL_Texture*> imageChargees;
    std::map<std::string, SDL_Texture*>::iterator imIterator;
    SDL_Renderer* renderer;

    std::string imageFormat = ".png";
    static const std::map<std::string, std::string> nomFichiers; // J'aimerai que ce soit initialisé lors du make. Exemple de ce que je veux dire par là :
    /*
    std::string array[3] = {"nomSprite1" : "nomFichier1",
                            "nomSprite2" : "nomFichier2",
                            "nomSprite3" : "nomFichier3"
                            } 
    */

public :
    /* CONSTRUCTEURS ET DESTRUCTEURS */
    Affichage(SDL_Renderer *rend) : renderer(rend){};
/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

    void enleveSprite(const Sprite& s);

    SDL_Texture* visit(Sprite& s, std::string& spriteName); // Un Sprite n'a pas à savoir le nom ou le chemin du fichier de l'image qu'il possède. Il doit juste connaître son nom et son état.

    void affiche_all() const;
};

#endif