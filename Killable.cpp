#include "Killable.hpp"

/* CONSTRUCTEURS ET DESTRUCTEURS */
Killable::Killable() {
    hitBoxType(1, 0); // Pour l'instant, on part du principe qu'un Killable a une hitBox ronde
}

Killable::Killable(std::string sName, uint8_t nbE, uint8_t nbFPE[MAX_FPE]) : Entite(sName, nbE, nbFPE, this) {
}

Killable::~Killable() {
    std::cout << "Delete Killable" << std::endl;
    for (uint8_t i=0; i<entite.size(); i++) {
        delete(entite[i]);
    }
    entite.clear();
}
/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

void Killable::translate(Vector2D& v) {
    Entite::translate(v); // Le Killable se déplace lui-même.
    for (Entite* ent : entite) { // Et il déplace les autres Entite qu'il contient
       ent->translate(v);
    }
}

void Killable::updateSpeedWithCollisions() {
    
    Entite::updateSpeedWithCollisions();

    for (uint8_t i=0; i<entite.size(); i++) {
        entite[i]->Entite::updateSpeedWithCollisions();
    }
}

void Killable::update() {
    Sprite::update();
    for (Entite* ent : entite) {
       ent->update();
    }
}

void Killable::mort() {}