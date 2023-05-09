#include "Stockeur.hpp"

Stockeur::Stockeur(){}

void Stockeur::addSprites(Sprite* sp){
    sprites.push_back(sp);
}

void Stockeur::addEntite(Entite* en){
    entities.push_back(en);
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

void Stockeur::removeEntite(Entite* en){
    auto it = std::find(entities.begin(), entities.end(), en);
    if (it != entities.end()) {
        entities.erase(it); 
    }
}

void Stockeur::removeEnemies(Enemies* en){
    auto it = std::find(enemies.begin(), enemies.end(), en);
    if (it != enemies.end()) {
        enemies.erase(it); 
    }
}

std::vector<Sprite*>* Stockeur::getSpriteVector(){
    return &sprites;
}

std::vector<Entite*>* Stockeur::getEntiteVector(){
    return &entities;
}

std::vector<Enemies*>* Stockeur::getEnemiesVector(){
    return &enemies;
}