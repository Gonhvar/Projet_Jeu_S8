#include "Killable.hpp"

Killable(std::string& spriteName) : Entite(spriteName) {}

Killable::translate(float dx, float dy) {
    for (int i=0; i<entite.size(); i++) {
       entite[i].translate(dx, dy);
    }
}