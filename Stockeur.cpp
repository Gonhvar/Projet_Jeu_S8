#include "Stockeur.hpp"

Stockeur::Stockeur(){}

void Stockeur::addSprites(Sprite* sp){
    sprites.push_back(sp);
}

void Stockeur::addCircEntite(Entite* en){
    circEntities.push_back(en);
}

void Stockeur::addRectEntite(Entite* en){
    rectEntities.push_back(en);
}

void Stockeur::addEnemies(Enemies* en){
    enemies.push_back(en);
}

void Stockeur::addMc(Mc* j){
    mc = j;
}


void Stockeur::removeSprites(Sprite* sp){
    auto it = std::find(sprites.begin(), sprites.end(), sp);
    if (it != sprites.end()) {
        sprites.erase(it); 
    }

}

void Stockeur::removeCircEntite(Entite* en){
    auto it = std::find(circEntities.begin(), circEntities.end(), en);
    if (it != circEntities.end()) {
        circEntities.erase(it); 
    }
}

void Stockeur::removeRectEntite(Entite* en){
    auto it = std::find(rectEntities.begin(), rectEntities.end(), en);
    if (it != rectEntities.end()) {
        rectEntities.erase(it); 
    }
}

void Stockeur::removeEnemies(Enemies* en){
    auto it = std::find(enemies.begin(), enemies.end(), en);
    if (it != enemies.end()) {
        enemies.erase(it); 
    }
}

Mc* Stockeur::getMc() {
    return mc;
}

std::vector<Sprite*>* Stockeur::getSpriteVector(){
    return &sprites;
}

std::vector<Entite*>* Stockeur::getCircEntiteVector(){
    return &circEntities;
}

std::vector<Entite*>* Stockeur::getRectEntiteVector(){
    return &rectEntities;
}

std::vector<Enemies*>* Stockeur::getEnemiesVector(){
    return &enemies;
}