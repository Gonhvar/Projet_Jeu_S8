#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Inc.hpp"

class Sprite;
class Entite;
class Enemies;
class Drop;
class Mc;
class Joueur2;

#define MODE_JEU 0
#define MODE_MAP 1
#define MODE_MAXNUM 2

class Stockeur {
protected:
    std::vector<Sprite*> sprites;
    std::vector<Entite*> circEntities;
    std::vector<Entite*> rectEntities;
    std::vector<Enemies*> enemies;
    std::vector<Drop*> items;

    Mc* mc;
    Joueur2* j2;

    bool menuOff = true; // Pas de menu de base
    int mode = MODE_JEU;

public:

    bool printEverything = 0; // Sert au debug X(

    Stockeur();

    void addSprites(Sprite* sp);
    void addCircEntite(Entite* en);
    void addRectEntite(Entite* en);
    void addEnemies(Enemies* en);
    void addItem(Drop* dr);

    void addMc(Mc* j);
    void addJoueur2(Joueur2* j);
    
    void removeSprites(Sprite* sp);
    void removeCircEntite(Entite* en);
    void removeRectEntite(Entite* en);
    void removeEnemies(Enemies* en);
    void removeItem(Drop* dr);

    Mc* getMc();
    Joueur2* getJ2();
    
    std::vector<Sprite*>* getSpriteVector();
    std::vector<Entite*>* getCircEntiteVector();
    std::vector<Entite*>* getRectEntiteVector();
    std::vector<Enemies*>* getEnemiesVector();
    std::vector<Drop*>* getItemVector();


    void deleteAllEnemies();

    void setMenuOff(bool toBe);
    bool getMenuOff();
    void swapMenuOff();

    void setMode(int toBe);
    int getMode();
};

#endif