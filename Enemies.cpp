#include "Enemies.hpp"

Enemies::Enemies() {
    Sprite::stockeur->addEnemies(this);
    hitBoxType(1, 0);
}

Enemies::Enemies(std::string sName, uint8_t nbE, uint8_t nbFPE[MAX_FPE]) : Drop(sName, nbE, nbFPE) {
    Sprite::stockeur->addEnemies(this);
    hitBoxType(1, 0);
}


void Enemies::update() {
    if (Sprite::stockeur->printEverything) std::cout << "Enemies::update() : " << this << std::endl;
    deplacementBehaviour();
    attackBehaviour();
}