#ifndef MAP_HPP
#define MAP_HPP

#include "Inc.hpp"

class Entite;
class Sprite;

typedef std::vector<std::vector<Sprite*> > SpriteMap;

class Map {
private :
    float tileSize[2];
    SpriteMap tiles;
    // std::vector<Entite*> entities;

public :
    Map();
    SpriteMap* getTiles();
    // std::vector<Entite*>& getEntities();
    // void addEntite(Entite* e);
    void toRemove(Entite* toRemove);
};

#endif
