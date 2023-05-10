#include "Killable.hpp"

Killable::Killable() {
    possesseur = this;
    Sprite::stockeur->addCircEntite(this);
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

void Killable::moveAllCollision(Vector2D& v) {
    // float porte = v.norme + rayon;
    // Collision avec les cercles :
    std::vector<Entite*>& list1 = *(stockeur->getCircEntiteVector());
    for (uint16_t i=0; i<list1.size(); i++) { // max 65000 Entite :O
        // std::cout << "collision circ entre : " << this << "(" << states->spriteName << ")" << " et " << list1[i] << std::endl;
        
        // On pourrait ajouter un test pour vérifier que l'Entite est à porté.
        Entite::moveCollisionCercle(list1[i], v);
        // if (v.norme == 0) { // Peut accélérer la boucle si les Entite ont beaucoup tendance à se bloquer
        //     break;
        // }
    }

    // Collision avec les rectangles :
    std::vector<Entite*>& list2 = *(stockeur->getRectEntiteVector());
    for (uint16_t i=0; i<list2.size(); i++) { // max 65000 Entite :O
        // std::cout << "collision rect entre : " << this << " et " << list2[i] << std::endl;
        // On pourrait ajouter un test pour vérifier que l'Entite est à porté.
        Entite::moveCollisionRectangle(list2[i], v);
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