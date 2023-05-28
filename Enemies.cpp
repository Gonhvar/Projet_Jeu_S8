#include "Enemies.hpp"

Enemies::Enemies() {
    Sprite::stockeur->addEnemies(this);
}

Enemies::Enemies(std::string sName, uint8_t nbE, uint8_t nbFPE[MAX_FPE]) : Killable(sName, nbE, nbFPE) {}


void Enemies::update() {
    deplacementBehaviour();
    attackBehaviour();
}