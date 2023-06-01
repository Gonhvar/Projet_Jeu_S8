#ifndef AFFICHAGE_HPP
#define AFFICHAGE_HPP


#include "Sprite.hpp"
#include "Enemies.hpp"


#define PATH_TO_TEXTURE_FOLDER "Textures/" // Chemin relatif vers le dossier où se trouvent les textures.
#define NO_TEXTURE_FOUND "Textures/noTexture.png"

class Affichage {
protected :
    std::vector<Sprite*>* sprites; // copie de la liste des Sprite du Stockeur
    std::map<std::string, SDL_Texture*> imageChargees; // Dictionnaire stockant les texture chargées avec comme clée le nom de sprite associé
    std::map<std::string, SDL_Texture*>::iterator imIterator; // Permet simplement de ne pas avoir à allouer de la mémoire à chaque fois que l'on veut itérer sur imageChargees

    SDL_Renderer* renderer;
    SDL_Window* window;

    std::string imageFormat = ".png";

    SDL_Rect camera {0, 0, 512, 512}; // Position et taille de la caméra
    float rayonDistMc = 50;

    SDL_Texture* noTexture; // Texture mise par défaut lorsqu'aucune n'a été trouvée
    TTF_Font* font;
    SDL_Color textColor;
    
public :
    /* CONSTRUCTEURS ET DESTRUCTEURS */
    Affichage(SDL_Renderer* rend, SDL_Window* win, Stockeur* st);
    Affichage();
    ~Affichage();
    /* FIN CONSTRUCTEURS ET DESTRUCTEURS */

    void enleveSprite(const Sprite& s);

    void visit(Sprite* s, std::string className, const std::string spriteName);

    void update();

    void afficheHealth();
    void affiche_all() const;
    void setMcColor();

    int getCameraX();
    int getCameraY();
};

#endif
