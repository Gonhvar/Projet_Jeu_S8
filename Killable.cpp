#include "Killable.hpp"

Killable::Killable(std::string sName, uint8_t nbE, uint8_t nbFPE[MAX_FPE]) : Entite(sName, nbE, nbFPE, this) {}

void Killable::translate(float depX, float depY) {
    Entite::translate(depX, depY); // Le Killable se déplace lui-même.
    for (Entite* ent : entite) { // Et il déplace les autres Entite qu'il contient
       ent->translate(depX, depY);
    }
}

void Killable::update() {
    Sprite::update();
    for (Entite* ent : entite) {
       ent->update();
    }
}

void Killable::mort() {}