#include "Killable.hpp"

Killable::Killable() {
    possesseur = this;
}

Killable::Killable(std::string sName, uint8_t nbE, uint8_t nbFPE[MAX_FPE]) : Entite(sName, nbE, nbFPE, this) {
    possesseur = this;
}

void Killable::translate(Vector2D& v) {
    Entite::translate(v); // Le Killable se déplace lui-même.
    for (Entite* ent : entite) { // Et il déplace les autres Entite qu'il contient
       ent->translate(v);
    }
}

void Killable::moveAllCollision(std::vector<Entite*>& entities, Vector2D& v) {
    // float porte = v.norme + rayon;
    for (uint16_t i=0; i<entities.size(); i++) { // max 65000 Entite :O
        // On pourrait ajouter un test pour vérifier que l'Entite est à porté.
        Entite::moveCollisionRectangle(entities[i], v);
        // if (v.norme == 0) { // Peut accélérer la boucle si les Entite ont beaucoup tendance à se bloquer
        //     break;
        // }
    }
}

void Killable::update() {
    Sprite::update();
    for (Entite* ent : entite) {
       ent->update();
    }
}

void Killable::mort() {}