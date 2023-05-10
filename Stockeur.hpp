#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Inc.hpp"

class Sprite;
class Entite;
class Enemies;
class Mc;

class Stockeur {
protected:
    std::vector<Sprite*> sprites;
    std::vector<Entite*> circEntities;
    std::vector<Entite*> rectEntities;
    std::vector<Enemies*> enemies;

    Mc* mc;

public:

    Stockeur();

    void addSprites(Sprite* sp);
    void addCircEntite(Entite* en);
    void addRectEntite(Entite* en);
    void addEnemies(Enemies* en);
    void addMc(Mc* j);
    
    void removeSprites(Sprite* sp);
    void removeCircEntite(Entite* en);
    void removeRectEntite(Entite* en);
    void removeEnemies(Enemies* en);

    Mc* getMc();
    std::vector<Sprite*>* getSpriteVector();
    std::vector<Entite*>* getCircEntiteVector();
    std::vector<Entite*>* getRectEntiteVector();
    std::vector<Enemies*>* getEnemiesVector();

};

#endif