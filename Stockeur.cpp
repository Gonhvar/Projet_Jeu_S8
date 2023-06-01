#include "Stockeur.hpp"
#include "Enemies.hpp"


Stockeur::Stockeur(){}

// ADDER ----------------------------------------------------------------

void Stockeur::addSprites(Sprite* sp){
    if (printEverything) {
        std::cout << "added Sprite" << std::endl;
        std::cout << "taille de sprites : " << sprites.size()+1 << std::endl;
    }
    sprites.push_back(sp);
}

void Stockeur::addCircEntite(Entite* en){
    if (printEverything) {
        std::cout << "added circEntities" << std::endl;
        std::cout << "taille de circEntities : " << circEntities.size()+1 << std::endl;
    }
std::cout << circEntities.size() << std::endl;
    circEntities.push_back(en);
}

void Stockeur::addRectEntite(Entite* en){
    if (printEverything) {
        std::cout << "added rectEntities" << std::endl;
        std::cout << "taille de rectEntities : " << rectEntities.size()+1 << std::endl;
    }
    rectEntities.push_back(en);
}

void Stockeur::addEnemies(Enemies* en){
    if (printEverything) {
        std::cout << "added enemies" << std::endl;
        std::cout << "taille de enemies : " << enemies.size()+1 << std::endl;
    }
    enemies.push_back(en);
}

void Stockeur::addItem(Drop* dr){
    if (printEverything) {
        std::cout << "added items" << std::endl;
        std::cout << "taille de items : " << items.size()+1 << std::endl;
    }
    items.push_back(dr);
}

void Stockeur::addMc(Mc* j){
    if (printEverything) {
        std::cout << "added mc" << std::endl;
    }
    mc = j;
}

void Stockeur::addJoueur2(Joueur2* j){
    if (printEverything) {
        std::cout << "added j2" << std::endl;
    }
    j2 = j;
}


// REMOVER ----------------------------------------------------------------

void Stockeur::removeSprites(Sprite* sp){
    if (printEverything) {
        std::cout << "removed sprites" << std::endl;
        std::cout << "taille de sprites : " << sprites.size()-1 << std::endl;
    }
    auto it = std::find(sprites.begin(), sprites.end(), sp);
    if (it != sprites.end()) {
        sprites.erase(it); 
    }

}

void Stockeur::removeCircEntite(Entite* en){
    if (printEverything) {
        std::cout << "removed circEntities" << std::endl;
        std::cout << "taille de circEntities : " << circEntities.size()-1 << std::endl;
    }
    auto it = std::find(circEntities.begin(), circEntities.end(), en);
    if (it != circEntities.end()) {
        circEntities.erase(it); 
    }
}

void Stockeur::removeRectEntite(Entite* en){
    if (printEverything) {
        std::cout << "removed rectEntities" << std::endl;
        std::cout << "taille de rectEntities : " << rectEntities.size()-1 << std::endl;
    }
    auto it = std::find(rectEntities.begin(), rectEntities.end(), en);
    if (it != rectEntities.end()) {
        rectEntities.erase(it); 
    }
}

void Stockeur::removeEnemies(Enemies* en){
    if (printEverything) {
        std::cout << "removed enemies" << std::endl;
        std::cout << "taille de enemies : " << enemies.size()-1 << std::endl;
    }
    auto it = std::find(enemies.begin(), enemies.end(), en);
    if (it != enemies.end()) {
        enemies.erase(it); 
    }
}

void Stockeur::removeItem(Drop* dr){
    if (printEverything) {
        std::cout << "removed enemies" << std::endl;
        std::cout << "taille de enemies : " << enemies.size()-1 << std::endl;
    }
    auto it = std::find(items.begin(), items.end(), dr);
    if (it != items.end()) {
        items.erase(it); 
    }
}




// GETTER ----------------------------------------------------------------

Mc* Stockeur::getMc() {
    return mc;
}

Joueur2* Stockeur::getJ2(){
    return j2;
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

std::vector<Drop*>* Stockeur::getItemVector(){
    return &items;
}


void Stockeur::deleteAllEnemies(){
    std::cout << "enemies.size : " << enemies.size() << std::endl;
    for(Enemies* en : enemies){
        delete en;
    }
    enemies.clear();
}

void Stockeur::setMenuOff(bool toBe) {
    menuOff = toBe;
}

bool Stockeur::getMenuOff() {
    return menuOff;
}

void Stockeur::swapMenuOff() {
    menuOff = !menuOff;
}

void Stockeur::setMode(int toBe) {
    mode = toBe;
}

int Stockeur::getMode() {
    return mode;
}
