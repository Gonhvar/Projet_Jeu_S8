#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "Inc.hpp"
#include "Map.hpp"
#include "Stockeur.hpp"
#include "Serializable.hpp"


class Affichage;

typedef std::vector<std::vector<SDL_Texture*> > TexturePack;
#define MAX_FPE 10

typedef struct States_t{ // sert à décrire les états qu'un Sprite peut avoir, ainsi que son nom (in-game type)
    std::string spriteName;
    uint8_t nbEtats = 0;
    uint8_t nbFrameParEtat[MAX_FPE];
} States;


class Sprite : public Serializable {
protected :
    
    float _coord[3] = { 0, 0, 0 }; // Coordonnées au centre du rectangle x, y, theta
    float _largeur = 1; // Largeur voulue de la texture associée au sprite
    float _hauteur = 1; // Hauteur voulue de la texture associée au sprite
    bool onScreen = 0;

    const States* states = nullptr; // Ne pas modifier ce qu'il y a à l'adresse merci !
                                    // Pour l'instant chaque Sprite (ou descendant) a son propre state
    
    // Les tailles sont en pixels
    SDL_Rect stateRect = {0, 0, 32, 32}; // Rectangle intérieur à afficher :
                                         // où dans la SpriteSheet
                                         // dimension dans la SpriteSheet
    SDL_Rect stateRectIn = {0, 0, 32, 32}; // décalage x, décalage y : où commencent le Sprite dans un carreau
                                           // dimension d'un carreau
    
    SDL_Texture* texture = nullptr; // Sprite sheet

    uint8_t maxDelay = 0; // Temps entre chaque texture
    uint8_t delay = 0; // Temps entre chaque texture
    int etat = 0; // état dans lequel est le Sprite;
    int frame = 0; // 0 est l'état par défaut
    bool flip = false;


public:
    //L'afficheur est le même pour tous les sprites, la seule fois ou on le met est dans le constructeur du MC
    static Affichage* afficheur;
    //Beaucoup de choses existent en relation avec le joueur, mettre un static peut donc être une bonne idée
    // static Sprite* joueur;
    // static Sprite* joueur2;
    // On suppose pour l'instant qu'il n'y a qu'une seule map à la fois.
    static Map* map;

    static Stockeur* stockeur;

    bool markedForDeath = false;

    /* CONSTRUCTEURS ET DESTRUCTEURS */
    Sprite();
    Sprite(std::string sName, uint8_t nbE, uint8_t nbFPE[MAX_FPE]);

    virtual ~Sprite();
    /* FIN CONSTRUCTEURS ET DESTRUCTEURS */
    
    void update();

    float* getCoord();
    float getX();
    float getY();
    float getSpriteX();
    float getSpriteY();
    float& getLargeur();
    float& getHauteur();
    bool getOnScreen();

    void setCoord(float x, float y, float theta = 0.);
    void setCoord(float* coord);
    void setLargeur(float L);
    void setHauteur(float H);
    void setOnScreen(bool toBe);



    void addSprite(std::string className);
    SDL_Texture* getTexture();
    void setTexture(SDL_Texture* t);
    const SDL_Rect* getRightRectangle(); // Sert à renvoyer la texture que ce Sprite veut afficher
    
    const States* getStates();
    void setEtat(uint8_t toBe);
    bool getFlip();
    const std::string getName();

    // Fonctions de sauvegarde de l'objet
    virtual std::string serialize(std::string& toWrite);
    virtual void deSerialize(std::string& toRead);
    bool readBool(std::string& toRead);
};

#endif
