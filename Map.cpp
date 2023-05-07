#include "Map.hpp"

Map::Map() {
    tiles.resize(0);
}

SpriteMap* Map::getTiles() {
    return &tiles;
}

std::vector<Entite*>& Map::getEntities() {
    return entities;
}

void Map::addEntite(Entite* e) {
    entities.push_back(e);
}