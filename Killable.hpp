#ifndef KILLABLE_HPP
#define KILLABLE_HPP

#pragma once
#include "Entite.hpp"

class Killable : public Entite {
    // a priori c'est une classe virtuelle pure
    // Parce qu'il n'y a pas littérallement de Killable.
    // Il y a des mobs spécifiques qui sont des Killable, le Mc aussi

    // Killable hérite d'Entite car il y a beaucoup de paramètres et de fonctions similaires dans Entite et Killable
    // A priori, un Killable a toujours une Entite donc autant faire en sorte que c'en soit une.
    // Si on veut qu'un Killable contienne plus d'Entite on les rajoute dans le tableau entite.

protected :
    std::vector<Entite*> entite;

public :
    Killable() = default;
    Killable(std::string spriteName);

    void translate(float dx, float dy);
};

#endif