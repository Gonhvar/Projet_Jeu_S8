#include "Stockeur.hpp"

Stockeur::Stockeur(){}

void Stockeur::addSprites(Sprite* sp){
    std::cout << "added Sprite : " << std::endl;
    sprites.push_back(sp);
    std::cout << "taille de sprites : " << sprites.size() << std::endl;
}

void Stockeur::addCircEntite(Entite* en){
    std::cout << "added CircEntite" << std::endl;
    circEntities.push_back(en);
    std::cout << "taille de circEntities : " << circEntities.size() << std::endl;
}

void Stockeur::addRectEntite(Entite* en){
    std::cout << "added RectEntite" << std::endl;
    rectEntities.push_back(en);
    std::cout << "taille de rectEntities : " << rectEntities.size() << std::endl;
}

void Stockeur::addEnemies(Enemies* en){
    std::cout << "added Enemies" << std::endl;
    enemies.push_back(en);
    std::cout << "taille de enemies : " << enemies.size() << std::endl;
}

void Stockeur::addMc(Mc* j){
    std::cout << "added Mc" << std::endl;
    mc = j;
}

void Stockeur::addJoueur2(Joueur2* j){
    j2 = j;
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