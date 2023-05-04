#include "Killable.hpp"

Killable::Killable(std::string sName, uint8_t nbE, uint8_t nbFPE[MAX_FPE]) : Entite(sName, nbE, nbFPE, this) {
    possesseur = this;
}

void Killable::translate(float dx, float dy) {
    Entite::translate(dx, dy); // Le Killable se déplace lui-même.
    for (Entite* ent : entite) { // Et il déplace les autres Entite qu'il contient
       ent->translate(dx, dy);
    }
}

void Killable::update() {
    Sprite::update();
    for (Entite* ent : entite) {
       ent->update();
    }
}

void Killable::mort() {}