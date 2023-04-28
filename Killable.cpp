#include "Killable.hpp"

Killable::Killable(std::string spriteName) : Entite(spriteName) {}

void Killable::translate(float dx, float dy) {
    Entite::translate(dx, dy); // Le Killable se déplace lui-même.
    for (uint8_t i=0; i < entite.size(); i++) {
       entite[i]->translate(dx, dy);
    }
}