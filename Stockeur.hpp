#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Inc.hpp"

class Sprite;
class Entite;
class Enemies;

class Stockeur {
protected:
    std::vector<Sprite*> sprites;
    std::vector<Entite*> entities;
	std::vector<Enemies*> enemies;
public:
    void addSprites(Sprite* sp);
    void addEntite(Entite* en);
    void addEnemies(Enemies* en);
    
    void removeSprites(Sprite* sp);
    void removeEntite(Entite* en);
    void removeEnemies(Enemies* en);

    std::vector<Sprite*>& getSpriteVector();
    std::vector<Entite*>& getEntiteVector();
    std::vector<Enemies*>& getEnemiesVector();

    void update();
     
};

#endif