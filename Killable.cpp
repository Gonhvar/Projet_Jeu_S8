#include "Killable.hpp"

// Killable::Killable(std::string& spriteName, uint8_t nbStates, std::vector<uint8_t>& nbFPE) : Entite(spriteName, nbStates, nbFPE) {}


void Killable::translate(float dx, float dy) {
    Entite::translate(dx, dy); // Le Killable se déplace lui-même.
    for (Entite* ent : entite) { // Et il déplace les autres Entite qu'il contient
       ent->translate(dx, dy);
    }
}

void Killable::update() {
    for (Entite* ent : entite) {
       ent->update();
    }
}