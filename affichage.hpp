#ifndef AFFICHAGE_HPP
#define AFFICHAGE_HPP


#include "Sprite.hpp"
#include "Enemies.hpp"
#include "Mc.hpp"




#define PATH_TO_TEXTURE_FOLDER "Textures/" // Chemin relatif vers le dossier où se trouvent les textures.
#define NO_TEXTURE_FOUND "Textures/noTexture.png"

class Affichage {
protected :
    std::vector<Sprite*>* sprites; // copie de la liste des Sprite du Stockeur
    std::map<std::string, SDL_Texture*> imageChargees; // Dictionnaire stockant les texture chargées avec comme clée le nom de sprite associé
    std::map<std::string, SDL_Texture*>::iterator imIterator; // Permet simplement de ne pas avoir à allouer de la mémoire à chaque fois que l'on veut itérer sur imageChargees

    SDL_Renderer* renderer;

    std::string imageFormat = ".png";
    
    Mc* player;

    float camPos[2]; // Position de la caméra
    float zoom; // Zoom de la caméra

    SDL_Texture* noTexture; // Texture mise par défaut lorsqu'aucune n'a été trouvée
    TTF_Font* font;
    SDL_Color textColor;
    
public :
    /* CONSTRUCTEURS ET DESTRUCTEURS */
    Affichage(SDL_Renderer* rend, Stockeur* st);
    Affichage();
    ~Affichage();
    /* FIN CONSTRUCTEURS ET DESTRUCTEURS */

    void setZoom(float z);
    void setCamPos(float x, float y);
		void setPlayer(Mc* thePlayer);

    void enleveSprite(const Sprite& s);

    void visit(Sprite* s, const std::string spriteName);

    void update();

    void affiche_all() const;

    void afficheHealth();
};

#endif
