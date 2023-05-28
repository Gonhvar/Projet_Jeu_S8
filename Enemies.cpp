#include "Enemies.hpp"

/* CONSTRUCTEURS ET DESTRUCTEURS */
Enemies::Enemies() {
    Sprite::stockeur->addEnemies(this);
    hitBoxType(1, 0);
}

Enemies::Enemies(std::string sName, uint8_t nbE, uint8_t nbFPE[MAX_FPE]) : Entite(sName, nbE, nbFPE) {
    Sprite::stockeur->addEnemies(this);
    hitBoxType(1, 0);
}

Enemies::~Enemies() {
    Sprite::stockeur->removeEnemies(this);
}
/* FIN CONSTRUCTEURS ET DESTRUCTEURS */


void Enemies::update() {
    if (Sprite::stockeur->printEverything) std::cout << "Enemies::update() : " << this << std::endl;
    deplacementBehaviour();
    attackBehaviour();
}